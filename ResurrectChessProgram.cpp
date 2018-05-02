#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"


/* Assumes program was just initialized (initString sent).
Leaves program in force mode. */

void
ResurrectChessProgram(void){//引擎可能已退出,如果退出了
    ///* The chess program may have exited.
    //If so, restart it and feed it all the moves made so far. */

    //if (appData.noChessProgram || DIS.first.pr != NoProc){
    //    return;
    //}

    //StartChessProgram(&DIS.first);

    //InitChessProgram(&DIS.first);

    ///*FeedMovesToProgram(&DIS.first, DIS.currentMove);*/

    //FeedMovesToProgram(&DIS.first, DIS.pos.curStep);

    //if (!DIS.first.sendTime) {
    //    /* can't tell gnuchess what its clock should read,
    //    so we bow to its notion. */
    //    ResetClocks();
    //    DIS.timeRemaining[0][DIS.pos.curStep] = DIS.whiteTimeRemaining;
    //    DIS.timeRemaining[1][DIS.pos.curStep] = DIS.blackTimeRemaining;
    //}

    //switch(pDis->first.ucci){
    //    case UCCI_UCCI162:         //重新发送
    //        break;
    //    case UCCI_CYC105:
    //        break;
    //    case UCCI_QH:
    //        break;
    //    case UCCI_DIS:			//如果是分析状态哇
    //        ///* The chess program may have exited.
    //        //If so, restart it and feed it all the moves made so far. */

    //        //if (appData.noChessProgram || pDis->first.pr != NoProc){
    //        //    return;
    //        //}

    //        //StartChessProgram(&pDis->first);

    //        //InitChessProgram(&pDis->first);

    //        ///*FeedMovesToProgram(&DIS.first, DIS.currentMove);*/

    //        //FeedMovesToProgram(&pDis->first, pDis->pos.curStep);

    //        //if (!pDis->first.sendTime) {
    //        //    /* can't tell gnuchess what its clock should read,
    //        //    so we bow to its notion. */
    //        //    ResetClocks(DIS);
    //        //    pDis->timeRemaining[0][pDis->pos.curStep] = pDis->whiteTimeRemaining;
    //        //    pDis->timeRemaining[1][pDis->pos.curStep] = pDis->blackTimeRemaining;
    //        //}
    //        //if ((pDis->gameMode == AnalyzeMode || pDis->gameMode == AnalyzeFile) 
    //        //    &&	pDis->first.analysisSupport) {
    //        //    SendToProgram("analyze\n", &pDis->first);
    //        //    pDis->first.analyzing = TRUE;
    //        //}
    //        break;
    //    case UCCI_OTHER:
    //        break;
    //    default:
    //        break;
    //}
}
