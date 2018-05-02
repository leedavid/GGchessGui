#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"



int 
GetCountInfoByUserId(ChessProgramState *cps,int id){
    int rc = -1;
    sqlite3 *db_ini;
    char *szErrMsg          = 0;
    int  nrow               = 0;
    int  ncolumn            = 0;
    char **azResult;
    char sql[1024];

    if(rc = SqliteOpenDataBase(&db_ini,L3_DB_INI)){
        //LogOut(
        return rc;
    }
    sprintf_s(sql,sizeof(sql),"SELECT * FROM ics_count WHERE ics_ID = %d",id);

    rc = sqlite3_get_table(db_ini,sql,&azResult,&nrow,&ncolumn,&szErrMsg);

    if(rc != SQLITE_OK){
        return rc;
    }

    if(nrow == 0){
		sprintf_s(sql, sizeof(sql), "SELECT * FROM ics_count ");

		rc = sqlite3_get_table(db_ini, sql, &azResult, &nrow, &ncolumn, &szErrMsg);

		if (rc != SQLITE_OK){
			return rc;
		}
    }

	if (nrow != 0){
		cps->ICS_id = atoi(azResult[ncolumn + 0]);
		cps->ICS_net_id = atoi(azResult[ncolumn + 1]);
		swprintf_s(cps->ICS_user, sizeof(cps->ICS_user) / sizeof(TCHAR), _T("%S"), (azResult[ncolumn + 2]));
		swprintf_s(cps->ICS_pass, sizeof(cps->ICS_pass) / sizeof(TCHAR), _T("%S"), (azResult[ncolumn + 3]));
		//sprintf_s(cps->ICS_language,si
		//cps->ICS_language   = atoi(azResult[ncolumn+4]);
		swprintf_s(cps->ICS_info, sizeof(cps->ICS_info) / sizeof(TCHAR), _T("%S"), (azResult[ncolumn + 4]));
	}

    sqlite3_free_table(azResult);

    rc = sqlite3_close(db_ini);

    GetNetInfoByNetId(cps,cps->ICS_net_id);

    return rc;
}

int 
GetNetInfoByNetId(ChessProgramState *cps,int id){
    sqlite3 *db_ini;
    char    *szErrMsg       = 0;
    int      nrow           = 0;
    int      ncolumn        = 0;
    int      rc             = 0;
    char    **azResult;
    char     sql[1024];
    if(rc = SqliteOpenDataBase(&db_ini,L3_DB_INI)){
        return rc;
    }
	setlocale(LC_CTYPE, "chs");
    sprintf_s(sql,sizeof(sql),"SELECT * FROM ics_net WHERE net_id = %d",id);

    rc = sqlite3_get_table(db_ini,sql,&azResult,&nrow,&ncolumn,&szErrMsg);

    if(rc != SQLITE_OK){
        return rc;
    }

    if(nrow != 1){
        return -1;
    }

	swprintf_s(cps->ICS_net_type, sizeof(cps->ICS_net_type) / sizeof(TCHAR), _T("%S"), (azResult[1 * ncolumn + 4]));
	swprintf_s(cps->ICS_net_host, sizeof(cps->ICS_net_host) / sizeof(TCHAR), _T("%S"), (azResult[1 * ncolumn + 2]));
    cps->ICS_net_port   = atoi(azResult[1*ncolumn+3]);
	swprintf_s(cps->ICS_net_info, sizeof(cps->ICS_net_info) / sizeof(TCHAR), _T("%S"), (azResult[1 * ncolumn + 5]));

    sqlite3_free_table(azResult);

    rc = sqlite3_close(db_ini);

    return rc;

}

