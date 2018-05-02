#include "stdafx.h"
#include "GGchess.h"
#include <sys/stat.h>
#include <commdlg.h>
#include <dlgs.h>
#include <commctrl.h>

#include "chess.h"
#include "data.h"
#include "pregen.h"

HWND			//建立状态栏
CreateStatus(HWND hMain){		
	HWND  hwndStatus = CreateWindowEx(
        0,                       // no extended styles
        STATUSCLASSNAME,         // name of status bar class
        (LPCTSTR) NULL,          // no text when first created
        SBARS_SIZEGRIP |         // includes a sizing grip
		WS_VISIBLE |
        WS_CHILD,                // creates a child window
        0, 0, 0, 0,              // ignores size and position
        hMain,                   // handle to parent window
        (HMENU)ID_STATUSBAR,	 // child window identifier
        hInst,                   // handle to application instance
        NULL);                   // no window creation data
	ShowWindow(hwndStatus, SW_SHOW); 
	int dwWidth[10] = {	2024,5,5	};
	SendMessage(hwndStatus,SB_SETPARTS,4,(LPARAM)&dwWidth);
	//SendMessage(hwndStatus,SB_SETTEXT,0,(LPARAM)"红");
	//SendMessage(hwndStatus,SB_SETTEXT,0,(LPARAM)"R:00:00:00");
	////SendMessage(hwndStatus,SB_SETTEXT,2,(LPARAM)"黑");
	//SendMessage(hwndStatus,SB_SETTEXT,1,(LPARAM)"B:00:00:00");
	//SendMessage(hwndStatus,SB_SETTEXT,4,(LPARAM)"输入> 炮二平五");
    SendMessage(hwndStatus,SB_SETTEXT,0,(LPARAM)"系统初始化正常...");
	
	char buf[MSG_SIZ];
	//StringCbPrintf(buf,MSG_SIZ,"%schessboard\\%d\\timeRed.ico",
	//		installDir,appData.pieceStyle);	
	//HANDLE timeicon = LoadImage(hInst,buf,IMAGE_ICON,
	//	14,
	//	14,
	//	LR_LOADFROMFILE);
	//SendMessage(hwndStatus,SB_SETICON,0,(LPARAM)timeicon);

	//StringCbPrintf(buf,MSG_SIZ,"%schessboard\\%d\\timeBlue.ico",
	//		installDir,appData.pieceStyle);	
	//timeicon = LoadImage(hInst,buf,IMAGE_ICON,
	//	14,
	//	14,
	//	LR_LOADFROMFILE);
	//SendMessage(hwndStatus,SB_SETICON,1,(LPARAM)timeicon);

	StringCbPrintf(buf,MSG_SIZ,"%schessboard\\%d\\status.ico",
			installDir,appData.pieceStyle);	
	HANDLE timeicon = LoadImage(hInst,buf,IMAGE_ICON,
		14,
		14,
		LR_LOADFROMFILE);
	SendMessage(hwndStatus,SB_SETICON,0,(LPARAM)timeicon);
	return hwndStatus;
}