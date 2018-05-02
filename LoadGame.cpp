#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

//int				//读入一个棋步到内存中
//LoadGameOneMove(ChessMove readAhead){
//    //int				fromX = 0;
//    //int				fromY = 0;
//    //int				toX   = 0;
//    //int				toY   = 0;
//    //int				done;
//    //   ChessMove		moveType;
//    //char			move[MSG_SIZ];
//    //char            *p;
//    //char            *q;
//
//    //if (DIS.gameMode != PlayFromGameFile && DIS.gameMode != AnalyzeFile && 
//    //    DIS.gameMode != AnalyzeMode && DIS.gameMode != Training) {
//    //        DIS.gameFileFP = NULL;
//    //        return FALSE;
//    //}
//    return false;
//}

/* Load the nth game from the given file */
//int
//LoadGameFromFile(char *filename,int n,char *title,int useList){
//    //   FILE *f;
//    //   char buf[MSG_SIZ];
//
//    //   if (strcmp(filename, "-") == 0) {
//    //f = stdin;
//    //title = "stdin";
//    //   } else {
//    //f = fopen(filename, "rb");
//    //if (f == NULL) {
//    //   // sprintf(buf, "Can't open \"%s\"", filename);
//    //    DisplayError(buf, errno);
//    //    return FALSE;
//    //}
//    //   }
//    //   if (fseek(f, 0, 0) == -1) {
//    ///* f is not seekable; probably a pipe */
//    //useList = FALSE;
//    //   }
//    //   if (useList && n == 0) {
//    //int error = GameListBuild(f);
//    //if (error) {
//    //    DisplayError("Cannot build game list", error);
//    //} else if (!ListEmpty(&DIS.gameList) &&
//    //	   ((ListGame *) DIS.gameList.tailPred)->number > 1) {
//    //    GameListPopUp(f, title);
//    //    return TRUE;
//    //}
//    //GameListDestroy();
//    //n = 1;
//    //   }
//    //   if (n == 0) n = 1;
//    //   return LoadGame(f, n, title, FALSE);
//    return false;
//}



/* Support for LoadNextGame, LoadPreviousGame, ReloadSameGame */
//int
//ReloadGame(int offset){
//    //int gameNumber = DIS.lastLoadGameNumber + offset;
//    //if (DIS.lastLoadGameFP == NULL) {
//    //    DisplayError("No game has been loaded yet", 0);
//    //    return FALSE;
//    //}
//    //if (gameNumber <= 0) {
//    //    DisplayError("Can't back up any further", 0);
//    //    return FALSE;
//    //}
//    ///*    if (DIS.cmailMsgLoaded) {
//    //return CmailLoadGame(DIS.lastLoadGameFP, gameNumber,
//    //DIS.lastLoadGameTitle, DIS.lastLoadGameUseList);
//    //} 
//    //else*/ 
//    //{
//    //    return LoadGame(DIS.lastLoadGameFP, gameNumber,
//    //        DIS.lastLoadGameTitle, DIS.lastLoadGameUseList);
//    //}
//    return false;
//}






