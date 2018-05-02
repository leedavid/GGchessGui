#include "stdafx.h"
#include "chess.h"
#include "data.h"
#include "resource.h"

//#include "config.h"

//#include <windows.h>   /* required for all Windows applications */
//#include <stdio.h>
//#include <stdlib.h>
//#include <malloc.h>
#include <sys/stat.h>

//#include "common.h"
//#include "winboard.h"
//#include "frontend.h"
//#include "backend.h"
//#include "wclipbrd.h"

/* Imports from winboard.c */
//extern HWND hwndMain;

/* File globals */
static char *copyTemp;
static char *pasteTemp;

VOID 
CopyFENToClipboard(dispboard_t* pDis){
  //char *fen = NULL;
  TCHAR fen[MSG_SIZ];


  PositionToFEN(pDis,fen,pDis->pos->curStep,UCCI_UCCI_ms);
  //if (!fen) {
  //  DisplayError("Unable to convert position to FEN.", 0);
  //  return;
  //}
  if (!CopyTextToClipboard(fen))
	  LogOut(L"Unable to copy FEN to clipboard.");
  //free(fen);
}



void SendAllEvalToClipBoardFlip(dispboard_t* pDis){


	//ChessProgramState *cps;

	//cps = &pDis->first;

	//if (cps->cps_stat == Cps_Thinking || cps->cps_stat == Cps_Pondering || cps->cps_stat == Cps_Analyse
	//	|| cps->cps_stat == Cps_NotLoad){
	//	LogOut(_T("\n对不起，当前引擎正在思考或没有加载成功，不能输出相关的信息\n")); return;
	//}

	//dispboard_t *NewDis = new dispboard_t;
	//memcpy(NewDis, pDis, sizeof(dispboard_t));

	//CopyGameToClipboardUBB(NewDis, FALSE);

	//SendCurPosToProgram(pDis, cps);

	//SendToProgram(L"cmd eval\n", cps);

	////dispboard_t *NewDis = new dispboard_t;
	////memcpy(NewDis, pDis, sizeof(dispboard_t));

	////board_red2black(NewDis);
	////SendAllEvalToClipBoard(pDis);

	//delete NewDis;

}

//输出所有信息到剪帖板
void SendAllEvalToClipBoard(dispboard_t* pDis){
	
    ChessProgramState *cps;

	cps = &pDis->first;

	if(cps->cps_stat == Cps_Thinking || cps->cps_stat == Cps_Pondering || cps->cps_stat == Cps_Analyse 
		|| cps->cps_stat == Cps_NotLoad){
		LogOut(_T("\n对不起，当前引擎正在思考或没有加载成功，不能输出相关的信息\n")); return;
	}

	CopyGameToClipboardUBB(pDis, FALSE);

	//SendOnlyFenToProgram(pDis, cps);
	SendCurPosToProgram(pDis, cps);

	SendToProgram(L"cmd eval\n", cps);

}


TCHAR *MoveToUBBove(TCHAR *pm){
	static TCHAR Ubb[32];
	//Ubb[0] = 'Z';
	//Ubb[1] = 'Z';
	//Ubb[2] = 'Z';
	//Ubb[3] = 'Z';
	Ubb[4] = 0;

	for(int i= 0; i<4; i++){
		TCHAR *p = pm + i;

		//uint16 name = *((uint16*)p);

		//int name = *p + ((*(p+1))<<8);

		TCHAR name = *p;

		switch(name){
			case L'车':
				Ubb[i] = '1';    //车
				break;			
			case L'马':
				Ubb[i] = '2';    //马
				break;
			case L'相':
				Ubb[i] = '3';    //相
				break;
			case L'象':
				Ubb[i] = '4';    //象
				break;
			case L'仕':
				Ubb[i] = '5';    //仕
				break;
			case L'士':
				Ubb[i] = '6';    //士
				break;
			case L'帅':
				Ubb[i] = '7';    //帅
				break;
			case L'将':
				Ubb[i] = '8';    //将
				break;
			case L'炮':           //炮
				Ubb[i] = '9';
				break;
			case L'兵':		     //兵
				Ubb[i] = 'A';
			case L'卒':
				Ubb[i] = 'B';    //卒
				break;	
			case L'一':
				Ubb[i] = 'C';    //一
				break;
			case L'１':
				Ubb[i] = 'D';    //1
				break;
			case L'二':           //二
				Ubb[i] = 'E';
				break;
			case L'２':		     //2
				Ubb[i] = 'F';
				break;			
			case L'三':           //三
				Ubb[i] = 'G';
				break;
			case L'３':
				Ubb[i] = 'H';    //3
				break;
			case L'四':
				Ubb[i] = 'I';    //四
				break;
			case L'４':
				Ubb[i] = 'J';    //4
				break;
			case L'五':
				Ubb[i] = 'K';    //五
				break;
			case L'５':
				Ubb[i] = 'L';    //5
				break;
			case L'六':
				Ubb[i] = 'M';    //六
				break;
			case L'６':
				Ubb[i] = 'N';    //6
				break;
			case L'七':
				Ubb[i] = 'O';    //七
				break;
			case L'７':
				Ubb[i] = 'P';    //7
				break;
			case L'八':
				Ubb[i] = 'Q';    //八
				break;
			case L'８':
				Ubb[i] = 'R';    //8
				break;
			case '九':
				Ubb[i] = 'S';    //九
				break;
			case L'９':
				Ubb[i] = 'T';    //9
				break;
			case L'进':
				Ubb[i] = 'X';    //进
				break;
			case L'退':
				Ubb[i] = 'Y';    //退
				break;
			case L'平':
				Ubb[i] = 'Z';    //平
				break;
			case L'前':
				Ubb[i] = 'U';	 //前
				break;
			case L'后':
				Ubb[i] = 'W';	 //后
				break;
			default:
				Ubb[i] = 'Z';
		}

	}

	return Ubb;
}


