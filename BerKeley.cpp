#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"







// db_err_handle

void BD_my_error_handler(const DB_ENV* env, const char *error_prefix, const char *msg){
    if(msg != NULL){
        //printf("info DB_ERR: %s %s\n",error_prefix,msg); 

		LogOut(_T("DB_ERR: "));
		LogOuts((char*)error_prefix);
		LogOuts((char*)msg);
    }
}

int BD_initEnv2(){     //初始化环境

#define	DATABASE "access4.db"
	DB *dbp;
	int rret;
	rret = db_create(&dbp, NULL, 0);
	rret = dbp->open(dbp,
		NULL,
		"afaefa",
		NULL,
		DB_HASH,
		DB_CREATE,
		0);

	if (rret) {
		dbp->err(dbp, rret, "%s", DATABASE);
	}

	return 0;
}

// db_init

int BD_initEnv(STOCK_DBS* mst){      //初始化环境





	mst->Book_Init_Ok = FALSE;

	LogOut(_T("正在初始化棋库数据库。。。!\n"));

	memset(mst,0,sizeof(STOCK_DBS));

	uint32 env_flag =  DB_CREATE
		|DB_INIT_MPOOL;      //初始化in-memory cache
	//|DB_THREAD ;        //数据库句柄可以给多个线程使用

	mst->book_db_name = "book.db";
	mst->good_db_name = "good.db";

	int ret;
	
	ret = db_env_create(&mst->Env,0);

	if(ret != 0){
		LogOut(_T("DB_ERR: Create env: "));
		LogOuts(db_strerror(ret));
		return ret;
	}

	ret = mst->Env->open(mst->Env,
		CW2A(installDir),
		env_flag,
		0);

	if(ret != 0){
		LogOut(_T("DB_ERR: Environment open: "));
		LogOuts(db_strerror(ret));
		return ret;
	}

	//建立book数据库连接

	//ret = db_create(&mst->book,NULL,0);

	ret = db_create(&mst->book,mst->Env,0);
	
	if(ret != 0){
		LogOut(_T("DB_ERR: Create Book: "));
		LogOuts(db_strerror(ret));
		return ret;
	}



	mst->book->set_errcall(mst->book,BD_my_error_handler);
	mst->book->set_errpfx(mst->book,"book->");

	//打开book 数据库
	ret = mst->book->open(mst->book,
		NULL,
		mst->book_db_name,
		NULL,
		DB_HASH,
		DB_CREATE,
		0);

	if(ret != 0){
		mst->book->err(mst->book,ret,"book file open failed: %s",mst->book_db_name);
		return ret;
	}

	LogOut(_T("初始化棋库数据库成功!\n"));

	mst->Book_Init_Ok = TRUE;

	mst->back_db = NULL;

    return ret;

}

int BD_openGoodDb(STOCK_DBS* mst){			//这是当前使用的的book;){

	int ret;

	ret = db_create(&mst->back_db,mst->Env, 0);

	if(ret != 0){
		LogOut(_T("DB_ERR: Create back db: "));
		LogOuts(db_strerror(ret));
		return ret;
	}

	mst->back_db->set_errcall(mst->back_db,BD_my_error_handler);
	mst->back_db->set_errpfx(mst->back_db,"back->");

	//打开备份数据库

	ret = mst->back_db->open(mst->back_db,
		NULL,
		mst->good_db_name,
		NULL,
		DB_HASH,
		DB_CREATE,
		0);

	if(ret != 0){
		mst->back_db->err(mst->back_db,ret,"book file open failed: %s",mst->good_db_name);
		return ret;
	}

	return ret;

}

void BerKeley_DB_EXIT(STOCK_DBS *mst){		// 
	if(mst->book != NULL){
		mst->book->close(mst->book,0);
	}
	if(mst->back_db != NULL){
		mst->back_db->close(mst->back_db,0);
	}
}


void Back_Up_Book(void){

	if (BD_openGoodDb(MST) == 0){

		Book_Back_Up(MST->back_db, MST->book);

		if (MST->back_db != NULL){
			MST->back_db->close(MST->back_db, 0);
		}
	}

}
