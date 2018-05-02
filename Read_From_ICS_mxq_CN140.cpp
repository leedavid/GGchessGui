#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"




void ParseIcsBuf_CN(char *buf){


    //char str[512];
    //int  len = (int)strlen(buf);

    //if(ICS.loggedOn == FALSE){
    //    LogOut("正在登录,请稍候....\n");
    //    
    //    //nowisnot183..
    //    if(strstr(buf,"client? :")){
    //        //SendToICSDelayed("\n", MXQ_LOG_DELAY_MS);      
    //    }
 
    //    //nowisnot183..  nowisnot183..
    //    if(strstr(buf,"Is your client in english")){
    //        SendToICSDelayed("nowis183\n", MXQ_LOG_DELAY_MS);  

    //        //SendToICSDelayed("nowisnot183\n", MXQ_LOG_DELAY_MS); 
    //    }

    //    //H7]^B(..  //H7]^B(..  Jesi[ave..
    //    else if(strstr(buf,"你不是初来乍到吗")){

    //        //str[0] = 0x48;
    //        //str[1] = 0x37;
    //        //str[2] = 0x5D;
    //        //str[3] = 0x5E;
    //        //str[4] = 0x42;
    //        //str[5] = 0x28;
    //        //str[6] = 0x0D;
    //        //str[7] = 0x0A;
    //        //str[8] = 0x00;
    //        //str[9] = 0x00;

    //        //sprintf_s(str,sizeof(str),buf);
    //        //
    //        //sprintf_s(str,sizeof(str),"yesihave\n");
    //        //sprintf_s(str,sizeof(str),"kknd1974\n");
    //        //sprintf_s(str,sizeof(str),"msnlgl\n");


    //        //SendToICSDelayed(str, MXQ_LOG_DELAY_MS);
    //        SendToICSDelayed("yesihave\n", MXQ_LOG_DELAY_MS);  

    //    }
    //    else if(strstr(buf,"登陆名(英文):")){
    //        sprintf_s(str,sizeof(str),"%s\n",DIS.third.ICS_user);
    //        SendToICSDelayed(str, MXQ_LOG_DELAY_MS);           
    //    }

    //    else if(strstr(buf,"Do you have a account?(y or n):")){
    //        SendToICSDelayed("yesihave\n", MXQ_LOG_DELAY_MS);  
    //    }
    //    

    //    else if(strstr(buf,"口令:")){
    //        sprintf_s(str,sizeof(str),"%s\n",DIS.third.ICS_pass);
    //        SendToICSDelayed(str, MXQ_LOG_DELAY_MS);  
    //    }
    //    if(buf[len-1] == '%'){
    //        SetIcsLogOk(buf);
    //        SendToICS("map\n");
    //    }

    //    SendToPlayerByColor(buf,ColorSeek,TRUE);
    //    return;
    //}


    //if(buf[len-1] == '%' || buf[len-2]  == '%'){                  //这是地方
    //    //if(ICS.getPlace == FALSE){
    //    //    ICS.getPlace = TRUE;
    //        SetIcsTitleName(buf);
    //    //}

    //    //test 

    //    //SendToPlayerByColor(&buf[2],ColorSeek,TRUE);
    //    //

    //    return;
    //}

    //if(len < 4){
    //    return;
    //}

    //ICS.index = 0;
//    if(false){
//    }
//    //
//    //{ # 第 113 桌 吴铭小卒(3弦) vs 凌云飞渡(1弦) 对 局 开 始 }
//    //{ # 第 71 桌 凌云飞渡(1弦) vs icelolly(4f) 黑 方 被 绝 杀 }  
//    //{ # 第 57 桌 长孙无忌(5f) vs 云霄阿泉(9星) 黑 方  投 子 认 负 }
//    //{ # 第 64 桌 aaggdd(1弦) vs kldk(风魔) 对 局 开 始 }
//    else if(looking_at(buf,&ICS.index,"{ # 第 @ 桌 @(@) vs @(@) @}")){
//        SendToPlayerByColor(&buf[2],ColorSeek,TRUE);
//    }
//    //{ Table 2 yyhhff(4r) Leave Red To Obs }
//    //{ Table 120 xiaoshulan(5K) Leave Black To Obs }
//    else if(looking_at(buf,&ICS.index,"{ Table @ @(@) Leave @ To Obs }")){
//        SendToPlayerByColor(&buf[2],ColorKibitz,TRUE);
//    }
//    //
//    //{ Table 120 黄天霸(4弦) Join Red From Obs }
//    else if(looking_at(buf,&ICS.index,"{ Table @ @(@) Join @ From Obs }")){
//        SendToPlayerByColor(&buf[2],ColorKibitz,TRUE);
//    }
//    //{ Table 72 Side Reset }
//    else if(looking_at(buf,&ICS.index,"{ Table @ Side Reset }")){
//        SendToPlayerByColor(&buf[2],ColorTell,TRUE);
//    }
//    
//
//    //{ + 吾乃林冲(7级)  从 北 来 了. }\015\012聚义堂%
//    else if(looking_at(buf,&ICS.index, "{ +@. }")){         //有人来了
//        SendToPlayerByColor(&buf[2],ColorShout,TRUE);
//    }
//    //  { - 义县那小子(3段)  向 西南 去了 . }
//    else if(looking_at(buf,&ICS.index, "{ -@. }")){          //有人走了
//        SendToPlayerByColor(&buf[2],ColorShout,TRUE);
//    }
//    // { * 第 63 桌 yetmee(1弦) 离 开 红 方 }                //加入棋局或离开  
//    // { * 第 7 桌 fleming(2级) 加 入 黑 方 }
//    else if(looking_at(buf,&ICS.index, "{@第 @ 桌 @ 离 开 @}")){ 
//        SendToPlayerByColor(&buf[2],ColorShout,TRUE);      
//    }
//    else if(looking_at(buf,&ICS.index, "{@第 @ 桌 @ 加 入 @}")){ 
//        SendToPlayerByColor(&buf[2],ColorShout,TRUE);      
//    }
//
//    //广告
//    // ! ! 华山圣殿:*论剑月赛*, [北丐]圣域狐狼(人王) vs [北丐]牛皮九段(日帅) 龙虎斗!!
//    else if(looking_at(buf,&ICS.index,"! ! @")){
//        SendToPlayerByColor(&buf[2],ColorKibitz,TRUE);    
//    }   
//    // # 4 帮主贴士:可以单独关闭帮派成员使用专线权利，
//    //具体办法是在在线会员或会员列表中选中该成员，
//    //然后按下“开/关专线”按纽即可关闭其使用专线权利。
//    //如果要恢复其专线权限使用同样操作即可。[当前弈天时间21:36]
//
//    else if(looking_at(buf,&ICS.index," # @")){
//        SendToPlayerByColor(&buf[2],ColorNormal,TRUE);    
//    }
//    // ^ *
//
//    else if(looking_at(buf,&ICS.index,"^ @")){
//        SendToPlayerByColor(&buf[2],ColorSShout,TRUE);
//    } 
//    else if(looking_at(buf,&ICS.index,"[ Dir     Room        Status Players ]")){
//        //if(DLG.hwndGoPlace != NULL){
//            //ICS.start_line ++;                      //跳过[ Dir     Room        Status Players ]
//            //if(ICS.start_line >= ICS_BUF_NUM){
//            //    ICS.start_line = 0;
//            //}
//
//
//
//        for(int i = 0; i < 8; i++){
//            ICS.start_line ++;                      //East <帮派>英雄楼 open 0
//            if(ICS.start_line >= ICS_BUF_NUM){
//                ICS.start_line = 0;
//            }
//            buf = ICS.buf[ICS.start_line];
//            ICS.index = 0;
//            if(looking_at(buf,&ICS.index,"@ @ @ @")){
//                //int test = 0;
//                sprintf_s(str,sizeof(str),"%s\n%s\n%s", ICS.star_match[1],
//                     ICS.star_match[2], ICS.star_match[3]);
//
//                //SetDlgItemText(HWND_CONSOLE,IDC_ICS_CONNECT,"退出");
//                SetDlgItemText(DLG.hwndGoPlace,MXQ_ICS_PLACE[i],str);
//            }
//        }
//        sprintf_s(str,sizeof(str),"当前位置\n");
//        GetWindowText(HWND_CONSOLE,&str[9],10);
//        SetDlgItemText(DLG.hwndGoPlace,MXQ_ICS_PLACE[8],str);
//            
//        //}
//        //ParseIcsBuf(ICS.buf[ICS.start_line]);
//
//        //ICS.start_line ++;
//        //if(ICS.start_line >= ICS_BUF_NUM){
//        //    ICS.start_line = 0;
//        //}
//        
//    }
//
////    ~ Room Map
////[ Dir     Room        Status Players ]
////East <帮派>英雄楼 open 0
////South NO      closed 0
////West <空地>空地盘 open 0
////North <空地>空地盘 open 0
////EastNorth <空地>空地盘 open 0
////EastSouth NO      closed 0
////WestSouth NO      closed 0
////WestNorth <残局>铁人巷 open 0
//
//    else{       //没有任何可识别选项时
//        SendToPlayer(buf,(int)strlen(buf));
//    }          

    //当前登录成功了    
}





