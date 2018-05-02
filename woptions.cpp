#include "stdafx.h"
#include "chess.h"
#include "data.h"
#include "resource.h"



/*---------------------------------------------------------------------------*\
*
* General Options Dialog functions
*
\*---------------------------------------------------------------------------*/


LRESULT CALLBACK
GeneralOptionsDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    static Boolean oldShowCoords;
    static Boolean oldBlindfold;
    static Boolean oldShowButtonBar;

	dispboard_t *pDis = OBS[0];

    switch (message) {
        case WM_INITDIALOG: /* message: initialize dialog box */
            oldShowCoords = appData.showCoords;
            oldBlindfold  = appData.blindfold;
            oldShowButtonBar = appData.showButtonBar;

            /* Center the dialog over the application window */
            CenterWindow (hDlg, GetWindow (hDlg, GW_OWNER));

            /* Initialize the dialog items */
#define CHECK_BOX(x,y) CheckDlgButton(hDlg, (x), (BOOL)(y))

            CHECK_BOX(OPT_AlwaysOnTop, appData.alwaysOnTop);
            //CHECK_BOX(OPT_AlwaysQueen, appData.alwaysPromoteToQueen);
            CHECK_BOX(OPT_AnimateDragging, appData.animateDragging);
            CHECK_BOX(OPT_AnimateMoving, appData.animate);
            CHECK_BOX(OPT_AutoFlag, appData.autoCallFlag);
            CHECK_BOX(OPT_AutoFlipView, appData.autoFlipView);
            CHECK_BOX(OPT_AutoRaiseBoard, appData.autoRaiseBoard);
            CHECK_BOX(OPT_Blindfold, appData.blindfold);
            CHECK_BOX(OPT_HighlightDragging, appData.highlightDragging);
            CHECK_BOX(OPT_HighlightLastMove, appData.highlightLastMove);
            CHECK_BOX(OPT_PeriodicUpdates, appData.periodicUpdates);
            CHECK_BOX(OPT_PonderNextMove, appData.ponderNextMove);
            CHECK_BOX(OPT_PopupExitMessage, appData.popupExitMessage);
            CHECK_BOX(OPT_PopupMoveErrors, appData.popupMoveErrors);
            CHECK_BOX(OPT_ShowButtonBar, appData.showButtonBar);
            CHECK_BOX(OPT_ShowCoordinates, appData.showCoords);
            CHECK_BOX(OPT_ShowThinking, appData.showThinking);
            CHECK_BOX(OPT_TestLegality, appData.testLegality);

#undef CHECK_BOX

            //EnableWindow(GetDlgItem(hDlg, OPT_AutoFlag),
            //    appData.icsActive || !pDis->noChessProgram);
            //EnableWindow(GetDlgItem(hDlg, OPT_AutoFlipView),
            //    appData.icsActive || !pDis->noChessProgram);


			EnableWindow(GetDlgItem(hDlg, OPT_AutoFlag),
				appData.icsActive);
			EnableWindow(GetDlgItem(hDlg, OPT_AutoFlipView),
				appData.icsActive);

            //EnableWindow(GetDlgItem(hDlg, OPT_PonderNextMove),
            //    !pDis->noChessProgram);
            //EnableWindow(GetDlgItem(hDlg, OPT_PeriodicUpdates), 
            //    !pDis->noChessProgram && !appData.icsActive);
            //EnableWindow(GetDlgItem(hDlg, OPT_ShowThinking), 
            //    !pDis->noChessProgram);


            return TRUE;


        case WM_COMMAND: /* message: received a command */
            switch (LOWORD(wParam)) {
        case IDOK:
            /* Read changed options from the dialog box */

#define IS_CHECKED(x) (Boolean)IsDlgButtonChecked(hDlg, (x))

            appData.alwaysOnTop         = IS_CHECKED(OPT_AlwaysOnTop);
            //appData.alwaysPromoteToQueen = IS_CHECKED(OPT_AlwaysQueen);
            appData.animateDragging      = IS_CHECKED(OPT_AnimateDragging);
            appData.animate              = IS_CHECKED(OPT_AnimateMoving);
            appData.autoCallFlag         = IS_CHECKED(OPT_AutoFlag);
            appData.autoFlipView         = IS_CHECKED(OPT_AutoFlipView);
            appData.autoRaiseBoard       = IS_CHECKED(OPT_AutoRaiseBoard);
            appData.blindfold            = IS_CHECKED(OPT_Blindfold);
            appData.highlightDragging    = IS_CHECKED(OPT_HighlightDragging);
            appData.highlightLastMove    = IS_CHECKED(OPT_HighlightLastMove);
            PeriodicUpdatesEvent(  pDis,         IS_CHECKED(OPT_PeriodicUpdates));
            PonderNextMoveEvent( pDis,           IS_CHECKED(OPT_PonderNextMove));
            appData.popupExitMessage     = IS_CHECKED(OPT_PopupExitMessage);
            appData.popupMoveErrors      = IS_CHECKED(OPT_PopupMoveErrors);
            appData.showButtonBar        = IS_CHECKED(OPT_ShowButtonBar);
            appData.showCoords           = IS_CHECKED(OPT_ShowCoordinates);
            ShowThinkingEvent( pDis,           IS_CHECKED(OPT_ShowThinking));
            appData.testLegality         = IS_CHECKED(OPT_TestLegality);

#undef IS_CHECKED

            SetWindowPos(pDis->hwndThis, appData.alwaysOnTop ? HWND_TOPMOST : HWND_NOTOPMOST,
                0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
#if AOT_CONSOLE
            if (hwndConsole) {
                SetWindowPos(hwndConsole, alwaysOnTop ? HWND_TOPMOST : HWND_NOTOPMOST,
                    0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
            }
#endif
            if (!appData.highlightLastMove) {
                ClearHighlights(pDis);
                //DrawPosition(FALSE, NULL);
            }
            /* 
            * for some reason the redraw seems smoother when we invalidate
            * the board rect after the call to EndDialog()
            */
            EndDialog(hDlg, TRUE);

            if (oldShowButtonBar != appData.showButtonBar) {
                //InitDrawingSizes(boardSize, 0);
            } else if ((oldShowCoords != appData.showCoords) || 
                (oldBlindfold != appData.blindfold)) {
                    InvalidateRect(pDis->hwndThis, &pDis->boardRect, FALSE);
            }

            return TRUE;

        case IDCANCEL:
            EndDialog(hDlg, FALSE);
            return TRUE;

            }
            break;
    }
    return FALSE;
}

VOID 
GeneralOptionsPopup(HWND hwnd){
    FARPROC lpProc;

    lpProc = MakeProcInstance((FARPROC)GeneralOptionsDialog, hInst);
    DialogBox(hInst, MAKEINTRESOURCE(DLG_GeneralOptions), hwnd,
        (DLGPROC) lpProc);
    FreeProcInstance(lpProc);
}
/*---------------------------------------------------------------------------*\
*
* Board Options Dialog functions
*
\*---------------------------------------------------------------------------*/



VOID
ChangeBoardSize(dispboard_t* pDis, BoardSize newSize){
    if (newSize != pDis->bsize) {
        pDis->bsize = newSize;
        InitDrawingSizes(pDis, pDis->bsize, 0);
    }
}

VOID
PaintSampleSquare(
                  HWND     hwnd, 
                  int      ctrlid, 
                  COLORREF squareColor, 
                  COLORREF pieceColor,
                  COLORREF squareOutlineColor,
                  COLORREF pieceDetailColor,
                  BOOL     isWhitePiece,
                  BOOL     isMono,
                  HBITMAP  pieces[3] 
)
{
    HBRUSH  brushSquare;
    HBRUSH  brushSquareOutline;
    HBRUSH  brushPiece;
    HBRUSH  brushPieceDetail;
    HBRUSH  oldBrushPiece;
    HBRUSH  oldBrushSquare;
    HBITMAP oldBitmapMem;
    HBITMAP oldBitmapTemp;
    HBITMAP bufferBitmap;
    RECT    rect;
    HDC     hdcScreen, hdcMem, hdcTemp;
    HPEN    pen, oldPen;
    HWND    hCtrl = GetDlgItem(hwnd, ctrlid);
    int     x, y;

    const int SOLID   = 0;
    const int WHITE   = 1;
    const int OUTLINE = 2;
    const int BORDER  = 4;

    InvalidateRect(hCtrl, NULL, TRUE);
    UpdateWindow(hCtrl);
    GetClientRect(hCtrl, &rect);
    x = rect.left + (BORDER / 2);
    y = rect.top  + (BORDER / 2);
    hdcScreen = GetDC(hCtrl);
    hdcMem  = CreateCompatibleDC(hdcScreen);
    hdcTemp = CreateCompatibleDC(hdcScreen);

    bufferBitmap = CreateCompatibleBitmap(hdcScreen, rect.right-rect.left+1,
        rect.bottom-rect.top+1);
    oldBitmapMem = (HBITMAP)SelectObject(hdcMem, bufferBitmap);

	dispboard_t *pDis = OBS[0];

    if (!isMono) {
        SelectPalette(hdcMem, pDis->hPal, FALSE);
    }
    brushSquare         = CreateSolidBrush(squareColor);
    brushSquareOutline  = CreateSolidBrush(squareOutlineColor);
    brushPiece          = CreateSolidBrush(pieceColor);
    brushPieceDetail    = CreateSolidBrush(pieceDetailColor);

    /* 
    * first draw the rectangle 
    */
    pen      = CreatePen(PS_SOLID, BORDER, squareOutlineColor);
    oldPen   = (HPEN)  SelectObject(hdcMem, pen);
    oldBrushSquare = (HBRUSH)SelectObject(hdcMem, brushSquare);
    Rectangle(hdcMem, rect.left, rect.top, rect.right, rect.bottom);

    /* 
    * now draw the piece
    */
    if (isMono) {
        oldBitmapTemp = (HBITMAP)SelectObject(hdcTemp, pieces[OUTLINE]);
        BitBlt(hdcMem, x, y, SAMPLE_SQ_SIZE, SAMPLE_SQ_SIZE, hdcTemp, 0, 0,
            isWhitePiece ? SRCCOPY : NOTSRCCOPY);
        SelectObject(hdcTemp, oldBitmapTemp);
    } else {
        if (isWhitePiece) {
            oldBitmapTemp = (HBITMAP)SelectObject(hdcTemp, pieces[WHITE]);
            oldBrushPiece = (HBRUSH)SelectObject(hdcMem, brushPiece);
            BitBlt(hdcMem, x, y, SAMPLE_SQ_SIZE, SAMPLE_SQ_SIZE, 
                hdcTemp, 0, 0, 0x00B8074A);
#if 0
            /* Use pieceDetailColor for outline of white pieces */
            SelectObject(hdcTemp, pieces[OUTLINE]);
            SelectObject(hdcMem, brushPieceDetail);
            BitBlt(hdcMem, x, y, SAMPLE_SQ_SIZE, SAMPLE_SQ_SIZE, 
                hdcTemp, 0, 0, 0x00B8074A);
#else
            /* Use black for outline of white pieces */
            SelectObject(hdcTemp, pieces[OUTLINE]);
            BitBlt(hdcMem, x, y, SAMPLE_SQ_SIZE, SAMPLE_SQ_SIZE, 
                hdcTemp, 0, 0, SRCAND);
#endif
        } else {
#if 0
            /* Use pieceDetailColor for details of black pieces */
            /* Requires filled-in solid bitmaps (BLACK_PIECE class); the
            WHITE_PIECE ones aren't always the right shape. */
            oldBitmapTemp = SelectObject(hdcTemp, pieces[BLACK]);
            oldBrushPiece = SelectObject(hdcMem, brushPieceDetail);
            BitBlt(hdcMem, x, y, SAMPLE_SQ_SIZE, SAMPLE_SQ_SIZE, 
                hdcTemp, 0, 0, 0x00B8074A);
            SelectObject(hdcTemp, pieces[SOLID]);
            SelectObject(hdcMem, brushPiece);
            BitBlt(hdcMem, x, y, SAMPLE_SQ_SIZE, SAMPLE_SQ_SIZE, 
                hdcTemp, 0, 0, 0x00B8074A);
#else
            /* Use square color for details of black pieces */
            oldBitmapTemp = (HBITMAP)SelectObject(hdcTemp, pieces[SOLID]);
            oldBrushPiece = (HBRUSH)SelectObject(hdcMem, brushPiece);
            BitBlt(hdcMem, x, y, SAMPLE_SQ_SIZE, SAMPLE_SQ_SIZE, 
                hdcTemp, 0, 0, 0x00B8074A);
#endif
        }
        SelectObject(hdcMem, oldBrushPiece);
        SelectObject(hdcTemp, oldBitmapTemp);
    }
    /* 
    * copy the memory dc to the screen
    */
    SelectObject(hdcMem, bufferBitmap);
    BitBlt(hdcScreen, rect.left, rect.top,
        rect.right - rect.left,
        rect.bottom - rect.top,
        hdcMem, rect.left, rect.top, SRCCOPY);
    SelectObject(hdcMem, oldBitmapMem);
    /* 
    * clean up
    */
    SelectObject(hdcMem, oldBrushPiece);
    SelectObject(hdcMem, oldPen);
    DeleteObject(brushPiece);
    DeleteObject(brushPieceDetail);
    DeleteObject(brushSquare);
    DeleteObject(brushSquareOutline);
    DeleteObject(pen);
    DeleteDC(hdcTemp);
    DeleteDC(hdcMem);
    ReleaseDC(hCtrl, hdcScreen);
}


void
PaintColorBlock(HWND hwnd, int ctrlid, COLORREF color)
{
    HDC    hdc;
    HBRUSH brush, oldBrush;
    RECT   rect;
    HWND   hCtrl = GetDlgItem(hwnd, ctrlid);

    hdc = GetDC(hCtrl);
    InvalidateRect(hCtrl, NULL, TRUE);
    UpdateWindow(hCtrl);
    GetClientRect(hCtrl, &rect);
    brush = CreateSolidBrush(color);
    oldBrush = (HBRUSH)SelectObject(hdc, brush);
    Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
    SelectObject(hdc, oldBrush);
    DeleteObject(brush);
    ReleaseDC(hCtrl, hdc);
}


void
SetBoardOptionEnables(HWND hDlg)
{
    if (IsDlgButtonChecked(hDlg, OPT_Monochrome)) {
        ShowWindow(GetDlgItem(hDlg, OPT_LightSquareColor), SW_HIDE);
        ShowWindow(GetDlgItem(hDlg, OPT_DarkSquareColor), SW_HIDE);
        ShowWindow(GetDlgItem(hDlg, OPT_WhitePieceColor), SW_HIDE);
        ShowWindow(GetDlgItem(hDlg, OPT_BlackPieceColor), SW_HIDE);

        EnableWindow(GetDlgItem(hDlg, OPT_ChooseLightSquareColor), FALSE);
        EnableWindow(GetDlgItem(hDlg, OPT_ChooseDarkSquareColor), FALSE);
        EnableWindow(GetDlgItem(hDlg, OPT_ChooseWhitePieceColor), FALSE);
        EnableWindow(GetDlgItem(hDlg, OPT_ChooseBlackPieceColor), FALSE);
    } else {
        ShowWindow(GetDlgItem(hDlg, OPT_LightSquareColor), SW_SHOW);
        ShowWindow(GetDlgItem(hDlg, OPT_DarkSquareColor), SW_SHOW);
        ShowWindow(GetDlgItem(hDlg, OPT_WhitePieceColor), SW_SHOW);
        ShowWindow(GetDlgItem(hDlg, OPT_BlackPieceColor), SW_SHOW);

        EnableWindow(GetDlgItem(hDlg, OPT_ChooseLightSquareColor), TRUE);
        EnableWindow(GetDlgItem(hDlg, OPT_ChooseDarkSquareColor), TRUE);
        EnableWindow(GetDlgItem(hDlg, OPT_ChooseWhitePieceColor), TRUE);
        EnableWindow(GetDlgItem(hDlg, OPT_ChooseBlackPieceColor), TRUE);
    }
}

BoardSize 
BoardOptionsWhichRadio(HWND hDlg)
{
    return (IsDlgButtonChecked(hDlg, OPT_SizeTiny) ? SizeTiny :
        (IsDlgButtonChecked(hDlg, OPT_SizeTeeny) ? SizeTeeny :
        (IsDlgButtonChecked(hDlg, OPT_SizeDinky) ? SizeDinky :
        (IsDlgButtonChecked(hDlg, OPT_SizePetite) ? SizePetite :
        (IsDlgButtonChecked(hDlg, OPT_SizeSlim) ? SizeSlim :
        (IsDlgButtonChecked(hDlg, OPT_SizeSmall) ? SizeSmall :
        (IsDlgButtonChecked(hDlg, OPT_SizeMediocre) ? SizeMediocre :
        (IsDlgButtonChecked(hDlg, OPT_SizeMiddling) ? SizeMiddling :
        (IsDlgButtonChecked(hDlg, OPT_SizeAverage) ? SizeAverage :
        (IsDlgButtonChecked(hDlg, OPT_SizeModerate) ? SizeModerate :
        (IsDlgButtonChecked(hDlg, OPT_SizeMedium) ? SizeMedium :
        (IsDlgButtonChecked(hDlg, OPT_SizeBulky) ? SizeBulky :
        (IsDlgButtonChecked(hDlg, OPT_SizeLarge) ? SizeLarge :
        (IsDlgButtonChecked(hDlg, OPT_SizeBig) ? SizeBig :
        (IsDlgButtonChecked(hDlg, OPT_SizeHuge) ? SizeHuge :
        (IsDlgButtonChecked(hDlg, OPT_SizeGiant) ? SizeGiant :
        (IsDlgButtonChecked(hDlg, OPT_SizeColossal) ? SizeColossal :
        SizeTitanic )))))))))))))))));
}

LRESULT CALLBACK
BoardOptionsDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    static Boolean  mono;
    static BoardSize size;
    static COLORREF lsc, dsc, wpc, bpc, hsc, phc;
    static HBITMAP pieces[3];

	 dispboard_t* pDis = OBS[0];

    switch (message) {
  case WM_INITDIALOG: /* message: initialize dialog box */
      /* Center the dialog over the application window */
      CenterWindow (hDlg, GetWindow (hDlg, GW_OWNER));
      /* Initialize the dialog items */
      switch (pDis->bsize) {
  case SizeTiny:
      CheckDlgButton(hDlg, OPT_SizeTiny, TRUE);
      break;
  case SizeTeeny:
      CheckDlgButton(hDlg, OPT_SizeTeeny, TRUE);
      break;
  case SizeDinky:
      CheckDlgButton(hDlg, OPT_SizeDinky, TRUE);
      break;
  case SizePetite:
      CheckDlgButton(hDlg, OPT_SizePetite, TRUE);
      break;
  case SizeSlim:
      CheckDlgButton(hDlg, OPT_SizeSlim, TRUE);
      break;
  case SizeSmall:
      CheckDlgButton(hDlg, OPT_SizeSmall, TRUE);
      break;
  case SizeMediocre:
      CheckDlgButton(hDlg, OPT_SizeMediocre, TRUE);
      break;
  case SizeMiddling:
      CheckDlgButton(hDlg, OPT_SizeMiddling, TRUE);
      break;
  case SizeAverage:
      CheckDlgButton(hDlg, OPT_SizeAverage, TRUE);
      break;
  case SizeModerate:
      CheckDlgButton(hDlg, OPT_SizeModerate, TRUE);
      break;
  case SizeMedium:
      CheckDlgButton(hDlg, OPT_SizeMedium, TRUE);
      break;
  case SizeBulky:
      CheckDlgButton(hDlg, OPT_SizeBulky, TRUE);
      break;
  case SizeLarge:
      CheckDlgButton(hDlg, OPT_SizeLarge, TRUE);
      break;
  case SizeBig:
      CheckDlgButton(hDlg, OPT_SizeBig, TRUE);
      break;
  case SizeHuge:
      CheckDlgButton(hDlg, OPT_SizeHuge, TRUE);
      break;
  case SizeGiant:
      CheckDlgButton(hDlg, OPT_SizeGiant, TRUE);
      break;
  case SizeColossal:
      CheckDlgButton(hDlg, OPT_SizeColossal, TRUE);
      break;
  case SizeTitanic:
      CheckDlgButton(hDlg, OPT_SizeTitanic, TRUE);
      }

      //if (appData.monoMode)
      //    CheckDlgButton(hDlg, OPT_Monochrome, TRUE);

      //pieces[0] = DoLoadBitmap(hInst, "n", SAMPLE_SQ_SIZE, "s");
      //pieces[1] = DoLoadBitmap(hInst, "n", SAMPLE_SQ_SIZE, "w");
      //pieces[2] = DoLoadBitmap(hInst, "n", SAMPLE_SQ_SIZE, "o");

      lsc = appData.lightSquareColor;
      dsc = appData.darkSquareColor;
      wpc = appData.whitePieceColor;
      bpc = appData.blackPieceColor;
      hsc = appData.highlightSquareColor;
      phc = appData.premoveHighlightColor;
      //mono = appData.monoMode;
      size = pDis->bsize;

      SetBoardOptionEnables(hDlg);
      return TRUE;

  case WM_PAINT:
      PaintColorBlock(hDlg, OPT_LightSquareColor, lsc);
      PaintColorBlock(hDlg, OPT_DarkSquareColor,  dsc);
      PaintColorBlock(hDlg, OPT_WhitePieceColor,  wpc);
      PaintColorBlock(hDlg, OPT_BlackPieceColor,  bpc);
      PaintColorBlock(hDlg, OPT_HighlightSquareColor, hsc);
      PaintColorBlock(hDlg, OPT_PremoveHighlightColor, phc);
      PaintSampleSquare(hDlg, OPT_SampleLightSquare, lsc, wpc, hsc, bpc,
          TRUE, mono, pieces);
      PaintSampleSquare(hDlg, OPT_SampleDarkSquare, dsc, bpc, phc, wpc,
          FALSE, mono, pieces);

      return FALSE;

  case WM_COMMAND: /* message: received a command */
      switch (LOWORD(wParam)) {
  case IDOK:
      /* 
      * if we call EndDialog() after the call to ChangeBoardSize(),
      * then ChangeBoardSize() does not take effect, although the new
      * boardSize is saved. Go figure...
      */
      EndDialog(hDlg, TRUE);

      size = BoardOptionsWhichRadio(hDlg);

      /*
      * did any settings change?
      */
      if (size != pDis->bsize) {
          ChangeBoardSize(pDis,size);
      }

      //if ((mono != appData.monoMode) ||
      if ((lsc  != appData.lightSquareColor) ||
          (dsc  != appData.darkSquareColor) ||
          (wpc  != appData.whitePieceColor) ||
          (bpc  != appData.blackPieceColor) ||
          (hsc  != appData.highlightSquareColor) ||
          (phc  != appData.premoveHighlightColor)) {

              appData.lightSquareColor = lsc;
              appData.darkSquareColor = dsc;
              appData.whitePieceColor = wpc;
              appData.blackPieceColor = bpc;
              appData.highlightSquareColor = hsc;
              appData.premoveHighlightColor = phc;
              //appData.monoMode = mono;

              //InitDrawingColors();
              //InitDrawingSizes(boardSize, 0);
              InvalidateRect(pDis->hwndThis, &pDis->boardRect, FALSE);
      }
      DeleteObject(pieces[0]);
      DeleteObject(pieces[1]);
      DeleteObject(pieces[2]);
      return TRUE;

  case IDCANCEL:
      DeleteObject(pieces[0]);
      DeleteObject(pieces[1]);
      DeleteObject(pieces[2]);
      EndDialog(hDlg, FALSE);
      return TRUE;

  case OPT_ChooseLightSquareColor:
      if (ChangeColor(hDlg, &lsc)) 
          PaintColorBlock(hDlg, OPT_LightSquareColor, lsc);
      PaintSampleSquare(hDlg, OPT_SampleLightSquare, lsc, wpc, hsc, bpc,
          TRUE, mono, pieces);
      break;

  case OPT_ChooseDarkSquareColor:
      if (ChangeColor(hDlg, &dsc)) 
          PaintColorBlock(hDlg, OPT_DarkSquareColor, dsc);
      PaintSampleSquare(hDlg, OPT_SampleDarkSquare, dsc, bpc, phc, wpc,
          FALSE, mono, pieces);
      break;

  case OPT_ChooseWhitePieceColor:
      if (ChangeColor(hDlg, &wpc)) 
          PaintColorBlock(hDlg, OPT_WhitePieceColor, wpc);
      PaintSampleSquare(hDlg, OPT_SampleLightSquare, lsc, wpc, hsc, bpc,
          TRUE, mono, pieces);
      break;

  case OPT_ChooseBlackPieceColor:
      if (ChangeColor(hDlg, &bpc)) 
          PaintColorBlock(hDlg, OPT_BlackPieceColor, bpc);
      PaintSampleSquare(hDlg, OPT_SampleDarkSquare, dsc, bpc, phc, wpc,
          FALSE, mono, pieces);
      break;

  case OPT_ChooseHighlightSquareColor:
      if (ChangeColor(hDlg, &hsc)) 
          PaintColorBlock(hDlg, OPT_HighlightSquareColor, hsc);
      PaintSampleSquare(hDlg, OPT_SampleLightSquare, lsc, wpc, hsc, bpc,
          TRUE, mono, pieces);
      break;

  case OPT_ChoosePremoveHighlightColor:
      if (ChangeColor(hDlg, &phc)) 
          PaintColorBlock(hDlg, OPT_PremoveHighlightColor, phc);
      PaintSampleSquare(hDlg, OPT_SampleDarkSquare, dsc, bpc, phc, wpc,
          FALSE, mono, pieces);
      break;

  case OPT_DefaultBoardColors:
      lsc = ParseColorName(LIGHT_SQUARE_COLOR);
      dsc = ParseColorName(DARK_SQUARE_COLOR);
      wpc = ParseColorName(WHITE_PIECE_COLOR);
      bpc = ParseColorName(BLACK_PIECE_COLOR);
      hsc = ParseColorName(HIGHLIGHT_SQUARE_COLOR);
      phc = ParseColorName(PREMOVE_HIGHLIGHT_COLOR);
      mono = FALSE;
      CheckDlgButton(hDlg, OPT_Monochrome, FALSE);
      PaintColorBlock(hDlg, OPT_LightSquareColor, lsc);
      PaintColorBlock(hDlg, OPT_DarkSquareColor,  dsc);
      PaintColorBlock(hDlg, OPT_WhitePieceColor,  wpc);
      PaintColorBlock(hDlg, OPT_BlackPieceColor,  bpc);
      PaintColorBlock(hDlg, OPT_HighlightSquareColor, hsc);
      PaintColorBlock(hDlg, OPT_PremoveHighlightColor, phc);
      SetBoardOptionEnables(hDlg);
      PaintSampleSquare(hDlg, OPT_SampleLightSquare, lsc, wpc, hsc, bpc,
          TRUE, mono, pieces);
      PaintSampleSquare(hDlg, OPT_SampleDarkSquare, dsc, bpc, phc, wpc,
          FALSE, mono, pieces);
      break;

  case OPT_Monochrome:
      mono = !mono;
      SetBoardOptionEnables(hDlg);
      break;
      }
      break;
    }
    return FALSE;
}


