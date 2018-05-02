#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

#include <sys/stat.h>
#include <commdlg.h>
#include <dlgs.h>
#include <commctrl.h>

//CMX_183CN_Get_Pass_By_Client(str,passbuf); 
//SendToICSDelayed(passbuf, MXQ_LOG_DELAY_MS);

LRESULT CALLBACK
GoPlaceDialogCallBack(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam){
    //char passbuf[128];
    TCHAR *pcommand;
    //bool is183;
    MINMAXINFO* mmi;
    switch(message){
        case WM_INITDIALOG:
            PostMessage(hDlg, WM_SETICON, (WPARAM) TRUE, (LPARAM) appData.iconWhite); 
            return FALSE;            
        case WM_COMMAND:  
            switch(LOWORD(wParam)){
                    case IDC_DIR_1:
                        pcommand = L"go 1";
                        break;
                    case IDC_DIR_2:
                        pcommand = L"go 2";
                        break;
                    case IDC_DIR_3:
                        pcommand = L"go 3";
                        break;
                    case IDC_DIR_4:
                        pcommand = L"go 4";
                        break;
                    case IDC_DIR_5:
                        pcommand = L"go 5";
                        break;
                    case IDC_DIR_6:
                        pcommand = L"go 6";
                        break;
                    case IDC_DIR_7:
                        pcommand = L"go 7";
                        break;
                    case IDC_DIR_8:
                        pcommand = L"go 8";
                        break;
                    default:
                        return FALSE;
                        break;
                }
            if(appData.ACPSics.ICS_net_id == ICS_MXQ_EN183 ||
                    appData.ACPSics.ICS_net_id == ICS_MXQ_CN183){
                        CMX_183_SEND_CODDING(pcommand);
                        Sleep(500);
                        CMX_183_SEND_CODDING(L"map");
                }
                else{
					SendToICS(pcommand);
                    SendToICS(L"map\n");
                }

            break;
        case WM_SIZE:
            //FitTimeDisplayDlgItem(hDlg);
            break;
        case WM_CLOSE:
            //TimeDisplayListEvent();

            //如果子酱//IDC_GO_PLACE

            SendDlgItemMessage(HWND_CONSOLE,IDC_GO_PLACE,BM_SETCHECK,0,0);
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

	 dispboard_t* pDis = OBS[0];
    FARPROC lpProc  = MakeProcInstance((FARPROC)GoPlaceDialogCallBack,hInst);
    TAB.hwndGoPlace = CreateDialog(hInst,MAKEINTRESOURCE(IDD_GO_PLACE),
        pDis->hwndThis,(DLGPROC)lpProc);
    FreeProcInstance(lpProc);
    ShowWindow(TAB.hwndGoPlace,SW_HIDE);             //隐藏
    CenterWindow(TAB.hwndGoPlace,pDis->hwndThis);
}


void LogOut(TCHAR *data){
    ConsoleOutput(data,(int)wcslen(data),true);
    //SendToPlayer(data,(int)strlen(data));
}

void LogOuts(char *data){
	ConsoleOutput(CA2W(data), (int)strlen(data), true);
	//SendToPlayer(data,(int)strlen(data));
}


VOID
ConsoleOutput(TCHAR* data, int length, int forceVisible){
    HWND hText;

	static int total_num = 0;
	static int num = 0;

    //日志窗口句柄
    if(HWND_CONSOLE == NULL || length > CO_MAX-100 || length == 0){
        return;
    }	

	total_num += length;
	hText = TAB.hText;

	if (total_num > 28000){
		total_num = 0;
		num++;
		TCHAR buf[128];
		swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), L"日志数据太多，已清空了 %d 次！\n", num);

		CHARRANGE  sel;
		sel.cpMin = 0;
		sel.cpMax = -1;
		SendMessage(hText, EM_EXSETSEL, 0, (LPARAM)&sel);
		SendMessage(hText, EM_REPLACESEL, 0, (LPARAM)buf);
	}	

	SendMessage(hText, EM_SETSEL, -1, -1);
	SendMessage(hText, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&appData.AconsoleCF);
	SendMessage(hText, EM_REPLACESEL, 0, (LPARAM)data);
	PostMessage(hText, WM_VSCROLL, SB_BOTTOM, 0);

	return;

}

