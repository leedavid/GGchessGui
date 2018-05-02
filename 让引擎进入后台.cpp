#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

//void LetCpsPonder(ChessProgramState *cps){
//
//	char buf[MSG_SIZ];
//	//
//	dispboard_t* pDis = OBS[cps->table];
//
//	//首先发送初始局面, 
//
//	if(cps->UCCI_havePonder == FALSE){
//		return;
//	}
//
//	LogOut("\n引擎后台思考棋步:");
//	LogOut(cps->UCCI_ponderMove);
//
//	SendMoveToProgram(pDis,cps, cps->UCCI_ponderMove);
//	
//	 switch(cps->ucci){
//		 case UCCI_UCCI_ms:
//			 sprintf_s(buf,sizeof(buf),"%s", "go ponder\n");
//			 break;
//		 case UCCI_GGchess:
//			 sprintf_s(buf,sizeof(buf),"%s", "go ponder\n");
//			 break;
//		 case UCCI_UCCI_OLD:
//			 sprintf_s(buf,sizeof(buf),"%s", "go ponder\n");
//			 break;
//		 case UCCI_CYC105:
//			 sprintf_s(buf,sizeof(buf),"%s", "go ponder\n");
//			 break;
//		 default:
//			 sprintf_s(buf,sizeof(buf),"%s", "go ponder\n");
//			 break;
//	 }
//
//	 SendToProgram(buf,cps);
//	 //StartClocks(pDis);			//开始计时
//	 cps->maybePonering = TRUE;
//
//	 //PostMessage(hwndToolBar,TB_ENABLEBUTTON,IDT_Stop,1);
//
//}

