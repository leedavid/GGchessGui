#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"



void		//发送走步到引擎,注意只是发送用户走了一步,并不要叫诉引擎要走棋!!!
SendCurPosToProgram(dispboard_t* pDis, ChessProgramState *cps){
    TCHAR    buf[FEN_SIZE];
	//TCHAR*   pb;
	TCHAR    fen[MSG_SIZ];
    int     start;
    int     startSide;

	int     gply   = pDis->pos->curStep;
    int     nonCap = pDis->pos->His[gply].nonCap;

	//将当前的局面复制一下
	memcpy(cps->pos, pDis->pos, sizeof(position_t));

	//发送最一个不吃子的局面  
	startSide = pDis->pos->side ^ (nonCap%2);
	start     = gply - nonCap;

	position_to_fen_by_b256(pDis->B256dis[start],startSide,fen);

	swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), L"fen %s moves", fen);

	//pb = buf + wcslen(buf);

	for(int i = start; i < gply; i++){
		//swprintf_s(pb, sizeof(buf) / sizeof(TCHAR), L" %s", pDis->parseList[i]);
		//pb += 5;

		wcscat_s(buf, sizeof(buf) / sizeof(TCHAR), L" ");
		wcscat_s(buf, sizeof(buf) / sizeof(TCHAR), pDis->parseList[i]);
	}

	wcscat_s(buf, sizeof(buf) / sizeof(TCHAR), L"\n");
	SendToProgram(buf,cps);   //发送初始局面 
}

void SendOnlyFenToProgram(dispboard_t* pDis, ChessProgramState *cps){

	TCHAR    buf[MSG_SIZ];
	int start = pDis->pos->curStep;
	int startSide = pDis->pos->side;
	position_to_fen_by_b256(pDis->pos->b256, pDis->pos->side, buf);

	wcscat_s(buf, sizeof(buf) / sizeof(TCHAR), L"\n");
	SendToProgram(buf, cps);   //发送初始局面 
}


