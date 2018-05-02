#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

//VOID
//InitEngineBox(HWND hDlg, HWND hwndCombo, char* nthcp, char* nthd, char* nthdir, char *nthnames)
//{
//  char buf[MSG_SIZ];
//  char *q;
//
//  InitComboStringsFromOption(hwndCombo, nthnames);
//  q = QuoteForFilename(nthcp);
//  //sprintf(buf, "%s%s%s", q, nthcp, q);
//  StringCbPrintf(buf,MSG_SIZ,"%s%s%s", q, nthcp, q);
//  if (*nthdir != NULLCHAR) {
//    q = QuoteForFilename(nthdir);
//    //sprintf(buf + strlen(buf), " /%s=%s%s%s", nthd, q, nthdir, q);
//	StringCbPrintf(buf + strlen(buf),MSG_SIZ,
//		" /%s=%s%s%s", nthd, q, nthdir, q);
//  }
//  if (*nthcp == NULLCHAR) {
//    SendMessage(hwndCombo, CB_SETCURSEL, (WPARAM) 0, (LPARAM) 0);
//  } else if (SendMessage(hwndCombo, CB_SELECTSTRING, (WPARAM) -1, (LPARAM) buf) == CB_ERR) {
//    SendMessage(hwndCombo, CB_SETCURSEL, (WPARAM) -1, (LPARAM) 0);
//    SendMessage(hwndCombo, WM_SETTEXT, (WPARAM) 0, (LPARAM) buf);
//  }
//}


//void
//SetStartupDialogEnables(HWND hDlg){
//	//EnableWindow(GetDlgItem(hDlg, OPT_ChessEngineName),
//	//	IsDlgButtonChecked(hDlg, OPT_ChessEngine) || appData.zippyPlay && IsDlgButtonChecked(hDlg, OPT_ChessServer));
//
//	//IDC_EDIT_YQA
//
//	//EnableWindow(GetDlgItem(hDlg, OPT_ChessEngineName),      IsDlgButtonChecked(hDlg, OPT_ChessEngine));
//	//EnableWindow(GetDlgItem(hDlg, OPT_SecondChessEngineName),IsDlgButtonChecked(hDlg, OPT_ChessEngine));
//
//	EnableWindow(GetDlgItem(hDlg, IDC_EDIT_YQA),      IsDlgButtonChecked(hDlg, OPT_ChessEngine));
//	EnableWindow(GetDlgItem(hDlg, IDC_EDIT_YQB),      IsDlgButtonChecked(hDlg, OPT_ChessEngine));
//
//	EnableWindow(GetDlgItem(hDlg, IDC_EDIT_YQA_XY),   IsDlgButtonChecked(hDlg, OPT_ChessEngine));
//	EnableWindow(GetDlgItem(hDlg, IDC_EDIT_YQB_XY),   IsDlgButtonChecked(hDlg, OPT_ChessEngine));
//
//
//	EnableWindow(GetDlgItem(hDlg, IDC_BUTTON_YQA),    IsDlgButtonChecked(hDlg, OPT_ChessEngine));
//
//	EnableWindow(GetDlgItem(hDlg, OPT_ChessServerName), 	 IsDlgButtonChecked(hDlg, OPT_ChessServer));
//	EnableWindow(GetDlgItem(hDlg, OPT_AdditionalOptions),  	 IsDlgButtonChecked(hDlg, OPT_AnyAdditional));
//	EnableWindow(GetDlgItem(hDlg, IDOK),
//		IsDlgButtonChecked(hDlg, OPT_ChessEngine) || IsDlgButtonChecked(hDlg, OPT_ChessServer) 
//		|| IsDlgButtonChecked(hDlg, OPT_View));
//}


