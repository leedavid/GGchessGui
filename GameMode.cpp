#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

void
SetGNUMode(){
  //SetMenuEnables(GetMenu(pDis->DIS.hwndThis), gnuEnables);
}

void
SetNCPMode(){
    //HMENU hmenu = GetMenu(hwndMain);
    //SetMenuEnables(hmenu, ncpEnables);
    //EnableMenuItem(GetSubMenu(hmenu, OPTIONS_POS), SOUNDS_POS, MF_BYPOSITION|MF_GRAYED);
    //DrawMenuBar(hwndMain);
}

void
SetCmailMode()
{
  //SetMenuEnables(GetMenu(hwndMain), cmailEnables);
}
void
SetICSMode()
{
  //HMENU hmenu = GetMenu(hwndMain);
  //SetMenuEnables(hmenu, icsEnables);
  //EnableMenuItem(GetSubMenu(hmenu, OPTIONS_POS), ICS_POS,
  //  MF_BYPOSITION|MF_ENABLED);
#ifdef ZIPPY
  if (appData.zippyPlay) {
    SetMenuEnables(hmenu, zippyEnables);
  }
#endif
}
void
SetMachineThinkingEnables(dispboard_t* DIS) {       //使引擎开始运算棋步
  //HMENU hMenu = GetMenu(hwndMain);
  //int flags = MF_BYCOMMAND|MF_ENABLED;

  //SetMenuEnables(hMenu, machineThinkingEnables);

  //if (DIS.gameMode == MachinePlaysBlack) {
  //  (void)EnableMenuItem(hMenu, IDM_MachineBlack, flags);
  //} 
  //else if (DIS.gameMode == MachinePlaysWhite) {
  //  (void)EnableMenuItem(hMenu, IDM_MachineWhite, flags);
  //} 
  //else if (DIS.gameMode == TwoMachinesPlay) {
  //  (void)EnableMenuItem(hMenu, IDM_TwoMachines, flags);
  //}
}

