#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

//CMX_183CN_Get_Pass_By_Client(str,passbuf); 
//SendToICSDelayed(passbuf, MXQ_LOG_DELAY_MS);

LRESULT CALLBACK
GoPlaceDialogCallBack(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam){
    //char passbuf[128];
    char *pcommand;
    //bool is183;
    MINMAXINFO* mmi;
    switch(message){
        case WM_INITDIALOG:
            PostMessage(hDlg, WM_SETICON, (WPARAM) TRUE, (LPARAM) appData.iconWhite); 
            return FALSE;            
        case WM_COMMAND:  
            switch(LOWORD(wParam)){
                    case IDC_DIR_1:
                        pcommand = "go 1";
                        break;
                    case IDC_DIR_2:
                        pcommand = "go 2";
                        break;
                    case IDC_DIR_3:
                        pcommand = "go 3";
                        break;
                    case IDC_DIR_4:
                        pcommand = "go 4";
                        break;
                    case IDC_DIR_5:
                        pcommand = "go 5";
                        break;
                    case IDC_DIR_6:
                        pcommand = "go 6";
                        break;
                    case IDC_DIR_7:
                        pcommand = "go 7";
                        break;
                    case IDC_DIR_8:
                        pcommand = "go 8";
                        break;
                    default:
                        return FALSE;
                        break;
                }
            if(appData.ACPSics.ICS_net_id == ICS_MXQ_EN183 ||
                    appData.ACPSics.ICS_net_id == ICS_MXQ_CN183){
                        CMX_183_SEND_CODDING(pcommand);
                        Sleep(100);
                        CMX_183_SEND_CODDING("map");
                }
                else{
                    char buf[256];
                    sprintf_s(buf,sizeof(buf),"%s\n",pcommand);
                    SendToICS(buf);
                    SendToICS("map\n");
                }

            break;
        case WM_SIZE:
            //FitTimeDisplayDlgItem(hDlg);
            break;
        case WM_CLOSE:
            //TimeDisplayListEvent();

            //如果子酱//IDC_GO_PLACE

            SendDlgItemMessage(DLG.hwndConsole,IDC_GO_PLACE,BM_SETCHECK,0,0);
            ShowWindow(hDlg,SW_HIDE);
            //EndDialog(hDlg, LOWORD(wParam));

            //DLG.hwndGoPlace = NULL;

            return (INT_PTR)TRUE;
            break;
        case WM_GETMINMAXINFO:    //避免窗口拉的过小 /* Prevent resizing window too small */
            mmi = (MINMAXINFO*) lParam;
            mmi->ptMinTrackSize.x = 112;
            mmi->ptMinTrackSize.y = 130;
            break;
        default:
            break;
    }
    return FALSE;

    //窗口过程对应于不同的消息有各种不同含义的返回值，
    //而对话框过程返回BOOL类型的值，返回TRUE表示已经处理了某条消息，
    //返回FALSE表示没有处理。“对话框管理器”代码会根据
    //返回值决定是否继续处理某一条消息（惟一的例外是WM_INITDIALOG消息）。
}


void PopGoPlaceDialog(void){
    FARPROC lpProc = MakeProcInstance((FARPROC)GoPlaceDialogCallBack,hInst);
    DLG.hwndGoPlace = CreateDialog(hInst,MAKEINTRESOURCE(IDD_GO_PLACE),
        OBS[0]->hwndThis,(DLGPROC)lpProc);
    FreeProcInstance(lpProc);
    ShowWindow(DLG.hwndGoPlace,SW_HIDE);
    CenterWindow(DLG.hwndGoPlace,OBS[0]->hwndThis);
}



void
ConsoleCreate(){
    //HWND hCons;
    if (DLG.hwndConsole) return; //"WBCONSOLE"
    //hCons = CreateDialog(hInst, szConsoleName, 0, NULL);

    //  FARPROC lpProc = MakeProcInstance((FARPROC)DLG_BOOK_PROC,hInst);
    //DLG.dlgBook = CreateDialog(hInst,MAKEINTRESOURCE(DLG_BOOK),hwndMain,(DLGPROC)lpProc);

    //FARPROC lpProc = MakeProcInstance((FARPROC)ConsoleWndProc,hInst);

    FARPROC lpProc = MakeProcInstance((FARPROC)ConsoleWndProc,hInst);

    //hCons = CreateDialog(hInst,MAKEINTRESOURCE(DLG_InterPlay),hwndMain,(DLGPROC)lpProc);

    FreeProcInstance(lpProc);

    //HWND test = hCons;
    //SendMessage(hCons, WM_INITDIALOG, 0, 0);
}



//void LogOut(ColorClass cc, char* data, bool NotShout){
//
//
//    ColorClass pre = DLG.currentColorClass;
//
//    int len = (int)strlen(data);
//    Colorize(cc,NotShout);
//
//    if(len > 0){       
//        ConsoleOutput(data,len,TRUE);
//        //if(IsReturn){               //加上一个回车
//        //    LogOutput("\n",1,FALSE);
//        //}
//    }
//
//    DLG.currentColorClass = pre;
//
//}

void LogOut(char *data){
    ConsoleOutput(data,(int)strlen(data),true);
    //SendToPlayer(data,(int)strlen(data));
}


