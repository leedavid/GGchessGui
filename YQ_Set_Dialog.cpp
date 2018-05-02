#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

#include <windows.h>   /* required for all Windows applications */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <fcntl.h>
#include <math.h>
#include <commdlg.h>
#include <dlgs.h>

//卸载引擎子线程
//DWORD WINAPI 
//UnLoadCpsThread(LPVOID lpParam){
//    ChessProgramState *cps = (ChessProgramState *)lpParam;
//
// 
//   
//
//    if(cps->UCCI_initDone == 0){
//        //MessageBox(hwndMain,"当前引擎还没加载！不用卸载！",cps->UCCI_name,MB_OK);
//		cps->hwndHide = NULL;
//        LogOut("当前引擎还没加载！不用卸载！\n");
//        return false;
//    }
//
//    //if(cps->UCCI_which != 1 && cps->UCCI_which != 2){
//    //if(cps->playWhat == NEUTRAL){
//    //    //MessageBox(hwndMain,"这个要卸载的引擎不是工作引擎！",cps->UCCI_name,MB_OK);
//    //    LogOut("这个要卸载的引擎不是工作引擎！\n");
//    //    return false;
//    //}
//
//    if(cps->hwndHide != NULL){
//         ShowWindow(cps->hwndHide,SW_HIDE);
//    }
//    //dispboard_t* DIS = OBS[cps->table];
//    //
//    LogOut("正在卸载引擎：");
//    LogOut(cps->UCCI_name);
//    LogOut("\n可能要一些时间，请稍候....\n");
//
//    bool rc = false;
//    switch(cps->ucci){
//        case UCCI_UCCI162:
//            if(cps->maybeThinking){
//                SendToProgram("stop\n", cps);
//                Sleep(1000);
//            }
//            SendToProgram("quit\n",cps);
//            for(int i = 0; i < 50; i++){
//                Sleep(100);
//                if(cps->UCCI_initDone == 0){
//                    rc = true;
//                    break;
//                }
//            }
//            break;
//        case UCCI_CYC105:
//            if(cps->maybeThinking){
//                SendToProgram("stop\n", cps);
//                Sleep(1000);
//            }
//            SendToProgram("quit\n",cps);
//            for(int i = 0; i < 50; i++){
//                Sleep(100);
//                if(cps->UCCI_initDone == 0){
//                    rc = true;
//                    break;
//                }
//            }
//            break;
//        case UCCI_DIS:
//            break;
//        case UCCI_QH:
//            break;
//        case UCCI_OTHER:
//            break;
//        default:
//            break;
//    }
//
//    if(rc == true){
//        LogOut("卸载引擎成功了！\n");
//    }
//    else{
//        LogOut("卸载引擎失败！\n");
//    }
//
//    if(cps->hwndHide != NULL){
//        ShowWindow(cps->hwndHide,SW_SHOW);
//        cps->hwndHide = NULL;
//    }
//    return rc;
//}
////卸载一个引擎
//void 
//UnLoadChessProgramState(ChessProgramState *cps, HWND win){
//
//    DWORD dwThreadId;    
//    cps->hwndHide = win;
//    //DWORD dwThrdParam = cps->UCCI_which;
//
//    HANDLE hLoadCPS = CreateThread(
//        NULL,
//        NULL,
//        UnLoadCpsThread,
//        cps,
//        0,
//        &dwThreadId);
//
//    //                //    if(cps->UCCI_initDone){
//    //                //    LogOut(ColorShout,"正在卸载引擎：",true);
//    //                //    LogOut(ColorShour,cps->UCCI_name,true);
//    //                //    LogOut(ColorSeek,"可能要一些时间，请稍候....＼n",true);
//    //                //    if(UnLoadChessProgramState(cps)){
//    //                //        LogOut(
//    //                //    }
//    //                //    else{
//    //                //    }
//    //                //}
//
//    //if(cps->UCCI_initDone == 0){
//    //    //MessageBox(hwndMain,"当前引擎还没加载！不用卸载！",cps->UCCI_name,MB_OK);
//    //    LogOut(ColorShout,"当前引擎还没加载！不用卸载！\n",true);
//    //    return false;
//    //}
//
//    //if(cps->UCCI_which != 1 && cps->UCCI_which != 2){
//    //    //MessageBox(hwndMain,"这个要卸载的引擎不是工作引擎！",cps->UCCI_name,MB_OK);
//    //    LogOut(ColorShout,"这个要卸载的引擎不是工作引擎！\n",true);
//    //    return false;
//    //}
//
//    ////
//    //LogOut(ColorShout,"正在卸载引擎：",true);
//    //LogOut(ColorShout,cps->UCCI_name,true);
//    //LogOut(ColorSeek,"\n可能要一些时间，请稍候....\n",true);
//
//    //bool rc = false;
//    //switch(cps->ucci){
//    //    case UCCI_UCCI:
//    //        break;
//    //    case UCCI_DIS:
//    //        break;
//    //    case UCCI_QH:
//    //        break;
//    //    case UCCI_OHTER:
//    //        break;
//    //    default:
//    //        break;
//    //}
//
//    //if(rc == true){
//    //    LogOut(ColorShout,"卸载引擎成功了！\n",true);
//    //}
//    //else{
//    //    LogOut(ColorShout,"卸载引擎失败！\n",true);
//    //}
//    //return rc;
//}
//
//

