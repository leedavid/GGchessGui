#include "stdafx.h"
#include "GGchess.h"
#include <sys/stat.h>
#include <commdlg.h>
#include <dlgs.h>
#include <commctrl.h>

#include "chess.h"
#include "data.h"
#include "pregen.h"

void		   //鼠标动作程序
MouseEvent(dispboard_t* pDis,HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
	int x, y;
	POINT pt;
	//static int recursive = 0;
	HMENU hmenu;
	BOOLEAN saveAnimate;
	//static BOOLEAN sameAgain = FALSE;
    pDis->sameAgain = FALSE;
    pDis->recursive = 0;

	if (pDis->recursive) {  //递归的
		if (message == WM_MBUTTONUP) {
			/* Hideous kludge to fool TrackPopupMenu into paying attention
			to the middle button: we simulate pressing the left button too!
			*/
			PostMessage(hwnd, WM_LBUTTONDOWN, wParam, lParam);
			PostMessage(hwnd, WM_LBUTTONUP,   wParam, lParam);
		}
		return;
	}
	pDis->recursive++;

	pt.x = LOWORD(lParam);
	pt.y = HIWORD(lParam);
	x = EventToSquare_X(pt.x - pDis->boardRect.left, pDis);
	y = EventToSquare_Y(pt.y - pDis->boardRect.top,  pDis);
	if (!pDis->flipView && y >= 0) {
		y = 9 - y;

		//x = BOARD_SIZE_X - 1 - x;
	}
	if (pDis->flipView && x >= 0) {
		x = 8 - x;

		//y = 9 - y ;
	}

	switch (message) {
		case WM_LBUTTONDOWN:     //是左键按下
			//ErrorPopDown();		 //如果有错误信息对话框，则显示并关闭
			pDis->sameAgain = FALSE;
			if (y == -2) {
				//判断是不是按下了时间
				/* Downclick vertically off board; check if on clock */
				//if (PtInRect((LPRECT) &whiteRect, pt)) {
				//	if (gameMode == EditPosition) {
				//		SetWhiteToPlayEvent();
				//	} else if (gameMode == IcsPlayingBlack ||
				//		gameMode == MachinePlaysWhite) {
				//			CallFlagEvent();
				//		}
				//} else if (PtInRect((LPRECT) &blackRect, pt)) {
				//	if (gameMode == EditPosition) {
				//		SetBlackToPlayEvent();
				//	} else if (gameMode == IcsPlayingWhite ||
				//		gameMode == MachinePlaysBlack) {
				//			CallFlagEvent();
				//		}
				//}
				if (!appData.highlightLastMove) {  //如果不显示
					ClearHighlights(pDis);
					DrawPosition(pDis,false, NULL);
				}
				pDis->fromX = pDis->fromY = -1;
				pDis->dragInfo.start.x = pDis->dragInfo.start.y = -1;
				pDis->dragInfo.from = pDis->dragInfo.start;
				break;
			} 
			else if (x < 0 || y < 0) {
				break;
			} 
			else if (pDis->fromX == x && pDis->fromY == y) {  //按下了相同的棋格
				/* Downclick on same square again */
				ClearHighlights(pDis);
				DrawPosition(pDis,false, NULL);
				pDis->sameAgain = TRUE;  
			} 
            else if (pDis->fromX != -1) {// 按下了不同的棋格
                /* Downclick on different square */				   
                //sq_t pdown = DIS.boards[DIS.currentMove][FRto90(DIS.fromX,DIS.fromY)];		 //上次放的棋子
                //sq_t pup   = DIS.boards[DIS.currentMove][FRto90(x,y)];						 //这次拿的棋子

                int pdown = pDis->pos->b256[XYtoS(pDis->fromX+3,pDis->fromY+3)];
                int pup   = pDis->pos->b256[XYtoS(x+3,y+3)];
                if(pDis->gameMode == EditPosition || 
                    !( (IsBlack(pdown) && IsBlack(pup)) || (IsWhite(pdown) && IsWhite(pup)))){
                        //编辑局面，空棋格，不同的棋格，可移动哇
                        pDis->toX = x;
                        pDis->toY = y;
                        if(appData.animate || appData.highlightLastMove){
                            SetHighlights(pDis,pDis->fromX, pDis->fromY, pDis->toX, pDis->toY);
                        }
                        else{
                            ClearHighlights(pDis);
                        }
                        UserMoveEvent(pDis,pDis->fromX, pDis->fromY, pDis->toX, pDis->toY, NULLCHAR);
                        if(appData.animate && !appData.highlightLastMove){
                            ClearHighlights(pDis);
                            DrawPosition(pDis,false,NULL);
                        }
                        if(pDis->gotPremove){
                            SetPremoveHighlights(pDis,pDis->fromX,pDis->fromY,pDis->toX,pDis->toY);
                        }
                        pDis->fromX = pDis->fromY = -1;
                        break;

                }//if(gameMode == EditPosition ||
                ClearHighlights(pDis);
                DrawPosition(pDis,false, NULL);
            }//else if (fromX != -1)

			/* First downclick, or restart on a square with same color piece */
			if (!appData.Afrozen && OKToStartUserMove(pDis,x, y)) {
				pDis->fromX = x;
				pDis->fromY = y;
				pDis->dragInfo.lastpos	    = pt;
				pDis->dragInfo.from.x		= pDis->fromX;
				pDis->dragInfo.from.y		= pDis->fromY;
				pDis->dragInfo.start		    = pDis->dragInfo.from;
                SetCapture(pDis->hwndThis);
			} 
			else {
				pDis->fromX = pDis->fromY = -1;
				pDis->dragInfo.start.x = pDis->dragInfo.start.y = -1;
				pDis->dragInfo.from = pDis->dragInfo.start;
			}
			break;

		case WM_LBUTTONUP:					//左键放开
			ReleaseCapture();
			if (pDis->fromX == -1){
				break;
			}
			if (x == pDis->fromX && y == pDis->fromY) {       //按下了相同的棋格位置
				pDis->dragInfo.from.x = pDis->dragInfo.from.y = -1;
				/* Upclick on same square */
				if (pDis->sameAgain) {
					/* Clicked same square twice: abort click-click move */
					pDis->fromX = pDis->fromY = -1;
					pDis->gotPremove = 0;
					ClearPremoveHighlights(pDis);
				} 
				else {
					/* First square clicked: start click-click move */
					SetHighlights(pDis,pDis->fromX, pDis->fromY, -1, -1);
				}
				DrawPosition(pDis,false, NULL);
			} 
			else if (pDis->dragInfo.from.x < 0 || pDis->dragInfo.from.y < 0) {
				/* Errant click; ignore */
				break;
			} 
			else {
				/* Finish drag move */
				pDis->dragInfo.from.x = pDis->dragInfo.from.y = -1;
				pDis->toX = x;
				pDis->toY = y;
				saveAnimate = appData.animate; /* sorry, Hawk :) */
				appData.animate = appData.animate && !appData.animateDragging;
				
				//用户走了一步棋哇
				UserMoveEvent(pDis,pDis->fromX, pDis->fromY, pDis->toX, pDis->toY, NULLCHAR);

				if (pDis->gotPremove){
					SetPremoveHighlights(pDis,pDis->fromX, pDis->fromY, pDis->toX, pDis->toY);
				}
				appData.animate = saveAnimate;
				pDis->fromX = pDis->fromY = -1;
				if (appData.highlightDragging && !appData.highlightLastMove) {
					ClearHighlights(pDis);
				}
				if (appData.animate || appData.animateDragging ||
					appData.highlightDragging || pDis->gotPremove) {
						DrawPosition(pDis,false, NULL);
				}
			}
			pDis->dragInfo.start.x = pDis->dragInfo.start.y = -1; 
			pDis->dragInfo.pos = pDis->dragInfo.lastpos = pDis->dragInfo.start;
			break;

		case WM_MOUSEMOVE:		//鼠标移动时
			if ((appData.animateDragging || appData.highlightDragging) 
				&& (wParam & MK_LBUTTON)	&& pDis->dragInfo.from.x >= 0) {
				if (appData.animateDragging) {
					pDis->dragInfo.pos = pt;
				}
				if (appData.highlightDragging) {
					SetHighlights(pDis,pDis->fromX, pDis->fromY, x, y);
				}
				DrawPosition(pDis,false, NULL);
				pDis->dragInfo.lastpos = pDis->dragInfo.pos;
			}
			break;

		case WM_MBUTTONDOWN:
		case WM_RBUTTONDOWN:
			//ErrorPopDown();
			ReleaseCapture();
			pDis->fromX = pDis->fromY = -1;
			pDis->dragInfo.pos.x = pDis->dragInfo.pos.y = -1;
			pDis->dragInfo.start.x = pDis->dragInfo.start.y = -1;
			pDis->dragInfo.from = pDis->dragInfo.start;
			pDis->dragInfo.lastpos = pDis->dragInfo.pos;
			if (appData.highlightDragging) {
				ClearHighlights(pDis);
			}
			DrawPosition(pDis,true, NULL);

			switch (pDis->gameMode) {
				case EditPosition:
				case IcsExamining:
					if (x < 0 || y < 0) break;
					pDis->fromX = x;
					pDis->fromY = y;
					if (message == WM_MBUTTONDOWN) {
						appData.buttonCount = 3;  /* even if system didn't think so */
						if (wParam & MK_SHIFT) 
							MenuPopup(hwnd, pt, LoadMenu(hInst, _T("BlackPieceMenu")), -1);
						else
							MenuPopup(hwnd, pt, LoadMenu(hInst, _T("WhitePieceMenu")), -1);
					} else { /* message == WM_RBUTTONDOWN */
				#if 0
						if (buttonCount == 3) {
							if (wParam & MK_SHIFT) 
								MenuPopup(hwnd, pt, LoadMenu(hInst, "WhitePieceMenu"), -1);
							else
								MenuPopup(hwnd, pt, LoadMenu(hInst, "BlackPieceMenu"), -1);
						} else {
							MenuPopup(hwnd, pt, LoadMenu(hInst, "PieceMenu"), -1);
						}
				#else
						/* Just have one menu, on the right button.  Windows users don't
						think to try the middle one, and sometimes other software steals
						it, or it doesn't really exist. */
						MenuPopup(hwnd, pt, LoadMenu(hInst, _T("PieceMenu")), -1);
				#endif
					}
					break;
				case IcsPlayingWhite:
				case IcsPlayingBlack:
				case EditGame:
				case MachinePlaysWhite:
				case MachinePlaysBlack:
				case BeginningOfGame:
					//if (appData.testLegality &&
					//	DIS.pgn.variant != VariantBughouse &&
					//	DIS.pgn.variant != VariantCrazyhouse) break;
					if (x < 0 || y < 0) break;
					pDis->fromX = x;
					pDis->fromY = y;
					//hmenu = LoadMenu(hInst, _T("DropPieceMenu"));
					//SetupDropMenu(hmenu);
					//MenuPopup(hwnd, pt, hmenu, -1);
					{

						POINT pt;
						hmenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU_MAIN));
						//SendMessage(hWnd, EM_EXGETSEL, 0, (LPARAM)&sel);
						//if (sel.cpMin == sel.cpMax) {
						//	EnableMenuItem(hmenu, IDM_Copy, MF_BYCOMMAND | MF_GRAYED);
						//	EnableMenuItem(hmenu, IDM_QuickPaste, MF_BYCOMMAND | MF_GRAYED);
						//}
						//if (!IsClipboardFormatAvailable(CF_TEXT)) {
						//	EnableMenuItem(hmenu, IDM_Paste, MF_BYCOMMAND | MF_GRAYED);
						//}
						pt.x = LOWORD(lParam);
						pt.y = HIWORD(lParam);
						MenuPopup(hwnd, pt, hmenu, -1);

					}
					break;
				default:


					break;
			}
			break;
	}

	pDis->recursive--;
}



