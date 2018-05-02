#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

void	//两个引擎是否准备好了哇
TwoMachinesEventIfReady (dispboard_t* DIS){
    //if (pDis->first.lastPing != pDis->first.lastPong) {
    //    DisplayMessage(DIS,"", "Waiting for first chess program");
    //    ScheduleDelayedEvent(DIS,TwoMachinesEventIfReady, 1000);
    //    return;
    //}
    //if (pDis->second.lastPing != pDis->second.lastPong) {
    //    DisplayMessage(DIS,"", "Waiting for second chess program");
    //    ScheduleDelayedEvent(DIS,TwoMachinesEventIfReady, 1000);
    //    return;
    //}
    //ThawUI();
    //TwoMachinesEvent();
}


void
SetWhiteToPlayEvent(dispboard_t* DIS){
    //if (pDis->gameMode == EditPosition) {
    //    //DIS.blackPlaysFirst = FALSE;
    //    DisplayBothClocks(DIS);	/* works because currentMove is 0 */
    //} 
    //else if (DIS.gameMode == IcsExamining) {
    //    //SendToICS(DIS.ics_prefix);
    //    SendToICS("tomove white\n");
    //}
}

void
SetBlackToPlayEvent(){
    //if (DIS.gameMode == EditPosition) {
    //    //DIS.blackPlaysFirst = TRUE;
    //    //DIS.currentMove = 1;	/* kludge */
    //    DisplayBothClocks();
    //    //DIS.currentMove = 0;
    //} 
    //else if (DIS.gameMode == IcsExamining) {
    //    SendToICS(DIS.ics_prefix);
    //    SendToICS("tomove black\n");
    //}
}


void        //设定CPS走那方, 不改变当前的游戏方式
SetCpsPlayWhat(ChessProgramState* now){

	dispboard_t* pDis = (dispboard_t*)now->pDis;

	now->playWhat = NEUTRAL;

	//ChessProgramState* other;


	if(pDis->gameMode == IcsPlayingWhite){
		now->playWhat    = WHITE;
	}
	else if(pDis->gameMode == IcsPlayingBlack){
		now->playWhat    = BLACK;
	}
	else {
		now->playWhat = pDis->pos->side;
	}

	//new->pl

	if(pDis->first.playWhat == NEUTRAL){
		SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_COM_RED, 0);
	}
	else{
		SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_COM_RED, 1);
	}

	//if(pDis->second.playWhat == NEUTRAL){
	//	SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_COM_BLUE, 0);
	//}
	//else{
	//	SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_COM_BLUE, 1);
	//}

	ChangeGameMode(pDis, GameNoneMode);
}

void ToolBarMachineThink(dispboard_t* pDis, BOOL isRed){


	ChessProgramState *cps;
	int idt;

	cps = &pDis->first;

	if (isRed){
		idt = IDT_COM_RED;
	}
	else{
		idt = IDT_COM_BLUE;
	}

	if (SendMessage(hwndToolBar, TB_GETSTATE, idt, 0) & TBSTATE_CHECKED){
		MachinePlayEvent(cps);
	}
	else{
		if (cps->cps_stat != Cps_Waiting){
			SendToProgram(L"stop\n", cps);
			Sleep(100);
		}
		cps->playWhat = NEUTRAL;
		ChangeGameMode(pDis, GameNoneMode);
	}
}

void MachinePlayEvent(ChessProgramState* now){

	//看一下CPS是走那一方
	SetCpsPlayWhat(now);

	//1, 得到CPS的控制参数
	//GetTimeSetInfoFromCps(now);

	//2, 发送初始参数到CPS
	SendControlParameterToCps(now);

	//3, 看能不能走一步
	dispboard_t* pDis = (dispboard_t*)now->pDis;

	if(now->playWhat == pDis->pos->side){
		SendProgramGo(now,Cps_Thinking,NULL);
	}

}



