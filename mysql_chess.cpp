#include "stdafx.h"
#include "chess.h"
#include "data.h"

#ifdef USE_MYSQL_DATABASE
void  
initializeMySql(void){
	//
	
	if(appData.sql_installed){
		if(mysql_init(&DIS.mysql) == NULL){
            LogOut(ColorTell,"不能初始化MYSQL数据库连接!!, 请确认MYSQL有没安装....\n", true); 
		}
        else{
			/*pmycon = MysqlCreateConnect(&mysql,sql_host,
			sql_user,sql_pass,sql_db,sql_port);*/	

			if(mysql_real_connect(&DIS.mysql,appData.sql_host,
				appData.sql_user,appData.sql_pass,appData.sql_db_chess,
				appData.sql_port,NULL,0) != NULL){
					mysql_set_character_set(&DIS.mysql, MYSQLCHAESET);
					//DispLog("初始化Mysql数据库成功!");
					//DispLog(DIS.mysql.server_version);
                    LogOut(ColorShout,"初始化Mysql数据库成功!", true);
                    LogOut(ColorTell, DIS.mysql.server_version, true);
                    LogOutput("\n",1,FALSE); //回车换行
			}
			else{
				//DispLog("初始化Mysql数据库失败!");
                LogOut(ColorShout,"初始化Mysql数据库失败!\n", true);
                //LogOutput("\n",1,FALSE); //回车换行
			}
		}
	}
	else{
		//DispLog("MySql数据库未加载！！");
        LogOut(ColorTell,"MySql数据库未加载！！\n", true);
        //LogOutput("\n",1,FALSE); //回车换行
	}
}
#endif





#ifdef USE_MYSQL_DATABASE