//1：[DhtmlXQ ]                                  UBB 开始标志，必选
//2：[DhtmlXQ_ver]文件版本[/DhtmlXQ_ver]         用来支持不同文件版本  必选
//3：[DhtmlXQ_init]500,350[/DhtmlXQ_init]        这一项设定iframe大小  必选
//4：[DhtmlXQ_title]棋局标题[/DhtmlXQ_title]
//5：[DhtmlXQ_event]赛事名称[/DhtmlXQ_event]
//6：[DhtmlXQ_date]比赛日期[/DhtmlXQ_date]
//7：[DhtmlXQ_place]比赛地点[/DhtmlXQ_place]
//8：[DhtmlXQ_round]比赛轮次[/DhtmlXQ_round]
//9：[DhtmlXQ_red]红方[/DhtmlXQ_red]             包括三项：团体 姓名 (等级)
//9.1：[DhtmlXQ_redteam]红方团体[/DhtmlXQ_redteam]  
//9.2：[DhtmlXQ_redlevel]红方等级[/DhtmlXQ_redlevel] 
//9.3：[DhtmlXQ_redrating]红方等级分[/DhtmlXQ_redrating]
//9.4：[DhtmlXQ_redeng]红方英文名[/DhtmlXQ_redeng]
//9.5：[DhtmlXQ_redtime]红方用时[/DhtmlXQ_redtime]
//10：[DhtmlXQ_black]黑方[/DhtmlXQ_black]        格式举例：湖北 汪洋 (大师)
//10.1：[DhtmlXQ_blackteam]黑方团体[/DhtmlXQ_blackteam]  
//10.2：[DhtmlXQ_blacklevel]黑方等级[/DhtmlXQ_blacklevel] 
//10.3：[DhtmlXQ_blackrating]黑方等级分[/DhtmlXQ_blackrating]
//10.4：[DhtmlXQ_blackeng]黑方英文名[/DhtmlXQ_blackeng]
//10.5：[DhtmlXQ_blacktime]黑方用时[/DhtmlXQ_blacktime]
//11：[DhtmlXQ_result]对局结果[/DhtmlXQ_result]  
//12：[DhtmlXQ_open]布局[/DhtmlXQ_open]          使用布局
//12：[DhtmlXQ_remark]评注人员[/DhtmlXQ_remark]
//13：[DhtmlXQ_author]棋谱作者[/DhtmlXQ_author]                棋谱录入人员
//14：[DhtmlXQ_binit]初始局面[/DhtmlXQ_binit]              14和15至少选其一
//15：[DhtmlXQ_movelist]着法序列[/DhtmlXQ_movelist]        14和15至少选其一
//16：[DhtmlXQ_comment0]注解0[/DhtmlXQ_comment0]
//………………
//………………  注解使用comment加数字的形式！注解中的换行全用“||”代替。
//………………
//17：[DhtmlXQ_commentn]注解n[/DhtmlXQ_commentn]
//18：[DhtmlXQ_type]棋局类型|n[/DhtmlXQ_type] 全局、布局、中残局、排局、江湖残局、实用残局、实战残局
//19：[DhtmlXQ_timerule]时间规则[/DhtmlXQ_timerule]  时间规则，慢棋还是快棋
//20：[DhtmlXQ_endtype]结束方式[/DhtmlXQ_endtype] 例如和棋分议和，判和，这里可以标出用来区分
//21：[DhtmlXQ_owner]棋谱主人[/DhtmlXQ_owner] 棋谱由谁所有
//22：[DhtmlXQ_other]其他信息[/DhtmlXQ_other]
//23：[DhtmlXQ_firstnum]初始序号[/DhtmlXQ_firstnum]
//24：[DhtmlXQ_length]着法长度[/DhtmlXQ_length]
//25：[DhtmlXQ_gametype]棋局性质[/DhtmlXQ_gametype] 慢棋、快棋、超快棋、未知
//26：[DhtmlXQ_class]棋局分类[/DhtmlXQ_class] 例如：网络赛事、大师对局、国际赛事
//27：[DhtmlXQ_refer]棋谱来源[/DhtmlXQ_refer]
//28：[/DhtmlXQ ]                                         UBB 结束标志，必选
//
//另外还包括 adddate[添加时间] hits[人气] price[价格] hidden[是否隐藏私有]  等项目，这些可有可无
//
//最新的 DhtmlXQ 支持文件和安装指南下载地址：http://www.dpxq.com/hldcg/share/soft/
//
//DhtmlXQ动态棋盘目前可导出UBB代码、HTML代码、文本棋谱、文本棋图几种功能！
//
//各类常见棋谱都能直接转换成本动态棋盘代码，如需要在网页中显示“转换棋谱”按钮，请


