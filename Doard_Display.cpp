#include "stdafx.h"
#include "GGchess.h"
#include <sys/stat.h>
#include <commdlg.h>
#include <dlgs.h>
#include <commctrl.h>

#include "chess.h"
#include "data.h"
#include "pregen.h"

void	/* Updates currentMove if not pausing */
ShowMove(dispboard_t* pDis,int fromX, int fromY, int toX,int toY){
    int instant = (pDis->gameMode == PlayFromGameFile) ?
        (pDis->matchMode || (appData.timeDelay == 0 && !pDis->pausing)) : pDis->pausing;
    if (!pDis->pausing  ) {
        if (!instant) {
            /*if (DIS.forwardMostMove == DIS.currentMove + 1) {*/
            if (pDis->pos->gply == pDis->pos->curStep + 1) {
                //AnimateMove(DIS.boards[DIS.forwardMostMove - 1], fromX, fromY, toX, toY);
                //AnimateMove(&DIS.pos, fromX, fromY, toX, toY);
                /*AnimateMove(DIS.pos.B256dis[DIS.forwardMostMove - 1], fromX, fromY, toX, toY);*/
                AnimateMove(pDis,pDis->B256dis[pDis->pos->gply - 1], fromX, fromY, toX, toY);
            }
            if (appData.highlightLastMove) {
                SetHighlights(pDis, fromX, fromY, toX, toY);
            }
        }
        //DIS.currentMove = DIS.forwardMostMove;
        pDis->pos->curStep = pDis->pos->gply;
    }

    if (instant){
        return;
    }
    //DisplayMove(DIS.currentMove - 1);
    //DisplayMove(pDis->pos->curStep - 1);
    /*DrawPosition(false,DIS.pos.B256dis[DIS.currentMove]);*/
    DrawPosition(pDis,false,pDis->B256dis[pDis->pos->curStep]);

    if (!pDis->pausing && appData.ringBellAfterMoves) {
        /*if(DIS.pos.His[DIS.currentMove].ischeck != 0){*/
        if(pDis->pos->His[pDis->pos->curStep].ischeck != 0){

			//cps->UCCI_otherString

   //         if(pDis->first.UCCI_otherString[0] != '1'){
			//	appData.PlaySoundNum = 0;
			//}
			//else{
			//	appData.PlaySoundNum = 1;
			//	/*PlayCheckSound*/(); //将军的声音
			//}

            
        }
        /*else if(CAPTURE(DIS.pos.His[DIS.currentMove].move) != 0){*/
        else if(CAPTURE(pDis->pos->His[pDis->pos->curStep].move) != 0){

			if(pDis->first.UCCI_otherString[0] != '1'){
				appData.PlaySoundNum = 0;
			}
			else{
				appData.PlaySoundNum = 1;
				//PlayEatSound();  //吃子的声音  MessageBeep(MB_ICONEXCLAMATION);
			}

            //PlayEatSound();  //吃子的声音  MessageBeep(MB_ICONEXCLAMATION);
        }
        else{


			//if(pDis->first.UCCI_otherString[0] != '1'){
			//	appData.PlaySoundNum = 0;
			//}
			//else{
			//	appData.PlaySoundNum = 1;
			//	//RingBell();      //走步的声音  MessageBeep(MB_OK);
			//}

			//MessageBeep(MB_ICONEXCLAMATION);
        }
    }
    //if(pDis->noChessProgram == FALSE){ //当前有象棋引擎在运行哇
    //    //if(WhiteOnMove(DIS.currentMove)){
    //    //    //DisLogYQBClear();
    //    //}
    //    //else{
    //    //    //DisLogYQAClear();
    //    //}
    //    if(pDis->pos->side == WHITE){
    //    }
    //    else{
    //    }
    //}

    DisplayBothClocks(pDis);
    //HistorySet(DIS.parseList,DIS.backwardMostMove,DIS.forwardMostMove,DIS.currentMove-1);

	//PaintChartProc(pDis, TAB.dlgScore);

	
}


