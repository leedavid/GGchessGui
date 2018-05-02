#include "stdafx.h"
#include "GGchess.h"
#include "chess.h"
#include "data.h"
#include "pregen.h"

int str2move(position_t* pos, TCHAR *str){

	int from = (str[0] - 'a' + 3) + (('9' - str[1] + 3) * 16);
	int to   = (str[2] - 'a' + 3) + (('9' - str[3] + 3) * 16);

	int piece = pos->b256[from];
	int cap   = pos->b256[to];

	return  MOVE_FROM(from,piece,to,cap);

}

BOOL ChangeGameMode(dispboard_t *pDis, GameMode gm){
	if(gm == GameNoneMode){		//这是重新设置方式
		
		//再调整一下棋局的模式
		if(pDis->gameMode == IcsPlayingWhite || pDis->gameMode == IcsPlayingBlack){

		}
		else if(pDis->first.playWhat != NEUTRAL){
			if(pDis->first.playWhat == WHITE){
				pDis->gameMode = MachinePlaysWhite;
			}
			else {
				pDis->gameMode = MachinePlaysBlack;
			}
		}
		else{
			pDis->gameMode = EditGame;
		}
	}
	else{
		pDis->gameMode = gm;
	}

	return TRUE;
}

HANDLE				//文件名,棋格大小,
LoadChessBitmapBySize(HINSTANCE hinst, TCHAR *fileName,int squareSize){
	TCHAR buf[MSG_SIZ];
    StringCbPrintf(buf,MSG_SIZ,_T("%schessboard\\%d\\%s"),
        installDir,appData.pieceStyle,fileName);
    return LoadImage(hinst,buf,IMAGE_BITMAP,		
        squareSize,squareSize,LR_LOADFROMFILE);
}

void //得到走步的名称,
GetMoveName(position_t *pos, TCHAR* szStepName, int move, int ntype) {

	static const TCHAR*   strnumc = _T("错一二三四五六七八九");
	static const TCHAR*   strnuma = _T("０１２３４５６７８９");  // _T("０１２３４５６７８９");
	static const TCHAR*   chessname = _T("错帅仕相马车炮兵将士象马车炮卒错");  //１２３４５６７８９

	//static const TCHAR*  stQ = _T("前");
	//static const TCHAR*  stH = _T("后");
	TCHAR* stQH;


	int from = FROM(move);
	int to = TO(move);

	int piece = PIECE(move);    //这个局面已走过了哇
	int fx = StoX(from);
	int fy = StoY(from);
	int tx = StoX(to);
	int ty = StoY(to);

	bool isQH = false;             // 如果没有前后了
	uint8* board = pos->b256;

	switch (ntype) {
	case StepNameTypeA: // 正常中文显示棋步名称，为简化显示，不分先后了。 	

		if (piece == RXIANG || piece == RSHI || piece == BXIANG || piece == BSHI) {
		}
		else {

			if (IsWhite(piece)) {
				// 向上看没有棋子
				for (int y = fy - 1; y > 2; y--) {
					int sq = XYtoS(fx, y);
					if (pos->b256[sq] == piece) {
						stQH = _T("后");
						isQH = true;
						goto QH_BRANCH;
					}
				}
				for (int y = fy + 1; y < 13; y++) {
					int sq = XYtoS(fx, y);
					if (pos->b256[sq] == piece) {
						stQH = _T("前");
						isQH = true;
						goto QH_BRANCH;
					}
				}
			}
			else {
				// 向上看没有棋子
				for (int y = fy - 1; y > 2; y--) {
					int sq = XYtoS(fx, y);
					if (pos->b256[sq] == piece) {
						stQH = _T("前");
						isQH = true;
						goto QH_BRANCH;
					}
				}
				for (int y = fy + 1; y < 13; y++) {
					int sq = XYtoS(fx, y);
					if (pos->b256[sq] == piece) {
						stQH = _T("后");
						isQH = true;
						goto QH_BRANCH;
					}
				}
			}
		}

QH_BRANCH:
		if (isQH == true) { // 这个是有前后二个棋子，要区别一下。
			if (IsWhite(piece)) {
				if (ty == fy) {
					*((szStepName)) = *stQH;
					*((szStepName + 1)) = *(chessname + piece);
					*((szStepName + 2)) = L'平'; //0xbdc6; //平
					*((szStepName + 3)) = *(strnumc + 12 - tx);
				}
				else {
					*((szStepName)) = *stQH;
					*((szStepName + 1)) = *(chessname + piece);
					if (to < from) {
						*((szStepName + 2)) = L'进'; //0xf8bd; //进
					}
					else {
						*((szStepName + 2)) = L'退'; //0xcbcd; //退
					}
					if (piece == RMA || piece == RSHI || piece == RXIANG) {//马,相,仕
						*((szStepName + 3)) = *(strnumc + 12 - tx);
					}
					else {//车,兵,炮,帅
						*((szStepName + 3)) = *(strnumc + abs(fy - ty));
					}
				}
			}
			else {
				if (ty == fy) {
					*((szStepName)) = *stQH;
					*((szStepName + 1)) = *(chessname + piece);
					*((szStepName + 2)) = L'平'; //0xbdc6; //平
					*((szStepName + 3)) = *(strnuma + tx - 2);
				}
				else {
					*((szStepName)) = *stQH;
					*((szStepName + 1)) = *(chessname + piece);
					if (to > from) {
						*((szStepName + 2)) = L'进'; //0xf8bd; //进
					}
					else {
						*((szStepName + 2)) = L'退'; //0xcbcd; //退
					}
					if (piece == BMA || piece == BSHI || piece == BXIANG) {//马,相,仕
						*((szStepName + 3)) = *(strnuma + tx - 2);
					}
					else {//车,兵,炮,帅
						*((szStepName + 3)) = *(strnuma + abs(fy - ty));
					}
				}
			}
		}
		else {
			if (IsWhite(piece)) {
				// 得到棋子的前后
				if (ty == fy) {
					//得到走的棋子名称
					*((szStepName)) = *(chessname + piece);
					//得到走步的FROM数名
					*((szStepName + 1)) = *(strnumc + 12 - fx);
					*((szStepName + 2)) = L'平'; //0xbdc6; //平
					*((szStepName + 3)) = *(strnumc + 12 - tx);
				}
				else {   //y坐标不相同                    
					*((szStepName)) = *(chessname + piece);
					//得到走步的FROM数名
					*((szStepName + 1)) = *(strnumc + 12 - fx);
					//
					if (to < from) {
						*((szStepName + 2)) = L'进'; //0xf8bd; //进
					}
					else {
						*((szStepName + 2)) = L'退'; //0xcbcd; //退
					}
					if (piece == RMA || piece == RSHI || piece == RXIANG) {//马,相,仕
						*((szStepName + 3)) = *(strnumc + 12 - tx);
					}
					else {//车,兵,炮,帅
						*((szStepName + 3)) = *(strnumc + abs(fy - ty));
					}
				}
			}
			else {
				if (ty == fy) {
					//得到走的棋子名称
					*((szStepName)) = *(chessname + piece);
					//得到走步的FROM数名
					*((szStepName + 1)) = *(strnuma + fx - 2);
					*((szStepName + 2)) = L'平'; //0xbdc6; //平
					*((szStepName + 3)) = *(strnuma + tx - 2);
				}
				else {   //y坐标不相同                    
					*((szStepName)) = *(chessname + piece);
					//得到走步的FROM数名
					*((szStepName + 1)) = *(strnuma + fx - 2);
					//
					if (to > from) {
						*((szStepName + 2)) = L'进'; //0xf8bd; //进
					}
					else {
						*((szStepName + 2)) = L'退'; //0xcbcd; //退
					}
					if (piece == BMA || piece == BSHI || piece == BXIANG) {//马,相,仕
						*((szStepName + 3)) = *(strnuma + tx - 2);
					}
					else {//车,兵,炮,帅
						*((szStepName + 3)) = *(strnuma + abs(fy - ty));
					}
				}
			}
		}
		
		szStepName[4] = ' ';
		szStepName[5] = NULLCHAR;
		break;
	case StepNameTypeB:
		swprintf_s(szStepName, 16, _T("%2d-%2d"), from, to);
		szStepName[6] = 0;
	default:
		break;
	}
}