void CopyUBBToClipboard(dispboard_t* pDis){

   TCHAR* buf = EvalInfo;
   PGN* pgn = pDis->pgn;

   const TCHAR* pweb =
	   L"<center>"
	   L"[DhtmlXQ]"
	   L"[DhtmlXQ_ver]www_dpxq_com[/DhtmlXQ_ver]";

   const TCHAR* ptitle =
	   L"[DhtmlXQ_init]500,350[/DhtmlXQ_init]"
	   L"[DhtmlXQ_title]";
   const TCHAR* ptitle_end =
	   L"[/DhtmlXQ_title]";

   const TCHAR* pred =
	   L"[DhtmlXQ_redteam]";
   const TCHAR* pred_end =
	   L"[/DhtmlXQ_redteam]";
   const TCHAR* pblack =
	   L"[DhtmlXQ_blackteam]";
   const TCHAR* pblack_end =
	   L"[/DhtmlXQ_blackteam]";
   const TCHAR* presult_start =
	   L"[DhtmlXQ_result]";
   const TCHAR* presult_end =
	   L"[/DhtmlXQ_result]";
   const TCHAR* pmove =
	   L"[DhtmlXQ_movelist]";
   const TCHAR* pmove_end =
	   L"[/DhtmlXQ_movelist]";
   const TCHAR* ptype =
	   L"[DhtmlXQ_type]";
   const TCHAR* ptype_end =
	   L"[/DhtmlXQ_type]";

   const TCHAR* prtime =
	   L"[DhtmlXQ_redtime]";
   const TCHAR* prtime_end =
	   L"[/DhtmlXQ_redtime]";
   const TCHAR* pbtime =
	   L"[DhtmlXQ_blacktime]";
   const TCHAR* pbtime_end =
	   L"[/DhtmlXQ_blacktime]";

   const TCHAR* pother =
	   L"[DhtmlXQ_other]";

   const TCHAR* pother_end =
	   L"[/DhtmlXQ_other]";

   const TCHAR* pfnum =
		L"[DhtmlXQ_firstnum]";
   const TCHAR* pfnum_end =
		L"[/DhtmlXQ_firstnum]";

   const TCHAR* prefer =
		L"[DhtmlXQ_refer]http://www.ggchess.com/[/DhtmlXQ_refer]"
		L"[/DhtmlXQ]</center>";

	//const char *pend =
	//	"UBB 代码由 [url=http://www.xiangqi.com.cn/down/view_58.html][color=Blue]象棋爱好者[/color][/url] 
	//	" 软件生成。 [url=http://www.xiangqi.com.cn/files/help/ubb.swf][color=Red]单击此处观看视频教程[/color][/url]";

   swprintf_s(buf, EVAL_INFO_SIZE, L"%s", pweb);

	//ptitle

   wcscat_s(buf, EVAL_INFO_SIZE, ptitle);

	//strcat_s(buf,sizeof(buf), pgn->note);

   wcscat_s(buf, EVAL_INFO_SIZE, L"-= 佳佳象棋 =-   ");

   wcscat_s(buf, EVAL_INFO_SIZE, (pgn->Red));

   wcscat_s(buf, EVAL_INFO_SIZE, L" vs ");

   wcscat_s(buf, EVAL_INFO_SIZE, (pgn->Black));

   wcscat_s(buf, EVAL_INFO_SIZE, L" ");

   wcscat_s(buf, EVAL_INFO_SIZE, (pgn->result));

   wcscat_s(buf, EVAL_INFO_SIZE, ptitle_end);

   wcscat_s(buf, EVAL_INFO_SIZE, pred);
   wcscat_s(buf, EVAL_INFO_SIZE, (pgn->Red));
   wcscat_s(buf, EVAL_INFO_SIZE, pred_end);

   wcscat_s(buf, EVAL_INFO_SIZE, pblack);
   wcscat_s(buf, EVAL_INFO_SIZE, (pgn->Black));
   wcscat_s(buf, EVAL_INFO_SIZE, pblack_end);

	wcscat_s(buf, EVAL_INFO_SIZE, presult_start);
	wcscat_s(buf, EVAL_INFO_SIZE, (pgn->result));
	wcscat_s(buf, EVAL_INFO_SIZE, presult_end);

	wcscat_s(buf, EVAL_INFO_SIZE, pmove);

	for(int i = 0; i < pDis->pos->gply; i++){
		TCHAR mbuf[64];
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

		//swprintf_s(mbuf, sizeof(mbuf) / sizeof(TCHAR), L"%d%d%d%d%s%d%d%d%d", fx, fy, tx, ty, MoveToUBBove(pDis->moveListName[i] + 4), n1000, n100, n10, n);

		swprintf_s(mbuf, sizeof(mbuf) / sizeof(TCHAR), L"%d%d%d%d", fx, fy, tx, ty);

		wcscat_s(buf, EVAL_INFO_SIZE, mbuf);
	}

	wcscat_s(buf, EVAL_INFO_SIZE, pmove_end);

	wcscat_s(buf, EVAL_INFO_SIZE, ptype);
	wcscat_s(buf, EVAL_INFO_SIZE, L"全局");
	wcscat_s(buf, EVAL_INFO_SIZE, ptype_end);
	wcscat_s(buf, EVAL_INFO_SIZE, prtime);
	wcscat_s(buf, EVAL_INFO_SIZE, (pgn->RtimeControl));
	wcscat_s(buf, EVAL_INFO_SIZE, prtime_end);
	wcscat_s(buf, EVAL_INFO_SIZE, pbtime);
	wcscat_s(buf, EVAL_INFO_SIZE, (pgn->BtimeControl));
	wcscat_s(buf, EVAL_INFO_SIZE, pbtime_end);
	wcscat_s(buf, EVAL_INFO_SIZE, pother);
	wcscat_s(buf, EVAL_INFO_SIZE, (pgn->note));
	wcscat_s(buf, EVAL_INFO_SIZE, pother_end);
	wcscat_s(buf, EVAL_INFO_SIZE, pfnum);
	wcscat_s(buf, EVAL_INFO_SIZE, pfnum_end);
	wcscat_s(buf, EVAL_INFO_SIZE, prefer);
	wcscat_s(buf, EVAL_INFO_SIZE, L"<br><center>[url=http://www.ggchess.com/][color=Blue]佳佳象棋欢迎您[/color][/url]</center>");


	if (!CopyTextToClipboard(buf)) {
		LogOut(L"Cannot copy text to clipboard");
	}
	else{
		LogOut(_T("\nUBB棋局已复制到剪贴板\n"));
	}


}

