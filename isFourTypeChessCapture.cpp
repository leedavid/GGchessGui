#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"


//cap 是捉的子, becap, 被捉的子.
BOOL isFourTypeChess(position_t *pos,int mfrom,int mto, int cap, int becap, int which){

	int rk = PieceListStart(pos,RKING);
	int bk = PieceListStart(pos,BKING);	

	//当前是黑方在走棋
	if(which == WHITE){	

		if(pos->b256[becap]== RPAWN){   //常捉不过河的兵不算捉
			if(StoY(becap) >= 0x8) return false;
		}

		//*****************************************************************************
		//1, 走的子直接去捉对方走的子．(对方必定是走动的那个子)
		if(cap == mto) return TRUE;
		//*****************************************************************************
		//2, 让开了我方的炮架,马腿,象眼,去捉对方的子.(对方可能不动,可能动)
		//   cap 原先是炮架,或走到了炮架上
		if(pos->b256[cap] == BPAO){  //捉吃的子是炮
			if(false){
			}
			else if(StoX(cap) == StoX(becap)){ //在同一列
				if(false){
				}
				else if(StoX(mfrom) == StoX(cap)){  //离开产生的捉
					if(false){
					}
					else if(becap > cap){
						if(mfrom < becap && mfrom > cap) return TRUE;
					}
					else if(becap < cap){
						if(mfrom > becap && mfrom < cap) return TRUE;
					}
				}
				else if(StoX(mto)   == StoX(cap)){  //上去产生的捉
					if(false){
					}
					else if(becap > cap){
						if(mto < becap && mto > cap) return TRUE;
					}
					else if(becap < cap){
						if(mto > becap && mto < cap) return TRUE;
					}
				}
			}
			else if(StoY(cap) == StoY(becap)){ //在同一行
				if(false){
				}
				else if(StoY(mfrom) == StoY(cap)){  //离开产生的捉
					if(false){
					}
					else if(becap > cap){
						if(mfrom < becap && mfrom > cap) return TRUE;
					}
					else if(becap < cap){
						if(mfrom > becap && mfrom < cap) return TRUE;
					}
				}
				else if(StoY(mto)   == StoY(cap)){  //上去产生的捉
					if(false){
					}
					else if(becap > cap){
						if(mto < becap && mto > cap) return TRUE;
					}
					else if(becap < cap){
						if(mto > becap && mto < cap) return TRUE;
					}
				}
			}
		}

		//3, 让开了车去捉. 
		//fen 3akab2/3n3r1/6c2/pN2p3p/1rb3pn1/2N3P2/4PR2P/1C2B4/4A4/2BAK1R2 w - - 0 0
		if(pos->b256[cap] == BCHE){
			if(false){
			}
			else if(StoX(cap) == StoX(becap)){ //在同一列
				if(false){
				}
				else if(StoX(mfrom) == StoX(cap)){  //离开产生的捉
					if(false){
					}
					else if(becap > cap){
						if(mfrom < becap && mfrom > cap) return TRUE;
					}
					else if(becap < cap){
						if(mfrom > becap && mfrom < cap) return TRUE;
					}
				}
			}
			else if(StoY(cap) == StoY(becap)){ //在同一行
				if(false){
				}
				else if(StoY(mfrom) == StoY(cap)){  //离开产生的捉
					if(false){
					}
					else if(becap > cap){
						if(mfrom < becap && mfrom > cap) return TRUE;
					}
					else if(becap < cap){
						if(mfrom > becap && mfrom < cap) return TRUE;
					}
				}
			}
		}

		if(pos->b256[cap] == BMA){     //捉吃的子是马
			//fen 3ak4/4a2r1/2c1b4/p7p/4nn3/9/P2R4P/5C3/5K3/3A1AB2 r 让开了马腿捉
			//要看一下走的子,是不是让开了马腿, 走的子就马腿
			int tmp = horseLegTab(becap-cap+256);
			if(cap+tmp == mfrom) return TRUE;
            
		}
		if(pos->b256[cap] == BXIANG){  //捉吃的子是相
			//fen Ccbak1br1/1n2a4/7n1/R7p/6p2/2P6/1r2P1P1P/4C1N2/9/2BAK1BR1 r 让开了相眼捉
			if((cap+becap)/2 == mfrom) return TRUE;
		}
		//*****************************************************************************
		//4, 切断对方的联系,

		//这儿分好几种情况, 最好是从becap的四面分析,
		//a  第一个子 becap X1
		//1, 如果第一个子是becap方的炮, 则要判断是不是对方让开了, 才形成 becap pao
		//2, 如果第一个子是becap方的车, 则要判断是不是对方让车不能走了, 才形成che不能保护 becap
        
		//b, 第二个子 becap X1 X2
		//1, 第二个子becap方的che,则要判断是不是挡住了对方的che,以至于对方的车不能保护 becap 
		//2, 第二个子是becap方的炮,则要判断是不是让对方的炮不能走了, 不能保护becap了
		
		//c, 第三个了 becap X1 X2 X3
		//1, 只要判断是不是X1,X2就行了. 如果是,就是走到那儿,不让对方的炮保护了,也是可能新的捉

		//禁止了对方的子走动,如果对方的子正好在保护becap, 则可能是捉.

		//主要的特征是对方方的子原先有保护. 比如炮保护,马保护,相保护,
		//****** a,切断对方的车的保护***********************************************************************************
		for(int protect = PieceListStart(pos,RCHE); protect > 0x32; protect = NextPiece(pos,protect)){
			if(protect != becap){
				if(false){
				}
				else if(StoX(protect) == StoX(becap)){  //对方的车与被吃的在同一列
					SlideMoveStruct *psmv;
					psmv = FileMove(StoY(protect),pos->wBitFiles[StoX(protect)]);
					if(StoX(mto) == StoX(protect) && StoX(mfrom) != StoX(protect)){
						if(false){
						}
						else if(psmv->CannonCap[DLoRight] + StoX(protect) == becap){
							if(mto > protect && mto < becap) return TRUE;
						}
						else if(psmv->CannonCap[DUpLeft]  + StoX(protect) == becap){
							if(mto < protect && mto > becap) return TRUE;
						}
					}
				}
				else if(StoY(protect) == StoY(becap)){  //对方的车与被吃的在同一行
					SlideMoveStruct *psmv;
					psmv = RankMove(StoX(protect),pos->wBitRanks[StoY(protect)]);
					//加进去变成2个
					if(StoY(mto)   == StoY(protect) && StoY(mfrom) != StoY(protect)){
						if(false){
						}
						else if(psmv->CannonCap[DLoRight] + (protect & 0xf0) == becap){
							if(mto > protect && mto < becap) return TRUE;
						}
						else if(psmv->CannonCap[DUpLeft]  + (protect & 0xf0) == becap){
							if(mto < protect && mto > becap) return TRUE;
						}
					}
				}
			}
		}
		//****** a,切断对方的炮的保护
		//fen 4kab2/4a4/2n1b4/p1p1c3p/4R4/2P1P4/P5r1P/C3BcN2/5C3/3AKAB2 w - - 0 0
		for(int protect = PieceListStart(pos,RPAO); protect > 0x32 ; protect = NextPiece(pos,protect)){
			if(protect != becap){
				if(false){
				}
				else if(StoX(protect) == StoX(becap)){
					SlideMoveStruct *psmv;
					psmv = FileMove(StoY(protect),pos->wBitFiles[StoX(protect)]);
					//加进去变成2个
					if(StoX(mto)   == StoX(protect) && StoX(mfrom) != StoX(protect)){
						if(false){
						}
						else if(psmv->SuperCap[DLoRight] + StoX(protect) == becap){
							if(mto > protect && mto < becap) return TRUE;
						}
						else if(psmv->SuperCap[DUpLeft]  + StoX(protect) == becap){
							if(mto < protect && mto > becap) return TRUE;
						}
					}
					//走开来变成0个
					if(StoX(mfrom) == StoX(protect) && StoX(mto) != StoX(protect)){
						if(false){
						}
						else if(psmv->RookCap[DLoRight] + StoX(protect) == becap){
							if(mfrom > protect && mfrom < becap) return TRUE;
						}
						else if(psmv->RookCap[DUpLeft]  + StoX(protect) == becap){
							if(mfrom < protect && mfrom > becap) return TRUE;
						}
					}
				}
				else if(StoY(protect) == StoY(becap)){
					SlideMoveStruct *psmv;
					psmv = RankMove(StoX(protect),pos->wBitRanks[StoY(protect)]);
					//加进去变成2个
					if(StoY(mto)   == StoY(protect) && StoY(mfrom) != StoY(protect)){
						if(false){
						}
						else if(psmv->SuperCap[DLoRight] + (protect & 0xf0) == becap){
							if(mto > protect && mto < becap) return TRUE;
						}
						else if(psmv->SuperCap[DUpLeft]  + (protect & 0xf0) == becap){
							if(mto < protect && mto > becap) return TRUE;
						}
					}
					//走开来变成0个
					if(StoY(mfrom) == StoY(protect) && StoY(mto) != StoY(protect)){
						if(false){
						}
						else if(psmv->RookCap[DLoRight] + (protect & 0xf0) == becap){
							if(mfrom > protect && mfrom < becap) return TRUE;
						}
						else if(psmv->RookCap[DUpLeft]  + (protect & 0xf0) == becap){
							if(mfrom < protect && mfrom > becap) return TRUE;
						}
					}
				}
			}
		}
		//****** b,切断对方的马的保护 fen 3akab2/3n3r1/6c2/pN2p3p/1rb3pn1/2N3P2/4PR2P/1C2B4/4A4/2BAK1R2 w - - 0 0
		for(int protect = PieceListStart(pos,RMA); protect > 0x32 ; protect = NextPiece(pos,protect)){
			if(protect != becap){
				int tmp = horseLegTab(becap-protect+256);
				if(tmp != 0 && protect+tmp == mto) return TRUE; 
			}
		}

		//****** b,切断对方的相的保护 fen 3ak4/4a4/8b/R8/9/9/9/4BA3/N1r1A1n2/2B2K3 b - - 0 0
		for(int protect = PieceListStart(pos,RXIANG); protect > 0x32 ; protect = NextPiece(pos,protect)){
			if(protect != becap){
				if((protect+becap)/2 == mto) return TRUE;
			}
		}
		//*****************************************************************************
		//5,释放了我方的子去捉, 比如挡了对方的炮架, 或车架.(对方可能不动,可能动), 
		//主要的特征是我方的子与我方的将在一条线上.就有可能是释放了的子去捉的.
		//fen CR1akab1r/9/2n1b1n2/2p5p/6p2/2P6/r3P1P1P/4CcN2/9/2BAK1BR1 r
		if(StoX(bk) == StoX(cap) && StoX(bk) == StoX(mto)){ 
			//=======================================================
			//我方走到我方的将线, 这样我方原先不能动的棋子,有可能可以动了.
			//1, 挡住了对方的炮, 中间有3子了. 2, 挡住了对方的车, 中间有2子了. 
            SlideMoveStruct *psmv;
			psmv = FileMove(StoY(mto),pos->wBitFiles[StoX(mto)]);
			//只要求得bk 下面的子就行了
			int up;
			int low;
			up  = psmv->RookCap[DUpLeft] + StoX(mto);
			if(up != mto){  //上面有子
				if(up == bk){ //将 mto X X pao 
					low = psmv->SuperCap[DLoRight] + StoX(mto);
					if(pos->b256[low] == RPAO){                                   //这儿暂时不计算车与对方的将　
						if(cap > bk && cap < low) return TRUE;
					}
				}
				else{
					up = psmv->CannonCap[DUpLeft] + StoX(mto);
					if(up != mto){
						if(up == bk){  //将　X　mto X pao 
							low = psmv->CannonCap[DLoRight] + StoX(mto);
							if(pos->b256[low] == RPAO){
								if(cap > bk && cap < low) return TRUE;
							}
						}
						else{
							up = psmv->SuperCap[DUpLeft] + StoX(mto);							
							if(up == bk){
								//看一下下面的是不是对方的炮
								low = psmv->RookCap[DLoRight] + StoX(mto);
								if(pos->b256[low] == RPAO){ //将　X  X mto pao 
									if(cap > bk && cap < low) return TRUE;
								}
							}							
						}
					}					
				}
			}
			//=======================================================
		}
            
		if(StoY(bk) == StoY(cap) && StoY(bk) == StoY(mto)){
			//将的右面　　 //将 mto X X pao 
			//=======================================================
			//我方走到我方的将线, 这样我方原先不能动的棋子,有可能可以动了.
			//1, 挡住了对方的炮, 中间有3子了. 2, 挡住了对方的车, 中间有2子了. 
            SlideMoveStruct *psmv;
			psmv = RankMove(StoX(mto),pos->wBitRanks[StoY(mto)]);
			//只要求得bk 下面的子就行了 //将的右面　　 //将 mto X X pao 
			int left;
			int right;
			left  = psmv->RookCap[DUpLeft] + (mto & 0xf0);
			if(left != mto){  //左面有子
				if(left == bk){ //将 mto X X pao 
					right = psmv->SuperCap[DLoRight] + (mto & 0xf0);
					if(pos->b256[right] == RPAO){                                   //这儿暂时不计算车与对方的将　
						if(cap > bk && cap < right) return TRUE;
					}
				}
				else{
					left = psmv->CannonCap[DUpLeft] + StoX(mto);
					if(left != mto){
						if(left == bk){  //将　X　mto X pao 
							right = psmv->CannonCap[DLoRight] + (mto & 0xf0);
							if(pos->b256[right] == RPAO){
								if(cap > bk && cap < right) return TRUE;
							}
						}
						else{
							left = psmv->SuperCap[DUpLeft] + StoX(mto);							
							if(left == bk){
								//看一下下面的是不是对方的炮
								right = psmv->RookCap[DLoRight] + (mto & 0xf0);
								if(pos->b256[right] == RPAO){ //将　X  X mto pao 
									if(cap > bk && cap < right) return TRUE;
								}
							}							
						}
					}					
				}
			}
			//将的右面
			//=======================================================
			right  = psmv->RookCap[DLoRight] + (mto & 0xf0);
			if(right != mto){  //右面有子
				if(right == bk){ //pao X X mto 将 
					left = psmv->SuperCap[DUpLeft] + (mto & 0xf0);
					if(pos->b256[left] == RPAO){                                   //这儿暂时不计算车与对方的将　
						if(cap < bk && cap > left) return TRUE;
					}
				}
				else{
					right = psmv->CannonCap[DLoRight] + StoX(mto);
					if(right != mto){
						if(right == bk){  //pao X mto X 将 
							left = psmv->CannonCap[DUpLeft] + (mto & 0xf0);
							if(pos->b256[left] == RPAO){
								if(cap < bk && cap > left) return TRUE;
							}
						}
						else{
							right = psmv->SuperCap[DLoRight] + StoX(mto);							
							if(right == bk){
								//看一下下面的是不是对方的炮
								left = psmv->RookCap[DUpLeft] + (mto & 0xf0);
								if(pos->b256[left] == RPAO){  //pao mto X X 将  
									if(cap < bk && cap > left) return TRUE;
								}
							}							
						}
					}					
				}
			}
			//=======================================================
		}
		//6,禁止对方的子力去保护产生的捉.
		//通过牵制对方的子,产生的捉
		//1, 如果走的子是炮,
		//if(pos->b256[mto] == BPAO){
		if(false){
		}
		else if(StoX(mto) == StoX(rk) && StoX(mfrom) != StoX(rk)){
			//得到mto 的上下的棋子
			SlideMoveStruct *psmv;
			psmv = FileMove(StoY(mto),pos->wBitFiles[StoX(mto)]);

			if(false){
			}
			else if(StoY(mto) < StoY(rk)){
				if(false){
				}
				else if(pos->b256[mto] == BCHE || pos->b256[mto] == BKING){ //这儿还得加上一个将 :)
					int low2 = psmv->CannonCap[DLoRight] + StoX(mto);
					if(pos->b256[low2] == RKING){
						int low1 = psmv->RookCap[DLoRight] + StoX(mto);
						if(isCanProtect_Last_Move(pos,WHITE,low1,becap)){ //我方走了车,可能牵制了对方一个子
							return TRUE;
						}
					}
				}
				else if(pos->b256[mto] == BPAO){ 
					int low3 = psmv->SuperCap[DLoRight] + StoX(mto);
					if(pos->b256[low3] == RKING){
						int low1 = psmv->RookCap[DLoRight] + StoX(mto);
						int low2 = psmv->CannonCap[DLoRight] + StoX(mto);
						if(isCanProtect_Last_Move(pos,WHITE,low1,becap)){ //我方走了车,可能牵制了对方一个子
							return TRUE;
						}
						if(isCanProtect_Last_Move(pos,WHITE,low2,becap)){ //我方走了车,可能牵制了对方一个子
							return TRUE;
						}
					}
				}
			}
			else if(StoY(mto) > StoY(rk)){
				if(false){
				}
				else if(pos->b256[mto] == BCHE){ 
					int up2 = psmv->CannonCap[DUpLeft] + StoX(mto);
					if(pos->b256[up2] == RKING){
						int up1 = psmv->RookCap[DUpLeft] + StoX(mto);
						if(isCanProtect_Last_Move(pos,WHITE,up1,becap)){ //我方走了车,可能牵制了对方一个子
							return TRUE;
						}
					}
				}
				//else if(pos->b256[mto] == BPAO){ //这个不用了,没有意义
				//}
			}
		}
		else if(StoY(mto) == StoY(rk) && StoY(mfrom) != StoY(rk)){
			//得到mto 的左右的棋子
			SlideMoveStruct *psmv;
			psmv = RankMove(StoX(mto),pos->wBitRanks[StoY(mto)]);
			if(false){
			}
			else if(StoX(mto) < StoX(rk)){
				if(false){
				}
				else if(pos->b256[mto] == BCHE){
                    int r2 = psmv->CannonCap[DLoRight] + (mto & 0xf0);
					if(pos->b256[r2] == RKING){
						int r1 = psmv->RookCap[DLoRight] + (mto & 0xf0);
						if(isCanProtect_Last_Move(pos,WHITE,r1,becap)){ //我方走了车,可能牵制了对方一个子
							return TRUE;
						}
					}
				}
				else if(pos->b256[mto] == BPAO){
					int r3 = psmv->SuperCap[DLoRight] + (mto & 0xf0);
					if(pos->b256[r3] = RKING){
						int r1 = psmv->RookCap[DLoRight] + (mto & 0xf0);
						int r2 = psmv->CannonCap[DLoRight] + (mto & 0xf0);
						if(isCanProtect_Last_Move(pos,WHITE,r1,becap)){ //我方走了车,可能牵制了对方一个子
							return TRUE;
						}
						if(isCanProtect_Last_Move(pos,WHITE,r2,becap)){ //我方走了车,可能牵制了对方一个子
							return TRUE;
						}
					}
				}
			}
			else if(StoX(mto) > StoX(rk)){
				if(false){
				}
				else if(pos->b256[mto] == BCHE){
                    int l2 = psmv->CannonCap[DUpLeft] + (mto & 0xf0);
					if(pos->b256[l2] == RKING){
						int l1 = psmv->RookCap[DUpLeft] + (mto & 0xf0);
						if(isCanProtect_Last_Move(pos,WHITE,l1,becap)){ //我方走了车,可能牵制了对方一个子
							return TRUE;
						}
					}
				}
				else if(pos->b256[mto] == BPAO){
					int l3 = psmv->SuperCap[DUpLeft] + (mto & 0xf0);
					if(pos->b256[l3] = RKING){
						int l1 = psmv->RookCap[DUpLeft] + (mto & 0xf0);
						int l2 = psmv->CannonCap[DUpLeft] + (mto & 0xf0);
						if(isCanProtect_Last_Move(pos,WHITE,l1,becap)){ //我方走了车,可能牵制了对方一个子
							return TRUE;
						}
						if(isCanProtect_Last_Move(pos,WHITE,l2,becap)){ //我方走了车,可能牵制了对方一个子
							return TRUE;
						}
					}
				}
			}
		}
	}
	//#######################################################################################################################
	//当前是红方在走棋
	//#######################################################################################################################
	else{

		if(pos->b256[becap] == BPAWN){
			if(StoY(becap) <= 0x7) return false;
		}

		//*****************************************************************************
		//1, 走的子直接去捉对方走的子．(对方必定是走动的那个子)
		if(cap == mto) return TRUE;
		//*****************************************************************************
		//2, 让开了我方的炮架,马腿,象眼,去捉对方的子.(对方可能不动,可能动)
		//   cap 原先是炮架,或走到了炮架上
		//fen 2ba1k3/1N1Ca4/9/1n2c4/2b3p2/8p/6P1c/2C1B4/4A4/4KAB2 b 回马捉黑相
		if(pos->b256[cap] == RPAO){  //捉吃的子是炮  
			if(false){
			}
			else if(StoX(cap) == StoX(becap)){ //在同一列
				if(false){
				}
				else if(StoX(mfrom) == StoX(cap)){  //离开产生的捉
					if(false){
					}
					else if(becap > cap){
						if(mfrom < becap && mfrom > cap) return TRUE;
					}
					else if(becap < cap){
						if(mfrom > becap && mfrom < cap) return TRUE;
					}
				}
				else if(StoX(mto)   == StoX(cap)){  //上去产生的捉
					if(false){
					}
					else if(becap > cap){
						if(mto < becap && mto > cap) return TRUE;
					}
					else if(becap < cap){
						if(mto > becap && mto < cap) return TRUE;
					}
				}
			}
			else if(StoY(cap) == StoY(becap)){ //在同一行
				if(false){
				}
				else if(StoY(mfrom) == StoY(cap)){  //离开产生的捉
					if(false){
					}
					else if(becap > cap){
						if(mfrom < becap && mfrom > cap) return TRUE;
					}
					else if(becap < cap){
						if(mfrom > becap && mfrom < cap) return TRUE;
					}
				}
				else if(StoY(mto)   == StoY(cap)){  //上去产生的捉
					if(false){
					}
					else if(becap > cap){
						if(mto < becap && mto > cap) return TRUE;
					}
					else if(becap < cap){
						if(mto > becap && mto < cap) return TRUE;
					}
				}
			}
		}
		//3, 让开了车去捉. 
		//fen 3akab2/3n3r1/6c2/pN2p3p/1rb3pn1/2N3P2/4PR2P/1C2B4/4A4/2BAK1R2 w - - 0 0
		if(pos->b256[cap] == RCHE){
			if(false){
			}
			else if(StoX(cap) == StoX(becap)){ //在同一列
				if(false){
				}
				else if(StoX(mfrom) == StoX(cap)){  //离开产生的捉
					if(false){
					}
					else if(becap > cap){
						if(mfrom < becap && mfrom > cap) return TRUE;
					}
					else if(becap < cap){
						if(mfrom > becap && mfrom < cap) return TRUE;
					}
				}
			}
			else if(StoY(cap) == StoY(becap)){ //在同一行
				if(false){
				}
				else if(StoY(mfrom) == StoY(cap)){  //离开产生的捉
					if(false){
					}
					else if(becap > cap){
						if(mfrom < becap && mfrom > cap) return TRUE;
					}
					else if(becap < cap){
						if(mfrom > becap && mfrom < cap) return TRUE;
					}
				}
			}
		}

		if(pos->b256[cap] == RMA){     //捉吃的子是马
			//要看一下走的子,是不是让开了马腿, 走的子就马腿
			int tmp = horseLegTab(becap-cap+256);
			if(cap+tmp == mfrom) return TRUE;
            
		}
		if(pos->b256[cap] == RXIANG){  //捉吃的子是相
			if((cap+becap)/2 == mfrom) return TRUE;
		}
		//*****************************************************************************
		//****** a,切断对方的车的保护
		for(int protect = PieceListStart(pos,BCHE); protect > 0x32; protect = NextPiece(pos,protect)){
			if(protect != becap){
				if(false){
				}
				else if(StoX(protect) == StoX(becap)){  //对方的车与被吃的在同一列
					SlideMoveStruct *psmv;
					psmv = FileMove(StoY(protect),pos->wBitFiles[StoX(protect)]);
					if(StoX(mto) == StoX(protect) && StoX(mfrom) != StoX(protect)){
						if(false){
						}
						else if(psmv->CannonCap[DLoRight] + StoX(protect) == becap){
							if(mto > protect && mto < becap) return TRUE;
						}
						else if(psmv->CannonCap[DUpLeft]  + StoX(protect) == becap){
							if(mto < protect && mto > becap) return TRUE;
						}
					}
				}
				else if(StoY(protect) == StoY(becap)){  //对方的车与被吃的在同一行
					//fen 3akab2/9/4bc2n/8C/4p4/6P2/P1c1P3P/4B1R2/1r2A1n1C/1N1AK1B2 r
					SlideMoveStruct *psmv;
					psmv = RankMove(StoX(protect),pos->wBitRanks[StoY(protect)]);
					//加进去变成2个
					if(StoY(mto)   == StoY(protect) && StoY(mfrom) != StoY(protect)){
						if(false){
						}
						else if(psmv->CannonCap[DLoRight] + (protect & 0xf0) == becap){
							if(mto > protect && mto < becap) return TRUE;
						}
						else if(psmv->CannonCap[DUpLeft]  + (protect & 0xf0) == becap){
							if(mto < protect && mto > becap) return TRUE;
						}
					}
				}
			}
		}
		//3, 切断对方的联系,
		//主要的特征是对方方的子原先有保护. 比如炮保护,马保护,相保护,
		//****** a,切断对方的炮的保护
		//fen 4kab2/4a4/2n1b4/p1p1c3p/4R4/2P1P4/P5r1P/C3BcN2/5C3/3AKAB2 w - - 0 0
		for(int protect = PieceListStart(pos,BPAO); protect > 0x32 ; protect = NextPiece(pos,protect)){
			if(protect != becap){
				if(false){
				}
				else if(StoX(protect) == StoX(becap)){
					SlideMoveStruct *psmv;
					psmv = FileMove(StoY(protect),pos->wBitFiles[StoX(protect)]);
					//加进去变成2个
					if(StoX(mto)   == StoX(protect) && StoX(mfrom) != StoX(protect)){
						if(false){
						}
						else if(psmv->SuperCap[DLoRight] + StoX(protect) == becap){
							if(mto > protect && mto < becap) return TRUE;
						}
						else if(psmv->SuperCap[DUpLeft]  + StoX(protect) == becap){
							if(mto < protect && mto > becap) return TRUE;
						}
					}
					//走开来变成0个
					if(StoX(mfrom) == StoX(protect) && StoX(mto) != StoX(protect)){
						if(false){
						}
						else if(psmv->RookCap[DLoRight] + StoX(protect) == becap){
							if(mfrom > protect && mfrom < becap) return TRUE;
						}
						else if(psmv->RookCap[DUpLeft]  + StoX(protect) == becap){
							if(mfrom < protect && mfrom > becap) return TRUE;
						}
					}
				}
				else if(StoY(protect) == StoY(becap)){
					SlideMoveStruct *psmv;
					psmv = RankMove(StoX(protect),pos->wBitRanks[StoY(protect)]);
					//加进去变成2个
					if(StoY(mto)   == StoY(protect) && StoY(mfrom) != StoY(protect)){
						if(false){
						}
						else if(psmv->SuperCap[DLoRight] + (protect & 0xf0) == becap){
							if(mto > protect && mto < becap) return TRUE;
						}
						else if(psmv->SuperCap[DUpLeft]  + (protect & 0xf0) == becap){
							if(mto < protect && mto > becap) return TRUE;
						}
					}
					//走开来变成0个
					if(StoY(mfrom) == StoY(protect) && StoY(mto) != StoY(protect)){
						if(false){
						}
						else if(psmv->RookCap[DLoRight] + (protect & 0xf0) == becap){
							if(mfrom > protect && mfrom < becap) return TRUE;
						}
						else if(psmv->RookCap[DUpLeft]  + (protect & 0xf0) == becap){
							if(mfrom < protect && mfrom > becap) return TRUE;
						}
					}
				}
			}
		}
		//****** b,切断对方的马的保护 fen 3akab2/3n3r1/6c2/pN2p3p/1rb3pn1/2N3P2/4PR2P/1C2B4/4A4/2BAK1R2 w - - 0 0
		for(int protect = PieceListStart(pos,BMA); protect > 0x32 ; protect = NextPiece(pos,protect)){
			if(protect != becap){
				int tmp = horseLegTab(becap-protect+256);
				if(tmp != 0 && protect+tmp == mto) return TRUE; 
			}
		}
		//****** c,切断对方的相的保护 3ak4/4a4/8b/R8/9/9/9/4BA3/N1r1A1n2/2B2K3 b - - 0 0
		for(int protect = PieceListStart(pos,BXIANG); protect > 0x32 ; protect = NextPiece(pos,protect)){
			if(protect != becap){
				if((protect+becap)/2 == mto) return TRUE;
			}
		}

		//*****************************************************************************
		//4,释放了我方的子去捉, 比如挡了对方的炮架, 或车架.(对方可能不动,可能动), 
		//主要的特征是我方的子与我方的将在一条线上.就有可能是释放了的子去捉的.
		if(StoX(rk) == StoX(cap) && StoX(rk) == StoX(mto)){ 
			//=======================================================
			//我方走到我方的将线, 这样我方原先不能动的棋子,有可能可以动了.
			//1, 挡住了对方的炮, 中间有3子了. 2, 挡住了对方的车, 中间有2子了. 
            SlideMoveStruct *psmv;
			psmv = FileMove(StoY(mto),pos->wBitFiles[StoX(mto)]);
			//只要求得rk 上面的子就行了
			int up;
			int low;
			low  = psmv->RookCap[DLoRight] + StoX(mto);
			if(low != mto){  //下面有子
				if(low == rk){ //将 mto X X pao 
					up = psmv->SuperCap[DUpLeft] + StoX(mto);
					if(pos->b256[up] == BPAO){                                   //这儿暂时不计算车与对方的将　
						if(cap < rk && cap > up) return TRUE;
					}
				}
				else{
					low = psmv->CannonCap[DLoRight] + StoX(mto);
					if(low != mto){
						if(low == rk){  //将　X　mto X pao 
							up = psmv->CannonCap[DUpLeft] + StoX(mto);
							if(pos->b256[up] == BPAO){
								if(cap < rk && cap > up) return TRUE;
							}
						}
						else{
							low = psmv->SuperCap[DLoRight] + StoX(mto);							
							if(low == rk){
								//看一下下面的是不是对方的炮
								up = psmv->RookCap[DUpLeft] + StoX(mto);
								if(pos->b256[up] == BPAO){ //将　X  X mto pao 
									if(cap < rk && cap > up) return TRUE;
								}
							}							
						}
					}					
				}
			}
			//=======================================================
		}
		//
		if(StoY(rk) == StoY(cap) && StoY(rk) == StoY(mto)){
			//将的右面　　 //将 mto X X pao 
			//=======================================================
			//我方走到我方的将线, 这样我方原先不能动的棋子,有可能可以动了.
			//1, 挡住了对方的炮, 中间有3子了. 2, 挡住了对方的车, 中间有2子了. 
            SlideMoveStruct *psmv;
			psmv = RankMove(StoX(mto),pos->wBitRanks[StoY(mto)]);
			//只要求得bk 下面的子就行了 //将的右面　　 //将 mto X X pao 
			int left;
			int right;
			left  = psmv->RookCap[DUpLeft] + (mto & 0xf0);
			if(left != mto){  //左面有子
				if(left == rk){ //将 mto X X pao 
					right = psmv->SuperCap[DLoRight] + (mto & 0xf0);
					if(pos->b256[right] == BPAO){                                   //这儿暂时不计算车与对方的将　
						if(cap > rk && cap < right) return TRUE;
					}
				}
				else{
					left = psmv->CannonCap[DUpLeft] + StoX(mto);
					if(left != mto){
						if(left == rk){  //将　X　mto X pao 
							right = psmv->CannonCap[DLoRight] + (mto & 0xf0);
							if(pos->b256[right] == BPAO){
								if(cap > rk && cap < right) return TRUE;
							}
						}
						else{
							left = psmv->SuperCap[DUpLeft] + StoX(mto);							
							if(left == rk){
								//看一下下面的是不是对方的炮
								right = psmv->RookCap[DLoRight] + (mto & 0xf0);
								if(pos->b256[right] == BPAO){ //将　X  X mto pao 
									if(cap > rk && cap < right) return TRUE;
								}
							}							
						}
					}					
				}
			}
			//将的右面
			//=======================================================
			right  = psmv->RookCap[DLoRight] + (mto & 0xf0);
			if(right != mto){  //右面有子
				if(right == rk){ //pao X X mto 将 
					left = psmv->SuperCap[DUpLeft] + (mto & 0xf0);
					if(pos->b256[left] == BPAO){                                   //这儿暂时不计算车与对方的将　
						if(cap < rk && cap > left) return TRUE;
					}
				}
				else{
					right = psmv->CannonCap[DLoRight] + StoX(mto);
					if(right != mto){
						if(right == rk){  //pao X mto X 将 
							left = psmv->CannonCap[DUpLeft] + (mto & 0xf0);
							if(pos->b256[left] == BPAO){
								if(cap < rk && cap > left) return TRUE;
							}
						}
						else{
							right = psmv->SuperCap[DLoRight] + StoX(mto);							
							if(right == rk){
								//看一下下面的是不是对方的炮
								left = psmv->RookCap[DUpLeft] + (mto & 0xf0);
								if(pos->b256[left] == BPAO){  //pao mto X X 将  
									if(cap < rk && cap > left) return TRUE;
								}
							}							
						}
					}					
				}
			}
			//=======================================================
		}

		//6,禁止对方的子力去保护产生的捉.
		//通过牵制对方的子,产生的捉
		//1, 如果走的子是炮,
		//if(pos->b256[mto] == BPAO){
		if(false){
		}
		else if(StoX(mto) == StoX(bk) && StoX(mfrom) != StoX(bk)){
			//得到mto 的上下的棋子
			SlideMoveStruct *psmv;
			psmv = FileMove(StoY(mto),pos->wBitFiles[StoX(mto)]);

			if(false){
			}
			else if(StoY(mto) < StoY(bk)){
				if(false){
				}
				else if(pos->b256[mto] == RCHE){ //这儿还得加上一个将 :)
					int low2 = psmv->CannonCap[DLoRight] + StoX(mto);
					if(pos->b256[low2] == BKING){
						int low1 = psmv->RookCap[DLoRight] + StoX(mto);
						if(isCanProtect_Last_Move(pos,BLACK,low1,becap)){ //我方走了车,可能牵制了对方一个子
							return TRUE;
						}
					}
				}
				//else if(pos->b256[mto] == BPAO){ 
				//	int low3 = psmv->SuperCap[DLoRight] + StoX(mto);
				//	if(pos->b256[low3] == RKING){
				//		int low1 = psmv->RookCap[DLoRight] + StoX(mto);
				//		int low2 = psmv->CannonCap[DLoRight] + StoX(mto);
				//		if(isCanProtect_Last_Move(pos,WHITE,low1,becap)){ //我方走了车,可能牵制了对方一个子
				//			return TRUE;
				//		}
				//		if(isCanProtect_Last_Move(pos,WHITE,low2,becap)){ //我方走了车,可能牵制了对方一个子
				//			return TRUE;
				//		}
				//	}
				//}
			}
			else if(StoY(mto) > StoY(bk)){
				if(false){
				}
				else if(pos->b256[mto] == RCHE || pos->b256[mto] == RKING){ 
					int up2 = psmv->CannonCap[DUpLeft] + StoX(mto);
					if(pos->b256[up2] == BKING){
						int up1 = psmv->RookCap[DUpLeft] + StoX(mto);
						if(isCanProtect_Last_Move(pos,BLACK,up1,becap)){ //我方走了车,可能牵制了对方一个子
							return TRUE;
						}
					}
				}
				else if(pos->b256[mto] == RPAO){ 
					int up3 = psmv->SuperCap[DUpLeft] + StoX(mto);
					if(pos->b256[up3] == BKING){
						int up1 = psmv->RookCap[DUpLeft] + StoX(mto);
						int up2 = psmv->CannonCap[DUpLeft] + StoX(mto);
						if(isCanProtect_Last_Move(pos,BLACK,up1,becap)){ //我方走了车,可能牵制了对方一个子
							return TRUE;
						}
						if(isCanProtect_Last_Move(pos,BLACK,up2,becap)){ //我方走了车,可能牵制了对方一个子
							return TRUE;
						}
					}
				}
			}
		}
		else if(StoY(mto) == StoY(bk) && StoY(mfrom) != StoY(bk)){
			//得到mto 的左右的棋子
			SlideMoveStruct *psmv;
			psmv = RankMove(StoX(mto),pos->wBitRanks[StoY(mto)]);
			if(false){
			}
			else if(StoX(mto) < StoX(rk)){
				if(false){
				}
				else if(pos->b256[mto] == RCHE){
                    int r2 = psmv->CannonCap[DLoRight] + (mto & 0xf0);
					if(pos->b256[r2] == BKING){
						int r1 = psmv->RookCap[DLoRight] + (mto & 0xf0);
						if(isCanProtect_Last_Move(pos,BLACK,r1,becap)){ //我方走了车,可能牵制了对方一个子
							return TRUE;
						}
					}
				}
				else if(pos->b256[mto] == RPAO){
					int r3 = psmv->SuperCap[DLoRight] + (mto & 0xf0);
					if(pos->b256[r3] == BKING){
						int r1 = psmv->RookCap[DLoRight] + (mto & 0xf0);
						int r2 = psmv->CannonCap[DLoRight] + (mto & 0xf0);
						if(isCanProtect_Last_Move(pos,BLACK,r1,becap)){ //我方走了车,可能牵制了对方一个子
							return TRUE;
						}
						if(isCanProtect_Last_Move(pos,BLACK,r2,becap)){ //我方走了车,可能牵制了对方一个子
							return TRUE;
						}
					}
				}
			}
			else if(StoX(mto) > StoX(rk)){
				if(false){
				}
				else if(pos->b256[mto] == RCHE){
                    int l2 = psmv->CannonCap[DUpLeft] + (mto & 0xf0);
					if(pos->b256[l2] == BKING){
						int l1 = psmv->RookCap[DUpLeft] + (mto & 0xf0);
						if(isCanProtect_Last_Move(pos,BLACK,l1,becap)){ //我方走了车,可能牵制了对方一个子
							return TRUE;
						}
					}
				}
				else if(pos->b256[mto] == RPAO){
					int l3 = psmv->SuperCap[DUpLeft] + (mto & 0xf0);
					if(pos->b256[l3] == BKING){
						int l1 = psmv->RookCap[DUpLeft] + (mto & 0xf0);
						int l2 = psmv->CannonCap[DUpLeft] + (mto & 0xf0);
						if(isCanProtect_Last_Move(pos,BLACK,l1,becap)){ //我方走了车,可能牵制了对方一个子
							return TRUE;
						}
						if(isCanProtect_Last_Move(pos,BLACK,l2,becap)){ //我方走了车,可能牵制了对方一个子
							return TRUE;
						}
					}
				}
			}
		}
	}

	return FALSE;
}


//1, 走的子直接去捉对方走的子．(对方必定是走动的那个子)
//2, 让开了我方的炮架,马腿,象眼,去捉对方的子.(对方可能不动,可能动)
//3, 切断对方的保护,去捉对方的子, 如对方的炮的保护, 去捉对方原先炮保护的子.(对方可能不动,可能动),
//4, 释放了我方的子去捉, 比如挡了对方的炮架, 或车架.(对方可能不动,可能动),
//
//先可这样, 找出目前所有的捉, 对每一个捉进行判断. 如果是上面的一种,就是捉. 