bool					//isUpdate 发现相同，是否要更新
MysqlSaveGGqj(GameQJ *pgg, MYSQL* mycon, bool isUpdate){
	char qbuf[1536];
	int samenum;
	int qjid;
	MYSQL_RES *res;

	//先得判断一下插入的棋谱是否正常
	if(false == IsGGqjNormal(pgg)){
		//DispLog("要保存的棋谱不正常哇!!");
        LogOut(ColorTell,"要保存的棋谱不正常哇!!\n", false);
        //LogOutput("\n",1,FALSE) //回车换行
		return false;
	}

	//先将棋谱处理一下
	
	for(int i=0; i<pgg->qipulen; i++){  
		//并将棋谱反过来一下,这样就不太可能有相同的了
		qbuf[pgg->qipulen-i-1] = P90ASC[pgg->qipu[i]];
	}
	memcpy(pgg->qipu,qbuf,pgg->qipulen);
	//再判断一下,有没有相同的棋谱在里面,如有则更新一下,没有,则加入
	StringCbPrintf(qbuf,sizeof(qbuf),
		"select qjid from ggqj where qipu = '%s' limit 1",pgg->qipu);
	if(mysql_query(mycon,qbuf)){
		//int kkk=0;
		return false;
	}
	res		= mysql_store_result(mycon);
    samenum	= (int)mysql_num_rows(res);

	//MYSQL_FIELD *field = mysql_
	//MYSQL_ROW mysql_fetch_row(MYSQL_RES *result) 
	if(samenum>0){
		MYSQL_ROW myrow = mysql_fetch_row(res);
		qjid = atoi(myrow[0]);
	}

	mysql_free_result(res);
	res = NULL;

	if(samenum >0){								//有相同的棋局
		qbuf[0] = 0;
		//StringCbPrintf(qbuf, sizeof(qbuf),
		//	"发现有 %d 局相同的棋局在棋库中!",samenum);
		//DispLog(qbuf);
		//更新一下棋局
		//SendMessage(hStatusBar,SB_SETTEXT,StaBarCom,(LPARAM)buf);
		if(isUpdate){
			StringCbPrintf(qbuf,sizeof(qbuf),
				"update ggqj set rname='%s', relo=%d,bname='%s',belo=%d,score=%d,result='%s',ischecked='%d',islearned='%d',addr='%s',note='%s' where qjid=%d",
				pgg->Rname,pgg->Relo,pgg->Bname,pgg->Belo,pgg->score,pgg->resultDetails,pgg->isChecked,pgg->isLearned,pgg->from,pgg->note,qjid);
			if(mysql_query(mycon,qbuf)){
				//DispLog("UPDATE qiju 失败! <MysqlSaveGGqj>"); /*pgg->isChecked*/
				return false;
			}else{
				StringCbPrintf(qbuf,MSG_SIZ,"更新棋库棋局编号：%d 成功！相同数：%d",qjid,samenum);
				//DispLog(qbuf);
				//SendMessage(hStatusBar,SB_SETTEXT,StaBarCom,(LPARAM)qbuf);
				//DispLog("成功更新了一局棋局到MYSQL数据库");
			}
		}
	}
	else{
		StringCbPrintf(qbuf,sizeof(qbuf),
			"insert into ggqj (qipu,rname,relo,bname,belo,score,result,ischecked,islearned,addr,note) values ('%s','%s',%d,'%s',%d,%d,'%s','%d','%d','%s','%s')",
			pgg->qipu,pgg->Rname,pgg->Relo,pgg->Bname,pgg->Belo,pgg->score,pgg->resultDetails,pgg->isChecked,pgg->isLearned,pgg->from,pgg->note);
		if(mysql_query(mycon,qbuf)){
			//DispLog("INSERT qiju 失败! <MysqlSaveGGqj>");
			return false;
		}else{
			//DispLog("成功插入了一局棋局到MYSQL数据库");
		}
	}
	return true;
}
bool //得到一局未校对的棋局
MysqlGetOneUncheckGGqj(GameQJ *pgg, MYSQL* mycon){
	
	if (DIS.gameMode != BeginningOfGame) {			//不是刚开始游戏
		GameReset(FALSE, TRUE);
	}
	
	
	//char qbuf[1000];
	MYSQL_RES	*res;
	bool		isok		= false;
	int			num			= 0;
    char		qbuf[1536];
	//StringCbPrintf(qbuf,sizeof(qbuf),
	//	"select * from ggqj where ischecked = 0 order by qjdi desc");
	//  "select * from ggqj where ischecked = 1 and islearned = 0 order by qjid desc LIMIT 0,1"

	if(mysql_query(mycon,"select * from ggqj where ischecked = 0 order by qjid desc LIMIT 1")){
	//if(mysql_query(mycon,"select * from ggqj where score = 80 and ischecked = 1 and islearned = 0 order by qjid desc LIMIT 0,1")){
		return false;
	}
	res = mysql_use_result(mycon);
    MYSQL_ROW myrow = mysql_fetch_row(res);
	if(myrow == NULL){
		//DispLog("当前已没有未校对的棋谱了!");
		return false;
	}
	//得到棋谱和内容
	pgg->qjid = atoi(myrow[0]);
	//StringCbPrintf(pgg->qipu,sizeof(pgg->qipu),  myrow[1]);
	int len = (int)strlen(myrow[1]);
	memcpy(pgg->qipu,myrow[1],len);
	pgg->qipu[len] = 0;

	StringCbPrintf(pgg->Rname,sizeof(pgg->Rname),myrow[2]);
	pgg->Relo = atoi(myrow[3]);
	StringCbPrintf(pgg->Bname,sizeof(pgg->Bname),myrow[4]);
	pgg->Belo		= atoi(myrow[5]);
	pgg->score		= atoi(myrow[6]);
	StringCbPrintf(pgg->resultDetails,sizeof(pgg->resultDetails), myrow[7]);
	pgg->isChecked  = atoi(myrow[8]);
	pgg->isLearned  = atoi(myrow[9]);
	StringCbPrintf(pgg->from,sizeof(pgg->from), myrow[10]);
	StringCbPrintf(pgg->note,sizeof(pgg->note), myrow[11]);

	pgg->qipulen  = (int)strlen(pgg->qipu);
    //还原一下棋谱
	for(int i=0; i<pgg->qipulen; i++){
		//pgg->qipu[i] = P90ASC[pgg->qipu[i]];
		//qbuf[pgg->qipulen-i-1] = P90ASC[pgg->qipu[i]];
		qbuf[i] = ASCP90[pgg->qipu[pgg->qipulen-i-1]];
	}
	memcpy(pgg->qipu,qbuf,pgg->qipulen);   //不用加 ‘0’了

	mysql_free_result(res);
	res = NULL;

	

	LoadGameOneGameFromMysql(pgg,true);
   
	return isok;
}