VOID
ConsoleOutput(char* data, int length, int forceVisible){
    HWND hText;
    int trim, exlen;
    char *p, *q;
    char buf[CO_MAX+1];
    POINT pEnd;
    RECT rect;
    static int delayLF = 0;
    CHARRANGE savesel, sel;

    //if (DIS.hwndConsole == NULL || length > CO_MAX-100 || length == 0) return;
    //日志窗口句柄
    if(DLG.hwndConsole == NULL || length > CO_MAX-100 || length == 0){
        return;
    }

    p = data;
    q = buf;
    if (delayLF) {
        *q++ = '\r';
        *q++ = '\n';
        delayLF = 0;
    }
    while (length--) {
        if (*p == '\n') {
            if (*++p) {
                *q++ = '\r';
                *q++ = '\n';
            } 
            else {
                delayLF = 1;
            }
        } 
        else if (*p == '\007') {
            MyPlaySound(&appData.Asounds[(int)SoundBell]);
            p++;
        } 
        else {
            *q++ = *p++;
        }
    }
    *q = NULLCHAR;
    //hText = GetDlgItem(DIS.hwndConsole, OPT_ConsoleText);

    hText = DLG.hText;

    SendMessage(hText, EM_HIDESELECTION, TRUE, FALSE);
    /* Save current selection */
    SendMessage(hText, EM_EXGETSEL, 0, (LPARAM)&savesel);
    exlen = GetWindowTextLength(hText);
    /* Find out whether current end of text is visible */
    SendMessage(hText, EM_GETRECT, 0, (LPARAM) &rect);
    SendMessage(hText, EM_POSFROMCHAR, (WPARAM) &pEnd, exlen);
    /* Trim existing text if it's too long */
    if (exlen + (q - buf) > CO_MAX) {
        trim = (int)((CO_TRIM > (q - buf)) ? CO_TRIM : (q - buf));
        sel.cpMin = 0;
        sel.cpMax = trim;
        SendMessage(hText, EM_EXSETSEL, 0, (LPARAM)&sel);
        SendMessage(hText, EM_REPLACESEL, 0, (LPARAM)"");
        exlen -= trim;
        savesel.cpMin -= trim;
        savesel.cpMax -= trim;
        if (exlen < 0) exlen = 0;
        if (savesel.cpMin < 0) savesel.cpMin = 0;
        if (savesel.cpMax < savesel.cpMin) savesel.cpMax = savesel.cpMin;
    }
    /* Append the new text */
    sel.cpMin = exlen;
    sel.cpMax = exlen;
    SendMessage(hText, EM_EXSETSEL, 0, (LPARAM)&sel);
    SendMessage(hText, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&appData.AconsoleCF);
    SendMessage(hText, EM_REPLACESEL, 0, (LPARAM) buf);
    if (forceVisible || exlen == 0 ||
        (rect.left <= pEnd.x && pEnd.x < rect.right &&
        rect.top <= pEnd.y && pEnd.y < rect.bottom)) {
            /* Scroll to make new end of text visible if old end of text
            was visible or new text is an echo of user typein */
            sel.cpMin = 9999999;
            sel.cpMax = 9999999;
            SendMessage(hText, EM_EXSETSEL, 0, (LPARAM)&sel);
            SendMessage(hText, EM_HIDESELECTION, FALSE, FALSE);
            SendMessage(hText, EM_SCROLLCARET, 0, 0);
            SendMessage(hText, EM_HIDESELECTION, TRUE, FALSE);
    }
    if (savesel.cpMax == exlen || forceVisible) {
        /* Move insert point to new end of text if it was at the old
        end of text or if the new text is an echo of user typein */
        sel.cpMin = 9999999;
        sel.cpMax = 9999999;
        SendMessage(hText, EM_EXSETSEL, 0, (LPARAM)&sel);
    } 
    else {
        /* Restore previous selection */
        SendMessage(hText, EM_EXSETSEL, 0, (LPARAM)&savesel);
    }
    SendMessage(hText, EM_HIDESELECTION, FALSE, FALSE);
}