void
BoardOptionsPopup(HWND hwnd)
{
    FARPROC lpProc = MakeProcInstance((FARPROC)BoardOptionsDialog, hInst);
    DialogBox(hInst, MAKEINTRESOURCE(DLG_BoardOptions), hwnd,
        (DLGPROC) lpProc);
    FreeProcInstance(lpProc);
}

/*---------------------------------------------------------------------------*\
*
* ICS Options Dialog functions
*
\*---------------------------------------------------------------------------*/

BOOL APIENTRY
MyCreateFont(HWND hwnd, MyFont *font)
{
    CHOOSEFONT cf;
    HFONT hf;

    /* Initialize members of the CHOOSEFONT structure. */
    cf.lStructSize = sizeof(CHOOSEFONT);
    cf.hwndOwner = hwnd;
    cf.hDC = (HDC)NULL;
    cf.lpLogFont = &font->lf;
    cf.iPointSize = 0;
    cf.Flags = CF_SCREENFONTS|/*CF_ANSIONLY|*/CF_INITTOLOGFONTSTRUCT;
    cf.rgbColors = RGB(0,0,0);
    cf.lCustData = 0L;
    cf.lpfnHook = (LPCFHOOKPROC)NULL;
    cf.lpTemplateName = NULL;
    cf.hInstance = (HINSTANCE) NULL;
    cf.lpszStyle = NULL;
    cf.nFontType = SCREEN_FONTTYPE;
    cf.nSizeMin = 0;
    cf.nSizeMax = 0;

    /* Display the CHOOSEFONT common-dialog box. */
    if (!ChooseFont(&cf)) {
        return FALSE;
    }

    /* Create a logical font based on the user's   */
    /* selection and return a handle identifying   */
    /* that font. */
    hf = CreateFontIndirect(cf.lpLogFont);
    if (hf == NULL) {
        return FALSE;
    }

    font->hf = hf;
    font->mfp.pointSize = (float) (cf.iPointSize / 10.0);
    font->mfp.bold = (font->lf.lfWeight >= FW_BOLD);
    font->mfp.italic = font->lf.lfItalic;
    font->mfp.underline = font->lf.lfUnderline;
    font->mfp.strikeout = font->lf.lfStrikeOut;
    //strcpy(font->mfp.faceName, font->lf.lfFaceName);
    StringCbCopy(font->mfp.faceName,32,font->lf.lfFaceName);
    return TRUE;
}


