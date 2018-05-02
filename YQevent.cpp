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

//void SetGameModeByDisCps(void){
//        //if(now->playWhat != NEUTRAL && other->playWhat != NEUTRAL){
//    //    DIS.gameMode = TwoMachinesPlay;
//    //}
//    //else{
//    //    if(now->playWhat == BLACK){
//    //        DIS.gameMode = 
//    //    }
//    //}
//    if(DIS.first.playWhat != NEUTRAL && DIS.second.playWhat != NEUTRAL){
//        DIS.gameMode = TwoMachinesPlay;
//    }
//    else{
//        if(DIS.first.playWhat == WHITE || DIS.second.playWhat == WHITE){
//            DIS.gameMode = MachinePlaysWhite;
//        }
//        else if(DIS.first.playWhat == BLACK || DIS.second.playWhat == BLACK){
//            DIS.gameMode = MachinePlaysBlack;
//        }
//        else{
//            DIS.gameMode = EditGame;
//        }
//    }
//}

void        //设定CPS走那方
SetCpsPlayWhat(ChessProgramState* now){

    dispboard_t* pDis = OBS[now->table];

    now->playWhat = NEUTRAL;
    //共三个CPS, 红,黑,ICS,
    if(pDis->ics.playWhat == NEUTRAL){      //ICS还没设定走棋
        //if(now->other->playWhat == WHITE){
        //}
        //else if(now->other->playWhat == BLACK){
        //}
        switch(now->other->playWhat){
            case WHITE:
                now->playWhat = BLACK;
                break;
            case BLACK:
                now->playWhat = WHITE;
                break;
            default:
                now->playWhat = pDis->pos->side;
                break;
        }
    }
    else{                                   //已经ICS登录了,并已确认了CPS的走方
        if(pDis->ics.playWhat == WHITE){
            if(now->other->playWhat != WHITE){
                now->playWhat = WHITE;
            }
        }
        else if(pDis->ics.playWhat == BLACK){
            if(now->other->playWhat == BLACK){
                now->playWhat = BLACK;
            }
        }
    }

    //
    //LogOut(
    LogOut(now->UCCI_path);
    LogOut(now->UCCI_file);
    LogOut(now->UCCI_name);
    switch(now->playWhat){
        case WHITE:
            LogOut("走红方\n");
            break;
        case BLACK:
            LogOut("走黑方\n");
            break;
        default:
            LogOut("不能确认走那方,请确认操作!\n");
            break;
    }

    pDis->gameMode = EditGame;

    //设定当前的GAMEMODE
    if(pDis->ics.playWhat != NEUTRAL){
    }
    else{
        if(pDis->first.playWhat == NEUTRAL){
            if(pDis->second.playWhat == BLACK){
                pDis->gameMode = MachinePlaysBlack;
            }
            else if(pDis->second.playWhat == WHITE){
                pDis->gameMode = MachinePlaysWhite;
            }
        }
        else if(pDis->second.playWhat == NEUTRAL){
            if(pDis->first.playWhat == BLACK){
                pDis->gameMode = MachinePlaysBlack;
            }
            else if(pDis->first.playWhat == WHITE){
                pDis->gameMode = MachinePlaysWhite;
            }
        }
        else{
            pDis->gameMode = TwoMachinesPlay;
        }
    }

    //if(now->playWhat == NEUTRAL){       //再看一下能不能走棋
    //    return;
    //}
}

