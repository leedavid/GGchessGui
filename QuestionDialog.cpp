#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

LRESULT CALLBACK
QuestionDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){
	static QuestionParams *qp;
	TCHAR reply[MSG_SIZ];
	int len, err;

	switch (message) {
  case WM_INITDIALOG:
	  qp = (QuestionParams *) lParam;
	  CenterWindow(hDlg, GetWindow(hDlg, GW_OWNER));
	  SetWindowText(hDlg, qp->title);
	  SetDlgItemText(hDlg, OPT_QuestionText, qp->question);
	  SetFocus(GetDlgItem(hDlg, OPT_QuestionInput));
	  return FALSE;

  case WM_COMMAND:
	  switch (LOWORD(wParam)) {
  case IDOK:
	  //strcpy(reply, qp->replyPrefix);
	  StringCbCopy(reply,MSG_SIZ,qp->replyPrefix);
	  if (*reply){
		  //strcat(reply, " ");
		  StringCbCat(reply,MSG_SIZ,_T(" "));
	  }
	  len = (int)wcslen(reply);
	  GetDlgItemText(hDlg, OPT_QuestionInput, reply + len, sizeof(reply) - len);
	  //strcat(reply, "\n");
	  StringCbCat(reply,MSG_SIZ,_T("\n"));
	  OutputToProcess(qp->pr, reply, (int)wcslen(reply), &err);
	  EndDialog(hDlg, TRUE);
	  if (err){
		  DisplayFatalError(L"Error writing to chess program", err, 1);
	  }
	  return TRUE;
  case IDCANCEL:
	  EndDialog(hDlg, FALSE);
	  return TRUE;
  default:
	  break;
	  }
	  break;
	}
	return FALSE;
}
void
AskQuestion(TCHAR* title, TCHAR *question, TCHAR *replyPrefix, ProcRef pr){

	dispboard_t* pDis = OBS[0];
	QuestionParams qp;
	FARPROC lpProc;

	qp.title = title;
	qp.question = question;
	qp.replyPrefix = replyPrefix;
	qp.pr = pr;
	lpProc = MakeProcInstance((FARPROC)QuestionDialog, hInst);
	DialogBoxParam(hInst, MAKEINTRESOURCE(DLG_Question),
		pDis->hwndThis, (DLGPROC)lpProc, (LPARAM)&qp);
	FreeProcInstance(lpProc);
}
