#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"



void 
SendControlParameterToCps(ChessProgramState *cps) {

    //if(cps->Already_Send_Initinfo == TRUE){     //已发送了初始信息
    //    return;
    //}

    //在这儿先设定时间方面的设定
    TCHAR buf[MSG_SIZ];

    //在这儿设定引擎的相关设置，时间，层数，后台思考等
    switch(cps->ucci){
        	
		//
        case UCCI_UCCI_ms:		//象堡协议 *******************************************************

			//
			SendToProgram(L"setoption usemillisec on\n",cps);

			//
			if(cps->UCCI_loadbook){
				SendToProgram(L"setoption usebook true\n",cps);
			}
			else{
				SendToProgram(L"setoption usebook off\n",cps);
			}

			//
			
			swprintf_s(buf,sizeof(buf)/sizeof(TCHAR),L"setoption hashsize %d\n",cps->UCCI_hashsize);
			SendToProgram(buf,cps);
			
            //............................................
            break;
		//
		case UCCI_UCCI_OLD:
			//
			SendToProgram(L"setoption usemillisec false\n",cps);

			//
			if(cps->UCCI_loadbook){
				SendToProgram(L"setoption usebook true\n",cps);
			}
			else{
				SendToProgram(L"setoption usebook off\n",cps);
			}

			
			swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), L"setoption hashsize %d\n", cps->UCCI_hashsize);
			SendToProgram(buf,cps);
			
            //............................................
            break;
		//
		case UCCI_GGchess:		//佳佳协议 *******************************************************

			if(cps->UCCI_hashsize < 64){
				cps->UCCI_hashsize = 64;
			}
			
			swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), L"setoption name Hash value %d\n", cps->UCCI_hashsize);
			SendToProgram(buf,cps);

			swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), L"setoption name Threads value %d\n", cps->UCCI_smpNum);
			SendToProgram(buf,cps);

			//define_uci_option(FALSE, "Threads",	         SMP_NUM,           UCI_SPIN,  1, 8);

			//SMP NUM

			swprintf_s(buf, sizeof(buf) / sizeof(TCHAR),
				L"\n*******************************\n"
				L"引擎 -> %s"
				L"线程数(SMP):  %6d\n"
				L"Hash表:       %6dm\n"
				L"开局步数:     %6d回合\n"
				L"********************************\n",
				cps->UCCI_name,
				cps->UCCI_smpNum,
				cps->UCCI_hashsize,
				cps->UCCI_Book_Num);

			LogOut(buf);

			//sprintf_s(buf,sizeof(buf), "

			//
            break;
		case UCCI_QianHong:		//浅红协议 *******************************************************
			if (wcsstr(cps->UCCI_file, L"keplugin.exe") != NULL){	//killegg特有的
                SendToProgram(L"LEVEL 5\n",cps);
            }
            else{
                SendToProgram(L"LEVEL 3\n",cps);
            }			
            //cps->maybeThinking = FALSE;
            //cps->offeredDraw = 0;
            break;
        case UCCI_CYC105:
            break;
        
        default:					 //*******************************************************
           
            break;
    }

}