void //得到走步的名称,
GetMoveNameSimple(position_t *pos, TCHAR* szStepName, int move, int ntype){


	return GetMoveName(pos, szStepName, move, ntype);

	static const TCHAR*   strnumc = _T("错一二三四五六七八九");
	static const TCHAR*   strnuma = _T("０１２３４５６７８９");  // _T("０１２３４５６７８９");
	static const TCHAR*   chessname = _T("错帅仕相马车炮兵将士象马车炮卒错");  //１２３４５６７８９

    int from            = FROM(move);
    int to              = TO(move);

    int piece           = PIECE(move);    //这个局面已走过了哇
    int fx              = StoX(from);
    int fy              = StoY(from);
    int tx              = StoX(to);
    int ty              = StoY(to);

    uint8* board        = pos->b256;

    switch(ntype){
	case StepNameTypeA: // 正常中文显示棋步名称，为简化显示，不分先后了。 	
		if (IsWhite(piece)) {
			if (ty == fy) {
				//得到走的棋子名称
				*((szStepName)) = *(chessname + piece);
				//得到走步的FROM数名
				*((szStepName + 1)) = *(strnumc + 12 - fx);
				*((szStepName + 2)) = L'平'; //0xbdc6; //平
				*((szStepName + 3)) = *(strnumc + 12 - tx);
			}
			else {   //y坐标不相同                    
				*((szStepName)) = *(chessname + piece);
				//得到走步的FROM数名
				*((szStepName + 1)) = *(strnumc + 12 - fx);
				//
				if (to < from) {
					*((szStepName + 2)) = L'进'; //0xf8bd; //进
				}
				else {
					*((szStepName + 2)) = L'退'; //0xcbcd; //退
				}
				if (piece == RMA || piece == RSHI || piece == RXIANG) {//马,相,仕
					*((szStepName + 3)) = *(strnumc + 12 - tx);
				}
				else {//车,兵,炮,帅
					*((szStepName + 3)) = *(strnumc + abs(fy - ty));
				}
			}
		}
		else {
			if (ty == fy) {
				//得到走的棋子名称
				*((szStepName)) = *(chessname + piece);
				//得到走步的FROM数名
				*((szStepName + 1)) = *(strnuma  + fx - 2);
				*((szStepName + 2)) = L'平'; //0xbdc6; //平
				*((szStepName + 3)) = *(strnuma  + tx - 2);
			}
			else {   //y坐标不相同                    
				*((szStepName)) = *(chessname + piece);
				//得到走步的FROM数名
				*((szStepName + 1)) = *(strnuma + fx - 2);
				//
				if (to > from) {
					*((szStepName + 2)) = L'进'; //0xf8bd; //进
				}
				else {
					*((szStepName + 2)) = L'退'; //0xcbcd; //退
				}
				if (piece == BMA || piece == BSHI || piece == BXIANG) {//马,相,仕
					*((szStepName + 3)) = *(strnuma + tx - 2);
				}
				else {//车,兵,炮,帅
					*((szStepName + 3)) = *(strnuma + abs(fy - ty));
				}
			}
		}
			szStepName[4] = ' ';
			szStepName[5] = NULLCHAR;
            break;
        case StepNameTypeB:
            swprintf_s(szStepName,16,_T("%2d-%2d"),from,to);
			szStepName[6] = 0;
        default:
            break;
    }    
}

void				//显示历史棋步名称
DispHistoryStepName(dispboard_t* pDis,int moveNum){

	if(pDis->first.pDis == OBS[0]){ //是主窗口
        if(SendDlgItemMessage(STEP_MAIN,IDC_LIST_STEP_MAIN,LB_GETCOUNT,0,0) != moveNum){
            SendDlgItemMessage(STEP_MAIN,IDC_LIST_STEP_MAIN,LB_RESETCONTENT,0,0);    //清空了哇
            for(int i=0; i<moveNum; i++){
                SendDlgItemMessage(STEP_MAIN,IDC_LIST_STEP_MAIN,LB_ADDSTRING,NULL,(LPARAM)&pDis->moveListName[i]);
            }
        }
        //只要加入一个棋步就行了哇
        SendDlgItemMessage(STEP_MAIN,IDC_LIST_STEP_MAIN,LB_ADDSTRING,NULL,(LPARAM)&pDis->moveListName[moveNum]);
        SendDlgItemMessage(STEP_MAIN,IDC_LIST_STEP_MAIN,LB_SETCURSEL,moveNum,0);       //

	}
    else{                               //是其它窗口

        if(SendDlgItemMessage(pDis->hwndThis,IDC_OBS_STEPLIST,LB_GETCOUNT,0,0) != moveNum){
            SendDlgItemMessage(pDis->hwndThis,IDC_OBS_STEPLIST,LB_RESETCONTENT,0,0);    //清空了哇
            for(int i=0; i<moveNum; i++){
                SendDlgItemMessage(pDis->hwndThis,IDC_OBS_STEPLIST,LB_ADDSTRING,NULL,(LPARAM)&pDis->moveListName[i]);
            }
        }
        //只要加入一个棋步就行了哇
        SendDlgItemMessage(pDis->hwndThis,IDC_OBS_STEPLIST,LB_ADDSTRING,NULL,(LPARAM)&pDis->moveListName[moveNum]);
        SendDlgItemMessage(pDis->hwndThis,IDC_OBS_STEPLIST,LB_SETCURSEL,moveNum,0);       //
    }

}

