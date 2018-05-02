#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"

#include <sys/types.h>
#include <sys/timeb.h>



//从数据库中得到一局已校对过的棋局
BOOL PgnGetOneCheckedGameFromSql(dispboard_t *pDis, sqlite3 *db){

	//1,打开Sqlite
	//sqlite3 *db_pgn;
    char    *szErrMsg       = 0;
    int      nrow           = 0;
    int      ncolumn        = 0;
    int      rc             = -1;
    char    **azResult;
    char     sql[4096];

	int      id = -1;

	//rc = SqliteOpenDataBase(&db_pgn,L3_DB_PGN);

	//if(rc != SQLITE_OK) return rc;

	sprintf_s(sql,sizeof(sql),
		"SELECT pgnID FROM pgn WHERE isChecked = 1 AND isLearned <> 1 ORDER BY pgnID DESC");

	//"SELECT pgnID FROM pgn ORDER BY pgnID DESC");

	rc = sqlite3_get_table(db,sql,&azResult,&nrow,&ncolumn,&szErrMsg);

	if(rc != SQLITE_OK){
		LogOuts(szErrMsg);
		sqlite3_free(szErrMsg);
		//sqlite3_close(db_pgn);
		return rc;
	}

	for(int k = 1; k <= nrow; k++){
		id = atoi(azResult[ncolumn + 0]);
		break;
	}

	sqlite3_free_table(azResult);

	//sqlite3_close(db_pgn);

	if(id == -1){
		return id;
	}

	return PgnGetGameInfoFromSqliteById(pDis,id,db);

}

////////////////////////////////////////////////////////////////////////////
// 从数据库中得到总的对局数
int PgnTotalGameNumFromSql(sqlite3 *db){

	//1,打开Sqlite
	//sqlite3 *db_pgn;
	char    *szErrMsg = 0;
	int      nrow = 0;
	int      ncolumn = 0;
	int      rc = -1;
	char    **azResult;
	char     sql[4096];

	int      result;


	sprintf_s(sql, sizeof(sql),
		"SELECT COUNT(*) FROM pgn");

	rc = sqlite3_get_table(db, sql, &azResult, &nrow, &ncolumn, &szErrMsg);

	if (rc != SQLITE_OK){
		LogOuts(szErrMsg);
		sqlite3_free(szErrMsg);
		//sqlite3_close(db_pgn);
		return rc;
	}
	result = atoi(azResult[1]);

	sqlite3_free_table(azResult);

	return result;
}

////////////////////////////////////////////////////////////////////////////
// 从数据库中得到还没有校对的对局数
int PgnTotalGameUncheckNumFromSql(sqlite3 *db){

	//1,打开Sqlite
	//sqlite3 *db_pgn;
	char    *szErrMsg = 0;
	int      nrow = 0;
	int      ncolumn = 0;
	int      rc = -1;
	char    **azResult;
	char     sql[4096];

	int      result;


	sprintf_s(sql, sizeof(sql),
		"SELECT COUNT(*) FROM pgn WHERE isChecked = 0");

	rc = sqlite3_get_table(db, sql, &azResult, &nrow, &ncolumn, &szErrMsg);

	if (rc != SQLITE_OK){
		LogOuts(szErrMsg);
		sqlite3_free(szErrMsg);
		//sqlite3_close(db_pgn);
		return rc;
	}

	result = atoi(azResult[1]);

	sqlite3_free_table(azResult);

	return result;
}

