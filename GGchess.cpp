// GGchess.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "GGchess.h"
#include "chess.h"
#include "data.h"
#include "pregen.h"
#include <shellapi.h>
#include <sys/stat.h>
#include <io.h>
#include <fcntl.h>
#include <share.h>


#define MAX_LOADSTRING 100




int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{

#ifdef USE_WINLICENSE

VM_START_WITHLEVEL(12) 

	int Status;


	Status = WLRegGetStatus(NULL);

	if(Status == 1){		//只有1是注册成功的
		//MessageBox(NULL, "(1)!!", "注册成功了!!", MB_OK | MB_ICONERROR);
	}
	else{					//这儿还没注册成功 
		//先读入注册文件，看能不能注册成功, 

		char *filepart;

		if(SearchPath(NULL,"GGchess.exe",NULL,MSG_SIZ,installDir,&filepart)){
			*filepart = NULLCHAR;
		}
		else{
			GetCurrentDirectory(MSG_SIZ,installDir);
		}

		if(strlen(installDir) < 5){
			exit(0);
		}

		//打开注册文件

		char pRegName[1024];

		sprintf_s(pRegName,1024,"%s%s", installDir,"mreg.bin");

		int pFile;
		char rbuf[4096];

		errno_t err = _sopen_s(&pFile,pRegName,_O_RDONLY, _SH_DENYNO,
			_S_IREAD | _S_IWRITE);

		if(err == 0){
			int byteRead = _read(pFile,rbuf,2048);

			_close(pFile);

			if(byteRead > 2000){
				exit(0);
			}

			

			//*********************************************************************
			//解密一下

			const char key[18] = {
				//00 01 02,03 04 05 06 07 08 09 10 11 12 13 14 15 16 17
				  25,15,75,74,66,55,15,37,71,64,34,25,87,81,43,19,85,47,
			};

			int k = 0;

			for(int i = 0; i < 2000; i++){

				char old = rbuf[i];

				rbuf[i] ^= key[k++];

				if(rbuf[i] == 0 || rbuf[i] < 32 || rbuf[i] > 125){
					rbuf[i] = old;
				}

				if(k>16){
					k = 0;
				}
			}
		}
		else{
			
		}		
		//***********************************************************************

		rbuf[2000] = 0;
		rbuf[2001] = 0;

		char keybuf[4096];

		for(int k = 0; k < 2048; k++){
			keybuf[k] = rbuf[k];

			if(rbuf[k] == 0){
				break;
			}
		}
        
		if(!WLRegNormalKeyCheck(keybuf)){
			
			DialogBox(NULL,(LPSTR)MAKEINTRESOURCE(IDD_FIRST_DIAG),NULL,(DLGPROC)firstDlgProc);
		}
		else{

			DeleteFile(pRegName);

			WLRegNormalKeyInstallToFile(keybuf);
			
			
			MessageBox(NULL, "感谢您的注册, 请重新启动本程序!!", "注册成功了!!", MB_OK | MB_ICONERROR);			
			
			WLRestartApplication();
		}
	}	


VM_END

#endif


#ifdef USE_WINLICENSE
	REGISTERED_START
#endif

    UNREFERENCED_PARAMETER(hPrevInstance);
    //UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    MSG msg;
    //HACCEL hAccelTable;
    HACCEL hAccelMain, hAccelNoAlt;

    appData.debugFP = stderr;

    OBS[0] = new dispboard_t[1];

    memset(OBS[0],0,sizeof(dispboard_t));

    OBS[0]->first.table 
        = OBS[0]->second.table 
        = OBS[0]->ics.table = 0;

    LoadLibrary("RICHED32.DLL"); 
 
#ifdef USE_WINLICENSE
	VM_START
#endif

    initPreGen();       //初始化走步

#ifdef USE_WINLICENSE
	VM_END
#endif

    // Initialize global strings
    LoadString(hInstance, IDS_APP_TITLE, szTitle,       MAX_LOADSTRING);
    LoadString(hInstance, IDC_GGCHESS,   szWindowClass, MAX_LOADSTRING);
    appData.iconWhite	= LoadIcon(hInstance,"icon_white");
    appData.iconBlack	= LoadIcon(hInstance,"icon_black");

    MyRegisterClass(hInstance);

    // Perform application initialization:         //应用程序的初始化
    if (!InitInstance (hInstance, nCmdShow,lpCmdLine)) {
        return FALSE;
    }
    //sqlite3 *db;



    //sqlite3_open("",&db);

    //加速键处理
    hAccelMain  = LoadAccelerators(hInstance, (LPCTSTR)IDC_GGCHESS);
    hAccelNoAlt = LoadAccelerators(hInstance,"NO_ALT");

    // 主消息循环:
    while (GetMessage(&msg, NULL, 0, 0)) 	{
        if (!(!appData.Afrozen && TranslateAccelerator(OBS[0]->hwndThis, hAccelMain, &msg))     //加速键
            && !(!DLG.hwndConsole && TranslateAccelerator(OBS[0]->hwndThis,hAccelNoAlt,&msg))) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

#ifdef USE_WINLICENSE
	REGISTERED_END
#endif

    return (int) msg.wParam;


}


//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM 
MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX); 

    wcex.style			= CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc	= (WNDPROC)WndProc;
    wcex.cbClsExtra		= 0;
    wcex.cbWndExtra		= 0;
    wcex.hInstance		= hInstance;
    wcex.hIcon			= appData.iconWhite;
    wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground	= (HBRUSH)(COLOR_BTNFACE+1);
    wcex.lpszMenuName	= (LPCTSTR)IDC_GGCHESS;
    wcex.lpszClassName	= szWindowClass;
    wcex.hIconSm		= appData.iconWhite;

    if(!RegisterClassEx(&wcex))   return false;			//注册主窗口 DIS.iconWhite

    ////****************************************************************************
    //wcex.style			= CS_HREDRAW | CS_VREDRAW;
    //wcex.lpfnWndProc    = (WNDPROC)ConsoleWndProc;
    //wcex.cbClsExtra     = 0;
    //wcex.hbrBackground  = (HBRUSH)DLGWINDOWEXTRA;
    //wcex.hInstance      = hInstance;
    ////wcex.hIcon			= LoadIcon(hInstance,"icon_white");
    //wcex.hIcon			= DIS.iconWhite;
    //wcex.hCursor        = LoadCursor(NULL,IDC_ARROW);
    //wcex.hbrBackground	= (HBRUSH)(COLOR_MENU+1);
    //wcex.lpszMenuName   = NULL;
    //wcex.lpszClassName  = szConsoleName;

    //if(!RegisterClassEx(&wcex)){
    //    return false;                 //注册连线窗口	
    //}
    //****************************************************************************

    return true;
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL 
InitInstance(HINSTANCE hInstance, int nCmdShow,LPSTR lpCmdLine){
    HWND hWnd;
    int  ibs;
    WINDOWPLACEMENT wp;
    char *filepart;

    hInst = hInstance; // 将实例句柄存储在全局变量中

    //当前目录确认  //!CycloneGui  GGchess
    if(SearchPath(NULL,"GGchess.exe",NULL,MSG_SIZ,installDir,&filepart)){
        *filepart = NULLCHAR;
    }
    else{
        GetCurrentDirectory(MSG_SIZ,installDir);
    }

    InitAppData(lpCmdLine);     /* Get run-time parameters */

//#ifdef DEBUG_MODE
//    appData.debugMode = TRUE;
//#else
//    appData.debugMode = FALSE;
//#endif

    //appData.debugMode = FALSE;
#ifdef DEBUG_MODE
    //if(appData.debugMode){      //调试模式  
    char buf[MAX_PATH];
    sprintf_s(buf,MAX_PATH,"%s%s",installDir,"GGchess.debug");
    errno_t err = fopen_s(&appData.debugFP,buf,"w");  
    if(err != 0){
        //int ddd = 0;
        MessageBox(NULL,"不能打开调试文件","出错啦",MB_OK);
        return FALSE;
    }
    else{
        //setvbuf(DIS.debugFP,NULL,NULL,0);
        //fwrite(
    }
    //}
#endif

    InitBackEnd1();

    hWnd  = CreateWindow(szWindowClass,                     //建立主窗口
        szTitle,
        //WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX,
        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX,
        CW_USEDEFAULT,
        0,
        CW_USEDEFAULT,	//680,
        0,				//570, 
        NULL,
        NULL,
        hInstance,
        NULL);

    if (!hWnd){
        return FALSE;
    }

	dispboard_t *pDis = OBS[0];

    pDis->hwndThis = hWnd;        //保存主窗口句柄

    hStatusBar  = CreateStatus(hWnd);
    hwndToolBar = CreateAToolBar(hWnd);	

    //DIS.ucci         = UCCI_UCCI;
    pDis->iconCurrent	 = appData.iconWhite;

    InitDrawingColors(pDis);

    pDis->screenHeight = GetSystemMetrics(SM_CYSCREEN);   //高
    pDis->screenWidth  = GetSystemMetrics(SM_CXSCREEN);   //宽

    for(ibs = (int)NUM_SIZES - 1; ibs >= 0; ibs--){
        //用每一个board尺寸与屏幕尺寸比较,缺省时使用匹配屏幕的最大使用尺寸*/
        InitDrawingSizes(pDis,(BoardSize)ibs, 0);
        //如果是-1,就表示上次还没有正确的尺寸
        if (pDis->bsize== (BoardSize)-1 
            &&  pDis->winHeight <= pDis->screenHeight ) {
            pDis->bsize = (BoardSize)ibs;
            break;
        }
    }

    if(appData.winWidth != -1){					//得到上回保存的placement
        RECT crect;
        GetClientRect(hWnd, &crect);
        WINDOWPLACEMENT wp;
        wp.length					= sizeof(WINDOWPLACEMENT);
        wp.flags					= WPF_RESTORETOMAXIMIZED;
        wp.showCmd					= SW_SHOW;
        wp.rcNormalPosition.left    = crect.left;
        wp.rcNormalPosition.top     = crect.top;
        wp.rcNormalPosition.right   = crect.left + appData.winWidth;
        wp.rcNormalPosition.bottom  = crect.left + OBS[0]->winHeight;
        SetWindowPlacement(hWnd,&wp);			
    }
    InitDrawingSizes(pDis,pDis->bsize,0);    //初始化显示区的大小

    InitMenuChecks();                 //只有退出保存和通讯端口两项

    appData.buttonCount = GetSystemMetrics(SM_CMOUSEBUTTONS);   //鼠标的按钮数量

    /* Make a console window if needed */
    //if (appData.icsActive) {
    //    ConsoleCreate();
    //}

    /* Make the window visible; update its client area; and return "success" */
    EnsureOnScreen(pDis, &pDis->boardX, &pDis->boardY);
    wp.length = sizeof(WINDOWPLACEMENT);
    wp.flags = 0;
    wp.showCmd = nCmdShow;
    wp.ptMaxPosition.x = wp.ptMaxPosition.y = 0;
    wp.rcNormalPosition.left  = pDis->boardX;
    wp.rcNormalPosition.right = pDis->boardX  + pDis->winWidth;
    wp.rcNormalPosition.top   = pDis->boardY;
    wp.rcNormalPosition.bottom = pDis->boardY + pDis->winHeight;
    SetWindowPlacement(hWnd, &wp);

    SetWindowPos(hWnd, appData.AalwaysOnTop ? HWND_TOPMOST : HWND_NOTOPMOST,
        0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
    //if (DIS.hwndConsole) {
    //    //#if AOT_CONSOLE
    //    //	  SetWindowPos(hwndConsole, alwaysOnTop ? HWND_TOPMOST : HWND_NOTOPMOST,
    //    //		  0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
    //    //#endif
    //    ShowWindow(DIS.hwndConsole, nCmdShow);
    //}

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    DLG_Rich_Log_Event();      //显示日志窗口

    initIcs();				   //初始化连线帐号

    SetIcsTitleName("尚未联机,按<连接>可连接网络下棋");

#ifdef USE_BerKeley_DB
	BD_initEnv(MST);			//初始化环境, BK 用于开局库的制作
#endif 


#ifdef USE_SQL_LITE_DATABASE   
   //initSqlLiteDB   ();
#endif

    InitBackEnd2();

    ThawUI();

	DLG_BOOK_Event();      //开始不显示棋库列表

	ResetGameEvent(OBS[0]);

#ifdef USE_WINLICENSE		//定义了加密

	VM_START

	if(wlIsRegistered == WLRegGetStatus(NULL)){
		char pName[256];
		char pCompanyName[256];
		char pCustomData[512];

		if(WLRegGetLicenseInfo(pName,pCompanyName,pCustomData)){
			char buf[256];
			sprintf_s(buf,sizeof(buf),"已注册给：%s, 感谢您使用本软件!",pName);
			SetWindowText(hWnd,buf);

			LogOut("\n本软件已注册给：\n用户: ");
			LogOut(pName);
			LogOut("\n公司名:");
			LogOut(pCompanyName);
			LogOut("\n其它信息：");
			LogOut(pCustomData);
		}
	}
	else{
		LogOut("对不起，您可能使用的是盗版，将在５秒后退出!");
		Sleep(1000);
		exit(0);
	}

	VM_END

#endif



    //LoadChessProgramState(&DIS.first,hwndMain);			    //调用第一个引擎
    //LoadChessProgramState(&DIS.second,hwndMain);			//调用第二个引擎






#ifdef USE_MY_PROTECT										//使用我的保护方法
VM_START

	buf[1024];

	sprintf_s(buf,1024,
		"%s%s",installDir,"GGchess.exe");

	HANDLE mfile =  CreateFile(buf,
		GENERIC_READ,          // open for reading
		FILE_SHARE_READ,       // share for reading
		NULL,                  // default security 
		OPEN_EXISTING,         // existing file only
		FILE_ATTRIBUTE_NORMAL, // normal file
		NULL);                 // no attr. template

	if (mfile == INVALID_HANDLE_VALUE) 
	{ 
		//printf("Could not open file (error %d)\n", GetLastError());
		exit(0);  //直接退出了
	}


	 int fsize = GetFileSize(mfile,NULL);

	 if(fsize > MAX_file_size || fsize < MIN_file_size){
		exit(0);
	 }

	 //int test = 0;
VM_END
#endif

    return TRUE;
}
//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT	CALLBACK				//主窗口处理程序
WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
    int wmId, wmEvent;
    //PAINTSTRUCT ps;
    //HDC hdc;
    switch (message) {
        case WM_CREATE:
            //random_init();


            break;
        case WM_PAINT:				//重绘窗口
            PaintProc(OBS[0]);
            break;
        case WM_ERASEBKGND:
            if (IsIconic(hWnd)) {
                /* Cheat; change the message */
                return (DefWindowProc(hWnd, WM_ICONERASEBKGND, wParam, lParam));
            } 
            else {
                return (DefWindowProc(hWnd, message, wParam, lParam));
            }
            break;
        case WM_CHAR:				//键盘输入信息			
            if (appData.icsActive) {
                //if (wParam == '\t') {
                //	if (GetKeyState(VK_SHIFT) < 0) {
                //		/* shifted */
                //		HWND h = GetDlgItem(hwndConsole, OPT_ConsoleInput);
                //		if (IsIconic(hwndConsole)) ShowWindow(hwndConsole, SW_RESTORE);
                //		SetFocus(h);
                //	} else {
                //		/* unshifted */
                //		HWND h = GetDlgItem(hwndConsole, OPT_ConsoleText);
                //		if (IsIconic(hwndConsole)) ShowWindow(hwndConsole, SW_RESTORE);
                //		SetFocus(h);
                //	}
                //} else {
                //	HWND h = GetDlgItem(hwndConsole, OPT_ConsoleInput);
                //	if (IsIconic(hwndConsole)) ShowWindow(hwndConsole, SW_RESTORE);
                //	SetFocus(h);
                //	SendMessage(h, message, wParam, lParam);
                //}
            } 
            else if (isalpha((char)wParam) || isdigit((char)wParam)) {
                //PopUpMoveDialog((char)wParam);
            }
            break;
        case WM_COMMAND:			//菜单或工具条
            wmId    = LOWORD(wParam); 
            wmEvent = HIWORD(wParam); 
            if(lParam == NULL){ // ;菜单总是NULL// 分析菜单选择:				
                switch (wmId){
                    //托盘菜单
        case ID_NOTEMENU_RESTORE:
            ShowWindow(hWnd,SW_RESTORE);
            break;
        case ID_NOTEMENU_EXIT:
            SendMessage(hWnd,WM_CLOSE,0,0);
            break;
            //*****************************************
        case IDM_NewGame:				// Reset Game,也就是新开一局哇
            ResetGameEvent(OBS[0]);
            AnalysisPopDown();
             //
            break;					
        case IDM_LoadGame:
            LoadGameDialog(hWnd, "Load Game from File");
            break;
        case IDM_Backward:
            BackwardEvent(OBS[0]);
            SetFocus(hWnd);
            break;
        case IDM_Forward:
            ForwardEvent(OBS[0]);
            SetFocus(hWnd);
            break;

        case IDM_ToStart:
            ToStartEvent(OBS[0]);
            SetFocus(hWnd);
            break;
        case IDM_TwoMachines:
            TwoMachinesEvent();
            /*
            * refresh the tags dialog only if it's visible
            */
            //if (DIS.gameMode == TwoMachinesPlay && IsWindowVisible(editTagsDialog)) {
            //	char *tags;
            //	tags = PGNTags(&gameInfo);
            //	TagsPopUp(tags, CmailMsg());
            //	free(tags);
            //}
            break;
        case IDM_MachineWhite:   //机器走红方
            //MachineWhiteEvent();




            MachinePlayEvent(&OBS[0]->first);

            /*
            * refresh the tags dialog only if it's visible
            */
            //if (gameMode == MachinePlaysWhite && IsWindowVisible(editTagsDialog)) {
            //	char *tags;
            //	tags = PGNTags(&gameInfo);
            //	TagsPopUp(tags, CmailMsg());
            //	free(tags);
            //}
            break;
        case IDM_MachineBlack:

            MachinePlayEvent(&OBS[0]->second);

            //MachineBlackEvent();
            /*
            * refresh the tags dialog only if it's visible
            */
            //if (gameMode == MachinePlaysBlack && IsWindowVisible(editTagsDialog)) {
            //	char *tags;
            //	tags = PGNTags(&gameInfo);
            //	TagsPopUp(tags, CmailMsg());
            //	free(tags);
            //}
            break;
        case IDM_FlipView:
            FlipViewEvent(OBS[0]);						
            break;

        case IDM_ToEnd:
            ToEndEvent(OBS[0]);
            SetFocus(hWnd);
            break;
        case IDM_GeneralOptions:			//通用选项菜单
            GeneralOptionsPopup(hWnd);
            break;
        case IDM_EditGame:
            EditGameEvent(OBS[0]);
            break;
        case IDM_TimeControl:
            YqSetOptionsPopup(0);
            break;
        case IDM_EditPosition:
            EditPositionEvent();
            break;
        case IDM_SaveSettings:
            //SaveSettings(DIS.settingsFileName);
            SaveSettingDataToSqlite();
            break;
        case IDM_SaveSettingsOnExit:
            appData.AsaveSettingsOnExit = !appData.AsaveSettingsOnExit;
            (void) CheckMenuItem(GetMenu(OBS[0]->hwndThis), IDM_SaveSettingsOnExit,
                MF_BYCOMMAND|(appData.AsaveSettingsOnExit ?  MF_CHECKED : MF_UNCHECKED));
            break;
            //-----------------------------------------

        case IDM_ABOUT:
            DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
            //DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
            //***********************************窗口菜单
        //case IDM_ShowStepListDlg:
        //    ShowStepListEvent();
        //    break;
        //case IDM_ShowTimeDisplay:
        //    TimeDisplayListEvent();
        //    break;
        case IDM_BOOK_DLG:
            DLG_BOOK_Event();
            break;
        case IDM_RichLog:
            DLG_Rich_Log_Event();
            break;
        case IDM_DlgDefaultPosition:
            DlgDefaultPosition();
            break;
            //*******************************************

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
                }
            }			
            else if( (HWND)lParam == hwndToolBar){ //工具条消息   
                switch(wmId){
        case IDT_NEW:                  //新建一局游戏
            //TestIsSame();
            ResetGameEvent(OBS[0]);


            //LoadChessProgramState(&DIS.first);

            break;

        case IDT_IMPORT:
            if(SendMessage(hwndToolBar,TB_ISBUTTONCHECKED,
                IDT_IMPORT,0)){//电脑走棋按钮按下了
#ifdef USE_MYSQL_DATABASE
                    Import_QJ_To_Mysql_Event();
#endif
            }
            break;					
        case IDT_CANJU:					//摆局按钮


            //if(SendMessage(hwndToolBar,TB_ISBUTTONCHECKED,IDT_CANJU,0)){							
            //if(DispTotalNum != 0){
            //	if(MessageBox(hwndMain,
            //		"确认将清除当前的内容,去消将返回！",
            //		"注意：当前已有棋步！",
            //		MB_OKCANCEL) != IDOK){  //如果按的不是确认
            //			return 0;	
            //		}
            //}
            //initBaiJu(&DispBoard);
            //	initBaiJu(&DispBoard);							
            //}else{
            //	//得判断棋局是不是正常哇
            //	if(!isCanFinishBaiJu(&DispBoard)){
            //		
            //	}
            //}
            //ManBaiCanJu();
            /*extern char		   sql_host[MSG_SIZ/2];
            extern char        sql_user[MSG_SIZ/2];
            extern char        sql_pass[MSG_SIZ/2];
            extern int         sql_port;
            extern char        sql_db[MSG_SIZ/2];*/
            //MysqlCreateConnect(&mysql,sql_host,
            //	sql_user,sql_pass,sql_db,sql_port);
            //Sql2000_To_Mysql_Event();
            //Web_To_Mysql_Event();
            break;
        case IDT_CORRECT_MAN:
            //GameQJ gg;
            #ifdef USE_MYSQL_DATABASE
            MysqlGetOneUncheckGGqj(&DIS.GGQJ,&DIS.mysql);
#endif
            break;
        case IDT_CHANGE_BR:				   //改变上下棋盘
            //Change_BlueRed();
            break;
        case IDT_CHANGE_RIGHT_LEFT:		//改变左右显示棋盘
            //Change_Right_Left();
            break;
        case IDT_Backward:
            BackwardEvent(OBS[0]);
            SetFocus(hWnd);
            break;
        case IDT_Forward:
            ForwardEvent(OBS[0]);
            SetFocus(hWnd);
            break;

        case IDT_ToStart:
            ToStartEvent(OBS[0]);
            SetFocus(hWnd);
            break;
        case IDT_FLIP:
            FlipViewEvent(OBS[0]);
            break;

        case IDT_ToEnd:
            ToEndEvent(OBS[0]);
            SetFocus(hWnd);
            break;
        case IDT_LEARN_QK:              //学习棋局
            //MysqlGetOneCheckedAndLearn(GameQJ *pgg, MYSQL *my);
            //MysqlGetOneCheckedAndLearn(&DIS.GGQJ, &DIS.mysql);
            if(SendMessage(hwndToolBar,TB_ISBUTTONCHECKED,IDT_LEARN_QK,0)){
#ifdef USE_MYSQL_DATABASE
                LearnChecked_QJ_To_Mysql_Event();
#endif
            }

            //TestFaceEvent();
            break;
        case IDT_COM_RED: {              //按下了第 1 个引擎            
            //MachineWhiteEvent();  //TBSTATE_CHECKED
            ////if(SendMessage(hwndToolBar,TB_CHECKBUTTON,but,0)){   //如果是引擎按钮按下了

            //ChessProgramState *cps = &OBS[0]->first;

            ////int k = SendMessage(hwndToolBar,TB_GETSTATE,IDT_COM_RED,0);

            //if(SendMessage(hwndToolBar,TB_GETSTATE,IDT_COM_RED,0) & TBSTATE_CHECKED){
            //    MachinePlayEvent(cps);
            //}
            //else{
            //    if(cps->maybeThinking == TRUE){
            //        SendToProgram(DIS,"stop\n", cps);
            //        Sleep(100);
            //    }                
            //    cps->maybeThinking  = FALSE;
            //    cps->playWhat       = NEUTRAL;
            //}  
                          }
            break;
        case IDT_COM_BLUE:  {            //按下了第 2 个引擎
            //MachineBlackEvent();
            //MachinePlayEvent(&DIS.second);
            //ChessProgramState *cps = &OBS[0]->second;

            //if(SendMessage(hwndToolBar,TB_GETSTATE,IDT_COM_BLUE,0) & TBSTATE_CHECKED){
            //    MachinePlayEvent(cps);
            //}
            //else{
            //    if(cps->maybeThinking == TRUE){
            //        SendToProgram("stop\n", cps);
            //        Sleep(100);
            //    }                
            //    cps->maybeThinking  = FALSE;
            //    cps->playWhat       = NEUTRAL;
            //} 
                            }
            break;
		case IDT_HUIQI:					//悔棋
			{ dispboard_t *pDis = OBS[0];
			BackwardEvent(pDis);
			if(pDis->pos->gply > 0){
				pDis->pos->gply--;
			};

			//
			FillBookbyPos(pDis,MST->book);

            SetFocus(hWnd);	
			}
			break;
        case IDT_INTERNET:              //连线到ＩＮＴＥＲＮＥＴ
            InternetPlayEvent();    
            break;
        case IDT_YQ_SET:
            YqSetOptionsPopup(0);
            break;
        default:
            break;
                }			
            }			
            break;
        case WM_USER_Input:
            InputEvent(hWnd, message, wParam, lParam);
            break;
        case WM_SIZE:
            //在工具栏和状态栏编程中，
            //要注意的就是工具栏和状态栏并不会随父窗口的大小
            //变化自己调整位置和大小，所以要在父窗口的 WM_SIZE 
            //消息中来移动和调整它们，这可以简单的把 WM_SIZE 消息传给它们就行了。
            //不必自己再去计算。
            SendMessage(hStatusBar, message,wParam,lParam);
            SendMessage(hwndToolBar,message,wParam,lParam);

            if(LOWORD(wParam) == SIZE_MINIMIZED){//最小化窗口
                Note.cbSize = sizeof(NOTIFYICONDATA);
                Note.hWnd	= hWnd;
                Note.uID    = IDI_TRAY;
                Note.uFlags = NIF_ICON + NIF_MESSAGE + NIF_TIP;
                Note.uCallbackMessage = WM_SHELLNOTIFY;
                Note.hIcon  = OBS[0]->iconCurrent;
                StringCbCopy(Note.szTip,128,"佳佳象棋");
                ShowWindow(hWnd,SW_HIDE);
                Shell_NotifyIcon(NIM_ADD,&Note);			
            }
            //else if(LOWORD(wParam) == SIZE_MAXIMIZED){//最大化窗口SIZE_MAXIMIZED
            //	return 0;				
            //}
            break;
            //case SC_MAXIMIZE:
            //	break;
        case WM_ENTERSIZEMOVE:
            if (hWnd == OBS[0]->hwndThis) {
                OBS[0]->doingSizing = TRUE;
                OBS[0]->lastSizing = 0;
            }
            break;
		case WM_NOTIFY: {			
            //if(wParam == hwndTabID){           //这是ＴＡＢ控件发来的消息哇
            //	NMHDR *lnm = (NMHDR *)lParam;
            //	if(lnm->code == TCN_SELCHANGE){//改变了选项卡哇
            //		ShowWindow(TAB.dlgTab[TAB.tabChosen],SW_HIDE);
            //		TAB.tabChosen = (int)SendMessage(TAB.hwndTab,TCM_GETCURSEL,0,0);
            //		ShowWindow(TAB.dlgTab[TAB.tabChosen],SW_SHOW);
            //		FitTabDialogToTabControl();			//重新调整大小
            //	}				
            //}	

			//if(wParam == IDR_TOOLBAR){
			//	//int test = 0;
			//    static int i = 0;
			//	i++;
			//	if(i%2){
			//		DispStatS("这是工具条信息哇");
			//	}
			//	else{
			//		DispStatS("这是工具条信息哇1");
			//	}
			//}

			NMHDR *lnm = (NMHDR*)lParam;

			if(lnm->code == TTN_NEEDTEXT){
				//static int i = 0;
				//i++;
				//if(i%2){
				//	DispStatS("这是工具条信息哇");
				//}
				//else{
				//	DispStatS("这是工具条信息哇1");
				//}

				TOOLTIPTEXT* ptip = (TOOLTIPTEXT*)lParam;

				//ptip->lpszText = ptip->hdr.idFrom;

				LoadString(hInst,(UINT)ptip->hdr.idFrom,ptip->szText,sizeof(ptip->szText));

				DispStatS(ptip->szText);


			}

						}
            break;
        case WM_SIZING:
            if (hWnd == OBS[0]->hwndThis) {
                OBS[0]->lastSizing = (int)wParam;
            }		
            break;
        case WM_EXITSIZEMOVE:
            if (hWnd == OBS[0]->hwndThis) {
                RECT client;
                OBS[0]->doingSizing = FALSE;
                InvalidateRect(hWnd, &OBS[0]->boardRect, FALSE);
                GetClientRect(hWnd, &client);
                ResizeBoard(OBS[0],client.right, client.bottom, OBS[0]->lastSizing);
                OBS[0]->lastSizing = 0;

                //
                SendEveryObsBoard(WM_USER_MainBoard_Sized,0,0);
            }
            break;
        case WM_SHELLNOTIFY:
            if(LOWORD(wParam) == IDI_TRAY){
                if(lParam == WM_RBUTTONDOWN){
                    POINT pt;
                    GetCursorPos(&pt);
                    SetForegroundWindow(hWnd);
                    HMENU hm = LoadMenu(hInst,MAKEINTRESOURCE(IDR_MENU_NOTE));	
                    hm = GetSubMenu(hm,0);
                    TrackPopupMenu(hm,TPM_RIGHTALIGN|TPM_LEFTBUTTON |
                        TPM_RIGHTBUTTON,pt.x,pt.y,NULL,hWnd,NULL);

                }
                else if(lParam == WM_LBUTTONDOWN){
                    SendMessage(hWnd,WM_COMMAND,ID_NOTEMENU_RESTORE,0);
                    SetForegroundWindow(hWnd);
                }
            }
            break;			
        case WM_LBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_MBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MOUSEMOVE:
            MouseEvent(OBS[0],hWnd, message, wParam, lParam);
            break; 
        case WM_TIMER:			    //自定义时间到了
            switch(wParam){
        case CLOCK_TIMER_ID:
            KillTimer(hWnd, OBS[0]->clockTimerEvent);  /* Simulate one-shot timer as in X */
            OBS[0]->clockTimerEvent = 0;
            DecrementClocks(OBS[0]); /* call into back end */
            break;
        case LOAD_GAME_TIMER_ID:
            KillTimer(hWnd, OBS[0]->loadGameTimerEvent); /* Simulate one-shot timer as in X*/
            OBS[0]->loadGameTimerEvent = 0;
            AutoPlayGameLoop(OBS[0]); /* call into back end */
            break;
        case ANALYSIS_TIMER_ID:
            if ((OBS[0]->gameMode == AnalyzeMode 
                || OBS[0]->gameMode == AnalyzeFile) && 
                appData.periodicUpdates) {
                    AnalysisPeriodicEvent(0);
            } 
            else {
                KillTimer(hWnd, OBS[0]->analysisTimerEvent);
                OBS[0]->analysisTimerEvent = 0;
            }
            break;
        case DELAYED_TIMER_ID:
            KillTimer(hWnd, OBS[0]->delayedTimerEvent);
            OBS[0]->delayedTimerEvent = 0;
            OBS[0]->delayedTimerCallback();
            break;
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_CLOSE:
            if(hWnd == OBS[0]->hwndThis){
                Shell_NotifyIcon(NIM_DELETE, &Note); // 将图标从系统托盘中删除 
                ExitEvent(0);
            }
            break;
        default:
            if(message == WM_TASKBARCREATED ){
                Shell_NotifyIcon(NIM_ADD,&Note);   //任务管理器失败后，重显图标
            }
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}



void
ResetFrontEnd(dispboard_t* pDis){
    pDis->fromX =  pDis->fromY = -1;
    if ( pDis->dragInfo.pos.x != -1 ||  pDis->dragInfo.pos.y != -1) {
         pDis->dragInfo.pos.x =  pDis->dragInfo.pos.y = -1;
         pDis->dragInfo.pos.x =  pDis->dragInfo.pos.y = -1;
         pDis->dragInfo.lastpos =  pDis->dragInfo.pos;
         pDis->dragInfo.start.x =  pDis->dragInfo.start.y = -1;
         pDis->dragInfo.from =  pDis->dragInfo.start;
        ReleaseCapture();
        DrawPosition(pDis,true, NULL);
    }
}

void
ShutDownFrontEnd(){
    if (appData.AsaveSettingsOnExit){			//如果设定退出保存
        //SaveSettings(DIS.settingsFileName);
        SaveSettingDataToSqlite();
    }	
    DeleteClipboardTempFiles();

//#ifdef DEBUG_MODE
//    fflush(DIS.debugFP);
//#endif
}


void
AutoSaveGame(){
    //char *defName;
    //FILE *f;
    //char fileTitle[MSG_SIZ];

    //defName = DefaultFileName("pgn");
    //f = OpenFileDialog(hwndMain, TRUE, defName,"pgn",GAME_FILT, 
    //    "Save Game to File", NULL, fileTitle, NULL);
    //if (f != NULL) {
    //    SaveGame(f, 0, "");
    //    fclose(f);
    //}
}