void
UpdateSampleText(HWND hDlg, int id, MyColorizeAttribs *mca)
{
     dispboard_t* pDis = OBS[0];
	CHARFORMAT cf;
    cf.cbSize = sizeof(CHARFORMAT);
    cf.dwMask = 
        CFM_COLOR|CFM_BOLD|CFM_ITALIC|CFM_UNDERLINE|CFM_STRIKEOUT|CFM_FACE|CFM_SIZE;
    cf.crTextColor = mca->color;
    cf.dwEffects = mca->effects;
    //strcpy(cf.szFaceName, font[boardSize][CONSOLE_FONT]->mfp.faceName);
    StringCbCopy(cf.szFaceName,32,appData.Afont[pDis->bsize][CONSOLE_FONT]->mfp.faceName);
    /* 
    * The 20.0 below is in fact documented. yHeight is expressed in twips.
    * A twip is 1/20 of a font's point size. See documentation of CHARFORMAT.
    * --msw
    */
    cf.yHeight = (int)(appData.Afont[pDis->bsize][CONSOLE_FONT]->mfp.pointSize * 20.0 + 0.5);
    cf.bCharSet = DEFAULT_CHARSET; /* should be ignored anyway */
    cf.bPitchAndFamily = DEFAULT_PITCH|FF_DONTCARE;
    SendDlgItemMessage(hDlg, id, EM_SETCHARFORMAT, SCF_ALL, (LPARAM)&cf);
}

LRESULT CALLBACK
ColorizeTextDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    static MyColorizeAttribs mca;
    static ColorClass cc;
    COLORREF background = (COLORREF)0;

    switch (message) {
  case WM_INITDIALOG:
      cc = (ColorClass)lParam;
      mca = colorizeAttribs[cc];
      /* Center the dialog over the application window */
      CenterWindow (hDlg, GetWindow (hDlg, GW_OWNER));
      /* Initialize the dialog items */
      CheckDlgButton(hDlg, OPT_Bold, (mca.effects & CFE_BOLD) != 0);
      CheckDlgButton(hDlg, OPT_Italic, (mca.effects & CFE_ITALIC) != 0);
      CheckDlgButton(hDlg, OPT_Underline, (mca.effects & CFE_UNDERLINE) != 0);
      CheckDlgButton(hDlg, OPT_Strikeout, (mca.effects & CFE_STRIKEOUT) != 0);

      /* get the current background color from the parent window */
      SendMessage(GetWindow(hDlg, GW_OWNER),WM_COMMAND, 
          (WPARAM)WM_USER_GetConsoleBackground, 
          (LPARAM)&background);

      /* set the background color */
      SendDlgItemMessage(hDlg, OPT_Sample, EM_SETBKGNDCOLOR, FALSE, background);

      SetDlgItemText(hDlg, OPT_Sample, mca.name);
      UpdateSampleText(hDlg, OPT_Sample, &mca);
      return TRUE;

  case WM_COMMAND: /* message: received a command */
      switch (LOWORD(wParam)) {
  case IDOK:
      /* Read changed options from the dialog box */
      colorizeAttribs[cc] = mca;
      appData.AtextAttribs[cc].color = mca.color;
      appData.AtextAttribs[cc].effects = mca.effects;
      Colorize(ICS.curColor, TRUE);
      if (cc == ColorNormal) {
          CHARFORMAT cf;
          cf.cbSize = sizeof(CHARFORMAT);
          cf.dwMask = CFM_COLOR;
          cf.crTextColor = mca.color;
          SendDlgItemMessage(HWND_CONSOLE, OPT_ConsoleInput, 
              EM_SETCHARFORMAT, SCF_ALL, (LPARAM)&cf);
      }
      EndDialog(hDlg, TRUE);
      return TRUE;

  case IDCANCEL:
      EndDialog(hDlg, FALSE);
      return TRUE;

  case OPT_ChooseColor:
      ChangeColor(hDlg, &mca.color);
      UpdateSampleText(hDlg, OPT_Sample, &mca);
      return TRUE;

  default:
      mca.effects =
          (IsDlgButtonChecked(hDlg, OPT_Bold) ? CFE_BOLD : 0) |
          (IsDlgButtonChecked(hDlg, OPT_Italic) ? CFE_ITALIC : 0) |
          (IsDlgButtonChecked(hDlg, OPT_Underline) ? CFE_UNDERLINE : 0) |
          (IsDlgButtonChecked(hDlg, OPT_Strikeout) ? CFE_STRIKEOUT : 0);
      UpdateSampleText(hDlg, OPT_Sample, &mca);
      break;
      }
      break;
    }
    return FALSE;
}

void
ColorizeTextPopup(HWND hwnd, ColorClass cc)
{
    FARPROC lpProc;

    lpProc = MakeProcInstance((FARPROC)ColorizeTextDialog, hInst);
    DialogBoxParam(hInst, MAKEINTRESOURCE(DLG_Colorize),
        hwnd, (DLGPROC)lpProc, (LPARAM) cc);
    FreeProcInstance(lpProc);
}

void
SetIcsOptionEnables(HWND hDlg)
{
#define ENABLE_DLG_ITEM(x,y) EnableWindow(GetDlgItem(hDlg,(x)), (y))

    UINT state = IsDlgButtonChecked(hDlg, OPT_Premove);
    ENABLE_DLG_ITEM(OPT_PremoveWhite, state);
    ENABLE_DLG_ITEM(OPT_PremoveWhiteText, state);
    ENABLE_DLG_ITEM(OPT_PremoveBlack, state);
    ENABLE_DLG_ITEM(OPT_PremoveBlackText, state);

    ENABLE_DLG_ITEM(OPT_IcsAlarmTime, IsDlgButtonChecked(hDlg, OPT_IcsAlarm));

#undef ENABLE_DLG_ITEM
}