void
CopyGameToClipboardUBB(dispboard_t* pDis, BOOL isStart){
  
	TCHAR *buf = EvalInfo;

	const TCHAR* UbbF3Start =
		 L"[align=center]"
		 L"[DhtmlXQ]"
		 L"[DhtmlXQ_ver]www_dpxq_com[/DhtmlXQ_ver]"
		 L"[DhtmlXQ_init]500,350[/DhtmlXQ_init]"
		 L"[DhtmlXQ_title]佳佳象棋 审局局面 详细信息[/DhtmlXQ_title]"
		 L"[DhtmlXQ_binit]";

	const TCHAR* UbbListStart = L"[/DhtmlXQ_binit][DhtmlXQ_movelist]";

	const TCHAR* UbbListEnd =
		 L"[/DhtmlXQ_movelist]"
		 L"[DhtmlXQ_refer]http://www.ggchess.com/[/DhtmlXQ_refer]"
		 L"[DhtmlXQ_generator]www.ggchess.com 佳佳象棋[/DhtmlXQ_generator]"
		 L"[/DhtmlXQ][/align]";

	swprintf_s(buf,EVAL_INFO_SIZE,L"%s", UbbF3Start);

	if(isStart){
		ToStartEvent(pDis);
	}
	//初始局面
	//
    TCHAR pchess[65];
	//memset(pchess,'9',64);
	for (int i = 0; i < 65; i++){
		pchess[i] = '9';
	}
	pchess[64] = 0;
	
	int pc[5];
	int k;

	//红车
	pc[0] = 0;
	pc[1] = 8 * 2;
	k     = 0;
	for(int from = PieceListStart(pDis->pos,RCHE); from > 0x32; from = NextPiece(pDis->pos,from)){
	   TCHAR x = StoX(from) - 3 + '0';
	   TCHAR y = StoY(from) - 3 + '0';
	   pchess[pc[k]    ] = x;
	   pchess[pc[k] + 1] = y;
	   k++;	  
	}
	//红马
	pc[0] = 1 * 2;
	pc[1] = 7 * 2;
	k     = 0;
	for(int from = PieceListStart(pDis->pos,RMA); from > 0x32; from = NextPiece(pDis->pos,from)){
		TCHAR x = StoX(from) - 3 + '0';
		TCHAR y = StoY(from) - 3 + '0';
	   pchess[pc[k]    ] = x;
	   pchess[pc[k] + 1] = y;
	   k++;	  
	}
	//红相
	pc[0] = 2 * 2;
	pc[1] = 6 * 2;
	k     = 0;
	for(int from = PieceListStart(pDis->pos,RXIANG); from > 0x32; from = NextPiece(pDis->pos,from)){
		TCHAR x = StoX(from) - 3 + '0';
		TCHAR y = StoY(from) - 3 + '0';
	   pchess[pc[k]    ] = x;
	   pchess[pc[k] + 1] = y;
	   k++;	  
	}
	//红仕
	pc[0] = 3 * 2;
	pc[1] = 5 * 2;
	k     = 0;
	for(int from = PieceListStart(pDis->pos,RSHI); from > 0x32; from = NextPiece(pDis->pos,from)){
		TCHAR x = StoX(from) - 3 + '0';
		TCHAR y = StoY(from) - 3 + '0';
	   pchess[pc[k]    ] = x;
	   pchess[pc[k] + 1] = y;
	   k++;	  
	}
	//红炮
	pc[0] = 9  * 2;
	pc[1] = 10 * 2;
	k     = 0;
	for(int from = PieceListStart(pDis->pos,RPAO); from > 0x32; from = NextPiece(pDis->pos,from)){
		TCHAR x = StoX(from) - 3 + '0';
		TCHAR y = StoY(from) - 3 + '0';
	   pchess[pc[k]    ] = x;
	   pchess[pc[k] + 1] = y;
	   k++;	  
	}
	//红帅
	pc[0] = 4 * 2;
	pc[1] = 4 * 2;
	k     = 0;
	for(int from = PieceListStart(pDis->pos,RKING); from > 0x32; from = NextPiece(pDis->pos,from)){
		TCHAR x = StoX(from) - 3 + '0';
		TCHAR y = StoY(from) - 3 + '0';
	   pchess[pc[k]    ] = x;
	   pchess[pc[k] + 1] = y;
	   k++;	  
	}
	//兵
	pc[0] = 11*2;
	pc[1] = 12*2;
	pc[2] = 13*2;
	pc[3] = 14*2;
	pc[4] = 15*2;
	k = 0; 
	for(int from = PieceListStart(pDis->pos,RPAWN); from > 0x32; from = NextPiece(pDis->pos,from)){
		TCHAR x = StoX(from) - 3 + '0';
		TCHAR y = StoY(from) - 3 + '0';
	   pchess[pc[k]    ] = x;
	   pchess[pc[k] + 1] = y;
	   k++;	
	}

	//
	//黑车
	pc[0] = 16 * 2;
	pc[1] = 24 * 2;
	k     = 0;
	for(int from = PieceListStart(pDis->pos,BCHE); from > 0x32; from = NextPiece(pDis->pos,from)){
		TCHAR x = StoX(from) - 3 + '0';
		TCHAR y = StoY(from) - 3 + '0';
	   pchess[pc[k]    ] = x;
	   pchess[pc[k] + 1] = y;
	   k++;	  
	}
	//黑马
	pc[0] = 17 * 2;
	pc[1] = 23 * 2;
	k     = 0;
	for(int from = PieceListStart(pDis->pos,BMA); from > 0x32; from = NextPiece(pDis->pos,from)){
		TCHAR x = StoX(from) - 3 + '0';
		TCHAR y = StoY(from) - 3 + '0';
	   pchess[pc[k]    ] = x;
	   pchess[pc[k] + 1] = y;
	   k++;	  
	}
	//黑相
	pc[0] = 18 * 2;
	pc[1] = 22 * 2;
	k     = 0;
	for(int from = PieceListStart(pDis->pos,BXIANG); from > 0x32; from = NextPiece(pDis->pos,from)){
		TCHAR x = StoX(from) - 3 + '0';
		TCHAR y = StoY(from) - 3 + '0';
	   pchess[pc[k]    ] = x;
	   pchess[pc[k] + 1] = y;
	   k++;	  
	}
	//黑仕
	pc[0] = 19 * 2;
	pc[1] = 21 * 2;
	k     = 0;
	for(int from = PieceListStart(pDis->pos,BSHI); from > 0x32; from = NextPiece(pDis->pos,from)){
		TCHAR x = StoX(from) - 3 + '0';
		TCHAR y = StoY(from) - 3 + '0';
	   pchess[pc[k]    ] = x;
	   pchess[pc[k] + 1] = y;
	   k++;	  
	}
	//黑炮
	pc[0] = 25  * 2;
	pc[1] = 26  * 2;
	k     = 0;
	for(int from = PieceListStart(pDis->pos,BPAO); from > 0x32; from = NextPiece(pDis->pos,from)){
		TCHAR x = StoX(from) - 3 + '0';
		TCHAR y = StoY(from) - 3 + '0';
	   pchess[pc[k]    ] = x;
	   pchess[pc[k] + 1] = y;
	   k++;	  
	}
	//黑将
	pc[0] = 20 * 2;
	pc[1] = 20 * 2;
	k     = 0;
	for(int from = PieceListStart(pDis->pos,BKING); from > 0x32; from = NextPiece(pDis->pos,from)){
		TCHAR x = StoX(from) - 3 + '0';
		TCHAR y = StoY(from) - 3 + '0';
	   pchess[pc[k]    ] = x;
	   pchess[pc[k] + 1] = y;
	   k++;	  
	}
	//兵
	pc[0] = 27*2;
	pc[1] = 28*2;
	pc[2] = 29*2;
	pc[3] = 30*2;
	pc[4] = 31*2;
	k = 0; 
	for(int from = PieceListStart(pDis->pos,BPAWN); from > 0x32; from = NextPiece(pDis->pos,from)){
		TCHAR x = StoX(from) - 3 + '0';
		TCHAR y = StoY(from) - 3 + '0';
	   pchess[pc[k]    ] = x;
	   pchess[pc[k] + 1] = y;
	   k++;	
	}

	wcscat_s(buf, EVAL_INFO_SIZE , pchess);
	wcscat_s(buf, EVAL_INFO_SIZE , UbbListStart);

	if(isStart){
		for(int i = 0; i < pDis->pos->gply; i++){
			TCHAR mbuf[64];
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

			//sprintf_s(mbuf,sizeof(mbuf),"%d%d%d%d%s%d%d%d%d",fx,fy,tx,ty,MoveToUBBove(pDis->moveListName[i]+4),n1000,n100,n10,n);

			swprintf_s(mbuf, sizeof(mbuf) / sizeof(TCHAR), L"%d%d%d%d", fx, fy, tx, ty);

			wcscat_s(buf, EVAL_INFO_SIZE , mbuf);
		}
	}
	else{
		for(int i = pDis->pos->curStep; i < pDis->pos->gply; i++){
			TCHAR mbuf[64];
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

			//sprintf_s(mbuf,sizeof(mbuf),"%d%d%d%d%s%d%d%d%d",fx,fy,tx,ty,MoveToUBBove(pDis->moveListName[i]+4),n1000,n100,n10,n);

			swprintf_s(mbuf, sizeof(mbuf) / sizeof(TCHAR), L"%d%d%d%d", fx, fy, tx, ty);

			wcscat_s(buf, EVAL_INFO_SIZE, mbuf);
		}
	}

	wcscat_s(buf, EVAL_INFO_SIZE, UbbListEnd);



	if (!CopyTextToClipboard(buf)) {
		LogOut(_T("Cannot copy text to clipboard"));
	}
	else{
		if(isStart){
			ToEndEvent(pDis);
			LogOut(_T("\nJAVA棋局已复制到剪贴板\n"));			
		}
	}


	

//[DhtmlXQ]
//[DhtmlXQ_ver]www_dpxq_com[/DhtmlXQ_ver]
//[DhtmlXQ_init]500,350[/DhtmlXQ_init]
//[DhtmlXQ_binit]9999474859999999999999458699999999994241405299999999994384199999[/DhtmlXQ_binit]
//[DhtmlXQ_movelist64]47254262[/DhtmlXQ_movelist]
//[DhtmlXQ_refer]http%3A//ggchess.game.topzj.com/%0D%0Ahttp%3A//ggchess.game.topzj.com/viewthread.php%3Ftid%3D19292%26page%3D1%26extra%3Dpage%253D1[/DhtmlXQ_refer]
//[DhtmlXQ_generator]www.dpxq.com[/DhtmlXQ_generator]
//[/DhtmlXQ]

//客户端编程指南 棋谱局面和行棋着法均采用坐标纪录，棋盘左上角为(0,0)，右下角为(8,9)，
//比如“炮二平五”，纪录为“7747”，是最简单的程序纪录格式。
//局面格式为“车马相士帅士相马车炮炮兵兵兵兵兵车马象士将士象马车炮炮卒卒卒卒卒”的顺序，
//纪录的都为棋子坐标，没有的棋子用99代替。这个项目用来支持残局显示 
//注解：[DhtmlXQ_comment+当前着法的序号+]+注解文本+[/DhtmlXQ_comment+当前着法的序号+]
//其中DhtmlXQ_comment是注解的特征字符串。
//例如：[DhtmlXQ_comment0]这是棋谱刚打开时看到的注解[/DhtmlXQ_comment0]



}