void
SetTrainingModeOff(){
  //int i;
  //SetMenuEnables(GetMenu(hwndMain), trainingOffEnables);
  //for (i = 0; i < N_BUTTONS; i++) {
  //  if (DIS.buttonDesc[i].hwnd != NULL)
  //    EnableWindow(DIS.buttonDesc[i].hwnd, TRUE);
  //}
}
void
SetUserThinkingEnables(){
  //SetMenuEnables(GetMenu(hwndMain), userThinkingEnables);
}
//LRESULT CALLBACK
//CommentDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){
//	static HANDLE hwndText = NULL;
//	int len, newSizeX, newSizeY, flags;
//	static int sizeX, sizeY;
//	char *str;
//	RECT rect;
//	MINMAXINFO *mmi;
//
//	switch (message) {
//  case WM_INITDIALOG: /* message: initialize dialog box */
//	  /* Initialize the dialog items */
//	  hwndText = GetDlgItem(hDlg, OPT_CommentText);
//	  SetDlgItemText(hDlg, OPT_CommentText, DIS.commentText);
//	  EnableWindow(GetDlgItem(hDlg, OPT_CancelComment), DIS.editComment);
//	  EnableWindow(GetDlgItem(hDlg, OPT_ClearComment), DIS.editComment);
//	  EnableWindow(GetDlgItem(hDlg, OPT_EditComment), !DIS.editComment);
//	  SendMessage((HWND)hwndText, EM_SETREADONLY, !DIS.editComment, 0);
//	  SetWindowText(hDlg, DIS.commentTitle);
//	  if (DIS.editComment) {
//		  SetFocus((HWND)hwndText);
//	  } else {
//		  SetFocus(GetDlgItem(hDlg, IDOK));
//	  }
//	  SendMessage(GetDlgItem(hDlg, OPT_CommentText),
//		  WM_SETFONT, (WPARAM)DIS.font[DIS.bsize][COMMENT_FONT]->hf, 
//		  MAKELPARAM(FALSE, 0));
//	  /* Size and position the dialog */
//	  if (!DIS.commentDialog) {
//		  DIS.commentDialog = hDlg;
//		  flags = SWP_NOZORDER;
//		  GetClientRect(hDlg, &rect);
//		  sizeX = rect.right;
//		  sizeY = rect.bottom;
//		  if (DIS.commentX != CW_USEDEFAULT && DIS.commentY != CW_USEDEFAULT &&
//			  DIS.commentW != CW_USEDEFAULT && DIS.commentH != CW_USEDEFAULT) {
//				  WINDOWPLACEMENT wp;
//				  EnsureOnScreen(&DIS.commentX, &DIS.commentY);
//				  wp.length = sizeof(WINDOWPLACEMENT);
//				  wp.flags = 0;
//				  wp.showCmd = SW_SHOW;
//				  wp.ptMaxPosition.x = wp.ptMaxPosition.y = 0;
//				  wp.rcNormalPosition.left = DIS.commentX;
//				  wp.rcNormalPosition.right = DIS.commentX + DIS.commentW;
//				  wp.rcNormalPosition.top = DIS.commentY;
//				  wp.rcNormalPosition.bottom = DIS.commentY + DIS.commentH;
//				  SetWindowPlacement(hDlg, &wp);
//
//				  GetClientRect(hDlg, &rect);
//				  newSizeX = rect.right;
//				  newSizeY = rect.bottom;
//				  ResizeEditPlusButtons(hDlg, (HWND)hwndText, sizeX, sizeY,
//					  newSizeX, newSizeY);
//				  sizeX = newSizeX;
//				  sizeY = newSizeY;
//			  }
//	  }
//	  return FALSE;
//
//  case WM_COMMAND: /* message: received a command */
//	  switch (LOWORD(wParam)) {
//  case IDOK:
//	  if (DIS.editComment) {
//		  char *p, *q;
//		  /* Read changed options from the dialog box */
//		  hwndText = GetDlgItem(hDlg, OPT_CommentText);
//		  len = GetWindowTextLength((HWND)hwndText);
//		  str = (char *) malloc(len + 1);
//		  GetWindowText((HWND)hwndText, str, len + 1);
//		  p = q = str;
//		  while (*q) {
//			  if (*q == '\r')
//				  q++;
//			  else
//				  *p++ = *q++;
//		  }
//		  *p = NULLCHAR;
//		  ReplaceComment(DIS.commentIndex, str);
//		  free(str);
//	  }
//	  CommentPopDown();
//	  return TRUE;
//
//  case IDCANCEL:
//  case OPT_CancelComment:
//	  CommentPopDown();
//	  return TRUE;
//
//  case OPT_ClearComment:
//	  SetDlgItemText(hDlg, OPT_CommentText, "");
//	  break;
//
//  case OPT_EditComment:
//	  EditCommentEvent();
//	  return TRUE;
//
//  default:
//	  break;
//	  }
//	  break;
//
//  case WM_SIZE:
//	  newSizeX = LOWORD(lParam);
//	  newSizeY = HIWORD(lParam);
//	  ResizeEditPlusButtons(hDlg, (HWND)hwndText, sizeX, sizeY, newSizeX, newSizeY);
//	  sizeX = newSizeX;
//	  sizeY = newSizeY;
//	  break;
//
//  case WM_GETMINMAXINFO:
//	  /* Prevent resizing window too small */
//	  mmi = (MINMAXINFO *) lParam;
//	  mmi->ptMinTrackSize.x = 100;
//	  mmi->ptMinTrackSize.y = 100;
//	  break;
//	}
//	return FALSE;
//}
//VOID
//EitherCommentPopUp(int index, char *title, char *str, BOOLEAN edit){
//	FARPROC lpProc;
//	char *p, *q;
//
//	CheckMenuItem(GetMenu(hwndMain), IDM_EditComment, edit ? MF_CHECKED : MF_UNCHECKED);
//
//	if (str == NULL) str = "";
//	p = (char *) malloc(2 * strlen(str) + 2);
//	q = p;
//	while (*str) {
//		if (*str == '\n') *q++ = '\r';
//		*q++ = *str++;
//	}
//	*q = NULLCHAR;
//	if (DIS.commentText != NULL) free(DIS.commentText);
//
//	DIS.commentIndex = index;
//	DIS.commentTitle = title;
//	DIS.commentText = p;
//	DIS.editComment = edit;
//
//	if (DIS.commentDialog) {
//		SendMessage(DIS.commentDialog, WM_INITDIALOG, 0, 0);
//		if (!DIS.commentDialogUp) ShowWindow(DIS.commentDialog, SW_SHOW);
//	} else {
//		lpProc = MakeProcInstance((FARPROC)CommentDialog, hInst);
//		CreateDialog(hInst, MAKEINTRESOURCE(DLG_EditComment),
//			hwndMain, (DLGPROC)lpProc);
//		FreeProcInstance(lpProc);
//	}
//	DIS.commentDialogUp = TRUE;
//}
//
//VOID
//CommentPopUp(char *title, char *str){
//	HWND hwnd = GetActiveWindow();
//	EitherCommentPopUp(0, title, str, FALSE);
//	SetActiveWindow(hwnd);
//}
//VOID
//CommentPopDown(void){
//	CheckMenuItem(GetMenu(hwndMain), IDM_EditComment, MF_UNCHECKED);
//	if (DIS.commentDialog) {
//		ShowWindow(DIS.commentDialog, SW_HIDE);
//	}
//	DIS.commentDialogUp = FALSE;
//}
void
SetTrainingModeOn(void){
	//int i;
	//SetMenuEnables(GetMenu(hwndMain), trainingOnEnables);
	//for (i = 0; i < N_BUTTONS; i++) {
	//	if (buttonDesc[i].hwnd != NULL)
	//		EnableWindow(buttonDesc[i].hwnd, FALSE);
	//}
	//CommentPopDown();
}