#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

void			//处理UCCI引擎输入过来的消息
HandleMachineCYC105(TCHAR *Tinfo, ChessProgramState *cps){
	 LogOut(_T("引擎未识别指令\n"));
     LogOut(Tinfo);
}