LRESULT CALLBACK
IcsOptionsDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    TCHAR buf[MSG_SIZ];
    int number;
    int i;
    static COLORREF cbc;
    static MyColorizeAttribs *mca;
    COLORREF *colorref;

    switch (message) {
  case WM_INITDIALOG: /* message: initialize dialog box */

      mca = colorizeAttribs;

      for (i=0; i < NColorClasses - 1; i++) {
          mca[i].color   = appData.AtextAttribs[i].color;
          mca[i].effects = appData.AtextAttribs[i].effects;
      }
      cbc = TAB.consoleBackgroundColor;

      /* Center the dialog over the application window */
      CenterWindow (hDlg, GetWindow (hDlg, GW_OWNER));

      /* Initialize the dialog items */
#define CHECK_BOX(x,y) CheckDlgButton(hDlg, (x), (BOOL)(y))

      CHECK_BOX(OPT_AutoComment, appData.autoComment);
      CHECK_BOX(OPT_AutoObserve, appData.autoObserve);
      CHECK_BOX(OPT_GetMoveList, appData.getMoveList);
      CHECK_BOX(OPT_LocalLineEditing, appData.localLineEditing);
      CHECK_BOX(OPT_QuietPlay, appData.quietPlay);
      CHECK_BOX(OPT_Premove, appData.premove);
      CHECK_BOX(OPT_PremoveWhite, appData.premoveWhite);
      CHECK_BOX(OPT_PremoveBlack, appData.premoveBlack);
      CHECK_BOX(OPT_IcsAlarm, appData.icsAlarm);
      CHECK_BOX(OPT_DontColorize, !appData.colorize);

#undef CHECK_BOX

      //sprintf(buf, "%d", appData.icsAlarmTime / 1000);
      StringCbPrintf(buf,MSG_SIZ,_T("%d"), appData.icsAlarmTime / 1000);
      SetDlgItemText(hDlg, OPT_IcsAlarmTime, buf);
      SetDlgItemText(hDlg, OPT_PremoveWhiteText, appData.premoveWhiteText);
      SetDlgItemText(hDlg, OPT_PremoveBlackText, appData.premoveBlackText);

      SendDlgItemMessage(hDlg, OPT_SampleShout,     EM_SETBKGNDCOLOR, 0, cbc);
      SendDlgItemMessage(hDlg, OPT_SampleSShout,    EM_SETBKGNDCOLOR, 0, cbc);
      SendDlgItemMessage(hDlg, OPT_SampleChannel1,  EM_SETBKGNDCOLOR, 0, cbc);
      SendDlgItemMessage(hDlg, OPT_SampleChannel,   EM_SETBKGNDCOLOR, 0, cbc);
      SendDlgItemMessage(hDlg, OPT_SampleKibitz,    EM_SETBKGNDCOLOR, 0, cbc);
      SendDlgItemMessage(hDlg, OPT_SampleTell,      EM_SETBKGNDCOLOR, 0, cbc);
      SendDlgItemMessage(hDlg, OPT_SampleChallenge, EM_SETBKGNDCOLOR, 0, cbc);
      SendDlgItemMessage(hDlg, OPT_SampleRequest,   EM_SETBKGNDCOLOR, 0, cbc);
      SendDlgItemMessage(hDlg, OPT_SampleSeek,      EM_SETBKGNDCOLOR, 0, cbc);
      SendDlgItemMessage(hDlg, OPT_SampleNormal,    EM_SETBKGNDCOLOR, 0, cbc);

      SetDlgItemText(hDlg, OPT_SampleShout,     mca[ColorShout].name);
      SetDlgItemText(hDlg, OPT_SampleSShout,    mca[ColorSShout].name);
      SetDlgItemText(hDlg, OPT_SampleChannel1,  mca[ColorChannel1].name);
      SetDlgItemText(hDlg, OPT_SampleChannel,   mca[ColorChannel].name);
      SetDlgItemText(hDlg, OPT_SampleKibitz,    mca[ColorKibitz].name);
      SetDlgItemText(hDlg, OPT_SampleTell,      mca[ColorTell].name);
      SetDlgItemText(hDlg, OPT_SampleChallenge, mca[ColorChallenge].name);
      SetDlgItemText(hDlg, OPT_SampleRequest,   mca[ColorRequest].name);
      SetDlgItemText(hDlg, OPT_SampleSeek,      mca[ColorSeek].name);
      SetDlgItemText(hDlg, OPT_SampleNormal,    mca[ColorNormal].name);

      UpdateSampleText(hDlg, OPT_SampleShout,     &mca[ColorShout]);
      UpdateSampleText(hDlg, OPT_SampleSShout,    &mca[ColorSShout]);
      UpdateSampleText(hDlg, OPT_SampleChannel1,  &mca[ColorChannel1]);
      UpdateSampleText(hDlg, OPT_SampleChannel,   &mca[ColorChannel]);
      UpdateSampleText(hDlg, OPT_SampleKibitz,    &mca[ColorKibitz]);
      UpdateSampleText(hDlg, OPT_SampleTell,      &mca[ColorTell]);
      UpdateSampleText(hDlg, OPT_SampleChallenge, &mca[ColorChallenge]);
      UpdateSampleText(hDlg, OPT_SampleRequest,   &mca[ColorRequest]);
      UpdateSampleText(hDlg, OPT_SampleSeek,      &mca[ColorSeek]);
      UpdateSampleText(hDlg, OPT_SampleNormal,    &mca[ColorNormal]);

      SetIcsOptionEnables(hDlg);
      return TRUE;

  case WM_COMMAND: /* message: received a command */
      switch (LOWORD(wParam)) {

  case WM_USER_GetConsoleBackground: 
      /* the ColorizeTextDialog needs the current background color */
      colorref = (COLORREF *)lParam;
      *colorref = cbc;
      return FALSE;

  case IDOK:
      /* Read changed options from the dialog box */
      GetDlgItemText(hDlg, OPT_IcsAlarmTime, buf, MSG_SIZ);
	  if (swscanf_s(buf, _T("%d"), &number) != 1 || (number < 0)){
		  MessageBox(hDlg, _T("Invalid ICS Alarm Time"),
			  _T("Option Error"), MB_OK | MB_ICONEXCLAMATION);
          return FALSE;
      }

#define IS_CHECKED(x) (Boolean)IsDlgButtonChecked(hDlg, (x))

      appData.icsAlarm         = IS_CHECKED(OPT_IcsAlarm);
      appData.premove          = IS_CHECKED(OPT_Premove);
      appData.premoveWhite     = IS_CHECKED(OPT_PremoveWhite);
      appData.premoveBlack     = IS_CHECKED(OPT_PremoveBlack);
      appData.autoComment      = IS_CHECKED(OPT_AutoComment);
      appData.autoObserve      = IS_CHECKED(OPT_AutoObserve);
      appData.getMoveList      = IS_CHECKED(OPT_GetMoveList);
      appData.localLineEditing = IS_CHECKED(OPT_LocalLineEditing);
      appData.quietPlay        = IS_CHECKED(OPT_QuietPlay);

#undef IS_CHECKED

      appData.icsAlarmTime = number * 1000;
      GetDlgItemText(hDlg, OPT_PremoveWhiteText, appData.premoveWhiteText, 5);
      GetDlgItemText(hDlg, OPT_PremoveBlackText, appData.premoveBlackText, 5);

      if (appData.localLineEditing) {
          DontEcho();
          EchoOn();
      } else {
          DoEcho();
          EchoOff();
      }

      appData.colorize =
          (Boolean)!IsDlgButtonChecked(hDlg, OPT_DontColorize);

      if (!appData.colorize) {
          CHARFORMAT cf;
          COLORREF background = ParseColorName(COLOR_BKGD);
          /*
          SetDefaultTextAttribs();
          Colorize(currentColorClass);
          */
          cf.cbSize = sizeof(CHARFORMAT);
          cf.dwMask = CFM_COLOR;
          cf.crTextColor = ParseColorName(COLOR_NORMAL);

          SendDlgItemMessage(HWND_CONSOLE, OPT_ConsoleInput, 
              EM_SETCHARFORMAT, SCF_ALL, (LPARAM)&cf);
          SendDlgItemMessage(HWND_CONSOLE, OPT_ConsoleText, 
              EM_SETBKGNDCOLOR, FALSE, background);
          SendDlgItemMessage(HWND_CONSOLE, OPT_ConsoleInput, 
              EM_SETBKGNDCOLOR, FALSE, background);
      }

      if (cbc != TAB.consoleBackgroundColor) {
          TAB.consoleBackgroundColor = cbc;
          if (appData.colorize) {
              SendDlgItemMessage(HWND_CONSOLE, OPT_ConsoleText, 
                  EM_SETBKGNDCOLOR, FALSE, TAB.consoleBackgroundColor);
              SendDlgItemMessage(HWND_CONSOLE, OPT_ConsoleInput, 
                  EM_SETBKGNDCOLOR, FALSE, TAB.consoleBackgroundColor);
          }
      }

      for (i=0; i < NColorClasses - 1; i++) {
          appData.AtextAttribs[i].color   = mca[i].color;
          appData.AtextAttribs[i].effects = mca[i].effects;
      }

      EndDialog(hDlg, TRUE);
      return TRUE;

  case IDCANCEL:
      EndDialog(hDlg, FALSE);
      return TRUE;

  case OPT_ChooseShoutColor:
      ColorizeTextPopup(hDlg, ColorShout);
      UpdateSampleText(hDlg, OPT_SampleShout, &mca[ColorShout]);
      break;

  case OPT_ChooseSShoutColor:
      ColorizeTextPopup(hDlg, ColorSShout);
      UpdateSampleText(hDlg, OPT_SampleSShout, &mca[ColorSShout]);
      break;

  case OPT_ChooseChannel1Color:
      ColorizeTextPopup(hDlg, ColorChannel1);
      UpdateSampleText(hDlg, OPT_SampleChannel1, 
          &colorizeAttribs[ColorChannel1]);
      break;

  case OPT_ChooseChannelColor:
      ColorizeTextPopup(hDlg, ColorChannel);
      UpdateSampleText(hDlg, OPT_SampleChannel, &mca[ColorChannel]);
      break;

  case OPT_ChooseKibitzColor:
      ColorizeTextPopup(hDlg, ColorKibitz);
      UpdateSampleText(hDlg, OPT_SampleKibitz, &mca[ColorKibitz]);
      break;

  case OPT_ChooseTellColor:
      ColorizeTextPopup(hDlg, ColorTell);
      UpdateSampleText(hDlg, OPT_SampleTell, &mca[ColorTell]);
      break;

  case OPT_ChooseChallengeColor:
      ColorizeTextPopup(hDlg, ColorChallenge);
      UpdateSampleText(hDlg, OPT_SampleChallenge, &mca[ColorChallenge]);
      break;

  case OPT_ChooseRequestColor:
      ColorizeTextPopup(hDlg, ColorRequest);
      UpdateSampleText(hDlg, OPT_SampleRequest, &mca[ColorRequest]);
      break;

  case OPT_ChooseSeekColor:
      ColorizeTextPopup(hDlg, ColorSeek);
      UpdateSampleText(hDlg, OPT_SampleSeek, &mca[ColorSeek]);
      break;

  case OPT_ChooseNormalColor:
      ColorizeTextPopup(hDlg, ColorNormal);
      UpdateSampleText(hDlg, OPT_SampleNormal, &mca[ColorNormal]);
      break;

  case OPT_ChooseBackgroundColor:
      if (ChangeColor(hDlg, &cbc)) {
          SendDlgItemMessage(hDlg, OPT_SampleShout,     EM_SETBKGNDCOLOR, 0, cbc);
          SendDlgItemMessage(hDlg, OPT_SampleSShout,    EM_SETBKGNDCOLOR, 0, cbc);
          SendDlgItemMessage(hDlg, OPT_SampleChannel1,  EM_SETBKGNDCOLOR, 0, cbc);
          SendDlgItemMessage(hDlg, OPT_SampleChannel,   EM_SETBKGNDCOLOR, 0, cbc);
          SendDlgItemMessage(hDlg, OPT_SampleKibitz,    EM_SETBKGNDCOLOR, 0, cbc);
          SendDlgItemMessage(hDlg, OPT_SampleTell,      EM_SETBKGNDCOLOR, 0, cbc);
          SendDlgItemMessage(hDlg, OPT_SampleChallenge, EM_SETBKGNDCOLOR, 0, cbc);
          SendDlgItemMessage(hDlg, OPT_SampleRequest,   EM_SETBKGNDCOLOR, 0, cbc);
          SendDlgItemMessage(hDlg, OPT_SampleSeek,      EM_SETBKGNDCOLOR, 0, cbc);
          SendDlgItemMessage(hDlg, OPT_SampleNormal,    EM_SETBKGNDCOLOR, 0, cbc);
      }
      break;

  case OPT_DefaultColors:
      for (i=0; i < NColorClasses - 1; i++)
          ParseAttribs(&mca[i].color, 
          &mca[i].effects,
          defaultTextAttribs[i]);

      cbc = ParseColorName(COLOR_BKGD);
      SendDlgItemMessage(hDlg, OPT_SampleShout,     EM_SETBKGNDCOLOR, 0, cbc);
      SendDlgItemMessage(hDlg, OPT_SampleSShout,    EM_SETBKGNDCOLOR, 0, cbc);
      SendDlgItemMessage(hDlg, OPT_SampleChannel1,  EM_SETBKGNDCOLOR, 0, cbc);
      SendDlgItemMessage(hDlg, OPT_SampleChannel,   EM_SETBKGNDCOLOR, 0, cbc);
      SendDlgItemMessage(hDlg, OPT_SampleKibitz,    EM_SETBKGNDCOLOR, 0, cbc);
      SendDlgItemMessage(hDlg, OPT_SampleTell,      EM_SETBKGNDCOLOR, 0, cbc);
      SendDlgItemMessage(hDlg, OPT_SampleChallenge, EM_SETBKGNDCOLOR, 0, cbc);
      SendDlgItemMessage(hDlg, OPT_SampleRequest,   EM_SETBKGNDCOLOR, 0, cbc);
      SendDlgItemMessage(hDlg, OPT_SampleSeek,      EM_SETBKGNDCOLOR, 0, cbc);
      SendDlgItemMessage(hDlg, OPT_SampleNormal,    EM_SETBKGNDCOLOR, 0, cbc);

      UpdateSampleText(hDlg, OPT_SampleShout,     &mca[ColorShout]);
      UpdateSampleText(hDlg, OPT_SampleSShout,    &mca[ColorSShout]);
      UpdateSampleText(hDlg, OPT_SampleChannel1,  &mca[ColorChannel1]);
      UpdateSampleText(hDlg, OPT_SampleChannel,   &mca[ColorChannel]);
      UpdateSampleText(hDlg, OPT_SampleKibitz,    &mca[ColorKibitz]);
      UpdateSampleText(hDlg, OPT_SampleTell,      &mca[ColorTell]);
      UpdateSampleText(hDlg, OPT_SampleChallenge, &mca[ColorChallenge]);
      UpdateSampleText(hDlg, OPT_SampleRequest,   &mca[ColorRequest]);
      UpdateSampleText(hDlg, OPT_SampleSeek,      &mca[ColorSeek]);
      UpdateSampleText(hDlg, OPT_SampleNormal,    &mca[ColorNormal]);
      break;

  default:
      SetIcsOptionEnables(hDlg);
      break;
      }
      break;
    }
    return FALSE;
}

