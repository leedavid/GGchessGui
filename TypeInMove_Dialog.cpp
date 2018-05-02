#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

/*---------------------------------------------------------------------------*\
 *
 * Type-in move dialog functions
 * 
\*---------------------------------------------------------------------------*/

LRESULT CALLBACK
TypeInMoveDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
  //char move[MSG_SIZ];
  //HWND hInput;
  ////ChessMove moveType;
  ////int fromX, fromY, toX, toY;
  ////char promoChar;

  //switch (message) {
  //case WM_INITDIALOG:
  //  move[0] = (char) lParam;
  //  move[1] = NULLCHAR;
  //  CenterWindow(hDlg, GetWindow(hDlg, GW_OWNER));
  //  hInput = GetDlgItem(hDlg, OPT_Move);
  //  SetWindowText(hInput, move);
  //  SetFocus(hInput);
  //  SendMessage(hInput, EM_SETSEL, (WPARAM)9999, (LPARAM)9999);
  //  return FALSE;

  //case WM_COMMAND:
  //    switch (LOWORD(wParam)) {
  //case IDOK:
  //    //if (DIS.gameMode != EditGame && DIS.currentMove != DIS.forwardMostMove && 
  //    //    DIS.gameMode != Training) {
  //    if (DIS.gameMode != EditGame && DIS.pos.curStep != DIS.pos.gply && 
  //        DIS.gameMode != Training) {
  //            DisplayMoveError("Displayed move is not current");
  //    } 
  //    else {
  //        GetDlgItemText(hDlg, OPT_Move, move, sizeof(move));
  //        //if (ParseOneMove(move, DIS.gameMode == EditPosition ? DIS.blackPlaysFirst : DIS.currentMove, 
  //        //    &moveType, &fromX, &fromY, &toX, &toY,DIS.ucci)) {
  //        //        if (DIS.gameMode != Training)
  //        //            DIS.forwardMostMove = DIS.currentMove;
  //        //        UserMoveEvent(fromX, fromY, toX, toY, DIS.ucci);	
  //        //} 
  //        //else {
  //        //    DisplayMoveError("Could not parse move");
  //        //}
  //        DisplayMoveError("Could not parse move");
  //    }
  //    EndDialog(hDlg, TRUE);
  //    return TRUE;
  //case IDCANCEL:
  //    EndDialog(hDlg, FALSE);
  //    return TRUE;
  //default:
  //    break;
  //    }
  //    break;
  //}
  return FALSE;
}

VOID
PopUpMoveDialog(char firstchar)
{
    //FARPROC lpProc;

    //if ((DIS.gameMode == BeginningOfGame && !appData.icsActive) || 
    //    DIS.gameMode == MachinePlaysWhite || DIS.gameMode == MachinePlaysBlack ||
    //    DIS.gameMode == AnalyzeMode || DIS.gameMode == EditGame || 
    //    DIS.gameMode == EditPosition || DIS.gameMode == IcsExamining ||
    //    DIS.gameMode == IcsPlayingWhite || DIS.gameMode == IcsPlayingBlack ||
    //    DIS.gameMode == Training) {
    //        lpProc = MakeProcInstance((FARPROC)TypeInMoveDialog, hInst);
    //        DialogBoxParam(hInst, MAKEINTRESOURCE(DLG_TypeInMove),
    //            hwndMain, (DLGPROC)lpProc, (LPARAM)firstchar);
    //        FreeProcInstance(lpProc);
    //}
}










