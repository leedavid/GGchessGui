#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

void	//重新开始一局棋局哇
ResetGameEvent(dispboard_t* pDis){
    if (pDis->gameMode == Training){
        SetTrainingModeOff();
    }

    GameReset(pDis, TRUE, TRUE, TRUE);

	FillBookbyPos(pDis,MST->book);

}



void MakePosMoveOnly(position_t *pos, int m){
    int from    = FROM(m);
    int to      = TO(m);
    int piece   = PIECE(m);
    int capture = CAPTURE(m);


	//if (piece == 0){
	//	int i = 0;
	//}
    ASSERT(piece != 0);

	if(piece == 0){
		int k = 0;
	}

    //pos->gply ++;

    pos->curStep ++;

    Record* re = &pos->His[pos->curStep];
    
    re->move    = m;
    re->nonCap  = (re-1)->nonCap;
    re->ischeck = move_is_check(pos,m);		//
    re->key     = (re-1)->key;

    if(capture){
        re->key     ^= ZOBRIST(capture,to);
        re->nonCap   = 0;
        
        RemovePiece(pos,to);
    }
    else{
        pos->wBitRanks[StoY(to)] ^= xBitMask(to);
        pos->wBitFiles[StoX(to)] ^= yBitMask(to);

        re->nonCap ++;
    }

    //from FR
    pos->wBitRanks[StoY(from)]  ^= xBitMask(from);
    pos->wBitFiles[StoX(from)]  ^= yBitMask(from);
    
 
    MovePiece(pos,from,to);

    //board
    pos->b256[to]      = piece;
    pos->b256[from]    = EMPTY;

    re->key ^= ZOBRIST(piece,to) ^ ZOBRIST(piece,from);
    re->key ^= ZobColour;       //就不要分开了

    pos->side ^= 1;


}




void UnMakePosMoveOnly(position_t *pos){
    //ASSERT(pos->gply > 0);

    int m = pos->His[pos->curStep].move;

    //pos->gply --;

    pos->curStep --;

    int from    = FROM(m);
    int to      = TO(m);
    int piece   = PIECE(m);    
    int capture = CAPTURE(m);

    //FR
    pos->wBitRanks[StoY(from)] ^= xBitMask(from);
    pos->wBitFiles[StoX(from)] ^= yBitMask(from);

    //P256
    pos->b256[from] = piece;
    pos->b256[to]   = capture;

    MovePiece(pos,to,from);

    //
    pos->side ^= 0x1;

    if(capture){
        //pos->pMat += MatAddress[capture];
        InsertPiece(pos,capture,to);
    }
    else{
        pos->wBitRanks[StoY(to)] ^= xBitMask(to);
        pos->wBitFiles[StoX(to)] ^= yBitMask(to);
    }

    //debug
    //ASSERT(position_is_ok(pos));



}


void
EditPositionMenuEvent(int selection,int x,int y){
    //char buf[MSG_SIZ];

    //if (DIS.gameMode != EditPosition && DIS.gameMode != IcsExamining){
    //    return;
    //}

    //switch (selection) {
    //  case ClearBoard:
    //      if (DIS.gameMode == IcsExamining && DIS.ics_type == ICS_FICS) {
    //          SendToICS(DIS.ics_prefix);
    //          SendToICS("bsetup clear\n");
    //      } 
    //      else if (DIS.gameMode == IcsExamining && DIS.ics_type == ICS_ICC) {
    //          SendToICS(DIS.ics_prefix);
    //          SendToICS("clearboard\n");
    //      } 
    //      else {
    //          /* for (x = 0; x < BOARD_SIZE; x++) {
    //          for (y = 0; y < BOARD_SIZE; y++) {
    //          if (gameMode == IcsExamining) {
    //          if (boards[currentMove][y][x] != EmptySquare) {
    //          sprintf(buf, "%sx@%c%c\n", ics_prefix,
    //          'a' + x, '1' + y);
    //          SendToICS(buf);
    //          }
    //          } else {
    //          boards[0][y][x] = EmptySquare;
    //          }
    //          }
    //          }*/
    //          for(int i=0; i<90; i++){
    //              if(DIS.gameMode == IcsExamining) {
    //                  if (DIS.boards[DIS.currentMove][i] != NOCHESS) {
    //                      /*sprintf(buf, "%sx@%c%c\n", ics_prefix,
    //                      'a' + x, '1' + y);*/
    //                      StringCbPrintf(buf,MSG_SIZ,"%sx@%c%c\n", DIS.ics_prefix, 'a' + x, '1' + y);
    //                      SendToICS(buf);
    //                  }
    //              }
    //              else{
    //                  DIS.boards[0][i] = NOCHESS;
    //              }
    //          }
    //      }
    //      if (DIS.gameMode == EditPosition) {
    //          DrawPosition(false, DIS.boards[0]);
    //      }
    //      break;

    //  case WhitePlay:
    //      SetWhiteToPlayEvent();
    //      break;

    //  case BlackPlay:
    //      SetBlackToPlayEvent();
    //      break;

    //  case NOCHESS:
    //      if (DIS.gameMode == IcsExamining) {
    //          //sprintf(buf, "%sx@%c%c\n", DIS.ics_prefix, 'a' + x, '1' + y);
    //          StringCbPrintf(buf,MSG_SIZ, "%sx@%c%c\n", DIS.ics_prefix, 'a' + x, '1' + y);
    //          SendToICS(buf);
    //      } 
    //      else {
    //          //boards[0][y][x] = EmptySquare;
    //          DIS.boards[0][FRto90(x,y)] = NOCHESS;
    //          DrawPosition(false, DIS.boards[0]);
    //      }
    //      break;

    //  default:
    //      if (DIS.gameMode == IcsExamining) {
    //          /*sprintf(buf, "%s%c@%c%c\n", DIS.ics_prefix,
    //          PieceToChar(selection), 'a' + x, '1' + y);*/
    //          StringCbPrintf(buf,MSG_SIZ,"%s%c@%c%c\n", DIS.ics_prefix,
    //              PieceToCharUCCI(selection,DIS.ucci), 'a' + x, '1' + y);
    //          SendToICS(buf);
    //      } 
    //      else {
    //          //boards[0][y][x] = selection;
    //          DIS.boards[0][FRto90(x,y)] = selection;
    //          DrawPosition(false, DIS.boards[0]);
    //      }
    //      break;
    //}
}