void
IcsOptionsPopup(HWND hwnd)
{
    FARPROC lpProc = MakeProcInstance((FARPROC)IcsOptionsDialog, hInst);
    DialogBox(hInst, MAKEINTRESOURCE(DLG_IcsOptions), hwnd,
        (DLGPROC) lpProc);
    FreeProcInstance(lpProc);
}

/*---------------------------------------------------------------------------*\
*
* Fonts Dialog functions
*
\*---------------------------------------------------------------------------*/

void
SetSampleFontText(HWND hwnd, int id, const MyFont *mf)
{
    TCHAR buf[MSG_SIZ];
    HWND hControl;
    HDC hdc;
    CHARFORMAT cf;
    SIZE size;
    RECT rectClient, rectFormat;
    HFONT oldFont;
    POINT center;
    int len;

    //len = sprintf(buf, "%.0f pt. %s%s%s\n",
    //mf->mfp.pointSize, mf->mfp.faceName,
    //mf->mfp.bold ? " bold" : "",
    //mf->mfp.italic ? " italic" : "");
    len = StringCbPrintf(buf,MSG_SIZ,
        _T("%.0f pt. %s%s%s\n"),
        mf->mfp.pointSize, mf->mfp.faceName,
        mf->mfp.bold ? " bold" : "",
        mf->mfp.italic ? " italic" : "");
    SetDlgItemText(hwnd, id, buf);

    hControl = GetDlgItem(hwnd, id);
    hdc = GetDC(hControl);
    SetMapMode(hdc, MM_TEXT);	/* 1 pixel == 1 logical unit */
    oldFont = (HFONT)SelectObject(hdc, mf->hf);

    /* get number of logical units necessary to display font name */
    GetTextExtentPoint32(hdc, buf, len, &size);

    /* calculate formatting rectangle in the rich edit control.  
    * May be larger or smaller than the actual control.
    */
    GetClientRect(hControl, &rectClient);
    center.x = (rectClient.left + rectClient.right) / 2;
    center.y = (rectClient.top  + rectClient.bottom) / 2;
    rectFormat.top    = center.y - (size.cy / 2) - 1;
    rectFormat.bottom = center.y + (size.cy / 2) + 1;
    rectFormat.left   = center.x - (size.cx / 2) - 1;
    rectFormat.right  = center.x + (size.cx / 2) + 1;

#if 0
    fprintf(debugFP, "\nfont: %s\n"
        "center.x   %d, centerY %d\n"
        "size.cx    %d, size.cy %d\n"
        "client.top %d, bottom %d, left %d, right %d\n"
        "format.top %d, bottom %d, left %d, right %d\n",
        buf,
        center.x, center.y,
        size.cx, size.cy,
        rectClient.top, rectClient.bottom, rectClient.left,
        rectClient.right,
        rectFormat.top, rectFormat.bottom, rectFormat.left,
        rectFormat.right);
#endif

    cf.cbSize = sizeof(CHARFORMAT);
    cf.dwMask = CFM_FACE|CFM_SIZE|CFM_CHARSET|CFM_BOLD|CFM_ITALIC;
    cf.dwEffects = 0;
    if (mf->lf.lfWeight == FW_BOLD) cf.dwEffects |= CFE_BOLD;
    if (mf->lf.lfItalic) cf.dwEffects |= CFE_ITALIC;
    //strcpy(cf.szFaceName, mf->mfp.faceName);
    StringCbCopy(cf.szFaceName,32, mf->mfp.faceName);
    /*
    * yHeight is expressed in twips.  A twip is 1/20 of a font's point
    * size. See documentation of CHARFORMAT.  --msw
    */
    cf.yHeight = (int)(mf->mfp.pointSize * 20.0 + 0.5);
    cf.bCharSet = mf->lf.lfCharSet;
    cf.bPitchAndFamily = mf->lf.lfPitchAndFamily;

    /* format the text in the rich edit control */
    SendMessage(hControl, EM_SETCHARFORMAT, SCF_ALL, (LPARAM) &cf);
    SendMessage(hControl, EM_SETRECT, (WPARAM)0, (LPARAM) &rectFormat);

    /* clean up */
    SelectObject(hdc, oldFont);
    ReleaseDC(hControl, hdc);
}

void
CopyFont(MyFont *dest, const MyFont *src)
{
    dest->mfp.pointSize = src->mfp.pointSize;
    dest->mfp.bold      = src->mfp.bold;
    dest->mfp.italic    = src->mfp.italic;
    dest->mfp.underline = src->mfp.underline;
    dest->mfp.strikeout = src->mfp.strikeout;
    //lstrcpy(dest->mfp.faceName, src->mfp.faceName);
    StringCbCopy(dest->mfp.faceName,32,src->mfp.faceName);
    CreateFontInMF(dest);
}


LRESULT CALLBACK
FontOptionsDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
     dispboard_t* pDis = OBS[0];
	static MyFont workFont[NUM_FONTS];
    static BOOL firstPaint;
    int i;
    //RECT rect;

    switch (message) {
  case WM_INITDIALOG:

      /* copy the current font settings into a working copy */
      for (i=0; i < NUM_FONTS; i++)
          CopyFont(&workFont[i], appData.Afont[pDis->bsize][i]);

      if (!appData.icsActive)
          EnableWindow(GetDlgItem(hDlg, OPT_ChooseConsoleFont), FALSE);

      firstPaint = TRUE;	/* see rant below */

      /* If I don't call SetFocus(), the dialog won't respond to the keyboard
      * when first drawn. Why is this the only dialog that behaves this way? Is
      * is the WM_PAINT stuff below?? Sigh...
      */
      SetFocus(GetDlgItem(hDlg, IDOK));
      break;

  case WM_PAINT:
      /* This should not be necessary. However, if SetSampleFontText() is called
      * in response to WM_INITDIALOG, the strings are not properly centered in
      * the controls when the dialog first appears. I can't figure out why, so
      * this is the workaround.  --msw
      */
      if (firstPaint) {
          SetSampleFontText(hDlg, OPT_SampleClockFont, &workFont[CLOCK_FONT]);
          SetSampleFontText(hDlg, OPT_SampleMessageFont, &workFont[MESSAGE_FONT]);
          SetSampleFontText(hDlg, OPT_SampleCoordFont, &workFont[COORD_FONT]);
          SetSampleFontText(hDlg, OPT_SampleTagFont, &workFont[EDITTAGS_FONT]);
          SetSampleFontText(hDlg, OPT_SampleCommentsFont, &workFont[COMMENT_FONT]);
          SetSampleFontText(hDlg, OPT_SampleConsoleFont, &workFont[CONSOLE_FONT]);
          firstPaint = FALSE;
      }
      break;

  case WM_COMMAND: /* message: received a command */
      switch (LOWORD(wParam)) {

  case IDOK:
      /* again, it seems to avoid redraw problems if we call EndDialog first */
      EndDialog(hDlg, FALSE);

      /* copy modified settings back to the fonts array */
      for (i=0; i < NUM_FONTS; i++)
          CopyFont(appData.Afont[pDis->bsize][i], &workFont[i]);

      /* a sad necessity due to the original design of having a separate
      * console font, tags font, and comment font for each board size.  IMHO
      * these fonts should not be dependent on the current board size.  I'm
      * running out of time, so I am doing this hack rather than redesign the
      * data structure. Besides, I think if I redesigned the data structure, I
      * might break backwards compatibility with old winboard.ini files.
      * --msw
      */
      for (i=0; i < NUM_SIZES; i++) {
          CopyFont(appData.Afont[i][EDITTAGS_FONT], &workFont[EDITTAGS_FONT]);
          CopyFont(appData.Afont[i][CONSOLE_FONT],  &workFont[CONSOLE_FONT]);
          CopyFont(appData.Afont[i][COMMENT_FONT],  &workFont[COMMENT_FONT]);
      }
      /* end sad necessity */

      //InitDrawingSizes(boardSize, 0);
      InvalidateRect(pDis->hwndThis, NULL, TRUE);

      //     if (DIS.commentDialog) {
      //SendDlgItemMessage(DIS.commentDialog, OPT_CommentText,
      //	WM_SETFONT, (WPARAM)DIS.font[DIS.bsize][COMMENT_FONT]->hf, 
      //  MAKELPARAM(TRUE, 0));
      //GetClientRect(GetDlgItem(DIS.commentDialog, OPT_CommentText), &rect);
      //InvalidateRect(DIS.commentDialog, &rect, TRUE);
      //     }

      //     if (DIS.editTagsDialog) {
      //SendDlgItemMessage(DIS.editTagsDialog, OPT_TagsText,
      //	WM_SETFONT, (WPARAM)DIS.font[DIS.bsize][EDITTAGS_FONT]->hf, 
      //  MAKELPARAM(TRUE, 0));
      //GetClientRect(GetDlgItem(DIS.editTagsDialog, OPT_TagsText), &rect);
      //InvalidateRect(DIS.editTagsDialog, &rect, TRUE);
      //     }

      if (HWND_CONSOLE) {
          ChangedConsoleFont();
      }

      for (i=0; i<NUM_FONTS; i++)
          DeleteObject(&workFont[i].hf);

      return TRUE;

  case IDCANCEL:
      for (i=0; i<NUM_FONTS; i++)
          DeleteObject(&workFont[i].hf);
      EndDialog(hDlg, FALSE);
      return TRUE;

  case OPT_ChooseClockFont:
      MyCreateFont(hDlg, &workFont[CLOCK_FONT]);
      SetSampleFontText(hDlg, OPT_SampleClockFont, &workFont[CLOCK_FONT]);
      break;

  case OPT_ChooseMessageFont:
      MyCreateFont(hDlg, &workFont[MESSAGE_FONT]);
      SetSampleFontText(hDlg, OPT_SampleMessageFont, &workFont[MESSAGE_FONT]);
      break;

  case OPT_ChooseCoordFont:
      MyCreateFont(hDlg, &workFont[COORD_FONT]);
      SetSampleFontText(hDlg, OPT_SampleCoordFont, &workFont[COORD_FONT]);
      break;

  case OPT_ChooseTagFont:
      MyCreateFont(hDlg, &workFont[EDITTAGS_FONT]);
      SetSampleFontText(hDlg, OPT_SampleTagFont, &workFont[EDITTAGS_FONT]);
      break;

  case OPT_ChooseCommentsFont:
      MyCreateFont(hDlg, &workFont[COMMENT_FONT]);
      SetSampleFontText(hDlg, OPT_SampleCommentsFont, &workFont[COMMENT_FONT]);
      break;

  case OPT_ChooseConsoleFont:
      MyCreateFont(hDlg, &workFont[CONSOLE_FONT]);
      SetSampleFontText(hDlg, OPT_SampleConsoleFont, &workFont[CONSOLE_FONT]);
      break;

  case OPT_DefaultFonts:
      for (i=0; i<NUM_FONTS; i++) {
          DeleteObject(&workFont[i].hf);
		  ParseFontName(appData.Afont[pDis->bsize][i]->def, &workFont[i].mfp);
          CreateFontInMF(&workFont[i]);
      }
      SetSampleFontText(hDlg, OPT_SampleClockFont, &workFont[CLOCK_FONT]);
      SetSampleFontText(hDlg, OPT_SampleMessageFont, &workFont[MESSAGE_FONT]);
      SetSampleFontText(hDlg, OPT_SampleCoordFont, &workFont[COORD_FONT]);
      SetSampleFontText(hDlg, OPT_SampleTagFont, &workFont[EDITTAGS_FONT]);
      SetSampleFontText(hDlg, OPT_SampleCommentsFont, &workFont[COMMENT_FONT]);
      SetSampleFontText(hDlg, OPT_SampleConsoleFont, &workFont[CONSOLE_FONT]);
      break;
      }
    }
    return FALSE;
}