//
//DWORD WINAPI 
//LoadCpsThread(LPVOID lpParam){  
//
//   char buf[MSG_SIZ];
//
//    ChessProgramState *cps = (ChessProgramState *)lpParam;      //先
//
//    //if(cps->UCCI_which != 1 && cps->UCCI_which != 2){
//    //    //MessageBox(hwndMain,"这个要加载的引擎不是工作引擎！",cps->UCCI_name,MB_OK);
//    //    LogOut("这个要加载的引擎不是工作引擎！\n");
//    //    return false;
//    //}
//
//    if(cps->UCCI_initDone == 1){        //如果这个引擎已加载了,得先卸载它
//        UnLoadChessProgramState(cps, cps->hwndHide);
//    }
//
//    for(int i = 0; i < 100; i++){
//        if(cps->UCCI_initDone == 0){        //已卸载了
//          break;
//        }       
//        Sleep(100);
//    }
//    if(cps->UCCI_initDone == 1){
//        //MessageBox(cps->hwndParent,cps->UCCI_name,"出错了，这个引擎不能卸载！！",MB_OK);
//        MessageBox(OBS[cps->table]->hwndThis,cps->UCCI_name,"出错了，这个引擎不能卸载！！",MB_OK);
//        return false;
//    }
//
//    //if(cps->UCCI_initDone == 1){
//    //    //MessageBox(hwndMain,"当前引擎还已成功加载！不用再卸载！",cps->UCCI_name,MB_OK);
//    //    LogOut(ColorShout,"当前引擎还已成功加载！不用再加载！\n",true);
//    //    return false;
//    //}
//
//
//    //
//
//    if(cps->hwndHide != NULL){
//        ShowWindow(cps->hwndHide,SW_HIDE);
//    }
//
//    bool rc = false;
//
//    //LogOut(ColorShout,"正在加载引擎：",true);
//    //LogOut(ColorShout,cps->UCCI_name,true);
//    //LogOut(ColorSeek,"\n可能要一些时间，请稍候....\n",true);
//
//    sprintf_s(buf,MSG_SIZ,"正在加载引擎: 名称: %s\n文件名: %s%s\n可能需要一些时间,请稍等...\n",
//        cps->UCCI_name,cps->UCCI_path,cps->UCCI_file);
//
//    LogOut(buf);
//
//    switch(cps->ucci){
//        case UCCI_UCCI162:
//            StartChessProgram(cps);
//            for(int i = 0; i < 50; i++){
//                Sleep(100);
//                if(cps->UCCI_initDone == 1){
//                    rc = true;
//                    break;
//                }
//            }           
//            break;
//        case UCCI_CYC105:
//            StartChessProgram(cps);
//            for(int i = 0; i < 50; i++){
//                Sleep(100);
//                if(cps->UCCI_initDone == 1){
//                    rc = true;
//                    break;
//                }
//            } 
//            break;
//        case UCCI_DIS:		//这个是佳佳象棋加载
//            break;
//        case UCCI_QH:
//            break;
//        case UCCI_OTHER:
//            break;
//        default:
//            break;
//    }
//
//    if(rc == true){
//        LogOut("加载引擎成功了！\n");
//    }
//    else{
//        LogOut("加载引擎失败！\n");
//    }
//
//    if(cps->hwndHide != NULL){
//        ShowWindow(cps->hwndHide,SW_SHOW);
//        cps->hwndHide = NULL;
//    }
//
//    return 0;
//}
//


void 
LoadChessProgramState(ChessProgramState *precps, ChessProgramState *loadcps, HWND hWin){

	//ShowWindow(win,SW_HIDE);			//将窗口隐藏一下

	loadcps->loadWin        = hWin;		   //保存引擎的窗口，好向窗口发送完成的，或退出的消息

	//1, 在加载前先要卸载要加载的引擎
	if(precps->UCCI_initDone == TRUE){		//就要先卸载它
		LogOut("\n正在卸载引擎: ");
		LogOut(precps->UCCI_name);
		LogOut("\n可能要一些时间， 请稍候...\n");

		switch(precps->ucci){
			case UCCI_UCCI162:
				if(precps->maybeThinking){
					SendToProgram("stop\n",precps);
					Sleep(500);
				}
				SendToProgram("quit\n", precps);
				for(int i = 0; i < 50; i++){
					Sleep(100);
					if(precps->UCCI_initDone == FALSE){
						break;
					}
				}
				break;
			case UCCI_CYC105:
				if(precps->maybeThinking){
					SendToProgram("stop\n",precps);
					Sleep(500);
				}
				SendToProgram("quit\n", precps);
				for(int i = 0; i < 50; i++){
					Sleep(100);
					if(precps->UCCI_initDone == FALSE){
						break;
					}
				}
				break;
			case UCCI_DIS:
				if(precps->maybeThinking){
					SendToProgram("stop\n",precps);
					Sleep(500);
				}
				SendToProgram("quit\n", precps);
				for(int i = 0; i < 50; i++){
					Sleep(100);
					if(precps->UCCI_initDone == FALSE){
						break;
					}
				}		
				break;
			default:
				break;
		}
	}

	if(precps->UCCI_initDone == TRUE){
		LogOut("\n当前引擎不能卸载\n");
		return;
	}

	//struct _CPS * loadWhich;        //加载引擎到那一个，是first,还是second
	//BOOL          isInLoading;      //引擎正在加载之中，

	loadcps->loadWhich		= precps;
	loadcps->isInLoading	= TRUE;        //正在加载引擎
	

	LogOut("\n正在加载引擎：");
	LogOut(loadcps->UCCI_name);
	LogOut("\n可能要一些时间，请稍候....\n");

	StartChessProgram(loadcps);

}

//加载一个引擎
//bool 
//LoadChessProgramState(ChessProgramState *cps){
//    
//    if(cps->UCCI_initDone == 1){
//        //MessageBox(hwndMain,"当前引擎还已成功加载！不用再卸载！",cps->UCCI_name,MB_OK);
//        LogOut(ColorShout,"当前引擎还已成功加载！不用再卸载！\n",true);
//        return false;
//    }
//    if(cps->UCCI_which != 1 && cps->UCCI_which != 2){
//        //MessageBox(hwndMain,"这个要加载的引擎不是工作引擎！",cps->UCCI_name,MB_OK);
//        LogOut(ColorShout,"这个要加载的引擎不是工作引擎！\n",true);
//        return false;
//    }
//
//    bool rc = false;
//
//    LogOut(ColorShout,"正在加载引擎：",true);
//    LogOut(ColorShout,cps->UCCI_name,true);
//    LogOut(ColorSeek,"\n可能要一些时间，请稍候....\n",true);
//
//
//    switch(cps->ucci){
//        case UCCI_UCCI:
//            StartChessProgram(cps);
//            for(int i = 0; i < 120; i++){
//                Sleep(100);
//                //if(cps->UCCI_which == 1){
//                //    if(DIS.first.UCCI_initDone == 1){
//                //        rc = true;
//                //        break;
//                //    }
//                //}
//                //else{
//                //    if(DIS.second.UCCI_initDone == 1){
//                //        rc = true;
//                //        break;
//                //    }
//                //}
//                if(cps->UCCI_initDone == 1){
//                    rc = true;
//                    break;
//                }
//            }
//            //Sleep(3000);
//            //if(cps->UCCI_initDone == 1){
//            //    rc = true;
//            //}
//            //else{
//            //    rc = false;
//            //}            
//            break;
//        case UCCI_DIS:
//            break;
//        case UCCI_QH:
//            break;
//        case UCCI_OHTER:
//            break;
//        default:
//            break;
//    }
//
//    if(rc == true){
//        LogOut(ColorShout,"加载引擎成功了！\n",true);
//    }
//    else{
//        LogOut(ColorSeek,"加载引擎失败！\n",false);
//    }
//
//    return rc;
//}

