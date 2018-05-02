#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

void 
ParaseDisMoveToUCCImove(int move, char *UCCImove, int ucci){
    //switch(ucci){
    //    case UCCI_UCCI:
    //        UCCImove[0] = 'a' + S90toF(MOVE_FROM(move));
    //        UCCImove[1] = '0' + 9 - S90toR(MOVE_FROM(move));
    //        //buf[2] = '-';
    //        UCCImove[2] = 'a' + S90toF(MOVE_TO(move));
    //        UCCImove[3] = '0' + 9 - S90toR(MOVE_TO(move));
    //        UCCImove[4] = '\n';
    //        UCCImove[5]	= NULLCHAR;
    //        break;
    //    case UCCI_DIS:
    //        UCCImove[0] = 'A' + S90toF(MOVE_FROM(move));
    //        UCCImove[1] = '0' + 9 - S90toR(MOVE_FROM(move));
    //        //UCCImove[2] = '-';
    //        UCCImove[2] = 'A' + S90toF(MOVE_TO(move));
    //        UCCImove[3] = '0' + 9 - S90toR(MOVE_TO(move));
    //        UCCImove[4] = '\n';
    //        UCCImove[5] = NULLCHAR;
    //        break;
    //    case UCCI_QH:		
    //    default:
    //        UCCImove[0] = 'A' + S90toF(MOVE_FROM(move));
    //        UCCImove[1] = '0' + 9 - S90toR(MOVE_FROM(move));
    //        UCCImove[2] = '-';
    //        UCCImove[3] = 'A' + S90toF(MOVE_TO(move));
    //        UCCImove[4] = '0' + 9 - S90toR(MOVE_TO(move));
    //        UCCImove[5] = '\n';
    //        UCCImove[6] = NULLCHAR;
    //        break;
    //        //case UCCI_DIS:
    //        //	buf[0] = 'A' + S90toF(MOVE_FROM(move));
    //        //	buf[1] = '0' + 9 - S90toR(MOVE_FROM(move));
    //        //	//buf[2] = '-';
    //        //	buf[2] = 'A' + S90toF(MOVE_TO(move));
    //        //	buf[3] = '0' + 9 - S90toR(MOVE_TO(move));
    //        //	buf[4] = '\n';
    //        //	buf[5] = NULLCHAR;
    //        //	break
    //        //default:
    //        //	buf[0] = 'A' + S90toF(MOVE_FROM(move));
    //        //	buf[1] = '0' + 9 - S90toR(MOVE_FROM(move));
    //        //	//buf[2] = '-';
    //        //	buf[2] = 'A' + S90toF(MOVE_TO(move));
    //        //	buf[3] = '0' + 9 - S90toR(MOVE_TO(move));
    //        //	buf[4] = '\n';
    //        //	buf[5] = NULLCHAR;
    //        //	break;
    //}
}
