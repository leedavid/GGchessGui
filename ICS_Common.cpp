#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

void
read_from_ics_not_ready_know(
InputSourceRef isr, VOIDSTAR closure, char *data, int count, int error)  {
	LogOut(_T("协议还没支持!\n"));
}


//void
//SendToPlayerByColor(char *str, ColorClass cc,int len, int notShout){
void
SendToPlayerByColor(TCHAR *str, ColorClass cc, int notShout){
    ICS.prevColor = ICS.curColor;

    int len = (int)wcslen(str);
    //str[len+1] = '\n';
    //str[len+2] = 0;

    //len += 2;

    if(cc != ICS.curColor || notShout == FALSE){
        Colorize(cc,notShout);
        ICS.curColor = cc;
        SendToPlayer(str,len);
        //S
        Colorize(ICS.prevColor,TRUE);
        ICS.curColor = ICS.prevColor;
        //ICS
    }
    else{
        SendToPlayer(str,len);
    }


}

void initIcs(void){
    Colorize(ColorChannel1, TRUE);
    ICS.curColor        = ColorChannel1;
    ICS.prevColor       = ColorChannel1;
    ICS.loggedOn        = FALSE;

	dispboard_t* pDis = OBS[0];
	pDis->table       = 0;

	//ChangeDisBoardTable(pDis,0);

    //ICS.lastnotfinish   = FALSE;

    //char buf[ICS_BUF_SIZE];
    //int  buf_len;
    //int  tkind;
    //int  started;
    //DIS.gameMode        = IcsIdle;
    ICS.buf_len         = 0;
    ICS.tkind           = 0;
    ICS.started         = STARTED_NONE;
    //ICS.i               = 0;
    //ICS.leftover_len    = 0;
    //ICS.leftover_start  = 0;
    //ICS.oldi            = 0;
    
    //ICS.next_out        = 0;
    

//const int MXQ_ICS_BUT[12] = {
//    IDC_ICS_CONNECT,        //连线或断线按钮
//    IDC_ICS_SET,            //设置连线帐号                    
//    IDC_GO_PLACE,
//    IDC_BUTTON5,
//    IDC_BUTTON6,
//    IDC_BUTTON7,
//    IDC_BUTTON8,
//    IDC_BUTTON9,
//    IDC_BUTTON10,
//    IDC_BUTTON11,
//    IDC_BUTTON2,
//    IDC_BUTTON12
//};

//#define STARTED_NONE            0
//#define STARTED_MOVES           1
//#define STARTED_BOARD           2
//#define STARTED_OBSERVE         3
//#define STARTED_HOLDINGS        4
//#define STARTED_CHATTER         5
//#define STARTED_COMMENT         6
//#define STARTED_MOVES_NOHIDE    7

    for(int i = 2; i< 8; i++){       
       ShowWindow(GetDlgItem(HWND_CONSOLE,MXQ_ICS_BUT[i]),SW_HIDE);
    }

    //char buf[ICS_BUF_SIZE];
    //int  buf_len;
    //int  started;
    //int  i;
    //int  old_i;
    //int  tkind;
    //int  next_out;
    //int  leftover_len;
    //int  leftover_start;  
    //char star_match[STAR_MATCH_N][MSG_SIZ];

}


void InternetPlayEvent(void){
}



