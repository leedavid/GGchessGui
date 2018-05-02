#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

Boolean /* Parser for moves from gnuchess, ICS, or user typein box */
ParseOneMove(TCHAR *move,int moveNum,ChessMove *moveType, 
             int *fromX, int *fromY,int *toX,int *toY,int ucci)
{  
	switch(ucci){
		case UCCI_UCCI_ms:
		case UCCI_UCCI_OLD:
			*fromX = move[0] - 'a';
			*fromY = 9 - (move[1] - '0');
			*toX   = move[2] - 'a';
			*toY   = 9 - (move[3] - '0');					
			break;	
		case UCCI_GGchess:
			*fromX = move[0] - 'a';
			*fromY = 9 - (move[1] - '0');
			*toX   = move[2] - 'a';
			*toY   = 9 - (move[3] - '0');
			break;
		case UCCI_CYC105:
			*fromX = move[0] - 'a';
			*fromY = 9 - (move[1] - '0');
			*toX   = move[2] - 'a';
			*toY   = 9 - (move[3] - '0');					
			break;
		case UCCI_QianHong:
			_wcsupr_s(move,5);  //将传过来的move转换成大写的
			*fromX = move[0] - 'A';
			*fromY = 9 - (move[1] - '0');
			*toX   = move[2] - 'A';
			*toY   = 9 - (move[3] - '0');					
			break;        
		default:
			*fromX = move[0] - 'a';
			*fromY = 9 - (move[1] - '0');
			*toX   = move[2] - 'a';
			*toY   = 9 - (move[3] - '0');	
			break;
	}		

    if(   *fromX>=0 && *fromX<=8 && *fromY>=0 && *fromY<=9      
        &&*toX  >=0 && *toX  <=8 && *toY  >=0 && *toY  <=9 && (!(*fromX == *toX && *fromY == *toY))){
            return TRUE;
    }
    else{
        return FALSE;
    }
}