void
AutoPlayGameLoop(dispboard_t* pDis){
    for (;;) {
        if (!AutoPlayOneMove(pDis)){
            return;
        }
        if (pDis->matchMode || appData.timeDelay == 0){
            continue;
        }
        if (appData.timeDelay < 0 ){
            return;
        }
        StartLoadGameTimer(pDis,(long)(1000.0 * appData.timeDelay));
        break;
    }
}

int							//自动走一步
AutoPlayOneMove(dispboard_t* pDis){

    int fromX, fromY, toX, toY;

#ifdef DEBUG_USE_DEBUG_FILE
    //if (appData.debugMode) {
        fprintf(appData.debugFP, "AutoPlayOneMove(): current %d\n", pDis->pos->curStep);
    //}
#endif

    if (pDis->gameMode != PlayFromGameFile)
        return FALSE;

    //if (DIS.currentMove >= DIS.forwardMostMove) {
    if(pDis->pos->curStep >= pDis->pos->gply){

        //pDis->gameMode = EditGame;

		ChangeGameMode(pDis,EditGame);

        ModeHighlight();
        return FALSE;
    }

    //toX = DIS.moveList[DIS.currentMove][2] - 'a';
    //toY = DIS.moveList[DIS.currentMove][3] - '1';
    //int curmove  = DIS.moveList[DIS.currentMove];
    //int curmove = DIS.pos.His[DIS.currentMove].move;
    int curmove = pDis->pos->His[pDis->pos->curStep].move;
    int to		= TO(curmove);
    toX			= StoX(to) - 3;
    toY			= StoY(to) - 3;

    //if (DIS.moveList[DIS.currentMove][1] == '@') {
    //	if (appData.highlightLastMove) {
    //		SetHighlights(-1, -1, toX, toY);
    //	}
    //}
    //else {
    int from	= FROM(curmove);
    fromX		= StoX(from) - 3;
    fromY		= StoY(from) - 3;

    //fromX = DIS.moveList[DIS.currentMove][0] - 'a';
    //fromY = DIS.moveList[DIS.currentMove][1] - '1';
    /*AnimateMove(DIS.pos.B256dis[DIS.currentMove], fromX, fromY, toX, toY);*/
    AnimateMove(pDis,pDis->B256dis[pDis->pos->curStep], fromX, fromY, toX, toY);

    //高亮当前的走步名称
    //SendDlgItemMessage(DLG.step,IDC_LIST_STEP,LB_SETCURSEL,DIS.currentMove,0);  

    //SendMessage(DLG.steplist,LB_SETCURSEL,DIS.currentMove,0);  

    //SendMessage(ppDis->steplist,LB_SETCURSEL,ppDis->pos.curStep,0);
	if(pDis->first.pDis == OBS[0]){ //是主窗口
        SendDlgItemMessage(STEP_MAIN,IDC_LIST_STEP_MAIN,LB_SETCURSEL,pDis->pos->curStep,0);
    }
    else{                               //是其它窗口
        SendDlgItemMessage(pDis->hwndThis,IDC_OBS_STEPLIST,LB_SETCURSEL,pDis->pos->curStep,0);
    }


    if (appData.highlightLastMove) {
        SetHighlights(pDis,fromX, fromY, toX, toY);
    }
    //}
    //DisplayMove(pDis->pos->curStep);
    //SendMoveToProgram(DIS.pos.curStep++, &DIS.first);
    DisplayBothClocks(pDis);
    DrawPosition(pDis,false, pDis->B256dis[pDis->pos->curStep]);
    //if (DIS.commentList[DIS.currentMove] != NULL) {
    //	DisplayComment(DIS.currentMove - 1, DIS.commentList[DIS.currentMove]);
    //}
    return TRUE;
}

void
EnsureOnScreen(dispboard_t* pDis, int *x, int *y)
{
    /* Be sure window at (x,y) is not off screen (or even mostly off screen) */
    if (*x > pDis->screenWidth - 32)   *x = 0;
    if (*y > pDis->screenHeight - 32)  *y = 0;
}

void
SetHighlights(dispboard_t* pDis, int fromX, int fromY, int toX, int toY){
    pDis->highlightInfo.sq[0].x = fromX;
    pDis->highlightInfo.sq[0].y = fromY;
    pDis->highlightInfo.sq[1].x = toX;
    pDis->highlightInfo.sq[1].y = toY;
}

void					//不显示高亮的棋格
ClearHighlights(dispboard_t* pDis){
        pDis->highlightInfo.sq[0].x = pDis->highlightInfo.sq[0].y = 
        pDis->highlightInfo.sq[1].x = pDis->highlightInfo.sq[1].y = -1;
}

void
SetPremoveHighlights(dispboard_t* pDis, int fromX, int fromY, int toX, int toY){
    pDis->premoveHighlightInfo.sq[0].x = fromX;
    pDis->premoveHighlightInfo.sq[0].y = fromY;
    pDis->premoveHighlightInfo.sq[1].x = toX;
    pDis->premoveHighlightInfo.sq[1].y = toY;
}

void
ClearPremoveHighlights(dispboard_t* pDis){
    pDis->premoveHighlightInfo.sq[0].x		= pDis->premoveHighlightInfo.sq[0].y = 
        pDis->premoveHighlightInfo.sq[1].x	= pDis->premoveHighlightInfo.sq[1].y = -1;
}

void 
FlipViewEvent(dispboard_t* pDis){
    pDis->flipView = !pDis->flipView;
    DrawPosition(pDis,false, NULL);
}

int
EventToSquare_X(int x, dispboard_t* pDis){
    /*
    * If the user selects on a border boundary, return -1; if off the board,
    *   return -2.  Otherwise map the event coordinate to the square.
    * The offset boardRect.left or boardRect.top must already have been
    *   subtracted from x.
    */
    if (x <= 0){
        return -2;
    }
    if (x < pDis->lineGap){
        return -1;
    }
    x -= pDis->lineGap;
    if ((x % (pDis->squareSize + pDis->lineGap)) >= pDis->squareSize){
        return -1;
    }
    x /= (pDis->squareSize + pDis->lineGap);
    if (x >= BOARD_SIZE_X){
        return -2;
    }
    return x;
}

int
EventToSquare_Y(int y, dispboard_t* pDis){
    if (y <= 0){
        return -2;
    }
    if (y < pDis->lineGap){
        return -1;
    }
    y -= pDis->lineGap;
    if ((y % (pDis->squareSize + pDis->lineGap)) >= pDis->squareSize){
        return -1;
    }
    y /= (pDis->squareSize + pDis->lineGap);
    if (y >= BOARD_SIZE_Y){
        return -2;
    }
    return 9-y;
}

void
BoardToTop(dispboard_t* pDis)
{
    if (IsIconic(pDis->hwndThis))
        ShowWindow(pDis->hwndThis, SW_RESTORE);

    SetActiveWindow(pDis->hwndThis);
}