LRESULT CALLBACK        //显示rich_edit子类化
ConsoleTextSubclass(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    //HWND hInput;
    CHARRANGE sel;

    switch (message) {
      case WM_KEYDOWN:
          if (!(GetKeyState(VK_CONTROL) & ~1)) break;
          switch (wParam) {
      case VK_PRIOR:
          SendMessage(hwnd, EM_LINESCROLL, 0, -999999);
          return 0;
      case VK_NEXT:
          sel.cpMin = 999999;
          sel.cpMax = 999999;
          SendMessage(hwnd, EM_EXSETSEL, 0, (LPARAM)&sel);
          SendMessage(hwnd, EM_SCROLLCARET, 0, 0);
          return 0;
          }
          break;
      case WM_CHAR:
          if (wParam == '\t') {
              if (GetKeyState(VK_SHIFT) < 0) {
                  /* shifted */
                  if (IsIconic(OBS[0]->hwndThis)){
                      ShowWindow(OBS[0]->hwndThis, SW_RESTORE);
                  }
                  //if (DIS.buttonDesc[0].hwnd) {
                  //    SetFocus(DIS.buttonDesc[0].hwnd);
                  //} 
                  //else {
                  SetFocus(OBS[0]->hwndThis);
                  //}
              }  else {
                  /* unshifted */
                  //SetFocus(GetDlgItem(DIS.hwndConsole, OPT_ConsoleInput));
                  SetFocus(DLG.hInput);
              }
          } else {
              //hInput = GetDlgItem(DIS.hwndConsole, OPT_ConsoleInput);
              //SetFocus(hInput);
              SetFocus(DLG.hInput);
              SendMessage(DLG.hInput, message, wParam, lParam);
          }
          return 0;
      case WM_PASTE:
          //hInput = GetDlgItem(DIS.hwndConsole, OPT_ConsoleInput);
          //SetFocus(hInput);
          SetFocus(DLG.hInput);
          return SendMessage(DLG.hInput, message, wParam, lParam);
      case WM_MBUTTONDOWN:
          return SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(IDM_QuickPaste, 0), 0);
      case WM_RBUTTONDOWN:
          if (!(GetKeyState(VK_SHIFT) & ~1)) {
              /* Move selection here if it was empty */
              POINT pt;
              pt.x = LOWORD(lParam);
              pt.y = HIWORD(lParam);
              SendMessage(hwnd, EM_EXGETSEL, 0, (LPARAM)&sel);
              if (sel.cpMin == sel.cpMax) {
                  sel.cpMin = (LONG)SendMessage(hwnd, EM_CHARFROMPOS, 0, (LPARAM)&pt); /*doc is wrong*/
                  sel.cpMax = sel.cpMin;
                  SendMessage(hwnd, EM_EXSETSEL, 0, (LPARAM)&sel);
              }
              SendMessage(hwnd, EM_HIDESELECTION, FALSE, FALSE);
          }
          return 0;
      case WM_RBUTTONUP:
          if (GetKeyState(VK_SHIFT) & ~1) {
              SendDlgItemMessage(DLG.hwndConsole, OPT_ConsoleText, 
                  WM_COMMAND, MAKEWPARAM(IDM_QuickPaste, 0), 0);
          } 
          else {
              //POINT pt;
              //HMENU hmenu = LoadIcsTextMenu(DIS.icsTextMenuEntry);
              //SendMessage(hwnd, EM_EXGETSEL, 0, (LPARAM)&sel);
              //if (sel.cpMin == sel.cpMax) {
              //    EnableMenuItem(hmenu, IDM_Copy, MF_BYCOMMAND|MF_GRAYED);
              //    EnableMenuItem(hmenu, IDM_QuickPaste, MF_BYCOMMAND|MF_GRAYED);
              //}
              //if (!IsClipboardFormatAvailable(CF_TEXT)) {
              //    EnableMenuItem(hmenu, IDM_Paste, MF_BYCOMMAND|MF_GRAYED);
              //}
              //pt.x = LOWORD(lParam);
              //pt.y = HIWORD(lParam);
              //MenuPopup(hwnd, pt, hmenu, -1);
          }
          return 0;
      case WM_COMMAND:
          switch (LOWORD(wParam)) {
      case IDM_QuickPaste:
          {
              SendMessage(hwnd, EM_EXGETSEL, 0, (LPARAM)&sel);
              if (sel.cpMin == sel.cpMax) {
                  MessageBeep(MB_ICONEXCLAMATION);
                  return 0;
              }
              SendMessage(hwnd, WM_COPY, 0, 0);
              //hInput = GetDlgItem(DIS.hwndConsole, OPT_ConsoleInput);
              SendMessage(DLG.hInput, WM_PASTE, 0, 0);
              SetFocus(DLG.hInput);
              return 0;
          }
      case IDM_Cut:
          SendMessage(hwnd, WM_CUT, 0, 0);
          return 0;
      case IDM_Paste:
          SendMessage(hwnd, WM_PASTE, 0, 0);
          return 0;
      case IDM_Copy:
          SendMessage(hwnd, WM_COPY, 0, 0);
          return 0;
      default:
          {
              //int i = LOWORD(wParam) - IDM_CommandX;
              //if (i >= 0 && i < ICS_TEXT_MENU_SIZE &&
              //    DIS.icsTextMenuEntry[i].command != NULL) {
              //        CommandX(hwnd, DIS.icsTextMenuEntry[i].command,
              //            DIS.icsTextMenuEntry[i].getname,
              //            DIS.icsTextMenuEntry[i].immediate);
              //        return 0;
              //}
              return 0;
          }
          break;
          }
          break;
    }

    return (*DLG.consoleTextWindowProc)(hwnd,message,wParam,lParam);
}

void USER_INPUT_COMMAND(char *buf){
    char *p;
    if((p = strstr(buf,"position fen ")) != NULL){       //用用户输入了一个局面

    }
}