void
DropMenuEvent(sq_t selection,int x,int y){
    //ChessMove moveType;

    //switch (DIS.gameMode) {
    //  case IcsPlayingWhite:
    //  case MachinePlaysBlack:
    //      if (!WhiteOnMove(DIS.currentMove)) {
    //          DisplayMoveError("It is Black's turn");
    //          return;
    //      }
    //      moveType = WhiteDrop;
    //      break;
    //  case IcsPlayingBlack:
    //  case MachinePlaysWhite:
    //      if (WhiteOnMove(DIS.currentMove)) {
    //          DisplayMoveError("It is White's turn");
    //          return;
    //      }
    //      moveType = BlackDrop;
    //      break;
    //  case EditGame:
    //      moveType = WhiteOnMove(DIS.currentMove) ? WhiteDrop : BlackDrop;
    //      break;
    //  default:
    //      return;
    //}

    ////if (moveType == BlackDrop && selection < BlackPawn) {
    ////	selection = (ChessSquare) ((int) selection
    ////		+ (int) BlackPawn - (int) WhitePawn);
    ////}

    //if (DIS.boards[DIS.currentMove][FRto90(x,y)] != NOCHESS) {
    //    DisplayMoveError("That square is occupied");
    //    return;
    //}

    //FinishMove(moveType, (int) selection, DROP_RANK, x, y);
}


void
ForwardInner(dispboard_t* pDis, int target){
    int limit;

#ifdef DEBUG_MODE
    //if (appData.debugMode){
        //fprintf(DIS.debugFP, "ForwardInner(%d), current %d, forward %d\n",
        //target, DIS.currentMove, DIS.forwardMostMove);
    //}
#endif

    if (pDis->gameMode == EditPosition)
        return;

    if (pDis->gameMode == PlayFromGameFile && !pDis->pausing)
        PauseEvent();

    if (pDis->gameMode == IcsExamining && pDis->pausing)
        limit = pDis->pauseExamForwardMostMove;
    else{
        //limit = DIS.forwardMostMove;
        limit = pDis->pos->gply;
    }

    if (target > limit) target = limit;
  
    int  tg_move = pDis->pos->His[target].move;

    if(tg_move > 0){
        int fromX, fromY,toX,toY;

        int from = FROM(tg_move);
        int to   = TO(tg_move);

        fromX    = StoX(from) - 3;
        fromY    = StoY(from) - 3;

        toX      = StoX(to) - 3;
        toY      = StoY(to) - 3;

        /*if(target == DIS.currentMove + 1){*/
        if(target == pDis->pos->curStep + 1){
           /* AnimateMove(DIS.pos.B256dis[DIS.currentMove],toX,toY,fromX,fromY);*/
             AnimateMove(pDis,pDis->B256dis[pDis->pos->curStep],toX,toY,fromX,fromY);
        }
        if(appData.highlightLastMove){
            SetHighlights(pDis,fromX, fromY, toX, toY);
        }
    }

    //*********************//得返回原来的Pos 
    /*for(int i = DIS.currentMove; i < target; i++){*/

    //int pre = DIS.pos.gply;

    for(int i = pDis->pos->curStep; i < target; i++){

        //DIS.pos.gply ++;

        //历史棋步名称
        //SendDlgItemMessage(DLG.step,IDC_LIST_STEP,LB_SETCURSEL,i,0);       //

        //SendMessage(pDis->steplist,LB_SETCURSEL,i,0);       //

		if(pDis->first.pDis == OBS[0]){ //是主窗口
            SendDlgItemMessage(HWND_CONSOLE,IDC_LIST_STEP_MAIN,LB_SETCURSEL,i,0);       //
        }
        else{                               //是其它窗口
            SendDlgItemMessage(pDis->hwndThis,IDC_OBS_STEPLIST,LB_SETCURSEL,i,0);       //
        }

        int move = pDis->pos->His[i+1].move;

        MakePosMoveOnly(pDis->pos,move);        
    }

    //DIS.pos.gply = pre;
    //*************************


	//if(pDis->IsAnalyzeMode == TRUE){
	//	LetYqAnalizeCurPos(pDis);            //让引擎思考
	//}


    //if (DIS.gameMode == EditGame || DIS.gameMode == AnalyzeMode || 
    //    DIS.gameMode == Training || DIS.gameMode == PlayFromGameFile || 
    //    DIS.gameMode == AnalyzeFile) {
    //        /*while (DIS.currentMove < target) {
    //            SendMoveToProgram(DIS.currentMove++, &DIS.first);
    //        }*/
    //        while (DIS.pos.curStep < target) {

    //            DIS.pos.curStep ++;
    //            //SendMoveToProgram(DIS.pos.curStep++, &DIS.first);
    //        }
    //} 
    //else {
    //    //DIS.currentMove = target;
    //    DIS.pos.curStep = target;
    //}

    if (pDis->gameMode == EditGame || pDis->gameMode == EndOfGame) {
        //pDis->whiteTimeRemaining = pDis->timeRemaining[0][pDis->pos->curStep];
        //pDis->blackTimeRemaining = pDis->timeRemaining[1][pDis->pos->curStep];
    }
    //DisplayBothClocks(pDis);

    //DisplayMove(pDis->pos->curStep - 1);
    //DisplayMove(DIS.currentMove - 1);
    
    /*DrawPosition(false, DIS.pos.B256dis[DIS.currentMove]);*/
    DrawPosition(pDis,false, pDis->B256dis[pDis->pos->curStep]);
    //DrawPosition(false, DIS.boards[DIS.currentMove]);
    //HistorySet(DIS.parseList,DIS.backwardMostMove,DIS.forwardMostMove,DIS.currentMove-1);
    //if (DIS.commentList[DIS.currentMove] && !DIS.matchMode && DIS.gameMode != Training) {
    //    DisplayComment(DIS.currentMove - 1, DIS.commentList[DIS.currentMove]);
    //}

	if(pDis->pos->curStep < pDis->pos->gply){
		SendMessage(hwndToolBar,TB_ENABLEBUTTON, IDT_ToEnd,		1);
		SendMessage(hwndToolBar,TB_ENABLEBUTTON, IDT_Forward,	1);
		//SendMessage(hwndToolBar,TB_ENABLEBUTTON, IDT_HUIQI,		0);
	}

	else{
		SendMessage(hwndToolBar,TB_ENABLEBUTTON, IDT_ToEnd,		0);
		SendMessage(hwndToolBar,TB_ENABLEBUTTON, IDT_Forward,	0);
		//SendMessage(hwndToolBar,TB_ENABLEBUTTON, IDT_HUIQI,		1);
	}

	if(pDis->pos->curStep > 0){
		SendMessage(hwndToolBar,TB_ENABLEBUTTON, IDT_ToStart,		1);
		SendMessage(hwndToolBar,TB_ENABLEBUTTON, IDT_Backward,	    1);
		SendMessage(hwndToolBar,TB_ENABLEBUTTON, IDT_HUIQI,		    1);
	}
	else{
		SendMessage(hwndToolBar,TB_ENABLEBUTTON, IDT_ToStart,		0);
		SendMessage(hwndToolBar,TB_ENABLEBUTTON, IDT_Backward,	    0);
		SendMessage(hwndToolBar,TB_ENABLEBUTTON, IDT_HUIQI,		    0);
	}

    ASSERT(position_is_ok(pDis->pos));

	
}