void
DisplayError(TCHAR *str, int error){
    //FARPROC lpProc;
	TCHAR buf[MSG_SIZ * 2], buf2[MSG_SIZ];
    int len;
    //char *p;
    //char *q;

	dispboard_t *pDis = OBS[0];

    if (error == 0) {
        //strcpy(buf, str);		
        StringCbCopy(buf,MSG_SIZ*2,str);
    } 
    else {
        len = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
            NULL, error, LANG_NEUTRAL,(LPWSTR) buf2, MSG_SIZ, NULL);
        if (len > 0) {
            //sprintf(buf, "%s:\n%s", str, buf2);
            StringCbPrintf(buf,MSG_SIZ*2,_T("%s:\n%s"), str, buf2);
        } 
        else {
            ErrorMap *em = errmap;
            while (em->err != 0 && em->err != error) em++;
            if (em->err != 0) {
                //sprintf(buf, "%s:\n%s", str, em->msg);
				StringCbPrintf(buf, MSG_SIZ * 2, _T("%s:\n%s"), str, em->msg);
            } else {
                //sprintf(buf, "%s:\nError code %d", str, error);
				StringCbPrintf(buf, MSG_SIZ * 2, _T("%s:\nError code %d"), str, error);
            }
        }		
    }
    /*MessageBox(hwndMain,buf,"ErrorPopUp...",MB_OK);*/
	MessageBox(pDis->hwndThis, buf, _T("ErrorPopUp..."), MB_OK);
    //ErrorPopUp("Error", buf);
    //DispLog("ErrorPopUp...");
    //DispLog(buf);
}

void		//显示错误的参数
DisplayFatalError(TCHAR *str, int error, int exitStatus){
	 dispboard_t* pDis = OBS[0];
	 TCHAR buf[2 * MSG_SIZ], buf2[MSG_SIZ];
    int len;
	TCHAR *label = exitStatus ? _T("Fatal Error") : _T("Exiting");

    if (error != 0) {
        len = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
            NULL, error, LANG_NEUTRAL,
            (LPWSTR) buf2, MSG_SIZ, NULL);
        if (len > 0) {
            //sprintf(buf, "%s:\n%s", str, buf2);
			StringCbPrintf(buf, 2 * MSG_SIZ, _T("%s:\n%s"), str, buf2);
        } else {
            ErrorMap *em = errmap;
            while (em->err != 0 && em->err != error) em++;
            if (em->err != 0) {
                //sprintf(buf, "%s:\n%s", str, em->msg);
				StringCbPrintf(buf, 2 * MSG_SIZ, _T("%s:\n%s"), str, em->msg);
            } else {
                //sprintf(buf, "%s:\nError code %d", str, error);
				StringCbPrintf(buf, 2 * MSG_SIZ, _T("%s:\nError code %d"), str, error);
            }
        }
        str = buf;
    }
#ifdef DEBUG_USE_DEBUG_FILE
    //if (appData.debugMode) {
    fprintf(appData.debugFP, "%s: %s\n", label, str);
    //}
#endif
    if (appData.popupExitMessage) {
        //(void) MessageBox(hwndMain, str, label, MB_OK|
        //    (exitStatus ? MB_ICONSTOP : MB_ICONINFORMATION));
       (void) MessageBox(pDis->hwndThis, str, label, MB_OK|
            (exitStatus ? MB_ICONSTOP : MB_ICONINFORMATION));
    }
    //ExitEvent(exitStatus);
    int text = 0;
}

void        //连线窗口标题
DisplayTitle(dispboard_t* pDis){
    TCHAR title[MSG_SIZ]; 

	PGN* pgn = pDis->pgn;

	switch(pDis->gameMode){
		case BeginningOfGame:
		case EditGame:
		case MachinePlaysWhite:
		case MachinePlaysBlack:
			swprintf_s(title, MSG_SIZ, _T("编辑棋局")); 
			break;

		case EndOfGame:
			swprintf_s(title, MSG_SIZ, _T("棋局结束"));
			break;

		case EditPosition:	
			swprintf_s(title, MSG_SIZ, _T("编辑局面"));
			break;

		case Training:
			swprintf_s(title, MSG_SIZ, _T("教练模式"));
			break;
		case IcsIdle:
			swprintf_s(title, MSG_SIZ, _T("联网等待"));
			break; 
		case IcsPlayingWhite:
			swprintf_s(title, MSG_SIZ, _T("联网执红"));
			break;
		case IcsPlayingBlack:
			swprintf_s(title, MSG_SIZ, _T("联网执黑"));
			break;
		case IcsObserving:
			swprintf_s(title, MSG_SIZ, _T("联网旁观"));
			break;
		case IcsExamining:
			swprintf_s(title, MSG_SIZ, _T("联网测试"));
			break;
		case EditBook:
			swprintf_s(title, MSG_SIZ, _T("编辑棋库"));
			break;
		default:
			swprintf_s(title, MSG_SIZ, _T("模式有错"));
			break;
	}

	SetDlgItemText(NAME_MAIN, IDC_TIME_RED_NAME, (pgn->Red));

	SetDlgItemText(TIME_MAIN, IDC_TIME_BLACK_NAME, (pgn->Black));

    SetWindowText(pDis->hwndThis, title);
}

void			//从file 与 rank 得到当前的坐标
SquareToPos(dispboard_t* pDis,int file, int rank, int * x, int * y){
    if (pDis->flipView) { //改变上下显示了
        *x = pDis->boardRect.left + pDis->lineGap + (8-file) * (pDis->squareSize + pDis->lineGap);
        *y = pDis->boardRect.top  + pDis->lineGap + (9-rank) * (pDis->squareSize + pDis->lineGap);
    } else {      //没有改变上下显示
        *x = pDis->boardRect.left + pDis->lineGap + file * (pDis->squareSize + pDis->lineGap);
        *y = pDis->boardRect.top  + pDis->lineGap + rank * (pDis->squareSize + pDis->lineGap);
    }
}

