#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"
#include <sys/stat.h>
#include <io.h>
#include <fcntl.h>
#include <share.h>
#include <time.h>
#include <sys/timeb.h>


//打开一局完整的棋局
//CopyUBBToClipboard(pDis);


BOOL CopyUBBToFile(dispboard_t* pDis, FILE* f, int num){

	errno_t err;
	time_t ltime;
	char timebuf[26];
    struct tm gmt, xmas = { 0, 0, 12, 25, 11, 93 };



	if((num-1)%51 == 0){

		time( &ltime );
		err = ctime_s(timebuf, 26, &ltime);
		err = _gmtime64_s( &gmt, &ltime );
		err = asctime_s(timebuf, 26, &gmt);

		//printf( "Coordinated universal time:\t\t%s", timebuf );
		fprintf(f,"<center>\n\n\n佳佳对局选  %s\n\n\n</center>", timebuf);



		//CString strTime = CTime::GetCurrentTime().Format("%Y-%m-%d-%a %H:%M:%S") ;
		//fprintf(f,"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	}

	//datetime

   char buf[8192];
   PGN* pgn = pDis->pgn;

   const char* pweb = 
	   "<center>"
	   "[DhtmlXQ]"
	   "[DhtmlXQ_ver]www_dpxq_com[/DhtmlXQ_ver]";

   const char* ptitle = 
	   "[DhtmlXQ_init]500,350[/DhtmlXQ_init]"
	   "[DhtmlXQ_title]";
   const char* ptitle_end =
	   "[/DhtmlXQ_title]";

   const char* pred =
	   "[DhtmlXQ_redteam]";
   const char* pred_end = 
	   "[/DhtmlXQ_redteam]";
   const char* pblack = 
	   "[DhtmlXQ_blackteam]";
   const char* pblack_end = 
	   "[/DhtmlXQ_blackteam]";
   const char* presult_start=
	   "[DhtmlXQ_result]";
   const char* presult_end  = 
	   "[/DhtmlXQ_result]";
   const char* pmove = 
	   "[DhtmlXQ_movelist]";
   const char* pmove_end =
	   "[/DhtmlXQ_movelist]";
   const char* ptype = 
	   "[DhtmlXQ_type]";
   const char* ptype_end = 
	   "[/DhtmlXQ_type]";

   const char* prtime = 
	   "[DhtmlXQ_redtime]";
   const char* prtime_end = 
	   "[/DhtmlXQ_redtime]";
   const char* pbtime = 
	   "[DhtmlXQ_blacktime]";
   const char* pbtime_end = 
	   "[/DhtmlXQ_blacktime]";

   const char* pother = 
	   "[DhtmlXQ_other]";

	const char* pother_end = 
	   "[/DhtmlXQ_other]";

	const char* pfnum = 
		"[DhtmlXQ_firstnum]";
	const char* pfnum_end =
		"[/DhtmlXQ_firstnum]";

	const char* prefer = 
		"[DhtmlXQ_refer]http://www.ggchess.com/[/DhtmlXQ_refer]"
		"[/DhtmlXQ]";

	//const char *pend =
	//	"UBB 代码由 [url=http://www.xiangqi.com.cn/down/view_58.html][color=Blue]象棋爱好者[/color][/url] 
	//	" 软件生成。 [url=http://www.xiangqi.com.cn/files/help/ubb.swf][color=Red]单击此处观看视频教程[/color][/url]";

	sprintf_s(buf,sizeof(buf),"%s", pweb);

	//ptitle

	strcat_s(buf,sizeof(buf), ptitle);

	//strcat_s(buf,sizeof(buf), pgn->note);

	strcat_s(buf,sizeof(buf), "-= 佳佳象棋 =-   ");

	strcat_s(buf,sizeof(buf), CW2A(pgn->Red));

	strcat_s(buf,sizeof(buf), " vs ");

	strcat_s(buf, sizeof(buf), CW2A(pgn->Black));

	strcat_s(buf,sizeof(buf), " ");

	strcat_s(buf, sizeof(buf), CW2A(pgn->result));

	strcat_s(buf,sizeof(buf), ptitle_end);

	strcat_s(buf,sizeof(buf), pred);
	strcat_s(buf, sizeof(buf), CW2A(pgn->Red));
	strcat_s(buf,sizeof(buf), pred_end);

	strcat_s(buf,sizeof(buf), pblack);
	strcat_s(buf, sizeof(buf), CW2A(pgn->Black));
	strcat_s(buf,sizeof(buf), pblack_end);

	strcat_s(buf,sizeof(buf), presult_start);
	strcat_s(buf, sizeof(buf), CW2A(pgn->result));
	strcat_s(buf,sizeof(buf), presult_end);

	strcat_s(buf,sizeof(buf), pmove);

	for(int i = 0; i < pDis->pos->gply; i++){
		TCHAR mbuf[32];
		//char *pm = pDis->parseList[i];
		//sprintf_s(mbuf,sizeof(mbuf),"%C%C-%C%C ",ToUpper(pm[0]),ToUpper(pm[1]),ToUpper(pm[2]),ToUpper(pm[3]));	

		int move = pDis->pos->His[i+1].move; 

		int from = FROM(move);
		int to   = TO(move);

		int fx   = StoX(from) - 3;
		int fy   = StoY(from) - 3;

		int tx   = StoX(to) - 3;
		int ty   = StoY(to) - 3;

		int num    = i;

		int n1000  = i / 1000;
		int n100   = (i - n1000 * 1000)/100;
		int n10    = (i - n1000 * 1000 - n100 * 100)/10;
		int n      = i % 10;

		swprintf_s(mbuf,sizeof(mbuf)/sizeof(TCHAR),L"%d%d%d%d%s%d%d%d%d",fx,fy,tx,ty,MoveToUBBove(pDis->moveListName[i]+4),n1000,n100,n10,n);

		strcat_s(buf,sizeof(buf),CW2A(mbuf));
	}

	strcat_s(buf,sizeof(buf), pmove_end);

	strcat_s(buf,sizeof(buf), ptype);
	strcat_s(buf,sizeof(buf), "全局");
	strcat_s(buf,sizeof(buf), ptype_end);

	strcat_s(buf,sizeof(buf), prtime);
	strcat_s(buf, sizeof(buf), CW2A(pgn->RtimeControl));
	strcat_s(buf,sizeof(buf), prtime_end);

	strcat_s(buf,sizeof(buf), pbtime);
	strcat_s(buf, sizeof(buf), CW2A(pgn->BtimeControl));
	strcat_s(buf,sizeof(buf), pbtime_end);

	strcat_s(buf,sizeof(buf), pother);
	strcat_s(buf, sizeof(buf), CW2A(pgn->note));
	strcat_s(buf,sizeof(buf), pother_end);

	strcat_s(buf,sizeof(buf), pfnum);
	//strcat_s(buf,sizeof(buf), pgn->note);
	strcat_s(buf,sizeof(buf), pfnum_end);

	strcat_s(buf,sizeof(buf), prefer);

	strcat_s(buf,sizeof(buf), "</center>");


	//if (!CopyTextToClipboard(buf)) {
	//	DisplayError("Cannot copy text to clipboard", 0);
	//}
	//else{
	//	LogOut("\nUBB棋局已复制到剪贴板\n");
	//}

	fprintf(f,"\n<br><center>**********************   %d  *********************%s<br></center>\n",num,buf);
	fflush(f);

	return TRUE;
}


void Export_Sqlite_Qj(void){

	//打开一个文件。

	FILE			    *FileWeb;
    int                num = 0;

	TCHAR buf[MAX_PATH];
	swprintf_s(buf, MAX_PATH, _T("%s%s"), installDir, _T("web_chess.txt"));
	errno_t err = _wfopen_s(&FileWeb, buf, _T("w"));
	if(err != 0){
		//int ddd = 0;
		MessageBox(NULL, _T("不能打开web_chess.txt文件"), _T("出错啦"), MB_OK);
		return ;
	}
	else{
		//setvbuf(DIS.debugFP,NULL,NULL,0);
		//fwrite(
	}

	dispboard_t pDis[1];

	LogOut(_T("\n正在导出棋局。。。\n"));

	fprintf(FileWeb,"<br><center>******************************************************************");
	        fprintf(FileWeb,"<br>----------------------佳佳象棋对局选------------------------------");
	        fprintf(FileWeb,"<br>******************************************************************</center>");


	//打开一局完成的棋局

	sqlite3 * db;
	int rc = SqliteOpenDataBase(&db,L3_DB_PGN);
	if(rc != SQLITE_OK){
		LogOut(_T("\n出错啦，不能打开棋局数据库!\n"));
        return;
	}

	while(PgnGetOneFinishedGameFromSql(pDis,db) == SQLITE_OK){

		num++;

		PgnFenToPos(pDis,false);

		if(CopyUBBToFile(pDis,FileWeb, num) == FALSE){

			LogOut(_T("\n读取棋局出错\n"));
			break;
		}


		swprintf_s(buf, MAX_PATH, _T("\n正在导出 %d 局棋局到web_chess.txt\n"), num);

		LogOut(buf);
	}

	//CorrectQiJu(pDis, db);




	sqlite3_close(db);
	//LogOut("\n导出棋局完成。。。\n");
	swprintf_s(buf, MAX_PATH, _T("\n导出棋局完成, 共导出 %d 局棋局到web_chess.txt\n"), num);

	LogOut(buf);

	return;
}