int	//读入一局佳佳棋局到内存中
LoadGameOneGameFromMysql(PGN *pgg, bool isToEnd){
    return 0;
    //ChessMove cm;
    //char buf[MSG_SIZ];
    ////int gn = gameNumber;
    ////ListGame *lg = NULL;
    ////int numPGNTags = 0;
    ////int err;


    //if (appData.debugMode){
    //    fprintf(DIS.debugFP, 
    //        "LoadGameOneGameFromMysql(): on entry, gameMode %d\n", DIS.gameMode);
    //}

    //if (DIS.gameMode == Training ){
    //    SetTrainingModeOff();
    //}

    ////GameMode oldGameMode;
    ////oldGameMode = DIS.gameMode;
    ////if (DIS.gameMode != BeginningOfGame) {			//不是刚开始游戏
    ////	GameReset(FALSE, TRUE);
    ////}

    ////GameListDestroy();
    //StringCbPrintf(buf,MSG_SIZ, "%s vs. %s", pgg->Rname,pgg->Bname);
    //DisplayTitle(buf);								//显示一下窗口标题
    ////显示一下其它信息到STEP对话框中
    //SendGGqjToDlg(pgg);

    //if (DIS.gameMode != AnalyzeFile && DIS.gameMode != AnalyzeMode) {
    //    DIS.gameMode = PlayFromGameFile;
    //    ModeHighlight();
    //}

    //DIS.currentMove = DIS.forwardMostMove = DIS.backwardMostMove = 0;
    ////CopyBoard(DIS.boards[0], initialPosition);
    //StopClocks();

    //cm = DIS.lastLoadGameStart = (ChessMove)0;

    ////得到初始局面
    ////DIS.gameInfo.
    //DIS.startedFromSetupPosition  = TRUE;
    //if(D8ToB90((int*)pgg->qipu,DIS.boards[0])){		//开始局面是红走
    //    DIS.blackPlaysFirst = FALSE;
    //}
    //else{
    //    DIS.blackPlaysFirst = TRUE;
    //}

    //if(DIS.blackPlaysFirst){
    //    DIS.currentMove = DIS.forwardMostMove = DIS.backwardMostMove = 1;
    //    CopyBoard(DIS.boards[1],DIS.boards[0]);

    //    //strcpy(DIS.moveList[0], "");
    //    //StringCbCopy(DIS.moveList[0],32,"");
    //    DIS.moveList[0] = 0;
    //    //strcpy(DIS.parseList[0], "");
    //    StringCbCopy(DIS.parseList[0],32,"");
    //    DIS.timeRemaining[0][1] = DIS.whiteTimeRemaining;
    //    DIS.timeRemaining[1][1] = DIS.blackTimeRemaining;
    //    //if (DIS.commentList[0] != NULL) {
    //    //	DIS.commentList[1] = DIS.commentList[0];
    //    //	DIS.commentList[0] = NULL;
    //    //}
    //}
    //else{
    //    DIS.currentMove = DIS.forwardMostMove = DIS.backwardMostMove = 0;
    //}

    ////SetGameInfo();
    ////TagsPopDown();
    ////DisplayMove(DIS.currentMove - 1);
    ////DrawPosition(false, DIS.boards[DIS.currentMove]);



    ///* if the first token after the PGN tags is a move
    //* and not move number 1, retrieve it from the parser 
    //*/
    ////if (cm != MoveNumberOne){
    ////	LoadGameOneMove(cm);
    ////}

    ///* load the remaining moves from the file */
    ////while (LoadGameOneMove((ChessMove)0)) {
    ////  DIS.timeRemaining[0][DIS.forwardMostMove] = DIS.whiteTimeRemaining;
    ////  DIS.timeRemaining[1][DIS.forwardMostMove] = DIS.blackTimeRemaining;
    ////}

    //// 读入每一个棋步
    //if (DIS.gameMode == PlayFromGameFile || DIS.gameMode == AnalyzeFile || 
    //    DIS.gameMode == AnalyzeMode      || DIS.gameMode == Training) {

    //        //char *pqipu = pgg->qipu + 32;
    //        char *pend  = pgg->qipu + pgg->qipulen;

    //        for(char *pqipu = pgg->qipu+32; pqipu<pend; pqipu+=2){
    //            //以上也可省略哇
    //            //LoadOneMoveFromGGqj(pqipu);	
    //            mv_t move = MOVE_MAKE(*pqipu,*(pqipu+1));
    //            //GetMoveName(DIS.boards[DIS.currentMove],move,DIS.currentMoveString,StepNameTypeB);

    //            //DIS.moveList[DIS.forwardMostMove] = move;

    //            //DIS.thinkOutput[0] = NULLCHAR;   //??

    //            MakeMove(S90toF(MOVE_FROM(move)),S90toR(MOVE_FROM(move)),
    //                S90toF(MOVE_TO(move)),   S90toR(MOVE_TO(move)), false);
    //            //DIS.currentMove = DIS.forwardMostMove;
    //            //	return true;
    //            //}
    //            //else{		
    //            //	return false;
    //            //}
    //            //DIS.timeRemaining[0][DIS.forwardMostMove] = DIS.whiteTimeRemaining;
    //            //DIS.timeRemaining[1][DIS.forwardMostMove] = DIS.blackTimeRemaining;
    //        }	
    //}


    ///* rewind to the start of the game */
    //DIS.currentMove = DIS.backwardMostMove;

    ////HistorySet(DIS.parseList, DIS.backwardMostMove,
    ////DIS.forwardMostMove, DIS.currentMove-1);

    ////if (oldGameMode == AnalyzeFile ||oldGameMode == AnalyzeMode) {
    ////		AnalyzeFileEvent();
    ////}

    //if(isToEnd){
    //    ToEndEvent();
    //    DIS.gameMode = EditGame;
    //    ModeHighlight();
    //}
    //else{
    //    if (DIS.matchMode || appData.timeDelay == 0) {
    //        ToEndEvent();
    //        DIS.gameMode = EditGame;
    //        ModeHighlight();
    //    } 
    //    else if (appData.timeDelay > 0) {
    //        AutoPlayGameLoop();
    //    }
    //}



    //if (appData.debugMode) {
    //    fprintf(DIS.debugFP, "LoadGameOneGameFromMysql(): on exit, gameMode %d\n", DIS.gameMode);
    //}
    //return TRUE;
}