void			//画上棋盘的线，与边框线
ChartDrawGridOnDC(HWND hwnd, dispboard_t* pDis, HDC hdc, HDC tmphdc, HDC hdcmask){
	HPEN oldPen;
	RECT Rect;
	GetClientRect(hwnd, &Rect);
	int x;
	int y;

	static POINT apt[MAX_GAME_LENGTH];

	int cx = Rect.right - Rect.left;
	int cy = Rect.bottom - Rect.top;

	//画上棋盘
	//SelectObject(tmphdc, (HBITMAP)pDis->chessQbBitmap);
	//BitBlt(hdc,
	//	pDis->boardRect.left,
	//	pDis->boardRect.top,
	//	boardWidth_x,
	//	boardWidth_y,
	//	tmphdc, 0, 0, SRCCOPY);

	HBRUSH hBrush = CreateSolidBrush(RGB(250,250,250));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	Rectangle(hdc, 0, 0, cx+1, cy+1);
	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);

	if (true){	    //画上底线格子

		HPEN pen[5];
		//pen[0] = CreatePen(PS_SOLID, 1, RGB(189, 99,  197));   // 中线，红色
		pen[0] = CreatePen(PS_SOLID, 1, RGB(255,   0, 255));     // 中线，红色
		pen[1] = CreatePen(PS_SOLID, 1, RGB(220, 220, 220));     // 格子线，淡灰色
		pen[2] = CreatePen(PS_SOLID, 1, RGB(255,   0,   0));	 // 红方的分数	
		pen[3] = CreatePen(PS_SOLID, 1, RGB(  0,   0, 255));	 // 黑方的分数	
		pen[4] = CreatePen(PS_SOLID, 1, RGB( 80,  80,  80));	 // 当前步的颜色	
		///////////////////////////////////////////
		// 画格子线
		oldPen = (HPEN)SelectObject(hdc, pen[1]);
		int ynum  = 10;
		int grid = cy / (ynum);
		y = cy/2;
		int y1 = y;
		int y2 = y;
		// 先画横纹
		for (int i = 0; i < ynum/2; i++){	
			y1 -= grid;
			MoveToEx(hdc, 1, y1, NULL);
			LineTo(hdc, cx-1, y1);

			y2 += grid;
			MoveToEx(hdc, 1, y2, NULL);
			LineTo(hdc, cx - 1, y2);
		}

		int xnum = cx / grid;
		int x1 = grid;
		for (int i = 0; i < xnum; i++){
			MoveToEx(hdc, x1, 1, NULL);
			LineTo(hdc, x1, cy-1);
			x1 += grid;
		}

		///////////////////////////////////////////
		// 画一个水平线
		SelectObject(hdc, pen[0]);
		x = 1;
		y = cy / 2;
		MoveToEx(hdc, x, y, NULL);
		x = cx - 1;
		LineTo(hdc, x, y);

		///////////////////////////////////////////
		// 求最大的要求点数
		int ply    = pDis->pos->gply;
		if (pDis->pos->gply == 0){
			ply = 1;
		}
		int Disply = cx * SCORE_WIDTH / 100;
		int MaxScore = 500;         // 最大500分
		int heigh = cy / 2 - 2;

		float step = (float)Disply / (float)ply;
		float xs = step;
		for (int i = 0; i < pDis->pos->gply; i++){

			apt[i + 0].y = cy/2;

			int score = pDis->pos->His[i].search_score;

			int h = score * heigh / MaxScore;

			if (h > heigh){
				h = heigh;
			}
			else if (h < -heigh){
				h = -heigh;
			}			

			apt[i + 0].y -= h;
			apt[i + 0].x = (int)xs;
			xs += step;
		}

		///////////////////////////////////////////
		// 画黑方的分数
		SelectObject(hdc, pen[2]);
		//PolyBezier(hdc, apt, pDis->pos->gply/2+1);
		MoveToEx(hdc, 0, cy/2, NULL);
		for (int i = 0; i < pDis->pos->gply; i+=2){
			LineTo(hdc, apt[i].x, apt[i].y);
		}

		///////////////////////////////////////////
		// 画红方的分数
		SelectObject(hdc, pen[3]);
		MoveToEx(hdc, 0, cy / 2, NULL);
		for (int i = 1; i < pDis->pos->gply; i+=2){
			LineTo(hdc, apt[i].x, apt[i].y);
		}

		///////////////////////////////////////////
		// 当前步子画一条竖线
		//pDis->pos->curStep
		SelectObject(hdc, pen[4]);
		int dx = int(pDis->pos->curStep * step);
		if (dx < 0){
			dx = 0;
		}
		MoveToEx(hdc, dx,  2, NULL);
		LineTo(hdc, dx, cy-1);

		DeleteObject(pen[0]);
		DeleteObject(pen[1]);
		DeleteObject(pen[2]);
		DeleteObject(pen[3]);
		DeleteObject(pen[4]);
	}
	SelectObject(hdc, oldPen);
}

void			//画上棋格坐标............................................
ChartDrawCoordsOnDC(HWND hwnd, dispboard_t* pDis, HDC hdc){
	//static char files[18] = {'0','1','2','3','4','5','6','7','8',
	//    '8','7','6','5','4','3','2','1','0'};
	//static char ranks[20] = {'I','J','H','G','F','E','D','C','B','A',
	//    'A','B','C','D','E','F','G','H','I','J'};


	static char files[20] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
		'i', 'i', 'h', 'g', 'f', 'e', 'd', 'c', 'b', 'a' };
	static char ranks[20] = { '9', '8', '7', '6', '5', '4', '3', '2', '1', '0',
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

	TCHAR str[2] = { NULLCHAR, NULLCHAR };
	int oldMode, oldAlign, x, y, start, i;
	HFONT oldFont;
	HBRUSH oldBrush;

	if (!appData.showCoords)				//如果不显示坐标
		return;

	start = pDis->flipView ? 10 : 0;

	oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(BLACK_BRUSH));

	/*oldMode = SetBkMode(hdc, (appData.monoMode ? OPAQUE : TRANSPARENT));*/

	oldMode = SetBkMode(hdc, (TRANSPARENT));

	oldAlign = GetTextAlign(hdc);

	oldFont = (HFONT)SelectObject(hdc, appData.Afont[pDis->bsize][COORD_FONT]->hf); //坐标字体

	y = pDis->boardRect.top + pDis->lineGap;
	x = pDis->boardRect.left + pDis->lineGap;

	SetTextAlign(hdc, TA_LEFT | TA_TOP);
	for (i = 0; i < 10; i++) {
		str[0] = ranks[start + i];
		ExtTextOut(hdc, x + 2, y + 1 + pDis->bsize / 2, 0, NULL, str, 1, NULL);
		y += pDis->squareSize + pDis->lineGap;
	}

	SetTextAlign(hdc, TA_RIGHT | TA_BOTTOM);
	for (i = 0; i < 9; i++) {
		str[0] = files[start + i];
		ExtTextOut(hdc, x + pDis->squareSize - 2, y - 1, 0, NULL, str, 1, NULL);
		x += pDis->squareSize + pDis->lineGap;
	}

	SelectObject(hdc, oldBrush);
	SetBkMode(hdc, oldMode);
	SetTextAlign(hdc, oldAlign);
	SelectObject(hdc, oldFont);
}