void			//画上棋格坐标............................................
DrawCoordsOnDC(dispboard_t* pDis, HDC hdc){

	static char files[20] = {'a','b','c','d','e','f','g','h','i',
		'i','i','h','g','f','e','d','c','b','a'};
	static char ranks[20] = {'9','8','7','6','5','4','3','2','1','0',
		'0','1','2','3','4','5','6','7','8','9'};

    TCHAR str[2] = { NULLCHAR, NULLCHAR };
    int oldMode, oldAlign, x, y, start, i;
    HFONT oldFont;
    HBRUSH oldBrush;

    if (!appData.showCoords)				//如果不显示坐标
        return;

    start = pDis->flipView ? 10 : 0;

    oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(BLACK_BRUSH));
    
    /*oldMode = SetBkMode(hdc, (appData.monoMode ? OPAQUE : TRANSPARENT));*/

    oldMode = SetBkMode(hdc, (TRANSPARENT));
   
    oldAlign = GetTextAlign(hdc);

    oldFont = (HFONT)SelectObject(hdc, appData.Afont[pDis->bsize][COORD_FONT]->hf); //坐标字体

    y = pDis->boardRect.top  + pDis->lineGap;
    x = pDis->boardRect.left + pDis->lineGap;

    SetTextAlign(hdc, TA_LEFT|TA_TOP);
    for (i = 0; i < 10; i++) {
        str[0] = ranks[start + i];
        ExtTextOut(hdc, x + 2 , y + 1 + pDis->bsize/2 , 0, NULL, str, 1, NULL);
        y += pDis->squareSize + pDis->lineGap;
    }

    SetTextAlign(hdc, TA_RIGHT|TA_BOTTOM);
    for (i = 0; i < 9; i++) {
        str[0] = files[start + i];
        ExtTextOut(hdc, x + pDis->squareSize - 2, y - 1, 0, NULL, str, 1, NULL);
        x += pDis->squareSize + pDis->lineGap;
    }    

    SelectObject(hdc, oldBrush);
    SetBkMode(hdc, oldMode);
    SetTextAlign(hdc, oldAlign);
    SelectObject(hdc, oldFont);
}

void			//画上棋盘的线，与边框线
DrawGridOnDC(dispboard_t* pDis, HDC hdc,HDC tmphdc, HDC hdcmask){
    HPEN oldPen;

    int	boardWidth_x = BoardWidth_X(pDis->bsize);
    int	boardWidth_y = BoardWidth_Y(pDis->bsize);

    //画上棋盘
    SelectObject(tmphdc,(HBITMAP)pDis->chessQbBitmap);  
    BitBlt(hdc,
        pDis->boardRect.left,
        pDis->boardRect.top,
        boardWidth_x,
        boardWidth_y,
        tmphdc,0,0,SRCCOPY);

    oldPen = (HPEN)SelectObject(hdc,pDis->gridPen); 
    if(pDis->lineGap != 0){	    //画上棋格边框     //使之有立体感哇
        HPEN pen[2];			
        pen[0] = CreatePen(PS_SOLID,0,RGB(50,50,50));
        pen[1] = CreatePen(PS_SOLID,2,RGB(240,240,240));

        SelectObject(hdc,pen[0]);
        MoveToEx(hdc,pDis->boardRect.left + boardWidth_x,pDis->boardRect.top,NULL);
        LineTo(hdc,pDis->boardRect.left,pDis->boardRect.top);
        LineTo(hdc,pDis->boardRect.left,pDis->boardRect.top + boardWidth_y);

        SelectObject(hdc,pen[1]);
        LineTo(hdc,pDis->boardRect.left+boardWidth_x, 
            pDis->boardRect.top + boardWidth_y);
        LineTo(hdc,pDis->boardRect.left+boardWidth_x, 
            pDis->boardRect.top);

        DeleteObject(pen[0]);
        DeleteObject(pen[1]);	 
    }
    SelectObject(hdc,oldPen);
}

BoardSize
ParseBoardSize(TCHAR *name){
    //BoardSize bs = SizeTiny;
    int bs = SizeTiny;
    while (sizeInfo[bs].name != NULL) {
        if (StrCaseCmp(CW2A(name), CW2A(sizeInfo[bs].name)) == 0){ 
            return (BoardSize)bs;
        }

        //return (BoardSize)bs;

        bs++;
    }
    ExitArgError(_T("Unrecognized board size value"), (name));
    return (BoardSize)bs; /* not reached */
}

void			//重新更新棋盘大小 /* Respond to board resize by dragging edge */
ResizeBoard(dispboard_t* pDis, int newSizeX, int newSizeY, int flags){
    int newSize = NUM_SIZES - 1;
    static int recurse = 0;
    /*if (IsIconic(hwndMain)) return;*/
    if (IsIconic(pDis->hwndThis)) return;
    if (recurse > 0) return;
    recurse++;
    while (newSize > 0 &&
        (newSizeX < sizeInfo[newSize].cliWidth - 4 ||
        newSizeY < sizeInfo[newSize].cliHeight - 4)) {
            newSize--;
    } 
    pDis->bsize = (BoardSize)newSize;
    InitDrawingSizes(pDis, pDis->bsize, flags);
    recurse--;
}

