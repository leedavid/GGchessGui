#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"
#include <sys/stat.h>
#include <io.h>
#include <fcntl.h>
#include <share.h>

BOOL		ReadMxqToPos   (dispboard_t* pDis, TCHAR* mxqFname){

   char mxqBuf[4096];
   char buf[256];
   char intbuf[32];
   char ss[256];

   int pFile;
   int i;

   setlocale(LC_CTYPE, "chs");

   PGN* pgn = pDis->pgn;

   errno_t err =   _wsopen_s(&pFile,mxqFname,_O_RDONLY, _SH_DENYNO, 
	   _S_IREAD | _S_IWRITE );

   if(err != 0){
	   //printf("info file %s does not exist.\n", mxqFname);
	   LogOut(L"info file %s does not exist.\n");
	   return FALSE;
   }
   //eof = fgets(mxqBuf, 2048, pFile);      //将文件PGN读入内存

   int bytesread;

   if( ( bytesread = _read( pFile, mxqBuf, 4096 ) ) <= 0 ){

	   LogOut(L"info ERR Problem reading file %s\n"); // , mxqFname );

	   return FALSE;
   }

    _close( pFile );


	if(strlen(mxqBuf) < 20){
		return FALSE;
	}

    char* pcAnsi = mxqBuf; 
    // 
	//sprintf_s(pgn->pevent,sizeof(pgn->pevent),"%s","弈天棋库");
    
    //得到evnet的的长度
    int len = *pcAnsi;      //
    pcAnsi++;
	strCopybyNum(ss,len,pcAnsi);
	swprintf_s(pgn->pevent, sizeof(pgn->pevent) / sizeof(TCHAR), _T("%S"), ss);
    pcAnsi += len;

    //得到对局比赛日期的长度
    len = *pcAnsi;
    pcAnsi++;
	strCopybyNum(ss,len,pcAnsi);
	swprintf_s(pgn->date, sizeof(pgn->date) / sizeof(TCHAR), _T("%S"), ss);
    //得到红方-结果-黑方名称长度
     pcAnsi += len;   

    //红方
    len   = *pcAnsi;
    pcAnsi ++;    
    for(i = 0; *pcAnsi != 0x2d; i++, len--){
		ss[i] = *(pcAnsi++);
    }
    ss[i] = 0; //加上结尾
	swprintf_s(pgn->Red, sizeof(pgn->Red) / sizeof(TCHAR), _T("%S"), ss);
    //结果
    pcAnsi++;    
    for(i = 0; *pcAnsi != 0x2d; i++, len--){
		ss[i] = *(pcAnsi++);
    }
    ss[i] = 0; //对局结果
	swprintf_s(pgn->result, sizeof(pgn->result) / sizeof(TCHAR), _T("%S"), ss);
    //黑方
    pcAnsi ++;    
    for(i = 0; len>2;  i++, len--){
		ss[i] = *(pcAnsi++);
    }
    ss[i] = 0; //加上结尾
	swprintf_s(pgn->Black, sizeof(pgn->Black) / sizeof(TCHAR), _T("%S"), ss);
    //红方等级分
    len = *pcAnsi;
    pcAnsi++;

    //strCopybyNum(PGN->pgn_white_elo,len,pcAnsi);
    //*****************************************************
    strCopybyNum(intbuf,len,pcAnsi);
	pgn->Relo = atoi(intbuf);
    //*****************************************************
    pcAnsi += len;
    
     //黑方等级分
    len = *pcAnsi;
    pcAnsi++;

    //strCopybyNum(PGN->pgn_black_elo,len,pcAnsi);
    //*****************************************************
    strCopybyNum(intbuf,len,pcAnsi);
    pgn->Belo = atoi(intbuf);
    //*****************************************************

    pcAnsi += len;

     //用时1
    len = *pcAnsi;
    pcAnsi++;
	ss[0] = 0;
	strcat_s(ss,sizeof(ss)," 红方用时:");
    //strCopybyNum(PGN->use_time1,len,pcAnsi);
    //*****************************************************
    strCopybyNum(intbuf,len,pcAnsi);
	strcat_s(ss, sizeof(ss), intbuf);
    //PGN->use_time1 = atoi(intbuf);.............................................
    //*****************************************************

    pcAnsi += len;

    //用时2
    len = *pcAnsi;
    pcAnsi++;
    //strCopybyNum(PGN->use_time2,len,pcAnsi);
    //*****************************************************
    strCopybyNum(intbuf,len,pcAnsi);
	strcat_s(ss, sizeof(ss), intbuf);
    //PGN->use_time2 = atoi(intbuf);.............................................
    //*****************************************************
    pcAnsi += len;

    //用时3
    len = *pcAnsi;
    pcAnsi++;
    //strCopybyNum(PGN->use_time3,len,pcAnsi);
    //*****************************************************
    strCopybyNum(intbuf,len,pcAnsi);
	strcat_s(ss, sizeof(ss), intbuf);
    //PGN->use_time3 = atoi(intbuf);.............................................
    //*****************************************************
    pcAnsi += len;

	strcat_s(ss, sizeof(ss), "　黑方用时:");

    //红方用时1
    len = *pcAnsi;
    pcAnsi++;
    //strCopybyNum(PGN->white_time,len,pcAnsi);
    //*****************************************************
    strCopybyNum(intbuf,len,pcAnsi);
	strcat_s(ss, sizeof(ss), intbuf);
    //PGN->white_time = atoi(intbuf);.............................................
    //*****************************************************
    pcAnsi += len;

    //黑方用时1
    len = *pcAnsi;
    pcAnsi++;
    //strCopybyNum(PGN->black_time,len,pcAnsi);
     //*****************************************************
    strCopybyNum(intbuf,len,pcAnsi);
	strcat_s(ss, sizeof(ss), intbuf);
	swprintf_s(pgn->note, sizeof(pgn->note) / sizeof(TCHAR), _T("%S"), ss);
    //*****************************************************
    pcAnsi += len;

    //网站判定
    len = *pcAnsi;
    pcAnsi++;
    //strCopybyNum(PGN->result_other,len,pcAnsi);

	strCopybyNum(intbuf,len,pcAnsi);

	wcscat_s(pgn->result, sizeof(pgn->result) / sizeof(TCHAR), _T(" "));
	wcscat_s(pgn->result, sizeof(pgn->result) / sizeof(TCHAR), CA2W(intbuf));

    pcAnsi += len;

    //---------------//MOVES or INITBOARD
    len = *pcAnsi;
    strCopybyNum(buf,len,++pcAnsi);

    if(string_start_with(buf,"initboard")){ //这是一个殘局

        return FALSE;//////////////////////////////////////////////////////////////
    }
    else{  //是全局
        //strcpy_s(PGN->Fen,128,StartFen);
        //set_position(pos, (char*)StartFen);
        pcAnsi += len;
		pDis->pgn->isFenGame = FALSE;	//是全新开局         
    }

    do{//读出第一个棋步
        len = *pcAnsi;
        if(len != 5){
            break;
        }
        strCopybyNum(buf,len,++pcAnsi);

        //int fx = buf[0]-0x30;
        //int fy = buf[1]
        int f90  = buf[0]-0x30 + (74-buf[1])*9;
        int to90 = buf[3]-0x30 + (74-buf[4])*9;

        int from        = A90toA256[f90]   ;
        int to          = A90toA256[to90]  ;
        //int piece       = pos->board[from];
        //int capture     = pos->board[to];

        //make_move(pos,MOVE_FROM(from,piece,to,capture));

        //MOVE(from,to);

        //make_move(pos,MOVE_FROM(from,piece,to,capture),0);

		MakeMove(pDis,  StoX(from) - 3,
						StoY(from) - 3,
						StoX(to)   - 3,
						StoY(to)   - 3, 0);		

        pcAnsi += len;

    }while(TRUE);

    //判断最后一步是不是将军

   
    if(len == 4){
        strCopybyNum(buf,len,++pcAnsi);
        if(string_start_with(buf,"Ends")){

            //pos->His[pos->gply].ischeck = (sint8)isTurnInCheck(pos,pos->side);

			if(pDis->pos->gply < 40){
				LogOut(_T("\n本棋局棋步小于40步,太少了,没有导入棋库\n"));
				return FALSE;
			}

            return TRUE;
        }
    }
    return FALSE;

}


