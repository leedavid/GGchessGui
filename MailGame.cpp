#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

/* Wrapper around LoadGame for use when a Cmail message is loaded */
//int
//CmailLoadGame(FILE *f,int gameNumber,char *title,int useList){
//    int retVal;
//
//    if (gameNumber > DIS.nCmailGames) {
//        DisplayError("No more games in this message", 0);
//        return FALSE;
//    }
//    if (f == DIS.lastLoadGameFP) {
//        int offset = gameNumber - DIS.lastLoadGameNumber;
//        if (offset == 0) {
//            DIS.cmailMsg[0] = NULLCHAR;
//            if (DIS.cmailMoveRegistered[DIS.lastLoadGameNumber - 1]) {
//                DIS.cmailMoveRegistered[DIS.lastLoadGameNumber - 1] = FALSE;
//                DIS.nCmailMovesRegistered--;
//            }
//            DIS.cmailMoveType[DIS.lastLoadGameNumber - 1] = CMAIL_MOVE;
//            if (DIS.cmailResult[DIS.lastLoadGameNumber - 1] == CMAIL_NEW_RESULT) {
//                DIS.cmailResult[DIS.lastLoadGameNumber - 1] = CMAIL_NOT_RESULT;
//            }
//        } else {
//            if (! RegisterMove()) return FALSE;
//        }
//    }
//
//    retVal = LoadGame(f, gameNumber, title, useList);
//
//    /* Make move registered during previous look at this game, if any */
//    MakeRegisteredMove();
//
//    if (DIS.cmailCommentList[DIS.lastLoadGameNumber - 1] != NULL) {
//        //DIS.commentList[DIS.currentMove]
//        //= StrSave(DIS.cmailCommentList[DIS.lastLoadGameNumber - 1]);
//        //DisplayComment(DIS.currentMove - 1, DIS.commentList[DIS.currentMove]);
//    }
//
//    return retVal;
//}
//void
//CmailSigHandlerCallBack(InputSourceRef isr, VOIDSTAR closure,
//			char *buf, int count, int error)
//{
//  DisplayFatalError("Not implemented", 0, 1);
//}


//void
//MakeRegisteredMove(void){
    //    int fromX, fromY, toX, toY;
    //    char promoChar;
    //    if (cmailMoveRegistered[lastLoadGameNumber - 1]) {
    //	switch (cmailMoveType[lastLoadGameNumber - 1]) {
    //	  case CMAIL_MOVE:
    //	  case CMAIL_DRAW:
    //	    if (appData.debugMode)
    //	      fprintf(debugFP, "Restoring %s for game %d\n",
    //		      cmailMove[lastLoadGameNumber - 1], lastLoadGameNumber);
    //    
    //	    thinkOutput[0] = NULLCHAR;
    ////	    strcpy(moveList[currentMove], cmailMove[lastLoadGameNumber - 1]);
    //	    fromX = cmailMove[lastLoadGameNumber - 1][0] - 'a';
    //	    fromY = cmailMove[lastLoadGameNumber - 1][1] - '1';
    //	    toX = cmailMove[lastLoadGameNumber - 1][2] - 'a';
    //	    toY = cmailMove[lastLoadGameNumber - 1][3] - '1';
    //	    promoChar = cmailMove[lastLoadGameNumber - 1][4];
    //	    MakeMove(fromX, fromY, toX, toY, promoChar);
    //	    ShowMove(fromX, fromY, toX, toY);
    //	      
    //	    switch (MateTest(boards[currentMove], PosFlags(currentMove),
    //			     EP_UNKNOWN)) {
    //	      case MT_NONE:
    //	      case MT_CHECK:
    //		break;
    //    		
    //	      case MT_CHECKMATE:
    //		if (WhiteOnMove(currentMove)) {
    //		    GameEnds(BlackWins, "Black mates", GE_PLAYER);
    //		} else {
    //		    GameEnds(WhiteWins, "White mates", GE_PLAYER);
    //		}
    //		break;
    //    		
    //	      case MT_STALEMATE:
    //		GameEnds(GameIsDrawn, "Stalemate", GE_PLAYER);
    //		break;
    //	    }
    //
    //	    break;
    //	    
    //	  case CMAIL_RESIGN:
    //	    if (WhiteOnMove(currentMove)) {
    //		GameEnds(BlackWins, "White resigns", GE_PLAYER);
    //	    } else {
    //		GameEnds(WhiteWins, "Black resigns", GE_PLAYER);
    //	    }
    //	    break;
    //	    
    //	  case CMAIL_ACCEPT:
    //	    GameEnds(GameIsDrawn, "Draw agreed", GE_PLAYER);
    //	    break;
    //	      
    //	  default:
    //	    break;
    //	}
    //    }
    //
    //    return;
