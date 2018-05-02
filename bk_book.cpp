#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"





BOOL Is_BanMove_By_Pos_Now(dispboard_t* pDis){
    
	position_t* nowpos = pDis->pos;
	nowpos->gply++;
	int res = ban_repeat(nowpos);
	nowpos->gply --;

	switch(res){
		case REPEAT_TRUE:      //重复走步
			//LogOut("\n双方走步重复了!\n");
			return false;
			break;
		case REPEAT_NO:			//不吃子超过了120步
			//LogOut("\n双方REPEAT_NO!");
			return false;
			break;
		case REPEAT_BAN_OTHER:
			//LogOut(ColorSeek,"不对,对方犯规,对方连将或连捉!",false);
			LogOut(_T("\n不对,对方犯规,对方连将或连捉! 此步从开局库中去除\n"));
			LogOut(_T("REPEAT_BAN_OTHER!"));
			return true;
			break;
		//case BLACK_CHECK_BAN:
		case REPEAT_BAN_ME:
			LogOut(_T("\n你又在连将或连捉了! ! 此步从开局库中不去除"));
			LogOut(_T("REPEAT_BAN_OTHER!"));
			return false;
			break;
		default:
			break;
	}

	return false;
}

BOOL isWhiteGo_By_FaceInfo(uint8* f33){

	switch(f33[0]){
		case 'f':
		case 'g':
		case 'h':

		case 'o':
		case 'p':
		case 'q':

		case 'x':
		case 'y':
		case 'z':
			return 1;  //return true;
		case '#':
		case '$':
		case '%':

		case ',':
		case '-':
		case '.':

		case '5':
		case '6':
		case '7':
			return 0;
		default:
			LogOut(_T("\n备份棋库局面出错,王的位置有错"));
			return 2;
	}

	return 2;
}

int Book_Back_Up(DB* dst, DB* src){
	//将src 中的棋步全部保存到dst中

	//用光标来保存
	int ret;

	DBC *cur;

	src->cursor(src,NULL, &cur,0);

	DBT key, data;
	
    int num = 0;

	do{
		memset(&key, 0, sizeof(DBT));
		memset(&data,0, sizeof(DBT));

		ret = cur->c_get(cur, &key, &data,DB_NEXT);                  //得到一个局面

		if(ret != 0){
			break;
		}

		//key.data  = bft->f33;

		//struct book_face_t {
		//	uint8  f33[33];
		//	book_face_info_t info[1];
		//};

		uint8* f33 = (uint8*)key.data;


		
		book_face_info_t *binfo = (book_face_info_t*)data.data;

	
	    //再在这儿判断一下是不是好的棋步,这儿不能用STEP来判断了
		
		int isw = isWhiteGo_By_FaceInfo(f33);

		if(isw  == 1){
			if(binfo->result < BOOK_BALANCE){
				continue;
			}
		}
		else if(isw == 0){
			if(binfo->result > BOOK_BALANCE){
				continue;
			}
		}
		else if (isw == 2){
			continue;
		}


		//写入相应的数据
		ret = dst->put(dst, NULL, &key, &data, 0);

		if (ret){
			LogOut(_T("\n不能写入局面数据到备份数据库中!!\n"));
			break;
		}
		num++;

	}while(true);

	if(cur != NULL){
		ret = cur->c_close(cur);
	}

	TCHAR buf[512];
	swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), _T("\n成功备份了 %d 局面!!\n"), num);

	LogOut(buf);

	return ret;
}



BOOL is_book_face_ok(book_face_t *bft){
	if(abs(bft->info->result) > 2){
		return FALSE;
	}
	//if(bft->info->step > 250){
	//	return FALSE;
	//}
	//if(bft->info->rate > 100){
	//	return FALSE;
	//}
	if(abs(bft->info->isuse) > 1){
		return FALSE;
	}
	return TRUE;
}