//将目录下的MXQ文件都一个一个读入开局库
BOOL MxqFileCatToSql(dispboard_t* pDis, TCHAR* pgnRoot){

	//char pgnPath[MAX_PATH];

	//sprintf_s(pgnPath,MAX_PATH,"%s%s",installDir,"pgn\\");

	BOOL havePgn = FALSE;

	TCHAR filename[MAX_PATH*2];

	BOOL isFind = FALSE;
	TCHAR dir[MAX_PATH];
	TCHAR pre_name[MAX_PATH * 2];
	TCHAR new_name[MAX_PATH * 2];

	TCHAR ok_dir[MAX_PATH];
	//char bad_dir[MAX_PATH];

	int ok_num = 0;	

	swprintf_s(ok_dir, sizeof(ok_dir) / sizeof(TCHAR), _T("%s%s"), pgnRoot, _T("_ok"));

	CreateDirectory(ok_dir,NULL);  //建立转换成功的目录 

	//sprintf_s(ok_dir,sizeof(ok_dir),"%s%s",pgnRoot,"_ok");


	do{		//打开一个pgn文件
		OpenAllCatFileOnebyOne(&isFind,pgnRoot,_T("*.mxq"),_T("_ok"),dir,filename);

		if(isFind){
			swprintf_s(pre_name, sizeof(pre_name) / sizeof(TCHAR), _T("%s%s"), dir, filename);

			swprintf_s((TCHAR*)pDis->pgn->note, sizeof(pDis->pgn->note) / sizeof(TCHAR), filename);  //将文件名称

			if(ReadMxqToPos(pDis,pre_name)){

				//读入成功了，就移动到_ok目录下
				swprintf_s(new_name, sizeof(new_name) / sizeof(TCHAR), _T("%s%s%s"), ok_dir, _T("\\"), filename);

				if(FALSE == MoveFileEx(pre_name,new_name,MOVEFILE_REPLACE_EXISTING)){
					LogOut(pre_name);
					LogOut(_T("\n不能移动或改名到_ok目录!!\n"));
					LogOut(new_name);
					break;
				}

				LogOut(_T("\n成功读入一局弈天文件!\n"));
				LogOut(pre_name);
				
				havePgn = TRUE;
			}

			else{
				//不能正确读入PGN文件
				LogOut(pre_name);
				LogOut(_T("读入弈天文件错误，请检查弈天格式!!\n"));

				//******************************************************************				
				swprintf_s(new_name, sizeof(new_name) / sizeof(TCHAR), _T("%s%s%s"), ok_dir, _T("\\"), filename);

				if(FALSE == MoveFileEx(pre_name,new_name,MOVEFILE_REPLACE_EXISTING)){
					LogOut(pre_name);
					LogOut(_T("\n不能移动或改名到_ok目录!!\n"));
					LogOut(new_name);
					break;
				}
				//******************************************************************
				havePgn = TRUE;
				break;
			}

			isFind = FALSE;

		}
		else{
			LogOut(pgnRoot);
			LogOut(_T("\n对不起，没有在以上目录下找到有效的弈天文件\n"));
		}

	}while(false);

	return havePgn;
	
}