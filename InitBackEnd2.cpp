#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

void     //第二步初始化
InitBackEnd2(dispboard_t *pDis){

#ifdef DEBUG_MODE
    //if (appData.debugMode) {
        //fprintf(appData.debugFP, "%s\n", MAIN.programVersion);
    //}
#endif


    GameReset(pDis, TRUE, FALSE,TRUE);
   /* if (appData.noChessProgram || DIS.first.protocolVersion == 1) {*/
    //if (pDis->noChessProgram ) {
    //    InitBackEnd3(pDis);     //没有象棋程序
    //} 
    //else {
        /* kludge: allow timeout for initial "feature" commands */
        FreezeUI();
        //DisplayMessage(pDis,"", MAIN.programVersion);
        //DisplayMessage(pDis,"", "Starting chess program");
		LogOut(_T("正在加载象棋引擎..."));
        ScheduleDelayedEvent(pDis,(DelayedEventCallback)InitBackEnd3, FEATURE_TIMEOUT);		//延时初始化第三步
        //ScheduleDelayedEvent(InitBackEnd3, 5000);		//延时初始化第三步
    //}
}



