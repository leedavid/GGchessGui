#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"
#include <sys/stat.h>
#include <io.h>
#include <fcntl.h>
#include <share.h>

//查看一下，PGN 棋步在不在当前可走的棋步中
int getMoveFormPgnStr(dispboard_t* pDis, char* pgnStr){


	position_t *pos = pDis->pos;

	gen_legal_moves(pos);

	while(pos->pMend > pos->all_move){

		pos->pMend--;

		if(pos->His[pos->curStep].ischeck == FALSE){
			if(move_is_legal(pos,pos->pMend->move) == FALSE){
				continue;
			}			
		}

		//pos->pMend--;

		//得到走步的名称
		GetMoveName(pDis,pos,pos->pMend->move, appData.moveType);

		char*   szStepName  = pDis->moveListName[pos->curStep] + 4;   //加上前面的编号哇

		//if(string_start_with(pgnStr,szStepName)){
		//	return pos->pMend->move;
		//}

		//看前面8个字符是不是一样
		BOOL find = TRUE;

		for(int i = 0; i < 8; i++){
			if(szStepName[i] != pgnStr[i]){
				find= FALSE;
				break;
			}
		}

		if(find == TRUE){
			return pos->pMend->move;
		}
	}

	return 0;
}

BOOL		ReadPgnToPos    (dispboard_t* pDis, char* pgnFname, pgn_file_t* PGN){

	char pgnBuf[4096];

	//memset(pgnBuf,0, sizeof(pgnBuf));
	//char buf[512];
	//char intbuf[32];
	int  pFile;
	//int  i;

	//将PGN清空一下
	memset(PGN,0,sizeof(pgn_file_t));

	sprintf_s(PGN->pgn_format,sizeof(PGN->pgn_format),"pgn");

	errno_t err = _sopen_s(&pFile, pgnFname, _O_RDONLY, _SH_DENYNO,
		_S_IREAD | _S_IWRITE);

	if(err != 0){
		LogOut(pgnFname);
		LogOut("\nPGN 文件不存在，或打不开!!\n");
		return FALSE;
	}

	//将文件全部读入BUF
	int bytesRead = _read(pFile, pgnBuf, sizeof(pgnBuf));

	if(bytesRead <= 0){
		LogOut(pgnFname);
		LogOut("\nPGN 文件不存在，或打不开!!\n");
		_close(pFile);
		return FALSE;
	}

	_close(pFile);

	if(bytesRead < 20){
		LogOut(pgnFname);
		LogOut("\nPGN 文件内容太少！！\n");
		return FALSE;
	}


	//Returns a pointer to the first occurrence of strSearch in str, 
	//or NULL if strSearch does not appear in str. 
	//If strSearch points to a string of zero length, the function returns str.


	char* ps;

	int len = (int)strlen(pgnBuf);

	char* pend = pgnBuf + len;

	*pend      = 0;
	*(pend-1)  = 0;

	//*(pend-1) = 0;       //加上一个结尾 
	
	//ps = strstr(pgnBuf,"Round");

	//if(ps == NULL){
	//	LogOut(pgnFname);
	//	LogOut("\nPGN 在PGN文件中没有发现 Round项 ！！\n");
	//	return FALSE;
	//}

	ps = pgnBuf;

	int ply = 1;         //PGN文件1开头

	char str_num[32];

	while(ps < pend){

		if((pend - ps) < 7){
			goto PGN_RET;  //没有棋步了
		}

		

		sprintf_s(str_num,sizeof(str_num),"%d. ",ply);

		ps = strstr(ps,str_num);

		if(ps != NULL){				//这儿可能有两步
			
			ps = strstr(ps," ");    //找到第一个空格

			if(ps == NULL){
				goto PGN_RET;  //没有棋步了
			}

			while(ps < pend && *(++ps) == ' '){	//跳过后面的空格
			}

			if(ps > pend){
				goto PGN_RET;  //没有棋步了
			}

			if((pend - ps) < 7){
				goto PGN_RET;  //没有棋步了
			}

			int move = getMoveFormPgnStr(pDis,ps);

			if(move == 0){
				goto PGN_RET;   //没有棋步了
			}

			//直接走步了
			UserMoveEvent(pDis,
				StoX(FROM(move)) - 3,
				StoY(FROM(move)) - 3,
				StoX(TO(move))   - 3,
				StoY(TO(move))   - 3, 0);


			if((pend - ps) < 7){
				goto PGN_RET;  //没有棋步了
			}

			ps = strstr(ps, " ");

			if(ps == NULL){
				goto PGN_RET;  //没有棋步了
			}


			while(ps < pend && *(++ps) == ' '){	//跳过后面的空格
			}

			if(ps > pend){
				goto PGN_RET;  //没有棋步了
			}

			if((pend - ps) < 7){
				goto PGN_RET;  //没有棋步了
			}

			move = getMoveFormPgnStr(pDis,ps);

			if(move == 0){
				goto PGN_RET;   //没有棋步了
			}

			//直接走步了
			UserMoveEvent(pDis,
				StoX(FROM(move)) - 3,
				StoY(FROM(move)) - 3,
				StoX(TO(move))   - 3,
				StoY(TO(move))   - 3, 0);


			ply++;		
			
		}

		else{
			goto PGN_RET;   //没有棋步了
		}
	}

PGN_RET:


	if( (pend-ps) > 7){

		LogOut(pgnFname);
		LogOut("\n还有棋步没有解析哇!!\n");
		LogOut(pgnBuf);
		LogOut("\n棋步编号：");
		LogOut(str_num);
	}

	if(ply > 1){

		//设为允许使用

		//CheckDlgItem(		

		LogOut(pgnBuf);

		LogOut("\n成功读入了一局ＰＧＮ文件到内存!\n");

		return TRUE;
	}
	else{
		return FALSE;
	}
	
}

