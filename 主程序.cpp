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

#define MaxSeDepth  58
#define MinSeDepth  12


int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{

    UNREFERENCED_PARAMETER(hPrevInstance);
    //UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    MSG msg;
    //HACCEL hAccelTable;
    HACCEL hAccelMain, hAccelNoAlt;
#ifdef DEBUG_USE_DEBUG_FILE
    appData.debugFP = stderr;
#endif
    OBS[0] = new dispboard_t[1];

	dispboard_t *pDis = OBS[0];

    memset(pDis,0,sizeof(dispboard_t));

 
	//ChangeDisBoardTable(pDis,0);
	pDis->table = 0;
	pDis->first.pDis  = pDis;

	pDis->first.playWhat  = NEUTRAL;

	PGN* pgn = pDis->pgn;

	swprintf_s(pgn->Red, sizeof(pgn->Red) / sizeof(TCHAR), _T("%s"), _T("刘邦"));
	swprintf_s(pgn->Black, sizeof(pgn->Black) / sizeof(TCHAR), _T("%s"), _T("项羽"));

	pgn->Relo =  2028;
	pgn->Belo =  2018;

	swprintf_s(pgn->round, sizeof(pgn->round) / sizeof(TCHAR), _T("%s"), _T("0-0"));

	hMod = LoadLibrary(_T("Riched20.dll"));

	if (hMod) {
		if (!AfxInitRichEdit2()) {
			AfxMessageBox(_T("AfxInitRichEdit2() 不成功！"));
			return false;
		}
	}



	

	//msft_mod = LoadLibrary(L"Msftedit.dll");

    initPreGen();       //初始化走步

    // Initialize global strings
    LoadString(hInstance, IDS_APP_TITLE, szTitle,       MAX_LOADSTRING);
    LoadString(hInstance, IDC_GGCHESS,   szWindowClass, MAX_LOADSTRING);
    appData.iconWhite	= LoadIcon(hInstance,_T("icon_white"));
    appData.iconBlack	= LoadIcon(hInstance,_T("icon_black"));

	//delete pDis;
	//return 1;

    MyRegisterClass(hInstance);

    // Perform application initialization:         //应用程序的初始化
    if (!InitInstance (hInstance, nCmdShow,lpCmdLine)) {
        return FALSE;
    }

    //加速键处理
    hAccelMain  = LoadAccelerators(hInstance, _T("GGCHESS"));
    hAccelNoAlt = LoadAccelerators(hInstance, _T("NO_ALT"));




    // 主消息循环:
    while (GetMessage(&msg, NULL, 0, 0)) 	{
        if (!(!appData.Afrozen && TranslateAccelerator(pDis->hwndThis, hAccelMain, &msg))     //加速键
            && !(!HWND_CONSOLE && TranslateAccelerator(pDis->hwndThis,hAccelNoAlt,&msg))) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

	delete EvalInfo;
	delete pDis;
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
InitInstance(HINSTANCE hInstance, int nCmdShow,LPTSTR lpCmdLine){
    HWND hWnd;
    int  ibs;
    WINDOWPLACEMENT wp;
    TCHAR *filepart;

	dispboard_t *pDis = OBS[0];
	m_nGdiplusToken = 0;

    hInst = hInstance; // 将实例句柄存储在全局变量中

    //当前目录确认  //!CycloneGui  GGchess
	if (SearchPath(NULL, _T("GGchess.exe"), NULL, MAX_PATH, installDir, &filepart)){
        *filepart = NULLCHAR;
    }
    else{
		GetCurrentDirectory(MAX_PATH, installDir);
    }

	//GetCurrentDirectory(MAX_PATH, installDir);

    InitAppData(lpCmdLine);     /* Get run-time parameters */




    InitBackEnd1(pDis);



	appData.autoSaveGames = TRUE;

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

	

    pDis->hwndThis = hWnd;        //保存主窗口句柄

	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_nGdiplusToken,
		&gdiplusStartupInput, NULL);

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
        wp.rcNormalPosition.bottom  = crect.left + pDis->winHeight;
        SetWindowPlacement(hWnd,&wp);	

		pDis->bsize  = appData.bsize;
    }
    InitDrawingSizes(pDis,pDis->bsize,0);    //初始化显示区的大小

    InitMenuChecks();                 //只有退出保存和通讯端口两项

    appData.buttonCount = GetSystemMetrics(SM_CMOUSEBUTTONS);   //鼠标的按钮数量

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

    SetWindowPos(hWnd, appData.alwaysOnTop ? HWND_TOPMOST : HWND_NOTOPMOST,
        0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    DLG_Rich_Log_Event();      //显示日志窗口

    initIcs();				   //初始化连线帐号
	//pDis->ics.playWhat = NEUTRAL;

    SetIcsTitleName(L"尚未联机,按<连接>可连接网络下棋");

	MST->Book_Init_Ok = FALSE;

	LogOut(_T("正在初始化棋库数据库。。。!\n"));

	memset(MST, 0, sizeof(STOCK_DBS));

	uint32 env_flag = DB_CREATE
		| DB_INIT_MPOOL;      //初始化in-memory cache
							  //|DB_THREAD ;        //数据库句柄可以给多个线程使用

	MST->book_db_name = "book.db";
	MST->good_db_name = "good.db";

	int ret;

	ret = db_env_create(&MST->Env, 0);

	if (ret != 0) {
		LogOut(_T("DB_ERR: Create env: "));
		LogOuts(db_strerror(ret));
		//return ret;
	}

	ret = MST->Env->open(MST->Env,
		CW2A(installDir),
		env_flag,
		0);

	if (ret != 0) {
		LogOut(_T("DB_ERR: Environment open: "));
		LogOuts(db_strerror(ret));
		//return ret;
	}

	//建立book数据库连接

	//ret = db_create(&mst->book,NULL,0);

	ret = db_create(&MST->book, MST->Env, 0);

	if (ret != 0) {
		LogOut(_T("DB_ERR: Create Book: "));
		LogOuts(db_strerror(ret));
		//return ret;
	}



	//mst->book->set_errcall(mst->book, BD_my_error_handler);
	//mst->book->set_errpfx(mst->book, "book->");

	//打开book 数据库
	ret = MST->book->open(MST->book,
		NULL,
		MST->book_db_name,
		NULL,
		DB_HASH,
		DB_CREATE,
		0);

	if (ret != 0) {
		MST->book->err(MST->book, ret, "book file open failed: %s", MST->book_db_name);
		//return ret;
	}

	LogOut(_T("初始化棋库数据库成功!\n"));

	MST->Book_Init_Ok = TRUE;

	MST->back_db = NULL;


	//BD_initEnv2();

	//BD_initEnv(MST);			//初始化环境, BK 用于开局库的制作

    InitBackEnd2(pDis);

    ThawUI();

	ResetGameEvent(pDis);

	pDis->clockMode   = TRUE;
	pDis->mustPonder  = TRUE;

    SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_PONDER, 1);

	SendMessage(hwndToolBar,TB_ENABLEBUTTON,IDT_COM_RED,0); 
	SendMessage(hwndToolBar,TB_ENABLEBUTTON,IDT_COM_BLUE,0); 


	//初始化用第一个引擎的时间设定
	GetTimeInfoFromCps(pDis, &pDis->TimeDisp[WHITE], &pDis->first);

	DisplayBothClocks(pDis);

    LoadChessProgramState(&pDis->first, &pDis->first, hWnd);			//调用第一个引擎
    return TRUE;
}