/////////////////////////////////////////////////////////
// 
BOOL GetCheckedqipuAndLearn(dispboard_t * pDis, sqlite3 *db){

	TCHAR buf[512];
	int rc;
	//1, 首先得到一局检查过的棋局
	while(ThStat.isFillQk){
		Sleep(100);
	};
	rc = PgnGetOneCheckedGameFromSql(pDis,db);

	if(rc != SQLITE_OK){
		LogOut(_T("\n当前棋库已没有已校对的棋局了\n"));
		return rc;
	}

	if(pDis->pgn->isChecked == 0 || pDis->pgn->isLearned == 1){
		LogOut(_T("\n棋库有错，请检查一下\n"));
		return -1;
	}

	//2, 再将FEN展开一下
	swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), _T("\n正在学习> ID:%d,N:%s,A:%s"),
		pDis->pgn->pid,pDis->pgn->note,pDis->pgn->pevent);

	LogOut(buf);

	if(PgnFenToPos(pDis,false) == FALSE){
		LogOut(_T("\n残局暂不能学习!!"));
		goto OutLearn;
	}

	//3, 开始学习棋步
	PGN*        pgn    = pDis->pgn;
	position_t* pos    = pDis->pos;

	if(pgn->score == BOOK_NOT_RESULT){
		LogOut(_T("\n学习的棋局还没有得分"));
		return -1;
	}

	//4, 

    book_face_t last_face[1];
	book_face_t tmp_face[1];
	
	//last_face->info->rate  = pgn->rate;	
	//last_face->info->step  = pos->curStep;
	last_face->info->isuse = 1;

	

	//得到当前的B32
	GetMirrorOnlyB33(pos,last_face->f33);

	while(ThStat.isFillQk){
		Sleep(100);
	};
	int nextScore = GetPosBookScoreByAllNextPos(pos,MST->book);

	int num = 0;

	if(nextScore == BOOK_NOT_RESULT){
		last_face->info->result = pgn->score;
		nextScore = pgn->score;
	}
	else{
		last_face->info->result = nextScore;
	}


	memcpy(tmp_face,last_face,sizeof(book_face_t));

	//if(pos->curStep > BOOK_LEARN_NUM){			//只有小于BOOK_LEARN_NUM棋步才能存入棋库
	//	bk_SaveBookInfo(tmp_face,MST->book);		//先将当前的保存一下
	//}


	//typedef enum {
	//	BOOK_VERY_BAD	= -2, 
	//	BOOK_LIT_BAD	= -1, 
	//	BOOK_BALANCE	=  0,
	//	BOOK_LIT_GOOD	=  1,
	//	BOOK_VERY_GOOD  =  2,
	//	BOOK_NOT_RESULT =  8
	//}Book_Sc;


	while(pos->curStep >= BOOK_MOVE_LEARN_PLY){
		UnMakePosMoveOnly(pos);
		tmp_face->info->result = tmp_face->info->result; //好象结果不应改变
	}

	//tmp_face->info->step = pos->curStep;
	GetMirrorOnlyB33(pos,tmp_face->f33);

	while(ThStat.isFillQk){
		Sleep(100);
	};
	bk_SaveBookInfo(tmp_face,MST->book);		//先将当前的保存一下

	while(pos->curStep > 0){

		UnMakePosMoveOnly(pos);
		GetMirrorOnlyB33(pos,tmp_face->f33);

		//tmp_face->info->step = pos->curStep;

		while(ThStat.isFillQk){
			Sleep(100);
		};
		bk_GetBookInfo(tmp_face,MST->book);				//得到原先存入的局面信息

		//tmp_face->info->step = pos->curStep;			//步子还是原来的

		while(ThStat.isFillQk){
			Sleep(100);
		};
		nextScore = GetPosBookScoreByAllNextPos(pos,MST->book);

		if(nextScore == BOOK_NOT_RESULT){
			LogOut(_T("出错了，存入的棋步找不到!!"));
			return -1;
		}
		
		if(pos->side == WHITE){		//如果这个局面太差，则不要rate,不要isuse
			if(nextScore == BOOK_VERY_GOOD){
				tmp_face->info->isuse = 0;
				//tmp_face->info->rate  = 0;
			}
			else if(nextScore <= BOOK_BALANCE){
				tmp_face->info->isuse = 1;
				//if(tmp_face->info->rate == 0){
				//	tmp_face->info->rate = 1;
				//}
			}			
		}
		else{
			if(nextScore == BOOK_VERY_BAD){
				tmp_face->info->isuse		= 0;
				//tmp_face->info->rate		= 0;
			}
			else if(nextScore >= BOOK_BALANCE){
				tmp_face->info->isuse		= 1;
				//if(tmp_face->info->rate == 0){
				//	tmp_face->info->rate = 1;
				//}
			}
		}
		tmp_face->info->result = nextScore;

		while(ThStat.isFillQk){
			Sleep(100);
		};
		bk_SaveBookInfo(tmp_face,MST->book);		//先将当前的保存一下

		num++;
	}


	//
	swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), _T("\n 此局共学习：%d 个局面"), num);
	LogOut(buf);

OutLearn:

	//   将这局变成学习过了
	pDis->pgn->isLearned = 1;

	while(ThStat.isFillQk){
		Sleep(100);
	};
    return PgnUpdateGameToSqlite(pDis,db);

}

/////////////////////////////////////////////////////////
//学习所有在棋库中保存的棋局,已检查过了
DWORD WINAPI 
LearnAllFileGameThread(LPVOID lpParam){

    sqlite3 *db;
	TCHAR buf[256];

	int rc = SqliteOpenDataBase(&db,L3_DB_PGN);

	if(rc != SQLITE_OK){
		LogOut(_T("\n出错啦，不能打开棋局数据库!\n"));
        goto OutLearn;
	}

	int num = 0;

	dispboard_t pDis[1];

	//pDis->gameMode   = PlayFromGameFile;

	ChangeGameMode(pDis,PlayFromGameFile);
	pDis->matchMode  = TRUE;						//这样走步就不会发声了

    //Thread_Stat |= TH_Learning;						//当前正在学习
	ThStat.isLearn  = TRUE;
	ThStat.outLearn = FALSE;


	//if(Thread_Stat & TH_OutLearningOK){
	//	Thread_Stat ^= TH_OutLearningOK;           //
	//}

	while(GetCheckedqipuAndLearn(pDis,db) == SQLITE_OK && ThStat.isLearn == TRUE){
		num++;
	}

OutLearn:


	//if(Thread_Stat & TH_Learning){
	//	Thread_Stat ^= TH_Learning;
	//}

	if(ThStat.isLearn)	{
		ThStat.isLearn = FALSE;
	};


	//一定要关了棋局数据库
	sqlite3_close(db);

	swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), _T("\n学习完成，共学习了：%d 棋局!\n"), num);

	LogOut(buf);

	//TH_OutLearningOK
    
	//Thread_Stat |= TH_OutLearningOK;    //已成功退出了学习状态
	ThStat.outLearn = TRUE;

	return 0;
}

/////////////////////////////////////////////////////////
//打开自动学习线程
void AutoLearnEvent(void){
	DWORD dwThreadId,dwThrdParam = 1;
	HANDLE hImport = CreateThread(
		NULL,
		NULL,
		LearnAllFileGameThread,
		&dwThrdParam,
		0,
		&dwThreadId);

	if(hImport == NULL){
		SendToPlayerByColor(_T("\n初始化学习棋局线程失败!\n"), ColorShout, FALSE);
	}
	else{
		SendToPlayerByColor(_T("\n初始化学习棋局线程成功!\n"), ColorShout, TRUE);
	}
}


