#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

char _pieceToCharUCCI[] = {
	'X', 'P', 'p', 'C', 'c', 'R', 'r', 'N', 'n', 'B', 'b', 'A', 'a','K','k','T'
};
char _pieceToCharUCCIQH[] = {
	'X', 'P', 'p', 'C', 'c', 'R', 'r', 'H', 'h', 'E', 'e', 'A', 'a','K','k','T'
};
char _pieceToCharDIS[] = {
	'X', 'P', 'p', 'C', 'c', 'R', 'r', 'H', 'h', 'E', 'e', 'A', 'a','K','k','T'
};

char _pieceToChar[UCCI_OTHER+1][32] = {
    //{  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
	//  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31},
	//UCCI_NONE
	{    0,  1,  2,  3,  4,'p','P',  7,  8,'c','C', 11, 12,'r','R', 15,
	    16,'n','N', 19, 20,'b','B', 23, 24,'a','A', 27, 28,'k','K', 31},
	//UCCI_UCCI
	{    0,  1,  2,  3,  4,'p','P',  7,  8,'c','C', 11, 12,'r','R', 15,
	    16,'n','N', 19, 20,'b','B', 23, 24,'a','A', 27, 28,'k','K', 31},
	//UCCI_QH
	{    0,  1,  2,  3,  4,'p','P',  7,  8,'c','C', 11, 12,'r','R', 15,
	    16,'h','H', 19, 20,'e','E', 23, 24,'a','A', 27, 28,'k','K', 31},
	//UCCI_DIS
	{    0,  1,  2,  3,  4,'p','P',  7,  8,'c','C', 11, 12,'r','R', 15,
	    16,'n','N', 19, 20,'b','B', 23, 24,'a','A', 27, 28,'k','K', 31},
	//UCCI_OTHER
	{    0,  1,  2,  3,  4,'p','P',  7,  8,'c','C', 11, 12,'r','R', 15,
	    16,'n','N', 19, 20,'b','B', 23, 24,'a','A', 27, 28,'k','K', 31},
};

//char _pieceToChar[] = {
//    'X', 'P', 'p', 'C', 'c', 'R', 'r', 'H', 'h', 'E', 'e', 'A', 'a','K','k','T'
//};



char 
PieceToCharUCCI(sq_t p, int ucci){
	return _pieceToChar[ucci][p];
}
int //是否被将死了哇
IsMateDead(position_t* pos){	
    gen_legal_moves(pos);

	while ((pos->pMend) > pos->all_move){
		pos->pMend--;
		if (move_is_legal(pos, pos->pMend->move)){
			return FALSE;
		}
	}

	return TRUE;

 //   if(pos->pMend == pos->all_move){
 //       return true;
 //   }
	//return false;		//是否将死了
}

int
IsInCheck(position_t* pos, int side){
    if(side == WHITE){     //红方是不是被将军了
        int nMyKing = PieceListStart(pos,RKING); 

        ASSERT(nMyKing != 0);

        int kx      = StoX(nMyKing);
        int ky      = StoY(nMyKing);

        //得到将的上下信息
        SlideMoveStruct *psmv;
        
        psmv = FileMove(ky,pos->wBitFiles[kx]);
        //得到上面第一个棋子
        int tmp = psmv->RookCap[DUpLeft] + kx;
        if(tmp != nMyKing){
            int checkChess  = pos->b256[tmp];
            if(    checkChess == BCHE || checkChess == BKING
                || (checkChess == BPAWN && tmp+16 == nMyKing)){
                    return (1);
            }
            //有了第一个棋子,才有第二个棋子哇
            tmp = psmv->CannonCap[DUpLeft] + kx;
            if(tmp != nMyKing){
                if(pos->b256[tmp] == BPAO){
                    return (1);
                }
            }           
        }
        //得到将下面的第一个棋子
        tmp = psmv->RookCap[DLoRight] + kx;
        if(tmp != nMyKing){
            if(pos->b256[tmp] == BCHE){
                return (1);
            }
            //有了第一个棋子,才有第二个棋子哇
            tmp = psmv->CannonCap[DLoRight] + kx;
            if(tmp != nMyKing){
                if(pos->b256[tmp] == BPAO){
                    return (1);
                }
            } 
        }

        psmv = RankMove(kx,pos->wBitRanks[ky]);
        int nDisp = nMyKing & 0xf0;
        //得到将左面的第一个棋子
        tmp = psmv->RookCap[DUpLeft] + nDisp;
        if(tmp != nMyKing){
            int checkChess  = pos->b256[tmp];
            if(     (checkChess == BCHE)
                ||(checkChess == BPAWN && tmp == nMyKing-1)){
                return (1);
            }
            //有了第一个棋子,才有第二个棋子哇
            tmp = psmv->CannonCap[DUpLeft] + nDisp;
            if(tmp != nMyKing){
                if(pos->b256[tmp] == BPAO){
                    return (1);
                }
            }
        }
        //得到将右面第一个棋子
        tmp = psmv->RookCap[DLoRight] + nDisp;
        if(tmp != nMyKing){
            int checkChess  = pos->b256[tmp];
            if(     (checkChess == BCHE)
                ||(checkChess == BPAWN && tmp == nMyKing+1)){
                return (1);
            }
            //有了第一个棋子,才有第二个棋子哇
            tmp = psmv->CannonCap[DLoRight] + nDisp;
            if(tmp != nMyKing){
                if(pos->b256[tmp] == BPAO){
                    return (1);
                }
            }
        }

         //是不是被马将军了
        for(int checkSq256 = PieceListStart(pos,BMA); checkSq256 > 0x32; checkSq256 = NextPiece(pos,checkSq256)){
            int m = horseLegTab(nMyKing - checkSq256 + 256);
            if(m && !pos->b256[checkSq256+m]){
                return (1);
            }
        }
    }
    else{                       //黑方是不是被将军了

        int nMyKing = PieceListStart(pos,BKING); 

        ASSERT(nMyKing != 0);

        int kx      = StoX(nMyKing);
        int ky      = StoY(nMyKing);

         //是不是被马将军了
        for(int checkSq256 = PieceListStart(pos,RMA); checkSq256 > 0x32; checkSq256 = NextPiece(pos,checkSq256)){
            int m = horseLegTab(nMyKing - checkSq256 + 256);
            if(m && !pos->b256[checkSq256+m]){
                return (1);
            }
        }
       
         //得到将的上下信息
        SlideMoveStruct *psmv;
        
        psmv = FileMove(ky,pos->wBitFiles[kx]);
        
        //得到下面第一个棋子
        int tmp = psmv->RookCap[DLoRight] + kx;
        if(tmp != nMyKing){
            int checkChess  = pos->b256[tmp];
            if((checkChess == RCHE) || checkChess == RKING
                ||(checkChess == RPAWN && tmp-16 == nMyKing)){
                    return (1);
            }
            //有了第一个棋子,才有第二个棋子哇
            tmp = psmv->CannonCap[DLoRight] + kx;
            if(tmp != nMyKing){
                if(pos->b256[tmp] == RPAO){
                    return (1);
                }
            } 
        }
        //得到上面第一个棋子
        tmp = psmv->RookCap[DUpLeft] + kx;
        if(tmp != nMyKing){
            if(pos->b256[tmp] == RCHE){
                return (1);
            }
            //有了第一个棋子,才有第二个棋子哇
            tmp = psmv->CannonCap[DUpLeft] + kx;
            if(tmp != nMyKing){
                if(pos->b256[tmp] == RPAO){
                    return (1);
                }
            } 
        }
        //******************************************************
        psmv = RankMove(kx,pos->wBitRanks[ky]);
        int nDisp = nMyKing & 0xf0;
        //得到将左面的第一个棋子
        tmp = psmv->RookCap[DUpLeft] + nDisp;
        if(tmp != nMyKing){
            int checkChess  = pos->b256[tmp];
            if(     (checkChess == RCHE)
                ||(checkChess == RPAWN && tmp == nMyKing-1)){
                return (1);
            }
            //有了第一个棋子,才有第二个棋子哇
            tmp = psmv->CannonCap[DUpLeft] + nDisp;
            if(tmp != nMyKing){
                if(pos->b256[tmp] == RPAO){
                    return (1);
                }
            }
        }
        //得到将右面第一个棋子
        tmp = psmv->RookCap[DLoRight] + nDisp;
        if(tmp != nMyKing){
            int checkChess  = pos->b256[tmp];
            if(     (checkChess == RCHE)
                ||(checkChess == RPAWN && tmp == nMyKing+1)){
                return (1);
            }
            //有了第一个棋子,才有第二个棋子哇
            tmp = psmv->CannonCap[DLoRight] + nDisp;
            if(tmp != nMyKing){
                if(pos->b256[tmp] == RPAO){
                    return (1);
                }
            }
        }

   
    }
    return (0);
}