////////////////////////////////////////////////////////////////////
// 主窗口处理程序
LRESULT	CALLBACK				
WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
    int wmId, wmEvent;
	dispboard_t *pDis = OBS[0];
    switch (message) {
        case WM_CREATE:
            //random_init();
            break;
        case WM_PAINT:				//重绘窗口
            PaintProc(pDis);
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

		case WM_USER_YqLoad_OK:	{		//引擎加载成功了
			ChessProgramState *loadokcps = (ChessProgramState*)lParam;

			//loadokcps->playWhat = NEUTRAL;

			if(loadokcps->loadPre == &pDis->first){
				SendToPlayerByColor(L"\n\n第 1 引擎加载成功了!!\n",ColorShout,TRUE);
				SendMessage(hwndToolBar,TB_ENABLEBUTTON,IDT_COM_RED,1); 								
			}
			else{
				SendToPlayerByColor(L"出错了，加载成功的引擎不是 1 , 或 2 引擎!!\n",ColorShout,FALSE);
			}

			//将引擎的数据拷到相应的显示中去
			if(loadokcps->playWhat != NEUTRAL){
				GetTimeInfoFromCps(pDis, &pDis->TimeDisp[loadokcps->playWhat], loadokcps);
			}

			LogOut(loadokcps->UCCI_name);		
			LogOut(loadokcps->UCCI_path);

			loadokcps->cps_stat = Cps_Waiting;   //正在等待输入命令  

			//1, 得到CPS的控制参数
			//GetTimeSetInfoFromCps(loadokcps);				
			//2, 发送初始参数到CPS
			SendControlParameterToCps(loadokcps); 
								}
			break;

		case WM_USER_YqUpload_OK:			//引擎已卸载成功了
			{
				ChessProgramState *uploadokcps = (ChessProgramState*)lParam;

				uploadokcps->playWhat = NEUTRAL;

				LogOut(_T("\n以下引擎\n"));
				LogOut(uploadokcps->UCCI_name);
				LogOut(_T("\n已卸载成功"));

				if(uploadokcps->loadWhich != NULL){
					LogOut(_T("\n正在加载引擎："));
				    LogOut(uploadokcps->loadWhich->UCCI_name);
					LogOut(_T("\n可能要一些时间，请稍候....\n"));

					StartChessProgram(uploadokcps->loadWhich);
				}
			}
			break;
		//
		case WM_USER_ICS_INFO:{				//联网信息输入


			//LogOut("\nics message*********\n");
			//LogOut((char*)lParam);

			if(HandleTableIcsMessage(pDis,(TCHAR*)lParam)){
				//LogOut("\n成功");
			}
			else{
				TCHAR str[2048];			//太小了缓冲区溢出
				swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("\n 棋桌(%d)信息处理没有成功\n"), pDis->table);
				//LogOut(str);
				SendToPlayerByColor(str,ColorShout,FALSE);
				LogOut((TCHAR*)lParam);
			}
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
            ResetGameEvent(pDis);
            AnalysisPopDown();
             //
            break;					
        case IDM_LoadGame:
            LoadGameDialog(hWnd, "Load Game from File");
            break;
        case IDM_Backward:
            BackwardEvent(pDis);
            SetFocus(hWnd);
            break;
        case IDM_Forward:
            ForwardEvent(pDis);
            SetFocus(hWnd);
            break;

        case IDM_ToStart:
            ToStartEvent(pDis);
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

            break;
        case IDM_MachineBlack:

            break;
        case IDM_FlipView:
            FlipViewEvent(pDis);						
            break;

        case IDM_ToEnd:
            ToEndEvent(pDis);
            SetFocus(hWnd);
            break;
        case IDM_GeneralOptions:			//通用选项菜单
            GeneralOptionsPopup(hWnd);
            break;
        case IDM_EditGame:
            EditGameEvent(pDis);
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
            (void) CheckMenuItem(GetMenu(pDis->hwndThis), IDM_SaveSettingsOnExit,
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

		case ID_ExportAllUbb:
			ExportAllUbb();    //将棋库中棋局全部输出为UBB格式的, 以便放到网上
			break;
        case IDM_BOOK_DLG:
            //DLG_BOOK_Event();
            break;
        case IDM_RichLog:
            DLG_Rich_Log_Event();
            break;
        case IDM_DlgDefaultPosition:
            DlgDefaultPosition();
            break;
		case IDM_PastePosition:
			PasteFENFromClipboard(pDis);							  
			break;
		case IDM_CopyGame:
			CopyGameToClipboardUBB(pDis,TRUE);
			break;
		case IDM_UBB:
			CopyUBBToClipboard(pDis);
			break;
		case IDM_PasteGame:
			PasteGameFromClipboard(pDis);
			break;
		case IDM_CopyPosition:
			CopyFENToClipboard(pDis);
			break;
            //*******************************************
		case IDM_BackUp_Book:  //备份棋库
			Back_Up_Book();
			break;
		case IDM_Sounds:
			//SoundOptionsPopup(hWnd);
			break;
		case IDM_Win_Default_Position:
			FitMainTabPosition(OBS[0]);
			break;

		case IDM_export_qj:
			Export_Sqlite_Qj();
			break;

		case IDT_COM_RED:              //按下了第 1 个引擎   
			if (SendMessage(hwndToolBar, TB_GETSTATE, IDT_COM_RED, 0) & TBSTATE_CHECKED){
				SendMessage(hwndToolBar, TB_CHECKBUTTON, IDT_COM_RED, 0);
			}
			else{
				SendMessage(hwndToolBar, TB_CHECKBUTTON, IDT_COM_RED, 1);
			}			
			ToolBarMachineThink(pDis, true);
			break;

		case IDT_ANALIZE_FUN:
			AnalizeEvent(pDis);
			break;

		case IDM_DebugEval:
			SendAllEvalToClipBoard(pDis);
			break;
		case IDM_DebugEvalF4:{   // 红黑交换后再输出局面评估信息。
			//SendAllEvalToClipBoardFlip(pDis);
		}

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
                }
            }			
            else if( (HWND)lParam == hwndToolBar){ //工具条消息   
                switch(wmId){
        case IDT_NEW:                  //新建一局游戏
            ResetGameEvent(pDis);
            break;


        case IDT_IMPORT:
            break;	
		case IDT_SAVE_GAME:    //显示保存棋局窗口

			DLG_SAVE_GAME_Event(0);

			break;
        case IDT_CHANGE_BR:				   //改变上下棋盘
            //Change_BlueRed();
            break;
        case IDT_CHANGE_RIGHT_LEFT:		//改变左右显示棋盘
            //Change_Right_Left();
            break;
        case IDT_Backward:
            BackwardEvent(pDis);
            SetFocus(hWnd);
            break;
        case IDT_Forward:
            ForwardEvent(pDis);
            SetFocus(hWnd);
            break;

        case IDT_ToStart:
            ToStartEvent(pDis);
            SetFocus(hWnd);
            break;
        case IDT_FLIP:
            FlipViewEvent(pDis);
            break;

        case IDT_ToEnd:
            ToEndEvent(pDis);
            SetFocus(hWnd);
            break;

        case IDT_COM_RED:              //按下了第 1 个引擎   
			ToolBarMachineThink(pDis, true);
            break;
        case IDT_COM_BLUE:              //按下了第 2 个引擎
			ToolBarMachineThink(pDis, false);
            break;
		case IDT_HUIQI:					//悔棋
			{ 
			BackwardEvent(pDis);
			if(pDis->pos->gply > 0){
				pDis->pos->gply--;
			};

			//
			FillBookbyPos(pDis,MST->book);

            SetFocus(hWnd);	
			}
			break;
		case IDT_ANALIZE_FUN:
			//if(SendMessage(hwndToolBar,TB_GETSTATE,IDT_ANALIZE_FUN,0) & TBSTATE_CHECKED){
			//	//开始分析功能
			//	//ChessProgramState *cps
			//	AnalizeFun(pDis,TRUE);
			//}
			//else{
			//	//
   //             AnalizeFun(pDis,FALSE);
			//}
			AnalizeEvent(pDis);
			break;
		case IDT_Stop:					//停止引擎工作

			if(pDis->first.cps_stat == Cps_Pondering
				||pDis->first.cps_stat == Cps_Thinking
				||pDis->first.cps_stat == Cps_Analyse){
				SendToProgram(L"stop\n", &pDis->first);
				Sleep(100);
				SendToProgram(L"stop\n", &pDis->first);
				Sleep(100);
			}

			break;
        case IDT_INTERNET:              //连线到ＩＮＴＥＲＮＥＴ
            InternetPlayEvent();    
            break;
        case IDT_YQ_SET:
            YqSetOptionsPopup(0);
            break;
		case IDT_PONDER:				//后台思考按钮

			if(SendMessage(hwndToolBar,TB_GETSTATE,IDT_PONDER,0) & TBSTATE_CHECKED){
				pDis->mustPonder = TRUE;
			}
			else{
				pDis->mustPonder =  FALSE;
			}
			//UCCI_ponder
			break;

		case  IDT_EVAL:		//输出所有的信息到剪贴板

			//SendAllEvalToClipBoard(pDis);

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
                Note.hIcon  = pDis->iconCurrent;
                StringCbCopy(Note.szTip,128,_T("佳佳象棋"));
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
            if (hWnd == pDis->hwndThis) {
                pDis->doingSizing = TRUE;
                pDis->lastSizing = 0;
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
				TOOLTIPTEXT* ptip = (TOOLTIPTEXT*)lParam;
				LoadString(hInst,(UINT)ptip->hdr.idFrom,ptip->szText,sizeof(ptip->szText));
			}

						}
            break;
        case WM_SIZING:
            if (hWnd == pDis->hwndThis) {
                pDis->lastSizing = (int)wParam;
            }		
            break;
        case WM_EXITSIZEMOVE:
            if (hWnd == pDis->hwndThis) {
                RECT client;
                pDis->doingSizing = FALSE;
                InvalidateRect(hWnd, &pDis->boardRect, FALSE);
                GetClientRect(hWnd, &client);
                ResizeBoard(pDis,client.right, client.bottom, pDis->lastSizing);
                pDis->lastSizing = 0;

                //
                //SendEveryObsBoard(WM_USER_MainBoard_Sized,0,0);
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
                    
					//Shell_NotifyIcon(NIM_DELETE, &Note); // 将图标从系统托盘中删除 

					NOTIFYICONDATA tnid; 
					tnid.cbSize = sizeof(NOTIFYICONDATA);
					tnid.hWnd	= hWnd;
					tnid.uID    = IDI_TRAY;

					Shell_NotifyIcon(NIM_DELETE, &tnid);

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
        case WM_MOUSEMOVE:
            MouseEvent(pDis,hWnd, message, wParam, lParam);
            break; 
        case WM_TIMER:			    //自定义时间到了
            switch(wParam){
        case CLOCK_TIMER_ID:
            KillTimer(hWnd, pDis->clockTimerEvent);  /* Simulate one-shot timer as in X */
            pDis->clockTimerEvent = 0;
            DecrementClocks(pDis); /* call into back end */
            break;
        case LOAD_GAME_TIMER_ID:
            KillTimer(hWnd, pDis->loadGameTimerEvent); /* Simulate one-shot timer as in X*/
            pDis->loadGameTimerEvent = 0;
            AutoPlayGameLoop(pDis); /* call into back end */
            break;
        case ANALYSIS_TIMER_ID:
            //if ((pDis->gameMode == AnalyzeMode 
			if ((pDis->gameMode == AnalyzeMode) && 
                appData.periodicUpdates) {
                    AnalysisPeriodicEvent(0);
            } 
            else {
                KillTimer(hWnd, pDis->analysisTimerEvent);
                pDis->analysisTimerEvent = 0;
            }
            break;
        case DELAYED_TIMER_ID:
            KillTimer(hWnd, pDis->delayedTimerEvent);
            pDis->delayedTimerEvent = 0;
            pDis->delayedTimerCallback(pDis);
            break;
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_CLOSE:
            if(hWnd == pDis->hwndThis){
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


BOOL					//自动保存游戏到文件
AutoSaveGame(dispboard_t* pDis){
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

	if(pDis->pgn->isFenGame){
		//
		LogOut(_T("对不起，残局库暂不能保存"));
		return FALSE;
	}

	sqlite3 * db;
	int rc = SqliteOpenDataBase(&db,L3_DB_PGN);

	if(rc != SQLITE_OK){
		LogOut(_T("\n出错啦，不能打开棋局数据库!\n"));
		return TRUE;
	}

	//PgnFromSaveDlg(pDis);

	pDis->pgn->score = BOOK_NOT_RESULT;

	PgnFenFromCurPosition(pDis);	

	pDis->pgn->isChecked = FALSE;
	pDis->pgn->isLearned = FALSE;

	BOOL saveorupok = FALSE;

	int saveId  = -1;
	if(PgnInsertGameToSqlite(pDis,&saveId,db) == SQLITE_OK){
		saveorupok = TRUE;								
	}	

	if(saveorupok){
		SendToPlayerByColor(L"\n保存当前的棋局成功\n", ColorSeek,FALSE);	
	}
	else{
		SendToPlayerByColor(L"\n保存当前的棋局失败了\n",ColorShout,FALSE);	
	}
	sqlite3_close(db);

	return TRUE;
}







