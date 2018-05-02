#include "stdafx.h"
#include "chess.h"
#include "data.h"
#include "preGen.h"
#include <ctime>
#include <cmath>
#include <sys/stat.h>
#include <io.h>
#include <fcntl.h>
#include <share.h>

//void     strCopybyNumTC(TCHAR* dst, size_t num, char* src) {
//	size_t i;
//	for (i = 0; i < num; i++) {
//		dst[i] = src[i];
//	}
//	dst[i] = 0; //加上结尾
//}


void strCopybyNum(char* dst, size_t num, char* src){
    size_t i;
    for(i = 0;i < num;i++){
        dst[i] = src[i];
    }
    dst[i] = 0; //加上结尾
}


void GetMirrorOnlyB33(position_t *pos, uint8 b33[33]){
	uint8 sq;
	int   chess;

	for(int i = 0; i < 32; i++){
		b33[i] = D8none;
	}

	

	bool useMirror = false;

	//pos->b256

	uint8 *pc = pos->b256 + 0x33;   
	for(int y = 0; y < 10; y++){       

        if(*(pc+8) > *(pc+0)){
            goto MIRROR;
        }
        else if(*(pc+8) < *(pc+0)){
            goto UNMIROR;
        }

        if(*(pc+7) > *(pc+1)){
            goto MIRROR;
        }
        else if(*(pc+7) < *(pc+1)){
            goto UNMIROR;
        }


        if(*(pc+6) > *(pc+2)){
            goto MIRROR;
        }
        else if(*(pc+6) < *(pc+2)){
            goto UNMIROR;
        }


        if(*(pc+5) > *(pc+3)){
            goto MIRROR;
        }
        else if(*(pc+5) < *(pc+3)){
            goto UNMIROR;
        }
        pc += 16;
    }

MIRROR:
    useMirror = true;
UNMIROR:

	for(sq = 0x33; sq<0xcc; sq++){
		if(inBoard(sq) &(IN_RSIDE + IN_BSIDE)){
			//chess = b256[sq];

			if(useMirror){
				chess = pos->b256[Mirror(sq)];
			}
			else{
				chess = pos->b256[sq];
			}

			switch(chess){
				case RKING:                          //红帅,如果是红方走,就b33[16] == RKING
					if(pos->side == WHITE){
						b33[16] = P256ASC[sq];
					}
					else{
						b33[0]  = P256ASC[sq];
					}
					break;
				case BKING:
					if(pos->side == WHITE){
						b33[0] = P256ASC[sq];
					}
					else{
						b33[16]  = P256ASC[sq];
					}
					break;
				case RSHI:
					if(b33[1] == D8none){
						b33[1] =  P256ASC[sq];
					}
					else{
						b33[2] =  P256ASC[sq];
					}
					break;
				case RXIANG:
					if(b33[3] == D8none){
						b33[3] =  P256ASC[sq];
					}
					else{
						b33[4] =  P256ASC[sq];
					}
					break;
				case RMA:
					if(b33[5] == D8none){
						b33[5] =  P256ASC[sq];
					}
					else{
						b33[6] =  P256ASC[sq];
					}
					break;
				case RCHE:
					if(b33[7] == D8none){
						b33[7] =  P256ASC[sq];
					}
					else{
						b33[8] =  P256ASC[sq];
					}
					break;
				case RPAO:
					if(b33[9] == D8none){
						b33[9] =  P256ASC[sq];
					}
					else{
						b33[10] =  P256ASC[sq];
					}
					break;
				case RPAWN:
					if(b33[11] == D8none){
						b33[11] =  P256ASC[sq];
					}
					else if(b33[12] == D8none){
						b33[12] =  P256ASC[sq];
					}
					else if(b33[13] == D8none){
						b33[13] =  P256ASC[sq];
					}
					else if(b33[14] == D8none){
						b33[14] =  P256ASC[sq];
					}
					else{
						b33[15] = P256ASC[sq];
					}
					break;
					//*********************************
				case BSHI:
					if(b33[17] == D8none){
						b33[17] =  P256ASC[sq];
					}
					else{
						b33[18] =  P256ASC[sq];
					}
					break;
				case BXIANG:
					if(b33[19] == D8none){
						b33[19] =  P256ASC[sq];
					}
					else{
						b33[20] =  P256ASC[sq];
					}
					break;
				case BMA:
					if(b33[21] == D8none){
						b33[21] =  P256ASC[sq];
					}
					else{
						b33[22] =  P256ASC[sq];
					}
					break;
				case BCHE:
					if(b33[23] == D8none){
						b33[23] =  P256ASC[sq];
					}
					else{
						b33[24] =  P256ASC[sq];
					}
					break;
				case BPAO:
					if(b33[25] == D8none){
						b33[25] =  P256ASC[sq];
					}
					else{
						b33[26] =  P256ASC[sq];
					}
					break;
				case BPAWN:
					if(b33[27] == D8none){
						b33[27] =  P256ASC[sq];
					}
					else if(b33[28] == D8none){
						b33[28] =  P256ASC[sq];
					}
					else if(b33[29] == D8none){
						b33[29] =  P256ASC[sq];
					}
					else if(b33[30] == D8none){
						b33[30] =  P256ASC[sq];
					}
					else{
						b33[31] = P256ASC[sq];
					}
					break;
				default:
					break;
			}
		}
	}

	
	b33[32] = 0;        //加上结尾

}


