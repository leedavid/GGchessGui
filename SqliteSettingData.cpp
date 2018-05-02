#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"


/////////////////////////////////////////////////////////
// 从设定数据库中得到当前的数据
int GetSetingInfoFromSqlite(void){

    // 1, 打开数据库
    sqlite3 *db_ini;
    char *szErrMsg  = 0;
    int  nrow       = 0;
    int  ncolumn    = 0;    //查询语句返回的结果集的行数，列数
    int  rc         = 0;
    char **azResult;        //用于保存查询结果集数据
    char buf[1024];
    ArgDescriptor   *ad;
	setlocale(LC_CTYPE, "chs");
    if( rc = SqliteOpenDataBase(&db_ini,L3_DB_INI)){
        LogOut(_T("-------------不能打开设定数据库-------------\n")); 
        return rc;      //打开有错,不能保存
    }

    // sqlite3_get_table函数可以返回SQL语句执行之后的记录集，以及行列数

    sprintf_s(buf,1024,"SELECT * FROM tab_ini WHERE IsSave != 0"); // 

    rc = sqlite3_get_table(db_ini,buf,&azResult,&nrow,&ncolumn,&szErrMsg);

    if(rc != SQLITE_OK){
       LogOuts(szErrMsg);
       LogOut(_T("-------------找不到任何设定选项-------------\n")); 
       sqlite3_free(szErrMsg);
       return rc;
    }
    TCHAR argName[1024];
	TCHAR argData[1024];
    for(int k = 0; k< nrow; k++){
        //得到名称:
        // i+1 skips over the first recored which is the column headers
		swprintf_s(argName, sizeof(argName) / sizeof(TCHAR), _T("%S"), (azResult[(k + 1)*ncolumn]));

        for(ad = argDescriptors; ad->argName != NULL; ad++){
            if(wcscmp(ad->argName,argName) == 0){
				swprintf_s(argData, 1024 / sizeof(TCHAR), (L"%S"), (azResult[(k + 1)*ncolumn + 3]));
                break;
            }   
        }

        if(ad->argName == NULL){
            LogOut(_T("-------------不能识别设定选项-------------\n")); 
            LogOut(argName);   
            continue;
        }

        if(ad->argType == ArgTrue){
            *(Boolean *) ad->argLoc = TRUE; 
            continue;
        }

        if(ad->argType == ArgFalse){
            *(Boolean *) ad->argLoc = FALSE;   
            continue;
        } 

        switch(ad->argType){
                case ArgInt:
                    *(int *)ad->argLoc = _wtoi(argData);
                    break;
                case ArgFloat:
                    *(float *)ad->argLoc = (float)_wtof(argData); 
                    break;
                case ArgString:
                case ArgFilename:
                    *(TCHAR **)ad->argLoc = _wcsdup(argData);
                    break;
                case ArgBoolean:
                    switch(argData[0]){
                case 't':
                case 'T':
                    *(Boolean *)ad->argLoc = TRUE;
                    break;
                case 'f':
                case 'F':
                    *(Boolean *)ad->argLoc  = FALSE;
                    break;
                default:
                    LogOut(_T("-------------不能识别布尔选项-------------\n")); 
                    LogOut(argData);
                    break;
                    }
                    break;
                case ArgColor:
                    *(COLORREF *)ad->argLoc = ParseColorName(argData);
                    break;
                case ArgAttribs:
                    {
                        ColorClass cc = (ColorClass)(_int64)ad->argLoc;
                        ParseAttribs(&appData.AtextAttribs[cc].color, 
                            &appData.AtextAttribs[cc].effects, argData);
                    }					
                    break;
                case ArgBoardSize:
                    *(BoardSize *)ad->argLoc = ParseBoardSize(argData);
                    break;
                case ArgNone:
                    //ExitArgError("Unrecognized argument", argValue);
                    break;
                default:
                    break;
        }  

    }
    //释放为记录集分配的内存，如果返回了空记录集并不会发生错误
    sqlite3_free_table(azResult);

    rc = sqlite3_close(db_ini);

    return rc;
}