//bool IsMoveValid(position_t *pos,int move){
//
//    int from = FROM(move);
//    int to   = TO(move);
//
//    int ffx = StoX(from) - 3;
//    int ffy = StoY(from) - 3;
//    int ttx = StoX(to) - 3;
//    int tty = StoY(to) - 3;
//
//    if(IsMoveValid_FT(pos,ffx,ffy,ttx,tty) == NormalMove){
//        return true;
//    }
//    else{
//        return false;
//    }
//}

BOOL  move_is_legal(position_t *pos, int move){

    int tmp;
    //int c14;

    int from    = FROM(move);
    int fx      = StoX(from);
    int fy      = StoY(from);

    int to      = TO(move);

    int tx      = StoX(to);
    int ty      = StoY(to);
    //int ty4     = to & 0xf0;

    //int nSideTag = 16 + board->turn * 16;
    //int kpos     = board->P48[nSideTag];
    
    int kpos;
    if(pos->side == WHITE){
        kpos = PieceListStart(pos,RKING);
    }
    else{
        kpos = PieceListStart(pos,BKING);
    }

    int kx       = StoX(kpos);
    int ky       = StoY(kpos);

    int kr       = pos->wBitRanks[ky];
    int kf       = pos->wBitFiles[kx];

    int tr       = pos->wBitRanks[ty];
    int tf       = pos->wBitFiles[tx];        //

    int from14  = pos->b256[from];

    if(pos->side == WHITE){   //现在是红方走棋        

        if(from14 == RKING){    //走的是红帅

            for(tmp = PieceListStart(pos,BMA); tmp > 0x32; tmp = NextPiece(pos,tmp)){
                int m = horseLegTab(to-tmp+256);
                if(m && pos->b256[tmp+m] == EMPTY){
                    return FALSE;
                }
            }

            tf ^= yBitMask(from);
            tr ^= xBitMask(from);

            SlideMaskStruct *psmsRank = RankMask(tx,tr);
            SlideMaskStruct *psmsFile = FileMask(ty,tf);            

            //判断是否对将帅
            int bk = PieceListStart(pos,BKING);
            if(tx == StoX(bk)){
                if(psmsFile->RookCap & yBitMask(bk)){
                    return FALSE;
                }
            }

            //判断是不是给炮将军
            for(tmp = PieceListStart(pos,BPAO); tmp > 0x32; tmp = NextPiece(pos,tmp)){
                if(StoX(tmp) == tx){
                    if(psmsFile->CannonCap & yBitMask(tmp)){
                        return FALSE;
                    }
                }
                else if(StoY(tmp) == ty){
                    if(psmsRank->CannonCap & xBitMask(tmp)){
                        return FALSE;
                    }
                }
            }
            //判断是不是给车将军
            for(tmp = PieceListStart(pos,BCHE); tmp > 0x32; tmp = NextPiece(pos,tmp)){
                if(StoX(tmp) == tx){
                    if(psmsFile->RookCap & yBitMask(tmp)){
                        return FALSE;
                    }
                }
                else if(StoY(tmp) == ty){
                    if(psmsRank->RookCap & xBitMask(tmp)){
                        return FALSE;
                    }
                }
            }
            //判断是不是给兵将军
            if(    pos->b256[to+1]  == BPAWN 
                || pos->b256[to-1]  == BPAWN 
                || pos->b256[to-16] == BPAWN){
                    return FALSE;
            }

        }  //走的是红帅 End
        else{       //判断其它的棋子可不可走
            
            // 1, 可不可走
                // a, 在将军的马腿上的棋子不可走, 但如果是吃那个马就可走
            for(tmp = PieceListStart(pos,BMA); tmp > 0x32; tmp = NextPiece(pos,tmp)){
                int m = horseLegTab(kpos-tmp+256);
                if(m){
                    if((tmp+m)==from && to != tmp){
                        return FALSE;
                    }
                }
            }
            // 2, 更新一下FR
            if(tx == kx){
                kf |= yBitMask(to);
            }
            if(ty == ky){
                kr |= xBitMask(to);
            }
            if(fx == kx){
                kf ^= yBitMask(from);
            }
            if(fy == ky){
                kr ^= xBitMask(from);
            }

            //SlideMaskStruct *psmsRank = smsRankMaskTab[kx-3] + kr;
            //SlideMaskStruct *psmsFile = smsFileMaskTab[ky-3] + kf;

            SlideMaskStruct *psmsRank = RankMask(kx,kr);
            SlideMaskStruct *psmsFile = FileMask(ky,kf);

            //再计算一下, 车,炮,将能不能将, 这儿得加上将哇

            for(tmp = PieceListStart(pos,BCHE); tmp > 0x32; tmp = NextPiece(pos,tmp)){
                if(tmp != to){
                    int x = StoX(tmp);
                    int y = StoY(tmp);
                    if(x == kx){
                        if(psmsFile->RookCap & yBitMask(tmp)){
                            return (FALSE);
                        }
                        //if(NumFromFR(FromToMask(y,ky) & kf) == 0){
                        //    return FALSE;
                        //}
                    }
                    else if(y == ky){
                        if(psmsRank->RookCap & xBitMask(tmp)){
                            return (FALSE);
                        }
                       /* if(NumFromFR(FromToMask(x,kx) & kr) == 0){
                            return FALSE;
                        }*/
                    }
                }
            }
            //再计算一下炮
            //for(int i = 41; i <= 42; i++){  //黑炮
            //    if(tmp = board->P48[i]){
            //        if(tmp != to){
            //            int x = StoX(tmp);
            //            int y = StoY(tmp);
            //            if(x == kx){
            //                if(NumFromFR(FromToMask(y,ky) & kf) == 1){
            //                    return FALSE;
            //                }
            //            }
            //            else if(y == ky){
            //                if(NumFromFR(FromToMask(x,kx) & kr) == 1){
            //                    return FALSE;
            //                }
            //            }
            //        }
            //    }
            //}
            for(tmp = PieceListStart(pos,BPAO); tmp > 0x32; tmp = NextPiece(pos,tmp)){
                if(tmp != to){
                    int x = StoX(tmp);
                    int y = StoY(tmp);
                    if(x == kx){
                        if(psmsFile->CannonCap & yBitMask(tmp)){
                            return (FALSE);
                        }
                        //if(NumFromFR(FromToMask(y,ky) & kf) == 1){
                        //    return FALSE;
                        //}
                    }
                    else if(y == ky){
                        if(psmsRank->CannonCap & xBitMask(tmp)){
                            return (FALSE);
                        }
                        //if(NumFromFR(FromToMask(x,kx) & kr) == 1){
                        //    return FALSE;
                        //}
                    }
                }
            }

            //再计算一下是不是对将了
             //tmp = board->P48[32];
             tmp = PieceListStart(pos,BKING);
             if(StoX(tmp) == kx){
                 if(psmsFile->RookCap & yBitMask(tmp)){
                    return (FALSE);
                 }
             }
        }
    }       //现在是红方走棋       End
    else{
        if(from14 == BKING){    //走的是黑将
            // 得到现在帅上面的第一个棋子           

            for(tmp = PieceListStart(pos,RMA); tmp > 0x32; tmp = NextPiece(pos,tmp)){
                int m = horseLegTab(to-tmp+256);
                if(m && pos->b256[tmp+m] == EMPTY){
                    return FALSE;
                }
            }

            tf ^= yBitMask(from);
            tr ^= xBitMask(from);

            SlideMaskStruct *psmsRank = RankMask(tx,tr);
            SlideMaskStruct *psmsFile = FileMask(ty,tf);


            //判断是否对将帅
            int rk = PieceListStart(pos,RKING);
            if(tx == StoX(rk)){
                if(psmsFile->RookCap & yBitMask(rk)){
                    return FALSE;
                }
            }

            //判断是不是给炮将军
            for(tmp = PieceListStart(pos,RPAO); tmp > 0x32; tmp = NextPiece(pos,tmp)){
                if(StoX(tmp) == tx){
                    if(psmsFile->CannonCap & yBitMask(tmp)){
                        return FALSE;
                    }
                }
                else if(StoY(tmp) == ty){
                    if(psmsRank->CannonCap & xBitMask(tmp)){
                        return FALSE;
                    }
                }
            }

            //判断是不是给车将军
            for(tmp = PieceListStart(pos,RCHE); tmp > 0x32; tmp = NextPiece(pos,tmp)){
                if(StoX(tmp) == tx){
                    if(psmsFile->RookCap & yBitMask(tmp)){
                        return FALSE;
                    }
                }
                else if(StoY(tmp) == ty){
                    if(psmsRank->RookCap & xBitMask(tmp)){
                        return FALSE;
                    }
                }
            }
            //判断是不是给兵将军
            if(    pos->b256[to+1]  == RPAWN 
                || pos->b256[to-1]  == RPAWN 
                || pos->b256[to+16] == RPAWN){
                    return FALSE;
            }         

        }  //走的是黑将 End
        else{       //判断其它的棋子可不可走
            // 1, 可不可走
                // a, 在将军的马腿上的棋子不可走, 但如果是吃那个马就可走
            //tmp = board->P48[21];
            //int m = horseLegTab(kpos - tmp + 256);
            //if(m){
            //    if(((tmp+m) == from) && to != tmp){
            //        return FALSE;   //
            //    }               
            //}
            //tmp = board->P48[22];
            //    m = horseLegTab(kpos - tmp + 256);
            //if(m){
            //    if(((tmp+m) == from) && to != tmp){
            //        return FALSE;   //
            //    }               
            //}
            for(tmp = PieceListStart(pos,RMA); tmp > 0x32; tmp = NextPiece(pos,tmp)){
                int m = horseLegTab(kpos-tmp+256);
                if(m){
                    if((tmp+m)==from && to != tmp){
                        return FALSE;
                    }
                }
            }
            // 2, 更新一下FR
            if(tx == kx){
                kf |= yBitMask(to);
            }
            if(ty == ky){
                kr |= xBitMask(to);
            }
            if(fx == kx){
                kf ^= yBitMask(from);
            }
            if(fy == ky){
                kr ^= xBitMask(from);
            }

            SlideMaskStruct *psmsRank = RankMask(kx,kr);
            SlideMaskStruct *psmsFile = FileMask(ky,kf);

            for(tmp = PieceListStart(pos,RCHE); tmp > 0x32; tmp = NextPiece(pos,tmp)){
                if(tmp != to){
                    int x = StoX(tmp);
                    int y = StoY(tmp);
                    if(x == kx){
                        if(psmsFile->RookCap & yBitMask(tmp)){
                            return (FALSE);
                        }
                    }
                    else if(y == ky){
                        if(psmsRank->RookCap & xBitMask(tmp)){
                            return (FALSE);
                        }
                    }
                }
            }

            for(tmp = PieceListStart(pos,RPAO); tmp > 0x32; tmp = NextPiece(pos,tmp)){
                if(tmp != to){
                    int x = StoX(tmp);
                    int y = StoY(tmp);
                    if(x == kx){
                        if(psmsFile->CannonCap & yBitMask(tmp)){
                            return (FALSE);
                        }
                    }
                    else if(y == ky){
                        if(psmsRank->CannonCap & xBitMask(tmp)){
                            return (FALSE);
                        }
                    }
                }
            }

             tmp = PieceListStart(pos,RKING);
             if(StoX(tmp) == kx){
                 if(psmsFile->RookCap & yBitMask(tmp)){
                    return (FALSE);
                 }
             }            
        }
    }

    return TRUE;

}