int FillIcsTypeToDlgById(HWND hDlg,int type_id){
    sqlite3 *db_ini;
    char    *szErrMsg       = 0;
    int      nrow           = 0;
    int      ncolumn        = 0;
    int      rc             = 0;
    char    **azResult;
    char     sql[1024];
    //char    buf[512];

    if(rc = SqliteOpenDataBase(&db_ini,L3_DB_INI)){
        return rc;
    }

    sprintf_s(sql,sizeof(sql),"SELECT * FROM ics_net WHERE net_id = %d",type_id);

    rc = sqlite3_get_table(db_ini,sql,&azResult,&nrow,&ncolumn,&szErrMsg);

    if(rc != SQLITE_OK){
        return rc;
    }

    if(nrow != 1){
        return -1;
    }

    //填充网站信息
    SetDlgItemInt(hDlg,IDC_ICS_NET_ID,type_id,false);
	SetDlgItemText(hDlg, IDC_ICS_NET_TYPE, CA2W(azResult[1 * ncolumn + 4]));
	SetDlgItemText(hDlg, IDC_ICS_NET_HOST, CA2W(azResult[1 * ncolumn + 2]));
    SetDlgItemInt(hDlg,IDC_ICS_NET_PORT,atoi(azResult[1*ncolumn+3]),false);
	SetDlgItemText(hDlg, IDC_ICS_NET_INFO, CA2W(azResult[1 * ncolumn + 5]));

    sqlite3_free_table(azResult);

    rc = sqlite3_close(db_ini);

    return rc;
}

int 
FillIcsCountTypeList(HWND hDlg, ChessProgramState *cps){ //IDC_NETTYPE_LIST
    sqlite3 *db_ini;
    char    *szErrMsg       = 0;
    int      nrow           = 0;
    int      ncolumn        = 0;
    int      rc             = 0;
    char    **azResult;
    char     sql[1024];
    TCHAR    buf[512];

    if(rc = SqliteOpenDataBase(&db_ini,L3_DB_INI)){
        return rc;
    }
	setlocale(LC_CTYPE, "chs");
    sprintf_s(sql,sizeof(sql),"%s","SELECT * FROM ics_net");

    rc = sqlite3_get_table(db_ini,sql,&azResult,&nrow,&ncolumn,&szErrMsg);

    if(rc != SQLITE_OK){
        return rc;
    }
    //清空
    SendDlgItemMessage(hDlg,IDC_NETTYPE_LIST,CB_RESETCONTENT,0,0);

    int nowID = -1;
    int k;
    for(k = 1; k<=nrow; k++){
        
        int tid = atoi(azResult[k*ncolumn + 1]);
        
        if(tid == cps->ICS_net_id){
            nowID = k;    
			swprintf_s(cps->ICS_net_name, sizeof(cps->ICS_net_name) / sizeof(TCHAR), _T("%S"), (azResult[(k)*ncolumn + 0]));
			swprintf_s(cps->ICS_net_host, sizeof(cps->ICS_net_host) / sizeof(TCHAR), _T("%S"), (azResult[(k)*ncolumn + 2]));
            cps->ICS_net_port = atoi(azResult[k*ncolumn + 3]);
			swprintf_s(cps->ICS_net_type, sizeof(cps->ICS_net_type) / sizeof(TCHAR), _T("%S"), (azResult[(k)*ncolumn + 4]));
			swprintf_s(cps->ICS_net_info, sizeof(cps->ICS_net_info) / sizeof(TCHAR), _T("%S"), (azResult[(k)*ncolumn + 5]));

            //设置编号
            SetDlgItemInt(hDlg,IDC_ICS_NET_ID,cps->ICS_net_id,false);
            //
			SetDlgItemText(hDlg, IDC_ICS_NET_TYPE, cps->ICS_net_type);
            //
			SetDlgItemText(hDlg, IDC_ICS_NET_HOST, cps->ICS_net_host);
            //
            SetDlgItemInt(hDlg,IDC_ICS_NET_PORT,cps->ICS_net_port,false);
            //
			SetDlgItemText(hDlg, IDC_ICS_NET_INFO, cps->ICS_net_info); 
        }
		swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), L"%d) %S", tid, (azResult[(k)*ncolumn + 0]));

        //列表
        SendDlgItemMessage(hDlg,IDC_NETTYPE_LIST,CB_ADDSTRING,0,(LPARAM)buf);

    }

    sqlite3_free_table(azResult);

    rc = sqlite3_close(db_ini);

    //将当前选择的项设为当前
    SendDlgItemMessage(hDlg,IDC_NETTYPE_LIST,CB_SETCURSEL,nowID-1,0);

    return rc;

}

