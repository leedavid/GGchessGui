#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"
//是不是构成真的捉
void test_Is_True_Cap(position_t *pos,int from, int to, int ot_from, int ot_to,int which){

  int to_id = PIECE_ID(pos->b256[to]);

   //---------------------------------------------------------------------------
   //1, 是兵或将在吃, 就返回 FALSE ,这儿不用了, 因为前面的已去除了
   //---------------------------------------------------------------------------


   //---------------------------------------------------------------------------
   //2, 判断这个棋能不能走, 如果不能走,也就不可能去吃对方了
   //---------------------------------------------------------------------------
	if(Is_Can_Move_To_Eat(pos,from,to) == FALSE){  //捉方的子不能动.
		return;
	}

	//---------------------------------------------------------------------------
	//2, 在这儿求得吃的那个子的ORDER?
	//---------------------------------------------------------------------------
	//int order = 0;
	//for(int chess = PieceListStart(pos,pos->b256[to]); chess > 0x32; chess = NextPiece(pos,chess)){
	//	if(chess == to){          
	//		break;
	//	}	
	//	order++;		
	//}

   //---------------------------------------------------------------------------
   //3, 再判断一下这个捉的棋的价值是不是比被捉的棋的价值小
   //---------------------------------------------------------------------------
	if(PieceValues[pos->b256[from]] >= PieceValues[pos->b256[to]]){
		//---------------------------------------------------------------------------
		//4, 如果双方的棋子相同,则要判断 1, 这个棋子能不能走, 2, 这个棋能不能反吃对方(马)
		//---------------------------------------------------------------------------
		if(PIECE_ID(pos->b256[from]) == to_id){

			//===================================================================================================
			//
			if(Is_Can_Move_To_Eat(pos,to,from) == TRUE ){ 
				if(to_id != MA) return;
				//fen 3ak4/4a4/2ncb4/4N4/2p1P1b2/6B2/2P6/1N7/9/3AKAB2 b - - 157 157 这个不是
				//fen 3ak4/4a4/2ncb4/4N4/2p3b2/6B2/2P6/1N7/9/3AKAB2 b 这个是常捉
				int m = horseLegTab(from - to + 256);
				if(pos->b256[to+m] == EMPTY) return;   //这个马能不能反吃对方
				////如果这个是马,则要看一下这个马能不能吃到对方
			}
		}
		//---------------------------------------------------------------------------
		//5, 再看一下这个棋有没有其它的棋子保护着
		//---------------------------------------------------------------------------
		//a, 更新一下from,to的File,Rank信息,			
		//-------------------------------------------------------
		int cap   = pos->b256[to];
		int piece = pos->b256[from];
		ASSERT(cap != EMPTY);
		RemovePiece(pos,to);  //暂时不去,是因为去了以后加入的次序不对了. 

		pos->wBitRanks[StoY(from)]  ^= xBitMask(from);
		pos->wBitFiles[StoX(from)]  ^= yBitMask(from);

		MovePiece(pos,from,to);
		//board
		pos->b256[to]      = piece;
		pos->b256[from]    = EMPTY;
		//-------------------------------------------------------
		//如果没有吃子,也要更新TO

		//b, 再看一下有没有其它的棋子保护着
		BOOL isP = isPretectedd(pos,which,to,EMPTY);
		//BOOL isP = isPretectedd(pos,which,to,to);

		//c, 还原一下from,to的File,Rank信息,
		pos->wBitRanks[StoY(from)] ^= xBitMask(from);
		pos->wBitFiles[StoX(from)] ^= yBitMask(from);

		//P256
		pos->b256[from] = piece;
		pos->b256[to]   = cap;

		MovePiece(pos,to,from);
		InsertPiece(pos,cap,to);
		//-------------------------------------------------------

		if(isP == TRUE) return;
		//}		
	}
	//与上次的捉进行比对
	//再在这儿判断一下是不是捉的同一个棋子-------------========================================================

	//这个有二个常捉在, 要二次判断那个捉, 所以这个最复杂.
	//fen 3a1kb2/2r6/4ba3/p6Np/9/P3p1RcP/9/4B4/4A4/2BK1A3 b - - 53 53 
	//fen r2akab2/1c7/2n1b1c2/p1R1p3p/5nr2/9/P3P2NP/1CN1C4/5R3/2BAKAB2 b - - 16 16 

	//保存本次的捉
	int num  = pos->cap_num[0][which];

	pos->LastCapChess[num][0][which]      = to_id;  //这个只是捉的棋子,
	pos->last_to[num][0][which]           = to;     //
	pos->last_ot_from[num][0][which]      = ot_from;
	//pos->last_ot_to[num][0][which]        = ot_to;  

	if(num < MAX_REAL_CAP_NUM - 1){   //最多同时判断三个常捉
	   pos->cap_num[0][which]++;
	}

}

//for(int from = PieceListStart(pos,RCHE); from > 0x32; from = NextPiece(pos,from)){


//enum  {
//       EMPTY=0,
//       RKING=1,  RSHI=2,RXIANG=3, RMA=4, RCHE=5, RPAO=6, RPAWN=7,
//       BKING=8,  BSHI=9,BXIANG=10,BMA=11,BCHE=12,BPAO=13,BPAWN=14,
//       EMPTY16=16, OUTSIDE=32};


	//if(last_id == EMPTY){
	//	//******只有捉了才能更新哇 start
	//	board->LastCapChess[which] = to_id;
	//	board->last_to[which]      = to;              //这次我们捉对方的棋格
	//	board->ot_from[which]      = ot_from;
	//	//******只有捉了才能更新哇 end
	//	return TRUE;                           //只有返回捉子步,才更新一下上次捉的棋子
	//}
	//else if(last_id == to_id){  //这儿可能还要判断一下是不是吃的同一个棋子,比如移动的那个

	//	if(last_ot_from == to || last_to == to){                 //对方走那,我们捉那
	//		//******只有捉了才能更新哇 start
	//		board->LastCapChess[which] = to_id;
	//		board->last_to[which]      = to;              //这次我们捉对方的棋格
	//		board->ot_from[which]      = ot_from;
	//		//******只有捉了才能更新哇 end
	//		return TRUE;
	//	}
	//	//if(last_to == to){                     //这个是炮打
	//	//	//******只有捉了才能更新哇 start
	//	//	board->LastCapChess[which] = to_id;
	//	//	board->last_to[which]      = to;              //这次我们捉对方的棋格
	//	//	board->ot_from[which]      = ot_from;
	//	//	//******只有捉了才能更新哇 end
	//	//	return TRUE;
	//	//}
	//}