void        //解码开始的四个字
CMX_183_Get_Client_Code(void){
    TCHAR MXQ_CLIENT[90*10];
    for(int i=0;i<90;i++){
        MXQ_CLIENT[0 * 90 + i] = MXQ_4C9BDC[i];
        MXQ_CLIENT[1 * 90 + i] = MXQ_4C9B80[i];
        MXQ_CLIENT[2 * 90 + i] = MXQ_4C9B24[i];
        MXQ_CLIENT[3 * 90 + i] = MXQ_4C9AC8[i];
        MXQ_CLIENT[4 * 90 + i] = MXQ_4C9A6C[i];
        MXQ_CLIENT[5 * 90 + i] = MXQ_4C9A10[i];
        MXQ_CLIENT[6 * 90 + i] = MXQ_4C99B4[i];
        MXQ_CLIENT[7 * 90 + i] = MXQ_4C9958[i];
        MXQ_CLIENT[8 * 90 + i] = MXQ_4C98FC[i];
        MXQ_CLIENT[9 * 90 + i] = MXQ_4C98A0[i];
    }    
	TCHAR buf[512];
	setlocale(LC_CTYPE, "chs");
	swprintf_s(buf, sizeof(buf)/sizeof(TCHAR), L"%s", ICS.star_match[0]);
    int edx = 0;
	TCHAR* StrMatch = buf;
	int   pc_len = (int)wcslen(StrMatch);
    if(pc_len <= 0){
        return;
    }
    int add = 0;
    for(int i = 0; i < pc_len; i++){
        add += buf[i];
    }
    int yushu = add % 10;           // edx = 3
    
    if(yushu == 0){
        yushu = 1;
    }
    if(pc_len <= 0){
        return;
    }
    int ebx;
    for(ebx = 0; ebx < pc_len; ebx ++){
		TCHAR dl = StrMatch[ebx]; //这是第一个字符,也就弈天的dl,

        //memcpy(MXQ_4D6460,MXQ_4C9BDC,92);
        //memcpy(MXQ_4D64BA,MXQ_4C9B80,92);
        //memcpy(MXQ_4D6514,MXQ_4C9B24,92);
        //memcpy(MXQ_4D656E,MXQ_4C9AC8,92);
        //memcpy(MXQ_4D65C8,MXQ_4C9A6C,92);
        //memcpy(MXQ_4D6622,MXQ_4C9A10,92);
        //memcpy(MXQ_4D667C,MXQ_4C99B4,92);
        //memcpy(MXQ_4D66D6,MXQ_4C9958,92);
        //memcpy(MXQ_4D6730,MXQ_4C98FC,92);
        //memcpy(MXQ_4D678A,MXQ_4C98A0,92);
        //char *pc = &MXQ_4D6460[0];
        TCHAR *pc = &MXQ_CLIENT[0];
        int t;
        for(t = 0; t < 90; t++){
            if(pc[t] == dl){
                break;
            }
        }
        if(t != 90){
             pc = &MXQ_CLIENT[yushu*90];
             dl = *(pc+t);
        }
        else{
        }
       
        ICS.ICS_183[ebx] = dl;
    }
    ICS.ICS_183[ebx++] = 0;
}

void        //解码输入的命令
CMX_183_Get_Code_By_Client(TCHAR *pre, TCHAR *passed){
    //将所传递过来的字符串加密后送出
    int len = (int)wcslen(pre);
    if(len <= 0 ) return;
    TCHAR MXQ_CLIENT[90*10];
    for(int i=0;i<90;i++){
        MXQ_CLIENT[0 * 90 + i] = MXQ_4C9BDC[i];
        MXQ_CLIENT[1 * 90 + i] = MXQ_4C9B80[i];
        MXQ_CLIENT[2 * 90 + i] = MXQ_4C9B24[i];
        MXQ_CLIENT[3 * 90 + i] = MXQ_4C9AC8[i];
        MXQ_CLIENT[4 * 90 + i] = MXQ_4C9A6C[i];
        MXQ_CLIENT[5 * 90 + i] = MXQ_4C9A10[i];
        MXQ_CLIENT[6 * 90 + i] = MXQ_4C99B4[i];
        MXQ_CLIENT[7 * 90 + i] = MXQ_4C9958[i];
        MXQ_CLIENT[8 * 90 + i] = MXQ_4C98FC[i];
        MXQ_CLIENT[9 * 90 + i] = MXQ_4C98A0[i];
    } 
    
    TCHAR *pclient = &ICS.ICS_183[0];
    
	TCHAR char_cl;
	TCHAR char_al;

    int            esi;
    int            ecx;
    
    for(esi = 0; esi < len; esi++){        
        ecx  = esi;
        ecx &= 80000003; //0040EF7D      |.  81E1 0>|and     ecx, 80000003        
        char_al   = pre[esi];      //取得第一个字符
        if(ecx < 0){
            ecx --;
            ecx |= 0xFFFFFFFC;   //0040EF89      |.  83C9 FC      |or      ecx, FFFFFFFC
            ecx ++;
        }
            
            char_cl  = pclient[ecx];
            char_cl ^= char_al;
            
            if(
                 (char_al <  0x20)
               ||(char_al == 0x2f)
               ||(char_al == 0x5C)
               ||(char_cl <  0x20)
               ||(char_cl == 0x2f)
               ||(char_cl == 0x5c)
               ){
                char_al = char_al;
            }
            else{
                char_al = char_cl;
            }
       
        passed[esi] = char_al;
    }

    passed[esi++] = '\n';
    passed[esi++] = 0;

    return;
}



