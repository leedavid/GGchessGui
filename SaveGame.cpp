#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"
//
//char *
//SavePart(char *str){
//    static char buf[MSG_SIZ];
//    char *p;
//
//    p = strchr(str, ' ');
//    if (p == NULL){
//        return str;
//    }
//    //strncpy(buf, str, p - str);
//    strncpy_s(buf,MSG_SIZ,str,p-str);
//    buf[p - str] = NULLCHAR;
//    return buf;
//}

//int  /* Save the current game to the given file */
//SaveGameToFile(char *filename,int append){
//    FILE *f;
//    char buf[MSG_SIZ];
//
//    if (strcmp(filename, "-") == 0) {
//        return SaveGame(stdout, 0, NULL);
//    } 
//    else {
//        //f = fopen(filename, append ? "a" : "w");
//        fopen_s(&f,filename,append ? "a" : "w");
//        if (f == NULL) {
//            //	    sprintf(buf, "Can't open \"%s\"", filename);
//            StringCbPrintf(buf,MSG_SIZ,"Can't open \"%s\"", filename);
//            DisplayError(buf, errno);
//            return FALSE;
//        } 
//        else {
//            return SaveGame(f, 0, NULL);
//        }
//    }
//}





/* Save game in PGN style and close the file */
int
SaveGamePGN(FILE *f){

    return false;
    //int i, offset, linelen, newblock;
    //time_t tm;
    //char *movetext;
    //char numtext[32];
    //int movelen, numlen, blank;

    //tm = time((time_t *) NULL);

    //PrintPGNTags(f, &DIS.GGQJ);

    //if (DIS.backwardMostMove > 0 || DIS.startedFromSetupPosition) {
    //    char fen[MSG_SIZ];
    //    PositionToFEN(fen,DIS.backwardMostMove,DIS.ucci);
    //    fprintf(f, "[FEN \"%s\"]\n[SetUp \"1\"]\n", fen);
    //    fprintf(f, "\n{--------------\n");
    //    PrintPosition(f, DIS.backwardMostMove);
    //    fprintf(f, "--------------}\n");
    //    //free(fen);
    //} 
    //else {
    //    fprintf(f, "\n");
    //}

    //i = DIS.backwardMostMove;
    //offset = DIS.backwardMostMove & (~1L); /* output move numbers start at 1 */
    //linelen = 0;
    //newblock = TRUE;

    //while (i < DIS.forwardMostMove) {
    //    /* Print comments preceding this move */
    //    //if (DIS.commentList[i] != NULL) {
    //    //	if (linelen > 0) fprintf(f, "\n");
    //    //	fprintf(f, "{\n%s}\n", DIS.commentList[i]);
    //    //	linelen = 0;
    //    //	newblock = TRUE;
    //    //}

    //    /* Format move number */
    //    if ((i % 2) == 0) {
    //        //sprintf(numtext, "%d.", (i - offset)/2 + 1);
    //        StringCbPrintf(numtext,sizeof(numtext),"%d.", (i - offset)/2 + 1);
    //    } 
    //    else {
    //        if (newblock) {
    //            //sprintf(numtext, "%d...", (i - offset)/2 + 1);
    //            StringCbPrintf(numtext,sizeof(numtext),"%d...", (i - offset)/2 + 1);
    //        } 
    //        else {
    //            numtext[0] = NULLCHAR;
    //        }
    //    }
    //    numlen = (int)strlen(numtext);
    //    newblock = FALSE;

    //    /* Print move number */
    //    blank = linelen > 0 && numlen > 0;
    //    if (linelen + (blank ? 1 : 0) + numlen > PGN_MAX_LINE) {
    //        fprintf(f, "\n");
    //        linelen = 0;
    //        blank = 0;
    //    }
    //    if (blank) {
    //        fprintf(f, " ");
    //        linelen++;
    //    }
    //    fprintf(f, numtext);
    //    linelen += numlen;

    //    /* Get move */
    //    movetext = SavePart(DIS.parseList[i]);
    //    movelen = (int)strlen(movetext);

    //    /* Print move */
    //    blank = linelen > 0 && movelen > 0;
    //    if (linelen + (blank ? 1 : 0) + movelen > PGN_MAX_LINE) {
    //        fprintf(f, "\n");
    //        linelen = 0;
    //        blank = 0;
    //    }
    //    if (blank) {
    //        fprintf(f, " ");
    //        linelen++;
    //    }
    //    fprintf(f, movetext);
    //    linelen += movelen;

    //    i++;
    //}

    ///* Start a new line */
    //if (linelen > 0) fprintf(f, "\n");

    ///* Print comments after last move */
    ////if (DIS.commentList[i] != NULL) {
    ////	fprintf(f, "{\n%s}\n", DIS.commentList[i]);
    ////}

    ///* Print result */
    ////if (DIS.gameInfo.resultDetails != NULL &&
    ////	DIS.gameInfo.resultDetails[0] != NULLCHAR) {
    //if(DIS.GGQJ.resultDetails[0] != NULLCHAR){
    //    fprintf(f, "{%s} %s\n\n", DIS.GGQJ.resultDetails,PGNResult(DIS.GGQJ.cmresult));
    //} 
    //else {
    //    fprintf(f, "%s\n\n", PGNResult(DIS.GGQJ.cmresult));
    //}

    //fclose(f);
    //return TRUE;
}


/* Save the current game to open file f and close the file */
int
SaveGame(FILE *f,int dummy,char *dummy2){
    //if (DIS.gameMode == EditPosition){
    //    EditPositionDone();
    //}
    //return SaveGamePGN(f);   
    return FALSE;
}

/* Save the current position to the given file */
int
SavePositionToFile(char *filename){
    //FILE *f;
    //char buf[MSG_SIZ];

    //if (strcmp(filename, "-") == 0) {
    //    return SavePosition(stdout, 0, NULL);
    //} else {
    //    //f = fopen(filename, "a");
    //    fopen_s(&f,filename,"a");
    //    if (f == NULL) {
    //        //  sprintf(buf, "Can't open \"%s\"", filename);
    //        StringCbPrintf(buf,MSG_SIZ,"Can't open \"%s\"", filename);
    //        DisplayError(buf, errno);
    //        return FALSE;
    //    } else {
    //        SavePosition(f, 0, NULL);
    //        return TRUE;
    //    }
    //}
    return FALSE;
}

/* Save the current position to the given open file and close the file */
int
SavePosition(FILE *f,int dummy,char *dummy2){
    //time_t tm;
    //char fen[MSG_SIZ];
    //char buf[MSG_SIZ];
    //if (appData.oldSaveStyle) {
    //    tm = time((time_t *) NULL);

    //    //fprintf(f, "# %s position file -- %s", DIS.programName, ctime(&tm));
    //    ctime_s(buf,MSG_SIZ,&tm);
    //    fprintf(f, "# %s position file -- %s", DIS.programName, buf);

    //    PrintOpponents(f);
    //    fprintf(f, "[--------------\n");
    //    PrintPosition(f, DIS.currentMove);
    //    fprintf(f, "--------------]\n");
    //} 
    //else {
    /*PositionToFEN(fen,DIS.currentMove,UCCI_UCCI);*/
    //PositionToFEN(fen,DIS.pos.curStep,UCCI_UCCI162);
    //fprintf(f, "%s\n", fen);
    ////free(fen);
    ////}
    //fclose(f);
    return TRUE;
}
