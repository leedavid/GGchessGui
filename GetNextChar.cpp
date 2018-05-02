#include "stdafx.h"
#include "chess.h"
#include "data.h"

void    get_Xor_Char(char* orgChar, int seed, char* nowChar){

	int len = (int)strlen(orgChar);

	for(int i = 0; i < len; i++){
		nowChar[i] = orgChar[i] ^ 0x77 ^ (seed * seed);

		nowChar[i] = (ABS(nowChar[i] * seed * 13 / 7) & 0xff);

		//if(nowChar[i] < 0x20 || nowChar[i] > 0x5d){

		//	if(i < len - 2){
		//		nowChar[i]  = orgChar[i+1];
		//	}
		//	else{
		//		nowChar[i]  = orgChar[i-5];
		//	}
		//}


		//if(nowChar[i] < 0x20){
		//	nowChar[i] += 0x20;
		//}
		//else if(nowChar[i] > 0x5d){
		//	if(i < len - 2){
		//		nowChar[i]  = orgChar[i+1];
		//	}
		//	else{
		//		nowChar[i]  = orgChar[i-5];
		//	}
		//}
		//else {
		//	nowChar[i]  = nowChar[i] ;
		//}
	}
}


//if(XOR_CHAR_2[i] < 0x20 || XOR_CHAR_2[i] > 0x5d){