bool         //得到棋库中一个局面的局面分数哇
MysqlGetOneFaceScore(position_t* pos, bool isWhiteGo,qkface_t *pf, MYSQL *my){
	////struct qkface_t {
	////	int  qnum;
	////	int  qsc;
	////	char qf32[36];   //miroronly
	////};
	//pf->qsc = SCORE_NO;
	//char qbuf[512];
	//pf->qf32[32] = 0;//加上结束标志哇
	//FindMirrorOnly(b90,(int*)qbuf,isWhiteGo);	
	//for(int i=0; i<32; i++){
	//	pf->qf32[i] = P90ASC[qbuf[i]];   //得到ASCII
	//}
 //   
	//MYSQL_RES *res;
	//
	//StringCbPrintf(qbuf,512,"SELECT qnum,qsc FROM tface WHERE qf32='%s' LIMIT 1",pf->qf32);

	//if(mysql_query(my,qbuf)){
	//	return false;
	//} 
	//res = mysql_use_result(my);
	//MYSQL_ROW myrow = mysql_fetch_row(res);
	//if(myrow == NULL){			
	//	mysql_free_result(res);
	//	res = NULL;
	//	return false;
	//}
	////pgg->Belo		= atoi(myrow[5]);
	//pf->qnum = atoi(myrow[0]);
	//pf->qsc  = atoi(myrow[1]);

	//mysql_free_result(res);
	//res = NULL;
    
	return true;
}
bool		//将当前这个局面存入棋库 
MysqlSaveOneFace(position_t* pos,bool isWhiteGo,qkface_t *pf, MYSQL *my){	
	//char qbuf[MSG_SIZ];
	////MYSQL_RES *res;
	////int samenum;
	////#define   SCORE_NO		101
	////#define   SCORE_B_WIN		0
	////#define   SCORE_B_GOOD	35
	////#define   SCORE_B_LITTLE	20
	////#define	SCORE_BALANCE   50
	////#define   SCORE_R_LITTLE	68
	////#define   SCORE_R_GOOD	80
	////#define   SCORE_R_WIN		100

	//if((pf->qsc == 101) || (pf->qsc != 0 && pf->qsc != 20 && pf->qsc != 35 && pf->qsc != 50
	//	&& pf->qsc != 68 && pf->qsc != 80 && pf->qsc != 100)){
	//	MessageBox(hwndMain,"要保存的得分不正确哇...","出错啦...",MB_OK);
	//	return false;
	//}

	//FindMirrorOnly(b90,(int*)qbuf,isWhiteGo);  //	void   //找到当前B90的唯一D8
	//for(int i=0; i<32; i++){
	//	pf->qf32[i] = P90ASC[qbuf[i]];   //得到ASCII
	//}
	//pf->qf32[32] = 0;        // 加上一个结尾
	////pf->qnum     = 1;
	//if((!isWhiteGo && pf->qsc < SCORE_B_LITTLE) || (isWhiteGo && pf->qsc > SCORE_R_LITTLE))
	//{		//删除不好的局面
	//	StringCbPrintf(qbuf,sizeof(qbuf),"delete from tface where qf32='%s'",pf->qf32);
	//	if(mysql_query(my,qbuf)){
	//		return false;
	//	}
	//	return true;
	//}
	////先插入局面,如果不成功,就表示已有局面,就将局面数加1
	//StringCbPrintf(qbuf,sizeof(qbuf),"insert into tface (qsc,qf32) value (%d,'%s')",pf->qsc,pf->qf32);
	//if(mysql_query(my,qbuf)){
	//	//可能已有局面,
	//	StringCbPrintf(qbuf,sizeof(qbuf),"update tface set qnum=qnum+1,qsc=%d where qf32='%s'",pf->qsc,pf->qf32);
	//	if(mysql_query(my,qbuf)){
	//		return false;
	//	}
	//}
	return true;	
}
bool 
MysqlGetScoreFromQkFaces(position_t* pos,bool isWhiteGo,qkface_t *pf, MYSQL *my){
    return false;
	//list_t list;	
	//int presc = pf->qsc;					   //保存原来的得分
	//int temp;
	//bool isScoreInQK = false;
	//gen_legal_moves(&list,b90,isWhiteGo);		//产品所有的走步


	//if(isWhiteGo){								//这个局面是红的走
	//	temp = 0;
	//	for(int i=0; i<list.size; i++){
	//		//走一步
	//		sq_t from		= MOVE_FROM(list.move[i]);
	//		sq_t to			= MOVE_TO(list.move[i]);
	//		sq_t tochess	= b90[to];
	//		b90[to]			= b90[from];
	//		b90[from]		= NOCHESS;
	//		if(MysqlGetOneFaceScore(b90,false,pf,my)){	//如果有得分
	//			isScoreInQK = true;
	//			if(pf->qsc > temp){
	//				temp = pf->qsc;
	//			}
	//		}			
	//		//还原
	//		b90[from]		= b90[to];
	//		b90[to]         = tochess;
	//		if(temp == 100){		//这个局面是红输了哇
	//			break;
	//		}
	//	}
	//	//判断当前得分 pf->qsc = sc;
	//	if(isScoreInQK){
	//		pf->qsc = temp;
	//	}
	//	else{
	//		pf->qsc = presc;
	//	}
	//}
	//else{	//这个局面是黑的走	
	//	temp = 100;
	//	for(int i=0; i<list.size; i++){
	//		//走一步
	//		sq_t from		= MOVE_FROM(list.move[i]);
	//		sq_t to			= MOVE_TO(list.move[i]);
	//		sq_t tochess	= b90[to];
	//		b90[to]			= b90[from];
	//		b90[from]		= NOCHESS;
	//		if(MysqlGetOneFaceScore(b90,true,pf,my)){	//如果有得分
	//			isScoreInQK = true;
	//			if(pf->qsc < temp){
	//				temp = pf->qsc;
	//			}
	//		}			
	//		//还原
	//		b90[from]		= b90[to];
	//		b90[to]         = tochess;
	//		if(temp == 0 ){		//这个局面是黑输了哇
	//			break;
	//		}
	//	}
	//	if(isScoreInQK){
	//		pf->qsc = temp;
	//	}
	//	else{
	//		pf->qsc = presc;
	//	}
	//	//判断当前得分
	//}

	//return MysqlSaveOneFace(b90,isWhiteGo,pf,my);
	//#define   SCORE_NO		101
	//#define   SCORE_B_WIN		0
	//#define   SCORE_B_GOOD	35
	//#define   SCORE_B_LITTLE	20
	//#define	SCORE_BALANCE   50
	//#define   SCORE_R_LITTLE	68
	//#define   SCORE_R_GOOD	80
	//#define   SCORE_R_WIN		100

   
	
}