//void SendProgramGo(ChessProgramState *cps){
//
//	  char buf[MSG_SIZ];
//
//    dispboard_t* pDis = OBS[cps->table];
//
//    if(cps->playWhat == NEUTRAL){
//        MessageBox(pDis->hwndThis,"出错啦!", "引擎不是走子方!!",MB_OK);
//        return;
//    }
//    if(cps->maybeThinking == TRUE){
//        MessageBox(pDis->hwndThis,"出错啦!", "引擎还在思考!!",MB_OK);
//        return;
//    }    
//
//    TruncateGame(pDis);
//
//    if(cps->playWhat != pDis->pos->side){
//        LogOut("引擎不是走子方!\n");
//        return;
//    }
//
//
//	if(cps->ucci == UCCI_GGchess){
//		//佳佳象棋得看一下是不是有开局步可走，如有，则不要思考了
//		//HandleMachineMove(char *message, ChessProgramState *cps)
//
//		if(cps->useBook == TRUE){		//使用开局库
//
//			int bookmove = HaveBookMoveInDB(pDis->pos, MST->book);
//
//			if(bookmove){
//
//				char movestr[16];
//
//				move2str(bookmove,movestr);
//
//				sprintf_s(buf,sizeof(buf),"bestmove %s\n",movestr);
//
//				HandleMachineMove(buf,cps);
//
//				return;
//			}
//		}
//	}
//
//
//	//首先发送初始局面, 
//	cps->UCCI_havePonder = FALSE;
//	SendMoveToProgram(pDis,cps, cps->UCCI_ponderMove);
//
//	
//
//    TimeDisp_t *pt      = &pDis->TimeDisp[cps->playWhat];
//    TimeDisp_t *pother  = &pDis->TimeDisp[cps->playWhat ^ 0x1];
//
//    switch(cps->ucci){
//        case UCCI_UCCI_ms:
//			if(pt->SetDepth == 0){
//				//没步时限制-----------------------------------------
//				if(pt->SetStepTime == 0){			
//					if(pt->isBaoGan == TRUE){		//包干计时
//						sprintf_s(buf,sizeof(buf),"go wtime %d btime %d\n",
//							pt->RemainTime, pother->RemainTime);
//					}
//					else{							//分段计时
//						pt->movestogo = GetMovesToGoByDis(pDis,pt);
//						sprintf_s(buf,sizeof(buf),"go wtime %d btime %d movestogo %d\n",
//							pt->RemainTime, pother->RemainTime, pt->movestogo);
//					}
//				}
//				//有步时限制-----------------------------------------
//				else{								
//					if(pt->isBaoGan == TRUE){
//						sprintf_s(buf,sizeof(buf),"go wtime %d btime %d movetime %d\n",
//							pt->RemainTime, pother->RemainTime, pt->movetime);
//					}
//					else{							//分段计时
//						pt->movestogo = GetMovesToGoByDis(pDis,pt);
//						sprintf_s(buf,sizeof(buf),"go wtime %d btime %d movestogo %d movetime %d\n",
//							pt->RemainTime, pother->RemainTime, pt->movestogo, pt->movetime);
//					}
//				}
//			}
//			//(pt->SetDepth != 0){
//			else{
//				//没步时限制-----------------------------------------
//				if(pt->SetStepTime == 0){			
//					if(pt->isBaoGan == TRUE){		//包干计时
//						sprintf_s(buf,sizeof(buf),"go wtime %d btime %d depth %d\n",
//							pt->RemainTime, pother->RemainTime, pt->SetDepth);
//					}
//					else{							//分段计时
//						pt->movestogo = GetMovesToGoByDis(pDis,pt);
//						sprintf_s(buf,sizeof(buf),"go wtime %d btime %d movestogo %d depth %d\n",
//							pt->RemainTime, pother->RemainTime, pt->movestogo, pt->SetDepth);
//					}
//				}
//				//有步时限制-----------------------------------------
//				else{							    
//					if(pt->isBaoGan == TRUE){		//不是包干计时
//						sprintf_s(buf,sizeof(buf),"go wtime %d btime %d depth %d movetime %d\n",
//							pt->RemainTime, pother->RemainTime, pt->SetDepth, pt->movetime);
//					}
//					else{							//分段计时
//						pt->movestogo = GetMovesToGoByDis(pDis,pt);
//						sprintf_s(buf,sizeof(buf),"go wtime %d btime %d movestogo %d depth %d movetime %d\n",
//							pt->RemainTime, pother->RemainTime,  pt->movestogo, pt->SetDepth, pt->movetime);
//					}
//				}
//			}
//
//            break;
//		case UCCI_UCCI_OLD:
//			if(pt->SetDepth == 0){
//				//没步时限制-----------------------------------------
//				if(pt->SetStepTime == 0){			
//					if(pt->isBaoGan == TRUE){		//包干计时
//						sprintf_s(buf,sizeof(buf),"go wtime %d btime %d\n",
//							pt->RemainTime/1000, pother->RemainTime/1000);
//					}
//					else{							//分段计时
//						pt->movestogo = GetMovesToGoByDis(pDis,pt);
//						sprintf_s(buf,sizeof(buf),"go wtime %d btime %d movestogo %d\n",
//							pt->RemainTime/1000, pother->RemainTime/1000, pt->movestogo);
//					}
//				}
//				//有步时限制-----------------------------------------
//				else{								
//					if(pt->isBaoGan == TRUE){
//						sprintf_s(buf,sizeof(buf),"go wtime %d btime %d movetime %d\n",
//							pt->RemainTime/1000, pother->RemainTime/1000, pt->movetime/1000);
//					}
//					else{							//分段计时
//						pt->movestogo = GetMovesToGoByDis(pDis,pt);
//						sprintf_s(buf,sizeof(buf),"go wtime %d btime %d movestogo %d movetime %d\n",
//							pt->RemainTime/1000, pother->RemainTime/1000, pt->movestogo, pt->movetime/1000);
//					}
//				}
//			}
//			//(pt->SetDepth != 0){
//			else{
//				//没步时限制-----------------------------------------
//				if(pt->SetStepTime == 0){			
//					if(pt->isBaoGan == TRUE){		//包干计时
//						sprintf_s(buf,sizeof(buf),"go wtime %d btime %d depth %d\n",
//							pt->RemainTime/1000, pother->RemainTime/1000, pt->SetDepth);
//					}
//					else{							//分段计时
//						pt->movestogo = GetMovesToGoByDis(pDis,pt);
//						sprintf_s(buf,sizeof(buf),"go wtime %d btime %d movestogo %d depth %d\n",
//							pt->RemainTime/1000, pother->RemainTime/1000, pt->movestogo, pt->SetDepth);
//					}
//				}
//				//有步时限制-----------------------------------------
//				else{							    
//					if(pt->isBaoGan == TRUE){		//不是包干计时
//						sprintf_s(buf,sizeof(buf),"go wtime %d btime %d depth %d movetime %d\n",
//							pt->RemainTime/1000, pother->RemainTime/1000, pt->SetDepth, pt->movetime/1000);
//					}
//					else{							//分段计时
//						pt->movestogo = GetMovesToGoByDis(pDis,pt);
//						sprintf_s(buf,sizeof(buf),"go wtime %d btime %d movestogo %d depth %d movetime %d\n",
//							pt->RemainTime/1000, pother->RemainTime/1000,  pt->movestogo, pt->SetDepth, pt->movetime/1000);
//					}
//				}
//			}
//
//            break;
//		//
//		case UCCI_GGchess:
//
//    		//
//			if(pt->SetDepth == 0){
//				//没步时限制-----------------------------------------
//				if(pt->SetStepTime == 0){			
//					if(pt->isBaoGan == TRUE){		//包干计时
//						sprintf_s(buf,sizeof(buf),"go wtime %d btime %d\n",
//							pt->RemainTime, pother->RemainTime);
//					}
//					else{							//分段计时
//						pt->movestogo = GetMovesToGoByDis(pDis,pt);
//						sprintf_s(buf,sizeof(buf),"go wtime %d btime %d movestogo %d\n",
//							pt->RemainTime, pother->RemainTime, pt->movestogo);
//					}
//				}
//				//有步时限制-----------------------------------------
//				else{								
//					if(pt->isBaoGan == TRUE){
//						sprintf_s(buf,sizeof(buf),"go wtime %d btime %d movetime %d\n",
//							pt->RemainTime, pother->RemainTime, pt->movetime);
//					}
//					else{							//分段计时
//						pt->movestogo = GetMovesToGoByDis(pDis,pt);
//						sprintf_s(buf,sizeof(buf),"go wtime %d btime %d movestogo %d movetime %d\n",
//							pt->RemainTime, pother->RemainTime, pt->movestogo, pt->movetime);
//					}
//				}
//			}
//			//(pt->SetDepth != 0){
//			else{
//				//没步时限制-----------------------------------------
//				if(pt->SetStepTime == 0){			
//					if(pt->isBaoGan == TRUE){		//包干计时
//						sprintf_s(buf,sizeof(buf),"go wtime %d btime %d depth %d\n",
//							pt->RemainTime, pother->RemainTime, pt->SetDepth);
//					}
//					else{							//分段计时
//						pt->movestogo = GetMovesToGoByDis(pDis,pt);
//						sprintf_s(buf,sizeof(buf),"go wtime %d btime %d movestogo %d depth %d\n",
//							pt->RemainTime, pother->RemainTime, pt->movestogo, pt->SetDepth);
//					}
//				}
//				//有步时限制-----------------------------------------
//				else{							    
//					if(pt->isBaoGan == TRUE){		//不是包干计时
//						sprintf_s(buf,sizeof(buf),"go wtime %d btime %d depth %d movetime %d\n",
//							pt->RemainTime, pother->RemainTime, pt->SetDepth, pt->movetime);
//					}
//					else{							//分段计时
//						pt->movestogo = GetMovesToGoByDis(pDis,pt);
//						sprintf_s(buf,sizeof(buf),"go wtime %d btime %d movestogo %d depth %d movetime %d\n",
//							pt->RemainTime, pother->RemainTime,  pt->movestogo, pt->SetDepth, pt->movetime);
//					}
//				}
//			}
//
//			break;
//		//
//        case UCCI_CYC105:
//
//
//			sprintf_s(buf,sizeof(buf), "go wtime %d btime %d \n",
//                    pt->RemainTime,pother->RemainTime);   
//            break;
//		//
//        case UCCI_QiBing:	
//			sprintf_s(buf,sizeof(buf),"%s","go\n");         
//            break;
//		//
//        default:
//
//			sprintf_s(buf,sizeof(buf), "go wtime %d btime %d \n",
//                    pt->RemainTime,pother->RemainTime);   
//            break;
//    }
//
//	
//	SendToProgram(buf,cps);
//
//	StartClocks(pDis);			//开始计时
//
//	cps->maybeThinking = TRUE;
//    
//}
