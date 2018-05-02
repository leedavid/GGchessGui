#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"




int 
CN183_Parse_Line(TCHAR* line){

    TCHAR str[512];
	TCHAR *p;
    
    if(ICS.buf_len < 4){
		LogOut(line);
        ICS.buf_len = 0;
        return TRUE;
    }

	//LogOut("\n<<<<<<<<<<>>>>>>>>>>\n");
	//LogOut(ICS.buf);

	//< 276 You ReJoin As Red > //棋桌，走子方

    //ICS.buf_len ++; //跳过一个换行

    //还没有登录成功
    if(ICS.loggedOn == FALSE){
        //
        //sprintf_s(ICS.star_match[0],16,"m`eW");
        //CMX_183_Get_Client_Code();

        //
        if(looking_at(&ICS.tbuf[1], _T("@ client?"))){
            CMX_183_Get_Client_Code();

#ifdef DEBUG_MODE 
        //LogOut(ICS.star_match[0]);
        //LogOut("\nDecode:\n");
        //LogOut(ICS.ICS_183);
#endif
            return TRUE;
        }

        if(looking_at(&ICS.tbuf[1],_T("Is your client in english?"))){
            //SendToICSDelayed("nowisnot187\n", MXQ_LOG_DELAY_MS);   
			SendToICSDelayed(L"nowitisnot191\n", MXQ_LOG_DELAY_MS); 
            return TRUE;
        }

        //
        if(looking_at(&ICS.tbuf[1],(TCHAR*)CN183_IsFirstCome)){ ////你是不是初来乍到？
            CMX_183_SEND_CODDING_DelayMs(L"yesihave", MXQ_LOG_DELAY_MS);
            return TRUE;
        }

        //
		if (looking_at(&ICS.tbuf[1], (TCHAR*)CN183_UserName)){
            CMX_183_SEND_CODDING_DelayMs((appData.ACPSics.ICS_user),MXQ_LOG_DELAY_MS);
            return TRUE;
        }

        //
		if (looking_at(&ICS.tbuf[1], (TCHAR*)CN183_PassWord)){
            CMX_183_SEND_CODDING_DelayMs((appData.ACPSics.ICS_pass),MXQ_LOG_DELAY_MS);
            return TRUE;
        }
        
        //
        //if(ICS.tbuf[ICS.buf_len - 3] == '%'){    //
		if (TCHAR* p = wcsstr(ICS.tbuf,L"%")){
            //for(int i=0; i<256; i++){
            //    TCHAR c = ICS.tbuf[i+1];
            //    if(c =='!' || c=='%'){
            //        str[i] = 0;
            //        break;
            //    }
            //    str[i] = c;
            //}
			int i;
			for (i = 0; i< (p - ICS.tbuf-1); i++){
				str[i] = ICS.tbuf[i + 1];
			}
			str[i] = 0;

			SetIcsLogOk(str);
            CMX_183_SEND_CODDING_DelayMs(L"map",MXQ_LOG_DELAY_MS);
            return TRUE;
        }

        SendToPlayerByColor(ICS.tbuf,ColorSeek,TRUE);
        return TRUE;
    }
    //*********************************以下是登录成功了*********************


    //***************************************************************************************
    //  ^
    if(ICS.tbuf[0] == ' ' && ICS.tbuf[1] == '^'){
        //开始登录的一句话
        SendToPlayerByColor(L"\n 您已正常登录ICS网站!!\n",ColorShout,TRUE);
        SendToPlayerByColor(ICS.tbuf,ColorShout,TRUE);
        return TRUE;
    }
    //***************************************************************************************
    //**
    if(ICS.tbuf[1] == '*' && ICS.tbuf[2] == '*'){
        ICS.tbuf[0] = ' ';
        SendToPlayerByColor(ICS.tbuf,ColorNormal,TRUE);
        return TRUE;
    }
    //***************************************************************************************
    //* 注意
    if(ICS.tbuf[1] == '*' && ICS.tbuf[2] == ' '){
        ICS.tbuf[0] = ' ';
        SendToPlayerByColor(ICS.tbuf,ColorShout,TRUE);
        return TRUE;
    }
    //***************************************************************************************
    //^              南帝擂台-大理国[慢棋]
	//
    if(ICS.tbuf[1] == '^' && ICS.tbuf[2] == ' '){
        ICS.tbuf[0] = ' ';
        SendToPlayerByColor(ICS.tbuf,ColorSeek,TRUE);
        return TRUE;
    }
    //***************************************************************************************
    // * 提示:在本大厅内点鼠标右键可查看更多功能菜单!
    if(ICS.tbuf[1] == ' ' && ICS.tbuf[2] == '*'){
        ICS.tbuf[0] = ' ';
        SendToPlayerByColor(ICS.tbuf,ColorSeek,TRUE);
        return TRUE;
    }
    //***************************************************************************************
    if(ICS.tbuf[1] == '!' && ICS.tbuf[2] == ' '){
        ICS.tbuf[0] = ' ';
        SendToPlayerByColor(ICS.tbuf,ColorKibitz,TRUE);
        return TRUE;
    }
    //# 
    //***************************************************************************************
    if(ICS.tbuf[1] == ' ' && ICS.tbuf[2] == '#'){
        ICS.tbuf[0] = ' ';
        SendToPlayerByColor(ICS.tbuf,ColorNormal,TRUE);
        return TRUE;
    }
    //***************************************************************************************
    if(ICS.tbuf[1] == '#' && ICS.tbuf[2] == ' '){
        ICS.tbuf[0] = ' ';
        SendToPlayerByColor(ICS.tbuf,ColorNormal,TRUE);
        return TRUE;
    }

	//~x  //可能是棋局开始的信息
	if(ICS.tbuf[1] == '~' && ICS.tbuf[2] == 'x'){

		LogOut(_T("\nDeBug 可能是棋局开始的信息\n"));
		LogOut(ICS.tbuf);

		if(ICS.table != 0){
			SendMessage(OBS[ICS.table]->hwndThis,WM_USER_ICS_INFO,NULL,(LPARAM)&ICS.tbuf[1]);
		}
		else{
			LogOut(_T("\n棋桌不对\n"));
		}
		return TRUE;
	}

	//if(strstr(ICS.buf,"~x")){
	//	return TRUE;
	//}

    //***************************************************************************************
    //===========下面的暂不能解析==
    //$$ 聚义堂 你好不是 4段 0 6 151 0 1 0 
    //
    //===========下面的暂不能解析==
    //$$$ maxads 1
    //if(ICS.buf[1] == '$' && ICS.buf[2] == '$'){
    //    ICS.buf[0] = ' ';
    //    SendToPlayerByColor(ICS.buf,ColorNormal,TRUE);
    //    return TRUE;
    //}
    if(looking_at(&ICS.tbuf[1],_T("$$ @ @ @ @ @ @ @ @ @"))){
        //SetIcsTitleName(ICS.star_match[0]);
		/*sprintf_s(ICS.ICS_log_name,sizeof(ICS.ICS_log_name),"%s(%s)",ICS.star_match[1],ICS.star_match[2]);*/

		swprintf_s(ICS.log_name, sizeof(ICS.log_name) / sizeof(TCHAR), L"%s", (ICS.star_match[1]));

        return TRUE;
    }
    if(looking_at(&ICS.tbuf[1],_T("$$$ maxads"))){
        return TRUE;
    }
    //***************************************************************************************
    //$ You Go East
    if(ICS.tbuf[1] == '$' && ICS.tbuf[2] == ' '){
        ICS.tbuf[0] = ' ';
        SendToPlayerByColor(ICS.tbuf,ColorKibitz,TRUE);
        return TRUE;
    }
    //***************************************************************************************
    //1,是不是% 或!%结尾
    if(ICS.cbuf[ICS.buf_len - 3] == '%'){    //
        for(int i=0; i<256; i++){
            TCHAR c = ICS.tbuf[i+1];
            if(c =='!' || c=='%'){
                str[i] = 0;
                break;
            }
            str[i] = c;
        }
        //SetIcsLogOk(str);
        //CMX_183_SEND_CODDING_DelayMs("map",MXQ_LOG_DELAY_MS);
        SetIcsTitleName(str);
        ICS.started = STARTED_NONE;
        return TRUE;
    }

	//+		&ICS.buf[1]	0x0053cfb9 "~ 聚义堂 快 棋 对 阵 表 //+		line	0x0053cfb8 "
	//~ 聚义堂 快 棋 对 阵 表 
	//"	char *
    //***************************************************************************************
		//if(ICS.buf[0] == '~' && ICS.buf[1] == ' '){


	//}

    //***************************************************************************************

    if(looking_at(&ICS.tbuf[1],_T("[ 名字(等级) ]"))){
        ICS.count   = 0;
        ICS.started = STARTED_PLAYER_LIST;
        return TRUE;
    }
    //名剑之锋(1段) adslhq
    if(ICS.started == STARTED_PLAYER_LIST){
        if(looking_at(&ICS.tbuf[1],_T("@(@) @"))){
			swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%s %s"), ICS.star_match[0], ICS.star_match[1]);
            SendDlgItemMessage(TAB.hwndICS_Board_List,IDC_ICS_USER_LIST,
                CB_INSERTSTRING,-1,(LPARAM)str);  
            ICS.count ++;
            SendDlgItemMessage(TAB.hwndICS_Board_List,
                IDC_ICS_USER_LIST, CB_SETCURSEL, ICS.count-1,0); 
            return TRUE;
        }
        else{            
            ICS.started = STARTED_NONE;
        }        
    }
    //***************************************************************************************

    if(looking_at(&ICS.tbuf[1],_T("[ Dir     Room        Status Players Command ]"))){
        ICS.started = STARTED_ROOM_DIR;
        ICS.count   = 0;
        return TRUE;
    }
    //EastSouth NO      closed 0
    if(ICS.started == STARTED_ROOM_DIR){
        if(
			(ICS.tkind = 1, looking_at(&ICS.tbuf[1], _T("@ <@>@ @ @ @")))
			|| (ICS.tkind = 2, looking_at(&ICS.tbuf[1], _T("@ NO      closed 0")))
			|| (ICS.tkind = 3, looking_at(&ICS.tbuf[1], _T("CenterLeft ")))
			|| (ICS.tkind = 4, looking_at(&ICS.tbuf[1], _T("CenterRight ")))
        ){            
            if(ICS.tkind == 1){
                //sprintf_s(str,sizeof(str),"%s\n%s%s\n%s",
                //    ICS.star_match[1],ICS.star_match[2],ICS.star_match[3],ICS.star_match[4]);
				swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%s\n%s\n%s"),
                    ICS.star_match[1],ICS.star_match[2],ICS.star_match[4]);
            }
            else if(ICS.tkind == 2){
				swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%s\n此处已关闭!\n"), ICS.star_match[0]);
            }
			if(ICS.count < 9){
				SetDlgItemText(TAB.hwndGoPlace,MXQ_ICS_PLACE[ICS.count],str);
			}
            ICS.count ++;
            return TRUE;
        }
        else{
            ICS.started = STARTED_NONE;
        }
    }
    //***************************************************************************************
  
	if (looking_at(&ICS.tbuf[1], _T("[ 桌号  红方 "))){
        ICS.count       = 0;
        ICS.started     = STARTED_TABLE_LIST;
        return TRUE;
    }
    if(ICS.started == STARTED_TABLE_LIST){

		if (looking_at(&ICS.tbuf[1], _T(" @ @  @ @  @ @ @ @"))){
            //1, 得到棋桌编号
            int bh = _wtoi(ICS.star_match[0]);
            if(bh == 0){
                ICS.count ++;
                return TRUE;
            }
            //ICS.count ++;
            int SubItem  = 0;
            LV_ITEM lvi;
            lvi.mask     = LVIF_TEXT + LVIF_PARAM;
            lvi.pszText  = str;
            lvi.iItem    = ++ICS.count;
            lvi.lParam   = bh;
            lvi.iSubItem = SubItem++;
			swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%d"), bh);
            SendDlgItemMessage(TAB.hwndICS_Board_List,
                IDC_LIST_BOARD,LVM_INSERTITEM,0,(LPARAM)&lvi);

           //得到红方名称,

			TrimIcsName(ICS.star_match[1]);

            lvi.iItem --;       //注意,这儿还得减一下
            lvi.iSubItem    = SubItem++;
            lvi.mask        = LVIF_TEXT;
            lvi.pszText     = ICS.star_match[1];
            SendDlgItemMessage(TAB.hwndICS_Board_List,
                IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)&lvi); 

            //3,红方级别
            lvi.iSubItem    = SubItem++;
            lvi.mask        = LVIF_TEXT;                
			lvi.pszText = ICS.star_match[2];
            SendDlgItemMessage(TAB.hwndICS_Board_List,
                IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)&lvi);

			TrimIcsName(ICS.star_match[3]);

            //4,黑方名称
            lvi.iSubItem    = SubItem++;
            lvi.mask        = LVIF_TEXT;                
			lvi.pszText = ICS.star_match[3];
            SendDlgItemMessage(TAB.hwndICS_Board_List,
                IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)&lvi);

			
            //5,黑方级别
            lvi.iSubItem    = SubItem++;
            lvi.mask        = LVIF_TEXT;                
			lvi.pszText = ICS.star_match[4];
            SendDlgItemMessage(TAB.hwndICS_Board_List,
                IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)&lvi);
            //6,计时方式
            lvi.iSubItem    = SubItem++;
            lvi.mask        = LVIF_TEXT;                
            lvi.pszText     = ICS.star_match[5];
            SendDlgItemMessage(TAB.hwndICS_Board_List,
                IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)&lvi);
            //7,有没有开始
            lvi.iSubItem    = SubItem++;
            lvi.mask        = LVIF_TEXT;                
            lvi.pszText     = ICS.star_match[6];
            SendDlgItemMessage(TAB.hwndICS_Board_List,
                IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)&lvi);
            //8,有多少人在旁观
            bh = _wtoi(ICS.star_match[7]);
            lvi.iSubItem    = SubItem++;
            lvi.mask        = LVIF_TEXT; 
            //lvi.lParam      = bh;
			swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%d"), bh);
            lvi.pszText     = str;
            SendDlgItemMessage(TAB.hwndICS_Board_List,
                IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)&lvi); 
            return TRUE;
        }

		else if (looking_at(&ICS.tbuf[1], _T(" @ @ @ @ @ @ @ @"))){
            //1, 得到棋桌编号
            int bh = _wtoi(ICS.star_match[0]);
            if(bh == 0){
                ICS.count ++;
                return TRUE;
            }
            //ICS.count ++;
            int SubItem  = 0;
            LV_ITEM lvi;
            lvi.mask     = LVIF_TEXT + LVIF_PARAM;
            lvi.pszText  = str;
            lvi.iItem    = ++ICS.count;
            lvi.lParam   = bh;
            lvi.iSubItem = SubItem++;
			swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%d"), bh);
            SendDlgItemMessage(TAB.hwndICS_Board_List,
                IDC_LIST_BOARD,LVM_INSERTITEM,0,(LPARAM)&lvi);

           //得到红方名称,

			TrimIcsName(ICS.star_match[1]);

            lvi.iItem --;       //注意,这儿还得减一下
            lvi.iSubItem    = SubItem++;
            lvi.mask        = LVIF_TEXT;
            lvi.pszText     = ICS.star_match[1];
            SendDlgItemMessage(TAB.hwndICS_Board_List,
                IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)&lvi); 

            //3,红方级别
            lvi.iSubItem    = SubItem++;
            lvi.mask        = LVIF_TEXT;                
            lvi.pszText     = ICS.star_match[2];
            SendDlgItemMessage(TAB.hwndICS_Board_List,
                IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)&lvi);

			TrimIcsName(ICS.star_match[3]);

            //4,黑方名称
            lvi.iSubItem    = SubItem++;
            lvi.mask        = LVIF_TEXT;                
            lvi.pszText     = ICS.star_match[3];
            SendDlgItemMessage(TAB.hwndICS_Board_List,
                IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)&lvi);

			
            //5,黑方级别
            lvi.iSubItem    = SubItem++;
            lvi.mask        = LVIF_TEXT;                
            lvi.pszText     = ICS.star_match[4];
            SendDlgItemMessage(TAB.hwndICS_Board_List,
                IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)&lvi);
            //6,计时方式
            lvi.iSubItem    = SubItem++;
            lvi.mask        = LVIF_TEXT;                
            lvi.pszText     = ICS.star_match[5];
            SendDlgItemMessage(TAB.hwndICS_Board_List,
                IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)&lvi);
            //7,有没有开始
            lvi.iSubItem    = SubItem++;
            lvi.mask        = LVIF_TEXT;                
            lvi.pszText     = ICS.star_match[6];
            SendDlgItemMessage(TAB.hwndICS_Board_List,
                IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)&lvi);
            //8,有多少人在旁观
            bh = _wtoi(ICS.star_match[7]);
            lvi.iSubItem    = SubItem++;
            lvi.mask        = LVIF_TEXT; 
            //lvi.lParam      = bh;
			swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%d"), bh);
            lvi.pszText     = str;
            SendDlgItemMessage(TAB.hwndICS_Board_List,
                IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)&lvi); 
            return TRUE;
        }
        else{
            ICS.started = STARTED_NONE;
        }
    }
    //***************************************************************************************
    //{ * 第 62 桌 哈洛(1f) 离 开 黑 方 }  ICS.buf[0] = ' '; ..if(ICS.buf[1] == '$' && ICS.buf[2] == '$'){
    if(ICS.tbuf[1] == '{' && ICS.tbuf[2] == ' ' && ICS.tbuf[3] == '*' ){

		/*
        //{ * 第 1 关 第 7 台 你好不是(0舵) 加 入 观 战 }
        if(
              (ICS.tkind = 1, looking_at(&ICS.buf[5],"第 @ 关 第 @ 台 @(@) @"))
            ||(ICS.tkind = 2, looking_at(&ICS.buf[5],"第 @ 台 @(@) @"))
            ){
            char* pwhat;
            if(ICS.tkind == 1){
                pwhat = ICS.star_match[4];
                ICS.stage   = atoi(ICS.star_match[0]);
                ICS.table   = (ICS.stage - 1) * 20 + atoi(ICS.star_match[1]);
            }
            else if(ICS.tkind == 2){
                ICS.stage   = 0;
                ICS.table   = atoi(ICS.star_match[0]);
                pwhat = ICS.star_match[3];
            }

            if(strstr(pwhat,"加 入 观 战")){
                //int test  = 0;
                //首先得判断是不是你自己在观战
                if(ICS.tkind == 1){
                    pwhat = ICS.star_match[2];
                }
                else if(ICS.tkind == 2){
                    pwhat = ICS.star_match[1];
                }
                if(strcmp(ICS.ICS_log_name,pwhat) == 0){    //是你加入观战了
                    //    //    if(DIS.gameMode == IcsObserving){
                    //        //你已经在旁观了解
                    //        LogOut("\n你已经在旁观了!!\n");
                    //        return TRUE;
                    //    }
                    //    DIS.gameMode = IcsObserving;
                    //    ICS.table    = atoi(ICS.star_match[0]);
                    //if(DIS.gameMode == IcsObserving){
                    //    //你已经在旁观了解
                    //    LogOut("\n你已经在旁观了!!\n");                       
                    //}
                    //else{
                        //DIS.gameMode = IcsObserving;
                        //sprintf_s(str,sizeof(str),"你正在旁观棋局: 第 %d 关 第 %d 桌",ICS.stage,ICS.table); 
                        //DispStatS(str);
                    //}
                    
                }
                else{       //别人加入了观战
                }
            }
        }
        
        ICS.buf[0] = ' ';
        SendToPlayerByColor(&ICS.buf[2],ColorNormal,TRUE); */
        return TRUE;
    }
    //***************************************************************************************
    if(ICS.tbuf[1] == '{' && ICS.tbuf[2] == ' ' && ICS.tbuf[3] == '+'){
        
        /*ICS.buf[0] = ' ';
        SendToPlayerByColor(&ICS.buf[2],ColorNormal,TRUE);*/
        return TRUE;
    }
    //***************************************************************************************
    if(ICS.tbuf[1] == '{' && ICS.tbuf[2] == ' ' && ICS.tbuf[3] == '-'){
        
        /*ICS.buf[0] = ' ';
        SendToPlayerByColor(&ICS.buf[2],ColorNormal,TRUE);*/
        return TRUE;
    }
    //***************************************************************************************
    if(ICS.tbuf[1] == '{' && ICS.tbuf[2] == ' ' && ICS.tbuf[3] == '#'){
        
        /*ICS.buf[0] = ' ';
        SendToPlayerByColor(&ICS.buf[2],ColorNormal,TRUE);*/
        return TRUE;
    }
    //***************************************************************************************
    //{ Stage 3 Table 2 early(8F) Leave Red To Obs } //{ Table 42 Side Reset }
    if(
		(ICS.tkind = 1, looking_at(&ICS.tbuf[1], _T("{ Stage @ Table @ @")))
		|| (ICS.tkind = 2, looking_at(&ICS.tbuf[1], _T("{ Table @ @")))
       ){
        /*ICS.buf[0] = ' ';
        SendToPlayerByColor(&ICS.buf[2],ColorNormal,TRUE);*/
        return TRUE;
    }

    if(ICS.tbuf[1] == '<'){                          //发送相应的棋桌信息

		ICS.started = STARTED_NONE;

			//	if(looking_at(message,"< @ You Join As @ >")){	

			//// 30 You Join As Red >

			////if(OBS[ICS.table] == NULL){
			////	OBS[ICS.table] = OBS[0];
			////	OBS[ICS.table]->table = ICS.table;
			////}

			//pDis->table = atoi(ICS.star_match[0]);

        if(looking_at(&ICS.tbuf[1],_T("< @ @"))){
			ICS.table = _wtoi(ICS.star_match[0]);

			if(OBS[ICS.table] == NULL){
				OBS[ICS.table] = OBS[0];
				OBS[ICS.table]->table = ICS.table;
			}
			else{
				OBS[ICS.table] = OBS[0];
				OBS[ICS.table]->table = ICS.table;
			}

			//如果棋桌没有开始，就要开始一下。

			SendMessage(OBS[ICS.table]->hwndThis,WM_USER_ICS_INFO,NULL,(LPARAM)&ICS.tbuf[1]);
		}

        //ICS.buf[0] = ' ';
        //SendToPlayerByColor(&ICS.buf[2],ColorNormal,TRUE); //这儿不显示了ICS棋步了

        return TRUE;
    }




	//=================================================================================================
	//将 "~ "开头的合在一起解析
	if(ICS.tbuf[0] == '~' || ICS.tbuf[1] == '~'){
		
		// \015\012~ Room Map\015\012[ Dir     Room        Status Players ]\015\012East <空地>空地盘 open 0\015\012South <空地>空地盘 open 0\015\012
		if(looking_at(&ICS.tbuf[3],_T("Room Map"))){
			ICS.started = STARTED_ROOM_DIR;
			ICS.count   = 0;
			return TRUE;
		}

		//~ Player List     //处理用户列表
		if(looking_at(&ICS.tbuf[3],_T("Player List"))){
			ICS.count   = 0;
			ICS.started = STARTED_PLAYER_LIST;
			//首先得清空　用户列表
			SendDlgItemMessage(TAB.hwndICS_Board_List,IDC_ICS_USER_LIST,CB_RESETCONTENT,0,0);  //CB_RESETCONTENT
			return TRUE;
		}
		
		//~ Table 183 Move
		if(looking_at(&ICS.tbuf[3],_T("Table @ Move"))){
			ICS.table   = _wtoi(ICS.star_match[0]);	
			ICS.started = STARTED_MOVES;                 //开始棋步输入
			ICS.count   = 0;
			LogOut(_T("\n开始接收初始棋步"));
			return TRUE;
		}

		if((p = wcsstr(&ICS.tbuf[1],_T(" 对 阵 表"))) != NULL){
			//1, 向前搜索
			//int len = (int)strlen(ICS.buf);
			TCHAR *oldp = p;
			while((p--) > &ICS.tbuf[1]){
				if(*p == '~' || *p == '\n'){
					break;
				}
			}

			ASSERT(p >= ICS.tbuf);

			p++;   //跳过一个空格
			p++;

			if(looking_at(p,_T("第 @ 关"))){
				ICS.stage = _wtoi(ICS.star_match[0]);
			}
			else{
				ICS.stage = 0;
			}

			memcpy(str,p,(oldp-p)*sizeof(TCHAR));
			str[(oldp - p)] = NULLCHAR;
			SetDlgItemText(TAB.hwndICS_Board_List,IDC_ICS_STAGE,str);

			//得先清空原有的列表
			SendDlgItemMessage(TAB.hwndICS_Board_List,
				IDC_LIST_BOARD,LVM_DELETEALLITEMS,0,0);

			ICS.count       = 0;
			ICS.started     = STARTED_TABLE_LIST;
			return TRUE;
		}

		//得到当前选手
		//if(looking_at(&ICS.buf[0],"~ 第 @ 桌 选 手")){

		if(wcsstr(&ICS.tbuf[0],_T(" 桌 选 手"))){

			//ICS.table = atoi(&ICS.buf[5]);

			ICS.started = STARTED_GAME_PLAYER;
			ICS.count   = 0;
			return TRUE;
		}


		//===========下面的暂不能解析==
		//~ 对手已经入座,现在开始对局吗?
		//
		if(wcsstr(&ICS.tbuf[3],_T("对手已经入座,现在开始对局吗?"))){		//对方已准备好了解
			//sprintf_s(str,sizeof(str),"< %d gamecanstart >\n", ICS.table);
			SendMessage(OBS[ICS.table]->hwndThis,WM_USER_ICS_INFO,NULL,(LPARAM)&ICS.tbuf[3]);
			ICS.started = STARTED_GAME_CAN_START;
			return TRUE;
		}
		
	}	//以上是以"~ "打头的命令

	if(ICS.started == STARTED_GAME_CAN_START){
		//===========下面的暂不能解析==
		//[   选项       对应棋盘左侧操作按纽               ]  
		//
		//===========下面的暂不能解析==
		//同意对局  蓝色指上箭头[第1排第1个] 
		//
		//===========下面的暂不能解析==
		//调整时间  小闹钟图标[第1排第2个] 
		//
		//===========下面的暂不能解析==
		//交换先手  红黑上下箭头[第2排第1个] 
		//
		//===========下面的暂不能解析==
		//离开本桌  红色推门图标[第2排第2个] 
		//
		//===========下面的暂不能解析==
		//放大棋盘  点桌窗口右上角”口“按纽
		//
		//===========下面的暂不能解析==
		//| Related : a[同意开始] pushtable+26+xiyutian[请他离座] side[交换先手] l[我要离开]

		//SendMessage(OBS[ICS.table]->hwndThis,WM_USER_ICS_INFO,NULL,(LPARAM)&ICS.buf[0]);
		return TRUE;
	}

	//=================================================================================================

	if(ICS.started == STARTED_MOVES){		
		if(ICS.count == 0){
			ICS.count ++;
			return TRUE;  //015\012[ Num Move ]
		}
		if(looking_at(&ICS.tbuf[1],_T(" @ @"))){
			swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("move %s %s\n"), ICS.star_match[0], ICS.star_match[1]);
			SendMessage(OBS[ICS.table]->hwndThis,WM_USER_ICS_INFO,NULL,(LPARAM)str);
		}
		ICS.count++;
		return TRUE;
	}

	
	//[ 名字        等级 等级分 级别     卫冕分 帮派      ]

	if(ICS.started == STARTED_GAME_PLAYER){
		if(wcsstr(&ICS.tbuf[0],_T("[ 名字 "))){
			ICS.count = 0;
			return TRUE;
		}

		ICS.count ++;

		//if(looking_at(&ICS.buf[1]," @ @ @ @ @ @")){
		//	ICS.count++;
		//	//sprintf_s(str,sizeof(str),"%s %s %s",ICS.star_match[0],ICS.star_match[1],ICS.star_match[2]);
		//	//if(ICS.count == 1){  //红方
		//	//	SetDlgItemText(HWND_CONSOLE,IDC_TIME_RED_NAME, &ICS.buf[1]);
		//	//}
		//	//else if(ICS.count == 2){
		//	//	SetDlgItemText(HWND_CONSOLE,IDC_TIME_BLACK_NAME, &ICS.buf[1]);
		//	//}
		//	return TRUE;
		//}

		//if(looking_at(&ICS.buf[1],"@ @ @ @ @ @")){		//旁观者
		//	LogOut("\n旁观者：");
		//	LogOut(&ICS.buf[1]);
		//	return TRUE;
		//}

		////其它就是
		//ICS.started = STARTED_NONE;

		swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("player %d %s\n"), ICS.count, &ICS.tbuf[1]);

		SendMessage(OBS[ICS.table]->hwndThis,WM_USER_ICS_INFO,NULL,(LPARAM)str);

		return TRUE;
	}



    //***************************************************************************************
    return FALSE;		//没有处理信息
}

