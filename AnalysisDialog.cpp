#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

VOID
AnalysisPopDown(){
	//if (DIS.analysisDialog) {
	//	ShowWindow(DIS.analysisDialog, SW_HIDE);
	//}
	//DIS.analysisDialogUp = FALSE;  
}

static int
only_one_move(char *str)
{
    while (*str && isspace(*str)) ++str;
    while (*str && !isspace(*str)) ++str;
    if (!*str) return 1;
    while (*str && isspace(*str)) ++str;
    if (!*str) return 1;
    return 0;
}

void
DisplayAnalysisText(char *text){
    //char buf[MSG_SIZ];

    //if (DIS.gameMode == AnalyzeMode || DIS.gameMode == AnalyzeFile) {
    //    //sprintf(buf, "Analysis (%s)", first.tidy);
    //    StringCbPrintf(buf,MSG_SIZ,"Analysis (%s)", DIS.first.tidy);
    //    AnalysisPopUp(buf, text);
    //}
}

void
DisplayAnalysis(){
    //char buf[MSG_SIZ];
    //double nps;
    //static char *xtra[] = { "", " (--)", " (++)" };
    //int h, m, s, cs;

    //if (DIS.programStats.time == 0) {
    //    DIS.programStats.time = 1;
    //}

    //if (DIS.programStats.got_only_move) {
    //    StringCbCopy(buf,MSG_SIZ,DIS.programStats.movelist);
    //} 
    //else {
    //    nps = (((double)DIS.programStats.nodes) / (((double)DIS.programStats.time)/100.0));

    //    cs = DIS.programStats.time % 100;
    //    s = DIS.programStats.time / 100;
    //    h = (s / (60*60));
    //    s = s - h*60*60;
    //    m = (s/60);
    //    s = s - m*60;

    //    if (DIS.programStats.moves_left > 0 && appData.periodicUpdates) {
    //        if (DIS.programStats.move_name[0] != NULLCHAR) {
    //            StringCbPrintf(buf,MSG_SIZ,"depth=%d %d/%d(%s) %+.2f %s%s\nNodes: %lu NPS: %d\nTime: %02d:%02d:%02d.%02d",
    //                //sprintf(buf, "depth=%d %d/%d(%s) %+.2f %s%s\nNodes: %lu NPS: %d\nTime: %02d:%02d:%02d.%02d",
    //                DIS.programStats.depth,
    //                DIS.programStats.nr_moves - DIS.programStats.moves_left,
    //                DIS.programStats.nr_moves, DIS.programStats.move_name,
    //                ((float)DIS.programStats.score)/100.0, DIS.programStats.movelist,
    //                only_one_move(DIS.programStats.movelist)?
    //                xtra[DIS.programStats.got_fail] : "",
    //                DIS.programStats.nodes, (int)nps, h, m, s, cs);
    //        } 
    //        else {
    //            StringCbPrintf(buf,MSG_SIZ,"depth=%d %d/%d %+.2f %s%s\nNodes: %lu NPS: %d\nTime: %02d:%02d:%02d.%02d",
    //                //sprintf(buf, "depth=%d %d/%d %+.2f %s%s\nNodes: %lu NPS: %d\nTime: %02d:%02d:%02d.%02d",
    //                DIS.programStats.depth,
    //                DIS.programStats.nr_moves - DIS.programStats.moves_left,
    //                DIS.programStats.nr_moves, ((float)DIS.programStats.score)/100.0,
    //                DIS.programStats.movelist,
    //                only_one_move(DIS.programStats.movelist)?
    //                xtra[DIS.programStats.got_fail] : "",
    //                DIS.programStats.nodes, (int)nps, h, m, s, cs);
    //        }
    //    } 
    //    else {
    //        StringCbPrintf(buf,MSG_SIZ,"depth=%d %+.2f %s%s\nNodes: %lu NPS: %d\nTime: %02d:%02d:%02d.%02d",
    //            //sprintf(buf, "depth=%d %+.2f %s%s\nNodes: %lu NPS: %d\nTime: %02d:%02d:%02d.%02d",
    //            DIS.programStats.depth,
    //            ((float)DIS.programStats.score)/100.0,
    //            DIS.programStats.movelist,
    //            only_one_move(DIS.programStats.movelist)?
    //            xtra[DIS.programStats.got_fail] : "",
    //            DIS.programStats.nodes, (int)nps, h, m, s, cs);
    //    }
    //}
    //DisplayAnalysisText(buf);
}




LRESULT CALLBACK
AnalysisDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	return FALSE;
}
void
AnalysisPopUp(char* title, char* str){
	//FARPROC lpProc;
	//char *p, *q;

	//if (str == NULL) str = "";
	//p = (char *) malloc(2 * strlen(str) + 2);
	//q = p;
	//while (*str) {
	//	if (*str == '\n') *q++ = '\r';
	//	*q++ = *str++;
	//}
	//*q = NULLCHAR;
	//if (DIS.analysisText != NULL) free(DIS.analysisText);
	//DIS.analysisText = p;

	//if (DIS.analysisDialog) {
	//	SetWindowText(DIS.analysisDialog, title);
	//	SetDlgItemText(DIS.analysisDialog, OPT_AnalysisText, DIS.analysisText);
	//	ShowWindow(DIS.analysisDialog, SW_SHOW);
	//} else {
	//	DIS.analysisTitle = title;
	//	lpProc = MakeProcInstance((FARPROC)AnalysisDialog, hInst);
	//	CreateDialog(hInst, MAKEINTRESOURCE(DLG_Analysis),
	//		hwndMain, (DLGPROC)lpProc);
	//	FreeProcInstance(lpProc);
	//}
	//DIS.analysisDialogUp = TRUE;  
}