void            //显示
HDCDrawChart(HWND hwnd, dispboard_t* pDis, HDC hdc, BOOLEAN repaint){

	int releaseDC;
	int x;
	//int y;
	//int x2, y2;
	int num_clips = 0;
	//int i;
	HDC tmphdc;
	HDC hdcmem;
	HBITMAP bufferBitmap;
	HBITMAP oldBitmap;
	RECT Rect;
	HRGN clips[MAX_CLIPS];

	Boolean fullrepaint = repaint;		//是否要重新全部显示

	if (IsIconic(hwnd)) {		//如果当前是图标化了
		return;
	}

	if (hdc == NULL) {
		hdc = GetDC(hwnd);
	
		SelectPalette(hdc, pDis->hPal, FALSE);
		RealizePalette(hdc);

		releaseDC = TRUE;
	}
	else {
		releaseDC = FALSE;
	}

	//SetBkColor(hdc, RGB(0, 0, 205));
	/* Create some work-DCs */
	hdcmem = CreateCompatibleDC(hdc);
	tmphdc = CreateCompatibleDC(hdc);
	HDC hdcmask = CreateCompatibleDC(hdc);


	/* Figure out which squares need updating by comparing the
	* newest board with the last drawn board and checking if
	* flipping has changed.
	*/
	//计算一下那些棋格要更新,与上一次的棋盘相比较
	if (!fullrepaint) {
		fullrepaint = TRUE;
	}			
	else{
		fullrepaint = TRUE;
	}

	/* Create a buffer bitmap - this is the actual bitmap
	* being written to.  When all the work is done, we can
	* copy it to the real DC (the screen).  This avoids
	* the problems with flickering.
	*/
	//建立一个缓冲图像,我们在上面做全部工作,然后再写到屏幕上,可避免闪烁
	//GetClientRect(hwndMain,&Rect);
	GetClientRect(hwnd, &Rect);
	bufferBitmap = CreateCompatibleBitmap(hdc, Rect.right - Rect.left+1,
		Rect.bottom - Rect.top+1);
	oldBitmap = (HBITMAP)SelectObject(hdcmem, bufferBitmap);

	SelectPalette(hdcmem, pDis->hPal, FALSE);


	/* Create clips for dragging */  //找出要更新的区域
	if (!fullrepaint) {
	}


	/* No clips?  Make sure we have fullrepaint set to TRUE */
	if (num_clips == 0)
		fullrepaint = TRUE;
	/* Set clipping on the memory DC */
	if (!fullrepaint) {
		SelectClipRgn(hdcmem, clips[0]);
		for (x = 1; x < num_clips; x++) {
			if (ExtSelectClipRgn(hdcmem, clips[x], RGN_OR) == ERROR)
				abort();  // this should never ever happen!
		}
	}
	/* Do all the drawing to the memory DC */
	ChartDrawGridOnDC(hwnd, pDis, hdcmem, tmphdc, hdcmask);	    //画上棋格
	//DrawHighlightsOnDC(pDis, hdcmem);							//高亮	
	//DrawBoardOnDC(pDis, hdcmem, B256, tmphdc, hdcmask);		//画上棋子
	//ChartDrawCoordsOnDC(hwnd, pDis, hdcmem);				    //坐标


	/* Release the bufferBitmap by selecting in the old bitmap
	* and delete the memory DC
	*/
	SelectObject(hdcmem, oldBitmap);
	DeleteDC(hdcmem);
	DeleteDC(hdcmask);

	/* Set clipping on the target DC */
	if (!fullrepaint) {
		SelectClipRgn(hdc, clips[0]);
		for (x = 1; x < num_clips; x++) {
			if (ExtSelectClipRgn(hdc, clips[x], RGN_OR) == ERROR)
				abort();   // this should never ever happen!
		}
	}

	/* Copy the new bitmap onto the screen in one go.
	* This way we avoid any flickering,显示整个棋盘
	*/
	oldBitmap = (HBITMAP)SelectObject(tmphdc, bufferBitmap);
	BitBlt(hdc, 
		0, 
		0,
		Rect.right - Rect.left,
		Rect.bottom - Rect.top,
		tmphdc, 
		0, 
		0, SRCCOPY);
	SelectObject(tmphdc, oldBitmap);

	/* Massive cleanup */
	for (x = 0; x < num_clips; x++){
		DeleteObject(clips[x]);
	}


	DeleteDC(tmphdc);
	DeleteObject(bufferBitmap);

	if (releaseDC) {
		ReleaseDC(hwnd, hdc);
	}
}

void			//主窗口绘图程序
PaintChartProc(dispboard_t* pDis, HWND hwnd){
	HDC         hdc;
	PAINTSTRUCT ps;
	//HFONT       oldFont;

	//if(hdc = BeginPaint(hwnd, &ps)) {
	if (hdc = BeginPaint(hwnd, &ps)) {

		HDCDrawChart(hwnd, pDis, hdc, true);

		//HBRUSH hbrush = CreateSolidBrush(RGB(0, 0, 255));
		//::SetBkColor(hdc, RGB(0, 0, 205));
		//SetTextColor(hdc, RGB(255, 0, 0));

		EndPaint(hwnd, &ps);
	}
	return;
}