void			//处理UCCI引擎输入过来的消息
HandleMachineGGyq(TCHAR* message, ChessProgramState *cps){

	TCHAR buf[MSG_SIZ * 8];

	dispboard_t* pDis = (dispboard_t*)cps->pDis;
	//setlocale(LC_CTYPE, "chs");
    if(false){
    }
	//*******************************************************************************
	else if (_wcsnicmp(message, L"cmd:", 4) == 0){
		LogOut(_T("\n"));
		LogOut(message);

		wcscat_s(EvalInfo, EVAL_INFO_SIZE, L"\n");
		wcscat_s(EvalInfo, EVAL_INFO_SIZE, message + 4);
	}
	else if (_wcsnicmp(message, L"cmdend:", 6) == 0){
		//将内复制到剪贴板
		LogOut(_T("\n当前的棋局，包括java棋盘,每一个局面的评估，已全部复制到剪帖板,请发表在论坛上，以便发现问题所在"));


		if (!CopyTextToClipboard(EvalInfo))
			LogOut(L"Unable to copy FEN to clipboard.");	
	}
    //*******************************************************************************
	else if (_wcsnicmp(message, L"bestmove", 8) == 0){


		if (pDis->gameMode != AnalyzeMode){		//当前不是分析模式

			if(cps->cps_stat == Cps_Pondering){				//以前是在后台思考
				cps->cps_stat =  Cps_Waiting;			 

				if(cps->PonderStop == TRUE){				//是后台思考后命中
					cps->PonderStop = FALSE;
					SendProgramGo(cps,Cps_Thinking,NULL);
				}
				return;
			}
		}

		cps->cps_stat =  Cps_Waiting;

		//if(cps->maybePonering == TRUE){
		//	cps->maybePonering = FALSE;
		//	return;
		//}
		

        message +=9;
        if(wcslen(message) < 2){
			LogOut(_T("Err"));
            LogOut(message);
			LogOut(_T("\n"));
            //ConsoleOutput("\n",1,FALSE); //回车换行
        }
        else{
            int machineWhite;
            switch(pDis->gameMode){
                case BeginningOfGame:
                    /* Extra move from before last reset; ignore */
#ifdef DEBUG_USE_DEBUG_FILE
                    //if (appData.debugMode) {    //可能是上一局的,不要了
                        fprintf(appData.debugFP, "Ignoring extra move from %s\n", cps->UCCI_name);
                    //}
#endif
                    return;                    
                case EndOfGame:
                case IcsIdle:

                case MachinePlaysWhite:
                case IcsPlayingWhite:
                    machineWhite = TRUE;
                    break;
                case MachinePlaysBlack:
                case IcsPlayingBlack:
                    machineWhite = FALSE;
                    break;
				default:
					/* Extra move after we tried to stop.  The mode test is
					not a reliable way of detecting this problem, but it's
					the best we can do on engines that don't support ping.
					*/
#ifdef DEBUG_USE_DEBUG_FILE
					//if (appData.debugMode) {
					fprintf(appData.debugFP, "Undoing extra move from %s, gameMode %d\n",
						cps->UCCI_name, pDis->gameMode);
					//}
#endif
					//SendToProgram("undo\n", cps);
					return;
            }
            //
            //if(WhiteOnMove(DIS.forwardMostMove) != machineWhite){

            if(pDis->pos->side != cps->playWhat){

                //LogOut(ColorTell,"Ignoring move out of turn by %s, gameMode %d, forwardMost %d\n",
                //        cps->which, DIS.gameMode, DIS.forwardMostMove, false);

               
                LogOut(message);
				LogOut(_T(" 不是引擎走步!!,当前这个引擎不是走子方!!\n"));

#ifdef DEBUG_MODE               
                //if(appData.debugMode){
                    //fprintf(DIS.debugFP,
                    //    "Ignoring move out of turn by %s, gameMode %d, forwardMost %d\n",
                    //    cps->UCCI_name, DIS.gameMode, DIS.forwardMostMove);
                //}
#endif
                return;
            }
            //解析走步
            int fromX,fromY,toX,toY;
            ChessMove moveType;

            TCHAR pmove[8];
            //StringCbPrintf(pmove,5,message);

			pmove[0] = message[0];
			pmove[1] = message[1];
			pmove[2] = message[2];
			pmove[3] = message[3];
			pmove[4] = 0;

            /*if(!ParseOneMove(pmove,DIS.forwardMostMove,&moveType,&fromX, &fromY, &toX, &toY, cps->ucci)) {*/
            /*if(!ParseOneMove(pmove,pDis->pos->gply,&moveType,&fromX, &fromY, &toX, &toY, cps->ucci)) {*/
			if(!ParseOneMove(pmove,pDis->pos->curStep,&moveType,&fromX, &fromY, &toX, &toY, cps->ucci)) {
                /* Machine move could not be parsed; ignore it. */
                swprintf_s(buf,MSG_SIZ,_T("Illegal move \"%s\" from %s machine"),message, cps->UCCI_name);
                //DisplayError(buf, 0);
				LogOut(buf);
                return;
            }
            //else{   //在这儿作重复判断或连将判断  rep_eat_or_check 用来作计数器,如果超过3次,就不行了
            //    
            //}

			TCHAR *ponder;

			if (pDis->gameMode != AnalyzeMode){		//当前不是分析模式

				if(ponder = wcsstr(message,L"ponder ")){	

					ponder += 7;

					cps->PonderMove[0] = *(ponder+0);
					cps->PonderMove[1] = *(ponder+1);
					cps->PonderMove[2] = *(ponder+2);
					cps->PonderMove[3] = *(ponder+3);
					cps->PonderMove[4] = 0;

					cps->PonderMoveInt = str2move(cps->pos, cps->PonderMove);


					//char bb[256];

					//sprintf_s(bb,sizeof(bb),"\npd int %d\n",cps->PonderMoveInt );

					//LogOut(bb);

		            //cps->PonderMoveInt = pmove;
				}
				else {
					cps->PonderMove[0] = 0;
				}
			}
			else{
				cps->PonderMove[0] = 0;
			}

            if (cps->offeredDraw){
                cps->offeredDraw--;
            }

			if (pDis->gameMode != AnalyzeMode){		//当前不是分析模式
				//放到UserMoveEvent中统一处理
				FinishMove(pDis,NormalMove,fromX,fromY,toX,toY);
			}
			else{									//当前是分析模式,看能不能走棋
							
			}
            return;
        }//有bestmove
    }
    //*******************************************************************************
	else if (_wcsnicmp(message, L"nobestmove", 10) == 0){
        
        LogOut(cps->UCCI_name);        //输出引擎名称
        LogOut(_T("晕,你太厉害了,引擎没有办法走棋了,只有认负\n"));  
        //DispStatS(message);

       SendMessage(hStatusBar,SB_SETTEXT,0,(LPARAM)L"引擎认负!");

		cps->cps_stat = Cps_Waiting;

		//cps->maybePonering = FALSE;
		//cps->maybeThinking = FALSE;
		//SendMessage(hwndToolBar,TB_ENABLEBUTTON,IDT_Stop,0); 

        //EndGame(

        //思考状态的反馈，此后引擎返回空闲状态。显示思考结果，
        // 但引擎一步着法也没计算，表示当前局面是死局面，
        // 或者接收到诸如“go depth 0”等只让引擎给出静态局面评价的指令。 
    }
    //*******************************************************************************
	else if (_wcsnicmp(message, L"id", 2) == 0){
        LogOut(cps->UCCI_name);        //输出引擎名称
        message +=3;

        //LogOut(ColorShout,message,true);

        if(false){
        }
		else if (_wcsnicmp(message, L"name", 4) == 0){

            swprintf_s(cps->UCCI_name,32,_T("%s\n"),(message+5));
            LogOut(_T("引擎名称: "));
            LogOut(cps->UCCI_name);            
        }
		else if (_wcsnicmp(message, L"copyright", 9) == 0){

			swprintf_s(cps->UCCI_copyright, 64, _T("%s\n"), (message + 10));
			LogOut(_T("版权所有: "));
			LogOut(cps->UCCI_copyright);
        }
		else if (_wcsnicmp(message, L"author", 6) == 0){

			swprintf_s(cps->UCCI_author, 64, _T("%s\n"), (message + 7));
			LogOut(_T("引擎作者: "));
			LogOut(cps->UCCI_author);
        }
		else if (_wcsnicmp(message, L"user", 4) == 0){

			swprintf_s(cps->UCCI_user, 32, _T("%s\n"), (message + 5));
			LogOut(_T("授权用户: "));
			LogOut(cps->UCCI_user);
        }
    }
    //*******************************************************************************
	else if (_wcsnicmp(message, L"option", 6) == 0){
		LogOut(cps->UCCI_name);        //输出引擎名称
        message +=7; 
        if(false){
        }
		else if (_wcsnicmp(message, L"batch", 5) == 0){

            message += 6;            
            TCHAR* p = wcsstr(message,L"default");
            if(p != 0){
                p += 8;
				if (_wcsnicmp(p, L"true", 4) == 0){
                    cps->UCCI_batch = true;
                }
                else{
                    cps->UCCI_batch = false;
                }
				LogOut(_T("引擎批处理模式: "));

                if(cps->UCCI_batch){
					LogOut(_T("已开启\n"));
                }
                else{
					LogOut(_T("已关闭\n"));
                }
            }
        }
		else if (_wcsnicmp(message, L"debug", 5) == 0){
            message += 6;
            TCHAR* p = wcsstr(message,L"default");
            if(p != 0){
                p += 8;
				if (_wcsnicmp(p, L"true", 4) == 0){
                    cps->UCCI_debug = true;
                }
                else{
                    cps->UCCI_debug = false;
                }
				LogOut(_T("引擎调试模式: "));

                if(cps->UCCI_debug){
					LogOut(_T("已开启\n"));
                }
                else{
					LogOut(_T("已关闭\n"));
                }
            }
        }
		else if (_wcsnicmp(message, L"usemillisec", 11) == 0){
            message += 12;
           TCHAR* p = wcsstr(message,L"default");
            if(p != 0){
                p += 8;     
				if (_wcsnicmp(p, L"true", 4) == 0){
                    cps->UCCI_usemillisec = true;
                }
                else{
                    cps->UCCI_usemillisec = false;
                }
				LogOut(_T("引擎毫秒模式: "));

                if(cps->UCCI_usemillisec){
					LogOut(_T("已开启\n"));
                }
                else{
					LogOut(_T("已关闭\n"));
                }
            }
        }
		else if (_wcsnicmp(message, L"ponder", 6) == 0){ //是否使用后台思考的时间策略

            //message += 7;
            //char* p  = strstr(message,"default");
            //if(p != 0){
            //    p       += 8; 
            //    if(strncasecmp(p,"true",4) == 0){
            //        cps->UCCI_ponder_chelu = true;
            //    }
            //    else{
            //        cps->UCCI_ponder_chelu = false;
            //    }
            //    LogOut("引擎后台思考时间策略: ");

            //    if(cps->UCCI_ponder_chelu){
            //        LogOut("已开启\n");
            //    }
            //    else{
            //        LogOut("已关闭\n");
            //    }
            //}
        }
		else if (_wcsnicmp(message, L"usebook", 7) == 0){
            message += 8;
            TCHAR* p  = wcsstr(message,L"default");
            if(p != 0){
                p += 8;
				if (_wcsnicmp(p, L"true", 4) == 0){
                    cps->UCCI_haveselfBook = true;
                }
                else{
                    cps->UCCI_haveselfBook = false;
                }
                if(cps->UCCI_haveselfBook){
					LogOut(_T("引擎自带开局库\n"));
                }
                else{
					LogOut(_T("引擎没有开局库\n"));
                }
            }

            /*LogOut(ColorChannel1,   "usebook, 界面未处理\n",true); */  
        }
		else if (_wcsnicmp(message, L"bookfiles", 9) == 0){
            message += 10;
            TCHAR* p  = wcsstr(message,L"default");
            if(p != 0){
                p       += 8;              
                //StringCbPrintf(cps->UCCI_bookfiles,MAX_PATH,"%s\n",p);
				LogOut(_T("引擎开局库路径: "));
                //LogOut(ColorChannel1,cps->UCCI_bookfiles,true); 
            }
        }
		else if (_wcsnicmp(message, L"egtbpaths", 9) == 0){
			LogOut(_T("egtbpaths, 界面未处理\n"));
        }
		else if (_wcsnicmp(message, L"hashsize", 8) == 0){
            message += 9;
            TCHAR* p  = wcsstr(message,L"default");
            if(p != 0){
                p       += 8;  
                cps->UCCI_hashsize = _wtoi(p);
				LogOut(_T("引擎HASH大小: "));
				swprintf_s(buf, 512, _T("%dMB\n"), cps->UCCI_hashsize);
                LogOut(buf);  
            }
        }
		else if (_wcsnicmp(message, L"threads", 7) == 0){
			LogOut(_T("threads, 界面未处理\n"));
        }
		else if (_wcsnicmp(message, L"drawmoves", 9) == 0){
			LogOut(_T("drawmoves, 界面未处理\n"));
        }
		else if (_wcsnicmp(message, L"repetition", 10) == 0){
			LogOut(_T("repetition, 界面未处理\n"));
        }
		else if (_wcsnicmp(message, L"pruning", 7) == 0){

            message += 8;
            //char* p  = strstr(message,"default");           
            //if(p != 0){
            //    p       += 8;  
            //    StringCbPrintf(cps->UCCI_pruning,32, "%s\n", p);
            //    LogOut("引擎裁剪程度: ");
            //    LogOut(cps->UCCI_pruning);
            //}
        }
		else if (_wcsnicmp(message, L"knowledge", 9) == 0){
            message += 10;
            //char* p  = strstr(message,"default");
            //if(p != 0){
            //    p       += 8;  
            //    StringCbPrintf(cps->UCCI_knowledge,32, "%s\n", p);
            //    LogOut("引擎设定知识大小: ");
            //    LogOut(cps->UCCI_knowledge);
            //}
        }
		else if (_wcsnicmp(message, L"selectivity", 11) == 0){
            message += 12;
            //char* p  = strstr(message,"default");

            //if(p != 0){
            //    p       += 8;  
            //    StringCbPrintf(cps->UCCI_selectivity,32, "%s\n", p);
            //    LogOut("引擎选择性(随机性)系数: ");
            //    LogOut(cps->UCCI_selectivity);
            //}
        }
		else if (_wcsnicmp(message, L"style", 5) == 0){
            //LogOut(   "style, 界面未处理\n"); 
        }
		else if (_wcsnicmp(message, L"loadbook", 8) == 0){
            //LogOut(ColorChannel1,   "loadbook, 界面未处理\n",false); 
        }
		else if (_wcsnicmp(message, L"clearhash", 9) == 0){
            LogOut(_T("clearhash, 界面未处理\n")); 
        }
		else if (_wcsnicmp(message, L"dualtime", 8) == 0){

            message += 9;
            TCHAR* p  = wcsstr(message,L"default");            
            if(p != 0){
                p       += 8;  
				if (_wcsnicmp(p, L"true", 4) == 0){
                    cps->UCCI_dualtime = true;
                }
                else{
                    cps->UCCI_dualtime = false;
                }              
				LogOut(_T("引擎双时限功能: "));
                if(cps->UCCI_dualtime){
					LogOut(_T("已开启\n"));
                }
                else{
					LogOut(_T("已关闭\n"));
                }
            }
            else{
                cps->UCCI_dualtime = false;
				LogOut(_T("引擎双时限功能: "));
				LogOut(_T("已关闭\n"));
            }
        }
		else if (_wcsnicmp(message, L"newgame", 7) == 0){
            //message +=8;
            LogOut(message);
			LogOut(_T("\n"));
        }
        else{     //未识别的选项
			LogOut(_T("界面不能识别引擎发送的选项: "));
			LogOut(message);
        }
    }
    //*******************************************************************************
	else if (_wcsnicmp(message, L"uciok", 5) == 0){
        //if(cps->UCCI_initDone == FALSE){

		//if(cps->cps_stat == Cps_Waiting){
		if(cps->cps_stat == Cps_InLoading){
			PostMessage(cps->loadWin,WM_USER_YqLoad_OK,0,(LPARAM)cps);  //向引擎所在窗口发送初始化成功的信息
        }  
    }
    //*******************************************************************************
	else if (_wcsnicmp(message, L"readyok", 7) == 0){
        //空闲状态和思考状态的反馈。表明引擎处于就绪状态(可正常接收指令)。
		LogOut(cps->UCCI_name);        //输出引擎名称
        LogOut(_T("引擎已在接受指令状态!\n"));
    }
    //*******************************************************************************
	else if (_wcsnicmp(message, L"info", 4) == 0){
        //思考状态的反馈。显示引擎思考信息，通常有以下几种信息： 
        //(1) nodes <已搜索的结点数> time <已花费的时间>：思考信息中给出的时间通常以毫秒为单位，结点数和时间相除就是引擎的速度(NPS值)，单位是KNPS。 
        //(2) depth <当前搜索深度> [score <分值> pv <主要变例>]：输出引擎思考到的深度及其思考路线和好坏，
        //目前UCCI引擎《象棋巫师》只对这种信息作出处理。例如在起始局面下，
        //《象棋巫师》收到引擎的反馈：info depth 6 score 4 pv b0c2 b9c7 c3c4 h9i7 c2d4 h7e7，
        //那么界面上应该输出：“深度：6，分值：4，主要变例：马八进七 马２进３ 兵七进一 马８进９ 马七进六 炮８平５”。
        //分值通常以一个轻子(马或炮)为100分记，以上信息说明此时当前要走的一方占有相当于0.04个轻子的优势。 
        //(3) currmove <当前搜索着法>：输出引擎正在思考的着法。
		if (_wcsnicmp(message, L"info time ", 10) == 0){
			LogOut(_T("\n\n"));
			LogOut(message);
		}

        TCHAR *movestr;
        message += 5;
        if(false){
        }
			// initok
		else if (_wcsnicmp(message, L"initok", 6) == 0){

			//IsSendRand = 1;
			//佳佳引擎初始化成功了
			Sleep(300);

			//LogOut("yq initok opppppppppppppppppppppp\n");
		}
		else if (_wcsnicmp(message, L"initend", 7) == 0){
		}

		else if (_wcsnicmp(message, L"log", 3) == 0){
        }
		else if(movestr = wcsstr(message,L"currmove ")){

			movestr += 9;
			movestr[5] = 0;

			int move = str2move(cps->pos, movestr);

			TCHAR szStepName[32];

			//char szStepName = str2move(cps->pos, movestr);
			GetMoveNameSimple(cps->pos,szStepName,move,appData.moveType);

			//if (movestr = wcsstr(message, L"currmovenumber ")){

			//	int num = _wtoi(movestr);
			//}

		//	int num = 

			SendMessage(hStatusBar,SB_SETTEXT,1,(LPARAM)szStepName);  //棋步名称

			//----------------------------------------------------			
			// movestr += 21;
            // SendMessage(hStatusBar,SB_SETTEXT,2,(LPARAM)movestr);  //棋步编号
			
		}
        else if(movestr = wcsstr(message,L"multipv ")){        //引擎反馈的关键路线

			//char CurInfo[102]; //当前信息

			TCHAR *depth = wcsstr(message, L" depth ");
			TCHAR *pv = wcsstr(message, L" pv ");
			TCHAR *psc = wcsstr(message, L" score");
			TCHAR *time = wcsstr(message, L" time ");
			TCHAR *nps = wcsstr(message, L" nps ");
			TCHAR *nodes = wcsstr(message, L" nodes ");
			//TCHAR *nodess = wcsstr(message, L" neodes ");
			int firstMove = -1;	

			buf[0] = '\n';

			//int slen = (int)wcslen(message);

			//if (psc == NULL) {
			//	LogOut(message);
			//	return;
			//}


			if(pv != NULL){
				pv[0] = '\n';
				pv[1]  = '.';
				pv[2]  = ' ';
				pv[3]  = 0; 
				//strcat_s(buf,sizeof(buf), depth);
			}			

			//******************************************************************
			//if(cps->maybePonering){	
			if (cps->cps_stat == Cps_Pondering){
				firstMove = cps->PonderMoveInt;
				TCHAR sta[256];
				swprintf_s(sta, sizeof(sta) / sizeof(TCHAR), L"后台:%8s", cps->PonderName);
				SendMessage(hStatusBar, SB_SETTEXT, 0, (LPARAM)sta);
				swprintf_s(buf + 1, sizeof(buf) / sizeof(TCHAR)-2, _T("\n%s %s >>>:\n%s"), _T("后台: "), cps->PonderName, depth);
			}
			else{
				if (pDis->gameMode == AnalyzeMode){
					SendMessage(hStatusBar, SB_SETTEXT, 0, (LPARAM)L"分析...");
					swprintf_s(buf + 1, sizeof(buf) / sizeof(TCHAR)-2, _T("\n%s\n%s"), _T("分析: >>>>>>> "), depth);
				}
				else{
					SendMessage(hStatusBar, SB_SETTEXT, 0, (LPARAM)L"思考...");
					swprintf_s(buf + 1, sizeof(buf) / sizeof(TCHAR)-2, _T("\n%s\n%s"), _T("思考: >>>>>>> "), depth);
				}
			}

			TCHAR szStepName[16];

			if(psc == NULL){
			  psc = wcsstr(message,L" mate ");
			}

			if(depth == NULL){
				LogOut(message);return;
			}
			if(psc == NULL){
				LogOut(message); return;
			}

			if(nodes == NULL){
				LogOut(message); return;
			}

			if(nps == NULL){
				LogOut(message); return;
			}


			int searchTime = 0;

			if(time == NULL){
				LogOut(message); return;
			}					
			
			psc[0]   = 0;
			time[0]  = 0;
			nodes[0] = 0;

            depth += 7;
			psc   += 7;
			time  += 6;	
			nps   += 5;	

			pDis->pos->His[cps->pos->gply].search_score = (sint16)_wtoi(psc);
			//pDis->pos->His[pDis->pos->gply].book_score = NO_BOOK_SCOER;

			HDCDrawChart(TAB.dlgScore, pDis, NULL, true);

			if(pv != NULL){

				movestr = pv;
				int num  = 0;
				movestr  += 4;

				int len   = (int)wcslen(movestr);

				BOOL First = TRUE;

				while(len >= 4){
					int move = str2move(cps->pos, movestr);
					GetMoveNameSimple(cps->pos,szStepName,move,appData.moveType);
					wcscat_s(buf,sizeof(buf)/sizeof(TCHAR),szStepName);

					if(cps->cps_stat != Cps_Pondering){
						if(First == TRUE){
							First = FALSE;
                          firstMove = move;
							//SendMessage(hStatusBar,SB_SETTEXT,1,(LPARAM)szStepName);
						}
					}

					MakePosMoveOnly(cps->pos,move);
					movestr += 5;
					len     -= 5;
					num++;
				}

				int old_num = num;

				while(num > 0){
					UnMakePosMoveOnly(cps->pos);
					num--;
				}
			}

		    LogOut(buf);		
        }
		//
  //      else if(movestr = strstr(message,"time ")){        //引擎反馈的关键路线
		//	LogOut("\n\n");
		//	LogOut(message);
		//}
		//else if(movestr = strstr(message,"hashfull ")){        //引擎反馈的关键路线
		//	LogOut("\n");
		//	LogOut(message);
		//}
        else {
            LogOut(message);               //将信息显示到状态栏中
        }
        
    }
    //*******************************************************************************
	else if (_wcsnicmp(message, L"bye", 3) == 0){
        //接收到quit指令后的反馈。引擎完成了退出运转前的准备工作，
        // 通知界面，引擎将在瞬间正常退出运转。界面收到该指令后，
        // 通常只需要等待1毫秒，即可关闭输入输出通道。

        //if(cps->twoMachinesColor[0] == 'w'){
        //    LogOut(ColorSeek,    "红方引擎已成功退出!\n",false);
        //}
        //else{
        //    LogOut(ColorChannel1,"黑方引擎已成功退出!\n",false);           
        //}
        //if(cps->UCCI_which == 1){           //这是第一个引擎
        //    SendMessage(hwndToolBar,TB_ENABLEBUTTON,IDT_COM_RED,0);    
        //}
        //else{
        //    SendMessage(hwndToolBar,TB_ENABLEBUTTON,IDT_COM_BLUE,0);
        //}
        
        //cps->UCCI_initDone  = FALSE;

		//LogOut(cps->UCCI_name);        //输出引擎名称
		//LogOut("引擎已成功退出!\n\n");
    }
    //*******************************************************************************
	else if (_wcsnicmp(message, L"copyprotection", 14) == 0){
        LogOut(cps->UCCI_name);        //输出引擎名称
        message +=15;
		LogOut(_T("引擎版权认证: "));

		if (_wcsnicmp(message, L"ok", 2) == 0){
			LogOut(_T("已通过\n"));
        }
        else{
			LogOut(_T("未通过\n"));
        }
    }   
    //*******************************************************************************
    else {  //可能是其它反馈信息
        LogOut(cps->UCCI_name);        //输出引擎名称
		LogOut(_T("引擎未识别指令\n"));
		LogOut(message);
        LogOut(_T("\n"));
    }
}