void
CMX_183_SEND_CODDING(TCHAR* pretext){
    TCHAR buf[1024];
    CMX_183_Get_Code_By_Client(pretext,buf);
    SendToICS(buf);
}
void 
CMX_183_SEND_CODDING_DelayMs(TCHAR* pretext, int ms){
	TCHAR buf[1024];
    CMX_183_Get_Code_By_Client(pretext,buf);
    SendToICSDelayed(buf, ms); 
}

void AlreadDisConnectIcs(void){
    appData.icsActive  = FALSE;
    ICS.loggedOn       = FALSE;
    //ICS.state          = ICS_NONE;
    SetDlgItemText(HWND_CONSOLE,IDC_ICS_CONNECT,_T("登录")); 
    LogOut(_T("\n已成功退出网络连接！．．\n"));

	// 如果连续打擂按钮已按下
	if(ICS.cont_dalei == TRUE){
		//1, 再登录，
		ConnectToIcs();
		Sleep(3000);
		//2, 再加入，打擂
		if(ICS.cont_dalei == TRUE){  
			ResetGameEvent(OBS[0]);					//恢位一下棋局
			Sleep(668);
			CMX_183_SEND_CODDING(L"j");	
			//Sleep(200);
		}
	}
	else{
		RECT re;
		GetClientRect(HWND_CONSOLE,&re);
		FitConsoleItemPosition(HWND_CONSOLE,(re.right - re.left),(re.bottom - re.top));	
	}	
}

void                //已登录成功了网站
SetIcsLogOk(TCHAR* buf){
    ICS.loggedOn = TRUE;
    //ICS.state    = ICS_JUST_LOGIN;
    SetIcsTitleName(buf);

    for(int i = 2; i< 8; i++){
        //EnableWindow(GetDlgItem(HWND_CONSOLE,MXQ_ICS_BUT[i]),false);
        ShowWindow(GetDlgItem(HWND_CONSOLE,MXQ_ICS_BUT[i]),SW_SHOW);
    }
}

void SetIcsTitleName(TCHAR* title){
    TCHAR buf[MSG_SIZ];
    /*sprintf_s(buf,"<日志> 帐号(%s) %s", DIS.third.ICS_user, title);*/
    swprintf_s(buf,sizeof(buf)/sizeof(TCHAR),_T("<%s> (%s) "),title, appData.ACPSics.ICS_user); //DIS.third.ICS_user);
    //SetWindowText(HWND_CONSOLE,buf);
	SetWindowText(TAB.tabMain,buf);
    SetWindowText(TAB.hwndGoPlace,buf);
    SetWindowText(TAB.hwndICS_Board_List,buf);
}

void IcsGameStart(dispboard_t* pDis){

	//在这儿重建一下开局库

	FillBookbyPos(pDis,MST->book); 
	
	if(pDis->IcsGameStartAlready){
		return;
	}

	TCHAR str[512];

	if(pDis->gameMode == IcsPlayingWhite){
		swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("\n%d桌游戏开始了，您执红!"), pDis->table);
	}
	else if(pDis->gameMode == IcsPlayingBlack){
		swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("\n%d桌游戏开始了，您执黑!"), pDis->table);
		// 要自动交换一下棋局棋子，便于观察
		pDis->flipView = 0;
		FlipViewEvent(pDis);
	}
	else{
		swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("\n%d桌游戏开始了，您正在旁观!"), pDis->table);
	}

	Sleep(1200);

	LogOut(str);

	if(pDis->gameMode == IcsPlayingWhite || pDis->gameMode == IcsPlayingBlack){
		//打开一个引擎，
		if(pDis->first.cps_stat != Cps_NotLoad){
			MachinePlayEvent(&pDis->first);
		}
	}

	pDis->IcsGameStartAlready = TRUE;
}




