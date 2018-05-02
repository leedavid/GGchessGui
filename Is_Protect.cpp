#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"


BOOL isPretectedd(position_t *pos, int side, int sqDst, int sqExcept){

	//走子方是不是有棋子在保护sqDst;

	if(side == WHITE){
		//1, 是不是受相的保护
		if(inBoard(sqDst) & IN_RXIANG){		//可能在红相的保护中
			for(int sq = PieceListStart(pos,RXIANG); sq > 0x32; sq = NextPiece(pos,sq)){
				if(sq != sqExcept && (GetDir(sq,sqDst) & DirXiang) && (pos->b256[(sq+sqDst)/2] == EMPTY)){
					 //还要看一下这个棋能不能走 Is_Can_Move_To_Eat(pos,from,to) 
					if(Is_Can_Move_To_Eat(pos,sq,sqDst)) return TRUE;
				}
			}
		}
		//1, 是不是受仕的保护
		if(inBoard(sqDst) & IN_RSHI){
			for(int sq = PieceListStart(pos,RSHI); sq > 0x32; sq = NextPiece(pos,sq)){
				if(sq != sqExcept && (GetDir(sq,sqDst) & DirShi)){
					if(Is_Can_Move_To_Eat(pos,sq,sqDst)) return TRUE;  //还要看一下这个棋能不能走 
				}
			}
		}
		//2, 是不是受马的保护
		for(int sq = PieceListStart(pos,RMA); sq > 0x32; sq = NextPiece(pos,sq)){
			if(sq != sqExcept){
				int m = horseLegTab(sqDst-sq+256);
				if(m && !pos->b256[sq+m]){
					if(Is_Can_Move_To_Eat(pos,sq,sqDst)) return TRUE;  //还要看一下这个棋能不能走 
				}
			}
		}

		//3, 是不是受到兵,将,车,炮的保护

		int tox = StoX(sqDst);
		int toy = StoY(sqDst);
		int tof = pos->wBitFiles[tox];
		int tor = pos->wBitRanks[toy];

		SlideMoveStruct *psmv;
		// 上下
		psmv = FileMove(toy,tof);

		//得到上面第一个---------------------------------------------------
		int tmp = psmv->RookCap[DUpLeft] + tox;

		if(tmp != sqDst){

			if(tmp != sqExcept){
				if(pos->b256[tmp] == RCHE){
					if(Is_Can_Move_To_Eat(pos,tmp,sqDst)) return TRUE;  //还要看一下这个棋能不能走 
				}
				else if(pos->b256[tmp] == RKING){
					if(tmp+16 == sqDst && toy > 0x9){
						//return TRUE;
						if(Is_Can_Move_To_Eat(pos,tmp,sqDst)) return TRUE;  //还要看一下这个棋能不能走 
					}
				}
			}
			//有了第一个才第二个
			tmp = psmv->CannonCap[DUpLeft] + tox;
			
			if(tmp != sqDst){
				if(tmp != sqExcept){
					if(pos->b256[tmp] == RPAO){
						if(Is_Can_Move_To_Eat(pos,tmp,sqDst)) return TRUE;  //还要看一下这个棋能不能走 
					}
				}
			}
		}
		//得到下面第一个---------------------------------------------------
		tmp = psmv->RookCap[DLoRight] + tox;
		if(tmp != sqDst){
			if(tmp != sqExcept){
				if(pos->b256[tmp] == RCHE){
					if(Is_Can_Move_To_Eat(pos,tmp,sqDst)) return TRUE;  //还要看一下这个棋能不能走 
				}
				else if(pos->b256[tmp] == RKING){
					if(tmp-16 == sqDst && toy > 0x9){
						if(Is_Can_Move_To_Eat(pos,tmp,sqDst)) return TRUE;  //还要看一下这个棋能不能走 
					}
				}
				else if(pos->b256[tmp] == RPAWN){
					if(tmp-16 == sqDst){
						if(Is_Can_Move_To_Eat(pos,tmp,sqDst)) return TRUE;  //还要看一下这个棋能不能走 
					}
				}
			}
			//有了第一个才第二个
			tmp = psmv->CannonCap[DLoRight] + tox;
			if(tmp != sqDst){
				if(tmp != sqExcept){
					if(pos->b256[tmp] == RPAO){
						if(Is_Can_Move_To_Eat(pos,tmp,sqDst)) return TRUE;  //还要看一下这个棋能不能走 
					}
				}
			}
		}
		//得到左面第一个---------------------------------------------------
		psmv = RankMove(tox,tor);

		int nDisp = sqDst & 0xf0;

		tmp = psmv->RookCap[DUpLeft] + nDisp;
		if(tmp != sqDst){
			if(tmp != sqExcept){
				if(pos->b256[tmp] == RCHE){
					if(Is_Can_Move_To_Eat(pos,tmp,sqDst)) return TRUE;  //还要看一下这个棋能不能走 
				}
				else if(pos->b256[tmp] == RPAWN){
					if(toy < 0x8 && tmp+1 == sqDst){
						if(Is_Can_Move_To_Eat(pos,tmp,sqDst)) return TRUE;  //还要看一下这个棋能不能走 
					}
				}
				else if(pos->b256[tmp] == RKING){
					if((inBoard(sqDst) & IN_RKING) && tmp+1 == sqDst){
						if(Is_Can_Move_To_Eat(pos,tmp,sqDst)) return TRUE;  //还要看一下这个棋能不能走 
					}
				}
			}

			//有了第一个才第二个
			tmp = psmv->CannonCap[DUpLeft] + nDisp;
			if(tmp != sqDst){
				if(tmp != sqExcept){
					if(pos->b256[tmp] == RPAO){
						if(Is_Can_Move_To_Eat(pos,tmp,sqDst)) return TRUE;  //还要看一下这个棋能不能走 
					}
				}
			}
		}
		//得到右面第一个---------------------------------------------------
		tmp = psmv->RookCap[DLoRight] + nDisp;
		if(tmp != sqDst){
			if(tmp != sqExcept){
				if(pos->b256[tmp] == RCHE){
					if(Is_Can_Move_To_Eat(pos,tmp,sqDst)) return TRUE;  //还要看一下这个棋能不能走 
				}
				else if(pos->b256[tmp] == RPAWN){
					if(toy < 0x8 && tmp-1 == sqDst){
						if(Is_Can_Move_To_Eat(pos,tmp,sqDst)) return TRUE;  //还要看一下这个棋能不能走 
					}
				}
				else if(pos->b256[tmp] == RKING){
					if((inBoard(sqDst) & IN_RKING) && tmp-1 == sqDst){
						if(Is_Can_Move_To_Eat(pos,tmp,sqDst)) return TRUE;  //还要看一下这个棋能不能走 
					}
				}
			}

			//有了第一个才第二个
			tmp = psmv->CannonCap[DLoRight] + nDisp;
			if(tmp != sqDst){
				if(tmp != sqExcept){
					if(pos->b256[tmp] == RPAO){
						if(Is_Can_Move_To_Eat(pos,tmp,sqDst)) return TRUE;  //还要看一下这个棋能不能走 
					}
				}
			}
		}
	}
	/////////////////////////////////////////////以下是判断黑方有没有保护棋子
	else{ 
		//1, 是不是受象的保护
		if(inBoard(sqDst) & IN_BXIANG){		//可能在黑象的保护中
			for(int sq = PieceListStart(pos,BXIANG); sq > 0x32; sq = NextPiece(pos,sq)){
				if(sq != sqExcept && (GetDir(sq,sqDst) & DirXiang) && (pos->b256[(sq+sqDst)/2] == EMPTY)){
					if(Is_Can_Move_To_Eat(pos,sq,sqDst)) return TRUE;  //还要看一下这个棋能不能走 
				}
			}
		}
		//1, 是不是受仕的保护
		if(inBoard(sqDst) & IN_BSHI){
			for(int sq = PieceListStart(pos,BSHI); sq > 0x32; sq = NextPiece(pos,sq)){
				if(sq != sqExcept && (GetDir(sq,sqDst) & DirShi)){
					if(Is_Can_Move_To_Eat(pos,sq,sqDst)) return TRUE;  //还要看一下这个棋能不能走 
				}
			}
		}
		//2, 是不是受马的保护
		for(int sq = PieceListStart(pos,BMA); sq > 0x32; sq = NextPiece(pos,sq)){
			if(sq != sqExcept){
				int m = horseLegTab(sqDst-sq+256);
				if(m && !pos->b256[sq+m]){
					if(Is_Can_Move_To_Eat(pos,sq,sqDst)) return TRUE;  //还要看一下这个棋能不能走 
				}
			}
		}

		//3, 是不是受到兵,将,车,炮的保护

		int tox = StoX(sqDst);
		int toy = StoY(sqDst);
		int tof = pos->wBitFiles[tox];
		int tor = pos->wBitRanks[toy];

		SlideMoveStruct *psmv;
		// 上下
		psmv = FileMove(toy,tof);

		//得到上面第一个---------------------------------------------------
		int tmp = psmv->RookCap[DUpLeft] + tox;

		if(tmp != sqDst){
			if(tmp != sqExcept){
				if(pos->b256[tmp] == BCHE){
					if(Is_Can_Move_To_Eat(pos,tmp,sqDst)) return TRUE;  //还要看一下这个棋能不能走 
				}
				else if(pos->b256[tmp] == BKING){
					if(tmp+16 == sqDst && toy < 0x6){
						if(Is_Can_Move_To_Eat(pos,tmp,sqDst)) return TRUE;  //还要看一下这个棋能不能走 
					}
				}
				else if(pos->b256[tmp] == BPAWN){
					if(tmp+16 == sqDst){
						if(Is_Can_Move_To_Eat(pos,tmp,sqDst)) return TRUE;  //还要看一下这个棋能不能走 
					}
				}
			}
			//有了第一个才第二个
			tmp = psmv->CannonCap[DUpLeft] + tox;

			if(tmp != sqDst){
				if(tmp != sqExcept){
					if(pos->b256[tmp] == BPAO){
						if(Is_Can_Move_To_Eat(pos,tmp,sqDst)) return TRUE;  //还要看一下这个棋能不能走 
					}
				}
			}
		}
		//得到下面第一个---------------------------------------------------
		tmp = psmv->RookCap[DLoRight] + tox;
		if(tmp != sqDst){
			if(tmp != sqExcept){
				if(pos->b256[tmp] == BCHE){
					if(Is_Can_Move_To_Eat(pos,tmp,sqDst)) return TRUE;  //还要看一下这个棋能不能走 
				}
				else if(pos->b256[tmp] == BKING){
					if(tmp-16 == sqDst && toy < 0x6){
						if(Is_Can_Move_To_Eat(pos,tmp,sqDst)) return TRUE;  //还要看一下这个棋能不能走 
					}
				}
			}
			//有了第一个才第二个
			tmp = psmv->CannonCap[DLoRight] + tox;
			if(tmp != sqDst){
				if(tmp != sqExcept){
					if(pos->b256[tmp] == BPAO){
						if(Is_Can_Move_To_Eat(pos,tmp,sqDst)) return TRUE;  //还要看一下这个棋能不能走 
					}
				}
			}
		}
		//得到左面第一个---------------------------------------------------
		psmv = RankMove(tox,tor);

		int nDisp = sqDst & 0xf0;

		tmp = psmv->RookCap[DUpLeft] + nDisp;
		if(tmp != sqDst){
			if(tmp != sqExcept){
				if(pos->b256[tmp] == BCHE){
					if(Is_Can_Move_To_Eat(pos,tmp,sqDst)) return TRUE;  //还要看一下这个棋能不能走 
				}
				else if(pos->b256[tmp] == BPAWN){
					if(toy > 0x7 && tmp+1 == sqDst){
						if(Is_Can_Move_To_Eat(pos,tmp,sqDst)) return TRUE;  //还要看一下这个棋能不能走 
					}
				}
				else if(pos->b256[tmp] == BKING){
					if((inBoard(sqDst) & IN_BKING) && tmp+1 == sqDst){
						if(Is_Can_Move_To_Eat(pos,tmp,sqDst)) return TRUE;  //还要看一下这个棋能不能走 
					}
				}
			}

			//有了第一个才第二个
			tmp = psmv->CannonCap[DUpLeft] + nDisp;
			if(tmp != sqDst){
				if(tmp != sqExcept){
					if(pos->b256[tmp] == BPAO){
						if(Is_Can_Move_To_Eat(pos,tmp,sqDst)) return TRUE;  //还要看一下这个棋能不能走 
					}
				}
			}
		}
		//得到右面第一个---------------------------------------------------
		tmp = psmv->RookCap[DLoRight] + nDisp;
		if(tmp != sqDst){
			if(tmp != sqExcept){
				if(pos->b256[tmp] == BCHE){
					if(Is_Can_Move_To_Eat(pos,tmp,sqDst)) return TRUE;  //还要看一下这个棋能不能走 
				}
				else if(pos->b256[tmp] == BPAWN){
					if(toy > 0x7 && tmp-1 == sqDst){
						if(Is_Can_Move_To_Eat(pos,tmp,sqDst)) return TRUE;  //还要看一下这个棋能不能走 
					}
				}
				else if(pos->b256[tmp] == BKING){
					if((inBoard(sqDst) & IN_BKING) && tmp-1 == sqDst){
						if(Is_Can_Move_To_Eat(pos,tmp,sqDst)) return TRUE;  //还要看一下这个棋能不能走 
					}
				}
			}

			//有了第一个才第二个
			tmp = psmv->CannonCap[DLoRight] + nDisp;
			if(tmp != sqDst){
				if(tmp != sqExcept){
					if(pos->b256[tmp] == BPAO){
						if(Is_Can_Move_To_Eat(pos,tmp,sqDst)) return TRUE;  //还要看一下这个棋能不能走 
					}
				}
			}
		}
	}

	return FALSE;





}