int 
CopyTextToClipboard(TCHAR *text)
{

	dispboard_t* pDis = OBS[0];
	//BOOL bResult;                   // generic Boolean value

	int len = int(wcslen(text));

	if (len <= 0){
		LogOut(L"空字串无法复制到剪贴板！\n");
		return FALSE;
	}

	len += 1;

	if (!OpenClipboard(pDis->hwndThis))
	{
		return FALSE;
	}
	EmptyClipboard();

	HANDLE hData = ::GlobalAlloc(GMEM_MOVEABLE, (len)*sizeof(TCHAR));

	LPWSTR pData = (LPWSTR)::GlobalLock(hData);

	wcscpy_s(pData, len, text);

	GlobalUnlock(hData);

	SetClipboardData(CF_UNICODETEXT, hData);

	CloseClipboard();



	//if (!OpenClipboard(pDis->hwndThis))
	//{
	//	LogOut(L"Cannot open the Clipboard");
	//	return FALSE;
	//}

	//// Remove the current Clipboard contents
	//if (!EmptyClipboard())
	//{
	//	LogOut(L"Cannot empty the Clipboard");
	//	return FALSE;
	//}

	//if (::SetClipboardData(CF_UNICODETEXT, text) == NULL){
	//	LogOut(L"Unable to set Clipboard data");
	//	CloseClipboard();
	//	return FALSE;
	//}

	//CloseClipboard();


	///////////////////////////////////////////////////////////////////////////  
	//// 2. Open and empty clipboard. (OpenClipboard, EmptyClipboard)  
	//// 

	//if (!OpenClipboard(pDis->hwndThis)){
	//	return FALSE;
	//}

	//EmptyClipboard();

	///////////////////////////////////////////////////////////////////////////  
	//// 3. Create global buffer. (GlobalAlloc)  
	////  
	//TCHAR* lptstrCopy = (TCHAR *)HeapAlloc(GetProcessHeap(), 0, len);
 // 
	//if (lptstrCopy == NULL)
 //   {
 //       CloseClipboard();
 //       return FALSE;
 //   }

	//// Enable the privilege.

	//if (!LoggedSetLockPagesPrivilege(GetCurrentProcess(), TRUE))
	//{
	//	return FALSE;
	//}


 //   /////////////////////////////////////////////////////////////////////////  
 //   // 5. Copy text to the buffer. (strcpy)  
 //   //   
 //
 //   wcscpy_s(lptstrCopy,len, text);

 //   /////////////////////////////////////////////////////////////////////////  
 //   // 6. Unlock the buffer. (GlobalUnlock)  
 //   //   

 //  // GlobalUnlock(hglbCopy);

 //  /////////////////////////////////////////////////////////////////////////  
 //  // 7. Set buffer data to clipboard. (SetClipboardData)  
 //  //   

	//SetClipboardData(CF_TEXT, lptstrCopy);

	//bResult = HeapFree(GetProcessHeap(), 0, lptstrCopy);

 //  if (bResult != TRUE)
 //  {
	//   _tprintf(_T("Call to HeapFree has failed (%u)\n"), GetLastError());
 //  }


 //    /////////////////////////////////////////////////////////////////////////  
 //    // 8. Close clipboard. (CloseClipboard)  
 //    //   
 //
 //    CloseClipboard();
 //


//  dispboard_t* pDis = OBS[0];
//  /* some (most?) of the error checking may be overkill, 
//   * but hey, this is Windows 
//   */
//  HGLOBAL hGlobalMem;
//  LPVOID lpGlobalMem;
//  BOOL locked;
//#ifdef DEBUG_USE_DEBUG_FILE
//  UINT lockCount;
//#endif
//  DWORD err;
//
//  int a = wcslen(text)+2;
//
//  hGlobalMem = GlobalAlloc(GHND, a);
//  if (hGlobalMem == NULL) {
//	  LogOut(L"Unable to allocate memory for clipboard.");
//    return FALSE;
//  }
//  lpGlobalMem = GlobalLock(hGlobalMem);
//  if (lpGlobalMem == NULL) {
//	  LogOut(L"Unable to lock clipboard memory.");
//    GlobalFree(hGlobalMem);
//    return FALSE;
//  }
//  //lstrcpy((LPSTR)lpGlobalMem, text);
//  StringCbCopy((LPWSTR)lpGlobalMem,wcslen(text)+1,text);
//
//#ifdef DEBUG_USE_DEBUG_FILE
//  //if (appData.debugMode) {
//    lockCount = GlobalFlags(hGlobalMem) & GMEM_LOCKCOUNT;
//    fprintf(appData.debugFP, "CopyTextToClipboard(): lock count %d\n", lockCount);
//  //}
//#endif
//
//
//  SetLastError(NO_ERROR);
//  locked = GlobalUnlock(hGlobalMem);
//  err = GetLastError();
//
//#ifdef DEBUG_USE_DEBUG_FILE
//  //if (appData.debugMode) {
//    lockCount = GlobalFlags(hGlobalMem) & GMEM_LOCKCOUNT;
//    fprintf(appData.debugFP, "CopyTextToClipboard(): lock count %d\n", lockCount);
//  //}
//#endif
//
//
//  if (!locked) {
//    locked = !((err == NO_ERROR) || (err == ERROR_NOT_LOCKED));
//
//#ifdef DEBUG_USE_DEBUG_FILE
//    //if (appData.debugMode) {
//      fprintf(appData.debugFP, 
//	      "CopyTextToClipboard(): err %d locked %d\n", err, locked);
//    //}
//#endif
//
//  }
//  if (locked) {
//	  LogOut(L"Cannot unlock clipboard memory.");
//    GlobalFree(hGlobalMem);
//    return FALSE;
//  }
//  if (!OpenClipboard(pDis->hwndThis)) {
//	  LogOut(L"Cannot open clipboard.");
//    GlobalFree(hGlobalMem);
//    return FALSE;
//  }
//  if (!EmptyClipboard()) {
//	  LogOut(L"Cannot empty clipboard.");
//    return FALSE;
//  }
//  if (hGlobalMem != SetClipboardData(CF_TEXT, hGlobalMem)) {
//	  LogOut(L"Cannot copy text to clipboard.");
//    CloseClipboard();
//    GlobalFree(hGlobalMem);
//    return FALSE;
//  }
//  if (!CloseClipboard())
//	  LogOut(L"Cannot close clipboard.");
//  
  return TRUE;
}