void
ForwardEvent(dispboard_t* pDis){
    if (pDis->gameMode == IcsExamining && !pDis->pausing) {
        //SendToICS(DIS.ics_prefix);
        SendToICS(L"forward\n");
    } 
    else {
        /*ForwardInner(DIS.currentMove + 1);*/
        ForwardInner(pDis,pDis->pos->curStep + 1);
    }


	HDCDrawChart(TAB.dlgScore, pDis, NULL, true);

}

void                //一直走到最后一步
ToEndEvent(dispboard_t* pDis){
    //if (pDis->gameMode == AnalyzeMode || pDis->gameMode == AnalyzeFile) {
	if (pDis->gameMode == AnalyzeMode){
        /* to optimze, we temporarily turn off analysis mode while we feed
        * the remaining moves to the engine. Otherwise we get analysis output
        * after each move.
        */ 
        if (pDis->first.analysisSupport) {
            SendToProgram(L"exit\nforce\n", &pDis->first);
            //pDis->first.analyzing = FALSE;
        }
    }

    if (pDis->gameMode == IcsExamining && !pDis->pausing) {
        //SendToICS(DIS.ics_prefix);
        SendToICS(L"forward 999999\n");
    } 
    else {
        //ForwardInner(DIS.forwardMostMove);
        ForwardInner(pDis,pDis->pos->gply);
    }

    //if (pDis->gameMode == AnalyzeMode || pDis->gameMode == AnalyzeFile) {
	if (pDis->gameMode == AnalyzeMode){
        /* we have fed all the moves, so reactivate analysis mode */
        SendToProgram(L"analyze\n", &pDis->first);
        //pDis->first.analyzing = TRUE;
        /*first.maybeThinking = TRUE;*/
        //pDis->first.maybeThinking = FALSE; /* avoid killing GNU Chess */
    }

	HDCDrawChart(TAB.dlgScore, pDis, NULL, true);

	SendMessage(hwndToolBar,TB_ENABLEBUTTON, IDT_ToEnd,		0);
}

void        //显示后退一步
BackwardInner(dispboard_t* pDis, int target){



#ifdef DEBUG_MODE
    //if (appData.debugMode){
        //fprintf(DIS.debugFP, "BackwardInner(%d), current %d, forward %d\n",
        //    target, DIS.currentMove, DIS.forwardMostMove);
    //}
#endif

    if (pDis->gameMode == EditPosition){
        return;
    }
    //if (DIS.currentMove <= DIS.backwardMostMove) {
    if (pDis->pos->curStep <= 0) {
        ClearHighlights(pDis);
        //DrawPosition(false, DIS.boards[DIS.currentMove]);
        DrawPosition(pDis,false,pDis->B256dis[pDis->pos->curStep]);
        return;
    }
    if (pDis->gameMode == PlayFromGameFile && !pDis->pausing){
        PauseEvent();
    }
    int  tg_move = pDis->pos->His[target+1].move;

    if(tg_move > 0){
        int fromX, fromY,toX,toY;

        int from = FROM(tg_move);
        int to   = TO(tg_move);

        fromX    = StoX(from) - 3;
        fromY    = StoY(from) - 3;

        toX      = StoX(to) - 3;
        toY      = StoY(to) - 3;

        /*if(target == DIS.currentMove - 1){*/
        if(target == pDis->pos->curStep - 1){
           /* AnimateMove(DIS.pos.B256dis[DIS.currentMove],toX,toY,fromX,fromY);*/
            AnimateMove(pDis,pDis->B256dis[pDis->pos->curStep],toX,toY,fromX,fromY);
        }
        if(appData.highlightLastMove){
            SetHighlights(pDis,fromX, fromY, toX, toY);
        }
    }


    //*********************//得返回原来的Pos 
    
    /*for(int i = DIS.currentMove; i > target; i--){*/

    //int pre = DIS.pos.gply;

    for(int i = pDis->pos->curStep; i > target; i--){  //

        //SendMessage(pDis->steplist,LB_SETCURSEL,i-1,0);       //

		if(pDis->first.pDis == OBS[0]){ //是主窗口
            SendDlgItemMessage(HWND_CONSOLE,IDC_LIST_STEP_MAIN,LB_SETCURSEL,i-1,0);       //
        }
        else{                               //是其它窗口
            SendDlgItemMessage(pDis->hwndThis,IDC_OBS_STEPLIST,LB_SETCURSEL,i-1,0);       //
        }

        UnMakePosMoveOnly(pDis->pos);
    }

    

	if (pDis->gameMode == AnalyzeMode){
		//LetYqAnalizeCurPos(pDis);            //让引擎思考
    }


    //DisplayMove(pDis->pos->curStep - 1);
    DrawPosition(pDis,false, pDis->B256dis[pDis->pos->curStep]);

    ASSERT(position_is_ok(pDis->pos));    


	if(pDis->pos->curStep == 0){
		SendMessage(hwndToolBar,TB_ENABLEBUTTON, IDT_ToStart,	0);
		SendMessage(hwndToolBar,TB_ENABLEBUTTON, IDT_Backward,	0);
		SendMessage(hwndToolBar,TB_ENABLEBUTTON, IDT_HUIQI,		0);
	}

	else{
		SendMessage(hwndToolBar,TB_ENABLEBUTTON, IDT_ToStart,	1);
		SendMessage(hwndToolBar,TB_ENABLEBUTTON, IDT_Backward,	1);
		SendMessage(hwndToolBar,TB_ENABLEBUTTON, IDT_HUIQI,		1);
	}

	if(pDis->pos->gply != 0){
		SendMessage(hwndToolBar,TB_ENABLEBUTTON, IDT_Forward,	1);
		SendMessage(hwndToolBar,TB_ENABLEBUTTON, IDT_ToEnd,		1);
	}
	else{
		SendMessage(hwndToolBar,TB_ENABLEBUTTON, IDT_Forward,	0);
		SendMessage(hwndToolBar,TB_ENABLEBUTTON, IDT_ToEnd,		0);
	}
}