//////////////////////////////////////////////////
/// 只保存当前的局面得分到棋库中去。
void UpDataOneFaceEvent(dispboard_t* pDis, DB *db){

	book_face_t last_face[1];
	last_face->info->result = BOOK_NOT_RESULT;

	//last_face->info->rate = 50;
	last_face->info->isuse = 1;
	//last_face->info->stepp = 60;

	position_t pos[1];

	memcpy(pos, pDis->pos, sizeof(position_t));

	//得到得分
	if (false){
	}
	else if (IsDlgButtonChecked(HWND_SAVE, IDC_VERY_GOOD) == BST_CHECKED){
		last_face->info->result = BOOK_VERY_GOOD;
	}
	else if (IsDlgButtonChecked(HWND_SAVE, IDC_LIT_GOOD) == BST_CHECKED){
		last_face->info->result = BOOK_LIT_GOOD;
	}
	else if (IsDlgButtonChecked(HWND_SAVE, IDC_BALANCE) == BST_CHECKED){
		last_face->info->result = BOOK_BALANCE;
	}
	else if (IsDlgButtonChecked(HWND_SAVE, IDC_LIT_BAD) == BST_CHECKED){
		last_face->info->result = BOOK_LIT_BAD;
	}
	else if (IsDlgButtonChecked(HWND_SAVE, IDC_VERY_BAD) == BST_CHECKED){
		last_face->info->result = BOOK_VERY_BAD;
	}

	if (last_face->info->result == BOOK_NOT_RESULT){
		LogOut(_T("你还没有设定当前局面的得分!!\n"));
		return;
	}

	GetMirrorOnlyB33(pos, last_face->f33);
	if (!bk_SaveBookInfo(last_face, db)){
		LogOut(L"\n保存单个局面成功了！");
	}//先将当前的保存一下
	else{
		LogOut(L"\n保存单个局面失败了！");
	}

	

	return;

}


//得到当前棋库的棋步信息
int bk_GetBookInfo(book_face_t* bft, DB *db){
	
	int ret;

	DBT key,data;
	memset(&key, 0, sizeof(DBT));
	memset(&data,0, sizeof(DBT));

	//memset(bft->info,0,sizeof(book_face_info_t));

	bft->info->result = BOOK_NOT_RESULT;
	//bft->info->rate   = 0;
	bft->info->isuse  = 0;

	key.data  = bft->f33;
	key.size  = 33;
	data.ulen = sizeof(book_face_info_t);

	ret = db->get(db,NULL,&key,&data,0);

	if(ret == 0){
		book_face_info_t *binfo = (book_face_info_t*)data.data;

		bft->info->isuse  = binfo->isuse;
		//bft->info->rate   = binfo->rate;
		bft->info->result = binfo->result;
		//bft->info->step   = binfo->step;
	}
	//else{
	//	bft->info->result = BOOK_NOT_RESULT;
	//}

	return ret;
}

//当前是不是有棋库棋步可走
int HaveBookMoveInDB(dispboard_t* pDis){

	if(pDis->book_num > 0){  //这儿不随机走步

#ifdef USE_RAND_BOOK_MOVE		
		int ra = 0;
		srand((int)time(0));
		ra = rand() % pDis->book_num;
		return pDis->book_move[ra];
#else
		return pDis->book_move[pDis->book_max_num];
#endif

	}
	else{
		return 0;
	}
}


//通过当前局面的后续着法得到得分
int GetPosBookScoreByAllNextPos(position_t *pos, DB *db){	
	int preScore;

	int  preSide   = pos->side;

	if(preSide == WHITE){			//当前是红走的话，则后面的分越大越好
		preScore = -BOOK_NOT_RESULT;
	}
	else{			                //当前是黑走的话，取后面的最小分
		preScore = BOOK_NOT_RESULT;
	}

	//产生所有的走步
	gen_legal_moves(pos);

	while(pos->pMend > pos->all_move){

		pos->pMend--;

		
		if (move_is_legal(pos, pos->pMend->move) == FALSE){		//走步不合法
			continue;
		}
		

		MakePosMoveOnly(pos,pos->pMend->move);			//走一步，仅更新curStep

		GetMirrorOnlyB33(pos,pos->book_face->f33);

		//pos->book_face->info->step = pos->curStep;
		bk_GetBookInfo(pos->book_face,db);

		int res = pos->book_face->info->result;

		if((res != BOOK_NOT_RESULT)){
			//if(pos->book_face->info->step == pos->curStep){
				if(preSide == WHITE){
					if(res > preScore){
						preScore = res;
						if(res == BOOK_VERY_GOOD){
							UnMakePosMoveOnly(pos);
							break;
						}
					}
				}
				else{
					if(res < preScore){
						preScore = res;
						if(res == BOOK_VERY_BAD){
							UnMakePosMoveOnly(pos);
							break;
						}
					}
				}
			//}
		}

		UnMakePosMoveOnly(pos);
	}

	if(abs(preScore) == BOOK_NOT_RESULT){
		return BOOK_NOT_RESULT;
	}
	else{
		return preScore;
	}
}