void
FontsOptionsPopup(HWND hwnd)
{
    FARPROC lpProc = MakeProcInstance((FARPROC)FontOptionsDialog, hInst);
    DialogBox(hInst, MAKEINTRESOURCE(DLG_Fonts), hwnd,
        (DLGPROC) lpProc);
    FreeProcInstance(lpProc);
}

/*---------------------------------------------------------------------------*\
*
* Sounds Dialog functions
*
\*---------------------------------------------------------------------------*/


//SoundComboData soundComboData[] = {
//    {"Move", NULL},
//    {"Bell", NULL},
//    {"ICS Alarm", NULL},
//    {"ICS Win", NULL},
//    {"ICS Loss", NULL},
//    {"ICS Draw", NULL},
//    {"ICS Unfinished", NULL},
//    {"Shout", NULL},
//    {"SShout/CShout", NULL},
//    {"Channel 1", NULL},
//    {"Channel", NULL},
//    {"Kibitz", NULL},
//    {"Tell", NULL},
//    {"Challenge", NULL},
//    {"Request", NULL},
//    {"Seek", NULL},
//    {NULL, NULL},
//};


//void
//InitSoundComboData(SoundComboData *scd)
//{
//    int sc;  //SoundClass sc;
//    int cc;  //ColorClass cc;
//    int index;
//
//    /* copy current sound settings to combo array */
//
//    //for ( sc = (SoundClass)0; sc < NSoundClasses; sc++) {
//    //    scd[sc].name = _strdup(appData.Asounds[sc].name);
//    //}
//    //for ( cc = (ColorClass)0; cc < NColorClasses - 2; cc++) {
//    //    index = (int)cc + (int)NSoundClasses;
//    //    scd[index].name = _strdup(appData.AtextAttribs[cc].sound.name);
//    //}
//}


//void
//ResetSoundComboData(SoundComboData *scd)
//{
//    //while (scd->label) {
//    //    if (scd->name != NULL) {
//    //        free (scd->name);
//    //        scd->name = NULL;
//    //    }
//    //    scd++;
//    //}
//}

//void
//InitSoundCombo(HWND hwndCombo, SoundComboData *scd)
//{
//    //char buf[255];
//    //DWORD err;
//    //DWORD cnt = 0;
//    //SendMessage(hwndCombo, CB_RESETCONTENT, 0, 0);
//
//    ///* send the labels to the combo box */
//    //while (scd->label) {
//    //    err = (DWORD)SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM) scd->label);
//    //    if (err != cnt++) {
//    //        //sprintf(buf, "InitSoundCombo(): err '%d', cnt '%d'\n",
//    //        //err, cnt);
//    //        StringCbPrintf(buf,255,"InitSoundCombo(): err '%d', cnt '%d'\n",
//    //            err, cnt);
//    //        MessageBox(NULL, buf, NULL, MB_OK);
//    //    }
//    //    scd++;
//    //}
//    //SendMessage(hwndCombo, CB_SETCURSEL, (WPARAM) 0, (LPARAM) 0);
//}
//
//int
//SoundDialogWhichRadio(HWND hDlg)
//{
//    if (IsDlgButtonChecked(hDlg, OPT_NoSound)) return OPT_NoSound;
//    if (IsDlgButtonChecked(hDlg, OPT_DefaultBeep)) return OPT_DefaultBeep;
//    if (IsDlgButtonChecked(hDlg, OPT_BuiltInSound)) return OPT_BuiltInSound;
//    if (IsDlgButtonChecked(hDlg, OPT_WavFile)) return OPT_WavFile;
//    return -1;
//}

//VOID
//SoundDialogSetEnables(HWND hDlg, int radio)
//{
//    EnableWindow(GetDlgItem(hDlg, OPT_BuiltInSoundName),
//        radio == OPT_BuiltInSound);
//    EnableWindow(GetDlgItem(hDlg, OPT_WavFileName), radio == OPT_WavFile);
//    EnableWindow(GetDlgItem(hDlg, OPT_BrowseSound), radio == OPT_WavFile);
//}

//char *
//SoundDialogGetName(HWND hDlg, int radio)
//{
//    static char buf[MSG_SIZ], buf2[MSG_SIZ], buf3[MSG_SIZ];
//    char *dummy, *ret;
//    switch (radio) {
//  case OPT_NoSound:
//  default:
//      return "";
//  case OPT_DefaultBeep:
//      return "$";
//  case OPT_BuiltInSound:
//      buf[0] = '!';
//      GetDlgItemText(hDlg, OPT_BuiltInSoundName, buf + 1, sizeof(buf) - 1);
//      return buf;
//  case OPT_WavFile:
//      GetDlgItemText(hDlg, OPT_WavFileName, buf, sizeof(buf));
//      GetCurrentDirectory(MSG_SIZ, buf3);
//      SetCurrentDirectory(installDir);
//      if (GetFullPathName(buf, MSG_SIZ, buf2, &dummy)) {
//          ret = buf2;
//      } else {
//          ret = buf;
//      }
//      SetCurrentDirectory(buf3);
//      return ret;
//    }
//}

//void
//DisplaySelectedSound(HWND hDlg, HWND hCombo, const char *name)
//{
//    int radio;
//    /* 
//    * I think it's best to clear the combo and edit boxes. It looks stupid
//    * to have a value from another sound event sitting there grayed out.
//    */
//    SetDlgItemText(hDlg, OPT_WavFileName, "");
//    SendMessage(hCombo, CB_SETCURSEL, (WPARAM) -1, (LPARAM) 0);
//
//#ifdef DEBUG_USE_DEBUG_FILE
//    //if (appData.debugMode)
//        fprintf(appData.debugFP, "DisplaySelectedSound(,,'%s'):\n", name);
//#endif
//
//
//    switch (name[0]) {
//  case NULLCHAR:
//      radio = OPT_NoSound;
//      break;
//  case '$':
//      if (name[1] == NULLCHAR) {
//          radio = OPT_DefaultBeep;
//      } else {
//          radio = OPT_WavFile;
//          SetDlgItemText(hDlg, OPT_WavFileName, name);
//      }
//      break;
//  case '!':
//      if (name[1] == NULLCHAR) {
//          radio = OPT_NoSound;
//      } else {
//          radio = OPT_BuiltInSound;
//          if (SendMessage(hCombo, CB_SELECTSTRING, (WPARAM) -1, 
//              (LPARAM) (name + 1)) == CB_ERR) {
//                  SendMessage(hCombo, CB_SETCURSEL, (WPARAM) -1, (LPARAM) 0);
//                  SendMessage(hCombo, WM_SETTEXT, (WPARAM) 0, (LPARAM) (name + 1));
//          }
//      }
//      break;
//  default:
//      radio = OPT_WavFile;
//      SetDlgItemText(hDlg, OPT_WavFileName, name);
//      break;
//    }
//    SoundDialogSetEnables(hDlg, radio);
//    CheckRadioButton(hDlg, OPT_NoSound, OPT_WavFile, radio);
//}
//
//
//char *builtInSoundNames[] = BUILT_IN_SOUND_NAMES;
//
//LRESULT CALLBACK
//SoundOptionsDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    static HWND hSoundCombo;
//    static DWORD index;
//    static HWND hBISN;
//    int radio;
//    MySound tmp;
//    FILE *f;
//    char buf[MSG_SIZ];
//    char *newName;
//    int sc;		//SoundClass sc;
//    int cc;    	//ColorClass cc;
//    SoundComboData *scd;
//
//    switch (message) {
//  case WM_INITDIALOG:
//      /* Center the dialog over the application window */
//      CenterWindow (hDlg, GetWindow (hDlg, GW_OWNER));
//
//      /* Initialize the built-in sounds combo */
//      hBISN = GetDlgItem(hDlg, OPT_BuiltInSoundName);
//      // InitComboStrings(hBISN, builtInSoundNames);
//
//      /* Initialize the  sound events combo */
//      index = 0;
//      InitSoundComboData(soundComboData);
//      hSoundCombo = GetDlgItem(hDlg, CBO_Sounds);
//      InitSoundCombo(hSoundCombo, soundComboData);
//
//      /* update the dialog */
//      DisplaySelectedSound(hDlg, hBISN, soundComboData[index].name);
//      return TRUE;
//
//  case WM_COMMAND: /* message: received a command */
//
//      if (((HWND)lParam == hSoundCombo) && 
//          (HIWORD(wParam) == CBN_SELCHANGE)) {
//              /* 
//              * the user has selected a new sound event. We must store the name for
//              * the previously selected event, then retrieve the name for the
//              * newly selected event and update the dialog. 
//              */
//              radio = SoundDialogWhichRadio(hDlg);
//              newName = _strdup(SoundDialogGetName(hDlg, radio));
//
//              if (strcmp(newName, soundComboData[index].name) != 0) {
//                  free(soundComboData[index].name);
//                  soundComboData[index].name = newName;
//              } else {
//                  free(newName);
//                  newName = NULL;
//              }
//              /* now get the settings for the newly selected event */
//              index = (DWORD)SendMessage(hSoundCombo, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
//              DisplaySelectedSound(hDlg, hBISN, soundComboData[index].name);
//
//              return TRUE;
//      }
//      switch (LOWORD(wParam)) {
//  case IDOK:
//      /* 
//      * save the name for the currently selected sound event 
//      */
//      radio = SoundDialogWhichRadio(hDlg);
//      newName = _strdup(SoundDialogGetName(hDlg, radio));
//
//      if (strcmp(soundComboData[index].name, newName) != 0) {
//          free(soundComboData[index].name);
//          soundComboData[index].name = newName;
//      } else {
//          free(newName);
//          newName = NULL;
//      }
//
//      /* save all the sound names that changed and load the sounds */
//
//      //for ( sc = (SoundClass)0; sc < NSoundClasses; sc++) {
//      //    if (strcmp(soundComboData[sc].name, appData.Asounds[sc].name) != 0) {
//      //        free(appData.Asounds[sc].name);
//      //        appData.Asounds[sc].name = _strdup(soundComboData[sc].name);
//      //        MyLoadSound(&appData.Asounds[sc]);
//      //    }
//      //}
//      for ( cc = (ColorClass)0; cc < NColorClasses - 2; cc++) {
//          index = (int)cc + (int)NSoundClasses;
//          if (strcmp(soundComboData[index].name, 
//              appData.AtextAttribs[cc].sound.name) != 0) {
//                  free(appData.AtextAttribs[cc].sound.name);
//                  appData.AtextAttribs[cc].sound.name = _strdup(soundComboData[index].name);
//                  MyLoadSound(&appData.AtextAttribs[cc].sound);
//          }
//      }
//
//      ResetSoundComboData(soundComboData);
//      EndDialog(hDlg, TRUE);
//      return TRUE;
//
//  case IDCANCEL:
//      ResetSoundComboData(soundComboData);
//      EndDialog(hDlg, FALSE);
//      return TRUE;
//
//  case OPT_DefaultSounds:
//      /* can't use SetDefaultSounds() because we need to be able to "undo" if
//      * user selects "Cancel" later on. So we do it the hard way here.
//      */
//      scd = &soundComboData[0];
//      while (scd->label != NULL) {
//          if (scd->name != NULL) free(scd->name);
//          scd->name = _strdup("");
//          scd++;
//      }
//      free(soundComboData[(int)SoundBell].name);
//      soundComboData[(int)SoundBell].name = _strdup(SOUND_BELL);
//      DisplaySelectedSound(hDlg, hBISN, soundComboData[index].name);
//      break;
//
//  case OPT_PlaySound:
//      radio = SoundDialogWhichRadio(hDlg);
//      tmp.name = _strdup(SoundDialogGetName(hDlg, radio));
//      tmp.data = NULL;
//      MyLoadSound(&tmp);
//      MyPlaySound(&tmp);
//      if (tmp.data  != NULL) free(tmp.data);
//      if (tmp.name != NULL) free(tmp.name);
//      return TRUE;
//
//  case OPT_BrowseSound:
//      f = OpenFileDialog(hDlg, FALSE, NULL, "wav", SOUND_FILT,
//          "Browse for Sound File", NULL, NULL, buf);
//      if (f != NULL) {
//          fclose(f);
//          SetDlgItemText(hDlg, OPT_WavFileName, buf);
//      }
//      return TRUE;
//
//  default:
//      radio = SoundDialogWhichRadio(hDlg);
//      SoundDialogSetEnables(hDlg, radio);
//      break;
//      }
//      break;
//    }
//    return FALSE;
//}
//
//
//VOID SoundOptionsPopup(HWND hwnd)
//{
//    FARPROC lpProc;
//
//    lpProc = MakeProcInstance((FARPROC)SoundOptionsDialog, hInst);
//    DialogBox(hInst, MAKEINTRESOURCE(DLG_Sound), hwnd, (DLGPROC)lpProc);
//    FreeProcInstance(lpProc);
//}