void
BackwardEvent(dispboard_t* pDis){            //后退	


	

    if (pDis->gameMode == IcsExamining && !pDis->pausing) {
        //SendToICS(DIS.ics_prefix);
        SendToICS(L"backward\n");
    } 
    else {
        BackwardInner(pDis,pDis->pos->curStep - 1);
    }

	HDCDrawChart(TAB.dlgScore, pDis, NULL, true);


}

void
ToStartEvent(dispboard_t* pDis){
    /*if (pDis->gameMode == AnalyzeMode || pDis->gameMode == AnalyzeFile) {*/
	if (pDis->gameMode == AnalyzeMode) {
        /* to optimze, we temporarily turn off analysis mode while we undo
        * all the moves. Otherwise we get analysis output after each undo.
        */ 
        if (pDis->first.analysisSupport) {
            SendToProgram(L"exit\nforce\n", &pDis->first);  //退出分析功能
            //pDis->first.analyzing = FALSE;
        }
    }

    if (pDis->gameMode == IcsExamining && !pDis->pausing) {
        //SendToICS(pDis->ics_prefix);
        SendToICS(L"backward 999999\n");
    } 
    else {
        /*BackwardInner(DIS.backwardMostMove);*/
        BackwardInner(pDis,0);
    }

    //if (pDis->gameMode == AnalyzeMode || pDis->gameMode == AnalyzeFile) {
	//if(pDis->IsAnalyzeMode == TRUE || p
 //       /* we have fed all the moves, so reactivate analysis mode */
 //       SendToProgram("analyze\n", &pDis->first);
 //       //pDis->first.analyzing = TRUE;
 //       /*first.maybeThinking = TRUE;*/
	//	//if(
 //       //pDis->first.maybeThinking = FALSE; /* avoid killing GNU Chess */
 //   }
	HDCDrawChart(TAB.dlgScore, pDis, NULL, true);
	SendMessage(hwndToolBar,TB_ENABLEBUTTON, IDT_ToStart,		0);
}

void
ToNrEvent(dispboard_t* pDis, int to){
    if (pDis->gameMode == PlayFromGameFile && !pDis->pausing){
        PauseEvent();
    }
    //if (to >= DIS.forwardMostMove){
    //    to = DIS.forwardMostMove;
    //}
    if (to >= pDis->pos->gply){
        to = pDis->pos->gply;
    }
    //if (to <= DIS.backwardMostMove){
    //    to = DIS.backwardMostMove;
    //}
    if (to <= 0){
        to = 0;
    }
    if (to < pDis->pos->curStep) {
        BackwardInner(pDis,to);
    } 
    else {
        ForwardInner(pDis,to);
    }
}

void
RevertEvent(dispboard_t* pDis){
    if (pDis->gameMode != IcsExamining) {
		LogOut(L"You are not examining a game");
        return;
    }
    if (pDis->pausing) {
		LogOut(L"You can't revert while pausing");
        return;
    }
    //SendToICS(DIS.ics_prefix);
    SendToICS(L"revert\n");
}

void
RetractMoveEvent(){
    //switch (DIS.gameMode) {
    //  case MachinePlaysWhite:
    //  case MachinePlaysBlack:
    //      if (WhiteOnMove(DIS.forwardMostMove) == (DIS.gameMode == MachinePlaysWhite)) {
    //          DisplayError("Wait until your turn,\nor select Move Now", 0);
    //          return;
    //      }
    //      if (DIS.forwardMostMove < 2){
    //          return;
    //      }
    //      DIS.currentMove = DIS.forwardMostMove = DIS.forwardMostMove - 2;
    //      DIS.whiteTimeRemaining = DIS.timeRemaining[0][DIS.currentMove];
    //      DIS.blackTimeRemaining = DIS.timeRemaining[1][DIS.currentMove];
    //      DisplayBothClocks();
    //      DisplayMove(DIS.currentMove - 1);
    //      ClearHighlights();/*!! could figure this out*/
    //      DrawPosition(FALSE, DIS.boards[DIS.currentMove]);
    //      SendToProgram("remove\n", &DIS.first);
    //      /*first.maybeThinking = TRUE;*/ /* GNU Chess does not ponder here */
    //      break;

    //  case BeginningOfGame:
    //  default:
    //      break;

    //  case IcsPlayingWhite:
    //  case IcsPlayingBlack:
    //      if (WhiteOnMove(DIS.forwardMostMove) == (DIS.gameMode == IcsPlayingWhite)) {
    //          SendToICS(DIS.ics_prefix);
    //          SendToICS("takeback 2\n");
    //      } 
    //      else {
    //          SendToICS(DIS.ics_prefix);
    //          SendToICS("takeback 1\n");
    //      }
    //      break;
    //}
}

void		//立即出步
MoveNowEvent(){
    //ChessProgramState *cps;

    //switch (DIS.gameMode) {
    //  case MachinePlaysWhite:
    //      if (!WhiteOnMove(DIS.forwardMostMove)) {
    //          DisplayError("It is your turn", 0);
    //          return;
    //      }
    //      cps = &DIS.first;
    //      break;
    //  case MachinePlaysBlack:
    //      if (WhiteOnMove(DIS.forwardMostMove)) {
    //          DisplayError("It is your turn", 0);
    //          return;
    //      }
    //      cps = &DIS.first;
    //      break;
    //  case TwoMachinesPlay:
    //      if (WhiteOnMove(DIS.forwardMostMove) ==
    //          (DIS.first.twoMachinesColor[0] == 'w')) {
    //              cps = &DIS.first;
    //      } 
    //      else {
    //          cps = &DIS.second;
    //      }
    //      break;
    //  case BeginningOfGame:
    //  default:
    //      return;
    //}
    //SendToProgram("?\n", cps);
}