void            //显示
HDCDrawPosition(dispboard_t* pDis, HDC hdc, BOOLEAN repaint, uint8* B256){

 //   static uint8  lastReq[256];
 //   static uint8  lastDrawn[256];

	//static HighlightInfo lastDrawnHighlight;
	//static HighlightInfo lastDrawnPremove;
	//static int lastDrawnFlipView = 0;
	//static int lastReqValid = 0;
	//static int lastDrawnValid = 0;


	int releaseDC;
	int x, y;
	int x2, y2;
	int num_clips = 0;
	int i;
	HDC tmphdc;
	HDC hdcmem;
	HBITMAP bufferBitmap;
	HBITMAP oldBitmap;
	RECT Rect;
	HRGN clips[MAX_CLIPS];
	sq_t dragged_piece = EMPTY;		//走动的棋子

	/* I'm undecided on this - this function figures out whether a full
	* repaint is necessary on its own, so there's no real reason to have the
	* caller tell it that.  I think this can safely be set to FALSE - but
	* if we trust the callers not to request full repaints unnessesarily, then
	* we could skip some clipping work.  In other words, only request a full
	* redraw when the majority of pieces have changed positions (ie. flip, 
	* gamestart and similar)  --Hawk
	*/
	// 翻转棋盘，游戏开始，或其它时要全部更新，其它是false
	Boolean fullrepaint = repaint;		//是否要重新全部显示

	if (B256 == NULL) {				//如果没有输入要显示的棋盘
		if (!pDis->lastReqValid) {
			return;
		}
		B256 = pDis->lastReq;
	} 
	else {
        CopyBoard(pDis->lastReq, B256);	   //复制一下
		pDis->lastReqValid = 1;
	}

	if (pDis->doingSizing) {
		return;
	}

	//if (IsIconic(hwndMain)) {		//如果当前是图标化了
    if (IsIconic(pDis->hwndThis)) {		//如果当前是图标化了
		return;
	}

	if (hdc == NULL) {
		/*hdc = GetDC(hwndMain);*/
        hdc = GetDC(pDis->hwndThis);

		//if (!appData.monoMode) {  //不是黑白显示的话
			SelectPalette(hdc, pDis->hPal, FALSE);
			RealizePalette(hdc);
		//}

		releaseDC = TRUE;
	} 
	else {
		releaseDC = FALSE;
	}


	/* Create some work-DCs */
	hdcmem = CreateCompatibleDC(hdc);
	tmphdc = CreateCompatibleDC(hdc);
    HDC hdcmask = CreateCompatibleDC(hdc);
	

	/* Figure out which squares need updating by comparing the 
	* newest board with the last drawn board and checking if
	* flipping has changed.
	*/
	//计算一下那些棋格要更新,与上一次的棋盘相比较
	if (!fullrepaint && pDis->lastDrawnValid && pDis->lastDrawnFlipView == pDis->flipView) {
		for(i=0x33;i<0xcc; i++){      //90个棋子那个要更新
			if(pDis->lastDrawn[i] != B256[i]){
				//SquareToPos(S90toF(i),S90toR(i),&x,&y); 

                SquareToPos(pDis,StoX(i)-3,StoY(i)-3,&x,&y);
				clips[num_clips++] = CreateRectRgn(x,y,x+pDis->squareSize,y+pDis->squareSize);
			}
		}
		for (i=0; i<2; i++) {
			if (pDis->lastDrawnHighlight.sq[i].x != pDis->highlightInfo.sq[i].x ||
				pDis->lastDrawnHighlight.sq[i].y != pDis->highlightInfo.sq[i].y) {
				if (pDis->lastDrawnHighlight.sq[i].x >= 0 && pDis->lastDrawnHighlight.sq[i].y >= 0) {
					SquareToPos(pDis,pDis->lastDrawnHighlight.sq[i].x,
						pDis->lastDrawnHighlight.sq[i].y, &x, &y);
					clips[num_clips++] =
						CreateRectRgn(x - pDis->lineGap, y - pDis->lineGap, 
						x + pDis->squareSize + pDis->lineGap,
						y + pDis->squareSize + pDis->lineGap);
				}
				if (pDis->highlightInfo.sq[i].x >= 0 	&& pDis->highlightInfo.sq[i].y >= 0) {
					SquareToPos(pDis,pDis->highlightInfo.sq[i].x, 
						pDis->highlightInfo.sq[i].y, &x, &y);
					clips[num_clips++] =
						CreateRectRgn(x - pDis->lineGap, y - pDis->lineGap, 
						x + pDis->squareSize + pDis->lineGap,
						y + pDis->squareSize + pDis->lineGap);
				}
			}
		}
		for (i=0; i<2; i++) {
			if (pDis->lastDrawnPremove.sq[i].x != pDis->premoveHighlightInfo.sq[i].x ||
				pDis->lastDrawnPremove.sq[i].y != pDis->premoveHighlightInfo.sq[i].y) {
				if (pDis->lastDrawnPremove.sq[i].x >= 0 && pDis->lastDrawnPremove.sq[i].y >= 0) {
					SquareToPos(pDis,pDis->lastDrawnPremove.sq[i].x,
						pDis->lastDrawnPremove.sq[i].y, &x, &y);
					clips[num_clips++] =
						CreateRectRgn(x - pDis->lineGap, y - pDis->lineGap, 
						x + pDis->squareSize + pDis->lineGap, 
						y + pDis->squareSize + pDis->lineGap);
				}
				if (pDis->premoveHighlightInfo.sq[i].x >= 0 && pDis->premoveHighlightInfo.sq[i].y >= 0) {
					SquareToPos(pDis,pDis->premoveHighlightInfo.sq[i].x, 
						pDis->premoveHighlightInfo.sq[i].y, &x, &y);
					clips[num_clips++] =
						CreateRectRgn(x - pDis->lineGap, y - pDis->lineGap, 
						x + pDis->squareSize + pDis->lineGap,
						y + pDis->squareSize + pDis->lineGap);
				}
			}
		}
	}			//if (!fullrepaint && lastDrawnValid && lastDrawnFlipView == DIS.flipView) {
	else{
		fullrepaint = TRUE;
	}
	
	/* Create a buffer bitmap - this is the actual bitmap
	* being written to.  When all the work is done, we can
	* copy it to the real DC (the screen).  This avoids
	* the problems with flickering.
	*/
	//建立一个缓冲图像,我们在上面做全部工作,然后再写到屏幕上,可避免闪烁
	//GetClientRect(hwndMain,&Rect);
    GetClientRect(pDis->hwndThis,&Rect);
	bufferBitmap = CreateCompatibleBitmap(hdc, Rect.right-Rect.left+1,
					Rect.bottom-Rect.top+1);
	oldBitmap = (HBITMAP)SelectObject(hdcmem, bufferBitmap);

	SelectPalette(hdcmem, pDis->hPal, FALSE);


	/* Create clips for dragging */  //找出要更新的区域
	if (!fullrepaint) {
		if (pDis->dragInfo.from.x >= 0) {
			SquareToPos(pDis,pDis->dragInfo.from.x, pDis->dragInfo.from.y, &x, &y);
			clips[num_clips++] = CreateRectRgn(x, y, x + pDis->squareSize, y + pDis->squareSize);
		}
		if (pDis->dragInfo.start.x >= 0) {
			SquareToPos(pDis,pDis->dragInfo.start.x, pDis->dragInfo.start.y, &x, &y);
			clips[num_clips++] = CreateRectRgn(x, y, x + pDis->squareSize, y + pDis->squareSize);
		}
		if (pDis->dragInfo.pos.x >= 0) {
			x = pDis->dragInfo.pos.x - pDis->squareSize / 2;
			y = pDis->dragInfo.pos.y - pDis->squareSize / 2;
			clips[num_clips++] = CreateRectRgn(x, y, x + pDis->squareSize, y + pDis->squareSize);
		}
		if (pDis->dragInfo.lastpos.x >= 0) {
			x = pDis->dragInfo.lastpos.x - pDis->squareSize / 2;
			y = pDis->dragInfo.lastpos.y - pDis->squareSize / 2;
			clips[num_clips++] = CreateRectRgn(x, y, x + pDis->squareSize, y + pDis->squareSize);
		}
	}
	// If dragging is in progress, we temporarely remove the piece  如果正在拖拉一个棋子，则将现在显示的棋盘的棋格的棋子去了
	if (pDis->dragInfo.from.x >= 0 && pDis->dragInfo.pos.x >= 0) {
		//sq_t s90 =   FRto90(DIS.dragInfo.from.x,DIS.dragInfo.from.y);
		//dragged_piece = board[s90];
  //      board[s90] = NOCHESS;

        int s256 = XYtoS(pDis->dragInfo.from.x+3,pDis->dragInfo.from.y+3);
        dragged_piece       = B256[s256];
        B256[s256]          = EMPTY;
	}
	/* Are we animating a move?  
	* If so, 
	*   - remove the piece from the board (temporarely)
	*   - calculate the clipping region
	*/
	if (!fullrepaint) {
		if (pDis->animInfo.piece != EMPTY) {			
			//sq_t s90   = FRto90(DIS.animInfo.from.x,DIS.animInfo.from.y);
			//board[s90] = NOCHESS;

            int s256         = XYtoS(pDis->animInfo.from.x+3,pDis->animInfo.from.y+3);
            B256[s256]       = EMPTY;

			x = pDis->boardRect.left + pDis->animInfo.lastpos.x;
			y = pDis->boardRect.top  + pDis->animInfo.lastpos.y;
			x2 = pDis->boardRect.left + pDis->animInfo.pos.x;
			y2 = pDis->boardRect.top  + pDis->animInfo.pos.y;
			clips[num_clips++] = CreateRectRgn(MIN(x,x2), MIN(y,y2), 
				MAX(x,x2) + pDis->squareSize, 
				MAX(y,y2) + pDis->squareSize);
			/* Slight kludge.  The real problem is that after AnimateMove is
			done, the position on the screen does not match lastDrawn.
			This currently causes trouble only on e.p. captures in
			atomic, where the piece moves to an empty square and then
			explodes.  The old and new positions both had an empty square
			at the destination, but animation has drawn a piece there and
			we have to remember to erase it. */
			//lastDrawn[animInfo.to.y][animInfo.to.x] = animInfo.piece;
			pDis->lastDrawn[s256] = pDis->animInfo.piece;
		}
	}

	/* No clips?  Make sure we have fullrepaint set to TRUE */
	if (num_clips == 0)
		fullrepaint = TRUE;
	/* Set clipping on the memory DC */
	if (!fullrepaint) {
		SelectClipRgn(hdcmem, clips[0]);
		for (x = 1; x < num_clips; x++) {
			if (ExtSelectClipRgn(hdcmem, clips[x], RGN_OR) == ERROR)
				abort();  // this should never ever happen!
		}
	}
	/* Do all the drawing to the memory DC */
	DrawGridOnDC(pDis,hdcmem,tmphdc,hdcmask);				//画上棋格
	DrawHighlightsOnDC(pDis,hdcmem);							//高亮	
	DrawBoardOnDC(pDis,hdcmem, B256, tmphdc,hdcmask);		//画上棋子
	DrawCoordsOnDC(pDis,hdcmem);								//坐标
	
	/* Put the dragged piece back into place and draw it */
	if (dragged_piece != EMPTY) {			

		//board[FRto90(DIS.dragInfo.from.x,DIS.dragInfo.from.y)] = dragged_piece;
        
        B256[XYtoS(pDis->dragInfo.from.x+3,pDis->dragInfo.from.y+3)] = dragged_piece;


		x = pDis->dragInfo.pos.x - pDis->squareSize / 2;
		y = pDis->dragInfo.pos.y - pDis->squareSize / 2;
		DrawPieceOnDC(pDis,hdcmem, dragged_piece,0, 
			(pDis->dragInfo.from.y + pDis->dragInfo.from.x) % 2, x, y, tmphdc,hdcmask);
	} 

	/* Put the animated piece back into place and draw it */
	if (pDis->animInfo.piece != EMPTY) {		
		//sq_t s90  = FRto90(DIS.animInfo.from.x,DIS.animInfo.from.y);
		//board[s90]  = DIS.animInfo.piece;

        int sq256           = XYtoS(pDis->animInfo.from.x+3,pDis->animInfo.from.y+3);
        B256[sq256]         = pDis->animInfo.piece;

		x = pDis->boardRect.left + pDis->animInfo.pos.x;
		y = pDis->boardRect.top  + pDis->animInfo.pos.y;
		DrawPieceOnDC(pDis,hdcmem, pDis->animInfo.piece,1,
			(pDis->animInfo.from.y + pDis->animInfo.from.x) % 2, x, y, tmphdc,hdcmask);
	}

	/* Release the bufferBitmap by selecting in the old bitmap 
	* and delete the memory DC
	*/
	SelectObject(hdcmem, oldBitmap);
	DeleteDC(hdcmem);
	DeleteDC(hdcmask);
	
	/* Set clipping on the target DC */
	if (!fullrepaint) {
		SelectClipRgn(hdc, clips[0]);
		for (x = 1; x < num_clips; x++) {
			if (ExtSelectClipRgn(hdc, clips[x], RGN_OR) == ERROR)
				abort();   // this should never ever happen!
		} 
	}

	/* Copy the new bitmap onto the screen in one go.
	* This way we avoid any flickering,显示整个棋盘
	*/
	oldBitmap = (HBITMAP)SelectObject(tmphdc, bufferBitmap);
	BitBlt(hdc, pDis->boardRect.left, pDis->boardRect.top,
		pDis->boardRect.right  - pDis->boardRect.left,
		pDis->boardRect.bottom - pDis->boardRect.top,
		tmphdc, pDis->boardRect.left, pDis->boardRect.top, SRCCOPY);
	SelectObject(tmphdc, oldBitmap);

	/* Massive cleanup */
	for (x = 0; x < num_clips; x++){
		DeleteObject(clips[x]);
	}


	DeleteDC(tmphdc);
	DeleteObject(bufferBitmap);

	if (releaseDC) {
		/*ReleaseDC(hwndMain, hdc);*/
        ReleaseDC(pDis->hwndThis, hdc);
	}

	//if (pDis->lastDrawnFlipView != pDis->flipView) {
	//	if (pDis->flipView)
	//		CheckMenuItem(GetMenu(hwndMain),IDM_FlipView, MF_BYCOMMAND|MF_CHECKED);
	//	else
	//		CheckMenuItem(GetMenu(hwndMain),IDM_FlipView, MF_BYCOMMAND|MF_UNCHECKED);
	//}

	CopyBoard(pDis->lastDrawn, B256);
	pDis->lastDrawnHighlight = pDis->highlightInfo;
	pDis->lastDrawnPremove   = pDis->premoveHighlightInfo;
	pDis->lastDrawnFlipView  = pDis->flipView;
	pDis->lastDrawnValid     = 1;

	//UpdateWindow(TAB.dlgScore);

	//

}