LRESULT CALLBACK        //棋局形势曲线子类化
ConsoleChartSubclass(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){

	dispboard_t* pDis = OBS[0];
	//HWND hInput;
	//CHARRANGE sel;

	//return false;

	switch (message) {
	
	case WM_PAINT:   // 要重绘图形了
		PaintChartProc(pDis,hwnd);
		break;
	case WM_LBUTTONDOWN:
	{
		// 棋步选择， 
		
		RECT Rect;
		int mx = LOWORD(lParam);
		GetClientRect(hwnd, &Rect);
		int cx = Rect.right - Rect.left;

		int ply = pDis->pos->gply;
		if (pDis->pos->gply == 0){
			ply = 1;
		}
		int Disply = cx * SCORE_WIDTH / 100;
		float step = (float)Disply / (float)ply;

		int p = int(mx / step);

		ToNrEvent(pDis,p);
		HDCDrawChart(TAB.dlgScore, pDis, NULL, true);
	}
		break;
	case WM_MBUTTONDOWN:
		//return SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(IDM_QuickPaste, 0), 0);
		break;
	case WM_RBUTTONDOWN:
		//if (!(GetKeyState(VK_SHIFT) & ~1)) {
		//	/* Move selection here if it was empty */
		//	POINT pt;
		//	pt.x = LOWORD(lParam);
		//	pt.y = HIWORD(lParam);
		//	SendMessage(hwnd, EM_EXGETSEL, 0, (LPARAM)&sel);
		//	if (sel.cpMin == sel.cpMax) {
		//		sel.cpMin = (LONG)SendMessage(hwnd, EM_CHARFROMPOS, 0, (LPARAM)&pt); /*doc is wrong*/
		//		sel.cpMax = sel.cpMin;
		//		SendMessage(hwnd, EM_EXSETSEL, 0, (LPARAM)&sel);
		//	}
		//	SendMessage(hwnd, EM_HIDESELECTION, FALSE, FALSE);
		//}
		break;
	case WM_RBUTTONUP:
		//if (GetKeyState(VK_SHIFT) & ~1) {
		//	SendDlgItemMessage(HWND_CONSOLE, OPT_ConsoleText,
		//		WM_COMMAND, MAKEWPARAM(IDM_QuickPaste, 0), 0);
		//}
		//else {
		//	//POINT pt;
		//	//HMENU hmenu = LoadIcsTextMenu(DIS.icsTextMenuEntry);
		//	//SendMessage(hwnd, EM_EXGETSEL, 0, (LPARAM)&sel);
		//	//if (sel.cpMin == sel.cpMax) {
		//	//    EnableMenuItem(hmenu, IDM_Copy, MF_BYCOMMAND|MF_GRAYED);
		//	//    EnableMenuItem(hmenu, IDM_QuickPaste, MF_BYCOMMAND|MF_GRAYED);
		//	//}
		//	//if (!IsClipboardFormatAvailable(CF_TEXT)) {
		//	//    EnableMenuItem(hmenu, IDM_Paste, MF_BYCOMMAND|MF_GRAYED);
		//	//}
		//	//pt.x = LOWORD(lParam);
		//	//pt.y = HIWORD(lParam);
		//	//MenuPopup(hwnd, pt, hmenu, -1);
		//}
		return 0;
	case WM_COMMAND:
		break;
	}

	return (*TAB.consoleScoreChartWindowProc)(hwnd, message, wParam, lParam);
}

LRESULT CALLBACK        //显示rich_edit子类化
ConsoleTextSubclass(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){

	 dispboard_t* pDis = OBS[0];
    //HWND hInput;
    CHARRANGE sel;

	//return false;

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
                  if (IsIconic(pDis->hwndThis)){
                      ShowWindow(pDis->hwndThis, SW_RESTORE);
                  }
                  //if (DIS.buttonDesc[0].hwnd) {
                  //    SetFocus(DIS.buttonDesc[0].hwnd);
                  //} 
                  //else {
                  SetFocus(pDis->hwndThis);
                  //}
              }  else {
                  /* unshifted */
                  //SetFocus(GetDlgItem(DIS.hwndConsole, OPT_ConsoleInput));
                  //SetFocus(TAB.hInput);
              }
          } else {
              //hInput = GetDlgItem(DIS.hwndConsole, OPT_ConsoleInput);
              //SetFocus(hInput);
//              SetFocus(TAB.hInput);
              //SendMessage(TAB.hInput, message, wParam, lParam);
          }
          return 0;
	  case WM_PASTE:{
		  //hInput = GetDlgItem(DIS.hwndConsole, OPT_ConsoleInput);
		  //SetFocus(hInput);
		  //          SetFocus(TAB.hInput);
		  // return SendMessage(TAB.hInput, message, wParam, lParam);
	  }
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
              SendDlgItemMessage(HWND_CONSOLE, OPT_ConsoleText, 
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
//              SendMessage(TAB.hInput, WM_PASTE, 0, 0);
  //            SetFocus(TAB.hInput);
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
	
    return (*TAB.consoleTextWindowProc)(hwnd,message,wParam,lParam);
}

void USER_INPUT_COMMAND(TCHAR *buf){
    TCHAR *p;
    if((p = wcsstr(buf,L"position fen ")) != NULL){       //用用户输入了一个局面

    }
}


/////////////////////////////////////////////////////////////////////////
// 对齐窗口

void FitRichLogDlgPosition(HWND hDlg){

	dispboard_t *pDis = OBS[0];

    RECT Rect;
    GetWindowRect(pDis->hwndThis,&Rect);

    int x       = Rect.right;
    int y       = Rect.top ;
	int width = LOG_WIN_WIDTH;
    int height  = Rect.bottom - Rect.top;

    SetWindowPos(hDlg,NULL,x,y,width,height,SWP_NOZORDER|SWP_NOACTIVATE);

    ShowWindow(hDlg,SW_SHOW);

    //PostMessage(hDlg,WM_SIZE,0,MAKELONG(width,height));///
}

int 
ConnectToIcs(void){

    TCHAR buf[MSG_SIZ];

    appData.useTelnet = false;
    int err = establish();

    if(err != 0){
		swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), _T("不能建立连线：网站：%s, 端口：%d\n"),
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
			case ICS_XQCLUB:
				appData.AtelnetISR =
					AddInputSource(appData.AicsPR, FALSE, read_from_ics_xqclub, &appData.AtelnetISR);
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
        //SetWindowText(HWND_CONSOLE,"日志信息:已联机(尚未登录成功)");
		SetIcsTitleName(_T("已联机(尚未登录成功)"));

		//联机后，可显示弈天的其它按钮

		//重新显示一下，将相应的按钮显示出来

		RECT re;
		//GetWindowRect(hDlg,&re);
		GetClientRect(HWND_CONSOLE,&re);
		FitConsoleItemPosition(HWND_CONSOLE,(re.right - re.left),(re.bottom - re.top));	

        //将按钮设置成 退出
        //IDC_ICS_CONNECT
        //SetWindowText(DlgGetItem(
        SetDlgItemText(HWND_CONSOLE,IDC_ICS_CONNECT,_T("退出"));
    }

    appData.colorize = TRUE;

    return err;
}