LRESULT CALLBACK        //输入rich_edit子类化
ConsoleInputSubclass(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){

    char buf[MSG_SIZ];
    char *p;
    static BOOL sendNextChar    = FALSE;
    static BOOL quoteNextChar   = FALSE;
    InputSource *is = DLG.consoleInputSource;
    CHARFORMAT cf;
    CHARRANGE sel;

    //if(appData.icsActive == 0){
    //   return (*DLG.consoleInputWindowProc)(hwnd,message,wParam,lParam);
    //}

    switch(message){
        case WM_CHAR:
            if(!appData.localLineEditing || sendNextChar){
                is->buf[0] = (CHAR)wParam;
                is->count  = 1;
                SendMessage(OBS[0]->hwndThis,WM_USER_Input, 0, (LPARAM)is);
                sendNextChar = FALSE;
                return 0;
            }
            if(quoteNextChar){
                buf[0] = (char)wParam;
                buf[1] = NULLCHAR;
                SendMessage(hwnd,EM_REPLACESEL,TRUE,(LPARAM)buf);
                quoteNextChar = FALSE;
                return 0;
            }
            switch(wParam){
        case '\r':      //Enter Key

            if(appData.icsActive == FALSE){     //还没有登录成功
                int get = GetWindowText(hwnd,buf,sizeof(buf));
                if((p = strstr(buf,"CMD ")) != NULL){
                    USER_INPUT_COMMAND(p);
                }
            }
            else{

                is->count = GetWindowText(hwnd,is->buf,INPUT_SOURCE_BUF_SIZE-1);  
                if(DLG.consoleEcho){
                    SaveInHistory(is->buf);
                }
                is->buf[is->count++] = '\n';
                is->buf[is->count]   = NULLCHAR;
                SendMessage(OBS[0]->hwndThis,WM_USER_Input,0,(LPARAM)is);
                if(DLG.consoleEcho){
                    ConsoleOutput(is->buf,is->count,TRUE);
                }
                else if(appData.localLineEditing){
                    ConsoleOutput("\n",1,TRUE);
                }
            }

            /*fall thru*/
        case '\033':  /*Esecape Key*/
            SetWindowText(hwnd,"");
            cf.cbSize = sizeof(CHARFORMAT);
            cf.dwMask = CFM_COLOR|CFM_BOLD|CFM_ITALIC|CFM_UNDERLINE|CFM_STRIKEOUT;

            if(DLG.consoleEcho){
                cf.crTextColor = appData.AtextAttribs[ColorNormal].color;
            }
            else{
                cf.crTextColor = COLOR_ECHOOFF;
                //DLG.consoleBackgroundColor
            }
            cf.dwEffects = appData.AtextAttribs[ColorNormal].effects;
            SendMessage(hwnd,EM_SETCHARFORMAT,SCF_ALL,(LPARAM)&cf);
            return 0;
        case '\t': /*Tab key */
            if(GetKeyState(VK_SHIFT) < 0){
                /*shifed*/
                SetFocus(DLG.hText);
            }
            else{
                /*unshifed */
                if(IsIconic(OBS[0]->hwndThis)){
                    ShowWindow(OBS[0]->hwndThis,SW_RESTORE);
                }
                //if(DIS.buttonDesc[0].hwnd){
                //    SetFocus(DIS.buttonDesc[0].hwnd);
                //}
                //else{
                SetFocus(OBS[0]->hwndThis);
                //}
            }
            return 0;
        case '\023':    /*Ctrl+S*/
            sendNextChar = TRUE;
            return 0;
        case '\021': /*Ctrl+Q*/
            quoteNextChar = TRUE;
            return 0;
        default:
            break;
            }
            break;
        case WM_KEYDOWN:
            switch(wParam){
        case VK_UP:
            GetWindowText(hwnd,buf,MSG_SIZ);
            p = PrevInHistory(buf);
            if(p != NULL){
                SetWindowText(hwnd,p);
                sel.cpMin = 999999;
                sel.cpMax = 999999;
                SendMessage(hwnd, EM_EXSETSEL, 0, (LPARAM)&sel);
                return 0;
            }
            break;
        case VK_DOWN:
            p = NextInHistory();
            if(p != NULL){
                SetWindowText(hwnd,p);
                sel.cpMin = 999999;
                sel.cpMax = 999999;
                SendMessage(hwnd, EM_EXSETSEL, 0, (LPARAM)&sel);
                return 0;
            }
            break;
        case VK_HOME:
        case VK_END:
            if (!(GetKeyState(VK_CONTROL) & ~1)){
                break;
            }
            /*fall thru*/
        case VK_PRIOR:
        case VK_NEXT:
            SendMessage(DLG.hText,message,wParam, lParam);
            return 0;
            }
            break;
        case WM_MBUTTONDOWN:
            SendDlgItemMessage(DLG.hText,OPT_ConsoleText, 
                WM_COMMAND, MAKEWPARAM(IDM_QuickPaste, 0), 0);
            break;
        case WM_RBUTTONUP:
            if (GetKeyState(VK_SHIFT) & ~1) {
                SendDlgItemMessage(DLG.hText, OPT_ConsoleText, 
                    WM_COMMAND, MAKEWPARAM(IDM_QuickPaste, 0), 0);
            } else {
                POINT pt;
                HMENU hmenu;
                hmenu = LoadMenu(hInst, "InputMenu");
                SendMessage(hwnd, EM_EXGETSEL, 0, (LPARAM)&sel);
                if (sel.cpMin == sel.cpMax) {
                    EnableMenuItem(hmenu, IDM_Copy, MF_BYCOMMAND|MF_GRAYED);
                    EnableMenuItem(hmenu, IDM_Cut, MF_BYCOMMAND|MF_GRAYED);
                }
                if (!IsClipboardFormatAvailable(CF_TEXT)) {
                    EnableMenuItem(hmenu, IDM_Paste, MF_BYCOMMAND|MF_GRAYED);
                }
                pt.x = LOWORD(lParam);
                pt.y = HIWORD(lParam);
                MenuPopup(hwnd, pt, hmenu, -1);
            }
            break;
        case WM_COMMAND:
            switch(LOWORD(wParam)){
        case IDM_Undo:
            SendMessage(hwnd,EM_UNDO,0,0);
            return 0;
        case IDM_SelectAll:
            sel.cpMin = 0;
            sel.cpMax = -1;
            SendMessage(hwnd,EM_EXSETSEL,0,(LPARAM)&sel);
            return 0;
        case IDM_Cut:
            SendMessage(hwnd,WM_CUT,0,0);
            return 0;
        case IDM_Paste:
            SendMessage(hwnd,WM_PASTE,0,0);
            return 0;
        case IDM_Copy:
            SendMessage(hwnd,WM_COPY,0,0);
            return 0;           
            }
            break;
        default:
            break;
    }
    return (*DLG.consoleInputWindowProc)(hwnd,message,wParam,lParam);
}



void FitRichLogDlgPosition(HWND hDlg){

    RECT Rect;
    GetWindowRect(OBS[0]->hwndThis,&Rect);

    int x       = Rect.right;
    int y       = Rect.top ;
    int width   = 320;
    int height  = Rect.bottom - Rect.top;

    SetWindowPos(hDlg,NULL,x,y,width,height,SWP_NOZORDER|SWP_NOACTIVATE);

    ShowWindow(hDlg,SW_SHOW);

    //PostMessage(hDlg,WM_SIZE,0,MAKELONG(width,height));///
}

