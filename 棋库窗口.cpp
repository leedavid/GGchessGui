#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

#include "db.h" 

const int Book_Default_Width  = 250;
const int Book_Default_Height = 200;

void FitBookDlgPositionDefault(HWND hDlg){  //调整棋步窗口到缺省位置
 //   WINDOWPLACEMENT wp;
	//wp.length = sizeof(WINDOWPLACEMENT);
	//GetWindowPlacement(hwndMain,&wp);
 //   
 //   wp.rcNormalPosition.bottom = wp.rcNormalPosition.top + 200;
 //   wp.rcNormalPosition.top    = wp.rcNormalPosition.top;
 //   wp.rcNormalPosition.left   = wp.rcNormalPosition.right;
 //   wp.rcNormalPosition.right  = wp.rcNormalPosition.left  + 200;
 //   SetWindowPlacement(hDlg,&wp);
 //   FitBookDlgItem(hDlg);

	dispboard_t* pDis = OBS[0];

    RECT Rect;
    GetWindowRect(pDis->hwndThis,&Rect);

    int x       = Rect.left;
    /*int y       = Rect.bottom;*/
    //int width   = Rect.right - Rect.left;
	int width   = Book_Default_Width;
    int height  = Book_Default_Height;

	int y       = Rect.top - Book_Default_Height;

    SetWindowPos(hDlg,NULL,x,y,width,height,SWP_NOZORDER|SWP_NOACTIVATE);

	ShowWindow(hDlg,SW_SHOW);
}






