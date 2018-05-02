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

//#define S0_LEN 80
//#define S1_LEN 54
//#define 

#define SEPRATE_ARR 4
              //                     层  分  T  NPS 变
	int slen[SEPRATE_ARR] = {80, 200, 100, 1024};

	//int slen[SEPRATE_ARR] = {80, 48, 40, 500,55, 64, 48, 40, 200};

	int dwWidth[SEPRATE_ARR];


	dwWidth[0] = slen[0];

	for(int i = 1; i < SEPRATE_ARR; i++){
		dwWidth[i] = dwWidth[i-1] + slen[i]; 
	}

	SendMessage(hwndStatus,SB_SETPARTS,SEPRATE_ARR,(LPARAM)&dwWidth);
	SendMessage(hwndStatus,SB_SETTEXT,0,(LPARAM)L"当前状态");
	SendMessage(hwndStatus,SB_SETTEXT,1,(LPARAM)L"当前变例");
	//SendMessage(hwndStatus,SB_SETTEXT,2,(LPARAM)L"No.");
	SendMessage(hwndStatus,SB_SETTEXT,2,(LPARAM)L"佳佳象棋!");
	
	TCHAR buf[MSG_SIZ];

	for(int i = 0; i < 3; i++){

		StringCbPrintf(buf,MSG_SIZ,_T("%schessboard\\%d\\status%d.ico"),
			installDir,appData.pieceStyle,i);	

		HANDLE timeicon = LoadImage(hInst,buf,IMAGE_ICON,
			14,
			14,
			LR_LOADFROMFILE);

		SendMessage(hwndStatus,SB_SETICON,i,(LPARAM)timeicon);
	}

	return hwndStatus;
}