void
DrawPosition(dispboard_t* DIS, bool fullRedraw, uint8* B256){
  HDCDrawPosition(DIS, NULL, (BOOLEAN) fullRedraw, B256); 

  
}

void				//在DC上画上棋子
DrawBoardOnDC(dispboard_t* DIS, HDC hdc, uint8* B256, HDC tmphdc, HDC hdcmask){
	int file;
	int rank;
	int x;
	int y;
	sq_t piece;
	//for(int i=0; i<90; i++){
	//	file = S90toF(i);
	//	rank = S90toR(i);
	//	SquareToPos(file,rank,&x,&y);
	//	piece = board[i]; 
	//	if(piece != NOCHESS){
	//		DrawPieceOnDC(hdc,piece,0,0,x,y,tmphdc,hdcmask);
	//	}
	//}

    for(int i = 0x33; i < 0xcc; i++){
        file = StoX(i);
        rank = StoY(i);
        SquareToPos(DIS,file-3,rank-3,&x,&y);
        piece = B256[i];
        if(piece != EMPTY){
            DrawPieceOnDC(DIS,hdc,piece,0,0,x,y,tmphdc,hdcmask);
        }
    }
}

void				//画上相应的一个棋子哇
DrawPieceOnDC(dispboard_t* pDis, HDC hdc, sq_t piece, int color, int sqcolor, int x, int y, HDC tmphdc, HDC hdcmask){
	SelectObject(hdcmask,(HBITMAP)pDis->chessMask);
	SelectObject(tmphdc,(HBITMAP)pDis->pieceBitmap[piece]);

	BitBlt(tmphdc, 0, 0, pDis->squareSize, pDis->squareSize, hdcmask, 0, 0, SRCAND);
	
	SelectObject(hdcmask,(HBITMAP)pDis->chessInve);
	BitBlt(hdc, x, y, pDis->squareSize, pDis->squareSize, hdcmask, 0, 0, SRCAND);

	BitBlt(hdc, x, y, pDis->squareSize, pDis->squareSize, tmphdc, 0, 0, SRCPAINT);
}

