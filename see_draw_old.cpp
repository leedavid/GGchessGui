#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

/*
//通过SEE来判断连捉
BOOL see_draw_20080818(position_t *pos,int mfrom,int mto, int from, int to, int which){


	int sq2;
	SlideMoveStruct *psmv;

	//当前是黑方在走棋
	if(which == WHITE){   
		//1, 切断对方的炮的保护,捉对方"不动"的子	
		for(int ot_pao = PieceListStart(pos,RPAO); ot_pao > 0x32; ot_pao = NextPiece(pos,ot_pao)){	
			//1,**************************************************
			if(StoX(mfrom) == StoX(ot_pao)){			//从炮的File上离开
				if(StoX(mto) != StoX(ot_pao)){					
					//看一下炮的上下信息
					psmv = FileMove(StoY(ot_pao),pos->wBitFiles[StoX(ot_pao)]);
					if(StoY(mfrom) > StoY(ot_pao)){		//在炮的下面
						int sq1 = psmv->RookCap[DLoRight] + StoX(ot_pao);
						if(StoY(mfrom) < StoY(sq1) && IsWhite(pos->b256[sq1]) && testall_TrueCap_noPawnKing(pos,sq1,from,which)){
							return TRUE;
						}
					}
					else{
						int sq1 = psmv->RookCap[DUpLeft] + StoX(ot_pao);
						if(StoY(mfrom) > StoY(sq1) && IsWhite(pos->b256[sq1]) && testall_TrueCap_noPawnKing(pos,sq1,from,which)){
							return TRUE;
						}						
					}
				}										
			}
			//2,**************************************************
			if(StoX(mto) == StoX(ot_pao)){			//走到炮的File上
				if(StoX(mfrom) != StoX(ot_pao)){					
					//看一下炮的上下信息
					psmv = FileMove(StoY(ot_pao),pos->wBitFiles[StoX(ot_pao)]);
					if(StoY(mto) > StoY(ot_pao)){		//在炮的下面
						int sq3 = psmv->SuperCap[DLoRight] + StoX(ot_pao);
						if(StoY(mto) < StoY(sq3) && IsWhite(pos->b256[sq3]) && testall_TrueCap_noPawnKing(pos,sq3,from,which)){
							return TRUE;
						}
					}
					else{
						int sq3 = psmv->SuperCap[DUpLeft] + StoX(ot_pao);
						if(StoY(mto) > StoY(sq3)&& IsWhite(pos->b256[sq3]) && testall_TrueCap_noPawnKing(pos,sq3,from,which)){
							return TRUE;
						}
					}
				}

			}
			//3,**************************************************
			if(StoY(mfrom) == StoY(ot_pao)){			//从炮的Rank上离开
				if(StoY(mto) != StoY(ot_pao)){
					//看一下炮的左右信息
					psmv = RankMove(StoX(ot_pao),pos->wBitRanks[StoY(ot_pao)]);
					if(StoX(mfrom) > StoX(ot_pao)){
						int sq1 = psmv->RookCap[DLoRight] + (ot_pao & 0xf0);
						if(StoX(mfrom) < StoX(sq1)  && IsWhite(pos->b256[sq1]) && testall_TrueCap_noPawnKing(pos,sq1,from,which)){
							return TRUE;
						}						
					}
					else{
						int sq1 = psmv->RookCap[DUpLeft] + (ot_pao & 0xf0);
						if(StoX(mfrom) > StoX(sq1) && IsWhite(pos->b256[sq1]) && testall_TrueCap_noPawnKing(pos,sq1,from,which)){
							return TRUE;
						}						
					}
				}
			}
			//4,**************************************************
			if(StoY(mto) == StoY(ot_pao)){			//走到炮的Rank上
				if(StoY(mfrom) != StoY(ot_pao)){
					//看一下炮的左右信息
					psmv = RankMove(StoX(ot_pao),pos->wBitRanks[StoY(ot_pao)]);
					if(StoX(mto) > StoX(ot_pao)){
						int sq3 = psmv->SuperCap[DLoRight] + (ot_pao & 0xf0);
						if(StoX(mto) < StoX(sq3) && IsWhite(pos->b256[sq3]) && testall_TrueCap_noPawnKing(pos,sq3,from,which)){
							return TRUE;
						}
					}
					else{
						int sq3 = psmv->SuperCap[DUpLeft] + (ot_pao & 0xf0);
						if(StoX(mto) > StoX(sq3) && IsWhite(pos->b256[sq3]) && testall_TrueCap_noPawnKing(pos,sq3,from,which)){
							return TRUE;
						}
					}
				}
			}
		}

		//2, 切断对方的马的保护,捉对方"不动"的子,这个情况少一些　	
		//3, 切断对方的相的保护,捉对方"不动"的子,这个情况少一些	
		
		//2, 让开了炮,捉对方"不动"的子	
		//fen 3aknr2/4a4/4b4/p4PN1p/4R4/P1R5P/3r2c2/4C2C1/4A1c2/2B1KAB2 w - - 13 13 
		//让开炮常打相
		//#####################################################################
		//是不是让开了炮,捉对方"不动"的子	
		for(int at = PieceListStart(pos,BPAO); at > 0x32; at = NextPiece(pos,at)){
			if(at != mto){		//走的不是那个炮							
				//1,**************************************************
				if(StoX(mfrom) == StoX(at)){			//从炮的File上离开
					if(StoX(mto) != StoX(at)){					
						//看一下炮的上下信息
						psmv = FileMove(StoY(at),pos->wBitFiles[StoX(at)]);
						if(StoY(mfrom) > StoY(at)){		//在炮的下面
							sq2 = psmv->CannonCap[DLoRight] + StoX(at);
							//if(IsWhitePaoNoRiverPawn(sq2) && StoY(mfrom) < StoY(sq2) ){   //走的棋在sq2 与 at 的中间
							if(IsWhite(pos->b256[sq2]) && StoY(mfrom) < StoY(sq2) ){   //走的棋在sq2 与 at 的中间
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
						else{
							sq2 = psmv->CannonCap[DUpLeft] + StoX(at);
							//if(IsWhitePaoNoRiverPawn(sq2)  && StoY(mfrom) > StoY(sq2) ){
							if(IsWhite(pos->b256[sq2]) && StoY(mfrom) > StoY(sq2) ){
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
					}										
				}
				//2,**************************************************
				if(StoX(mto) == StoX(at)){			//走到炮的File上
					if(StoX(mfrom) != StoX(at)){					
						//看一下炮的上下信息
						psmv = FileMove(StoY(at),pos->wBitFiles[StoX(at)]);

						if(StoY(mto) > StoY(at)){		//在炮的下面
							sq2 = psmv->CannonCap[DLoRight] + StoX(at);
							//if(IsWhitePaoNoRiverPawn(sq2)  && StoY(mto) < StoY(sq2) ){///⑽⑽劫难逃
							if(IsWhite(pos->b256[sq2]) && StoY(mto) < StoY(sq2) ){
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
						else{
							sq2 = psmv->CannonCap[DUpLeft] + StoX(at);
							//if(IsWhitePaoNoRiverPawn(sq2)  && StoY(mto) > StoY(sq2) ){
							if(IsWhite(pos->b256[sq2]) && StoY(mto) > StoY(sq2) ){
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
					}

				}
				//3,**************************************************
				if(StoY(mfrom) == StoY(at)){			//从炮的Rank上离开
					if(StoY(mto) != StoY(at)){
						//看一下炮的左右信息
						psmv = RankMove(StoX(at),pos->wBitRanks[StoY(at)]);

						if(StoX(mfrom) > StoX(at)){
							sq2 = psmv->CannonCap[DLoRight] + (at & 0xf0);
							//if(IsWhitePaoNoRiverPawn(sq2)  && StoX(mfrom) < StoX(sq2) ){
							if(IsWhite(pos->b256[sq2]) && StoX(mfrom) < StoX(sq2) ){
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
						else{
							sq2 = psmv->CannonCap[DUpLeft] + (at & 0xf0);
							//if(IsWhitePaoNoRiverPawn(sq2)  && StoX(mfrom) > StoX(sq2) ){
							if(IsWhite(pos->b256[sq2]) && StoX(mfrom) > StoX(sq2) ){
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
					}
				}
				//4,**************************************************
				if(StoY(mto) == StoY(at)){			//走到炮的Rank上
					if(StoY(mfrom) != StoY(at)){
						//看一下炮的左右信息
						psmv = RankMove(StoX(at),pos->wBitRanks[StoY(at)]);

						if(StoX(mto) > StoX(at)){
							sq2 = psmv->CannonCap[DLoRight] + (at & 0xf0);
							//if(IsWhitePaoNoRiverPawn(sq2)  && StoX(mto) < StoX(sq2) ){ 
							if(IsWhite(pos->b256[sq2]) && StoX(mto) < StoX(sq2) ){ 
								if(Is_True_Cap(pos,at,sq2,from,to,which)){  //BOOL Is_True_Cap(position_t *pos,int from, int to, int ot_from,int ot_to, int which){
									return TRUE;
								}
							}
						}
						else{
							sq2 = psmv->CannonCap[DUpLeft] + (at & 0xf0);
							//if(IsWhitePaoNoRiverPawn(sq2)  && StoX(mto) > StoX(sq2)){
							if(IsWhite(pos->b256[sq2]) && StoX(mto) > StoX(sq2)){
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
					}
				}

				//
			}
		}
		//#####################################################################
		//看一下是不是让开了车在捉,捉对方"不动"的子	
		for(int at = PieceListStart(pos,BCHE); at > 0x32; at = NextPiece(pos,at)){
			if(at != mto){		//走的不是那个炮							
				//1,**************************************************
				if(StoX(mfrom) == StoX(at)){			//从炮的File上离开
					if(StoX(mto) != StoX(at)){					
						//看一下炮的上下信息
						psmv = FileMove(StoY(at),pos->wBitFiles[StoX(at)]);

						if(StoY(mfrom) > StoY(at)){		//在炮的下面
							sq2 = psmv->RookCap[DLoRight] + StoX(at);
							if(IsWhite(pos->b256[sq2]) && StoY(mfrom) < StoY(sq2) ){   //走的棋在sq2 与 at 的中间
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
						else{
							sq2 = psmv->RookCap[DUpLeft] + StoX(at);
							if(IsWhite(pos->b256[sq2]) && StoY(mfrom) > StoY(sq2) ){
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
					}										
				}
				//2,**************************************************
				if(StoX(mto) == StoX(at)){			//走到车的File上
					if(StoX(mfrom) != StoX(at)){					
						//看一下车的上下信息
						psmv = FileMove(StoY(at),pos->wBitFiles[StoX(at)]);

						if(StoY(mto) > StoY(at)){		//在车的下面
							sq2 = psmv->RookCap[DLoRight] + StoX(at);
							if(IsWhite(pos->b256[sq2]) && StoY(mto) < StoY(sq2) ){
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
						else{
							sq2 = psmv->RookCap[DUpLeft] + StoX(at);
							if(IsWhite(pos->b256[sq2]) && StoY(mto) > StoY(sq2) ){
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
					}

				}
				//3,**************************************************
				if(StoY(mfrom) == StoY(at)){			//从车的Rank上离开
					if(StoY(mto) != StoY(at)){
						//看一下车的左右信息
						psmv = RankMove(StoX(at),pos->wBitRanks[StoY(at)]);

						if(StoX(mfrom) > StoX(at)){
							sq2 = psmv->RookCap[DLoRight] + (at & 0xf0);
							if(IsWhite(pos->b256[sq2]) && StoX(mfrom) < StoX(sq2) ){
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
						else{
							sq2 = psmv->RookCap[DUpLeft] + (at & 0xf0);
							if(IsWhite(pos->b256[sq2]) && StoX(mfrom) > StoX(sq2) ){
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
					}
				}
				//4,**************************************************
				if(StoY(mto) == StoY(at)){			//从车的Rank上离开
					if(StoY(mfrom) != StoY(at)){
						//看一下车的左右信息
						psmv = RankMove(StoX(at),pos->wBitRanks[StoY(at)]);

						if(StoX(mto) > StoX(at)){
							sq2 = psmv->RookCap[DLoRight] + (at & 0xf0);
							if(IsWhite(pos->b256[sq2]) && StoX(mto) < StoX(sq2) ){
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
						else{
							sq2 = psmv->RookCap[DUpLeft] + (at & 0xf0);
							if(IsWhite(pos->b256[sq2]) && StoX(mto) > StoX(sq2)){
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
					}
				}
				//
			}
		}

		//fen 4kab2/4a4/2n1b4/p1p1c3p/4R4/2P1P4/P5r1P/C3BcN2/5C3/3AKAB2 w - - 0 0


        //   以上是判断常捉对方不动的子，下面要判断常捉对方走动的子．
		//B, 常捉走动的子. 这个可用先前的捉, 现在的捉去判断一下.是不是多了数目. 
		//1, 切断对方的炮的联系捉, 这儿是常捉吃不动的子, 
		//2, 还是判断先前的捉, 判断走后的捉, 如果是多出来的捉,就是捉!!!! 
		//   这儿有个to的问题, 

		//这个比较复杂，要判断是不是常捉不动的子,
		if(testall_TrueCap_noPawnKing(pos,to,from,which)){
			return TRUE;
		}
	}
	//=================================================================================以下判断红方常捉
	else{

		//3, 让开了车，捉其它的子
		//4, 阻挡了对方的保护，捉其它的子
		//a,阻挡了连环马的保护．这个暂时没有出现
		//b,阻挡了连环象的保护．这个暂时没有出现
		//c,阻挡了炮的保护 
		//fen 4kab2/4a4/2n1b4/p1p1c3p/4R4/2P1P4/P5r1P/C3BcN2/5C3/3AKAB2 w - - 0 0
		//这个比较复杂，要判断是不是常捉不动的子,
		for(int ot_pao = PieceListStart(pos,BPAO); ot_pao > 0x32; ot_pao = NextPiece(pos,ot_pao)){	
			//1,**************************************************
			if(StoX(mfrom) == StoX(ot_pao)){			//从炮的File上离开
				if(StoX(mto) != StoX(ot_pao)){					
					//看一下炮的上下信息
					psmv = FileMove(StoY(ot_pao),pos->wBitFiles[StoX(ot_pao)]);
					if(StoY(mfrom) > StoY(ot_pao)){		//在炮的下面
						int sq1 = psmv->RookCap[DLoRight] + StoX(ot_pao);
						if(StoY(mfrom) < StoY(sq1) && IsBlack(pos->b256[sq1]) && testall_TrueCap_noPawnKing(pos,sq1,from,which)){
							return TRUE;
						}
					}
					else{
						int sq1 = psmv->RookCap[DUpLeft] + StoX(ot_pao);
						if(StoY(mfrom) > StoY(sq1) && IsBlack(pos->b256[sq1]) && testall_TrueCap_noPawnKing(pos,sq1,from,which)){
							return TRUE;
						}						
					}
				}										
			}
			//2,**************************************************
			if(StoX(mto) == StoX(ot_pao)){			//走到炮的File上
				if(StoX(mfrom) != StoX(ot_pao)){					
					//看一下炮的上下信息
					psmv = FileMove(StoY(ot_pao),pos->wBitFiles[StoX(ot_pao)]);
					if(StoY(mto) > StoY(ot_pao)){		//在炮的下面
						int sq3 = psmv->SuperCap[DLoRight] + StoX(ot_pao);
						if(StoY(mto) < StoY(sq3) && IsBlack(pos->b256[sq3]) && testall_TrueCap_noPawnKing(pos,sq3,from,which)){
							return TRUE;
						}
					}
					else{
						int sq3 = psmv->SuperCap[DUpLeft] + StoX(ot_pao);
						if(StoY(mto) > StoY(sq3)&& IsBlack(pos->b256[sq3]) && testall_TrueCap_noPawnKing(pos,sq3,from,which)){
							return TRUE;
						}
					}
				}

			}
			//3,**************************************************
			if(StoY(mfrom) == StoY(ot_pao)){			//从炮的Rank上离开
				if(StoY(mto) != StoY(ot_pao)){
					//看一下炮的左右信息
					psmv = RankMove(StoX(ot_pao),pos->wBitRanks[StoY(ot_pao)]);
					if(StoX(mfrom) > StoX(ot_pao)){
						int sq1 = psmv->RookCap[DLoRight] + (ot_pao & 0xf0);
						if(StoX(mfrom) < StoX(sq1)  && IsBlack(pos->b256[sq1]) && testall_TrueCap_noPawnKing(pos,sq1,from,which)){
							return TRUE;
						}						
					}
					else{
						int sq1 = psmv->RookCap[DUpLeft] + (ot_pao & 0xf0);
						if(StoX(mfrom) > StoX(sq1) && IsBlack(pos->b256[sq1]) && testall_TrueCap_noPawnKing(pos,sq1,from,which)){
							return TRUE;
						}						
					}
				}
			}
			//4,**************************************************
			if(StoY(mto) == StoY(ot_pao)){			//走到炮的Rank上
				if(StoY(mfrom) != StoY(ot_pao)){
					//看一下炮的左右信息
					psmv = RankMove(StoX(ot_pao),pos->wBitRanks[StoY(ot_pao)]);
					if(StoX(mto) > StoX(ot_pao)){
						int sq3 = psmv->SuperCap[DLoRight] + (ot_pao & 0xf0);
						if(StoX(mto) < StoX(sq3) && IsBlack(pos->b256[sq3]) && testall_TrueCap_noPawnKing(pos,sq3,from,which)){
							return TRUE;
						}
					}
					else{
						int sq3 = psmv->SuperCap[DUpLeft] + (ot_pao & 0xf0);
						if(StoX(mto) > StoX(sq3) && IsBlack(pos->b256[sq3]) && testall_TrueCap_noPawnKing(pos,sq3,from,which)){
							return TRUE;
						}
					}
				}
			}
		}
		
		//2, 让开了炮，捉其它的子
		//fen 3aknr2/4a4/4b4/p4PN1p/4R4/P1R5P/3r2c2/4C2C1/4A1c2/2B1KAB2 w - - 13 13 
		//让开炮常打相
		//#####################################################################

		//是不是让开了炮常捉        
		for(int at = PieceListStart(pos,RPAO); at > 0x32; at = NextPiece(pos,at)){
			if(at != mto){		//走的不是那个炮							
				//1,**************************************************
				if(StoX(mfrom) == StoX(at)){			//从炮的File上离开
					if(StoX(mto) != StoX(at)){					
						//看一下炮的上下信息
						psmv = FileMove(StoY(at),pos->wBitFiles[StoX(at)]);

						//sq1 = psmv->RookCap[DLoRight] + StoX(at);
						//sq2 = psmv->CannonCap[DLoRight] + StoX(at);
						//sq3 = psmv->SuperCap[DLoRight] + StoX(at);

						if(StoY(mfrom) > StoY(at)){		//在炮的下面
							sq2 = psmv->CannonCap[DLoRight] + StoX(at);
							//if(IsBlackPaoNoRiverPawn(sq2)  && StoY(mfrom) < StoY(sq2) ){	
							if(IsBlack(pos->b256[sq2]) && StoY(mfrom) < StoY(sq2) ){
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
						else{
							sq2 = psmv->CannonCap[DUpLeft] + StoX(at);
							//if(IsBlackPaoNoRiverPawn(sq2)   && StoY(mfrom) > StoY(sq2) ){	
							if(IsBlack(pos->b256[sq2]) && StoY(mfrom) > StoY(sq2) ){
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
					}										
				}
				//2,**************************************************
				if(StoX(mto) == StoX(at)){			//从炮的File上离开 //走到炮的FILE上
					if(StoX(mfrom) != StoX(at)){					
						//看一下炮的上下信息
						psmv = FileMove(StoY(at),pos->wBitFiles[StoX(at)]);

						if(StoY(mto) > StoY(at)){		//在炮的下面
							sq2 = psmv->CannonCap[DLoRight] + StoX(at);
							//if(IsBlackPaoNoRiverPawn(sq2)   && StoY(mto) < StoY(sq2) ){		
							if(IsBlack(pos->b256[sq2]) &&  StoY(mto) < StoY(sq2) ){		
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
						else{
							sq2 = psmv->CannonCap[DUpLeft] + StoX(at);
							//if(IsBlackPaoNoRiverPawn(sq2)  && StoY(mto) > StoY(sq2) ){	
							if(IsBlack(pos->b256[sq2]) && StoY(mto) > StoY(sq2) ){	
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
					}										
				}
				//3, **************************************************
				if(StoY(mfrom) == StoY(at)){			//从炮的Rank上离开
					if(StoY(mto) != StoY(at)){
						//看一下炮的左右信息
						psmv = RankMove(StoX(at),pos->wBitRanks[StoY(at)]);

						if(StoX(mfrom) > StoX(at)){
							sq2 = psmv->CannonCap[DLoRight] + (at & 0xf0);
							//if(IsBlackPaoNoRiverPawn(sq2)   && StoX(mfrom) < StoX(sq2) ){	
							if(IsBlack(pos->b256[sq2]) && StoX(mfrom) < StoX(sq2) ){	
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
						else{
							sq2 = psmv->CannonCap[DUpLeft] + (at & 0xf0);
							//if(IsBlackPaoNoRiverPawn(sq2)   && StoX(mfrom) > StoX(sq2) ){	
							if(IsBlack(pos->b256[sq2]) && StoX(mfrom) > StoX(sq2) ){
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
					}
				}
				//4, **************************************************
				if(StoY(mto) == StoY(at)){			//从炮的Rank上离开
					if(StoY(mfrom) != StoY(at)){
						//看一下炮的左右信息
						psmv = RankMove(StoX(at),pos->wBitRanks[StoY(at)]);

						if(StoX(mto) > StoX(at)){
							sq2 = psmv->CannonCap[DLoRight] + (at & 0xf0);
							//if(IsBlackPaoNoRiverPawn(sq2)   && StoX(mto) < StoX(sq2)){		
							if(IsBlack(pos->b256[sq2]) && StoX(mto) < StoX(sq2)){
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
						else{
							sq2 = psmv->CannonCap[DUpLeft] + (at & 0xf0);
							//if(IsBlackPaoNoRiverPawn(sq2)  && StoX(mto) > StoX(sq2)){	
							if(IsBlack(pos->b256[sq2]) && StoX(mto) > StoX(sq2)){	
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
					}
				}

				//
			}
		}



		//#####################################################################
		//是不是让开了车

		for(int at = PieceListStart(pos,RCHE); at > 0x32; at = NextPiece(pos,at)){
			if(at != mto){		//走的不是那个炮							
				//1,**************************************************
				if(StoX(mfrom) == StoX(at)){			//从车的File上离开
					if(StoX(mto) != StoX(at)){					
						//看一下炮的上下信息
						psmv = FileMove(StoY(at),pos->wBitFiles[StoX(at)]);

						//sq1 = psmv->RookCap[DLoRight] + StoX(at);
						//sq2 = psmv->CannonCap[DLoRight] + StoX(at);
						//sq3 = psmv->SuperCap[DLoRight] + StoX(at);

						if(StoY(mfrom) > StoY(at)){		//在车的下面
							sq2 = psmv->RookCap[DLoRight] + StoX(at);
							if(IsBlack(pos->b256[sq2]) && StoY(mfrom) < StoY(sq2) ){								

								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
						else{
							sq2 = psmv->RookCap[DUpLeft] + StoX(at);
							if(IsBlack(pos->b256[sq2])  && StoY(mfrom) > StoY(sq2) ){								

								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
					}										
				}
				//2,**************************************************
				if(StoX(mto) == StoX(at)){			//从车的File上离开 //走到车的File上
					if(StoX(mfrom) != StoX(at)){					
						//看一下炮的上下信息
						psmv = FileMove(StoY(at),pos->wBitFiles[StoX(at)]);

						if(StoY(mto) > StoY(at)){		//在车的下面
							sq2 = psmv->RookCap[DLoRight] + StoX(at);
							if(IsBlack(pos->b256[sq2])  && StoY(mto) < StoY(sq2) ){							

								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
						else{
							sq2 = psmv->RookCap[DUpLeft] + StoX(at);
							if(IsBlack(pos->b256[sq2]) && StoY(mto) > StoY(sq2) ){							

								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
					}										
				}
				//3, **************************************************
				if(StoY(mfrom) == StoY(at)){			//从车的Rank上离开
					if(StoY(mto) != StoY(at)){
						//看一下炮的左右信息
						psmv = RankMove(StoX(at),pos->wBitRanks[StoY(at)]);

						if(StoX(mfrom) > StoX(at)){
							sq2 = psmv->RookCap[DLoRight] + (at & 0xf0);
							if(IsBlack(pos->b256[sq2])  && StoX(mfrom) < StoX(sq2) ){							

								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
						else{
							sq2 = psmv->RookCap[DUpLeft] + (at & 0xf0);
							if(IsBlack(pos->b256[sq2])  && StoX(mfrom) > StoX(sq2) ){								

								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
					}
				}
				//4, **************************************************
				if(StoY(mto) == StoY(at)){			//从车的Rank上离开
					if(StoY(mfrom) != StoY(at)){
						//看一下车的左右信息
						psmv = RankMove(StoX(at),pos->wBitRanks[StoY(at)]);

						if(StoX(mto) > StoX(at)){
							sq2 = psmv->RookCap[DLoRight] + (at & 0xf0);
							if(IsBlack(pos->b256[sq2])  && StoX(mto) < StoX(sq2)){							

								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
						else{
							sq2 = psmv->RookCap[DUpLeft] + (at & 0xf0);
							if(IsBlack(pos->b256[sq2]) && StoX(mto) > StoX(sq2)){								

								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
					}
				}

				//
			}
		}
		

		//1, 直接捉的是走的棋
		//if(testall_TrueCap_noPawnKing(pos,to,from,which)){
		if(testall_TrueCap_noPawnKing(pos,to,from,which)){
			return TRUE;
		}
	}


	return FALSE;


} 
*/