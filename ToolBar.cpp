#include "stdafx.h"
#include "GGchess.h"
#include "chess.h"
#include "data.h"
#include "pregen.h"

HWND			//建立工具条窗口
CreateAToolBar(HWND hwndParent){
	#define NUM_BUTTONS               16
	HWND hwndTB; 

	TBADDBITMAP tbab; 
	tbab.hInst = hInst;
	tbab.nID   = IDR_TOOLBAR;

	TBBUTTON tbb[NUM_BUTTONS]; 


	// Create a toolbar.  WS_EX_TOOLWINDOW "ToolWindowClass
	hwndTB = CreateWindowEx(
		WS_EX_TOOLWINDOW, 
		TOOLBARCLASSNAME,	
		(LPSTR) NULL, 
		WS_CHILD + TBSTYLE_FLAT + WS_BORDER + TBSTYLE_TRANSPARENT + TBSTYLE_TOOLTIPS ,
		0,
		0, 
		0,
		0,
		hwndParent, 
		(HMENU)IDR_TOOLBAR, 
		hInst, NULL); 

	// Send the TB_BUTTONSTRUCTSIZE message, which is required for 
	// backward compatibility. 
	SendMessage(hwndTB, TB_BUTTONSTRUCTSIZE, (WPARAM) sizeof(TBBUTTON), 0); 
   
	//SendMessage(hwndTB, TB_SETBITMAPSIZE,0,(LPARAM)MAKELONG(16,15));

	SendMessage(hwndTB,(UINT) TB_ADDBITMAP,NUM_BUTTONS,(LPARAM)(LPTBADDBITMAP)&tbab);
	
	tbb[0].iBitmap		= 0; 
	tbb[0].idCommand	= IDT_NEW;              //新棋局
	tbb[0].fsState		= TBSTATE_ENABLED; 
	tbb[0].fsStyle		= BTNS_BUTTON ; 
	tbb[0].dwData		= 0; 
	tbb[0].iString		= 0; 

	tbb[1].iBitmap		= 1; 
	tbb[1].idCommand	= IDT_CANJU;           //摆局
	tbb[1].fsState		= TBSTATE_ENABLED; 
	tbb[1].fsStyle		= BTNS_BUTTON; 
	tbb[1].dwData		= 0; 
	tbb[1].iString		= 0; 

    tbb[2].iBitmap		= 2; 
	tbb[2].idCommand	= IDT_FLIP;           //上下翻转棋盘
	tbb[2].fsState		= TBSTATE_ENABLED; 
	tbb[2].fsStyle		= BTNS_BUTTON; 
	tbb[2].dwData		= 0; 
	tbb[2].iString		= 0; 

	tbb[3].iBitmap		= 3; 
	tbb[3].idCommand	= IDT_ToStart;         //到棋局开头
	tbb[3].fsState		= TBSTATE_ENABLED; 
	tbb[3].fsStyle		= BTNS_BUTTON; 
	tbb[3].dwData		= 0; 
	tbb[3].iString		= 0; 

	tbb[4].iBitmap		= 4; 
	tbb[4].idCommand	= IDT_Backward;		  //后退一步
	tbb[4].fsState		= TBSTATE_ENABLED; 
	tbb[4].fsStyle		= BTNS_BUTTON; 
	tbb[4].dwData		= 0; 
	tbb[4].iString		= 0; 

	tbb[5].iBitmap		= 5; 
	tbb[5].idCommand	= IDT_pause;          //暂停棋局
	tbb[5].fsState		= TBSTATE_ENABLED; 
	tbb[5].fsStyle		= BTNS_BUTTON; 
	tbb[5].dwData		= 0; 
	tbb[5].iString		= 0; 

	tbb[6].iBitmap		= 6; 
	tbb[6].idCommand	= IDT_Forward;        //前进一步
	tbb[6].fsState		= TBSTATE_ENABLED; 
	tbb[6].fsStyle		= BTNS_BUTTON; 
	tbb[6].dwData		= 0; 
	tbb[6].iString		= 0; 

	tbb[7].iBitmap		= 7; 
	tbb[7].idCommand	= IDT_ToEnd;          //到达棋局的结尾
	tbb[7].fsState		= TBSTATE_ENABLED; 
	tbb[7].fsStyle		= BTNS_BUTTON; 
	tbb[7].dwData		= 0; 
	tbb[7].iString		= 0; 

    tbb[8].iBitmap		= 8; 
	tbb[8].idCommand	= IDT_Stop;          //引擎停止思考
	tbb[8].fsState		= TBSTATE_ENABLED; 
	tbb[8].fsStyle		= BTNS_BUTTON; 
	tbb[8].dwData		= 0; 
	tbb[8].iString		= 0; 

    tbb[9].iBitmap		= 9; 
	tbb[9].idCommand	= IDT_HUIQI;          //用户悔棋
	tbb[9].fsState		= TBSTATE_ENABLED; 
	tbb[9].fsStyle		= BTNS_BUTTON; 
	tbb[9].dwData		= 0; 
	tbb[9].iString		= 0; 	
    
    //IDT_HuiQi
    //I

	tbb[10].iBitmap		= 10; 
	tbb[10].idCommand	= IDT_COM_RED;        //引擎(1)加入运算
	tbb[10].fsState		= TBSTATE_ENABLED; 
	tbb[10].fsStyle		= BTNS_CHECK; 
	tbb[10].dwData		= 0; 
	tbb[10].iString		= 0; 

	tbb[11].iBitmap		= 11; 
	tbb[11].idCommand	= IDT_COM_BLUE;       //引擎(2)加入运算
	tbb[11].fsState		= TBSTATE_ENABLED; 
	tbb[11].fsStyle		= BTNS_CHECK; 
	tbb[11].dwData		= 0; 
	tbb[11].iString		= 0; 

	tbb[12].iBitmap		= 12; 
	tbb[12].idCommand	= IDT_YQ_SET;        //设置引擎 
	tbb[12].fsState		= TBSTATE_ENABLED; 
	tbb[12].fsStyle		= BTNS_BUTTON; 
	tbb[12].dwData		= 0; 
	tbb[12].iString		= 0; 
	
	tbb[13].iBitmap		= 13; 
	tbb[13].idCommand	= IDT_ANALIZE;       //设置引擎成分析模式  
	tbb[13].fsState		= TBSTATE_ENABLED; 
	tbb[13].fsStyle		= BTNS_CHECK; 
	tbb[13].dwData		= 0; 
	tbb[13].iString		= 0; 

    tbb[14].iBitmap		= 14; 
	tbb[14].idCommand	= IDT_INTERNET; //自动学习棋库棋局IDT_LERANQJ
	tbb[14].fsState		= TBSTATE_ENABLED; 
	tbb[14].fsStyle		= BTNS_CHECK; 
	tbb[14].dwData		= 0; 
	tbb[14].iString		= 0; 
	
	tbb[15].iBitmap		= 15; 
	tbb[15].idCommand	= IDT_INTERNET; //自动学习棋库棋局IDT_LERANQJ
	tbb[15].fsState		= TBSTATE_ENABLED; 
	tbb[15].fsStyle		= BTNS_CHECK; 
	tbb[15].dwData		= 0; 
	tbb[15].iString		= 0; 

	////IDT_HUIQI //悔棋  ID_BUTTONGG
	//tbb[16].iBitmap		= 16; 
	//tbb[16].idCommand	= IDT_LEARN_QK; 
	//tbb[16].fsState		= TBSTATE_ENABLED; 
	//tbb[16].fsStyle		= BTNS_CHECK; 
	//tbb[16].dwData		= 0; 
	//tbb[16].iString		= 0; 

	////IDT_HUIQI //悔棋  ID_BUTTONGG
	//tbb[17].iBitmap		= 17; 
	//tbb[17].idCommand	= ID_BUTTONGG; 
	//tbb[17].fsState		= TBSTATE_ENABLED; 
	//tbb[17].fsStyle		= BTNS_BUTTON; 
	//tbb[17].dwData		= 0; 
	//tbb[17].iString		= 0; 

 //   tbb[18].iBitmap		= 18; 
	//tbb[18].idCommand	= IDT_CORRECT_MAN;	
	//tbb[18].fsState		= TBSTATE_ENABLED; 
	//tbb[18].fsStyle		= BTNS_BUTTON; 
	//tbb[18].dwData		= 0; 
	//tbb[18].iString		= 0; 

	

	SendMessage(hwndTB, TB_ADDBUTTONS, (WPARAM) NUM_BUTTONS, (LPARAM) (LPTBBUTTON) &tbb); 

	SendMessage(hwndTB, TB_AUTOSIZE, 0, 0); 

	

	ShowWindow(hwndTB, SW_SHOW); 
	//MoveWindow(hwndTB,0,0,300,20,false);


	return hwndTB; 
}