int 
ConnectToIcs(void){

    char buf[MSG_SIZ];

    appData.useTelnet = false;

    //sprintf_s(appData.icsHost,sizeof(appData.icsHost),"xiangqi.movesky.net");
    //sprintf_s(appData.icsPort,sizeof(appData.icsPort), "3791");

    int err = establish();

    //telnet xiangqi.movesky.net 3791


    if(err != 0){
        //if(*appData.icsCommPort != NULLCHAR){
        //    if (*appData.icsCommPort != NULLCHAR) {
        //        sprintf_s(buf,512, "Could not open comm port %s",  
        //            appData.icsCommPort);
        //    } 
        //    else {
        //        sprintf_s(buf,512, "Could not connect to host %s, port %s",  
        //            appData.icsHost, appData.icsPort);
        //    }
        //    DisplayFatalError(buf, err, 1);
        //    return err;
        //}
        sprintf_s(buf,sizeof(buf),"不能建立连线：网站：%s, 端口：%d\n", 
            appData.ACPSics.ICS_net_host,appData.ACPSics.ICS_net_port);
        LogOut(buf);
        return err;
    }

    //SetICSMode();

    //DIS.telnetISR = 
    //    AddInputSource(DIS.icsPR,FALSE,read_from_ics,&DIS.telnetISR);


    switch(appData.ACPSics.ICS_net_id){

            initIcs();

            case ICS_MXQ_CN:
                //read_from_ics_mxq_cn(isr,closure,data,count,error);
                PopGoPlaceDialog();
                PopIcsBoardDialog();
                appData.AtelnetISR = 
                    AddInputSource(appData.AicsPR,FALSE,read_from_ics_mxq_cn,&appData.AtelnetISR);
                break;
            case ICS_MXQ_EN:
                PopGoPlaceDialog();         //MXQ 转地窗口
                PopIcsBoardDialog();        //MXQ 棋局列表窗口
                appData.AtelnetISR = 
                    AddInputSource(appData.AicsPR,FALSE,read_from_ics_mxq_en,&appData.AtelnetISR);
                break;
            case ICS_MXQ_EN183:
                PopGoPlaceDialog();         //MXQ 转地窗口
                PopIcsBoardDialog();        //MXQ 棋局列表窗口
                appData.AtelnetISR = 
                    AddInputSource(appData.AicsPR,FALSE,read_from_ics_mxq_en183,&appData.AtelnetISR);
                break;
            case ICS_MXQ_CN183:
                PopGoPlaceDialog();         //MXQ 转地窗口
                PopIcsBoardDialog();        //MXQ 棋局列表窗口
                appData.AtelnetISR = 
                    AddInputSource(appData.AicsPR,FALSE,read_from_ics_mxq_cn183,&appData.AtelnetISR);
                break;
            case ICS_QQ:
                appData.AtelnetISR = 
                    AddInputSource(appData.AicsPR,FALSE,read_from_ics_not_ready_know,&appData.AtelnetISR);
                break;
            case ICS_CHINAGAME:
                appData.AtelnetISR = 
                    AddInputSource(appData.AicsPR,FALSE,read_from_ics_not_ready_know,&appData.AtelnetISR);
                break;
            case ICS_OURGAME:
                appData.AtelnetISR = 
                    AddInputSource(appData.AicsPR,FALSE,read_from_ics_not_ready_know,&appData.AtelnetISR);
                break;
            case ICS_GAMEABC:
                appData.AtelnetISR = 
                    AddInputSource(appData.AicsPR,FALSE,read_from_ics_not_ready_know,&appData.AtelnetISR);
                break;
            default:
                appData.AtelnetISR = 
                    AddInputSource(appData.AicsPR,FALSE,read_from_ics_not_ready_know,&appData.AtelnetISR);
                break;
    }

    appData.AfromUserISR =
        AddInputSource(NoProc,FALSE,read_from_player,&appData.AfromUserISR);

    if(err == 0){
        appData.icsActive = true;
        //SetWindowText(DLG.hwndConsole,"日志信息:已联机(尚未登录成功)");
        SetIcsTitleName("已联机(尚未登录成功)");

		//联机后，可显示弈天的其它按钮

		//重新显示一下，将相应的按钮显示出来

		RECT re;
		//GetWindowRect(hDlg,&re);
		GetClientRect(DLG.hwndConsole,&re);
		FitConsoleItemPosition(DLG.hwndConsole,(re.right - re.left),(re.bottom - re.top));	

        //将按钮设置成 退出
        //IDC_ICS_CONNECT
        //SetWindowText(DlgGetItem(
        SetDlgItemText(DLG.hwndConsole,IDC_ICS_CONNECT,"退出");
    }

    appData.colorize = TRUE;

    return err;
}

int 
DisConnectIcs(void){
    LogOut("\n正在断开连接，请稍候．．．\n");


    if(appData.ACPSics.ICS_net_id == ICS_MXQ_EN183 ||
        appData.ACPSics.ICS_net_id == ICS_MXQ_CN183){
        //SendToICS("quit\n");
        CMX_183_SEND_CODDING("quit");
    }
    else{
        SendToICS("quit\n"); 
    }

    
    //if(DIS.telnetISR != NULL){
    //     RemoveInputSource(DIS.telnetISR);
    //}
    //if (DIS.icsPR != NoProc) {
    //    DestroyChildProcess(DIS.icsPR, TRUE);
    //}
    return 0;
}
////按下了连线或断线按钮
//void 
//Console_Conect_Buttone(void){
//
//    HWND b = GetDlgItem(DLG.hwndConsole,IDC_ICS_CONNECT);
//
//    //if(appData.log
//
//
//}