void      //双引擎对战事件
TwoMachinesEvent (void){
    //int i;
    //char buf[MSG_SIZ];
    //ChessProgramState *onmove;

    //if (appData.noChessProgram){
    //    return;
    //}

    //switch (DIS.gameMode) {
    //  case TwoMachinesPlay:
    //      return;
    //  case MachinePlaysWhite:
    //  case MachinePlaysBlack:
    //      if (WhiteOnMove(DIS.forwardMostMove) == (DIS.gameMode == MachinePlaysWhite)) {
    //          DisplayError("Wait until your turn,\nor select Move Now", 0);
    //          return;
    //      }
    //      /* fall through */
    //  case BeginningOfGame:
    //  case PlayFromGameFile:
    //  case EndOfGame:
    //      EditGameEvent();
    //      if (DIS.gameMode != EditGame){
    //          return;
    //      }
    //      break;
    //  case EditPosition:
    //      EditPositionDone();
    //      break;
    //  case AnalyzeMode:
    //  case AnalyzeFile:
    //      ExitAnalyzeMode();
    //      break;
    //  case EditGame:
    //  default:
    //      break;
    //}

    //DIS.forwardMostMove = DIS.currentMove;
    //ResurrectChessProgram();	/* 如果第一个程序还没有开始的话 in case first program isn't running */

    //if (DIS.second.pr == NULL) {
    //    StartChessProgram(&DIS.second);
    //    //if (DIS.second.protocolVersion == 1) {
    //    //	TwoMachinesEventIfReady();
    //    //} 
    //    //else {
    //    /* kludge: allow timeout for initial "feature" command */
    //    FreezeUI();
    //    DisplayMessage("", "Starting second chess program");
    //    ScheduleDelayedEvent(TwoMachinesEventIfReady, FEATURE_TIMEOUT);
    //    //}
    //    return;
    //}
    //DisplayMessage("", "");
    //InitChessProgram(&DIS.second);

    //switch(DIS.second.ucci){
    //    case UCCI_UCCI:
    //        break;
    //    case UCCI_QH:
    //        //SendToProgram("AI\n", &DIS.second);
    //        break;
    //    case UCCI_DIS:
    //        break;
    //    default:
    //        SendToProgram("force\n", &DIS.second);
    //        break;
    //}


    //if (DIS.startedFromSetupPosition) {
    //    SendBoard(&DIS.second, DIS.backwardMostMove);
    //}
    //for (i = DIS.backwardMostMove; i < DIS.forwardMostMove; i++) {
    //    SendMoveToProgram(i, &DIS.second);
    //}

    //DIS.gameMode = TwoMachinesPlay;
    //DIS.pausing = FALSE;
    //ModeHighlight();
    //SetGameInfo();
    //DisplayTwoMachinesTitle();
    //DIS.firstMove = TRUE;
    //if ((DIS.first.twoMachinesColor[0] == 'w') == WhiteOnMove(DIS.forwardMostMove)) {
    //    onmove = &DIS.first;
    //} 
    //else {
    //    onmove = &DIS.second;
    //}

    ////SendToProgram(DIS.first.computerString, &DIS.first);

    //if (DIS.first.sendName) {
    //    //sprintf(buf, "name %s\n", DIS.second.tidy);
    //    StringCbPrintf(buf,MSG_SIZ,"name %s\n", DIS.second.tidy);
    //    SendToProgram(buf, &DIS.first);
    //}

    ////SendToProgram(DIS.second.computerString, &DIS.second);

    //if (DIS.second.sendName) {
    //    //sprintf(buf, "name %s\n", DIS.first.tidy);
    //    StringCbPrintf(buf,MSG_SIZ,"name %s\n", DIS.first.tidy);
    //    SendToProgram(buf, &DIS.second);
    //}

    //if (!DIS.first.sendTime || !DIS.second.sendTime) {
    //    ResetClocks();
    //    DIS.timeRemaining[0][DIS.forwardMostMove] = DIS.whiteTimeRemaining;
    //    DIS.timeRemaining[1][DIS.forwardMostMove] = DIS.blackTimeRemaining;
    //}

    //if (onmove->sendTime) {
    //    if (onmove->useColors) {
    //        SendToProgram(onmove->other->twoMachinesColor, onmove); /*gnu kludge*/
    //    }
    //    SendTimeRemaining(onmove, WhiteOnMove(DIS.forwardMostMove));
    //}

    //if (onmove->useColors) {
    //    SendToProgram(onmove->twoMachinesColor, onmove);
    //}

    ///*SendToProgram("go\n", onmove);*/

    //switch(onmove->ucci){
    //    case UCCI_UCCI:
    //        //SendMoveToProgram("");
    //        StringCbPrintf(buf,MSG_SIZ,"go depth %d\n",onmove->searchDepth);			
    //        SendToProgram(buf, onmove);
    //        break;
    //    case UCCI_QH:
    //        SendToProgram("AI\n", onmove);
    //        break;
    //    case UCCI_DIS:
    //        break;
    //    default:
    //        SendToProgram("go\n", onmove);
    //        break;
    //}

    //onmove->maybeThinking = TRUE;
    //SetMachineThinkingEnables();

    //StartClocks();
}