int    //列出所有的帐号，并绑定当前的ＩＤ
FillIcsCountSetNetList(HWND hDlg,ChessProgramState *cps){ //IDC_ICS_COUNT_LIST
    sqlite3 *db_ini;
    char    *szErrMsg       = 0;
    int      nrow           = 0;
    int      ncolumn        = 0;
    int      rc             = 0;
    char    **azResult;
    char     sql[1024];
    TCHAR    buf[512];

    rc = SqliteOpenDataBase(&db_ini,L3_DB_INI);
	if (rc != SQLITE_OK){
		return rc;
	}
	setlocale(LC_CTYPE, "chs");

    sprintf_s(sql,sizeof(sql),"%s","SELECT * FROM ics_count");

    rc = sqlite3_get_table(db_ini,sql,&azResult,&nrow,&ncolumn,&szErrMsg);

    if(rc != SQLITE_OK){
        return rc;
    }

    //清空帐号列表
    SendDlgItemMessage(hDlg,IDC_ICS_COUNT_LIST,CB_RESETCONTENT,0,0);

    int nowID = -1;
    int k;

    for(k = 1; k <= nrow; k++){     //对于每一个帐号
        //得到ＩＤ
        int tid = atoi(azResult[k*ncolumn + 0]);

        if(cps->ICS_id == tid){
            nowID = k;
        }

        //得到ＩＣＳ＿ＮＡＭＥ
		swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), L"%d) %S", tid, (azResult[(k)*ncolumn + 2]));

        //列表
        SendDlgItemMessage(hDlg,IDC_ICS_COUNT_LIST,CB_ADDSTRING,0,(LPARAM)buf);

    }
    //释放为记录集分配的内存，如果返回了空记录集并不会发生错误
    sqlite3_free_table(azResult);

    rc = sqlite3_close(db_ini);

    if(nowID == -1){
    }

    //将当前选择的项设为当前
    SendDlgItemMessage(hDlg,IDC_ICS_COUNT_LIST,CB_SETCURSEL,nowID-1,0);

    FillIcsCountTypeList(hDlg,cps);

    return rc;
}


//连线帐号设置
void 
ICS_yqinfoToDlg(HWND hDlg,ChessProgramState *cps){
    //
    //用户帐号：
    SetDlgItemInt(hDlg,IDC_ICS_COUNT_NO,cps->ICS_id,false);
    //用户名
	SetDlgItemText(hDlg, IDC_ICS_USER, cps->ICS_user);
    //用户口令
	SetDlgItemText(hDlg, IDC_ICS_PASSWORD, cps->ICS_pass);
    //帐号说明
	SetDlgItemText(hDlg, IDC_ICS_COUNT_INFO, cps->ICS_info);

    //使用语言
    //SendDlgItemMessage(hDlg,IDC_ICS_CHN,BM_SETCHECK, cps->ICS_language, 0);
    //SendDlgItemMessage(hDlg,IDC_ICS_ENG,BM_SETCHECK,!cps->ICS_language, 0);

    FillIcsCountSetNetList(hDlg,cps);
}
//得到list的选择id
int 
GetSelectIcsCoutdId(HWND hDlg){
    int sel = (int)SendDlgItemMessage(hDlg,IDC_ICS_COUNT_LIST,CB_GETCURSEL,0,0);
    TCHAR buf[512];
    SendDlgItemMessage(hDlg,IDC_ICS_COUNT_LIST,CB_GETLBTEXT,sel,(LPARAM)buf);
    int id = _wtoi(buf);
    return id;
}

//IDC_NETTYPE_LIST

int 
GetSelectNetTypeId(HWND hDlg){
    int sel = (int)SendDlgItemMessage(hDlg,IDC_NETTYPE_LIST,CB_GETCURSEL,0,0);
	TCHAR buf[512];
    SendDlgItemMessage(hDlg,IDC_NETTYPE_LIST,CB_GETLBTEXT,sel,(LPARAM)buf);
    int id = _wtoi(buf);
    return id;
}

int 
DeleteAIcsCount(HWND hDlg, ChessProgramState *cps){
    int rc = -1;

    int cid = GetSelectIcsCoutdId(hDlg);

    if(cid == cps->ICS_id){
		LogOut(_T("你不能删除当前的帐号，可能帐号正在使用中\n"));
        return rc;
    }

    sqlite3 *db_ini;
    char *szErrMsg = 0;
    char sql[4096];
    
    rc = SqliteOpenDataBase(&db_ini,L3_DB_INI);
    if(rc){
        return rc;
    }

    sprintf_s(sql,sizeof(sql),
        "DELETE FROM ics_count WHERE ics_ID = %d",cid);

    rc = sqlite3_exec(db_ini,sql,0,0,&szErrMsg);

    if(rc != 0){
        LogOuts(szErrMsg);
        sqlite3_free(szErrMsg);
    }
    sqlite3_close(db_ini);

    //现将当前的显示出来

    return rc;
}




