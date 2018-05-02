#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"






//void
//CopyPlayerNameIntoFileName(char **dest,char *src){
//    while (*src != NULLCHAR && *src != ',') {
//        if (*src == ' ') {
//            *(*dest)++ = '_';
//            src++;
//        } 
//        else {
//            *(*dest)++ = *src++;
//        }
//    }
//}
//
//char *DefaultFileName(char *ext){
//    static char def[MSG_SIZ];
//    char *p;
//
//    //if (DIS.gameInfo.white != NULL && DIS.gameInfo.white[0] != '-') {
//    if(DIS.pgn.Rname[0] != '-'){
//        p = def;
//        CopyPlayerNameIntoFileName(&p, DIS.pgn.Rname);
//        *p++ = '-';
//        CopyPlayerNameIntoFileName(&p, DIS.pgn.Bname);
//        *p++ = '.';
//        //strcpy(p, ext);
//        StringCbCopy(p,MSG_SIZ,ext);
//    } 
//    else {
//        def[0] = NULLCHAR;
//    }
//    return def;
//}




void
ExitAnalyzeMode(){
    //if (DIS.first.analysisSupport && DIS.first.analyzing) {
    //    SendToProgram("exit\n", &DIS.first);
    //    DIS.first.analyzing = FALSE;
    //}
    //AnalysisPopDown();
    //DIS.thinkOutput[0] = NULLCHAR;
}

void
EditPositionDone(){
    //DIS.startedFromSetupPosition = TRUE;
    //InitChessProgram(&DIS.first);
    //SendToProgram("force\n", &DIS.first);
    //if (DIS.blackPlaysFirst) {
    //    //strcpy(DIS.moveList[0], "");
    //    //StringCbCopy(DIS.moveList[0],32,"");
    //    DIS.moveList[0] = 0;
    //    //strcpy(DIS.parseList[0], "");
    //    StringCbCopy(DIS.parseList[0],34,"");
    //    DIS.currentMove = DIS.forwardMostMove = DIS.backwardMostMove = 1;
    //    CopyBoard(DIS.boards[1], DIS.boards[0]);
    //} 
    //else {
    //    DIS.currentMove = DIS.forwardMostMove = DIS.backwardMostMove = 0;
    //}
    //SendBoard(&DIS.first, DIS.forwardMostMove);
    //DisplayTitle("");
    //DIS.timeRemaining[0][DIS.forwardMostMove] = DIS.whiteTimeRemaining;
    //DIS.timeRemaining[1][DIS.forwardMostMove] = DIS.blackTimeRemaining;
    //DIS.gameMode = EditGame;
    //ModeHighlight();
    //HistorySet(DIS.parseList, DIS.backwardMostMove, DIS.forwardMostMove, DIS.currentMove-1);
}









/* end button procedures */

void
PrintPosition(FILE *fp,int move){
    //   int i, j;
    //   
    //   for (i = BOARD_SIZE - 1; i >= 0; i--) {
    //for (j = 0; j < BOARD_SIZE; j++) {
    //    char c = PieceToChar(boards[move][i][j]);
    //    fputc(c == 'x' ? '.' : c, fp);
    //    fputc(j == BOARD_SIZE - 1 ? '\n' : ' ', fp);
    //}
    //   }
    //   if ((gameMode == EditPosition) ? !blackPlaysFirst : (move % 2 == 0))
    //     fprintf(fp, "white to play\n");
    //   else
    //     fprintf(fp, "black to play\n");
}

//void
//PrintOpponents(FILE *fp){
//    //if (DIS.gameInfo.white != NULL) {
//    if(DIS.pgn.Rname[0] != NULLCHAR){
//        fprintf(fp, "\t%s vs. %s\n", DIS.pgn.Rname, DIS.pgn.Bname);
//    } 
//    else {
//        fprintf(fp, "\n");
//    }
//}