BOOL CALLBACK
ResizeEditPlusButtonsCallback(HWND hChild, LPARAM lparam){
	ResizeEditPlusButtonsClosure *cl = (ResizeEditPlusButtonsClosure *)lparam;
	RECT rect;
	POINT pt;

	if (hChild == cl->hText) return TRUE;
	GetWindowRect(hChild, &rect); /* gives screen coords */
	pt.x = rect.left + (cl->newSizeX - cl->sizeX)/2;
	pt.y = rect.top + cl->newSizeY - cl->sizeY;
	ScreenToClient(cl->hDlg, &pt);
	cl->hdwp = DeferWindowPos(cl->hdwp, hChild, NULL, 
		pt.x, pt.y, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER);
	return TRUE;
}
/* Resize a dialog that has a (rich) edit field filling most of
the top, with a row of buttons below */ //1
void
ResizeEditPlusButtons(HWND hDlg, HWND hText, int sizeX, int sizeY, int newSizeX, int newSizeY){
	RECT rectText;
	int newTextHeight, newTextWidth;
	ResizeEditPlusButtonsClosure cl;

	/*if (IsIconic(hDlg)) return;*/
	if (newSizeX == sizeX && newSizeY == sizeY) return;

	cl.hdwp = BeginDeferWindowPos(8);

	GetWindowRect(hText, &rectText); /* gives screen coords */
	newTextWidth = rectText.right - rectText.left + newSizeX - sizeX;
	newTextHeight = rectText.bottom - rectText.top + newSizeY - sizeY;
	if (newTextHeight < 0) {
		newSizeY += -newTextHeight;
		newTextHeight = 0;
	}
	cl.hdwp = DeferWindowPos(cl.hdwp, hText, NULL, 0, 0, 
		newTextWidth, newTextHeight, SWP_NOZORDER|SWP_NOMOVE);

	cl.hDlg = hDlg;
	cl.hText = hText;
	cl.sizeX = sizeX;
	cl.sizeY = sizeY;
	cl.newSizeX = newSizeX;
	cl.newSizeY = newSizeY;
	EnumChildWindows(hDlg, ResizeEditPlusButtonsCallback, (LPARAM)&cl);

	EndDeferWindowPos(cl.hdwp);
}



//LRESULT CALLBACK         //
//ButtonProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
 // int id = GetWindowLong(hwnd, GWL_ID);
 // int i, dir;

 // for (i=0; i<N_BUTTONS; i++) {
 //   if (DIS.buttonDesc[i].id == id) break;
 // }
 // if (i == N_BUTTONS) return 0;
 // switch (message) {
 // case WM_KEYDOWN:
 //   switch (wParam) {
 //   case VK_LEFT:
 //   case VK_RIGHT:
 //     dir = (wParam == VK_LEFT) ? -1 : 1;
 //     SetFocus(DIS.buttonDesc[(i + dir + N_BUTTONS) % N_BUTTONS].hwnd);
 //     return TRUE;
 //   }
 //   break;
 // case WM_CHAR:
 //   switch (wParam) {
 //   case '\r':
 //     SendMessage(hwndMain, WM_COMMAND, MAKEWPARAM(DIS.buttonDesc[i].id, 0), 0);
 //     return TRUE;
 //   case '\t':
 //     if (appData.icsActive) {
	//if (GetKeyState(VK_SHIFT) < 0) {
	//  /* shifted */
	//  HWND h = GetDlgItem(HWND_CONSOLE, OPT_ConsoleInput);
	//  if (IsIconic(HWND_CONSOLE)) ShowWindow(HWND_CONSOLE, SW_RESTORE);
	//  SetFocus(h);
	//} else {
	//  /* unshifted */
	//  HWND h = GetDlgItem(HWND_CONSOLE, OPT_ConsoleText);
	//  if (IsIconic(HWND_CONSOLE)) ShowWindow(HWND_CONSOLE, SW_RESTORE);
	//  SetFocus(h);
	//}
	//return TRUE;
 //     }
 //     break;
 //   default:
 //     if (appData.icsActive) {
 //       HWND h = GetDlgItem(HWND_CONSOLE, OPT_ConsoleInput);
	//if (IsIconic(HWND_CONSOLE)) ShowWindow(HWND_CONSOLE, SW_RESTORE);
	//SetFocus(h);
	//SendMessage(h, WM_CHAR, wParam, lParam);
	//return TRUE;
 //     } else if (isalpha((char)wParam) || isdigit((char)wParam)){
	//PopUpMoveDialog((char)wParam);
 //     }
 //     break;
 //   }
 //   break;
 // }
//  return CallWindowProc(DIS.buttonDesc[i].wndproc, hwnd, message, wParam, lParam);
//}