/*---------------------------------------------------------------------------*\
*
* Comm Port dialog functions
*
\*---------------------------------------------------------------------------*/


#define FLOW_NONE   0
#define FLOW_XOFF   1
#define FLOW_CTS    2
#define FLOW_DSR    3

#define PORT_NONE

ComboData cdPort[]     = { {"None", PORT_NONE}, {"COM1", 1}, {"COM2", 2},
{"COM3", 3}, {"COM4", 4}, {NULL, 0} };
ComboData cdDataRate[] = { {"110", 110}, {"300", 300}, {"600", 600}, {"1200", 1200},
{"2400", 2400}, {"4800", 4800}, {"9600", 9600}, {"19200", 19200},
{"38400", 38400}, {NULL, 0} };
ComboData cdDataBits[] = { {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8}, {NULL, 0} };
ComboData cdParity[]   = { {"None", NOPARITY}, {"Odd", ODDPARITY}, {"Even", EVENPARITY},
{"Mark", MARKPARITY}, {"Space", SPACEPARITY}, {NULL, 0} };
ComboData cdStopBits[] = { {"1", ONESTOPBIT}, {"1.5", ONE5STOPBITS},
{"2", TWOSTOPBITS}, {NULL, 0} };
ComboData cdFlow[]     = { {"None", FLOW_NONE}, {"Xoff/Xon", FLOW_XOFF}, {"CTS", FLOW_CTS},
{"DSR", FLOW_DSR}, {NULL, 0} };


void
ParseCommSettings(char *arg, DCB *dcb)
{
    int dataRate, count;
    char bits[MSG_SIZ], parity[MSG_SIZ], stopBits[MSG_SIZ], flow[MSG_SIZ];
    ComboData *cd;
    count = sscanf_s(arg, "%d%*[, ]%[^, ]%*[, ]%[^, ]%*[, ]%[^, ]%*[, ]%[^, ]",
        &dataRate, bits,(int)sizeof(bits), parity, (int)sizeof(parity), stopBits, (int)sizeof(stopBits), flow, (int)sizeof(flow));
    if (count != 5) goto cant_parse;
    dcb->BaudRate = dataRate;
    cd = cdDataBits;
    while (cd->label != NULL) {
        if (StrCaseCmp(cd->label, bits) == 0) {
            dcb->ByteSize = cd->value;
            break;
        }
        cd++;
    }
    if (cd->label == NULL) goto cant_parse;
    cd = cdParity;
    while (cd->label != NULL) {
        if (StrCaseCmp(cd->label, parity) == 0) {
            dcb->Parity = cd->value;
            break;
        }
        cd++;
    }
    if (cd->label == NULL) goto cant_parse;
    cd = cdStopBits;
    while (cd->label != NULL) {
        if (StrCaseCmp(cd->label, stopBits) == 0) {
            dcb->StopBits = cd->value;
            break;
        }
        cd++;
    }
    cd = cdFlow;
    if (cd->label == NULL) goto cant_parse;
    while (cd->label != NULL) {
        if (StrCaseCmp(cd->label, flow) == 0) {
            switch (cd->value) {
      case FLOW_NONE:
          dcb->fOutX = FALSE;
          dcb->fOutxCtsFlow = FALSE;
          dcb->fOutxDsrFlow = FALSE;
          break;
      case FLOW_CTS:
          dcb->fOutX = FALSE;
          dcb->fOutxCtsFlow = TRUE;
          dcb->fOutxDsrFlow = FALSE;
          break;
      case FLOW_DSR:
          dcb->fOutX = FALSE;
          dcb->fOutxCtsFlow = FALSE;
          dcb->fOutxDsrFlow = TRUE;
          break;
      case FLOW_XOFF:
          dcb->fOutX = TRUE;
          dcb->fOutxCtsFlow = FALSE;
          dcb->fOutxDsrFlow = FALSE;
          break;
            }
            break;
        }
        cd++;
    }
    if (cd->label == NULL) goto cant_parse;
    return;
cant_parse:
    ExitArgError(_T("Can't parse com port settings"), CA2W(arg));
}


void
PrintCommSettings(FILE *f, char *name, DCB *dcb)
{
    char *flow = "??", *parity = "??", *stopBits = "??";
    ComboData *cd;

    cd = cdParity;
    while (cd->label != NULL) {
        if (dcb->Parity == cd->value) {
            parity = cd->label;
            break;
        }
        cd++;
    }
    cd = cdStopBits;
    while (cd->label != NULL) {
        if (dcb->StopBits == cd->value) {
            stopBits = cd->label;
            break;
        }
        cd++;
    }
    if (dcb->fOutX) {
        flow = cdFlow[FLOW_XOFF].label;
    } else if (dcb->fOutxCtsFlow) {
        flow = cdFlow[FLOW_CTS].label;
    } else if (dcb->fOutxDsrFlow) {
        flow = cdFlow[FLOW_DSR].label;
    } else {
        flow = cdFlow[FLOW_NONE].label;
    }
    fprintf(f, "/%s=%d,%d,%s,%s,%s\n", name,
        dcb->BaudRate, dcb->ByteSize, parity, stopBits, flow);
}


void
InitCombo(HWND hwndCombo, ComboData *cd)
{
    SendMessage(hwndCombo, CB_RESETCONTENT, 0, 0);

    while (cd->label != NULL) {
        SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM) cd->label);
        cd++;
    }
}

void
SelectComboValue(HWND hwndCombo, ComboData *cd, unsigned value)
{
    int i;

    i = 0;
    while (cd->label != NULL) {
        if (cd->value == value) {
            SendMessage(hwndCombo, CB_SETCURSEL, (WPARAM) i, (LPARAM) 0);
            return;
        }
        cd++;
        i++;
    }
}