//将目录下的PGN文件都一个一个读入开局库
BOOL PgnFileCatToBook(char* pgnRoot){

	//char pgnPath[MAX_PATH];

	//sprintf_s(pgnPath,MAX_PATH,"%s%s",installDir,"pgn\\");

	BOOL havePgn = FALSE;

	char filename[MAX_PATH*2];

	BOOL isFind = FALSE;
	char dir[MAX_PATH];
	char pre_name[MAX_PATH*2];
	char new_name[MAX_PATH*2];

	char ok_dir[MAX_PATH];

	int ok_num = 0;

	dispboard_t *pDis = OBS[0];

	pgn_file_t PGN[1];

	ResetGameEvent(pDis);

	sprintf_s(ok_dir,sizeof(ok_dir),"%s%s",pgnRoot,"_ok");

	CreateDirectory(ok_dir,NULL);  //建立转换成功的目录 

	do{		//打开一个pgn文件
		OpenAllCatFileOnebyOne(&isFind,pgnRoot,"*.pgn","_ok",dir,filename);

		if(isFind){
			sprintf_s(pre_name,sizeof(pre_name),"%s%s",dir,filename);

			if(ReadPgnToPos(pDis,pre_name,PGN)){

				//读入成功了，就移动到_ok目录下
				sprintf_s(new_name,sizeof(new_name),"%s%s%s",ok_dir,"\\",filename);

				if(FALSE == MoveFileEx(pre_name,new_name,MOVEFILE_REPLACE_EXISTING)){
					LogOut(pre_name);
					LogOut("\n不能移动或改名到_ok目录!!\n");
					LogOut(new_name);
					break;
				}

				LogOut("\n成功读入一局PGN文件!\n");
				LogOut(pre_name);
				
				havePgn = TRUE;
			}

			else{
				//不能正确读入PGN文件
				LogOut(pre_name);
				LogOut("读入PGN文件错误，请检查PGN格式!!\n");
				break;
			}

			isFind = FALSE;

		}
		else{
			LogOut(pgnRoot);
			LogOut("\n对不起，没有在以上目录下找到有效的PGN文件\n");
		}

	}while(false);

	return havePgn;
	
}