/* Find last component of program's own name, using some heuristics */
//void
//TidyProgramName(char *prog,char *host,char buf[MSG_SIZ]){
//
//
//    //if(prog == NULL){
//    //    sprintf_s(buf,5,"无");
//    //    return;
//    //}
//
//    char *p, *q;
//    int local = (strcmp(host, "localhost") == 0);
//    while (!local && (p = strchr(prog, ';')) != NULL) {
//        p++;
//        while (*p == ' '){
//            p++;
//        }
//        prog = p;
//    }
//    if (*prog == '"' || *prog == '\'') {
//        q = strchr(prog + 1, *prog);
//    } 
//    else {
//        q = strchr(prog, ' ');
//    }
//    if (q == NULL){
//        q = prog + strlen(prog);
//    }
//    p = q;
//    while (p >= prog && *p != '/' && *p != '\\'){
//        p--;
//    }
//    p++;
//    if (q - p >= 4 && StrCaseCmp(q - 4, ".exe") == 0){
//        q -= 4;
//    }
//    memcpy(buf, p, q - p);
//    buf[q - p] = NULLCHAR;
//    if (!local) {
//        strcat_s(buf,MSG_SIZ,"@");
//		strcat_s(buf, MSG_SIZ, host);
//    }
//}







//void
//DisplayComment(int moveNumber,char *text){
//	char title[MSG_SIZ];
//
//	if (moveNumber < 0 || DIS.parseList[moveNumber][0] == NULLCHAR) {
//		//strcpy(title, "Comment");
//		StringCbCopy(title,MSG_SIZ,"Comment");
//	} 
//	else {
//		StringCbPrintf(title,MSG_SIZ,"Comment on %d.%s%s", moveNumber / 2 + 1,
//		//sprintf(title, "Comment on %d.%s%s", moveNumber / 2 + 1,
//			WhiteOnMove(moveNumber) ? " " : ".. ",
//			DIS.parseList[moveNumber]);
//	}
//
//	CommentPopUp(title, text);
//}

/* This routine sends a ^C interrupt to gnuchess, to awaken it if it
* might be busy thinking or pondering.  It can be omitted if your
* gnuchess is configured to stop thinking immediately on any user
* input.  However, that gnuchess feature depends on the FIONREAD
* ioctl, which does not work properly on some flavors of Unix.
*/
void
Attention(ChessProgramState *cps)
{
#if ATTENTION
    if (!cps->useSigint) return;
    if (appData.noChessProgram || (cps->pr == NoProc)) return;
    switch (DIS.gameMode) {
          case MachinePlaysWhite:
          case MachinePlaysBlack:
          case TwoMachinesPlay:
          case IcsPlayingWhite:
          case IcsPlayingBlack:
          case AnalyzeMode:
          case AnalyzeFile:
              /* Skip if we know it isn't thinking */
              if (!cps->maybeThinking) return;
              if (appData.debugMode){
                  fprintf(DIS.debugFP, "Interrupting %s\n", cps->which);
              }
              InterruptChildProcess(cps->pr);
              cps->maybeThinking = FALSE;
              break;
          default:
              break;
    }
#endif /*ATTENTION*/
}


void
EditPositionPasteFEN(TCHAR *fen, dispboard_t* pDis)
{

	if (appData.icsActive == FALSE) {
		ChessProgramState *cps = &pDis->first;

		if (cps->cps_stat == Cps_Thinking || cps->cps_stat == Cps_Pondering || cps->cps_stat == Cps_Analyse) {
			SendToPlayerByColor(_T("当前引擎正在思考,不能输入fen\n"), ColorSeek, FALSE);
			LogOut(fen);
			return;
		}
	}

	if (fen != NULL) {

		dispboard_t tmp[1];

		tmp->hwndThis = pDis->hwndThis;
		InitPosition(tmp, FALSE);

		if (set_position(tmp, tmp->pos, fen) == FALSE) {
			SendToPlayerByColor(_T("输入的fen格式有错\n"), ColorSeek, FALSE);
			LogOut(fen);
			return;
		}

		InitPosition(pDis, FALSE);
		set_position(pDis, pDis->pos, fen);

		pDis->pgn->isFenGame = TRUE;

		DrawPosition(pDis, false, pDis->B256dis[pDis->pos->curStep]);

	}
}












void
PackHolding(char packed[],char *holding)  {
    char *p = holding;
    char *q = packed;
    int runlength = 0;
    int curr = 9999;
    do {
        if (*p == curr) {
            runlength++;
        } 
        else {
            switch (runlength) {
                case 0:
                    break;
                case 1:
                    *q++ = curr;
                    break;
                case 2:
                    *q++ = curr;
                    *q++ = curr;
                    break;
                default:
                    //sprintf(q, "%d", runlength);
                    sprintf_s(q,MSG_SIZ,"%d", runlength);
                    while (*q) q++;
                    *q++ = curr;
                    break;
            }
            runlength = 1;
            curr = *p;
        }
    } while (*p++);
    *q = NULLCHAR;
}