/* Load the nth game from open file f */
//int
//LoadGame(FILE *f,int gameNumber,char *title,int useList){
//    //   ChessMove cm;
//    //   char buf[MSG_SIZ];
//    //   int gn = gameNumber;
//    //   ListGame *lg = NULL;
//    //   int numPGNTags = 0;
//    //   int err;
//    //   GameMode oldGameMode;
//
//    //if (appData.debugMode) {
//    //	fprintf(DIS.debugFP, "LoadGame(): on entry, gameMode %d\n", DIS.gameMode);
//    //}
//
//    //if (DIS.gameMode == Training ){
//    //	SetTrainingModeOff();
//    //}
//
//    //   oldGameMode = DIS.gameMode;
//    //   if (DIS.gameMode != BeginningOfGame) {
//    //     GameReset(FALSE, TRUE);
//    //   }
//
//    //DIS.gameFileFP = f;
//    //if (lastLoadGameFP != NULL && lastLoadGameFP != f) {
//    //	fclose(lastLoadGameFP);
//    //}
//
//    //if (useList) {
//    //	lg = (ListGame *) ListElem(&DIS.gameList, gameNumber-1);
//
//    //	if (lg) {
//    //		fseek(f, lg->offset, 0);
//    //		GameListHighlight(gameNumber);
//    //		gn = 1;
//    //	}
//    //	else {
//    //		DisplayError("Game number out of range", 0);
//    //		return FALSE;
//    //	}
//    //} 
//    //else {
//    //	GameListDestroy();
//    //	if (fseek(f, 0, 0) == -1) {
//    //		if (f == lastLoadGameFP ?
//    //			gameNumber == lastLoadGameNumber + 1 : gameNumber == 1) {
//    //			gn = 1;
//    //		} 
//    //		else {
//    //			DisplayError("Can't seek on game file", 0);
//    //			return FALSE;
//    //		}
//    //	}
//    //}
//    //lastLoadGameFP = f;
//    //lastLoadGameNumber = gameNumber;
//    ////strcpy(lastLoadGameTitle, title);
//    //StringCbCopy(lastLoadGameTitle,MSG_SIZ,title);
//    //lastLoadGameUseList = useList;
//
//    //   yynewfile(f);
//
//
//    //if (lg && lg->gameInfo.white && lg->gameInfo.black) {
//    //	sprintf(buf, "%s vs. %s", lg->gameInfo.white,
//    //		lg->gameInfo.black);
//    //	DisplayTitle(buf);
//    //} 
//    //else if (*title != NULLCHAR) {
//    //	if (gameNumber > 1) {
//    //		sprintf(buf, "%s %d", title, gameNumber);
//    //		DisplayTitle(buf);
//    //	} 
//    //	else {
//    //		DisplayTitle(title);
//    //	}
//    //}
//
//    //if (DIS.gameMode != AnalyzeFile && DIS.gameMode != AnalyzeMode) {
//    //	DIS.gameMode = PlayFromGameFile;
//    //	ModeHighlight();
//    //}
//
//    //   currentMove = forwardMostMove = backwardMostMove = 0;
//    //   CopyBoard(boards[0], initialPosition);
//    //   StopClocks();
//
//    //   /*
//    //    * Skip the first gn-1 games in the file.
//    //    * Also skip over anything that precedes an identifiable 
//    //    * start of game marker, to avoid being confused by 
//    //    * garbage at the start of the file.  Currently 
//    //    * recognized start of game markers are the move number "1",
//    //    * the pattern "gnuchess .* game", the pattern
//    //    * "^[#;%] [^ ]* game file", and a PGN tag block.  
//    //    * A game that starts with one of the latter two patterns
//    //    * will also have a move number 1, possibly
//    //    * following a position diagram.
//    //    * 5-4-02: Let's try being more lenient and allowing a game to
//    //    * start with an unnumbered move.  Does that break anything?
//    //    */
//    //   cm = lastLoadGameStart = (ChessMove) 0;
//    //   while (gn > 0) {
//    //yyboardindex = forwardMostMove;
//    //cm = (ChessMove) yylex();
//    //switch (cm) {
//    //  case (ChessMove) 0:
//    //    if (cmailMsgLoaded) {
//    //	nCmailGames = CMAIL_MAX_GAMES - gn;
//    //    } else {
//    //	Reset(TRUE, TRUE);
//    //	DisplayError("Game not found in file", 0);
//    //    }
//    //    return FALSE;
//
//    //  case GNUChessGame:
//    //  case XBoardGame:
//    //    gn--;
//    //    lastLoadGameStart = cm;
//    //    break;
//    //    
//    //  case MoveNumberOne:
//    //    switch (lastLoadGameStart) {
//    //      case GNUChessGame:
//    //      case XBoardGame:
//    //      case PGNTag:
//    //	break;
//    //      case MoveNumberOne:
//    //      case (ChessMove) 0:
//    //	gn--;		/* count this game */
//    //	lastLoadGameStart = cm;
//    //	break;
//    //      default:
//    //	/* impossible */
//    //	break;
//    //    }
//    //    break;
//
//    //  case PGNTag:
//    //    switch (lastLoadGameStart) {
//    //      case GNUChessGame:
//    //      case PGNTag:
//    //      case MoveNumberOne:
//    //      case (ChessMove) 0:
//    //	gn--;		/* count this game */
//    //	lastLoadGameStart = cm;
//    //	break;
//    //      case XBoardGame:
//    //	lastLoadGameStart = cm; /* game counted already */
//    //	break;
//    //      default:
//    //	/* impossible */
//    //	break;
//    //    }
//    //    if (gn > 0) {
//    //	do {
//    //	    yyboardindex = forwardMostMove;
//    //	    cm = (ChessMove) yylex();
//    //	} while (cm == PGNTag || cm == Comment);
//    //    }
//    //    break;
//
//    //  case WhiteWins:
//    //  case BlackWins:
//    //  case GameIsDrawn:
//    //    if (cmailMsgLoaded && (CMAIL_MAX_GAMES == lastLoadGameNumber)) {
//    //	if (   cmailResult[CMAIL_MAX_GAMES - gn - 1]
//    //	    != CMAIL_OLD_RESULT) {
//    //	    nCmailResults ++ ;
//    //	    cmailResult[  CMAIL_MAX_GAMES
//    //			- gn - 1] = CMAIL_OLD_RESULT;
//    //	}
//    //    }
//    //    break;
//
//    //  case NormalMove:
//    //    /* Only a NormalMove can be at the start of a game
//    //     * without a position diagram. */
//    //    if (lastLoadGameStart == (ChessMove) 0) {
//    //      gn--;
//    //      lastLoadGameStart = MoveNumberOne;
//    //    }
//    //    break;
//
//    //  default:
//    //    break;
//    //}
//    //   }
//    //   
//    //   if (appData.debugMode)
//    //     fprintf(debugFP, "Parsed game start '%s' (%d)\n", yy_text, (int) cm);
//
//    //   if (cm == XBoardGame) {
//    ///* Skip any header junk before position diagram and/or move 1 */
//    //for (;;) {
//    //    yyboardindex = forwardMostMove;
//    //    cm = (ChessMove) yylex();
//
//    //    if (cm == (ChessMove) 0 ||
//    //	cm == GNUChessGame || cm == XBoardGame) {
//    //	/* Empty game; pretend end-of-file and handle later */
//    //	cm = (ChessMove) 0;
//    //	break;
//    //    }
//
//    //    if (cm == MoveNumberOne || cm == PositionDiagram ||
//    //	cm == PGNTag || cm == Comment)
//    //      break;
//    //}
//    //   } else if (cm == GNUChessGame) {
//    //if (gameInfo.event != NULL) {
//    //    free(gameInfo.event);
//    //}
//    //gameInfo.event = StrSave(yy_text);
//    //   }	
//
//    //   startedFromSetupPosition = FALSE;
//    //   while (cm == PGNTag) {
//    //if (appData.debugMode) 
//    //  fprintf(debugFP, "Parsed PGNTag: %s\n", yy_text);
//    //err = ParsePGNTag(yy_text, &gameInfo);
//    //if (!err) numPGNTags++;
//
//    //if (gameInfo.fen != NULL) {
//    //  Board initial_position;
//    //  startedFromSetupPosition = TRUE;
//    //  if (!ParseFEN(initial_position, &blackPlaysFirst, gameInfo.fen)) {
//    //    Reset(TRUE, TRUE);
//    //    DisplayError("Bad FEN position in file", 0);
//    //    return FALSE;
//    //  }
//    //  CopyBoard(boards[0], initial_position);
//    //  if (blackPlaysFirst) {
//    //    currentMove = forwardMostMove = backwardMostMove = 1;
//    //    CopyBoard(boards[1], initial_position);
//    //    strcpy(moveList[0], "");
//    //    strcpy(parseList[0], "");
//    //    timeRemaining[0][1] = whiteTimeRemaining;
//    //    timeRemaining[1][1] = blackTimeRemaining;
//    //    if (commentList[0] != NULL) {
//    //      commentList[1] = commentList[0];
//    //      commentList[0] = NULL;
//    //    }
//    //  } else {
//    //    currentMove = forwardMostMove = backwardMostMove = 0;
//    //  }
//    //  yyboardindex = forwardMostMove;
//    //  free(gameInfo.fen);
//    //  gameInfo.fen = NULL;
//    //}
//
//    //yyboardindex = forwardMostMove;
//    //cm = (ChessMove) yylex();
//
//    ///* Handle comments interspersed among the tags */
//    //while (cm == Comment) {
//    //    char *p;
//    //    if (appData.debugMode) 
//    //      fprintf(debugFP, "Parsed Comment: %s\n", yy_text);
//    //    p = yy_text;
//    //    if (*p == '{' || *p == '[' || *p == '(') {
//    //	p[strlen(p) - 1] = NULLCHAR;
//    //	p++;
//    //    }
//    //    while (*p == '\n') p++;
//    //    AppendComment(currentMove, p);
//    //    yyboardindex = forwardMostMove;
//    //    cm = (ChessMove) yylex();
//    //}
//    //   }
//
//    //   /* don't rely on existence of Event tag since if game was
//    //    * pasted from clipboard the Event tag may not exist
//    //    */
//    //   if (numPGNTags > 0){
//    //       char *tags;
//    //if (gameInfo.variant == VariantNormal) {
//    //  gameInfo.variant = StringToVariant(gameInfo.event);
//    //}
//    //if (!matchMode) {
//    //  tags = PGNTags(&gameInfo);
//    //  TagsPopUp(tags, CmailMsg());
//    //  free(tags);
//    //}
//    //   } else {
//    ///* Make something up, but don't display it now */
//    //SetGameInfo();
//    //TagsPopDown();
//    //   }
//
//    //   if (cm == PositionDiagram) {
//    //int i, j;
//    //char *p;
//    //Board initial_position;
//
//    //if (appData.debugMode)
//    //  fprintf(debugFP, "Parsed PositionDiagram: %s\n", yy_text);
//
//    //if (!startedFromSetupPosition) {
//    //    p = yy_text;
//    //    for (i = BOARD_SIZE - 1; i >= 0; i--)
//    //      for (j = 0; j < BOARD_SIZE; p++)
//    //	switch (*p) {
//    //	  case '[':
//    //	  case '-':
//    //	  case ' ':
//    //	  case '\t':
//    //	  case '\n':
//    //	  case '\r':
//    //	    break;
//    //	  default:
//    //	    initial_position[i][j++] = CharToPiece(*p);
//    //	    break;
//    //	}
//    //    while (*p == ' ' || *p == '\t' ||
//    //	   *p == '\n' || *p == '\r') p++;
//    //
//    //    if (strncmp(p, "black", strlen("black"))==0)
//    //      blackPlaysFirst = TRUE;
//    //    else
//    //      blackPlaysFirst = FALSE;
//    //    startedFromSetupPosition = TRUE;
//    //
//    //    CopyBoard(boards[0], initial_position);
//    //    if (blackPlaysFirst) {
//    //	currentMove = forwardMostMove = backwardMostMove = 1;
//    //	CopyBoard(boards[1], initial_position);
//    //	strcpy(moveList[0], "");
//    //	strcpy(parseList[0], "");
//    //	timeRemaining[0][1] = whiteTimeRemaining;
//    //	timeRemaining[1][1] = blackTimeRemaining;
//    //	if (commentList[0] != NULL) {
//    //	    commentList[1] = commentList[0];
//    //	    commentList[0] = NULL;
//    //	}
//    //    } else {
//    //	currentMove = forwardMostMove = backwardMostMove = 0;
//    //    }
//    //}
//    //yyboardindex = forwardMostMove;
//    //cm = (ChessMove) yylex();
//    //   }
//
//    //   if (first.pr == NoProc) {
//    //StartChessProgram(&first);
//    //   }
//    //   InitChessProgram(&first);
//    //   SendToProgram("force\n", &first);
//    //   if (startedFromSetupPosition) {
//    //SendBoard(&first, forwardMostMove);
//    //DisplayBothClocks();
//    //   }      
//
//    //   while (cm == Comment) {
//    //char *p;
//    //if (appData.debugMode) 
//    //  fprintf(debugFP, "Parsed Comment: %s\n", yy_text);
//    //p = yy_text;
//    //if (*p == '{' || *p == '[' || *p == '(') {
//    //    p[strlen(p) - 1] = NULLCHAR;
//    //    p++;
//    //}
//    //while (*p == '\n') p++;
//    //AppendComment(currentMove, p);
//    //yyboardindex = forwardMostMove;
//    //cm = (ChessMove) yylex();
//    //   }
//
//    //   if ((cm == (ChessMove) 0 && lastLoadGameStart != (ChessMove) 0) ||
//    //cm == WhiteWins || cm == BlackWins ||
//    //cm == GameIsDrawn || cm == GameUnfinished) {
//    //DisplayMessage("", "No moves in game");
//    //if (cmailMsgLoaded) {
//    //    if (appData.debugMode)
//    //      fprintf(debugFP, "Setting flipView to %d.\n", FALSE);
//    //	    ClearHighlights();
//    //    flipView = FALSE;
//    //}
//    //DrawPosition(FALSE, boards[currentMove]);
//    //DisplayBothClocks();
//    //gameMode = EditGame;
//    //ModeHighlight();
//    //gameFileFP = NULL;
//    //cmailOldMove = 0;
//    //return TRUE;
//    //   }
//
//    //   if (commentList[currentMove] != NULL) {
//    //     if (!matchMode && (pausing || appData.timeDelay != 0)) {
//    //DisplayComment(currentMove - 1, commentList[currentMove]);
//    //     }
//    //   }
//    //   if (!matchMode && appData.timeDelay != 0) 
//    //     DrawPosition(FALSE, boards[currentMove]);
//
//    //   if (gameMode == AnalyzeFile || gameMode == AnalyzeMode) {
//    //     programStats.ok_to_send = 1;
//    //   }
//
//    //   /* if the first token after the PGN tags is a move
//    //    * and not move number 1, retrieve it from the parser 
//    //    */
//    //   if (cm != MoveNumberOne)
//    //LoadGameOneMove(cm);
//
//    //   /* load the remaining moves from the file */
//    //   while (LoadGameOneMove((ChessMove)0)) {
//    //     timeRemaining[0][forwardMostMove] = whiteTimeRemaining;
//    //     timeRemaining[1][forwardMostMove] = blackTimeRemaining;
//    //   }
//
//    //   /* rewind to the start of the game */
//    //   currentMove = backwardMostMove;
//
//    //   HistorySet(parseList, backwardMostMove, forwardMostMove, currentMove-1);
//
//    //   if (oldGameMode == AnalyzeFile ||
//    //oldGameMode == AnalyzeMode) {
//    //     AnalyzeFileEvent();
//    //   }
//
//    //   if (matchMode || appData.timeDelay == 0) {
//    //     ToEndEvent();
//    //     gameMode = EditGame;
//    //     ModeHighlight();
//    //   } else if (appData.timeDelay > 0) {
//    //     AutoPlayGameLoop();
//    //   }
//
//    //   if (appData.debugMode) 
//    //fprintf(debugFP, "LoadGame(): on exit, gameMode %d\n", gameMode);
//    return FALSE;
//}