//}
//
//void
//ReloadCmailMsgEvent(int unregister)
//{
    //#if !WIN32
    //    static char *inFilename = NULL;
    //    static char *outFilename;
    //    int i;
    //    struct stat inbuf, outbuf;
    //    int status;
    //    
    //    /* Any registered moves are unregistered if unregister is set, */
    //    /* i.e. invoked by the signal handler */
    //    if (unregister) {
    //	for (i = 0; i < CMAIL_MAX_GAMES; i ++) {
    //	    cmailMoveRegistered[i] = FALSE;
    //	    if (cmailCommentList[i] != NULL) {
    //		free(cmailCommentList[i]);
    //		cmailCommentList[i] = NULL;
    //	    }
    //	}
    //	nCmailMovesRegistered = 0;
    //    }
    //
    //    for (i = 0; i < CMAIL_MAX_GAMES; i ++) {
    //	cmailResult[i] = CMAIL_NOT_RESULT;
    //    }
    //    nCmailResults = 0;
    //
    //    if (inFilename == NULL) {
    //	/* Because the filenames are static they only get malloced once  */
    //	/* and they never get freed                                      */
    //	inFilename = (char *) malloc(strlen(appData.cmailGameName) + 9);
    //	sprintf(inFilename, "%s.game.in", appData.cmailGameName);
    //
    //	outFilename = (char *) malloc(strlen(appData.cmailGameName) + 5);
    //	sprintf(outFilename, "%s.out", appData.cmailGameName);
    //    }
    //    
    //    status = stat(outFilename, &outbuf);
    //    if (status < 0) {
    //	cmailMailedMove = FALSE;
    //    } else {
    //	status = stat(inFilename, &inbuf);
    //	cmailMailedMove = (inbuf.st_mtime < outbuf.st_mtime);
    //    }
    //    
    //    /* LoadGameFromFile(CMAIL_MAX_GAMES) with cmailMsgLoaded == TRUE
    //       counts the games, notes how each one terminated, etc.
    //       
    //       It would be nice to remove this kludge and instead gather all
    //       the information while building the game list.  (And to keep it
    //       in the game list nodes instead of having a bunch of fixed-size
    //       parallel arrays.)  Note this will require getting each game's
    //       termination from the PGN tags, as the game list builder does
    //       not process the game moves.  --mann
    //       */
    //    cmailMsgLoaded = TRUE;
    //    LoadGameFromFile(inFilename, CMAIL_MAX_GAMES, "", FALSE);
    //    
    //    /* Load first game in the file or popup game menu */
    //    LoadGameFromFile(inFilename, 0, appData.cmailGameName, TRUE);
    //
    //#endif /* !WIN32 */
