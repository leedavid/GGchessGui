#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"


//#define D8none          0x7e//33+90
//#define D8int           0x7e7e7e7e


/*
void GetMirrorOnlyB90(position_t *pos, uint8 b32[28]){

	uint8     sq;
	int     chess;

	const uint32  B32NONE_INT =   0xeeeeeeee;
	const uint8   B32NONE_CHAR=   0xee;        //238

	const uint8   NoRShi      =   0x66;
	
	memset(b32,B32NONE_INT,28);

	b32[1] = NoRShi;

	bool useMirror = false;

	//pos->b256

	uint8 *pc = pos->b256 + 0x33;   
	for(int y = 0; y < 10; y++){       

        if(*(pc+8) > *(pc+0)){
            goto MIRROR;
        }
        else if(*(pc+8) < *(pc+0)){
            goto UNMIROR;
        }

        if(*(pc+7) > *(pc+1)){
            goto MIRROR;
        }
        else if(*(pc+7) < *(pc+1)){
            goto UNMIROR;
        }


        if(*(pc+6) > *(pc+2)){
            goto MIRROR;
        }
        else if(*(pc+6) < *(pc+2)){
            goto UNMIROR;
        }


        if(*(pc+5) > *(pc+3)){
            goto MIRROR;
        }
        else if(*(pc+5) < *(pc+3)){
            goto UNMIROR;
        }
        pc += 16;
    }

MIRROR:
    useMirror = true;
UNMIROR:

    for(sq = 0x33; sq<0xcc; sq++){
        if(inBoard(sq) &(IN_RSIDE + IN_BSIDE)){
            //chess = b256[sq];

            if(useMirror){
                chess = pos->b256[Mirror(sq)];
            }
            else{
                chess = pos->b256[sq];
            }

            switch(chess){
                case RKING:
                    b32[0] &= 0xf0;
                    b32[0] |= B256ToByte[sq];
                    break;
                case RSHI:
                    if(b32[1]  == NoRShi){
                        b32[1] &= 0xf0;
                        b32[1] |= B256ToByte[sq];
                    }
                    else{
                        b32[1] &= 0x0f;
                        b32[1] |= (B256ToByte[sq] << 4);
                    } 
                    break;
                case RXIANG:
                    if(b32[2]  == B32NONE_CHAR){
                        b32[2] &= 0xf0;
                        b32[2] |= B256ToByte[sq];
                    }
                    else{
                        b32[2] &= 0x0f;
                        b32[2]  |= (B256ToByte[sq] << 4);
                    }
                    break;
                case RMA:
                    if(b32[3 + 0] == B32NONE_CHAR){
                        b32[3 + 0]  = sq;
                    }
                    else{
                        b32[3 + 1]  = sq;
                    }
                    break;
                case RCHE:
                    if(b32[5 + 0] == B32NONE_CHAR){
                        b32[5 + 0]  = sq;
                    }
                    else{
                        b32[5 + 1]  = sq;
                    }
                    break;
                case RPAO:
                    if(b32[7 + 0] == B32NONE_CHAR){
                        b32[7 + 0]  = sq;
                    }
                    else{
                        b32[7 + 1]  = sq;
                    }
                    break;
                case RPAWN:
                    if(b32[9 + 0] == B32NONE_CHAR){
                        b32[9 + 0]  = sq;
                    }
                    else if(b32[9 + 1] == B32NONE_CHAR){
                        b32[9 + 1]  = sq;
                    }
                    else if(b32[9 + 2] == B32NONE_CHAR){
                        b32[9 + 2]  = sq;
                    }
                    else if(b32[9 + 3] == B32NONE_CHAR){
                        b32[9 + 3]  = sq;
                    }
                    else {
                        b32[9 + 4]  = sq;
                    }
                    break;
                    //*******************************************
                case BKING:
                    //b32[P14To32[BKING]] = A256toASC[sq];
                    b32[0] &= 0x0f;
                    b32[0] |= (B256ToByte[sq]<<4);
                    break;
                case BSHI:
                    if(b32[14]  == B32NONE_CHAR){
                        b32[14] &= 0xf0;
                        b32[14] |= B256ToByte[sq];
                    }
                    else{
                        b32[14] &= 0x0f;
                        b32[14] |= (B256ToByte[sq] << 4);
                    }
                    break;
                case BXIANG:
                    if(b32[15]  == B32NONE_CHAR){
                        b32[15] &= 0xf0;
                        b32[15] |= B256ToByte[sq];
                    }
                    else{
                        b32[15] &= 0x0f;
                        b32[15] |= (B256ToByte[sq] << 4);
                    }
                    break;
                case BMA:
                    if(b32[16 + 0] == B32NONE_CHAR){
                        b32[16 + 0]  = sq;
                    }
                    else{
                        b32[16 + 1] = sq;
                    }
                    break;
                case BCHE:
                    if(b32[18 + 0] == B32NONE_CHAR){
                        b32[18 + 0]  = sq;
                    }
                    else{
                        b32[18 + 1] = sq;
                    }
                    break;
                case BPAO:
                    if(b32[20 + 0] == B32NONE_CHAR){
                        b32[20 + 0]  = sq;
                    }
                    else{
                        b32[20 + 1] = sq;
                    }
                    break;
                case BPAWN:
                    if(b32[22 + 0] == B32NONE_CHAR){
                        b32[22 + 0]  = sq;
                    }
                    else if(b32[22 + 1] == B32NONE_CHAR){
                        b32[22 + 1] = sq;
                    }
                    else if(b32[22 + 2] == B32NONE_CHAR){
                        b32[22 + 2] = sq;
                    }
                    else if(b32[22 + 3] == B32NONE_CHAR){
                        b32[22 + 3] = sq;
                    }
                    else {
                        b32[22 + 4] = sq;
                    }
                    break;
                default:
                    break;
            }
        }
    }



    //if(pos->side == BLACK){
    //    char bk = b32[P14To32[BKING]];
    //    char rk = b32[P14To32[RKING]];
    //    b32[P14To32[BKING]] = rk;
    //    b32[P14To32[RKING]] = bk;
    //}

    if(pos->side == BLACK){
        b32[1] |= 0x80;       //两个红仕不可能超过0x77, 没有就是超过了
    }

    //b32[32] = 0; //加上结尾
    b32[27] = 0; //加上结尾


    //for(int i=0; i<27; i++){
    //    if(b32[i] == 0){
    //        int tt= 0;
    //    }
    //}


}


*/