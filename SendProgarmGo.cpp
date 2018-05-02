#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

void SendProgramGo(ChessProgramState *cps){

    dispboard_t* pDis = OBS[cps->table];

    if(cps->playWhat == NEUTRAL){
        MessageBox(pDis->hwndThis,"出错啦!", "引擎不是走子方!!",MB_OK);
        return;
    }
    if(cps->maybeThinking == TRUE){
        MessageBox(pDis->hwndThis,"出错啦!", "引擎还在思考!!",MB_OK);
        return;
    }    

    TruncateGame(pDis);

    if(cps->playWhat != pDis->pos->side){
        LogOut("引擎不是走子方!\n");
        return;
    }

    char buf[MSG_SIZ];

    TimeDisp_t *pt      = &pDis->TimeDisp[cps->playWhat];
    TimeDisp_t *pother  = &pDis->TimeDisp[cps->playWhat ^ 0x1];

    switch(cps->ucci){
        case UCCI_UCCI162:
            //UCCI 得根据时间设定发送控制时间的go
            //SendToProgram("go depth 10\n", cps);        //这儿先用这个代替了

            //首先发送初始局面, 

            SendMoveToProgram(pDis,cps);
            
            if(pt->depth != 0){
                sprintf_s(buf,sizeof(buf), "go depth %d\n",pt->depth);                
            } 
            else if(pt->isBaoGan){
                sprintf_s(buf,sizeof(buf), "go wtime %d winc %d btime %d binc %d\n",
                    pt->msTotal,pt->stepAdd, pother->msTotal,pother->stepAdd);                

            }
            else{       //分段计时
                if(pDis->pos->gply/2 >= pt->c1step){
                    //if(
                }  
                else {      //还在第一时间段内
                    sprintf_s(buf,sizeof(buf),"go movetime %d\n", pt->c1time/(pt->c1step - pDis->pos->gply*2));
                }                 
            }

            SendToProgram(buf,cps);

            StartClocks(pDis);      //开始计时

            cps->maybeThinking = TRUE;

            break;
        case UCCI_CYC105:

            SendMoveToProgram(pDis,cps);
            
            if(pt->depth != 0){
                sprintf_s(buf,sizeof(buf), "go depth %d\n",pt->depth);                
            } 
            else if(pt->isBaoGan){
                sprintf_s(buf,sizeof(buf), "go wtime %d winc %d btime %d binc %d\n",
                    pt->msTotal,pt->stepAdd, pother->msTotal,pother->stepAdd);                

            }
            else{       //分段计时
                if(pDis->pos->gply/2 >= pt->c1step){
                    //if(
                }  
                else {      //还在第一时间段内
                    sprintf_s(buf,sizeof(buf),"go movetime %d\n", pt->c1time/(pt->c1step - pDis->pos->gply*2));
                }                 
            }

            SendToProgram(buf,cps);

            StartClocks(pDis);      //开始计时

            cps->maybeThinking = TRUE;

            break;
        case UCCI_QH:	
            break;
        case UCCI_DIS:	
            SendToProgram("go\n", cps);
            break;
        default:
            break;
    }
    
}
