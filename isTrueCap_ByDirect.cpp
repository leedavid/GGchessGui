#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"
/*
//是不是走的子或直接构成捉
BOOL isTrueCap_ByDirect(position_t *pos,int mto,int to, int from, int which){

	int moveChess = pos->b256[mto];

	int tox = StoX(to);
	int toy = StoY(to);

	int tof = pos->wBitFiles[tox];
	int tor = pos->wBitRanks[toy];   

	if(which == WHITE){
		//1, 看一下是不是走的棋在直接捉对方
		switch(moveChess){
		case BPAWN:       //这个不用算
			//dummy;
			break;
		case BKING:       //这个不用算
			//dummy;
			break;
		case BSHI:{
			if((GetDir(mto,to) & DirShi) != 0){
				if(Is_True_Cap(pos, mto,to,from,to,which)){
					return TRUE;
				}
			}
				  }
				  break;
		case BXIANG:{
			if((GetDir(mto,to) & DirXiang) != 0 && pos->b256[(mto+to)/2] == 0){
				if(Is_True_Cap(pos,mto,to,from,to,which)){
					return TRUE;
				}
			}
					}
					break;
		case BMA:{
			int t = horseLegTab(to - mto + 256);
			if(t != 0 && pos->b256[mto + t] == EMPTY){
				if(Is_True_Cap(pos,mto,to,from,to,which)){
					return TRUE;
				}
			}
				 }
				 break;
		case BPAO:{
			if(false){
			}
			else if(StoX(mto) == StoX(to)){
				if((FileMask(StoY(mto),tof)->CannonCap & yBitMask(to)) != 0){
					if(Is_True_Cap(pos,mto,to,from,to,which)){
						return TRUE;
					}
				}
			}
			else if(StoY(mto) == StoY(to)){
				if((RankMask(StoX(mto),tor)->CannonCap & xBitMask(to)) != 0){
					if(Is_True_Cap(pos,mto,to,from,to,which)){
						return TRUE;
					}
				}
			}
				  }
				  break;
		case BCHE:{
			if(false){
			}
			else if(StoX(mto) == StoX(to)){
				if((FileMask(StoY(mto),tof)->RookCap & yBitMask(to)) != 0){
					if(Is_True_Cap(pos,mto,to,from,to,which)){
						return TRUE;
					}
				}
			}
			else if(StoY(mto) == StoY(to)){
				if((RankMask(StoX(mto),tor)->RookCap & xBitMask(to)) != 0){
					if(Is_True_Cap(pos,mto,to,from,to,which)){
						return TRUE;
					}
				}
			}

				  }
				  break;
		default:
			break;
		}
	}
	else{
		switch(moveChess){
		case RPAWN:       //这个不用算
			//dummy;
			break;
		case RKING:       //这个不用算
			//dummy;
			break;
		case RSHI:{
			if((GetDir(mto,to) & DirShi) != 0){
				if(Is_True_Cap(pos,mto,to,from,to,which)){
					return TRUE;
				}
			}
				  }
				  break;
		case RXIANG:{
			if((GetDir(mto,to) & DirXiang) != 0 && pos->b256[(mto+to)/2] == 0){
				if(Is_True_Cap(pos,mto,to,from,to,which)){
					return TRUE;
				}
			}
					}
					break;
		case RMA:{
			int t = horseLegTab(to - mto + 256);
			if(t != 0 && pos->b256[mto + t] == EMPTY){
				if(Is_True_Cap(pos,mto,to,from,to,which)){
					return TRUE;
				}
			}
				 }
				 break;
		case RPAO:{
			if(false){
			}
			else if(StoX(mto) == StoX(to)){
				if((FileMask(StoY(mto),tof)->CannonCap & yBitMask(to)) != 0){
					if(Is_True_Cap(pos,mto,to,from,to,which)){
						return TRUE;
					}
				}
			}
			else if(StoY(mto) == StoY(to)){
				if((RankMask(StoX(mto),tor)->CannonCap & xBitMask(to)) != 0){
					if(Is_True_Cap(pos,mto,to,from,to,which)){
						return TRUE;
					}
				}
			}
				  }
				  break;
		case RCHE:{
			if(false){
			}
			else if(StoX(mto) == StoX(to)){
				if((FileMask(StoY(mto),tof)->RookCap & yBitMask(to)) != 0){
					if(Is_True_Cap(pos,mto,to,from,to,which)){
						return TRUE;
					}
				}
			}
			else if(StoY(mto) == StoY(to)){
				if((RankMask(StoX(mto),tor)->RookCap & xBitMask(to)) != 0){
					if(Is_True_Cap(pos,mto,to,from,to,which)){
						return TRUE;
					}
				}
			}

				  }
				  break;
		default:
			break;
		}
	}


	return FALSE;
}

BOOL testall_TrueCap_noPawnKing(position_t *pos,int to, int from, int which){

	if(which == WHITE){
		//看有没有其它的黑子在捉红方
		//黑车
		for(int mto = PieceListStart(pos,BCHE); mto > 0x32; mto = NextPiece(pos,mto)){
			if(isTrueCap_ByDirect(pos,mto,to,from,which)) return TRUE;
		}
		//黑炮
		for(int mto = PieceListStart(pos,BPAO); mto > 0x32; mto = NextPiece(pos,mto)){
			if(isTrueCap_ByDirect(pos,mto,to,from,which)) return TRUE;
		}
		//黑马的所有走步
		for(int mto = PieceListStart(pos,BMA); mto > 0x32; mto = NextPiece(pos,mto)){
			if(isTrueCap_ByDirect(pos,mto,to,from,which)) return TRUE;
		}
		//黑相的所有走步
		for(int mto = PieceListStart(pos,BXIANG); mto > 0x32; mto = NextPiece(pos,mto)){
			if(isTrueCap_ByDirect(pos,mto,to,from,which)) return TRUE;
		}

		//黑士的所有走步
		for(int mto = PieceListStart(pos,BSHI); mto > 0x32; mto = NextPiece(pos,mto)){
			if(isTrueCap_ByDirect(pos,mto,to,from,which)) return TRUE;
		}

	}
	else{
		//红车
		for(int mto = PieceListStart(pos,RCHE); mto > 0x32; mto = NextPiece(pos,mto)){
			if(isTrueCap_ByDirect(pos,mto,to,from,which)) return TRUE;
		}
		//红炮
		for(int mto = PieceListStart(pos,RPAO); mto > 0x32; mto = NextPiece(pos,mto)){
			if(isTrueCap_ByDirect(pos,mto,to,from,which)) return TRUE;
		}
		//红马的所有走步
		for(int mto = PieceListStart(pos,RMA); mto > 0x32; mto = NextPiece(pos,mto)){
			if(isTrueCap_ByDirect(pos,mto,to,from,which)) return TRUE;
		}
		//红相的所有走步
		for(int mto = PieceListStart(pos,RXIANG); mto > 0x32; mto = NextPiece(pos,mto)){
			if(isTrueCap_ByDirect(pos,mto,to,from,which)) return TRUE;
		}

		//红士的所有走步
		for(int mto = PieceListStart(pos,RSHI); mto > 0x32; mto = NextPiece(pos,mto)){
			if(isTrueCap_ByDirect(pos,mto,to,from,which)) return TRUE;
		}
	}

	return FALSE;
}
*/
//BOOL testall_TrueCap_noPawnKing_W_NewCap(position_t *pos,int mfrom,int mto, int from, int to, int which){
//
//	if(which == WHITE){
//		//看有没有其它的黑子在捉红方
//		//黑车
//		for(int cap = PieceListStart(pos,BCHE); cap > 0x32; cap = NextPiece(pos,cap)){
//			//if(mto == cap || (IsReleasePiece(){  //走子方不是去捉的子
//			//	//让开了车去捉??
//			//}
//			//else{
//			//	if(isTrueCap_ByDirect(pos,cap,to,from,which)) return TRUE;
//			//}
//			
//		}
//		//黑炮
//		for(int cap = PieceListStart(pos,BPAO); cap > 0x32; cap = NextPiece(pos,cap)){
//			if(mto != cap){  //走子方不是去捉的子
//				
//			}
//			else{
//				if(isTrueCap_ByDirect(pos,cap,to,from,which)) return TRUE;
//			}
//		}
//		//黑马
//		for(int cap = PieceListStart(pos,BMA); cap > 0x32; cap = NextPiece(pos,cap)){
//			if(mto != cap){  //走子方不是去捉的子
//				
//			}
//			else{
//				if(isTrueCap_ByDirect(pos,cap,to,from,which)) return TRUE;
//			}
//		}
//		//黑相
//		for(int cap = PieceListStart(pos,BXIANG); cap > 0x32; cap = NextPiece(pos,cap)){
//			if(mto != cap){  //走子方不是去捉的子, 是不是让开了象去捉的,或者解放了象去捉的. 
//				
//			}
//			else{
//				if(isTrueCap_ByDirect(pos,cap,to,from,which)) return TRUE;
//			}
//		}
//
//		//黑士
//		for(int cap = PieceListStart(pos,BSHI); cap > 0x32; cap = NextPiece(pos,cap)){
//			//if(mto != cap){  //走子方不是去捉的子
//			//	
//			//}
//			//else{
//				if(isTrueCap_ByDirect(pos,cap,to,from,which)) return TRUE;
//			//}
//		}
//
//	}
//	else{
//		//红车
//		for(int cap = PieceListStart(pos,RCHE); cap > 0x32; cap = NextPiece(pos,cap)){
//			if(mto != cap){  //走子方不是去捉的子
//				
//			}
//			else{
//				if(isTrueCap_ByDirect(pos,cap,to,from,which)) return TRUE;
//			}
//		}
//		//红炮
//		for(int cap = PieceListStart(pos,RPAO); cap > 0x32; cap = NextPiece(pos,cap)){
//			if(mto != cap){  //走子方不是去捉的子
//				
//			}
//			else{
//				if(isTrueCap_ByDirect(pos,cap,to,from,which)) return TRUE;
//			}
//		}
//		//红马
//		for(int cap = PieceListStart(pos,RMA); cap > 0x32; cap = NextPiece(pos,cap)){
//			if(mto != cap){  //走子方不是去捉的子
//				
//			}
//			else{
//				if(isTrueCap_ByDirect(pos,cap,to,from,which)) return TRUE;
//			}
//		}
//		//红相
//		for(int cap = PieceListStart(pos,RXIANG); cap > 0x32; cap = NextPiece(pos,cap)){
//			if(mto != cap){  //走子方不是去捉的子
//				
//			}
//			else{
//				if(isTrueCap_ByDirect(pos,cap,to,from,which)) return TRUE;
//			}
//		}
//
//		//红士
//		for(int cap = PieceListStart(pos,RSHI); cap > 0x32; cap = NextPiece(pos,cap)){
//			//if(mto != cap){  //走子方不是去捉的子
//			//	
//			//}
//			//else{
//				if(isTrueCap_ByDirect(pos,cap,to,from,which)) return TRUE;
//			//}
//		}
//	}
//
//	return FALSE;
//
//}