int     //插入一个连线帐号
InsertAIcsCount(HWND hDlg, ChessProgramState *cps){
    sqlite3 *db_ini;
    char    *szErrMsg       = 0;
    int      rc             = -1;
    char     sql[4096];
    
    rc = SqliteOpenDataBase(&db_ini,L3_DB_INI);
    if(rc != SQLITE_OK){
        return rc;
    }
	setlocale(LC_CTYPE, "chs");
    sprintf_s(sql,sizeof(sql),
        "INSERT INTO ics_count (ics_net_id,ics_user,ics_pass,ics_info) \
				        VALUES ('%d','%S','%S','%S')", cps->ICS_net_id, cps->ICS_user, cps->ICS_pass, cps->ICS_info);

    rc = sqlite3_exec(db_ini,sql,0,0,&szErrMsg);
    if(rc != SQLITE_OK){
		LogOuts(szErrMsg);
        sqlite3_free(szErrMsg);
    }
    else{
        LogOut(_T("插入一个连线帐号成功！\n"));
    }

    sqlite3_close(db_ini);

    return rc;


}
int 
UpDateCpsToIcsCount(HWND hDlg,ChessProgramState *cps){
    int         rc          = -1;
    sqlite3     *db_ini;
    char        *szErrMsg   = 0;
    char        sql[4096];

	//char user[128];
	//char pass[128];
	//char info[128];

	//UnicodeToAnsi(cps->ICS_user, user);

    rc = SqliteOpenDataBase(&db_ini,L3_DB_INI);
    if(rc != SQLITE_OK){
        return rc;
    }
	setlocale(LC_CTYPE, "chs");
    sprintf_s(sql,sizeof(sql),
        "UPDATE ics_count SET ics_net_id = %d, ics_user = '%S',ics_pass='%S',\
        ics_info='%S' WHERE ics_ID = %d",
		cps->ICS_net_id, cps->ICS_user, cps->ICS_pass, cps->ICS_info, cps->ICS_id);

    rc = sqlite3_exec(db_ini,sql,0,0,&szErrMsg);
    if(rc != 0){
		LogOuts(szErrMsg);
        sqlite3_free(szErrMsg);        
    }

    sqlite3_close(db_ini);
    return rc;
}

bool //将对话框架的信息输入到CPS中
DlgInfoToIcsCps(HWND hDlg,ChessProgramState *cps){
    BOOL isGet;
    int  intGet;

    //得到网站类型的编号

    intGet = GetDlgItemInt(hDlg,IDC_ICS_NET_ID,&isGet,TRUE);
    if(!isGet){
		MessageBox(hDlg, _T("请设置正确的网站帐号编号"), _T("ＥＲＲＯＲ。。。"), MB_OK);
       return false;
    }
    cps->ICS_net_id = intGet;

    //得到网站的类型
    GetDlgItemText(hDlg,IDC_ICS_NET_TYPE,cps->ICS_net_type,sizeof(cps->ICS_net_type));

    //得到host
    GetDlgItemText(hDlg,IDC_ICS_NET_HOST,cps->ICS_net_host,sizeof(cps->ICS_net_host));

    //得到port

    intGet = GetDlgItemInt(hDlg,IDC_ICS_NET_PORT,&isGet,TRUE);
    if(!isGet){
		MessageBox(hDlg, _T("请设置正确的网站端口"), _T("ＥＲＲＯＲ。。。"), MB_OK);
       return false;
    }
    cps->ICS_net_port = intGet;

    //得到ＮＥＴ的说明

    GetDlgItemText(hDlg,IDC_ICS_NET_INFO,(TCHAR*)cps->ICS_net_info,sizeof(cps->ICS_net_info));

    //得到用户的帐号编号
    intGet = GetDlgItemInt(hDlg,IDC_ICS_COUNT_NO,&isGet,TRUE);
    if(!isGet){
		MessageBox(hDlg, _T("请设置正确的帐号编号"), _T("ＥＲＲＯＲ。。。"), MB_OK);
       return false;
    }
    cps->ICS_id = intGet;

    //得到user name
    GetDlgItemText(hDlg,IDC_ICS_USER,cps->ICS_user,sizeof(cps->ICS_user));
    //得到password
    GetDlgItemText(hDlg,IDC_ICS_PASSWORD,cps->ICS_pass,sizeof(cps->ICS_pass));

    //得到是中文还是英文
    //if(IsDlgButtonChecked(hDlg,IDC_ICS_CHN) == BST_CHECKED){
    //    cps->ICS_language = 1;
    //}
    //else{
    //    cps->ICS_language = 0;
    //}

    //得到帐号简介
    GetDlgItemText(hDlg,IDC_ICS_COUNT_INFO,cps->ICS_info,sizeof(cps->ICS_info));
    
    return true;
}

