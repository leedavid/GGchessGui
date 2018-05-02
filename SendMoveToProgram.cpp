#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

//void
//SendMoveToProgram(moveNum, cps)
//     int moveNum;
//     ChessProgramState *cps;
//{
//    char buf[MSG_SIZ];
//    if (cps->useUsermove) {
//      SendToProgram("usermove ", cps);
//    }
//    if (cps->useSAN) {
//      char *space;
//      if ((space = strchr(parseList[moveNum], ' ')) != NULL) {
//	int len = space - parseList[moveNum];
//	memcpy(buf, parseList[moveNum], len);
//	buf[len++] = '\n';
//	buf[len] = NULLCHAR;
//      } else {
//	sprintf(buf, "%s\n", parseList[moveNum]);
//      }
//      SendToProgram(buf, cps);
//    } else {
//      SendToProgram(moveList[moveNum], cps);
//    }
//}
//
//void		//发送走步到引擎,注意只是发送用户走了一步,并不要叫诉引擎要走棋!!!
//SendMoveToProgram(int moveNum, ChessProgramState *cps){


void		//发送走步到引擎,注意只是发送用户走了一步,并不要叫诉引擎要走棋!!!
SendMoveToProgram(dispboard_t* pDis, ChessProgramState *cps, TCHAR* ponderMove){
    TCHAR   buf[FEN_SIZE];
	TCHAR *   pb;
	TCHAR    fen[MSG_SIZ];
    int     start;
    int     startSide;

    int     gply   = pDis->pos->gply;
    int     nonCap = pDis->pos->His[gply].nonCap;

	if (pDis->gameMode != AnalyzeMode){
		if(gply != pDis->pos->curStep){
			LogOut(_T("出错了,在发送初始局面时,步数不正确!\n"));
			return;
		}
	}
	else{                                  //这是分析模式
		gply   = pDis->pos->curStep;
		nonCap = pDis->pos->His[gply].nonCap;
	}

	//if(cps->maybeThinking || cps->maybePonering){                 //如果引擎正在后台思考
	//	SendToProgram("stop\n",cps);
	//	Sleep(1);		
	//}

    //解析走步到命令
    //if(moveNum>0){
    //    ParaseDisMoveToUCCImove(DIS.moveList[moveNum-1],DIS.parseList[moveNum-1],cps->ucci);
    //}
    //ParaseDisMoveToUCCImove(DIS.moveList[moveNum],DIS.parseList[moveNum],cps->ucci);



	//将当前的局面复制一下
	memcpy(cps->pos, pDis->pos, sizeof(position_t));

	if(ponderMove != NULL){

		int pmove = str2move(cps->pos, cps->PonderMove);

		//cps->PonderMoveInt = pmove;
		//cps->PonderName[9] = 0; 
		GetMoveNameSimple(cps->pos,cps->PonderName,pmove,appData.moveType);
		MakePosMoveOnly(cps->pos,pmove);
		cps->pos->gply++;
	}

	//if(cps->UCCI_havePonder){

	//	int m = cps->pos->His[cps->pos->curStep].move;

	//	UnMakePosMoveOnly(cps->pos);

	//	cps->pdmove = str2move(cps->pos,ponderMove+1);  //这儿要加一

	//	MakePosMoveOnly(cps->pos,m);
	//}

 //   int finalStep = gply;
	//if(ponder == TRUE){
	//	finalStep ++;
	//}

    switch(cps->ucci){
        case UCCI_UCCI_ms:	  //在这儿还得发送一下时间控制给UCCI
		case UCCI_UCCI_OLD:
            //
            //发送最一个不吃子的局面  
            startSide = pDis->pos->side ^ (nonCap%2);
            start     = gply - nonCap;


            position_to_fen_by_b256(pDis->B256dis[start],startSide,fen);

			swprintf_s(buf, FEN_SIZE, L"position fen %s moves", fen);


            pb = buf + wcslen(buf);

            for(int i = start; i < gply; i++){

				swprintf_s(pb,FEN_SIZE,L" %s", pDis->parseList[i]);
                pb += 5;
            }

			if(ponderMove != NULL){
				wcscat_s(buf, sizeof(buf) / sizeof(TCHAR), L" ");
				wcscat_s(buf, sizeof(buf) / sizeof(TCHAR), ponderMove);
				//cps->UCCI_havePonder = FALSE;
			}

			wcscat_s(buf, sizeof(buf) / sizeof(TCHAR), L"\n");

            SendToProgram(buf,cps);   //发送初始局面 

            break;
		case UCCI_GGchess:

            //发送最一个不吃子的局面  
            startSide = pDis->pos->side ^ (nonCap%2);
            start     = gply - nonCap;


            position_to_fen_by_b256(pDis->B256dis[start],startSide,fen);

           swprintf_s(buf,FEN_SIZE,L"fen %s moves",fen);

            pb = buf + wcslen(buf);

            for(int i = start; i < gply; i++){
				swprintf_s(pb, FEN_SIZE/2, L" %s", pDis->parseList[i]);
                pb += 5;
            }

			if(ponderMove != NULL){
				wcscat_s(buf, sizeof(buf) / sizeof(TCHAR), L" ");
				wcscat_s(buf, sizeof(buf) / sizeof(TCHAR), ponderMove);
				//cps->UCCI_havePonder = FALSE;
			}

			wcscat_s(buf, sizeof(buf) / sizeof(TCHAR), L"\n");

            SendToProgram(buf,cps);   //发送初始局面 

#ifdef  USE_OUT_FEN_TO_LOG
			LogOut(buf);
#endif

            break;
		//
        case UCCI_CYC105:

            //发送最一个不吃子的局面  
            startSide = pDis->pos->side ^ (nonCap%2);
            start     = gply - nonCap;


            position_to_fen_by_b256(pDis->B256dis[start],startSide,fen);

			swprintf_s(buf, FEN_SIZE, L"fen %s moves", fen);

            pb = buf + wcslen(buf);

            for(int i = start; i < gply; i++){
				swprintf_s(pb, FEN_SIZE, L" %s", pDis->parseList[i]);
                pb += 5;
            }

			if(ponderMove != NULL){
				wcscat_s(buf, sizeof(buf) / sizeof(TCHAR), L" ");
				wcscat_s(buf, sizeof(buf) / sizeof(TCHAR), ponderMove);
				//cps->UCCI_havePonder = FALSE;
			}

			wcscat_s(buf, sizeof(buf) / sizeof(TCHAR), L"\n");

            SendToProgram(buf,cps);   //发送初始局面 
            break;
		//
        case UCCI_QianHong:			
            //StringCbPrintf(buf,MSG_SIZ,"PLAY %s",DIS.parseList[moveNum]);
            //SendToProgram(buf, cps);
            //SendToProgram("AI\n", cps);
            //SendToProgram("AI",cps);
            //浅红典型的中断AI 命令只在用户关闭应用程序或退出当前棋局时. 
            //例外是和TIMEOUT命令, 它, 如果被支持, 被发送到引起 AI 停止思考
            //并回应使用到目前为止提出来的最好的棋步.
            break;
        //
        default:			
            //StringCbPrintf(buf,MSG_SIZ,"force %s\n",DIS.parseList[moveNum]);
            //StringCbPrintf(buf,MSG_SIZ,"%s\n",DIS.parseList[moveNum]);
            //SendToProgram(buf, cps);
            //SendToProgram("go\n", cps);
            break;

    }


}