void 
FitConsoleItemPosition(HWND hDlg,int newSizeX,int newSizeY){
#define hInputHeigh                 20      //控制台输入的高度
#define ConSoleButHeigh             25      //控制台按钮的高度
#define ConSoleSideW                6
    bool showStep;
    if(IsDlgButtonChecked(hDlg,IDC_TIMESTEP) == BST_CHECKED){
        ShowWindow(GetDlgItem(hDlg,IDC_LIST_STEP_MAIN   ),SW_SHOW);
        ShowWindow(GetDlgItem(hDlg,IDC_redTimeIcon      ),SW_SHOW);
        ShowWindow(GetDlgItem(hDlg,IDC_blueTimeIcon     ),SW_SHOW);
        ShowWindow(GetDlgItem(hDlg,IDC_TIME_RED_TOTAL   ),SW_SHOW);
        ShowWindow(GetDlgItem(hDlg,IDC_TIME_RED_STEP    ),SW_SHOW);
        ShowWindow(GetDlgItem(hDlg,IDC_TIME_BLUE_TOTAL  ),SW_SHOW);
        ShowWindow(GetDlgItem(hDlg,IDC_TIME_BLUE_STEP   ),SW_SHOW);
        showStep = true;
    }
    else{
        ShowWindow(GetDlgItem(hDlg,IDC_LIST_STEP_MAIN   ),SW_HIDE);
        ShowWindow(GetDlgItem(hDlg,IDC_redTimeIcon      ),SW_HIDE);
        ShowWindow(GetDlgItem(hDlg,IDC_blueTimeIcon     ),SW_HIDE);
        ShowWindow(GetDlgItem(hDlg,IDC_TIME_RED_TOTAL   ),SW_HIDE);
        ShowWindow(GetDlgItem(hDlg,IDC_TIME_RED_STEP    ),SW_HIDE);
        ShowWindow(GetDlgItem(hDlg,IDC_TIME_BLUE_TOTAL  ),SW_HIDE);
        ShowWindow(GetDlgItem(hDlg,IDC_TIME_BLUE_STEP   ),SW_HIDE);
        showStep = false;
    }
    int x, y, w, h;

    const int hstep = 52;

    x   = 1;
    y   = 5;
    w   = newSizeX - 2;


    if(showStep == false){	//显示棋步
        h   = newSizeY - hInputHeigh - 10 - ConSoleButHeigh;
    }
    else{
        y  += hstep;
        h   = newSizeY - hInputHeigh - 10 - ConSoleButHeigh - hstep;
    }

	if(appData.icsActive == FALSE){			// ICS 连线功能还没好

		//将相应弈天的按钮隐藏了
		for(int a = 0; a < 10; a++){
			ShowWindow(GetDlgItem(hDlg,YT_LX_AN[a]), SW_HIDE);
		}
		
	}
	else{									// ICS 连线连上了
		h -= ConSoleButHeigh * 2 + 5;
	}

    SetWindowPos(DLG.hText,NULL,x,y,w,h,SWP_NOZORDER|SWP_NOACTIVATE);   //hText 是LogOut RichEdit

    y = y + h + 4;

    h = hInputHeigh;
    SetWindowPos(DLG.hInput,NULL,x,y,w,h,SWP_NOZORDER|SWP_NOACTIVATE);


    w = (w-ConSoleSideW) / 5 - 1;
    x = ConSoleSideW / 2;
    y = y + h + 4;
    h = ConSoleButHeigh - 3;
    for(int i=0; i<5; i++){			//现在只用5个
        HWND b = GetDlgItem(DLG.hwndConsole,MXQ_ICS_BUT[i]);
        SetWindowPos(b,NULL,x,y,w,h,SWP_NOZORDER|SWP_NOACTIVATE);
        x += w + 2;
    }

	//弈天按键

	if(appData.icsActive == TRUE){
		
		for(int p=0; p<2; p++){		//一共二行

			w = newSizeX - 2;

			w = (w - ConSoleSideW) / 5 - 1;

			x = ConSoleSideW / 2;

			h = ConSoleButHeigh - 3;

			y = y + h + 4;
			
			for(int a = 0; a < 5; a++){

				HWND Hbut = GetDlgItem(DLG.hwndConsole, YT_LX_AN[p*5 + a]);

				SetWindowPos(Hbut,NULL,x,y,w,h,SWP_NOZORDER|SWP_NOACTIVATE);

				x += w+2;
			}
		}

		for(int a = 0; a < 10; a++){
			ShowWindow(GetDlgItem(hDlg,YT_LX_AN[a]), SW_SHOW);
		}
	}
}

