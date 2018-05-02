#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

//char *
//TimeControlTagValue(){
//	char buf[MSG_SIZ];
//	if (!appData->clockMode) {
//		StringCbCopy(buf,MSG_SIZ,"-");
//	} else if (DIS.movesPerSession > 0) {
//		StringCbPrintf(buf,MSG_SIZ,"%d/%ld", DIS.movesPerSession, DIS.timeControl/1000);
//	} else if (DIS.timeIncrement == 0) {
//		StringCbPrintf(buf,MSG_SIZ,"%ld", DIS.timeControl/1000);
//	} else {
//		StringCbPrintf(buf,MSG_SIZ,"%ld+%ld", DIS.timeControl/1000, DIS.timeIncrement/1000);
//	}
//	return StrSave(buf);
//}

void
SetGameInfo(){
    /* This routine is used only for certain modes */
    //VariantClass v = DIS.pgn.variant;
    //ClearGameInfo(&DIS.pgn);
    //DIS.pgn.variant = v;

    //switch (DIS.gameMode) {
    //  case MachinePlaysWhite:
    //      //DIS.gameInfo.event = StrSave("Computer chess game"); IcsObserving
    //      StringCbPrintf(DIS.pgn.GameEvent,sizeof(DIS.pgn.GameEvent),"Computer chess game");
    //      //DIS.gameInfo.site = StrSave(HostName());
    //      StringCbPrintf(DIS.pgn.site,sizeof(DIS.pgn.site),HostName());
    //      //DIS.gameInfo.date = PGNDate();

    //      //StringCbPrintf(DIS.GGQJ.date,sizeof(DIS.GGQJ.date),PGNDate());
    //      PGNDate(DIS.pgn.date);

    //      //DIS.gameInfo.round = StrSave("-");
    //      StringCbPrintf(DIS.pgn.round,sizeof(DIS.pgn.round),"-");
    //      //DIS.gameInfo.white = StrSave(DIS.first.tidy);
    //      StringCbPrintf(DIS.pgn.Rname,sizeof(DIS.pgn.Rname),DIS.first.tidy);
    //      //DIS.gameInfo.black = StrSave(UserName());
    //      StringCbPrintf(DIS.pgn.Bname,sizeof(DIS.pgn.Bname),UserName());
    //      //DIS.gameInfo.timeControl = TimeControlTagValue();
    //      //StringCbPrintf(DIS.GGQJ.timeControl,sizeof(DIS.GGQJ.timeControl),TimeControlTagValue());
    //      TimeControlTagValue(DIS.pgn.timeControl);
    //      break;

    //  case MachinePlaysBlack:
    //      //DIS.gameInfo.event = StrSave("Computer chess game");
    //      StringCbPrintf(DIS.pgn.GameEvent,sizeof(DIS.pgn.GameEvent),"Computer chess game");
    //      //DIS.gameInfo.site = StrSave(HostName());
    //      StringCbPrintf(DIS.pgn.site,sizeof(DIS.pgn.site),HostName());
    //      //DIS.gameInfo.date = PGNDate();
    //      //StringCbPrintf(DIS.GGQJ.date,sizeof(DIS.GGQJ.date),PGNDate());
    //      PGNDate(DIS.pgn.date);
    //      //DIS.gameInfo.round = StrSave("-");
    //      StringCbPrintf(DIS.pgn.round,sizeof(DIS.pgn.round),"-");
    //      //DIS.gameInfo.white = StrSave(UserName());
    //      StringCbPrintf(DIS.pgn.Rname,sizeof(DIS.pgn.Rname),UserName());
    //      //DIS.gameInfo.black = StrSave(DIS.first.tidy);
    //      StringCbPrintf(DIS.pgn.Bname,sizeof(DIS.pgn.Bname),DIS.first.tidy);
    //      //DIS.gameInfo.timeControl = TimeControlTagValue();
    //      //StringCbPrintf(DIS.GGQJ.timeControl,sizeof(DIS.GGQJ.timeControl),TimeControlTagValue());
    //      TimeControlTagValue(DIS.pgn.timeControl);
    //      break;

    //  case TwoMachinesPlay:
    //      //DIS.gameInfo.event = StrSave("Computer chess game");
    //      StringCbPrintf(DIS.pgn.GameEvent,sizeof(DIS.pgn.GameEvent),"Computer chess game");
    //      //DIS.gameInfo.site = StrSave(HostName());
    //      StringCbPrintf(DIS.pgn.site,sizeof(DIS.pgn.site),HostName());
    //      //DIS.gameInfo.date = PGNDate();
    //      //StringCbPrintf(DIS.GGQJ.date,sizeof(DIS.GGQJ.date),PGNDate());
    //      PGNDate(DIS.pgn.date);
    //      if (DIS.matchGame > 0) {
    //          char buf[MSG_SIZ];
    //          //	    sprintf(buf, "%d", matchGame);
    //          StringCbPrintf(buf,MSG_SIZ,"%d", DIS.matchGame);
    //          //DIS.gameInfo.round = StrSave(buf);
    //          StringCbPrintf(DIS.pgn.round,sizeof(DIS.pgn.round),buf);
    //      } 
    //      else {
    //          //DIS.gameInfo.round = StrSave("-");
    //          StringCbPrintf(DIS.pgn.round,sizeof(DIS.pgn.round),"-");
    //      }
    //      //if (DIS.first.twoMachinesColor[0] == 'w') {
    //          //DIS.gameInfo.white = StrSave(DIS.first.tidy);
    //          StringCbPrintf(DIS.pgn.Rname,sizeof(DIS.pgn.Rname),DIS.first.tidy);
    //          //DIS.gameInfo.black = StrSave(DIS.second.tidy);
    //          StringCbPrintf(DIS.pgn.Bname,sizeof(DIS.pgn.Bname),DIS.second.tidy);
    //      //} 
    //      //else {
    //      //    //DIS.gameInfo.white = StrSave(DIS.second.tidy);
    //      //    StringCbPrintf(DIS.GGQJ.Rname,sizeof(DIS.GGQJ.Rname),DIS.second.tidy);
    //      //    //DIS.gameInfo.black = StrSave(DIS.first.tidy);
    //      //    StringCbPrintf(DIS.GGQJ.Bname,sizeof(DIS.GGQJ.Bname),DIS.first.tidy);
    //      //}
    //      //DIS.gameInfo.timeControl = TimeControlTagValue();
    //      //StringCbPrintf(DIS.GGQJ.timeControl,sizeof(DIS.GGQJ.timeControl),TimeControlTagValue());
    //      TimeControlTagValue(DIS.pgn.timeControl);
    //      break;

    //  case EditGame:
    //      //DIS.gameInfo.event = StrSave("Edited game");
    //      StringCbPrintf(DIS.pgn.GameEvent,sizeof(DIS.pgn.GameEvent),"Edited game");
    //      //DIS.gameInfo.site = StrSave(HostName());
    //      StringCbPrintf(DIS.pgn.site,sizeof(DIS.pgn.site),HostName());
    //      //DIS.gameInfo.date = PGNDate();
    //      //StringCbPrintf(DIS.GGQJ.date,sizeof(DIS.GGQJ.date),PGNDate());
    //      PGNDate(DIS.pgn.date);
    //      //DIS.gameInfo.round = StrSave("-");
    //      StringCbPrintf(DIS.pgn.round,sizeof(DIS.pgn.round),"-");
    //      //DIS.gameInfo.white = StrSave("-");
    //      StringCbPrintf(DIS.pgn.Rname,sizeof(DIS.pgn.Rname),"-");
    //      //DIS.gameInfo.black = StrSave("-");
    //      StringCbPrintf(DIS.pgn.Bname,sizeof(DIS.pgn.Bname),"-");
    //      break;

    //  case EditPosition:
    //      //DIS.gameInfo.event = StrSave("Edited position");
    //      StringCbPrintf(DIS.pgn.GameEvent,sizeof(DIS.pgn.GameEvent),"Edited position");
    //      //DIS.gameInfo.site = StrSave(HostName());
    //      StringCbPrintf(DIS.pgn.site,sizeof(DIS.pgn.site),HostName());
    //      //DIS.gameInfo.date = PGNDate();
    //      //StringCbPrintf(DIS.GGQJ.date,sizeof(DIS.GGQJ.date),PGNDate());
    //      PGNDate(DIS.pgn.date);
    //      //DIS.gameInfo.round = StrSave("-");
    //      StringCbPrintf(DIS.pgn.round,sizeof(DIS.pgn.round),"-");
    //      //DIS.gameInfo.white = StrSave("-");
    //      StringCbPrintf(DIS.pgn.Rname,sizeof(DIS.pgn.Rname),"-");
    //      //DIS.gameInfo.black = StrSave("-");
    //      StringCbPrintf(DIS.pgn.Bname,sizeof(DIS.pgn.Bname),"-");
    //      break;

    //  case IcsPlayingWhite:
    //  case IcsPlayingBlack:
    //  case IcsObserving:
    //  case IcsExamining:
    //      break;

    //  case PlayFromGameFile:
    //      //DIS.gameInfo.event = StrSave("Game from non-PGN file");
    //      StringCbPrintf(DIS.pgn.GameEvent,sizeof(DIS.pgn.GameEvent),"Game from non-PGN file");
    //      //DIS.gameInfo.site = StrSave(HostName());
    //      StringCbPrintf(DIS.pgn.site,sizeof(DIS.pgn.site),HostName());
    //      //DIS.gameInfo.date = PGNDate();
    //      //StringCbPrintf(DIS.GGQJ.date,sizeof(DIS.GGQJ.date),PGNDate());
    //      PGNDate(DIS.pgn.date);
    //      //DIS.gameInfo.round = StrSave("-");
    //      StringCbPrintf(DIS.pgn.round,sizeof(DIS.pgn.round),"-");
    //      //DIS.gameInfo.white = StrSave("?");
    //      StringCbPrintf(DIS.pgn.Rname,sizeof(DIS.pgn.Rname),"?");
    //      //DIS.gameInfo.black = StrSave("?");
    //      StringCbPrintf(DIS.pgn.Bname,sizeof(DIS.pgn.Bname),"?");
    //      break;

    //  default:
    //      break;
    //}
}