VOID
PasteFENFromClipboard(dispboard_t *pDis)
{
  TCHAR *fen = NULL;
 
  if (!PasteTextFromClipboard(&fen, pDis)) {
	  LogOut(L"Unable to paste FEN from clipboard.");
      return;
  }

#ifdef DEBUG_USE_DEBUG_FILE
  //if (appData.debugMode) {
    fprintf(appData.debugFP, "PasteFenFromClipboard(): fen '%s'\n", fen);
  //}
#endif

	//if(fen == 

	//if(strstr(fen,"fen ") == NULL){
	//	SendToPlayerByColor("对不起，要粘贴的局面不是以 fen 开头的字符串\n", ColorSeek, FALSE);
	//	free(fen);
	//	return;
	//}

  EditPositionPasteFEN(fen, pDis); /* call into backend */

  // ********************************
  pDis->book_num = 0; 

  if(pDis->gameMode == BeginningOfGame){
	  pDis->gameMode = EditGame;
  }

  //pDis->IsFenGame = TRUE; 
 

  swprintf_s(pDis->pgn->start_fen,sizeof(pDis->pgn->start_fen)/sizeof(TCHAR),L"%s",fen);

  FillBookbyPos(pDis,MST->book);

  free(fen);
}


VOID
PasteGameFromClipboard(dispboard_t* pDis)
{
  /* Write the clipboard to a temp file, then let LoadGameFromFile()
   * do all the work.  */
  //char *buf;
  //FILE *f;
  //size_t len;
  //if (!PasteTextFromClipboard(&buf, pDis)) {
  //  return;
  //}
  //if (!pasteTemp) {
  //  pasteTemp = _tempnam(NULL, "wbpt");
  //}
  ////f = fopen(pasteTemp, "w");
  //fopen_s(&f,pasteTemp, "w");
  //if (!f) {
  //  DisplayError("Unable to create temporary file.", 0);
  //  return;
  //}
  //len = fwrite(buf, sizeof(char), strlen(buf), f);
  //fclose(f);
  //if (len != strlen(buf)) {
  //  DisplayError("Error writing to temporary file.", 0);
  //  return;
  //}
  //LoadGameFromFile(pasteTemp, 0, "Clipboard", TRUE);
}


