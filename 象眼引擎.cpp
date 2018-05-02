#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

void			//处理UCCI引擎输入过来的消息
HandleMachineUCCI162(TCHAR *Tinfo, ChessProgramState *cps){


//    //char* yqName;
//    char buf[MSG_SIZ*8];
//
//
//	dispboard_t* pDis = (dispboard_t*)cps->pDis;
//
//	if(cps == &pDis->first){
//		LogOut("1:");
//	}
//	else{
//		LogOut("2:");
//	}
//
//    if(false){
//    }
//    //*******************************************************************************
//    else if(strncasecmp(message,"bestmove",8) == 0){
//
//        LogOut(cps->UCCI_name);        //输出引擎名称
//		LogOut(message);
//
//        //DispStatS(message);
//		SendMessage(hStatusBar,SB_SETTEXT,0,(LPARAM)"引擎认负!");
//
//        message +=9;
//        if(strlen(message) < 2){
//            LogOut("Err");
//            LogOut(message);
//            LogOut("\n");
//            //ConsoleOutput("\n",1,FALSE); //回车换行
//        }
//        else{
//            int machineWhite;
//            switch(pDis->gameMode){
//                case BeginningOfGame:
//                    /* Extra move from before last reset; ignore */
//#ifdef DEBUG_USE_DEBUG_FILE
//                    //if (appData.debugMode) {    //可能是上一局的,不要了
//                        fprintf(appData.debugFP, "Ignoring extra move from %s\n", cps->UCCI_name);
//                    //}
//#endif
//                    return;                    
//                case EndOfGame:
//                case IcsIdle:
//                default:
//                    /* Extra move after we tried to stop.  The mode test is
//                    not a reliable way of detecting this problem, but it's
//                    the best we can do on engines that don't support ping.
//                    */
//#ifdef DEBUG_USE_DEBUG_FILE
//                    //if (appData.debugMode) {
//                        fprintf(appData.debugFP, "Undoing extra move from %s, gameMode %d\n",
//                            cps->UCCI_name, pDis->gameMode);
//                    //}
//#endif
//                    //SendToProgram("undo\n", cps);
//                    return;
//                case MachinePlaysWhite:
//                case IcsPlayingWhite:
//                    machineWhite = TRUE;
//                    break;
//                case MachinePlaysBlack:
//                case IcsPlayingBlack:
//                    machineWhite = FALSE;
//                    break;
//                case TwoMachinesPlay:   //引擎对战识别
//                    //machineWhite  = (cps->UCCI_which == 1);      //是第一个引擎 
//                    machineWhite = cps->playWhat == WHITE;
//                    break;
//            }
//            //
//            //if(WhiteOnMove(DIS.forwardMostMove) != machineWhite){
//
//            if(pDis->pos->side != cps->playWhat){
//
//                //LogOut(ColorTell,"Ignoring move out of turn by %s, gameMode %d, forwardMost %d\n",
//                //        cps->which, DIS.gameMode, DIS.forwardMostMove, false);
//
//               
//                LogOut(message);
//                LogOut(" 不是引擎走步!!\n");
//
//#ifdef DEBUG_MODE               
//                //if(appData.debugMode){
//                    //fprintf(DIS.debugFP,
//                    //    "Ignoring move out of turn by %s, gameMode %d, forwardMost %d\n",
//                    //    cps->UCCI_name, DIS.gameMode, DIS.forwardMostMove);
//                //}
//#endif
//                return;
//            }
//            //解析走步
//            int fromX,fromY,toX,toY;
//            ChessMove moveType;
//
//            char pmove[8];
//			sprintf_s(pmove, 5, message);
//
//            /*if(!ParseOneMove(pmove,DIS.forwardMostMove,&moveType,&fromX, &fromY, &toX, &toY, cps->ucci)) {*/
//            if(!ParseOneMove(pmove,pDis->pos->gply,&moveType,&fromX, &fromY, &toX, &toY, cps->ucci)) {
//                /* Machine move could not be parsed; ignore it. */
//				sprintf_s(buf, MSG_SIZ, "Illegal move \"%s\" from %s machine", message, cps->UCCI_name);
//                DisplayError(buf, 0);
//                if (pDis->gameMode == TwoMachinesPlay) {
//                    GameEnds(pDis,machineWhite ? BlackWins : WhiteWins,"Forfeit due to illegal move", GE_XBOARD);
//                }
//                return;
//            }
//            //else{   //在这儿作重复判断或连将判断  rep_eat_or_check 用来作计数器,如果超过3次,就不行了
//            //    
//            //}
//
//
//
//            //pDis->hintRequested = FALSE;
//            //pDis->lastHint[0]   = NULLCHAR;
//            //pDis->bookRequested = FALSE;
//            /* Program may be pondering now */
//            //cps->maybeThinking = TRUE;
//            //if (cps->sendTime == 2){
//            //    cps->sendTime = 1;
//            //}
//            if (cps->offeredDraw){
//                cps->offeredDraw--;
//            }
//            //StringCbCopy(machineMove,MSG_SIZ,DIS.currentMoveString);        
//            //StringCbCat(machineMove,MSG_SIZ,"\n");
//            MakeMove(pDis,fromX,fromY,toX,toY,false);    /*updates forwardMostMove*/
//            if(pDis->gameMode == TwoMachinesPlay){    //是双引擎对战
//                //if(cps->other->sendTime){
//                //    /*SendTimeRemaining(cps->other,cps->other->twoMachinesColor[0] == 'w');*/
//                //    //SendTimeRemaing(
//                //}
//                // UCCI 不发送时间,
//                //SendMoveToProgram(DIS.forwardMostMove-1,cps->other);    //
//                //SendMoveToProgram(DIS.pos.gply - 1,cps->other);    //
//
//				
//				ChessProgramState* other;
//
//				if(cps == &pDis->first){
//					other = &pDis->second;
//				}
//				else{
//					other = &pDis->first;
//				}
//
//                //SendProgramGo(other);                              //使用引擎开始运算
//
//                if(pDis->firstMove){
//                    pDis->firstMove = FALSE;
//                }
//                //cps->other->maybeThinking = TRUE;
//            }            
//
//            ShowMove(pDis,fromX,fromY,toX,toY);
//
//            if(pDis->gameMode != TwoMachinesPlay){
//                
//				SetUserThinkingEnables();
//
//                //if(cps->UCCI_ponder_chelu == false){
//                //    cps->maybeThinking = false;
//                //}
//                //else{ //让这个cps进入后台思考 
//                //    ////
//                //}
//            }
//            return;
//        }//有bestmove
//    }
//    //*******************************************************************************
//    else if(strncasecmp(message,"nobestmove",10) == 0){
//        
//        LogOut(cps->UCCI_name);        //输出引擎名称
//        LogOut(_T("nobestmove\n"));  
//        //DispStatS(message);
//		SendMessage(hStatusBar,SB_SETTEXT,0,(LPARAM)"引擎认负!");
//
//		cps->cps_stat = Cps_Waiting;
//
//		//cps->maybePonering = FALSE;
//		//cps->maybeThinking = FALSE;
//		//PostMessage(hwndToolBar,TB_ENABLEBUTTON,IDT_Stop,0); 
//
//        //EndGame(
//
//        //思考状态的反馈，此后引擎返回空闲状态。显示思考结果，
//        // 但引擎一步着法也没计算，表示当前局面是死局面，
//        // 或者接收到诸如“go depth 0”等只让引擎给出静态局面评价的指令。 
//    }
//    //*******************************************************************************
//    else if(strncasecmp(message,"id", 2) == 0){
//        LogOut(cps->UCCI_name);        //输出引擎名称
//        message +=3;
//
//        //LogOut(ColorShout,message,true);
//
//        if(false){
//        }
//        else if(strncasecmp(message,"name", 4) == 0){  
//
//            StringCbPrintf(cps->UCCI_name,128,"%s\n",message+5);
//            LogOut("引擎名称: ");
//            LogOut(cps->UCCI_name);            
//        }
//        else if(strncasecmp(message,"copyright", 9) == 0){
//
//            StringCbPrintf(cps->UCCI_copyright,128,"%s\n",message+10);
//            LogOut("版权所有: ");
//            LogOut(cps->UCCI_copyright);     
//        }
//        else if(strncasecmp(message,"author", 6) == 0){
//
//            StringCbPrintf(cps->UCCI_author,128,"%s\n",message+7);
//            LogOut("引擎作者: ");
//            LogOut(cps->UCCI_author);  
//        }
//        else if(strncasecmp(message,"user", 4) == 0){
//
//            StringCbPrintf(cps->UCCI_user,128,"%s\n",message+5);
//            LogOut("授权用户: ");
//            LogOut(cps->UCCI_user);  
//        }
//    }
//    //*******************************************************************************
//    else if(strncasecmp(message,"option", 6) == 0){
//        LogOut(cps->UCCI_name);        //输出引擎名称
//        message +=7; 
//        if(false){
//        }
//        else if(strncasecmp(message,"batch", 5) == 0){
//
//            message += 6;            
//            char* p = strstr(message,"default");
//            if(p != 0){
//                p += 8;
//                if(strncasecmp(p,"true",4) == 0){
//                    cps->UCCI_batch = true;
//                }
//                else{
//                    cps->UCCI_batch = false;
//                }
//                LogOut("引擎批处理模式: ");
//
//                if(cps->UCCI_batch){
//                    LogOut("已开启\n");
//                }
//                else{
//                    LogOut("已关闭\n");
//                }
//            }
//        }
//        else if(strncasecmp(message,"debug", 5) == 0){
//            message += 6;
//            char* p = strstr(message,"default");
//            if(p != 0){
//                p += 8;
//                if(strncasecmp(p,"true",4) == 0){
//                    cps->UCCI_debug = true;
//                }
//                else{
//                    cps->UCCI_debug = false;
//                }
//                LogOut("引擎调试模式: ");
//
//                if(cps->UCCI_debug){
//                    LogOut("已开启\n");
//                }
//                else{
//                    LogOut("已关闭\n");
//                }
//            }
//        }
//        else if(strncasecmp(message,"usemillisec", 11) == 0){
//            message += 12;
//            char* p = strstr(message,"default");
//            if(p != 0){
//                p += 8;     
//                if(strncasecmp(p,"true",4) == 0){
//                    cps->UCCI_usemillisec = true;
//                }
//                else{
//                    cps->UCCI_usemillisec = false;
//                }
//                LogOut("引擎毫秒模式: ");
//
//                if(cps->UCCI_usemillisec){
//                    LogOut("已开启\n");
//                }
//                else{
//                    LogOut("已关闭\n");
//                }
//            }
//        }
//        else if(strncasecmp(message,"ponder", 6) == 0){ //是否使用后台思考的时间策略
//
//            //message += 7;
//            //char* p  = strstr(message,"default");
//            //if(p != 0){
//            //    p       += 8; 
//            //    if(strncasecmp(p,"true",4) == 0){
//            //        cps->UCCI_ponder_chelu = true;
//            //    }
//            //    else{
//            //        cps->UCCI_ponder_chelu = false;
//            //    }
//            //    LogOut("引擎后台思考时间策略: ");
//
//            //    if(cps->UCCI_ponder_chelu){
//            //        LogOut("已开启\n");
//            //    }
//            //    else{
//            //        LogOut("已关闭\n");
//            //    }
//            //}
//        }
//        else if(strncasecmp(message,"usebook", 7) == 0){
//            message += 8;
//            char* p  = strstr(message,"default");
//            if(p != 0){
//                p += 8;
//                if(strncasecmp(p,"true",4) == 0){
//                    cps->UCCI_haveselfBook = true;
//                }
//                else{
//                    cps->UCCI_haveselfBook = false;
//                }
//                if(cps->UCCI_haveselfBook){
//                    LogOut("引擎自带开局库\n");
//                }
//                else{
//                    LogOut( "引擎没有开局库\n");
//                }
//            }
//
//            /*LogOut(ColorChannel1,   "usebook, 界面未处理\n",true); */  
//        }
//        else if(strncasecmp(message,"bookfiles", 9) == 0){
//            message += 10;
//            char* p  = strstr(message,"default");
//            if(p != 0){
//                p       += 8;              
//                //StringCbPrintf(cps->UCCI_bookfiles,MAX_PATH,"%s\n",p);
//                LogOut("引擎开局库路径: ");
//                //LogOut(ColorChannel1,cps->UCCI_bookfiles,true); 
//            }
//        }
//        else if(strncasecmp(message,"egtbpaths", 9) == 0){
//            LogOut(   "egtbpaths, 界面未处理\n"); 
//        }
//        else if(strncasecmp(message,"hashsize", 8) == 0){
//            message += 9;
//            char* p  = strstr(message,"default");
//            if(p != 0){
//                p       += 8;  
//                //cps->UCCI_hashsize = atoi(p);
//				int hash = atoi(p);
//                LogOut("引擎HASH大小: ");
//                StringCbPrintf(buf,512, "%dMB\n", hash);
//                LogOut(buf);  
//            }
//        }
//        else if(strncasecmp(message,"threads", 7) == 0){
//            LogOut(  "threads, 界面未处理\n"); 
//        }
//        else if(strncasecmp(message,"drawmoves", 9) == 0){
//            LogOut(   "drawmoves, 界面未处理\n"); 
//        }
//        else if(strncasecmp(message,"repetition", 10) == 0){
//            LogOut(   "repetition, 界面未处理\n"); 
//        }
//        else if(strncasecmp(message,"pruning", 7) == 0){
//
//            message += 8;
//            char* p  = strstr(message,"default");           
//            if(p != 0){
//                p       += 8;  
//                StringCbPrintf(cps->UCCI_pruning,32, "%s\n", p);
//                LogOut("引擎裁剪程度: ");
//                LogOut(cps->UCCI_pruning);
//            }
//        }
//        else if(strncasecmp(message,"knowledge", 9) == 0){
//            message += 10;
//            char* p  = strstr(message,"default");
//            if(p != 0){
//                p       += 8;  
//                StringCbPrintf(cps->UCCI_knowledge,32, "%s\n", p);
//                LogOut("引擎设定知识大小: ");
//                LogOut(cps->UCCI_knowledge);
//            }
//        }
//        else if(strncasecmp(message,"selectivity",11) == 0){
//            message += 12;
//            char* p  = strstr(message,"default");
//
//            if(p != 0){
//                p       += 8;  
//                StringCbPrintf(cps->UCCI_selectivity,32, "%s\n", p);
//                LogOut("引擎选择性(随机性)系数: ");
//                LogOut(cps->UCCI_selectivity);
//            }
//        }
//        else if(strncasecmp(message,"style",5) == 0){
//            LogOut(   "style, 界面未处理\n"); 
//        }
//        else if(strncasecmp(message,"loadbook",8) == 0){
//            //LogOut(ColorChannel1,   "loadbook, 界面未处理\n",false); 
//        }
//        else if(strncasecmp(message,"clearhash",9) == 0){
//            LogOut(   "clearhash, 界面未处理\n"); 
//        }
//        else if(strncasecmp(message,"dualtime",8) == 0){
//
//            message += 9;
//            char* p  = strstr(message,"default");            
//            if(p != 0){
//                p       += 8;  
//                if(strncasecmp(p,"true",4) == 0){
//                    cps->UCCI_dualtime = true;
//                }
//                else{
//                    cps->UCCI_dualtime = false;
//                }              
//                LogOut("引擎双时限功能: ");
//                if(cps->UCCI_dualtime){
//                    LogOut("已开启\n");
//                }
//                else{
//                    LogOut("已关闭\n");
//                }
//            }
//            else{
//                cps->UCCI_dualtime = false;
//                LogOut("引擎双时限功能: "); 
//                LogOut("已关闭\n");                
//            }
//        }
//        else if(strncasecmp(message,"newgame", 7) == 0){
//            //message +=8;
//            LogOut( message);
//            LogOut( "\n");
//        }
//        else{     //未识别的选项
//            LogOut("界面不能识别引擎发送的选项: ");
//            LogOut(message);
//        }
//    }
//    //*******************************************************************************
//    else if(strncasecmp(message,"ucciok", 6) == 0){
//        //if(cps->UCCI_initDone == FALSE){
//		if(cps->cps_stat == Cps_InLoading){
//			PostMessage(cps->loadWin,WM_USER_YqLoad_OK,0,(LPARAM)cps);  //向引擎所在窗口发送初始化成功的信息
//        }  
//    }
//    //*******************************************************************************
//    else if(strncasecmp(message,"readyok", 7) == 0){
//        //空闲状态和思考状态的反馈。表明引擎处于就绪状态(可正常接收指令)。
//        LogOut(cps->UCCI_name);        //输出引擎名称
//        LogOut("引擎已在接受指令状态!\n");
//    }
//    //*******************************************************************************
//    else if(strncasecmp(message,"info", 4) == 0){
//        //思考状态的反馈。显示引擎思考信息，通常有以下几种信息： 
//        //(1) nodes <已搜索的结点数> time <已花费的时间>：思考信息中给出的时间通常以毫秒为单位，结点数和时间相除就是引擎的速度(NPS值)，单位是KNPS。 
//        //(2) depth <当前搜索深度> [score <分值> pv <主要变例>]：输出引擎思考到的深度及其思考路线和好坏，
//        //目前UCCI引擎《象棋巫师》只对这种信息作出处理。例如在起始局面下，
//        //《象棋巫师》收到引擎的反馈：info depth 6 score 4 pv b0c2 b9c7 c3c4 h9i7 c2d4 h7e7，
//        //那么界面上应该输出：“深度：6，分值：4，主要变例：马八进七 马２进３ 兵七进一 马８进９ 马七进六 炮８平５”。
//        //分值通常以一个轻子(马或炮)为100分记，以上信息说明此时当前要走的一方占有相当于0.04个轻子的优势。 
//        //(3) currmove <当前搜索着法>：输出引擎正在思考的着法。 
//        char *movestr;
//        message += 5;
//        if(false){
//        }
//        else if(strncasecmp(message,"log",3) == 0){
//            LogOut(cps->UCCI_name);        //输出引擎名称
//            LogOut(message+4);
//            LogOut("\n");
//        }
//        else if(movestr = strstr(message,"pv")){        //引擎反馈的关键路线
//            LogOut(cps->UCCI_name);        //输出引擎名称
//            //DispStatS(message);               //将信息显示到状态栏中
//			//SendMessage(hStatusBar,SB_SETTEXT,0,(LPARAM)"引擎认负!");
//            LogOut(message);
//            LogOut("\n");
//
//            //不有MPV
//
//            //movestr += 3;          
//            //uint8 B256[256];
//            //memcpy(B256,DIS.pos.b256,256);
//            //int len = (int)strlen(movestr);
//            //int from;
//            //int to;     
//            //int chess;
//            //while(len >= 4){  
//            //    from = (movestr[0] - 'a' + 3) + (('9' - movestr[1] + 3) * 16);
//            //    to   = (movestr[2] - 'a' + 3) + (('9' - movestr[3] + 3) * 16);  
//            //    if(from < 0x32 || from > 0xcb || to < 0x32 || to > 0xcb){
//            //        LogOut(ColorSShout,"引擎思考路径有错: ",false);
//            //        LogOut(ColorSShout,message,true);
//            //        break;
//            //    }
//            //    chess  = B256[from];
//            //    B256[from] = EMPTY;
//            //    B256[to]   = chess;                
//            //    movestr += 5;
//            //    len -= 5;
//            //} 
//            //char fen[256];
//            ////if(WhiteOnMove(DIS.currentMove+num)){
//            //if(IsBlack(chess)){
//            //    position_to_fen_by_b256(B256,WHITE,fen);
//            //}
//            //else{
//            //    position_to_fen_by_b256(B256,BLACK,fen);
//            //}
//            //StringCbPrintf(buf,512,"PV End fen %s\n",fen);            
//            //BoardDisplay(B256,buf); 
//        }
//        else {
//            //LogOut(ColorChannel1,message,true);
//            //LogOut(ColorNormal,"\n",true);
//            //DispStatS(message);               //将信息显示到状态栏中
//        }
//        
//    }
//    //*******************************************************************************
//    else if(strncasecmp(message,"bye", 3) == 0){
//        //接收到quit指令后的反馈。引擎完成了退出运转前的准备工作，
//        // 通知界面，引擎将在瞬间正常退出运转。界面收到该指令后，
//        // 通常只需要等待1毫秒，即可关闭输入输出通道。
//
//        //if(cps->twoMachinesColor[0] == 'w'){
//        //    LogOut(ColorSeek,    "红方引擎已成功退出!\n",false);
//        //}
//        //else{
//        //    LogOut(ColorChannel1,"黑方引擎已成功退出!\n",false);           
//        //}
//        //if(cps->UCCI_which == 1){           //这是第一个引擎
//        //    SendMessage(hwndToolBar,TB_ENABLEBUTTON,IDT_COM_RED,0);    
//        //}
//        //else{
//        //    SendMessage(hwndToolBar,TB_ENABLEBUTTON,IDT_COM_BLUE,0);
//        //}
//        
//        //cps->UCCI_initDone  = FALSE;
//
//		//LogOut(cps->UCCI_name);        //输出引擎名称
//  //      LogOut("引擎已成功退出!\n\n");
//    }
//    //*******************************************************************************
//    else if(strncasecmp(message,"copyprotection", 14) == 0){
//        LogOut(cps->UCCI_name);        //输出引擎名称
//        message +=15;
//        LogOut("引擎版权认证: ");
//
//        if(strncasecmp(message,"ok",2) == 0){
//            LogOut( "已通过\n"); 
//        }
//        else{
//            LogOut( "未通过\n"); 
//        }
//    }   
//    //*******************************************************************************
//    else {  //可能是其它反馈信息
//        //if(cps->twoMachinesColor[0] == 'w'){
//        //    LogOut(ColorSeek,     "红方引擎未识别指令\n", false);            
//        //}
//        //else{
//        //    LogOut(ColorChannel1, "黑方引擎未识别指令\n", false);            
//        //}
//
//        LogOut(cps->UCCI_name);        //输出引擎名称
//        LogOut("引擎未识别指令\n"); 
//        LogOut( message);
//        LogOut( "\n");
//    }
	LogOut(_T("引擎未识别指令\n"));
	LogOut(Tinfo);
}

