#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

int GetMovesToGoByDis(dispboard_t* pDis, TimeDisp_t *pt){
	//return 40;

	//int ret = 1;

	//int step = pDis->pos->gply / 2 + 1;

	//if(step < pt->c1step){
	//	ret  = pt->c1step - step;
	//}
	//else{
	//	ret =  pt->c2step - ((step - pt->c1step + 1) % pt->c2step);

	//	if( ret == 0){		
	//		ret = pt->c2step;
	//	}
	//}

	//return ret; 

	int ret;

	int total_nb = pDis->pos->gply / 2;

	if(total_nb < pt->c1step){
		ret = pt->c1step - (total_nb % pt->c1step);
	}
	else{
		ret = pt->c2step - ((total_nb - pt->c1step) % pt->c2step);
	}

	return ret;
}

void SendProgramGo(ChessProgramState *cps, CPS_STAT go_type, TCHAR* premove){

	TCHAR buf[MSG_SIZ];
	TCHAR tmp[MSG_SIZ];

    //dispboard_t* pDis = OBS[cps->table];

	dispboard_t* pDis = (dispboard_t*)cps->pDis;

    if(cps->playWhat == NEUTRAL){
        //MessageBox(pDis->hwndThis,"出错啦!", "引擎不是走子方!!",MB_OK);

		LogOut(_T("\n出错了,引擎不是走子方!!\n"));
        return;
    }


	if (pDis->gameMode != AnalyzeMode){		//不是分析模式,就要截平gply
		cps->PonderStop = FALSE;
		TruncateGame(pDis);					
	}

	if(go_type == Cps_Pondering){
		if(cps->playWhat != (pDis->pos->side ^0x1)){
			LogOut(_T("引擎不是走子方!\n"));
			return;
		}
	}
	else{
		if(cps->playWhat != pDis->pos->side){
			LogOut(_T("引擎不是走子方!\n"));
			return;
		}
	}

	//首先发送初始局面, 	
	
	StartClocks(pDis);			//开始计时	

	if(cps->cps_stat == Cps_Pondering){		//引擎正在后台思考
		if(go_type == Cps_Thinking){
			//看一下是不是命中的后台
			TCHAR *pm = cps->PonderMove;		
			
			if(wcslen(pm) >= 4 && (pm[0] == premove[0] && pm[1] == premove[1] && pm[2] == premove[2] && pm[3] == premove[3])){
				SendToProgram(L"ponderhit\n",cps);
				cps->cps_stat = go_type;
				//LogOut("\n引擎走步调试输出：ponderhit\n");
				
				LogOut(_T("\n************************\n哈哈! 后台命中棋步!!\n************************"));
				return;
			}
			else{	//在后台先要停止思考，再搜索
				SendToProgram(L"stop\n",cps);
				cps->PonderStop = TRUE;
				return;
			}
		}
	}

	cps->cps_stat = go_type;

	if (go_type == Cps_Thinking) {

		if (cps->ucci == UCCI_GGchess) {
			//佳佳象棋得看一下是不是有开局步可走，如有，则不要思考了
			//HandleMachineMove(char *message, ChessProgramState *cps)

			/*if(pDis->pos->gply <= BOOK_MOVE_USE_PLY){*/

			//if(pDis->pos->gply <= (cps->UCCI_Book_Num * 2)){

			//if (cps->useBook == TRUE) {		//使用开局库

			//	int bookmove = HaveBookMoveInDB(pDis);

			//	if (bookmove) {

			//		TCHAR movestr[16];
			//		move2str(bookmove, movestr);

			//		//这儿发送棋库棋步到引擎，让引擎反馈棋步
			//		swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), L"cmd bookmove %s\n", movestr);

			//		SendToProgram(buf, cps);

			//		return;
			//	}
			//}

		}
	}

	//cps->UCCI_havePonder = FALSE;
	//SendMoveToProgram(pDis,cps, cps->UCCI_ponderMove);

	if(go_type == Cps_Pondering){						//要进入后台思考
	   
		if(cps->PonderMove[0] != 0){
			SendMoveToProgram(pDis, cps, cps->PonderMove);
		}
		else{
			LogOut(_T("当前还没有后台思考棋步可用\n"));
			cps->cps_stat = Cps_Waiting;
			return;
		}
	}
	else{
		SendMoveToProgram(pDis,cps,NULL);
	}

	TimeDisp_t *pt;
	TimeDisp_t *pother;

	pt      = &pDis->TimeDisp[0];
	pother  = &pDis->TimeDisp[1];

	if(go_type == Cps_Thinking || go_type == Cps_Pondering || go_type == Cps_Analyse){
		
		switch(cps->ucci){
			case UCCI_UCCI_ms:

				break;
			case UCCI_GGchess:
				swprintf_s(buf,sizeof(buf)/sizeof(TCHAR),L"go");

				if(go_type == Cps_Analyse){			   //当前是分析模式
					wcscat_s(buf, sizeof(buf) / sizeof(TCHAR), L" infinite");
				}
				
				else{
                    
					if(go_type == Cps_Thinking && pt->SetDepth != 0){
						swprintf_s(tmp, sizeof(tmp) / sizeof(TCHAR), L" depth %d", pt->SetDepth);
						wcscat_s(buf, sizeof(buf) / sizeof(TCHAR), tmp);
					}
					else{

						//if(pother->RemainTime <= 3000){
						//	pother->RemainTime = 3000;
						//}

						if(pt->RemainTime < 60000){
							pt->RemainTime /= 3;
						}

						if(pt->RemainTime <= 10000){
							pt->RemainTime = 800;
						}
						
						swprintf_s(tmp, sizeof(tmp) / sizeof(TCHAR), L" wtime %d btime %d", pt->RemainTime, pother->RemainTime);
						wcscat_s(buf, sizeof(buf) / sizeof(TCHAR), tmp);

						//time inc
						if(pt->inc != 0 || pother->inc != 0){
							swprintf_s(tmp, sizeof(tmp) / sizeof(TCHAR), L" winc %d binc %d", pt->inc, pother->inc);
							wcscat_s(buf, sizeof(buf) / sizeof(TCHAR), tmp);
						}

						//mps 
						if(pt->isBaoGan == FALSE){			//是分段计时
							swprintf_s(tmp, sizeof(tmp) / sizeof(TCHAR), L" movestogo %d", GetMovesToGoByDis(pDis, pt));
							wcscat_s(buf, sizeof(buf) / sizeof(TCHAR), tmp);
						}
					}

					if(go_type == Cps_Pondering){
						wcscat_s(buf, sizeof(buf) / sizeof(TCHAR), L" ponder");
					}
				}
				break;
			case UCCI_UCCI_OLD:
				break;
			case UCCI_CYC105:
				break;
			default:
				break;
		}

		//加上一个回车
		wcscat_s(buf, sizeof(buf) / sizeof(TCHAR), L"\n");

	}
	else if(go_type == Cps_Analyse){
		switch(cps->ucci){
			case UCCI_UCCI_ms:
				swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), L"go infinite\n");
				break;
			case UCCI_UCCI_OLD:
				swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), L"go infinite\n");
				break;
			case UCCI_GGchess:
				swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), L"go infinite\n");
				break;
			default:
				//
				LogOut(_T("\n对不起，本引擎的协议暂不支持分析模式"));
				cps->cps_stat = Cps_Waiting;
				break;
		}
	}
	else{
		ASSERT(false);
	}

	SendToProgram(buf,cps);

}
