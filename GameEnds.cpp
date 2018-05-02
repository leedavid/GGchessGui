#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

void			//结束当前游戏
GameEnds(dispboard_t* pDis, ChessMove result,TCHAR *resultDetails,int whosays){
    GameMode nextGameMode;
    int isIcsGame;
    TCHAR buf[MSG_SIZ];

#ifdef DEBUG_USE_DEBUG_FILE
    //if (appData.debugMode) {
        fprintf(appData.debugFP, "GameEnds(%d, %s, %d)\n",
            result, resultDetails ? resultDetails : "(null)", whosays);
    //}
#endif
	//	backend.cpp(261): if(cps->cps_stat == Cps_Thinking || cps->cps_stat == Cps_Pondering || cps->cps_stat == Cps_Analyse){

	ChessProgramState *cps = &pDis->first;

	if(cps->cps_stat == Cps_Thinking || cps->cps_stat == Cps_Pondering || cps->cps_stat == Cps_Analyse){
		SendToProgram(L"stop\n", cps);
		Sleep(100);
		SendToProgram(L"stop\n", cps);
		Sleep(100);
		cps->playWhat       = NEUTRAL;
		ChangeGameMode(pDis, GameNoneMode);
		SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_COM_RED, 0);
	}

    /* If we're loading the game from a file, stop */
    if (whosays == GE_FILE) {               //GAME END FROM FIE
        (void) StopLoadGameTimer(pDis);
        //MAIN.gameFileFP = NULL;
    }

    /* Cancel draw offers */
    pDis->first.offeredDraw = 0;

    /* If this is an ICS game, only ICS can really say it's done;
    if not, anyone can. */
    isIcsGame = (pDis->gameMode == IcsPlayingWhite || pDis->gameMode == IcsPlayingBlack || 
        pDis->gameMode == IcsObserving    || pDis->gameMode == IcsExamining);

    if (!isIcsGame || whosays == GE_ICS) {
        /* OK -- not an ICS game, or ICS said it was done */
        StopClocks(pDis);
       /* if (!isIcsGame && !pDis->noChessProgram){*/
		if (!isIcsGame ){
            SetUserThinkingEnables();
        }

        if (resultDetails != NULL) {
            //gameInfo.result = result;
            //DIS.pgn.cmresult = result;
            //gameInfo.resultDetails = StrSave(resultDetails);
            //StringCbPrintf(DIS.pgn.resultDetails,sizeof(DIS.pgn.resultDetails),resultDetails);

            /* Tell program how game ended in case it is learning */
            if (pDis->gameMode == MachinePlaysWhite ||
                pDis->gameMode == MachinePlaysBlack ||               
                pDis->gameMode == IcsPlayingWhite ||
                pDis->gameMode == IcsPlayingBlack ||
                pDis->gameMode == BeginningOfGame) 
            {
                //char buf[MSG_SIZ];
                //sprintf(buf, "result %s {%s}\n", PGNResult(result),resultDetails);
                //StringCbPrintf(buf,MSG_SIZ,"result %s {%s}\n", PGNResult(result),resultDetails);
                //if (DIS.first.pr != NoProc) {
                //    SendToProgram(buf, &DIS.first);
                //}
                //if (DIS.second.pr != NoProc &&DIS.gameMode == TwoMachinesPlay) {
                //    SendToProgram(buf, &DIS.second);
                //}
            }


            if (pDis->pos->gply != 0) {/*if (DIS.forwardMostMove != 0) {*/
				if (pDis->gameMode != PlayFromGameFile && pDis->gameMode != EditGame ) { //&& ThStat.isLearn == FALSE
                    //if (*appData.saveGameFile != NULLCHAR) {
                    //    SaveGameToFile(appData.saveGameFile, TRUE);
                    //} 
                    //else if (appData.autoSaveGames) {
                    //    AutoSaveGame();
                    //}
                    //if (*appData.savePositionFile != NULLCHAR) {
                    //    SavePositionToFile(appData.savePositionFile);
                    //}

					if(appData.autoSaveGames){
						ThStat.isFillQk = TRUE;
						AutoSaveGame(pDis);
						ThStat.isFillQk = FALSE;
					}
                }
            }
        }

        if (appData.icsActive) {
            if (appData.quietPlay &&
                (pDis->gameMode == IcsPlayingWhite ||
                pDis->gameMode == IcsPlayingBlack)) {
                    //SendToICS(pDis->ics_prefix);
                    //SendToICS("set shout 1\n");
            }
            //nextGameMode = IcsIdle;
            //pDis->ics_user_moved = FALSE;
            /* clean up premove.  It's ugly when the game has ended and the
            * premove highlights are still on the board.
            */
            if (pDis->gotPremove) {
                pDis->gotPremove = FALSE;
                ClearPremoveHighlights(pDis);
                //DrawPosition(false,DIS.pos.B256dis[DIS.currentMove]);
                DrawPosition(pDis,false,pDis->B256dis[pDis->pos->curStep]);
            }
            if (whosays == GE_ICS) {
                switch (result) {
                    case WhiteWins:
						if (pDis->gameMode == IcsPlayingWhite){
							//PlayIcsWinSound();
						}
						else if (pDis->gameMode == IcsPlayingBlack){
							//PlayIcsLossSound();
						}
                        break;
                    case BlackWins:
						if (pDis->gameMode == IcsPlayingBlack){
							//PlayIcsWinSound();
						}
						else if (pDis->gameMode == IcsPlayingWhite){
							//PlayIcsLossSound();
						}
                        break;
                    case GameIsDrawn:
                        //PlayIcsDrawSound();
                        break;
					default:{
						//PlayIcsUnfinishedSound();
					}
                }
            }
        } 
        else if (pDis->gameMode == EditGame ||
            pDis->gameMode == PlayFromGameFile || 
            pDis->gameMode == AnalyzeMode ) {
                nextGameMode = pDis->gameMode;
        } 
        else {
            nextGameMode = EndOfGame;
        }
        pDis->pausing = FALSE;
        ModeHighlight();
    } 
    else {
        nextGameMode = pDis->gameMode;
    }


    if (pDis->first.reuse) {
        /* Put first chess program into idle state */
        if (pDis->first.pr != NoProc &&
            ( pDis->gameMode == MachinePlaysWhite || pDis->gameMode == MachinePlaysBlack 
            || pDis->gameMode == IcsPlayingWhite 
            ||pDis->gameMode == IcsPlayingBlack || pDis->gameMode == BeginningOfGame)) 
        {
            SendToProgram(L"force\n", &pDis->first);
            if (pDis->first.usePing) {

                swprintf_s(buf,128,(L"ping %d\n"), ++pDis->first.lastPing);
                SendToProgram(buf, &pDis->first);
            }
        }
    } 
    else if (result != GameUnfinished || nextGameMode == IcsIdle) {
        /* Kill off first chess program */
        if (pDis->first.isr != NULL){
            RemoveInputSource(pDis->first.isr);
        }
        pDis->first.isr = NULL;

        if (pDis->first.pr != NoProc) {
            ExitAnalyzeMode();
			SendToProgram(L"quit\n", &pDis->first);
            DestroyChildProcess(pDis->first.pr, pDis->first.useSigterm);
        }
        pDis->first.pr = NoProc;
    }


	if (pDis->gameMode == AnalyzeMode)
        ExitAnalyzeMode();

	ChangeGameMode(pDis,nextGameMode);
	
    ModeHighlight();
}