void            //根据棋盘大小，更新相应的数据变量
InitDrawingSizes(dispboard_t* pDis,int boardSize, int flags){
    //int i;
    int boardWidth_x;
    int boardWidth_y;
    //sint8 piece;
    static int oldBoardSize = -1, oldTinyLayout = 0;
    //HDC hdc;
    //SIZE clockSize, messageSize;  //这个不用，写在旁边了
    //SIZE messageSize;
    //HFONT oldFont;
    TCHAR buf[MSG_SIZ];
    //char *str;
    /*HMENU hmenu = GetMenu(hwndMain);*/
    HMENU hmenu = GetMenu(pDis->hwndThis);
    RECT crect, wrect;
    int offby;
    LOGBRUSH logbrush;

    pDis->tinyLayout  = sizeInfo[boardSize].tinyLayout;
    pDis->smallLayout = sizeInfo[boardSize].smallLayout;
    pDis->squareSize  = sizeInfo[boardSize].squareSize;
    pDis->lineGap     = sizeInfo[boardSize].lineGap;

    if (pDis->tinyLayout != oldTinyLayout) {
    }

    boardWidth_x = BoardWidth_X(boardSize);	 //棋盘的宽度
    boardWidth_y = BoardWidth_Y(boardSize);  //棋盘的高度，

    //boardRect.left = whiteRect.left;		
    pDis->boardRect.left   = OUTER_MARGIN;							//显示区域的大小
    pDis->boardRect.right  = pDis->boardRect.left + boardWidth_x;
    //boardRect.top    = messageRect.bottom + INNER_MARGIN;
    pDis->boardRect.top    = 30 + INNER_MARGIN;						//空上上面的工具条
    pDis->boardRect.bottom = pDis->boardRect.top  + boardWidth_y;

    sizeInfo[boardSize].cliWidth  = pDis->boardRect.right + OUTER_MARGIN;
    sizeInfo[boardSize].cliHeight = pDis->boardRect.bottom + OUTER_MARGIN;
    //DIS.winWidth = 2 * GetSystemMetrics(SM_CXFRAME) + DIS.boardRect.right + OUTER_MARGIN;
    /*GetClientRect(hwndMain, &crect);*/
    GetClientRect(pDis->hwndThis, &crect);

    pDis->winHeight = 2 * GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYMENU) +
        GetSystemMetrics(SM_CYCAPTION) + pDis->boardRect.bottom + OUTER_MARGIN + 4;
    offby = pDis->boardRect.bottom + OUTER_MARGIN - crect.bottom;

    pDis->winWidth  = 2 * GetSystemMetrics(SM_CXFRAME) + pDis->boardRect.right + OUTER_MARGIN + 4;

    /*GetWindowRect(hwndMain, &wrect);*/

    GetWindowRect(pDis->hwndThis, &wrect);

   SetWindowPos(pDis->hwndThis, NULL, 0, 0, pDis->winWidth, pDis->winHeight,
        SWP_NOCOPYBITS|SWP_NOZORDER|SWP_NOMOVE);
    /* compensate if menu bar wrapped */
   /* GetClientRect(hwndMain, &crect);*/

   GetClientRect(pDis->hwndThis, &crect);

    offby = pDis->boardRect.bottom + OUTER_MARGIN - crect.bottom;
    pDis->winHeight += offby + 18;

    switch (flags) {
        case WMSZ_TOPLEFT:
            //SetWindowPos(hwndMain, NULL, 
            //    wrect.right - ppDis->winWidth, wrect.bottom - ppDis->winHeight, 
            //    ppDis->winWidth, ppDis->winHeight, 
            //    SWP_NOCOPYBITS|SWP_NOZORDER);
            SetWindowPos(pDis->hwndThis, NULL, 
                wrect.right - pDis->winWidth, wrect.bottom - pDis->winHeight, 
                pDis->winWidth, pDis->winHeight, 
                SWP_NOCOPYBITS|SWP_NOZORDER);
            break;

        case WMSZ_TOPRIGHT:
        case WMSZ_TOP:
            /*SetWindowPos(hwndMain, NULL, 
                wrect.left, wrect.bottom - ppDis->winHeight, 
                ppDis->winWidth, ppDis->winHeight, SWP_NOCOPYBITS|SWP_NOZORDER);*/
            SetWindowPos(pDis->hwndThis, NULL, 
                wrect.left, wrect.bottom - pDis->winHeight, 
                pDis->winWidth, pDis->winHeight, SWP_NOCOPYBITS|SWP_NOZORDER);
            break;

        case WMSZ_BOTTOMLEFT:
        case WMSZ_LEFT:
           SetWindowPos(pDis->hwndThis, NULL, 
                wrect.right - pDis->winWidth, wrect.top, 
                pDis->winWidth, pDis->winHeight,
                SWP_NOCOPYBITS|SWP_NOZORDER);
            //SetWindowPos(hwndMain, NULL, 
            //    wrect.right - ppDis->winWidth, wrect.top, 
            //    ppDis->winWidth, ppDis->winHeight,
            //    SWP_NOCOPYBITS|SWP_NOZORDER);
            break;

        case WMSZ_BOTTOMRIGHT:
        case WMSZ_BOTTOM:
        case WMSZ_RIGHT:
        default:
            /*SetWindowPos(hwndMain, NULL, 0, 0, ppDis->winWidth, ppDis->winHeight,
                SWP_NOCOPYBITS|SWP_NOZORDER|SWP_NOMOVE);*/
            SetWindowPos(pDis->hwndThis, NULL, 0, 0, pDis->winWidth, pDis->winHeight,
                SWP_NOCOPYBITS|SWP_NOZORDER|SWP_NOMOVE);
            break;
    }

    //ppDis->hwndPause = NULL;    
    if (pDis->gridPen != NULL) DeleteObject(pDis->gridPen);
    if (pDis->highlightPen != NULL) DeleteObject(pDis->highlightPen);
    if (pDis->premovePen != NULL) DeleteObject(pDis->premovePen);
    if (pDis->lineGap != 0) {
        logbrush.lbStyle = BS_SOLID;
        logbrush.lbColor = RGB(0, 0, 0); /* grid pen color = black */
        pDis->gridPen =
            ExtCreatePen(PS_GEOMETRIC|PS_SOLID|PS_ENDCAP_FLAT|PS_JOIN_MITER,
            pDis->lineGap, &logbrush, 0, NULL);
        logbrush.lbColor = appData.AhighlightSquareColor;
        pDis->highlightPen =
            ExtCreatePen(PS_GEOMETRIC|PS_SOLID|PS_ENDCAP_FLAT|PS_JOIN_MITER,
            pDis->lineGap, &logbrush, 0, NULL);

        logbrush.lbColor = appData.ApremoveHighlightColor; 
        pDis->premovePen =
            ExtCreatePen(PS_GEOMETRIC|PS_SOLID|PS_ENDCAP_FLAT|PS_JOIN_MITER,
            pDis->lineGap, &logbrush, 0, NULL);
    }   

    //**********************************************
    if (boardSize == oldBoardSize){
        return;
    }
    oldBoardSize =  boardSize;
    oldTinyLayout = pDis->tinyLayout;

    /* Load piece bitmaps for this board size */
    /* 根据棋盘的大小调用相应的棋子           */
    for(int i=0; i<15; i++){
        if(pDis->pieceBitmap[i] != NULL){
            DeleteObject(pDis->pieceBitmap[i]);
        }
    }
    //棋盘		
    if(pDis->chessQbBitmap != NULL){
        DeleteObject(pDis->chessQbBitmap);
    }
    StringCbPrintf(buf,MSG_SIZ,_T("%schessboard\\%d\\qp.bmp"),
        installDir,appData.pieceStyle);
    //int x = squareSize * 9;		//棋盘大小
    //int y = squareSize * 10;
    pDis->chessQbBitmap = LoadImage(hInst,buf,IMAGE_BITMAP,
        boardWidth_x,
        boardWidth_y,
        LR_LOADFROMFILE);	
    if(pDis->piecePickFromBitmap != NULL){
        DeleteObject(pDis->piecePickFromBitmap);
    }
    pDis->piecePickFromBitmap 
		= LoadChessBitmapBySize(hInst, L"p.bmp", pDis->squareSize);		//拿起棋子的地方
    if(pDis->piecePutDownBitmap != NULL){
        DeleteObject(pDis->piecePutDownBitmap);
    }
    pDis->piecePutDownBitmap
		= LoadChessBitmapBySize(hInst, L"f.bmp", pDis->squareSize);		//拿起棋子的地方

    if(pDis->chessMask != NULL){
        DeleteObject(pDis->chessMask);
    }
	pDis->chessMask = LoadChessBitmapBySize(hInst, L"mask.bmp", pDis->squareSize);//拿起棋子的地方
    if(pDis->chessInve != NULL){
        DeleteObject(pDis->chessInve);
    }
	pDis->chessInve = LoadChessBitmapBySize(hInst, L"inve.bmp", pDis->squareSize);


    //红棋棋子*************************************
    pDis->pieceBitmap[RPAWN] 
    = LoadChessBitmapBySize(hInst,L"rpawn.bmp",pDis->squareSize);		//兵
    pDis->pieceBitmap[RPAO]		
		= LoadChessBitmapBySize(hInst, L"rpao.bmp", pDis->squareSize);		//炮
    pDis->pieceBitmap[RCHE] 
		= LoadChessBitmapBySize(hInst, L"rche.bmp", pDis->squareSize);
    pDis->pieceBitmap[RMA] 
		= LoadChessBitmapBySize(hInst, L"rma.bmp", pDis->squareSize);
    pDis->pieceBitmap[RXIANG] 
		= LoadChessBitmapBySize(hInst, L"rxiang.bmp", pDis->squareSize);
    pDis->pieceBitmap[RSHI] 
		= LoadChessBitmapBySize(hInst, L"rshi.bmp", pDis->squareSize);
    pDis->pieceBitmap[RKING] 
		= LoadChessBitmapBySize(hInst, L"rking.bmp", pDis->squareSize);
    //黑棋棋子**************************************
    pDis->pieceBitmap[BPAWN] 
		= LoadChessBitmapBySize(hInst, L"bpawn.bmp", pDis->squareSize);
    pDis->pieceBitmap[BPAO] 
		= LoadChessBitmapBySize(hInst, L"bpao.bmp", pDis->squareSize);
    pDis->pieceBitmap[BCHE] 
		= LoadChessBitmapBySize(hInst, L"bche.bmp", pDis->squareSize);
    pDis->pieceBitmap[BMA] 
		= LoadChessBitmapBySize(hInst, L"bma.bmp", pDis->squareSize);
    pDis->pieceBitmap[BXIANG] 
		= LoadChessBitmapBySize(hInst, L"bxiang.bmp", pDis->squareSize);
    pDis->pieceBitmap[BSHI] 
		= LoadChessBitmapBySize(hInst, L"bshi.bmp", pDis->squareSize);
    pDis->pieceBitmap[BKING] 
		= LoadChessBitmapBySize(hInst, L"bking.bmp", pDis->squareSize);
}