/* Support for LoadNextPosition, LoadPreviousPosition, ReloadSamePosition */
//int
//ReloadPosition(int offset){
//    //int positionNumber = DIS.lastLoadPositionNumber + offset;
//    //if (DIS.lastLoadPositionFP == NULL) {
//    //    DisplayError("No position has been loaded yet", 0);
//    //    return FALSE;
//    //}
//    //if (positionNumber <= 0) {
//    //    DisplayError("Can't back up any further", 0);
//    //    return FALSE;
//    //}
//    //return LoadPosition(DIS.lastLoadPositionFP, positionNumber,
//    //    DIS.lastLoadPositionTitle);
//    return FALSE;
//}

/* Load the nth position from the given file */
//int
//LoadPositionFromFile(char *filename,int n,char *title){
//    FILE *f;
//    char buf[MSG_SIZ];
//
//    if (strcmp(filename, "-") == 0) {
//        return LoadPosition(stdin, n, "stdin");
//    } 
//    else {
//        //f = fopen(filename, "rb");
//        fopen_s(&f,filename,"rb");
//        if (f == NULL) {
//            //	    sprintf(buf, "Can't open \"%s\"", filename);
//            StringCbPrintf(buf,MSG_SIZ,"Can't open \"%s\"", filename);
//            DisplayError(buf, errno);
//            return FALSE;
//        } 
//        else {
//            return LoadPosition(f, n, title);
//        }
//    }
//}

