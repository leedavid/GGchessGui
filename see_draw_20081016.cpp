#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

BOOL see_draw_20081016(position_t *pos,int mfrom,int mto, int from, int to, int which){

	pos->cap_num[0][which] = 0;
	pos->isTrueCap         = false;

	//当前是黑方在走棋
	if(which == WHITE){   //************************************//
		//1,我方的兵,将不要算捉.
		//2,看一下是不是我方的车有捉, 产生黑车的吃子步
        //黑车
        for(int cap = PieceListStart(pos,BCHE); cap > 0x32; cap = NextPiece(pos,cap)){

            //int tmp = MOVE_capFC(cap,RCHE);
            int x   = StoX(cap);
            int y   = StoY(cap);

            //横向吃子步
            int nDisp;
            SlideMoveStruct* psmv;

            nDisp = cap & 0xf0;            

			int becap;

			//如果车不是横向走
			if(StoY(mfrom) != StoY(mto) || mto != cap){
				psmv = RankMove(x,pos->wBitRanks[y]);
				becap = psmv->RookCap[DUpLeft] + nDisp;            
				if(becap != cap){                
					if(IsWhite(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}
				becap = psmv->RookCap[DLoRight] + nDisp;
				if(becap != cap){                
					if(IsWhite(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}
			}

            //纵向吃子步
			//如果车不是纵向走
			if(StoX(mfrom) != StoX(mto) || mto != cap){
				psmv   = FileMove(y,pos->wBitFiles[x]);
				becap = psmv->RookCap[DUpLeft] + x;
				if(becap != cap){                
					if(IsWhite(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}
				becap = psmv->RookCap[DLoRight] + x;
				if(becap != cap){                
					if(IsWhite(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}
			}
         }

		//黑炮
        for(int cap = PieceListStart(pos,BPAO); cap > 0x32; cap = NextPiece(pos,cap)){

            //int tmp = MOVE_capFC(cap,RPAO);
            int x   = StoX(cap);
            int y   = StoY(cap);

            int nDisp;
            SlideMoveStruct* psmv;

            nDisp = cap & 0xf0;
			int becap;

			//fen 1rb1ka3/4a4/2C1b4/p3p3p/9/2p3P2/P3P3P/N3C1N2/1c2A4/1RBAKR1rc b - - 20 20 
			//这个不要中 mto != cap

			//如果炮不是横向走,让开的子也不能横向走哇
			if(StoY(mfrom) != StoY(mto)){
				psmv  = RankMove(x,pos->wBitRanks[y]);
				becap = psmv->CannonCap[DUpLeft] + nDisp;            
				if(becap != cap){                
					if(IsWhite(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}

				becap = psmv->CannonCap[DLoRight] + nDisp;
				if(becap != cap){                
					if(IsWhite(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}
			}

			//如果炮不是纵向走,让开的子也不能纵向走哇
			if(StoX(mfrom) != StoX(mto)){
				//纵向吃子步
				psmv = FileMove(y,pos->wBitFiles[x]);
				becap = psmv->CannonCap[DUpLeft] + x;
				if(becap != cap){                
					if(IsWhite(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}

				becap = psmv->CannonCap[DLoRight] + x;
				if(becap != cap){                
					if(IsWhite(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}
			}
        }


		//黑马
        for(int cap = PieceListStart(pos,BMA); cap > 0x32; cap = NextPiece(pos,cap)){

            //int tmp      = MOVE_capFC(cap,BMA);
            uint8* lpDst = PreMaAndLegMove[cap];
			while(int becap = *lpDst++){ 
				if(pos->b256[*lpDst] == 0){ //马腿没棋子
					if(IsWhite(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}
                lpDst++;
            }
		}
		//黑象的所有走步
		for(int cap = PieceListStart(pos,BXIANG); cap > 0x32; cap = NextPiece(pos,cap)){
			//int      tmp = MOVE_capFC(cap,BXIANG);
			uint8* lpDst = PreShiXiangAndEyeMove[cap];
			while(int becap = *lpDst++){
				if(pos->b256[*lpDst] == 0){    //相眼没棋子
					if(IsWhite(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}
				lpDst++;
			}
		}

		//黑士的所有走步
		for(int cap = PieceListStart(pos,BSHI); cap > 0x32; cap = NextPiece(pos,cap)){
			//int      tmp = MOVE_capFC(cap,BSHI);
			uint8* lpDst = PreShiXiangAndEyeMove[cap];
			while(int becap = *lpDst++){
				if(IsWhite(pos->b256[becap])){
					if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
						test_Is_True_Cap(pos,cap,becap,from,to,which);
					}
				}
			}
		}
	}
	//当前是红方在走棋
	else{		
		 //红车
        for(int cap = PieceListStart(pos,RCHE); cap > 0x32; cap = NextPiece(pos,cap)){

            //int tmp = MOVE_capFC(cap,RCHE);
            int x   = StoX(cap);
            int y   = StoY(cap);

            //横向吃子步
            int nDisp;
            SlideMoveStruct* psmv;
			int becap;
            nDisp = cap & 0xf0;

			//如果不是横向走,让开的子也不能横向走哇
			if(StoY(mfrom) != StoY(mto) || mto != cap){
				psmv = RankMove(x,pos->wBitRanks[y]);
				becap = psmv->RookCap[DUpLeft] + nDisp;            
				if(becap != cap){                
					if(IsBlack(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}
				becap = psmv->RookCap[DLoRight] + nDisp;
				if(becap != cap){                
					if(IsBlack(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}
			}

			//如果不是横向走,让开的子也不能横向走哇
			if(StoX(mfrom) != StoX(mto) || mto != cap){
				//纵向吃子步
				psmv   = FileMove(y,pos->wBitFiles[x]);
				becap = psmv->RookCap[DUpLeft] + x;
				if(becap != cap){                
					if(IsBlack(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}
				becap = psmv->RookCap[DLoRight] + x;
				if(becap != cap){                
					if(IsBlack(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}
			}
         }

		//红炮
        for(int cap = PieceListStart(pos,RPAO); cap > 0x32; cap = NextPiece(pos,cap)){

            //int tmp = MOVE_capFC(cap,RPAO);
            int x   = StoX(cap);
            int y   = StoY(cap);

            int nDisp;
            SlideMoveStruct* psmv;
            nDisp = cap & 0xf0;
            int becap;

			//如果不是横向走,让开的子也不能横向走哇
			if(StoY(mfrom) != StoY(mto)){
				psmv  = RankMove(x,pos->wBitRanks[y]);
				becap = psmv->CannonCap[DUpLeft] + nDisp;            
				if(becap != cap){                
					if(IsBlack(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}

				becap = psmv->CannonCap[DLoRight] + nDisp;
				if(becap != cap){                
					if(IsBlack(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}
			}

			//如果不是横向走,让开的子也不能横向走哇
			if(StoX(mfrom) != StoX(mto)){
				//纵向吃子步
				psmv = FileMove(y,pos->wBitFiles[x]);
				becap = psmv->CannonCap[DUpLeft] + x;
				if(becap != cap){                
					if(IsBlack(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}
				becap = psmv->CannonCap[DLoRight] + x;
				if(becap != cap){                
					if(IsBlack(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}
			}
        }


		//红马
        for(int cap = PieceListStart(pos,RMA); cap > 0x32; cap = NextPiece(pos,cap)){

            //int tmp      = MOVE_capFC(cap,RMA);
            uint8* lpDst = PreMaAndLegMove[cap];
			while(int becap = *lpDst++){ 
				if(pos->b256[*lpDst] == 0){ //马腿没棋子
					if(IsBlack(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}
                lpDst++;
            }
		}
		 //红相的所有走步
		for(int cap = PieceListStart(pos,RXIANG); cap > 0x32; cap = NextPiece(pos,cap)){
			//int      tmp = MOVE_capFC(cap,RXIANG);
			uint8* lpDst = PreShiXiangAndEyeMove[cap];
			while(int becap = *lpDst++){
				if(pos->b256[*lpDst] == 0){    //相眼没棋子
					if(IsBlack(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}
				lpDst++;
			}
		}

		//红士的所有走步
		for(int cap = PieceListStart(pos,RSHI); cap > 0x32; cap = NextPiece(pos,cap)){
			//int      tmp = MOVE_capFC(cap,RSHI);
			uint8* lpDst = PreShiXiangAndEyeMove[cap];
			while(int becap = *lpDst++){
				if(IsBlack(pos->b256[becap])){
					if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
						test_Is_True_Cap(pos,cap,becap,from,to,which);
					}
				}
			}
		}	
	}

	//所有的捉有列表了, 与上次的所有的捉比对一下, 如果有对同一个ID的,就是捉.
	//这个有二个常捉在, 要二次判断那个捉, 所以这个最复杂.
	//fen 3a1kb2/2r6/4ba3/p6Np/9/P3p1RcP/9/4B4/4A4/2BK1A3 b - - 53 53 
	//fen r2akab2/1c7/2n1b1c2/p1R1p3p/5nr2/9/P3P2NP/1CN1C4/5R3/2BAKAB2 b - - 16 16 

    int this_num = pos->cap_num[0][which];

	while(this_num > 0){  //本次有捉
		this_num --;
		int n_to_id			= pos->LastCapChess		 [this_num][0][which];	
		int n_last_to		= pos->last_to           [this_num][0][which];
		int last_num   = pos->cap_num[1][which];

		if(last_num == 0){
			pos->isTrueCap = true;
		}
		else{
			while(last_num > 0){
				last_num --;
				//int last_id      = pos->LastCapChess		[last_num][1][which];
				if(pos->LastCapChess[last_num][1][which] == n_to_id){
					//fen 3a5/9/4k4/3N1n3/9/3C2B2/3c5/4B4/2C1A4/4K4 w - - 13 13 
					if(pos->last_to[last_num][1][which] == n_last_to){
						pos->isTrueCap = true;  //这个一般是让开炮的捉
					}
					if(pos->last_ot_from[last_num][1][which] == n_last_to){
						pos->isTrueCap = true;						  
					}
				}
			}
		}
	}	

	for(int i = 0;  i < pos->cap_num[0][which]; i++){
		pos->LastCapChess[i][1][which]	= pos->LastCapChess[i][0][which];

		pos->last_ot_from[i][1][which]  = pos->last_ot_from[i][0][which];
		//pos->last_ot_to[i][1][which]    = pos->last_ot_to[i][0][which];

		pos->last_to     [i][1][which]  = pos->last_to     [i][0][which];
	}

	pos->cap_num[1][which] = pos->cap_num[0][which]; 

	return pos->isTrueCap;
}



//enum  {
//       EMPTY=0,
//       RKING=1,  RSHI=2,RXIANG=3, RMA=4, RCHE=5, RPAO=6, RPAWN=7,
//       BKING=8,  BSHI=9,BXIANG=10,BMA=11,BCHE=12,BPAO=13,BPAWN=14,
//       EMPTY16=16, OUTSIDE=32};