int 
PasteTextFromClipboard(TCHAR **text, dispboard_t* pDis)
{
	//dispboard_t* pDis = OBS[0];
	/* some (most?) of the error checking may be overkill, 
	* but hey, this is Windows 
	*/
	HANDLE hClipMem;
	LPVOID lpClipMem;
	BOOL locked = FALSE;
	DWORD err;
	UINT lockCount;

	if (!OpenClipboard(pDis->hwndThis)) {
		LogOut(L"Unable to open clipboard.");
		return FALSE;
	}
	hClipMem = GetClipboardData(CF_UNICODETEXT);
	if (hClipMem == NULL) {
		CloseClipboard();
		LogOut(L"No text in clipboard.");
		return FALSE;
	}
	lpClipMem = GlobalLock(hClipMem);
	if (lpClipMem == NULL) {
		CloseClipboard();
		LogOut(L"Unable to lock clipboard memory.");
			return FALSE;
	}
	//*text = (TCHAR *) malloc(GlobalSize(hClipMem)+1);

	*text = (TCHAR *)malloc((GlobalSize(hClipMem) + 1)*sizeof(TCHAR));
	if (!*text) {
		LogOut(L"Unable to allocate memory for text string.");
		CloseClipboard();
		return FALSE;
	}
	//lstrcpy(*text, (LPCSTR)lpClipMem);
	StringCbCopy(*text, (lstrlen((LPCWSTR)lpClipMem) + 1)*sizeof(TCHAR), (LPCWSTR)lpClipMem);

	SetLastError(NO_ERROR);

	/*suggested by Wilkin Ng*/
	lockCount = GlobalFlags(hClipMem) & GMEM_LOCKCOUNT;
	if (lockCount) {
		locked = GlobalUnlock(hClipMem);
	}

	err = GetLastError();

	if (!locked) {
		locked = !((err == NO_ERROR) || (err == ERROR_NOT_LOCKED));
	}
	if (locked) 
		LogOut(L"Unable to unlock clipboard memory.");

	if (!CloseClipboard())
		LogOut(L"Unable to close clipboard.");

	return TRUE;
}

VOID
DeleteClipboardTempFiles()
{
  if (copyTemp) remove(copyTemp);
  if (pasteTemp) remove(pasteTemp);
}
