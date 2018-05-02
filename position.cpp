#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

void
InitPosition(dispboard_t* pDis, int redraw) {
    //DIS.currentMove = DIS.forwardMostMove = DIS.backwardMostMove = 0;
    pDis->pos->curStep = pDis->pos->gply = 0;
    set_position(pDis, pDis->pos, StartFen);

       //保存一下b256
    CopyBoard(pDis->B256dis[0],pDis->pos->b256);

    if (redraw){
        //DrawPosition(false,DIS.pos.B256dis[DIS.currentMove]);
        DrawPosition(pDis,false,pDis->B256dis[pDis->pos->curStep]);
    }
}



void init_position(position_t *pos){

    memset(pos,0,sizeof(position_t));
}


void init_piece_lists(position_t *pos){
    int sq, piece;

    for(piece = RPAWN; piece >= RSHI; piece--){
        PieceListStart(pos,piece)   = piece-1;
        PrevPiece(pos,piece-1)      = piece;
    }

    for(piece = BPAWN; piece >= BSHI; piece--){
        PieceListStart(pos,piece)   = piece-1;
        PrevPiece(pos,piece-1)    = piece;
    }



    PieceListStart(pos,RKING) = PieceListStart(pos,BKING) = PieceListEnd;


    for(sq = 0x33; sq < 0xcc; sq++){
        int chess = pos->b256[sq];
        if(inBoard(sq) && chess != EMPTY){
            InsertPiece(pos,chess,sq);
        }
    }
}


BOOL set_position(dispboard_t* pDis, position_t *pos, TCHAR *fen){      //从fen得到当前的局面情况
    
    init_position(pos);

    int pf  = 0;
    int c   = fen[pf];
    int number[16];

    //int posVal = 0;

    for(int i = 0; i<16; i++){
        number[i] = 0;
    }

    for(int rank = 0; rank <= 9; rank++){
        for(int file = 0; file <=8;){
            int sq256 = XYtoS(file+3, rank+3);
            
            if(c >= '1' && c <= '9'){
                int len = c - '0';

                for(int i = 0; i < len; i++){
                    if(file > 8){
                        printf("Error>行空格不正确,board_from_fen(): bad FEN (pos=%d)\n",pf);
						return FALSE;
                    }
                    pos->b256[sq256] = EMPTY;
                    file++;
                }
            }
            else{   //// piece, 这是一个棋子
                int piece = piece_from_char(c);
                if(piece == -1){
                    printf("Error>棋子不对, board_from_fen(): bad FEN (pos=%d)\n",pf);
					return FALSE;
                }
                pos->b256[sq256] = piece;

                //posVal += PstVal[piece][sq256];

                number[piece] ++;

                pos->wBitFiles[StoX(sq256)] ^= yBitMask(sq256);
                pos->wBitRanks[StoY(sq256)] ^= xBitMask(sq256);

                file++;
            }
            c = fen[++pf];
        }
        if(rank < 9){
            if( c != '/'){
                 printf("Error>棋子没行结束,board_from_fen(): bad FEN (pos=%d)\n",pf);
				 return FALSE;
            }
            c = fen[++pf];
        }
    }
    
       // active colour
    if(c != ' '){
        printf("Error>棋子后没有空格,board_from_fen(): bad FEN (pos=%d)\n",pf);
		return FALSE;
    }

        c = fen[++pf];

    switch(c){
     case 'r':
     case 'R':
     case 'w':
     case 'W':
         pos->side = WHITE;
         break;
     case 'b':
     case 'B':
         pos->side = BLACK;
         //board->hkey   ^=  ZobKeyTurn;
         //hlock  ^=  dwZobLockTurn;
         break;
     default:
         printf("Error>走子方不对, board_from_fen(): bad FEN (pos=%d)\n",pf);
		 return FALSE;
         break;
    }


    init_piece_lists(pos);

    //pos->key  = compute_hash_key(pos);
    //pos->pkey = compute_phash_key(pos);


    //pos->StartRec.key     = pos->key;
    //pos->StartRec.pkey    = pos->pkey;
    pos->gply    = 0;
    pos->curStep = 0;
    //pos->nonCap = 0;
    //pos->StartRec.ischeck = isTurnInCheck(pos);

    Record* re = &pos->His[pos->gply];

    re->key     = compute_hash_key(pos);

#ifdef USE_PAWN_HASH 
    re->pkey    = compute_phash_key(pos);
#endif

    re->move    = 0;
    re->nonCap  = 0;
    //re->posVal  = posVal;
    re->ischeck = isTurnInCheck(pos,pos->side);

    //保存一下256棋盘  ReBoard
    //memcpy(pos->disBoard[pos->gply],pos->b256,256);

    memcpy(pDis->B256dis[pos->gply],pos->b256,256);

	/////////////////////////////////////////////////////////////////////
	// 再看一下有没有走步
    //
	TCHAR *pc = wcsstr(fen, L"moves ");

	if (pc == NULL) return true;

	TCHAR *pend = pc + wcslen(pc);

	pc += 6;

	while ((*pc) != '\0' && pc < pend && *pc != ' '){
		int move = str2move(pDis->pos, pc);

		if (move){
			//MakeMove(pDis,fromX, fromY, toX, toY,true); /*updates forwardMostMove*/
			int from = FROM(move);
			int to = TO(move);

			int fromX = StoX(from) - 3;
			int fromY = StoY(from) - 3;
			int toX = StoX(to) - 3;
			int toY = StoY(to) - 3;

			MakeMove(pDis, fromX, fromY, toX, toY, FALSE);
			ShowMove(pDis, fromX, fromY, toX, toY);
			pc += 5;
		}
		else{
			break;
		}
	}

	//TCHAR* pStr = pgn->strStepScore;
	for (int i = 0; i <= pDis->pos->gply; i++){
		pDis->pos->His[i].search_score = 0;
	}

    ASSERT(position_is_ok(pos));

    //if(isTurnInCheck(pos,pos->side ^0x1)){
    //    return false;
    //}
    return TRUE;
}