//    return;
//}
//int
//RegisterMove()
//{
    //   FILE *f;
    //   char string[MSG_SIZ];

    //   if (   cmailMailedMove
    //|| (cmailResult[lastLoadGameNumber - 1] == CMAIL_OLD_RESULT)) {
    //return TRUE;		/* Allow free viewing  */
    //   }

    //   /* Unregister move to ensure that we don't leave RegisterMove        */
    //   /* with the move registered when the conditions for registering no   */
    //   /* longer hold                                                       */
    //   if (cmailMoveRegistered[lastLoadGameNumber - 1]) {
    //cmailMoveRegistered[lastLoadGameNumber - 1] = FALSE;
    //nCmailMovesRegistered --;

    //if (cmailCommentList[lastLoadGameNumber - 1] != NULL) 
    //  {
    //      free(cmailCommentList[lastLoadGameNumber - 1]);
    //      cmailCommentList[lastLoadGameNumber - 1] = NULL;
    //  }
    //   }

    //   if (cmailOldMove == -1) {
    //DisplayError("You have edited the game history.\nUse Reload Same Game and make your move again.", 0);
    //return FALSE;
    //   }

    //   if (currentMove > cmailOldMove + 1) {
    //DisplayError("You have entered too many moves.\nBack up to the correct position and try again.", 0);
    //return FALSE;
    //   }

    //   if (currentMove < cmailOldMove) {
    //DisplayError("Displayed position is not current.\nStep forward to the correct position and try again.", 0);
    //return FALSE;
    //   }

    //   if (forwardMostMove > currentMove) {
    ///* Silently truncate extra moves */
    //TruncateGame();
    //   }

    //   if (   (currentMove == cmailOldMove + 1)
    //|| (   (currentMove == cmailOldMove)
    //    && (   (cmailMoveType[lastLoadGameNumber - 1] == CMAIL_ACCEPT)
    //	|| (cmailMoveType[lastLoadGameNumber - 1] == CMAIL_RESIGN)))) {
    //if (gameInfo.result != GameUnfinished) {
    //    cmailResult[lastLoadGameNumber - 1] = CMAIL_NEW_RESULT;
    //}

    //if (commentList[currentMove] != NULL) {
    //    cmailCommentList[lastLoadGameNumber - 1]
    //      = StrSave(commentList[currentMove]);
    //}
    //strcpy(cmailMove[lastLoadGameNumber - 1], moveList[currentMove - 1]);

    //if (appData.debugMode)
    //  fprintf(debugFP, "Saving %s for game %d\n",
    //	  cmailMove[lastLoadGameNumber - 1], lastLoadGameNumber);

    //sprintf(string,
    //	"%s.game.out.%d", appData.cmailGameName, lastLoadGameNumber);
    //
    //f = fopen(string, "w");
    //if (appData.oldSaveStyle) {
    //    SaveGameOldStyle(f); /* also closes the file */
    //    
    //    sprintf(string, "%s.pos.out", appData.cmailGameName);
    //    f = fopen(string, "w");
    //    SavePosition(f, 0, NULL); /* also closes the file */
    //} else {
    //    fprintf(f, "{--------------\n");
    //    PrintPosition(f, currentMove);
    //    fprintf(f, "--------------}\n\n");
    //    
    //    SaveGame(f, 0, NULL); /* also closes the file*/
    //}
    //
    //cmailMoveRegistered[lastLoadGameNumber - 1] = TRUE;
    //nCmailMovesRegistered ++;
    //   } else if (nCmailGames == 1) {
    //DisplayError("You have not made a move yet", 0);
    //return FALSE;
    //   }