LRESULT CALLBACK				// Message handler for about box.
IcsCountSetCallBack(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static ChessProgramState *cps  = NULL;

    UNREFERENCED_PARAMETER(lParam);
	//switch (message)
	//{
	//case WM_INITDIALOG:
	//	return (INT_PTR)TRUE;

	//case WM_COMMAND:
	//	if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
	//	{
	//		EndDialog(hDlg, LOWORD(wParam));
	//		return (INT_PTR)TRUE;
	//	}
	//	break;
	//}

    switch(message){
        case WM_INITDIALOG:
            CenterWindow(hDlg,GetWindow(hDlg,GW_OWNER));
            cps = &appData.ACPSics;//&DIS.third;
            GetCountInfoByUserId(cps,cps->ICS_id);
            ICS_yqinfoToDlg(hDlg,cps);
            //pre_first_id   = DIS.first.yqID;
            //pre_second_id  = DIS.second.yqID;

            //cps = &DIS.first;
            //GetYqinfoFromSqliteByID(cps,cps->yqID);
            //YqInfoToSetDialog(cps,hDlg);
            //SetTimeControlItemlEnables(hDlg,cps);

            return TRUE;           
        case WM_COMMAND:{
            switch(LOWORD(wParam)){
                case IDC_ICS_COUNT_LIST:        //更新的帐号
                    if(HIWORD(wParam) == CBN_SELCHANGE){
                        ChessProgramState tmp[1];
                        tmp->ICS_id = GetSelectIcsCoutdId(hDlg);                        
                        GetCountInfoByUserId(tmp,tmp->ICS_id);
                        ICS_yqinfoToDlg(hDlg,tmp);
                    }
                    break;
                case IDC_NETTYPE_LIST:
                    if(HIWORD(wParam) == CBN_SELCHANGE){
                        int ICS_type_id = GetSelectNetTypeId(hDlg);
                        FillIcsTypeToDlgById(hDlg,ICS_type_id);
                    }
                    break;
                case ID_Count_Add:              //加入一个帐号
                    {
                        ChessProgramState tmp[1];
                        if(DlgInfoToIcsCps(hDlg,tmp)==true){      //从对话框到cps
                            InsertAIcsCount(hDlg,tmp);
                            GetCountInfoByUserId(cps,cps->ICS_id);
                            ICS_yqinfoToDlg(hDlg,cps);
                        }
                    }
                    break;
                case ID_Count_Del:              //删除一个帐号
                    DeleteAIcsCount(hDlg,cps);
                    //再将当前的显示出来
                    GetCountInfoByUserId(cps,cps->ICS_id);
                    ICS_yqinfoToDlg(hDlg,cps);
                    break;
                case IDOK:
                    //保存或更新
                    if(DlgInfoToIcsCps(hDlg,cps)){
                        if(UpDateCpsToIcsCount(hDlg,cps) == 0){ //更新一下帐号到数据库
							LogOut(_T("更新连线帐号成功！\n"));
                        }
                        else{
							LogOut(_T("更新连线帐号失败！\n"));
                        }
                    }
                    EndDialog(hDlg, TRUE);
                    return TRUE;
                    break;
                case IDCANCEL:
                    EndDialog(hDlg, FALSE);
                    return TRUE;
                    break;
                default:
                    break;
            }
                        }
        default:
            break;
    } 

	return (INT_PTR)FALSE;
}

void 
IcsCountSetPopup(void){ //打开帐号设置按钮

	dispboard_t *pDis = OBS[0];

    FARPROC lpProc = MakeProcInstance((FARPROC)IcsCountSetCallBack, hInst);
    DialogBox(hInst, MAKEINTRESOURCE(DLG_ICS_Count), pDis->hwndThis, (DLGPROC) lpProc);
    FreeProcInstance(lpProc);
}