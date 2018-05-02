#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"



#ifdef DEBUG_CYCREPEAT_OPPSIDE
int debug_cyc_repeat(position_t * pos){
#else
int ban_repeat(position_t * pos){
#endif
    
    int i;

    //if(recog_draw(pos)){        //双方没有可攻击的棋子了
    //    return REPEAT_TRUE;
    //}

    //if(pos->pMat->mat_dummy == MAT_MUST_DRAW) return REPEAT_TRUE;

    Record*  re    = &pos->His[pos->gply];

    if(re->nonCap < 4){
        return REPEAT_NO;           //不可能重复
    }

    if(re->nonCap >= 256){
        return REPEAT_TRUE;         //双方不吃子步子太多了
    }

    uint32 b32 = ((uint32*)&(re-0)->key)[0];     //得到当前的key32

	int n;

    for(i = 4; i <= re->nonCap; i += 2){
        if(((uint32*)&(re-i)->key)[0] == b32){

			//首先判断是不是常捉对方了*******************************************
			int nOwnChecks = 1;
			int nOppChecks = 1;
			for(n = 0; n <i; n++){
				if((re-n)->ischeck == TRUE){
					/*if(1 & n){
						if(nOppChecks){
							nOppChecks++;
						}					
					}
					else{
						if(nOwnChecks){
							nOwnChecks ++;							
						}
					}	*/				
				}
				else{
					if( 1 & n){
						nOppChecks = 0;
					}
					else{
						nOwnChecks = 0;
					}
				}

				if(nOwnChecks == 0 && nOppChecks == 0){
					break;
				}
			}

			if(nOwnChecks && nOppChecks){		//双方长将
				return REPEAT_TRUE;
			}
			else if(nOwnChecks){
				 return REPEAT_BAN_OTHER;
			}
			else if(nOppChecks){
				return REPEAT_BAN_ME;
			}

			//再判断是不是常捉对方了*******************************************
			nOwnChecks = 1;
			nOppChecks = 1;

			//pos->eatNum = 0;        //复位常捉的棋子

            //---------------------------------------------------------------------------
			//#define MAX_EAT_REPEAT       16              //最大常捉步检测){
			//if(i > (MAX_EAT_REPEAT - 1)){
			//	i = MAX_EAT_REPEAT - 1;  //最多检查 MAX_EAT_REPEAT - 1步,就行了
			//}
			//----------------------------------------------------------------------------

			for(n = 0; n <i; n++){
#ifdef   USE_EAT_DIFF_CHESS            //常捉不同的子，不算常捉
				pos->eatNum = n;
				pos->eatChess[n] = EMPTY;   //先复位一下
#endif
				BOOL alwaysCap = FALSE;
				//BOOL alwaysChe = FALSE;

				//
				int other_m = (re-n)->move;
				int me_m    = (re-n-1)->move;

				int to;
				int from;

				if(n == i - 1){
					to    = FROM((re - n + 1)->move);
					from  = TO((re - n + 1)->move);
				}
				else{
					to   = TO(me_m);
					from = FROM(me_m);
				}

				int mfrom = FROM(other_m);
				int mto   = TO(other_m);

				if((re-n)->ischeck == FALSE && see_draw_20081016(pos,mfrom,mto, from,to, pos->side)){
					alwaysCap = TRUE;
				}				

//NONEED:				
                UnMakePosMoveOnly(pos);  //int m = pos->His[pos->curStep].move;

				

				//

				if(alwaysCap == TRUE){
			
				}
				else{
					if( 1 & n){
						nOppChecks = 0;
					}
					else{
						nOwnChecks = 0;
					}										
				}				

				if(nOwnChecks == 0 && nOppChecks == 0){
					n++;
					break;
				}
			}

			while(--n >= 0){
				MakePosMoveOnly(pos,(re-n)->move);
			}
#ifdef   USE_EAT_DIFF_CHESS            //常捉不同的子，不算常捉
			//---------------------------------------------------------------
			//再在这儿判断一下,是不是常捉的同一个棋子
			if(nOwnChecks){
				if(pos->eatChess[pos->eatNum-1] != pos->eatChess[pos->eatNum-3]){
					nOwnChecks = 0;
				}
			}

			if(nOppChecks){
				if(pos->eatChess[pos->eatNum-0] != pos->eatChess[pos->eatNum-2]){
					nOppChecks = 0;
				}
			}
			//---------------------------------------------------------------
#endif

			if(nOwnChecks && nOppChecks){		//双方长捉
				return REPEAT_TRUE;
			}
			else if(nOwnChecks){
				 //return REPEAT_NO;
				return REPEAT_BAN_OTHER;
			}
			else if(nOppChecks){		
				return REPEAT_BAN_ME;
				//return REPEAT_BAN_OTHER;
			}

            return REPEAT_TRUE;
        }
    }



    return REPEAT_NO;
}

#ifdef DEBUG_CYCREPEAT_OPPSIDE

int cyc_repeat(position_t * pos){


    
  int pcyc = debug_cyc_repeat(pos);


  //再将原先的POS undo 到初始局面,

  //int pgply = pos->gply;


  static position_t mpos[1];

  

  //int kkk = sizeof(mpos->b256_);

  memcpy(mpos,pos,sizeof(mpos->b256_));

  mpos->b256 = mpos->b256_;

  pos_red2black(mpos);

  mpos->side = pos->side ^ 0x1;
  mpos->gply = pos->gply;

  memcpy(mpos->His,pos->His,sizeof(pos->His));


  //还有走步,也要更新
  for(int i = 0; i < pos->gply; i++){
    
      //int test = 0;

      int move = pos->His[i+1].move;

      int from = 254 - FROM(move);
      int to   = 254 - TO(move);

      mpos->His[i+1].move = MOVE(from,to);
  }


  int mcyc = debug_cyc_repeat(mpos);

  
  

  if(pcyc != mcyc){


     board_display(pos, "repeat>>  原先的pos",stdout);
     board_display(mpos,"repeat>>  交换的pos",stdout);

     mcyc = debug_cyc_repeat(mpos);

     int test = 0;
  }

  return pcyc;
}


#endif