//void //计算机能不能走一步
//IsComputerCanGo(ChessProgramState* now){
        
    //char buf[MSG_SIZ];

    

    //ChessProgramState* other;

    //if(now->UCCI_initDone == 0){
    //    LogOut("不能加载引擎,请重新设置引擎\n");
    //    if(now->UCCI_which == 1){
    //        SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_COM_RED, 0);
    //    }
    //    else{
    //        SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_COM_BLUE, 0);
    //    }  
    //    return;
    //}

    //if(now == &DIS.first){
    //    other = &DIS.second;
    //}
    //else{
    //    other = &DIS.first;
    //}

    //if(now->playWhat == NEUTRAL){
    //    //SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_COM_BLUE, 1);
    //    if(WhiteOnMove(DIS.currentMove)){           //现在红方走棋
    //        if(other->playWhat == WHITE){ //另一个引擎也走了红棋
    //            LogOut("另一引擎已走了红方\n");        //输出引擎名称
    //            //还得将按下去的按钮弹出来
    //            if(now->UCCI_which == 1){
    //                SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_COM_RED, 0);
    //            }
    //            else{
    //                SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_COM_BLUE, 0);
    //            }                
    //            return;
    //        }
    //        else{
    //            now->playWhat  = WHITE;  
    //            //DIS.gameMode   = MachinePlaysWhite;
    //        }
    //    }
    //    else{
    //        if(other->playWhat == BLACK){
    //            LogOut("另一引擎已走了黑方\n");        //输出引擎名称
    //            //还得将按下去的按钮弹出来
    //            if(now->UCCI_which == 1){
    //                SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_COM_RED, 0);
    //            }
    //            else{
    //                SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_COM_BLUE, 0);
    //            }
    //            return;
    //        }
    //        else{
    //            now->playWhat  = BLACK;  
    //            //DIS.gameMode   = MachinePlaysBlack;
    //        }
    //    }
    //    //now->working = true;
    //    LogOut(now->UCCI_name);
    //    LogOut("已加入运算!\n");
    //}
    //else{
    //    //SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_COM_BLUE, 0);
    //    if(now->maybeThinking){                 //如果引擎可能在思考
    //        SendToProgram("stop\n",now);
    //    }
    //    //now->working = false;
    //    now->playWhat = NEUTRAL;
    //    LogOut(now->UCCI_name);
    //    LogOut("::已停止运算!\n");

    //    return;
    //}

    //if(now->playWhat != NEUTRAL && other->playWhat != NEUTRAL){
    //    DIS.gameMode = TwoMachinesPlay;
    //}
    //else{
    //    if(now->playWhat == BLACK){
    //        DIS.gameMode = 
    //    }
    //}
    //SetGameModeByDisCps();

    //if(now->working && other->working){
    //    DIS.gameMode = TwoMachinesPlay;
    //}

    //if (appData.noChessProgram || (DIS.gameMode == MachinePlaysWhite)){
    //    return;
    //}
    //if (DIS.gameMode == PlayFromGameFile || DIS.gameMode == TwoMachinesPlay  
    //    || DIS.gameMode == Training      || DIS.gameMode == AnalyzeMode      
    //    || DIS.gameMode == EndOfGame)
    //{
    //    EditGameEvent();
    //}

    //if (DIS.gameMode == EditPosition) {
    //    EditPositionDone();
    //}

    //if (!WhiteOnMove(DIS.currentMove)) {			//现在不是红走
    //    DisplayError("It is not White's turn", 0);
    //    return;
    //}

    //if (DIS.gameMode == AnalyzeMode || DIS.gameMode == AnalyzeFile){
    //    ExitAnalyzeMode();
    //}

    //if (DIS.gameMode == EditGame || DIS.gameMode == AnalyzeMode || DIS.gameMode == AnalyzeFile){
          //TruncateGame();
    //}

    //ResurrectChessProgram();	/* in case it isn't running */
    //DIS.gameMode	= MachinePlaysWhite;
    //DIS.pausing		= FALSE;
    //ModeHighlight();
    //SetGameInfo(); 
    
    //显示窗口标题, 是谁和谁在下

    //StringCbPrintf(DIS.GGQJ.Rname,sizeof(DIS.GGQJ.Rname),"佳佳用户"); 
    //StringCbPrintf(DIS.GGQJ.Bname,sizeof(DIS.GGQJ.Bname),"佳佳用户"); 

    //if(now->playWhat == WHITE){
    //    StringCbPrintf(DIS.GGQJ.Rname, sizeof(DIS.GGQJ.Rname), now->UCCI_name);
    //}
    //else if(now->playWhat == BLACK){
    //    StringCbPrintf(DIS.GGQJ.Bname, sizeof(DIS.GGQJ.Bname), now->UCCI_name);
    //}

    //if(other->playWhat == WHITE){
    //    StringCbPrintf(DIS.GGQJ.Rname, sizeof(DIS.GGQJ.Rname), other->UCCI_name);
    //}
    //else if(other->playWhat == BLACK){
    //    StringCbPrintf(DIS.GGQJ.Bname, sizeof(DIS.GGQJ.Bname), other->UCCI_name);
    //}

    //StringCbPrintf(buf,MSG_SIZ,"%s vs. %s", DIS.GGQJ.Rname, DIS.GGQJ.Bname);
    //DisplayTitle(buf);				//窗口标题显示一下

    //FeedMovesToProgram(now,DIS.currentMove);  //发送初始局面给引擎

    //switch(now->ucci){
    //    case UCCI_UCCI:
    //        SendMoveToProgram(DIS.currentMove-1,now);
    //        SendProgramGo(now);
    //        break;
    //    case UCCI_QH:
    //        break;
    //    default:
    //        break;
    //}

    //now->maybeThinking = TRUE;
    //StartClocks();


    //SetMachineThinkingEnables();		//更新菜单项
    //DIS.first.maybeThinking = TRUE;
    //StartClocks();
    //if (appData.autoFlipView && !DIS.flipView) {
    //    DIS.flipView = !DIS.flipView;
    //    DrawPosition(false, NULL);
    //}