int
BoardWidth_X(int boardSize){
    return (BOARD_SIZE_X + 1) * sizeInfo[boardSize].lineGap +
        BOARD_SIZE_X * sizeInfo[boardSize].squareSize;
}

int
BoardWidth_Y(int boardSize){
    return (BOARD_SIZE_Y + 1) * sizeInfo[boardSize].lineGap +
        BOARD_SIZE_Y * sizeInfo[boardSize].squareSize;
}

void      //复制棋盘
CopyBoard(uint8* target,uint8* src){
    memcpy(target,src,256);
}

int		//比较两个棋盘
CompareBoards(uint8* board1, uint8*  board2){
    for(int i=0x33; i<0xcc; i++){
        if(board1[i] != board2[i]){
            return FALSE;
        }
    }
    return TRUE;
}

VOID
DisplayMoveError(dispboard_t* pDis, TCHAR *str){
    pDis->fromX = pDis->fromY = -1;
    ClearHighlights(pDis);
    DrawPosition(pDis,false, NULL);
    if (appData.popupMoveErrors) {
        //ErrorPopUp(L"Error", str);
    } 
    else {

        TCHAR buf[MSG_SIZ];
        swprintf_s(buf,MSG_SIZ,_T("\n走步错误: %s\n"), str);
        LogOut(buf);
    }
}

void
DisplayMessage(dispboard_t* pDis, TCHAR *str1, TCHAR *str2){
    int remain = MESSAGE_TEXT_MAX - 1;
    int len;

    //ppDis->moveErrorMessageUp = FALSE; /* turned on later by caller if needed */
    pDis->messageText[0] = NULLCHAR;
    if (*str1) {
        len = (int)wcslen(str1);
        if (len > remain){
            len = remain;
        }
        wcsncpy_s(pDis->messageText,sizeof(pDis->messageText),str1, len);
        pDis->messageText[len] = NULLCHAR;
        remain -= len;
    }
    if (*str2 && remain >= 2) {
        if (*str1) {
            wcscat_s(pDis->messageText,MESSAGE_TEXT_MAX,_T("  "));
            remain -= 2;
        }
        len = (int)wcslen(str2);
        if (len > remain) len = remain;	
        wcsncat_s(pDis->messageText,sizeof(pDis->messageText), str2, len);
    }
    pDis->messageText[MESSAGE_TEXT_MAX - 1] = NULLCHAR;

    StringCbCat(pDis->messageText,sizeof(pDis->messageText),_T("\n"));
    LogOut(pDis->messageText);
}

void  /*      Convert board position to corner of screen rect and color       */
ScreenSquare(dispboard_t* pDis, int x, int y,POINT * pt){
    if (!pDis->flipView) {
        pt->x = pDis->lineGap + ((BOARD_SIZE_X-1)-x) * (pDis->squareSize + pDis->lineGap);
        pt->y = pDis->lineGap + y * (pDis->squareSize + pDis->lineGap);
    } 
    else {
        pt->x = pDis->lineGap + x * (pDis->squareSize + pDis->lineGap);
        pt->y = pDis->lineGap + ((BOARD_SIZE_Y-1)-y) * (pDis->squareSize + pDis->lineGap);
    }
}

/*      Generate a series of frame coords from start->mid->finish.
The movement rate doubles until the half way point is
reached, then halves back down to the final destination,
which gives a nice slow in/out effect. The algorithmn
may seem to generate too many intermediates for short
moves, but remember that the purpose is to attract the
viewers attention to the piece about to be moved and
then to where it ends up. Too few frames would be less
noticeable.                                             */

void
Tween(POINT *start,POINT * mid, POINT *finish,int factor,POINT frames[],int *nFrames){
    int n, fraction = 1, count = 0;

    /* Slow in, stepping 1/16th, then 1/8th, ... */
    for (n = 0; n < factor; n++)
        fraction *= 2;
    for (n = 0; n < factor; n++) {
        frames[count].x = start->x + (mid->x - start->x) / fraction;
        frames[count].y = start->y + (mid->y - start->y) / fraction;
        count ++;
        fraction = fraction / 2;
    }

    /* Midpoint */
    frames[count] = *mid;
    count ++;

    /* Slow out, stepping 1/2, then 1/4, ... */
    fraction = 2;
    for (n = 0; n < factor; n++) {
        frames[count].x = finish->x - (finish->x - mid->x) / fraction;
        frames[count].y = finish->y - (finish->y - mid->y) / fraction;
        count ++;
        fraction = fraction * 2;
    }
    *nFrames = count;
}