/////////////////////////////////////////////////////////
// bool 
int SaveOneArgToSqlite(ArgDescriptor *ad, sqlite3 *db_ini){

    //1, 先检查有没有数据项,如有则更新,没有则加入

    char *szErrMsg  = 0;
    int  nrow       = 0;
    int  ncolumn    = 0;    //查询语句返回的结果集的行数，列数

    int  rc         = 0;

    char **azResult;        //用于保存查询结果集数据

    // sqlite3_get_table函数可以返回SQL语句执行之后的记录集，以及行列数   

    char buf[1024];

    sprintf_s(buf,1024,"SELECT * FROM tab_ini WHERE argName = '%S'", ad->argName);

    rc = sqlite3_get_table(db_ini,buf,&azResult,&nrow,&ncolumn,&szErrMsg);

    if(rc != SQLITE_OK){
       LogOuts(szErrMsg);
       LogOut(_T("-------------不能查找保存项-------------\n")); 
       sqlite3_free(szErrMsg);
    }

    //释放为记录集分配的内存，如果返回了空记录集并不会发生错误
    sqlite3_free_table(azResult);

    TCHAR data[1024];
    //int  type;
    //int  
	TCHAR *p;
    data[0] = 0;

    switch (ad->argType) {
            case ArgString: 
            case ArgFilename:
                p = *(TCHAR **)ad->argLoc;

                if(p == NULL){
                    return 0;
                }

				swprintf_s(data, sizeof(data) / sizeof(TCHAR), L"%s", p);

                break;
            case ArgInt:
                //				fprintf(f, "/%s=%d\n", ad->argName, *(int *)ad->argLoc);
				swprintf_s(data, sizeof(data) / sizeof(TCHAR), L"%d", *(int*)ad->argLoc);
                break;
            case ArgFloat:
                //				fprintf(f, "/%s=%g\n", ad->argName, *(float *)ad->argLoc);
				swprintf_s(data, sizeof(data) / sizeof(TCHAR), L"%g", *(float*)ad->argLoc);
                break;
            case ArgBoolean:
                //				fprintf(f, "/%s=%s\n", ad->argName, 
                //					(*(Boolean *)ad->argLoc) ? "true" : "false");
				swprintf_s(data, sizeof(data) / sizeof(TCHAR), L"%s", (*(Boolean *)ad->argLoc) ? L"true" : L"false");
                break;
            case ArgTrue:
                //				if (*(Boolean *)ad->argLoc) fprintf(f, "/%s\n", ad->argName);
                if (*(Boolean *)ad->argLoc){
					swprintf_s(data, sizeof(data) / sizeof(TCHAR), L"%s", ad->argName);
                }
                break;
            case ArgFalse:
                //				if (!*(Boolean *)ad->argLoc) fprintf(f, "/%s\n", ad->argName);
                if (!*(Boolean *)ad->argLoc){
					swprintf_s(data, sizeof(data) / sizeof(TCHAR), L"%s", ad->argName);
                }
                break;
            case ArgColor:
                //				{
                //					COLORREF color = *(COLORREF *)ad->argLoc;
                //					fprintf(f, "/%s=#%02x%02x%02x\n", ad->argName, 
                //						color&0xff, (color>>8)&0xff, (color>>16)&0xff);
                //				}
                {
                    COLORREF color = *(COLORREF *)ad->argLoc;
					swprintf_s(data, sizeof(data) / sizeof(TCHAR), L"#%02x%02x%02x", color & 0xff, (color >> 8) & 0xff, (color >> 16) & 0xff);
                }
                break;
            case ArgAttribs:
                //				{
                //					MyTextAttribs* ta = &DIS.textAttribs[(ColorClass)(__int64)ad->argLoc];
                //					fprintf(f, "/%s=\"%s%s%s%s%s#%02x%02x%02x\"\n", ad->argName,
                //						(ta->effects & CFE_BOLD) ? "b" : "",
                //						(ta->effects & CFE_ITALIC) ? "i" : "",
                //						(ta->effects & CFE_UNDERLINE) ? "u" : "",
                //						(ta->effects & CFE_STRIKEOUT) ? "s" : "",
                //						(ta->effects) ? " " : "",
                //						ta->color&0xff, (ta->color >> 8)&0xff, (ta->color >> 16)&0xff);
                //				}
                {
                    MyTextAttribs* ta = &appData.AtextAttribs[(ColorClass)(__int64)ad->argLoc];
					swprintf_s(data, sizeof(data) / sizeof(TCHAR), L"%s%s%s%s%s#%02x%02x%02x",
                						(ta->effects & CFE_BOLD) ? L"b" : L"",
                						(ta->effects & CFE_ITALIC) ? L"i" : L"",
                						(ta->effects & CFE_UNDERLINE) ? L"u" : L"",
                						(ta->effects & CFE_STRIKEOUT) ? L"s" : L"",
                						(ta->effects) ? L" " : L"",
                						ta->color&0xff, (ta->color >> 8)&0xff, (ta->color >> 16)&0xff);
                }
                break;
            //case ArgFilename:
            //    //				if (strchr(*(char **)ad->argLoc, '\"')) {
            //    //					fprintf(f, "/%s='%s'\n", ad->argName, *(char **)ad->argLoc);
            //    //				} else {
            //    //					fprintf(f, "/%s=\"%s\"\n", ad->argName, *(char **)ad->argLoc);
            //    //				}
            //    if (strchr(*(char **)ad->argLoc, '\"')) {
            //        sprintf_s(data,512, "'%s'",   *(char **)ad->argLoc);
            //    } else {
            //        sprintf_s(data,512, "%s", *(char **)ad->argLoc);
            //    }
            //    break;
            case ArgBoardSize:
                //				fprintf(f, "/%s=%s\n", ad->argName,
                //					sizeInfo[*(BoardSize *)ad->argLoc].name);
				swprintf_s(data, sizeof(data) / sizeof(TCHAR), L"%s", sizeInfo[*(BoardSize *)ad->argLoc].name);
                break;
            case ArgFont:
                //				{
                //					int bs;
                //					for (bs=0; bs<NUM_SIZES; bs++) {
                //						MyFontParams *mfp = &DIS.font[bs][(int)(__int64) ad->argLoc]->mfp;
                //						fprintf(f, "/size=%s ", sizeInfo[bs].name);
                //						fprintf(f, "/%s=\"%s:%g%s%s%s%s%s\"\n",
                //							ad->argName, mfp->faceName, mfp->pointSize,
                //							mfp->bold || mfp->italic || mfp->underline || mfp->strikeout ? " " : "",
                //							mfp->bold ? "b" : "",
                //							mfp->italic ? "i" : "",
                //							mfp->underline ? "u" : "",
                //							mfp->strikeout ? "s" : "");
                //					}
                //				}

                return 0;   //字体暂时不保存了
                break;
            case ArgCommSettings:
                				//PrintCommSettings(f, ad->argName, (DCB *)ad->argLoc);
                return 0;  //通讯不保存了
                break;
            default:
                break;
    }

    if(nrow != 0){      //更新
        sprintf_s(buf,1024,"UPDATE tab_ini SET IsSave = %d,argType = %d,argData = '%S' WHERE argName = '%S'",
            ad->save, ad->argType, data, ad->argName);

        rc = sqlite3_exec(db_ini,buf,0,0,&szErrMsg);
        if(rc != SQLITE_OK){
			LogOuts(szErrMsg);
            LogOut(_T("-------------不能更新保存项-------------\n")); 
            sqlite3_free(szErrMsg);
        }
    }
    else{               //插入
        sprintf_s(buf,1024,"INSERT INTO tab_ini VALUES ('%S',%d,%d,'%S','%S');", 
            ad->argName,ad->save,ad->argType,data,data);
        rc = sqlite3_exec(db_ini,buf,0,0,&szErrMsg);
        if(rc != SQLITE_OK){
			LogOuts(szErrMsg);
            LogOut(_T("-------------不能插入保存项-------------\n")); 
            sqlite3_free(szErrMsg);
        }
    }

    
    return rc;
}

