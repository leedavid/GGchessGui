#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

void
SendTimeRemaining(ChessProgramState *cps,int machineWhite)
{
    //   char message[MSG_SIZ];
    //   long time, otime;

    //   /* Note: this routine must be called when the clocks are stopped
    //      or when they have *just* been set or switched; otherwise
    //      it will be off by the time since the current tick started.
    //   */
    //   if (machineWhite) {
    //time = whiteTimeRemaining / 10;
    //otime = blackTimeRemaining / 10;
    //   } else {
    //time = blackTimeRemaining / 10;
    //otime = whiteTimeRemaining / 10;
    //   }
    //   if (time <= 0) time = 1;
    //   if (otime <= 0) otime = 1;
    //   
    //   sprintf(message, "time %ld\notim %ld\n", time, otime);
    //   SendToProgram(message, cps);
}