//}

void MachinePlayEvent(ChessProgramState* now){
    

    //DIS.first.playWhat    = NEUTRAL;
    //DIS.second.playWhat   = NEUTRAL;

    //LoadChessProgramState(&DIS.second,hwndMain);

   //if(SendMessage(hwndToolBar,TB_ISBUTTONCHECKED,
   //             IDT_IMPORT,0)){//电脑走棋按钮按下了

    //int but = (now == &DIS.first?IDT_COM_RED:IDT_COM_BLUE);

    //if(SendMessage(hwndToolBar,TB_CHECKBUTTON,but,0)){   //如果是引擎按钮按下了

       //SetDlgButton(

//**************************************************************
        //if(now->UCCI_initDone == FALSE){        //如果当前的引擎还没加载,就加载它
        //    //先将引擎按钮弹出，如果成功再按下
        //    if(now == &DIS.first){
        //        SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_COM_RED,0);
        //    }
        //    else{
        //        SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_COM_BLUE,0);
        //    }
        //    LoadChessProgramState(now,hwndMain);
        //    return;
        //}
        //else if(now->yqOldId != now->yqID){ //可能是更新了引擎, 得将先前的卸载，再加载当前的
        //    now->UCCI_initDone = FALSE;
        //    //先将引擎按钮弹出，如果成功再按下
        //    if(now == &DIS.first){
        //        SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_COM_RED,0);
        //    }
        //    else{
        //        SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_COM_BLUE,0);
        //    }
        //    LoadChessProgramState(now,hwndMain);
        //    return;
        //}


        //if(now->Already_Send_Initinfo == FALSE){
        //    SendControlParameterToCps(now);
        //    now->Already_Send_Initinfo = TRUE;
        //}

        ////当前引擎已加载了

        //SetCpsPlayWhat(now);

        ////得到控制时间
        //GetTimeSetInfoFromCps(now);

        //if(now->playWhat == DIS.pos.side){
        //    //
        //    SendProgramGo(now);  



        //}
    //**************************************************************
             

    //}
    //else{                                           //如果是引擎按钮弹出了
    //    if(now->maybeThinking){
    //        SendToProgram("stop\n", now);
    //    }

    //    Sleep(100);
    //    now->maybeThinking  = FALSE;
    //    now->playWhat       = NEUTRAL;

    //}


}

    ////将按钮弹出了

    //SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_COM_RED, 0);
    //SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_COM_BLUE,0);

void	//引擎走红方事件, 现在是按下了第一个引擎
MachineWhiteEvent(void){

    //char buf[MSG_SIZ];
    //ChessProgramState* first  = &DIS.first;

    //char buf[MSG_SIZ];
    //ChessProgramState* cps = &DIS.first;


    //if (appData.noChessProgram || (DIS.gameMode == MachinePlaysWhite)){
    //    return;
    //}
    //if (DIS.gameMode == PlayFromGameFile || DIS.gameMode == TwoMachinesPlay  
    //    || DIS.gameMode == Training      || DIS.gameMode == AnalyzeMode      
    //    || DIS.gameMode == EndOfGame)
    //{
    //    EditGameEvent();
    //}

    //if (DIS.gameMode == EditPosition) {
    //    EditPositionDone();
    //}

    //if (!WhiteOnMove(DIS.currentMove)) {			//现在不是红走
    //    DisplayError("It is not White's turn", 0);
    //    return;
    //}

    //if (DIS.gameMode == AnalyzeMode || DIS.gameMode == AnalyzeFile){
    //    ExitAnalyzeMode();
    //}

    //if (DIS.gameMode == EditGame || DIS.gameMode == AnalyzeMode || DIS.gameMode == AnalyzeFile){
    //    TruncateGame();
    //}

    //ResurrectChessProgram();	/* in case it isn't running */
    //DIS.gameMode	= MachinePlaysWhite;
    //DIS.pausing		= FALSE;
    //ModeHighlight();
    //SetGameInfo();

    //StringCbPrintf(buf,MSG_SIZ,"%s vs. %s", DIS.GGQJ.Rname, DIS.GGQJ.Bname);
    //DisplayTitle(buf);				//窗口标题显示一下



    ////FeedMovesToProgram(cps,DIS.currentMove);  //发送初始局面给引擎

    //switch(DIS.first.ucci){
    //    case UCCI_UCCI:

    //        if(cps->isBaoGan){	//包干记时
    //            StringCbPrintf(buf,MSG_SIZ,"go time %d increment %d depth %d\n", 
    //                cps->timePerStep,cps->addTimePerStep,cps->searchDepth);
    //            SendToProgram(buf, cps);
    //        }
    //        else{
    //            Sleep(10);
    //            StringCbPrintf(buf,MSG_SIZ,"go depth %d\n",cps->searchDepth);
    //            SendToProgram(buf, cps);
    //        }
    //        break;
    //    case UCCI_QH:
    //        SendToProgram("AI\n", cps);	
    //        break;
    //    case UCCI_DIS:
    //        if (DIS.first.sendName) {
    //            //sprintf(buf, "name %s\n", DIS.gameInfo.black);
    //            StringCbPrintf(buf,MSG_SIZ,"name %s\n", DIS.GGQJ.Bname);
    //            SendToProgram(buf, &DIS.first);
    //        }
    //        if (DIS.first.sendTime) {
    //            if (DIS.first.useColors) {
    //                SendToProgram("black\n", &DIS.first); /*gnu kludge*/
    //            }
    //            SendTimeRemaining(&DIS.first, TRUE);
    //        }
    //        if (DIS.first.useColors) {
    //            SendToProgram("white\ngo\n", &DIS.first);
    //        } 
    //        else {
    //            SendToProgram("go\n", &DIS.first);	
    //        }
    //        break;
    //    default:
    //        break;
    //}


    //SetMachineThinkingEnables();		//更新菜单项
    //DIS.first.maybeThinking = TRUE;
    //StartClocks();
    //if (appData.autoFlipView && !DIS.flipView) {
    //    DIS.flipView = !DIS.flipView;
    //    DrawPosition(false, NULL);
    //}
}