void
TruncateGameEvent(dispboard_t* pDis){
    EditGameEvent(pDis);
    if (pDis->gameMode != EditGame){
        return;
    }
    TruncateGame(pDis);
}


void
HintEvent()
{
    //if (appData.noChessProgram) return;
    //switch (DIS.gameMode) {
    //  case MachinePlaysWhite:
    //      if (WhiteOnMove(DIS.forwardMostMove)) {
    //          DisplayError("Wait until your turn", 0);
    //          return;
    //      }
    //      break;
    //  case BeginningOfGame:
    //  case MachinePlaysBlack:
    //      if (!WhiteOnMove(DIS.forwardMostMove)) {
    //          DisplayError("Wait until your turn", 0);
    //          return;
    //      }
    //      break;
    //  default:
    //      DisplayError("No hint available", 0);
    //      return;
    //}
    //SendToProgram("hint\n", &DIS.first);
    //DIS.hintRequested = TRUE;
}

void
BookEvent(){
    //if (appData.noChessProgram){
    //    return;
    //}
    //switch (DIS.gameMode) {
    //  case MachinePlaysWhite:
    //      if (WhiteOnMove(DIS.forwardMostMove)) {
    //          DisplayError("Wait until your turn", 0);
    //          return;
    //      }
    //      break;
    //  case BeginningOfGame:
    //  case MachinePlaysBlack:
    //      if (!WhiteOnMove(DIS.forwardMostMove)) {
    //          DisplayError("Wait until your turn", 0);
    //          return;
    //      }
    //      break;
    //  case EditPosition:
    //      EditPositionDone();
    //      break;
    //  case TwoMachinesPlay:
    //      return;
    //  default:
    //      break;
    //}
    //SendToProgram("bk\n", &DIS.first);
    //DIS.bookOutput[0] = NULLCHAR;
    //DIS.bookRequested = TRUE;
}

void
AboutGameEvent(){
    //char *tags = PGNTags(&DIS.GGQJ);
    //TagsPopUp(tags, CmailMsg());
    //free(tags);
}

void
AnalysisPeriodicEvent(int force) {
    //if (((DIS.programStats.ok_to_send == 0 || DIS.programStats.line_is_book)
    //    && !force) || !appData.periodicUpdates){
    //        return;
    //}

    ///* Send . command to Crafty to collect stats */
    //SendToProgram(".\n", &DIS.first);

    ///* Don't send another until we get a response (this makes
    //us stop sending to old Crafty's which don't understand
    //the "." command (sending illegal cmds resets node count & time,
    //which looks bad)) */
    //DIS.programStats.ok_to_send = 0;
}


void
PeriodicUpdatesEvent(dispboard_t* pDis,int newState){
    if (newState == appData.periodicUpdates){
        return;
    }

    appData.periodicUpdates=newState;

    /* Display type changes, so update it now */
    DisplayAnalysis();

    /* Get the ball rolling again... */
    if (newState) {
        AnalysisPeriodicEvent(1);
        StartAnalysisClock(pDis);
    }
}

void
PonderNextMoveEvent(dispboard_t* pDis,int newState){
    if (newState == appData.ponderNextMove) return;
    if (pDis->gameMode == EditPosition) EditPositionDone();
 //   if (newState) {
	//	SendToProgram(L"hard\n", &pDis->first);
 //       if (pDis->gameMode == TwoMachinesPlay) {
	//		SendToProgram(L"hard\n", &pDis->second);
 //       }
 //   } 
	//else {
	//	SendToProgram(L"easy\n", &pDis->first);
 //       //pDis->thinkOutput[0] = NULLCHAR;
 //       if (pDis->gameMode == TwoMachinesPlay) {
	//		SendToProgram(L"easy\n", &pDis->second);
 //       }
 //   }
    appData.ponderNextMove = newState;
}

void
ShowThinkingEvent(dispboard_t* pDis,int newState){
    if (newState == appData.showThinking) return;
    if (pDis->gameMode == EditPosition) EditPositionDone();
    if (newState) {
		SendToProgram(L"post\n", &pDis->first);

    } else {
		SendToProgram(L"nopost\n", &pDis->first);
        //pDis->thinkOutput[0] = NULLCHAR;
    }
    appData.showThinking = newState;
}

//void
//AskQuestionEvent(dispboard_t* pDis, TCHAR *title, TCHAR *question, TCHAR *replyPrefix, TCHAR *which){
//    ProcRef pr = (which[0] == '1') ? pDis->first.pr : pDis->second.pr;
//    if (pr == NoProc){
//        return;
//    }
//    AskQuestion(title, question, replyPrefix, pr);
//}



void
AbortEvent(dispboard_t* pDis)
{
    /* Offer Abort or accept pending Abort offer from opponent */

    if (appData.icsActive) {
        //SendToICS(pDis->ics_prefix);
        SendToICS(L"abort\n");
    } 
    else {
        GameEnds(pDis, GameUnfinished, _T("Game aborted"), GE_PLAYER);
    }
}

void		//主窗口关闭时
ExitEvent(int status){

	dispboard_t* pDis = OBS[0];

    appData.Aexiting++;
    if (appData.Aexiting > 2) {
        /* Give up on clean exit */
        exit(status);
    }
    if (appData.Aexiting > 1) {
        /* Keep trying for clean exit */
        return;
    }

    if (appData.icsActive && appData.colorize){
        Colorize(ColorNone, FALSE);
    }

    if (appData.AtelnetISR != NULL) {
        RemoveInputSource(appData.AtelnetISR);
    }
    if (appData.AicsPR != NoProc) {
        DestroyChildProcess(appData.AicsPR, TRUE);
    }
   
    GameEnds(pDis, (ChessMove) 0, NULL, GE_PLAYER);

    /* Kill off chess programs */
    if (pDis->first.pr != NoProc) {
        ExitAnalyzeMode();
        switch(pDis->first.ucci){
            case UCCI_UCCI_ms:
			case UCCI_UCCI_OLD:
				SendToProgram(L"stop\n", &pDis->first);
				SendToProgram(L"quit\n", &pDis->first);
                break;
			case UCCI_GGchess:
				SendToProgram(L"stop\n", &pDis->first);
				SendToProgram(L"quit\n", &pDis->first);
				break;
            case UCCI_CYC105:
				SendToProgram(L"stop\n", &pDis->first);
				SendToProgram(L"quit\n", &pDis->first);
                break;
            case UCCI_QianHong:
				SendToProgram(L"QUIT\n", &pDis->first);
                break;
			
            default:
				SendToProgram(L"quit\n", &pDis->first);
                break;
        }		
        DestroyChildProcess(pDis->first.pr, pDis->first.useSigterm);
    }

    if (pDis->first.isr != NULL) {
        RemoveInputSource(pDis->first.isr);
    }


    ShutDownFrontEnd();

	if(ThStat.isLearn){
		ThStat.isLearn = FALSE;
		Sleep(200);
	}

	BerKeley_DB_EXIT(MST);
	Gdiplus::GdiplusShutdown(m_nGdiplusToken);
    exit(status);
}