bool position_is_ok(position_t *pos){

   bool    posisok = true; 

#ifdef USE_SLOW_BOARD   
   
    int     num[16];
    uint16  bF[16];
    uint16  bR[16];
    //list_t  piece_list[256];       //

    //sint32  posVal  = 0;
    uint64  key     = 0;
    //uint64 pkey     = 0;
    
    //init

    //position_t tmppos;
    //memset(&tmppos,0,sizeof(position_t));
    //tmppos.board = tmppos.board;

    //init_position(&tmppos);

    Record* re = &pos->His[pos->curStep]; 

    for(int i = 0; i < 16; i++){
          bF[i]   = 0;
          bR[i]   = 0;
          num[i]  = 0;
    }

    // 判断一下plist的棋子对不对

    //设定一下list
    for(int p256 = 0x33; p256 < 0xcc; p256++){
        int chess = pos->b256[p256];
        if(chess != 0){     //有了一个棋子
            num[chess] ++;

            //posVal += PstVal[chess][p256];

           /* tmppos.wBitFiles[StoX(p256)] |= yBitMask(p256);
            tmppos.wBitRanks[StoY(p256)] |= xBitMask(p256);*/

            bF[StoX(p256)] |= yBitMask(p256);
            bR[StoY(p256)] |= xBitMask(p256);

            //InsertPiece(&tmppos,chess,p256);

            //tmppos.board[p256] = chess;

            key ^= ZOBRIST(chess,p256);

        }
    }

    if(pos->side == BLACK) key ^= ZobColour;

    //init_piece_lists(&tmppos);

    //下面判断有没将帅
    if(pos->b256[PieceListStart(pos,RKING)] != RKING || pos->b256[PieceListStart(pos,BKING)] != BKING){
        posisok = false;
        //fprintf(stdout,"Error>board_is_ok, 没将帅\n");
        LogOut("Error>board_is_ok, 没将帅\n");
    }
    
    // key
    if(key != re->key){
        posisok = false;
        //fprintf(stdout,"Error>board_is_ok, hashkey 不相同\n");
        LogOut("Error>board_is_ok, hashkey 不相同\n");
    }


    //
    for(int i=0; i<16; i++){
        if(bF[i] != pos->wBitFiles[i]){
            posisok = false;
            LogOut("Error>board_is_ok, pos->wBitFiles[i]\n");
        }
    }
    for(int i=0; i<16; i++){
        if(bR[i] != pos->wBitRanks[i]){
            posisok = false;           
            LogOut("Error>board_is_ok, pos->wBitRanks[i]\n");
        }
    }

    for(int i=0; i<256; i++){
        if(pos->piece_list[i].n != 0){
            if(pos->piece_list[i].n == i){
                 posisok = false;           
                 LogOut("Error>board_is_ok, list\n");
                 //board_display(pos,"局面有错哇\n", stdout);
                 return false;
            }
        }
    }


    char tb[256];
    memset(tb,0,sizeof(tb));
    //检查红棋list 
    //for(int chess = 7; chess >= 0; chess --){
        for(int from = PieceListStart(pos,RPAWN); from != PieceListEnd; from = NextPiece(pos,from)){
            if(from>0x32){
                tb[from] = pos->b256[from];
            }
        }
    //}
    //检查黑棋list 
    //for(int chess = 14; chess >= 8; chess --){
        for(int from = PieceListStart(pos,BPAWN); from != PieceListEnd ; from = NextPiece(pos,from)){
            if(from>0x32){
                tb[from] = pos->b256[from];
            }
        }
    //}

    for(int i = 0; i < 256; i++){
        if(tb[i] != pos->b256[i]){
            posisok = false;           
            LogOut("Error>board_is_ok, pos->piecelist[i]\n");
        }
    }

    if(  num[RPAWN]>5||num[RCHE]>2||num[RPAO]>2||num[RMA]>2||num[RXIANG]>2||num[RSHI]>2||num[RKING]!=1
        ||num[BPAWN]>5||num[BCHE]>2||num[BPAO]>2||num[BMA]>2||num[BXIANG]>2||num[BSHI]>2||num[BKING]!=1
        ){
            posisok = false;
            LogOut("Error>board_is_ok, num!!!!\n");        
    }
 
    

   //if(pos->pMat    != & PreMatInfo[num[RPAWN]]
   //                               [num[BPAWN]]
   //                               [num[RCHE]]
   //                               [num[RMA]]
   //                               [num[RPAO]]
   //                               [num[RSHI]]
   //                               [num[RXIANG]]
   //                               [num[BCHE]]
   //                               [num[BMA]]
   //                               [num[BPAO]]
   //                               [num[BSHI]]
   //                               [num[BXIANG]]){
   //        posisok = false;
   //        LogOut("Error>board_is_ok, board->pMat 不相同\n");
   //        /*board_display(board,"Error>board_is_ok, number 不相同\n", log_file);*/
   // } 

  if(posisok == false){
      //board_display(pos,"局面有错哇\n", stdout);
      //board_display(pos,"局面有错哇\n", log_file);

      LogOut("局面有错哇\n");
  }

#endif
  

   return posisok;
}