int 
GetYqinfoFromSqliteByID(ChessProgramState *cps,int id){

    sqlite3 *db_ini;
    char    *szErrMsg       = 0;
    int      nrow           = 0;
    int      ncolumn        = 0;
    int      rc             = 0;
    char    **azResult;
    char     sql[1024];

    if(rc = SqliteOpenDataBase(&db_ini,L3_DB_INI)){
        LogOut("-------------不能打开设定数据库-------------\n"); 
        return rc;      //打开有错,不能保存
    }

    sprintf_s(sql,1024,"SELECT * FROM yq WHERE yqID = %d",id);

    rc = sqlite3_get_table(db_ini,sql,&azResult,&nrow,&ncolumn,&szErrMsg);

    if(rc != SQLITE_OK){
        return rc;
    }

    if(nrow != 0){      //找到了记录 
        cps->yqID = id;
        sprintf_s(cps->UCCI_name,sizeof(cps->UCCI_name),"%s",azResult[ncolumn+1]);
        sprintf_s(cps->UCCI_file,sizeof(cps->UCCI_file),"%s",azResult[ncolumn+2]);
        sprintf_s(cps->UCCI_author,sizeof(cps->UCCI_author),"%s",azResult[ncolumn+3]);
        sprintf_s(cps->UCCI_verson,sizeof(cps->UCCI_verson),"%s",azResult[ncolumn+4]);
        /*sprintf_s(cps->UCCI_dualtime,"%d",*/
        cps->UCCI_dualtime = atoi(azResult[ncolumn+5]);
        sprintf_s(cps->UCCI_path,sizeof(cps->UCCI_path),"%s",azResult[ncolumn+6]);
        cps->ucci       = atoi(azResult[ncolumn+7]);
        cps->UCCI_elo   = atoi(azResult[ncolumn+8]);        
        sprintf_s(cps->UCCI_iniString,sizeof(cps->UCCI_iniString),"%s",azResult[ncolumn+9]);
        sprintf_s(cps->UCCI_otherString,sizeof(cps->UCCI_otherString),"%s",azResult[ncolumn+10]);
        
        cps->UCCI_smpNum    = atoi(azResult[ncolumn+11]);
        cps->UCCI_hashsize  = atoi(azResult[ncolumn+12]);
        cps->timePerStep    = atoi(azResult[ncolumn+13]);
        cps->searchDepth    = atoi(azResult[ncolumn+14]);
        cps->isBaoGan       = atoi(azResult[ncolumn+15]);
        cps->BaoGanTime     = atoi(azResult[ncolumn+16]);
        cps->addTimePerStep = atoi(azResult[ncolumn+17]);
        cps->islostTimeUp   = atoi(azResult[ncolumn+18]);
        cps->firstClassTimeStep = atoi(azResult[ncolumn+19]);
        cps->firstClassTime     = atoi(azResult[ncolumn+20]);
        cps->secondClassTimeStep= atoi(azResult[ncolumn+21]);
        cps->secondClassTime    = atoi(azResult[ncolumn+22]);
        cps->isBook             = atoi(azResult[ncolumn+23]);
        cps->isEGB              = atoi(azResult[ncolumn+24]);
        sprintf_s(cps->UCCI_addInfo,sizeof(cps->UCCI_addInfo),"%s",azResult[ncolumn+25]);
    }

    sqlite3_free_table(azResult);

    rc = sqlite3_close(db_ini);
    
    return rc;
}


//根据引擎的信息得到引擎的UCCI详细信息
int
FillYqUccciToSetDialog(ChessProgramState *cps, HWND hDlg){ //IDC_YQUCCI
            //1, 打开设定数据库
    sqlite3 *db_ini;
    char    *szErrMsg       = 0;
    int      nrow           = 0;
    int      ncolumn        = 0;
    int      rc             = 0;
    char    **azResult;
    char     sql[1024];
    //char    buf[512];

    if(rc = SqliteOpenDataBase(&db_ini,L3_DB_INI)){
        LogOut("-------------不能打开设定数据库-------------\n"); 
        return rc;      //打开有错,不能保存
    }

    sprintf_s(sql,1024,"SELECT * FROM ucci");

    rc = sqlite3_get_table(db_ini,sql,&azResult,&nrow,&ncolumn,&szErrMsg);

    if(rc != SQLITE_OK){
        return rc;
    }

     //清空协议列表
    SendDlgItemMessage(hDlg,IDC_YQUCCI,CB_RESETCONTENT,0,0);

    if(cps->ucci == 0){
        cps->ucci = 1;  //UCCI
    }
    int k;
    int nowID = -1;
    for(k = 1; k <= nrow; k++){      //对于每一个引擎
        //
        int   id = atoi(azResult[k*ncolumn+1]);
        if(id == cps->ucci){
            nowID = k;
        }    
        char  info[128];
        sprintf_s(info,sizeof(info),"%d) %s <%s>",id,azResult[k*ncolumn+0],azResult[k*ncolumn+2]);
        SendDlgItemMessage(hDlg,IDC_YQUCCI,CB_ADDSTRING,0,(LPARAM)info);
    }

    //释放为记录集分配的内存，如果返回了空记录集并不会发生错误
    sqlite3_free_table(azResult);

    rc = sqlite3_close(db_ini);

    //将当前选择的项设为当前 CB_SETCURSEL
    SendDlgItemMessage(hDlg,IDC_YQUCCI,CB_SETCURSEL,nowID-1,0);

    return rc;
}

//将所有的引擎名称填充到对话框
int
FillYqListToSetDialog(ChessProgramState *cps, HWND hDlg){  //IDC_YQ_LIST

        //1, 打开设定数据库
    sqlite3 *db_ini;
    char    *szErrMsg       = 0;
    int      nrow           = 0;
    int      ncolumn        = 0;
    int      rc             = 0;
    char    **azResult;
    char     sql[1024];
    char    buf[512];

    if(rc = SqliteOpenDataBase(&db_ini,L3_DB_INI)){
        LogOut("-------------不能打开设定数据库-------------\n"); 
        return rc;      //打开有错,不能保存
    }

    sprintf_s(sql,1024,"SELECT * FROM yq");

    rc = sqlite3_get_table(db_ini,sql,&azResult,&nrow,&ncolumn,&szErrMsg);

    if(rc != SQLITE_OK){
        return rc;
    }

    ChessProgramState tmp[1];
    //char  arg[512];

    //清空引擎列表
    SendDlgItemMessage(hDlg,IDC_YQ_LIST,CB_RESETCONTENT,0,0);

    int nowID = -1;
    int k;

    for(k = 1; k <= nrow; k++){      //对于每一个引擎
        //得到ID
        tmp->yqID = atoi(azResult[k*ncolumn + 0]);

        if(cps->yqID == tmp->yqID){
            nowID = k;
        }

        //得到程序名称
        sprintf_s(tmp->UCCI_name,32,"%s",azResult[(k)*ncolumn + 1]);
        //
        sprintf_s(buf,sizeof(buf),"%d) %s",tmp->yqID,tmp->UCCI_name);
        //列表
        SendDlgItemMessage(hDlg,IDC_YQ_LIST,CB_ADDSTRING,0,(LPARAM)buf);
    }
    
    //释放为记录集分配的内存，如果返回了空记录集并不会发生错误
    sqlite3_free_table(azResult);

    rc = sqlite3_close(db_ini);

    if(nowID == -1){ //当前选择的引擎不在列表中
        cps->yqID = tmp->yqID;
        GetYqinfoFromSqliteByID(cps,tmp->yqID);
        YqInfoToSetDialog(cps,hDlg);
        nowID = k;
    }

    //将当前选择的项设为当前 CB_SETCURSEL
     SendDlgItemMessage(hDlg,IDC_YQ_LIST,CB_SETCURSEL,nowID-1,0);

    return rc;
}