LRESULT CALLBACK
ConsoleWndProc(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam){
    MINMAXINFO *mmi;
    static int sizeX, sizeY;
    int newSizeX, newSizeY;
    InputSource *is = DLG.consoleInputSource;

    //CHARFORMAT cf;
    switch(message){
        case WM_INITDIALOG:  
            //设置第一个图标
            PostMessage(hDlg, WM_SETICON, (WPARAM) TRUE, (LPARAM) appData.iconWhite);

            DLG.hText   = GetDlgItem(hDlg,OPT_RichLog);
            DLG.hInput  = GetDlgItem(hDlg,OPT_RichInput);
            SetFocus(DLG.hInput);

            DLG.consoleTextWindowProc  = (WNDPROC)(__int64)
                SetWindowLong(DLG.hText,GWL_WNDPROC,(LONG)(__int64)ConsoleTextSubclass);
            //SendMessage(DLG.hText,EM_SETBKGNDCOLOR,FALSE,11);
            //SendMessage(DLG.hText,EM_SETBKGNDCOLOR,FALSE,DLG.consoleBackgroundColor);

            DLG.consoleInputWindowProc  = (WNDPROC)(__int64)
                SetWindowLong(DLG.hInput,GWL_WNDPROC,(LONG)(__int64)ConsoleInputSubclass);

            //SendMessage(hInput, EM_SETBKGNDCOLOR, FALSE, consoleBackgroundColor);

            Colorize(ColorChannel1,TRUE);

            ChangedConsoleFont();
            //  初始化输入框的字体
            SendMessage(DLG.hInput,EM_SETCHARFORMAT,SCF_ALL,(LPARAM)&appData.AconsoleCF);   

            DLG.consoleEcho = true;

            return FALSE;            
        case WM_COMMAND:
            switch(LOWORD(wParam)){
        case IDC_ICS_CONNECT:       //连线按钮
            {
                if(appData.icsActive == FALSE){
                    ConnectToIcs();
                }
                else{
                    DisConnectIcs();
                }
            }
            break;
        case IDC_ICS_SET:            //设置连线帐号                     
            IcsCountSetPopup();
            break;
        case IDC_GO_PLACE:
            if(IsDlgButtonChecked(hDlg,IDC_GO_PLACE) == BST_CHECKED){ 
                ShowWindow(DLG.hwndGoPlace,SW_SHOW);
            }
            else{
                ShowWindow(DLG.hwndGoPlace,SW_HIDE);
            }
            break;
        case IDC_BUT_ICS_BOARD:
            if(IsDlgButtonChecked(hDlg,IDC_BUT_ICS_BOARD) == BST_CHECKED){ 
                ShowWindow(DLG.hwndICS_Board_List,SW_SHOW);
            }
            else{
                ShowWindow(DLG.hwndICS_Board_List,SW_HIDE);
            }
            break;
        case IDC_TIMESTEP:      //显示棋步与时间
            {
                //先得到当前的窗口的大小{
                RECT re;
                //GetWindowRect(hDlg,&re);
                GetClientRect(hDlg,&re);
                FitConsoleItemPosition(hDlg,(re.right - re.left),(re.bottom - re.top));
            }
            break;
        case IDC_BUTTON8: // 认输
            //t
            //<ICS: \015\012{ * 第 1 关 第 8 台 wral(4r) 离 开 红 方 }\015\012大理国!%
            //<ICS: \015\012{ * 第 1 关 第 8 台 wral(4r) 加 入 红 方 }\015\012大理国!%
            {
                //ICS.loggedOn = TRUE;
                //initIcs();
                //char t0[] =  "\r\n大理国!%";
                ////char t1[] =  "\r\n{ * 第 1 关 第 8 台 wral(4r) 离 开 红 方 }\r\n大理国!%";
                //char t2[] =  "\r\n{ + 伏舟人(9级)  从 西 来 了. }\r\n大理国!%";

                //char t1[] = "\r\n{ * 第 1 关 第 8 台 wral(4r) 离 开 红 方 }\r\n大理国!%\r\n{ + 伏舟人(9级)  从 西 来 了. }\r\n大理国!%";

                //int len0  = (int)strlen(t0);
                //int len1  = (int)strlen(t1);
                //int len2  = (int)strlen(t2);
                ////+		ICS.buf	0x0059fbe8 "
                ////{ * 第 1 关 第 8 台 wral(4r) 离 开 红 方 }
                ////{ + 伏舟人(9级)  从 西 来 了. }"	char [8192]

                //read_from_ics_mxq_cn183(NULL,NULL,t0,len0,0);
                //read_from_ics_mxq_cn183(NULL,NULL,t1,len1,0);
                //read_from_ics_mxq_cn183(NULL,NULL,t2,len2,0);
            }
            break;
            //if(IsDlgButtonChecked(hDlg,IDC_GO_PLACE) == BST_CHECKED){   //转地按钮按下了
        default:
            break;
            }
            break;
        case WM_SETFOCUS:
            SetFocus(DLG.hInput);
            return 0;
            break;
        case WM_SIZE:
            //FitRichLogDlgItem(hDlg);
            if(IsIconic(hDlg)){
                break;
            }
            newSizeX = LOWORD(lParam);
            newSizeY = HIWORD(lParam);
            if(sizeX != newSizeX || sizeY != newSizeY){

                FitConsoleItemPosition(hDlg,newSizeX,newSizeY);
                //}                
            }


            //LogOut(ColorShout,"ColorShout\n");
            //LogOut(ColorRequest,"ColorRequest\n");

            sizeX = newSizeX;
            sizeY = newSizeY;
            break;
        case WM_CLOSE:
            DLG_Rich_Log_Event();
            break;
        case WM_GETMINMAXINFO:    //避免窗口拉的过小 /* Prevent resizing window too small */
            mmi = (MINMAXINFO*) lParam;
            mmi->ptMinTrackSize.x = 100;
            mmi->ptMinTrackSize.y = 300;
            break;
        default:
            break;
    }
    //return DefWindowProc(hDlg, message, wParam, lParam);

    return false;

    //窗口过程对应于不同的消息有各种不同含义的返回值，
    //而对话框过程返回BOOL类型的值，返回TRUE表示已经处理了某条消息，
    //返回FALSE表示没有处理。“对话框管理器”代码会根据
    //返回值决定是否继续处理某一条消息（惟一的例外是WM_INITDIALOG消息）。
}