int bk_SaveBookInfo(book_face_t* bft, DB *db){
	
	int ret;
	
	//1

	if(is_book_face_ok(bft) == FALSE){
		LogOut((TCHAR*)(bft->f33));
		LogOut(_T("\nDB_ERR: 当前要存入的棋步不正确！！\n"));
		return -1;
	}

	//2 	
	// 检查当前存入的棋步的STEP是不是大于当前棋库中已有的，
	//如有，说明是重复步，不能存入

	//book_face_info_t pre = bft->info[0];

	//int oldStep = 
	//
	//bk_GetBookInfo(bft,db);

	//if(bft->info->step != 0){
	//	if(bft->info->step < pre.step){
	//		LogOut("当前棋库中已有此棋步，且步数比当前要保存的小\n");
	//		LogOut((char*)bft->f33);
	//		return -1;
	//	}
	//}

	//bft->info[0] = pre;


	//3

	DBT key,data;
	memset(&key, 0, sizeof(DBT));
	memset(&data,0, sizeof(DBT));

    //
	key.data	= bft->f33;
	key.size	= 33;
	data.data   = &bft->info[0];
	data.size	= sizeof(book_face_info_t);

	ret = db->put(db,NULL,&key,&data,0);


	db->sync(db,0);

	return ret;
}


//根据棋库的得分，得到结果字符串
TCHAR* BookScoreToChar(int score){

	switch (score){
	case BOOK_VERY_GOOD:
		return _T("红大优");
		break;
	case BOOK_LIT_GOOD:
		return _T("红略优");
		break;
	case BOOK_BALANCE:
		return _T("  均势");
		break;
	case BOOK_LIT_BAD:
		return _T("黑略优");
		break;
	case BOOK_VERY_BAD:
		return _T("黑大优");
		break;
	default:
		return _T(" ");
		break;
	}	
}


void UpdateBookResult(dispboard_t * pDis, DB *db){


	position_t pos[1];
	book_face_t last_face[1];
	book_face_t tmp_face[1];
	
	memcpy(pos,pDis->pos,sizeof(position_t));	

	last_face->info->result = BOOK_NOT_RESULT;

	//得到得分
	if(false){
	}
	else if (IsDlgButtonChecked(HWND_SAVE, IDC_VERY_GOOD) == BST_CHECKED){
		last_face->info->result = BOOK_VERY_GOOD;
	}
	else if (IsDlgButtonChecked(HWND_SAVE, IDC_LIT_GOOD) == BST_CHECKED){
		last_face->info->result = BOOK_LIT_GOOD;
	}
	else if (IsDlgButtonChecked(HWND_SAVE, IDC_BALANCE) == BST_CHECKED){
		last_face->info->result = BOOK_BALANCE;
	}
	else if (IsDlgButtonChecked(HWND_SAVE, IDC_LIT_BAD) == BST_CHECKED){
		last_face->info->result = BOOK_LIT_BAD;
	}
	else if (IsDlgButtonChecked(HWND_SAVE, IDC_VERY_BAD) == BST_CHECKED){
		last_face->info->result = BOOK_VERY_BAD;
	}

	if(last_face->info->result == BOOK_NOT_RESULT){
		LogOut(_T("你还没有设定当前局面的得分!!\n"));
		return;
	}

	last_face->info->isuse = FALSE;

	
	//得到当前的B28

	GetMirrorOnlyB33(pos,last_face->f33);

	int nextScore = GetPosBookScoreByAllNextPos(pos,db);

	int  num = 0;

	//int oldStep   = pos->curStep; 

	//face->info->isuse = lastIsUse;

	

	if(nextScore == BOOK_NOT_RESULT){
		//后面没有得分了，要全部更新，从后面往前

		//tmp_face = last_face;

		memcpy(tmp_face,last_face,sizeof(book_face_t));

		bk_SaveBookInfo(tmp_face,db);		//先将当前的保存一下

		while((pos->curStep) > 0){


			UnMakePosMoveOnly(pos);

			GetMirrorOnlyB33(pos,tmp_face->f33);

			//tmp_face->info->step = pos->curStep;
          
			bk_GetBookInfo(tmp_face,db);

			nextScore = GetPosBookScoreByAllNextPos(pos,db);

			if(nextScore == BOOK_NOT_RESULT){
				LogOut(_T("出错了，存入的棋步找不到！！"));
				break;
			}

			if(tmp_face->info->result == BOOK_NOT_RESULT){		//这个也是新局面
				//tmp_face->info->step		= pos->curStep;
				tmp_face->info->isuse		= last_face->info->isuse;
				//tmp_face->info->rate		= last_face->info->rate;
			}

			if(pos->side == WHITE){		//如果这个局面太差，则不要rate,不要isuse
				if(nextScore == BOOK_VERY_GOOD){
					tmp_face->info->isuse		= 0;
					//tmp_face->info->rate		= 0;
				}
				else if(nextScore <= BOOK_BALANCE){
					tmp_face->info->isuse		= 1;
				}
			}
			else{
				if(nextScore == BOOK_VERY_BAD){
					tmp_face->info->isuse		= 0;
					//tmp_face->info->rate		= 0;
				}
				else if(nextScore >= BOOK_BALANCE){
					tmp_face->info->isuse		= 1;
				}
			}


			tmp_face->info->result       = nextScore;
			bk_SaveBookInfo(tmp_face,db);			

			num++;	
			
		}


		//1,得到当前的局面的信息

	}
	else{		
		last_face->info->result = nextScore;
		bk_SaveBookInfo(last_face,db);			//只要更新当前的一个局面,因为有后面的分

		num++;
	}

    
	TCHAR buf[128];

	swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), _T("\n更新了 %d 个棋库局面!!\n"), num);

	LogOut(buf);

	//SendToPlayerByColor(buf,ColorSeek,FALSE);

};