void
CommandX(HWND hwnd, TCHAR *command, BOOLEAN getname, BOOLEAN immediate){
  TCHAR buf[MSG_SIZ], name[MSG_SIZ];
  HWND hInput = GetDlgItem(HWND_CONSOLE, OPT_ConsoleInput);
  CHARRANGE sel;

  if (!getname) {
    SetWindowText(hInput, command);
    if (immediate) {
      SendMessage(hInput, WM_CHAR, '\r', 0);
    } else {
      sel.cpMin = 999999;
      sel.cpMax = 999999;
      SendMessage(hInput, EM_EXSETSEL, 0, (LPARAM)&sel);
      SetFocus(hInput);
    }
    return;
  }    
  SendMessage(hwnd, EM_EXGETSEL, 0, (LPARAM)&sel);
  if (sel.cpMin == sel.cpMax) {
    /* Expand to surrounding word */
    TEXTRANGE tr;
    do {
      tr.chrg.cpMax = sel.cpMin;
      tr.chrg.cpMin = --sel.cpMin;
      if (sel.cpMin < 0) break;
      tr.lpstrText = name;
      SendMessage(hwnd, EM_GETTEXTRANGE, 0, (LPARAM) &tr);
    } while (isalpha(name[0]) || isdigit(name[0]) || name[0] == '-');
    sel.cpMin++;

    do {
      tr.chrg.cpMin = sel.cpMax;
      tr.chrg.cpMax = ++sel.cpMax;
      tr.lpstrText = name;
      if (SendMessage(hwnd, EM_GETTEXTRANGE, 0, (LPARAM) &tr) < 1) break;
    } while (isalpha(name[0]) || isdigit(name[0]) || name[0] == '-');
    sel.cpMax--;

    if (sel.cpMax == sel.cpMin || sel.cpMax - sel.cpMin > MSG_SIZ/2) {
      MessageBeep(MB_ICONEXCLAMATION);
      return;
    }
    tr.chrg = sel;
    tr.lpstrText = name;
    SendMessage(hwnd, EM_GETTEXTRANGE, 0, (LPARAM) &tr);
  } else {
    if (sel.cpMax - sel.cpMin > MSG_SIZ/2) {
      MessageBeep(MB_ICONEXCLAMATION);
      return;
    }
    SendMessage(hwnd, EM_GETSELTEXT, 0, (LPARAM) name);
  }
  if (immediate) {
    //sprintf(buf, "%s %s", command, name);
	StringCbPrintf(buf,sizeof(buf),_T("%s %s"), command, name);
    SetWindowText(hInput, buf);
    SendMessage(hInput, WM_CHAR, '\r', 0);
  } else {
    //sprintf(buf, "%s %s ", command, name); /* trailing space */
	StringCbPrintf(buf,sizeof(buf),_T("%s %s"), command, name);
    SetWindowText(hInput, buf);
    sel.cpMin = 999999;
    sel.cpMax = 999999;
    SendMessage(hInput, EM_EXSETSEL, 0, (LPARAM)&sel);
    SetFocus(hInput);
  }
}


//char *
//UserName()
//{
//  static char buf[MSG_SIZ];
//  DWORD bufsiz = MSG_SIZ;
//
//  if (!GetUserName(buf, &bufsiz)) {
//    DisplayError("Error getting user name", GetLastError());
//    //strcpy(buf, "User");
//	StringCbCopy(buf,MSG_SIZ,"User");
//  }
//  return buf;
//}

//char *
//HostName()
//{
//  static char buf[MSG_SIZ];
//  DWORD bufsiz = MSG_SIZ;
//
//  if (!GetComputerName(buf, &bufsiz)) {
//    DisplayError("Error getting host name", GetLastError());
//    //strcpy(buf, "Unknown");
//	StringCbCopy(buf,MSG_SIZ,"Unknown");
//  }
//  return buf;
//}