/* Load the nth position from the given open file, and close it */
//int
//LoadPosition(FILE *f,int positionNumber,char *title)
//{
//    //   char *p, line[MSG_SIZ];
//    //   Board initial_position;
//    //   int i, j, fenMode, pn;
//    //   
//    //   if (gameMode == Training )
//    //SetTrainingModeOff();
//
//    //   if (gameMode != BeginningOfGame) {
//    //Reset(FALSE, TRUE);
//    //   }
//    //   if (lastLoadPositionFP != NULL && lastLoadPositionFP != f) {
//    //fclose(lastLoadPositionFP);
//    //   }
//    //   if (positionNumber == 0) positionNumber = 1;
//    //   lastLoadPositionFP = f;
//    //   lastLoadPositionNumber = positionNumber;
//    //   strcpy(lastLoadPositionTitle, title);
//    //   if (first.pr == NoProc) {
//    //     StartChessProgram(&first);
//    //     InitChessProgram(&first);
//    //   }    
//    //   pn = positionNumber;
//    //   if (positionNumber < 0) {
//    ///* Negative position number means to seek to that byte offset */
//    //if (fseek(f, -positionNumber, 0) == -1) {
//    //    DisplayError("Can't seek on position file", 0);
//    //    return FALSE;
//    //};
//    //pn = 1;
//    //   } else {
//    //if (fseek(f, 0, 0) == -1) {
//    //    if (f == lastLoadPositionFP ?
//    //	positionNumber == lastLoadPositionNumber + 1 :
//    //	positionNumber == 1) {
//    //	pn = 1;
//    //    } else {
//    //	DisplayError("Can't seek on position file", 0);
//    //	return FALSE;
//    //    }
//    //}
//    //   }
//    //   /* See if this file is FEN or old-style xboard */
//    //   if (fgets(line, MSG_SIZ, f) == NULL) {
//    //DisplayError("Position not found in file", 0);
//    //return FALSE;
//    //   }
//    //   switch (line[0]) {
//    //     case '#':  case 'x':
//    //     default:
//    //fenMode = FALSE;
//    //break;
//    //     case 'p':  case 'n':  case 'b':  case 'r':  case 'q':  case 'k':
//    //     case 'P':  case 'N':  case 'B':  case 'R':  case 'Q':  case 'K':
//    //     case '1':  case '2':  case '3':  case '4':  case '5':  case '6':
//    //     case '7':  case '8':
//    //fenMode = TRUE;
//    //break;
//    //   }
//
//    //   if (pn >= 2) {
//    //if (fenMode || line[0] == '#') pn--;
//    //while (pn > 0) {
//    //    /* skip postions before number pn */
//    //    if (fgets(line, MSG_SIZ, f) == NULL) {
//    //        Reset(TRUE, TRUE);
//    //	DisplayError("Position not found in file", 0);
//    //	return FALSE;
//    //    }
//    //    if (fenMode || line[0] == '#') pn--;
//    //}
//    //   }
//
//    //   if (fenMode) {
//    //if (!ParseFEN(initial_position, &blackPlaysFirst, line)) {
//    //    DisplayError("Bad FEN position in file", 0);
//    //    return FALSE;
//    //}
//    //   } else {
//    //(void) fgets(line, MSG_SIZ, f);
//    //(void) fgets(line, MSG_SIZ, f);
//    //   
//    //for (i = BOARD_SIZE - 1; i >= 0; i--) {
//    //    (void) fgets(line, MSG_SIZ, f);
//    //    for (p = line, j = 0; j < BOARD_SIZE; p++) {
//    //	if (*p == ' ')
//    //	  continue;
//    //	initial_position[i][j++] = CharToPiece(*p);
//    //    }
//    //}
//    //   
//    //blackPlaysFirst = FALSE;
//    //if (!feof(f)) {
//    //    (void) fgets(line, MSG_SIZ, f);
//    //    if (strncmp(line, "black", strlen("black"))==0)
//    //      blackPlaysFirst = TRUE;
//    //}
//    //   }
//    //   startedFromSetupPosition = TRUE;
//    //   
//    //   SendToProgram("force\n", &first);
//    //   CopyBoard(boards[0], initial_position);
//    //   if (blackPlaysFirst) {
//    //currentMove = forwardMostMove = backwardMostMove = 1;
//    //strcpy(moveList[0], "");
//    //strcpy(parseList[0], "");
//    //CopyBoard(boards[1], initial_position);
//    //DisplayMessage("", "Black to play");
//    //   } else {
//    //currentMove = forwardMostMove = backwardMostMove = 0;
//    //DisplayMessage("", "White to play");
//    //   }
//    //   SendBoard(&first, forwardMostMove);
//
//    //   if (positionNumber > 1) {
//    //sprintf(line, "%s %d", title, positionNumber);
//    //DisplayTitle(line);
//    //   } else {
//    //DisplayTitle(title);
//    //   }
//    //   gameMode = EditGame;
//    //   ModeHighlight();
//    //   ResetClocks();
//    //   timeRemaining[0][1] = whiteTimeRemaining;
//    //   timeRemaining[1][1] = blackTimeRemaining;
//    //   DrawPosition(FALSE, boards[currentMove]);
//
//    return TRUE;
//}

