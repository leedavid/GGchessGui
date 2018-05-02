#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

/* Nonmodal error box */
LRESULT CALLBACK ErrorDialog(HWND hDlg, UINT message,
			     WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK
ErrorDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
  //HANDLE hwndText;
  //RECT rChild;

  //switch (message) {
  //case WM_INITDIALOG:
  //  GetWindowRect(hDlg, &rChild);
  //  SetWindowPos(hDlg, NULL, rChild.left,
  //    rChild.top + DIS.boardRect.top - (rChild.bottom - rChild.top), 
  //    0, 0, SWP_NOZORDER|SWP_NOSIZE);
  //  DIS.errorDialog = hDlg;
  //  SetWindowText(hDlg, DIS.errorTitle);
  //  hwndText = GetDlgItem(hDlg, OPT_ErrorText);
  //  SetDlgItemText(hDlg, OPT_ErrorText, DIS.errorMessage);
  //  return FALSE;

  //case WM_COMMAND:
  //  switch (LOWORD(wParam)) {
  //  case IDOK:
  //  case IDCANCEL:
  //    if (DIS.errorDialog == hDlg) DIS.errorDialog = NULL;
  //    DestroyWindow(hDlg);
  //    return TRUE;

  //  default:
  //    break;
  //  }
  //  break;
  //}
  return FALSE;
}

//void
//ErrorPopUp(char *title, TCHAR *content){
	//FARPROC lpProc;
	//char *p, *q;
	//BOOLEAN modal = hwndMain == NULL;

	//p = content;
	//q = DIS.errorMessage;
	//while (*p) {
	//	if (*p == '\n') {
	//		if (modal) {
	//			*q++ = ' ';
	//			p++;
	//		} else {
	//			*q++ = '\r';
	//			*q++ = *p++;
	//		}
	//	} else {
	//		*q++ = *p++;
	//	}
	//}
 // *q = NULLCHAR;
 // //strncpy(DIS.errorTitle, title, sizeof(DIS.errorTitle));
 // strncpy_s(DIS.errorTitle,MSG_SIZ, title, sizeof(DIS.errorTitle));

 // DIS.errorTitle[sizeof(DIS.errorTitle) - 1] = '\0';
 // 
 // if (modal) {
 //   MessageBox(NULL, DIS.errorMessage, DIS.errorTitle, MB_OK|MB_ICONEXCLAMATION);
 // } 
 // else {
 //   lpProc = MakeProcInstance((FARPROC)ErrorDialog, hInst);
 //   CreateDialog(hInst, MAKEINTRESOURCE(DLG_Error),
	//	 hwndMain, (DLGPROC)lpProc);
 //   FreeProcInstance(lpProc);
 // }
//}





//void
//ErrorPopDown()
//{
//	//if (!appData.popupMoveErrors && DIS.moveErrorMessageUp){
//	//	DisplayMessage("", "");                //当前有错误信息哇
//	//}
//	//if (DIS.errorDialog == NULL){
//	//	return;
//	//}
//	//DestroyWindow(DIS.errorDialog);
//	//DIS.errorDialog = NULL;
//}

