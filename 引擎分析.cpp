
#include "stdafx.h"
#include "GGchess.h"
#include "chess.h"
#include "data.h"

//让引擎分析当前的局面
BOOL LetYqAnalizeCurPos(dispboard_t* pDis){

	ChessProgramState *cps = &pDis->first; 

	if(cps->cps_stat != Cps_Waiting){
		SendToProgram(L"stop\n", cps);		
		Sleep(150);	
		pDis->gameMode = AnalyzeMode;
	}

	cps = &pDis->first; 	

	if(cps == NULL){

		LogOut(_T("\n**********************\n您不能进入分析模式,可能没有加载任何成功引擎!\n**********************"));
		
		return FALSE;
	}

	//让引擎思考当前局面

	if(cps->playWhat != pDis->pos->side){
		cps->playWhat = pDis->pos->side;
	}

	SendProgramGo(cps,Cps_Analyse,L"none");

	return TRUE;
}
//
//int
//AnalyzeModeEvent()
//{
//	char buf[MSG_SIZ];
//
//	if (!first.analysisSupport) {
//		snprintf(buf, sizeof(buf), _("%s does not support analysis"), first.tidy);
//		DisplayError(buf, 0);
//		return 0;
//	}
//	/* [DM] icsEngineAnalyze [HGM] This is horrible code; reverse the gameMode and isEngineAnalyze tests! */
//	if (appData.icsActive) {
//		if (gameMode != IcsObserving) {
//			snprintf(buf, MSG_SIZ, _("You are not observing a game"));
//			DisplayError(buf, 0);
//			/* secure check */
//			if (appData.icsEngineAnalyze) {
//				if (appData.debugMode)
//					fprintf(debugFP, "Found unexpected active ICS engine analyze \n");
//				ExitAnalyzeMode();
//				ModeHighlight();
//			}
//			return 0;
//		}
//		/* if enable, user wants to disable icsEngineAnalyze */
//		if (appData.icsEngineAnalyze) {
//			ExitAnalyzeMode();
//			ModeHighlight();
//			return 0;
//		}
//		appData.icsEngineAnalyze = TRUE;
//		if (appData.debugMode)
//			fprintf(debugFP, "ICS engine analyze starting... \n");
//	}
//
//	if (gameMode == AnalyzeMode) { ToggleSecond(); return 0; }
//	if (appData.noChessProgram || gameMode == AnalyzeMode)
//		return 0;
//
//	if (gameMode != AnalyzeFile) {
//		if (!appData.icsEngineAnalyze) {
//			EditGameEvent();
//			if (gameMode != EditGame) return 0;
//		}
//		if (!appData.showThinking) ToggleShowThinking();
//		ResurrectChessProgram();
//		SendToProgram("analyze\n", &first);
//		first.analyzing = TRUE;
//		/*first.maybeThinking = TRUE;*/
//		first.maybeThinking = FALSE; /* avoid killing GNU Chess */
//		EngineOutputPopUp();
//	}
//	if (!appData.icsEngineAnalyze) gameMode = AnalyzeMode;
//	pausing = FALSE;
//	ModeHighlight();
//	SetGameInfo();
//
//	StartAnalysisClock();
//	GetTimeMark(&lastNodeCountTime);
//	lastNodeCount = 0;
//	return 1;
//}

BOOL AnalizeEvent(dispboard_t* pDis){

	 //(appData.noche)

	if (pDis->gameMode != AnalyzeMode){   //当前不是分析模式

		if(LetYqAnalizeCurPos(pDis)){

			if((SendMessage(hwndToolBar,TB_GETSTATE,IDT_ANALIZE_FUN,0) & TBSTATE_CHECKED) == FALSE){
				//再将按钮按下
				SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_ANALIZE_FUN, 1);
			}

			pDis->gameMode = AnalyzeMode;

			LogOut(_T("\n**********************\n您当前已成功进入分析模式\n**********************"));

			//将悔棋变成不可用
			SendMessage(hwndToolBar,TB_ENABLEBUTTON,IDT_HUIQI,	0);
			

			////将停止变为不可用
			//SendMessage(hwndToolBar,TB_ENABLEBUTTON,IDT_Stop,	0);			

			//将后台弹出, 并变成不可用
			pDis->mustPonder =  FALSE;
			SendMessage(hwndToolBar,TB_ENABLEBUTTON,IDT_PONDER,	0); 
	
			return TRUE;

		}
	}

	//-------------------------------------------------------------------------------------------------

	//else{
	pDis->gameMode = BeginningOfGame;

	//再将按钮弹出
	SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_ANALIZE_FUN, 0);

	//将悔棋变成可用
	SendMessage(hwndToolBar,TB_ENABLEBUTTON,IDT_HUIQI,	1);


	////将停止变为可用
	//SendMessage(hwndToolBar,TB_ENABLEBUTTON,IDT_Stop,	1);			

	//将后台变成可用
	pDis->mustPonder =  FALSE;
	SendMessage(hwndToolBar,TB_ENABLEBUTTON,IDT_PONDER,	1); 


	//如果原先后台是压下的,则要恢复一下
	if((SendMessage(hwndToolBar,TB_GETSTATE,IDT_PONDER,0) & TBSTATE_CHECKED) == TRUE){
		pDis->mustPonder =  TRUE;
	}

	ChessProgramState *cps = &pDis->first; 

	if(cps->cps_stat != Cps_Waiting){
		SendToProgram(L"stop\n", cps);
		Sleep(100);
		SendToProgram(L"stop\n", cps);
		Sleep(100);
	}


	if((SendMessage(hwndToolBar,TB_GETSTATE,IDT_ANALIZE_FUN,0) & TBSTATE_CHECKED) == TRUE){
		//再将按钮弹出
		SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_ANALIZE_FUN, 0);
	}

	pDis->gameMode = BeginningOfGame;

	LogOut(_T("\n**********************\n您当前已退出了分析模式\n**********************"));

	return TRUE;
}