ChessMove		//判断走步是不是有效哇
IsMoveValid_FT(position_t *pos,int ffx, int ffy, int ttx, int tty){


    ASSERT(position_is_ok(pos));

    int fx      = ffx+3;
    int fy      = ffy+3;
    int tx      = ttx+3;
    int ty      = tty+3;
    int from    = XYtoS(fx,fy);
    int to      = XYtoS(tx,ty);
    int piece   = pos->b256[from];
    int capture = pos->b256[to];

    int nDisp;
    SlideMaskStruct *psmsRank ;
    SlideMaskStruct *psmsFile ;

    int kpos;
    if(pos->side == WHITE){
        kpos = PieceListStart(pos,RKING);
    }
    else{
        kpos = PieceListStart(pos,BKING);
    }

    int kx = StoX(kpos);
    int ky = StoY(kpos);

    int kr = pos->wBitRanks[ky];
    int kf = pos->wBitFiles[kx];

    int tr = pos->wBitRanks[ty];
    int tf = pos->wBitFiles[tx];

    int tmp;

    if(pos->side == WHITE){
        if(!IsWhite(piece) || IsWhite(capture)){
            return IllegalMove;
        }
    }
    else{
        if(!IsBlack(piece) || IsBlack(capture)){
            return IllegalMove;
        }
    }
    
    if(from == to){
        return IllegalMove;
    }

    switch(piece){
        case RPAWN:     //红兵
            if((GetDir(from,to) & DirKing) == 0){
                return IllegalMove;
            }
            if((from & 0x80) != 0){   //还没过河
                if((from-to) != 16){
                    return IllegalMove;
                }
            }
            break;
        case BPAWN:     //黑卒
            if((GetDir(from,to) & DirKing) == 0){
                return IllegalMove;
            }
            if((from & 0x80) == 0){   //还没过河
                if((to-from) != 16){
                    return IllegalMove;
                }
            }
            break;
        case BKING:
            if((inBoard(to) & IN_BKING) == 0){
                return IllegalMove;
            }
            if((GetDir(from,to) & DirKing) == 0){
                return IllegalMove;
            }
            break;
        case RKING:
            if((inBoard(to) & IN_RKING) == 0){
                return IllegalMove;
            }
            if((GetDir(from,to) & DirKing) == 0){
                return IllegalMove;
            }
            break;
        case BSHI:
        case RSHI:
            if((GetDir(from,to) & DirShi) == 0){
                return IllegalMove;
            }
            break;         
         case BXIANG:
         case RXIANG:  
             if((GetDir(from,to) & DirXiang) == 0){
                 return IllegalMove;
             }
             if(pos->b256[(from+to)/2] != EMPTY){
                return IllegalMove;
             }
             break; 
         case RMA:
         case BMA:
             nDisp = horseLegTab(to-from+256);
             if(nDisp == 0){
                return IllegalMove;
             }
             if(pos->b256[from+nDisp] != EMPTY){
                return IllegalMove;
             }
             break;
         case RCHE:
         case BCHE:
              psmsRank = RankMask(fx,pos->wBitRanks[fy]);
              psmsFile = FileMask(fy,pos->wBitFiles[fx]);

             if(fx == tx){
                 if(!(psmsFile->RookCap & yBitMask(to))){
                     return IllegalMove;
                 }
             }
             else if(fy == ty){
                 if(!(psmsRank->RookCap & xBitMask(to))){
                    return IllegalMove;
                 }
             }
             else return IllegalMove;
             break;
         case RPAO:
         case BPAO:
              psmsRank = RankMask(fx,pos->wBitRanks[fy]);
              psmsFile = FileMask(fy,pos->wBitFiles[fx]);
              if(fx == tx){
                  if(capture){
                      if(!(psmsFile->CannonCap & yBitMask(to))){
                          return IllegalMove;
                      }
                  }
                  else{
                      if(!(psmsFile->NonCap & yBitMask(to))){
                          return IllegalMove;
                      }
                  }

              }
              else if(fy == ty){
                  if(capture){
                      if(!(psmsRank->CannonCap & xBitMask(to))){
                          return IllegalMove;
                      }
                  }
                  else{
                      if(!(psmsRank->NonCap & xBitMask(to))){
                          return IllegalMove;
                      }
                  }                  
              }
              else return IllegalMove;
             break;
         default:
             return IllegalMove;
             break;
    }
    //下面判断走子后是不是给对方将军了

    if(pos->side == WHITE){
        if(piece == RKING){     //走的是红帅
            for(tmp = PieceListStart(pos,BMA); tmp > 0x32; tmp = NextPiece(pos,tmp)){
                int m = horseLegTab(to-tmp+256);
                if(m && pos->b256[tmp+m] == EMPTY){
                    return IllegalMove;
                }
            }
            tf ^= yBitMask(from);
            tr ^= xBitMask(from);

            psmsRank = RankMask(tx,tr);
            psmsFile = FileMask(ty,tf);

            //判断是不是对将帅
            int bk = PieceListStart(pos,BKING);
            if(tx == StoX(bk)){
                if(psmsFile->RookCap & yBitMask(bk)){
                    return IllegalMove;
                }
            }

            //判断是不是给炮将军
            for(tmp = PieceListStart(pos,BPAO); tmp > 0x32; tmp = NextPiece(pos,tmp)){
                if(StoX(tmp) == tx){
                    if(psmsFile->CannonCap & yBitMask(tmp)){
                        return IllegalMove;
                    }
                }
                else if(StoY(tmp) == ty){
                    if(psmsRank->CannonCap & xBitMask(tmp)){
                        return IllegalMove;
                    }
                }
            }
            //判断是不是给车将军
            for(tmp = PieceListStart(pos,BCHE); tmp > 0x32; tmp = NextPiece(pos,tmp)){
                if(StoX(tmp) == tx){
                    if(psmsFile->RookCap & yBitMask(tmp)){
                        return IllegalMove;
                    }
                }
                else if(StoY(tmp) == ty){
                    if(psmsRank->RookCap & xBitMask(tmp)){
                        return IllegalMove;
                    }
                }
            }
            //判断是不是给兵将军
            if(    pos->b256[to+1]  == BPAWN 
                || pos->b256[to-1]  == BPAWN 
                || pos->b256[to-16] == BPAWN){
                    return IllegalMove;
            }
        }
        else{//判断其它的棋子可不可走
            // a, 在将军的马腿上的棋子不可走, 但如果是吃那个马就可走
            for(tmp = PieceListStart(pos,BMA); tmp > 0x32; tmp = NextPiece(pos,tmp)){
                int m = horseLegTab(kpos-tmp+256);
                if(m){
                    if((tmp+m)==from && to != tmp){
                        return IllegalMove;
                    }
                }
            }
            // 2, 更新一下FR
            if(tx == kx){
                kf |= yBitMask(to);
            }
            if(ty == ky){
                kr |= xBitMask(to);
            }
            if(fx == kx){
                kf ^= yBitMask(from);
            }
            if(fy == ky){
                kr ^= xBitMask(from);
            }

            psmsRank = RankMask(kx,kr);
            psmsFile = FileMask(ky,kf);

            //再计算一下, 车,炮,将能不能将, 这儿得加上将哇

            for(tmp = PieceListStart(pos,BCHE); tmp > 0x32; tmp = NextPiece(pos,tmp)){
                if(tmp != to){
                    int x = StoX(tmp);
                    int y = StoY(tmp);
                    if(x == kx){
                        if(psmsFile->RookCap & yBitMask(tmp)){
                            return IllegalMove;
                        }
                    }
                    else if(y == ky){
                        if(psmsRank->RookCap & xBitMask(tmp)){
                            return IllegalMove;
                        }
                    }
                }
            }
            for(tmp = PieceListStart(pos,BPAO); tmp > 0x32; tmp = NextPiece(pos,tmp)){
                if(tmp != to){
                    int x = StoX(tmp);
                    int y = StoY(tmp);
                    if(x == kx){
                        if(psmsFile->CannonCap & yBitMask(tmp)){
                            return IllegalMove;
                        }
                    }
                    else if(y == ky){
                        if(psmsRank->CannonCap & xBitMask(tmp)){
                            return IllegalMove;
                        }
                    }
                }
            }

            //再计算一下是不是对将了
            //tmp = board->P48[32];
            tmp = PieceListStart(pos,BKING);
            if(StoX(tmp) == kx){
                if(psmsFile->RookCap & yBitMask(tmp)){
                    return IllegalMove;
                }
            }
        }
    }
    else{       //走的是黑棋
        if(piece == BKING){
            for(tmp = PieceListStart(pos,RMA); tmp > 0x32; tmp = NextPiece(pos,tmp)){
                int m = horseLegTab(to-tmp+256);
                if(m && pos->b256[tmp+m] == EMPTY){
                    return IllegalMove;
                }
            }

            tf ^= yBitMask(from);
            tr ^= xBitMask(from);

            psmsRank = RankMask(tx,tr);
            psmsFile = FileMask(ty,tf);

            //判断是否对将帅
            int rk = PieceListStart(pos,RKING);
            if(tx == StoX(rk)){
                if(psmsFile->RookCap & yBitMask(rk)){
                    return IllegalMove;
                }
            }

            //判断是不是给炮将军
            for(tmp = PieceListStart(pos,RPAO); tmp > 0x32; tmp = NextPiece(pos,tmp)){
                if(StoX(tmp) == tx){
                    if(psmsFile->CannonCap & yBitMask(tmp)){
                        return IllegalMove;
                    }
                }
                else if(StoY(tmp) == ty){
                    if(psmsRank->CannonCap & xBitMask(tmp)){
                        return IllegalMove;
                    }
                }
            }
            //判断是不是给车将军
            for(tmp = PieceListStart(pos,RCHE); tmp > 0x32; tmp = NextPiece(pos,tmp)){
                if(StoX(tmp) == tx){
                    if(psmsFile->RookCap & yBitMask(tmp)){
                        return IllegalMove;
                    }
                }
                else if(StoY(tmp) == ty){
                    if(psmsRank->RookCap & xBitMask(tmp)){
                        return IllegalMove;
                    }
                }
            }
            //判断是不是给兵将军
            if(    pos->b256[to+1]  == RPAWN 
                || pos->b256[to-1]  == RPAWN 
                || pos->b256[to+16] == RPAWN){
                    return IllegalMove;
            } 
        }
        else{
                        
            for(tmp = PieceListStart(pos,RMA); tmp > 0x32; tmp = NextPiece(pos,tmp)){
                int m = horseLegTab(kpos-tmp+256);
                if(m){
                    if((tmp+m)==from && to != tmp){
                        return IllegalMove;
                    }
                }
            }
            // 2, 更新一下FR
            if(tx == kx){
                kf |= yBitMask(to);
            }
            if(ty == ky){
                kr |= xBitMask(to);
            }
            if(fx == kx){
                kf ^= yBitMask(from);
            }
            if(fy == ky){
                kr ^= xBitMask(from);
            }

            psmsRank = RankMask(kx,kr);
            psmsFile = FileMask(ky,kf);

            for(tmp = PieceListStart(pos,RCHE); tmp > 0x32; tmp = NextPiece(pos,tmp)){
                if(tmp != to){
                    int x = StoX(tmp);
                    int y = StoY(tmp);
                    if(x == kx){
                        if(psmsFile->RookCap & yBitMask(tmp)){
                            return IllegalMove;
                        }
                    }
                    else if(y == ky){
                        if(psmsRank->RookCap & xBitMask(tmp)){
                            return IllegalMove;
                        }
                    }
                }
            }

            for(tmp = PieceListStart(pos,RPAO); tmp > 0x32; tmp = NextPiece(pos,tmp)){
                if(tmp != to){
                    int x = StoX(tmp);
                    int y = StoY(tmp);
                    if(x == kx){
                        if(psmsFile->CannonCap & yBitMask(tmp)){
                            return IllegalMove;
                        }
                    }
                    else if(y == ky){
                        if(psmsRank->CannonCap & xBitMask(tmp)){
                            return IllegalMove;
                        }
                    }
                }
            }

             tmp = PieceListStart(pos,RKING);
             if(StoX(tmp) == kx){
                 if(psmsFile->RookCap & yBitMask(tmp)){
                    return IllegalMove;
                 }
             } 
        }
    }

    return NormalMove;
}


