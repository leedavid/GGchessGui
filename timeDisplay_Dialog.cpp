#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

#include <windows.h>   /* required for all Windows applications */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <fcntl.h>
#include <math.h>
#include <commdlg.h>
#include <dlgs.h>



//void FitTimeDisplayDlgPosition(HWND hDlg){  //调整棋步窗口到缺省位置
// //   WINDOWPLACEMENT wp;
//	//wp.length = sizeof(WINDOWPLACEMENT);
//	//GetWindowPlacement(hwndMain,&wp);
// //   
// //   wp.rcNormalPosition.bottom = wp.rcNormalPosition.bottom;
// //   wp.rcNormalPosition.top    = wp.rcNormalPosition.bottom - 130;
// //   wp.rcNormalPosition.right  = wp.rcNormalPosition.left;
// //   wp.rcNormalPosition.left   = wp.rcNormalPosition.right - 112;
// //   SetWindowPlacement(hDlg,&wp);
// //   //FitTimeDisplayDlgItem(hDlg);
//
//    RECT Rect;
//    GetWindowRect(OBS[0]->hwndThis,&Rect);
//
//    int x       = Rect.left   - 112;
//    int y       = Rect.bottom - 130;
//    int width   = 112;
//    int height  = 130;
//
//    SetWindowPos(hDlg,NULL,x,y,width,height,SWP_NOZORDER|SWP_NOACTIVATE);
//
//    ShowWindow(hDlg,SW_SHOW);
//}

//LRESULT CALLBACK
//TimeDisplayDialog(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam){
//    MINMAXINFO* mmi;
//    switch(message){
//        case WM_INITDIALOG:
//            PostMessage(hDlg, WM_SETICON, (WPARAM) TRUE, (LPARAM)MAIN.iconWhite);
//            
//            //OBS[0]->TimeRedTotal    = GetDlgItem(hDlg,IDC_TIME_RED_TOTAL);
//            //OBS[0]->TimeRedStep     = GetDlgItem(hDlg,IDC_TIME_RED_STEP);
//
//            //OBS[0]->TimeBlueTotal   = GetDlgItem(hDlg,IDC_TIME_BLUE_TOTAL);
//            //OBS[0]->TimeBlueStep    = GetDlgItem(hDlg,IDC_TIME_BLUE_STEP);
//
//            return FALSE;            
//        case WM_COMMAND:
//            break;
//        case WM_SIZE:
//            //FitTimeDisplayDlgItem(hDlg);
//            break;
//        case WM_CLOSE:
//            TimeDisplayListEvent();
//            break;
//        case WM_GETMINMAXINFO:    //避免窗口拉的过小 /* Prevent resizing window too small */
//            mmi = (MINMAXINFO*) lParam;
//            mmi->ptMinTrackSize.x = 112;
//            mmi->ptMinTrackSize.y = 130;
//            break;
//        default:
//            break;
//    }
//    return FALSE;
//
//    //窗口过程对应于不同的消息有各种不同含义的返回值，
//    //而对话框过程返回BOOL类型的值，返回TRUE表示已经处理了某条消息，
//    //返回FALSE表示没有处理。“对话框管理器”代码会根据
//    //返回值决定是否继续处理某一条消息（惟一的例外是WM_INITDIALOG消息）。
//}

//void TimeDisplayListEvent(void){
//    //(void) CheckMenuItem(GetMenu(hwndMain), IDM_SaveSettingsOnExit,
//				//			MF_BYCOMMAND|(DIS.saveSettingsOnExit ?  MF_CHECKED : MF_UNCHECKED));
//    if(DLG.dlgTimeDisplay){
//        if(IsWindowVisible(DLG.dlgTimeDisplay)){
//            ShowWindow(DLG.dlgTimeDisplay,SW_HIDE);
//            CheckMenuItem(GetMenu(OBS[0]->hwndThis),IDM_ShowTimeDisplay,MF_UNCHECKED);
//        }
//        else{
//            ShowWindow(DLG.dlgTimeDisplay,SW_SHOW);
//            CheckMenuItem(GetMenu(OBS[0]->hwndThis),IDM_ShowTimeDisplay,MF_CHECKED);
//        }
//        //if(DLG.dlgTimeDisplayUp){     //当前棋步对话框已显示了           
//        //    ShowWindow(DLG.dlgTimeDisplay,SW_HIDE);
//        //    DLG.dlgTimeDisplayUp = false;
//        //    CheckMenuItem(GetMenu(hwndMain),IDM_ShowTimeDisplay,MF_UNCHECKED);
//        //}
//        //else{               //是隐藏了
//        //    ShowWindow(DLG.dlgTimeDisplay,SW_SHOW);
//        //    DLG.dlgTimeDisplayUp = true;
//        //    CheckMenuItem(GetMenu(hwndMain),IDM_ShowTimeDisplay,MF_CHECKED);
//        //}
//    }
//    else{
//         FARPROC lpProc = MakeProcInstance((FARPROC)TimeDisplayDialog,hInst);
//         DLG.dlgTimeDisplay = CreateDialog(hInst,MAKEINTRESOURCE(DLG_TimeDisplay),OBS[0]->hwndThis,(DLGPROC)lpProc);
//         FreeProcInstance(lpProc);
//         FitTimeDisplayDlgPosition(DLG.dlgTimeDisplay);
//         ShowWindow(DLG.dlgTimeDisplay,SW_SHOW);
//         //DLG.dlgTimeDisplayUp = true;
//         CheckMenuItem(GetMenu(OBS[0]->hwndThis),IDM_ShowTimeDisplay,MF_CHECKED);
//    }
//}
//
//