void OpenAllCatFileOnebyOne(BOOL* isFindOne, TCHAR *root,
	TCHAR *ftype, TCHAR* NotOpen, TCHAR* dir, TCHAR* filename){
 
    if(*isFindOne == TRUE){
        return;
    }

    if(false == SetCurrentDirectory(root)){
        //fprintf(stdout,"cmd_err: can_not_find cat: %s\n",root);
		LogOut(_T("不能进入以下目录\n"));
		LogOut(root);
        return ;
    }

    HANDLE hFind = NULL;

    WIN32_FIND_DATA wfdt;
    hFind = FindFirstFile(ftype,&wfdt);
    
    if(hFind != INVALID_HANDLE_VALUE){
        //do{
            //if(CMD_stop == true){
            //    return false;
            //}
        
            //int k = strlen(NotOpen);

            //if(strncasecmp(wfdt.cFileName, NotOpen, strlen(NotOpen)) == 0){
            //    continue;   //当前的文件已学习过了
            //}
            swprintf_s(filename,MAX_PATH,_T("%s"),wfdt.cFileName);
			swprintf_s(dir, MAX_PATH, root);
            *isFindOne = true;


            FindClose(hFind); 
            return;            //得到一个文件
            
        //}while(TRUE);/*while(FindNextFile(hFind,&wfdt));*/
    }
    hFind = FindFirstFile(_T("*.*"),&wfdt);     //查找其它目录有没有要打开的文件
    if(hFind == INVALID_HANDLE_VALUE){
        return;
    }

    while(false != FindNextFile(hFind,&wfdt)){
        if((wfdt.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY){ // 这是一个子目录哇
			if(wfdt.cFileName[0] != '.'){ //这不是上级目录
                //再判断一下不是临时保存的目录
                if(strncasecmp((char*)wfdt.cFileName, (char*)NotOpen, strlen((char*)NotOpen)) == 0){
                    continue;   //如是,则跳过这个目录
                }
               
				TCHAR CurPath[MAX_PATH];
                swprintf_s(CurPath,MAX_PATH,_T("%s%s\\"),root,wfdt.cFileName);
                OpenAllCatFileOnebyOne(isFindOne, CurPath,ftype,NotOpen,dir,filename);				
			}
		}
    }
    FindClose(hFind);
    return ;
}





void 
p90ToAsc(void){
    for(int i=0; i<sizeof(ASCP90); i++){
        P90ASC[ASCP90[i]] = i;					//90得到了相应的ASCII
    }

	for(int i=0; i<90; i++){					//90到256
		P256ASC[A90toA256[i]] = P90ASC[i];
	}
}

int piece_to_char(int piece) {
    static const char PieceString[14+2] = "0KABNRCPkabnrcp";

   //ASSERT(piece_is_ok(piece));

   return PieceString[piece];
}

int piece_from_char(int c) {

   //const char *ptr;

   //ptr = strchr(PieceString,c);
   //if (ptr == NULL) return PieceNone256;

   //return piece_from_12(ptr-PieceString);
 
    switch(c){
        case 'K':
            return RKING;
        case 'A':
            return RSHI;
        case 'B':
        case 'E':
            return RXIANG;
        case 'N':
        case 'H':
            return RMA;
        case 'R':
            return RCHE;
        case 'C':
            return RPAO;
        case 'P':
            return RPAWN;

        case 'k':
            return BKING;
        case 'a':
            return BSHI;
        case 'b':
        case 'e':
            return BXIANG;
        case 'n':
        case 'h':
            return BMA;
        case 'r':
            return BCHE;
        case 'c':
            return BPAO;
        case 'p':
            return BPAWN;
        default:
            return -1;
    }
}



//void		//将字符串显示到状态栏中
//DispStatS(const char* string){
//	//SendMessage(hwndStatus,SB_SETTEXT,2,(LPARAM)"电脑搜索结果........,哦,你要输了哦");
//	SendMessage(hStatusBar,SB_SETTEXT,0,(LPARAM)string);
//}
//void 
//DispStatRtime(const char* string){
//	//SendMessage(hStatusBar,SB_SETTEXT,0,(LPARAM)string);
//}
//void
//DispStatBtime(const char* string){
//	//SendMessage(hStatusBar,SB_SETTEXT,1,(LPARAM)string);
//}


//int  Get90FromPoint(POINT* p){
//	if((*p).x < DisOffX || (*p).x > DisOffX + DisW
//		|| (*p).y <DisOffY +20 || (*p).y > DisOffY + DisH){	
//			return 90;
//		}    
//		return ((*p).x - DisOffX)/40 +((*p).y - DisOffY - 20 )/40 * 9 ;	
//}
//测试一下当前的所有可走步子，并显示到log窗口中去
void 
DispAllCanMove(void){	
	//DispLogClear();
	//gen_legal_moves(&DispMoveList,&DispBoard);
	//char MoveStr[20];
	//for(int i=0; i<DispMoveList.size; i++){
	//	StringCbPrintf(MoveStr,20,"%3d > ",i+1);		
	//	GetMoveName(&DispBoard,DispMoveList.move[i],&MoveStr[6],StepNameTypeA);
	//	DispLog(MoveStr);
	//}
}
bool //如果是红的走的局面，则返回true,else返回false
D8ToB90(int *D8, sq_t *b90){
    return false;
	
	//memset(b90,EMPTY,90*sizeof(sq_t));

	////case WhiteKing:
	////			*((char*)D8+8) = i;
	////			break;

	//if(*((char*)D8 +0) < 66){			//这是黑走的局面
	//	char p = *((char*)D8 +31);
	//	if(p < 90){
	//		*(b90+p) = RCHE;
	//	}
	//	p = *((char*)D8 +30);
	//	if(p < 90){
	//		*(b90+p) = RCHE;
	//	}
	//	p = *((char*)D8 +29);
	//	if(p < 90){
	//		*(b90+p) = RMA;
	//	}
	//	p = *((char*)D8 +28);
	//	if(p < 90){
	//		*(b90+p) = RMA;
	//	}
	//	p = *((char*)D8 +27);
	//	if(p < 90){
	//		*(b90+p) = RXIANG;
	//	}
	//	p = *((char*)D8 +26);
	//	if(p < 90){
	//		*(b90+p) = WhiteXiang;
	//	}
	//	p = *((char*)D8 +25);
	//	if(p < 90){
	//		*(b90+p) = WhiteShi;
	//	}
	//	p = *((char*)D8 +24);
	//	if(p < 90){
	//		*(b90+p) = WhiteShi;
	//	}
	//	p = *((char*)D8 +23);
	//	if(p < 90){
	//		*(b90+p) = WhiteKing;
	//	}
	//	p = *((char*)D8 +22);
	//	if(p < 90){
	//		*(b90+p) = WhitePao;
	//	}
	//	p = *((char*)D8 +21);
	//	if(p < 90){
	//		*(b90+p) = WhitePao;
	//	}
	//	p = *((char*)D8 +20);
	//	if(p < 90){
	//		*(b90+p) = WhitePawn;
	//	}
	//	p = *((char*)D8 +19);
	//	if(p < 90){
	//		*(b90+p) = WhitePawn;
	//	}
	//	p = *((char*)D8 +18);
	//	if(p < 90){
	//		*(b90+p) = WhitePawn;
	//	}
	//	p = *((char*)D8 +17);
	//	if(p < 90){
	//		*(b90+p) = WhitePawn;
	//	}
	//	p = *((char*)D8 +16);
	//	if(p < 90){
	//		*(b90+p) = WhitePawn;
	//	}
	//	//*************************************
	//	p = *((char*)D8 +15);
	//	if(p < 90){
	//		*(b90+p) = BlackChe;
	//	}
	//	p = *((char*)D8 +14);
	//	if(p < 90){
	//		*(b90+p) = BlackChe;
	//	}
	//	p = *((char*)D8 +13);
	//	if(p < 90){
	//		*(b90+p) = BlackMa;
	//	}
	//	p = *((char*)D8 +12);
	//	if(p < 90){
	//		*(b90+p) = BlackMa;
	//	}
	//	p = *((char*)D8 +11);
	//	if(p < 90){
	//		*(b90+p) = BlackXiang;
	//	}
	//	p = *((char*)D8 +10);
	//	if(p < 90){
	//		*(b90+p) = BlackXiang;
	//	}
	//	p = *((char*)D8 +9);
	//	if(p < 90){
	//		*(b90+p) = BlackShi;
	//	}
	//	p = *((char*)D8 +8);
	//	if(p < 90){
	//		*(b90+p) = BlackShi;
	//	}
	//	p = *((char*)D8 +7);
	//	if(p < 90){
	//		*(b90+p) = BlackKing;
	//	}
	//	p = *((char*)D8 +6);
	//	if(p < 90){
	//		*(b90+p) = BlackPao;
	//	}
	//	p = *((char*)D8 +5);
	//	if(p < 90){
	//		*(b90+p) = BlackPao;
	//	}
	//	p = *((char*)D8 +4);
	//	if(p < 90){
	//		*(b90+p) = BlackPawn;
	//	}
	//	p = *((char*)D8 +3);
	//	if(p < 90){
	//		*(b90+p) = BlackPawn;
	//	}
	//	p = *((char*)D8 +2);
	//	if(p < 90){
	//		*(b90+p) = BlackPawn;
	//	}
	//	p = *((char*)D8 +1);
	//	if(p < 90){
	//		*(b90+p) = BlackPawn;
	//	}
	//	p = *((char*)D8 +0);
	//	if(p < 90){
	//		*(b90+p) = BlackPawn;
	//	}
	//	return false;
	//}
	//else{								//这是红走的局面
	//	char p = *((char*)D8 +0);
	//	if(p < 90){
	//		*(b90+p) = WhiteChe;
	//	}
	//	p = *((char*)D8 +1);
	//	if(p < 90){
	//		*(b90+p) = WhiteChe;
	//	}
	//	p = *((char*)D8 +2);
	//	if(p < 90){
	//		*(b90+p) = WhiteMa;
	//	}
	//	p = *((char*)D8 +3);
	//	if(p < 90){
	//		*(b90+p) = WhiteMa;
	//	}
	//	p = *((char*)D8 +4);
	//	if(p < 90){
	//		*(b90+p) = WhiteXiang;
	//	}
	//	p = *((char*)D8 +5);
	//	if(p < 90){
	//		*(b90+p) = WhiteXiang;
	//	}
	//	p = *((char*)D8 +6);
	//	if(p < 90){
	//		*(b90+p) = WhiteShi;
	//	}
	//	p = *((char*)D8 +7);
	//	if(p < 90){
	//		*(b90+p) = WhiteShi;
	//	}
	//	p = *((char*)D8 +8);
	//	if(p < 90){
	//		*(b90+p) = WhiteKing;
	//	}
	//	p = *((char*)D8 +9);
	//	if(p < 90){
	//		*(b90+p) = WhitePao;
	//	}
	//	p = *((char*)D8 +10);
	//	if(p < 90){
	//		*(b90+p) = WhitePao;
	//	}
	//	p = *((char*)D8 +11);
	//	if(p < 90){
	//		*(b90+p) = WhitePawn;
	//	}
	//	p = *((char*)D8 +12);
	//	if(p < 90){
	//		*(b90+p) = WhitePawn;
	//	}
	//	p = *((char*)D8 +13);
	//	if(p < 90){
	//		*(b90+p) = WhitePawn;
	//	}
	//	p = *((char*)D8 +14);
	//	if(p < 90){
	//		*(b90+p) = WhitePawn;
	//	}
	//	p = *((char*)D8 +15);
	//	if(p < 90){
	//		*(b90+p) = WhitePawn;
	//	}
	//	//*************************************
	//	p = *((char*)D8 +16);
	//	if(p < 90){
	//		*(b90+p) = BlackChe;
	//	}
	//	p = *((char*)D8 +17);
	//	if(p < 90){
	//		*(b90+p) = BlackChe;
	//	}
	//	p = *((char*)D8 +18);
	//	if(p < 90){
	//		*(b90+p) = BlackMa;
	//	}
	//	p = *((char*)D8 +19);
	//	if(p < 90){
	//		*(b90+p) = BlackMa;
	//	}
	//	p = *((char*)D8 +20);
	//	if(p < 90){
	//		*(b90+p) = BlackXiang;
	//	}
	//	p = *((char*)D8 +21);
	//	if(p < 90){
	//		*(b90+p) = BlackXiang;
	//	}
	//	p = *((char*)D8 +22);
	//	if(p < 90){
	//		*(b90+p) = BlackShi;
	//	}
	//	p = *((char*)D8 +23);
	//	if(p < 90){
	//		*(b90+p) = BlackShi;
	//	}
	//	p = *((char*)D8 +24);
	//	if(p < 90){
	//		*(b90+p) = BlackKing;
	//	}
	//	p = *((char*)D8 +25);
	//	if(p < 90){
	//		*(b90+p) = BlackPao;
	//	}
	//	p = *((char*)D8 +26);
	//	if(p < 90){
	//		*(b90+p) = BlackPao;
	//	}
	//	p = *((char*)D8 +27);
	//	if(p < 90){
	//		*(b90+p) = BlackPawn;
	//	}
	//	p = *((char*)D8 +28);
	//	if(p < 90){
	//		*(b90+p) = BlackPawn;
	//	}
	//	p = *((char*)D8 +29);
	//	if(p < 90){
	//		*(b90+p) = BlackPawn;
	//	}
	//	p = *((char*)D8 +30);
	//	if(p < 90){
	//		*(b90+p) = BlackPawn;
	//	}
	//	p = *((char*)D8 +31);
	//	if(p < 90){
	//		*(b90+p) = BlackPawn;
	//	}

	//	return true;
	//}
	//*(D8+0) -= 0x21212121;
	//*(D8+1) -= 0x21212121;
	//*(D8+2) -= 0x21212121;
	//*(D8+3) -= 0x21212121;
	//*(D8+4) -= 0x21212121;
	//*(D8+5) -= 0x21212121;
	//*(D8+6) -= 0x21212121;
	//*(D8+7) -= 0x21212121;

	//p = *((char*)D8 +0) & 0x7f;

}

void 
B90ToD8(sq_t *b90, int *D8,bool isWhiteGo){
	////#define     D8add           33  0x21
	////#define     D8none          0x7b//33+90
	////#define     D8int           0x7b7b7b7b;
	//*(D8+0) = 0x5a5a5a5a;
	//*(D8+1) = 0x5a5a5a5a;
	//*(D8+2) = 0x5a5a5a5a;
	//*(D8+3) = 0x5a5a5a5a;
	//*(D8+4) = 0x5a5a5a5a;
	//*(D8+5) = 0x5a5a5a5a;
	//*(D8+6) = 0x5a5a5a5a;
	//*(D8+7) = 0x5a5a5a5a;
	//if(isWhiteGo){					//现在是白的走
	//	for(char i=0; i<90; i++){
	//		sq_t chess = *(b90+i);
	//		switch(chess){
	//			case WhiteChe:
	//				if (*((char*)D8+0) == D8none){
	//					*((char*)D8+0) = i;
	//				}else{
	//					*((char*)D8+1) = i;
	//				}
	//				break;
	//			case WhiteMa:
	//				if (*((char*)D8+2) == D8none){
	//					*((char*)D8+2) = i;
	//				}else{
	//					*((char*)D8+3) = i;
	//				}
	//				break;
	//			case WhiteXiang:
	//				if (*((char*)D8+4) == D8none){
	//					*((char*)D8+4) = i;
	//				}else{
	//					*((char*)D8+5) = i;
	//				}
	//				break;
	//			case WhiteShi:
	//				if (*((char*)D8+6) == D8none){
	//					*((char*)D8+6) = i;
	//				}else{
	//					*((char*)D8+7) = i;
	//				}
	//				break;
	//			case WhiteKing:
	//				*((char*)D8+8) = i;
	//				break;
	//			case WhitePao:
	//				if (*((char*)D8+9) == D8none){
	//					*((char*)D8+9) = i;
	//				}else{
	//					*((char*)D8+10) = i;
	//				}
	//				break;
	//			case WhitePawn:
	//				if (*((char*)D8+11) == D8none){
	//					*((char*)D8+11) = i;
	//				}
	//				else if (*((char*)D8+12) == D8none){
	//					*((char*)D8+12) = i;
	//				}
	//				else if (*((char*)D8+13) == D8none){
	//					*((char*)D8+13) = i;
	//				}
	//				else if (*((char*)D8+14) == D8none){
	//					*((char*)D8+14) = i;
	//				}
	//				else {
	//					*((char*)D8+15) = i;
	//				}
	//				break;
	//				//*********************************************
	//			case BlackChe:
	//				if (*((char*)D8+16) == D8none){
	//					*((char*)D8+16) = i;
	//				}else{
	//					*((char*)D8+17) = i;
	//				}
	//				break;
	//			case BlackMa:
	//				if (*((char*)D8+18) == D8none){
	//					*((char*)D8+18) = i;
	//				}else{
	//					*((char*)D8+19) = i;
	//				}
	//				break;
	//			case BlackXiang:
	//				if (*((char*)D8+20) == D8none){
	//					*((char*)D8+20) = i;
	//				}else{
	//					*((char*)D8+21) = i;
	//				}
	//				break;
	//			case BlackShi:
	//				if (*((char*)D8+22) == D8none){
	//					*((char*)D8+22) = i;
	//				}else{
	//					*((char*)D8+23) = i;
	//				}
	//				break;
	//			case BlackKing:
	//				*((char*)D8+24) = i;
	//				break;
	//			case BlackPao:
	//				if (*((char*)D8+25) == D8none){
	//					*((char*)D8+25) = i;
	//				}else{
	//					*((char*)D8+26) = i;
	//				}
	//				break;
	//			case BlackPawn:
	//				if (*((char*)D8+27) == D8none){
	//					*((char*)D8+27) = i;
	//				}
	//				else if (*((char*)D8+28) == D8none){
	//					*((char*)D8+28) = i;
	//				}
	//				else if (*((char*)D8+29) == D8none){
	//					*((char*)D8+29) = i;
	//				}
	//				else if (*((char*)D8+30) == D8none){
	//					*((char*)D8+30) = i;
	//				}
	//				else {
	//					*((char*)D8+31) = i;
	//				}
	//				break;
	//			default:
	//				break;
	//		}
	//	}
	//}
	//else{							//现在是黑的走，则将顺序反过来一下
	//	for(char i=0; i<90; i++){
	//		sq_t chess = *(b90+i);
	//		switch(chess){
	//		case WhiteChe:
	//			if (*((char*)D8+31) == D8none){
	//				*((char*)D8+31) = i;
	//			}else{
	//				*((char*)D8+30) = i;
	//			}
	//			break;
	//		case WhiteMa:
	//			if (*((char*)D8+29) == D8none){
	//				*((char*)D8+29) = i;
	//			}else{
	//				*((char*)D8+28) = i;
	//			}
	//			break;
	//		case WhiteXiang:
	//			if (*((char*)D8+27) == D8none){
	//				*((char*)D8+27) = i;
	//			}else{
	//				*((char*)D8+26) = i;
	//			}
	//			break;
	//		case WhiteShi:
	//			if (*((char*)D8+25) == D8none){
	//				*((char*)D8+25) = i;
	//			}else{
	//				*((char*)D8+24) = i;
	//			}
	//			break;
	//		case WhiteKing:
	//			*((char*)D8+23) = i;
	//			break;
	//		case WhitePao:
	//			if (*((char*)D8+22) == D8none){
	//				*((char*)D8+22) = i;
	//			}else{
	//				*((char*)D8+21) = i;
	//			}
	//			break;
	//		case WhitePawn:
	//			if (*((char*)D8+20) == D8none){
	//				*((char*)D8+20) = i;
	//			}
	//			else if (*((char*)D8+19) == D8none){
	//				*((char*)D8+19) = i;
	//			}
	//			else if (*((char*)D8+18) == D8none){
	//				*((char*)D8+18) = i;
	//			}
	//			else if (*((char*)D8+17) == D8none){
	//				*((char*)D8+17) = i;
	//			}
	//			else {
	//				*((char*)D8+16) = i;
	//			}
	//			break;
	//			//*********************************************
	//		case BlackChe:
	//			if (*((char*)D8+15) == D8none){
	//				*((char*)D8+15) = i;
	//			}else{
	//				*((char*)D8+14) = i;
	//			}
	//			break;
	//		case BlackMa:
	//			if (*((char*)D8+13) == D8none){
	//				*((char*)D8+13) = i;
	//			}else{
	//				*((char*)D8+12) = i;
	//			}
	//			break;
	//		case BlackXiang:
	//			if (*((char*)D8+11) == D8none){
	//				*((char*)D8+11) = i;
	//			}else{
	//				*((char*)D8+10) = i;
	//			}
	//			break;
	//		case BlackShi:
	//			if (*((char*)D8+9) == D8none){
	//				*((char*)D8+9) = i;
	//			}else{
	//				*((char*)D8+8) = i;
	//			}
	//			break;
	//		case BlackKing:
	//			*((char*)D8+7) = i;
	//			break;
	//		case BlackPao:
	//			if (*((char*)D8+6) == D8none){
	//				*((char*)D8+6) = i;
	//			}else{
	//				*((char*)D8+5) = i;
	//			}
	//			break;
	//		case BlackPawn:
	//			if (*((char*)D8+4) == D8none){
	//				*((char*)D8+4) = i;
	//			}
	//			else if (*((char*)D8+3) == D8none){
	//				*((char*)D8+3) = i;
	//			}
	//			else if (*((char*)D8+2) == D8none){
	//				*((char*)D8+2) = i;
	//			}
	//			else if (*((char*)D8+1) == D8none){
	//				*((char*)D8+1) = i;
	//			}
	//			else {
	//				*((char*)D8+0) = i;
	//			}
	//			break;
	//		default:
	//			break;
	//		}
	//	}
	//}
	//*(D8+0) += 0x21212121;
	//*(D8+1) += 0x21212121;
	//*(D8+2) += 0x21212121;
	//*(D8+3) += 0x21212121;
	//*(D8+4) += 0x21212121;
	//*(D8+5) += 0x21212121;
	//*(D8+6) += 0x21212121;
	//*(D8+7) += 0x21212121;
	//if(whogo != WhiteGo){   //是黑棋走
	//	*D8 |= 0x80000000;  //黑棋走的标志
	//}
}
void RenewBoard(dispboard_t* pDis){
	RECT re = {0,0,360,484};
    InvalidateRect(pDis->hwndThis,&re,false);
}
bool //检查一局棋局是否合法
IsGGqjNormal(PGN *pgg){
	//void gen_legal_moves(list_t * list, board_t * board) {
	//static board_t board;
	//static list_t  list;
	//static undo_t  undo;

	//if(pgg->qipulen < 32){
	//	DispLog("佳佳棋局的棋谱太短了!!");
	//	return false;
	//}
	//
	//bool whoFirst;
	//Board90 board;

 //   whoFirst = D8ToB90((int*)pgg->qipu,board);

	//sq_t *ps = pgg->qipu + 32;

	//for(int i=0; i<(pgg->qipulen-32)/2; i +=2 ){	//检验每步,看是不是合法
	//	//sq_t from	= *(ps+i);
	//	//sq_t   to	= *(ps+i+1);
	//	//mv_t  move	= MOVE_MAKE(from,to);
	//	//yq_gen_legal_moves(&list,&board);
	//	//bool ishave = false;
	//	//for(int s=0; s<list.size; s++){
	//	//	if(list.move[s] == move){
	//	//		ishave = true;
	//	//		//走上一步
	//	//		//move_do(board_t * board, int move, undo_t * undo)
	//	//		yq_move_do(&board,move,&undo);
	//	//		break;
	//	//	}
	//	//}
	//	//if(false == ishave){
	//	//	DispLog("佳佳棋局的棋步有错哇!!");
	//	//	return false;
	//	//}
 //       //DIS.currentMove%2 == 0 ? F_WHITE_ON_MOVE : 0
	//	sq_t from	= *(ps+i);
	//	sq_t   to	= *(ps+i+1);
	//	if(IsMoveValid(board,(i/2)%2 == 0 ? F_WHITE_ON_MOVE : 0,
	//		S90toF(from),S90toR(from),S90toF(to),S90toR(to)) != NormalMove){
	//		DispLog("佳佳棋局的棋步有错哇!!");
	//		return false;
	//	}
	//	//走上一步
	//	board[to]	= board[from];
	//	board[from] = NOCHESS; 
	//}	
	//return true;
	//return false;
    return false;
}
//void //发送佳佳棋局中的信息到对话框中
//SendGGqjToDlg(PGN *pgg){
//	//char buf[MSG_SIZ];
//	//
//	//SetDlgItemInt(TAB.dlgTab[DSTEP],IDC_STEP_ID,pgg->qjid,true);
//
// //   SendDlgItemMessage(TAB.dlgTab[DSTEP],IDC_STEP_RNAME,WM_SETTEXT,0,(LPARAM)pgg->Rname);
//	//SetDlgItemInt(TAB.dlgTab[DSTEP],IDC_STEP_RELO,pgg->Relo,true);
//
//	//SendDlgItemMessage(TAB.dlgTab[DSTEP],IDC_STEP_BNAME,WM_SETTEXT,0,(LPARAM)pgg->Bname);
//	//SetDlgItemInt(TAB.dlgTab[DSTEP],IDC_STEP_BELO,pgg->Belo,true);
//	//
//	//SendDlgItemMessage(TAB.dlgTab[DSTEP],IDC_STEP_RESULT,WM_SETTEXT,0,(LPARAM)pgg->resultDetails);
//
//	//SendDlgItemMessage(TAB.dlgTab[DSTEP],IDC_STEP_ADDR,WM_SETTEXT,0,(LPARAM)pgg->from);
//	//SendDlgItemMessage(TAB.dlgTab[DSTEP],IDC_STEP_NOTE,WM_SETTEXT,0,(LPARAM)pgg->note);
//
//
//	//switch(pgg->score){
//	//	case SCORE_NO:
//	//		SendDlgItemMessage(TAB.dlgTab[DSTEP],IDC_STEP_SCORE,CB_SETCURSEL,0,0);	
//	//		break;
//	//	case SCORE_R_WIN:			//红胜
//	//		SendDlgItemMessage(TAB.dlgTab[DSTEP],IDC_STEP_SCORE,CB_SETCURSEL,1,0);
//	//		break;
//	//	case SCORE_R_GOOD:			//红优
//	//		SendDlgItemMessage(TAB.dlgTab[DSTEP],IDC_STEP_SCORE,CB_SETCURSEL,2,0);
//	//		break;
//	//	case SCORE_R_LITTLE:		//红略优
//	//		SendDlgItemMessage(TAB.dlgTab[DSTEP],IDC_STEP_SCORE,CB_SETCURSEL,3,0);
//	//		break;
//	//	case SCORE_BALANCE:			//双方均势
//	//		SendDlgItemMessage(TAB.dlgTab[DSTEP],IDC_STEP_SCORE,CB_SETCURSEL,4,0);
//	//		break;
//	//	case SCORE_B_LITTLE:		//黑略优
//	//		SendDlgItemMessage(TAB.dlgTab[DSTEP],IDC_STEP_SCORE,CB_SETCURSEL,5,0);
//	//		break;
//	//	case SCORE_B_GOOD:			//黑优
//	//		SendDlgItemMessage(TAB.dlgTab[DSTEP],IDC_STEP_SCORE,CB_SETCURSEL,6,0);
//	//	case SCORE_B_WIN:			//黑胜
//	//		SendDlgItemMessage(TAB.dlgTab[DSTEP],IDC_STEP_SCORE,CB_SETCURSEL,7,0);
//	//		break;
//	//	default:					//ERROR	
//	//		_itoa_s(pgg->qjid,buf,MSG_SIZ,10);
//	//		MessageBox(hwndMain,buf,"佳佳棋局得分有错：ID",MB_OK);
//	//		SendDlgItemMessage(TAB.dlgTab[DSTEP],IDC_STEP_SCORE,CB_SETCURSEL,0,0);	
//	//		break;
//	//	//case 
//	//}	
//}
//bool  //从棋局话框中得到佳佳棋局的信息
//GetGGqjFromDlg(PGN *pgg){
//	////结局评论 SendMessage(TAB.dlgStep_Score,CB_SETCURSEL,0,0);   //选中第一项
//	//DIS.GGQJ.score = ST_SCORE[SendDlgItemMessage(TAB.dlgTab[DSTEP],IDC_STEP_SCORE,CB_GETCURSEL,0,0)];
//	//if(DIS.GGQJ.score == SCORE_NO){
//	//	MessageBox(hwndMain,"请选择一个评价哇！","嗨",MB_OK);
//	//	return false;
//	//}
//	////得到结局名称	
//	//GetDlgItemText(TAB.dlgTab[DSTEP],IDC_STEP_RESULT,pgg->resultDetails,sizeof(pgg->resultDetails));
//	////得到地点
//	//GetDlgItemText(TAB.dlgTab[DSTEP],IDC_STEP_ADDR, pgg->from, sizeof(pgg->from));
//	////得到棋局信息
//	//GetDlgItemText(TAB.dlgTab[DSTEP],IDC_STEP_NOTE, pgg->note, sizeof(pgg->note));
//	////得到棋手信息
//	//BOOL isGet;
//	//int  tnum;
//
//	//GetDlgItemText(TAB.dlgTab[DSTEP],IDC_STEP_RNAME,pgg->Rname,sizeof(pgg->Rname));
//	//tnum = GetDlgItemInt (TAB.dlgTab[DSTEP],IDC_STEP_RELO, &isGet, true);
//	//if(isGet){
//	//	pgg->Relo = tnum;
//	//}
//	//else{
//	//	return false;
//	//}
//
//	//GetDlgItemText(TAB.dlgTab[DSTEP],IDC_STEP_BNAME,pgg->Bname,sizeof(pgg->Bname));
//	//tnum = GetDlgItemInt (TAB.dlgTab[DSTEP],IDC_STEP_BELO, &isGet, true);
//	//if(isGet){
//	//	pgg->Belo = tnum;
//	//}
//	//else{
//	//	return false;
//	//}
// //   //得到赛事 IDC_STEP_LENCI
//	//GetDlgItemText(TAB.dlgTab[DSTEP],IDC_STEP_EVENT, pgg->event, sizeof(pgg->event));
//	////得到轮次 IDC_STEP_EVENT
//	//GetDlgItemText(TAB.dlgTab[DSTEP],IDC_STEP_LENCI, pgg->round, sizeof(pgg->round));
// //   //是否自动读取下入一局
//	//if(SendDlgItemMessage(TAB.dlgTab[DSTEP],IDC_AUTO_READ_NEXT,BM_GETSTATE,0,0)
//	//	== BST_CHECKED)
//	//{
//	//	pgg->isAutoNext = true;
//	//}
//	//else{
//	//	pgg->isAutoNext = false;
//	//}
//	//return true;
//	//SendMessage(TAB.dlgStep_ID,WM_GETTEXT,0,(LPARAM)itoa(pgg->qjid,buf,10));
//
//    return true;
//}

BOOL 
string_start_with(const char s1[], const char s2[]) {

   ASSERT(s1!=NULL);
   ASSERT(s2!=NULL);

   return strstr(s1, s2) == s1;
}
// end of util.cpp
void   //找到当前B90的唯一D8
FindMirrorOnly(position_t* pos, int *D8, bool isWhiteGo){
//	sq_t Mir90[90];
//	//sq_t bend = b90+90;
//	sq_t *ip = b90;
//	for(int y=0; y<10; y++){		//对于每一个file
//		/*if((*(ip+8) > *(ip+0))||(*(ip+7) > *(ip+1))||(*(ip+6) > *(ip+2))||(*(ip+5) > *(ip+3))){
//			
//		}*/
//		if(*(ip+8) > *(ip)){
//			goto MIRROR;
//		}
//		else if(*(ip+8) < *(ip)){
//			goto UNMIROR;
//		}
//		if(*(ip+7) > *(ip+1)){
//			goto MIRROR;
//		}
//		else if(*(ip+7) < *(ip+1)){
//			goto UNMIROR;
//		}
//		if(*(ip+6) > *(ip+2)){
//			goto MIRROR;
//		}
//		else if(*(ip+6) < *(ip+2)){
//			goto UNMIROR;
//		}
//		if(*(ip+5) > *(ip+3)){
//			goto MIRROR;
//		}
//		else if(*(ip+5) < *(ip+3)){
//			goto UNMIROR;
//		}
//		ip += 9;
//	}
//MIRROR:
//	//第一行
//	Mir90[0]	= *(b90+8);
//	Mir90[1]	= *(b90+7);
//	Mir90[2]	= *(b90+6);
//	Mir90[3]	= *(b90+5);
//	Mir90[4]	= *(b90+4);
//	Mir90[5]	= *(b90+3);
//	Mir90[6]	= *(b90+2);
//	Mir90[7]	= *(b90+1);
//	Mir90[8]	= *(b90+0);
//	//第二行
//	Mir90[9]	= *(b90+17);
//	Mir90[10]	= *(b90+16);
//	Mir90[11]	= *(b90+15);
//	Mir90[12]	= *(b90+14);
//	Mir90[13]	= *(b90+13);
//	Mir90[14]	= *(b90+12);
//	Mir90[15]	= *(b90+11);
//	Mir90[16]	= *(b90+10);
//	Mir90[17]	= *(b90+9);
//	//第三行
//	Mir90[18]	= *(b90+26);
//	Mir90[19]	= *(b90+25);
//	Mir90[20]	= *(b90+24);
//	Mir90[21]	= *(b90+23);
//	Mir90[22]	= *(b90+22);
//	Mir90[23]	= *(b90+21);
//	Mir90[24]	= *(b90+20);
//	Mir90[25]	= *(b90+19);
//	Mir90[26]	= *(b90+18);
//	//第四行
//	Mir90[27]	= *(b90+35);
//	Mir90[28]	= *(b90+34);
//	Mir90[29]	= *(b90+33);
//	Mir90[30]	= *(b90+32);
//	Mir90[31]	= *(b90+31);
//	Mir90[32]	= *(b90+30);
//	Mir90[33]	= *(b90+29);
//	Mir90[34]	= *(b90+28);
//	Mir90[35]	= *(b90+27);
//	//第五行
//	Mir90[36]	= *(b90+44);
//	Mir90[37]	= *(b90+43);
//	Mir90[38]	= *(b90+42);
//	Mir90[39]	= *(b90+41);
//	Mir90[40]	= *(b90+40);
//	Mir90[41]	= *(b90+39);
//	Mir90[42]	= *(b90+38);
//	Mir90[43]	= *(b90+37);
//	Mir90[44]	= *(b90+36);
//	//第六行
//	Mir90[45]	= *(b90+53);
//	Mir90[46]	= *(b90+52);
//	Mir90[47]	= *(b90+51);
//	Mir90[48]	= *(b90+50);
//	Mir90[49]	= *(b90+49);
//	Mir90[50]	= *(b90+48);
//	Mir90[51]	= *(b90+47);
//	Mir90[52]	= *(b90+46);
//	Mir90[53]	= *(b90+45);
//	//第七行
//	Mir90[54]	= *(b90+62);
//	Mir90[55]	= *(b90+61);
//	Mir90[56]	= *(b90+60);
//	Mir90[57]	= *(b90+59);
//	Mir90[58]	= *(b90+58);
//	Mir90[59]	= *(b90+57);
//	Mir90[60]	= *(b90+56);
//	Mir90[61]	= *(b90+55);
//	Mir90[62]	= *(b90+54);
//	//第八行
//	Mir90[63]	= *(b90+71);
//	Mir90[64]	= *(b90+70);
//	Mir90[65]	= *(b90+69);
//	Mir90[66]	= *(b90+68);
//	Mir90[67]	= *(b90+67);
//	Mir90[68]	= *(b90+66);
//	Mir90[69]	= *(b90+65);
//	Mir90[70]	= *(b90+64);
//	Mir90[71]	= *(b90+63);
//	//第九行
//	Mir90[72]	= *(b90+80);
//	Mir90[73]	= *(b90+79);
//	Mir90[74]	= *(b90+78);
//	Mir90[75]	= *(b90+77);
//	Mir90[76]	= *(b90+76);
//	Mir90[77]	= *(b90+75);
//	Mir90[78]	= *(b90+74);
//	Mir90[79]	= *(b90+73);
//	Mir90[80]	= *(b90+72);
//	//第十行
//	Mir90[81]	= *(b90+89);
//	Mir90[82]	= *(b90+88);
//	Mir90[83]	= *(b90+87);
//	Mir90[84]	= *(b90+86);
//	Mir90[85]	= *(b90+85);
//	Mir90[86]	= *(b90+84);
//	Mir90[87]	= *(b90+83);
//	Mir90[88]	= *(b90+82);
//	Mir90[89]	= *(b90+81);
//	B90ToD8(Mir90,D8,isWhiteGo);
//	return;
//UNMIROR:
//	B90ToD8(b90,D8,isWhiteGo);
//	return;
}

void 
WinErrorDisp(LPTSTR lpszFunction) { 
    TCHAR szBuf[80]; 
    LPVOID lpMsgBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    StringCbPrintf(szBuf,80, 
        _T("%s failed with error %d: %s\n"), 
        lpszFunction, dw, lpMsgBuf); 
 
    //MessageBox(NULL, szBuf, "Error", MB_OK); 
	//DispLog(szBuf);
    LogOut(szBuf);
    //LogOutput("\n",1,FALSE); //回车换行
    LocalFree(lpMsgBuf);

    //ExitProcess(dw); 
}

//找到当前B90的唯一D8，
//void FindMirrorOnly(POSITION* pos){
//	int Mir90[90];         //临时数组
//	int* b90	= pos->b256;
//	int* bend	= b90+90;
//	//int* addD8	= pos->pfd9;
//	
//	for(int* ip=b90; ip<bend; ip+=9){
//		for(int x=0; x<9; x++){
//			if(*(ip+8-x) > *(ip+x)){
//				goto MIRROR;
//			}
//		}
//	}
//	//不要反过来镜像
//	D90ToD8(b90,pos->pfd9,pos->pwtm);
//	return;
//MIRROR://要反过来镜像哇
//	//第一行
//	Mir90[0]	= *(b90+8);
//	Mir90[1]	= *(b90+7);
//	Mir90[2]	= *(b90+6);
//	Mir90[3]	= *(b90+5);
//	Mir90[4]	= *(b90+4);
//	Mir90[5]	= *(b90+3);
//	Mir90[6]	= *(b90+2);
//	Mir90[7]	= *(b90+1);
//	Mir90[8]	= *(b90+0);
//	//第二行
//	Mir90[9]	= *(b90+17);
//	Mir90[10]	= *(b90+16);
//	Mir90[11]	= *(b90+15);
//	Mir90[12]	= *(b90+14);
//	Mir90[13]	= *(b90+13);
//	Mir90[14]	= *(b90+12);
//	Mir90[15]	= *(b90+11);
//	Mir90[16]	= *(b90+10);
//	Mir90[17]	= *(b90+9);
//	//第三行
//	Mir90[18]	= *(b90+26);
//	Mir90[19]	= *(b90+25);
//	Mir90[20]	= *(b90+24);
//	Mir90[21]	= *(b90+23);
//	Mir90[22]	= *(b90+22);
//	Mir90[23]	= *(b90+21);
//	Mir90[24]	= *(b90+20);
//	Mir90[25]	= *(b90+19);
//	Mir90[26]	= *(b90+18);
//	//第四行
//	Mir90[27]	= *(b90+35);
//	Mir90[28]	= *(b90+34);
//	Mir90[29]	= *(b90+33);
//	Mir90[30]	= *(b90+32);
//	Mir90[31]	= *(b90+31);
//	Mir90[32]	= *(b90+30);
//	Mir90[33]	= *(b90+29);
//	Mir90[34]	= *(b90+28);
//	Mir90[35]	= *(b90+27);
//	//第五行
//	Mir90[36]	= *(b90+44);
//	Mir90[37]	= *(b90+34);
//	Mir90[38]	= *(b90+33);
//	Mir90[39]	= *(b90+32);
//	Mir90[40]	= *(b90+31);
//	Mir90[41]	= *(b90+30);
//	Mir90[42]	= *(b90+29);
//	Mir90[43]	= *(b90+28);
//	Mir90[44]	= *(b90+27);
//	//第六行
//	Mir90[45]	= *(b90+53);
//	Mir90[46]	= *(b90+52);
//	Mir90[47]	= *(b90+51);
//	Mir90[48]	= *(b90+50);
//	Mir90[49]	= *(b90+49);
//	Mir90[50]	= *(b90+48);
//	Mir90[51]	= *(b90+47);
//	Mir90[52]	= *(b90+46);
//	Mir90[53]	= *(b90+45);
//	//第七行
//	Mir90[54]	= *(b90+62);
//	Mir90[55]	= *(b90+61);
//	Mir90[56]	= *(b90+60);
//	Mir90[57]	= *(b90+59);
//	Mir90[58]	= *(b90+58);
//	Mir90[59]	= *(b90+57);
//	Mir90[60]	= *(b90+56);
//	Mir90[61]	= *(b90+55);
//	Mir90[62]	= *(b90+54);
//	//第八行
//	Mir90[63]	= *(b90+71);
//	Mir90[64]	= *(b90+70);
//	Mir90[65]	= *(b90+69);
//	Mir90[66]	= *(b90+68);
//	Mir90[67]	= *(b90+67);
//	Mir90[68]	= *(b90+66);
//	Mir90[69]	= *(b90+65);
//	Mir90[70]	= *(b90+64);
//	Mir90[71]	= *(b90+63);
//	//第九行
//	Mir90[72]	= *(b90+80);
//	Mir90[73]	= *(b90+79);
//	Mir90[74]	= *(b90+78);
//	Mir90[75]	= *(b90+77);
//	Mir90[76]	= *(b90+76);
//	Mir90[77]	= *(b90+75);
//	Mir90[78]	= *(b90+74);
//	Mir90[79]	= *(b90+73);
//	Mir90[80]	= *(b90+72);
//	//第十行
//	Mir90[81]	= *(b90+89);
//	Mir90[82]	= *(b90+88);
//	Mir90[83]	= *(b90+87);
//	Mir90[84]	= *(b90+86);
//	Mir90[85]	= *(b90+85);
//	Mir90[86]	= *(b90+84);
//	Mir90[87]	= *(b90+83);
//	Mir90[88]	= *(b90+82);
//	Mir90[89]	= *(b90+81);
//	D90ToD8(Mir90,pos->pfd9,pos->pwtm);
//	return;
//}