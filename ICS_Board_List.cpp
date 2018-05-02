#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

#define ICS_MXQ_SPEAK_STR_NUM 13
TCHAR ICS_MXQ_SPEAK_STR[][16] = {
    {L"帮主专线"},
    {L"本帮呼叫"},
    {L"长啸"},
    {L"长啸进桌"},
    {L"传音入密"},
    {L"大叫"},
    {L"大叫进桌"},
    {L"好友热线"},
    {L"呼叫网管"},
    {L"轻诉"},
    {L"狮子吼"},
    {L"宣传干线"},
    {L"邀请"},
};

#define ICS_MXQ_BOARD_TITLE_NUM 8




//void        //加入或改变棋局情况
//MXQ_ChangOrAdd_Board_List(HWND hDlg, LV_ITEM* plvi, int id, bool isClear){
//    //
//    if(isClear){        //清空列表
//        SendDlgItemMessage(hDlg,IDC_LIST_BOARD,LVM_DELETEALLITEMS,0,0);	
//    }
//
//    //
//    //LV_ITEM
//    SendDlgItemMessage(hDlg,IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)plvi);
//}


LRESULT CALLBACK
PopIcsBoardCallBack(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam){
    MINMAXINFO* mmi;
    static int curSel = 0;
    TCHAR str[512];
	int table;
    switch(message){
        case WM_INITDIALOG:
            PostMessage(hDlg, WM_SETICON, (WPARAM) TRUE, (LPARAM) appData.iconWhite); 

            //初始化说话命令列表
            for(int i=0; i<ICS_MXQ_SPEAK_STR_NUM; i++){
                SendDlgItemMessage(hDlg,IDC_COMBO_SPEAK,CB_INSERTSTRING,-1, 
                    (LPARAM)ICS_MXQ_SPEAK_STR[i]);
            }
            SendDlgItemMessage(hDlg,IDC_COMBO_SPEAK, CB_SETCURSEL, 12,0);

            //初始化棋局列表头
            LV_COLUMN lvc;
            lvc.mask    = LVCF_FMT+LVCF_TEXT+LVCF_WIDTH;
            lvc.fmt     = LVCFMT_CENTER;
            lvc.cx      = 40;
            lvc.pszText = _T("桌号");
            SendDlgItemMessage(hDlg,IDC_LIST_BOARD,LVM_INSERTCOLUMN,0,(LPARAM)&lvc);

            lvc.cx      = 80;
			lvc.pszText = _T("红方");
            SendDlgItemMessage(hDlg,IDC_LIST_BOARD,LVM_INSERTCOLUMN,1,(LPARAM)&lvc);

            lvc.cx      = 45;
			lvc.pszText = _T("级别");
            SendDlgItemMessage(hDlg,IDC_LIST_BOARD,LVM_INSERTCOLUMN,2,(LPARAM)&lvc);

            lvc.cx      = 80;
			lvc.pszText = _T("黑方");
            SendDlgItemMessage(hDlg,IDC_LIST_BOARD,LVM_INSERTCOLUMN,3,(LPARAM)&lvc);

            lvc.cx      = 45;
			lvc.pszText = _T("级别");
            SendDlgItemMessage(hDlg,IDC_LIST_BOARD,LVM_INSERTCOLUMN,4,(LPARAM)&lvc);

            lvc.cx      = 60;
			lvc.pszText = _T("类型");
            SendDlgItemMessage(hDlg,IDC_LIST_BOARD,LVM_INSERTCOLUMN,5,(LPARAM)&lvc);

            lvc.cx      = 24;
			lvc.pszText = _T("局");
            SendDlgItemMessage(hDlg,IDC_LIST_BOARD,LVM_INSERTCOLUMN,6,(LPARAM)&lvc);

            lvc.cx      = 36;
			lvc.pszText = _T("旁观");
            SendDlgItemMessage(hDlg,IDC_LIST_BOARD,LVM_INSERTCOLUMN,7,(LPARAM)&lvc);

            //lvc.cx      = 40;
            //lvc.pszText = "其它";
            //SendDlgItemMessage(hDlg,IDC_LIST_BOARD,LVM_INSERTCOLUMN,8,(LPARAM)&lvc);


            SendDlgItemMessage(hDlg,IDC_LIST_BOARD,
				   LVM_SETEXTENDEDLISTVIEWSTYLE,0,
				   LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT  );

            return FALSE; 
        case  WM_NOTIFY:               
            // returns LRESULT in lResult     (HWND) hWndControl,      
            // handle to destination control     (UINT) WM_NOTIFY,     
            // message ID     (WPARAM) wParam,      
            // = (WPARAM) (int) idCtrl;    (LPARAM) lParam     
            // = (LPARAM) (LPNMHDR) pnmh; );  
            //1, 得检查是不是这个ＩＤＣ＿ＬＩＳＴ＿ＢＯＡＲＤ
            {
                //HWND list = GetDlgItem(hDlg,IDC_LIST_BOARD);
                //if(list == (HWND)wParam){
                //    int test = 0;
                //}
                if(wParam == IDC_LIST_BOARD){ //LVN_COLUMNCLICK
                    switch (((LPNMHDR) lParam)->code){
                        case NM_CLICK:
                            {
                                NMITEMACTIVATE  *lpnmitem = (LPNMITEMACTIVATE) lParam;
                                int item = lpnmitem->iItem;
                                LVITEM lvi;
                                lvi.pszText     = str;
                                lvi.iSubItem    = 0;
                                lvi.iItem       = item;
                                lvi.cchTextMax  = 510;
                                SendDlgItemMessage(hDlg,IDC_LIST_BOARD,LVM_GETITEMTEXT,item,(LPARAM)(&lvi));
                                 
                                curSel = _wtoi(lvi.pszText);
                                if(curSel == 0){
                                    return FALSE;
                                }

								//


                                POINT pt;
                                GetCursorPos(&pt);
                                //SetFore
                                HMENU hm = LoadMenu(hInst,MAKEINTRESOURCE(IDR_MENU_ICS_BOARD));	
                                hm       = GetSubMenu(hm,0);
                                TrackPopupMenu(hm,TPM_LEFTALIGN|TPM_LEFTBUTTON |
                                    TPM_RIGHTBUTTON,pt.x,pt.y,NULL,hDlg,NULL);
                            }
                            break;
                        default:
                            break;
                    }

                   //NMITEMACTIVATE  *pnml = (NMITEMACTIVATE *)lParam;
                   //if(pnml->hdr.code == NM_CLICK){ //|| pnml->hdr.code == NM_RCLICK 
                   ////  //int kk = 0;
                   //// LVN_ITEMCHANGED
                   // //_WIN32_IE
                   // //NMITEMACTIVATE *pnml = (NMITEMACTIVATE*)lParam;
                   // //if(pnml->hdr.code == LVN_ITEMACTIVATE){
                   //    int   item = pnml->iItem;
                   //    LVITEM lvi;                       
                   //    lvi.pszText  = str;
                   //    lvi.iSubItem = 0;
                   //    lvi.iItem    = item;
                   //    SendDlgItemMessage(hDlg,IDC_LIST_BOARD,LVM_GETITEMTEXT,item,(LPARAM)(&lvi));
                   //    //if(pnum == NULL){
                   //    //  return FALSE;
                   //    //}

                   //    curSel = atoi(lvi.pszText);

                   //    if(curSel == 0){
                   //      return FALSE;
                   //    }
                   //    //  
                   //    POINT pt;
                   //    GetCursorPos(&pt);
                   //    //SetFore
                   //    HMENU hm = LoadMenu(hInst,MAKEINTRESOURCE(IDR_MENU_ICS_BOARD));	
                   //    hm       = GetSubMenu(hm,0);
                   //    TrackPopupMenu(hm,TPM_LEFTALIGN|TPM_LEFTBUTTON |
                   //            TPM_RIGHTBUTTON,pt.x,pt.y,NULL,hDlg,NULL);
                   //    //int test   = 0;
                   //    //if(lParam == WM_RBUTTONDOWN){
                   //    //    POINT pt;
                   //    //    GetCursorPos(&pt);
                   //    //    SetForegroundWindow(hWnd);
                   //    //    HMENU hm = LoadMenu(hInst,MAKEINTRESOURCE(IDR_MENU_NOTE));	
                   //    //    hm = GetSubMenu(hm,0);
                   //    //    TrackPopupMenu(hm,TPM_RIGHTALIGN|TPM_LEFTBUTTON |
                   //    //        TPM_RIGHTBUTTON,pt.x,pt.y,NULL,hWnd,NULL);

                   //    //}
                   //    //else if(lParam == WM_LBUTTONDOWN){
                   //    //    SendMessage(hWnd,WM_COMMAND,ID_NOTEMENU_RESTORE,0);
                   //    //    SetForegroundWindow(hWnd);
                   //    //}
                   //}
                }//if(wParam == IDC_LIST_BOARD)
            }
            break;
        //case WM_RBUTTONDOWN:        //是右键按下的
        //    {
        //        //首先判断是不是选择了一列
        //        int sel = (int)SendDlgItemMessage(hDlg,IDC_LIST_BOARD,
        //             LVM_GETSELECTEDCOLUMN,0,0);
        //        if(sel != 0){
        //            int test = 0;
        //        }
        //    }
        //    return FALSE;
        case WM_COMMAND:
            switch(LOWORD(wParam)){  //wmId    = LOWORD(wParam); 
                    //case ID_OBS:  {      //旁观按钮
                    ////得到当前选择的列表框的编号
                    ////LVM_INSERTITEM
                    ////int sel = ListView_GetSelectedColumn(IDC_LIST_BOARD);
                    //  int sel = (int)SendDlgItemMessage(hDlg,IDC_LIST_BOARD,
                    //      LVM_GETSELECTEDCOLUMN,0,0);
                    //  int test  = 0;
                    //  }
                    //break;
                case IDC_LIST_BOARD:{
                    int test = WM_RBUTTONDOWN;
                            }
                    break;
				case IDC_NEXT_STAGE: //下一关					
					{
					
						if(ICS.stage > 0){
							swprintf_s(str,sizeof(str)/sizeof(TCHAR),L"lt %d",ICS.stage + 1); 
						}
						else{
							swprintf_s(str, sizeof(str) / sizeof(TCHAR), L"lt %d", 1);
						}
						CMX_183_SEND_CODDING(str);
					}
					break;
				case IDC_PREV_STAGE: //上一关
					{
					
						if(ICS.stage > 0){
							swprintf_s(str, sizeof(str) / sizeof(TCHAR), L"lt %d", ICS.stage - 1);
						}
						else{
							swprintf_s(str, sizeof(str) / sizeof(TCHAR), L"lt %d", 0);
						}
						CMX_183_SEND_CODDING(str);
					}					
					break;
				case IDC_DALEI:{		//打擂

					dispboard_t* pDis = OBS[0];

					ResetGameEvent(pDis);					//恢位一下棋局
					
					if(pDis->table != 0){		//只有旁观可离开						
						swprintf_s(str, sizeof(str) / sizeof(TCHAR), L"l %d", pDis->table);
						CMX_183_SEND_CODDING(str);
					}
					else{
	/*					sprintf_s(str,sizeof(str),"l 1");
						CMX_183_SEND_CODDING(str);*/
					}
					Sleep(500);
					CMX_183_SEND_CODDING(L"j");	
							   }
					break;
				//旁观棋桌
                case IDM_ICS_OBS_MAIN:			//用主窗口，旁观棋桌 
					switch(appData.ACPSics.ICS_net_id){
						case ICS_MXQ_CN183:		{
							//当前只有一个棋桌
							dispboard_t* pDis = OBS[0];
							PGN* pgn = pDis->pgn;
						
							if(pDis->table != 0){
								//
								swprintf_s(str, sizeof(str) / sizeof(TCHAR),
									_T("\n对不起，你正在%d桌旁观或下棋,请关闭后再打开"),pDis->table);
								LogOut(str);
								break;
							}							

							if(ICS.stage == 0){
								swprintf_s(str, sizeof(str) / sizeof(TCHAR), L"obs %d", curSel);
								table = curSel;
							}
							else{
								swprintf_s(str, sizeof(str) / sizeof(TCHAR), L"obs %d %d", ICS.stage, curSel);
								table = (ICS.stage-1)*20 + curSel;
							}

							OBS[table] = pDis;
							pDis->table = table;
							
							CMX_183_SEND_CODDING(str);

							SendDlgItemMessage(HWND_CONSOLE,IDC_BUT_ICS_BOARD,BM_SETCHECK,0,0);
						    ShowWindow(hDlg,SW_HIDE);

							//
												}
							break;
						default:
							LogOut(_T("此联网协议暂不能使用\n"));
							break;							
					}
					break;
                    //if(appData.ACPSics.ICS_net_id == ICS_MXQ_CN183){
                    //    int table;
                    //    if(ICS.stage == 0){
                    //        sprintf_s(str,sizeof(str),"obs %d",curSel);
                    //        table = curSel;
                    //    }
                    //    else{
                    //        sprintf_s(str,sizeof(str),"obs %d %d",ICS.stage,curSel);
                    //        table = (ICS.stage-1)*20 + curSel;
                    //    }                        
                    //    //打开旁观窗口,可能要延时一会儿
                    //    PopObsBoardDialog(table);
                    //    //while(OBS.pob[table]->hwndTable == NULL){
                    //    //    Sleep(100);
                    //    //    LogOut("请等待,正在打开棋局窗口");
                    //    //}
                    //    if(OBS[table] != NULL){
                    //        CMX_183_SEND_CODDING(str);
                    //    }
                    //}
                    //else{
                    //}
                    //break;
                case IDM_ICS_JOIN_MAIN:		  //用主窗口，加入棋桌对战
					switch(appData.ACPSics.ICS_net_id){
						case ICS_MXQ_CN183:{

							dispboard_t* pDis = OBS[0];
							if(pDis->table != 0){
								//
								swprintf_s(str, sizeof(str) / sizeof(TCHAR),
									_T("\n对不起，你正在%d桌旁观或下棋,请关闭后再打开"),pDis->table);
								LogOut(str);
								break;
							}

							if(ICS.stage == 0){
								swprintf_s(str, sizeof(str) / sizeof(TCHAR), L"j %d", curSel);
								table = curSel;
							}
							else{
								swprintf_s(str, sizeof(str) / sizeof(TCHAR), L"j %d %d", ICS.stage, curSel);
								table = (ICS.stage-1)*20 + curSel;
							}

							OBS[table] = pDis;
							pDis->table = table;
							
							CMX_183_SEND_CODDING(str);

							SendDlgItemMessage(HWND_CONSOLE,IDC_BUT_ICS_BOARD,BM_SETCHECK,0,0);
							ShowWindow(hDlg,SW_HIDE);


										   }
							break;
						default:
							LogOut(_T("此联网协议暂不能使用\n"));
							break;							
					}
                    break;
				//口令加入棋盘
                case IDM_ICS_JOIN_W_PASS:
                    break;
                default:
                    break;
            }
            //SendToICS("map\n");
            break;
        case WM_SIZE:
            //FitTimeDisplayDlgItem(hDlg);
            break;
        case WM_CLOSE:
            //TimeDisplayListEvent();

            //如果子酱//IDC_GO_PLACE

            SendDlgItemMessage(HWND_CONSOLE,IDC_BUT_ICS_BOARD,BM_SETCHECK,0,0);
            ShowWindow(hDlg,SW_HIDE);
            //EndDialog(hDlg, LOWORD(wParam));

            //DLG.hwndGoPlace = NULL;

            return (INT_PTR)TRUE;
            break;
        case WM_GETMINMAXINFO:    //避免窗口拉的过小 /* Prevent resizing window too small */
            mmi = (MINMAXINFO*) lParam;
            mmi->ptMinTrackSize.x = 112;
            mmi->ptMinTrackSize.y = 130;
            break;
        default:
            break;
    }
    return FALSE;

    //窗口过程对应于不同的消息有各种不同含义的返回值，
    //而对话框过程返回BOOL类型的值，返回TRUE表示已经处理了某条消息，
    //返回FALSE表示没有处理。“对话框管理器”代码会根据
    //返回值决定是否继续处理某一条消息（惟一的例外是WM_INITDIALOG消息）。
}


void PopIcsBoardDialog(void){

	dispboard_t* pDis = OBS[0];

    FARPROC lpProc = MakeProcInstance((FARPROC)PopIcsBoardCallBack,hInst);
    TAB.hwndICS_Board_List = CreateDialog(hInst,MAKEINTRESOURCE(DLG_ICS_TABLE),        
        pDis->hwndThis,(DLGPROC)lpProc);
    FreeProcInstance(lpProc);
    ShowWindow(TAB.hwndICS_Board_List,SW_HIDE);
    CenterWindow(TAB.hwndICS_Board_List,pDis->hwndThis);
}