void
DrawHighlightsOnDC(dispboard_t* pDis, HDC hdc){
  int i;
  for (i=0; i<2; i++) {
    if (pDis->highlightInfo.sq[i].x >= 0 && pDis->highlightInfo.sq[i].y >= 0) 
      DrawHighlightOnDC(pDis,hdc, TRUE,
			pDis->highlightInfo.sq[i].x, 
			pDis->highlightInfo.sq[i].y,
			HIGHLIGHT_PEN);
  }
  for (i=0; i<2; i++) {
    if (pDis->premoveHighlightInfo.sq[i].x >= 0 && 
	pDis->premoveHighlightInfo.sq[i].y >= 0) {
	DrawHighlightOnDC(pDis,hdc, TRUE,
	   		  pDis->premoveHighlightInfo.sq[i].x, 
			  pDis->premoveHighlightInfo.sq[i].y,
			  PREMOVE_PEN);
    }
  }
}


void        //动画走步
AnimateMove(dispboard_t* pDis, uint8* B256, int fromX, int fromY, int toX, int toY){
    sq_t piece;
    POINT start, finish, mid;
    POINT frames[kFactor * 2 + 1];
    int nFrames, n;

    if (!appData.animate) return;
    if (pDis->doingSizing) return;
    if (fromY < 0 || fromX < 0) return;

    //piece = board[FRto90(fromX,fromY)];

    //piece  = pos->b256[XYtoS(fromX+3,fromY+3)];

    piece = B256[XYtoS(fromX+3,fromY+3)];

    //if (piece >= NOCHESS) return;

    if(piece == EMPTY) return;

    ScreenSquare(pDis,fromX, fromY, &start);
    ScreenSquare(pDis,toX, toY, &finish);

	/* All pieces except knights move in straight line */
	if (piece != RMA && piece != BMA) {
		mid.x = start.x + (finish.x - start.x) / 2;
		mid.y = start.y + (finish.y - start.y) / 2;
	} 
    else {
		/* Knight: make diagonal movement then straight */
		if (abs(toY - fromY) < abs(toX - fromX)) {
			mid.x = start.x + (finish.x - start.x) / 2;
			mid.y = finish.y;
		} else {
			mid.x = finish.x;
			mid.y = start.y + (finish.y - start.y) / 2;
		}
	}

	/* Don't use as many frames for very short moves */
	if (abs(toY - fromY) + abs(toX - fromX) <= 2)
		Tween(&start, &mid, &finish, kFactor - 1, frames, &nFrames);
	else
		Tween(&start, &mid, &finish, kFactor, frames, &nFrames);

	pDis->animInfo.from.x = fromX;
	pDis->animInfo.from.y = fromY;
	pDis->animInfo.to.x = toX;
	pDis->animInfo.to.y = toY;
	pDis->animInfo.lastpos = start;
	pDis->animInfo.piece = piece;
	for (n = 0; n < nFrames; n++) {
		pDis->animInfo.pos = frames[n];
		DrawPosition(pDis,false, NULL);
		pDis->animInfo.lastpos = pDis->animInfo.pos;
		Sleep(appData.animSpeed);
	}
	pDis->animInfo.pos = finish;
	DrawPosition(pDis,false, NULL);
	pDis->animInfo.piece = EMPTY;
}