void
PauseEvent(void){
    //if (appData.debugMode)
    //    fprintf(DIS.debugFP, "PauseEvent(): pausing %d\n", DIS.pausing);
    //if (DIS.pausing) {
    //    DIS.pausing = FALSE;
    //    ModeHighlight();
    //    if (DIS.gameMode == MachinePlaysWhite ||
    //        DIS.gameMode == MachinePlaysBlack) {
    //            StartClocks();
    //    } 
    //    else {
    //        DisplayBothClocks();
    //    }
    //    if (DIS.gameMode == PlayFromGameFile) {
    //        if (appData.timeDelay >= 0) {
    //            AutoPlayGameLoop();
    //        }
    //    } 
    //    else if (DIS.gameMode == IcsExamining && DIS.pauseExamInvalid) {
    //        GameReset(FALSE, TRUE);
    //        SendToICS(DIS.ics_prefix);
    //        SendToICS("refresh\n");
    //    }
    //    else if (DIS.currentMove < DIS.forwardMostMove) {
    //        ForwardInner(DIS.forwardMostMove);
    //    }
    //    DIS.pauseExamInvalid = FALSE;
    //} 
    //else {
    //    switch (DIS.gameMode) {
    //        default:
    //            return;
    //        case IcsExamining:
    //            DIS.pauseExamForwardMostMove = DIS.forwardMostMove;
    //            DIS.pauseExamInvalid = FALSE;
    //            /* fall through */
    //        case IcsObserving:
    //        case IcsPlayingWhite:
    //        case IcsPlayingBlack:
    //            DIS.pausing = TRUE;
    //            ModeHighlight();
    //            return;
    //        case PlayFromGameFile:
    //            (void) StopLoadGameTimer();
    //            DIS.pausing = TRUE;
    //            ModeHighlight();
    //            break;
    //        case BeginningOfGame:
    //            if (appData.icsActive) return;
    //            /* else fall through */
    //        case MachinePlaysWhite:
    //        case MachinePlaysBlack:
    //        case TwoMachinesPlay:
    //            if (DIS.forwardMostMove == 0)
    //                return;		/* don't pause if no one has moved */
    //            if ((DIS.gameMode == MachinePlaysWhite &&
    //                !WhiteOnMove(DIS.forwardMostMove)) ||
    //                (DIS.gameMode == MachinePlaysBlack &&
    //                WhiteOnMove(DIS.forwardMostMove))) {
    //                    StopClocks();
    //            }
    //            DIS.pausing = TRUE;
    //            ModeHighlight();
    //            break;
    //    }
    //}
}



void
AnalyzeModeEvent(dispboard_t* pDis){
    //if (appData.noChessProgram || pDis->gameMode == AnalyzeMode){
    //    return;
    //}

    //if (pDis->gameMode != AnalyzeFile) {
    //    EditGameEvent();
    //    if (pDis->gameMode != EditGame){
    //        return;
    //    }
    //    ResurrectChessProgram();
    //    SendToProgram("analyze\n", &pDis->first);
    //    pDis->first.analyzing = TRUE;
    //    /*first.maybeThinking = TRUE;*/
    //    pDis->first.maybeThinking = FALSE; /* avoid killing GNU Chess */
    //    AnalysisPopUp("Analysis",
    //        "Starting analysis mode...\nIf this message stays up, your chess program does not support analysis.");
    //}
    //DIS.gameMode = AnalyzeMode;
    //DIS.pausing = FALSE;
    //ModeHighlight();
    //SetGameInfo();

    //StartAnalysisClock();
    //GetTimeMark(&DIS.lastNodeCountTime);
    //DIS.lastNodeCount = 0;
}

void
AnalyzeFileEvent(dispboard_t* pDis){
    //if (appData.noChessProgram || DIS.gameMode == AnalyzeFile){
    //    return;
    //}

    //if (DIS.gameMode != AnalyzeMode) {
    //    EditGameEvent();
    //    if (DIS.gameMode != EditGame){
    //        return;
    //    }
    //    ResurrectChessProgram();
    //    SendToProgram("analyze\n", &DIS.first);
    //    DIS.first.analyzing = TRUE;
    //    /*first.maybeThinking = TRUE;*/
    //    DIS.first.maybeThinking = FALSE; /* avoid killing GNU Chess */
    //    AnalysisPopUp("Analysis",
    //        "Starting analysis mode...\nIf this message stays up, your chess program does not support analysis.");
    //}
    //DIS.gameMode = AnalyzeFile;
    //DIS.pausing  = FALSE;
    //ModeHighlight();
    //SetGameInfo();

    //StartAnalysisClock();
    //GetTimeMark(&DIS.lastNodeCountTime);
    //DIS.lastNodeCount = 0;
}


void
TrainingEvent(){
    //if (DIS.gameMode == Training) {
    //    SetTrainingModeOff();
    //    DIS.gameMode = PlayFromGameFile;
    //    DisplayMessage("", "Training mode off");
    //} 
    //else {
    //    DIS.gameMode = Training;
    //    DIS.animateTraining = appData.animate;

    //    /* make sure we are not already at the end of the game */
    //    /*if (DIS.currentMove < DIS.forwardMostMove) {*/
    //    if (DIS.pos.curStep < DIS.pos.gply) {
    //        SetTrainingModeOn();
    //        DisplayMessage("", "Training mode on");
    //    } 
    //    else {
    //        DIS.gameMode = PlayFromGameFile;
    //        DisplayError("Already at end of game", 0);
    //    }
    //}
    //ModeHighlight();
}