//    return TRUE;
//}
//
//void
//MailMoveEvent()
//{
    //#if !WIN32
    //    static char *partCommandString = "cmail -xv%s -remail -game %s 2>&1";
    //    FILE *commandOutput;
    //    char buffer[MSG_SIZ], msg[MSG_SIZ], string[MSG_SIZ];
    //    int nBytes = 0;		/*  Suppress warnings on uninitialized variables    */
    //    int nBuffers;
    //    int i;
    //    int archived;
    //    char *arcDir;
    //
    //    if (! cmailMsgLoaded) {
    //	DisplayError("The cmail message is not loaded.\nUse Reload CMail Message and make your move again.", 0);
    //	return;
    //    }
    //
    //    if (nCmailGames == nCmailResults) {
    //	DisplayError("No unfinished games", 0);
    //	return;
    //    }
    //
    //#if CMAIL_PROHIBIT_REMAIL
    //    if (cmailMailedMove) {
    //	sprintf(msg, "You have already mailed a move.\nWait until a move arrives from your opponent.\nTo resend the same move, type\n\"cmail -remail -game %s\"\non the command line.", appData.cmailGameName);
    //	DisplayError(msg, 0);
    //	return;
    //    }
    //#endif
    //
    //    if (! (cmailMailedMove || RegisterMove())) return;
    //    
    //    if (   cmailMailedMove
    //	|| (nCmailMovesRegistered + nCmailResults == nCmailGames)) {
    //	sprintf(string, partCommandString,
    //		appData.debugMode ? " -v" : "", appData.cmailGameName);
    //	commandOutput = popen(string, "rb");
    //
    //	if (commandOutput == NULL) {
    //	    DisplayError("Failed to invoke cmail", 0);
    //	} else {
    //	    for (nBuffers = 0; (! feof(commandOutput)); nBuffers ++) {
    //		nBytes = fread(buffer, 1, MSG_SIZ - 1, commandOutput);
    //	    }
    //	    if (nBuffers > 1) {
    //		(void) memcpy(msg, buffer + nBytes, MSG_SIZ - nBytes - 1);
    //		(void) memcpy(msg + MSG_SIZ - nBytes - 1, buffer, nBytes);
    //		nBytes = MSG_SIZ - 1;
    //	    } else {
    //		(void) memcpy(msg, buffer, nBytes);
    //	    }
    //	    *(msg + nBytes) = '\0'; /* \0 for end-of-string*/
    //
    //	    if(StrStr(msg, "Mailed cmail message to ") != NULL) {
    //		cmailMailedMove = TRUE; /* Prevent >1 moves    */
    //
    //		archived = TRUE;
    //		for (i = 0; i < nCmailGames; i ++) {
    //		    if (cmailResult[i] == CMAIL_NOT_RESULT) {
    //			archived = FALSE;
    //		    }
    //		}
    //		if (   archived
    //		    && (   (arcDir = (char *) getenv("CMAIL_ARCDIR"))
    //			!= NULL)) {
    //		    sprintf(buffer, "%s/%s.%s.archive",
    //			    arcDir,
    //			    appData.cmailGameName,
    //			    gameInfo.date);
    //		    LoadGameFromFile(buffer, 1, buffer, FALSE);
    //		    cmailMsgLoaded = FALSE;
    //		}
    //	    }
    //
    //	    DisplayInformation(msg);
    //	    pclose(commandOutput);
    //	}
    //    } else {
    //	if ((*cmailMsg) != '\0') {
    //	    DisplayInformation(cmailMsg);
    //	}
    //    }
    //
    //    return;
    //#endif /* !WIN32 */
//}
//
//char *
//CmailMsg(void){
//#if WIN32
//    return NULL;
//#else
//    int  prependComma = 0;
//    char number[5];
//    char string[MSG_SIZ];	/* Space for game-list */
//    int  i;
//
//    if (!cmailMsgLoaded) return "";
//
//    if (cmailMailedMove) {
//        sprintf(cmailMsg, "Waiting for reply from opponent\n");
//    } else {
//        /* Create a list of games left */
//        sprintf(string, "[");
//        for (i = 0; i < nCmailGames; i ++) {
//            if (! (   cmailMoveRegistered[i]
//            || (cmailResult[i] == CMAIL_OLD_RESULT))) {
//                if (prependComma) {
//                    sprintf(number, ",%d", i + 1);
//                } else {
//                    sprintf(number, "%d", i + 1);
//                    prependComma = 1;
//                }
//
//                strcat(string, number);
//            }
//        }
//        strcat(string, "]");
//
//        if (nCmailMovesRegistered + nCmailResults == 0) {
//            switch (nCmailGames) {
//          case 1:
//              sprintf(cmailMsg,
//                  "Still need to make move for game\n");
//              break;
//
//          case 2:
//              sprintf(cmailMsg,
//                  "Still need to make moves for both games\n");
//              break;
//
//          default:
//              sprintf(cmailMsg,
//                  "Still need to make moves for all %d games\n",
//                  nCmailGames);
//              break;
//            }
//        } else {
//            switch (nCmailGames - nCmailMovesRegistered - nCmailResults) {
//          case 1:
//              sprintf(cmailMsg,
//                  "Still need to make a move for game %s\n",
//                  string);
//              break;
//
//          case 0:
//              if (nCmailResults == nCmailGames) {
//                  sprintf(cmailMsg, "No unfinished games\n");
//              } else {
//                  sprintf(cmailMsg, "Ready to send mail\n");
//              }
//              break;
//
//          default:
//              sprintf(cmailMsg,
//                  "Still need to make moves for games %s\n",
//                  string);
//            }
//        }
//    }
//    return cmailMsg;
//#endif /* WIN32 */
//}
//