//将引擎的信息显示到对话框,要注意当前选定的是那一个
void
YqInfoToSetDialog(ChessProgramState *cps, HWND hDlg){

	//得到棋桌号
	int table;
	BOOL isGet;
	int  intGet;
	char buf[512];

	intGet = GetDlgItemInt(hDlg,IDC_Table,&isGet,false);

	if(isGet){
		table = intGet;
	}
	else{
		table = 0;
	}
	dispboard_t *pDis = OBS[table];		//cps = pDis->cur_set_cps;


	BOOL isDef = FALSE;

	//得到当前是那个引擎按下了
	if(IsDlgButtonChecked(hDlg,IDC_RADIO_YQA) == BST_CHECKED){	//是引擎Ａ按下了
		sprintf_s(buf,sizeof(buf),"引擎 (1) 设置对话框, 使用引擎号: %d, 当前引擎号: %d", 
			pDis->first.yqID,	cps->yqID);

		//看一下编号是不是相同了
		if(pDis->first.yqID != cps->yqID){
			isDef = TRUE;
		}

	}
	else{
		sprintf_s(buf,sizeof(buf),"引擎 (2) 设置对话框, 使用引擎号: %d, 当前引擎号: %d", 
			pDis->second.yqID,	cps->yqID);
		//看一下编号是不是相同了
		if(pDis->second.yqID != cps->yqID){
			isDef = TRUE;
		}
	}

	if(isDef == TRUE){
		EnableWindow(GetDlgItem(hDlg,ID_LOAD_SET_YQ),TRUE);		//使加载引擎按钮可用		
	}
	else{
		EnableWindow(GetDlgItem(hDlg,ID_LOAD_SET_YQ),FALSE);		
	}	

	// 还要看一下是不能删除，要不是一二才能删除哇
	if(pDis->set_cps.yqID != pDis->first.yqID && pDis->set_cps.yqID != pDis->second.yqID){
		EnableWindow(GetDlgItem(hDlg,IDC_DELETE_YQ), TRUE);		//使删除引擎按钮可用
	}
	else{
		EnableWindow(GetDlgItem(hDlg,IDC_DELETE_YQ), FALSE);	//使删除引擎按钮可用
	}

	SetWindowText(hDlg,buf);

	//

    //2, 填充ＹＱ列表框
    FillYqListToSetDialog(cps,hDlg);

    //3, 填充ＵＣＣＩ列表框
    FillYqUccciToSetDialog(cps,hDlg);

    //4, 引擎名称
    SetDlgItemText(hDlg,IDC_YQ_NAME,cps->UCCI_name);

    //5, 引擎的评估分
    SetDlgItemInt(hDlg, IDC_YQ_ELO, cps->UCCI_elo,false); //FALSE, uValue is unsigned. 
    
    //6, 多线程  IDC_SMP_NUM
    SetDlgItemInt(hDlg,IDC_SMP_NUM,cps->UCCI_smpNum,false);

    //引擎程序名
    SetDlgItemText(hDlg,IDC_YQ_PROGRAME,cps->UCCI_file);

    //引擎相对路径
    SetDlgItemText(hDlg,IDC_YQ_PATH,cps->UCCI_path);

    //初始指令
    SetDlgItemText(hDlg,IDC_initString,cps->UCCI_iniString);
    //其它指令
    SetDlgItemText(hDlg,IDC_YqOtherString,cps->UCCI_otherString);
    //开局库
    SendDlgItemMessage(hDlg,IDC_IsBook,BM_SETCHECK,cps->isBook,0);
    //残局库
    SendDlgItemMessage(hDlg,IDC_IsEGB, BM_SETCHECK,cps->isEGB,0);
    //hash表大小
    SetDlgItemInt(hDlg,IDC_HashSize,cps->UCCI_hashsize,false);
    //每步最多时间
    SetDlgItemInt(hDlg,IDC_TimePerStep,cps->timePerStep,false);
    //depth
    SetDlgItemInt(hDlg,IDC_SearchDepth,cps->searchDepth,false);

    //包干计时
    SendDlgItemMessage(hDlg,IDC_IsBaoGan,BM_SETCHECK,cps->isBaoGan,0);
    //是否分段计时 IDC_IsFenDuanTime
    SendDlgItemMessage(hDlg,IDC_IsFenDuanTime,BM_SETCHECK,!cps->isBaoGan,0);

    //多少分钟每局 IDC_BanGanTime
    SetDlgItemInt(hDlg,IDC_BanGanTime,cps->BaoGanTime,false);
    //每走一步加时 TimeAddPerStep
    SetDlgItemInt(hDlg,IDC_TimeAddPerStep,cps->addTimePerStep,false);
    //IDC_IsLostTimeUp ?
    SendDlgItemMessage(hDlg,IDC_IsLostTimeUp,BM_SETCHECK,cps->islostTimeUp,0);

    //第一时间段步 IDC_firstClassStep
    SetDlgItemInt(hDlg,IDC_firstClassStep,cps->firstClassTimeStep,false);
    //第一时间段时间 IDC_firstClassTime
    SetDlgItemInt(hDlg,IDC_firstClassTime,cps->firstClassTime,false);
    //第二时间段步
    SetDlgItemInt(hDlg,IDC_secondClassStep,cps->secondClassTimeStep,false);
    //第二时间段时间 secondClassTime
    SetDlgItemInt(hDlg,IDC_secondClassTime,cps->secondClassTime,false);
}