bool //得到一局已校对的棋局来学习一下
MysqlGetOneCheckedAndLearn(GameQJ *pgg, MYSQL *my){

    return false;

	//MYSQL_RES *res;
	//bool isok = false;
	//char qbuf[1536];
	////检查数据库有没有未学习的棋局哇

	//if(mysql_query(my,"select * from ggqj where ischecked = 1 and islearned = 0 order by qjid desc LIMIT 0,1")){
	////if(mysql_query(my,"select * from ggqj where score = 80 and ischecked = 1 and islearned = 0 order by qjid desc LIMIT 0,1")){
	//	return false;
	//}	
	//res = mysql_use_result(my);
	//MYSQL_ROW myrow = mysql_fetch_row(res);
	//if(myrow == NULL){
	//	DispLog("当前已没有校对好的的棋谱了!");
	//	return false;
	//}
	////得到棋谱和内容
	//pgg->qjid = atoi(myrow[0]);
 //   int len = (int)strlen(myrow[1]);
	//memcpy(pgg->qipu,myrow[1],len);
 //   
	//pgg->qipulen   = len;
	//pgg->qipu[len] = 0;				//加上结尾哇
	////StringCbPrintf(pgg->Rname,sizeof(pgg->Rname),myrow[2]);
	////pgg->Relo = atoi(myrow[3]);
	////StringCbPrintf(pgg->Bname,sizeof(pgg->Bname),myrow[4]);
	////pgg->Belo		= atoi(myrow[5]);
	//pgg->score		= atoi(myrow[6]);
	////StringCbPrintf(pgg->resultDetails,sizeof(pgg->resultDetails), myrow[7]);
	////pgg->isChecked  = atoi(myrow[8]);
	////pgg->isLearned  = atoi(myrow[9]);
	////StringCbPrintf(pgg->from,sizeof(pgg->from), myrow[10]);
	////StringCbPrintf(pgg->note,sizeof(pgg->note), myrow[11]);

	//////还原一下棋谱
	//for(int i=0; i<pgg->qipulen; i++){
	//	//pgg->qipu[i] = P90ASC[pgg->qipu[i]];
	//	//qbuf[pgg->qipulen-i-1] = P90ASC[pgg->qipu[i]];
	//	qbuf[i] = ASCP90[pgg->qipu[pgg->qipulen-i-1]];
	//}
	//memcpy(pgg->qipu,qbuf,pgg->qipulen);   //不用加 ‘0’了

	//mysql_free_result(res);
	//res = NULL;
 //   
	////以上得到了一局校对好了的棋谱
 //   Board90 b90;
	//bool    who = D8ToB90((int*)pgg->qipu,b90);	//谁先走,并求得开始局面

	//char *pm		= pgg->qipu+32;		//棋步指针
	//char *pend		= pgg->qipu + pgg->qipulen;
	//sq_t from;
	//sq_t to;
	//sq_t Eat[1000];                     //保存吃掉的棋子
	//qkface_t qkface;
	//int num = (pgg->qipulen-32)/2;           //棋步数目
	//if(who){
	//	//走到最后
	//	for(int i=0; i<num; i++){
	//		from		= *(pm+i*2);
	//		to			= *(pm+i*2+1);
	//		Eat[i]		= b90[to];
	//		b90[to]		= b90[from];
	//		b90[from]	= NOCHESS;
	//		who        ^= 0x01;
	//	}
	//	//向前返回  
	//	//qkface.qsc = pgg->score;   //最后一步,放上得分
	//	for(int i=(num-1); i>=0; i--){	
	//		qkface.qsc = pgg->score;   
	//		MysqlGetScoreFromQkFaces(b90,who,&qkface,my);			
	//		who         ^= 0x01;
	//		from         = *(pm+i*2);
	//		to			 = *(pm+i*2+1);
	//		b90[from]    = b90[to];
	//		b90[to]      = Eat[i];
	//		//qkface.qsc   = SCORE_NO;
	//	}		
	//}
	//else{
	//	MessageBox(hwndMain,"本棋局是黑的先走哇！","提醒一下",MB_OK);
	//	return false;
	//}
	////将这个棋局变为学习过了
	////"update ggqj set rname='%s', relo=%d,bname='%s',belo=%d,score=%d,result='%s',ischecked='%d',islearned='%d',addr='%s',note='%s' where qjid=%d",
	//StringCbPrintf(qbuf,sizeof(qbuf),"update ggqj set islearned = 1 where qjid=%d",pgg->qjid);
	//if(mysql_query(my,qbuf)){
	//	MessageBox(hwndMain,"更新棋局失败了!!","MysqlGetOneCheckedAndLearn",MB_OK);
	//	return false;
	//}
    //return true;
}