//根据棋库得分，更新相应的按钮
void UpDateBookScoreButton(int score){
	//SendDlgItemMessage(HWND_BOOK,IDC_VERY_GOOD,1,0);

	//1,先将所有的按钮弹出再说
	SendDlgItemMessage(HWND_SAVE, IDC_VERY_GOOD, BM_SETCHECK, 0, 0);
	SendDlgItemMessage(HWND_SAVE, IDC_LIT_GOOD, BM_SETCHECK, 0, 0);
	SendDlgItemMessage(HWND_SAVE, IDC_BALANCE, BM_SETCHECK, 0, 0);
	SendDlgItemMessage(HWND_SAVE, IDC_LIT_BAD, BM_SETCHECK, 0, 0);
	SendDlgItemMessage(HWND_SAVE, IDC_VERY_BAD, BM_SETCHECK, 0, 0);

	if(false){
	}
     
	else if(score == BOOK_VERY_GOOD){

		SendDlgItemMessage(HWND_SAVE, IDC_VERY_GOOD, BM_SETCHECK, 1, 0);
	}
	else if(score == BOOK_LIT_GOOD){

		SendDlgItemMessage(HWND_SAVE, IDC_LIT_GOOD, BM_SETCHECK, 1, 0);
	}

	else if(score == BOOK_BALANCE){

		SendDlgItemMessage(HWND_SAVE, IDC_BALANCE, BM_SETCHECK, 1, 0);
	}

	else if(score == BOOK_LIT_BAD){

		SendDlgItemMessage(HWND_SAVE, IDC_LIT_BAD, BM_SETCHECK, 1, 0);
	}

	else if(score == BOOK_VERY_BAD){

		SendDlgItemMessage(HWND_SAVE, IDC_VERY_BAD, BM_SETCHECK, 1, 0);
	}
}


int GetValByBookFaceInfo(book_face_info_t *pFinfo, int side){

	int val = 0;

	int pj  = pFinfo->result;
	

	if(side == BLACK){
		val =  (+ pj * 50 * 100 / 50)   ;
	}
	else{
		val =  (- pj * 50 * 100 / 50)   ;
	}

	return val;
}