DWORD
InputThread(LPVOID arg){
	InputSource *is;
	OVERLAPPED ovl;

	dispboard_t *pDis = OBS[0];

	is = (InputSource *) arg;
	ovl.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	ovl.Internal = ovl.InternalHigh = ovl.Offset = ovl.OffsetHigh = 0;
	while (is->hThread != NULL) {
		is->error = DoReadFile(is->hFile, is->next,
			(int)(INPUT_SOURCE_BUF_SIZE - (is->next - is->buf)),
			&is->count, &ovl);
		if (is->error == NO_ERROR) {
			is->next += is->count;
		} else {
			if (is->error == ERROR_BROKEN_PIPE) {
				/* Correct for MS brain damage.  EOF reading a pipe is not an error. */
				is->count = 0;
			} else {
				is->count = (DWORD) -1;
			}
		}
		SendMessage(pDis->hwndThis, WM_USER_Input, 0, (LPARAM) is);
		if (is->count <= 0) break;  /* Quit on EOF or error */
	}
	CloseHandle(ovl.hEvent);
	CloseHandle(is->hFile);
	return 0;
}

DWORD  /* Windows 95 beta 2 won't let you do overlapped i/o on a console or pipe */
NonOvlInputThread(LPVOID arg) {

	dispboard_t *pDis = OBS[0];
	InputSource *is;
	char *p, *q;
	int i;
	char prev;

	is = (InputSource *) arg;
	while (is->hThread != NULL) {
		is->error = ReadFile(is->hFile, is->next,
			(int)(INPUT_SOURCE_BUF_SIZE - (is->next - is->buf)),
			&is->count, NULL) ? NO_ERROR : GetLastError();
		if (is->error == NO_ERROR) {
			/* Change CRLF to LF */
			if (is->next > is->buf) {
				p = is->next - 1;
				i = is->count + 1;
			} 
			else {
				p = is->next;
				i = is->count;
			}
			q = p;
			prev = NULLCHAR;
			while (i > 0) {
				if (prev == '\r' && *p == '\n') {
					*(q-1) = '\n';
					is->count--;
				} 
				else { 
					*q++ = *p;
				}
				prev = *p++;
				i--;
			}
			*q = NULLCHAR;
			is->next = q;
		} 
		else {
            //


			if (is->error == ERROR_BROKEN_PIPE) {
				/* Correct for MS brain damage.  EOF reading a pipe is not an error. */
				is->count = 0; 
			} 
			else {
				is->count = (DWORD) -1;
			}
		}
		SendMessage(pDis->hwndThis, WM_USER_Input, 0, (LPARAM) is);
		if (is->count < 0) break;  /* Quit on error */
	}
	CloseHandle(is->hFile);
	return 0;
}
DWORD
SocketInputThread(LPVOID arg)
{
  InputSource *is;

  dispboard_t *pDis = OBS[0];

  is = (InputSource *) arg;
  while (is->hThread != NULL) {
    is->count = recv(is->sock, is->buf, INPUT_SOURCE_BUF_SIZE, 0);
    if ((int)is->count == SOCKET_ERROR) {
      is->count = (DWORD) -1;
      is->error = WSAGetLastError();
    } else {
      is->error = NO_ERROR;
      is->next += is->count;
      if (is->count == 0 && is->second == is) {
	/* End of file on stderr; quit with no message */
	break;
      }
    }
    SendMessage(pDis->hwndThis, WM_USER_Input, 0, (LPARAM) is);
    if (is->count <= 0) break;  /* Quit on EOF or error */
  }
  return 0;
}



void
GetMoveListEvent(void){
    //char buf[MSG_SIZ];
    //if (appData.icsActive && DIS.gameMode != IcsIdle && DIS.ics_gamenum > 0) {
    //    DIS.ics_getting_history = H_REQUESTED;
    //    //	sprintf(buf, "%smoves %d\n", ics_prefix, ics_gamenum);
    //    StringCbPrintf(buf,MSG_SIZ,"%smoves %d\n", DIS.ics_prefix, DIS.ics_gamenum);
    //    SendToICS(buf);
    //}
}

