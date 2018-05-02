#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

void		//发送时间控制到引擎中
SendTimeControl(ChessProgramState *cps,int mps,long tc,int inc,int sd,int st){
    //char buf[MSG_SIZ];
    int seconds = (tc / 1000) % 60;

    switch(cps->ucci){
        case UCCI_UCCI_ms:		//象堡协议
		case UCCI_UCCI_OLD:
            break;
		//
		case UCCI_GGchess:
			break;
		//
        case UCCI_CYC105:
            break;
		//
        case UCCI_QianHong:		//浅红协议
            break;
        //
        default:		
            break;

    }

    //if (st > 0) {
    //	/* Set exact time per move, normally using st command */
    //	if (cps->stKludge) {
    //		/* GNU Chess 4 has no st command; uses level in a nonstandard way */
    //		seconds = st % 60;
    //		if (seconds == 0) {
    //			sprintf(buf, "level 1 %d\n", st/60);
    //		} 
    //		else {
    //			sprintf(buf, "level 1 %d:%02d\n", st/60, seconds);
    //		}
    //	} 
    //	else {
    //		sprintf(buf, "st %d\n", st);
    //	}
    //} 
    //else {
    //	/* Set conventional or incremental time control, using level command */
    //	if (seconds == 0) {
    //		/* Note old gnuchess bug -- minutes:seconds used to not work.
    //		Fixed in later versions, but still avoid :seconds
    //		when seconds is 0. */
    //		sprintf(buf, "level %d %ld %d\n", mps, tc/60000, inc/1000);
    //	} 
    //	else {
    //		sprintf(buf, "level %d %ld:%02d %d\n", mps, tc/60000,
    //			seconds, inc/1000);
    //	}
    //}
    //SendToProgram(buf, cps);

    ///* Orthoganally (except for GNU Chess 4), limit time to st seconds */
    ///* Orthogonally, limit search to given depth */
    //if (sd > 0) {
    //	if (cps->sdKludge) {
    //		sprintf(buf, "depth\n%d\n", sd);
    //	} 
    //	else {
    //		sprintf(buf, "sd %d\n", sd);
    //	}
    //	SendToProgram(buf, cps);
    //}
}
