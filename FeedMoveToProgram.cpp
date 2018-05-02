#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"



void  //发送初始局面给引擎哇, 只有奇兵引擎要发送
FeedMovesToProgram(ChessProgramState *cps,int upto){
    //int i;
    //int start;
    //char fen[128];
    //char buf[FEN_SIZE];

    //int  side;

    switch(cps->ucci){
        case UCCI_UCCI_ms:
		case UCCI_UCCI_OLD:
            //从上一个不吃子步开始发送走步 
            //首先得到不吃子的第一个局面的编号:
            //if(upto == 0){
            //    position_to_fen_by_b256(DIS.pos.B256dis[0],WHITE,fen);
            //    StringCbPrintf(buf,MSG_SIZ,"position fen %s\n",fen);
            //}
            //else{
            //    start = upto - DIS.pos.His[upto].nonCap;

            //    if(start%2 == 0){
            //        side = WHITE;
            //    }
            //    else{
            //        side = BLACK;
            //    }
            //    position_to_fen_by_b256(DIS.pos.B256dis[start],side,fen);
            //    StringCbPrintf(buf,MSG_SIZ,"position fen %s moves",fen);
            //    char* pb = buf + strlen(buf);
            //    for(int i = start; i <= upto; i++){
            //        StringCbPrintf(pb,FEN_SIZE," %s",DIS.pos.parseList[i]);
            //        pb += 5; 
            //    }
            //    StringCbPrintf(pb+1, FEN_SIZE,"\n");
            //}            
            //SendToProgram(buf,cps);
            break;
		case UCCI_GGchess:
            //if (appData.debugMode)
            //    fprintf(DIS.debugFP, "Feeding %smoves %d through %d to %s chess program\n",
            //    DIS.startedFromSetupPosition ? "position and " : "",
            //    DIS.backwardMostMove, upto, cps->UCCI_name);
            //SendToProgram("force\n", cps);
            //if (DIS.startedFromSetupPosition) {
            //    SendBoard(cps, DIS.backwardMostMove);
            //}
            //for (int i = DIS.backwardMostMove; i < upto; i++) {
            //    SendMoveToProgram(i, cps);
            //}
			break;
        case UCCI_CYC105:
            break;
        case UCCI_QianHong:
            break;

        default:
            break;

    }



    //char fen[MSG_SIZ];

    //ParaseDisMoveToUCCImove(DIS.moveList[moveNum],DIS.parseList[moveNum],cps->ucci);

    //PositionToFEN(fen, moveNum, cps->ucci);
    //StringCbPrintf(buf,MSG_SIZ,"position fen %s moves %s \n",fen,DIS.parseList[moveNum]);
    //SendToProgram(buf, cps); //不要重复发送哇
}

/* Assumes program was just initialized (initString sent).
   Leaves program in force mode. */
//void
//FeedMovesToProgram(cps, upto) 
//ChessProgramState *cps;
//int upto;
//{
//    int i;
//
//    if (appData.debugMode)
//        fprintf(debugFP, "Feeding %smoves %d through %d to %s chess program\n",
//        startedFromSetupPosition ? "position and " : "",
//        backwardMostMove, upto, cps->which);
//    SendToProgram("force\n", cps);
//    if (startedFromSetupPosition) {
//        SendBoard(cps, backwardMostMove);
//    }
//    for (i = backwardMostMove; i < upto; i++) {
//        SendMoveToProgram(i, cps);
//    }
//}