//#define STARTED_NONE            0
//#define STARTED_MOVES           1
//#define STARTED_BOARD           2
//#define STARTED_OBSERVE         3
//#define STARTED_HOLDINGS        4
//#define STARTED_CHATTER         5
//#define STARTED_COMMENT         6
//#define STARTED_MOVES_NOHIDE    7
//#define STARTED_PLAYER_LIST     8
//#define STARTED_TABE_LIST       9

void 
read_from_ics_xqclub(InputSourceRef isr, VOIDSTAR closure, char *data, int count, int error){
	//if (count <= 0){
	//	RemoveInputSource(isr);
	//	LogOut(_T("Connection closed by ICS"));
	//	SetIcsTitleName(_T("已断线!"));
	//	AlreadDisConnectIcs();
	//	initIcs();
	//	return;
	//}

	for (int i = 0; i <= count; i++){
		int k = 0;
	}
}

//  
void
read_from_ics_mxq_cn183(InputSourceRef isr, VOIDSTAR closure,	char *data, int count, int error)  {
#ifdef DEBUG_MODE 
    //if(appData.debugMode){
    if(!error){
#ifdef DEBUG_USE_DEBUG_FILE
		fprintf(appData.debugFP, "<ICS: ");
        show_bytes(appData.debugFP,data,count);
        fprintf(appData.debugFP,"\n");
#endif
    }
    //}
#endif
    if(count <= 0){
        RemoveInputSource(isr);
        LogOut(_T("Connection closed by ICS"));
        SetIcsTitleName(_T("已断线!"));
        AlreadDisConnectIcs();
        initIcs();
        return;
    }

    //一行一行读下去
    //if(ICS.lastnotfinish == TRUE){      //上次有没有结束的行'

    for(int i = 0; i <= count; i++){
        //
        char d = data[i];
        switch(d){
            case '\r':       //有一行结束了
                if(ICS.buf_len == 0){
                    continue;           //跳过第一个'r'
                }
                goto PARSE_LINE;
                break;
            case '%':
                ICS.cbuf[ICS.buf_len++] = d;
                goto PARSE_LINE;
                break;
            default:
                if(i == count){
                    if(ICS.loggedOn == FALSE){
                        goto PARSE_LINE;
                    }
                    else{
                        //ICS.buf_len--;      //可能要减一哇
                    }
                }
                else{
                    ICS.cbuf[ICS.buf_len++] = d; 
                }
                break;
        }
        continue;
PARSE_LINE:
        ICS.cbuf[ICS.buf_len++] = '\n';      //加上一个结尾
        ICS.cbuf[ICS.buf_len++] = NULLCHAR;  //
		//ICS.tbuf = CA2W(ICS.cbuf);
		swprintf_s(ICS.tbuf, sizeof(ICS.tbuf) / sizeof(TCHAR) , _T("%S"), (ICS.cbuf));
        if(CN183_Parse_Line(ICS.tbuf) == TRUE){
            ICS.buf_len = 0;
        } 
        else{
            SendToPlayerByColor(L"\n===========下面的暂不能解析==\n",ColorChannel,FALSE);
            SendToPlayerByColor(ICS.tbuf,ColorChannel,TRUE);
            ICS.buf_len = 0;
        }
    }//for(int i = 0; i <= count; i++){
}