void //产生所有的合法走步
gen_legal_moves(position_t *pos){ 

	pos->pMend = generate_moves(pos, pos->all_move);
}


int  move_is_check(position_t *pos,int move){

    int from    = FROM(move);
    int to      = TO(move);
    int piece   = PIECE(move);
    //int capture = CAPTURE(move);

    int tx      = StoX(to);
    int ty      = StoY(to);

    int fx      = StoX(from);
    int fy      = StoY(from);

    if(IsWhite(piece)){     //判断红方是不是将军步

        int opkPos = PieceListStart(pos,BKING);
        int mekPos = PieceListStart(pos,RKING);

        int kx      = StoX(opkPos);
        int ky      = StoY(opkPos);

        int kr      = pos->wBitRanks[ky];
        int kf      = pos->wBitFiles[kx];

        //        int kx      = StoX(nMyKing);
        //int ky      = StoY(nMyKing);
        ////int kr      = pos->wBitRanks[ky];
        ////int kf      = pos->wBitFiles[kx];
        

        //更新一下FR
        if(fx == kx){
            kf ^= yBitMask(from);
        }
        if(fy == ky){
            kr ^= xBitMask(from);
        }
        if(tx == kx){
            kf |= yBitMask(to);
        }
        if(ty == ky){
            kr |= xBitMask(to);
        }

        //SlideMaskStruct *psmsRank = smsRankMaskTab[kx-3] + kr;
        //SlideMaskStruct *psmsFile = smsFileMaskTab[ky-3] + kf;

        SlideMaskStruct *psmsRank = RankMask(kx,kr);
        SlideMaskStruct *psmsFile = FileMask(ky,kf);

        //再判断一下老头子是不是对面了,如果,就不是将军步

        if(piece == RKING){     //走是红帅
            if(tx == kx){
                //if(NumFromFR(FromToMask(ty,ky) & kf) == 0){
                //    return false;
                //}
                if(psmsFile->RookCap & yBitMask(to)){
                    return false;
                }
            }
        }
        else{
            if(kx == StoX(mekPos)){
                //if(NumFromFR(FromToMask(StoY(mekPos),ky) & kf) == 0){
                //    return false;
                //}
                if(psmsFile->RookCap & yBitMask(mekPos)){
                    return false;
                }
            }
        }

        int tmp;

        //是不是直接将军  兵,车,炮,马 四个棋能直接将军
        switch(piece){
            case RPAWN:
                if((to-1) == opkPos || (to+1) == opkPos || (to-16) == opkPos){
                    return true;
                }
                break;
            case RMA:
                tmp = horseLegTab(opkPos - to + 256);
                if(tmp != 0 && pos->b256[to + tmp] == 0){
                    return true;
                }
                break;
            case RCHE:
                if(tx == kx){
                    if(psmsFile->RookCap & yBitMask(to)){
                        return true;
                    }
                    //if(NumFromFR(FromToMask(ty,ky) & kf) == 0){
                    //    return true;
                    //}
                }
                else if(ty == ky){
                    if(psmsRank->RookCap & xBitMask(to)){
                        return true;
                    }
                    //if(NumFromFR(FromToMask(tx,kx) & kr) == 0){
                    //    return true;
                    //}
                }
                break;
            case RPAO:
                if(tx == kx){
                    if(psmsFile->CannonCap & yBitMask(to)){
                        return true;
                    }
                    //if(NumFromFR(FromToMask(ty,ky) & kf) == 1){
                    //    return true;
                    //}
                }
                else if(ty == ky){
                    if(psmsRank->CannonCap & xBitMask(to)){
                        return true;
                    }
                    /*    if(NumFromFR(FromToMask(tx,kx) & kr) == 1){
                    return true;
                    }*/
                }
                break;
            default:
                break;
        }

        //是不是闪将
        for(int p256 = PieceListStart(pos,RMA); p256 > 0x32; p256 = NextPiece(pos,p256)){
            int can = horseLegTab(opkPos - p256 + 256);
            if(can != 0){
                if((p256 + can) == from){
                    return true;
                }
            }
        }
        //再计算一下,车炮能不能闪将
        for(int p256 = PieceListStart(pos,RCHE); p256 > 0x32; p256 = NextPiece(pos,p256)){
            if(p256 != from){
                int x = StoX(p256);
                int y = StoY(p256);
                if(x == kx){
                    //if(NumFromFR(FromToMask(y,ky) & kf) == 0){
                    //    return true;
                    //}
                    if(psmsFile->RookCap & yBitMask(p256)){
                        return true;
                    }
                }
                else if(y == ky){
                    if(psmsRank->RookCap & xBitMask(p256)){
                        return true;
                    }
                    //if(NumFromFR(FromToMask(x,kx) & kr) == 0){
                    //    return true;
                    //}
                }
            }
        }
        //再计算一下,车炮能不能闪将
        for(int p256 = PieceListStart(pos,RPAO); p256 > 0x32; p256 = NextPiece(pos,p256)){
            if(p256 != from){
                int x = StoX(p256);
                int y = StoY(p256);
                if(x == kx){
                    if(psmsFile->CannonCap & yBitMask(p256)){
                        return true;
                    }
                   /* if(NumFromFR(FromToMask(y,ky) & kf) == 1){
                        return true;
                    }*/
                }
                else if(y == ky){
                    if(psmsRank->CannonCap & xBitMask(p256)){
                        return true;
                    }
                    //if(NumFromFR(FromToMask(x,kx) & kr) == 1){
                    //    return true;
                    //}
                }
            }
        }
    }
    else{                   //判断黑方是不是将军步
        int opkPos = PieceListStart(pos,RKING);
        int mekPos = PieceListStart(pos,BKING);

        int kx      = StoX(opkPos);
        int ky      = StoY(opkPos);
        int kr      = pos->wBitRanks[ky];
        int kf      = pos->wBitFiles[kx];

        //更新一下FR
        if(fx == kx){
            kf ^= yBitMask(from);
        }
        if(fy == ky){
            kr ^= xBitMask(from);
        }
        if(tx == kx){
            kf |= yBitMask(to);
        }
        if(ty == ky){
            kr |= xBitMask(to);
        }

        //SlideMaskStruct *psmsRank = smsRankMaskTab[kx-3] + kr;
        //SlideMaskStruct *psmsFile = smsFileMaskTab[ky-3] + kf;

        SlideMaskStruct *psmsRank = RankMask(kx,kr);
        SlideMaskStruct *psmsFile = FileMask(ky,kf);

        //再判断一下老头子是不是对面了,如果,就不是将军步

        if(piece == BKING){     //走的是黑将
            if(tx == kx){
                //if(NumFromFR(FromToMask(ty,ky) & kf) == 0){
                //    return false;
                //}
                if(psmsFile->RookCap & yBitMask(to)){
                    return false;
                }
            }
        }
        else{
            if(kx == StoX(mekPos)){
                if(psmsFile->RookCap & yBitMask(mekPos)){
                    return false;
                }
                //if(NumFromFR(FromToMask(StoY(mekPos),ky) & kf) == 0){
                //    return false;
                //}
            }
        }

        int tmp;

        //是不是直接将军  兵,车,炮,马 四个棋能直接将军
        switch(piece){
            case BPAWN:
                if((to-1) == opkPos || (to+1) == opkPos || (to+16) == opkPos){
                    return true;
                }        
                break;
            case BMA:
                tmp = horseLegTab(opkPos - to + 256);
                if(tmp != 0 && pos->b256[to + tmp] == 0){
                    return true;
                }
                break;
            case BCHE:
                if(tx == kx){
                    if(psmsFile->RookCap & yBitMask(to)){
                        return true;
                    }
                    //if(NumFromFR(FromToMask(ty,ky) & kf) == 0){
                    //    return true;
                    //}
                }
                else if(ty == ky){
                     if(psmsRank->RookCap & xBitMask(to)){
                        return true;
                    }
                   /* if(NumFromFR(FromToMask(tx,kx) & kr) == 0){
                        return true;
                    }*/
                }
                break;
            case BPAO:
                if(tx == kx){
                    if(psmsFile->CannonCap & yBitMask(to)){
                        return true;
                    }
                    /*if(NumFromFR(FromToMask(ty,ky) & kf) == 1){
                        return true;
                    }*/
                }
                else if(ty == ky){
                    if(psmsRank->CannonCap & xBitMask(to)){
                        return true;
                    }
                   /* if(NumFromFR(FromToMask(tx,kx) & kr) == 1){
                        return true;
                    }*/
                }
                break;
            default:
                break;
        }

        //是不是闪将
        for(int p256 = PieceListStart(pos,BMA); p256 > 0x32; p256 = NextPiece(pos,p256)){
            int can = horseLegTab(opkPos - p256 + 256);
            if(can != 0){
                if((p256 + can) == from){
                    return true;
                }
            }
        }
        //再计算一下,车炮能不能闪将
        for(int p256 = PieceListStart(pos,BCHE); p256 > 0x32; p256 = NextPiece(pos,p256)){
            if(p256 != from){
                int x = StoX(p256);
                int y = StoY(p256);
                if(x == kx){
                    if(psmsFile->RookCap & yBitMask(p256)){
                        return true;
                    }
                    //if(NumFromFR(FromToMask(y,ky) & kf) == 0){
                    //    return true;
                    //}
                }
                else if(y == ky){
                    if(psmsRank->RookCap & xBitMask(p256)){
                        return true;
                    }
                    //if(NumFromFR(FromToMask(x,kx) & kr) == 0){
                    //    return true;
                    //}
                }
            }
        }
        //再计算一下,车炮能不能闪将
        for(int p256 = PieceListStart(pos,BPAO); p256 > 0x32; p256 = NextPiece(pos,p256)){
            if(p256 != from){
                int x = StoX(p256);
                int y = StoY(p256);
                if(x == kx){
                    if(psmsFile->CannonCap & yBitMask(p256)){
                        return true;
                    }
                    /*if(NumFromFR(FromToMask(y,ky) & kf) == 1){
                        return true;
                    }*/
                }
                else if(y == ky){
                    if(psmsRank->CannonCap & xBitMask(p256)){
                        return true;
                    }
                    /*if(NumFromFR(FromToMask(x,kx) & kr) == 1){
                        return true;
                    }*/
                }
            }
        }
    }

    return false;
}
void			/* Updates forwardMostMove */
MakeMove(dispboard_t* pDis, int fromX,int fromY,int toX,int toY, bool isMateTest){
    //DIS.forwardMostMove++;

    SwitchClocks(pDis);

    //pDis->timeRemaining[0][pDis->pos->gply] = pDis->whiteTimeRemaining;
    //pDis->timeRemaining[1][pDis->pos->gply] = pDis->blackTimeRemaining;
    //if (DIS.commentList[DIS.forwardMostMove] != NULL) {   //棋步说明
    //	free(DIS.commentList[DIS.forwardMostMove]);
    //	DIS.commentList[DIS.forwardMostMove] = NULL;
    //}

    /*CopyBoard(DIS.boards[DIS.forwardMostMove], DIS.boards[DIS.forwardMostMove - 1]);
    ApplyMove(DIS.boards[DIS.forwardMostMove],fromX, fromY, toX, toY);*/

    int from    = XYtoS(fromX+3,fromY+3);
    int to      = XYtoS(toX+3,toY+3);

	//if (pDis->pos->b256[202] == RKING){
	//	int k = 1;
	//}
    int piece   = pDis->pos->b256[from];
    int capture = pDis->pos->b256[to];    
    int move = MOVE_FROM(from,piece,to,capture);

   

	//GetMoveName(pDis,pDis->pos,move,appData.moveType);

	//char*   szStepName  = pDis->moveListName[pos->curStep] + 4;   //加上前面的编号哇

	GetMoveNameSimple(pDis->pos,pDis->moveListName[pDis->pos->curStep] + 4,move,appData.moveType);

    move2str(move,pDis->parseList[pDis->pos->gply]);  

	MakePosMoveOnly(pDis->pos,move);

	if(pDis->hwndThis == OBS[0]->hwndThis){
		SendMessage(hwndToolBar,TB_ENABLEBUTTON, IDT_ToStart, 1);
		SendMessage(hwndToolBar,TB_ENABLEBUTTON, IDT_Backward, 1);
		SendMessage(hwndToolBar,TB_ENABLEBUTTON, IDT_HUIQI, 1);
	}

	pDis->pos->gply ++;   //只在这儿加上
    pDis->pos->curStep = pDis->pos->gply;
    if (pDis->pos->gply >= MAX_MOVES) {		//走步数超限了哇
		DisplayFatalError(L"Game too long; increase MAX_MOVES and recompile", 0, 1);
        return;
    }
	//错误	7	error LNK2001 : 无法解析的外部符号 "void __cdecl DisplayMove(int)" (? DisplayMove@@YAXH@Z)	E : \PROG\GGchessGUi\Doard_Display.obj	GGchess

    memcpy(pDis->B256dis[pDis->pos->gply],pDis->pos->b256,256);

	//再在这儿加上填充棋库棋步的功能

	if (pDis->hwndThis == OBS[0]->hwndThis && pDis->notLookBook == false){
		FillBookbyPos(pDis,MST->book);	
	}
		DispHistoryStepName(pDis, pDis->pos->gply - 1);
	

    //   
   /* DispHistoryStepName(DIS.forwardMostMove-1);*/
    

    //DIS.pgn.cmresult = GameUnfinished;

    pDis->pgn->isFinish = GameUnfinished;

    if(isMateTest){
        //switch(IsMateDead(DIS.boards[DIS.forwardMostMove],
        //    DIS.currentMove%2 == 0 ? F_WHITE_ON_MOVE : 0)){
        switch(IsMateDead(pDis->pos)){
            case MT_NONE:
            //case MT_STALEMATE:
            default:
                break;
            case MT_CHECK:
                //strcat(DIS.parseList[DIS.forwardMostMove - 1], "+");
                //StringCbCat(DIS.parseList[DIS.forwardMostMove - 1],MSG_SIZ,"+");
                break;
            case MT_CHECKMATE:
                //strcat(DIS.parseList[DIS.forwardMostMove - 1], "#");
                //StringCbCat(DIS.parseList[DIS.forwardMostMove - 1],MSG_SIZ,"#");
                break;
        }
    }

    //在这儿作重复判断或连将判断
    //Draw_Repeat_Ban
    //if(!ParseOneMove(pmove,DIS.forwardMostMove,&moveType,&fromX, &fromY, &toX, &toY, cps->ucci)) {
    //    /* Machine move could not be parsed; ignore it. */
    //    StringCbPrintf(buf,MSG_SIZ,"Illegal move \"%s\" from %s machine",message, cps->which);
    //    DisplayError(buf, 0);
    //    if (DIS.gameMode == TwoMachinesPlay) {
    //        GameEnds(machineWhite ? BlackWins : WhiteWins,"Forfeit due to illegal move", GE_XBOARD);
    //    }
    //    return;
    //}

//	#define   REPEAT_NO        0       //没有重复
//#define   REPEAT_TRUE      1       //是真和棋
////#define   REPEAT_BAN_ME    3       //走子方走了禁着
//#define   REPEAT_BAN_OTHER 4       //走子方走了禁着


    switch(ban_repeat(pDis->pos)){
        case REPEAT_TRUE:      //重复走步
			LogOut(_T("双方走步重复了!\n"));
            break;
        case REPEAT_NO:			//不吃子超过了120步
            //LogOut("双方不吃子超过了120步!");
            break;
        case REPEAT_BAN_OTHER:
            //LogOut(ColorSeek,"不对,对方犯规,对方连将或连捉!",false);
			LogOut(_T("不对,对方犯规,对方连将或连捉!\n"));
            break;
        //case BLACK_CHECK_BAN:
        //case BLACK_CAP_BAN:
        //    LogOut("你又在连将或连捉了!");
            //break;
        default:
            break;
    }
}