void
DoEcho(){
    if (!appData.icsActive){
        return;
    }
    TelnetRequest(TN_DO, TN_ECHO);
}
void
DontEcho(){
    if (!appData.icsActive){
        return;
    }
    TelnetRequest(TN_DONT, TN_ECHO);
}

int		//与host建立一个连接哇
establish(void){	
    /*
    * Establish will establish a contact to a remote host.port.
    * Sets icsPR to a ProcRef for a process (or pseudo-process)
    *  used to talk to the host.
    * Returns 0 if okay, error code if not.
    */
    TCHAR buf[MSG_SIZ];

    //if (*appData.icsCommPort != NULLCHAR) {
    //    /* Talk to the host through a serial comm port */
    //    return OpenCommPort(appData.icsCommPort, &appData.AicsPR);

    //} 
    //else 
	if (*appData.gateway != NULLCHAR) {
        if (*appData.remoteShell == NULLCHAR) {
            /* Use the rcmd protocol to run telnet program on a gateway host */
            //StringCbPrintf(buf,MSG_SIZ,"%s %s %s",
            //    appData.telnetProgram, appData.icsHost, appData.icsPort);
            swprintf_s(buf,sizeof(buf) / sizeof(TCHAR),_T("%s %s %d"),appData.telnetProgram,
                appData.ACPSics.ICS_net_host,appData.ACPSics.ICS_net_port); //MAIN.CPSics
            return OpenRcmd(CW2A(appData.gateway), CW2A(appData.remoteUser), CW2A(buf), &appData.AicsPR);

        } 
        else {
            /* Use the rsh program to run telnet program on a gateway host */
            if (*appData.remoteUser == NULLCHAR) {
                //StringCbPrintf(buf,MSG_SIZ,"%s %s %s %s %s", appData.remoteShell,
                //    appData.gateway, appData.telnetProgram,
                //    appData.icsHost, appData.icsPort);
                swprintf_s(buf,sizeof(buf) / sizeof(TCHAR),_T("%s %s %s %s %d"),appData.remoteShell,appData.gateway,
                    appData.telnetProgram,appData.ACPSics.ICS_net_host,appData.ACPSics.ICS_net_port);
            } 
            else {
                //StringCbPrintf(buf,MSG_SIZ,"%s %s -l %s %s %s %s",
                //    appData.remoteShell, appData.gateway, 
                //    appData.remoteUser, appData.telnetProgram,
                //    appData.icsHost, appData.icsPort);
            }
            return StartChildProcess(buf, _T(""), &appData.AicsPR);
        }
    } 
    else if (appData.useTelnet) {
        //return OpenTelnet(appData.icsHost, appData.icsPort, &DIS.icsPR);
        swprintf_s(buf,sizeof(buf) / sizeof(TCHAR),_T("%d"),appData.ACPSics.ICS_net_port);
		return OpenTelnet(appData.ACPSics.ICS_net_host, buf, &appData.AicsPR);

    } 
    else {
        /* TCP socket interface differs somewhat between
        Unix and NT; handle details in the front end.
        */
        swprintf_s(buf,sizeof(buf) / sizeof(TCHAR),_T("%d"),appData.ACPSics.ICS_net_port);
        return OpenTCP(CW2A(appData.ACPSics.ICS_net_host),CW2A(buf), &appData.AicsPR);
    }
}


void  /* Telnet protocol requests from the front end */
TelnetRequest(TCHAR ddww, TCHAR option)  {
    TCHAR msg[3];
    int outCount, outError;

    //if (*appData.icsCommPort != NULLCHAR || appData.useTelnet) return;

	if ( appData.useTelnet) return;

    msg[0] = TN_IAC;
    msg[1] = ddww;
    msg[2] = option;
    outCount = OutputToProcess(appData.AicsPR, msg, 3, &outError);
    if (outCount < 3) {
		DisplayFatalError(L"Error writing to ICS", outError, 1);
    }
}