int 
DisConnectIcs(void){
	LogOut(_T("\n正在断开连接，请稍候．．．\n"));

	ICS.cont_dalei = FALSE;

    if(appData.ACPSics.ICS_net_id == ICS_MXQ_EN183 ||
        appData.ACPSics.ICS_net_id == ICS_MXQ_CN183){
        //SendToICS("quit\n");
        CMX_183_SEND_CODDING(L"quit");
    }
    else{
        SendToICS(L"quit\n"); 
    }

    
    //if(DIS.telnetISR != NULL){
    //     RemoveInputSource(DIS.telnetISR);
    //}
    //if (DIS.icsPR != NoProc) {
    //    DestroyChildProcess(DIS.icsPR, TRUE);
    //}
    return 0;
}



/////////////////////////////////////////////////////////////////
/// 调整日志窗口中每个控件的大小
void 
FitConsoleItemPosition(HWND hDlg,int newSizeX,int newSizeY){
#define hInputHeigh                 20      //控制台输入的高度
#define ConSoleButHeigh             26      //控制台按钮的高度
#define ConSoleSideW                6
#define ConStep_Width               95
#define ConStep_Hight               100
//#define ConScore_High               60     // 双方形势的图表高度
#define BR_High                     45
//#define BOOK_HIGH                   70
    bool showOther;
    if(IsDlgButtonChecked(hDlg,IDC_MORE_BUTTON) == BST_CHECKED){  //IDC_MORE_BUTTON 
        showOther = true;
    }
    else{
        showOther = false;
    }


    int x, y, w, h;

    x   = 1;
    y   = 2;
    w   = newSizeX - 2;

	int stx = newSizeX - ConStep_Width - 2;
	SetWindowPos(TAB.dlgStepList, NULL, stx, y, ConStep_Width, ConStep_Hight, SWP_NOZORDER | SWP_NOACTIVATE);   //hText 是LogOut RichEdit


    //if(showStep == false){	//显示棋步
	//TAB.dlgStepList

	y = BR_High;
	h = ConStep_Hight - BR_High + 3;
 
	
	int sw = w - ConStep_Width - 2;
	SetWindowPos(TAB.dlgScore, NULL, x+1, y, sw-3, h-1, SWP_NOZORDER | SWP_NOACTIVATE);   //TAB.dlgScore 棋局形势控件

	y = ConStep_Hight + 4;
	h = newSizeY - 0 - 2 - ConSoleButHeigh - ConStep_Hight;

	// 形势图表控制位置与大小

  
	if(appData.icsActive == FALSE){			// ICS 连线功能还没好

		//将相应弈天的按钮隐藏了
		for(int a = 0; a < 10; a++){
			ShowWindow(GetDlgItem(hDlg,YT_LX_AN[a]), SW_HIDE); //共10个按钮
		}
		
	}
	else if(showOther == true){									// ICS 连线连上了
		h -= ConSoleButHeigh * 2 + 2;
	}

	SetWindowPos(TAB.hText, NULL, x, y, w, h, SWP_NOZORDER | SWP_NOACTIVATE);   //hText 是LogOut RichEdit

    w = (w-ConSoleSideW) / 5 - 1;
    x = ConSoleSideW / 2;
    y = y + h + 2;
    h = ConSoleButHeigh - 3;
    for(int i=0; i<5; i++){			//现在只用5个
        HWND b = GetDlgItem(HWND_CONSOLE,MXQ_ICS_BUT[i]);
        SetWindowPos(b,NULL,x,y,w,h,SWP_NOZORDER|SWP_NOACTIVATE);
        x += w + 2;
		//ShowWindow(b, SW_SHOW);
    }

	//HWND ff = GetDlgItem(HWND_CONSOLE, MXQ_ICS_BUT[0]);
	//SetWindowPos(ff, NULL, 0, 100, 300, 300, SWP_NOZORDER | SWP_NOACTIVATE);
	//ShowWindow(ff, SW_SHOW);


	//弈天按键

	if(appData.icsActive == TRUE){
		
		for(int p=0; p<2; p++){		//一共二行

			w = newSizeX - 2;

			w = (w - ConSoleSideW) / 5 - 1;

			x = ConSoleSideW / 2;

			h = ConSoleButHeigh - 3;

			y = y + h + 4;
			
			for(int a = 0; a < 5; a++){

				HWND Hbut = GetDlgItem(HWND_CONSOLE, YT_LX_AN[p*5 + a]);

				SetWindowPos(Hbut,NULL,x,y,w,h,SWP_NOZORDER|SWP_NOACTIVATE);

				x += w+2;
			}
		}

		for(int a = 0; a < 10; a++){
			ShowWindow(GetDlgItem(hDlg,YT_LX_AN[a]), SW_SHOW);
		}
	}
}

//调整窗口的大小
void FitMainTabPosition(dispboard_t *pDis){

	//dispboard_t *pDis = OBS[0];

	HWND hDlg = TAB.tabMain;

    RECT Rect;
    GetWindowRect(pDis->hwndThis,&Rect);

    int x       = Rect.right;
    int y       = Rect.top ;
	int width = LOG_WIN_WIDTH;
    int height  = Rect.bottom - Rect.top;

    SetWindowPos(hDlg,NULL,x,y,width,height,SWP_NOZORDER|SWP_NOACTIVATE);

    ShowWindow(hDlg,SW_SHOW);
}