void            //用户走步事件
UserMoveEvent(dispboard_t* pDis, int fromX,int fromY,int toX,int toY,int ucci){
    ChessMove moveType;

    if (fromX < 0 || fromY < 0){
        return;				//按下坐标不在棋盘内
    }
    if ((fromX == toX) && (fromY == toY)) {			//按下了原地方
        return;
    }
    //   Check if the user is playing in turn.  This is complicated because we
    //   let the user "pick up" a piece before it is his turn.  So the piece he
    //   tried to pick up may have been captured by the time he puts it down!
    //   Therefore we use the color the user is supposed to be playing in this
    //   test, not the color of the piece that is currently on the starting
    //   square---except in EditGame mode, where the user is playing both
    //   sides; fortunately there the capture race can't happen.  (It can
    //   now happen in IcsExamining mode, but that's just too bad.  The user
    //   will get a somewhat confusing message in that case.)


    switch (pDis->gameMode) {						  //当前的游戏方式
      case PlayFromGameFile:
      //case AnalyzeFile: 
      case EndOfGame:							  //游戏结束
      case IcsObserving:			
      case IcsIdle:
          /* We switched into a game mode where moves are not accepted,
          perhaps while the mouse button was down. */
          return;

      case MachinePlaysWhite:				//机器下白棋
          /* User is moving for Black */
          //if (WhiteOnMove(DIS.currentMove)) {
          if(pDis->pos->side == WHITE){
			  DisplayMoveError(pDis, L"It is Black's turn");
              return;
          }
          break;
      case MachinePlaysBlack:			    //机器下黑棋
          /* User is moving for White */
          //if(!WhiteOnMove(DIS.currentMove)) {
          if(pDis->pos->side == BLACK){
			  DisplayMoveError(pDis, L"It is White's turn");
              return;
          }
          break;

      case EditGame:
      case IcsExamining:
      case BeginningOfGame:
      //case AnalyzeMode:
      case Training:
          //if(ISB_CH(DIS.boards[DIS.currentMove][FRto90(DIS.fromX,DIS.fromY)])){
         /* if(IsBlack(pDis->pos->b256[XYtoS(pDis->fromX+3,pDis->fromY+3)])){*/
		  if(IsBlack(pDis->pos->b256[XYtoS(fromX+3,fromY+3)])){
              ////if(WhiteOnMove(DIS.currentMove)){
              if(pDis->pos->side == WHITE){
				  DisplayMoveError(pDis, L"It is White's turn!!");
                  return;
              }
          }
          else{
              //if(!WhiteOnMove(DIS.currentMove)){
              if(pDis->pos->side == BLACK){
				  DisplayMoveError(pDis, L"It is Black's turn!!");
                  return;
              }
          }
          break;
      case IcsPlayingBlack:
          /* User is moving for Black */
          /*  if (WhiteOnMove(currentMove)) {
          if (!appData.premove) {
          DisplayMoveError("It is White's turn");
          } else if (toX >= 0 && toY >= 0) {
          premoveToX = toX;
          premoveToY = toY;
          premoveFromX = fromX;
          premoveFromY = fromY;
          premovePromoChar = promoChar;
          gotPremove = 1;
          if (appData.debugMode) 
          fprintf(debugFP, "Got premove: fromX %d,"
          "fromY %d, toX %d, toY %d\n",
          fromX, fromY, toX, toY);
          }
          return;
          }*/
          break;

      case IcsPlayingWhite:
          /* User is moving for White */
          /* if (!WhiteOnMove(currentMove)) {
          if (!appData.premove) {
          DisplayMoveError("It is Black's turn");
          } else if (toX >= 0 && toY >= 0) {
          premoveToX = toX;
          premoveToY = toY;
          premoveFromX = fromX;
          premoveFromY = fromY;
          premovePromoChar = promoChar;
          gotPremove = 1;
          if (appData.debugMode) 
          fprintf(debugFP, "Got premove: fromX %d,"
          "fromY %d, toX %d, toY %d\n",
          fromX, fromY, toX, toY);
          }
          return;
          }*/
          break;

      default:
          break;

      case EditPosition:        //残局
          if (toX == -2 || toY == -2) {
              pDis->B256dis[0][XYtoS(pDis->fromX+3,pDis->fromY+3)] = EMPTY;
              //DrawPosition(false,DIS.pos.B256dis[DIS.currentMove]);	
              DrawPosition(pDis,false,pDis->B256dis[pDis->pos->curStep]);
          } 
          else if (toX >= 0 && toY >= 0) {
              pDis->B256dis[0][XYtoS(pDis->toX+3,pDis->toY+3)]     
                    = pDis->B256dis[0][XYtoS(pDis->fromX+3,pDis->fromY+3)] ;
              pDis->B256dis[0][XYtoS(pDis->fromX+3,pDis->fromY+3)] = EMPTY;
              /*DrawPosition(false,DIS.pos.B256dis[DIS.currentMove]);	*/	
              DrawPosition(pDis,false,pDis->B256dis[pDis->pos->curStep]);	
          }
          return;
    }// switch (DIS.gameMode) End.................

    if (toX < 0 || toY < 0){
        return;
    }

    pDis->userOfferedDraw = FALSE;  

    if (appData.testLegality) {             //要检测走步的合法性
        //*int flag = DIS.currentMove%2 == 0 ? 0 : F_WHITE_ON_MOVE;
        //flag    |= F_CHECK_CHECK;*/
        //IsMoveValid(position_t *pos,int fx, int fy, int tx, int ty)
        moveType = IsMoveValid_FT(pDis->pos,fromX, fromY, toX, toY);
        if (moveType == IllegalMove || moveType == ImpossibleMove) {
            DisplayMoveError(pDis,L"Illegal move");
            return;
        }		
    } 
    else {       
        moveType = NormalMove;
    }

    if (pDis->gameMode == Training) { //
        /* compare the move played on the board to the next move in the
        * game. If they match, display the move and the opponent's response. 
        * If they don't match, display an error message.
        */
        // int saveAnimate;
        //Board testBoard;
        //CopyBoard(testBoard, boards[currentMove]);
        //ApplyMove(fromX, fromY, toX, toY, promoChar, testBoard);

        //if (CompareBoards(testBoard, boards[currentMove+1])) {
        // ForwardInner(currentMove+1);

        // /* Autoplay the opponent's response.
        // * if appData.animate was TRUE when Training mode was entered,
        // * the response will be animated.
        // */
        // saveAnimate = appData.animate;
        // appData.animate = animateTraining;
        // ForwardInner(currentMove+1);
        // appData.animate = saveAnimate;

        // /* check for the end of the game */
        // if (currentMove >= forwardMostMove) {
        //  gameMode = PlayFromGameFile;
        //  ModeHighlight();
        //  SetTrainingModeOff();
        //  DisplayInformation("End of game");
        // }
        //} else {
        // DisplayError("Incorrect move", 0);
        //}
        return;
    }

    FinishMove(pDis,moveType, fromX, fromY, toX, toY);

	//if(pDis->IsAnalyzeMode == TRUE){		//当前是分析模式
	//	LetYqAnalizeCurPos(pDis);
	//}
}