//void
//ProcessICSInitScript(FILE *f){
//    char buf[MSG_SIZ];
//
//    while (fgets(buf, MSG_SIZ, f)) {
//        SendToICSDelayed(buf,(long)appData.msLoginDelay);
//    }
//
//    fclose(f);
//}

//发送走步到ICS
void	
SendMoveToICS(dispboard_t* pDis, ChessMove moveType, int fromX, int fromY,int toX,int toY) {

	if (pDis->gameMode == AnalyzeMode){    //当前是分析模式,就不发送走步到ICS
		return;
	}

	//Sleep(500);   // 

	TCHAR user_move[MSG_SIZ];	

	swprintf_s(user_move,sizeof(user_move)/sizeof(TCHAR), L"%c%c-%c%c\n", '0' + fromX, 'J' - fromY, '0' + toX, 'J' - toY);

	CMX_183_SEND_CODDING(user_move);
}

int  /* Returns an errno value */
OutputMaybeTelnet(ProcRef pr, TCHAR *message, int count, int *outError) {
    TCHAR buf[8192*2], *p, *q, *buflim;
    int left, newcount, outcount;

    //if (*appData.icsCommPort != NULLCHAR || appData.useTelnet || *appData.gateway != NULLCHAR) {

if ( appData.useTelnet || *appData.gateway != NULLCHAR) {

#ifdef DEBUG_USE_DEBUG_FILE      
        //if (appData.debugMode) {
            fprintf(appData.debugFP, ">ICS: ");
            show_bytes(appData.debugFP, message, count);
            fprintf(appData.debugFP, "\n");
        //}
#endif

        return OutputToProcess(pr, message, count, outError);
    }

    buflim = &buf[sizeof(buf)-1]; /* allow 1 byte for expanding last char */
    p = message;
    q = buf;
    left = count;
    newcount = 0;
    while (left) {
        if (q >= buflim) {

            outcount = OutputToProcess(pr, buf, newcount, outError);
            if (outcount < newcount) return -1; /* to be sure */
            q = buf;
            newcount = 0;
        }
        if (*p == '\n') {
            *q++ = '\r';
            newcount++;
        } else if (((unsigned char) *p) == TN_IAC) {
            *q++ = (char) TN_IAC;
            newcount ++;
        }
        *q++ = *p++;
        newcount++;
        left--;
    }

    outcount = OutputToProcess(pr, buf, newcount, outError);
    if (outcount < newcount){
        return -1; /* to be sure */
    }
    return count;
}

void
read_from_player(InputSourceRef isr, VOIDSTAR closure, char *message, int count, int error)  {
    int outError, outCount;
    static int gotEof = 0;

    /* Pass data read from player on to ICS */
    if (count > 0) {
        gotEof = 0;
        outCount = OutputMaybeTelnet(appData.AicsPR, CA2W(message), count, &outError);
        if (outCount < count) {
			DisplayFatalError(L"Error writing to ICS", outError, 1);
        }
    } 
    else if (count < 0) {
        RemoveInputSource(isr);
		DisplayFatalError(L"Error reading from keyboard", error, 1);
    } 
    else if (gotEof++ > 0) {
        RemoveInputSource(isr);
		DisplayFatalError(L"Got end of file from keyboard", 0, 0);
    }
}



void
SendToICS(TCHAR *s){
    int count, outCount, outError;

    if (appData.AicsPR == NULL) return;

    count = (int)(wcslen(s));
    outCount = OutputMaybeTelnet(appData.AicsPR, s, count, &outError);
    if (outCount < count) {
		DisplayFatalError(L"Error writing to ICS", outError, 1);
    }
}
void
SendToICSDelayed(TCHAR *s,long msdelay)  {
    /* This is used for sending logon scripts to the ICS. Sending
    without a delay causes problems when using timestamp on ICC
    (at least on my machine). */
    int count, outCount, outError;

    if (appData.AicsPR == NULL) return;

    count = int(wcslen(s));

    outCount = OutputToProcessDelayed(appData.AicsPR, s, count, &outError, msdelay);
    if (outCount < count) {
		DisplayFatalError(L"Error writing to ICS", outError, 1);
    }
}