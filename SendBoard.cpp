#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

void		//发送一个盘面到引擎
SendBoard(ChessProgramState *cps,int moveNum){
    TCHAR message[MSG_SIZ];
	TCHAR fen[MSG_SIZ];

	dispboard_t* pDis = (dispboard_t*)cps->pDis;

    /*PositionToFEN(fen,moveNum,cps->ucci);*/
    switch(cps->ucci){
        case UCCI_UCCI_ms:	
		case UCCI_UCCI_OLD:
            //StringCbPrintf(message,MSG_SIZ,"position fen %s\n", fen);
            ////free(fen);
            //SendToProgram(message, cps);
            //这个就不用了
            break;
        case UCCI_CYC105:
            break;
        case UCCI_QianHong:			
            swprintf_s(message,MSG_SIZ,L"FEN %s\n", fen);
            //free(fen);
            SendToProgram(message, cps);
            break;
        default:
            PositionToFEN(pDis, fen,moveNum,cps->ucci);
            if (cps->useSetboard) {				
				swprintf_s(message, MSG_SIZ, L"setboard %s\n", fen);
                SendToProgram(message, cps);
                free(fen);
            }
            else {

            }
            break;
    }

}