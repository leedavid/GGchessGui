#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"

//保存棋局窗口

void DLG_SAVE_GAME_Event(dispboard_t *pDis){
	
	if(pDis->hwndSaveDlg == NULL){			//
		//建立对话框

	}
	else{
		SendMessage(pDis->hwndSaveDlg,WM_CLOSE,0,0);		//关闭窗口
	}

}