//bool 
//TestMysqlGetOneQj(GameQJ *pgg, MYSQL *my){
//
//}

//void 
//FindZiShu(int ff[],int start,int num){
//	//for(int n=0;n<num;n++){
//		for(int i=start,n=0;n<num;i++){
//			if(i%2==0){
//				continue;
//			}
//			//判断3，5，7，9……i/2是否有i的因子
//			int j=3;
//			while(j<=i/2 && i%j!=0){
//				j+=2;
//			}
//			//若上述数都不是i的因子，则i是质数
//			if(j>i/2){
//				ff[n++] = i;
//			}
//		}
//	//}
//}
//
//void 
//FillZiShu(void){
//	//extern int ZF90[90];
//	//extern int KF32[32];
//	
//	FindZiShu(ZF90,91*91,91);
//	FindZiShu(KF32,90,32);
//
//	//以下测试一下就没有重复的情况哇
//	
//}
//
//void 
//TestIsSame(void){
//	FillZiShu();
//	F64Count = 0;
//	////判断有没有相同的局面出现哇
//	////int face[32];
//	////for(int i=0; i<32; i++){
//	////	//放入棋子
//	////	for(int k=0; k<90; k++){
//	////		face[i] = ZF90[k];
//
//	////	}
//	////}
//	////TTFACE[32]
//	////ZeroMemory(TTFACE,sizeof(TTFACE));
//	////memset(TTFACE,90,sizeof(TTFACE));
//	//for(int i=0; i<32; i++){
//	//	TTFACE[i] = 90;
//	//}
//	//int weitotal = 1;
//	//F64Count = 0;
//	////GetOneFace(TTFACE,0,0,0);
//	//while(TTFACE[31] > 0){
//	//	TTFACE[0] --;
//	//	if(TTFACE[0] > 0){	
//	//		//查看有没有相同的哇
//	//		for(int i=1; i<weitotal; i++){
//	//			if(TTFACE[0] == TTFACE[i]){
//	//				break;
//	//			}
//	//			GetOneFaceAndStore(TTFACE);		
//	//		}				
//	//	}
//	//	else{
//	//		//得退位哇
//	//		TTFACE[0] = 90;	
//	//		int i=1;
//	//		TTFACE[i] --;			
//	//		while(TTFACE[i] < 0){	//得退位		
//	//			TTFACE[i] = 90;
//	//			i++;
//	//			TTFACE[i] 
//	//		}
//	//		
//	//		
//	//		//for(int i=1; i<31; i++){
//	//		//	if(TTFACE[i] < 91){
//	//		//		break;		//不要再进位了
//	//		//	}
//	//		//	else{			//还要再进位哇
//	//		//		TTFACE[i] = 0;					
//	//		//		i++;
//	//		//		TTFACE[i] ++;
//	//		//	}
//	//		//}
//	//	}		
//	//}
//}
//
//
//void
//TestMysqlSaveOneFace(Board90 b90,bool who,MYSQL *my){
//	char qbuf[MSG_SIZ];
//	char b32[36];
////	MYSQL_RES *res;
//	FindMirrorOnly(b90,(int*)qbuf,who);
//	for(int i=0; i<32; i++){
//		b32[i] = P90ASC[qbuf[i]];   //得到ASCII
//	}
//	b32[32] = 0;
//
//	//---------------------------------------------------
//	int fint = 0;
//	for( int i=0; i<32; i++){
//		fint += ZF90[b90[i]] * KF32[i];
//	}
//	StringCbPrintf(qbuf,sizeof(qbuf),
//		"insert into intface (Fint) value (%d)",fint);
//	if(mysql_query(my,qbuf)){
//		//DispLog("INSERT face 失败! <MysqlSaveGGqj>");		
//	}else{
//		//DispLog("成功插入了一局棋局到MYSQL数据库");
//
//	}
//	//----------------------------------------------------
//
//	StringCbPrintf(qbuf,sizeof(qbuf),
//		"insert into tface (qf32) value ('%s')",b32);
//	if(mysql_query(my,qbuf)){
//		//DispLog("INSERT face 失败! <MysqlSaveGGqj>");		
//	}else{
//		//DispLog("成功插入了一局棋局到MYSQL数据库");
//
//	}
//}
//bool 
//TestMysqlSaveFace(MYSQL *my,GameQJ *pgg){
//	MYSQL_RES *res;
//	bool isok   = false;
//	char qbuf[1536];
//	if(mysql_query(my,"select * from ggqj where ischecked = 0 order by qjid desc LIMIT 1")){
//		return false;
//	}
//    res = mysql_use_result(my);
//	MYSQL_ROW myrow = mysql_fetch_row(res);
//	if(myrow == NULL){
//		return false;
//	}
//	pgg->qjid = atoi(myrow[0]);
//	int len = (int)strlen(myrow[1]);
//	memcpy(pgg->qipu,myrow[1],len);
//	pgg->qipu[len] = 0;
//
//	pgg->qipulen  = (int)strlen(pgg->qipu);
//    //还原一下棋谱
//	for(int i=0; i<pgg->qipulen; i++){
//		//pgg->qipu[i] = P90ASC[pgg->qipu[i]];
//		//qbuf[pgg->qipulen-i-1] = P90ASC[pgg->qipu[i]];
//		qbuf[i] = ASCP90[pgg->qipu[pgg->qipulen-i-1]];
//	}
//	memcpy(pgg->qipu,qbuf,pgg->qipulen);   //不用加 ‘0’了
//	mysql_free_result(res);
//	res = NULL;
//
//	char *pm		= pgg->qipu+32;		//棋步指针
//    Board90 b90;
//	sq_t from;
//	sq_t to;
//	bool    who = D8ToB90((int*)pgg->qipu,b90);	//谁先走
//	int num = (pgg->qipulen-32)/2;              //棋步数目
//	if(who){
//		//走到最后
//		for(int i=0; i<num; i++){
//			from		= *(pm+i*2);
//			to			= *(pm+i*2+1);			
//			b90[to]		= b90[from];
//			b90[from]	= NOCHESS;
//			who        ^= 0x01;
//			TestMysqlSaveOneFace(b90,who,my);
//		}		
//	}
//	else{
//		MessageBox(hwndMain,"本棋局是黑的先走哇！","提醒一下",MB_OK);
//		return false;
//	}
//	//-------------------------------------------------------------------------
//	StringCbPrintf(qbuf,sizeof(qbuf),"update ggqj set ischecked = 1 where qjid=%d",pgg->qjid);
//	if(mysql_query(my,qbuf)){
//		MessageBox(hwndMain,"更新棋局失败了!!","MysqlGetOneCheckedAndLearn",MB_OK);
//		return false;
//	}
//	//--------------------------------------------------------------------------
//
//	return true;
//}
//DWORD WINAPI 
//TestChecked_QJ_MysqlThread(LPVOID lpParam){
//	MYSQL mysql_test;
//	char buf[MSG_SIZ];
//
//	if(mysql_init(&mysql_test) == NULL){
//		DispLog("不能初始化MYSQL连接,<TestChecked_QJ_MysqlThread>");
//		goto OutTest;
//	}
//	if(NULL == mysql_real_connect(&mysql_test,appData.sql_host,
//		appData.sql_user,appData.sql_pass,appData.sql_db_chess,
//		appData.sql_port,NULL,0))	{
//			DispLog("WebToMysqlThread,不能建立MYSQL连接");
//			goto OutTest;
//	}	
//	mysql_set_character_set(&mysql_test, MYSQLCHAESET);
//
//	int testNum = 0;
//	GameQJ gg;
//	while(true){
//		if(TestMysqlSaveFace(&mysql_test,&gg) == false){
//			break;
//		}
//		testNum ++;
//		StringCbPrintf(buf,MSG_SIZ,"正在测试 %d",gg.qjid);
//		SendMessage(hStatusBar,SB_SETTEXT,StaBarCom,(LPARAM)buf);
//		if(!SendMessage(hwndToolBar,TB_ISBUTTONCHECKED,IDT_LEARN_QK,0)){
//			goto OutTest;        //又按下了导入按钮
//		}
//	}
//
//OutTest:
//	StringCbPrintf(buf,MSG_SIZ,"当前成功学习了 %d 局棋局........",testNum);
//	SendMessage(hStatusBar,SB_SETTEXT,StaBarCom,(LPARAM)buf);
//	DispLog(buf);
//	mysql_close(&mysql_test);	
//	SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_LEARN_QK,false);//将学习按钮弹出了哇
//	return 0;
//}
//void 
//TestFaceEvent(void){
//	TestIsSame();
//   	DWORD dwThreadId, dwThrdParam = 1;
//	//建立学习线程
//	HANDLE hlearnTH = CreateThread(
//		NULL,
//		NULL,
//		TestChecked_QJ_MysqlThread,
//		&dwThrdParam,
//		0,
//		&dwThreadId);
//	if(hlearnTH == NULL){
//		//StringCbPrintf(buf,MSG_SIZ,"初始WEB导入线程 %d 失败！",i);
//		DispLog("TEST棋局学习线程失败！");
//	}
//	else{
//		//StringCbPrintf(buf,MSG_SIZ,"初始WEB导入线程 %d 成功！",i);
//		DispLog("TEST棋局学习线程成功了...........！");
//		SetThreadPriority(hlearnTH,THREAD_PRIORITY_BELOW_NORMAL);
//	}	
//
//
//}

//**************************************************************************************
#endif