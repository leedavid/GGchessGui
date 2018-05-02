#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"



BOOL HandleTableIcsMessage(dispboard_t *pDis, TCHAR* message){

	TCHAR str[512];
	PGN* pgn = pDis->pgn;

	//LogOut("\ntable message*********\n");
	//LogOut(message);

	//~x  //可能是棋局开始的信息
	if(message[0] == '~' && message[1] == 'x'){

		if(pDis->IcsGameStartAlready == FALSE){

			GameReset(pDis,TRUE,TRUE,FALSE);

			IcsGameStart(pDis);

			Sleep(200);
		}

		//LogOut(message);

		return TRUE;
	}

	//< 181 State Red 北丐10关 0 英雄同盟会Black 北丐10关 6 剑月轩
    //=====================================================================================
	if(looking_at(message,_T("< @ State "))){

		LogOut(message);

		return TRUE;
	}
    //=====================================================================================
	if (looking_at(message, _T("< @ You @"))){
		if (looking_at(message, _T("< @ You Join As @ >"))){

			// 30 You Join As Red >

			//if(OBS[ICS.table] == NULL){
			//	OBS[ICS.table] = OBS[0];
			//	OBS[ICS.table]->table = ICS.table;
			//}

			pDis->table = _wtoi(ICS.star_match[0]);


			if (wcsstr(ICS.star_match[1], _T("Obs"))){
				
				ChangeGameMode(pDis,IcsObserving);	
				
				GameReset(pDis,TRUE,TRUE, FALSE);
						
				swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("\n你正在%d桌旁观"), pDis->table);
				//DispStatS(str);
				LogOut(str);
			}
			else if (wcsstr(ICS.star_match[1], _T("Red"))){
				swprintf_s(pgn->Red, sizeof(pgn->Red) / sizeof(TCHAR), _T("%s"), ICS.log_name);
				ChangeGameMode(pDis,IcsPlayingWhite);
				
				swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%s"), _T("\n加入红方,等待对局开始!"));
				//DispStatS(str);
				LogOut(str);

			}
			else if (wcsstr(ICS.star_match[1], _T("Black"))){
				swprintf_s(pgn->Black, sizeof(pgn->Black) / sizeof(TCHAR), _T("%s"), ICS.log_name);
				ChangeGameMode(pDis,IcsPlayingBlack);

				swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%s"), _T("\n加入黑方,等待对局开始!"));
				//DispStatS(str);
				LogOut(str);
			}
			else{
				//DispStatS(message);
				LogOut(message);
			}
			return TRUE;
		}

		//< 40 You Leave Red To Obs >
		if (looking_at(message, _T("< @ You Leave @ To Obs >"))){
			if (wcsstr(ICS.star_match[1], _T("Red"))){
				swprintf_s(pgn->Red, sizeof(pgn->Red) / sizeof(TCHAR), _T("%s"), _T("No(No)"));
				ChangeGameMode(pDis,IcsObserving);	

				swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%s"), _T("\n你已离开红方，加入旁观!"));
				//DispStatS(str);
				//SendMessage(hStatusBar,SB_SETTEXT,0,(LPARAM)str);
				LogOut(str);
			}
			else if (wcsstr(ICS.star_match[1], _T("Black"))){
				swprintf_s(pgn->Black, sizeof(pgn->Black) / sizeof(TCHAR), _T("%s"), _T("No(No)"));
				ChangeGameMode(pDis,IcsObserving);	

				swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%s"), _T("\n你已离开黑方，加入旁观!"));
				//DispStatS(str);
				//SendMessage(hStatusBar,SB_SETTEXT,0,(LPARAM)str);
				LogOut(str);
			}			
			DisplayTitle(pDis);	

			if(ICS.cont_dalei == TRUE){  
				ResetGameEvent(pDis);					//恢位一下棋局
				Sleep(668);
				CMX_183_SEND_CODDING(L"j");	
				//Sleep(200);
			}

			return TRUE;
		}

		//< 26 You Leave From Red >
		//< 26 You Leave From Obs >
		//
		if (looking_at(message, _T("< @ You Leave From @ >"))){

			if (wcsstr(ICS.star_match[1], _T("Red"))){
				swprintf_s(pgn->Red, sizeof(pgn->Red) / sizeof(TCHAR), _T("%s"), _T("No(No)"));

				swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%s"), _T("\n你已离开红方!"));
				//DispStatS(str);
				LogOut(str);
			}
			else if (wcsstr(ICS.star_match[1], _T("Black"))){
				swprintf_s(pgn->Black, sizeof(pgn->Black) / sizeof(TCHAR), _T("%s"), _T("No(No)"));

				swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%s"), _T("\n你已离开黑方!"));
				//DispStatS(str);
				LogOut(str);
			}
			else{
				swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%s"), _T("\n你已不在旁观棋桌了!"));
				//DispStatS(str);
				LogOut(str);
			}

			pDis->table = 0;
			ChangeGameMode(pDis,IcsIdle);
			DisplayTitle(pDis);	

						//if(IsDlgButtonChecked(hDlg,IDC_LX_9) == BST_CHECKED){  //连续打擂按键按下了
			//if(ICS.cont_dalei == TRUE){  
			//	//1,再加入棋局,
			//	//if(ICS.stage == 0){
			//	//	sprintf_s(str,sizeof(str),"j %d", curSel);
			//	//	table = curSel;
			//	//}
			//	//else{
			//	//	sprintf_s(str,sizeof(str),"j %d %d",ICS.stage,curSel);
			//	//	table = (ICS.stage-1)*20 + curSel;
			//	//}

			//	Sleep(1000);

			//	CMX_183_SEND_CODDING("j");					

			//	//2,再同意对局
			//	//sprintf_s(str,sizeof(str),"a %d",pDis->table);
			//	//CMX_183_SEND_CODDING(str);
			//}
			//else{
			//	sprintf_s(str,sizeof(str),"l %d", ICS.table);		//结束了就离开了
			//    CMX_183_SEND_CODDING(str);
			//}


            if(ICS.cont_dalei == TRUE){  
				ResetGameEvent(pDis);					//恢位一下棋局
				Sleep(668);
				CMX_183_SEND_CODDING(L"j");	
				//Sleep(200);
			}
			return TRUE;
		}
		
		// 棋桌(40)信息处理没有成功
		//< 40 You ReJoin As Red >
		// 40 You ReJoin As Red >
		// 40 1 40 List 0 你好不是 4段 2118 NO 地狱使者 4段 2336 NO 20-3-50 *  
		// 40 State Red NO NO NOBlack 英雄无敌帮 玄武堂 理事
		//
		// 棋桌(40)信息处理没有成功
		//player 3 ~ Table 40 Move

		if (looking_at(message, _T("< @ You ReJoin As @ >"))){
			if (wcsstr(ICS.star_match[1], _T("Red"))){
				swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%s"), _T("\n你重新执红,加入棋局了!"));
				//DispStatS(str);

				LogOut(str);

				ChangeGameMode(pDis,IcsPlayingWhite);

				GameReset(pDis,TRUE,TRUE, FALSE);

				Sleep(300);
				
			}
			else if (wcsstr(ICS.star_match[1], _T("Black"))){
				swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%s"), _T("\n你重新执黑,加入棋局了!"));
				//DispStatS(str);

				LogOut(str);

				ChangeGameMode(pDis,IcsPlayingBlack);

				GameReset(pDis,TRUE,TRUE, FALSE);

				Sleep(300);
				
			}
			else{
				//DispStatS(message);
				LogOut(message);
			}
			return TRUE;
		}
	}
	//=====================================================================================
	if (wcsstr(message, _T("\n对手已经入座,现在开始对局吗?"))){		//对方已准备好了解
		SendToPlayerByColor(message,ColorShout,FALSE);
		//DispStatS(message);
		return TRUE;
	}
	//=====================================================================================
	//< 26 totentanz(地煞) 2706 NO NO NO Leave Red To Obs >
	if (looking_at(message, _T("< @ @(@) @ @ @ @ Leave @ To Obs >"))){
		if (wcsstr(ICS.star_match[7], _T("Red"))){
			swprintf_s(pgn->Red, sizeof(pgn->Red) / sizeof(TCHAR), _T("No(No)"));
			DisplayTitle(pDis);
		}
		if (wcsstr(ICS.star_match[7], _T("Black"))){
			swprintf_s(pgn->Black, sizeof(pgn->Black) / sizeof(TCHAR), _T("No(No)"));
			DisplayTitle(pDis);
		}
		return TRUE;
	}	

	//=====================================================================================
	if (looking_at(message, _T("< @   * @"))){
		//< 40   * 黑 方 要求换边 >
		if (looking_at(message, _T("< @   * @ 方 要求换边 >"))){
			SendToPlayerByColor(message,ColorShout,FALSE);
			//DispStatS(message);
			return TRUE;
		}
		//< 80   * 黑 方 同 意 对局 >
		if (looking_at(message, _T("< @   * @ 方 同 意 对局 >"))){

			if (wcsstr(ICS.star_match[1], _T("红"))){
				//在这儿看一下是不是自己在下
				if(wcsstr(pDis->pgn->Red,ICS.log_name)){
					ChangeGameMode(pDis,IcsPlayingWhite);
				}
			}
			else if (wcsstr(ICS.star_match[1], _T("黑"))){
				//在这儿看一下是不是自己在下
				if(wcsstr(pDis->pgn->Black,ICS.log_name)){
					ChangeGameMode(pDis,IcsPlayingBlack);
				}
			}

			SendToPlayerByColor(message,ColorShout,FALSE);
			//DispStatS(message);
			return TRUE;
		}
		//< 181   * 你好不是(4段) 来 了 >
		if (looking_at(message, _T("< @   * @(@) 来 了 >"))){
			LogOut(message);
			return TRUE;
		}		
		//< 26   * totentanz(地煞) 离 开 观 战 >
	    //< 27   * totentanz(地煞) 离 开 红 方 >
		if (looking_at(message, _T("< @   * @(@) 离 开 @ @ >"))){
			if (wcsstr(ICS.star_match[3], _T("红"))){
				swprintf_s(pgn->Red, sizeof(pgn->Red) / sizeof(TCHAR), _T("No(No)"));
				DisplayTitle(pDis);
			}
			else if (wcsstr(ICS.star_match[3], _T("黑"))){
				swprintf_s(pgn->Black, sizeof(pgn->Black) / sizeof(TCHAR), _T("No(No)"));
				DisplayTitle(pDis);
			}
			else if (wcsstr(ICS.star_match[3], _T("观"))){

			}
			return TRUE;
		}
	}
	//< 40   * 
	//=====================================================================================

	//< 39 Side Reset >  //红黑交换了
	if(looking_at(message,_T("< @ Side Reset >"))){

		TCHAR ss[128];
		swprintf_s(ss, sizeof(ss) / sizeof(TCHAR), _T("%s"), pgn->Red);

		swprintf_s(pgn->Red, sizeof(pgn->Red) / sizeof(TCHAR), _T("%s"), pgn->Black);

		swprintf_s(pgn->Black, sizeof(pgn->Black) / sizeof(TCHAR), _T("%s"), ss);

		int elo   =  pgn->Relo;
		pgn->Relo =  pgn->Belo;
		pgn->Belo =  elo;

		if(pDis->gameMode == IcsPlayingWhite){
			ChangeGameMode(pDis,IcsPlayingBlack);
		}
		else if(pDis->gameMode == IcsPlayingBlack){
			ChangeGameMode(pDis,IcsPlayingWhite);
		}
		else {
			//ChangeGameMode(pDis,IcsPlayingBlack);
		}


		DisplayTitle(pDis);			

		return TRUE;
	}

	//=====================================================================================
	//游戏结束或对方命令标志
	if (looking_at(message, _T("< @   $ @"))){

		//if(strstr(message,"透明隔音罩") == NULL){

		//	if(strstr(message,"请求") == NULL){
		//		//结局
		//		sprintf_s(pgn->result,sizeof(pgn->result),ICS.star_match[1]);
		//		//地方
		//		sprintf_s(pgn->pevent,sizeof(pgn->pevent),"弈天ICS棋局");

		//		GameEnds(pDis,NAG,pgn->result,GE_ICS);	

		//		LogOut(message);
		//	}
		//}

		if(false){
		}
		else if (wcsstr(message, _T("升起透明隔音罩"))){
		}
		else if (wcsstr(message, _T("放下透明隔音罩"))){
		}
		else if (wcsstr(message, _T("关闭了观战通道"))){
		}
		else if (wcsstr(message, _T("开放了观战通道"))){
		}
		else if (wcsstr(message, _T("请求"))){
		}
		else if (wcsstr(message, _T("在桌上放了个消音器"))){
		}
		else if (wcsstr(message, _T("拿走了桌上的消音器"))){
		}		
		else{
			//结局
			swprintf_s(pgn->result, sizeof(pgn->result) / sizeof(TCHAR), (ICS.star_match[1]));
			//地方
			swprintf_s(pgn->pevent, sizeof(pgn->pevent) / sizeof(TCHAR), _T("弈天ICS棋局"));

			GameEnds(pDis,NAG,pgn->result,GE_ICS);	

			if(ICS.only_this_table == FALSE){
				Sleep(1000);
				swprintf_s(str, sizeof(str) / sizeof(TCHAR), L"l %d", ICS.table);		//结束了就离开了
				CMX_183_SEND_CODDING(str);                          //先离开,再加入
			}
			else{
				//ICS.table = 
				Sleep(1000);
				swprintf_s(str, sizeof(str) / sizeof(TCHAR), L"a %d", pDis->table);
				CMX_183_SEND_CODDING(str);
			}
		}

		LogOut(message);
		return TRUE;
	}

	//=====================================================================================
	//< 27    2 Red Rating 2716 天罡 长安棋社 〖棋研部〗 名譽社長 Black Rating 2703 地煞 NO NO NO >
	if (looking_at(message, _T("< @    @ Red Rating @ @ @ @ @ Black Rating @ @ @ @ @ >"))){
		return TRUE;
	}
	//=====================================================================================

	//< 42 Game Start >
	if (looking_at(message, _T("< @ Game Start >"))){
		
		GameReset(pDis,TRUE,TRUE, FALSE);

		//if(strstr(ICS.star_match[1],"Red")){
		//sprintf_s(pgn->Red,sizeof(pgn->Red),"%s",ICS.log_name);	

		if(wcsstr(pgn->Red,ICS.log_name) != NULL){

			swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%s"), _T("\n你重新执红,加入棋局了!"));
			//DispStatS(str);

			LogOut(str);

			ChangeGameMode(pDis,IcsPlayingWhite);

			IcsGameStart(pDis);

			Sleep(300);

			//GameReset(pDis,TRUE,TRUE, FALSE);

		}

		//else if(strstr(ICS.star_match[1],"Black")){

		if(wcsstr(pgn->Black,ICS.log_name) != NULL){

			swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%s"), _T("\n你重新执黑,加入棋局了!"));
			//DispStatS(str);

			LogOut(str);

			ChangeGameMode(pDis,IcsPlayingBlack);

			IcsGameStart(pDis);

			Sleep(300);

			//GameReset(pDis,TRUE,TRUE, FALSE);

		}
		else{
			//DispStatS(message);
			LogOut(message);
		}

		DisplayTitle(pDis);

		return TRUE;
		
		//return TRUE;
	}
	//=====================================================================================

	// < 25 梁山小蚂蚁(天罡) 2552 楚水战队 总政治部 副帮主 加 入 红 方 >
	if (looking_at(message, _T("< @ @(@) @ @ @ @ 加 入 @ @ >"))){
		if (wcsstr(ICS.star_match[7], _T("红"))){

			TrimIcsName(ICS.star_match[1]);

			swprintf_s(pgn->Red, sizeof(pgn->Red) / sizeof(TCHAR), _T("%s(%s)"), ICS.star_match[1], ICS.star_match[2]);
			pgn->Relo = _wtoi(ICS.star_match[3]);
			DisplayTitle(pDis);
			return TRUE;
		}
		else if (wcsstr(ICS.star_match[7], _T("黑"))){

			TrimIcsName(ICS.star_match[1]);

			swprintf_s(pgn->Black, sizeof(pgn->Red) / sizeof(TCHAR), _T("%s(%s)"), ICS.star_match[1], ICS.star_match[2]);
			pgn->Relo = _wtoi(ICS.star_match[3]);
			DisplayTitle(pDis);
			return TRUE;
		}
		else if (wcsstr(ICS.star_match[7], _T("观"))){
			return TRUE;
		}		
	}

	//=====================================================================================

	//< 56 地狱使者(9星) 2388 英雄无敌帮 玄武堂 理事 Join Black From Obs >
	if(looking_at(message,_T("< @ @(@) @ @ @ @ Join @ From @ >"))){
		if(wcsstr(ICS.star_match[7],_T("Red"))){

			TrimIcsName(ICS.star_match[1]);

			swprintf_s(pgn->Red, sizeof(pgn->Red) / sizeof(TCHAR), _T("%s(%s)"), ICS.star_match[1], ICS.star_match[2]);
			pgn->Relo = _wtoi(ICS.star_match[3]);
			DisplayTitle(pDis);
			return TRUE;
		}
		else if(wcsstr(ICS.star_match[7],_T("Black"))){

			TrimIcsName(ICS.star_match[1]);

			swprintf_s(pgn->Black, sizeof(pgn->Black) / sizeof(TCHAR), _T("%s(%s)"), ICS.star_match[1], ICS.star_match[2]);
			pgn->Belo = _wtoi(ICS.star_match[3]);
			DisplayTitle(pDis);
			return TRUE;
		}
	}
	//=====================================================================================

	//看一下记时方式
	TCHAR *ptime;
	if(ptime = wcsstr(message,_T("List "))){
		if (looking_at(ptime, _T("@ @ @ @ @ @ @ @ @ @ @ "))){

			//得到时间控制
			swprintf_s(pgn->RtimeControl, sizeof(pgn->RtimeControl) / sizeof(TCHAR), _T("%s"), (ICS.star_match[10]));
			swprintf_s(pgn->BtimeControl, sizeof(pgn->BtimeControl) / sizeof(TCHAR), _T("%s"), (ICS.star_match[10]));

			//得到红方的信息  //+		[0x2]	0x00568a20 "叽叽歪歪[-1&-1&-1]"	char [512]
			//要将这儿的信息去了哇

			TrimIcsName(ICS.star_match[2]);

			swprintf_s(pgn->Red, sizeof(pgn->Red) / sizeof(TCHAR), _T("%s(%s)"), ICS.star_match[2], ICS.star_match[3]);

			//elo
			pgn->Relo = _wtoi(ICS.star_match[4]);

			//得到黑方的信息
			TrimIcsName(ICS.star_match[7]);
			swprintf_s(pgn->Black, sizeof(pgn->Black) / sizeof(TCHAR), _T("%s(%s)"), ICS.star_match[6], ICS.star_match[7]);

			//elo
			pgn->Belo = _wtoi(ICS.star_match[8]);

			DisplayTitle(pDis);

			//初始化计时方式
			//局时，步时，读秒
			//if(looking_at(ICS.ICS_TimeMode,"@-@-@")){

			TCHAR* ps = pgn->RtimeControl;

			int t1 = _wtoi(ps);					//局时
			int t2 = 1;
			ps = wcsstr(ps, _T("-"));
			if(ps != NULL){
				ps++;
				t2 = _wtoi(ps);					//步时
			}

			int t3 = 1;
			ps = wcsstr(ps, _T("-"));
			if(ps != NULL){					    //读秒
				ps++;
				t3 = _wtoi(ps);
			}  

			//总是包干记时
			TimeDisp_t* pt = &pDis->TimeDisp[WHITE];

			pt->isBaoGan        = TRUE;

			pt->SetDepth		= 0;
			pt->inc             = 0;

			pt->SetStepTime     = 0;
			pt->movetime		= 0;

			pt->RemainTime		= t1 * 1000 * 60;	

			pgn->IcsStepTime    = t2 * 1000 * 60;
 
			pgn->IcsReadTime    = t3 * 1000;             //t3 总是秒

			
			if(pgn->IcsReadTime == 0){
				pgn->IcsReadTime = 3000;
			}

			pt->movetime        = pgn->IcsStepTime;

			pt->inc             = pgn->IcsReadTime;			//每步加时
			

			memcpy(&pDis->TimeDisp[BLACK],&pDis->TimeDisp[WHITE],sizeof(TimeDisp_t));

			return TRUE;
		}
	}

	//=====================================================================================

	//得到得分
	if (looking_at(message, _T("< @  Score @ : @ >"))){
		swprintf_s(pgn->round, sizeof(pgn->round) / sizeof(TCHAR), _T("%s:%s"), ICS.star_match[1], ICS.star_match[2]);
		return TRUE;
	}

	//=====================================================================================

	//得到棋步  //181  Move 51 1E-1J 661 1612 >		
	            // 40  Move 0 ---- 752 1200 >

	//if(looking_at(message,"< @ Move @")){
	if (looking_at(message, _T("< @  Move @ @ @ @ >"))){

		//LogOut(message);

		int num   = _wtoi(ICS.star_match[1]);

		if(pDis->pos->curStep != pDis->pos->gply){
			ToEndEvent(pDis);
		}

		//更新一下双方的时间
		int wtime = _wtoi(ICS.star_match[3]) * 1000;
		int btime = _wtoi(ICS.star_match[4]) * 1000;

		TimeDisp_t* pt = &pDis->TimeDisp[WHITE];

		pt->RemainTime = wtime;
		pt->movetime   = pgn->IcsStepTime;

		if(pt->RemainTime <= pgn->IcsReadTime * 6){

			pt->RemainTime      = pgn->IcsReadTime;		//读秒时间
			pt->SetStepTime     = pgn->IcsReadTime;
			pt->movetime        = pgn->IcsReadTime;
			pt->inc             = pgn->IcsReadTime * 4;

		}

		pt = &pDis->TimeDisp[BLACK];

		pt->RemainTime = btime;
		pt->movetime   = pgn->IcsStepTime;

		if(pt->RemainTime <= pgn->IcsReadTime * 6){

			pt->RemainTime      = pgn->IcsReadTime;		//读秒时间
			pt->SetStepTime     = pgn->IcsReadTime;
			pt->movetime        = pgn->IcsReadTime;
			pt->inc             = pgn->IcsReadTime * 4;
		}


		if(num != pDis->pos->gply + 1){
			//LogOut("\nICS 输入重复棋步!");
			//LogOut(&ICS.buf[1]);

			//这儿可能是游戏正式开始
			IcsGameStart(pDis);

			return TRUE;
		}

		int fromX  = ICS.star_match[2][0] - '0';
		int fromY  = 'J' - ICS.star_match[2][1];
		int toX    = ICS.star_match[2][3] - '0';
		int toY    = 'J' - ICS.star_match[2][4];

		if(IsMoveValid_FT(pDis->pos,fromX,fromY,toX,toY) == NormalMove){  
			//MakeMove(pDis,fromX,fromY,toX,toY,false); 
			//ShowMove(pDis,fromX,fromY,toX,toY);
			Sleep(1080);

			FinishMove(pDis,NormalMove,fromX,fromY,toX,toY); 			
			return TRUE;
		}
		else{
			SendToPlayerByColor(_T("\n解析开始棋步，棋步内容不正确!\n\n"), ColorSShout, FALSE);
		}
	}
	//}



	//=====================================================================================
	//sprintf_s(str,sizeof(str),"move %s %s",ICS.star_match[0],ICS.star_match[1]);
	if (looking_at(message, _T("move @ @"))){
		
		
		//LogOut(message);
		
		int num = _wtoi(ICS.star_match[0]);

		if(pDis->pos->curStep != pDis->pos->gply){
			ToEndEvent(pDis);
		}

		if(num != pDis->pos->gply + 1){
			LogOut(_T("\nICS 输入重复棋步!"));
		}
		else{
			int fromX  = ICS.star_match[1][0] - '0';
			int fromY  = 'J' - ICS.star_match[1][1];
			int toX    = ICS.star_match[1][3] - '0';
			int toY    = 'J' - ICS.star_match[1][4];

			if(IsMoveValid_FT(pDis->pos,fromX,fromY,toX,toY) == NormalMove){  
				//Sleep(150);
				MakeMove(pDis,fromX,fromY,toX,toY,false); 
				ShowMove(pDis,fromX,fromY,toX,toY);
				return TRUE;
			}
			else{
				SendToPlayerByColor(_T("\n解析开始棋步，棋步内容不正确!\n\n"), ColorSShout, FALSE);
			}
		}

		return TRUE;
	}
	//=====================================================================================
	//player 1 淡看风云 9段 2047 北丐10关 0 英雄同盟会
	//sprintf_s(str,sizeof(str),"player %d %s\n",ICS.count, &ICS.buf[1]);
	//得到player


	if (looking_at(message, _T("player @"))){
		if (looking_at(message, _T("player @  @ @ @ @ @ @"))){
			int count = _wtoi(ICS.star_match[0]);

			if(count == 1){				//红方

				////将  "[" 去了
				//char *ptmp; 
				//ptmp = strstr(ICS.star_match[1],"[");
				//if(ptmp){
				//}

				TrimIcsName(ICS.star_match[1]);

				swprintf_s(pgn->Red, sizeof(pgn->Red) / sizeof(TCHAR), _T("%s(%s)"), ICS.star_match[1], ICS.star_match[2]);
				pgn->Relo = _wtoi(ICS.star_match[3]);
			}
			else if(count == 2){        //黑方

				TrimIcsName(ICS.star_match[1]);

				swprintf_s(pgn->Black, sizeof(pgn->Black) / sizeof(TCHAR), _T("%s(%s)"), ICS.star_match[1], ICS.star_match[2]);
				pgn->Belo = _wtoi(ICS.star_match[3]);
			}		
			DisplayTitle(pDis);
			return TRUE;
		}

		else if (looking_at(message, _T("player @ @ @ @ @ @ @"))){
			int count = _wtoi(ICS.star_match[0]);
			return TRUE;
		}
		else {

		}
	}

	//=====================================================================================
    //< 40   # 剑之神 在 *飞刀擂台* 第1次 成 功 卫 冕! >

	if (looking_at(message, _T("< 40   # @ "))){
		LogOut(message+6);
		return TRUE;
	}

	//< 123 *          取消对局
	if (looking_at(message, _T("< @ *          取消对局"))){

		if(ICS.cont_dalei == TRUE){  //如果是连续打擂
			//1,再加入棋局,
			//if(ICS.stage == 0){
			//	sprintf_s(str,sizeof(str),"j %d", curSel);
			//	table = curSel;
			//}
			//else{
			//	sprintf_s(str,sizeof(str),"j %d %d",ICS.stage,curSel);
			//	table = (ICS.stage-1)*20 + curSel;
			//}

             /*			Sleep(1000);

			CMX_183_SEND_CODDING("j");		*/			

			//2,再同意对局

			//新建一局
			//GameReset(pDis,TRUE,TRUE,FALSE);

			if(pDis->IcsGameStartAlready == FALSE){            //如果还没有开始,就按同意
				Sleep(1000);                                   //
				swprintf_s(str, sizeof(str)/sizeof(TCHAR), L"a %d", pDis->table);
				CMX_183_SEND_CODDING(str);
			}
		}
		return TRUE;
	}

	//< 123 # 注意:如果你不想与对手对局,你可以在开局阶段(走子不超过10步并且对局时间不超过5分钟)取消对局[不影响双方积分]
	if (looking_at(message, _T("< @ # @:"))){
		LogOut(message);
		return TRUE;
	}

	//* 对不起:此关已经没有空位了，请稍后再试!

	if (looking_at(message, _T("< @ * 对不起:@"))){
		Sleep(1000);                                 //
		swprintf_s(str, sizeof(str) / sizeof(TCHAR), L"%hs", "j");           // 再一次加入
		CMX_183_SEND_CODDING(str);
	}
	//< 123 # 方法:在桌右侧观战玩家列表选中对手名字后点鼠标右键选“请你离座”即可[黄金会员适用][需要扣除500碎银]
	//if(looking_at(message,"< @ # @:")){
	//	return TRUE;
	//}

	return FALSE;
}



void TrimIcsName(TCHAR* Name){

	TCHAR *pc = wcsstr(Name,_T("["));

	if(pc){
		*pc = 0;
	}
}