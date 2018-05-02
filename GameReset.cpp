#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"


void
GameReset(dispboard_t* pDis,int redraw, BOOL isResetYq, BOOL isResetGameMode){
    //    int i;
#ifdef DEBUG_USE_DEBUG_FILE
    //if (appData.debugMode) {
        fprintf(appData.debugFP, 
			"Reset(%d, %d, %d) from gameMode %d\n",redraw, isResetYq,isResetGameMode, pDis->gameMode);
    //}
#endif

	pDis->IcsGameStartAlready      = FALSE;

    pDis->pausing					= FALSE;
    pDis->startedFromSetupPosition	= FALSE;
	pDis->firstMove					= TRUE;
    pDis->whiteFlag					= FALSE;
    pDis->blackFlag					= FALSE;
    pDis->userOfferedDraw	        = FALSE;

	//pDis->IsFenGame                 = FALSE;
	pDis->notLookBook = false;

	SendMessage(hwndToolBar,TB_ENABLEBUTTON, IDT_ToStart, 0);
	SendMessage(hwndToolBar,TB_ENABLEBUTTON, IDT_Backward, 0);

	SendMessage(hwndToolBar,TB_ENABLEBUTTON, IDT_Forward, 0);
	SendMessage(hwndToolBar,TB_ENABLEBUTTON, IDT_ToEnd, 0);

	SendMessage(hwndToolBar,TB_ENABLEBUTTON, IDT_HUIQI, 0);

	//SendMessage(hwndToolBar,TB_ENABLEBUTTON, IDT_ANALIZE, 0);

	pDis->pgn->isFenGame = FALSE;

	if (HWND_SAVE != NULL){
		SetDlgItemInt(HWND_SAVE, IDC_SAVE_PID, -1, TRUE);
		SendDlgItemMessage(HWND_SAVE, IDC_VERY_GOOD, BM_SETCHECK, 0, 0);
		SendDlgItemMessage(HWND_SAVE, IDC_LIT_GOOD, BM_SETCHECK, 0, 0);
		SendDlgItemMessage(HWND_SAVE, IDC_BALANCE, BM_SETCHECK, 0, 0);
		SendDlgItemMessage(HWND_SAVE, IDC_LIT_BAD, BM_SETCHECK, 0, 0);
		SendDlgItemMessage(HWND_SAVE, IDC_VERY_BAD, BM_SETCHECK, 0, 0);
	}

	ChessProgramState* cps = &pDis->first;

	if(cps->cps_stat == Cps_Pondering
		|| cps->cps_stat == Cps_Thinking
		|| cps->cps_stat == Cps_Analyse){
		SendToProgram(L"stop\n", cps);
		Sleep(100);
		SendToProgram(L"stop\n", cps);
		Sleep(100);
	}


    //将按钮弹出了

    SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_COM_RED, 0);
    SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_COM_BLUE,0);

    pDis->first.playWhat  = NEUTRAL;

    ClearGameInfo(pDis->pgn);

    ClearProgramStats();    
    ResetFrontEnd(pDis);
    ClearHighlights(pDis);
    pDis->flipView					= appData.flipView;
    ClearPremoveHighlights(pDis);
    pDis->gotPremove					= FALSE;
    appData.alarmSounded				= FALSE;

    GameEnds(pDis,(ChessMove) 0, NULL, GE_PLAYER);       //人手动结束的
    
	ExitAnalyzeMode();

	if(isResetGameMode){
		ChangeGameMode(pDis,BeginningOfGame);
	}


    ModeHighlight();
    InitPosition(pDis,redraw);

    ResetClocks(pDis);

    if (isResetYq){
        InitChessProgram(&pDis->first);
    }

    pDis->first.playWhat    = NEUTRAL;

	// 清空棋步列表
	SendDlgItemMessage(STEP_MAIN, IDC_LIST_STEP_MAIN, LB_RESETCONTENT, 0, 0);    //清空了哇


    //DisplayTitle(pDis, "New Game Started...");

	DisplayTitle(pDis);
	LogOut(_T("\n朋友，游戏开始了哦!\n"));

	HDCDrawChart(TAB.dlgScore, pDis, NULL, true);
}