/* Common tail of UserMoveEvent and DropMenuEvent */
void
FinishMove(dispboard_t* pDis,ChessMove moveType,int fromX,int fromY,int toX,int toY){
    /* Ok, now we know that the move is good, so we can kill
    the previous line in Analysis Mode */
    //if (DIS.gameMode == AnalyzeMode && DIS.currentMove < DIS.forwardMostMove) {
    //    DIS.forwardMostMove = DIS.currentMove;
    //}

    //if (pDis->gameMode == AnalyzeMode && pDis->pos->curStep < pDis->pos->gply) {
	if (pDis->gameMode == AnalyzeMode || pDis->pos->curStep < pDis->pos->gply) {
        pDis->pos->gply = pDis->pos->curStep;
    }

    /* If we need the chess program but it's dead, restart it */
    ResurrectChessProgram();

    /* A user move restarts a paused game*/
    if (pDis->pausing){
        //PauseEvent();
    }

    //pDis->thinkOutput[0] = NULLCHAR;

    MakeMove(pDis,fromX, fromY, toX, toY,true); /*updates forwardMostMove*/

    if (pDis->gameMode == BeginningOfGame) {
        //if (appData.noChessProgram) {
        //    DIS.gameMode = EditGame;
        //    SetGameInfo();
        //}
        //else {
        //    char buf[MSG_SIZ];
        //    DIS.gameMode = MachinePlaysBlack;
        //    SetGameInfo();			
        //    StringCbPrintf(buf,MSG_SIZ,"%s vs. %s", DIS.pgn.Rname, DIS.pgn.Bname);
        //    DisplayTitle(buf);
        //    if (DIS.first.sendName) {				
        //        StringCbPrintf(buf,MSG_SIZ, "name %s\n", DIS.pgn.Rname);
        //        SendToProgram(buf, &DIS.first);
        //    }
        //}

		pDis->gameMode = EditGame;

        ModeHighlight();
    }

    /* Relay move to ICS or chess engine */

	int from    = XYtoS(fromX+3,fromY+3);
	int to      = XYtoS(toX+3,toY+3);
	int piece   = pDis->pos->b256[from];
	int capture = pDis->pos->b256[to];

	TCHAR premove[16];
	move2str(MOVE_FROM(from,piece,to,capture),premove);


	ChessProgramState *cps = NULL;

	if (pDis->gameMode != AnalyzeMode){

		switch(pDis->gameMode){
			//双方引擎对战
		//case TwoMachinesPlay:
		//	if(pDis->first.playWhat == pDis->pos->side){
		//		cps = &pDis->first;
		//	}
		//	else if(pDis->second.playWhat == pDis->pos->side){
		//		cps = &pDis->second;
		//	}
		//	if(cps != NULL){
		//		SendProgramGo(cps,Cps_Thinking, L"none");                              //使用引擎开始运算
		//	}
		//	break;
		case MachinePlaysWhite:
			cps = &pDis->first;
			ASSERT(cps != NULL);

			if(cps->playWhat == pDis->pos->side){
				//让引擎思考
				SendProgramGo(cps, Cps_Thinking, premove);
			}
			else{
				//让引擎进入后台
				if(pDis->mustPonder == TRUE){		//后台思考
					if(cps->PonderMove[0] != 0){
						SendProgramGo(cps, Cps_Pondering, cps->PonderMove);
					}
				}
			}
			break;
		case MachinePlaysBlack:

			cps = &pDis->first;
			ASSERT(cps != NULL);

			if(cps->playWhat == pDis->pos->side){
				//让引擎思考
				SendProgramGo(cps, Cps_Thinking, premove);
			}
			else{
				//让引擎进入后台
				if(pDis->mustPonder == TRUE){		//后台思考
					if(cps->PonderMove[0] != 0){						
						SendProgramGo(cps, Cps_Pondering, cps->PonderMove);
					}
				}
			}
			break;
		case IcsPlayingWhite:		//上网了，我走红
			if(pDis->pos->side == WHITE){
				cps = &pDis->first;
				if(cps != NULL){					
					//让引擎思考
					SendProgramGo(cps, Cps_Thinking, premove);
				}
			}
			else{		
				//发送走步给ICS
				SendMoveToICS(pDis,moveType, fromX, fromY, toX, toY);
				pDis->ics_user_moved = TRUE;					      //用户已走棋子哇
				//再看一下，能不能后台思考	
				cps = &pDis->first;
				if(cps != NULL){
					if(pDis->mustPonder == TRUE){
						if(cps->PonderMove[0] != 0){							
							SendProgramGo(cps, Cps_Pondering, cps->PonderMove);
						}
					}
				}
			}
			break;
		case IcsPlayingBlack:
			if(pDis->pos->side == BLACK){
				cps = &pDis->first;
				if(cps != NULL){					
					//让引擎思考
					SendProgramGo(cps, Cps_Thinking, premove);
				}
			}
			else{		
				//发送走步给ICS
				SendMoveToICS(pDis,moveType, fromX, fromY, toX, toY);
				pDis->ics_user_moved = TRUE;					      //用户已走棋子哇
				//再看一下，能不能后台思考
				cps = &pDis->first;
				if(cps != NULL){
					if(pDis->mustPonder == TRUE){
						if(cps->PonderMove[0] != 0){							
							SendProgramGo(cps, Cps_Pondering, cps->PonderMove);
						}
					}
				}
			}
			break;
		default:
			break;
		}
	}

    ShowMove(pDis,fromX, fromY, toX, toY); /*updates currentMove*/

    switch (pDis->gameMode) {
        case EditGame:
            //switch (MateTest(DIS.boards[DIS.currentMove],PosFlags(DIS.currentMove))) {
            //DIS.currentMove%2 == 0 ? F_CHECK_CHECK|F_WHITE_ON_MOVE : F_CHECK_CHECK,
            //switch(IsMateDead(DIS.boards[DIS.currentMove],
            //    DIS.currentMove%2 == 0 ? F_WHITE_ON_MOVE : 0)) {
            switch(IsMateDead(pDis->pos)){
                case MT_NONE:
                case MT_CHECK:
                    break;
                case MT_CHECKMATE:
                    //if (WhiteOnMove(DIS.currentMove)) {
                    if(pDis->pos->side == WHITE){
                        GameEnds(pDis,BlackWins, _T("Black mates"), GE_PLAYER);
                    } else {
						GameEnds(pDis, WhiteWins, _T("White mates"), GE_PLAYER);
                    }
                    break;
     //           case MT_STALEMATE:
					//GameEnds(pDis, GameIsDrawn, _T("Stalemate"), GE_PLAYER);
     //               break;
            }
            break;
        case MachinePlaysBlack:
        case MachinePlaysWhite:
            /* disable certain menu options while machine is thinking */
            SetMachineThinkingEnables(pDis);
            break;
        default:
            break;
    } //switch (DIS.gameMode) End

}





