#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

#include "stdafx.h"
#include "chess.h"
#include "preGen.h"

////产生解将步
//move_stack_t *generate_check_evasions(position_t *pos, move_stack_t *ms) {
//    //产生合法的解将步子
//
//    //计算出所有的将军信息哇 //不用算出两个老将对面,前面已算过了
//    //bool have           = false;
//
//#ifdef  DEBUG_EVASION_MOVE
//    //ASSERT(isTurnInCheck(pos,pos->side));    //当前局面的走子方被将车了
//    //if(!isTurnInCheck(pos,pos->side)){
//    //    board_display(pos,"解将军\n",stdout);
//    //}
//
//    ASSERT(!isTurnInCheck(pos,pos->side^0x1));  
//        
//    if(isTurnInCheck(pos,pos->side^0x1)){
//         board_display(pos,"解将军\n",stdout);
//        int test = 0;
//    }
//
//
//    move_stack_t *prePS = ms;       //保存开始的走步
//#endif
//
//    int CheckType       =0;            //马,0001, 炮 0010 兵 0100 车 1000  将军的类型
//    int CheckPieceNum   =0;            //将军的棋子的数量
//    int CheckPos256[8];                //将军的棋子的位置, 最多只可能同时有5个棋子在将哇
//    int MaLeg256[4];                   //如果是马将军,必有马腿哇 256
//
//    int PaoJiaNum       =0;            //炮架子的数目
//    int PaoJia256[4];                  //炮架子数组,因为有双炮将军哇
//    int PaoJiaChess[4];                //炮架子的棋子类型    
//    int PaoHuo256[4];                  //在将军的炮的后面的棋子
//    int PaoDir[4];                     //炮将军的方向   
//    int PaoHuoChess[4];
//
//
//    int Not256Pos[16];
//    int NotNum          =0;         //不可能解将的棋子的数量 
//    //1,别住了对方可能将军的马腿,
//    //2,后面是车 或上(下)面是将,帅,
//    //3, 第三个棋子是炮,也就是被牵制住了,不能用来解将了  
//    //   将这个棋子从P48中暂时去了,最后再还原一下,则剩下的棋子都可走动了
//
//    int NotToFile       =0;         //解将的棋子不能去的地方 File
//    int NotToRank       =0;         //将将的棋子不能去的地方 Rank
//
//    int K256Up1         =0;         //将上面第一个棋子
//    int K256Up2         =0;
//    int K256Up3         =0;
//
//    int K256Left1       =0;
//    int K256Left2       =0;
//    int K256Left3       =0;
//
//    int K256Right1      =0;
//    int K256Right2      =0;
//    int K256Right3      =0;
//
//    int K256Lo1         =0;
//    int K256Lo2         =0;
//    int K256Lo3         =0;
//
//    int checkChess;            //将我军的棋子
//    int checkSq256;            //将我军的棋子的位置
//    int checkSqX;
//    int checkSqY;
//    int tCheckDir1;             //将军的棋子的第一个方向    
//
//    int paohou256       ;
//    int paojia256       ;
//    int paojiaX         ;
//    int paojiaY         ;
//    int paohouChess     ;       //炮架后的棋子类型
//    int paojiaChess     ;
//
//    int leg256;
//    int to256;
//    int nDisp;
//
//    bool paojiaCan;
//
//    int OutCheckR = 0;  //水平方向可解将的棋格 Ranks
//    int OutCheckF = 0;  //上下方向可解将的棋格 Files  
//
//    SlideMoveStruct *psmv;
//
//    SlideMaskStruct *psF;
//    SlideMaskStruct *psR;   
//
//    if(pos->side == WHITE){   //红方要解将
//
//        int MyKing256  = PieceListStart(pos,RKING);
//        int MyKingX    = StoX(MyKing256);
//        int MyKingY    = StoY(MyKing256);
//        int ky4        = MyKing256 & 0xf0;
//
//        int MyKingFile = pos->wBitFiles[MyKingX];
//        int MyKingRank = pos->wBitRanks[MyKingY];
//
//        //得到将的上下信息
//        psmv = FileMove(MyKingY,MyKingFile);
//        //得到将上面的第一个棋子
//        K256Up1 = psmv->RookCap[DUpLeft] + MyKingX;
//        if(K256Up1 != MyKing256){
//            int chess1    = pos->b256[K256Up1];
//            if(chess1 == BCHE){
//                CheckType                       |= CheCheck;
//                CheckPos256[CheckPieceNum++]     = K256Up1;
//            }
//            else if(chess1 == BPAWN){
//                if((K256Up1 + 16) == MyKing256){
//                    CheckType                   |= PawnCheck;
//                    CheckPos256[CheckPieceNum++]     = K256Up1;
//                }
//            }
//            else if(chess1 == BPAO){
//                NotToFile  = UpMask(MyKing256) & LoMask(K256Up1);       //不能到的那个地方
//            }
//            //有了第一个棋子,才有第二个棋子哇
//            K256Up2 = psmv->CannonCap[DUpLeft] + MyKingX;
//            if(K256Up2 != MyKing256){
//                int chess2      = pos->b256[K256Up2];
//                if(chess2 == BPAO){                   //黑炮将军
//                    CheckType                       |= PaoCheck;
//                    CheckPos256[CheckPieceNum++]     = K256Up2;
//
//                    PaoJia256[PaoJiaNum]             = K256Up1;
//                    PaoJiaChess[PaoJiaNum]           = chess1;
//                    PaoDir[PaoJiaNum]                = DirUp;
//                    PaoHuo256[PaoJiaNum]             = 0;
//                    PaoJiaNum ++;
//
//                    if(chess1 == BPAO){             //炮架子是对方的黑炮,重炮将
//                        OutCheckF = UpMask(K256Up1) & LoMask(K256Up2) | yBitMask(K256Up2);
//                    }
//                    else{
//                        OutCheckF =(UpMask(MyKing256) & LoMask(K256Up2) 
//                            | yBitMask(K256Up2)) ^ yBitMask(K256Up1); // 异或的优先级高, 得加上括号哇
//                    }
//                }
//                else if(chess2 == BCHE || chess2 == BKING){  //棋子上面是黑车,或黑将,则KingUp1的棋子不能动了解
//                    if(IsWhite(chess1)){
//                        //Not48Pos[NotNum]            = chess481;
//                        Not256Pos[NotNum]           = K256Up1;
//                        //board->P48[chess481]        = 0;
//                        RemovePiece(pos, K256Up1);
//                        NotNum++;
//                    }
//                }
//                //有了第二个棋子,才有第三个棋子哇
//                K256Up3 = psmv ->SuperCap[DUpLeft] + MyKingX;                
//                if(K256Up3 != MyKingX){                   
//                    int chess3  = pos->b256[K256Up3];
//                    if(chess2 == BPAO){
//                        PaoHuo256[PaoJiaNum-1]      = K256Up3;
//                        PaoHuoChess[PaoJiaNum-1]    = chess3;
//                    }
//
//                    if(chess3 == BPAO){         //第三个棋子是黑炮,1,第二个棋子不可能解将了,                         
//                        if(IsWhite(chess2)){
//                            Not256Pos[NotNum]           = K256Up2;
//                            RemovePiece(pos, K256Up2);
//                            NotNum++;
//                        }
//                        if(IsWhite(chess1) && chess2 != BCHE && chess2 != BKING){
//                            Not256Pos[NotNum]           = K256Up1;
//                            RemovePiece(pos, K256Up1);
//                            NotNum++;                           
//                        }
//                    }
//                } 
//            }            
//        }
//        //得到将下面的第一个棋子
//        K256Lo1 = psmv->RookCap[DLoRight] + MyKingX;
//        if(K256Lo1 != MyKing256){
//            int chess1 = pos->b256[K256Lo1];
//            if( chess1 == BCHE){
//                CheckType                       |= CheCheck;
//                CheckPos256[CheckPieceNum++]     = K256Lo1;
//            }
//            else if(chess1 == BPAO){
//                NotToFile |= UpMask(K256Lo1) & LoMask(MyKing256);
//            }
//            //有了第一个棋子,才有第二个棋子哇
//            K256Lo2 = psmv->CannonCap[DLoRight] + MyKingX;
//            if(K256Lo2 != MyKing256){
//                int chess2 = pos->b256[K256Lo2];
//                if(chess2 == BPAO){
//                    CheckType                      |= PaoCheck;
//                    CheckPos256[CheckPieceNum++]    = K256Lo2;
//
//                    PaoJia256[PaoJiaNum]            = K256Lo1;
//                    PaoJiaChess[PaoJiaNum]          = chess1;                   
//                    PaoDir[PaoJiaNum]               = DirLow;
//                    PaoHuo256[PaoJiaNum]            = 0;              //暂时设为0
//                    PaoJiaNum ++;
//                    OutCheckF    = yBitMask(K256Lo2);              //只能吃炮
//                }
//                else if(chess2 == BCHE){
//                    if(IsWhite(chess1)){
//                        Not256Pos[NotNum]            = K256Lo1;
//                        RemovePiece(pos, K256Lo1);
//                        NotNum++;
//                    }
//                }
//            }
//        } //红帅下面不可能有第三个棋子 
//        //向左判断一下
//        psmv = RankMove(MyKingX,MyKingRank);
//
//        K256Left1 = psmv->RookCap[DUpLeft] + ky4;
//        if(K256Left1 != MyKing256){
//            int chess1 = pos->b256[K256Left1];
//            if(chess1 == BCHE){
//                CheckType                          |= CheCheck;
//                CheckPos256[CheckPieceNum++]        = K256Left1;
//            }
//            else if((chess1 == BPAWN) &&(K256Left1 == MyKing256-1)){
//                CheckType                          |= PawnCheck;  
//                CheckPos256[CheckPieceNum++]        = K256Left1;
//            }
//            else if(chess1 == BPAO){
//                NotToRank |= LeftMask(MyKing256) & RightMask(K256Left1);
//            }
//            //有了第一个棋子,才有第二个棋子哇
//            K256Left2 = psmv->CannonCap[DUpLeft] + ky4;
//            if(K256Left2 != MyKing256){
//                int chess2 = pos->b256[K256Left2];
//                if(chess2 == BPAO){
//                    CheckType                      |= PaoCheck;
//                    CheckPos256[CheckPieceNum++]    = K256Left2;
//
//                    PaoJia256[PaoJiaNum]            = K256Left1;
//                    PaoJiaChess[PaoJiaNum]          = chess1;                   
//                    PaoDir[PaoJiaNum]               = DirLeft;
//                    PaoHuo256[PaoJiaNum]            = 0;              //暂时设为0
//                    PaoJiaNum ++;
//
//                    if(chess1 == BPAO){
//                        OutCheckR =  RightMask(K256Left2) & LeftMask(K256Left1) | xBitMask(K256Left2);
//                    }
//                    else {
//                        OutCheckR = (RightMask(K256Left2) & LeftMask(MyKing256)  | xBitMask(K256Left2)) ^ xBitMask(K256Left1);
//                    }
//                }
//                else if(chess2 == BCHE){
//                    if(IsWhite(chess1)){
//                        Not256Pos[NotNum]           = K256Left1;
//                        RemovePiece(pos, K256Left1);
//                        NotNum++;
//                    }
//                }
//                //有了二个才有第三个
//                K256Left3 = psmv->SuperCap[DUpLeft] + ky4;
//                if(K256Left3 != MyKing256){
//                    int chess3 = pos->b256[K256Left3];
//                    if(chess2 == BPAO){
//                        PaoHuo256[PaoJiaNum-1]      = K256Left3;
//                        PaoHuoChess[PaoJiaNum-1]    = chess3;
//                    }
//                    if(chess3 == BPAO){         //第三个棋子是黑炮,1,第二个棋子不可能解将了,  
//                        if(IsWhite(chess2)){
//                            Not256Pos[NotNum]            = K256Left2;
//                            RemovePiece(pos, K256Left2);
//                            NotNum++;
//                        }
//                        if(IsWhite(chess1) && chess2 != BCHE){                        
//                            Not256Pos[NotNum]            = K256Left1;
//                            RemovePiece(pos, K256Left1);
//                            NotNum++;                        
//                        }
//                    } 
//                }
//            }
//        }
//        //向右判断一下
//        K256Right1 = psmv->RookCap[DLoRight] + ky4;
//        if(K256Right1 != MyKing256){
//            int chess1 = pos->b256[K256Right1];
//            if(chess1 == BCHE){
//                CheckType                          |= CheCheck;
//                CheckPos256[CheckPieceNum++]        = K256Right1;
//            }
//            else if((chess1 == BPAWN) &&(K256Right1 == MyKing256+1)){
//                CheckType                          |= PawnCheck;  
//                CheckPos256[CheckPieceNum++]        = K256Right1;
//            }
//            else if(chess1 == BPAO){
//                NotToRank |= LeftMask(K256Right1) & RightMask(MyKing256);
//            }
//            //有了第一个棋子,才有第二个棋子哇
//            K256Right2 = psmv->CannonCap[DLoRight] + ky4;
//            if(K256Right2 != MyKing256){
//                int chess2 = pos->b256[K256Right2];
//                if(chess2 == BPAO){
//                    CheckType                      |= PaoCheck;
//                    CheckPos256[CheckPieceNum++]    = K256Right2;
//
//                    PaoJia256[PaoJiaNum]            = K256Right1;
//                    PaoJiaChess[PaoJiaNum]          = chess1;                   
//                    PaoDir[PaoJiaNum]               = DirRight;
//                    PaoHuo256[PaoJiaNum]            = 0;              //暂时设为0
//                    PaoJiaNum ++;
//
//                    if(chess1 == BPAO){
//                        OutCheckR =  RightMask(K256Right1) & LeftMask(K256Right2) | xBitMask(K256Right2);
//                    }
//                    else {
//                        OutCheckR = (RightMask(MyKing256)  & LeftMask(K256Right2)  | xBitMask(K256Right2)) ^ xBitMask(K256Right1);
//                    }
//                }
//                else if(chess2 == BCHE){
//                    if(IsWhite(chess1)){
//                        Not256Pos[NotNum]           = K256Right1;
//                        RemovePiece(pos, K256Right1);
//                        NotNum++;
//                    }
//                }
//                //有了第二个棋子,才有第三个棋子哇
//                K256Right3 = psmv->SuperCap[DLoRight] + ky4;
//                if(K256Right3 != MyKing256){
//                    int chess3 = pos->b256[K256Right3];
//                    if(chess2 == BPAO){
//                        PaoHuo256[PaoJiaNum-1]      = K256Right3;
//                        PaoHuoChess[PaoJiaNum-1]    = chess3;
//                    }
//
//                    if(chess3 == BPAO){ //第三个棋子是黑炮,1,第二个棋子不可能解将了,                        
//                        if(IsWhite(chess2)){
//                            Not256Pos[NotNum]           = K256Right2;
//                            RemovePiece(pos, K256Right2);
//                            NotNum++;
//                        }
//                        if(IsWhite(chess1) && chess2 != BCHE){                       
//                            Not256Pos[NotNum]           = K256Right1;
//                            RemovePiece(pos, K256Right1);
//                            NotNum++;                            
//                        }
//                    }
//                }
//            }
//        }
//        //判断一下有没有马在将军哇
//
//        for(checkSq256 = PieceListStart(pos,BMA); checkSq256 > 0x32; checkSq256 = NextPiece(pos,checkSq256)){
//            int x       = horseLegTab(MyKing256 - checkSq256 + 256);
//            leg256  = checkSq256 + x;
//            int leg14;
//            if(x){                                  //马有可能将军 
//                leg14 = pos->b256[leg256];
//                if(!leg14){                         //马腿无子
//                    CheckType                       |= MaCheck;
//                    CheckPos256[CheckPieceNum]       = checkSq256;
//                    MaLeg256[CheckPieceNum]          = leg256;  //如果是马将军,必有马腿哇,为以后解将方便哇
//                    CheckPieceNum++;
//                }
//                else{                               //马腿上有棋子哇
//                    if(IsWhite(leg14)){
//                        //得判断一下,是不是已经拿走了
//                        bool isRemove = false;
//                        for(int i = 0; i < NotNum; i++){
//                            if(leg256 == Not256Pos[i]){
//                                isRemove = true;
//                                break;
//                            }
//                        }
//                        if(!isRemove){
//                            Not256Pos[NotNum]       = leg256;
//                            RemovePiece(pos, leg256);
//                            NotNum++;
//                        }
//                    }
//                }
//            }
//        }
//
//        ASSERT(CheckPieceNum!=0);      //走子方一定要被将军了 ////////////////////////////
//#if defined(DEBUG_EVASION_MOVE)
//        if(CheckPieceNum == 0){
//            board_display(pos,"ERROR 当前是红方解将,但没有棋子在将!!!!\n",stdout);
//            //return ms;
//        }
//#endif
//        //----------------------------------------------------------下面开始算解将步哇
//        checkSq256    = CheckPos256[0];
//        checkSqX      = StoX(checkSq256);
//        checkSqY      = StoY(checkSq256);  
//        tCheckDir1    = GetDir(checkSq256, MyKing256); 
//        switch(CheckType){
//case PaoCheck:              //当前是炮在将军
//    paojia256       = PaoJia256[0];
//    paojiaX         = StoX(paojia256);
//    paojiaY         = StoY(paojia256);
//    paohouChess     = PaoHuoChess[0];       //炮架后的棋子类型
//    paojiaChess     = PaoJiaChess[0]; 
//    if(PaoJiaNum > 1){  
//        int jian;
//        int tjiadir;
//        int paojia2;
//        int paocheck2;
//        if(paojiaChess >= BKING){   //不是自己的棋子
//            if(PaoJiaChess[1] >= BKING){
//                  break; //board_display(pos,"有两个黑炮同时在将！!,没法解将\n",stdout);               
//            }
//            else{
//                paojia256       = PaoJia256[1];
//                paojiaX         = StoX(paojia256);
//                paojiaY         = StoY(paojia256);
//                paohouChess     = PaoHuoChess[1];       //炮架后的棋子类型
//                paojiaChess     = PaoJiaChess[1]; 
//                paojia2         = PaoJia256[0];
//                paocheck2       = CheckPos256[0];
//                tjiadir         = GetDir(paojia2,MyKing256);
//                jian = 1;
//            }
//        }
//        else{
//            paojia2     = PaoJia256[1];
//            paocheck2   = CheckPos256[1];
//            tjiadir     = GetDir(paojia2,MyKing256);
//            jian        = 0;
//        }
//        OutCheckF = 0;
//        OutCheckR = 0; 
//        if(tjiadir & DirUp){
//            OutCheckF =(UpMask(MyKing256) & LoMask(paocheck2) 
//                | yBitMask(paocheck2)) ^ yBitMask(paojia2); // 异或的优先级高, 得加上括号哇
//        }
//        else if(tjiadir & DirLow){
//            OutCheckF = (UpMask(paocheck2) & LoMask(MyKing256)
//                | yBitMask(paocheck2)) ^ yBitMask(paojia2);
//        }
//        else if(tjiadir & DirLeft){
//            OutCheckR = (RightMask(paocheck2) & LeftMask(MyKing256) 
//                | xBitMask(paocheck2)) ^ xBitMask(paojia2);
//        }
//        else if(tjiadir & DirRight){
//            OutCheckR = (LeftMask(paocheck2) & RightMask(MyKing256) 
//                | xBitMask(paocheck2)) ^ xBitMask(paojia2);
//        }
//
//        switch(paojiaChess){    //只有红马,红仕,红相才可能解双炮将
//            uint8* lpDst;
//            int    tmp;
//case RMA:                            
//    lpDst = PreMaAndLegMove[paojia256];
//    tmp      = MOVE_FromFC(paojia256,RMA);
//    while(int to256 = *lpDst++){     //可以挡炮或吃炮                                
//        int tx    = StoX(to256);
//        int ty    = StoY(to256);
//        if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//            || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){
//                if(pos->b256[*lpDst] == 0){  //马腿没有棋子
//                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                } 
//        } 
//        lpDst++;
//    }                            
//    break;
//case RSHI:
//    lpDst = PreShiXiangAndEyeMove[paojia256];
//    tmp      = MOVE_FromFC(paojia256,RSHI);
//    while(int to256 = *lpDst++){                                
//        int tx    = StoX(to256);
//        int ty    = StoY(to256);
//        if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//            || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){ 
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//        }
//        lpDst++;
//    }
//    break;
//case RXIANG:
//    lpDst = PreShiXiangAndEyeMove[paojia256];
//    tmp      = MOVE_FromFC(paojia256,RXIANG);
//    while(int to256 = *lpDst++){                                
//        int tx    = StoX(to256);
//        int ty    = StoY(to256);
//        if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//            || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){
//                if(pos->b256[*lpDst] == 0){  //象眼上没有棋子 if(!tree->board.B256[(nSrc+nDst)>>1])
//                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                } 
//        }
//        lpDst++;
//    }
//    break;
//default:
//    break;
//        }
//    }
//    else{                   //只有一个炮在将                   
//        //int  paohou256       = 
//        //先判断一下炮架上的棋子能不能走
//        if(IsWhite(paojiaChess)){
//            if(paohouChess == BPAO){        //炮后还有炮
//                if(paojiaChess == RPAO){
//                    (ms++)->move = MOVE_FROM(paojia256,RPAO,PaoHuo256[0],BPAO);
//                }
//            }
//            else{  
//                int nSrcX = StoX(paojia256);
//                int nSrcY = StoY(paojia256);
//                int sr16  = pos->wBitRanks[nSrcY];
//                int sf16  = pos->wBitFiles[nSrcX];  
//                switch(paojiaChess){                                            //对于炮架上的棋子
//                    int     tmp;
//                    uint8*  lpDst;
//case RPAWN:     //红兵是炮架
//    tmp      = MOVE_FromFC(paojia256,RPAWN);
//    //1, 向上吃炮解将
//    if((paojia256-16) == checkSq256){  
//        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BPAO);
//    }
//    //2,左右动兵解将
//    if(paojia256<0x7b){      //过河兵才能解将哇
//        int to256 = paojia256-1;
//        int to14  = pos->b256[to256];
//        if(!IsWhite(to14)){       
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//        to256 = paojia256+1;
//        to14  = pos->b256[to256];
//        if(!IsWhite(to14)){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    break;
//case RPAO:      //红炮是炮架    //可左右解将, 上下吃子解将  
//    tmp      = MOVE_FromFC(paojia256,RPAO);
//    psmv     = RankMove(nSrcX,sr16);
//
//    //左右吃子步
//    nDisp    = paojia256 & 0xf0;    
//    to256    = psmv->CannonCap[DUpLeft] + nDisp;
//    if(to256 != paojia256){
//        int to14 = pos->b256[to256];
//        if(IsBlack(to14)){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    to256    = psmv->CannonCap[DLoRight] + nDisp;
//    if(to256 != paojia256){
//        int to14 = pos->b256[to256];
//        if(IsBlack(to14)){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    if(tCheckDir1 & (DirUp+DirLow)){
//        //左右不吃子步
//        to256 = psmv->NonCap[DUpLeft] + nDisp;
//        while(to256 != paojia256){
//            (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            to256++;
//        }
//        to256 = psmv->NonCap[DLoRight] + nDisp;
//        while(to256 != paojia256){
//            (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            to256--;
//        }
//    }
//    // 上下吃子步
//    psmv    = FileMove(nSrcY,sf16);
//    to256   = psmv->CannonCap[DUpLeft] + nSrcX;
//    if(to256 != paojia256){
//        int to14 = pos->b256[to256];
//        if(IsBlack(to14)){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    to256   = psmv->CannonCap[DLoRight] + nSrcX;
//    if(to256 != paojia256){
//        int to14 = pos->b256[to256];
//        if(IsBlack(to14)){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    if(tCheckDir1 & (DirLeft+DirRight)){    //不吃子步
//        to256 = psmv->NonCap[DUpLeft] + nSrcX;
//        while(to256 != paojia256){
//            (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            to256 += 16;
//        }
//        to256 = psmv->NonCap[DLoRight] + nSrcX;
//        while(to256 != paojia256){
//            (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            to256 -= 16;
//        }
//    }
//    break;
//case RCHE:      //红车是炮架   
//    tmp      = MOVE_FromFC(paojia256,RCHE);
//    //左右吃子步
//    psmv     = RankMove(nSrcX,sr16);
//    //左右吃子步
//    nDisp    = paojia256 & 0xf0;
//    to256    = psmv->RookCap[DUpLeft] + nDisp;
//    if(to256 != paojia256){
//        int to14 = pos->b256[to256];
//        if(IsBlack(to14)){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    to256    = psmv->RookCap[DLoRight] + nDisp;
//    if(to256 != paojia256){
//        int to14 = pos->b256[to256];
//        if(IsBlack(to14)){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    if(tCheckDir1 & (DirUp+DirLow)){        //上下将,可左右不吃子解将
//        to256 = psmv->NonCap[DUpLeft] + nDisp;
//        while(to256 != paojia256){
//            (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            to256++;
//        }
//        to256 = psmv->NonCap[DLoRight] + nDisp;
//        while(to256 != paojia256){
//            (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            to256--;
//        }
//    }
//    //上下方向解将
//    psmv  = FileMove(nSrcY,sf16);
//    to256 = psmv->RookCap[DUpLeft] + nSrcX;
//    if(to256 != paojia256){
//        int to14 = pos->b256[to256];
//        if(IsBlack(to14)){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    to256 = psmv->RookCap[DLoRight] + nSrcX;
//    if(to256 != paojia256){
//        int to14 = pos->b256[to256];
//        if(IsBlack(to14)){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    //左右将,可上下不吃子解将
//    if(tCheckDir1 & (DirLeft+DirRight)){    //不吃子步
//        to256 = psmv->NonCap[DUpLeft] + nSrcX;
//        while(to256 != paojia256){
//            (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            to256 += 16;
//        }
//        to256 = psmv->NonCap[DLoRight] + nSrcX;
//        while(to256 != paojia256){
//            (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            to256 -= 16;
//        }
//    }                                 
//    break;
//case RMA:       //红马是炮架        //马向8个方向解将 
//    tmp      = MOVE_FromFC(paojia256,RMA);
//    lpDst = PreMaAndLegMove[paojia256];
//    while(int to256 = *lpDst++){               
//        if(pos->b256[*lpDst]){  //马腿有棋子
//            lpDst++;
//            continue;
//        }
//        lpDst++;
//        int to14  =  pos->b256[to256];
//        if(IsWhite(to14)){    //是自己的的棋子
//            continue;  
//        } 
//        int tx = StoX(to256);
//        int ty = StoY(to256);
//        if(tx == MyKingX){  //走到了File上
//            if(NotToFile & yBitMask(to256)){
//                continue;
//            }
//        } 
//        else if(ty == MyKingY){
//            if(NotToRank & xBitMask(to256)){
//                continue;
//            }
//        }        
//        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//    }                                   
//    break;
//case RXIANG:    //红相是炮架
//    tmp      = MOVE_FromFC(paojia256,RXIANG);
//    lpDst  = PreShiXiangAndEyeMove[paojia256];
//    while(int to256 = *lpDst++){                                         
//        if(pos->b256[*lpDst]){  //相眼有棋子
//            lpDst++;
//            continue;
//        }
//        lpDst++;
//        int to14  =  pos->b256[to256];
//        if(IsWhite(to14)){
//            continue;
//        }  
//        int tx = StoX(to256);
//        int ty = StoY(to256);
//        if(tx == MyKingX){  //走到了File上
//            if(NotToFile & yBitMask(to256)){
//                continue;
//            }
//        }
//        else if(ty == MyKingY){
//            if(NotToRank & xBitMask(to256)){
//                continue;
//            }
//        }        
//        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//    }
//    break;
//case RSHI:      //红士是炮架
//    tmp      = MOVE_FromFC(paojia256,RSHI);
//    lpDst  = PreShiXiangAndEyeMove[paojia256];
//    while(int to256 = *lpDst++){                                         
//        int to14  =  pos->b256[to256];
//        if(IsWhite(to14)){
//            continue;
//        }
//        int tx = StoX(to256);
//        int ty = StoY(to256);
//        if(tx == MyKingX){  //走到了File上
//            if(NotToFile & yBitMask(to256)){
//                continue;
//            }
//        }
//        else if(ty == MyKingY){
//            if(NotToRank & xBitMask(to256)){
//                continue;
//            }
//        }
//        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//    }
//    break;
//default:
//    break;
//                }
//            }
//        }
//        //以下情况的棋子都不是炮架了
//        //1.红兵将黑炮将*************************************************************
//        if(tCheckDir1 & DirUp){                             //红兵只能将上面的炮将 
//            for(int nSrc256 = PieceListStart(pos,RPAWN); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){                
//
//                if(nSrc256 == paojia256){
//                    continue;
//                }
//
//                //不在炮架上的兵只能左右解将哇
//                if(nSrc256 > 0x7b){
//                    continue;
//                }
//                int tmp      = MOVE_FromFC(nSrc256,RPAWN);
//                int to256 = nSrc256+1;
//                int tx    = StoX(to256);
//                if(tx == MyKingX){
//                    if(yBitMask(to256) & OutCheckF){                        
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                    }
//                }
//                to256 = nSrc256-1;
//                tx    = StoX(to256);
//                if(tx == MyKingX){
//                    if(yBitMask(to256) & OutCheckF){                        
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                    }
//                }
//            }
//        }// End 红兵将黑炮将
//        //红仕解炮将
//        for(int nSrc256 = PieceListStart(pos,RSHI); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            if(nSrc256 == paojia256){
//                continue;
//            }
//            int tmp      = MOVE_FromFC(nSrc256,RSHI); 
//            uint8* lpDst = PreShiXiangAndEyeMove[nSrc256];
//            while(int to256 = *lpDst++){                                
//                int tx    = StoX(to256);
//                int ty    = StoY(to256);
//                if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                    || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){ 
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                }
//            }
//        }//红仕解炮将 End
//        //红相解炮将
//        for(int nSrc256 = PieceListStart(pos,RXIANG); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//
//            if(nSrc256 == paojia256){
//                continue;
//            }
//
//            int tmp         = MOVE_FromFC(nSrc256,RXIANG); 
//            uint8* lpDst    = PreShiXiangAndEyeMove[nSrc256];
//            while(int to256 = *lpDst++){                                
//                int tx    = StoX(to256);
//                int ty    = StoY(to256);
//                if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                    || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){
//                        if(pos->b256[*lpDst] == 0){  //象眼上没有棋子 if(!tree->board.B256[(nSrc+nDst)>>1])
//                            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                        } 
//                }
//                lpDst++;
//            }
//        }//红相解炮将 End
//        //红马解黑炮将
//        for(int nSrc256 = PieceListStart(pos,RMA); nSrc256 > 0x32  ; nSrc256 = NextPiece(pos,nSrc256)){
//
//            if(nSrc256 == paojia256){
//                continue;
//            }
//
//            int tmp      = MOVE_FromFC(nSrc256,RMA); 
//            uint8* lpDst = PreMaAndLegMove[nSrc256];
//            while(int to256 = *lpDst++){     //可以挡炮或吃炮                                
//                int tx    = StoX(to256);
//                int ty    = StoY(to256);
//                if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                    || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){
//                        if(pos->b256[*lpDst] == 0){  //马腿没有棋子
//                            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                        } 
//                } 
//                lpDst++;
//            }
//        }//红马解黑炮将 End
//        // 2. 红炮解黑炮将
//        for(int nSrc256 = PieceListStart(pos,RPAO); nSrc256 > 0x32 ; nSrc256 = NextPiece(pos,nSrc256)){
//
//            if(nSrc256 == paojia256){
//                continue;
//            }
//
//            int tmp   = MOVE_FromFC(nSrc256,RPAO); 
//            int nSrcX = StoX(nSrc256);
//            int nSrcY = StoY(nSrc256);       
//            psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//            psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]);
//            if(OutCheckF){                  //上下方向可以解将               
//                if(nSrcX == checkSqX){      //在同一行,只有吃包哇 
//                    if(psF->CannonCap & yBitMask(checkSq256)){
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BPAO);
//                    }
//                }
//                else{                       //不在同一列, 吃包,挡包
//                    if(OutCheckF & yBitMask(nSrc256)){  //在解将的列上
//                        if(nSrcY == checkSqY){          //在同一行
//                            if(psR->CannonCap & xBitMask(checkSq256)){
//                                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BPAO);
//                            }
//                        }
//                        else{
//                            if(psR->RookCap & xBitMask(checkSq256)){
//                                (ms++)->move =  MOVE_FromFc_to(tmp,XYtoS(checkSqX,nSrcY));
//                            }
//                        }                                      
//                    }
//                }
//            }
//            else if(OutCheckR){              //左右方向可以解将                
//                if(nSrcY == checkSqY){       //在同一行,只有吃炮
//                    if(psR->CannonCap & xBitMask(checkSq256)){
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BPAO);
//                    }
//                }
//                else{
//                    if(OutCheckR & xBitMask(nSrc256)){
//                        if(nSrcX == checkSqX){
//                            if(psF->CannonCap & yBitMask(checkSq256)){
//                                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BPAO);                            
//                            }
//                        }
//                        else{                    
//                            if(psF->RookCap & yBitMask(checkSq256)){
//                                (ms++)->move =  MOVE_FromFc_to(tmp,XYtoS(nSrcX,checkSqY));                           
//                            }
//                        }
//                    }
//                }
//            }
//        }// End 红炮解黑炮将
//        //3.红车将黑炮将*************************************************************
//        for(int nSrc256 = PieceListStart(pos,RCHE); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){ 
//            if(nSrc256 == paojia256){
//                continue;
//            }
//            int tmp      = MOVE_FromFC(nSrc256,RCHE); 
//            int nSrcX = StoX(nSrc256);
//            int nSrcY = StoY(nSrc256);
//            psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//            psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]);
//            if(OutCheckF){                  //上下方向可以解将
//                if(nSrcX == checkSqX){      //在同一行,只有吃包哇                   
//                    if(psF->RookCap & yBitMask(checkSq256)){
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BPAO);
//                    }
//                }
//                else{                       //不在同一列, 吃包,挡包
//                    if(OutCheckF & yBitMask(nSrc256)){  //在解将的列上                        
//                        if(psR->RookCap & xBitMask(checkSq256)){
//                            int target256 = XYtoS(checkSqX,nSrcY);                             
//                            (ms++)->move =  MOVE_FromFc_to_tc(tmp,target256,pos->b256[target256]);
//                        }
//                    }
//                }
//            }
//            else if(OutCheckR){              //左右方向可以解将
//                if(nSrcY == checkSqY){      //在同一列,只有吃炮
//                    if(psR->RookCap & xBitMask(checkSq256)){
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BPAO);
//                    }
//                }
//                else{
//                    if(OutCheckR & xBitMask(nSrc256)){ //在解将的列上哇
//                        if(psF->RookCap & yBitMask(checkSq256)){
//                            int target256 = XYtoS(nSrcX,checkSqY);                             
//                            (ms++)->move =  MOVE_FromFc_to_tc(tmp,target256,pos->b256[target256]);
//                        }
//                    }
//                }
//            }
//        }// End 红车解黑炮将 
//    }                
//    break;  //..........只有一个炮在将 End
//case CheCheck:     //当前只有一个车在将 1, 吃车, 2, 挡车
//    if(CheckPieceNum > 1){   
//        //board_display(board,"ERROR 有两个黑车同时在将！！, 怎么办哇.....\n",log_file);  
//    }
//    else{
//        if(tCheckDir1 & DirUp){
//            OutCheckF = UpMask(MyKing256) & LoMask(checkSq256) | yBitMask(checkSq256); // 吃车,挡车哇
//        }
//        else if(tCheckDir1 & DirLow){
//            OutCheckF = UpMask(checkSq256) & LoMask(MyKing256) | yBitMask(checkSq256);
//        }
//        else if(tCheckDir1 & DirLeft){
//            OutCheckR = (RightMask(checkSq256) & LeftMask(MyKing256)  | xBitMask(checkSq256));
//        }
//        else if(tCheckDir1 & DirRight){
//            OutCheckR = (RightMask(MyKing256) & LeftMask(checkSq256)  | xBitMask(checkSq256));
//        }
//        //1.红兵解黑车将*************************************************************
//        if(tCheckDir1 & DirUp){                             //红兵只能将上面的车将 
//            for(int nSrc256 = PieceListStart(pos,RPAWN); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//
//                if(nSrc256 > 0x7b){
//                    continue;   //没过河的兵不能解将哇
//                }
//
//                int tmp      = MOVE_FromFC(nSrc256,RPAWN);
//                //兵只能左右解车将哇
//                int to256 = nSrc256+1;
//                int tx    = StoX(to256);
//                if(tx == MyKingX){
//                    if(yBitMask(to256) & OutCheckF){ 
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                    }
//                }
//                to256 = nSrc256-1;
//                tx    = StoX(to256);
//                if(tx == MyKingX){
//                    if(yBitMask(to256) & OutCheckF){ 
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                    }
//                }
//            }
//        }// End 红兵解黑车将
//        //红仕解车将
//        for(int nSrc256 = PieceListStart(pos,RSHI); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,RSHI);    
//            uint8* lpDst = PreShiXiangAndEyeMove[nSrc256];
//            while(int to256 = *lpDst++){                               
//                int tx    = StoX(to256);
//                int ty    = StoY(to256);
//                if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                    || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){   
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                }
//            }
//        }//红仕解车将 End
//        //红相解车将
//        for(int nSrc256 = PieceListStart(pos,RXIANG); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,RXIANG);  
//            uint8* lpDst = PreShiXiangAndEyeMove[nSrc256];
//            while(int to256 = *lpDst++){                                 
//                int tx    = StoX(to256);
//                int ty    = StoY(to256);
//                if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                    || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){
//                        if(pos->b256[*lpDst] == 0){  //象眼上没有棋子 if(!tree->board.B256[(nSrc+nDst)>>1])
//                            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                        } 
//                }
//                lpDst++;
//            }
//        }//红相解车将 End
//        //红马解黑车将 
//        for(int nSrc256 = PieceListStart(pos,RMA); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,RMA); 
//            uint8* lpDst = PreMaAndLegMove[nSrc256];
//            while(int to256 = *lpDst++){     //可以挡车或吃车                                
//                int tx    = StoX(to256);
//                int ty    = StoY(to256);
//                if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                    || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){
//                        if(pos->b256[*lpDst] == 0){  //马腿没有棋子
//                            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                        } 
//                } 
//                lpDst++;
//            }
//        }//红马解黑车将 End
//        // 2. 红炮解黑车将
//        for(int nSrc256 = PieceListStart(pos,RPAO); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,RPAO); 
//            int nSrcX = StoX(nSrc256);
//            int nSrcY = StoY(nSrc256);
//            psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//            psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]);
//            if(OutCheckF){                  //上下方向可以解将
//                if(nSrcX == checkSqX){      //在同一行,只有吃车哇
//                    if(psF->CannonCap & yBitMask(checkSq256)){
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BCHE);
//                    }
//                }
//                else{                       //不在同一列, 吃车,挡车
//                    if(OutCheckF & yBitMask(nSrc256)){  //在解将的列上
//                        if(nSrcY == checkSqY){          //在同一行
//                            if(psR->CannonCap & xBitMask(checkSq256)){                               
//                                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BCHE);
//                            }
//                        }
//                        else{
//                            if(psR->RookCap & xBitMask(checkSq256)){  
//                                (ms++)->move =  MOVE_FromFc_to(tmp,XYtoS(checkSqX,nSrcY));  
//                            }
//                        }                                      
//                    }
//                }
//            }
//            else if(OutCheckR){              //左右方向可以解将
//                if(nSrcY == checkSqY){       //在同一行,只有吃车
//                    if(psR->CannonCap & xBitMask(checkSq256)){
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BCHE);
//                    }
//                }
//                else{
//                    if(OutCheckR & xBitMask(nSrc256)){
//                        if(nSrcX == checkSqX){
//                            if(psF->CannonCap & yBitMask(checkSq256)){
//                                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BCHE);
//                            }
//                        }
//                        else{
//                            if(psF->RookCap & yBitMask(checkSq256)){  
//                                (ms++)->move =  MOVE_FromFc_to(tmp,XYtoS(nSrcX,checkSqY));  
//                            }
//                        }
//                    }
//                }
//            }
//        }// End 红炮解黑车将
//        //3.红车解黑车将*************************************************************
//        for(int nSrc256 = PieceListStart(pos,RCHE); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,RCHE); 
//            int nSrcX = StoX(nSrc256);
//            int nSrcY = StoY(nSrc256);
//            psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//            psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]);  
//            if(OutCheckF){                  //上下方向可以解将
//                if(nSrcX == checkSqX){      //在同一行,只有吃车哇
//                    if(psF->RookCap & yBitMask(checkSq256)){
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BCHE);
//                    }
//                }
//                else{                       //不在同一列, 吃车,挡车
//                    if(OutCheckF & yBitMask(nSrc256)){  //在解将的列上
//                        if(psR->RookCap & xBitMask(checkSq256)){
//                            int target256 = XYtoS(checkSqX,nSrcY); 
//                            (ms++)->move =  MOVE_FromFc_to_tc(tmp,target256,pos->b256[target256]);
//                        }                                                                  
//                    }
//                }
//            }
//            else if(OutCheckR){              //左右方向可以解将
//                if(nSrcY == checkSqY){      //在同一列,只有吃车
//                    if(psR->RookCap & xBitMask(checkSq256)){
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BCHE);
//                    }
//                }
//                else{
//                    if(OutCheckR & xBitMask(nSrc256)){ //在解将的列上哇
//                        if(psF->RookCap & yBitMask(checkSq256)){
//                            int target256 = XYtoS(nSrcX,checkSqY);
//                            (ms++)->move =  MOVE_FromFc_to_tc(tmp,target256,pos->b256[target256]);
//                        }
//                    }
//                }
//            } 
//        }// End 红车解黑车将 
//    }
//    break;      //End 黑车将军
//case MaCheck:         //当前有马在将军哇, 1, 吃马, 2, 别马腿
//    if(CheckPieceNum > 1){ 
//        if(MaLeg256[0] == MaLeg256[1]){  //同时有两个马在将,则只有Maleg相同才能解将
//            leg256 = MaLeg256[0];
//            //1,  红兵不可能解马将   //2,  红仕解马将 1, 吃马,挡马,
//            for(int nSrc256 = PieceListStart(pos,RSHI); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//                int tmp      = MOVE_FromFC(nSrc256,RSHI); 
//                if(inBoard(leg256) & IN_RSHI){
//                    if(GetDir(nSrc256,leg256) & DirShi){ 
//                        (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                    } 
//                }
//            }//红仕解马将 End
//            //红相解马将   if(!tree->board.B256[(nSrc256 + to256)>>1])
//            for(int nSrc256 = PieceListStart(pos,RXIANG); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//                int tmp      = MOVE_FromFC(nSrc256,RXIANG); 
//                if(inBoard(leg256) & IN_RXIANG){
//                    if(GetDir(nSrc256,leg256) & DirXiang){
//                        if(!pos->b256[(nSrc256 + leg256)>>1]){  //相眼没有棋子
//                            (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                        } 
//                    }
//                }
//            }//红相解马将 End
//            //红马解黑马将
//            for(int nSrc256 = PieceListStart(pos,RMA); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//                int tmp      = MOVE_FromFC(nSrc256,RMA);
//                if(GetDir(nSrc256,leg256) & DirMa){
//                    if(!pos->b256[nSrc256 + horseLegTab(leg256 - nSrc256 + 256)]){  //马腿没有棋子
//                        (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                    } 
//                }              
//            }  //红马解黑马将 End
//                    // 2. 红炮解黑马将
//            for(int nSrc256 = PieceListStart(pos,RPAO); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//                int tmp      = MOVE_FromFC(nSrc256,RPAO); 
//                int nSrcX = StoX(nSrc256);
//                int nSrcY = StoY(nSrc256);
//                psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//                psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]);             
//
//                if(GetDir(nSrc256,leg256) & (DirUp+DirLow)){
//                    if(psF->RookCap & yBitMask(leg256)){ 
//                        (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                    }
//                }
//                else if(GetDir(nSrc256,leg256) & (DirLeft+DirRight)){
//                    if(psR->RookCap & xBitMask(leg256)){
//                        (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                    }
//                }
//            }// End 红炮解黑马将
//             // 2. 红车解黑马将
//            for(int nSrc256 = PieceListStart(pos,RCHE); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//                int tmp   = MOVE_FromFC(nSrc256,RCHE); 
//                int nSrcX = StoX(nSrc256);
//                int nSrcY = StoY(nSrc256);
//                psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//                psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]); 
//
//                if(GetDir(nSrc256,leg256) & (DirUp+DirLow)){
//                    if(psF->RookCap & yBitMask(leg256)){ 
//                        (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                    }
//                }
//                else if(GetDir(nSrc256,leg256) & (DirLeft+DirRight)){
//                    if(psR->RookCap & xBitMask(leg256)){
//                        (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                    }
//                }
//            }// End 红车解黑马将
//        }
//    }
//    else{//解马将, 不用再判断能不能走到那个位置, 因为不可能再形成其它的包将军
//        leg256 = MaLeg256[0];
//        //1,  红兵不可能解马将   //2,  红仕解马将 1, 吃马,挡马,
//        for(int nSrc256 = PieceListStart(pos,RSHI); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,RSHI); 
//            if(inBoard(leg256) & IN_RSHI){
//                if(GetDir(nSrc256,leg256) & DirShi){ 
//                    (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                } 
//            }
//            if(inBoard(checkSq256) & IN_RSHI){
//                if(GetDir(nSrc256,checkSq256) & DirShi){ 
//                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BMA);
//                }
//            }
//        }//红仕解马将 End
//        //红相解马将   if(!tree->board.B256[(nSrc256 + to256)>>1])
//        for(int nSrc256 = PieceListStart(pos,RXIANG); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,RXIANG); 
//            if(inBoard(leg256) & IN_RXIANG){
//                if(GetDir(nSrc256,leg256) & DirXiang){
//                    if(!pos->b256[(nSrc256 + leg256)>>1]){  //相眼没有棋子
//                        (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                    } 
//                }
//            }
//            if(inBoard(checkSq256) & IN_RXIANG){
//                if(GetDir(nSrc256,checkSq256) & DirXiang){
//                    if(!pos->b256[(nSrc256 + checkSq256)>>1]){  //相眼没有棋子
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BMA);
//                    } 
//                }
//            }
//        }//红相解马将 End
//        //红马解黑马将
//        for(int nSrc256 = PieceListStart(pos,RMA); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,RMA);
//            if(GetDir(nSrc256,leg256) & DirMa){
//                if(!pos->b256[nSrc256 + horseLegTab(leg256 - nSrc256 + 256)]){  //马腿没有棋子
//                    (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                } 
//            }
//            else if(GetDir(nSrc256,checkSq256) & DirMa){
//                if(!pos->b256[nSrc256 + horseLegTab(checkSq256 - nSrc256 + 256)]){  //马腿没有棋子
//                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BMA);
//                } 
//            }                
//        }  //红马解黑马将 End
//        // 2. 红炮解黑马将
//        for(int nSrc256 = PieceListStart(pos,RPAO); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,RPAO); 
//            int nSrcX = StoX(nSrc256);
//            int nSrcY = StoY(nSrc256);
//            psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//            psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]);             
//
//            if(GetDir(nSrc256,leg256) & (DirUp+DirLow)){
//                if(psF->RookCap & yBitMask(leg256)){ 
//                    (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                }
//            }
//            else if(GetDir(nSrc256,leg256) & (DirLeft+DirRight)){
//                if(psR->RookCap & xBitMask(leg256)){
//                    (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                }
//            }
//            if(GetDir(nSrc256,checkSq256) & (DirUp+DirLow)){
//                if(psF->CannonCap & yBitMask(checkSq256)){ 
//                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BMA);
//                }
//            }
//            else if(GetDir(nSrc256,checkSq256) & (DirLeft+DirRight)){
//                if(psR->CannonCap & xBitMask(checkSq256)){
//                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BMA);
//                }
//            }
//        }// End 红炮解黑马将
//        // 2. 红车解黑马将
//        for(int nSrc256 = PieceListStart(pos,RCHE); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp   = MOVE_FromFC(nSrc256,RCHE); 
//            int nSrcX = StoX(nSrc256);
//            int nSrcY = StoY(nSrc256);
//            psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//            psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]); 
//
//            if(GetDir(nSrc256,leg256) & (DirUp+DirLow)){
//                if(psF->RookCap & yBitMask(leg256)){ 
//                    (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                }
//            }
//            else if(GetDir(nSrc256,leg256) & (DirLeft+DirRight)){
//                if(psR->RookCap & xBitMask(leg256)){
//                    (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                }
//            }
//            if(GetDir(nSrc256,checkSq256) & (DirUp+DirLow)){
//                if(psF->RookCap & yBitMask(checkSq256)){ 
//                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BMA);
//                }
//            }
//            else if(GetDir(nSrc256,checkSq256) & (DirLeft+DirRight)){
//                if(psR->RookCap & xBitMask(checkSq256)){ 
//                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BMA);
//                }
//            }
//        }// End 红车解黑马将
//    }
//    break;            //End马将军
//case PawnCheck:       //光一个卒在将, 不可能同时有两个卒在将, 只有吃卒来解将
//    //2, 红相解卒将, 1, 红兵不可能解卒将
//    for(int nSrc256 = PieceListStart(pos,RXIANG); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp   = MOVE_FromFC(nSrc256,RXIANG);
//        if(GetDir(nSrc256,checkSq256) & DirXiang){
//            if(!pos->b256[(nSrc256 + checkSq256)>>1]){ 
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BPAWN);
//            }
//        }
//    } 
//    //3,红仕解卒将
//    if(inBoard(checkSq256) & IN_RSHI){
//        for(int nSrc256 = PieceListStart(pos,RSHI); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp   = MOVE_FromFC(nSrc256,RSHI);             
//            if(GetDir(nSrc256,checkSq256) & DirShi){
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BPAWN);
//            }        
//        }//红仕解卒将 End                
//    }
//    //3,红马解卒将                
//    for(int nSrc256 = PieceListStart(pos,RMA); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp   = MOVE_FromFC(nSrc256,RMA);
//        if(GetDir(nSrc256,checkSq256) & DirMa){
//            if(!pos->b256[nSrc256 + horseLegTab(checkSq256 - nSrc256 + 256)]){  //马腿没有棋子
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BPAWN);
//            } 
//        }                   
//    }  //红马解黑卒将 End
//    //红炮解卒将                
//    for(int nSrc256 = PieceListStart(pos,RPAO); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp   = MOVE_FromFC(nSrc256,RPAO);   
//        int nSrcX = StoX(nSrc256);
//        int nSrcY = StoY(nSrc256);
//        psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//        psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]);   
//
//        if(GetDir(nSrc256,checkSq256) & (DirUp+DirLow)){
//            if(psF->CannonCap & yBitMask(checkSq256)){ 
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BPAWN);
//            }
//        }
//        else if(GetDir(nSrc256,checkSq256) & (DirLeft+DirRight)){
//            if(psR->CannonCap & xBitMask(checkSq256)){
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BPAWN);
//            }
//        }
//    } // End 红炮解黑卒将
//    //红车解卒将                
//    for(int nSrc256 = PieceListStart(pos,RCHE); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp   = MOVE_FromFC(nSrc256,RCHE);  
//        int nSrcX = StoX(nSrc256);
//        int nSrcY = StoY(nSrc256);
//        psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//        psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]); 
//        if(GetDir(nSrc256,checkSq256) & (DirUp+DirLow)){
//            if(psF->RookCap & yBitMask(checkSq256)){
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BPAWN);
//            }
//        }
//        else if(GetDir(nSrc256,checkSq256) & (DirLeft+DirRight)){
//            if(psR->RookCap & xBitMask(checkSq256)){  
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BPAWN);
//            }
//        }
//    } // End 红车解黑卒将
//    break;
//case MaCheck | PaoCheck:    //马炮双将,可解将
//    paojia256    = PaoJia256[0];
//    //if(NextPiece(pos,paojia256) < 0x33){ //if(board->P48[board->P256[paojia256]] == 0){   //炮架上的棋子不可以走哇
//    //    break;
//    //}
//
//    paojiaCan = true;
//    for(int i = 0; i<NotNum; i++){
//        if(paojia256 == Not256Pos[i]){
//            paojiaCan = false;
//            break;
//        }
//    }
//    if(false == paojiaCan){
//        break;
//    }
//    leg256       = MaLeg256[1];    
//    paojiaChess  = PaoJiaChess[0];
//    paohou256    = PaoHuo256[0];
//    int tmp;
//    int nSrcX;
//    int nSrcY;
//    switch(paojiaChess){
//        //case RPAWN:             //不可能
//        //    Print(4095,"马炮双将,红兵没法解将,动将解将");
//        //    DisplayChessBoard(tree->board);
//        //    break;                        
//case RXIANG:            //不可能 
//    tmp   = MOVE_FromFC(paojia256,RXIANG);  
//    if(inBoard(leg256) & IN_RXIANG){
//        if(GetDir(paojia256,leg256) & DirXiang){
//            if(!pos->b256[(paojia256 + leg256)>>1]){  //相眼没有棋子 
//                (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//            }
//        }
//    }
//    if(inBoard(CheckPos256[1]) & IN_RXIANG){
//        if(GetDir(paojia256,CheckPos256[1]) & DirXiang){
//            if(!pos->b256[(paojia256 + CheckPos256[1])>>1]){  //相眼没有棋子 
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,CheckPos256[1],BMA);
//            }
//        }
//    }
//    break;
//case RSHI:
//    tmp   = MOVE_FromFC(paojia256,RSHI);  
//    if(inBoard(leg256) & IN_RSHI){ 
//        if(inBoard(leg256) & IN_RSHI){
//            if(GetDir(paojia256,leg256) & DirShi){
//                (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//            }
//        }
//    }
//    if(inBoard(CheckPos256[1]) & IN_RSHI){  
//        if(inBoard(CheckPos256[1]) & IN_RSHI){
//            if(GetDir(paojia256,CheckPos256[1]) & DirShi){
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,CheckPos256[1],BMA);
//            }
//        }
//    }
//    break;
//case RMA:
//    tmp   = MOVE_FromFC(paojia256,RMA); 
//    if(GetDir(paojia256,leg256) & DirMa){
//        if(!pos->b256[paojia256 + horseLegTab(leg256 - paojia256 + 256)]){  //马腿没有棋子
//            (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//        } 
//    }
//    else if(GetDir(paojia256,CheckPos256[1]) & DirMa){
//        if(!pos->b256[paojia256 + horseLegTab(CheckPos256[1] - paojia256 + 256)]){  //马腿没有棋子
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,CheckPos256[1],BMA);
//        } 
//    } 
//    break;
//case RPAO:
//    tmp   = MOVE_FromFC(paojia256,RPAO); 
//    nSrcX = StoX(paojia256);
//    nSrcY = StoY(paojia256);
//    psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//    psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]);  
//    if(GetDir(paojia256,leg256) & (DirUp+DirLow)){
//        if(psF->RookCap & yBitMask(leg256)){ 
//            (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//        }
//    }
//    else if(GetDir(paojia256,leg256) & (DirLeft+DirRight)){
//        if(psR->RookCap & xBitMask(leg256)){
//            (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//        }
//    }
//    if(GetDir(paojia256,CheckPos256[1]) & (DirUp+DirLow)){
//        if(psF->CannonCap & yBitMask(CheckPos256[1])){ 
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,CheckPos256[1],BMA);
//        }
//    }
//    else if(GetDir(paojia256,CheckPos256[1]) & (DirRight+DirLeft)){
//        if(psR->CannonCap & xBitMask(CheckPos256[1])){ 
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,CheckPos256[1],BMA);
//        }
//    }
//    break;
//case RCHE:
//    tmp   = MOVE_FromFC(paojia256,RCHE); 
//    nSrcX = StoX(paojia256);
//    nSrcY = StoY(paojia256);
//    psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//    psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]); 
//
//    if(GetDir(paojia256,leg256) & (DirUp+DirLow)){
//        if(psF->RookCap & yBitMask(leg256)){ 
//            (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//        }
//    }
//    else if(GetDir(paojia256,leg256) & (DirLeft+DirRight)){
//        if(psR->RookCap & xBitMask(leg256)){
//            (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//        }
//    }
//    if(GetDir(paojia256,CheckPos256[1]) & (DirUp+DirLow)){
//        if(psF->RookCap & yBitMask(CheckPos256[1])){ 
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,CheckPos256[1],BMA);
//        }
//    }
//    else if(GetDir(paojia256,CheckPos256[1]) & (DirRight+DirLeft)){
//        if(psR->RookCap & xBitMask(CheckPos256[1])){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,CheckPos256[1],BMA);
//        }
//    }
//    break;
//default:
//    break;
//    }
//    break;
//case CheCheck | PaoCheck:   //车炮双将, 有些情况可解将, 如果不在一直线,不可解将
//    if(CheckPieceNum > 2){
//        //还有棋子在将,不能解将
//        break;
//    }
//    //CheckDir1 = IsCanTo(CheckPos256[1],CheckPos256[0]);
//    tCheckDir1 = GetDir(CheckPos256[1],CheckPos256[0]);
//    if(!(tCheckDir1 & DirChe)){               
//        /* Print(4095,"黑方车炮双将,且不在一直线, 没法解将,只有动将解将");
//        DisplayChessBoard(tree->board); */
//        break;
//    }
//    if(tCheckDir1 & DirUp){
//        OutCheckF  = UpMask(MyKing256) & LoMask(K256Up1);
//    }
//    else if(tCheckDir1 & DirLow){
//        OutCheckF  = LoMask(MyKing256) & UpMask(K256Lo1); 
//    }
//    else if(tCheckDir1 & DirLeft){
//        OutCheckR  = LeftMask(MyKing256) &  RightMask(K256Left1);
//    }
//    else if(tCheckDir1 & DirRight){
//        OutCheckR =  RightMask(MyKing256) & LeftMask(K256Right1);
//    }
//    //1.红兵解车炮将*************************************************************
//    //if(CheckDir1 == DirUp){                             //红兵只能解上面的车炮将 
//    if(tCheckDir1 & DirUp){
//        //for(int p48=27; p48<32; p48++){
//        //    if((nSrc256 = board->P48[p48])){      //当有红兵存在时 
//        for(int nSrc256 = PieceListStart(pos,RPAWN); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp   = MOVE_FromFC(nSrc256,RPAWN);  
//            if(nSrc256 > 0x7b){
//                continue;
//            }
//            //不在炮架上的兵只能左右解将哇
//            int to256 = nSrc256+1;
//            int tx    = StoX(to256);
//            if(tx == MyKingX){
//                if(yBitMask(to256) & OutCheckF){  
//                    (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//                }
//            }
//            to256 = nSrc256-1;
//            tx    = StoX(to256);
//            if(tx == MyKingX){
//                if(yBitMask(to256) & OutCheckF){
//                    (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//                }
//            }
//        }
//    }// End 红兵解车炮将
//    //红仕解车炮将
//    for(int nSrc256 = PieceListStart(pos,RSHI); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp      = MOVE_FromFC(nSrc256,RSHI);  
//        uint8* lpDst = PreShiXiangAndEyeMove[nSrc256];
//        while(int to256 = *lpDst++){                            
//            int tx    = StoX(to256);
//            int ty    = StoY(to256);
//            if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){ 
//                    (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            }
//        }        
//    }//红仕解车炮将 End
//    //红相解车炮将
//    for(int nSrc256 = PieceListStart(pos,RXIANG); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp      = MOVE_FromFC(nSrc256,RXIANG); 
//        uint8* lpDst = PreShiXiangAndEyeMove[nSrc256];
//        while(int to256 = *lpDst++){                            
//            int tx    = StoX(to256);
//            int ty    = StoY(to256);
//            if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){
//                    if(!pos->b256[*lpDst]){  //象眼上没有棋子 if(!tree->board.B256[(nSrc+nDst)>>1]) 
//                        (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//                    } 
//            }
//            lpDst++;
//        }        
//    }//红相解车炮将 End
//    //红马解车炮将
//    for(int nSrc256 = PieceListStart(pos,RMA); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp      = MOVE_FromFC(nSrc256,RMA); 
//        uint8* lpDst = PreMaAndLegMove[nSrc256];
//        while(int to256 = *lpDst++){     //可以挡炮或吃炮                            
//            int tx    = StoX(to256);
//            int ty    = StoY(to256);
//            if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){
//                    if(!pos->b256[*lpDst]){  //马腿没有棋子                       
//                        (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//                    } 
//            } 
//            lpDst++;
//        }                                
//    }   ////红马解车炮将 End
//    // 2. 红炮解黑车炮将
//    for(int nSrc256 = PieceListStart(pos,RPAO); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp      = MOVE_FromFC(nSrc256,RPAO); 
//        int nSrcX = StoX(nSrc256);
//        int nSrcY = StoY(nSrc256);
//        psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//        psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]); 
//
//        if(OutCheckF){                  //上下方向可以解将
//            if(nSrcX != checkSqX){      //不在同一行,                                                    
//                if(OutCheckF & yBitMask(nSrc256)){  //在解将的列上
//                    if(nSrcY != checkSqY){          //不在同一行                                           
//                        if(psR->RookCap & xBitMask(checkSq256)){    //挡车
//                            (ms++)->move =  MOVE_FromFc_to(tmp,XYtoS(checkSqX,nSrcY)); 
//                        }
//                    }                                      
//                }
//            }
//        }
//        else if(OutCheckR){              //左右方向可以解将
//            if(nSrcY != checkSqY){                                       
//                if(OutCheckR & xBitMask(nSrc256)){
//                    if(nSrcX != checkSqX){                                          
//                        if(psF->RookCap & yBitMask(checkSq256)){
//                            (ms++)->move =  MOVE_FromFc_to(tmp,XYtoS(nSrcX,checkSqY)); 
//                        }
//                    }
//                }
//            }
//        }    
//    } // End 红炮解黑炮将
//
//    // 2. 红车解黑车炮将
//    for(int nSrc256 = PieceListStart(pos,RCHE); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp      = MOVE_FromFC(nSrc256,RCHE); 
//        int nSrcX = StoX(nSrc256);
//        int nSrcY = StoY(nSrc256);
//        psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//        psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]); 
//
//        if(OutCheckF){                  //上下方向可以解将
//            if(nSrcX != checkSqX){      //不在同一行,                                                    
//                if(OutCheckF & yBitMask(nSrc256)){  //在解将的列上
//                    if(nSrcY != checkSqY){          //不在同一行                                           
//                        if(psR->RookCap & xBitMask(checkSq256)){    //挡车
//                            (ms++)->move =  MOVE_FromFc_to(tmp,XYtoS(checkSqX,nSrcY)); 
//                        }
//                    }                                      
//                }
//            }
//        }
//        else if(OutCheckR){              //左右方向可以解将
//            if(nSrcY != checkSqY){       //在同一行,只有吃炮                                   
//                if(OutCheckR & xBitMask(nSrc256)){
//                    if(nSrcX != checkSqX){ 
//                        if(psF->RookCap & yBitMask(checkSq256)){   //挡车
//                            (ms++)->move =  MOVE_FromFc_to(tmp,XYtoS(nSrcX,checkSqY)); 
//                        }
//                    }
//                }
//            }
//        }    
//    } // End 红炮解黑炮将 
//
//    break;
//case CheCheck | PawnCheck:  //车兵双将, 不动将不可能解将哇
//    /*Print(4095,"车兵双将,没法解将,只有动将解将");
//    DisplayChessBoard(tree->board);*/
//    break;
//case PaoCheck | PawnCheck:
//    /*Print(4095,"炮兵双将,没法解将,只有动将解将");
//    DisplayChessBoard(tree->board);*/
//    break;
//case MaCheck | PawnCheck:   //马兵双将,不可解将
//    /*DisplayChessBoard(tree->board);
//    Print(4095,"马兵双将,没法解将");*/
//    break;            
//case CheCheck | MaCheck:    //车马双将,不可解将
//    //DisplayChessBoard(tree->board);
//    //Print(4095,"车马双将,没法解将");
//    break;            
//default:        //其它情况,不可能出现哇
//    /* Print(4095,"其它情况的将军,看一下有没办法解将哇！！, 怎么办哇.....");  
//    DisplayChessBoard(tree->board);*/
//    break;
//        }
//        // 最后动将来解将哇             
//        uint8* lpDst = PreKingMove[MyKing256];
//        int ktmp        = MOVE_FromFC(MyKing256,RKING); 
//        while(int to256 = *lpDst++){  
//            int to14        = pos->b256[to256];
//            int tx          = StoX(to256);
//            int ty          = StoY(to256);
//            int ky4         = to256 & 0xf0;
//            int tKingDir  = GetDir(MyKing256,to256);
//            if(!IsWhite(to14)){       //是黑棋或无棋子
//                if(tKingDir == tCheckDir1 && (CheckType & (CheCheck + PaoCheck))){
//                    continue;
//                }//如果将走的方向与将军的方向相同,且将军的棋子不是兵，那么就不可能解将
//                //再判断一下走将后会不会还是被将              
//
//                int kToF  = pos->wBitFiles[StoX(to256)] ^ yBitMask(MyKing256);     //这个应该是对的哇
//                int kToR  = pos->wBitRanks[StoY(to256)] ^ xBitMask(MyKing256);               
//
//                //得to的到上下的信息
//                psmv = FileMove(ty,kToF);            
//                //得到现在将上的第一个棋子 tmp = kf & UpMask(nMyKing);
//                int tmp = psmv->RookCap[DUpLeft] + tx;
//                if(tmp != to256){
//                    checkChess = pos->b256[tmp];
//                    if(    checkChess == BCHE 
//                        || checkChess == BKING 
//                        || (checkChess == BPAWN && (tmp+16) == to256)){            //???????????????
//                            continue;                        
//                    }
//                    //有了第一个才可能有第二个
//                    tmp = psmv->CannonCap[DUpLeft] + tx;
//                    if(tmp != to256){
//                        if(pos->b256[tmp] == BPAO){
//                            continue;
//                        }
//                    }
//                }
//                //得到将下面的第一个棋子
//                tmp = psmv->RookCap[DLoRight] + tx;
//                if(tmp != to256){
//                    if(pos->b256[tmp] == BCHE){
//                        continue;
//                    }
//                    //有了第一个才可能有第二个
//                    tmp = psmv->CannonCap[DLoRight] + tx;
//                    if(tmp != to256){ 
//                        if(pos->b256[tmp] == BPAO){
//                            continue;
//                        }
//                    }
//                }
//
//                //得到将的棋左面的第一个棋子
//                psmv = RankMove(tx,kToR);
//                tmp  = psmv->RookCap[DUpLeft] + ky4;
//                if(tmp != to256){
//                    checkChess = pos->b256[tmp];
//                    if((checkChess == BCHE)
//                        || (checkChess == BPAWN && tmp+1 == to256)){
//                            continue;
//                    }
//                    //有了第一个才可能有第二个
//                    tmp = psmv->CannonCap[DUpLeft] + ky4;
//                    if(tmp != to256){
//                        if(pos->b256[tmp] == BPAO){
//                            continue;
//                        }
//                    }
//                }
//                //得到将的右面的第一个棋子
//                tmp  = psmv->RookCap[DLoRight] + ky4;
//                if(tmp != to256){
//                    checkChess = pos->b256[tmp];
//                    if((checkChess == BCHE)
//                        || (checkChess == BPAWN && tmp-1 == to256)){
//                            continue;
//                    }
//                    //有了第一个才可能有第二个
//                    tmp = psmv->CannonCap[DLoRight] + ky4;
//                    if(tmp != to256){
//                        if(pos->b256[tmp] == BPAO){
//                            continue;
//                        }
//                    }
//                }
//                //还得看一下有没给马将军了
//                bool isMaCheck = false;
//                for(int nSrc256 = PieceListStart(pos,BMA); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//                    int m = horseLegTab(to256-nSrc256+256);
//                    if(m && !pos->b256[nSrc256 + m]){
//                        isMaCheck = true;
//                        break;
//                    }
//                } 
//                if(false == isMaCheck){
//                    (ms++)->move =  MOVE_FromFc_to_tc(ktmp,to256,to14);
//                }
//            }
//        }
//    }   //红方要解将 End
//    else{ //黑方要解将...............................................................................................
//        int MyKing256      = PieceListStart(pos,BKING);                              //黑将的位置
//        int MyKingX        = StoX(MyKing256);                       //黑将的X
//        int MyKingY        = StoY(MyKing256);                       //黑将的Y
//        int ky4            = MyKing256 & 0xf0;
//
//        int MyKingFile     = pos->wBitFiles[MyKingX];
//        int MyKingRank     = pos->wBitRanks[MyKingY];
//
//        //得到将的上下信息
//        psmv = FileMove(MyKingY,MyKingFile);
//        //得到将上面的第一个棋子
//        K256Up1 = psmv->RookCap[DUpLeft] + MyKingX;
//        if(K256Up1 != MyKing256){
//            int chess1      = pos->b256[K256Up1]; 
//            if(chess1 == RCHE){                                 //红车在将
//                CheckType                         |= CheCheck;
//                CheckPos256[CheckPieceNum++]       = K256Up1;
//            }
//            else if(chess1 == RPAO){                            //帅上面是红炮,则将与红炮之间的棋子不能走棋哇
//                NotToFile = UpMask(MyKing256) & LoMask(K256Up1);               
//            }
//            //有了第一个棋子,才有第二个棋子哇
//            K256Up2 = psmv->CannonCap[DUpLeft] + MyKingX;
//            if(K256Up2 != MyKing256){
//                int chess2    = pos->b256[K256Up2];               
//                if(chess2 == RPAO){         //红炮将军
//                    CheckType                      |= PaoCheck;
//                    CheckPos256[CheckPieceNum++]    = K256Up2;
//
//                    PaoJia256[PaoJiaNum]            = K256Up1;
//                    PaoJiaChess[PaoJiaNum]          = chess1;                   
//                    PaoDir[PaoJiaNum]               = DirUp;
//                    PaoHuo256[PaoJiaNum]            = 0;              //暂时设为0
//                    PaoJiaNum ++;
//                    OutCheckF                       = yBitMask(K256Up2);              //只能吃炮
//                }
//                else if(chess2 == RCHE){  //棋子上面是黑车,或黑将,则KingUp1的棋子不能动了解
//                    if(IsBlack(chess1)){
//                        Not256Pos[NotNum]           = K256Up1;
//                        RemovePiece(pos, K256Up1);
//                        NotNum++;
//                    }
//                }  //黑将上面不可能有第三个棋子
//            }
//        }
//        //得到将下面的第一个棋子
//        K256Lo1 = psmv->RookCap[DLoRight] + MyKingX;
//        if(K256Lo1 != MyKing256){
//            int chess1    = pos->b256[K256Lo1];
//            if( chess1 == RCHE){
//                CheckType                       |= CheCheck;
//                CheckPos256[CheckPieceNum++]     = K256Lo1;
//            }
//            else if(chess1 == RPAWN){
//                if((K256Lo1-16) == MyKing256){
//                    CheckType                       |= PawnCheck;
//                    CheckPos256[CheckPieceNum++]    = K256Lo1;
//                }
//            }
//            else if(chess1 == RPAO){
//                NotToFile |= UpMask(K256Lo1) & LoMask(MyKing256);
//            }            
//            //有了第一个棋子,才有第二个棋子哇
//            K256Lo2 = psmv->CannonCap[DLoRight] + MyKingX;
//            if(K256Lo2 != MyKing256){
//                int chess2    = pos->b256[K256Lo2];               
//                if(chess2 == RPAO){
//                    CheckType                      |= PaoCheck;
//                    CheckPos256[CheckPieceNum++]    = K256Lo2;
//
//                    PaoJia256[PaoJiaNum]            = K256Lo1;
//                    PaoJiaChess[PaoJiaNum]          = chess1;                   
//                    PaoDir[PaoJiaNum]               = DirLow;
//                    PaoHuo256[PaoJiaNum]            = 0;              //暂时设为0
//                    PaoJiaNum ++;
//
//                    if(chess1 == RPAO){ //炮架子是对方的红炮,重炮将
//                        OutCheckF = UpMask(K256Lo2) & LoMask(K256Lo1) | yBitMask(K256Lo2);
//                    }
//                    else{
//                        OutCheckF =(UpMask(K256Lo2) & LoMask(MyKing256) 
//                            | yBitMask(K256Lo2)) ^ yBitMask(K256Lo1); // 异或的优先级高, 得加上括号哇
//                    }
//                }
//                else if(chess2 == RCHE || chess2 == RKING) {
//                    if(IsBlack(chess1)){                        
//                        Not256Pos[NotNum]           = K256Lo1;
//                        RemovePiece(pos, K256Lo1);
//                        NotNum++;
//                    }
//                }
//                //有了第二个才有第三个哇
//                K256Lo3 = psmv->SuperCap[DLoRight] + MyKingX;
//                if(K256Lo3 != MyKing256){
//                    int chess3  = pos->b256[K256Lo3];
//                    if(chess2 == RPAO){
//                        PaoHuo256[PaoJiaNum-1]      = K256Lo3;
//                        PaoHuoChess[PaoJiaNum-1]    = chess3;
//                    }
//
//                    if(chess3 == RPAO){
//                        if(IsBlack(chess2)){
//                            //Not48Pos[NotNum]            = chess2;
//                            Not256Pos[NotNum]           = K256Lo2;
//                            RemovePiece(pos, K256Lo2);
//                            NotNum++;
//                        }
//                        if(IsBlack(chess1) && chess2 != RCHE && chess2 != RKING){                            
//                            Not256Pos[NotNum]           = K256Lo1;
//                            RemovePiece(pos, K256Lo1);
//                            NotNum++;
//                        }
//                    }
//                }
//            }
//        }
//        //向左判断一下
//        psmv = RankMove(MyKingX,MyKingRank);
//        K256Left1 = psmv->RookCap[DUpLeft] + ky4;
//        if(K256Left1 != MyKing256){
//            int chess1 = pos->b256[K256Left1];            
//            if(chess1 == RCHE){
//                CheckType                          |= CheCheck;
//                CheckPos256[CheckPieceNum++]        = K256Left1;
//            }
//            else if((chess1 == RPAWN) &&(K256Left1 == MyKing256-1)){
//                CheckType                          |= PawnCheck;  
//                CheckPos256[CheckPieceNum++]        = K256Left1;
//            }
//            else if(chess1 == RPAO){
//                NotToRank |= LeftMask(MyKing256) & RightMask(K256Left1);
//            }
//            //有了第一个棋子,才有第二个棋子哇
//            K256Left2 = psmv->CannonCap[DUpLeft] + ky4;
//            if(K256Left2 != MyKing256){
//                int chess2    = pos->b256[K256Left2];                
//                if(chess2 == RPAO){
//                    CheckType                      |= PaoCheck;
//                    CheckPos256[CheckPieceNum++]    = K256Left2;
//
//                    PaoJia256[PaoJiaNum]            = K256Left1;
//                    PaoJiaChess[PaoJiaNum]          = chess1;                   
//                    PaoDir[PaoJiaNum]               = DirLeft;
//                    PaoHuo256[PaoJiaNum]            = 0;              //暂时设为0
//                    PaoJiaNum ++;
//
//                    if(chess1 == RPAO){
//                        OutCheckR =  RightMask(K256Left2) & LeftMask(K256Left1) | xBitMask(K256Left2);
//                    }
//                    else {
//                        OutCheckR = (RightMask(K256Left2) & LeftMask(MyKing256)  | xBitMask(K256Left2)) ^ xBitMask(K256Left1);
//                    }
//                }
//                else if(chess2 == RCHE){
//                    if(IsBlack(chess1)){
//                        //Not48Pos[NotNum]            = chess481;
//                        Not256Pos[NotNum]           = K256Left1;
//                        //board->P48[chess481]               = 0;
//                        RemovePiece(pos, K256Left1);
//                        NotNum++;
//                    }
//                }
//                //有了第二个棋子,才有第三个棋子哇
//                K256Left3 = psmv->SuperCap[DUpLeft] + ky4;
//                if(K256Left3 != MyKing256){
//                    int chess3   = pos->b256[K256Left3];
//                    if(chess2 == RPAO){
//                        PaoHuo256[PaoJiaNum-1]      = K256Left3;
//                        PaoHuoChess[PaoJiaNum-1]    = chess3;
//                    }
//
//                    if(chess3 == RPAO){         //第三个棋子是黑炮,1,第二个棋子不可能解将了, 
//                        //2, 第一个棋子如果不是红炮,也不能是解将了
//                        if(IsBlack(chess2)){                           
//                            Not256Pos[NotNum]            = K256Left2;
//                            RemovePiece(pos, K256Left2);
//                            NotNum++;
//                        }
//                        if(IsBlack(chess1) && chess2 != RCHE){           
//                            Not256Pos[NotNum]            = K256Left1;
//                            RemovePiece(pos, K256Left1);
//                            NotNum++;
//                        }
//                    } 
//                }
//            }
//        }
//        //向右判断一下
//        K256Right1 = psmv->RookCap[DLoRight] + ky4;
//        if(K256Right1 != MyKing256){
//            int chess1    = pos->b256[K256Right1];           
//            if(chess1 == RCHE){
//                CheckType                          |= CheCheck;
//                CheckPos256[CheckPieceNum++]        = K256Right1;
//            }
//            else if((chess1 == RPAWN) &&(K256Right1 == MyKing256+1)){
//                CheckType                          |= PawnCheck;  
//                CheckPos256[CheckPieceNum++]        = K256Right1;
//            }
//            else if(chess1 == RPAO){
//                NotToRank |= LeftMask(K256Right1) & RightMask(MyKing256);
//            }
//            //有了第一个棋子,才有第二个棋子哇
//            K256Right2 = psmv->CannonCap[DLoRight] + ky4;
//            if(K256Right2 != MyKing256){
//                int chess2    = pos->b256[K256Right2];                
//                if(chess2 == RPAO){
//                    CheckType                      |= PaoCheck;
//                    CheckPos256[CheckPieceNum++]    = K256Right2;
//
//                    PaoJia256[PaoJiaNum]            = K256Right1;
//                    PaoJiaChess[PaoJiaNum]          = chess1;                   
//                    PaoDir[PaoJiaNum]               = DirRight;
//                    PaoHuo256[PaoJiaNum]            = 0;              //暂时设为0
//                    PaoJiaNum ++;
//
//                    if(chess1 == RPAO){
//                        OutCheckR =  RightMask(K256Right1) & LeftMask(K256Right2) | xBitMask(K256Right2);
//                    }
//                    else {
//                        OutCheckR = (RightMask(MyKing256)  & LeftMask(K256Right2)  | xBitMask(K256Right2)) ^ xBitMask(K256Right1);
//                    }
//                }
//                else if(chess2 == RCHE){
//                    if(IsBlack(chess1)){
//                        Not256Pos[NotNum]           = K256Right1;
//                        RemovePiece(pos, K256Right1);
//                        NotNum++;
//                    }
//                }
//                //有了第二个棋子,才有第三个棋子哇
//                K256Right3 = psmv->SuperCap[DLoRight] + ky4;
//                if(K256Right3 != MyKing256){                                      
//                    int chess3     = pos->b256[K256Right3];
//                    if(chess2 == RPAO){
//                        PaoHuo256[PaoJiaNum-1]      = K256Right3;
//                        PaoHuoChess[PaoJiaNum-1]    = chess3;
//                    }
//                    if(chess3 == RPAO){ //第三个棋子是黑炮,1,第二个棋子不可能解将了, 
//                        //2, 第一个棋子如果不是红炮,也不能是解将了
//                        if(IsBlack(chess2)){
//                            Not256Pos[NotNum]           = K256Right2;
//                            RemovePiece(pos, K256Right2);
//                            NotNum++;
//                        }
//                        if(IsBlack(chess1) && chess2 != RCHE){
//                            Not256Pos[NotNum]           = K256Right1;
//                            RemovePiece(pos, K256Right1);
//                            NotNum++;
//                        }
//                    }
//                }                
//            }
//        }
//        //判断一下有没有马在将军哇
//        for(checkSq256 = PieceListStart(pos,RMA); checkSq256 > 0x32; checkSq256 = NextPiece(pos,checkSq256)){
//            int x       = horseLegTab(MyKing256 - checkSq256 + 256);
//            leg256      = checkSq256 + x;
//            int leg14;
//            if(x){                                  //马有可能将军 
//                leg14   = pos->b256[leg256];
//                if(!leg14){                         //马腿无子
//                    CheckType                       |= MaCheck;
//                    CheckPos256[CheckPieceNum]       = checkSq256;
//                    MaLeg256[CheckPieceNum]          = leg256;  //如果是马将军,必有马腿哇,为以后解将方便哇
//                    CheckPieceNum++;
//                }
//                else{                               //马腿上有棋子哇
//                    if(IsBlack(leg14)){
//                        //得判断一下,是不是已经拿走了
//                        bool isRemove = false;
//                        for(int i = 0; i < NotNum; i++){
//                            if(leg256 == Not256Pos[i]){
//                                isRemove = true;
//                                break;
//                            }
//                        }
//                        //Not48Pos[NotNum]        = leg48;
//                        if(!isRemove){
//                            Not256Pos[NotNum]       = leg256;
//                            RemovePiece(pos, leg256);
//                            NotNum++;
//                        }
//                    }
//                }
//            }
//        }
//        ASSERT(CheckPieceNum!=0);      //走子方一定要被将军了 ////////////////////////////
//#if defined(DEBUG_EVASION_MOVE)   
//        if(CheckPieceNum == 0){ 
//            board_display(pos,"ERROR 黑方解将,但没有棋子在将!!!!\n",stdout);
//            //return ms;
//        }
//#endif
//
//        //----------------------------------------------------------下面开始算解将步哇
//
//        checkSq256    = CheckPos256[0];
//        checkSqX      = StoX(checkSq256);
//        checkSqY      = StoY(checkSq256);        //得到将军的第一个棋子的方向哇 
//        tCheckDir1    = GetDir(checkSq256,MyKing256);
//        //根据将军的棋子的类型来解将
//        switch(CheckType){
//case PaoCheck:              //当前是炮在将军               
//    paojia256       = PaoJia256[0];
//    paojiaX         = StoX(paojia256);
//    paojiaY         = StoY(paojia256);
//    paohouChess     = PaoHuoChess[0];       //炮架后的棋子类型
//    paojiaChess     = PaoJiaChess[0]; 
//    if(PaoJiaNum > 1){                    
//        //DisplayChessBoard("ERROR 有两个黑炮同时在将！！\n"); 
//        //也有可能解将, 只有一个炮架是自己的的棋才能解将
//        //#define  BKING             7
//        int jian;
//        //int jiadir;
//        uint32 tjiadir;
//        int paojia2;
//        //int paojia2chess;
//        int paocheck2;
//        if(paojiaChess < BKING){   //不是自己的棋子
//            if(PaoJiaChess[1] < BKING){                            
//                //board_display(pos,"有两个红炮同时在将！!,没法解将\n",stdout);
//                //break;
//                break;
//            }
//            else{
//                paojia256       = PaoJia256[1];
//                paojiaX         = StoX(paojia256);
//                paojiaY         = StoY(paojia256);
//                paohouChess     = PaoHuoChess[1];       //炮架后的棋子类型
//                paojiaChess     = PaoJiaChess[1]; 
//                paojia2         = PaoJia256[0];
//                paocheck2       = CheckPos256[0];
//                tjiadir         = GetDir(paojia2,MyKing256);
//                jian = 1;
//            }
//        }
//        else{
//            paojia2   = PaoJia256[1];
//            paocheck2 = CheckPos256[1];
//            //jiadir  = IsCanTo(paojia2,MyKing256);
//            tjiadir  = GetDir(paojia2,MyKing256);
//            jian   = 0;
//        }
//        OutCheckF = 0;
//        OutCheckR = 0;
//
//        if(tjiadir & DirUp){
//            OutCheckF =(UpMask(MyKing256) & LoMask(paocheck2) 
//                | yBitMask(paocheck2)) ^ yBitMask(paojia2); // 异或的优先级高, 得加上括号哇
//        }
//        else if(tjiadir & DirLow){
//            OutCheckF = (UpMask(paocheck2) & LoMask(MyKing256)
//                | yBitMask(paocheck2)) ^ yBitMask(paojia2);
//        }
//        else if(tjiadir & DirLeft){
//            OutCheckR = (RightMask(paocheck2) & LeftMask(MyKing256) 
//                | xBitMask(paocheck2)) ^ xBitMask(paojia2);
//        }
//        else if(tjiadir & DirRight){
//            OutCheckR = (LeftMask(paocheck2) & RightMask(MyKing256) 
//                | xBitMask(paocheck2)) ^ xBitMask(paojia2);
//        }
//        switch(paojiaChess){    //只有黑马,黑仕,黑象才可能解双炮将
//            uint8* lpDst;
//            int    tmp;
//case BMA:                            
//    lpDst     = PreMaAndLegMove[paojia256];
//    tmp      = MOVE_FromFC(paojia256,BMA);
//    while(int to256 = *lpDst++){     //可以挡炮或吃炮                                
//        int tx    = StoX(to256);
//        int ty    = StoY(to256);
//        if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//            || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){
//                if(pos->b256[*lpDst] == 0){  //马腿没有棋子
//                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                } 
//        } 
//        lpDst++;
//    }                            
//    break;
//case BSHI:
//    lpDst = PreShiXiangAndEyeMove[paojia256];
//    tmp   = MOVE_FromFC(paojia256,BSHI);
//    while(int to256 = *lpDst++){                                
//        int tx    = StoX(to256);
//        int ty    = StoY(to256);
//        if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//            || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){ 
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//        }
//        lpDst++;
//    }
//    break;
//case BXIANG:
//    lpDst = PreShiXiangAndEyeMove[paojia256];
//    tmp   = MOVE_FromFC(paojia256,BXIANG);
//    while(int to256 = *lpDst++){                                
//        int tx    = StoX(to256);
//        int ty    = StoY(to256);
//        if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//            || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){
//                if(pos->b256[*lpDst] == 0){  //象眼上没有棋子 if(!tree->board.B256[(nSrc+nDst)>>1])                    
//                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                } 
//        }
//        lpDst++;
//    }
//    break;
//default:
//    break;
//        }
//    }
//    else{                   //只有一个炮在将 
//        //先判断一下炮架上的棋子能不能走
//        if(paojiaChess > RPAWN){
//            if(paohouChess == RPAO){
//                if(paojiaChess == BPAO){
//                    (ms++)->move = MOVE_FROM(paojia256,BPAO,PaoHuo256[0],RPAO);
//                }
//            }
//            else{ 
//                int nSrcX = StoX(paojia256);
//                int nSrcY = StoY(paojia256);
//                int sr16  = pos->wBitRanks[nSrcY];
//                int sf16  = pos->wBitFiles[nSrcX];  
//                switch(paojiaChess){                                            //对于炮架上的棋子
//                    int     tmp;
//                    uint8*  lpDst;
//case BPAWN:     //黑卒是炮架
//    //1, 向下吃炮解将
//    tmp      = MOVE_FromFC(paojia256,BPAWN);
//    if((paojia256+16) == checkSq256){ 
//        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RPAO);
//    }
//    //2,左右动卒解将
//    if(paojia256>0x7b){      //过河兵才能解将哇
//        int to256 = paojia256-1;
//        int to14  = pos->b256[to256];
//        if(!IsBlack(to14)){    
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//        to256 = paojia256+1;
//        to14  = pos->b256[to256];
//        if(!IsBlack(to14)){   
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    break;
//case BPAO:      //黑炮是炮架 
//    tmp      = MOVE_FromFC(paojia256,BPAO);
//    psmv     = RankMove(nSrcX,sr16);
//
//    //左右吃了步
//    nDisp = paojia256 & 0xf0;
//    to256 = psmv->CannonCap[DUpLeft] + nDisp;
//    if(to256 != paojia256){
//        int to14    = pos->b256[to256];
//        if(IsWhite(to14)){ 
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    to256 = psmv->CannonCap[DLoRight] + nDisp;
//    if(to256 != paojia256){
//        int to14    = pos->b256[to256];
//        if(IsWhite(to14)){ 
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    if(tCheckDir1 & (DirUp+DirLow)){ //左右不吃子步
//        //左右不吃子步
//        to256 = psmv->NonCap[DUpLeft] + nDisp;
//        while(to256 != paojia256){
//            (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            to256++;
//        }
//        to256 = psmv->NonCap[DLoRight] + nDisp;
//        while(to256 != paojia256){
//            (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            to256--;
//        }
//    }
//    // 上下吃子步
//    psmv    = FileMove(nSrcY,sf16);
//    to256   = psmv->CannonCap[DUpLeft] + nSrcX;
//    if(to256 != paojia256){
//        int to14 = pos->b256[to256];
//        if(IsWhite(to14)){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    to256   = psmv->CannonCap[DLoRight] + nSrcX;
//    if(to256 != paojia256){
//        int to14 = pos->b256[to256];
//        if(IsWhite(to14)){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    if(tCheckDir1 & (DirLeft+DirRight)){    //不吃子步
//        to256 = psmv->NonCap[DUpLeft] + nSrcX;
//        while(to256 != paojia256){
//            (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            to256 += 16;
//        }
//        to256 = psmv->NonCap[DLoRight] + nSrcX;
//        while(to256 != paojia256){
//            (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            to256 -= 16;
//        }
//    }
//    break;
//case BCHE:      //黑车是炮架   
//    tmp      = MOVE_FromFC(paojia256,BCHE);
//    psmv     = RankMove(nSrcX,sr16);
//    //左右吃子步
//    nDisp    = paojia256 & 0xf0;
//    to256    = psmv->RookCap[DUpLeft] + nDisp;
//    if(to256 != paojia256){
//        int to14 = pos->b256[to256];
//        if(IsWhite(to14)){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    to256    = psmv->RookCap[DLoRight] + nDisp;
//    if(to256 != paojia256){
//        int to14 = pos->b256[to256];
//        if(IsWhite(to14)){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    if(tCheckDir1 & (DirUp+DirLow)){        //上下将,可左右不吃子解将
//        to256 = psmv->NonCap[DUpLeft] + nDisp;
//        while(to256 != paojia256){
//            (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            to256++;
//        }
//        to256 = psmv->NonCap[DLoRight] + nDisp;
//        while(to256 != paojia256){
//            (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            to256--;
//        }
//    }
//    //上下方向解将
//    psmv  = FileMove(nSrcY,sf16);
//    to256 = psmv->RookCap[DUpLeft] + nSrcX;
//    if(to256 != paojia256){
//        int to14 = pos->b256[to256];
//        if(IsWhite(to14)){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    to256 = psmv->RookCap[DLoRight] + nSrcX;
//    if(to256 != paojia256){
//        int to14 = pos->b256[to256];
//        if(IsWhite(to14)){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    //左右将,可上下不吃子解将
//    if(tCheckDir1 & (DirLeft+DirRight)){    //不吃子步
//        to256 = psmv->NonCap[DUpLeft] + nSrcX;
//        while(to256 != paojia256){
//            (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            to256 += 16;
//        }
//        to256 = psmv->NonCap[DLoRight] + nSrcX;
//        while(to256 != paojia256){
//            (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            to256 -= 16;
//        }
//    }                                   
//    break;
//case BMA:       //黑马是炮架        //马向8个方向解将 
//    tmp      = MOVE_FromFC(paojia256,BMA);
//    lpDst = PreMaAndLegMove[paojia256];
//    while(int to256 = *lpDst++){                                         
//        if(pos->b256[*lpDst]){  //马腿有棋子
//            lpDst++;
//            continue;
//        }
//        lpDst++;
//        int to14  =  pos->b256[to256];
//        if(IsBlack(to14)){    //是自己的的棋子
//            continue;  
//        }
//        int tx = StoX(to256);
//        int ty = StoY(to256);
//        if(tx == MyKingX){  //走到了File上
//            if(NotToFile & yBitMask(to256)){
//                continue;
//            }
//        }
//        else if(ty == MyKingY){
//            if(NotToRank & xBitMask(to256)){
//                continue;
//            }
//        }  
//        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//    }                                   
//    break;
//case BXIANG:    //黑相是炮架
//    tmp      = MOVE_FromFC(paojia256,BXIANG);
//    lpDst  = PreShiXiangAndEyeMove[paojia256];
//    while(int to256 = *lpDst++){
//        if(pos->b256[*lpDst]){  //相眼有棋子
//            lpDst++;
//            continue;
//        }
//        lpDst++;
//        int to14    = pos->b256[to256];
//        if(IsBlack(to14)){
//            continue;
//        }
//        int tx = StoX(to256);
//        int ty = StoY(to256);
//        if(tx == MyKingX){  //走到了File上
//            if(NotToFile & yBitMask(to256)){
//                continue;
//            }
//        }
//        else if(ty == MyKingY){
//            if(NotToRank & xBitMask(to256)){
//                continue;
//            }
//        } 
//        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//    }
//    break;
//case BSHI:      //黑仕是炮架
//    lpDst  = PreShiXiangAndEyeMove[paojia256];
//    tmp      = MOVE_FromFC(paojia256,BSHI);
//    while(int to256 = *lpDst++){                                         
//        int to14    = pos->b256[to256];
//        if(IsBlack(to14)){      //如果是黑棋
//            continue;
//        }
//        /* if(tree->board.B256[(to256 + paojia256)>>1]){
//        continue;
//        }*/
//        int tx = StoX(to256);
//        int ty = StoY(to256);
//        if(tx == MyKingX){  //走到了File上
//            if(NotToFile & yBitMask(to256)){
//                continue;
//            }
//        }
//        else if(ty == MyKingY){
//            if(NotToRank & xBitMask(to256)){
//                continue;
//            }
//        } 
//        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//    }
//    break;
//default:
//    break;
//                }
//            }
//
//        }
//        //以下情况的棋子都不是炮架了
//        //1.黑卒解红炮将*************************************************************
//        //if(CheckDir1 == DirLow){                             //黑卒只能解下面的炮将  
//        if(tCheckDir1 & DirLow){
//            for(int nSrc256 = PieceListStart(pos,BPAWN); nSrc256 > 0x32 ; nSrc256 = NextPiece(pos,nSrc256)){ 
//                if(nSrc256 == paojia256){
//                    continue;
//                }
//
//                if(nSrc256 < 0x7b){
//                    continue;
//                }
//                int tmp      = MOVE_FromFC(nSrc256,BPAWN);
//                //不在炮架上的兵只能左右解将哇
//                int to256 = nSrc256+1;
//                int tx    = StoX(to256);
//                if(tx == MyKingX){
//                    if(yBitMask(to256) & OutCheckF){ 
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                    }
//                }
//                to256 = nSrc256-1;
//                tx    = StoX(to256);
//                if(tx == MyKingX){
//                    if(yBitMask(to256) & OutCheckF){  
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                    }
//                }
//            }
//        }// End 黑卒将红炮将
//        //黑仕解红炮将
//        for(int nSrc256 = PieceListStart(pos,BSHI); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){                
//            if(nSrc256 == paojia256){
//                continue;
//            }
//
//            int tmp      = MOVE_FromFC(nSrc256,BSHI); 
//            uint8* lpDst = PreShiXiangAndEyeMove[nSrc256];
//            while(int to256 = *lpDst++){                                
//                int tx    = StoX(to256);
//                int ty    = StoY(to256);
//                if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                    || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){ 
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                }
//            }           
//        }//黑仕解红炮将 End
//        //黑象解炮将
//        for(int nSrc256 = PieceListStart(pos,BXIANG); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){                
//            if(nSrc256 == paojia256){
//                continue;
//            }
//
//            int tmp         = MOVE_FromFC(nSrc256,BXIANG); 
//            uint8* lpDst = PreShiXiangAndEyeMove[nSrc256];
//            while(int to256 = *lpDst++){
//                int tx    = StoX(to256);
//                int ty    = StoY(to256);
//                if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                    || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){
//                        if(pos->b256[*lpDst] == 0){  //象眼上没有棋子 if(!tree->board.B256[(nSrc+nDst)>>1])  
//                            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                        } 
//                }
//                lpDst++;
//            }           
//        }//黑象解炮将 End
//        //黑马解红炮将
//        for(int nSrc256 = PieceListStart(pos,BMA); nSrc256 > 0x32 ; nSrc256 = NextPiece(pos,nSrc256)){                
//            if(nSrc256 == paojia256){
//                continue;
//            }
//            int tmp      = MOVE_FromFC(nSrc256,BMA); 
//            uint8* lpDst = PreMaAndLegMove[nSrc256];
//            while(int to256 = *lpDst++){     //可以挡炮或吃炮                                
//                int tx    = StoX(to256);
//                int ty    = StoY(to256);
//                if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                    || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){
//                        if(pos->b256[*lpDst] == 0){  //马腿没有棋子  
//                            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                        } 
//                } 
//                lpDst++;
//            }                                    
//        }   ////黑马解红炮将 End
//        // 2. 黑炮解红炮将
//        for(int nSrc256 = PieceListStart(pos,BPAO); nSrc256 > 0x32 ; nSrc256 = NextPiece(pos,nSrc256)){                
//            if(nSrc256 == paojia256){
//                continue;
//            }
//            int tmp      = MOVE_FromFC(nSrc256,BPAO); 
//            int nSrcX = StoX(nSrc256);
//            int nSrcY = StoY(nSrc256);
//            psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//            psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]);
//            if(OutCheckF){                  //上下方向可以解将               
//                if(nSrcX == checkSqX){      //在同一行,只有吃包哇 
//                    if(psF->CannonCap & yBitMask(checkSq256)){
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RPAO);
//                    }
//                }
//                else{                       //不在同一列, 吃包,挡包
//                    if(OutCheckF & yBitMask(nSrc256)){  //在解将的列上
//                        if(nSrcY == checkSqY){          //在同一行
//                            if(psR->CannonCap & xBitMask(checkSq256)){
//                                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RPAO);
//                            }
//                        }
//                        else{
//                            if(psR->RookCap & xBitMask(checkSq256)){
//                                (ms++)->move =  MOVE_FromFc_to(tmp,XYtoS(checkSqX,nSrcY));
//                            }
//                        }                                      
//                    }
//                }
//            }
//            else if(OutCheckR){              //左右方向可以解将                
//                if(nSrcY == checkSqY){       //在同一行,只有吃炮
//                    if(psR->CannonCap & xBitMask(checkSq256)){
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RPAO);
//                    }
//                }
//                else{
//                    if(OutCheckR & xBitMask(nSrc256)){
//                        if(nSrcX == checkSqX){
//                            if(psF->CannonCap & yBitMask(checkSq256)){
//                                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RPAO);                            
//                            }
//                        }
//                        else{                    
//                            if(psF->RookCap & yBitMask(checkSq256)){
//                                (ms++)->move =  MOVE_FromFc_to(tmp,XYtoS(nSrcX,checkSqY));                          
//                            }
//                        }
//                    }
//                }
//            }          
//        } // End 黑炮解红炮将
//        //3.黑车解红炮将*************************************************************
//        for(int nSrc256 = PieceListStart(pos,BCHE); nSrc256 > 0x32 ; nSrc256 = NextPiece(pos,nSrc256)){ 
//            if(nSrc256 == paojia256){
//                continue;
//            }
//            int tmp      = MOVE_FromFC(nSrc256,BCHE); 
//            int nSrcX = StoX(nSrc256);
//            int nSrcY = StoY(nSrc256);
//            psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//            psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]);
//            if(OutCheckF){                  //上下方向可以解将
//                if(nSrcX == checkSqX){      //在同一行,只有吃包哇                   
//                    if(psF->RookCap & yBitMask(checkSq256)){
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RPAO);
//                    }
//                }
//                else{                       //不在同一列, 吃包,挡包
//                    if(OutCheckF & yBitMask(nSrc256)){  //在解将的列上                        
//                        if(psR->RookCap & xBitMask(checkSq256)){
//                            int target256 = XYtoS(checkSqX,nSrcY);                             
//                            (ms++)->move =  MOVE_FromFc_to_tc(tmp,target256,pos->b256[target256]);
//                        }
//                    }
//                }
//            }
//            else if(OutCheckR){              //左右方向可以解将
//                if(nSrcY == checkSqY){      //在同一列,只有吃炮
//                    if(psR->RookCap & xBitMask(checkSq256)){
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RPAO);
//                    }
//                }
//                else{
//                    if(OutCheckR & xBitMask(nSrc256)){ //在解将的列上哇
//                        if(psF->RookCap & yBitMask(checkSq256)){
//                            int target256 = XYtoS(nSrcX,checkSqY);                             
//                            (ms++)->move =  MOVE_FromFc_to_tc(tmp,target256,pos->b256[target256]);
//                        }
//                    }
//                }
//            }          
//        } // End 黑车解红炮将 
//    }                
//    break;  //..........只有一个炮在将 End
//case CheCheck:     //当前只有一个车在将 1, 吃车, 2, 挡车
//    if(CheckPieceNum > 1){                    
//        //board_display(board,"ERROR 有两个红车同时在将！！, 怎么办哇.....\n",log_file); 
//    }
//    else{
//        if(tCheckDir1 & DirUp){
//            OutCheckF = UpMask(MyKing256) & LoMask(checkSq256) | yBitMask(checkSq256); // 吃车,挡车哇
//        }
//        else if(tCheckDir1 & DirLow){
//            OutCheckF = UpMask(checkSq256) & LoMask(MyKing256) | yBitMask(checkSq256);
//        }
//        else if(tCheckDir1 & DirLeft){
//            OutCheckR = (RightMask(checkSq256) & LeftMask(MyKing256)  | xBitMask(checkSq256));
//        }
//        else if(tCheckDir1 & DirRight){
//            OutCheckR = (RightMask(MyKing256) & LeftMask(checkSq256)  | xBitMask(checkSq256));
//        }
//        //1.黑卒解红车将*************************************************************
//        //if(CheckDir1 == DirLow){                             //黑卒只能将下面的红车将  
//        if(tCheckDir1 & DirLow){
//            for(int nSrc256 = PieceListStart(pos,BPAWN); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//                if(nSrc256 < 0x7b){
//                    continue;
//                }
//                int tmp      = MOVE_FromFC(nSrc256,BPAWN);
//                int to256 = nSrc256+1;
//                int tx    = StoX(to256);
//                if(tx == MyKingX){
//                    if(yBitMask(to256) & OutCheckF){  
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                    }
//                }
//                to256 = nSrc256-1;
//                tx    = StoX(to256);
//                if(tx == MyKingX){
//                    if(yBitMask(to256) & OutCheckF){
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                    }
//                }
//            }           
//        }// End 黑卒将红车将
//        //黑仕解红车将
//        for(int nSrc256 = PieceListStart(pos,BSHI); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,BSHI);   
//            uint8* lpDst = PreShiXiangAndEyeMove[nSrc256];
//            while(int to256 = *lpDst++){                                   
//                int tx    = StoX(to256);
//                int ty    = StoY(to256);
//                if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                    || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){ 
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                }
//            }            
//        }//黑仕解红车将 End
//        //黑象解红车将
//        for(int nSrc256 = PieceListStart(pos,BXIANG); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,BXIANG);  
//            uint8* lpDst = PreShiXiangAndEyeMove[nSrc256];
//            while(int to256 = *lpDst++){                                 
//                int tx    = StoX(to256);
//                int ty    = StoY(to256);
//                if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                    || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){
//                        if(pos->b256[*lpDst] == 0){  //象眼上没有棋子 if(!tree->board.B256[(nSrc+nDst)>>1])
//                            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                        } 
//                }
//                lpDst++;
//            }            
//        }//黑象解红车将 End
//        //黑马解红车将
//        for(int nSrc256 = PieceListStart(pos,BMA); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,BMA); 
//            uint8* lpDst = PreMaAndLegMove[nSrc256];
//            while(int to256 = *lpDst++){     //可以挡车或吃车                                
//                int tx    = StoX(to256);
//                int ty    = StoY(to256);
//                if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                    || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){
//                        if(pos->b256[*lpDst] == 0){  //马腿没有棋子
//                            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                        } 
//                } 
//                lpDst++;
//            }                                    
//        }  //黑马解红车将 End
//        // 2. 黑炮解红车将
//        for(int nSrc256 = PieceListStart(pos,BPAO); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,BPAO);  
//            int nSrcX = StoX(nSrc256);
//            int nSrcY = StoY(nSrc256);
//            psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//            psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]);
//            if(OutCheckF){                  //上下方向可以解将
//                if(nSrcX == checkSqX){      //在同一行,只有吃车哇
//                    if(psF->CannonCap & yBitMask(checkSq256)){
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RCHE);
//                    }
//                }
//                else{                       //不在同一列, 吃车,挡车
//                    if(OutCheckF & yBitMask(nSrc256)){  //在解将的列上
//                        if(nSrcY == checkSqY){          //在同一行
//                            if(psR->CannonCap & xBitMask(checkSq256)){                               
//                                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RCHE);
//                            }
//                        }
//                        else{
//                            if(psR->RookCap & xBitMask(checkSq256)){  
//                                (ms++)->move =  MOVE_FromFc_to(tmp,XYtoS(checkSqX,nSrcY));  
//                            }
//                        }                                      
//                    }
//                }
//            }
//            else if(OutCheckR){              //左右方向可以解将
//                if(nSrcY == checkSqY){       //在同一行,只有吃车
//                    if(psR->CannonCap & xBitMask(checkSq256)){
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RCHE);
//                    }
//                }
//                else{
//                    if(OutCheckR & xBitMask(nSrc256)){
//                        if(nSrcX == checkSqX){
//                            if(psF->CannonCap & yBitMask(checkSq256)){
//                                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RCHE);
//                            }
//                        }
//                        else{
//                            if(psF->RookCap & yBitMask(checkSq256)){  
//                                (ms++)->move =  MOVE_FromFc_to(tmp,XYtoS(nSrcX,checkSqY));  
//                            }
//                        }
//                    }
//                }
//            }           
//        } // End 黑炮解红车将
//        //3.黑车将红车将*************************************************************
//        for(int nSrc256 = PieceListStart(pos,BCHE); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,BCHE); 
//            int nSrcX = StoX(nSrc256);
//            int nSrcY = StoY(nSrc256);
//            psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//            psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]);  
//            if(OutCheckF){                  //上下方向可以解将
//                if(nSrcX == checkSqX){      //在同一行,只有吃车哇
//                    if(psF->RookCap & yBitMask(checkSq256)){
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RCHE);
//                    }
//                }
//                else{                       //不在同一列, 吃车,挡车
//                    if(OutCheckF & yBitMask(nSrc256)){  //在解将的列上
//                        if(psR->RookCap & xBitMask(checkSq256)){
//                            int target256 = XYtoS(checkSqX,nSrcY); 
//                            (ms++)->move =  MOVE_FromFc_to_tc(tmp,target256,pos->b256[target256]);
//                        }                                                                  
//                    }
//                }
//            }
//            else if(OutCheckR){              //左右方向可以解将
//                if(nSrcY == checkSqY){      //在同一列,只有吃车
//                    if(psR->RookCap & xBitMask(checkSq256)){
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RCHE);
//                    }
//                }
//                else{
//                    if(OutCheckR & xBitMask(nSrc256)){ //在解将的列上哇
//                        if(psF->RookCap & yBitMask(checkSq256)){
//                            int target256 = XYtoS(nSrcX,checkSqY);
//                            (ms++)->move =  MOVE_FromFc_to_tc(tmp,target256,pos->b256[target256]);
//                        }
//                    }
//                }
//            }           
//        } // End 黑车将红车将
//    }
//    break;      //End 红车将军
//case MaCheck:         //当前有马在将军哇, 1, 吃马, 2, 别马腿
//    if(CheckPieceNum > 1){        
//        if(MaLeg256[0] == MaLeg256[1]){  //同时有两个马在将,则只有Maleg相同才能解将
//            //查看黑仕能不能解将
//             leg256 = MaLeg256[0];
//             for(int nSrc256 = PieceListStart(pos,BSHI); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//                 int tmp      = MOVE_FromFC(nSrc256,BSHI);
//                 if(inBoard(leg256) & IN_BSHI){
//                     if(GetDir(nSrc256,leg256) & DirShi){
//                         (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                     }
//                 }                
//             }//黑仕解红马将 End
//             for(int nSrc256 = PieceListStart(pos,BXIANG); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//                 int tmp      = MOVE_FromFC(nSrc256,BXIANG); 
//                 if(inBoard(leg256) & IN_BXIANG){
//                     if(GetDir(nSrc256,leg256) & DirXiang){
//                         if(!pos->b256[(nSrc256 + leg256)>>1]){  //黑象眼没有棋子 
//                             (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                         } 
//                     }
//                 }
//             }//黑象解红马将 End
//              //黑马解红马将
//             for(int nSrc256 = PieceListStart(pos,BMA); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//                 int tmp      = MOVE_FromFC(nSrc256,BMA); 
//                 if(GetDir(nSrc256,leg256) & DirMa){
//                     if(!pos->b256[nSrc256 + horseLegTab(leg256 - nSrc256 + 256)]){  //马腿没有棋子 
//                         (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                     } 
//                 }               
//             } //黑马解红马将 End
//             // 2. 黑炮解红马将
//             for(int nSrc256 = PieceListStart(pos,BPAO); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//                 int tmp      = MOVE_FromFC(nSrc256,BPAO);  
//                 int nSrcX = StoX(nSrc256);
//                 int nSrcY = StoY(nSrc256);
//                 psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//                 psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]);             
//
//                 if(GetDir(nSrc256,leg256) & (DirUp+DirLow)){
//                     if(psF->RookCap & yBitMask(leg256)){ 
//                         (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                     }
//                 }
//                 else if(GetDir(nSrc256,leg256) & (DirLeft+DirRight)){
//                     if(psR->RookCap & xBitMask(leg256)){
//                         (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                     }
//                 }    
//             } // End 黑炮解红马将
//             for(int nSrc256 = PieceListStart(pos,BCHE); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//                 int tmp   = MOVE_FromFC(nSrc256,BCHE);  
//                 int nSrcX = StoX(nSrc256);
//                 int nSrcY = StoY(nSrc256);
//                 psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//                 psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]); 
//
//                 if(GetDir(nSrc256,leg256) & (DirUp+DirLow)){
//                     if(psF->RookCap & yBitMask(leg256)){ 
//                         (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                     }
//                 }
//                 else if(GetDir(nSrc256,leg256) & (DirLeft+DirRight)){
//                     if(psR->RookCap & xBitMask(leg256)){
//                         (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                     }
//                 }
//             } // End 黑车解红马将
//        }
//    }
//    else{//解马将, 不用再判断能不能走到那个位置, 因为不可能再形成其它的包将军
//        //1,  黑卒不可能解马将   //2,  黑仕解红马将 1, 吃马,挡马,
//        //Not256Pos[NotNum]       = leg256;
//        leg256 = MaLeg256[0];
//        for(int nSrc256 = PieceListStart(pos,BSHI); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,BSHI);
//            if(inBoard(leg256) & IN_BSHI){
//                if(GetDir(nSrc256,leg256) & DirShi){
//                    (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                }
//            }
//            if(inBoard(checkSq256) & IN_BSHI){
//                if(GetDir(nSrc256,checkSq256) & DirShi){
//                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RMA);
//                }
//            }
//        }//黑仕解红马将 End
//        //黑象解红马将   if(!tree->board.B256[(nSrc256 + to256)>>1])
//        for(int nSrc256 = PieceListStart(pos,BXIANG); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,BXIANG); 
//            if(inBoard(leg256) & IN_BXIANG){
//                if(GetDir(nSrc256,leg256) & DirXiang){
//                    if(!pos->b256[(nSrc256 + leg256)>>1]){  //黑象眼没有棋子 
//                        (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                    } 
//                }
//            }
//            if(inBoard(checkSq256) & IN_BXIANG){
//                if(GetDir(nSrc256,checkSq256) & DirXiang){
//                    if(!pos->b256[(nSrc256 + checkSq256)>>1]){  //黑象眼没有棋子 
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RMA);
//                    } 
//                }  
//            }
//        }//黑象解红马将 End
//        //黑马解红马将
//        for(int nSrc256 = PieceListStart(pos,BMA); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,BMA); 
//            if(GetDir(nSrc256,leg256) & DirMa){
//                if(!pos->b256[nSrc256 + horseLegTab(leg256 - nSrc256 + 256)]){  //马腿没有棋子 
//                    (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                } 
//            }
//            else  if(GetDir(nSrc256,checkSq256) & DirMa){
//                if(!pos->b256[nSrc256 + horseLegTab(checkSq256 - nSrc256 + 256)]){  //马腿没有棋子 
//                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RMA);
//                } 
//            }                
//        } //黑马解红马将 End
//        // 2. 黑炮解红马将
//        for(int nSrc256 = PieceListStart(pos,BPAO); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,BPAO);  
//            int nSrcX = StoX(nSrc256);
//            int nSrcY = StoY(nSrc256);
//            psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//            psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]);             
//
//            if(GetDir(nSrc256,leg256) & (DirUp+DirLow)){
//                if(psF->RookCap & yBitMask(leg256)){ 
//                    (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                }
//            }
//            else if(GetDir(nSrc256,leg256) & (DirLeft+DirRight)){
//                if(psR->RookCap & xBitMask(leg256)){
//                    (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                }
//            }
//            if(GetDir(nSrc256,checkSq256) & (DirUp+DirLow)){
//                if(psF->CannonCap & yBitMask(checkSq256)){ 
//                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RMA);
//                }
//            }
//            else if(GetDir(nSrc256,checkSq256) & (DirLeft+DirRight)){
//                if(psR->CannonCap & xBitMask(checkSq256)){
//                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RMA);
//                }
//            }
//        } // End 黑炮解红马将
//        // 2. 黑车解红马将
//        for(int nSrc256 = PieceListStart(pos,BCHE); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp   = MOVE_FromFC(nSrc256,BCHE);  
//            int nSrcX = StoX(nSrc256);
//            int nSrcY = StoY(nSrc256);
//            psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//            psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]); 
//
//            if(GetDir(nSrc256,leg256) & (DirUp+DirLow)){
//                if(psF->RookCap & yBitMask(leg256)){ 
//                    (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                }
//            }
//            else if(GetDir(nSrc256,leg256) & (DirLeft+DirRight)){
//                if(psR->RookCap & xBitMask(leg256)){
//                    (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                }
//            }
//            if(GetDir(nSrc256,checkSq256) & (DirUp+DirLow)){
//                if(psF->RookCap & yBitMask(checkSq256)){ 
//                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RMA);
//                }
//            }
//            else if(GetDir(nSrc256,checkSq256) & (DirLeft+DirRight)){
//                if(psR->RookCap & xBitMask(checkSq256)){ 
//                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RMA);
//                }
//            }
//        } // End 黑车解红马将
//    }
//    break;            //End 黑马将军
//case PawnCheck:       //光一个红兵在将, 不可能同时有两个兵在将, 只有吃兵来解将
//    //2, 黑象解红兵将, 1, 黑卒不可能解红兵将
//    for(int nSrc256 = PieceListStart(pos,BXIANG); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp   = MOVE_FromFC(nSrc256,BXIANG);
//        //if(IsCanTo(nSrc256,checkSq256) == DirXiang){    //黑象能吃到
//        if(GetDir(nSrc256,checkSq256) & DirXiang){
//            if(!pos->b256[(nSrc256 + checkSq256)>>1]){                                 
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RPAWN);
//            }
//        }       
//    } // End 黑象解红兵将,
//    //3,黑士解红兵将
//    if(inBoard(checkSq256) & IN_BSHI){
//        for(int nSrc256 = PieceListStart(pos,BSHI); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp   = MOVE_FromFC(nSrc256,BSHI); 
//            if(GetDir(nSrc256,checkSq256) & DirShi){
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RPAWN);
//            }  
//        }
//    }//黑士解红兵将 End                
//    //3,黑马解红兵将                
//    for(int nSrc256 = PieceListStart(pos,BMA); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp   = MOVE_FromFC(nSrc256,BMA); 
//        if(GetDir(nSrc256,checkSq256) & DirMa){
//            if(!pos->b256[nSrc256 + horseLegTab(checkSq256 - nSrc256 + 256)]){  //马腿没有棋子                                
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RPAWN);
//            } 
//        }                  
//    } //黑马解红兵将   End
//    //黑炮解红兵将                
//    for(int nSrc256 = PieceListStart(pos,BPAO); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp   = MOVE_FromFC(nSrc256,BPAO);  
//        int nSrcX = StoX(nSrc256);
//        int nSrcY = StoY(nSrc256);
//        int sr16  = pos->wBitRanks[nSrcY];
//        int sf16  = pos->wBitFiles[nSrcX];
//        psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//        psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]);   
//
//        if(GetDir(nSrc256,checkSq256) & (DirUp+DirLow)){
//            if(psF->CannonCap & yBitMask(checkSq256)){ 
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RPAWN);
//            }
//        }
//        else if(GetDir(nSrc256,checkSq256) & (DirLeft+DirRight)){
//            if(psR->CannonCap & xBitMask(checkSq256)){
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RPAWN);
//            }
//        }
//    } // End 黑炮解红兵将 
//    //黑车解红兵将                
//    for(int nSrc256 = PieceListStart(pos,BCHE); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp   = MOVE_FromFC(nSrc256,BCHE);   
//        int nSrcX = StoX(nSrc256);
//        int nSrcY = StoY(nSrc256);
//        psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//        psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]); 
//        if(GetDir(nSrc256,checkSq256) & (DirUp+DirLow)){
//            if(psF->RookCap & yBitMask(checkSq256)){
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RPAWN);
//            }
//        }
//        else if(GetDir(nSrc256,checkSq256) & (DirLeft+DirRight)){
//            if(psR->RookCap & xBitMask(checkSq256)){  
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RPAWN);
//            }
//        }
//    } // End 红车解黑卒将
//    break;
//case MaCheck | PaoCheck:    //红马红炮双将,可解将
//    paojia256       = PaoJia256[0];
//    //if(NextPiece(pos,paojia256) < 0x33){ //if(board->P48[board->P256[paojia256]] == 0){   //炮架上的棋子不可以走哇
//    //    break;
//    //}
//    paojiaCan = true;
//    for(int i = 0; i<NotNum; i++){
//        if(paojia256 == Not256Pos[i]){
//            paojiaCan = false;
//            break;
//        }
//    }
//    if(false == paojiaCan){
//        break;
//    }
//    leg256          = MaLeg256[1]; 
//    paohouChess     = PaoHuoChess[0];       //炮架后的棋子类型
//    paojiaChess     = PaoJiaChess[0]; 
//    int tmp;
//    int nSrcX;
//    int nSrcY;
//    switch(paojiaChess){
//
//        //还得判断一下炮架上的棋子能不能走哇
//
//        //case BPAWN:             //不可能
//        //    Print(4095,"马炮双将,红兵没法解将,动将解将");
//        //    DisplayChessBoard(tree->board);
//        //    break;                        
//case BXIANG:            //不可能 
//    tmp   = MOVE_FromFC(paojia256,BXIANG); 
//    if(inBoard(leg256) & IN_BXIANG){
//        if(GetDir(paojia256,leg256) & DirXiang){
//            if(!pos->b256[(paojia256 + leg256)>>1]){  //相眼没有棋子 
//                (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//            }
//        }
//    }
//    if(inBoard(CheckPos256[1]) & IN_BXIANG){
//        if(GetDir(paojia256,CheckPos256[1]) & DirXiang){
//            if(!pos->b256[(paojia256 + CheckPos256[1])>>1]){  //相眼没有棋子 
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,CheckPos256[1],RMA);
//            }
//        }
//    }
//    break;
//case BSHI:
//    tmp   = MOVE_FromFC(paojia256,BSHI); 
//    if(inBoard(leg256) & IN_BSHI){
//        if(GetDir(paojia256,leg256) & DirShi){
//            (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//        }
//    }
//    if(inBoard(CheckPos256[1]) & IN_BSHI){
//        if(GetDir(paojia256,CheckPos256[1]) & DirShi){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,CheckPos256[1],RMA);
//        }
//    }
//    break;
//case BMA:
//    tmp   = MOVE_FromFC(paojia256,BMA); 
//    if(GetDir(paojia256,leg256) & DirMa){
//        if(!pos->b256[paojia256 + horseLegTab(leg256 - paojia256 + 256)]){  //马腿没有棋子
//            (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//        } 
//    }
//    else if(GetDir(paojia256,CheckPos256[1]) & DirMa){
//        if(!pos->b256[paojia256 + horseLegTab(CheckPos256[1] - paojia256 + 256)]){  //马腿没有棋子
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,CheckPos256[1],RMA);
//        } 
//    } 
//    break;
//case BPAO:
//    tmp   = MOVE_FromFC(paojia256,BPAO); 
//    nSrcX = StoX(paojia256);
//    nSrcY = StoY(paojia256);
//    psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//    psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]);       //能不能走到马腿
//    if(GetDir(paojia256,leg256) & (DirUp+DirLow)){
//        if(psF->RookCap & yBitMask(leg256)){ 
//            (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//        }
//    }
//    else if(GetDir(paojia256,leg256) & (DirLeft+DirRight)){
//        if(psR->RookCap & xBitMask(leg256)){
//            (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//        }
//    }
//    if(GetDir(paojia256,CheckPos256[1]) & (DirUp+DirLow)){
//        if(psF->CannonCap & yBitMask(CheckPos256[1])){ 
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,CheckPos256[1],RMA);
//        }
//    }
//    else if(GetDir(paojia256,CheckPos256[1]) & (DirRight+DirLeft)){
//        if(psR->CannonCap & xBitMask(CheckPos256[1])){ 
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,CheckPos256[1],RMA);
//        }
//    }
//    break;
//case BCHE:
//    tmp      = MOVE_FromFC(paojia256,BCHE);
//    nSrcX = StoX(paojia256);
//    nSrcY = StoY(paojia256);
//    psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//    psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]); 
//
//    if(GetDir(paojia256,leg256) & (DirUp+DirLow)){
//        if(psF->RookCap & yBitMask(leg256)){ 
//            (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//        }
//    }
//    else if(GetDir(paojia256,leg256) & (DirLeft+DirRight)){
//        if(psR->RookCap & xBitMask(leg256)){
//            (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//        }
//    }
//    if(GetDir(paojia256,CheckPos256[1]) & (DirUp+DirLow)){
//        if(psF->RookCap & yBitMask(CheckPos256[1])){ 
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,CheckPos256[1],RMA);
//        }
//    }
//    else if(GetDir(paojia256,CheckPos256[1]) & (DirRight+DirLeft)){
//        if(psR->RookCap & xBitMask(CheckPos256[1])){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,CheckPos256[1],RMA);
//        }
//    }
//    break;
//default:
//    break;
//    }
//    break;
//case CheCheck | PaoCheck:   //车炮双将, 有些情况可解将, 如果不在一直线,不可解将
//    if(CheckPieceNum > 2){  //还有棋子在将,不能解将
//        break;
//    }
//    tCheckDir1 = GetDir(CheckPos256[1],CheckPos256[0]);
//    if(!(tCheckDir1 & DirChe)){               
//        /* Print(4095,"红方车炮双将,且不在一直线, 没法解将,只有动将解将");
//        DisplayChessBoard(tree->board); */
//        break;
//    } 
//    if(tCheckDir1 & DirUp){
//        OutCheckF  = UpMask(MyKing256) & LoMask(K256Up1);
//    }
//    else if(tCheckDir1 & DirLow){
//        OutCheckF  = LoMask(MyKing256) & UpMask(K256Lo1); 
//    }
//    else if(tCheckDir1 & DirLeft){
//        OutCheckR  = LeftMask(MyKing256) &  RightMask(K256Left1);
//    }
//    else if(tCheckDir1 & DirRight){
//        OutCheckR =  RightMask(MyKing256) & LeftMask(K256Right1);
//    }
//    //1.黑卒解车炮将*************************************************************
//    //if(CheckDir1 == DirLow){                             //黑卒只能解下面的车炮将   
//    if(tCheckDir1 & DirLow){
//        for(int nSrc256 = PieceListStart(pos,BPAWN); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp   = MOVE_FromFC(nSrc256,BPAWN); 
//            if(nSrc256 < 0x7b){
//                continue;
//            }
//            //不在炮架上的卒只能左右解将哇
//            int to256 = nSrc256+1;
//            int tx    = StoX(to256);
//            if(tx == MyKingX){
//                if(yBitMask(to256) & OutCheckF){
//                    (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//                }
//            }
//            to256 = nSrc256-1;
//            tx    = StoX(to256);
//            if(tx == MyKingX){
//                if(yBitMask(to256) & OutCheckF){
//                    (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//                }
//            }
//        }       
//    }// End 黑卒解车炮将
//    //黑仕解车炮将
//    for(int nSrc256 = PieceListStart(pos,BSHI); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp      = MOVE_FromFC(nSrc256,BSHI);  
//        uint8* lpDst = PreShiXiangAndEyeMove[nSrc256];
//        while(int to256 = *lpDst++){                             
//            int tx    = StoX(to256);
//            int ty    = StoY(to256);
//            if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){  
//                    (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            }
//        }        
//    }//黑仕解车炮将 End
//    //黑象解车炮将
//    for(int nSrc256 = PieceListStart(pos,BXIANG); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp      = MOVE_FromFC(nSrc256,BXIANG); 
//        uint8* lpDst = PreShiXiangAndEyeMove[nSrc256];
//        while(int to256 = *lpDst++){                            
//            int tx    = StoX(to256);
//            int ty    = StoY(to256);
//            if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){
//                    if(!pos->b256[*lpDst]){  //象眼上没有棋子 if(!tree->board.B256[(nSrc+nDst)>>1])
//                        (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//                    }
//            }
//            lpDst++;
//        }       
//    }//黑象解车炮将 End
//    //黑马解车炮将
//    for(int nSrc256 = PieceListStart(pos,BMA); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp      = MOVE_FromFC(nSrc256,BMA); 
//        uint8* lpDst = PreMaAndLegMove[nSrc256];
//        while(int to256 = *lpDst++){     //可以挡炮或吃炮                            
//            int tx    = StoX(to256);
//            int ty    = StoY(to256);
//            if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){
//                    if(!pos->b256[*lpDst]){  //马腿没有棋子
//                        (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//                    } 
//            }
//            lpDst++;
//        }                               
//    } ////黑马解车炮将 End
//    // 2. 黑炮解红车炮将
//    for(int nSrc256 = PieceListStart(pos,BPAO); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp   = MOVE_FromFC(nSrc256,BPAO);  
//        int nSrcX = StoX(nSrc256);
//        int nSrcY = StoY(nSrc256);
//        psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//        psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]); 
//
//        if(OutCheckF){                  //上下方向可以解将
//            if(nSrcX != checkSqX){      //不在同一行,                                                    
//                if(OutCheckF & yBitMask(nSrc256)){  //在解将的列上
//                    if(nSrcY != checkSqY){          //不在同一行                                           
//                        if(psR->RookCap & xBitMask(checkSq256)){    //挡车
//                            (ms++)->move =  MOVE_FromFc_to(tmp,XYtoS(checkSqX,nSrcY)); 
//                        }
//                    }                                      
//                }
//            }
//        }
//        else if(OutCheckR){              //左右方向可以解将
//            if(nSrcY != checkSqY){                                       
//                if(OutCheckR & xBitMask(nSrc256)){
//                    if(nSrcX != checkSqX){                                          
//                        if(psF->RookCap & yBitMask(checkSq256)){
//                            (ms++)->move =  MOVE_FromFc_to(tmp,XYtoS(nSrcX,checkSqY)); 
//                        }
//                    }
//                }
//            }
//        }        
//    } // End // 2. 黑车解红车炮将
//
//    for(int nSrc256 = PieceListStart(pos,BCHE); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp   = MOVE_FromFC(nSrc256,BCHE);  
//        int nSrcX = StoX(nSrc256);
//        int nSrcY = StoY(nSrc256);
//        psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//        psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]); 
//
//        if(OutCheckF){                  //上下方向可以解将
//            if(nSrcX != checkSqX){      //不在同一行,                                                    
//                if(OutCheckF & yBitMask(nSrc256)){  //在解将的列上
//                    if(nSrcY != checkSqY){          //不在同一行                                           
//                        if(psR->RookCap & xBitMask(checkSq256)){    //挡车
//                            (ms++)->move =  MOVE_FromFc_to(tmp,XYtoS(checkSqX,nSrcY)); 
//                        }
//                    }                                      
//                }
//            }
//        }
//        else if(OutCheckR){              //左右方向可以解将
//            if(nSrcY != checkSqY){       //不在同一行,                                   
//                if(OutCheckR & xBitMask(nSrc256)){
//                    if(nSrcX != checkSqX){ 
//                        if(psF->RookCap & yBitMask(checkSq256)){   //挡车
//                            (ms++)->move =  MOVE_FromFc_to(tmp,XYtoS(nSrcX,checkSqY)); 
//                        }
//                    }
//                }
//            }
//        }       
//    } // End // 2. 黑炮解红车炮将 黑车可加在一起算,
//
//    break;
//case CheCheck | PawnCheck:  //车兵双将, 不动将不可能解将哇
//    /* Print(4095,"车兵双将,没法解将,只有动将解将");
//    DisplayChessBoard(tree->board);*/
//    break;
//case PaoCheck | PawnCheck:
//    /*Print(4095,"炮兵双将,没法解将,只有动将解将");
//    DisplayChessBoard(tree->board);*/
//    break;
//case MaCheck | PawnCheck:   //马兵双将,不可解将
//    //*DisplayChessBoard(tree->board);
//    //Print(4095,"马兵双将,没法解将");
//    break;            
//case CheCheck | MaCheck:    //车马双将,不可解将
//    /*DisplayChessBoard(tree->board);
//    Print(4095,"车马双将,没法解将");*/
//    break;            
//default:        //其它情况,不可能出现哇
//    /*Print(4095,"其它情况的将军,看一下有没办法解将哇！！, 怎么办哇.....");  
//    DisplayChessBoard(tree->board);*/
//    break;
//        }
//        // 最后动将来解将哇             
//        uint8* lpDst = PreKingMove[MyKing256];
//        int ktmp    = MOVE_FromFC(MyKing256,BKING); 
//        while(int to256 = *lpDst++){              
//            int to14        = pos->b256[to256];
//            int tx          = StoX(to256);
//            int ty          = StoY(to256);
//            int ky4         = to256 & 0xf0;
//            //int KingDir = IsCanTo(MyKing256,to256);
//            int tKingDir  = GetDir(MyKing256,to256);
//            if(!IsBlack(to14)){       //不是黑棋
//                if(tKingDir == tCheckDir1 && (CheckType & (CheCheck + PaoCheck))){
//                    continue;
//                }//如果将走的方向与将军的方向相同,且将军的棋子不是兵，那么就不可能解将
//                //再判断一下走将后会不会还是被将              
//
//                int kToF  = pos->wBitFiles[StoX(to256)] ^ yBitMask(MyKing256);     //这个应该是对的哇
//                int kToR  = pos->wBitRanks[StoY(to256)] ^ xBitMask(MyKing256);
//
//                //得to的到上下的信息
//                psmv = FileMove(ty,kToF); 
//                //得到现在将上的第一个棋子 tmp = kf & UpMask(nMyKing);
//                int tmp = psmv->RookCap[DUpLeft] + tx;
//                if(tmp != to256){
//                    checkChess = pos->b256[tmp];
//                    if(checkChess == RCHE ){
//                        continue;                        
//                    }
//                    //有了第一个才可能有第二个
//                    tmp = psmv->CannonCap[DUpLeft] + tx;
//                    if(tmp != to256){
//                        if(pos->b256[tmp] == RPAO){
//                            continue;
//                        }
//                    }
//                } 
//                //得到将下面的第一个棋子
//                tmp = psmv->RookCap[DLoRight] + tx;
//                if(tmp != to256){
//                    checkChess = pos->b256[tmp];
//                    if( (checkChess == RCHE)
//                        || checkChess == RKING 
//                        || (checkChess == RPAWN && (tmp-16) == to256)){            //???????????????{
//                            continue;
//                    }
//                    //有了第一个才可能有第二个
//                    tmp = psmv->CannonCap[DLoRight] + tx;
//                    if(tmp != to256){
//                        if(pos->b256[tmp] == RPAO){
//                            continue;
//                        }
//                    }
//                } 
//                //得到将的棋左面的第一个棋子
//                psmv = RankMove(tx,kToR);
//                tmp  = psmv->RookCap[DUpLeft] + ky4;
//                if(tmp != to256){
//                    checkChess = pos->b256[tmp];
//                    if((checkChess == RCHE)
//                        || (checkChess == RPAWN && tmp+1 == to256)){
//                            continue;
//                    }
//                    //有了第一个才可能有第二个
//                    tmp = psmv->CannonCap[DUpLeft] + ky4;
//                    if(tmp != to256){
//                        if(pos->b256[tmp] == RPAO){
//                            continue;
//                        }
//                    }
//                }
//                //得到将的棋右面的第一个棋子
//                psmv = RankMove(tx,kToR);
//                tmp  = psmv->RookCap[DLoRight] + ky4;
//                if(tmp != to256){
//                    checkChess = pos->b256[tmp];
//                    if((checkChess == RCHE)
//                        || (checkChess == RPAWN && tmp-1 == to256)){
//                            continue;
//                    }
//                    //有了第一个才可能有第二个
//                    tmp = psmv->CannonCap[DLoRight] + ky4;
//                    if(tmp != to256){
//                        if(pos->b256[tmp] == RPAO){
//                            continue;
//                        }
//                    }
//                }
//                //还得看一下有没给马将军了
//                bool isMaCheck = false;
//                for(int nSrc256 = PieceListStart(pos,RMA); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//                    int m = horseLegTab(to256-nSrc256+256);
//                    if(m && !pos->b256[nSrc256 + m]){
//                        //continue;       //给马将军了哇,不能加入走步
//                        isMaCheck = true;
//                        break;
//                    }
//                }
//                if(false == isMaCheck){
//                    (ms++)->move =  MOVE_FromFc_to_tc(ktmp,to256,to14);
//                }
//            }
//        }
//    }
//    //************************************************************************************************************************
//    //RES_EV:  
//    for(int i=0; i<NotNum; i++){
//        int sq = Not256Pos[i];
//        InsertPiece(pos,pos->b256[sq], sq);
//    }
//
//#ifdef  DEBUG_EVASION_MOVE
//    move_stack_t testMS[256];
//    //ASSERT(position_is_ok(pos));
//    //position fen 1rbakabnr/9/1c7/C1p1p1p1p/9/6P2/P1P1c3P/9/9/RNBAKABNR b - - 7 0
//    int check = false;
//    //int evnum  = 0;
//    int allnum = 0;
//    ////1, 解将的步子正不正确 prePS
//    //for(move_stack_t *tms = prePS; tms < ms; tms++){
//    //    //make_move(pos,tms->move);
//    //    //check = isTurnInCheck(pos,pos->side^0x1);
//    //    //unmake_move(pos);
//
//    //    //if(check){
//    //    //    board_display(pos,"ERROR 解将步不对??",stdout);
//    //    //    generate_check_evasions(pos,testMS);
//    //    //}
//    //    evnum++;
//    //}  
//
//    //走步的数目是不是对
//    //ASSERT(position_is_ok(pos));
//
//    move_stack_t *allEnd = generate_moves(pos,testMS);
//
//    for(move_stack_t *st = testMS; st < allEnd; st++){
//        check = false;
//        make_move(pos,st->move);
//        check = isTurnInCheck(pos,pos->side^0x1);
//        unmake_move(pos);
//        if(false == check){         //这是一个解将步
//            allnum++;
//
//            bool isInEva = false;
//            for(move_stack_t *tms = prePS; tms < ms; tms++){
//                if(tms->move == st->move){
//                    isInEva = true;
//                    break;
//                }
//            }
//
//            if(!isInEva){
//                board_display(pos,"isInEva err\n",stdout);
//                generate_check_evasions(pos,prePS);
//            }
//
//            ASSERT(isInEva);
//        }        
//    }
//
//    ASSERT((int)(ms-prePS) == allnum);
//
//#endif
//
//    ASSERT(position_is_ok(pos));
//
//    return ms;
//}
//
