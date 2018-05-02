#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

void	//从象棋引擎中接收数据
ReceiveFromProgram(InputSourceRef isr,VOIDSTAR  closure, char *message,int count,int error){
    char *end_str;
    TCHAR buf[MSG_SIZ];
    ChessProgramState *cps = (ChessProgramState *)closure;

    if (isr != cps->isr){
        return; /* Killed intentionally */
    }
    if (count <= 0) {
        if (count == 0) {
            //sprintf(buf, "Error: %s chess program (%s) exited unexpectedly",
            // cps->which, cps->program);
            StringCbPrintf(buf,MSG_SIZ,_T("\nError: %s chess program (%s) exited unexpectedly\n"),
                /*cps->which, cps->program);*/
                cps->UCCI_file, cps->UCCI_name);
           
            RemoveInputSource(cps->isr);

			LogOut(buf);

			//这个引擎已退出了，就要发送相关的信息到窗口中

			//int ee

			//cps->UCCI_initDone  = FALSE;

			cps->cps_stat = Cps_NotLoad;

			PostMessage(cps->loadWin,WM_USER_YqUpload_OK,0,(LPARAM)cps);  //向引擎所在窗口发送已卸载成功的信息

           
            //DisplayFatalError(buf, 0, 1);
        } 
        else {
            //sprintf(buf,  "Error reading from %s chess program (%s)",
            // cps->which, cps->program);
            StringCbPrintf(buf,MSG_SIZ,_T("\nError reading from %s chess program (%s)\n"),
                //cps->which, cps->program);
                cps->UCCI_file,  cps->UCCI_name);
            RemoveInputSource(cps->isr);

            LogOut(buf);
            //DisplayFatalError(buf, error, 1);
        }
		GameEnds((dispboard_t*)cps->pDis,(ChessMove) 0, NULL, GE_PLAYER);
        return;
    }

    if ((end_str = strchr(message, '\r')) != NULL){
        *end_str = NULLCHAR;
    }
    if ((end_str = strchr(message, '\n')) != NULL){
        *end_str = NULLCHAR;
    }

#ifdef DEBUG_MODE 
    //if (appData.debugMode) {                    //调试模式
        //TimeMark now;
        //GetTimeMark(&now);
        //fprintf(MAIN.debugFP, "%ld <%-6s: %s\n", 
        //    SubtractTimeMarks(&now, &pDis->programStartTime),
        //    cps->UCCI_name, message);
    //}
#endif
	TCHAR tInfo[1024];
	swprintf_s(tInfo, sizeof(tInfo) / sizeof(TCHAR), L"%S", message);
    HandleMachineMove(tInfo, cps);
}