//上次这个子是不是提供了保护.
BOOL isCanProtect_Last_Move(position_t *pos, int side, int from, int to){
	//if(side == WHITE){
	//	int pc = pos->b256[protect];
	//	if(IsBlack(pc)) return false;
	//	switch(pc){
	//	}
	//}
	//else{
	//}

	int piece = pos->b256[from];

	if(COLOR(piece) != side) return FALSE;

	int tmp;
	switch(piece){
		 case RMA:
        case BMA:
            tmp = horseLegTab(to-from+256);
            return tmp != 0 && pos->b256[from + tmp] == 0;
            break;
        case RXIANG:
        case BXIANG:
            //return ccLegalMoveTab[nDst256 - nSrc256 + 256] == 3 && board->P256[(nSrc256 + nDst256) / 2] == 0;
            return (GetDir(from,to) & DirXiang) && pos->b256[(from+to)/2] == 0;
            break;
        case BSHI:
        case RSHI:
            return (GetDir(from,to) & DirShi) != 0;
            break;
        case RCHE:
        case BCHE:
            {
              int x = StoX(from);
              int y = StoY(from);
              if(x == StoX(to)){
                  //if(cap == EMPTY){
                  //    return (FileMask(y,board->wBitFiles[x])->NonCap & yBitMask(to))  != 0;
                  //}
                  //else{
                     return  (FileMask(y,pos->wBitFiles[x])->RookCap & yBitMask(to)) != 0;

                  //}                   
              }
              else if(y == StoY(to)){
                  //if(cap == EMPTY){
                  //    return (RankMask(x,board->wBitRanks[y])->NonCap & xBitMask(to))  != 0;
                  //}
                  //else{
                     return  (RankMask(x,pos->wBitRanks[y])->RookCap & xBitMask(to)) != 0;

                  //}
              }
            }
            break;
        case RPAO:
        case BPAO:
            {
              int x = StoX(from);
              int y = StoY(from);
              if(x == StoX(to)){
                  //if(cap == EMPTY){
                  //    return (FileMask(y,board->wBitFiles[x])->NonCap & yBitMask(to))  != 0;
                  //}
                  //else{
                     return  (FileMask(y,pos->wBitFiles[x])->CannonCap & yBitMask(to)) != 0;

                  //}                   
              }
              else if(y == StoY(to)){
                  //if(cap == EMPTY){
                  //    return (RankMask(x,board->wBitRanks[y])->NonCap & xBitMask(to))  != 0;
                  //}
                  //else{
                     return  (RankMask(x,pos->wBitRanks[y])->CannonCap & xBitMask(to)) != 0;

                  //}
              }
            }
            break;
        case RPAWN:
            return to == from - 16 || ((to & 0x80) == 0 && (to == from - 1 || to == from + 1));
            break;
        case BPAWN:
            return to == from + 16 || ((to & 0x80) != 0 && (to == from - 1 || to == from + 1));
            break;
        case RKING:
        case BKING:
            return (GetDir(from,to) & DirKing) != 0;
            break;
        default:
            return FALSE;
            break;
	}



	return FALSE;
}