void
ParseBoard12(char *string)  { 
//    GameMode newGameMode;
//    int gamenum, newGame, newMove, relation, basetime, increment, ics_flip = 0;
//    int j, k, n, moveNum, white_stren, black_stren, white_time, black_time;
//    int double_push, castle_ws, castle_wl, castle_bs, castle_bl, irrev_count;
//    char to_play, board_chars[72];
//    char move_str[500], str[500], elapsed_time[500];
//    char black[32], white[32];
//    //board_t board;
//    int prevMove = DIS.currentMove;	
//
//    int ticking = 2;
//    ChessMove moveType;
//    int fromX, fromY, toX, toY;
//    //char promoChar;
//
//    fromX = fromY = toX = toY = -1;
//
//    newGame = FALSE;
//
//    if (appData.debugMode)
//        fprintf(DIS.debugFP, "Parsing board: %s\n", string);
//
//    move_str[0] = NULLCHAR;
//    elapsed_time[0] = NULLCHAR;
//    //n = sscanf_s(string, PATTERN, board_chars, &to_play, &double_push,
//    //    &castle_ws, &castle_wl, &castle_bs, &castle_bl, &irrev_count,
//    //    &gamenum, white, black, &relation, &basetime, &increment,
//    //    &white_stren, &black_stren, &white_time, &black_time,
//    //    &moveNum, str, elapsed_time, move_str, &ics_flip,
//    //    &ticking);
//
//    n = sscanf_s(string, PATTERN, board_chars,sizeof(board_chars), &to_play,sizeof(to_play),
//        &double_push, &castle_ws, &castle_wl, &castle_bs, &castle_bl, &irrev_count,
//        &gamenum, white,sizeof(white), black,sizeof(black), &relation, &basetime, &increment,
//        &white_stren, &black_stren, &white_time, &black_time,
//        &moveNum, str,sizeof(str), elapsed_time,sizeof(elapsed_time), move_str,sizeof(move_str),
//        &ics_flip, &ticking);
//
//    if (n < 22) {
//        //	sprintf(str, "Failed to parse board string:\n\"%s\"", string);
//        DisplayError(str, 0);
//        return;
//    }
//
//    /* Convert the move number to internal form */
//    moveNum = (moveNum - 1) * 2;
//    if (to_play == 'B') moveNum++;
//    if (moveNum >= MAX_MOVES) {
//        DisplayFatalError("Game too long; increase MAX_MOVES and recompile",
//            0, 1);
//        return;
//    }
//
//    switch (relation) {
//      case RELATION_OBSERVING_PLAYED:
//      case RELATION_OBSERVING_STATIC:
//          if (gamenum == -1) {
//              /* Old ICC buglet */
//              relation = RELATION_OBSERVING_STATIC;
//          }
//          newGameMode = IcsObserving;
//          break;
//      case RELATION_PLAYING_MYMOVE:
//      case RELATION_PLAYING_NOTMYMOVE:
//          newGameMode =
//              ((relation == RELATION_PLAYING_MYMOVE) == (to_play == 'W')) ?
//IcsPlayingWhite : IcsPlayingBlack;
//          break;
//      case RELATION_EXAMINING:
//          newGameMode = IcsExamining;
//          break;
//      case RELATION_ISOLATED_BOARD:
//      default:
//          /* Just display this board.  If user was doing something else,
//          we will forget about it until the next board comes. */ 
//          newGameMode = IcsIdle;
//          break;
//      case RELATION_STARTING_POSITION:
//          newGameMode = DIS.gameMode;
//          break;
//    }
//
//    /* Modify behavior for initial board display on move listing
//    of wild games.
//    */
//    switch (DIS.ics_getting_history) {
//      case H_FALSE:
//      case H_REQUESTED:
//          break;
//      case H_GOT_REQ_HEADER:
//      case H_GOT_UNREQ_HEADER:
//          /* This is the initial position of the current game */
//          gamenum = DIS.ics_gamenum;
//          moveNum = 0;		/* old ICS bug workaround */
//          if (to_play == 'B') {
//              DIS.startedFromSetupPosition = TRUE;
//              DIS.blackPlaysFirst = TRUE;
//              moveNum = 1;
//              if (DIS.forwardMostMove == 0){
//                  DIS.forwardMostMove = 1;
//              }
//              if (DIS.backwardMostMove == 0){
//                  DIS.backwardMostMove = 1;
//              }
//              if (DIS.currentMove == 0){
//                  DIS.currentMove = 1;
//              }
//          }
//          newGameMode = DIS.gameMode;
//          relation = RELATION_STARTING_POSITION; /* ICC needs this */
//          break;
//      case H_GOT_UNWANTED_HEADER:
//          /* This is an initial board that we don't want */
//          return;
//      case H_GETTING_MOVES:
//          /* Should not happen */
//          DisplayError("Error gathering move list: extra board", 0);
//          DIS.ics_getting_history = H_FALSE;
//          return;
//    }
//
//    /* Take action if this is the first board of a new game, or of a
//    different game than is currently being displayed.  */
//    if (gamenum != DIS.ics_gamenum || newGameMode != DIS.gameMode ||
//        relation == RELATION_ISOLATED_BOARD) {
//
//            /* Forget the old game and get the history (if any) of the new one */
//            if (DIS.gameMode != BeginningOfGame) {
//                GameReset(FALSE, TRUE);
//            }
//            newGame = TRUE;
//            if (appData.autoRaiseBoard) BoardToTop();
//            prevMove = -3;
//            if (gamenum == -1) {
//                newGameMode = IcsIdle;
//            } else if (moveNum > 0 && newGameMode != IcsIdle &&
//                appData.getMoveList) {
//                    /* Need to get game history */
//                    DIS.ics_getting_history = H_REQUESTED;
//                    //	    sprintf(str, "%smoves %d\n", ics_prefix, gamenum);
//                    SendToICS(str);
//            }
//
//            /* Initially flip the board to have black on the bottom if playing
//            black or if the ICS flip flag is set, but let the user change
//            it with the Flip View button. */
//            DIS.flipView = appData.autoFlipView ? 
//                (newGameMode == IcsPlayingBlack) || ics_flip :
//            appData.flipView;
//
//            /* Done with values from previous mode; copy in new ones */
//            DIS.gameMode = newGameMode;
//            ModeHighlight();
//            DIS.ics_gamenum = gamenum;
//            if (gamenum == DIS.gs_gamenum) {
//                int klen = int(strlen(DIS.gs_kind));
//                if (DIS.gs_kind[klen - 1] == '.'){
//                    DIS.gs_kind[klen - 1] = NULLCHAR;
//                }
//                // sprintf(str, "ICS %s", gs_kind);
//                // DIS.gameInfo.event = StrSave(str);
//                StringCbPrintf(DIS.GGQJ.event,sizeof(DIS.GGQJ.event),"ICS %s", DIS.gs_kind);
//            } 
//            else {
//                //DIS.gameInfo.event = StrSave("ICS game");
//                StringCbPrintf(DIS.GGQJ.event,sizeof(DIS.GGQJ.event),"ICS game");
//            }
//            //DIS.gameInfo.site = StrSave(appData.icsHost);
//            StringCbPrintf(DIS.GGQJ.site,sizeof(DIS.GGQJ.site),appData.icsHost);
//            //DIS.gameInfo.date = PGNDate();
//            //StringCbPrintf(DIS.GGQJ.date,sizeof(DIS.GGQJ.date),PGNDate());
//            PGNDate(DIS.GGQJ.date);
//            //DIS.gameInfo.round = StrSave("-");
//            StringCbPrintf(DIS.GGQJ.round,sizeof(DIS.GGQJ.round),"-");
//            //DIS.gameInfo.white = StrSave(white);
//            StringCbPrintf(DIS.GGQJ.Rname,sizeof(DIS.GGQJ.Rname),white);
//            //DIS.gameInfo.black = StrSave(black);
//            StringCbPrintf(DIS.GGQJ.Bname,sizeof(DIS.GGQJ.Bname),black);
//            DIS.timeControl   = basetime * 60 * 1000;
//            DIS.timeIncrement = increment * 1000;
//            DIS.movesPerSession = 0;
//            //DIS.gameInfo.timeControl = TimeControlTagValue();
//            //StringCbPrintf(DIS.GGQJ.timeControl,sizeof(DIS.GGQJ.timeControl),TimeControlTagValue());
//            TimeControlTagValue(DIS.GGQJ.timeControl);
//            DIS.GGQJ.variant = StringToVariant(DIS.GGQJ.event);
//            //StringCbPrintf(DIS.GGQJ.variant,sizeof(DIS.GGQJ.variant),StringToVariant(DIS.GGQJ.event));
//            /* Do we have the ratings? */
//            if (strcmp(DIS.player1Name, white) == 0 &&strcmp(DIS.player2Name, black) == 0) {
//                if (appData.debugMode){
//                    fprintf(DIS.debugFP, "Remembered ratings: W %d, B %d\n",
//                        DIS.player1Rating, DIS.player2Rating);
//                }
//                //DIS.gameInfo.whiteRating = DIS.player1Rating;
//                DIS.GGQJ.Relo = DIS.player1Rating;
//                //DIS.gameInfo.blackRating = DIS.player2Rating;
//                DIS.GGQJ.Belo = DIS.player2Rating;
//            } 
//            else if (strcmp(DIS.player2Name, white) == 0 && strcmp(DIS.player1Name, black) == 0) {
//                if (appData.debugMode){
//                    fprintf(DIS.debugFP, "Remembered ratings: W %d, B %d\n",
//                        DIS.player2Rating, DIS.player1Rating);
//                }
//                //DIS.gameInfo.whiteRating = DIS.player2Rating;
//                DIS.GGQJ.Relo = DIS.player2Rating;
//                //DIS.gameInfo.blackRating = DIS.player1Rating;
//                DIS.GGQJ.Belo = DIS.player1Rating;
//            }
//            DIS.player1Name[0] = DIS.player2Name[0] = NULLCHAR;
//
//            /* Silence shouts if requested */
//            if (appData.quietPlay &&
//                (DIS.gameMode == IcsPlayingWhite || DIS.gameMode == IcsPlayingBlack)) {
//                    SendToICS(DIS.ics_prefix);
//                    SendToICS("set shout 0\n");
//            }
//    }
//
//    /* Deal with midgame name changes */
//    if (!newGame) {
//        //if (!DIS.gameInfo.white || strcmp(DIS.gameInfo.white, white) != 0) {
//        //	if (DIS.gameInfo.white) free(DIS.gameInfo.white);
//        //	DIS.gameInfo.white = StrSave(white);
//        //}
//        if(strcmp(DIS.GGQJ.Rname,white) != 0){
//            StringCbCopy(DIS.GGQJ.Rname,sizeof(DIS.GGQJ.Rname),white);
//        }
//        //if (!DIS.gameInfo.black || strcmp(DIS.gameInfo.black, black) != 0) {
//        //	if (DIS.gameInfo.black) free(DIS.gameInfo.black);
//        //	DIS.gameInfo.black = StrSave(black);
//        //}
//        if(strcmp(DIS.GGQJ.Bname,black) != 0){
//            StringCbCopy(DIS.GGQJ.Bname,sizeof(DIS.GGQJ.Bname),black);
//        }
//    }
//
//    /* Throw away game result if anything actually changes in examine mode */
//    if (DIS.gameMode == IcsExamining && !newGame) {
//        DIS.GGQJ.cmresult = GameUnfinished;
//        //if (DIS.gameInfo.resultDetails != NULL) {
//        //	free(DIS.gameInfo.resultDetails);
//        //	DIS.gameInfo.resultDetails = NULL;
//        //}
//    }
//
//    /* In pausing && IcsExamining mode, we ignore boards coming
//    in if they are in a different variation than we are. */
//    if (DIS.pauseExamInvalid) return;
//    if (DIS.pausing && DIS.gameMode == IcsExamining) {
//        if (moveNum <= DIS.pauseExamForwardMostMove) {
//            DIS.pauseExamInvalid = TRUE;
//            DIS.forwardMostMove = DIS.pauseExamForwardMostMove;
//            return;
//        }
//    }
//
//    /* Parse the board */
//    for (k = 0; k < 8; k++)
//        for (j = 0; j < 8; j++)
//            //	board[k][j] = CharToPiece(board_chars[(7-k)*9 + j]);
//            //    CopyBoard(boards[moveNum], board);
//            if (moveNum == 0) {
//                //	startedFromSetupPosition =
//                //	  !CompareBoards(board, initialPosition);
//            }
//
//            if (DIS.ics_getting_history == H_GOT_REQ_HEADER ||
//                DIS.ics_getting_history == H_GOT_UNREQ_HEADER) {
//                    /* This was an initial position from a move list, not
//                    the current position */
//                    return;
//            }
//
//            /* Update currentMove and known move number limits */
//            newMove = newGame || moveNum > DIS.forwardMostMove;
//            if (newGame) {
//                DIS.forwardMostMove = DIS.backwardMostMove = DIS.currentMove = moveNum;
//                if (DIS.gameMode == IcsExamining && moveNum == 0) {
//                    /* Workaround for ICS limitation: we are not told the wild
//                    type when starting to examine a game.  But if we ask for
//                    the move list, the move list header will tell us */
//                    DIS.ics_getting_history = H_REQUESTED;
//                    //	    sprintf(str, "%smoves %d\n", ics_prefix, gamenum);
//                    SendToICS(str);
//                }
//            } else if (moveNum == DIS.forwardMostMove + 1 
//                || moveNum ==  DIS.forwardMostMove
//                || (moveNum <  DIS.forwardMostMove
//                && moveNum >=  DIS.backwardMostMove)) {
//                    DIS.forwardMostMove = moveNum;
//                    if (!DIS.pausing || DIS.currentMove > DIS.forwardMostMove)
//                        DIS.currentMove = DIS.forwardMostMove;
//            } else {
//                /* New part of history that is not contiguous with old part */ 
//                if (DIS.pausing && DIS.gameMode == IcsExamining) {
//                    DIS.pauseExamInvalid = TRUE;
//                    DIS.forwardMostMove = DIS.pauseExamForwardMostMove;
//                    return;
//                }
//                DIS.forwardMostMove = DIS.backwardMostMove = DIS.currentMove = moveNum;
//                if (DIS.gameMode == IcsExamining && moveNum > 0 && appData.getMoveList) {
//                    DIS.ics_getting_history = H_REQUESTED;
//                    //	    sprintf(str, "%smoves %d\n", ics_prefix, gamenum);
//                    SendToICS(str);
//                }
//            }
//
//            /* Update the clocks */
//            if (strchr(elapsed_time, '.')) {
//                /* Time is in ms */
//                DIS.timeRemaining[0][moveNum] = DIS.whiteTimeRemaining = white_time;
//                DIS.timeRemaining[1][moveNum] = DIS.blackTimeRemaining = black_time;
//            } else {
//                /* Time is in seconds */
//                DIS.timeRemaining[0][moveNum] = DIS.whiteTimeRemaining = white_time * 1000;
//                DIS.timeRemaining[1][moveNum] = DIS.blackTimeRemaining = black_time * 1000;
//            }
//
//
//            //#if ZIPPY
//            //    if (appData.zippyPlay && newGame &&
//            //	gameMode != IcsObserving && gameMode != IcsIdle &&
//            //	gameMode != IcsExamining)
//            //      ZippyFirstBoard(moveNum, basetime, increment);
//            //#endif
//
//            /* Put the move on the move list, first converting
//            to canonical algebraic form. */
//            if (moveNum > 0) {
//                if (moveNum <= DIS.backwardMostMove) {
//                    /* We don't know what the board looked like before
//                    this move.  Punt. */
//                    //	    strcpy(parseList[moveNum - 1], move_str);
//                    //	    strcat(parseList[moveNum - 1], " ");
//                    //	    strcat(parseList[moveNum - 1], elapsed_time);
//                    //	    DIS.moveList[moveNum - 1][0] = NULLCHAR;
//                } 
//                else if (ParseOneMove(move_str, moveNum - 1, &moveType,
//                    &fromX, &fromY, &toX, &toY, DIS.ucci)) {
//                        //(void) CoordsToAlgebraic(boards[moveNum - 1],
//                        //    PosFlags(moveNum - 1), EP_UNKNOWN,
//                        //    fromY, fromX, toY, toX, promoChar,
//                        //    parseList[moveNum-1]);
//                        //   switch (MateTest(boards[moveNum], PosFlags(moveNum), EP_UNKNOWN)){
//                        //     case MT_NONE:
//                        //     case MT_STALEMATE:
//                        //     default:
//                        //break;
//                        //     case MT_CHECK:
//                        //strcat(parseList[moveNum - 1], "+");
//                        //break;
//                        //     case MT_CHECKMATE:
//                        //strcat(parseList[moveNum - 1], "#");
//                        //break;
//                        //   }
//                        //  strcat(parseList[moveNum - 1], " ");
//                        //  strcat(parseList[moveNum - 1], elapsed_time);
//                        /* currentMoveString is set as a side-effect of ParseOneMove */
//                        //	    strcpy(moveList[moveNum - 1], currentMoveString);
//                        //	    strcat(moveList[moveNum - 1], "\n");
//                } 
//                else if (strcmp(move_str, "none") == 0) {
//                    /* Again, we don't know what the board looked like;
//                    this is really the start of the game. */
//                    DIS.parseList[moveNum - 1][0] = NULLCHAR;
//                    // DIS.moveList[moveNum - 1][0] = NULLCHAR;
//                    DIS.backwardMostMove = moveNum;
//                    DIS.startedFromSetupPosition = TRUE;
//                    fromX = fromY = toX = toY = -1;
//                } else {
//                    /* Move from ICS was illegal!?  Punt. */
//                    //#if 0
//                    //	    if (appData.testLegality && appData.debugMode) {
//                    //		sprintf(str, "Illegal move \"%s\" from ICS", move_str);
//                    //		DisplayError(str, 0);
//                    //	    }
//                    //#endif
//                    ////	    strcpy(parseList[moveNum - 1], move_str);
//                    //	    strcat(parseList[moveNum - 1], " ");
//                    //	    strcat(parseList[moveNum - 1], elapsed_time);
//                    // DIS.moveList[moveNum - 1][0] = NULLCHAR;
//                    fromX = fromY = toX = toY = -1;
//                }
//
//                //#if ZIPPY
//                //	/* Send move to chess program (BEFORE animating it). */
//                //	if (appData.zippyPlay && !newGame && newMove && 
//                //	   (!appData.getMoveList || backwardMostMove == 0) && first.initDone) {
//                //
//                //	    if ((gameMode == IcsPlayingWhite && WhiteOnMove(moveNum)) ||
//                //		(gameMode == IcsPlayingBlack && !WhiteOnMove(moveNum))) {
//                //		if (moveList[moveNum - 1][0] == NULLCHAR) {
//                //		 //   sprintf(str, "Couldn't parse move \"%s\" from ICS",
//                //		//	    move_str);
//                //		    DisplayError(str, 0);
//                //		} else {
//                //		    if (first.sendTime) {
//                //			SendTimeRemaining(&first, gameMode == IcsPlayingWhite);
//                //		    }
//                //		    SendMoveToProgram(moveNum - 1, &first);
//                //		    if (firstMove) {
//                //			firstMove = FALSE;
//                //			if (first.useColors) {
//                //			  SendToProgram(gameMode == IcsPlayingWhite ?
//                //					"white\ngo\n" :
//                //					"black\ngo\n", &first);
//                //			} else {
//                //			  SendToProgram("go\n", &first);
//                //			}
//                //			first.maybeThinking = TRUE;
//                //		    }
//                //		}
//                //	    } else if (gameMode == IcsObserving || gameMode == IcsExamining) {
//                //	      if (moveList[moveNum - 1][0] == NULLCHAR) {
//                ////		sprintf(str, "Couldn't parse move \"%s\" from ICS", move_str);
//                //		DisplayError(str, 0);
//                //	      } else {
//                //		SendMoveToProgram(moveNum - 1, &first);
//                //	      }
//                //	    }
//                //	}
//                //#endif
//            }
//
//            if (moveNum > 0 && !DIS.gotPremove) {
//                /* If move comes from a remote source, animate it.  If it
//                isn't remote, it will have already been animated. */
//                if (!DIS.pausing && !DIS.ics_user_moved && prevMove == moveNum - 1) {
//                    AnimateMove(DIS.boards[moveNum - 1], fromX, fromY, toX, toY);
//                }
//                if (!DIS.pausing && appData.highlightLastMove) {
//                    SetHighlights(fromX, fromY, toX, toY);
//                }
//            }
//
//            /* Start the clocks */
//            DIS.whiteFlag = DIS.blackFlag = FALSE;
//            appData->clockMode = !(basetime == 0 && increment == 0);
//            if (ticking == 0) {
//                DIS.ics_clock_paused = TRUE;
//                StopClocks();
//            } else if (ticking == 1) {
//                DIS.ics_clock_paused = FALSE;
//            }
//            if (DIS.gameMode == IcsIdle ||
//                relation == RELATION_OBSERVING_STATIC ||
//                relation == RELATION_EXAMINING ||
//                DIS.ics_clock_paused)
//                DisplayBothClocks();
//            else
//                StartClocks();
//
//            /* Display opponents and material strengths */
//            if (DIS.GGQJ.variant != VariantBughouse && DIS.GGQJ.variant != VariantCrazyhouse) {
//                if (DIS.tinyLayout || DIS.smallLayout) {
//                    //	    sprintf(str, "%s(%d) %s(%d) {%d %d}", 
//                    //		    gameInfo.white, white_stren, gameInfo.black, black_stren,
//                    //		    basetime, increment);
//                    StringCbPrintf(str,sizeof(str),"%s(%d) %s(%d) {%d %d}", 
//                        DIS.GGQJ.Rname, white_stren, DIS.GGQJ.Bname, black_stren, basetime, increment);
//                } 
//                else {
//                    //	    sprintf(str, "%s (%d) vs. %s (%d) {%d %d}", 
//                    //		    gameInfo.white, white_stren, gameInfo.black, black_stren,
//                    //		    basetime, increment);
//                    StringCbPrintf(str,sizeof(str),"%s (%d) vs. %s (%d) {%d %d}", 
//                        DIS.GGQJ.Rname, white_stren, DIS.GGQJ.Bname, black_stren,basetime, increment);
//                }
//                DisplayTitle(str);
//            }
//
//
//            /* Display the board */
//            if (!DIS.pausing) {
//
//                if (appData.premove){
//                    if (!DIS.gotPremove || 
//                        ((DIS.gameMode == IcsPlayingWhite) && (WhiteOnMove(DIS.currentMove))) ||
//                        ((DIS.gameMode == IcsPlayingBlack) && (!WhiteOnMove(DIS.currentMove)))){
//                            ClearPremoveHighlights();
//                    }
//                }
//
//                DrawPosition(false, DIS.boards[DIS.currentMove]);
//                DisplayMove(moveNum - 1);
//                if (appData.ringBellAfterMoves && !DIS.ics_user_moved){
//                    RingBell();
//                }
//            }

            //  HistorySet(DIS.parseList, DIS.backwardMostMove,
            //DIS.forwardMostMove, DIS.currentMove-1);
}