//走子方是不是被将军
int isTurnInCheck(position_t * pos, int side){
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

//将棋子的Ｂ２５６转换成fen
void position_to_fen_by_b256(uint8 B256[256],int side, TCHAR* fen){
    int pc = 0;
    for(int rank = 0; rank <= 9; rank ++){
        for(int file = 0; file <= 8;){
            int sq256 = XYtoS(file+3, rank+3);
            int piece = B256[sq256];
            int c;
            ASSERT(piece < 16);

           

            if(piece == 0){
                int len = 0;
                for(; file <= 8 && B256[XYtoS(file+3,rank+3)] == 0; file++){
                    len ++;
                }

                ASSERT(len>=1&&len<=9);

                c = '0' + len;
            }
            else{
                c = piece_to_char(piece);
                file++;
            }
            fen[pc++] = c;
        }
        fen[pc++] = '/';
    }
    fen[pc-1] = ' '; // HACK: remove the last '/'   
    fen[pc++] = (side==WHITE) ? 'w' : 'b';
    swprintf_s(fen+pc, 128, L" - - %d %d", 0, 1);    
}


//int start = pDis->pos->curStep;
//int startSide = pDis->pos->side;

void board_red2black(dispboard_t* pDis){

	uint8  B256New[256];
	uint8* B256 = pDis->B256dis[pDis->pos->curStep];
	memset(B256New, EMPTY, sizeof(B256New));

	for (int rank = 0; rank <= 9; rank++){
		for (int file = 0; file <= 8; file++){
			int sq256 = XYtoS(file + 3, rank + 3);
			int piece = B256[sq256];

			if (piece != EMPTY){
				int npiece = r2b_chess[piece];
				int s90 = rank * 9 + file;
				int f90 = 89 - s90;
				int nrank = f90 / 9;
				int nfile = f90 % 9;
				int n256 = XYtoS(nfile + 3, nrank + 3);
				B256New[n256] = npiece;
			}
		}
	}
	memcpy(B256, B256New, sizeof(B256New));
	pDis->pos->side ^= 1;

	TCHAR fen[2048];

	PositionToFEN(pDis, fen, pDis->pos->curStep, UCCI_UCCI_ms);
	set_position(pDis, pDis->pos, fen);

}

//static const  Piece r2b_chess[16] = {
//	EMPTY,  //这个不用了
//	BKING, BSHI, BXIANG, BMA, BCHE, BPAO, BPAWN,
//	_X_X,
//	RKING, RSHI, RXIANG, RMA, RCHE, RPAO, RPAWN,
//};




void
PositionToFEN(dispboard_t* pDis, TCHAR *fen, int move, int ucci){

	position_to_fen_by_b256(pDis->B256dis[move],pDis->pos->side, fen);
   
}