//LRESULT CALLBACK           //初始化开始窗口子类化程序
//StartupDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){
//	char buf[MSG_SIZ];
//	HWND hwndCombo;
//	char *p;
//
//	switch (message) {
//		case WM_INITDIALOG:
//			/* Center the dialog 将窗口放到桌面的中间 */
//			CenterWindow (hDlg, GetDesktopWindow());      
//
//			//引擎选项
//			SetDlgItemText(hDlg,IDC_EDIT_YQA,appData.first.ProgramNames);
//			SetDlgItemText(hDlg,IDC_EDIT_YQB,appData.second.ProgramNames);
//
//			SetDlgItemText(hDlg,IDC_EDIT_YQA_XY,ST_UCCI[appData.first.ucci]);
//			SetDlgItemText(hDlg,IDC_EDIT_YQB_XY,ST_UCCI[appData.second.ucci]);
//
//			//网络服务器选项
//			hwndCombo = GetDlgItem(hDlg, OPT_ChessServerName);
//			InitComboStringsFromOption(hwndCombo, appData.icsNames);			
//			StringCbPrintf(buf,MSG_SIZ,"%s /icsport=%s", appData.icsHost, appData.icsPort);
//			if (*appData.icsHelper != NULLCHAR) {
//				char *q = QuoteForFilename(appData.icsHelper);				
//				StringCbPrintf(buf + strlen(buf),MSG_SIZ," /icshelper=%s%s%s", q, appData.icsHelper, q);
//			}
//			if (*appData.icsHost == NULLCHAR) {
//				SendMessage(hwndCombo, CB_SETCURSEL, (WPARAM) 0, (LPARAM) 0);
//				/*SendMessage(hwndCombo, CB_SHOWDROPDOWN, (WPARAM) TRUE, (LPARAM) 0); !!too soon */
//			} 
//			else if (SendMessage(hwndCombo, CB_SELECTSTRING, (WPARAM) -1, (LPARAM) buf) == CB_ERR) {
//				SendMessage(hwndCombo, CB_SETCURSEL, (WPARAM) -1, (LPARAM) 0);
//				SendMessage(hwndCombo, WM_SETTEXT,   (WPARAM)  0, (LPARAM) buf);
//			}
//			if (DIS.chessProgram) {
//				CheckDlgButton(hDlg, OPT_ChessEngine, BST_CHECKED);
//			} 
//			else if (appData.icsActive) {
//				CheckDlgButton(hDlg, OPT_ChessServer, BST_CHECKED);
//			} 
//			else if (appData.noChessProgram) {
//				CheckDlgButton(hDlg, OPT_View, BST_CHECKED);
//			}
//			SetStartupDialogEnables(hDlg);
//			return TRUE;
//
//		case WM_COMMAND:
//			switch (LOWORD(wParam)) {				
//				case IDC_BUTTON_YQA:		            //设置引擎A按钮						
//					YqSetOptionsPopup(hDlg);      //显示引擎设定选项
//					//再显示一下设置的东东
//					/*SendDlgItemMessage(hDlg,IDC_EDIT_YQA,WM_SETTEXT,0,(LPARAM)appData.first.ProgramNames);
//					SendDlgItemMessage(hDlg,IDC_EDIT_YQB,WM_SETTEXT,0,(LPARAM)appData.second.ProgramNames);*/
//					
//					SetDlgItemText(hDlg,IDC_EDIT_YQA,appData.first.ProgramNames);
//					SetDlgItemText(hDlg,IDC_EDIT_YQB,appData.second.ProgramNames);
//
//					SetDlgItemText(hDlg,IDC_EDIT_YQA_XY,ST_UCCI[appData.first.ucci]);
//					SetDlgItemText(hDlg,IDC_EDIT_YQB_XY,ST_UCCI[appData.second.ucci]);
//
//					break;
//				case IDOK:					//按下了OK按钮
//					if (IsDlgButtonChecked(hDlg, OPT_ChessEngine)) {  //按下了象棋引擎选项						
//
//						appData.noChessProgram = FALSE;
//						appData.icsActive = FALSE;
//					} 
//					else if (IsDlgButtonChecked(hDlg, OPT_ChessServer)) { //按下了服务器选项
//						//strcpy(buf, "/ics /icshost=");
//						StringCbCopy(buf,MSG_SIZ,"/ics /icshost=");
//						GetDlgItemText(hDlg, OPT_ChessServerName, buf + strlen(buf), 
//							(int)(sizeof(buf) - strlen(buf)));
//						p = buf;
//
//#ifdef USE_SQL_LITE_DATABASE
//#else
//                        ParseArgs(StringGet, &p);
//#endif
//						
//						//if (appData.zippyPlay) {
//						//	//strcpy(buf, "/fcp=");
//						//	StringCbCopy(buf,MSG_SIZ,"/fcp=");
//						//	GetDlgItemText(hDlg, OPT_ChessEngineName, buf + strlen(buf), 
//						//		(int)(sizeof(buf) - strlen(buf)));
//						//	p = buf;
//						//	ParseArgs(StringGet, &p);
//						//}
//					}
//					else if (IsDlgButtonChecked(hDlg, OPT_View)) {		//按下了查看或编辑棋局
//						appData.noChessProgram = TRUE;                  //没有象棋引擎 
//						appData.icsActive = FALSE;
//					}
//					else {
//						MessageBox(hDlg, "Choose an option, or cancel to exit",
//							"Option Error", MB_OK|MB_ICONEXCLAMATION);
//						return TRUE;
//					}
//					if (IsDlgButtonChecked(hDlg, OPT_AnyAdditional)) {
//						GetDlgItemText(hDlg, OPT_AdditionalOptions, buf, sizeof(buf));
//						p = buf;
//#ifdef USE_SQL_LITE_DATABASE
//#else
//						ParseArgs(StringGet, &p);				//解析其它选项
//#endif
//					}
//					EndDialog(hDlg, TRUE);
//					return TRUE;
//				case IDCANCEL:
//					ExitEvent(0);
//					return TRUE;
//				case IDM_HELPCONTENTS:
//					if (!WinHelp (hDlg, "ggFchess.hlp", HELP_KEY,(DWORD)(__int64)(LPSTR)"CONTENTS")) {
//						MessageBox (GetFocus(),
//							"Unable to activate help",
//							szAppName, MB_SYSTEMMODAL|MB_OK|MB_ICONHAND);
//					}
//					break;
//				default:
//					SetStartupDialogEnables(hDlg);
//					break;
//				}
//			break;
//	}
//	return FALSE;
//}
