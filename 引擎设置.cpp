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


void							//原先的引擎，   //要加载的引擎				 //引擎引擎的窗口
LoadChessProgramState(ChessProgramState *precps, ChessProgramState *loadcps, HWND hWin){

	//ShowWindow(win,SW_HIDE);			//将窗口隐藏一下

	//if(precps->isUpLoading == TRUE){
	//	SendToPlayerByColor("对不起，当前的引擎正在卸载之中，请稍等后再加载!!\n",ColorShout,FALSE);
	//	return;
	//}

	if(precps->cps_stat == Cps_UpLoading){
		SendToPlayerByColor(L"对不起，当前的引擎正在卸载之中，请稍等后再加载!!\n",ColorShout,FALSE);
		return;
	}

	if(loadcps->cps_stat == Cps_InLoading){
		SendToPlayerByColor(L"对不起，当前的引擎正在加载之中，请稍等后再加载!!\n",ColorShout,FALSE);
		return;
	}

	if(loadcps->cps_stat == Cps_Waiting){
		SendToPlayerByColor(L"对不起，当前的引擎已加载，请不要再次加载!!\n",ColorShout,FALSE);
		return;
	}


	loadcps->loadWin        = hWin;		   //保存引擎的窗口，好向窗口发送完成的，或退出的消息
	loadcps->loadPre        = precps;      //
	precps->loadWhich		= loadcps;

	loadcps->playWhat       = precps->playWhat;
	precps->playWhat        = NEUTRAL;

	if(precps->cps_stat != Cps_NotLoad){
		LogOut(_T("\n正在卸载引擎: "));
		LogOut(precps->UCCI_name);
		LogOut(_T("\n可能要一些时间， 请稍候...\n"));

		switch(precps->ucci){
			case UCCI_UCCI_ms:
			case UCCI_UCCI_OLD:
				if(precps->cps_stat == Cps_Pondering 
					|| precps->cps_stat == Cps_Thinking 
					|| precps->cps_stat == Cps_Analyse){
						SendToProgram(L"stop\n",precps);
						Sleep(100);
				}
				SendToProgram(L"quit\n", precps);
				break;
			case UCCI_GGchess:
				if(precps->cps_stat == Cps_Pondering 
					|| precps->cps_stat == Cps_Thinking 
					|| precps->cps_stat == Cps_Analyse){
					SendToProgram(L"stop\n", precps);
						Sleep(100);
				}
				SendToProgram(L"quit\n", precps);
				break;
			case UCCI_CYC105:
				if(precps->cps_stat == Cps_Pondering 
					|| precps->cps_stat == Cps_Thinking 
					|| precps->cps_stat == Cps_Analyse){
					SendToProgram(L"stop\n", precps);
						Sleep(100);
				}
				SendToProgram(L"quit\n", precps);
				break;
			default:
				SendToProgram(L"quit\n", precps);
				SendToProgram(L"QUIT\n", precps);
				break;
		}
		precps->cps_stat = Cps_UpLoading;			//引擎正在卸载
	}
	else{
		LogOut(_T("\n正在加载引擎:\n"));
		LogOut(loadcps->UCCI_name);
		LogOut(_T("\n可能要一些时间，请稍候....\n"));
		StartChessProgram(loadcps);
	}
}


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
		LogOut(_T("-------------不能打开设定数据库-------------\n"));
		return rc;      //打开有错,不能保存
	}
	setlocale(LC_CTYPE, "chs");
	sprintf_s(sql,1024,"SELECT * FROM yq WHERE yqID = %d",id);

	rc = sqlite3_get_table(db_ini,sql,&azResult,&nrow,&ncolumn,&szErrMsg);

	if(rc != SQLITE_OK){

		MessageBox(NULL, _T("不能打开引擎信息"), _T("Error"), MB_OK);

		return rc;
	}

	if(nrow != 0){      //找到了记录 
		cps->yqID = id;
		swprintf_s(cps->UCCI_name, sizeof(cps->UCCI_name) / sizeof(TCHAR), _T("%S"), (azResult[ncolumn + 1]));
		swprintf_s(cps->UCCI_file, sizeof(cps->UCCI_file) / sizeof(TCHAR), _T("%S"), (azResult[ncolumn + 2]));
		swprintf_s(cps->UCCI_author, sizeof(cps->UCCI_author) / sizeof(TCHAR), _T("%S"), (azResult[ncolumn + 3]));
		swprintf_s(cps->UCCI_verson, sizeof(cps->UCCI_verson) / sizeof(TCHAR), _T("%S"), (azResult[ncolumn + 4]));
		/*sprintf_s(cps->UCCI_dualtime,"%d",*/
		cps->UCCI_dualtime = atoi(azResult[ncolumn+5]);
		//swprintf_s(cps->UCCI_path, sizeof(cps->UCCI_path) / sizeof(TCHAR), _T("%S"), (azResult[ncolumn + 6]));

		swprintf_s(cps->UCCI_path, sizeof(cps->UCCI_path) / sizeof(TCHAR), _T("%S"), "");
		cps->ucci            = atoi(azResult[ncolumn+7]);
		cps->UCCI_Book_Num   = atoi(azResult[ncolumn+8]);        
		swprintf_s(cps->UCCI_iniString, sizeof(cps->UCCI_iniString) / sizeof(TCHAR), _T("%S"), (azResult[ncolumn + 9]));
		swprintf_s(cps->UCCI_otherString, sizeof(cps->UCCI_otherString) / sizeof(TCHAR), _T("%S"), (azResult[ncolumn + 10]));

		cps->UCCI_smpNum		= atoi(azResult[ncolumn+11]);
		cps->UCCI_hashsize		= atoi(azResult[ncolumn+12]);
		cps->timePerStep		= atoi(azResult[ncolumn+13]);
		cps->timeSearchDepth    = atoi(azResult[ncolumn+14]);
		cps->IsBaoGan		    = atoi(azResult[ncolumn+15]);
		cps->BaoGanTime  		= atoi(azResult[ncolumn+16]);
		cps->timePerStepAdd		= atoi(azResult[ncolumn+17]);
		cps->timeIsLost			= atoi(azResult[ncolumn+18]);
		cps->time_1_Step		= atoi(azResult[ncolumn+19]);
		cps->time_1_Time		= atoi(azResult[ncolumn+20]);
		cps->time_2_Step		= atoi(azResult[ncolumn+21]);
		cps->time_2_Time		= atoi(azResult[ncolumn+22]);
		cps->useBook            = atoi(azResult[ncolumn+23]);
		cps->isEGB              = atoi(azResult[ncolumn+24]);
		swprintf_s(cps->UCCI_addInfo, sizeof(cps->UCCI_addInfo) / sizeof(TCHAR), _T("%S"), (azResult[ncolumn + 25]));
	}
	else{
		cps->UCCI_addInfo[0] = NULLCHAR;
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
		LogOut(_T("-------------不能打开设定数据库-------------\n"));
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
		TCHAR  info[128];
		swprintf_s(info,sizeof(info)/sizeof(TCHAR),L"%d) %S <%S>",id,azResult[k*ncolumn+0],azResult[k*ncolumn+2]);
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
	TCHAR    buf[512];

	if(rc = SqliteOpenDataBase(&db_ini,L3_DB_INI)){
		LogOut(_T("-------------不能打开设定数据库-------------\n"));
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
		swprintf_s(tmp->UCCI_name, 64 , _T("%S"), (azResult[(k)*ncolumn + 1]));
		//
		swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), _T("%d) %s"), tmp->yqID, tmp->UCCI_name);
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
	TCHAR buf[512];

	intGet = GetDlgItemInt(hDlg,IDC_Table,&isGet,TRUE);

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
		swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), _T("引擎 (1) 设置对话框, 使用引擎号: %d, 当前引擎号: %d"),
			pDis->first.yqID,	cps->yqID);

		//看一下编号是不是相同了
		if(pDis->first.yqID != cps->yqID){
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
	if(pDis->set_cps.yqID != pDis->first.yqID ){
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

	//3, 填充SMP线程数 列表框

	//4, 引擎名称
	SetDlgItemText(hDlg, IDC_YQ_NAME, cps->UCCI_name);

	//5, 引擎的使用棋库棋步数

	SendDlgItemMessage(hDlg,IDC_YQ_LIST_BOOK_NUM,CB_SETCURSEL,cps->UCCI_Book_Num,0);

	//6, 线程数
	SendDlgItemMessage(hDlg,IDC_YQ_SMP_LIST,CB_SETCURSEL,cps->UCCI_smpNum - 1,0);  //初始一个线程

	//引擎程序名
	SetDlgItemText(hDlg,IDC_YQ_PROGRAME,cps->UCCI_file);
	//引擎相对路径
	SetDlgItemText(hDlg, IDC_YQ_PATH, cps->UCCI_path);
	//初始指令
	SetDlgItemText(hDlg, IDC_initString, cps->UCCI_iniString);
	//其它指令
	SetDlgItemText(hDlg, IDC_YqOtherString, cps->UCCI_otherString);
	//开局库
	SendDlgItemMessage(hDlg,IDC_IsBook,BM_SETCHECK,cps->useBook,0);
	//残局库
	SendDlgItemMessage(hDlg,IDC_IsEGB, BM_SETCHECK,cps->isEGB,0);
	//hash表大小
	SetDlgItemInt(hDlg,IDC_HashSize,cps->UCCI_hashsize,false);
	//每步最多时间
	SetDlgItemInt(hDlg,IDC_TimePerStep,cps->timePerStep,false);
	//depth
	SetDlgItemInt(hDlg,IDC_SearchDepth,cps->timeSearchDepth,false);

	//包干计时
	SendDlgItemMessage(hDlg,IDC_IsBaoGan,		BM_SETCHECK, cps->IsBaoGan, 0);
	//是否分段计时 IDC_IsFenDuanTime
	SendDlgItemMessage(hDlg,IDC_IsFenDuanTime,	BM_SETCHECK,!cps->IsBaoGan, 0);

	//多少分钟每局 IDC_BanGanTime
	SetDlgItemInt(hDlg,IDC_BanGanTime,cps->BaoGanTime,false);
	//每走一步加时 TimeAddPerStep
	SetDlgItemInt(hDlg,IDC_TimeAddPerStep,cps->timePerStepAdd,false);
	//IDC_IsLostTimeUp ?
	SendDlgItemMessage(hDlg,IDC_IsLostTimeUp,BM_SETCHECK,cps->timeIsLost,0);

	//第一时间段步 IDC_firstClassStep
	SetDlgItemInt(hDlg,IDC_firstClassStep,cps->time_1_Step,false);
	//第一时间段时间 IDC_firstClassTime
	SetDlgItemInt(hDlg,IDC_firstClassTime,cps->time_1_Time,false);
	//第二时间段步
	SetDlgItemInt(hDlg,IDC_secondClassStep,cps->time_2_Step,false);
	//第二时间段时间 secondClassTime
	SetDlgItemInt(hDlg,IDC_secondClassTime,cps->time_2_Time,false);
}

//将对话框的信息转到CPS中
bool
SetDialogToCps(ChessProgramState *cps, HWND hDlg){

	BOOL isGet;
	int  intGet;

	//1,得到当前选择的引擎的编号
	int sel = (int)SendDlgItemMessage(hDlg,IDC_YQ_LIST,CB_GETCURSEL,0,0);
	TCHAR buf[MSG_SIZ];
	SendDlgItemMessage(hDlg,IDC_YQ_LIST,CB_GETLBTEXT,sel,(LPARAM)buf);

	cps->yqID  = _wtoi(buf);

	//得到选择协议编号
	sel = (int)SendDlgItemMessage(hDlg,IDC_YQUCCI,CB_GETCURSEL,0,0);
	SendDlgItemMessage(hDlg,IDC_YQUCCI,CB_GETLBTEXT,sel,(LPARAM)buf);

	cps->ucci = _wtoi(buf);

	//得到引擎的名称
	GetDlgItemText(hDlg,IDC_YQ_NAME,cps->UCCI_name,sizeof(cps->UCCI_name));

	//得到引擎当前的ＥＬＯ
	//intGet = GetDlgItemInt(hDlg,IDC_YQ_ELO,&isGet,TRUE);
	//if(!isGet){
	//	MessageBox(hDlg,"请设置正确的引擎得分(ELO)!","ＥＲＲＯＲ。。。",MB_OK);
	//	return false;
	//}

	sel = (int)SendDlgItemMessage(hDlg,IDC_YQ_LIST_BOOK_NUM,CB_GETCURSEL,0,0);

	cps->UCCI_Book_Num = sel;

	//线程数
	//intGet = GetDlgItemInt(hDlg,IDC_SMP_NUM,&isGet,TRUE);
	//if(!isGet){
	//	MessageBox(hDlg,"请设置正确的线程数!","ＥＲＲＯＲ。。。",MB_OK);
	//	return false;
	//}
	//cps->UCCI_smpNum = intGet;
	//if(cps->UCCI_smpNum < 0 || cps->UCCI_smpNum > 16){
	//	cps->UCCI_smpNum = 1;
	//}

	sel = (int)SendDlgItemMessage(hDlg,IDC_YQ_SMP_LIST,CB_GETCURSEL,0,0);

	cps->UCCI_smpNum = sel + 1;



	//是否使用开局库
	if(IsDlgButtonChecked(hDlg,IDC_IsBook) == BST_CHECKED){
		cps->useBook = TRUE;
	}
	else{
		cps->useBook = FALSE;
	}
	//是否使用残局库
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
	intGet = GetDlgItemInt(hDlg,IDC_HashSize,&isGet,TRUE);  //&cps->hashSize,    
	if(!isGet){
		MessageBox(hDlg, _T("请设置正确的HASH表大小!"), _T("ＥＲＲＯＲ。。。"), MB_OK);
		return false;
	}


	cps->UCCI_hashsize = intGet;
	if(cps->UCCI_hashsize < 16 || cps->UCCI_hashsize > 2048){
		MessageBox(hDlg, _T("请设置正确的HASH表大小!, （64M ~ 1024M）"), _T("ＥＲＲＯＲ。。。"), MB_OK);
		cps->UCCI_hashsize = 16;
	}
	/*
	int h = cps->UCCI_hashsize;
	if(h != 32 || h != 64 || h != 128 ||  */ 

	//每步时间
	intGet = GetDlgItemInt(hDlg,IDC_TimePerStep,&isGet,TRUE); //&cps->timePerStep,
	if(!isGet){
		MessageBox(hDlg, _T("请设置正确的每步搜索时间!"), _T("ＥＲＲＯＲ。。。"), MB_OK);
		return false;
	}
	cps->timePerStep = intGet;
	//搜索层数
	intGet = GetDlgItemInt(hDlg,IDC_SearchDepth,&isGet,TRUE);

	if(!isGet){
		MessageBox(hDlg, _T("请设置正确的每步搜索层数!"), _T("ＥＲＲＯＲ。。。"), MB_OK);
		return false;
	}
	cps->timeSearchDepth = intGet;

	if(cps->timeSearchDepth < 0 || cps->timeSearchDepth > 60){
		cps->timeSearchDepth = 0;
	}
	//计时设定
	if(IsDlgButtonChecked(hDlg,IDC_IsBaoGan) == BST_CHECKED){
		cps->IsBaoGan = 1;
	}
	else{
		cps->IsBaoGan  = 0;
	}

	//多少分钟／局
	intGet = GetDlgItemInt(hDlg,IDC_BanGanTime,&isGet,TRUE);
	if(!isGet){
		MessageBox(hDlg, _T("请设置正确的包干时间!"), _T("ＥＲＲＯＲ。。。"), MB_OK);
		return false;
	}
	cps->BaoGanTime = intGet;    
	if(cps->BaoGanTime == 0){
		cps->BaoGanTime = 1;
	}

	//每走一步加多少秒
	intGet = GetDlgItemInt(hDlg,IDC_TimeAddPerStep,&isGet,TRUE);
	if(!isGet){
		MessageBox(hDlg, _T("请设置正确的每步加时!"), _T("ＥＲＲＯＲ。。。"), MB_OK);
		return false;
	}
	cps->timePerStepAdd = intGet;

	//不是超时判负
	if(IsDlgButtonChecked(hDlg,IDC_IsLostTimeUp) == BST_CHECKED){
		cps->timeIsLost = 1;
	}
	else{
		cps->timeIsLost = 0;
	}
	//第一时间段步子
	intGet = GetDlgItemInt(hDlg,IDC_firstClassStep,&isGet,TRUE);
	if(!isGet){
		MessageBox(hDlg, _T("请设置正确的第一时间段要走的步数!"), _T("ＥＲＲＯＲ。。。"), MB_OK);
		return false;
	}
	cps->time_1_Step = intGet;
	if(cps->time_1_Step == 0){
		cps->time_1_Step = 30;
	}
	//第一时间段时间
	intGet = GetDlgItemInt(hDlg,IDC_firstClassTime,&isGet,TRUE);
	if(!isGet){
		MessageBox(hDlg, _T("请设置正确的第一时间段时间!"), _T("ＥＲＲＯＲ。。。"), MB_OK);
		return false;
	}
	cps->time_1_Time = intGet;
	if(cps->time_1_Time == 0){
		cps->time_1_Time = 1;
	}
	//第二时间段步子
	intGet = GetDlgItemInt(hDlg,IDC_secondClassStep,&isGet,TRUE);
	if(!isGet){
		MessageBox(hDlg, _T("请设置正确的第二时间段要走的步数!"), _T("ＥＲＲＯＲ。。。"), MB_OK);
		return false;
	}
	cps->time_2_Step = intGet;
	if(cps->time_2_Step == 0){
		cps->time_2_Step = 10;
	}
	intGet = GetDlgItemInt(hDlg,IDC_secondClassTime,&isGet,TRUE);
	if(!isGet){
		MessageBox(hDlg, _T("请设置正确的第二时间段时间!"), _T("ＥＲＲＯＲ。。。"), MB_OK);
		return false;
	}
	cps->time_2_Time = intGet;
	if(cps->time_2_Time == 0){
		cps->time_2_Time = 1;
	}

	cps->UCCI_addInfo[0] = NULLCHAR;
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
			"UPDATE yq SET yqName='%S',yqFile='%S',yqAuthor='%S',yqVerson='%S',yqDualTime=%d, \
			path='%S',xieyiID=%d,elo=%d,initString='%S',OtherString='%S',smpNum=%d,hashSize=%d,moveTime=%d,\
			depth=%d,isBaoGan=%d,BaoGanTime=%d,stepInc=%d,TimeUpLose=%d,FT_Step=%d,FT_Time=%d,SC_Step=%d,\
			SC_Time=%d,haveBook=%d,haveEGB=%d,yqOther='%S' WHERE yqID = %d",
			cps->UCCI_name,
			cps->UCCI_file,
			cps->UCCI_author,
			cps->UCCI_verson,
			cps->UCCI_dualtime,
			cps->UCCI_path,
			cps->ucci,
			cps->UCCI_Book_Num,
			cps->UCCI_iniString,
			cps->UCCI_otherString,
			cps->UCCI_smpNum,
			cps->UCCI_hashsize,
			cps->timePerStep,
			cps->timeSearchDepth,
			cps->IsBaoGan,
			cps->BaoGanTime,
			cps->timePerStepAdd,
			cps->timeIsLost,
			cps->time_1_Step,
			cps->time_1_Time,
			cps->time_2_Step,
			cps->time_2_Time,
			cps->useBook,
			cps->isEGB,
			cps->UCCI_addInfo,
			cps->yqID
			);

		rc = sqlite3_exec(db_ini,sql,0,0,&szErrMsg);
		if(rc != 0){
			LogOuts(szErrMsg);
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
			LogOuts(szErrMsg);
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
			VALUES('%S','%S','%S','%S','%d','%S','%d','%d','%S','%S',\
			'%d','%d','%d','%d','%d','%d','%d','%d','%d','%d',\
			'%d','%d','%d','%d','%S')",
			cps->UCCI_name,
			cps->UCCI_file,
			cps->UCCI_author,
			cps->UCCI_verson,
			cps->UCCI_dualtime,
			cps->UCCI_path,
			cps->ucci,
			cps->UCCI_Book_Num,
			cps->UCCI_iniString,
			cps->UCCI_otherString,
			cps->UCCI_smpNum,
			cps->UCCI_hashsize,
			cps->timePerStep,
			cps->timeSearchDepth,
			cps->IsBaoGan,
			cps->BaoGanTime,
			cps->timePerStepAdd,
			cps->timeIsLost,
			cps->time_1_Step,
			cps->time_1_Time,
			cps->time_2_Step,
			cps->time_2_Time,
			cps->useBook,
			cps->isEGB,
			cps->UCCI_addInfo
			);

		rc = sqlite3_exec(db_ini,sql,0,0,&szErrMsg);

		if(rc != 0){
			LogOuts(szErrMsg);
			sqlite3_free(szErrMsg);
		}

		// sprintf_s(sql,1024,"SELECT * FROM ucci");
		// SELECT relname, relpages FROM pg_class ORDER BY relpages DESC

		sprintf_s(sql,sizeof(sql),
			"SELECT yqID FROM yq ORDER BY yqID DESC");                        

		rc = sqlite3_get_table(db_ini,sql,&azResult,&nrow,&ncolumn,&szErrMsg);

		if(rc != 0){
			LogOuts(szErrMsg);
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

	EnableWindow(GetDlgItem(hDlg,IDC_BanGanTime),		 cps->IsBaoGan);
	EnableWindow(GetDlgItem(hDlg,IDC_firstClassStep),	!cps->IsBaoGan);
	EnableWindow(GetDlgItem(hDlg,IDC_firstClassTime),	!cps->IsBaoGan);
	EnableWindow(GetDlgItem(hDlg,IDC_secondClassStep),	!cps->IsBaoGan);
	EnableWindow(GetDlgItem(hDlg,IDC_secondClassTime),	!cps->IsBaoGan);

	//EnableWindow(GetDlgItem(hDlg,IDC_TimeAddPerStep),	!cps->isBaoGan);

	//EnableWindow(GetDlgItem(hDlg,IDC_IsLostTimeUp),		!cps->isBaoGan);

	SendDlgItemMessage(hDlg,IDC_IsBaoGan,BM_SETCHECK,		cps->IsBaoGan,0);
	SendDlgItemMessage(hDlg,IDC_IsFenDuanTime,BM_SETCHECK, !cps->IsBaoGan,0);

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
	TCHAR buf[MSG_SIZ];
	SendDlgItemMessage(hDlg,IDC_YQ_LIST,CB_GETLBTEXT,sel,(LPARAM)buf);                        
	int id  = _wtoi(buf);
	return id;
}

LRESULT CALLBACK
YqSetCallBack(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){


	OPENFILENAME  ofn;
	TCHAR buf[MSG_SIZ];
	TCHAR initDir[MAX_PATH];
	TCHAR title[MSG_SIZ];

	switch(message){
		case WM_INITDIALOG:{
			CenterWindow(hDlg,GetWindow(hDlg,GW_OWNER));	

			SendDlgItemMessage(hDlg,IDC_RADIO_YQA,BM_SETCHECK,1,0);
			SendDlgItemMessage(hDlg,IDC_RADIO_YQB,BM_SETCHECK,0,0);

			int  table = (int)lParam;

			SetDlgItemInt(hDlg,IDC_Table,table,FALSE);			//将桌号保存到对话框中

			dispboard_t *pDis = OBS[table];

			pDis->set_cps = pDis->first;							//显示第一个引擎

			//初始化开局使用棋步列表
			//1, 清空列表
			SendDlgItemMessage(hDlg,IDC_YQ_LIST_BOOK_NUM,CB_RESETCONTENT,0,0);
			
			for(int i = 0; i <= BOOK_MOVE_LEARN_PLY/2; i++){   //最大25回合
               //char buf[
				swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), _T("%d"), i);
				SendDlgItemMessage(hDlg,IDC_YQ_LIST_BOOK_NUM,CB_ADDSTRING,0,(LPARAM)buf);
			}
			//设置成缺省25回合
			SendDlgItemMessage(hDlg,IDC_YQ_LIST_BOOK_NUM,CB_SETCURSEL,BOOK_MOVE_LEARN_PLY/2,0);

			//初始化线程列表 IDC_YQ_SMP_LIST
			SendDlgItemMessage(hDlg,IDC_YQ_SMP_LIST,CB_RESETCONTENT,0,0);
			for(int i = 0; i < 16; i++){
				swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), _T("%d"), i + 1);
			   SendDlgItemMessage(hDlg,IDC_YQ_SMP_LIST,CB_ADDSTRING,0,(LPARAM)buf);
			}
			SendDlgItemMessage(hDlg,IDC_YQ_SMP_LIST,CB_SETCURSEL,0,0);  //初始一个线程

			YqInfoToSetDialog(&pDis->set_cps,hDlg);								//将引擎信息显示到对话框中

			SetTimeControlItemlEnables(hDlg,pDis);								//显示相应的设定时间			

			return TRUE;
						   }
		case WM_USER_YqLoad_OK:	{		//引擎加载成功了

			//PostMessage(cps->loadWin,WM_USER_YqLoad_OK,0,(LPARAM)cps);  //向引擎所在窗口发送初始化成功的信息

			int table;
			BOOL isGet;
			int  intGet;

			intGet = GetDlgItemInt(hDlg,IDC_Table,&isGet,TRUE);

			if(isGet){
				table = intGet;
			}
			else{
				table = 0;
			}
			dispboard_t *pDis = OBS[table];		//cps = pDis->cur_set_cps;

			ChessProgramState *loadokcps = (ChessProgramState*)lParam;

			//loadokcps->isInLoading		= FALSE;
			//loadokcps->isUpLoading      = FALSE;
			//loadokcps->UCCI_initDone	= TRUE;

			//loadokcps->playWhat         = NEUTRAL;

			loadokcps->cps_stat = Cps_Waiting;

			//将引擎的数据拷到相应的显示中去
			if(loadokcps->playWhat != NEUTRAL){
				GetTimeInfoFromCps(pDis, &pDis->TimeDisp[loadokcps->playWhat], loadokcps);
			}


			//更新引擎

			if(loadokcps->yqID == pDis->set_cps.yqID){
				SendToPlayerByColor(L"\n引擎加载成功了!!\n",ColorShout,TRUE);
				LogOut(loadokcps->UCCI_name);		
				LogOut(loadokcps->UCCI_path);

				//pDis->set_cps.isInLoading = FALSE;

				pDis->set_cps.cps_stat = Cps_Waiting;

				memcpy(pDis->set_cps.loadWhich, &pDis->set_cps, sizeof(ChessProgramState));
				YqInfoToSetDialog(&pDis->set_cps,hDlg);
				SetTimeControlItemlEnables(hDlg,pDis);

				//1, 得到CPS的控制参数
				//GetTimeSetInfoFromCps(loadokcps);				
				//2, 发送初始参数到CPS
				SendControlParameterToCps(loadokcps);
			}
			else{
				//
				SendToPlayerByColor(L"出错了，加载成功的引擎不是当前设定的引擎!!\n",ColorShout,FALSE);
			}

								}
								break;
		case WM_USER_YqUpload_OK:			//引擎已卸载成功了
			{
				ChessProgramState *uploadokcps = (ChessProgramState*)lParam;

				LogOut(_T("\n以下引擎\n<"));
				LogOut(uploadokcps->UCCI_name);
				LogOut(_T("\n已卸载成功"));

				if(uploadokcps->loadWhich != NULL){
					LogOut(_T("\n正在加载引擎："));
					LogOut(uploadokcps->loadWhich->UCCI_name);
					LogOut(_T("\n可能要一些时间，请稍候....\n"));

					StartChessProgram(uploadokcps->loadWhich);
				}
			}
			break;
			//--------------------------------------------------------------                 
		case WM_COMMAND:{	//有按钮信息  			

			int table;
			BOOL isGet;
			int  intGet;

			intGet = GetDlgItemInt(hDlg,IDC_Table,&isGet,TRUE);

			if(isGet){
				table = intGet;
			}
			else{
				table = 0;
			}
			dispboard_t *pDis = OBS[table];		//cps = pDis->cur_set_cps;



			switch(LOWORD(wParam)){
				//		                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
		case IDC_YQ_ADD:{                   //添加引擎按钮
			ZeroMemory(&ofn,sizeof(ofn));
			ofn.lStructSize         = sizeof(OPENFILENAME);
			ofn.lpstrFilter         = _T("象棋引擎\0*.exe\0");
			ofn.nMaxCustFilter      = MSG_SIZ;
			ofn.nFilterIndex        = 1;
			ofn.hInstance           = hInst;
			ofn.nMaxFile            = MAX_PATH;
			ofn.hwndOwner           = hDlg;
			buf[0]                  = 0;
			ofn.lpstrFile           = buf;
			StringCbPrintf(title,sizeof(title),
				_T("请选择一个象棋引擎 (引擎应放在主程序目录下的plugins目录下!)"));
			ofn.lpstrTitle          = title;
			StringCbPrintf(initDir,sizeof(initDir),
				_T("%s%s"), installDir, L"plugins\\");
			ofn.lpstrInitialDir		= initDir;			//初始化目录
			ofn.Flags               = OFN_EXPLORER+OFN_FILEMUSTEXIST+OFN_PATHMUSTEXIST+OFN_HIDEREADONLY;
			if(GetOpenFileName(&ofn)){
				//先判断一下，是不是在installDir以下
				_wcslwr_s(initDir, sizeof(initDir)/sizeof(TCHAR));
				_wcslwr_s(buf, sizeof(buf)/sizeof(TCHAR));
				if(wcsstr(buf,initDir) == NULL){
					StringCbPrintf(buf, MSG_SIZ, _T("请将象棋引擎放到 %s目录下！"), initDir);
					MessageBox(hDlg, buf, _T("ERROR..."), MB_OK);
					return TRUE;
				}

				//得到了一个引擎文件

				//1,得到程序的名称
				ChessProgramState tmp[1];

				memcpy(tmp,&pDis->set_cps,sizeof(ChessProgramState));

				StringCbPrintf(tmp->UCCI_file,sizeof(tmp->UCCI_file),buf+ofn.nFileOffset);
				StringCbPrintf(tmp->UCCI_name,sizeof(tmp->UCCI_file),buf+ofn.nFileOffset);

				//2,得到引擎的目录
				TCHAR *p1 = wcsstr(buf,_T("plugins\\"));
				TCHAR *p2 = wcsstr(buf, tmp->UCCI_file);

				StringCbPrintf(tmp->UCCI_path,(p2-p1+1)*sizeof(TCHAR),p1);

				LogOut(_T("象棋引擎：<<"));
				LogOut(tmp->UCCI_name);

				int id = pDis->set_cps.yqID;

				if(InsertCpsInfoToSqlite(tmp, &id) == 0){       //将信息保存到数据库中                            
					//LogOut(">>已成功保存! 请更改相应的设置\n");
					SendToPlayerByColor(L">>已成功保存! 请更改相应的设置\n",ColorShout,FALSE);

					//得到当前的ID信息
					GetYqinfoFromSqliteByID(tmp, id);

					FillYqListToSetDialog(tmp,hDlg);	 //还是将原先使用的显示一下

					pDis->set_cps.yqID = id;			 //更新当前的ID

					YqInfoToSetDialog(&pDis->set_cps,hDlg);
				}
				else{
					//LogOut(">>保存失败!\n");
					SendToPlayerByColor(L">>保存失败!\n",ColorShout,FALSE);
				}
			}  
						}
						break;
						//
		case IDC_IsBaoGan:{                  //包干计时按钮
			pDis->set_cps.IsBaoGan   = TRUE;
			SetTimeControlItemlEnables(hDlg,pDis);
						  }
						  break;    
						  //
		case IDC_IsFenDuanTime:  {           //分段计时按钮
			pDis->set_cps.IsBaoGan    = FALSE;
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
		//case IDC_RADIO_YQB:  {               //引擎(2)按钮
		//	if(IsDlgButtonChecked(hDlg,IDC_RADIO_YQB) == BST_CHECKED){

		//		SendDlgItemMessage(hDlg,IDC_RADIO_YQA,BM_SETCHECK,0,0);

		//		pDis->set_cps = pDis->second;

		//		GetYqinfoFromSqliteByID(&pDis->set_cps,pDis->set_cps.yqID);

		//		YqInfoToSetDialog(&pDis->set_cps,hDlg);

		//		SetTimeControlItemlEnables(hDlg,pDis);
		//	}           
		//					 }
		//					 break;
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
				if(MessageBox(hDlg,_T("请确认,本操作将删除这个引擎的!"),_T("注意了!"),MB_OKCANCEL) == IDOK){
					int id  = GetSelectYqID(hDlg);

					if(DeleteCpsByYqID(id) == SQLITE_OK){
						SendToPlayerByColor(L"\n您已成功删除了一个引擎\n",ColorShout,FALSE);

						//将当前的引擎设定为使用的引擎
						if(IsDlgButtonChecked(hDlg,IDC_RADIO_YQA) == BST_CHECKED){	//是引擎Ａ按下了
							pDis->set_cps = pDis->first;
						}
						//else{
						//	pDis->set_cps = pDis->second;
						//}
						YqInfoToSetDialog(&pDis->set_cps,hDlg);
						SetTimeControlItemlEnables(hDlg,pDis);
					}
					else{
						SendToPlayerByColor(L"\n您无法删除这个引擎\n",ColorShout,FALSE);
					}
				}
			}
			break;
			//
		case ID_LOAD_SET_YQ: {            //加载一个引擎

			//if(TRUE == pDis->set_cps.isInLoading){		//当前正在加载引擎

			if(pDis->set_cps.cps_stat == Cps_InLoading){
				SendToPlayerByColor(L"\n当前正在加载引擎之中\n",ColorShout,FALSE);
				break;
			}

			BOOL can = TRUE;
			ChessProgramState *precps = NULL;
			if(IsDlgButtonChecked(hDlg,IDC_RADIO_YQA) == BST_CHECKED){
				if(pDis->set_cps.yqID == pDis->first.yqID){		//
					can = FALSE;							
				}
				precps = &pDis->first;
			}
			//else{
			//	if(pDis->set_cps.yqID == pDis->second.yqID){		//
			//		can = FALSE;							
			//	}
			//	precps = &pDis->second;
			//}
			if(can == FALSE){
				MessageBox(hDlg, _T("你已加载了当前的引擎，不要再加载了"), _T("Error"), MB_OK);
				EnableWindow(GetDlgItem(hDlg,ID_LOAD_SET_YQ),FALSE);
				break;
			}

			LoadChessProgramState(precps, &pDis->set_cps, hDlg);					

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

						SetDialogToCps(&pDis->first,hDlg);

						SendControlParameterToCps(&pDis->first);
					}
					//if(pDis->set_cps.yqID == pDis->second.yqID){								

					//	SetDialogToCps(&pDis->second,hDlg);
					//	SendControlParameterToCps(&pDis->second);
					//}

					ResetClocks(pDis);

					//GetTimeInfoFromCps(pDis, &pDis->TimeDisp[WHITE], &pDis->first);
					//GetTimeInfoFromCps(pDis, &pDis->TimeDisp[BLACK], &pDis->second);

					//if(pDis->first.playWhat != NEUTRAL){
					//	GetTimeInfoFromCps(pDis, &pDis->TimeDisp[pDis->first.playWhat], &pDis->first);
					//}

					//if(pDis->second.playWhat != NEUTRAL){
					//	GetTimeInfoFromCps(pDis, &pDis->TimeDisp[pDis->second.playWhat], &pDis->second);
					//}

					LogOut(_T("\n更新当前引擎设置成功！\n"));
				}
				else{
					SendToPlayerByColor(_T("\n您无法更新当前的引擎参数\n"), ColorShout, FALSE);
				}						
			}
			break;
		case IDOK:                          //确认按钮

			{
				//1, 看是不是更换了引擎,如果是更换了，则要停止当前的，尝试加载现在的，

				//if(pDis->set_cps.isInLoading == TRUE){		//正在加载当前的引擎
				if(pDis->set_cps.cps_stat == Cps_InLoading){
					SendToPlayerByColor(L"\n正在加载当前引擎，请稍候。。。\n",ColorShout,FALSE);
					break;
				}						

				if(pDis->first.cps_stat == Cps_NotLoad){
					SendToPlayerByColor(L"\n第一引擎还没加载成功，请重新加载或更换引擎试一下\n",ColorShout,FALSE);
					//break;
				}
				//if(pDis->second.cps_stat == Cps_NotLoad){
				//	SendToPlayerByColor(L"\n第二引擎还没加载成功，请重新加载或更换引擎试一下\n",ColorShout,FALSE);
				//	//break;
				//}



				//更新一下设置
				ChessProgramState tmp[1];						
				SetDialogToCps(tmp,hDlg);

				if(UpdateCpsInfoToSqlite(tmp) != SQLITE_OK){
					SendToPlayerByColor(L"\n您无法更新当前的引擎参数\n",ColorShout,FALSE);
					break;
				}
				else{
					//还要看一下是不是当前使用的引擎设置
					if(pDis->set_cps.yqID == pDis->first.yqID){											

						SetDialogToCps(&pDis->first,hDlg);
						SendControlParameterToCps(&pDis->first);
					}
					//if(pDis->set_cps.yqID == pDis->second.yqID){								

					//	SetDialogToCps(&pDis->second,hDlg);
					//	SendControlParameterToCps(&pDis->second);
					//}

					ResetClocks(pDis);

					//GetTimeInfoFromCps(pDis, &pDis->TimeDisp[WHITE], &pDis->first);
					//GetTimeInfoFromCps(pDis, &pDis->TimeDisp[BLACK], &pDis->second);

					//if(pDis->first.playWhat != NEUTRAL){
					//	GetTimeInfoFromCps(pDis, &pDis->TimeDisp[pDis->first.playWhat], &pDis->first);
					//}

					//if(pDis->second.playWhat != NEUTRAL){
					//	GetTimeInfoFromCps(pDis, &pDis->TimeDisp[pDis->second.playWhat], &pDis->second);
					//}

					//SendToPlayerByColor("\n更新当前引擎设置成功！\n",ColorShout,FALSE);
					LogOut(_T("\n更新当前引擎设置成功！\n"));
				}						

				DisplayBothClocks(pDis);

				EndDialog(hDlg, TRUE);
				return TRUE;
			} 
			break;
		case IDCANCEL:

			//if(pDis->first.UCCI_initDone == FALSE){
			//	SendToPlayerByColor("\n第一引擎还没加载成功，请重新加载或更换引擎试一下\n",ColorShout,FALSE);
			//	break;
			//}
			//else if(pDis->second.UCCI_initDone == FALSE){
			//	SendToPlayerByColor("\n第二引擎还没加载成功，请重新加载或更换引擎试一下\n",ColorShout,FALSE);
			//	break;
			//}

			DisplayBothClocks(pDis);
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