//将对话框的信息转到CPS中
bool
SetDialogToCps(ChessProgramState *cps, HWND hDlg){

    BOOL isGet;
    int  intGet;

    //1,得到当前选择的引擎的编号
    int sel = (int)SendDlgItemMessage(hDlg,IDC_YQ_LIST,CB_GETCURSEL,0,0);
    char buf[MSG_SIZ];
    SendDlgItemMessage(hDlg,IDC_YQ_LIST,CB_GETLBTEXT,sel,(LPARAM)buf);

    cps->yqID  = atoi(buf);

    //得到选择协议编号
    sel = (int)SendDlgItemMessage(hDlg,IDC_YQUCCI,CB_GETCURSEL,0,0);
    SendDlgItemMessage(hDlg,IDC_YQUCCI,CB_GETLBTEXT,sel,(LPARAM)buf);

    cps->ucci = atoi(buf);

    //得到引擎的名称
    GetDlgItemText(hDlg,IDC_YQ_NAME,cps->UCCI_name,sizeof(cps->UCCI_name));

    //得到引擎当前的ＥＬＯ
    intGet = GetDlgItemInt(hDlg,IDC_YQ_ELO,&isGet,false);
    if(!isGet){
       MessageBox(hDlg,"请设置正确的引擎得分(ELO)!","ＥＲＲＯＲ。。。",MB_OK);
       return false;
    }
    cps->UCCI_elo = intGet;

    //线程数
    intGet = GetDlgItemInt(hDlg,IDC_SMP_NUM,&isGet,false);
    if(!isGet){
       MessageBox(hDlg,"请设置正确的线程数!","ＥＲＲＯＲ。。。",MB_OK);
       return false;
    }
    cps->UCCI_smpNum = intGet;
    if(cps->UCCI_smpNum < 0 || cps->UCCI_smpNum > 16){
        cps->UCCI_smpNum = 1;
    }
   

    //是否有开局库
    if(IsDlgButtonChecked(hDlg,IDC_IsBook) == BST_CHECKED){
        cps->isBook = 1;
    }
    else{
        cps->isBook = 0;
    }
    //是否有残局库
    if(IsDlgButtonChecked(hDlg,IDC_IsEGB) == BST_CHECKED){
        cps->isEGB = 1;
    }
    else{
        cps->isEGB = 0;
    }
    //初始指令
    GetDlgItemText(hDlg,IDC_initString,cps->UCCI_iniString,sizeof(cps->UCCI_iniString));
    //其它指令
    GetDlgItemText(hDlg,IDC_YqOtherString,cps->UCCI_otherString,sizeof(cps->UCCI_otherString));
    //相对路径
    GetDlgItemText(hDlg,IDC_YQ_PATH,cps->UCCI_path,sizeof(cps->UCCI_path));
    //引擎文件名
    GetDlgItemText(hDlg,IDC_YQ_PROGRAME,cps->UCCI_file,sizeof(cps->UCCI_file));
    //HASH表大小
    intGet = GetDlgItemInt(hDlg,IDC_HashSize,&isGet,false);  //&cps->hashSize,    
    if(!isGet){
       MessageBox(hDlg,"请设置正确的HASH表大小!","ＥＲＲＯＲ。。。",MB_OK);
       return false;
    }
    cps->UCCI_hashsize = intGet;
    if(cps->UCCI_hashsize < 16 || cps->UCCI_hashsize > 256){
        cps->UCCI_hashsize = 16;
    }
    //每步时间
    intGet = GetDlgItemInt(hDlg,IDC_TimePerStep,&isGet,false); //&cps->timePerStep,
    if(!isGet){
       MessageBox(hDlg,"请设置正确的每步搜索时间!","ＥＲＲＯＲ。。。",MB_OK);
       return false;
    }
    cps->timePerStep = intGet;
    //搜索层数
    intGet = GetDlgItemInt(hDlg,IDC_SearchDepth,&isGet,false);

    if(!isGet){
        MessageBox(hDlg,"请设置正确的每步搜索层数!","ＥＲＲＯＲ。。。",MB_OK);
        return false;
    }
    cps->searchDepth = intGet;

    if(cps->searchDepth < 0 || cps->searchDepth > 60){
        cps->searchDepth = 0;
    }
    //计时设定
    if(IsDlgButtonChecked(hDlg,IDC_IsBaoGan) == BST_CHECKED){
        cps->isBaoGan = 1;
    }
    else{
        cps->isBaoGan = 0;
    }
    
    //多少分钟／局
    intGet = GetDlgItemInt(hDlg,IDC_BanGanTime,&isGet,false);
    if(!isGet){
        MessageBox(hDlg,"请设置正确的包干时间!","ＥＲＲＯＲ。。。",MB_OK);
        return false;
    }
    cps->BaoGanTime = intGet;    
    if(cps->BaoGanTime == 0){
        cps->BaoGanTime = 1;
    }

    //每走一步加多少秒
    intGet = GetDlgItemInt(hDlg,IDC_TimeAddPerStep,&isGet,false);
    if(!isGet){
        MessageBox(hDlg,"请设置正确的每步加时!","ＥＲＲＯＲ。。。",MB_OK);
        return false;
    }
    cps->addTimePerStep = intGet;

    //不是超时判负
    if(IsDlgButtonChecked(hDlg,IDC_IsLostTimeUp) == BST_CHECKED){
        cps->islostTimeUp = 1;
    }
    else{
        cps->islostTimeUp = 0;
    }
    //第一时间段步子
    intGet = GetDlgItemInt(hDlg,IDC_firstClassStep,&isGet,false);
    if(!isGet){
        MessageBox(hDlg,"请设置正确的第一时间段要走的步数!","ＥＲＲＯＲ。。。",MB_OK);
        return false;
    }
    cps->firstClassTimeStep = intGet;
    if(cps->firstClassTimeStep == 0){
        cps->firstClassTimeStep = 30;
    }
    //第一时间段时间
    intGet = GetDlgItemInt(hDlg,IDC_firstClassTime,&isGet,false);
    if(!isGet){
        MessageBox(hDlg,"请设置正确的第一时间段时间!","ＥＲＲＯＲ。。。",MB_OK);
        return false;
    }
    cps->firstClassTime = intGet;
    if(cps->firstClassTime == 0){
        cps->firstClassTime = 1;
    }
    //第二时间段步子
    intGet = GetDlgItemInt(hDlg,IDC_secondClassStep,&isGet,false);
    if(!isGet){
        MessageBox(hDlg,"请设置正确的第二时间段要走的步数!","ＥＲＲＯＲ。。。",MB_OK);
        return false;
    }
    cps->secondClassTimeStep = intGet;
    if(cps->secondClassTimeStep == 0){
        cps->secondClassTimeStep = 10;
    }
    intGet = GetDlgItemInt(hDlg,IDC_secondClassTime,&isGet,false);
    if(!isGet){
        MessageBox(hDlg,"请设置正确的第二时间段时间!","ＥＲＲＯＲ。。。",MB_OK);
        return false;
    }
    cps->secondClassTime = intGet;
    if(cps->secondClassTime == 0){
        cps->secondClassTime = 1;
    }
    return true;
}


//更新引擎信息到设定数据库中
int 
UpdateCpsInfoToSqlite(ChessProgramState *cps){
    int rc              = -1;
    sqlite3 *db_ini;
    char    *szErrMsg   = 0;
    char    sql[4096];

    if((rc = SqliteOpenDataBase(&db_ini,L3_DB_INI)) == 0){
        sprintf_s(sql,sizeof(sql),
            "UPDATE yq SET yqName='%s',yqFile='%s',yqAuthor='%s',yqVerson='%s',yqDualTime=%d, \
            path='%s',xieyiID=%d,elo=%d,initString='%s',OtherString='%s',smpNum=%d,hashSize=%d,moveTime=%d,\
            depth=%d,isBaoGan=%d,BaoGanTime=%d,stepInc=%d,TimeUpLose=%d,FT_Step=%d,FT_Time=%d,SC_Step=%d,\
            SC_Time=%d,haveBook=%d,haveEGB=%d,yqOther='%s' WHERE yqID = %d",
            cps->UCCI_name,
            cps->UCCI_file,
            cps->UCCI_author,
            cps->UCCI_verson,
            cps->UCCI_dualtime,
            cps->UCCI_path,
            cps->ucci,
            cps->UCCI_elo,
            cps->UCCI_iniString,
            cps->UCCI_otherString,
            cps->UCCI_smpNum,
            cps->UCCI_hashsize,
            cps->timePerStep,
            cps->searchDepth,
            cps->isBaoGan,
            cps->BaoGanTime,
            cps->addTimePerStep,
            cps->islostTimeUp,
            cps->firstClassTimeStep,
            cps->firstClassTime,
            cps->secondClassTimeStep,
            cps->secondClassTime,
            cps->isBook,
            cps->isEGB,
            cps->UCCI_addInfo,
            cps->yqID
            );

        

        rc = sqlite3_exec(db_ini,sql,0,0,&szErrMsg);
        if(rc != 0){
            LogOut(szErrMsg);
            sqlite3_free(szErrMsg);
        }
        sqlite3_close(db_ini);      //关闭数据库        
    }

    return rc;
}