void			/* Apply a move to the given board  */
ApplyMove(position_t *pos,int fromX,int fromY,int toX,int toY){
    //sq_t captured = board[FRto90(toX,toY)];			//得到吃的棋子

    //if (fromY == DROP_RANK) {					    //特殊定义???
    //    /* must be first */
    //    //board[toY][toX] = (ChessSquare) fromX;
    //    board[FRto90(toX,toY)] = fromX;
    //} 
    //else if (fromX == toX && fromY == toY) {		//相同
    //    return;
    //}
    //else {											//正常走步
    //    board[FRto90(toX,toY)]		= board[FRto90(fromX,fromY)];
    //    board[FRto90(fromX,fromY)]	= NOCHESS;
    //}
    //if (DIS.GGQJ.variant == VariantCrazyhouse) {
    //    //#if 0
    //    //		/* !!A lot more code needs to be written to support holdings */
    //    //		if (fromY == DROP_RANK) {
    //    //			/* Delete from holdings */
    //    //			if (holdings[(int) fromX] > 0) holdings[(int) fromX]--;
    //    //		}
    //    //		if (captured != EmptySquare) {
    //    //			/* Add to holdings */
    //    //			if (captured < BlackPawn) {
    //    //				holdings[(int)captured - (int)BlackPawn + (int)WhitePawn]++;
    //    //			} else {
    //    //				holdings[(int)captured - (int)WhitePawn + (int)BlackPawn]++;
    //    //			}
    //    //		}
    //    //#endif
    //} 
    //else if (DIS.GGQJ.variant == VariantAtomic) {
    //    if (captured != NOCHESS) {
    //        //int y, x;
    //        //for (y = toY-1; y <= toY+1; y++) {
    //        //	for (x = toX-1; x <= toX+1; x++) {
    //        //		if (y >= 0 && y <= 7 && x >= 0 && x <= 7 &&
    //        //			board[y][x] != WhitePawn && board[y][x] != BlackPawn) {
    //        //				board[y][x] = EmptySquare;
    //        //			}
    //        //	}
    //        //}
    //        board[FRto90(toX,toY)] = NOCHESS;
    //    }
    //}
}



//将走步转为字符串
TCHAR * move2str(int move, TCHAR *str){
    
    if(move == NULLMOVE){
        swprintf_s(str,8,L"(none)");
    }
    else if(move == NOMOVE){
        swprintf_s(str,8,L"(none)");
    }
    else{
        str[0] = char(StoX(FROM(move)) - 3 + 'a');
        str[1] = char('9' - StoY(FROM(move)) + 3);
        str[2] = char(StoX(TO(move)) - 3 + 'a');
        str[3] = char('9' - StoY(TO(move)) + 3);

        str[4] = 0;
    }
    return str;
}