void				//画上高亮的棋格
DrawHighlightOnDC(dispboard_t* pDis, HDC hdc, BOOLEAN on, int x, int y, int pen){
    int x1, y1;
    HPEN oldPen, hPen;
    if (pDis->lineGap == 0){
        return;
    }
    if (pDis->flipView) {
        x1 = pDis->boardRect.left +
            pDis->lineGap/2 + (8-x) * (pDis->squareSize + pDis->lineGap);
        y1 = pDis->boardRect.top +
            pDis->lineGap/2 + (9-y) * (pDis->squareSize + pDis->lineGap);
    } 
    else {
        x1 = pDis->boardRect.left +
            pDis->lineGap/2 + x * (pDis->squareSize + pDis->lineGap);
        y1 = pDis->boardRect.top +
            pDis->lineGap/2 + y * (pDis->squareSize + pDis->lineGap);
    }
    hPen = pen ? pDis->premovePen : pDis->highlightPen;
    oldPen = (HPEN)SelectObject(hdc, on ? hPen : pDis->gridPen);
    MoveToEx(hdc, x1, y1, NULL);
    LineTo(hdc, x1 + pDis->squareSize + pDis->lineGap, y1);
    LineTo(hdc, x1 + pDis->squareSize + pDis->lineGap, y1 + pDis->squareSize + pDis->lineGap);
    LineTo(hdc, x1, y1 + pDis->squareSize + pDis->lineGap);
    LineTo(hdc, x1, y1);
    SelectObject(hdc, oldPen);
}

BOOL			//将窗口
CenterWindow (HWND hwndChild, HWND hwndParent) {
    RECT    rChild, rParent;
    int     wChild, hChild, wParent, hParent;
    int     wScreen, hScreen, xNew, yNew;
    HDC     hdc;

    /* Get the Height and Width of the child window */
    GetWindowRect (hwndChild, &rChild);
    wChild = rChild.right - rChild.left;
    hChild = rChild.bottom - rChild.top;

    /* Get the Height and Width of the parent window */
    GetWindowRect (hwndParent, &rParent);
    wParent = rParent.right - rParent.left;
    hParent = rParent.bottom - rParent.top;

    /* Get the display limits */
    hdc = GetDC (hwndChild);
    wScreen = GetDeviceCaps (hdc, HORZRES);
    hScreen = GetDeviceCaps (hdc, VERTRES);
    ReleaseDC(hwndChild, hdc);

    /* Calculate new X position, then adjust for screen */
    xNew = rParent.left + ((wParent - wChild) /2);
    if (xNew < 0) {
        xNew = 0;
    } else if ((xNew+wChild) > wScreen) {
        xNew = wScreen - wChild;
    }

    /* Calculate new Y position, then adjust for screen */
    yNew = rParent.top  + ((hParent - hChild) /2);
    if (yNew < 0) {
        yNew = 0;
    } else if ((yNew+hChild) > hScreen) {
        yNew = hScreen - hChild;
    }

    /* Set it, and return */
    return SetWindowPos (hwndChild, NULL,
        xNew, yNew, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}


int				//从x,y 得到棋盘上的棋子
PieceForSquare (dispboard_t* pDis, int x,int y){
    if(x<0 || x >= BOARD_SIZE_X || y<0 || y >= BOARD_SIZE_Y){
        return -1;
    }
    else{
        /* return DIS.pos.B256dis[DIS.currentMove][XYtoS(x+3,y+3)];*/
        return pDis->B256dis[pDis->pos->curStep][XYtoS(x+3,y+3)];
    }
}

int						//用户可以开始走棋了..........
OKToStartUserMove(dispboard_t* pDis,int x,int y){

    int from_piece;
    int white_piece;

    if (pDis->matchMode){
        return FALSE;
    }
    if (pDis->gameMode == EditPosition){
        return TRUE;
    }

    if (x >= 0 && y >= 0){
        from_piece = pDis->B256dis[pDis->pos->curStep][XYtoS(x+3,y+3)];
    }
    else{
        from_piece = EMPTY;
    }

    if (from_piece == EMPTY){
        return FALSE;
    }

    white_piece = IsWhite(from_piece);			//是否走的是白棋

    switch (pDis->gameMode) {
      case PlayFromGameFile:
      case EndOfGame:
          return FALSE;

      case IcsObserving:
      case IcsIdle:
          return FALSE;

      case MachinePlaysWhite:
      case IcsPlayingBlack:		 
          if (white_piece) {
			  DisplayMoveError(pDis, L"You are playing Black");
              return FALSE;
          }
          break;

      case MachinePlaysBlack:
      case IcsPlayingWhite:		 
          if (!white_piece) {
			  DisplayMoveError(pDis, L"You are playing White");
              return FALSE;
          }
          break;

      case EditGame:
          //if (!white_piece && WhiteOnMove(DIS.currentMove)) {
          if(!white_piece && (pDis->pos->side == WHITE)){
			  DisplayMoveError(pDis, L"It is White's turn");
              return FALSE;
          }	    
          /*if (white_piece && !WhiteOnMove(DIS.currentMove)) {*/
          if (white_piece && !(pDis->pos->side == WHITE)) {
			  DisplayMoveError(pDis, L"It is Black's turn");
              return FALSE;
          }	    
          //if (DIS.cmailMsgLoaded && (DIS.currentMove < DIS.cmailOldMove)) {
          //    /* Editing correspondence game history */
          //    /* Could disallow this or prompt for confirmation */
          //    DIS.cmailOldMove = -1;
          //}
          /*if (DIS.currentMove < DIS.forwardMostMove) {*/
          if (pDis->pos->curStep < pDis->pos->gply) {
              /* Discarding moves */
              /* Could prompt for confirmation here,
              but I don't think that's such a good idea */
              //DIS.forwardMostMove = DIS.currentMove;
              pDis->pos->gply = pDis->pos->curStep;
          }
          break;

      case BeginningOfGame:
          if (appData.icsActive) return FALSE;
          //if (!pDis->noChessProgram) {
              if (!white_piece) {
				  DisplayMoveError(pDis, L"You are playing White");
                  return FALSE;
              }
          //}
          break;

      case Training:
          /*if (!white_piece && WhiteOnMove(DIS.currentMove)) {*/
          if (!white_piece && (pDis->pos->side == WHITE)) {
			  DisplayMoveError(pDis, L"It is White's turn");
              return FALSE;
          }	    
          //if (white_piece && !WhiteOnMove(DIS.currentMove)) {
          if (white_piece && !(pDis->pos->side == WHITE)) {
			  DisplayMoveError(pDis, L"It is Black's turn");
              return FALSE;
          }	    
          break;

      default:
      case IcsExamining:
          break;
    }
    /*if (DIS.currentMove != DIS.forwardMostMove && DIS.gameMode != AnalyzeMode*/
  //  if (pDis->pos->curStep != pDis->pos->gply && pDis->gameMode != AnalyzeMode
		//&& pDis->gameMode != AnalyzeFile && pDis->gameMode != Training ) {
  //          DisplayMoveError(pDis, "Displayed position is not current");
  //          return FALSE;
  //  }

	if (pDis->pos->curStep != pDis->pos->gply && pDis->gameMode != AnalyzeMode && pDis->gameMode != Training ) {
		DisplayMoveError(pDis, L"Displayed position is not current");
			return FALSE;
	}
	//else{
	//	ppDis->pos->gply = ppDis->pos->curStep;
	//}
    return TRUE;
}