/////////////////////////////////////////////////////////
// bool 
int SaveSettingDataToSqlite(void){

    // 1, 打开数据库
    sqlite3 *db_ini;
    int      rc;
    char     *szErrMsg;
    ArgDescriptor *ad;

    WINDOWPLACEMENT wp;
    //char dir[MSG_SIZ];


	dispboard_t *pDis = OBS[0];

    if (!pDis->hwndThis){
        return 0;
    }
	
    wp.length = sizeof(WINDOWPLACEMENT);
    GetWindowPlacement(pDis->hwndThis, &wp);
    appData.boardX = wp.rcNormalPosition.left;
    appData.boardY = wp.rcNormalPosition.top;

	appData.bsize = pDis->bsize;              //尺寸

    //得到当前的窗口的宽度： GetClientRect(hwndMain, &crect);
    RECT crect;
    GetClientRect(pDis->hwndThis, &crect);
    appData.winWidth = crect.right- crect.left;

	//得到当前的引擎信息，取第一个窗口的引擎
	appData.first_yqID	= pDis->first.yqID;
	//appData.second_yqID	= pDis->second.yqID;

    if( rc = SqliteOpenDataBase(&db_ini,L3_DB_INI)){
        return rc;      //打开有错,不能保存
    }


    //开始事务

    rc = sqlite3_exec(db_ini,"BEGIN;",0,0, &szErrMsg);

    if(rc != SQLITE_OK){
		LogOuts(szErrMsg);
       LogOut(_T("-------------不能开始保存事务-------------\n")); 
       sqlite3_free(szErrMsg);
       return rc;
    }

    //appData.animateDragging     = true;           //拖动时
    appData.animate               = false;          //走棋时
    //appData.highlightLastMove   = true;
    //appData.highlightDragging   = true;           //将要放的目标棋格
    //appData.testLegality        = true;           //走步的合法性判断


    //
    for (ad = argDescriptors; ad->argName != NULL; ad++) {
        if (!ad->save) {
            continue;
        }
        if(SaveOneArgToSqlite(ad,db_ini)){
            LogOut(_T("不能保存下列选择项:"));
			LogOut(ad->argName);
			LogOut(_T("\n"));
        }

        //break;
    }




    //结束事务

    rc = sqlite3_exec(db_ini,"COMMIT;",0,0, &szErrMsg);

    if(rc != SQLITE_OK){
		LogOuts(szErrMsg);
		LogOut(_T("-------------不能结束保存事务-------------\n"));
       sqlite3_free(szErrMsg);
       return rc;
    }


	LogOut(_T("保存设定数据成功!\n"));

    //关闭数据库

    sqlite3_close(db_ini);

    return rc;
}


