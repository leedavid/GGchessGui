#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"


void StartChessProgram(ChessProgramState *cps) {
    
    TCHAR buf[MSG_SIZ];
    int  err;



    //GetSetYQsetFromAppData();           //得到引擎的设定参数

    //if(cps->UCCI_initDone == TRUE){
    //    return;
    //}

	if(cps->cps_stat != Cps_NotLoad){
		return;
	}

	//cps->isInLoading	= TRUE;        //正在加载引擎
 //   cps->UCCI_initDone  = FALSE;

	cps->cps_stat = Cps_InLoading;

	if(strcmp(cps->szHost,"localhost") == 0){     //是本机游戏
		switch(cps->ucci){
			case UCCI_UCCI_ms:	
			case UCCI_UCCI_OLD:
				StringCbPrintf(buf, MSG_SIZ, _T("%s"), cps->UCCI_file);
				break;
			//
			case UCCI_GGchess:
				IsSendRand = 0;
				StringCbPrintf(buf, MSG_SIZ, _T("%s"), cps->UCCI_file);
				break;
			//
			case UCCI_CYC105:
				StringCbPrintf(buf, MSG_SIZ, _T("%s%s%s"), installDir, cps->UCCI_path, cps->UCCI_file);
				break;
			//
			case UCCI_QianHong:			//浅红协议
				StringCbPrintf(buf, MSG_SIZ, _T("%s -plugin"), cps->UCCI_file);  // 加上一个-plugin				
				break;
			//
			default:
				StringCbPrintf(buf, MSG_SIZ, _T("%s"), cps->UCCI_file);
				break;
		}
		err = StartChildProcess(buf, cps->UCCI_path, &cps->pr);	         //打开引擎进程
	}
	else if(*appData.remoteShell == NULLCHAR){                           //联网游戏
		err = OpenRcmd(cps->szHost, CW2A(appData.remoteUser),CW2A(cps->UCCI_file), &cps->pr);
	}
	else{                                                                //远程用户
		if (*appData.remoteUser == NULLCHAR) {
			StringCbPrintf(buf, MSG_SIZ, _T("%s %s %s"), appData.remoteShell, cps->szHost, cps->UCCI_file);
		} 
		else {		
			StringCbPrintf(buf, MSG_SIZ, _T("%s %s -l %s %s"), appData.remoteShell,
				cps->szHost, appData.remoteUser, cps->UCCI_file);
		}
		err = StartChildProcess(buf, _T(""), &cps->pr);
	}

	//********************************************************
	if (err != 0) {						//如果初始出错
		StringCbPrintf(buf, MSG_SIZ, _T("Startup failure on '%s'"), cps->UCCI_file);
		LogOut(buf);
		//DisplayFatalError(buf, err, 1);
		cps->pr = NoProc;
		cps->isr = NULL;
		return;
	}
    cps->isr = AddInputSource(cps->pr, TRUE, ReceiveFromProgram, cps);      //加入一个接收线程

    // 协议版本控制

    //if (cps->protocolVersion > 1) {
    //	//sprintf(buf, "xboard\nprotover %d\n", cps->protocolVersion);
    //	//StringCbPrintf(buf,MSG_SIZ,"xboard\nprotover %d\n", cps->protocolVersion);
    //	//SendToProgram(buf, cps);
    //	//SendToProgram("ucci",cps);
    //} 
    //else {
    //	//SendToProgram("ucci",cps);
    //	//SendToProgram("xboard\n", cps);
    //}


    //发送引擎初始化命令
    switch(cps->ucci){
        case UCCI_UCCI_ms:			//象堡协议
		case UCCI_UCCI_OLD:
            //这是引擎启动后，界面需要给引擎发送的第一条指令，通知引擎现在使用的是UCCI协议。
			SendToProgram(L"ucci\n", cps);
            break;
		case UCCI_GGchess:		    //不在这儿发送哇
			//Sleep(1000);
			//sprintf_s(buf,sizeof(buf),"%s",UCCI_START);
			//SendToProgram(buf,cps);

            //SendToProgram("Authenticate 801C85DE5F7BDACFF1F8DC789FBE5B1B\n",cps);
            //StringCbPrintf(buf,MSG_SIZ,"Md5check %s%s%s\n",
            //	installDir,cps->dir,cps->program);
            //SendToProgram(buf,cps);
            //SendToProgram("notation 4 3\n",cps);		//棋步格式
            ////SendToProgram("hard\n",cps);				//开启后台思考
            //SendToProgram("learn 0\n",cps);				//开启学习功能
            //SendToProgram("log off\n",cps);				//关了日志


            //SendToProgram("st 1\n",cps);				//关了日志
            //SendToProgram("time sd/10\n",cps);		//关了日志
            //SendToProgram("force H2E2\n",cps);
            //force H2E2
            //SendToProgram("Authenticate 801C85DE5F7BDACFF1F8DC789FBE5B1B\n",cps);

            //GetCurrentDirectory(MSG_SIZ, buf);
            //SetCurrentDirectory(installDir);
            //SetCurrentDirectory(dir);
            break;
        case UCCI_CYC105:
			SendToProgram(L"ucci\n", cps);
            break;
        case UCCI_QianHong:			//浅红协议			
            break;
        
        default:			
            break;			
    }
}


