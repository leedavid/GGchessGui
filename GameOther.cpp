#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

void
TruncateGame(dispboard_t* pDis){  //截平
    /*if (DIS.forwardMostMove > DIS.currentMove) {*/
    if (pDis->pos->gply > pDis->pos->curStep) {
        //if (DIS.gameInfo.resultDetails != NULL) {
        //	free(DIS.gameInfo.resultDetails);
        //	DIS.gameInfo.resultDetails = NULL;
        //	DIS.gameInfo.result = GameUnfinished;
        //}
        //DIS.pgn.resultDetails[0] = NULLCHAR;
        //DIS.pgn.cmresult = GameUnfinished;
        pDis->pgn->isFinish = GameUnfinished;
        //DIS.forwardMostMove = DIS.currentMove;
        pDis->pos->gply = pDis->pos->curStep;
        //HistorySet(DIS.parseList, DIS.backwardMostMove, DIS.forwardMostMove,
        //	DIS.currentMove-1);
    }
}

void           //更换注解
ReplaceComment(int index,char *text){
    int len;

    while (*text == '\n'){
        text++;
    }
    len = (int)strlen(text);
    while (len > 0 && text[len - 1] == '\n'){
        len--;
    }

    //	if (DIS.commentList[index] != NULL){
    //		free(DIS.commentList[index]);
    //	}

    //	if (len == 0) {
    //		DIS.commentList[index] = NULL;
    //		return;
    //	}
    //	DIS.commentList[index] = (char *) malloc(len + 2);
    //strncpy(DIS.commentList[index], text, len);
    //DIS.commentList[index][len] = '\n';
    //DIS.commentList[index][len + 1] = NULLCHAR;
}

void
CrushCRs(char *text){
    char *p = text;
    char *q = text;
    char ch;

    do {
        ch = *p++;
        if (ch == '\r') continue;
        *q++ = ch;
    } while (ch != '\0');
}

void            //加入棋步的注解
AppendComment(int index,char *text){  
    //	int oldlen, len;
    //	char *old;

    //CrushCRs(text);					//去掉回车键
    //while (*text == '\n'){			//去掉前面的换行
    //	text++;
    //}
    //len = (int)strlen(text);
    //while (len > 0 && text[len - 1] == '\n'){
    //	len--;
    //}//去掉后面的换行

    //if (len == 0){
    //	return;		//没有内容哇
    //}

    //if (DIS.commentList[index] != NULL) {
    //	old = DIS.commentList[index];
    //	oldlen = (int)strlen(old);
    //	DIS.commentList[index] = (char *) malloc(oldlen + len + 2);
    //	//strcpy(commentList[index], old);
    //	StringCbCopy(DIS.commentList[index],(oldlen + len ), old);
    //	free(old);
    //	strncpy(&DIS.commentList[index][oldlen], text, len);
    //	DIS.commentList[index][oldlen + len] = '\n';
    //	DIS.commentList[index][oldlen + len + 1] = NULLCHAR;
    //} 
    //else {
    //	DIS.commentList[index] = (char *) malloc(len + 2);
    //	strncpy(DIS.commentList[index], text, len);
    //	DIS.commentList[index][len] = '\n';
    //	DIS.commentList[index][len + 1] = NULLCHAR;
    //}
}