void
ParseGameHistory(char *game)
{

}

//void 
//GetSetYQsetFromAppData(void){
//    //在这儿读入设定的参数哇
//    //DIS.first.program				= appData.first.program;
//    //DIS.first.bookFile				= appData.first.bookFile;
//    //DIS.first.dir					= appData.first.dir;
//    //DIS.first.isBook				= appData.first.isBook;
//    //DIS.first.isPonderThink			= appData.first.isPonderThink;
//    //DIS.first.ucci					= appData.first.ucci;
//    //DIS.first.protocolVersion		= appData.first.protocolVersion;
//    //DIS.first.hashSize				= appData.first.hashSize;
//    //DIS.first.timePerStep			= appData.first.timePerStep;
//    //DIS.first.searchDepth			= appData.first.searchDepth;
//    //DIS.first.isBaoGan				= appData.first.isBaoGan;
//    //DIS.first.BaoGanTime			= appData.first.BaoGanTime;
//    //DIS.first.firstClassTimeStep	= appData.first.firstClassTimeStep;
//    //DIS.first.firstClassTime		= appData.first.firstClassTime;
//    //DIS.first.secondClassTimeStep	= appData.first.secondClassTimeStep;
//    //DIS.first.secondClassTime		= appData.first.secondClassTime;
//    //DIS.first.initString			= appData.first.initString;
//    //DIS.first.computerString		= appData.first.computerString;
//
//    //DIS.second.program				= appData.second.program;
//    //DIS.second.bookFile				= appData.second.bookFile;
//    //DIS.second.dir					= appData.second.dir;
//    //DIS.second.isBook				= appData.second.isBook;
//    //DIS.second.isPonderThink		= appData.second.isPonderThink;
//    //DIS.second.ucci					= appData.second.ucci;
//    //DIS.second.protocolVersion		= appData.second.protocolVersion;
//    //DIS.second.hashSize				= appData.second.hashSize;
//    //DIS.second.timePerStep			= appData.second.timePerStep;
//    //DIS.second.searchDepth			= appData.second.searchDepth;
//    //DIS.second.isBaoGan				= appData.second.isBaoGan;
//    //DIS.second.BaoGanTime			= appData.second.BaoGanTime;
//    //DIS.second.firstClassTimeStep	= appData.second.firstClassTimeStep;
//    //DIS.second.firstClassTime		= appData.second.firstClassTime;
//    //DIS.second.secondClassTimeStep	= appData.second.secondClassTimeStep;
//    //DIS.second.secondClassTime		= appData.second.secondClassTime;
//    //DIS.second.initString			= appData.second.initString;
//    //DIS.second.computerString		= appData.second.computerString;
//}
//
//