void
read_from_ics_mxq_cn(InputSourceRef isr, VOIDSTAR closure,	char *data, int count, int error)  {

//#ifdef DEBUG_MODE 
//    //if(appData.debugMode){
//        if(!error){
//            fprintf(DIS.debugFP, "<ICS: ");
//            show_bytes(DIS.debugFP,data,count);
//            fprintf(DIS.debugFP,"\n");
//        }
//    //}
//#endif
//
//    //#define BUF_SIZE (8192)
//
//    //#define ICS_BUF_SIZE 8192
//    //#define ICS_BUF_NUM  16
//
//    //if(count > ICS_BUF_SIZE){
//    //    MessageBox(hwndMain,"ICS 缓冲区太少","Err",MB_OK);
//    //    return;
//    //}
//
//
//
//    if(count <= 0){
//        RemoveInputSource(isr);
//        LogOut("Connection closed by ICS");
//        //SetWindowText(HWND_CONSOLE,"日志信息(已断线)");
//        //sprintf_s(buf,sizeof(buf),"日志信息 帐号: %s (已断线)!",DIS.third.ICS_user);
//        SetIcsTitleName("已断线!");
//        AlreadDisConnectIcs();
//
//        //started = STARTED_NONE;
//        //parse_pos = 0;
//        //firstTime = TRUE, intfSet = FALSE;
//        //ColorClass curColor = ColorNormal;
//        //ColorClass prevColor = ColorNormal;
//        //savingComment = FALSE;
//
//        initIcs();
//    }
//
//    //下面是有数据了
//    /* If last read ended with a partial line that we couldn't parse,
//    prepend it to the new read and try again. */
//
//    //1, 将data中的数据以\015\012分段
//
//    //if(count > ICS_BUF_SIZE){
//    //    MessageBox(hwndMain,"ICS缓冲区太少","Err",MB_OK);
//    //    return;
//    //}
//
//    //char *p;
//    int  pi = 0;  
//    ICS.sstart_line = ICS.cur_line;
//    for(int i = 0; i < count; i++){
//        //if(data[i] == NULLCHAR || data[i] == 'r'){
//        //    ICS.buf[bufNum][pi++] = '\n';
//        //    ICS.buf[bufNum][pi++] = 0;
//        //    ICS.bufNum++;
//        //    pi = 0;
//        //}
//
//        if(pi > ICS_BUF_SIZE){
//            MessageBox(hwndMain,"ICS 缓冲区太少","Err",MB_OK);
//            return;
//        }
//
//        if(data[i] == '\015' && data[i+1] == '\012'){
//            i += 1;
//            goto NextLine;
//        }
//        //if(data[i] == '0' || data[i] == '\r'){
//        //    i += 0;
//        //    goto NextLine;
//        //}
//
//        ICS.buf[ICS.cur_line][pi++] = data[i];
//        continue;
//NextLine:
//
//        ICS.buf[ICS.cur_line][pi++] = '\n';
//        ICS.buf[ICS.cur_line][pi++] = 0;
//
//        //#define ICS_BUF_SIZE    8192
//        //#define ICS_BUF_NUM  16
//
//        ICS.cur_line ++;
//
//        if(ICS.cur_line >= ICS_BUF_NUM){
//            ICS.cur_line = 0;
//        }        
//        pi = 0;     //从开头开始
//
//    }
//
//    //ICS.buf[ICS.cur_line][pi++] = '\n';
//    ICS.buf[ICS.cur_line][pi++] = 0;
//
//    //再在最后一行上加上结束标志
//    ICS.cur_line ++;
//
//    if(ICS.cur_line >= ICS_BUF_NUM){
//        ICS.cur_line = 0;
//    } 
//    ICS.buf[ICS.cur_line][0] = 0;
//
//    while(ICS.buf[ICS.sstart_line][0] != 0){
//        ParseIcsBuf_CN(ICS.buf[ICS.sstart_line]);
//
//        ICS_LINE_ADD();
//
//        //ICS.start_line ++;
//        //if(ICS.start_line >= ICS_BUF_NUM){
//        //    ICS.start_line = 0;
//        //}
//    }
//    ICS.cur_line = ICS.sstart_line;
//
//
//
//    //if(count < 3){
//    //   return;
//    //}
//
//    //int len;
//    ////ICS.curNum = 0;
//    //while(p < (data + count)){
//    //    if(strstr(p,"\015\012")){
//    //        p += 2;
//    //        char *pend = strstr(p,"\015\012");
//    //        if(pend == NULL){          //只有一行
//    //            //memcpy(ICS.buf,p,strlen(p)); 
//    //            //sprintf_s(ICS.buf,data + count - p - 1,p);
//    //            len = (int)(data + count - p);
//    //            memcpy(ICS.buf,p,len);
//    //            ICS.buf[len+1] = '\n';
//    //            ICS.buf[len+2] = 0;
//    //        }
//    //        else{   
//    //           len = (int)(pend - p);
//    //           memcpy(ICS.buf,p,len); 
//    //           p = pend;
//    //           ICS.buf[len+1] = '\n';
//    //           ICS.buf[len+2] = 0;
//    //        }
//    //        ParseIcsBuf(ICS.buf);
//    //    }
//    //    else{
//    //        break;
//    //       //SendToPlayer(data,count);
//    //    }
//    //}
}






