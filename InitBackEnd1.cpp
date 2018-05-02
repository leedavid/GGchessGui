#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

void
InitBackEnd1(dispboard_t *pDis){
    //int matched;
    //int min;		//分
    //int sec;		//秒
    //int ms;         //ms
    //TCHAR buf[MSG_SIZ];
    //GetTimeMark(&pDis->programStartTime);

	pDis->programStartTime = GetTickCount();

    ClearProgramStats();
    //DIS.programStats.ok_to_send = 1;
    //DIS.programStats.seen_stat  = 0;

    //ListNew(&DIS.gameList);    //Initialize game list

    if (appData.icsActive) { //Internet chess server status, 连线服务器状态
        //appData.matchMode  = FALSE;
        //appData.matchGames = 0;

        //appData.noChessProgram = TRUE;

        //if (*appData.icsHelper != NULLCHAR) {
        //    appData.useTelnet = TRUE;
        //    appData.telnetProgram = appData.icsHelper;
        //}
    } 
    else {
        //appData.zippyTalk = appData.zippyPlay = FALSE;
    }

    //if (!ParseTimeControl(appData.timeControl, appData.timeIncrement,appData.movesPerSession)){		
    //    StringCbPrintf(buf,MSG_SIZ,	"bad timeControl option %s", appData.timeControl);
    //    DisplayFatalError(buf, 0, 2);
    //}

    //if (*appData.searchTime != NULLCHAR) {  //Parse searchTime resource, 解析搜索时间
    //    matched = sscanf_s(appData.searchTime, "%d:%d:%d", &min, &sec,&ms);
    //    if (matched == 1) {
    //        DIS.searchTime = (min * 60) * 1000;
    //    } 
    //    else if (matched == 2) {
    //        DIS.searchTime = (min * 60 + sec) * 1000;
    //    }
    //    else if(matched == 3){
    //        DIS.searchTime = (min * 60 + sec) * 1000 + ms;
    //    }
    //    else {
    //        //char buf[MSG_SIZ];
    //        //sprintf(buf, "bad searchTime option %s", appData.searchTime);
    //        StringCbPrintf(buf,MSG_SIZ,"bad searchTime option %s", appData.searchTime);
    //        DisplayFatalError(buf, 0, 2);
    //    }
    //}

    //DIS.first.which				        = "first:  ";
    //DIS.second.which			        = "second: ";

    //DIS.first.UCCI_which         = 1;       //1,是红方
    //DIS.second.UCCI_which        = 2;       //2,是黑方

    pDis->first.playWhat           = NEUTRAL;
    //pDis->second.playWhat          = NEUTRAL;
    //.third.playWhat           = NEUTRAL;   //ICS

    //pDis->first.Already_Send_Initinfo = false;
    //pDis->first.Changed_ControlTime   = true;
    
    //pDis->second.Already_Send_Initinfo = false;
    //DIS.second.Changed_ControlTime   = true;

    //DIS.third.yqID               = 1;         //连线帐号

    appData.ACPSics.yqID = 1;

    //szHost

    sprintf_s(pDis->first.szHost, sizeof(pDis->first.szHost),"%s","localhost");
    //sprintf_s(pDis->second.szHost,sizeof(pDis->second.szHost),"%s","localhost");

    //DIS.first.UCCI_readyok              = false;
    //DIS.second.UCCI_readyok             = false;    //引擎还没有准备好

    //DIS.first.yqName                    = "引擎(1):";
    //DIS.second.yqName                   = "引擎(2):";

 //   pDis->first.maybeThinking		    = pDis->second.maybeThinking = FALSE;
	//pDis->first.maybePonering           = pDis->second.maybePonering = FALSE;

	pDis->first.cps_stat   = Cps_NotLoad;
	//pDis->second.cps_stat  = Cps_NotLoad;

	//SendMessage(hwndToolBar,TB_ENABLEBUTTON,IDT_Stop,0); 

    pDis->first.pr				        =  NoProc;
    pDis->first.isr				        =  NULL;

    //pDis->first.sendTime			    = pDis->second.sendTime = 1;

    pDis->first.sendDrawOffers	        = 1;

    appData.AconsoleCF.cbSize                = sizeof(CHARFORMAT);   //这是我加的   

    //DIS.first.program			= appData.first.program;
    //DIS.second.program			= appData.second.program;
    //DIS.first.host				= appData.first.host;
    //DIS.second.host				= appData.second.host;
    //DIS.first.dir				= appData.first.dir;
    //DIS.second.dir				= appData.second.dir;
 /*   pDis->first.other			= &pDis->second;
    pDis->second.other			= &pDis->first;*/
    //DIS.first.ucci				= appData.first.ucci;
    //DIS.second.ucci				= appData.second.ucci;


    //DIS.chessProgram            = false;


    //DIS.first.initString		= appData.first.initString;
    //DIS.second.initString		= appData.second.initString;	

    pDis->first.useSigint			 = TRUE;
    pDis->first.useSigterm		 = TRUE;
    pDis->first.reuse				= appData.reuseFirst; 
    pDis->first.useSetboard		 = FALSE;
    pDis->first.useSAN			= FALSE;
    pDis->first.usePing			= FALSE;
    pDis->first.lastPing			 = 0;
    pDis->first.lastPong			 = 0;
    pDis->first.usePlayother		 = FALSE;
    pDis->first.useColors			 = TRUE;
    pDis->first.useUsermove		 = FALSE;
    pDis->first.sendICS			 = FALSE;
    pDis->first.sendName			 = appData.icsActive;
    pDis->first.sdKludge			 = FALSE;
    pDis->first.stKludge			= FALSE;

    //TidyProgramName(DIS.first.program, DIS.first.host, DIS.first.tidy);
    //TidyProgramName(DIS.second.program, DIS.second.host, DIS.second.tidy);
    
    pDis->first.matchWins  = 0;
    //StringCbCopy(pDis->first.variants, MSG_SIZ,appData.variant);
    //StringCbCopy(pDis->second.variants,MSG_SIZ,appData.variant);
    pDis->first.analysisSupport  = 2; /* detect 分析功能哇 */
   
    //pDis->first.analyzing      = pDis->second.analyzing = FALSE;
    //pDis->first.UCCI_initDone  = pDis->second.UCCI_initDone = FALSE;

    //if (appData.firstProtocolVersion > PROTOVER || appData.firstProtocolVersion < 1) { //版本控制
    //    StringCbPrintf(buf,MSG_SIZ,"protocol version %d not supported",
    //        appData.secondProtocolVersion);
    //    DisplayFatalError(buf, 0, 2);
    //} 
    //else {
    //    //DIS.first.protocolVersion = appData.firstProtocolVersion;
    //}

    //if (appData.secondProtocolVersion > PROTOVER ||
    //    appData.secondProtocolVersion < 1) {
    //        //char buf[MSG_SIZ];
    //        //sprintf(buf, "protocol version %d not supported",
    //        //    appData.secondProtocolVersion);
    //        StringCbPrintf(buf,MSG_SIZ,"protocol version %d not supported",
    //            appData.secondProtocolVersion);
    //        DisplayFatalError(buf, 0, 2);
    //}
    //else {
    //    //DIS.second.protocolVersion = appData.secondProtocolVersion;
    //}

    //if (appData.icsActive) {
    //    //appData->clockMode = TRUE;  /* changes dynamically in ICS mode */
    //} 
    //else if (*appData.searchTime != NULLCHAR || appData.noChessProgram) {
    //    appData->clockMode = FALSE;
    //    pDis->first.sendTime = pDis->second.sendTime = 0;
    //}


    //if (pDis->noChessProgram) {		//没有象棋程序
    //    //MAIN.programVersion = (char*) malloc(5 + strlen(PRODUCT) + strlen(VERSION)
    //    //    + strlen(PATCHLEVEL));
    //    //StringCbPrintf(MAIN.programVersion, MSG_SIZ,
    //    //    "%s %s.%s", PRODUCT, VERSION, PATCHLEVEL);
    //} 
    //else {
    //    //char *p, *q;
    //    //q = DIS.first.program;
    //    //while (*q != ' ' && *q != NULLCHAR){
    //    //    q++;
    //    //}
    //    //p = q;
    //    //while (p > DIS.first.program && *(p-1) != '/'){
    //    //    p--;
    //    //}
    //    //DIS.programVersion = (char*) malloc(8 + strlen(PRODUCT) + strlen(VERSION)
    //    //    + strlen(PATCHLEVEL) + (q - p));        
    //    //StringCbPrintf(DIS.programVersion,MSG_SIZ,
    //    //    "%s %s.%s + ", PRODUCT, VERSION, PATCHLEVEL);    
    //    //strncat_s(DIS.programVersion,MSG_SIZ,p, q - p);
    //}

    if (!appData.icsActive) {
        //char buf[MSG_SIZ];
        /* Check for variants that are supported only in ICS mode,
        or not at all.  Some that are accepted here nevertheless
        have bugs; see comments below.
        */
        //VariantClass variant = StringToVariant(pDis->variant);
        //switch (variant) {
        //    case VariantBughouse:     // 四人游戏，二个棋盘 need four players and two boards */
        //    case VariantKriegspiel:   /* 盲目棋？？　　　　 need to hide pieces and move details */
        //    case VariantFischeRandom: /* castling doesn't work, shuffle not done */
        //        //sprintf(buf, "Variant %s supported only in ICS mode", appData.variant);
        //        StringCbPrintf(buf,MSG_SIZ,
        //            _T("Variant %s supported only in ICS mode"), pDis->variant);
        //        DisplayFatalError(buf, 0, 2);
        //        return;
        //    case VariantNormal:     /* definitely works! */
        //    case VariantWildCastle: /* pieces not automatically shuffled */
        //    case VariantNoCastle:   /* pieces not automatically shuffled */
        //    case VariantCrazyhouse: /* holdings not shown,offboard interposition not understood */
        //    case VariantLosers:     /* should work except for win condition,
        //                            and doesn't know captures are mandatory */
        //    case VariantSuicide:    /* should work except for win condition,
        //                            and doesn't know captures are mandatory */
        //    case VariantGiveaway:   /* should work except for win condition,
        //                            and doesn't know captures are mandatory */
        //    case VariantTwoKings:   /* should work */
        //    case VariantAtomic:     /* should work except for win condition */
        //    case Variant3Check:     /* should work except for win condition */
        //    case VariantShatranj:   /* might work if TestLegality is off */
        //        break;
        //    case VariantUnknown:
        //    case VariantLoadable:
        //    case Variant29:
        //    case Variant30:
        //    case Variant31:
        //    case Variant32:
        //    case Variant33:
        //    case Variant34:
        //    case Variant35:
        //    case Variant36:
        //    default:
        //        //未知参数
        //        //sprintf(buf, "Unknown variant name %s", appData.variant);
        //        StringCbPrintf(buf,MSG_SIZ,	"Unknown variant name %s", pDis->variant);
        //        DisplayFatalError(buf, 0, 2);
        //        return;
        //}
    }
}