//通过引擎的ID删除引擎
int 
DeleteCpsByYqID(int yqid){
    int rc = -1;
    sqlite3 *db_ini;
    char *szErrMsg = 0;
    char sql[4096];
    if((rc == SqliteOpenDataBase(&db_ini,L3_DB_INI)) == 0){//打开成功了
        sprintf_s(sql,sizeof(sql),
            "DELETE FROM yq WHERE yqID = %d",yqid);
        rc = sqlite3_exec(db_ini,sql,0,0,&szErrMsg);
        if(rc != 0){
            LogOut(szErrMsg);
            sqlite3_free(szErrMsg);
        }
        sqlite3_close(db_ini);
    }
    return rc;
}

//插入一个新引擎,并得到新引擎的ID
int
InsertCpsInfoToSqlite(ChessProgramState *cps, int *id){
            //1, 打开设定数据库
    sqlite3 *db_ini;
    char    *szErrMsg       = 0;
    int      nrow           = 0;
    int      ncolumn        = 0;
    int      rc             = -1;
    char    **azResult;
    char     sql[4096];

    if((rc = SqliteOpenDataBase(&db_ini,L3_DB_INI)) == 0){   //打开成功了
        //插入引擎信息
        //INSERT INTO table (column_list) VALUES (value_list);
        sprintf_s(sql,sizeof(sql),
            "INSERT INTO yq (yqName,yqFile,yqAuthor,yqVerson,yqDualTime,path,xieyiID,elo,\
                            initString,OtherString,smpNum,hashSize,moveTime,depth,isBaoGan,\
                            BaoGanTime,stepInc,TimeUpLose,FT_Step,FT_Time,SC_Step,\
                            SC_Time,haveBook,haveEGB,yqOther)  \
                            VALUES('%s','%s','%s','%s','%d','%s','%d','%d','%s','%s',\
                                   '%d','%d','%d','%d','%d','%d','%d','%d','%d','%d',\
                                   '%d','%d','%d','%d','%s')",
            cps->UCCI_name,
            cps->UCCI_file,
            cps->UCCI_author,
            cps->UCCI_verson,
            cps->UCCI_dualtime,
            cps->UCCI_path,
            cps->ucci,
            cps->UCCI_elo,
            cps->UCCI_iniString,
            cps->UCCI_otherString,
            cps->UCCI_smpNum,
            cps->UCCI_hashsize,
            cps->timePerStep,
            cps->searchDepth,
            cps->isBaoGan,
            cps->BaoGanTime,
            cps->addTimePerStep,
            cps->islostTimeUp,
            cps->firstClassTimeStep,
            cps->firstClassTime,
            cps->secondClassTimeStep,
            cps->secondClassTime,
            cps->isBook,
            cps->isEGB,
            cps->UCCI_addInfo
            );

        rc = sqlite3_exec(db_ini,sql,0,0,&szErrMsg);

        if(rc != 0){
            LogOut(szErrMsg);
            sqlite3_free(szErrMsg);
        }

		// sprintf_s(sql,1024,"SELECT * FROM ucci");
		// SELECT relname, relpages FROM pg_class ORDER BY relpages DESC

		sprintf_s(sql,sizeof(sql),
			"SELECT yqID FROM yq ORDER BY yqID DESC");                        

		rc = sqlite3_get_table(db_ini,sql,&azResult,&nrow,&ncolumn,&szErrMsg);

		if(rc != 0){
            LogOut(szErrMsg);
            sqlite3_free(szErrMsg);
			sqlite3_close(db_ini);
			return rc;
        }


		for(int k = 1; k <= nrow; k++){
			*id = atoi(azResult[k*ncolumn + 0]);
			break;
		}

		sqlite3_free_table(azResult);

        sqlite3_close(db_ini);
    }
    return rc;
}

//
void 
SetTimeControlItemlEnables(HWND hDlg,dispboard_t* pDis){

	ChessProgramState *cps = &pDis->set_cps;

    EnableWindow(GetDlgItem(hDlg,IDC_BanGanTime),		 cps->isBaoGan);
    EnableWindow(GetDlgItem(hDlg,IDC_firstClassStep),	!cps->isBaoGan);
    EnableWindow(GetDlgItem(hDlg,IDC_firstClassTime),	!cps->isBaoGan);
    EnableWindow(GetDlgItem(hDlg,IDC_secondClassStep),	!cps->isBaoGan);
    EnableWindow(GetDlgItem(hDlg,IDC_secondClassTime),	!cps->isBaoGan);	
    EnableWindow(GetDlgItem(hDlg,IDC_TimeAddPerStep),	!cps->isBaoGan);
    EnableWindow(GetDlgItem(hDlg,IDC_IsLostTimeUp),		!cps->isBaoGan);

    SendDlgItemMessage(hDlg,IDC_IsBaoGan,BM_SETCHECK,		cps->isBaoGan,0);
    SendDlgItemMessage(hDlg,IDC_IsFenDuanTime,BM_SETCHECK, !cps->isBaoGan,0);

    //SendDlgItemMessage(hDlg,IDC_RADIO_YQA,BM_SETCHECK,cps == &ppDis->first,0);
    //SendDlgItemMessage(hDlg,IDC_RADIO_YQB,BM_SETCHECK,cps != &ppDis->first,0);

    //if(cps->UCCI_which == 1){
    //if(cps->playWhat == WHITE){
    //   SetWindowText(hDlg,  "引擎 (1) 设置对话框");	
    //}
    //else{
    //    SetWindowText(hDlg, "引擎 (2) 设置对话框");	
    //}
}

//
int 
GetSelectYqID(HWND hDlg){       //得到当前选项的引擎ＩＤ
    int sel = (int)SendDlgItemMessage(hDlg,IDC_YQ_LIST,CB_GETCURSEL,0,0);
    char buf[MSG_SIZ];
    SendDlgItemMessage(hDlg,IDC_YQ_LIST,CB_GETLBTEXT,sel,(LPARAM)buf);                        
    int id  = atoi(buf);
    return id;
}

