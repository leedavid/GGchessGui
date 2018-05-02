#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"

#include <sys/types.h>
#include <sys/timeb.h>

//const int  

BOOL GetFaceAndLearn(int time, int detph, int num){

	TCHAR buf[512];

	swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), _T("\n 正在校验第 %d 局面 \n"), num);
	LogOut(buf);


    


	return FALSE;
}

DWORD WINAPI 
VeryAllFaceThread(LPVOID lpParam){

    int num = 0;

	TCHAR buf[512];

	//dispboard_t pDis[1];

	while(GetFaceAndLearn(16 * 1000, 0, num) && ThStat.outVerfyFace == FALSE){

		num ++;

	}

	swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), _T("\n共校对了 %d 局面 \n"), num);

	LogOut(buf);


	return 0;

}



//打开自动校验线程
void AutoVeryFaceEvent(void){

	if(ThStat.isVerfyFace == TRUE){
       SendToPlayerByColor(L"\n当前已在校验界面, 正在停止校验...\n",ColorShout,FALSE);

	   ThStat.outVerfyFace = TRUE;

	   return; 
	}

	

	DWORD dwThreadId,dwThrdParam = 1;
	HANDLE hVerfy = CreateThread(
		NULL,
		NULL,
		VeryAllFaceThread,
		&dwThrdParam,
		0,
		&dwThreadId);

	if(hVerfy == NULL){
		SendToPlayerByColor(L"\n初始化校验开局库界面线程失败!\n",ColorShout,FALSE);
	}
	else{

		ThStat.isVerfyFace   = TRUE;
		ThStat.outVerfyFace  = FALSE;

		SendToPlayerByColor(L"\n初始化校验开局库界面线程成功!\n",ColorShout,TRUE);

		

		//SetThreadPriority(hImport,THREAD_PRIORITY_BELOW_NORMAL);

		//Thread_Stat |= TH_Learning;
		//ThStat.isLearn = TRUE;
	}
}