LRESULT CALLBACK
CommPortOptionsDialog(HWND hDlg, UINT message, WPARAM wParam,	LPARAM lParam)
{
//    char buf[MSG_SIZ];
//    HWND hwndCombo;
//    char *p;
//    LRESULT index;
//    unsigned value;
//    int err;
//
//    switch (message) {
//  case WM_INITDIALOG: /* message: initialize dialog box */
//      /* Center the dialog over the application window */
//      CenterWindow (hDlg, GetWindow(hDlg, GW_OWNER));
//      /* Initialize the dialog items */
//      /* !! There should probably be some synchronization
//      in accessing hCommPort and dcb.  Or does modal nature
//      of this dialog box do it for us?
//      */
//      hwndCombo = GetDlgItem(hDlg, OPT_Port);
//      InitCombo(hwndCombo, cdPort);
//      p = strrchr(appData.icsCommPort, '\\');
//      if (p++ == NULL) p = appData.icsCommPort;
//      if ((*p == '\0') ||
//          (SendMessage(hwndCombo, CB_SELECTSTRING, (WPARAM) -1, (LPARAM) p) == CB_ERR)) {
//              SendMessage(hwndCombo, CB_SELECTSTRING, (WPARAM) -1, (LPARAM) "None");
//      }
//      EnableWindow(hwndCombo, MAIN.hCommPort == NULL); /*!! don't allow change for now*/
//
//      hwndCombo = GetDlgItem(hDlg, OPT_DataRate);
//      InitCombo(hwndCombo, cdDataRate);
//      //sprintf(buf, "%u", dcb.BaudRate);
//      StringCbPrintf(buf,MSG_SIZ,"%u", MAIN.dcb.BaudRate);
//      if (SendMessage(hwndCombo, CB_SELECTSTRING, (WPARAM) -1, (LPARAM) buf) == CB_ERR) {
//          SendMessage(hwndCombo, CB_SETCURSEL, (WPARAM) -1, (LPARAM) 0);
//          SendMessage(hwndCombo, WM_SETTEXT, (WPARAM) 0, (LPARAM) buf);
//      }
//
//      hwndCombo = GetDlgItem(hDlg, OPT_Bits);
//      InitCombo(hwndCombo, cdDataBits);
//      SelectComboValue(hwndCombo, cdDataBits, MAIN.dcb.ByteSize);
//
//      hwndCombo = GetDlgItem(hDlg, OPT_Parity);
//      InitCombo(hwndCombo, cdParity);
//      SelectComboValue(hwndCombo, cdParity, MAIN.dcb.Parity);
//
//      hwndCombo = GetDlgItem(hDlg, OPT_StopBits);
//      InitCombo(hwndCombo, cdStopBits);
//      SelectComboValue(hwndCombo, cdStopBits, MAIN.dcb.StopBits);
//
//      hwndCombo = GetDlgItem(hDlg, OPT_Flow);
//      InitCombo(hwndCombo, cdFlow);
//      if (DIS.dcb.fOutX) {
//          SelectComboValue(hwndCombo, cdFlow, FLOW_XOFF);
//      } else if (DIS.dcb.fOutxCtsFlow) {
//          SelectComboValue(hwndCombo, cdFlow, FLOW_CTS);
//      } else if (DIS.dcb.fOutxDsrFlow) {
//          SelectComboValue(hwndCombo, cdFlow, FLOW_DSR);
//      } else {
//          SelectComboValue(hwndCombo, cdFlow, FLOW_NONE);
//      }
//      return TRUE;
//
//  case WM_COMMAND: /* message: received a command */
//      switch (LOWORD(wParam)) {
//  case IDOK:
//      /* Read changed options from the dialog box */
//#ifdef NOTDEF
//      /* !! Currently we can't change comm ports in midstream */
//      hwndCombo = GetDlgItem(hDlg, OPT_Port);
//      index = SendMessage(hwndCombo, CB_GETCURSEL, (WPARAM) 0, (LPARAM) 0);
//      if (index == PORT_NONE) {
//          appData.icsCommPort = "";
//          if (hCommPort != NULL) {
//              CloseHandle(hCommPort);
//              hCommPort = NULL;
//          }
//          EndDialog(hDlg, TRUE);
//          return TRUE;
//      }
//      SendMessage(hwndCombo, WM_GETTEXT, (WPARAM) MSG_SIZ, (LPARAM) buf);
//      appData.icsCommPort = strdup(buf);
//      if (hCommPort != NULL) {
//          CloseHandle(hCommPort);
//          hCommPort = NULL;
//      }
//      /* now what?? can't really do this; have to fix up the ChildProc
//      and InputSource records for the comm port that we gave to the
//      back end. */
//#endif /*NOTDEF*/
//
//      hwndCombo = GetDlgItem(hDlg, OPT_DataRate);
//      SendMessage(hwndCombo, WM_GETTEXT, (WPARAM) MSG_SIZ, (LPARAM) buf);
//      if (sscanf_s(buf, "%u", &value) != 1) {
//          MessageBox(hDlg, "Invalid data rate",
//              "Option Error", MB_OK|MB_ICONEXCLAMATION);
//          return TRUE;
//      }
//      DIS.dcb.BaudRate = value;
//
//      hwndCombo = GetDlgItem(hDlg, OPT_Bits);
//      index = SendMessage(hwndCombo, CB_GETCURSEL, (WPARAM) 0, (LPARAM) 0);
//      DIS.dcb.ByteSize = cdDataBits[index].value;
//
//      hwndCombo = GetDlgItem(hDlg, OPT_Parity);
//      index = SendMessage(hwndCombo, CB_GETCURSEL, (WPARAM) 0, (LPARAM) 0);
//      DIS.dcb.Parity = cdParity[index].value;
//
//      hwndCombo = GetDlgItem(hDlg, OPT_StopBits);
//      index = SendMessage(hwndCombo, CB_GETCURSEL, (WPARAM) 0, (LPARAM) 0);
//      DIS.dcb.StopBits = cdStopBits[index].value;
//
//      hwndCombo = GetDlgItem(hDlg, OPT_Flow);
//      index = SendMessage(hwndCombo, CB_GETCURSEL, (WPARAM) 0, (LPARAM) 0);
//      switch (cdFlow[index].value) {
//  case FLOW_NONE:
//      DIS.dcb.fOutX = FALSE;
//      DIS.dcb.fOutxCtsFlow = FALSE;
//      DIS.dcb.fOutxDsrFlow = FALSE;
//      break;
//  case FLOW_CTS:
//      DIS.dcb.fOutX = FALSE;
//      DIS.dcb.fOutxCtsFlow = TRUE;
//      DIS.dcb.fOutxDsrFlow = FALSE;
//      break;
//  case FLOW_DSR:
//      DIS.dcb.fOutX = FALSE;
//      DIS.dcb.fOutxCtsFlow = FALSE;
//      DIS.dcb.fOutxDsrFlow = TRUE;
//      break;
//  case FLOW_XOFF:
//      DIS.dcb.fOutX = TRUE;
//      DIS.dcb.fOutxCtsFlow = FALSE;
//      DIS.dcb.fOutxDsrFlow = FALSE;
//      break;
//      }
//      if (!SetCommState(DIS.hCommPort, (LPDCB) &DIS.dcb)) {
//          err = GetLastError();
//          switch(MessageBox(hDlg, 
//              "Failed to set comm port state;\r\ninvalid options?",
//              "Option Error", MB_ABORTRETRYIGNORE|MB_ICONQUESTION)) {
//  case IDABORT:
//      DisplayFatalError("Failed to set comm port state", err, 1);
//      exit(1);  /*is it ok to do this from here?*/
//
//  case IDRETRY:
//      return TRUE;
//
//  case IDIGNORE:
//      EndDialog(hDlg, TRUE);
//      return TRUE;
//          }
//      }
//
//      EndDialog(hDlg, TRUE);
//      return TRUE;
//
//  case IDCANCEL:
//      EndDialog(hDlg, FALSE);
//      return TRUE;
//
//  default:
//      break;
//      }
//      break;
//    }
    return FALSE;
}

void
CommPortOptionsPopup(HWND hwnd)
{
    //FARPROC lpProc = MakeProcInstance((FARPROC)CommPortOptionsDialog, hInst);
    //DialogBox(hInst, MAKEINTRESOURCE(DLG_CommPort), hwnd, (DLGPROC) lpProc);
    //FreeProcInstance(lpProc);
}

/*---------------------------------------------------------------------------*\
*
* Load Options dialog functions
*
\*---------------------------------------------------------------------------*/

void
SetLoadOptionEnables(HWND hDlg)
{
    UINT state;

    state = IsDlgButtonChecked(hDlg, OPT_Autostep);
    EnableWindow(GetDlgItem(hDlg, OPT_ASTimeDelay), state);
    EnableWindow(GetDlgItem(hDlg, OPT_AStext1), state);
}

LRESULT CALLBACK
LoadOptions(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    TCHAR buf[MSG_SIZ];
    float fnumber;

    switch (message) {
  case WM_INITDIALOG: /* message: initialize dialog box */
      /* Center the dialog over the application window */
      CenterWindow (hDlg, GetWindow (hDlg, GW_OWNER));
      /* Initialize the dialog items */
      if (appData.timeDelay >= 0.0) {
          CheckDlgButton(hDlg, OPT_Autostep, TRUE);
          //sprintf(buf, "%.2g", appData.timeDelay);
          StringCbPrintf(buf,MSG_SIZ,_T("%.2g"), appData.timeDelay);
          SetDlgItemText(hDlg, OPT_ASTimeDelay, buf);
      } 
      else {
          CheckDlgButton(hDlg, OPT_Autostep, FALSE);
      }
      SetLoadOptionEnables(hDlg);
      return TRUE;

  case WM_COMMAND: /* message: received a command */
      switch (LOWORD(wParam)) {
  case IDOK:
      /* Read changed options from the dialog box */
      if (IsDlgButtonChecked(hDlg, OPT_Autostep)) {
          GetDlgItemText(hDlg, OPT_ASTimeDelay, buf, MSG_SIZ);
          if (swscanf_s(buf, _T("%f"), &fnumber) != 1) {
              MessageBox(hDlg, _T("Invalid load game step rate"),
                  _T("Option Error"), MB_OK|MB_ICONEXCLAMATION);
              return FALSE;
          }
          appData.timeDelay = fnumber;
      } else {
          appData.timeDelay = (float) -1.0;
      }
      EndDialog(hDlg, TRUE);
      return TRUE;

  case IDCANCEL:
      EndDialog(hDlg, FALSE);
      return TRUE;

  default:
      SetLoadOptionEnables(hDlg);
      break;
      }
      break;
    }
    return FALSE;
}


void 
LoadOptionsPopup(HWND hwnd)
{
    FARPROC lpProc = MakeProcInstance((FARPROC)LoadOptions, hInst);
    DialogBox(hInst, MAKEINTRESOURCE(DLG_LoadOptions), hwnd, (DLGPROC) lpProc);
    FreeProcInstance(lpProc);
}

/*---------------------------------------------------------------------------*\
*
* Save Options dialog functions
*
\*---------------------------------------------------------------------------*/

void
SetSaveOptionEnables(HWND hDlg)
{
    UINT state;

    state = IsDlgButtonChecked(hDlg, OPT_Autosave);
    EnableWindow(GetDlgItem(hDlg, OPT_AVPrompt), state);
    EnableWindow(GetDlgItem(hDlg, OPT_AVToFile), state);
    if (state && !IsDlgButtonChecked(hDlg, OPT_AVPrompt) &&
        !IsDlgButtonChecked(hDlg, OPT_AVToFile)) {
            CheckRadioButton(hDlg, OPT_AVPrompt, OPT_AVToFile, OPT_AVPrompt);
    }

    state = state && IsDlgButtonChecked(hDlg, OPT_AVToFile);
    EnableWindow(GetDlgItem(hDlg, OPT_AVFilename), state);
    EnableWindow(GetDlgItem(hDlg, OPT_AVBrowse), state);
}

LRESULT CALLBACK
SaveOptionsDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    TCHAR buf[MSG_SIZ];
    FILE *f;

    switch (message) {
  case WM_INITDIALOG: /* message: initialize dialog box */
      /* Center the dialog over the application window */
      CenterWindow (hDlg, GetWindow (hDlg, GW_OWNER));
      /* Initialize the dialog items */
      //if (*appData.saveGameFile != NULLCHAR) {
      //    CheckDlgButton(hDlg, OPT_Autosave, (UINT) TRUE);
      //    CheckRadioButton(hDlg, OPT_AVPrompt, OPT_AVToFile, OPT_AVToFile);
      //    SetDlgItemText(hDlg, OPT_AVFilename, appData.saveGameFile);
      //} else if (appData.autoSaveGames) {
      //    CheckDlgButton(hDlg, OPT_Autosave, (UINT) TRUE);
      //    CheckRadioButton(hDlg, OPT_AVPrompt, OPT_AVToFile, OPT_AVPrompt);
      //} else {
      //    CheckDlgButton(hDlg, OPT_Autosave, (UINT) FALSE);
      //}

      CheckRadioButton(hDlg, OPT_PGN, OPT_Old, OPT_PGN);

      SetSaveOptionEnables(hDlg);
      return TRUE;

  case WM_COMMAND: /* message: received a command */
      switch (LOWORD(wParam)) {
  case IDOK:
      /* Read changed options from the dialog box */
      if (IsDlgButtonChecked(hDlg, OPT_Autosave)) {
          appData.autoSaveGames = TRUE;
          if (IsDlgButtonChecked(hDlg, OPT_AVPrompt)) {
              //appData.saveGameFile = "";
          } else /*if (IsDlgButtonChecked(hDlg, OPT_AVToFile))*/ {
              GetDlgItemText(hDlg, OPT_AVFilename, buf, MSG_SIZ);
              if (*buf == NULLCHAR) {
                  MessageBox(hDlg, _T("Invalid save game file name"),
                      _T("Option Error"), MB_OK|MB_ICONEXCLAMATION);
                  return FALSE;
              }
              if ((isalpha(buf[0]) && buf[1] == ':') ||
                  (buf[0] == '\\' && buf[1] == '\\')) {
                      //appData.saveGameFile = _strdup(buf);
              } else {
                  TCHAR buf2[MSG_SIZ], buf3[MSG_SIZ];
				  TCHAR *dummy;
                  GetCurrentDirectory(MSG_SIZ, buf3);
                  SetCurrentDirectory(installDir);
                  if (GetFullPathName(buf, MSG_SIZ, buf2, &dummy)) {
                      //appData.saveGameFile = _strdup(buf2);
                  } else {
                      //appData.saveGameFile = _strdup(buf);
                  }
                  SetCurrentDirectory(buf3);
              }
          }
      } else {
          appData.autoSaveGames = FALSE;
          //appData.saveGameFile = "";
      }
      //appData.oldSaveStyle = IsDlgButtonChecked(hDlg, OPT_Old);
      EndDialog(hDlg, TRUE);
      return TRUE;

  case IDCANCEL:
      EndDialog(hDlg, FALSE);
      return TRUE;

  case OPT_AVBrowse:
      f = OpenFileDialog(hDlg, TRUE, NULL, _T("pgn"), 
          GAME_FILT, _T("Browse for Auto Save File"), 
          NULL, NULL, buf);
      if (f != NULL) {
          fclose(f);
          SetDlgItemText(hDlg, OPT_AVFilename, buf);
      }
      break;

  default:
      SetSaveOptionEnables(hDlg);
      break;
      }
      break;
    }
    return FALSE;
}

void
SaveOptionsPopup(HWND hwnd){
    FARPROC lpProc = MakeProcInstance((FARPROC)SaveOptionsDialog, hInst);
    DialogBox(hInst, MAKEINTRESOURCE(DLG_SaveOptions), hwnd, (DLGPROC) lpProc);
    FreeProcInstance(lpProc);
}

