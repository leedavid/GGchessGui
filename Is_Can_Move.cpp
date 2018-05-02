#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"


BOOL Is_Can_Move_To_Eat(position_t *pos,int from, int to){

    int tmp;

	int fx      = StoX(from);
    int fy      = StoY(from);

	int tx      = StoX(to);
    int ty      = StoY(to);

	int kpos;

	if(IsWhite(pos->b256[from])){
		if(pos->b256[from] != RKING){
			kpos = PieceListStart(pos,RKING);
		}
		else{
			kpos = to;
		}
	}
	else{
		if(pos->b256[from] != BKING){
		    kpos = PieceListStart(pos,BKING);
		}
		else{
			kpos = to;
		}
	}

	int kx       = StoX(kpos);
    int ky       = StoY(kpos);

    int kr       = pos->wBitRanks[ky];
    int kf       = pos->wBitFiles[kx];

    int tr       = pos->wBitRanks[ty];
    int tf       = pos->wBitFiles[tx];        //



	if(IsWhite(pos->b256[from])){          //判断红的能不能走棋
		// a, 在将军的马腿上的棋子不可走, 但如果是吃那个马就可走
		//for(tmp = PieceListStart(pos,BMA); tmp > 0x32; tmp = NextPiece(pos,tmp)){
		//	int m = horseLegTab(kpos-tmp+256);
		//	if(m){
		//		if((tmp+m)==from && to != tmp){
		//			return FALSE;
		//		}
		//	}
		//}
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

		//再计算一下, 车,炮,将能不能将, 这儿得加上将哇
		for(tmp = PieceListStart(pos,BCHE); tmp > 0x32; tmp = NextPiece(pos,tmp)){
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
		//再计算一下炮
		for(tmp = PieceListStart(pos,BPAO); tmp > 0x32; tmp = NextPiece(pos,tmp)){
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
		//再计算一下是不是对将了
		tmp = PieceListStart(pos,BKING);
		if(StoX(tmp) == kx){
			if(psmsFile->RookCap & yBitMask(tmp)){
				return (FALSE);
			}
		}

		/*for(tmp = PieceListStart(pos,BMA); tmp > 0x32 && to != tmp; tmp = NextPiece(pos,tmp)){*/
		for(tmp = PieceListStart(pos,BMA); tmp > 0x32 ; tmp = NextPiece(pos,tmp)){

			if(to != tmp){
				int m = horseLegTab(kpos-tmp+256);
				if(m){
					//if((tmp+m)==from && to != tmp){
					//	return FALSE;
					//}

					//if(!pos->b256[tmp+m]){   //马腿上没有棋子
					//	return FALSE;
					//}

					if(from == tmp + m){
						return false;
					}
				}
			}
		}
	}
	else{                                  //判断黑的能不能走棋
		//for(tmp = PieceListStart(pos,RMA); tmp > 0x32; tmp = NextPiece(pos,tmp)){
		//	int m = horseLegTab(kpos-tmp+256);
		//	if(m){   //红马可能在将军
		//		//if((tmp+m)==from && to != tmp){
		//		//	return FALSE;  //在红马的将军的脚上的棋不能走
		//		//}
		//		if(!pos->b256[tmp+m]){   //马腿上没有棋子
		//		}
		//		else if((tmp+m)==from && to != tmp){
		//			return FALSE;
		//		}
		//	}
		//}
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

		/*for(tmp = PieceListStart(pos,RMA); tmp > 0x32 && to != tmp; tmp = NextPiece(pos,tmp)){*/
		for(tmp = PieceListStart(pos,RMA); tmp > 0x32 ; tmp = NextPiece(pos,tmp)){
            
			if(to != tmp){

				int m = horseLegTab(kpos-tmp+256);
				if(m){   //红马可能在将军
					//if((tmp+m)==from && to != tmp){
					//	return FALSE;  //在红马的将军的脚上的棋不能走
					//}
					//if(!pos->b256[tmp+m]){   //马腿上没有棋子
					//	return FALSE;
					//}

					if(from == tmp + m){
						return false;
					}

					//if((tmp+m)==from && to != tmp){
					//	return FALSE;
					//}
				}
			}
		}
	}

	return TRUE;
}