void
IcsClientEvent(dispboard_t* pDis){
    if (!appData.icsActive){
        return;
    }
    switch (pDis->gameMode) {
      case IcsPlayingWhite:
      case IcsPlayingBlack:
      case IcsObserving:
      case IcsIdle:
      case BeginningOfGame:
      case IcsExamining:
          return;

      case EditGame:
          break;

      case EditPosition:
          EditPositionDone();
          break;

      case AnalyzeMode:
      //case AnalyzeFile:
          ExitAnalyzeMode();
          break;

      default:
          EditGameEvent(pDis);
          break;
    }

    //pDis->gameMode = IcsIdle;

	ChangeGameMode(pDis,IcsIdle);

    ModeHighlight();
    return;
}


void             //编辑游戏菜单事件
EditGameEvent(dispboard_t* pDis){
    //int i;

    //switch (DIS.gameMode) {
    //  case Training:
    //      SetTrainingModeOff();
    //      break;
    //  case MachinePlaysWhite:
    //  case MachinePlaysBlack:
    //  case BeginningOfGame:
    //      SendToProgram("force\n", &DIS.first);
    //      SetUserThinkingEnables();
    //      break;
    //  case PlayFromGameFile:
    //      (void) StopLoadGameTimer();
    //      if (DIS.gameFileFP != NULL) {
    //          DIS.gameFileFP = NULL;
    //      }
    //      break;
    //  case EditPosition:
    //      EditPositionDone();
    //      break;
    //  case AnalyzeMode:
    //  case AnalyzeFile:
    //      ExitAnalyzeMode();
    //      SendToProgram("force\n", &DIS.first);
    //      break;
    //  case TwoMachinesPlay:
    //      GameEnds((ChessMove) 0, NULL, GE_PLAYER);
    //      ResurrectChessProgram();
    //      SetUserThinkingEnables();
    //      break;
    //  case EndOfGame:
    //      ResurrectChessProgram();
    //      break;
    //  case IcsPlayingBlack:
    //  case IcsPlayingWhite:
    //      DisplayError("Warning: You are still playing a game", 0);
    //      break;
    //  case IcsObserving:
    //      DisplayError("Warning: You are still observing a game", 0);
    //      break;
    //  case IcsExamining:
    //      DisplayError("Warning: You are still examining a game", 0);
    //      break;
    //  case IcsIdle:
    //      break;
    //  case EditGame:
    //  default:
    //      return;
    //}

    //DIS.pausing = FALSE;
    //StopClocks();
    //DIS.first.offeredDraw = DIS.second.offeredDraw = 0;

    //if (DIS.gameMode == PlayFromGameFile) {
    //    DIS.whiteTimeRemaining = DIS.timeRemaining[0][DIS.pos.curStep];
    //    DIS.blackTimeRemaining = DIS.timeRemaining[1][DIS.pos.curStep];
    //    DisplayTitle("");
    //}

    //if (DIS.gameMode == MachinePlaysWhite ||
    //    DIS.gameMode == MachinePlaysBlack ||
    //    DIS.gameMode == TwoMachinesPlay ||
    //    DIS.gameMode == EndOfGame) {
    //        /*i = DIS.forwardMostMove;*/
    //        i = DIS.pos.gply;
    //        while (i > DIS.pos.curStep) {
    //            SendToProgram("undo\n", &DIS.first);
    //            i--;
    //        }
    //        DIS.whiteTimeRemaining = DIS.timeRemaining[0][DIS.pos.curStep];
    //        DIS.blackTimeRemaining = DIS.timeRemaining[1][DIS.pos.curStep];
    //        DisplayBothClocks();
    //        if (DIS.whiteFlag || DIS.blackFlag) {
    //            DIS.whiteFlag = DIS.blackFlag = 0;
    //        }
    //        DisplayTitle("");
    //}		

	pDis->gameMode = EditGame;
    //ModeHighlight();
    //SetGameInfo();
}


void			//编辑游戏局面事件
EditPositionEvent(){
    //if (DIS.gameMode == EditPosition) {
    //    EditGameEvent();
    //    return;
    //}

    //EditGameEvent();
    //if (DIS.gameMode != EditGame){
    //    return;
    //}

    //DIS.gameMode = EditPosition;
    //ModeHighlight();
    //SetGameInfo();
    //if (DIS.currentMove > 0){
    //    CopyBoard(DIS.boards[0],DIS.boards[DIS.currentMove]);
    //}
    //DIS.blackPlaysFirst = !WhiteOnMove(DIS.currentMove);
    //ResetClocks();
    //DIS.currentMove = DIS.forwardMostMove = DIS.backwardMostMove = 0;
    ////HistorySet(DIS.parseList, DIS.backwardMostMove, DIS.forwardMostMove, DIS.currentMove-1);
    //DisplayMove(-1);
}




void
AcceptEvent(dispboard_t* DIS){
    /* Accept a pending offer of any kind from opponent */

    if (appData.icsActive) {
        //SendToICS(DIS.ics_prefix);
        SendToICS(L"accept\n");
    } 
    //else if (DIS.cmailMsgLoaded) {
    //    //if (DIS.currentMove == DIS.cmailOldMove && 	DIS.commentList[DIS.cmailOldMove] != NULL 
    //    //	&& StrStr(DIS.commentList[DIS.cmailOldMove], WhiteOnMove(DIS.cmailOldMove) ?
    //    //	"Black offers a draw" : "White offers a draw")) {
    //    //		TruncateGame();
    //    //		GameEnds(GameIsDrawn, "Draw agreed", GE_PLAYER);
    //    //		DIS.cmailMoveType[DIS.lastLoadGameNumber - 1] = CMAIL_ACCEPT;
    //    //} 
    //    //else {
    //    //		DisplayError("There is no pending offer on this move", 0);
    //    //		DIS.cmailMoveType[DIS.lastLoadGameNumber - 1] = CMAIL_MOVE;
    //    //}
    //} 
    //else {
    //    /* Not used for offers from chess program */
    //}
}