BOOL FillBookbyPos(dispboard_t* pDis, DB *db){		//根据局面填充book_列表

	//return FALSE;


	if(pDis->hwndThis == NULL){
		return FALSE;
	}
	position_t *pos = pDis->pos;


	pDis->book_num		= 0;					//棋步数量
	//pDis->book_max_num	= 0;

	int max_book_val = -1;


	ThStat.isFillQk = TRUE;


	//f
	if(MST->Book_Init_Ok == FALSE){
		return FALSE;
	}


	//产生所有的走步
	gen_legal_moves(pos);


	LogOut(_T("\n\n棋库棋步列表\n---------------------"));

	int id = 0;

	bool have_next = FALSE;
	while(pos->pMend > pos->all_move){

		pos->pMend--;

		
		if (move_is_legal(pos, pos->pMend->move) == FALSE){
			continue;
		}
		
		
		//pos->pMend--;

		//得到走步的名称
		//GetMoveName(pDis,pos,pos->pMend->move, appData.moveType);

		TCHAR szStepName[16];

		GetMoveNameSimple(pDis->pos,szStepName,pos->pMend->move, appData.moveType);

		//if (pos->pMend->move != 0x6a4a7) continue;

		MakePosMoveOnly(pos,pos->pMend->move);    

		GetMirrorOnlyB33(pos,pos->book_face->f33);

		//pos->book_face->info->step = pos->curStep;

		bk_GetBookInfo(pos->book_face,db);

		int res = pos->book_face->info->result;

		if(res != BOOK_NOT_RESULT){

			//if(pos->book_face->info->step >= pos->curStep){ //走步比较小
			if(Is_BanMove_By_Pos_Now(pDis) == false){  //当前已走步了, 就可以直接判断是不是禁止步了
				have_next = TRUE;
				if(pos->book_face->info->isuse == TRUE ){		//这个棋步使用了						
						if((pos->side == WHITE && res != BOOK_VERY_GOOD && res != BOOK_LIT_GOOD )		//不太好的棋步也不走
							||(pos->side == BLACK && res != BOOK_VERY_BAD && res != BOOK_LIT_BAD )){

								int tval = GetValByBookFaceInfo(pos->book_face->info, pos->side);

								pDis->book_move[pDis->book_num] = pos->pMend->move;	
								pDis->book_val[pDis->book_num]  = tval;

								if(tval > max_book_val){
									pDis->book_num = 0;               // 重新开始填充棋库棋步
									max_book_val = tval;									
								}

								if (tval == max_book_val){
									pDis->book_move[pDis->book_num] = pos->pMend->move;
									pDis->book_val[pDis->book_num] = tval;
									pDis->book_num++;
								}
						}
				}
			}

			/////////////////////////////////////////////////////////////////////////
			// 显示到日志中去 
			TCHAR buf[256]; 
			swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), _T("\n%s ->  %s"),
				szStepName, BookScoreToChar(res));
			LogOut(buf);
		}

		id++;


		//-----------------------------
		UnMakePosMoveOnly(pos);
	}



	//if(have_next){			//当前棋步有后续步，就要将得分按钮不能按下

	//	EnableWindow(GetDlgItem(HWND_SAVE, IDC_VERY_GOOD), FALSE);
	//	EnableWindow(GetDlgItem(HWND_SAVE, IDC_LIT_GOOD), FALSE);
	//	EnableWindow(GetDlgItem(HWND_SAVE, IDC_BALANCE), FALSE);
	//	EnableWindow(GetDlgItem(HWND_SAVE, IDC_LIT_BAD), FALSE);
	//	EnableWindow(GetDlgItem(HWND_SAVE, IDC_VERY_BAD), FALSE);
	//	
	//}
	//else{
	//	EnableWindow(GetDlgItem(HWND_SAVE, IDC_VERY_GOOD), TRUE);
	//	EnableWindow(GetDlgItem(HWND_SAVE, IDC_LIT_GOOD), TRUE);
	//	EnableWindow(GetDlgItem(HWND_SAVE, IDC_BALANCE), TRUE);
	//	EnableWindow(GetDlgItem(HWND_SAVE, IDC_LIT_BAD), TRUE);
	//	EnableWindow(GetDlgItem(HWND_SAVE, IDC_VERY_BAD), TRUE);
	//}

	//1,首先得到当前局面的信息
	GetMirrorOnlyB33(pos,pos->book_face->f33);
	//pos->book_face->info->step = pos->curStep;

	bk_GetBookInfo(pos->book_face,db);

	//是不是允许使用
	SendDlgItemMessage(HWND_SAVE, IDC_BOOK_CAN_USE, BM_SETCHECK, pos->book_face->info->isuse, 0);

	pDis->pos->His[pDis->pos->curStep].search_score = 0;
	if(have_next == TRUE){
		int ret = GetPosBookScoreByAllNextPos(pos, db);
		UpDateBookScoreButton(ret);		
		int maxsc = ret * 200;
		if(pos->side != WHITE){
			maxsc *= -1;
		}
		pDis->pos->His[pDis->pos->curStep].search_score = (sint16)maxsc;
		HDCDrawChart(TAB.dlgScore, pDis, NULL, true);
	}
	else{
		UpDateBookScoreButton(pos->book_face->info->result);
	}

	

	SetDlgItemInt(HWND_SAVE, IDC_GPLY, pos->curStep, 0);


	ThStat.isFillQk = FALSE;

	return TRUE;  
};