void FitMainTabSubItemPosition(HWND hDlg, int newX, int newY){

	//RECT Rect;
 //   GetWindowRect(pDis->hwndThis,&Rect);

	//int tt = 0;

	//先调整一下Tab的位置
	int x, y, w, h;

	x =  1;
	y =  1;
	w = newX - 1;
	h = newY - 1;

	SetWindowPos(TAB.tab,NULL,x,y,w,h,SWP_NOZORDER|SWP_NOACTIVATE);

	//再设子窗口的位置

	x = 2;
	y = 2;
	w = w - 6;
	h = h - 26;

	//调整日志窗口的大小
	for(int i = 0; i < TIE_NUM; i++){
		SetWindowPos(TAB.dlgTab[i],NULL,x,y,w,h,SWP_NOZORDER|SWP_NOACTIVATE);
	}

}

LRESULT CALLBACK
MainTabWndProc(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam){
	MINMAXINFO *mmi;
    static int sizeX, sizeY;
    int newSizeX, newSizeY;

	switch(message){
		case WM_INITDIALOG: {
			//设置第一个图标
            PostMessage(hDlg, WM_SETICON, (WPARAM) TRUE, (LPARAM) appData.iconWhite);

			//加入TAB 
			TAB.tab = CreateWindow( 
				WC_TABCONTROL, _T(""), 
				WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE |TCS_BOTTOM | TCS_HOTTRACK, 
				0,
				0, 
				100,
				200, 
				hDlg, 
				(HMENU)hwndTabID,         //控件ＩＤ
				hInst,
				NULL );

			HGDIOBJ of = GetStockObject(DEFAULT_GUI_FONT);        //设置一下缺省字体
			SendMessage(TAB.tab, WM_SETFONT, (WPARAM)of,TRUE);

			TCITEM tie;    
			tie.mask = TCIF_TEXT | TCIF_PARAM; 
			tie.iImage = -1;
			
			TCHAR TieTitle[TIE_NUM][20]={
				{ _T("日志") },
				{ _T("引擎") },
				{ _T("分析") },
				{ _T("其它") },
			};	


			for (int i = 0; i < TIE_NUM; i++) { 
				tie.pszText = TieTitle[i];
				tie.lParam  = i; 
				if (TabCtrl_InsertItem(TAB.tab, i, &tie) == -1) { 
					DestroyWindow(TAB.tab); 
					//return NULL; 
				} 
			} 

			TabCtrl_SetMinTabWidth(TAB.tab,5);

			TAB.tabChosen = DLOG;

			//-----------------------------------------------------------------------
		    //放入子窗口

			//日志
			TAB.dlgTab[DLOG] = CreateDialogParam(hInst,(LPCWSTR)DLG_RICH_LOG, TAB.tab,
				(DLGPROC)ConsoleWndProc,NULL);

			//棋库
			//TAB.dlgTab[DBOOK] = CreateDialogParam(hInst,(LPCWSTR)DLG_BOOK,    TAB.tab,
			//	(DLGPROC)DLG_BOOK_PROC,NULL);

			
			//HWND_CONSOLE = DLG.TAB.dlgTab[DLOG];
			SendDlgItemMessage(HWND_CONSOLE, IDC_MORE_BUTTON,BM_SETCHECK,0, 0);  //更多按钮 

			//-----------------------------------------------------------------------

			ShowWindow(TAB.dlgTab[TAB.tabChosen],SW_SHOWDEFAULT);

							}

			break;
		case WM_COMMAND:
			break;
		case WM_NOTIFY:
			if(wParam == hwndTabID){
				NMHDR *lnm = (NMHDR *)lParam;
				if(lnm->code == TCN_SELCHANGE){//改变了选项卡哇
					ShowWindow(TAB.dlgTab[TAB.tabChosen],SW_HIDE);
				    TAB.tabChosen = (int)SendMessage(TAB.tab,TCM_GETCURSEL,0,0);
					ShowWindow(TAB.dlgTab[TAB.tabChosen],SW_SHOW);
					//FitTabDialogToTabControl();			//重新调整大小	
					//FitMainTabPosition(OBS[0]);
				}
			}
			break;

		case WM_SIZE:
			//FitRichLogDlgItem(hDlg);
			if(IsIconic(hDlg)){
				break;
			}
			newSizeX = LOWORD(lParam);
			newSizeY = HIWORD(lParam);
			if(sizeX != newSizeX || sizeY != newSizeY){

				FitMainTabSubItemPosition(hDlg,newSizeX,newSizeY);
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
	}

	return false;
}

//LRESULT CALLBACK SCORE_CHART_Proc(HWND hwnd, UINT msg,
//	WPARAM wParam, LPARAM lParam){
//
//	WNDCLASS rwc = { 0 };
//	INITCOMMONCONTROLSEX InitCtrlEx;
//	//初始化通用控件类
//	InitCtrlEx.dwSize = sizeof(INITCOMMONCONTROLSEX);
//	InitCtrlEx.dwICC = ICC_BAR_CLASSES;
//	InitCommonControlsEx(&InitCtrlEx);
//
//	switch (msg){
//	case WM_CREATE:
//
//		break;
//
//	case WM_PAINT:
//
//		break;
//
//	case WM_DESTROY:
//
//		PostQuitMessage(0);
//		break;
//
//	}
//
//	return DefWindowProc(hwnd, msg, wParam, lParam);
//}

//WNDCLASS wc = { 0 };

LRESULT CALLBACK
ConsoleWndProc(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam){
    MINMAXINFO *mmi;
    static int sizeX, sizeY;
    int newSizeX, newSizeY;
	static int  curSel;
	static int  ListId;
	static int  move;
	TCHAR str[512];
    InputSource *is = TAB.consoleInputSource;
	dispboard_t* pDis = OBS[0];


    switch(message){
        case WM_INITDIALOG:  
            //设置第一个图标
            PostMessage(hDlg, WM_SETICON, (WPARAM) TRUE, (LPARAM) appData.iconWhite);

            TAB.hText   = GetDlgItem(hDlg,OPT_RichLog);
			TAB.dlgScore = GetDlgItem(hDlg, IDC_LineChart_Score);
			TAB.dlgStepList = GetDlgItem(hDlg, IDC_LIST_STEP_MAIN);

			//SendMessage(TAB.hText, EM_EXGETSEL, 0, (LPARAM)&curSel);

            TAB.consoleTextWindowProc  = (WNDPROC)(__int64)
   				SetWindowLongPtr(TAB.hText,GWLP_WNDPROC,(__int64)ConsoleTextSubclass);

			//SendMessage(TAB.hText, EM_EXGETSEL, 0, (LPARAM)&curSel);

            TAB.consoleScoreChartWindowProc   = (WNDPROC)(__int64)
				SetWindowLongPtr(TAB.dlgScore, GWLP_WNDPROC, (__int64)ConsoleChartSubclass);

			//int cursel;
			//int aa;
			//SendMessage(TAB.hText, EM_EXGETSEL, 0, (LPARAM)&cursel);

            Colorize(ColorChannel1,TRUE);

            ChangedConsoleFont();
            //  初始化输入框的字体
//            SendMessage(TAB.hInput,EM_SETCHARFORMAT,SCF_ALL,(LPARAM)&appData.AconsoleCF);   

            TAB.consoleEcho = true;

			//////////////////////////////////////////////////////
			// 创建自定义分数显示控件
			//WNDCLASS wc = { 0 };
			//wc.lpszClassName = L"SCORE_CHART_CLASS";
			//wc.hInstance = hInst;
			//wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
			//wc.lpfnWndProc = SCORE_CHART_Proc;
			//wc.hCursor = LoadCursor(0, IDC_ARROW);
			////注册窗口类
			//RegisterClass(&wc);
			//TAB.dlgScore = CreateWindow(wc.lpszClassName, L"Score Chart control",
			//	WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CLIPCHILDREN,
			//	100, 100, 400, 250, 0, 0, hInst, 0);


			return FALSE;
        case WM_COMMAND:
			pDis = OBS[0];                     //这是主窗口
			switch (LOWORD(wParam)){
			case IDC_ICS_CONNECT:       //连线按钮
			{
				if (appData.icsActive == FALSE){
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
				if (IsDlgButtonChecked(hDlg, IDC_GO_PLACE) == BST_CHECKED){
					ShowWindow(TAB.hwndGoPlace, SW_SHOW);
				}
				else{
					ShowWindow(TAB.hwndGoPlace, SW_HIDE);
				}
				break;
			case IDC_BUT_ICS_BOARD:
				if (IsDlgButtonChecked(hDlg, IDC_BUT_ICS_BOARD) == BST_CHECKED){
					ShowWindow(TAB.hwndICS_Board_List, SW_SHOW);
				}
				else{
					ShowWindow(TAB.hwndICS_Board_List, SW_HIDE);
				}
				break;
			case IDC_MORE_BUTTON:      //显示棋步与时间
			{
				//先得到当前的窗口的大小{
				RECT re;
				//GetWindowRect(hDlg,&re);
				GetClientRect(hDlg, &re);
				FitConsoleItemPosition(hDlg, (re.right - re.left), (re.bottom - re.top));
			}
				break;
			case IDC_LX_8:        //离开棋桌
				if (pDis->table != 0){		//只有旁观可离开	
					swprintf_s(str, sizeof(str) / sizeof(TCHAR), L"l %d", pDis->table);
					CMX_183_SEND_CODDING(str);
				}
				else{
					//sprintf_s(str,sizeof(str),"l %d",pDis->table);
					swprintf_s(str, sizeof(str) / sizeof(TCHAR), L"l");
					CMX_183_SEND_CODDING(str);
				}
				break;
			case IDC_LX_3:          //要求换边
				if (pDis->table != 0){
					swprintf_s(str, sizeof(str) / sizeof(TCHAR), L"side %d", pDis->table);
					CMX_183_SEND_CODDING(str);
				}
				break;
			case IDC_LX_5:         //握手求和
				if (pDis->table != 0){
					swprintf_s(str, sizeof(str) / sizeof(TCHAR), L"pass %d", pDis->table);
					CMX_183_SEND_CODDING(str);
				}
				break;
			case IDC_LX_4:		   //加入棋桌
				if (pDis->table != 0){
					swprintf_s(str, sizeof(str) / sizeof(TCHAR), L"j %d", pDis->table);
					CMX_183_SEND_CODDING(str);
				}
				break;
			case IDC_lX_1:		  //同意对局
				if (pDis->table != 0){
					swprintf_s(str, sizeof(str) / sizeof(TCHAR), L"a %d", pDis->table);
					CMX_183_SEND_CODDING(str);
				}
				break;
			case IDC_LX_6:        //投子认负
				if (pDis->table != 0){
					swprintf_s(str, sizeof(str) / sizeof(TCHAR), L"res %d", pDis->table);
					CMX_183_SEND_CODDING(str);
				}
				break;
				//if(IsDlgButtonChecked(hDlg,IDC_GO_PLACE) == BST_CHECKED){   //转地按钮按下了
			case IDC_LX_7:
				//要求仲裁
			{
				if (pDis->table != 0){
					//sprintf_s(str,sizeof(str),"rest judge %d",pDis->table);
					//CMX_183_SEND_CODDING(str);

					swprintf_s(str, sizeof(str) / sizeof(TCHAR), L"judge %d 6 bpi", pDis->table);
					CMX_183_SEND_CODDING(str);
					swprintf_s(str, sizeof(str) / sizeof(TCHAR), L"judge %d 2", pDis->table);
					CMX_183_SEND_CODDING(str);
					swprintf_s(str, sizeof(str) / sizeof(TCHAR), L"judge %d 4 opa", pDis->table);
					CMX_183_SEND_CODDING(str);
					swprintf_s(str, sizeof(str) / sizeof(TCHAR), L"flag %d 3", pDis->table);
					CMX_183_SEND_CODDING(str);

					//judge  6 bpi
					//judge 2
					//judge 4 opa
					//flag 3
				}
			}
				break;
				//if(IsDlgButtonChecked(hDlg,IDC_LX_9) == BST_CHECKED){  //连续打擂按键按下了
			case IDC_LX_9:
				if (IsDlgButtonChecked(hDlg, IDC_LX_9) == BST_CHECKED){
					ICS.cont_dalei = TRUE;
					LogOut(_T("\n当前已进入连续打擂状态"));
				}
				else{
					ICS.cont_dalei = FALSE;
					LogOut(_T("\n当前已取消连续打擂状态"));
				}
				break;
			case IDC_LX_10:
				if (IsDlgButtonChecked(hDlg, IDC_LX_10) == BST_CHECKED){
					ICS.only_this_table = TRUE;
					LogOut(_T("\n当前设定只在此桌下棋"));
				}
				else{
					ICS.only_this_table = FALSE;
					LogOut(_T("\n当前设定下一桌换一桌"));
				}
				break;
			default:
				break;
			}
			break;

		case WM_SETFOCUS:
//            SetFocus(TAB.hInput);
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

	dispboard_t *pDis = OBS[0];

	//************************************************
	if(TAB.tabMain){
		if(IsWindowVisible(TAB.tabMain)){
			ShowWindow(TAB.tabMain,SW_HIDE);
			CheckMenuItem(GetMenu(pDis->hwndThis),IDM_MAIN_TAB,MF_UNCHECKED);
		}
		else{
			ShowWindow(TAB.tabMain,SW_SHOW);
			CheckMenuItem(GetMenu(pDis->hwndThis),IDM_MAIN_TAB,MF_CHECKED);
		}
	}
	else{
		 FARPROC lpProc = MakeProcInstance((FARPROC)MainTabWndProc,hInst);
		 TAB.tabMain = CreateDialog(hInst,MAKEINTRESOURCE(IDD_SIDE_WIN),pDis->hwndThis,(DLGPROC)lpProc);
		 FreeProcInstance(lpProc);

         FitMainTabPosition(pDis);   //调整窗口的大小
		 ShowWindow(TAB.tabMain,SW_SHOW);
		 CheckMenuItem(GetMenu(pDis->hwndThis),IDM_MAIN_TAB,MF_CHECKED);
	}
	//************************************************
}
VOID
ChangedConsoleFont()
{
    
	
	//int cursel;
	//int aa;
	//SendMessage(TAB.hText, EM_EXGETSEL, 0, (LPARAM)&cursel);
	
	CHARFORMAT cfmt;
    CHARRANGE tmpsel, sel;
    MyFont *f   = appData.Afont[appData.bsize][CONSOLE_FONT];

    HWND hText    = TAB.hText;
    PARAFORMAT paraf;

    cfmt.cbSize = sizeof(CHARFORMAT);
    cfmt.dwMask = CFM_FACE|CFM_SIZE|CFM_CHARSET;
    wcscpy_s(cfmt.szFaceName, 32, appData.Afont[appData.bsize][CONSOLE_FONT]->mfp.faceName);
    /* yHeight is expressed in twips.  A twip is 1/20 of a font's point
    * size.  This was undocumented in the version of MSVC++ that I had
    * when I wrote the code, but is apparently documented now.
    */
    cfmt.yHeight = (int)(f->mfp.pointSize * 20.0 + 0.5);
    cfmt.bCharSet = f->lf.lfCharSet;
    cfmt.bPitchAndFamily = f->lf.lfPitchAndFamily;
	//GetCharFormatSelection
	//hText->GetCharFormat()
	//cfmt.bCharSet = 0;  SendMessage(TAB.hText, EM_EXGETSEL, 0, (LPARAM)&curSel);

	

	CHARFORMAT  dcfmt;
	dcfmt.dwMask = CFM_BACKCOLOR;
	dcfmt.cbSize = sizeof(CHARFORMAT);
	SendMessage(hText, EM_GETCHARFORMAT, SCF_DEFAULT, (LPARAM)&dcfmt);

    SendMessage(hText, EM_SETCHARFORMAT, SCF_ALL, (LPARAM) &cfmt); 
  //  SendMessage(hInput, EM_SETCHARFORMAT, SCF_ALL, (LPARAM) &cfmt); 
    /* Why are the following seemingly needed too? */
    SendMessage(hText, EM_SETCHARFORMAT, SCF_DEFAULT, (LPARAM) &cfmt); 
 //   SendMessage(hInput, EM_SETCHARFORMAT, SCF_DEFAULT, (LPARAM) &cfmt); 
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
 //   HWND hInput;
    TAB.consoleEcho = TRUE;
//    hInput = TAB.hInput;
    //SendMessage(hInput, EM_SETCHARFORMAT, SCF_ALL, (LPARAM)&appData.AconsoleCF);
    //SendMessage(hInput, EM_SETBKGNDCOLOR, FALSE, TAB.consoleBackgroundColor);
}

VOID
EchoOff()
{
//    CHARFORMAT cf;
//    HWND hInput;
    TAB.consoleEcho = FALSE;
//    hInput = TAB.hInput;
    /* This works OK: set text and background both to the same color */
    //cf = appData.AconsoleCF;
    //cf.crTextColor = COLOR_ECHOOFF;
    //SendMessage(hInput, EM_SETCHARFORMAT, SCF_ALL, (LPARAM)&cf);
    //SendMessage(hInput, EM_SETBKGNDCOLOR, FALSE, cf.crTextColor);
}