void
DeclineEvent(dispboard_t* DIS){
    /* Decline a pending offer of any kind from opponent */

    if (appData.icsActive) {
        //SendToICS(DIS.ics_prefix);
        SendToICS(L"decline\n");
    } 
    //else if (DIS.cmailMsgLoaded) {
    //    //if (DIS.currentMove == DIS.cmailOldMove &&
    //    //	DIS.commentList[DIS.cmailOldMove] != NULL &&
    //    //	StrStr(DIS.commentList[DIS.cmailOldMove], WhiteOnMove(DIS.cmailOldMove) ?
    //    //	"Black offers a draw" : "White offers a draw")) {
    //    //	#ifdef NOTDEF
    //    //					AppendComment(DIS.cmailOldMove, "Draw declined");
    //    //					DisplayComment(DIS.cmailOldMove - 1, "Draw declined");
    //    //	#endif /*NOTDEF*/
    //    //} 
    //    //else {
    //    //		DisplayError("There is no pending offer on this move", 0);
    //    //}
    //} 
    //else {
    //    /* Not used for offers from chess program */
    //}
}

void
RematchEvent(void){
    /* Issue ICS rematch command */
    if (appData.icsActive) {
        //SendToICS(DIS.ics_prefix);
        SendToICS(L"rematch\n");
    }
}

void
CallFlagEvent(dispboard_t* pDis){
    /* Call your opponent's flag (claim a win on time) */
    if (appData.icsActive) {
        //SendToICS(DIS.ics_prefix);
        SendToICS(L"flag\n");
    }
    else {
        switch (pDis->gameMode) {
            default:
                return;
            case MachinePlaysWhite:
                if (pDis->whiteFlag) {
                    if (pDis->blackFlag)
						GameEnds(pDis, GameIsDrawn, _T("Both players ran out of time"), GE_PLAYER);
                    else
						GameEnds(pDis, BlackWins, _T("Black wins on time"), GE_PLAYER);
                } 
                else {
					LogOut(L"Your opponent is not out of time");
                }
                break;
            case MachinePlaysBlack:
                if (pDis->blackFlag) {
                    if (pDis->whiteFlag)
						GameEnds(pDis, GameIsDrawn, _T("Both players ran out of time"),
                        GE_PLAYER);
                    else
						GameEnds(pDis, WhiteWins, _T("White wins on time"), GE_PLAYER);
                } 
                else {
					LogOut(L"Your opponent is not out of time");
                }
                break;
        }
    }
}

//错误	10	error LNK2001 : 无法解析的外部符号 "void __cdecl DisplayFatalError(char *,int,int)" (? DisplayFatalError@@YAXPADHH@Z)	E : \PROG\GGchessGUi\ICS_Common.obj	GGchess


void
DrawEvent(dispboard_t* pDis)
{
    /* Offer draw or accept pending draw offer from opponent */

    if (appData.icsActive) {
        /* Note: tournament rules require draw offers to be
        made after you make your move but before you punch
        your clock.  Currently ICS doesn't let you do that;
        instead, you immediately punch your clock after making
        a move, but you can offer a draw at any time. */

        //SendToICS(DIS.ics_prefix);
        SendToICS(L"draw\n");
    } 
    //else if (DIS.cmailMsgLoaded) {
    //    //if (DIS.currentMove == DIS.cmailOldMove &&
    //    //	DIS.commentList[DIS.cmailOldMove] != NULL &&
    //    //	StrStr(DIS.commentList[DIS.cmailOldMove], WhiteOnMove(DIS.cmailOldMove) ?
    //    //	"Black offers a draw" : "White offers a draw")) {
    //    //		GameEnds(GameIsDrawn, "Draw agreed", GE_PLAYER);
    //    //		DIS.cmailMoveType[DIS.lastLoadGameNumber - 1] = CMAIL_ACCEPT;
    //    //	} 
    //    //else if (DIS.currentMove == DIS.cmailOldMove + 1) {
    //    //	char *offer = WhiteOnMove(DIS.cmailOldMove) ?
    //    //		"White offers a draw" : "Black offers a draw";
    //    //	AppendComment(DIS.currentMove, offer);
    //    //	//DisplayComment(DIS.currentMove - 1, offer);
    //    //	DIS.cmailMoveType[DIS.lastLoadGameNumber - 1] = CMAIL_DRAW;
    //    //} 
    //    //else {
    //    //	DisplayError("You must make your move before offering a draw", 0);
    //    //	DIS.cmailMoveType[DIS.lastLoadGameNumber - 1] = CMAIL_MOVE;
    //    //}
    //} 
    else if (pDis->first.offeredDraw) {
        GameEnds(pDis,GameIsDrawn, _T("Draw agreed"), GE_XBOARD);
    } 
    else {
        if (pDis->first.sendDrawOffers) {
            SendToProgram(L"draw\n", &pDis->first);
            pDis->userOfferedDraw = TRUE;
        }
    }
}

void
AdjournEvent()
{
    /* Offer Adjourn or accept pending Adjourn offer from opponent */

    if (appData.icsActive) {
        //SendToICS(DIS.ics_prefix);
        SendToICS(L"adjourn\n");
    } else {
        /* Currently GNU Chess doesn't offer or accept Adjourns */
    }
}




void
ResignEvent()
{
    /* Resign.  You can do this even if it's not your turn. */

    //if (appData.icsActive) {
    //    SendToICS(DIS.ics_prefix);
    //    SendToICS("resign\n");
    //} else {
    //    switch (DIS.gameMode) {
    //  case MachinePlaysWhite:
    //      GameEnds(WhiteWins, "Black resigns", GE_PLAYER);
    //      break;
    //  case MachinePlaysBlack:
    //      GameEnds(BlackWins, "White resigns", GE_PLAYER);
    //      break;
    //  case EditGame:
    //      if (DIS.cmailMsgLoaded) {
    //          TruncateGame();
    //          if (WhiteOnMove(DIS.cmailOldMove)) {
    //              GameEnds(BlackWins, "White resigns", GE_PLAYER);
    //          } else {
    //              GameEnds(WhiteWins, "Black resigns", GE_PLAYER);
    //          }
    //          DIS.cmailMoveType[DIS.lastLoadGameNumber - 1] = CMAIL_RESIGN;
    //      }
    //      break;
    //  default:
    //      break;
    //    }
    //}
}


void
StopObservingEvent()
{
    /* Stop observing current games */
    //SendToICS(DIS.ics_prefix);
    SendToICS(L"unobserve\n");
}

void
StopExaminingEvent()
{
    /* Stop observing current game */
    //SendToICS(DIS.ics_prefix);
    SendToICS(L"unexamine\n");
}