void DLG_Rich_Log_Event(void){
    //(void) CheckMenuItem(GetMenu(hwndMain), IDM_SaveSettingsOnExit,
    //			MF_BYCOMMAND|(DIS.saveSettingsOnExit ?  MF_CHECKED : MF_UNCHECKED));
    if(DLG.hwndConsole){
        if(IsWindowVisible(DLG.hwndConsole)){
            ShowWindow(DLG.hwndConsole,SW_HIDE);
            CheckMenuItem(GetMenu(OBS[0]->hwndThis),IDM_RichLog,MF_UNCHECKED);
        }
        else{
            ShowWindow(DLG.hwndConsole,SW_SHOW);
            CheckMenuItem(GetMenu(OBS[0]->hwndThis),IDM_RichLog,MF_CHECKED);
        }
        //if(DLG.hwndConsole){     //当前棋步对话框已显示了           
        //    ShowWindow(DLG.hwndConsole,SW_HIDE);
        //    DLG.IsConsoleShow = false;
        //    CheckMenuItem(GetMenu(hwndMain),IDM_RichLog,MF_UNCHECKED);
        //}
        //else{               //是隐藏了
        //    ShowWindow(DLG.hwndConsole,SW_SHOW);
        //    DLG.IsConsoleShow = true;
        //    CheckMenuItem(GetMenu(hwndMain),IDM_RichLog,MF_CHECKED);
        //}
    }
    else{
        FARPROC lpProc = MakeProcInstance((FARPROC)ConsoleWndProc,hInst);
        /*DLG.hwndConsole = CreateDialog(hInst,MAKEINTRESOURCE(DLG_RICH_LOG),NULL,(DLGPROC)lpProc);*/
        DLG.hwndConsole = CreateDialog(hInst,MAKEINTRESOURCE(DLG_RICH_LOG),OBS[0]->hwndThis,(DLGPROC)lpProc);
        FreeProcInstance(lpProc);
        FitRichLogDlgPosition(DLG.hwndConsole);
        ShowWindow(DLG.hwndConsole,SW_SHOW);
        //DLG.IsConsoleShow = true;
        CheckMenuItem(GetMenu(OBS[0]->hwndThis),IDM_RichLog,MF_CHECKED);
    }
}
VOID
ChangedConsoleFont()
{
    CHARFORMAT cfmt;
    CHARRANGE tmpsel, sel;
    MyFont *f   = appData.Afont[appData.Absize][CONSOLE_FONT];

    //HWND hText  = GetDlgItem(DLG.hwndConsole, OPT_ConsoleText);
    //HWND hInput = GetDlgItem(DLG.hwndConsole, OPT_ConsoleInput);


    HWND hText    = DLG.hText;
    HWND hInput   = DLG.hInput;
    PARAFORMAT paraf;

    cfmt.cbSize = sizeof(CHARFORMAT);
    cfmt.dwMask = CFM_FACE|CFM_SIZE|CFM_CHARSET;
    strcpy_s(cfmt.szFaceName, 32, appData.Afont[appData.Absize][CONSOLE_FONT]->mfp.faceName);
    /* yHeight is expressed in twips.  A twip is 1/20 of a font's point
    * size.  This was undocumented in the version of MSVC++ that I had
    * when I wrote the code, but is apparently documented now.
    */
    cfmt.yHeight = (int)(f->mfp.pointSize * 20.0 + 0.5);
    cfmt.bCharSet = f->lf.lfCharSet;
    cfmt.bPitchAndFamily = f->lf.lfPitchAndFamily;
    SendMessage(hText, EM_SETCHARFORMAT, SCF_ALL, (LPARAM) &cfmt); 
    SendMessage(hInput, EM_SETCHARFORMAT, SCF_ALL, (LPARAM) &cfmt); 
    /* Why are the following seemingly needed too? */
    SendMessage(hText, EM_SETCHARFORMAT, SCF_DEFAULT, (LPARAM) &cfmt); 
    SendMessage(hInput, EM_SETCHARFORMAT, SCF_DEFAULT, (LPARAM) &cfmt); 
    SendMessage(hText, EM_EXGETSEL, 0, (LPARAM)&sel);
    tmpsel.cpMin = 0;
    tmpsel.cpMax = -1; /*999999?*/
    SendMessage(hText, EM_EXSETSEL, 0, (LPARAM)&tmpsel);
    SendMessage(hText, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM) &cfmt); 
    /* Trying putting this here too.  It still seems to tickle a RichEdit
    *  bug: sometimes RichEdit indents the first line of a paragraph too.
    */
    paraf.cbSize = sizeof(paraf);
    paraf.dwMask = PFM_OFFSET | PFM_STARTINDENT;
    paraf.dxStartIndent = 0;
    paraf.dxOffset = WRAP_INDENT;
    SendMessage(hText, EM_SETPARAFORMAT, 0, (LPARAM) &paraf);
    SendMessage(hText, EM_EXSETSEL, 0, (LPARAM)&sel);
}

VOID
EchoOn()
{
    HWND hInput;
    DLG.consoleEcho = TRUE;
    //hInput = GetDlgItem(hwndConsole, OPT_ConsoleInput);
    hInput = DLG.hInput;
    SendMessage(hInput, EM_SETCHARFORMAT, SCF_ALL, (LPARAM)&appData.AconsoleCF);
    SendMessage(hInput, EM_SETBKGNDCOLOR, FALSE, DLG.consoleBackgroundColor);
}

VOID
EchoOff()
{
    CHARFORMAT cf;
    HWND hInput;
    DLG.consoleEcho = FALSE;
    //hInput = GetDlgItem(hwndConsole, OPT_ConsoleInput);
    hInput = DLG.hInput;
    /* This works OK: set text and background both to the same color */
    cf = appData.AconsoleCF;
    cf.crTextColor = COLOR_ECHOOFF;
    SendMessage(hInput, EM_SETCHARFORMAT, SCF_ALL, (LPARAM)&cf);
    SendMessage(hInput, EM_SETBKGNDCOLOR, FALSE, cf.crTextColor);
}

