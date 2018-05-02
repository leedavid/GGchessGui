#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

void        //自动进行下一局对局
NextMatchGame (dispboard_t* pDis){
    GameReset(pDis, FALSE, TRUE,TRUE);
    //if (*appData.loadGameFile != NULLCHAR) {
    //    LoadGameFromFile(appData.loadGameFile,
    //        appData.loadGameIndex,
    //        appData.loadGameFile, FALSE);
    //} 
    //else if (*appData.loadPositionFile != NULLCHAR) {
    //    LoadPositionFromFile(appData.loadPositionFile,
    //        appData.loadPositionIndex,
    //        appData.loadPositionFile);
    //}
    TwoMachinesEventIfReady(pDis);
}