void
MachineBlackEvent(){
    //char buf[MSG_SIZ];
    //ChessProgramState* cps = &DIS.first;

    //if (appData.noChessProgram || (DIS.gameMode == MachinePlaysBlack)){
    //    return;
    //}


    //if (	DIS.gameMode == PlayFromGameFile || DIS.gameMode == TwoMachinesPlay  
    //    || 	DIS.gameMode == Training         || DIS.gameMode == AnalyzeMode     
    //    || 	DIS.gameMode == EndOfGame)
    //{
    //    EditGameEvent();
    //}

    //if (DIS.gameMode == EditPosition) { 
    //    EditPositionDone();
    //}

    //if (WhiteOnMove(DIS.currentMove)) {
    //    DisplayError("It is not Black's turn", 0);
    //    return;
    //}

    //if (DIS.gameMode == AnalyzeMode || DIS.gameMode == AnalyzeFile)
    //    ExitAnalyzeMode();

    //if (DIS.gameMode == EditGame || DIS.gameMode == AnalyzeMode || 
    //    DIS.gameMode == AnalyzeFile)
    //    TruncateGame();

    //ResurrectChessProgram();	/* in case it isn't running */
    //DIS.gameMode = MachinePlaysBlack;
    //DIS.pausing = FALSE;
    //ModeHighlight();
    //SetGameInfo();	
    //StringCbPrintf(buf,MSG_SIZ,"%s vs. %s", DIS.GGQJ.Rname, DIS.GGQJ.Bname);
    //DisplayTitle(buf);


    ////if (DIS.first.useColors) {
    ////	SendToProgram("black\ngo\n", &DIS.first);
    ////} 
    ////else {
    ////	SendToProgram("go\n", &DIS.first);
    ////}
    ////FeedMovesToProgram(cps,DIS.currentMove);  //发送初始局面给引擎

    //switch(cps->ucci){
    //    case UCCI_UCCI:
    //        if(cps->isBaoGan){	//包干记时
    //            StringCbPrintf(buf,MSG_SIZ,"go time %d increment %d depth %d\n", 
    //                cps->timePerStep,cps->addTimePerStep,cps->searchDepth);
    //            SendToProgram(buf, cps);
    //        }
    //        else{
    //            StringCbPrintf(buf,MSG_SIZ,"go depth %d\n",cps->searchDepth);
    //            SendToProgram(buf, cps);
    //        }
    //        break;			
    //    case UCCI_QH:
    //        SendToProgram("AI\n",cps);	
    //        break;
    //    case UCCI_DIS:
    //        if (cps->sendName) {		
    //            StringCbPrintf(buf,MSG_SIZ,"name %s\n", DIS.GGQJ.Rname);
    //            SendToProgram(buf, &DIS.first);
    //        }
    //        if (cps->sendTime) {
    //            if (cps->useColors) {
    //                SendToProgram("white\n", cps); /*gnu kludge*/
    //            }
    //            SendTimeRemaining(cps, FALSE);
    //        }
    //        break;
    //    default:
    //        break;
    //}

    //SetMachineThinkingEnables();
    //DIS.first.maybeThinking = TRUE;
    //StartClocks();

    //if (appData.autoFlipView && DIS.flipView) {
    //    DIS.flipView = !DIS.flipView;
    //    DrawPosition(false, NULL);
    //}
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