//void 


//recognized 'normal' (-1) as variant normal
//GGchess 1.0.8
//Reset(1, 0) from gameMode 0
//recognized 'normal' (-1) as variant normal
//GameEnds(0, (null), 2)
//<ICS: \015\0123OT< client? :
//<ICS: \015\012Is your client in english?(y or n):
//>ICS: noitisnot140\012
//<ICS: \015\012你不是初来乍到吗?:
//>ICS: yesihave\012
//<ICS: \015\012登陆名(英文):
//>ICS: msnlgl\012
//<ICS: \015\012口令:
//>ICS: kknd1974\012
//<ICS: \015\012聚义堂%
//<ICS:  ^                   　　 欢迎加入弈天江湖!\015\012*********************
//*******************************************\015\012!        　  
//弈天网是以擂会友的象棋江湖，笑纳各路豪杰！ \015\012!        　　   　　
//试看天下英雄，谁能一统江湖！\015\012***************************************
//*************************\015\012# 有任何建议或疑问或发现程序BUG，请给网管留言!
//\015\012^ 观看华山论剑,请登上华山绝顶一游![30分钟慢棋-9段以上]\015\012^ 
//决战慢棋,请渡船到岳阳楼施展身手![25分钟慢棋-1100+过路客]\015\012^ 决战快棋,
//请渡海到桃花岛一逞风流![10分钟快棋-1100+过路客]\015\012! 欲自设残局请买银点升级为有牌户，
//可到聚义堂设残局\015\012^ 快刀擂台-281桌，1560+ ，飞刀擂台-282桌  
//1560+\015\012****************************************************************\015\012! 
//买银点卡：点大厅的"补点"->"我要购买银点卡"打开买卡网页\015\012*****************************
//***********************************\015\012^ 新来的和对弈天功能还不大熟悉的人可以点击右侧地图区的“助”
//字图\015\012^ 标，里面有直观的客户端的图形帮助系统\015\012****************************
//************************************.\015\012^ 弈天棋缘－网上象棋专业网站（www.chesssky.net），
//欢迎您的光临！\015\012****************************************************************\015\012
//聚义堂%\015\012~ Player List\015\012[ 名字(等级) ]\015\012aaacccc(4r) aaacccc\015\012aaggdd(初级)
//aaggdd\015\012快乐的我(2r) aakuaile\015\012沧海快刀(3r) adslabcd\015\012非棋中滋味(5r) 
//ahtlhyq\015\012谭咏伦(9级) alanal\015\012anabc(4r) anabc\015\012汉水人(初级) aotian\015\012黄天霸(2级)
//appley\015\012过河小车(3级) atttta\015\012老七(5r) azhu\015\012米卡哈基宁(4r) azzlxjj\015\012决不服输(初级)
//bailinhao\015\012狼灰大(初级) bestplayer\015\012超级小黄蜂(9段) billjack\015\012宠物(5r)
//biwen\015\012丁三(5r) cccpzj\015\012华山论箭(4级) cghabc\015\012上党一家(3r) chaoren\015\012棋力马马虎(2级)
//chengweyin\015\012海浪无言(5r) chunxiao\015\012不怕强敌(6r) chysh\015\012czdxsb(3r) 
//czdxsb\015\012当爱已成米(9段) daycm\015\012超级奥特曼(4r) dong\015\012一凡(初级) 
//dudulaile\015\012斗兽特师(5r) elmo\015\012魔王尊者(9级) fefefefe\015\012飞奔飞天(2段) 
//feiben\015\012凌云飞渡(2级) feidu\015\012大臣猎虎(初级) fffgggfg\015\012fleming(2级) 
//fleming\015\012双刀龙旋风(初级) frankdu\015\012抚顺第一(7段) fsjo\015\012gjfaaaaaad(4r) 
//gjfaaaaaad\015\012一招惊心(4段) glpglp\015\012gongqk(4r) gongqk\015\012温侯吕布(3级) 
//guinfirst\015\012很喜欢下棋(3级) guokai\015\012guozhu(4r) guozhu\015\012gzfd(5r) gzfd\015\012大学(初级)
//haoping\015\012独创天蚕(5级) himwerttui\015\012广西蓝向农(5r) hjhdr\015\012呵叽咳嘛(2级) 
//hjhmang\015\012hualeyi(3r) hualeyi\015\012和平使命(4r) huangxi\015\012二三小门口(初级) 
//huuua\015\012胡大刀(6级) huyong\015\012寒流几何(2r) hyklh\015\012icelolly(5r) 
//icelolly\015\012iikkmmiikk(4r) iikkmmiikk\015\012捷波惊云(3级) jbjy\015\012南方求胜(初级) 
//jerwwwww\015\012亮亮宝(3级) jiaqiba\015\012jigangxc(4r) jigangxc\015\012金韵(2r) 
//jimmy\015\012凡凡看海(2级) jingfan\015\012金威(5r) jinw\015\012金小林(5r) 
//jinxiaolin\015\012山风和(2r) jjhfzzh\015\012jjyyahg(5r) jjyyahg\015\012jovialkids(5r) 
//jovialkids\015\012大盗(5r) kikiki\015\012达旗人(5r) kisslove\015\012悠悠天使(1r) 
//kkooa\015\012kldk(3段) kldk\015\012蓝武(5r) lanwu\015\012你还敢来(5r) ldyffff\015\012冷雪下(3级) 
//lengxuejs\015\012凌峰阁上客(5级) lfgshk\015\012宇宙密探(5段) linjinmt\015\012铁腿屏风马(4级) 
//liqingquan\015\012周口一虎(2级) lishanli\015\012流通(2r) liutong\015\012lizhao(4r) 
//lizhao\015\012无敌神龙(5r) lllfffhhh\015\012啥叫飞象局(4级) lmafx\015\012如来如死(3r)
//lschew\015\012ltaoys(5r) ltaoys\015\012路边摊(4r) lululu\015\012难得胡涂(8级) 
//luwq\015\012秋风凉(3段) lxshh\015\012阳扬坨(3r) lywzy\015\012majinan(4r) majinan\015\012maker(4r) 
//maker\015\012火将(初级) maoshun\015\012象棋我的爱(5r) miping\015\012乙烯蓬布(3r) 
//mjigl\015\012名剑之笨笨(1段) mklh\015\012名自扬(1段) mmmmzz\015\012象棋老人(3级)
//mrchess\015\012你好不是(4段) msnlgl\015\012张张(4r) nedshow\015\012newcat(5r)
//newcat\015\012小小强强(3r) newcom\015\012妙手是我(9级) nshshch\015\012牛魔王之王(5r) 
//nxgnxg\015\012小欧(3级) ouxl\015\012温酒斩双雄(1段) pdsx\015\012奕林小光(3r) 
//peterliao\015\012当然就(9级) pianke\015\012暴风雨(初级) poiuj\015\012名剑之重剑(4级) 
//ppoollk\015\012傻蛋哥哥(9级) pppppppp\015\012飞天大侠(8级) qazmlp\015\012qdzfhong(初级) 
//qdzfhong\015\012幻刀无影(初级) qgom\015\012qiyujin(4r) qiyujin\015\012弃马局(5r) 
//qmjqmjqmj\015\012东湖高手(5r) qqabcd\015\012寻应(9级) qqqqqqaa\015\012西夏棋侠(4r) 
//qqqqqqs\015\012大撒发(3级) qwaszxerdf\015\012庆阳美棋(5r) qymq\015\012老裴(5r) 
//ralaopei\015\012六絃舞姬(2级) raphael\015\012风刀(2r) ruihongqin\015\012享受快感(8级) 
//shmilyfy\015\012一刀一个人(2级) sjzsmt\015\012练练(5级) tianming\015\012天津苗金顺(4r) 
//tjmjs\015\012老狗(4r) tlliu\015\012四四六六(初级) toto\015\012无恒(3级) ttttllll\015\012秘密武器(2r)
//tytyaaaaaa\015\012孙老总(4r) tyuhjk\015\012红鸡比鸡笨(2r) violence\015\012大阿老(3r) 
//vvvttt\015\012棋坛大圣(1r) wangbotaoq\015\012王二小(9级) wangcaiabc\015\012北北(2级) 
//wdyhm\015\012wlhsjsn(5r) wlhsjsn\015\012神棋不倒翁(1段) wrfhaibei\015\012五福娃(3级)
//wufuwa\015\012武内(1r) wune\015\012五泉(1r) wuquan\015\012弈帅(5r) wuysh\015\012少年元帅(3级) 
//wwssxxxx\015\012wwwsoshj(0r) wwwsoshj\015\012棋迷一号(初级) xiaodan\015\012小舒兰(9段) 
//xiaoshulan\015\012小文(初级) xiaowen\015\012星生(6级) xingsheng\015\012总管柳五(1段) 
//xqchenl\015\012新世纪棋七(4r) xsjqq\015\012新世纪太阳(月将) xsjty\015\012惊涛拍岸(5r) 
//xtflewis\015\012xuzi(4r) xuzi\015\012一意(3r) xxsxx\015\012xxxhutu(5r) xxxhutu\015\012百无聊赖(4r)
//xymasdf\015\012xyzfzs(5r) xyzfzs\015\012弈林狂人(月将) yangguanga\015\012瘦马翁(3r) 
//yanghongbo\015\012菜背篼(初级) yangwu\015\012俺村俺最嘎(6级) yccz\015\012郑努力(4级) 
//ycfengwen\015\012大蒜炒牛肉(6级) ycxycx\015\012弈棋天(5级) ydhrhutft\015\012一邓飞天(5r) 
//<ICS: \015\012{ * 第 81 桌 jjyyahg(2弦) 离 开 黑 方 }\015\012聚义堂%
//<ICS: \015\012{ # 第 41 桌 弈棋天(2弦) vs 无敌神龙(5f) 对 局 开 始 }\015\012聚义堂%
//<ICS: \015\012{ * 第 116 桌 jjyyahg(2弦) 加 入 黑 方 }\015\012聚义堂%
//<ICS: \015\012{ - 练练(5级)  走 了. }\015\012聚义堂%
//<ICS: \015\012{ # 第 117 桌 你还敢来(6f) vs 庆阳美棋(5f) 红 方  投 子 认 负 }\015\012聚义堂%
//<ICS: \015\012{ # 第 117 桌 你还敢来(6f) vs 庆阳美棋(5f) 对 局 开 始 }\015\012聚义堂%
//<ICS: \015\012{ * 第 75 桌 弈帅(5f) 离 开 红 方 }\015\012聚义堂%
//<ICS: \015\012{ * 第 73 桌 一意(5弦) 加 入 红 方 }\015\012聚义堂%
//<ICS: \015\012{ # 第 73 桌 一意(5弦) vs jigangxc(5f) 对 局 开 始 }\015\012聚义堂%
//<ICS: \015\012{ - 猪葛亮(3段)  向 东南 去了 . }\015\012聚义堂%
//<ICS: \015\012{ * 第 55 桌 kldk(风魔) 离 开 红 方 }\015\012聚义堂%
//<ICS: \015\012{ # 第 45 桌 平平君(2弦) vs 如来如死(6f) 红 方 被 绝 杀 }\015\012聚义堂%
//<ICS: \015\012{ # 第 70 桌 和平使命(2f) vs 棋逢对手上(6弦) 红 方  投 子 认 负 }\015\012聚义堂%
//<ICS: \015\012{ * 第 55 桌 kldk(风魔) 加 入 红 方 }\015\012聚义堂%
//<ICS: \015\012{ * 第 45 桌 平平君(2弦) 离 开 红 方 }\015\012聚义堂%
//<ICS: \015\012{ # 第 120 桌 小舒兰(无极) vs 总管柳五(6星) 红 方 局 超 时 }\015\012聚义堂%
//<ICS: \015\012{ * 第 45 桌 平平君(2弦) 加 入 红 方 }\015\012聚义堂%
//<ICS: \015\012{ # 第 70 桌 和平使命(2f) vs 棋逢对手上(6弦) 对 局 开 始 }\015\012聚义堂%
//<ICS: \015\012{ * 第 4 桌 义县那小子(3段) 离 开 黑 方 }\015\012聚义堂%
//<ICS: \015\012{ # 第 45 桌 平平君(2弦) vs 如来如死(6f) 对 局 开 始 }\015\012聚义堂%
//<ICS: \015\012{ - 义县那小子(3段)  向 西南 去了 . }\015\012聚义堂%
//<ICS: \015\012{ + 笑花无语(5r)  从 北 来 了. }\015\012聚义堂%
//<ICS: \015\012{ - 宇宙密探(5段) ╱◥██◣''o╱◥██◣^'''╭⌒╮⌒╮.','╱╱☆╱ 走 了. }\015\012聚义堂%
//<ICS: \015\012{ * 第 121 桌 飞奔飞天(3星) 离 开 红 方 }\015\012聚义堂%
//<ICS: \015\012{ - 傻蛋哥哥(9级)  向 东 去了 . }\015\012聚义堂%
//<ICS: \015\012{ + 义县那小子(3段)  从 西南 来 了. }\015\012聚义堂%
//<ICS: \015\012{ + 一刀杀神(7级) ≈☆≈太平天国≈☆≈天下太平≈☆≈████████ 来 了. }\015\012聚义堂%
//<ICS: \015\012{ # 第 64 桌 aaggdd(1弦) vs anabc(5f) 黑 方 被 绝 杀 }\015\012聚义堂%
//<ICS: \015\012{ * 第 55 桌 kldk(风魔) 离 开 红 方 }\015\012聚义堂%
//<ICS: \015\012{ * 第 41 桌 笑花无语(3f) 加 入 观 战 }\015\012聚义堂%
//<ICS: \015\012{ # 第 120 桌 小舒兰(无极) vs 总管柳五(6星) 对 局 开 始 }\015\012聚义堂%
//<ICS: \015\012{ * 第 64 桌 anabc(5f) 离 开 黑 方 }\015\012聚义堂%
//<ICS: \015\012{ * 第 122 桌 一刀杀神(2星) 加 入 红 方 }\015\012聚义堂%
//<ICS: \015\012{ * 第 55 桌 义县那小子(1星) 加 入 红 方 }\015\012聚义堂%
//<ICS: \015\012{ * 第 64 桌 kldk(风魔) 加 入 黑 方 }\015\012聚义堂%
//<ICS: \015\012{ # 第 42 桌 majinan(1f) vs 温酒斩双雄(9星) 黑 方 被 绝 杀 }\015\012聚义堂%
//<ICS: \015\012{ * 第 120 桌 一刀杀神(2星) 加 入 观 战 }\015\012聚义堂%
//<ICS: \015\012{ * 第 75 桌 anabc(5f) 加 入 红 方 }\015\012聚义堂%
//<ICS: \015\012{ # 第 64 桌 aaggdd(1弦) vs kldk(风魔) 对 局 开 始 }\015\012聚义堂%
//<ICS: \015\012{ * 第 120 桌 一刀杀神(2星) 离 开 观 战 }\015\012聚义堂%
//<ICS: \015\012{ * 第 116 桌 竹楷轩离(4f) 离 开 红 方 }\015\012聚义堂%
//<ICS: \015\012{ * 第 119 桌 竹楷轩离(4f) 加 入 红 方 }\015\012聚义堂%
//<ICS: \015\012{ Table 3 Side Reset }\015\012聚义堂%
//<ICS: \015\012{ Table 3 Side Reset }\015\012聚义堂%
//<ICS: \015\012{ * 第 3 桌 红鸡比鸡笨(2r) 离 开 红 方 }\015\012聚义堂%
//<ICS: \015\012{ * 第 4 桌 红鸡比鸡笨(2r) 加 入 黑 方 }\015\012聚义堂%
//<ICS: \015\012{ * 第 118 桌 过河小车(1弦) 加 入 红 方 }\015\012聚义堂%
//<ICS: \015\012{ Table 118 Side Reset }\015\012聚义堂%
//<ICS: \015\012{ # 第 18 桌 路边摊(4r) vs 幻刀无影(初级) 双 方 议 和 }\015\012聚义堂%
//<ICS: \015\012{ * 第 55 桌 义县那小子(1星) 离 开 红 方 }\015\012聚义堂%
//<ICS: \015\012{ * 第 75 桌 anabc(5f) 离 开 红 方 }\015\012聚义堂%
//<ICS: \015\012{ * 第 55 桌 强者无敌(1弦) 加 入 红 方 }\015\012聚义堂%
//<ICS: \015\012{ * 第 72 桌 悠悠天使(3f) 加 入 红 方 }\015\012聚义堂%
//<ICS: \015\012{ - 义县那小子(3段)  向 南 去了 . }\015\012聚义堂%
//<ICS: \015\012{ - 亮亮宝(3级)  走 了. }\015\012聚义堂%
//<ICS: \015\012{ * 第 4 桌 红鸡比鸡笨(2r) 离 开 黑 方 }\015\012聚义堂%
//<ICS: \015\012{ + 西风咧(初级)  从 东北 来 了. }\015\012聚义堂%
//<ICS: \015\012{ * 第 55 桌 强者无敌(1弦) 离 开 红 方 }\015\012聚义堂%
//<ICS: \015\012{ * 第 118 桌 狐绒花(8弦) 加 入 红 方 }\015\012聚义堂%
//<ICS: \015\012{ # 第 72 桌 悠悠天使(3f) vs 金小林(1f) 对 局 开 始 }\015\012聚义堂%
//<ICS: \015\012{ # 第 54 桌 少年元帅(2弦) vs 上党一家(1弦) 黑 方 被 绝 杀 }\015\012聚义堂%
//<ICS: \015\012{ * 第 55 桌 百无聊赖(5f) 离 开 观 战 }\015\012聚义堂%
//<ICS: \015\012{ # 第 67 桌 ltaoys(2f) vs 铁腿屏风马(9弦) 红 方 步 超 时 }\015\012聚义堂%
//<ICS: \015\012{ * 第 55 桌 红鸡比鸡笨(4f) 加 入 红 方 }\015\012聚义堂%
//<ICS: \015\012{ # 第 54 桌 少年元帅(2弦) vs 上党一家(1弦) 对 局 开 始 }\015\012聚义堂%
//<ICS: \015\012{ * 第 75 桌 百无聊赖(5f) 加 入 红 方 }\015\012聚义堂%%
//<ICS: \015\012{ * 第 118 桌 过河小车(1弦) 离 开 黑 方 }\015\012聚义堂%
//<ICS: \015\012{ + 吾乃林冲(7级)  从 北 来 了. }\015\012聚义堂%
//<ICS: \015\012{ # 第 100 桌 谭咏伦(2星) vs 老狗(6f) 黑 方  投 子 认 负 }\015\012聚义堂%
//<ICS: \015\012{ - 大司馬(初级)  向 南 去了 . }\015\012聚义堂%
//<ICS: \015\012{ # 第 66 桌 hualeyi(4弦) vs 汉水人(4f) 黑 方  投 子 认 负 }\015\012聚义堂%
//<ICS: \015\012{ * 第 100 桌 老狗(6f) 离 开 黑 方 }\015\012聚义堂%
//<ICS: \015\012{ * 第 81 桌 anabc(5f) 加 入 红 方 }\015\012聚义堂%
//<ICS: \015\012{ + 杨金生(8级)  来 了. }\015\012聚义堂%
//<ICS: \015\012{ + 百段花鎗(4级)  来 了. }\015\012聚义堂%
//<ICS: \015\012{ Table 81 Side Reset }\015\012聚义堂%
//<ICS: \015\012{ * 第 67 桌 铁腿屏风马(9弦) 离 开 黑 方 }\015\012聚义堂%
//<ICS: \015\012{ - 老狗(4r)  走 了. }\015\012聚义堂%
//<ICS: \015\012{ * 第 120 桌 吾乃林冲(3弦) 加 入 观 战 }\015\012聚义堂%
//<ICS: \015\012{ + 天下第一(9级)  来 了. }\015\012聚义堂%
//<ICS: \015\012{ - 西风咧(初级)  向 东北 去了 . }\015\012聚义堂%
//<ICS: \015\012{ * 第 116 桌 jjyyahg(2弦) 离 开 黑 方 }\015\012聚义堂%
//<ICS: \015\012{ + wonaigaoqi(5r)  来 了. }\015\012聚义堂%
//<ICS: \015\012{ - 冷雪下(3级)  向 东 去了 . }\015\012聚义堂%
//<ICS: \015\012{ * 第 81 桌 弈帅(5f) 加 入 红 方 }\015\012聚义堂%
//<ICS: \015\012{ * 第 100 桌 jjyyahg(2弦) 加 入 黑 方 }\015\012聚义堂%
//<ICS: \015\012{ # 第 59 桌 棋坛大圣(1f) vs 我想砍你啊(4弦) 红 方 被 绝 杀 }\015\012聚义堂%
//<ICS: \015\012{ * 第 59 桌 我想砍你啊(4弦) 离 开 黑 方 }\015\012聚义堂%
//<ICS: \015\012{ * 第 59 桌 我想砍你啊(4弦) 加 入 黑 方 }\015\012聚义堂%
//<ICS: \015\012{ # 第 100 桌 谭咏伦(2星) vs jjyyahg(2弦) 对 局 开 始 }\015\012聚义堂%
//<ICS: \015\012{ # 第 68 桌 超级小黄蜂(天罡) vs 抚顺第一(风魔) 红 方 步 超 时 }\015\012聚义堂%
//<ICS: \015\012{ * 第 81 桌 弈帅(5f) 离 开 红 方 }\015\012聚义堂%
//<ICS: \015\012{ # 第 59 桌 棋坛大圣(1f) vs 我想砍你啊(4弦) 对 局 开 始 }\015\012聚义堂%
//<ICS: \015\012{ * 第 67 桌 ltaoys(2f) 离 开 红 方 }\015\012聚义堂%
//<ICS: \015\012{ + 重见江湖(6级)  来 了. }\015\012聚义堂%
//<ICS: \015\012{ * 第 78 桌 ltaoys(2f) 加 入 红 方 }\015\012聚义堂%
//<ICS: \015\012{ + 北虎(2级)  来 了. }\015\012聚义堂%
//<ICS: \015\012{ + 飙风快车(5r)  来 了. }\015\012聚义堂%
//<ICS: \015\012{ * 第 75 桌 百无聊赖(5f) 加 入 红 方 }\015\012聚义堂%
//<ICS: \015\012{ - 杨金生(8级)  向 东北 去了 . }\015\012聚义堂%
//<ICS: \015\012{ * 第 118 桌 弈帅(5f) 加 入 黑 方 }\015\012聚义堂%
//<ICS: \015\012{ # 第 78 桌 ltaoys(2f) vs 俞诗欣(2f) 对 局 开 始 }\015\012聚义堂%
//<ICS: \015\012{ - 金韵(2r)  向 东 去了 . }\015\012聚义堂%
//<ICS: \015\012{ * 第 55 桌 红鸡比鸡笨(4f) 离 开 红 方 }\015\012聚义堂%
//<ICS: \015\012{ + 中山棋院枫(6级)  从 西南 来 了. }\015\012聚义堂%
//<ICS: \015\012{ * 第 55 桌 红鸡比鸡笨(4f) 加 入 红 方 }\015\012聚义堂%
//<ICS: \015\012{ * 第 55 桌 红鸡比鸡笨(4f) 离 开 红 方 }\015\012聚义堂%
//<ICS: \015\012{ - 中山棋院枫(6级)  向 西北 去了 . }\015\012聚义堂%
//<ICS: \015\012{ - xyzfzs(5r)  向 东南 去了 . }\015\012聚义堂%
//<ICS: \015\012{ * 第 55 桌 红鸡比鸡笨(4f) 加 入 红 方 }\015\012聚义堂%
//<ICS: \015\012{ + 余奇(3r)  来 了. }\015\012聚义堂%
//<ICS: \015\012{ # 第 117 桌 你还敢来(6f) vs 庆阳美棋(5f) 黑 方  投 子 认 负 }\015\012聚义堂%
//<ICS: \015\012{ - 铁腿屏风马(4级)  走 了. }\015\012聚义堂%
//<ICS: \015\012{ + 福利老孙(5r)  来 了. }\015\012聚义堂%
//<ICS: \015\012{ * 第 116 桌 宇宙奇侠(6f) 加 入 红 方 }\015\012聚义堂%
//<ICS: \015\012{ + 柯巴(初级)  来 了. }\015\012聚义堂%
//<ICS: \015\012{ # 第 117 桌 你还敢来(6f) vs 庆阳美棋(5f) 对 局 开 始 }\015\012聚义堂%
//<ICS: \015\012{ # 第 65 桌 孙老总(3f) vs 米卡哈基宁(5f) 红 方  投 子 认 负 }\015\012聚义堂%
//<ICS: \015\012{ * 第 55 桌 wonaigaoqi(5f) 加 入 红 方 }\015\012聚义堂%
//<ICS: \015\012{ Table 116 Clock 1-1-10 }\015\012聚义堂%
//<ICS: \015\012{ - 强者无敌(初级)  向 东南 去了 . }\015\012聚义堂%
//<ICS: \015\012{ - 福利老孙(5r)  向 南 去了 . }\015\012聚义堂%
//<ICS: \015\012{ + 文明礼貌(2r)  来 了. }\015\012聚义堂%\015\012{ Table 116 Side Reset }\015\012聚义堂%
//<ICS: \015\012{ # 第 118 桌 狐绒花(8弦) vs 弈帅(5f) 对 局 开 始 }\015\012聚义堂%
//<ICS: \015\012{ * 第 4 桌 呵叽咳嘛(2级) 离 开 观 战 }\015\012聚义堂%
//<ICS: \015\012{ * 第 75 桌 百无聊赖(5f) 离 开 红 方 }\015\012聚义堂%
//<ICS: \015\012{ * 第 3 桌 余奇(3r) 加 入 红 方 }\015\012聚义堂%
//<ICS: \015\012{ # 第 85 桌 蓝武(5f) vs qiyujin(4f) 红 方 被 绝 杀 }\015\012聚义堂%
//<ICS: \015\012{ * 第 65 桌 米卡哈基宁(5f) 离 开 黑 方 }\015\012聚义堂%
//<ICS: \015\012{ - 烈火雄心(5段) 我在岁月里改变了模样,心中的思念  还是相同的地方. 走 了. }\015\012聚义堂%
//<ICS: \015\012{ * 第 65 桌 百无聊赖(5f) 加 入 黑 方 }\015\012聚义堂%
//<ICS: \015\012{ - 红鸡比鸡笨(2r)  向 南 去了 . }\015\012聚义堂%
//<ICS: \015\012{ * 第 66 桌 hualeyi(4弦) 离 开 红 方 }\015\012聚义堂%
//<ICS: \015\012{ - 秋风凉(3段)  向 东南 去了 . }\015\012聚义堂%
//<ICS: \015\012{ # 第 65 桌 孙老总(3f) vs 百无聊赖(5f) 对 局 开 始 }\015\012聚义堂%
//<ICS: \015\012{ - hualeyi(3r)  走 了. }\015\012聚义堂%
//<ICS: \015\012{ + 决战天下(3级)  来 了. }\015\012聚义堂%
//<ICS: \015\012{ # 第 84 桌 老七(8星) vs 流通(3f) 红 方 步 超 时 }\015\012聚义堂%
//<ICS: \015\012{ + 有一点冷(初级)  来 了. }\015\012聚义堂%
//<ICS: \015\012{ # 第 85 桌 蓝武(4f) vs qiyujin(4f) 对 局 开 始 }\015\012聚义堂%
//<ICS: \015\012{ # 第 84 桌 老七(8星) vs 流通(3f) 对 局 开 始 }\015\012聚义堂%
//<ICS: \015\012{ + 史创(2级)  来 了. }\015\012聚义堂%
//GameEnds(0, (null), 2)
