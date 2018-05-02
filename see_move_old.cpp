#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

//goto nextStep 时还要看一下是不是那个不能走哇




//通过SEE来判断连捉
//BOOL see_draw_old(position_t *pos,int mfrom,int mto, int to){
//
//    //return 0;
//
//    //int num_of_attackers[2];
//    //int swaplist[32];
//    //int attackers[2][16];
//    //int piece;
//    //int capture;
//    //int side;
//    //int piece_val;
//    //int val;
//    //int n;
//
//	int tochess = pos->b256[to];  //得到tochess;
//
//	//BOOL Ispao    = FALSE;          //炮能吃到
//	//int  paoToSq  = 0;
//
//	if(tochess == EMPTY){
//		return FALSE;
//	}
//
//	int side;
//
//	if(IsWhite(tochess)){
//		side = BLACK;			//得到那个在SEE
//	}
//	else {
//		side = WHITE;
//	}
//
//	//第一步，得到可吃to的棋子，但要是走子方的
//
//    register int tmp;
//
//    // Find attackers for both sides.  The capturing piece is not added 
//    // to the attack list.  Instead, we scan for X-ray attacks behind the
//    // capturing piece.
//
//    int tox = StoX(to);
//    int toy = StoY(to);
//
//    int tof = pos->wBitFiles[tox];
//    int tor = pos->wBitRanks[toy];     
//
//    int nDisp = to & 0xf0;
//
//    //num_of_attackers[WHITE] = num_of_attackers[BLACK] = 0;
//
//	//int whiteAttacker = 0;
//	//int blackAttacker = 0; 
//
//	int attacker = 0;
//    SlideMoveStruct *psmv;
//
//    //得to的到上下的信息
//
//
//	int NotList[16];
//	int NotBoard[16];               //棋盘上的棋子也得去了哇
//    int NotNum          =0;         //不可能走的棋子的数量 
//
//	//**************************************************************************
//	// 得到攻击者的棋子
//	//**************************************************************************
//
//	if(side == BLACK){
//
//		//////////////////////////////////////////////////////////////////////////////
//		// 将黑方不可走棋去了
//		int king  = PieceListStart(pos,BKING);
//	    int kx    = StoX(king);
//		int ky    = StoY(king);
//		int ky4   = king & 0xf0;
//
//		int sq1;
//		int sq2;
//		int sq3;
//
//		psmv = FileMove(ky,pos->wBitFiles[kx]);
//
//		//得到将的上下信息
//		sq2 = psmv->CannonCap[DUpLeft] + kx;
//	
//		if(sq2 != king){
//			if(pos->b256[sq2] == RCHE){
//				sq1 = psmv->RookCap[DUpLeft] + kx;
//
//				if(IsBlack(pos->b256[sq1])){
//					//Not256Pos[NotNum] = sq1;
//
//					//------------------------------------
//					NotList[NotNum]  = sq1;
//					NotBoard[NotNum] = pos->b256[sq1];  //保存一下棋子
//					pos->b256[sq1]   = EMPTY;
//                    //-------------------------------------
//					RemovePiece(pos,sq1);
//					NotNum++;
//				}				
//			}
//		}
//        ///////////////////////////////////////////////////////////////////
//		//得到将下面第一个棋子
//		sq1 = psmv->RookCap[DLoRight] + kx;
//		
//		if(sq1 != king){
//			
//			sq2 = psmv->CannonCap[DLoRight] + kx;
//
//			if(sq2 != king){
//
//				int chess1 = pos->b256[sq1];
//				int chess2 = pos->b256[sq2];
//
//				if(chess2 == RCHE || chess2 == RKING){
//					if(IsBlack(chess1)){
//						//Not256Pos[NotNum] = sq1;
//
//						//------------------------------------
//						NotList[NotNum]  = sq1;
//						NotBoard[NotNum] = pos->b256[sq1];  //保存一下棋子
//						pos->b256[sq1]   = EMPTY;
//						//-------------------------------------
//
//						RemovePiece(pos,sq1);
//						NotNum++;
//					}
//				}
//
//				sq3 = psmv->SuperCap[DLoRight] + kx;
//				if(sq3 != king){
//					int chess3 = pos->b256[sq3];
//					if(chess3 == RPAO && sq3 != to){  //if(chess3 == RPAO){
//						if(IsBlack(chess2)){   //这儿还得判断一下ToChess 是不是炮
//							//if(tochess
//							//Not256Pos[NotNum] = sq2;
//
//							//------------------------------------
//							NotList[NotNum]  = sq2;
//							NotBoard[NotNum] = pos->b256[sq2];  //保存一下棋子
//							pos->b256[sq2]   = EMPTY;
//							//-------------------------------------
//
//							RemovePiece(pos,sq2);
//							NotNum++;
//						}
//						if(IsBlack(chess1) && chess2 != RCHE && chess2 != RKING){
//							//Not256Pos[NotNum] = sq1;
//							
//							//------------------------------------
//							NotList[NotNum]  = sq1;
//							NotBoard[NotNum] = pos->b256[sq1];  //保存一下棋子
//							pos->b256[sq1]   = EMPTY;
//							//-------------------------------------
//
//							RemovePiece(pos,sq1);
//							NotNum++;
//						}
//					}
//				}
//			}
//		}
//
//		//向左判断一下
//		psmv = RankMove(kx,pos->wBitRanks[ky]);
//
//		sq1 = psmv->RookCap[DUpLeft] + ky4;
//		if(sq1 != king){
//			
//			sq2 = psmv->CannonCap[DUpLeft] + ky4;
//
//			if(sq2 != king){
//				int chess1 = pos->b256[sq1];
//				int chess2 = pos->b256[sq2];
//				
//				if(chess2 == RCHE){
//					if(IsBlack(chess1)){
//						//Not256Pos[NotNum] = sq1;
//						//------------------------------------
//						NotList[NotNum]  = sq1;
//						NotBoard[NotNum] = pos->b256[sq1];  //保存一下棋子
//						pos->b256[sq1]   = EMPTY;
//						//-------------------------------------
//						RemovePiece(pos,sq1);
//						NotNum++;
//					}
//				}
//
//				sq3 = psmv->SuperCap[DUpLeft] + ky4;
//				if(sq3 != king){
//					int chess3 = pos->b256[sq3];
//					//if(chess3 == RPAO){
//					if(chess3 == RPAO && sq3 != to){  //if(chess3 == RPAO){
//						if(IsBlack(chess2)){
//							//Not256Pos[NotNum] = sq2;
//							//------------------------------------
//							NotList[NotNum]  = sq2;
//							NotBoard[NotNum] = pos->b256[sq2];  //保存一下棋子
//							pos->b256[sq2]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq2);
//							NotNum++;
//						}
//						if(IsBlack(chess1) && chess2 != RCHE ){
//							//Not256Pos[NotNum] = sq1;
//							//------------------------------------
//							NotList[NotNum]  = sq1;
//							NotBoard[NotNum] = pos->b256[sq1];  //保存一下棋子
//							pos->b256[sq1]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq1);
//							NotNum++;
//						}
//					}
//				}
//			}		
//		}
//
//		//向右判断一下
//
//		psmv = RankMove(kx,pos->wBitRanks[ky]);
//
//		sq1 = psmv->RookCap[DLoRight] + ky4;
//		if(sq1 != king){
//			
//			sq2 = psmv->CannonCap[DLoRight] + ky4;
//
//			if(sq2 != king){
//				int chess1 = pos->b256[sq1];
//				int chess2 = pos->b256[sq2];
//				
//				if(chess2 == RCHE){
//					if(IsBlack(chess1)){
//						//Not256Pos[NotNum] = sq1;
//						//------------------------------------
//						NotList[NotNum]  = sq1;
//						NotBoard[NotNum] = pos->b256[sq1];  //保存一下棋子
//						pos->b256[sq1]   = EMPTY;
//						//-------------------------------------
//						RemovePiece(pos,sq1);
//						NotNum++;
//					}
//				}
//
//				sq3 = psmv->SuperCap[DLoRight] + ky4;
//				if(sq3 != king){
//					int chess3 = pos->b256[sq3];
//					//if(chess3 == RPAO){
//					if(chess3 == RPAO && sq3 != to){  //if(chess3 == RPAO){
//						if(IsBlack(chess2)){
//							//Not256Pos[NotNum] = sq2;
//							//------------------------------------
//							NotList[NotNum]  = sq2;
//							NotBoard[NotNum] = pos->b256[sq2];  //保存一下棋子
//							pos->b256[sq2]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq2);
//							NotNum++;
//						}
//						if(IsBlack(chess1) && chess2 != RCHE ){
//							//Not256Pos[NotNum] = sq1;
//							//------------------------------------
//							NotList[NotNum]  = sq1;
//							NotBoard[NotNum] = pos->b256[sq1];  //保存一下棋子
//							pos->b256[sq1]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq1);
//							NotNum++;
//						}
//					}
//				}
//			}		
//		}
//
//		//*********************************************************
//		//再看一下马
//		 //判断一下有没有马在将军哇
//        for(int checkSq256 = PieceListStart(pos,RMA); checkSq256 > 0x32; checkSq256 = NextPiece(pos,checkSq256)){
//
//			//还得看一下走的是不是那个马, 如果是马,就不要判断
//
//			if(checkSq256 != to){
//
//				int x   = horseLegTab(king - checkSq256 + 256);
//				int leg256 = checkSq256 + x;
//
//				if(x){
//					int leg14 = pos->b256[leg256];
//
//					if(IsBlack(leg14)){
//						//得判断一下,是不是已经拿走了
//						BOOL isRemove = FALSE;
//						for(int i = 0; i < NotNum; i++){
//							if(leg256 == NotList[i]){
//								isRemove = TRUE;
//								break;
//							}
//						}
//						//Not48Pos[NotNum]        = leg48;
//						if(isRemove == FALSE){
//							//Not256Pos[NotNum]       = leg256;
//
//							//------------------------------------
//							NotList[NotNum]  = leg256;
//							NotBoard[NotNum] = pos->b256[leg256];  //保存一下棋子
//							pos->b256[leg256]   = EMPTY;
//							//-------------------------------------
//
//							RemovePiece(pos, leg256);
//							NotNum++;
//						}
//					}
//				}
//			}
//		}
//		//**********************************************************
//
//        // 将黑方不可走棋去了 End
//		//////////////////////////////////////////////////////////////////////////////
//
//		//黑仕
//		if(inBoard(to) & IN_BSHI){
//			for(int at = PieceListStart(pos,BSHI); at > 0x32; at = NextPiece(pos,at)){
//				//if(at != from && (GetDir(at,to) & DirShi)){
//				if((GetDir(at,to) & DirShi)){
//					attacker = at;
//				    goto NextStep;
//				}
//			}
//		}
//		//黑象
//		if(inBoard(to) & IN_BXIANG){
//			for(int at = PieceListStart(pos,BXIANG); at > 0x32; at = NextPiece(pos,at)){
//				/*if(at != from && (GetDir(at,to) & DirXiang) && pos->b256[(at+to)/2] == EMPTY){*/
//				if((GetDir(at,to) & DirXiang) && pos->b256[(at+to)/2] == EMPTY){
//					attacker = at;
//				    goto NextStep;
//				}
//			}
//		}
//
//		//黑马
//		for(int at = PieceListStart(pos,BMA); at > 0x32; at = NextPiece(pos,at)){
//			//if(at != from){
//			int m = horseLegTab(to-at+256);
//			if(m && !pos->b256[at+m]){
//				attacker = at;
//			    goto NextStep;
//			}
//			//}
//		}
//
//		psmv = FileMove(toy,tof);
//		//得到上面第一个
//		tmp = psmv->RookCap[DUpLeft] + tox;
//		if(tmp != to){ 
//
//			switch(pos->b256[tmp]){
//				case BCHE:  //黑车
//					attacker = tmp;
//					goto NextStep;
//					break;			
//				case BKING: //黑将
//					if(tmp+16 == to && toy < 0x6){
//						attacker = tmp;
//						goto NextStep;
//					}
//					break;
//				case BPAWN: //黑卒
//					if(tmp+16 == to){
//						attacker = tmp;
//						goto NextStep;
//					}
//					break;
//				default:
//					break;
//			}
//
//			//有了第一个才有第二个棋子
//			tmp = psmv->CannonCap[DUpLeft] + tox;
//			if(tmp != to){
//				int c14 = pos->b256[tmp];
//				if(c14 == BPAO){
//					attacker = tmp;
//					goto NextStep;
//				}
//			}
//		}
//		//得到to的下面第一个的棋子
//		tmp = psmv->RookCap[DLoRight] + tox;
//		if(tmp != to){   
//
//			switch(pos->b256[tmp]){			
//				case BCHE:
//					attacker = tmp;
//					goto NextStep;
//					break;
//				case BKING:
//					if(tmp-16 == to && toy < 0x6){
//						attacker = tmp;
//						goto NextStep;
//					}	
//					break;
//				default:
//					break;
//			} 
//
//			//有了第一个才有第二个棋子
//			tmp = psmv->CannonCap[DLoRight] + tox;
//			if(tmp != to ){
//				int c14 = pos->b256[tmp];
//				if(c14 == BPAO){
//					attacker = tmp;
//					goto NextStep;
//				}
//			}
//		}
//		//得到to的左右的信息
//		//psmv = smvRankMoveTab[tox-3] + tor; 
//
//		psmv = RankMove(tox,tor);
//		//得到to左面的第一个棋子
//		tmp = psmv->RookCap[DUpLeft] + nDisp;
//		if(tmp != to){ 
//
//			switch(pos->b256[tmp]){
//				 case BCHE:
//					attacker = tmp;
//					goto NextStep;
//					 break;		
//					
//				 case BKING:
//					 if((inBoard(to) & IN_BKING) && tmp+1 == to){
//						 attacker = tmp;
//						 goto NextStep;
//					 }
//					 break;				
//				 case BPAWN:
//					 if(toy > 0x7 && tmp+1 == to){
//						 attacker = tmp;
//						 goto NextStep;
//					 }
//					 break;
//				 default:
//					 break;                
//			}  
//
//			//有了第一个棋,才有第二个棋
//			tmp = psmv->CannonCap[DUpLeft] + nDisp;
//			if(tmp != to){
//				int c14 = pos->b256[tmp];
//				if(c14 == BPAO){
//					attacker = tmp;
//				    goto NextStep;
//				}
//			}
//		}
//		//得到to右面的第一个棋子
//		tmp = psmv->RookCap[DLoRight] + nDisp;
//		if(tmp != to){
//
//			switch(pos->b256[tmp]){				
//				case BCHE:
//					attacker = tmp;
//				    goto NextStep;
//					break;				
//				case BKING:
//					if((inBoard(to) & IN_BKING) && tmp-1 == to){
//						attacker = tmp;
//						goto NextStep;
//					}
//					break;			
//				case BPAWN:
//					if(toy > 0x7 && tmp-1 == to){
//						attacker = tmp;
//				        goto NextStep;
//					}
//					break;
//				default:
//					break;
//			}
//
//			//有了第一个棋,才有第二个棋
//			tmp = psmv->CannonCap[DLoRight] + nDisp;
//			if(tmp != to ){
//				int c14 = pos->b256[tmp];
//				if(c14 == BPAO){
//					attacker = tmp;
//				    goto NextStep;
//				}            
//			}
//		}
//
//
//
//
//        //***************************************
//		//这个走的棋,得在吃的子与炮架的中间
//		/////////////////////////////////////////////////////////////////////////////////////////////////
//		//再在这儿看一下, 是不是走到炮架,或去了炮架, 形成新的捉
//		for(int at = PieceListStart(pos,BPAO); at > 0x32; at = NextPiece(pos,at)){
//			if(at != mto){		//走的不是那个炮							
//				//1,**************************************************
//				if(StoX(mfrom) == StoX(at)){			//从炮的File上离开
//					if(StoX(mto) != StoX(at)){					
//						//看一下炮的上下信息
//						psmv = FileMove(StoY(at),pos->wBitFiles[StoX(at)]);
//
//						if(StoY(mfrom) > StoY(at)){		//在炮的下面
//							sq2 = psmv->CannonCap[DLoRight] + StoX(at);
//							if(IsWhite(pos->b256[sq2]) && StoY(mfrom) < StoY(sq2) ){   //走的棋在sq2 与 at 的中间
//								//paoTo				= TRUE;
//								attacker			= at;
//
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy]; 
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//						else{
//							sq2 = psmv->CannonCap[DUpLeft] + StoX(at);
//							if(IsWhite(pos->b256[sq2]) && StoY(mfrom) > StoY(sq2) ){
//								//paoTo				= TRUE;								
//								attacker			= at;
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy];  
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//					}										
//				}
//				//2,**************************************************
//				if(StoX(mto) == StoX(at)){			//从炮的File上离开
//					if(StoX(mfrom) != StoX(at)){					
//						//看一下炮的上下信息
//						psmv = FileMove(StoY(at),pos->wBitFiles[StoX(at)]);
//
//						if(StoY(mto) > StoY(at)){		//在炮的下面
//							sq2 = psmv->CannonCap[DLoRight] + StoX(at);
//							if(IsWhite(pos->b256[sq2]) && StoY(mto) < StoY(sq2) ){
//								//paoTo				= TRUE;
//								attacker			= at;
//
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy]; 
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//						else{
//							sq2 = psmv->CannonCap[DUpLeft] + StoX(at);
//							if(IsWhite(pos->b256[sq2]) && StoY(mto) > StoY(sq2) ){
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy]; 
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//					}
//										
//				}
//				//3,**************************************************
//				if(StoY(mfrom) == StoY(at)){			//从炮的Rank上离开
//					if(StoY(mto) != StoY(at)){
//						//看一下炮的左右信息
//						psmv = RankMove(StoX(at),pos->wBitRanks[StoY(at)]);
//
//						if(StoX(mfrom) > StoX(at)){
//							sq2 = psmv->CannonCap[DLoRight] + (at & 0xf0);
//							if(IsWhite(pos->b256[sq2]) && StoX(mfrom) < StoX(sq2) ){
//								//paoTo				= TRUE;								
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy];  
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//						else{
//							sq2 = psmv->CannonCap[DUpLeft] + (at & 0xf0);
//							if(IsWhite(pos->b256[sq2]) && StoX(mfrom) > StoX(sq2) ){
//								//paoTo				= TRUE;						
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy]; 
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//					}
//				}
//				//4,**************************************************
//				if(StoY(mto) == StoY(at)){			//从炮的Rank上离开
//					if(StoY(mfrom) != StoY(at)){
//						//看一下炮的左右信息
//						psmv = RankMove(StoX(at),pos->wBitRanks[StoY(at)]);
//
//						if(StoX(mto) > StoX(at)){
//							sq2 = psmv->CannonCap[DLoRight] + (at & 0xf0);
//							if(IsWhite(pos->b256[sq2]) && StoX(mto) < StoX(sq2) ){
//								//paoTo				= TRUE;						
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy];
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//						else{
//							sq2 = psmv->CannonCap[DUpLeft] + (at & 0xf0);
//							if(IsWhite(pos->b256[sq2]) && StoX(mto) > StoX(sq2)){
//								//paoTo				= TRUE;
//								
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy];  
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//					}
//				}
//
//				//
//			}
//		}
//		//////////////////////////////////////////////////////////////////////////////////////////////////
//
//	}
//	//************************************************************************** 看红棋能不能吃
//	else{
//
//
//		//////////////////////////////////////////////////////////////////////////////
//		// 将红方不可走棋去了
//		int king  = PieceListStart(pos,RKING);
//	    int kx    = StoX(king);
//		int ky    = StoY(king);
//		int ky4   = king & 0xf0;
//
//		int sq1;
//		int sq2;
//		int sq3;
//
//		psmv = FileMove(ky,pos->wBitFiles[kx]);
//
//		//得到将下面第二个棋子
//		sq2 = psmv->CannonCap[DLoRight] + kx;
//	
//		if(sq2 != king){
//			if(pos->b256[sq2] == BCHE){
//				sq1 = psmv->RookCap[DLoRight] + kx;
//
//				if(IsWhite(pos->b256[sq1])){
//					//Not256Pos[NotNum] = sq1;
//					//------------------------------------
//					NotList[NotNum]  = sq1;
//					NotBoard[NotNum] = pos->b256[sq1];  //保存一下棋子
//					pos->b256[sq1]   = EMPTY;
//					//-------------------------------------
//					RemovePiece(pos,sq1);
//					NotNum++;
//				}				
//			}
//		}
//
//		//得到将上面第一个棋子
//		sq1 = psmv->RookCap[DUpLeft] + kx;
//		
//		if(sq1 != king){
//			
//			sq2 = psmv->CannonCap[DUpLeft] + kx;
//
//			if(sq2 != king){
//
//				int chess1 = pos->b256[sq1];
//				int chess2 = pos->b256[sq2];
//
//				if(chess2 == BCHE || chess2 == BKING){
//					if(IsWhite(chess1)){
//						//Not256Pos[NotNum] = sq1;
//						//------------------------------------
//						NotList[NotNum]  = sq1;
//						NotBoard[NotNum] = pos->b256[sq1];  //保存一下棋子
//						pos->b256[sq1]   = EMPTY;
//						//-------------------------------------
//						RemovePiece(pos,sq1);
//						NotNum++;
//					}
//				}
//
//				sq3 = psmv->SuperCap[DUpLeft] + kx;
//				if(sq3 != king){
//					int chess3 = pos->b256[sq3];
//					//if(chess3 == BPAO){
//					if(chess3 == BPAO && sq3 != to){  //if(chess3 == BPAO){
//						if(IsWhite(chess2)){
//							//Not256Pos[NotNum] = sq2;
//							//------------------------------------
//							NotList[NotNum]  = sq2;
//							NotBoard[NotNum] = pos->b256[sq2];  //保存一下棋子
//							pos->b256[sq2]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq2);
//							NotNum++;
//						}
//						if(IsWhite(chess1) && chess2 != BCHE && chess2 != BKING){
//							//Not256Pos[NotNum] = sq1;
//							//------------------------------------
//							NotList[NotNum]  = sq1;
//							NotBoard[NotNum] = pos->b256[sq1];  //保存一下棋子
//							pos->b256[sq1]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq1);
//							NotNum++;
//						}
//					}
//				}
//			}
//		}
//
//		//向左判断一下
//		psmv = RankMove(kx,pos->wBitRanks[ky]);
//
//		sq1 = psmv->RookCap[DUpLeft] + ky4;
//		if(sq1 != king){
//			
//			sq2 = psmv->CannonCap[DUpLeft] + ky4;
//
//			if(sq2 != king){
//				int chess1 = pos->b256[sq1];
//				int chess2 = pos->b256[sq2];
//				
//				if(chess2 == BCHE){
//					if(IsWhite(chess1)){
//						//Not256Pos[NotNum] = sq1;
//						//------------------------------------
//						NotList[NotNum]  = sq1;
//						NotBoard[NotNum] = pos->b256[sq1];  //保存一下棋子
//						pos->b256[sq1]   = EMPTY;
//						//-------------------------------------
//						RemovePiece(pos,sq1);
//						NotNum++;
//					}
//				}
//
//				sq3 = psmv->SuperCap[DUpLeft] + ky4;
//				if(sq3 != king){
//					int chess3 = pos->b256[sq3];
//					//if(chess3 == BPAO){
//					if(chess3 == BPAO && sq3 != to){  //if(chess3 == BPAO){
//						if(IsWhite(chess2)){
//							//Not256Pos[NotNum] = sq2;
//							//------------------------------------
//							NotList[NotNum]  = sq2;
//							NotBoard[NotNum] = pos->b256[sq2];  //保存一下棋子
//							pos->b256[sq2]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq2);
//							NotNum++;
//						}
//						if(IsWhite(chess1) && chess2 != BCHE ){
//							//Not256Pos[NotNum] = sq1;
//							//------------------------------------
//							NotList[NotNum]  = sq1;
//							NotBoard[NotNum] = pos->b256[sq1];  //保存一下棋子
//							pos->b256[sq1]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq1);
//							NotNum++;
//						}
//					}
//				}
//			}		
//		}
//
//		//向右判断一下
//
//		psmv = RankMove(kx,pos->wBitRanks[ky]);
//
//		sq1 = psmv->RookCap[DLoRight] + ky4;
//		if(sq1 != king){
//			
//			sq2 = psmv->CannonCap[DLoRight] + ky4;
//
//			if(sq2 != king){
//				int chess1 = pos->b256[sq1];
//				int chess2 = pos->b256[sq2];
//				
//				if(chess2 == BCHE){
//					if(IsWhite(chess1)){
//						//Not256Pos[NotNum] = sq1;
//						//------------------------------------
//						NotList[NotNum]  = sq1;
//						NotBoard[NotNum] = pos->b256[sq1];  //保存一下棋子
//						pos->b256[sq1]   = EMPTY;
//						//-------------------------------------
//						RemovePiece(pos,sq1);
//						NotNum++;
//					}
//				}
//
//				sq3 = psmv->SuperCap[DLoRight] + ky4;
//				if(sq3 != king){
//					int chess3 = pos->b256[sq3];
//					//if(chess3 == BPAO){
//					if(chess3 == BPAO && sq3 != to){  //if(chess3 == BPAO){
//						if(IsWhite(chess2)){
//							//Not256Pos[NotNum] = sq2;
//							//------------------------------------
//							NotList[NotNum]  = sq2;
//							NotBoard[NotNum] = pos->b256[sq2];  //保存一下棋子
//							pos->b256[sq2]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq2);
//							NotNum++;
//						}
//						if(IsWhite(chess1) && chess2 != BCHE ){
//							//Not256Pos[NotNum] = sq1;
//							//------------------------------------
//							NotList[NotNum]  = sq1;
//							NotBoard[NotNum] = pos->b256[sq1];  //保存一下棋子
//							pos->b256[sq1]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq1);
//							NotNum++;
//						}
//					}
//				}
//			}		
//		}
//
//		//再看一下马
//		 //判断一下有没有马在将军哇
//        for(int checkSq256 = PieceListStart(pos,BMA); checkSq256 > 0x32; checkSq256 = NextPiece(pos,checkSq256)){
//
//			if(checkSq256 != to){
//
//				int x   = horseLegTab(king - checkSq256 + 256);
//				int leg256 = checkSq256 + x;
//
//				if(x){
//					int leg14 = pos->b256[leg256];
//
//					if(IsWhite(leg14)){
//						//得判断一下,是不是已经拿走了
//						BOOL isRemove = FALSE;
//						for(int i = 0; i < NotNum; i++){
//							if(leg256 == NotList[i]){
//								isRemove = TRUE;
//								break;
//							}
//						}
//						//Not48Pos[NotNum]        = leg48;
//						if(isRemove == FALSE){
//							//Not256Pos[NotNum]       = leg256;
//							//------------------------------------
//							NotList[NotNum]  = leg256;
//							NotBoard[NotNum] = pos->b256[leg256];  //保存一下棋子
//							pos->b256[leg256]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos, leg256);
//							NotNum++;
//						}
//					}
//				}
//			}
//		}
//
//        // 将红方不可走棋去了 End
//		//////////////////////////////////////////////////////////////////////////////
//		
//		//红仕  //要先判断小子能不能吃哇
//		if(inBoard(to) & IN_RSHI){
//			for(int at = PieceListStart(pos,RSHI); at > 0x32; at = NextPiece(pos,at)){
//				//if(at != from && shortDir(at-to+256) == 1){
//				/*if(at != from && (GetDir(at,to) & DirShi)){*/
//				if((GetDir(at,to) & DirShi)){
//					attacker = at;
//					goto NextStep;
//				}
//			}
//		}
//		//红相
//		if(inBoard(to) & IN_RXIANG){
//			for(int at = PieceListStart(pos,RXIANG); at > 0x32; at = NextPiece(pos,at)){
//				/*if(at != from && (GetDir(at,to) & DirXiang) && pos->b256[(at+to)/2] == EMPTY){*/
//				if((GetDir(at,to) & DirXiang) && pos->b256[(at+to)/2] == EMPTY){
//					attacker = at;
//					goto NextStep;
//				}
//			}
//		}
//
//
//		//红马
//		for(int at = PieceListStart(pos,RMA); at > 0x32; at = NextPiece(pos,at)){
//			//if(at != from){
//			int m = horseLegTab(to-at+256);
//			if(m && !pos->b256[at+m]){
//				attacker = at;
//				goto NextStep;
//			}
//			//}
//		}
//        //////////////////////////////////////////////////////////////////////////////////////////
//
//
//		psmv = FileMove(toy,tof);
//		//得到上面第一个
//		tmp = psmv->RookCap[DUpLeft] + tox;
//		if(tmp != to){ 
//
//			switch(pos->b256[tmp]){
//				case RCHE:  //红车
//					attacker = tmp;
//					goto NextStep;
//					break;
//				case RKING: //红帅
//					if(tmp+16 == to && toy > 0x9){
//						attacker = tmp;
//						goto NextStep;
//					}
//					break;				
//				default:
//					break;
//			}
//
//			//有了第一个才有第二个棋子
//			tmp = psmv->CannonCap[DUpLeft] + tox;
//			if(tmp != to){
//				int c14 = pos->b256[tmp];
//				if(c14 == RPAO){
//					attacker = tmp;
//					goto NextStep;
//				}				
//			}
//		}
//		//得到to的下面第一个的棋子
//		tmp = psmv->RookCap[DLoRight] + tox;
//		if(tmp != to){   
//
//			switch(pos->b256[tmp]){
//				case RCHE:
//					attacker = tmp;
//					goto NextStep;
//					break;
//				
//				case RKING:
//					if(tmp-16 == to && toy > 0x9){
//						attacker = tmp;
//						goto NextStep;
//					}
//					break;
//				
//				case RPAWN:
//					if(tmp-16 == to){
//						attacker = tmp;
//					    goto NextStep;
//					}
//					break;
//
//				default:
//					break;
//			} 
//
//			//有了第一个才有第二个棋子
//			tmp = psmv->CannonCap[DLoRight] + tox;
//			if(tmp != to ){
//				int c14 = pos->b256[tmp];
//				if(c14 == RPAO){
//					attacker = tmp;
//					goto NextStep;
//				}				
//			}
//		}
//		//得到to的左右的信息
//		//psmv = smvRankMoveTab[tox-3] + tor; 
//
//		psmv = RankMove(tox,tor);
//		//得到to左面的第一个棋子
//		tmp = psmv->RookCap[DUpLeft] + nDisp;
//		if(tmp != to){ 
//
//			switch(pos->b256[tmp]){
//				 case RCHE:
//					 attacker = tmp;
//					 goto NextStep;
//					 break;
//				
//				 case RKING:
//					 if((inBoard(to) & IN_RKING) && tmp+1 == to){
//						 attacker = tmp;
//						 goto NextStep;
//					 }
//					 break;
//				 
//				 case RPAWN:
//					 if(toy < 0x8 && tmp+1 == to){
//						 attacker = tmp;
//						 goto NextStep;
//					 }
//					 break;
//
//				 default:
//					 break;                
//			}  
//
//			//有了第一个棋,才有第二个棋
//			tmp = psmv->CannonCap[DUpLeft] + nDisp;
//			if(tmp != to){
//				int c14 = pos->b256[tmp];
//				if(c14 == RPAO){
//					attacker = tmp;
//					goto NextStep;
//				}			
//			}
//		}
//		//得到to右面的第一个棋子
//		tmp = psmv->RookCap[DLoRight] + nDisp;
//		if(tmp != to){
//
//			switch(pos->b256[tmp]){
//				case RCHE:
//					attacker = tmp;
//					goto NextStep;
//					break;
//				
//				case RKING:
//					if((inBoard(to) & IN_RKING) && tmp-1 == to){
//						attacker = tmp;
//					    goto NextStep;
//					}
//					break;
//				
//				case RPAWN:
//					if(toy < 0x8 && tmp-1 == to){
//						attacker = tmp;
//					    goto NextStep;
//					}
//					break;
//
//				default:
//					break;
//			}
//
//			//有了第一个棋,才有第二个棋
//			tmp = psmv->CannonCap[DLoRight] + nDisp;
//			if(tmp != to ){
//				int c14 = pos->b256[tmp];
//				if(c14 == RPAO){
//					attacker = tmp;
//					goto NextStep;
//				}				           
//			}
//		}
//
//	
//
//		/////////////////////////////////////////////////////////////////////////////////////////////////
//		//再在这儿看一下, 是不是走到炮架,或去了炮架, 形成新的捉
//		for(int at = PieceListStart(pos,RPAO); at > 0x32; at = NextPiece(pos,at)){
//			if(at != mto){		//走的不是那个炮							
//				//1,**************************************************
//				if(StoX(mfrom) == StoX(at)){			//从炮的File上离开
//					if(StoX(mto) != StoX(at)){					
//						//看一下炮的上下信息
//						psmv = FileMove(StoY(at),pos->wBitFiles[StoX(at)]);
//
//						//sq1 = psmv->RookCap[DLoRight] + StoX(at);
//						//sq2 = psmv->CannonCap[DLoRight] + StoX(at);
//						//sq3 = psmv->SuperCap[DLoRight] + StoX(at);
//
//						if(StoY(mfrom) > StoY(at)){		//在炮的下面
//							sq2 = psmv->CannonCap[DLoRight] + StoX(at);
//							if(IsBlack(pos->b256[sq2]) && StoY(mfrom) < StoY(sq2) ){								
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy]; 
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//						else{
//							sq2 = psmv->CannonCap[DUpLeft] + StoX(at);
//							if(IsBlack(pos->b256[sq2])  && StoY(mfrom) > StoY(sq2) ){								
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy]; 
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//					}										
//				}
//				//2,**************************************************
//				if(StoX(mto) == StoX(at)){			//从炮的File上离开
//					if(StoX(mfrom) != StoX(at)){					
//						//看一下炮的上下信息
//						psmv = FileMove(StoY(at),pos->wBitFiles[StoX(at)]);
//
//						if(StoY(mto) > StoY(at)){		//在炮的下面
//							sq2 = psmv->CannonCap[DLoRight] + StoX(at);
//							if(IsBlack(pos->b256[sq2])  && StoY(mfrom) < StoY(sq2) ){							
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy];  
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//						else{
//							sq2 = psmv->CannonCap[DUpLeft] + StoX(at);
//							if(IsBlack(pos->b256[sq2]) && StoY(mfrom) > StoY(sq2) ){							
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy];  
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//					}										
//				}
//				//3, **************************************************
//				if(StoY(mfrom) == StoY(at)){			//从炮的Rank上离开
//					if(StoY(mto) != StoY(at)){
//						//看一下炮的左右信息
//						psmv = RankMove(StoX(at),pos->wBitRanks[StoY(at)]);
//
//						if(StoX(mfrom) > StoX(at)){
//							sq2 = psmv->CannonCap[DLoRight] + (at & 0xf0);
//							if(IsBlack(pos->b256[sq2])  && StoX(mfrom) < StoX(sq2) ){							
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy];  
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//						else{
//							sq2 = psmv->CannonCap[DUpLeft] + (at & 0xf0);
//							if(IsBlack(pos->b256[sq2])  && StoX(mfrom) > StoX(sq2) ){								
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy]; 
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//					}
//				}
//				//4, **************************************************
//				if(StoY(mto) == StoY(at)){			//从炮的Rank上离开
//					if(StoY(mfrom) != StoY(at)){
//						//看一下炮的左右信息
//						psmv = RankMove(StoX(at),pos->wBitRanks[StoY(at)]);
//
//						if(StoX(mto) > StoX(at)){
//							sq2 = psmv->CannonCap[DLoRight] + (at & 0xf0);
//							if(IsBlack(pos->b256[sq2])  && StoX(mto) < StoX(sq2)){							
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy]; 
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//						else{
//							sq2 = psmv->CannonCap[DUpLeft] + (at & 0xf0);
//							if(IsBlack(pos->b256[sq2]) && StoX(mto) > StoX(sq2)){								
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy]; 
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//					}
//				}
//
//				//
//		     }
//		}
//		//////////////////////////////////////////////////////////////////////////////////////////////////
//	}
//	//**************************************************************************
//
//
//	
//    
//NextStep:
//
//	/////////////////////////////////////////////////////////////////////////////////////
//	//在这儿将棋子恢复一下
//	for(int i=0; i<NotNum; i++){
//        int sq = NotList[i];
//		//
//		pos->b256[sq] = NotBoard[i];
//		//
//        InsertPiece(pos,pos->b256[sq], sq);
//
//        ASSERT(NextPiece(pos,PieceListStart(pos,pos->b256[sq])) != sq);
//    }
//	/////////////////////////////////////////////////////////////////////////////////////
//
//	if(attacker == 0){
//		return FALSE;
//	}
//
//	//////////////////////////////////////////////////////////////////////
//	////再看一下,如果二个棋相同,就不是
//	//if(PIECE_ID(pos->b256[to]) == PIECE_ID(pos->b256[attacker])){
//	//	return FALSE;
//	//}
//
//	//****************************************************************************
//    int at_id    = PIECE_ID(pos->b256[attacker]);
//	int to_id    = PIECE_ID(pos->b256[to]);
//
//#ifdef   USE_EAT_DIFF_CHESS            //常捉不同的子，不算常捉
//	//在这儿将被吃的棋子存一下
//	pos->eatChess[pos->eatNum] = to_id;
//#endif
//
//	if(at_id == PAWN || at_id == KING){
//		return FALSE;
//	}
//
//	//int me_id    = PIECE_ID(pos->b256[mto]);
//
//	//if(me_id == PAWN || me_id == KING){
//	//	return FALSE;
//	//}
//
//	//再看一下fromchess的价值是不是比tochess的价值小
//	if(PieceValues[pos->b256[attacker]] < PieceValues[pos->b256[to]]){
//		return TRUE;
//	}
//
//	//if(at_id == to_id){
//	//	return FALSE;
//	//}
//	//*****************************************************************************
//
//	
//
////再看一下吃了子后，对方有没有棋子可吃回
//
//	//更新一下FR*************
//
//	//if(paoTo == FALSE){
//		if(StoX(attacker) == tox){
//			tof ^= yBitMask(attacker);
//		}
//		if(StoY(attacker) == toy){
//			tor ^= xBitMask(attacker);
//		} 
//	//}
//	//else{
//	//	if(StoX(
//	//}
//
//	//再看一下对方能不能吃回来 
//
//	//////////////////////////////////////////////////////////////////////////////////////////////////
//	//  得先将对方不能走的棋子去了才行
//	NotNum          =0;         //不可能走的棋子的数量 
//
//		//**************************************************************************
//	if(side == WHITE){
//
//		//////////////////////////////////////////////////////////////////////////////
//		// 将黑方不可走棋去了
//		int king  = PieceListStart(pos,BKING);
//	    int kx    = StoX(king);
//		int ky    = StoY(king);
//		int ky4   = king & 0xf0;
//
//		int sq1;
//		int sq2;
//		int sq3;
//
//		psmv = FileMove(ky,pos->wBitFiles[kx]);
//
//		//得到将的上下信息
//		sq2 = psmv->CannonCap[DUpLeft] + kx;
//	
//		if(sq2 != king){
//			if(pos->b256[sq2] == RCHE){
//				sq1 = psmv->RookCap[DUpLeft] + kx;
//
//				if(IsBlack(pos->b256[sq1])){
//					//Not256Pos[NotNum] = sq1;
//					//------------------------------------
//					NotList[NotNum]  = sq1;
//					NotBoard[NotNum] = pos->b256[sq1];  //保存一下棋子
//					pos->b256[sq1]   = EMPTY;
//					//-------------------------------------
//					RemovePiece(pos,sq1);
//					NotNum++;
//				}				
//			}
//		}
//
//		//得到将下面第一个棋子
//		sq1 = psmv->RookCap[DLoRight] + kx;
//		
//		if(sq1 != king){
//			
//			sq2 = psmv->CannonCap[DLoRight] + kx;
//
//			if(sq2 != king){
//
//				int chess1 = pos->b256[sq1];
//				int chess2 = pos->b256[sq2];
//
//				if(chess2 == RCHE || chess2 == RKING){
//					if(IsBlack(chess1)){
//						//Not256Pos[NotNum] = sq1;
//						//------------------------------------
//						NotList[NotNum]  = sq1;
//						NotBoard[NotNum] = pos->b256[sq1];  //保存一下棋子
//						pos->b256[sq1]   = EMPTY;
//						//-------------------------------------
//						RemovePiece(pos,sq1);
//						NotNum++;
//					}
//				}
//
//				sq3 = psmv->SuperCap[DLoRight] + kx;
//				if(sq3 != king){
//					int chess3 = pos->b256[sq3];
//					if(chess3 == RPAO){
//						if(IsBlack(chess2)){
//							//Not256Pos[NotNum] = sq2;
//							//------------------------------------
//							NotList[NotNum]  = sq2;
//							NotBoard[NotNum] = pos->b256[sq2];  //保存一下棋子
//							pos->b256[sq2]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq2);
//							NotNum++;
//						}
//						if(IsBlack(chess1) && chess2 != RCHE && chess2 != RKING){
//							//Not256Pos[NotNum] = sq1;
//							//------------------------------------
//							NotList[NotNum]  = sq1;
//							NotBoard[NotNum] = pos->b256[sq1];  //保存一下棋子
//							pos->b256[sq1]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq1);
//							NotNum++;
//						}
//					}
//				}
//			}
//		}
//
//		//向左判断一下
//		psmv = RankMove(kx,pos->wBitRanks[ky]);
//
//		sq1 = psmv->RookCap[DUpLeft] + ky4;
//		if(sq1 != king){
//			
//			sq2 = psmv->CannonCap[DUpLeft] + ky4;
//
//			if(sq2 != king){
//				int chess1 = pos->b256[sq1];
//				int chess2 = pos->b256[sq2];
//				
//				if(chess2 == RCHE){
//					if(IsBlack(chess1)){
//						//Not256Pos[NotNum] = sq1;
//						//------------------------------------
//						NotList[NotNum]  = sq1;
//						NotBoard[NotNum] = pos->b256[sq1];  //保存一下棋子
//						pos->b256[sq1]   = EMPTY;
//						//-------------------------------------
//						RemovePiece(pos,sq1);
//						NotNum++;
//					}
//				}
//
//				sq3 = psmv->SuperCap[DUpLeft] + ky4;
//				if(sq3 != king){
//					int chess3 = pos->b256[sq3];
//					if(chess3 == RPAO){
//						if(IsBlack(chess2)){
//							//Not256Pos[NotNum] = sq2;
//							//------------------------------------
//							NotList[NotNum]  = sq2;
//							NotBoard[NotNum] = pos->b256[sq2];  //保存一下棋子
//							pos->b256[sq2]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq2);
//							NotNum++;
//						}
//						if(IsBlack(chess1) && chess2 != RCHE ){
//							//Not256Pos[NotNum] = sq1;
//							//------------------------------------
//							NotList[NotNum]  = sq1;
//							NotBoard[NotNum] = pos->b256[sq1];  //保存一下棋子
//							pos->b256[sq1]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq1);
//							NotNum++;
//						}
//					}
//				}
//			}		
//		}
//
//		//向右判断一下
//
//		psmv = RankMove(kx,pos->wBitRanks[ky]);
//
//		sq1 = psmv->RookCap[DLoRight] + ky4;
//		if(sq1 != king){
//			
//			sq2 = psmv->CannonCap[DLoRight] + ky4;
//
//			if(sq2 != king){
//				int chess1 = pos->b256[sq1];
//				int chess2 = pos->b256[sq2];
//				
//				if(chess2 == RCHE){
//					if(IsBlack(chess1)){
//						//Not256Pos[NotNum] = sq1;
//						//------------------------------------
//						NotList[NotNum]  = sq1;
//						NotBoard[NotNum] = pos->b256[sq1];  //保存一下棋子
//						pos->b256[sq1]   = EMPTY;
//						//-------------------------------------
//						RemovePiece(pos,sq1);
//						NotNum++;
//					}
//				}
//
//				sq3 = psmv->SuperCap[DLoRight] + ky4;
//				if(sq3 != king){
//					int chess3 = pos->b256[sq3];
//					if(chess3 == RPAO){
//						if(IsBlack(chess2)){
//							//Not256Pos[NotNum] = sq2;
//							//------------------------------------
//							NotList[NotNum]  = sq2;
//							NotBoard[NotNum] = pos->b256[sq2];  //保存一下棋子
//							pos->b256[sq2]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq2);
//							NotNum++;
//						}
//						if(IsBlack(chess1) && chess2 != RCHE ){
//							//Not256Pos[NotNum] = sq1;
//							//------------------------------------
//							NotList[NotNum]  = sq1;
//							NotBoard[NotNum] = pos->b256[sq1];  //保存一下棋子
//							pos->b256[sq1]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq1);
//							NotNum++;
//						}
//					}
//				}
//			}		
//		}
//
//		//再看一下马
//		 //判断一下有没有马在将军哇
//        for(int checkSq256 = PieceListStart(pos,RMA); checkSq256 > 0x32; checkSq256 = NextPiece(pos,checkSq256)){
//
//			//if(checkSq256 != mto){
//
//				int x   = horseLegTab(king - checkSq256 + 256);
//				int leg256 = checkSq256 + x;
//
//				if(x){
//					int leg14 = pos->b256[leg256];
//
//					if(IsBlack(leg14)){
//						//得判断一下,是不是已经拿走了
//						BOOL isRemove = FALSE;
//						for(int i = 0; i < NotNum; i++){
//							if(leg256 == NotList[i]){
//								isRemove = TRUE;
//								break;
//							}
//						}
//						//Not48Pos[NotNum]        = leg48;
//						if(isRemove == FALSE){
//							//Not256Pos[NotNum]       = leg256;
//							//------------------------------------
//							NotList[NotNum]  = leg256;
//							NotBoard[NotNum] = pos->b256[leg256];  //保存一下棋子
//							pos->b256[leg256]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos, leg256);
//							NotNum++;
//						}
//					}
//				}
//			//}
//		}
//        // 将黑方不可走棋去了 End
//		//////////////////////////////////////////////////////////////////////////////
//
//		psmv = FileMove(toy,tof);
//		//得到上面第一个
//		tmp = psmv->RookCap[DUpLeft] + tox;
//		if(tmp != to){ 
//
//			switch(pos->b256[tmp]){
//				case BCHE:  //黑车
//					attacker = tmp;
//					goto CanEatBack;
//					break;			
//				case BKING: //黑将
//					if(tmp+16 == to && toy < 0x6){
//						attacker = tmp;
//						goto CanEatBack;
//					}
//					break;
//				case BPAWN: //黑卒
//					if(tmp+16 == to){
//						attacker = tmp;
//						goto CanEatBack;
//					}
//					break;
//				default:
//					break;
//			}
//
//			//有了第一个才有第二个棋子
//			tmp = psmv->CannonCap[DUpLeft] + tox;
//			if(tmp != to){
//				int c14 = pos->b256[tmp];
//				if(c14 == BPAO){
//					attacker = tmp;
//					goto CanEatBack;
//				}
//			}
//		}
//		//得到to的下面第一个的棋子
//		tmp = psmv->RookCap[DLoRight] + tox;
//		if(tmp != to){   
//
//			switch(pos->b256[tmp]){			
//				case BCHE:
//					attacker = tmp;
//					goto CanEatBack;
//					break;
//				case BKING:
//					if(tmp-16 == to && toy < 0x6){
//						attacker = tmp;
//						goto CanEatBack;
//					}	
//					break;
//				default:
//					break;
//			} 
//
//			//有了第一个才有第二个棋子
//			tmp = psmv->CannonCap[DLoRight] + tox;
//			if(tmp != to ){
//				int c14 = pos->b256[tmp];
//				if(c14 == BPAO){
//					attacker = tmp;
//					goto CanEatBack;
//				}
//			}
//		}
//		//得到to的左右的信息
//		//psmv = smvRankMoveTab[tox-3] + tor; 
//
//		psmv = RankMove(tox,tor);
//		//得到to左面的第一个棋子
//		tmp = psmv->RookCap[DUpLeft] + nDisp;
//		if(tmp != to){ 
//
//			switch(pos->b256[tmp]){
//				 case BCHE:
//					attacker = tmp;
//					goto CanEatBack;
//					 break;		
//					
//				 case BKING:
//					 if((inBoard(to) & IN_BKING) && tmp+1 == to){
//						 attacker = tmp;
//						 goto CanEatBack;
//					 }
//					 break;				
//				 case BPAWN:
//					 if(toy > 0x7 && tmp+1 == to){
//						 attacker = tmp;
//						 goto CanEatBack;
//					 }
//					 break;
//				 default:
//					 break;                
//			}  
//
//			//有了第一个棋,才有第二个棋
//			tmp = psmv->CannonCap[DUpLeft] + nDisp;
//			if(tmp != to){
//				int c14 = pos->b256[tmp];
//				if(c14 == BPAO){
//					attacker = tmp;
//				    goto CanEatBack;
//				}
//			}
//		}
//		//得到to右面的第一个棋子
//		tmp = psmv->RookCap[DLoRight] + nDisp;
//		if(tmp != to){
//
//			switch(pos->b256[tmp]){				
//				case BCHE:
//					attacker = tmp;
//				    goto CanEatBack;
//					break;				
//				case BKING:
//					if((inBoard(to) & IN_BKING) && tmp-1 == to){
//						attacker = tmp;
//						goto CanEatBack;
//					}
//					break;			
//				case BPAWN:
//					if(toy > 0x7 && tmp-1 == to){
//						attacker = tmp;
//				       goto CanEatBack;
//					}
//					break;
//				default:
//					break;
//			}
//
//			//有了第一个棋,才有第二个棋
//			tmp = psmv->CannonCap[DLoRight] + nDisp;
//			if(tmp != to ){
//				int c14 = pos->b256[tmp];
//				if(c14 == BPAO){
//					attacker = tmp;
//				    goto CanEatBack;
//				}            
//			}
//		}
//
//
//
//		//黑仕
//		if(inBoard(to) & IN_BSHI){
//			for(int at = PieceListStart(pos,BSHI); at > 0x32; at = NextPiece(pos,at)){
//				//if(at != from && (GetDir(at,to) & DirShi)){
//				if((GetDir(at,to) & DirShi)){
//					attacker = at;
//				    goto CanEatBack;
//				}
//			}
//		}
//		//黑象
//		if(inBoard(to) & IN_BXIANG){
//			for(int at = PieceListStart(pos,BXIANG); at > 0x32; at = NextPiece(pos,at)){
//				/*if(at != from && (GetDir(at,to) & DirXiang) && pos->b256[(at+to)/2] == EMPTY){*/
//				if((GetDir(at,to) & DirXiang) && pos->b256[(at+to)/2] == EMPTY){
//					attacker = at;
//				    goto CanEatBack;
//				}
//			}
//		}
//
//		//黑马
//		for(int at = PieceListStart(pos,BMA); at > 0x32; at = NextPiece(pos,at)){
//			//if(at != from){
//			int m = horseLegTab(to-at+256);
//			if(m && !pos->b256[at+m]){
//				attacker = at;
//			    goto CanEatBack;
//			}
//			//}
//		}
//
//	}
//	//************************************************************************** 看红棋能不能吃
//	else{
//
//		//////////////////////////////////////////////////////////////////////////////
//		// 将红方不可走棋去了
//		int king  = PieceListStart(pos,RKING);
//	    int kx    = StoX(king);
//		int ky    = StoY(king);
//		int ky4   = king & 0xf0;
//
//		int sq1;
//		int sq2;
//		int sq3;
//
//		psmv = FileMove(ky,pos->wBitFiles[kx]);
//
//		//得到将下面第一个棋子
//		sq2 = psmv->CannonCap[DLoRight] + kx;
//	
//		if(sq2 != king){
//			if(pos->b256[sq2] == BCHE){
//				sq1 = psmv->RookCap[DLoRight] + kx;
//
//				if(IsWhite(pos->b256[sq1])){
//					//Not256Pos[NotNum] = sq1;
//					//------------------------------------
//					NotList[NotNum]  = sq1;
//					NotBoard[NotNum] = pos->b256[sq1];  //保存一下棋子
//					pos->b256[sq1]   = EMPTY;
//					//-------------------------------------
//					RemovePiece(pos,sq1);
//					NotNum++;
//				}				
//			}
//		}
//
//		//得到将上面第一个棋子
//		sq1 = psmv->RookCap[DUpLeft] + kx;
//		
//		if(sq1 != king){
//			
//			sq2 = psmv->CannonCap[DUpLeft] + kx;
//
//			if(sq2 != king){
//
//				int chess1 = pos->b256[sq1];
//				int chess2 = pos->b256[sq2];
//
//				if(chess2 == BCHE || chess2 == BKING){
//					if(IsWhite(chess1)){
//						//Not256Pos[NotNum] = sq1;
//						//------------------------------------
//						NotList[NotNum]  = sq1;
//						NotBoard[NotNum] = pos->b256[sq1];  //保存一下棋子
//						pos->b256[sq1]   = EMPTY;
//						//-------------------------------------
//						RemovePiece(pos,sq1);
//						NotNum++;
//					}
//				}
//
//				sq3 = psmv->SuperCap[DUpLeft] + kx;
//				if(sq3 != king){
//					int chess3 = pos->b256[sq3];
//					if(chess3 == BPAO){
//						if(IsWhite(chess2)){
//							//Not256Pos[NotNum] = sq2;
//							//------------------------------------
//							NotList[NotNum]  = sq2;
//							NotBoard[NotNum] = pos->b256[sq2];  //保存一下棋子
//							pos->b256[sq2]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq2);
//							NotNum++;
//						}
//						if(IsWhite(chess1) && chess2 != BCHE && chess2 != BKING){
//							//Not256Pos[NotNum] = sq1;
//							//------------------------------------
//							NotList[NotNum]  = sq1;
//							NotBoard[NotNum] = pos->b256[sq1];  //保存一下棋子
//							pos->b256[sq1]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq1);
//							NotNum++;
//						}
//					}
//				}
//			}
//		}
//
//		//向左判断一下
//		psmv = RankMove(kx,pos->wBitRanks[ky]);
//
//		sq1 = psmv->RookCap[DUpLeft] + ky4;
//		if(sq1 != king){
//			
//			sq2 = psmv->CannonCap[DUpLeft] + ky4;
//
//			if(sq2 != king){
//				int chess1 = pos->b256[sq1];
//				int chess2 = pos->b256[sq2];
//				
//				if(chess2 == BCHE){
//					if(IsWhite(chess1)){
//						//Not256Pos[NotNum] = sq1;
//						//------------------------------------
//						NotList[NotNum]  = sq1;
//						NotBoard[NotNum] = pos->b256[sq1];  //保存一下棋子
//						pos->b256[sq1]   = EMPTY;
//						//-------------------------------------
//						RemovePiece(pos,sq1);
//						NotNum++;
//					}
//				}
//
//				sq3 = psmv->SuperCap[DUpLeft] + ky4;
//				if(sq3 != king){
//					int chess3 = pos->b256[sq3];
//					if(chess3 == BPAO){
//						if(IsWhite(chess2)){
//							//Not256Pos[NotNum] = sq2;
//							//------------------------------------
//							NotList[NotNum]  = sq2;
//							NotBoard[NotNum] = pos->b256[sq2];  //保存一下棋子
//							pos->b256[sq2]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq2);
//							NotNum++;
//						}
//						if(IsWhite(chess1) && chess2 != BCHE ){
//							//Not256Pos[NotNum] = sq1;
//							//------------------------------------
//							NotList[NotNum]  = sq1;
//							NotBoard[NotNum] = pos->b256[sq1];  //保存一下棋子
//							pos->b256[sq1]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq1);
//							NotNum++;
//						}
//					}
//				}
//			}		
//		}
//
//		//向右判断一下
//
//		psmv = RankMove(kx,pos->wBitRanks[ky]);
//
//		sq1 = psmv->RookCap[DLoRight] + ky4;
//		if(sq1 != king){
//			
//			sq2 = psmv->CannonCap[DLoRight] + ky4;
//
//			if(sq2 != king){
//				int chess1 = pos->b256[sq1];
//				int chess2 = pos->b256[sq2];
//				
//				if(chess2 == BCHE){
//					if(IsWhite(chess1)){
//						//Not256Pos[NotNum] = sq1;
//						//------------------------------------
//						NotList[NotNum]  = sq1;
//						NotBoard[NotNum] = pos->b256[sq1];  //保存一下棋子
//						pos->b256[sq1]   = EMPTY;
//						//-------------------------------------
//						RemovePiece(pos,sq1);
//						NotNum++;
//					}
//				}
//
//				sq3 = psmv->SuperCap[DLoRight] + ky4;
//				if(sq3 != king){
//					int chess3 = pos->b256[sq3];
//					if(chess3 == BPAO){
//						if(IsWhite(chess2)){
//							//Not256Pos[NotNum] = sq2;
//							//------------------------------------
//							NotList[NotNum]  = sq2;
//							NotBoard[NotNum] = pos->b256[sq2];  //保存一下棋子
//							pos->b256[sq2]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq2);
//							NotNum++;
//						}
//						if(IsWhite(chess1) && chess2 != BCHE ){
//							//Not256Pos[NotNum] = sq1;
//							//------------------------------------
//							NotList[NotNum]  = sq1;
//							NotBoard[NotNum] = pos->b256[sq1];  //保存一下棋子
//							pos->b256[sq1]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq1);
//							NotNum++;
//						}
//					}
//				}
//			}		
//		}
//
//		//再看一下马
//		 //判断一下有没有马在将军哇
//        for(int checkSq256 = PieceListStart(pos,BMA); checkSq256 > 0x32; checkSq256 = NextPiece(pos,checkSq256)){
//			int x   = horseLegTab(king - checkSq256 + 256);
//			int leg256 = checkSq256 + x;
//
//			if(x){
//				int leg14 = pos->b256[leg256];
//
//				if(IsWhite(leg14)){
//					//得判断一下,是不是已经拿走了
//					BOOL isRemove = FALSE;
//					for(int i = 0; i < NotNum; i++){
//						if(leg256 == NotList[i]){
//							isRemove = TRUE;
//							break;
//						}
//					}
//					//Not48Pos[NotNum]        = leg48;
//					if(isRemove == FALSE){
//						//Not256Pos[NotNum]       = leg256;
//						//------------------------------------
//						NotList[NotNum]  = leg256;
//						NotBoard[NotNum] = pos->b256[leg256];  //保存一下棋子
//						pos->b256[leg256]   = EMPTY;
//						//-------------------------------------
//						RemovePiece(pos, leg256);
//						NotNum++;
//					}
//				}
//			}
//		}
//
//        // 将红方不可走棋去了 End
//		//////////////////////////////////////////////////////////////////////////////
//
//
//		psmv = FileMove(toy,tof);
//		//得到上面第一个
//		tmp = psmv->RookCap[DUpLeft] + tox;
//		if(tmp != to){ 
//
//			switch(pos->b256[tmp]){
//				case RCHE:  //红车
//					attacker = tmp;
//					goto CanEatBack;
//					break;
//				case RKING: //红帅
//					if(tmp+16 == to && toy > 0x9){
//						attacker = tmp;
//						goto CanEatBack;
//					}
//					break;				
//				default:
//					break;
//			}
//
//			//有了第一个才有第二个棋子
//			tmp = psmv->CannonCap[DUpLeft] + tox;
//			if(tmp != to){
//				int c14 = pos->b256[tmp];
//				if(c14 == RPAO){
//					attacker = tmp;
//					goto CanEatBack;
//				}				
//			}
//		}
//		//得到to的下面第一个的棋子
//		tmp = psmv->RookCap[DLoRight] + tox;
//		if(tmp != to){   
//
//			switch(pos->b256[tmp]){
//				case RCHE:
//					attacker = tmp;
//					goto CanEatBack;
//					break;
//				
//				case RKING:
//					if(tmp-16 == to && toy > 0x9){
//						attacker = tmp;
//						goto CanEatBack;
//					}
//					break;
//				
//				case RPAWN:
//					if(tmp-16 == to){
//						attacker = tmp;
//					    goto CanEatBack;
//					}
//					break;
//
//				default:
//					break;
//			} 
//
//			//有了第一个才有第二个棋子
//			tmp = psmv->CannonCap[DLoRight] + tox;
//			if(tmp != to ){
//				int c14 = pos->b256[tmp];
//				if(c14 == RPAO){
//					attacker = tmp;
//					goto CanEatBack;
//				}				
//			}
//		}
//		//得到to的左右的信息
//		//psmv = smvRankMoveTab[tox-3] + tor; 
//
//		psmv = RankMove(tox,tor);
//		//得到to左面的第一个棋子
//		tmp = psmv->RookCap[DUpLeft] + nDisp;
//		if(tmp != to){ 
//
//			switch(pos->b256[tmp]){
//				 case RCHE:
//					 attacker = tmp;
//					 goto CanEatBack;
//					 break;
//				
//				 case RKING:
//					 if((inBoard(to) & IN_RKING) && tmp+1 == to){
//						 attacker = tmp;
//						 goto CanEatBack;
//					 }
//					 break;
//				 
//				 case RPAWN:
//					 if(toy < 0x8 && tmp+1 == to){
//						 attacker = tmp;
//						 goto CanEatBack;
//					 }
//					 break;
//
//				 default:
//					 break;                
//			}  
//
//			//有了第一个棋,才有第二个棋
//			tmp = psmv->CannonCap[DUpLeft] + nDisp;
//			if(tmp != to){
//				int c14 = pos->b256[tmp];
//				if(c14 == RPAO){
//					attacker = tmp;
//					goto CanEatBack;
//				}			
//			}
//		}
//		//得到to右面的第一个棋子
//		tmp = psmv->RookCap[DLoRight] + nDisp;
//		if(tmp != to){
//
//			switch(pos->b256[tmp]){
//				case RCHE:
//					attacker = tmp;
//					goto CanEatBack;
//					break;
//				
//				case RKING:
//					if((inBoard(to) & IN_RKING) && tmp-1 == to){
//						attacker = tmp;
//					    goto CanEatBack;
//					}
//					break;
//				
//				case RPAWN:
//					if(toy < 0x8 && tmp-1 == to){
//						attacker = tmp;
//					    goto CanEatBack;
//					}
//					break;
//
//				default:
//					break;
//			}
//
//			//有了第一个棋,才有第二个棋
//			tmp = psmv->CannonCap[DLoRight] + nDisp;
//			if(tmp != to ){
//				int c14 = pos->b256[tmp];
//				if(c14 == RPAO){
//					attacker = tmp;
//					goto CanEatBack;
//				}				           
//			}
//		}
//
//		//红仕
//		if(inBoard(to) & IN_RSHI){
//			for(int at = PieceListStart(pos,RSHI); at > 0x32; at = NextPiece(pos,at)){
//				//if(at != from && shortDir(at-to+256) == 1){
//				/*if(at != from && (GetDir(at,to) & DirShi)){*/
//				if((GetDir(at,to) & DirShi)){
//					attacker = at;
//					goto CanEatBack;
//				}
//			}
//		}
//		//红相
//		if(inBoard(to) & IN_RXIANG){
//			for(int at = PieceListStart(pos,RXIANG); at > 0x32; at = NextPiece(pos,at)){
//				/*if(at != from && (GetDir(at,to) & DirXiang) && pos->b256[(at+to)/2] == EMPTY){*/
//				if((GetDir(at,to) & DirXiang) && pos->b256[(at+to)/2] == EMPTY){
//					attacker = at;
//					goto CanEatBack;
//				}
//			}
//		}
//
//
//		//红马
//		for(int at = PieceListStart(pos,RMA); at > 0x32; at = NextPiece(pos,at)){
//			//if(at != from){
//			int m = horseLegTab(to-at+256);
//			if(m && !pos->b256[at+m]){
//				attacker = at;
//				goto CanEatBack;
//			}
//			//}
//		}
//	}
//	//**************************************************************************
//
//	//先得恢复一下,
//	/////////////////////////////////////////////////////////////////////////////////////
//	//在这儿将棋子恢复一下
//	for(int i=0; i<NotNum; i++){
//        int sq = NotList[i];
//		//
//		pos->b256[sq] = NotBoard[i];
//		//
//        InsertPiece(pos,pos->b256[sq], sq);
//
//        ASSERT(NextPiece(pos,PieceListStart(pos,pos->b256[sq])) != sq);
//    }
//	/////////////////////////////////////////////////////////////////////////////////////
//
//	// PIECE_ID(pos->b256[attacker]);
//	int moveChessId = PIECE_ID(pos->b256[mto]);
//	
//	//再看一下
//
//	//********************************************************************
//	if(moveChessId == to_id ){
//		//再看一下, to_id 是不是不能动,如果不能动,就是true;
//
//		BOOL canMove = TRUE;
//		for(int i = 0; i < NotNum; i++){
//			if(to == NotList[i]){
//				canMove = FALSE;
//				break;
//			}
//		}
//
//		//这儿还要看一下是不是走的相同的棋
//
//		if(canMove){
//			return FALSE;
//		}
//	}
//	//**********************************************************************
//	else if(at_id == to_id){
//		if(false){
//		}
//		else if(at_id == MA){
//			int tmp = horseLegTab(attacker - to + 256);  //看一下对方的马能不能回吃
//
//			ASSERT(tmp != 0);
//
//			if(pos->b256[to + tmp] == 0){
//				return FALSE;
//			}
//		}
//		else if(at_id == PAO){
//			//这儿已经是 moveId != to_id 了
//
//			if(moveChessId == CHE){
//
//				//int at_id    = PIECE_ID(this->board[attacker]);
//				//int to_id    = PIECE_ID(this->board[to]);
//				//return TRUE;
//				//再看一下, 车能不能吃到炮 //mto 
//
//				if(false){
//				}
//				else if(StoX(mto) == StoX(to)){
//					if((FileMask(StoY(mto),pos->wBitFiles[StoX(mto)])->RookCap & yBitMask(to)) != 0){
//						return TRUE;
//					}
//				}
//				else if(StoY(mto) == StoY(to)){
//					if((RankMask(StoX(mto),pos->wBitFiles[StoY(mto)])->RookCap & xBitMask(to)) != 0){
//						return TRUE;
//					}
//				}	
//
//				return FALSE;
//			}
//		}
//		else return FALSE;
//	}
//
//	return TRUE;
//
//
//	////////////////////////////////////////////////////////////////////////////////////////
//	// 能吃回来
//CanEatBack:
//
//	//先得恢复一下,
//	/////////////////////////////////////////////////////////////////////////////////////
//	//在这儿将棋子恢复一下
//	for(int i=0; i<NotNum; i++){
//        int sq = NotList[i];
//		//
//		pos->b256[sq] = NotBoard[i];
//		//
//        InsertPiece(pos,pos->b256[sq], sq);
//
//        ASSERT(NextPiece(pos,PieceListStart(pos,pos->b256[sq])) != sq);
//    }
//	/////////////////////////////////////////////////////////////////////////////////////
//	return FALSE;
//
//}
//