LRESULT CALLBACK
YqSetCallBack(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){

    //char str[512];

    OPENFILENAME  ofn;
    char buf[MSG_SIZ];
    char initDir[MAX_PATH];
    char title[MSG_SIZ];

    switch(message){
        case WM_INITDIALOG:{
            CenterWindow(hDlg,GetWindow(hDlg,GW_OWNER));	

			SendDlgItemMessage(hDlg,IDC_RADIO_YQA,BM_SETCHECK,1,0);
			SendDlgItemMessage(hDlg,IDC_RADIO_YQB,BM_SETCHECK,0,0);

            int  table = (int)lParam;

			SetDlgItemInt(hDlg,IDC_Table,table,FALSE);			//将桌号保存到对话框中

            dispboard_t *pDis = OBS[table];

            pDis->set_cps = pDis->first;							//显示第一个引擎

			//这儿不用了
            //GetYqinfoFromSqliteByID(pDis->cur_set_cps,pDis->cur_set_cps->yqID);	//从数据库中取得引擎信息

            YqInfoToSetDialog(&pDis->set_cps,hDlg);								//将引擎信息显示到对话框中

            SetTimeControlItemlEnables(hDlg,pDis);								//显示相应的设定时间			

            return TRUE;
						   }
		case WM_USER_YqLoad_OK:	{		//引擎加载成功了

			int table;
			BOOL isGet;
			int  intGet;

			intGet = GetDlgItemInt(hDlg,IDC_Table,&isGet,false);

			if(isGet){
				table = intGet;
			}
			else{
				table = 0;
			}
            dispboard_t *pDis = OBS[table];		//cps = pDis->cur_set_cps;

			//更新引擎
			pDis->set_cps.isInLoading  = FALSE;
			
			memcpy(pDis->set_cps.loadWhich, &pDis->set_cps, sizeof(ChessProgramState));

			YqInfoToSetDialog(&pDis->set_cps,hDlg);
			SetTimeControlItemlEnables(hDlg,pDis);

								}
			break;
        //--------------------------------------------------------------                 
        case WM_COMMAND:{	//有按钮信息   

			

			int table;
			BOOL isGet;
			int  intGet;

			intGet = GetDlgItemInt(hDlg,IDC_Table,&isGet,false);

			if(isGet){
				table = intGet;
			}
			else{
				table = 0;
			}
            dispboard_t *pDis = OBS[table];		//cps = pDis->cur_set_cps;

			if(TRUE == pDis->set_cps.isInLoading){		//当前正在加载引擎
				SendToPlayerByColor("\n当前正在加载引擎之中\n",ColorShout,FALSE);
				break;
			}

            
            switch(LOWORD(wParam)){
		//		                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
        case IDC_YQ_ADD:{                   //添加引擎按钮
                    ZeroMemory(&ofn,sizeof(ofn));
                    ofn.lStructSize         = sizeof(OPENFILENAME);
                    ofn.lpstrFilter         = "象棋引擎\0*.exe\0";
                    ofn.nMaxCustFilter      = MSG_SIZ;
                    ofn.nFilterIndex        = 1;
                    ofn.hInstance           = hInst;
                    ofn.nMaxFile            = MAX_PATH;
                    ofn.hwndOwner           = hDlg;
                    buf[0]                  = 0;
                    ofn.lpstrFile           = buf;
                    StringCbPrintf(title,sizeof(title),
                        "请选择一个象棋引擎 (引擎应放在主程序目录下的plugins目录下!)");
                    ofn.lpstrTitle          = title;
                    StringCbPrintf(initDir,sizeof(initDir),
                        "%s%s",installDir,"plugins\\");
                    ofn.lpstrInitialDir		= initDir;			//初始化目录
                    ofn.Flags               = OFN_EXPLORER+OFN_FILEMUSTEXIST+OFN_PATHMUSTEXIST+OFN_HIDEREADONLY;
                    if(GetOpenFileName(&ofn)){
                       //先判断一下，是不是在installDir以下
                        _strlwr_s(initDir,sizeof(initDir));
                        _strlwr_s(buf,sizeof(buf));
                        if(strstr(buf,initDir) == NULL){
                            StringCbPrintf(buf,MSG_SIZ,"请将象棋引擎放到 %s目录下！",initDir);
                            MessageBox(hDlg,buf,"ERROR...",MB_OK);
                            return TRUE;
                        }

                        //得到了一个引擎文件
                        
                        //1,得到程序的名称
                        ChessProgramState tmp[1];

						memcpy(tmp,&pDis->set_cps,sizeof(ChessProgramState));
                        
                        StringCbPrintf(tmp->UCCI_file,sizeof(tmp->UCCI_file),buf+ofn.nFileOffset);
                        StringCbPrintf(tmp->UCCI_name,sizeof(tmp->UCCI_file),buf+ofn.nFileOffset);

                        //2,得到引擎的目录
                        char *p1 = strstr(buf,"plugins\\");
                        char *p2 = strstr(buf,tmp->UCCI_file);

                        StringCbPrintf(tmp->UCCI_path,p2-p1+1,p1);
                        
                        LogOut("象棋引擎：<<");
                        LogOut(tmp->UCCI_name);

						int id = pDis->set_cps.yqID;
                        
                        if(InsertCpsInfoToSqlite(tmp, &id) == 0){       //将信息保存到数据库中                            
                            //LogOut(">>已成功保存! 请更改相应的设置\n");
							SendToPlayerByColor(">>已成功保存! 请更改相应的设置\n",ColorShout,FALSE);

							//得到当前的ID信息
							GetYqinfoFromSqliteByID(tmp, id);

                            FillYqListToSetDialog(tmp,hDlg);	 //还是将原先使用的显示一下

							pDis->set_cps.yqID = id;			 //更新当前的ID
                        }
                        else{
                             //LogOut(">>保存失败!\n");
							SendToPlayerByColor(">>保存失败!\n",ColorShout,FALSE);
                        }
                    }  
                        }
                    break;
				//
                case IDC_IsBaoGan:{                  //包干计时按钮
                    pDis->set_cps.isBaoGan   = TRUE;
                    SetTimeControlItemlEnables(hDlg,pDis);
                                  }
                    break;    
				//
                case IDC_IsFenDuanTime:  {           //分段计时按钮
                    pDis->set_cps.isBaoGan   = FALSE;
                    SetTimeControlItemlEnables(hDlg,pDis);
                                         }
                    break;
				//
				case IDC_RADIO_YQA: {                //引擎(1)按钮
					if(IsDlgButtonChecked(hDlg,IDC_RADIO_YQA) == BST_CHECKED){

						SendDlgItemMessage(hDlg,IDC_RADIO_YQB,BM_SETCHECK,0,0);

						pDis->set_cps = pDis->first;

						GetYqinfoFromSqliteByID(&pDis->set_cps,pDis->set_cps.yqID);

						YqInfoToSetDialog(&pDis->set_cps,hDlg);
					}
					SetTimeControlItemlEnables(hDlg,pDis);
									}
									break;
				//
				case IDC_RADIO_YQB:  {               //引擎(2)按钮
					if(IsDlgButtonChecked(hDlg,IDC_RADIO_YQB) == BST_CHECKED){

						SendDlgItemMessage(hDlg,IDC_RADIO_YQA,BM_SETCHECK,0,0);

						pDis->set_cps = pDis->second;

						GetYqinfoFromSqliteByID(&pDis->set_cps,pDis->set_cps.yqID);

						YqInfoToSetDialog(&pDis->set_cps,hDlg);

						SetTimeControlItemlEnables(hDlg,pDis);
					}           
									 }
									 break;
                //  
                case IDC_YQ_LIST: {    //改变了当前的引擎
                    if(HIWORD(wParam) == CBN_SELCHANGE){

                        pDis->set_cps.yqID = GetSelectYqID(hDlg);

                        GetYqinfoFromSqliteByID(&pDis->set_cps,pDis->set_cps.yqID);

                        YqInfoToSetDialog(&pDis->set_cps,hDlg);

                        SetTimeControlItemlEnables(hDlg,pDis);
                    }
                                  }
                    break;
                //
                case IDC_DELETE_YQ:                 //删除引擎按钮
                    {
						if(MessageBox(hDlg,"请确认,本操作将删除这个引擎的!","注意了!",MB_OKCANCEL) == IDOK){
							int id  = GetSelectYqID(hDlg);

							if(DeleteCpsByYqID(id) == SQLITE_OK){
								SendToPlayerByColor("\n您已成功删除了一个引擎\n",ColorShout,FALSE);
								
								//将当前的引擎设定为使用的引擎
								if(IsDlgButtonChecked(hDlg,IDC_RADIO_YQA) == BST_CHECKED){	//是引擎Ａ按下了
									pDis->set_cps = pDis->first;
								}
								else{
									pDis->set_cps = pDis->second;
								}
								YqInfoToSetDialog(&pDis->set_cps,hDlg);
								SetTimeControlItemlEnables(hDlg,pDis);
							}
							else{
								SendToPlayerByColor("\n您无法删除这个引擎\n",ColorShout,FALSE);
							}
						}
                    }
                    break;
				//
				case ID_LOAD_SET_YQ: {            //加载一个引擎
					BOOL can = TRUE;
					ChessProgramState *precps = NULL;
					if(IsDlgButtonChecked(hDlg,IDC_RADIO_YQA) == BST_CHECKED){
						if(pDis->set_cps.yqID == pDis->first.yqID){		//
							can = FALSE;							
						}
						precps = &pDis->first;
					}
					else{
						if(pDis->set_cps.yqID == pDis->second.yqID){		//
							can = FALSE;							
						}
						precps = &pDis->second;
					}
					if(can == FALSE){
						MessageBox(hDlg,"你已加载了当前的引擎，不要再加载了","Error",MB_OK);
						EnableWindow(GetDlgItem(hDlg,ID_LOAD_SET_YQ),FALSE);
						break;
					}

					LogOut("\n正在加载引擎，请稍候一下....\n");

					LoadChessProgramState(precps, &pDis->set_cps, hDlg);					

					//先得卸载原先的引擎
					//UnLoadChessProgramState(precps, hDlg);

					//while(precps->hwndHide != NULL){
					//	Sleep(500);
					//}
					//Sleep(500);

					//LoadChessProgramState(&ppDis->set_cps,hDlg);		//这是用线程加载，

					//while(&ppDis->set_cps.hwndHide != NULL){
					//	Sleep(500);
					//}

					//Sleep(2000);

					//下面的不能用，因为可能还没加载成功
		
					//if(TRUE == ppDis->set_cps.UCCI_initDone){			//已加载成功了
					//	if(IsDlgButtonChecked(hDlg,IDC_RADIO_YQA) == BST_CHECKED){
					//		ppDis->first = ppDis->set_cps;
					//	}
					//	else{
					//		ppDis->second = ppDis->second;
					//	}

					//	YqInfoToSetDialog(&ppDis->set_cps,hDlg);

					//	SetTimeControlItemlEnables(hDlg,pDis);
					//}
					//else{
					//	SendToPlayerByColor(">>不能加载当前的引擎!\n",ColorShout,FALSE);
					//}
									 }
					break;
				//
                case ID_UPDATE_SET_ONLY:      //将设置更新
                    {                       
						//1，先要看一下要更新的是不是与当前使用的一样
						
						ChessProgramState tmp[1];
						
						SetDialogToCps(tmp,hDlg);
						
						if(UpdateCpsInfoToSqlite(tmp) == SQLITE_OK){

							//还要看一下是不是当前使用的引擎设置
							if(pDis->set_cps.yqID == pDis->first.yqID){
								pDis->first = pDis->set_cps;
							}
							if(pDis->set_cps.yqID == pDis->second.yqID){
								pDis->second = pDis->set_cps;
							}

							//SendToPlayerByColor("\n更新当前引擎设置成功！\n",ColorShout,FALSE);
							LogOut("\n更新当前引擎设置成功！\n");
						}
						else{
							SendToPlayerByColor("\n您无法更新当前的引擎参数\n",ColorShout,FALSE);
						}                      
                    }
                    break;
                case IDOK:                          //确认按钮
                    //1, 看是不是更换了引擎,如果是更换了，则要停止当前的，尝试加载现在的，
                    {
                        //int id = GetSelectYqID(hDlg);
                        // ChessProgramState tmp[1];
                        // SetDialogToCps(tmp,hDlg);
                        // if(!UpdateCpsInfoToSqlite(tmp)){
                        //     //MessageBox(hDlg,"更新当前引擎设置成功！","请按ＯＫ返回",MB_OK);
                        //     LogOut("更新当前引擎设置成功！\n");
                        //     if(id == pDis->first.yqID){
                        //         SetDialogToCps(&pDis->first,hDlg);
                        //     }
                        //     else if(id == pDis->second.yqID){
                        //         SetDialogToCps(&pDis->second,hDlg);
                        //     }
                        // }
                        // else{
                        //     //MessageBox(hDlg,"更新当前引擎设置失败！","请按ＯＫ返回",MB_OK);
                        //     LogOut("更新当前引擎设置失败！\n");
                        // } 

                        // if(pDis->first.yqID != pDis->pre_first_id){
                        //     GetYqinfoFromSqliteByID(&pDis->first,pDis->first.yqID);
                        //     LoadChessProgramState(&pDis->first, hDlg);
                        // }
                        // if(pDis->second.yqID != pDis->pre_second_id){
                        //     GetYqinfoFromSqliteByID(&pDis->second,pDis->second.yqID);
                        //     LoadChessProgramState(&pDis->second, hDlg);
                        // }
                    }
                    //
                    EndDialog(hDlg, TRUE);
                    return TRUE;
                    break;
                case IDCANCEL:
                    EndDialog(hDlg,FALSE);
                    return TRUE;                    
                default:
                    break;
            }
                        }
                        break;        
        default:
            break;
    }

    return FALSE;
}

//引擎设置对话框 传入一个桌号参数

void		
YqSetOptionsPopup(int table){

	dispboard_t *pDis = OBS[table];
    FARPROC lpProc = MakeProcInstance((FARPROC)YqSetCallBack, hInst);
    DialogBoxParam(hInst,MAKEINTRESOURCE(IDD_YQ_SET),pDis->hwndThis,(DLGPROC) lpProc,(LPARAM)table);
    FreeProcInstance(lpProc);

}
