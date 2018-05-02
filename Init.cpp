#include "stdafx.h"
#include "chess.h"
#include "data.h"
#include "resource.h"


VOID							//初始化设定数据
InitAppData(LPWSTR lpCmdLine){
  int i, j;
  //char buf[ARG_MAX];
  TCHAR currDir[MSG_SIZ];
  //char *dummy;

  dispboard_t *pDis = OBS[0];
  //char *p;


  EvalInfo = (TCHAR*)malloc((EVAL_INFO_SIZE + 1) * 2);



 

  //pDis->DIS.programName = szAppName;

  /* Initialize to defaults */
  appData.AlightSquareColor          = ParseColorName(LIGHT_SQUARE_COLOR);
  appData.AdarkSquareColor           = ParseColorName(DARK_SQUARE_COLOR);
  appData.AwhitePieceColor           = ParseColorName(WHITE_PIECE_COLOR);
  appData.AblackPieceColor           = ParseColorName(BLACK_PIECE_COLOR);
  appData.AhighlightSquareColor      = ParseColorName(HIGHLIGHT_SQUARE_COLOR);
  appData.ApremoveHighlightColor     = ParseColorName(PREMOVE_HIGHLIGHT_COLOR);
  
  TAB.consoleBackgroundColor		 = ParseColorName(COLOR_BKGD);
  
  SetDefaultTextAttribs();

 
  

  appData.timeDelay			    = TIME_DELAY;
  //appData.timeControl		    = TIME_CONTROL;
  //appData.timeIncrement		    = TIME_INCREMENT;


  appData.icsActive			    = FALSE;                    //是否打开了联网


  appData.useTelnet			    = FALSE;
  appData.telnetProgram		    = TELNET_PROGRAM;
  appData.gateway			    = L"";

  appData.autoSaveGames		    = FALSE;        //自动保存游戏

  pDis->bsize		   	        = (BoardSize) -1; /* determine by screen size */

  //appData.searchTime		    = "";
  //appData.searchDepth		    = 0;
  appData.showCoords		    = FALSE;    //显示棋盘坐标
  appData.ringBellAfterMoves    = TRUE;     //走步后发声
  appData.autoCallFlag		    = FALSE;
  appData.flipView			    = FALSE;    //翻转棋盘
  appData.autoFlipView		    = TRUE;     //自动
  appData.cmailGameName		    = "";

  appData.quietPlay			    = FALSE;
  appData.showThinking		    = FALSE;
  appData.ponderNextMove	    = TRUE;
  appData.periodicUpdates	    = TRUE;
  appData.popupExitMessage      = TRUE;
  appData.popupMoveErrors       = FALSE;
  appData.autoObserve		    = FALSE;
  appData.autoComment		    = FALSE;
  appData.animate			    = TRUE;     //动画速度
  appData.animSpeed			    = 10;
  appData.animateDragging	    = TRUE;
  appData.highlightLastMove     = TRUE;
  appData.getMoveList		    = TRUE;
  appData.testLegality		    = TRUE;
  appData.premove			    = TRUE;
  appData.premoveWhite		    = FALSE;
  appData.premoveWhiteText	    = _T("");
  appData.premoveBlack		     = FALSE;
  appData.premoveBlackText	    = _T("");
  appData.icsAlarm			    = TRUE;
  appData.icsAlarmTime		    = 5000;
  appData.autoRaiseBoard	    = TRUE;
  appData.localLineEditing	    = TRUE;
  appData.colorize			    = TRUE;
  appData.reuseFirst		    = TRUE;
  appData.reuseSecond		    = TRUE;
  appData.blindfold			    = FALSE;

  appData.AsaveSettingsOnExit	 = TRUE;
  pDis->boardX					 = CW_USEDEFAULT;
  pDis->boardY					 = CW_USEDEFAULT;

  //appData.icsNames				 = ICS_NAMES;


  appData.AhistP				= 0;
  appData.AhistIn				= 0;

  pDis->initialMode				= "";
  //pDis->variant					= "normal";
  //appData.firstProtocolVersion  = PROTOVER;
  //appData.secondProtocolVersion = PROTOVER;
  appData.showButtonBar			= TRUE;
  //-------------------------------------------------
  appData.winWidth				= -1;

  /* Point font array elements to structures and
     parse default font names */
  for (i=0; i<NUM_FONTS; i++) {
    for (j=0; j<NUM_SIZES; j++) {
      appData.Afont[j][i] = &fontRec[j][i];
      ParseFontName(appData.Afont[j][i]->def, &appData.Afont[j][i]->mfp);
    }
  }


    GetSetingInfoFromSqlite();


    pDis->boardX = appData.boardX;
    pDis->boardY = appData.boardY;


    pDis->first.yqID  = appData.first_yqID;

    pDis->lastDrawnFlipView = 0;
    pDis->lastReqValid      = 0;
    pDis->lastDrawnValid    = 0;

    memset(pDis->lastReq,0,256);
    memset(pDis->lastDrawn,0,256);


    GetYqinfoFromSqliteByID(&pDis->first, pDis->first.yqID);
    //GetYqinfoFromSqliteByID(&pDis->second,pDis->second.yqID);
    //GetCountInfoByUserId(&pDis->DIS.third,pDis->DIS.third.ICS_id); 
    GetCountInfoByUserId(&appData.ACPSics,appData.ACPSics.ICS_id);



  appData.icsActive         = FALSE;

  
  /* Make sure save files land in the right (?) directory */
  //if (GetFullPathName(appData.saveGameFile, MSG_SIZ, buf, &dummy)) {
	 // appData.saveGameFile = _strdup(buf);
  //}
  //if (GetFullPathName(appData.savePositionFile, MSG_SIZ, buf, &dummy)) {
	 // appData.savePositionFile = _strdup(buf);
  //}

  /* Finish initialization for fonts and sounds */
  for (i=0; i<NUM_FONTS; i++) {
	  for (j=0; j<NUM_SIZES; j++) {
		  CreateFontInMF(appData.Afont[j][i]);
	  }
  }


  GetCurrentDirectory(MSG_SIZ, currDir);
  SetCurrentDirectory(installDir);
  SetCurrentDirectory(currDir);

 // p = DIS.icsTextMenuString;
 // if (p[0] == '@') {
 //   //FILE* f = fopen(p + 1, "r");
 //   FILE *f;
	//fopen_s(&f,p + 1, "r");
 //   if (f == NULL) {
 //     DisplayFatalError(p + 1, errno, 2);
 //     return;
 //   }
 //   i = (int)fread(buf, 1, sizeof(buf)-1, f);
 //   fclose(f);
 //   buf[i] = NULLCHAR;
 //   p = buf;
 // }
 // ParseIcsTextMenu(_strdup(p));
}

