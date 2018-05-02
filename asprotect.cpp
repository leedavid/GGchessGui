#include "stdafx.h"
#include "GGchess.h"
#include "chess.h"
#include "data.h"
#include "pregen.h"
#include <shellapi.h>


#ifdef USE_ASPROTECT23


char*	LocalHardwareID = NULL;
char*	ModeName		= NULL;

DWORD	TrialDaysTotal	= 0,
		TrialDaysLeft	= 0;

MODE_STATUS   mode_status;
//char*		  UserKey		= NULL;
//char*		  UserName		= NULL;
BOOL          regOk         = FALSE;



//判断注册是不是成功了
BOOL ProcessRegistration( HWND hwnd ){

	char caption[100];
	char buffer[1024];

	

	GetRegistrationInformation(MODEID, &UserKey, &UserName);

	if((UserKey != NULL) && (strlen(UserKey) > 0)){
		
		//Trial doesn.t expire
		// Application was registered

		REG_CRYPT_BEGIN2

		strcpy_s(caption, sizeof(caption), "Registerd version(已注册版)!");
		
		SetWindowText(hwnd,caption);

		GetModeInformation(MODEID, &ModeName, &mode_status);

		//ID_WANT_REG

		SetWindowText(GetDlgItem(hwnd,ID_WANT_REG), "关闭");

		//hide trial buttons 
		ShowWindow(GetDlgItem(hwnd,IDC_BUYNOW), SW_HIDE);

		ShowWindow(GetDlgItem(hwnd,ID_EXIT), SW_HIDE);

		//registered info

		sprintf_s(buffer,sizeof(buffer),
			"Key: %s\nName: \t\t%s\nMode Name: \t%s",
			UserKey,UserName,ModeName);

		SetDlgItemText(hwnd,IDC_TEXT_REG_INFO,buffer);



		REG_CRYPT_END2

		return TRUE;

	}
	else{

		if(GetTrialDays(1, &TrialDaysTotal, &TrialDaysLeft)){

			// caption 
			strcpy_s(caption, sizeof(caption), "Trial version(体验版)!");
			SetWindowText(hwnd,caption);

			//
			ShowWindow(GetDlgItem(hwnd,IDC_BUYNOW), SW_SHOW);
			ShowWindow(GetDlgItem(hwnd,ID_EXIT), SW_SHOW);

			//trial info

			if(TrialDaysLeft == 0){
				strcpy_s(buffer,sizeof(buffer),
					"\t\tTrial Expired!(软件试用到期了)");
				SetDlgItemText(hwnd,IDC_TEXT_REG_INFO,buffer);
			}
			else{
				sprintf_s(buffer,sizeof(buffer),
					"\tUnregistered trial verson (未注册版): \n\n\tYou have : %d days left",
					TrialDaysLeft);
				SetDlgItemText(hwnd,IDC_TEXT_REG_INFO,buffer);
			}
		}
	}

	return FALSE;
}

//注册窗口的处理程序

BOOL APIENTRY RegDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){

	char keybuf[1024];
	char namebuf[1024];
	char buffer[1024];
	int  size;

	switch(msg){
		case WM_INITDIALOG:
			LocalHardwareID = GetHardwareID();
			SetDlgItemText(hwnd,IDC_HARD_ID,LocalHardwareID);
			return TRUE;
			break;
		case WM_COMMAND:
			switch(LOWORD(wParam)){
				case IDOK:		//注册按钮
					
					// key 

					size = GetDlgItemText(hwnd,IDC_REG_KEY,keybuf,sizeof(keybuf));
					keybuf[size] = 0;

					// name
					size = GetDlgItemText(hwnd,IDC_USER_ID,namebuf,sizeof(namebuf));
					namebuf[size] = 0;

					if( CheckKeyAndDecrypt((char*)keybuf, (char*)namebuf,TRUE) == TRUE){
						MessageBox(hwnd,
							"Thank you for you registration!\n 感谢您的注册！",
							"Registration",
							MB_ICONINFORMATION);
						EndDialog(hwnd,IDOK);
						break;
					}

					else{
						MessageBox(hwnd,
							"Key is not valid !!\n注册码无效!! \n请联系作者(asmchess@126.com)",
							"Registration",
							MB_ICONWARNING);
						break;
					}


					break;
				case ID_SEND_MAIL:		//发送邮件
					//sprintf_s(buffer,
					buffer[0] = NULLCHAR;
					StringCbCat(buffer,sizeof(buffer),
						"mailto:asmchess@126.com?subject=Hardware%20ID%20for%20佳佳象棋程序%20(GGchess)%20&body=Hardware%20ID is%20:%20");
					StringCbCat(buffer,sizeof(buffer),
						LocalHardwareID);
					StringCbCat(buffer,sizeof(buffer),
						"%0d%0aRegistration%20information%20:");
					ShellExecute((HWND)GetDesktopWindow(), "open", buffer, NULL, NULL, SW_SHOWNORMAL);
					break;
				case IDCANCEL:
					EndDialog(hwnd,IDCANCEL);
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}

	return FALSE;
}

BOOL APIENTRY firstDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
	switch(msg){

		case WM_INITDIALOG:
			CenterWindow(hwnd,GetDesktopWindow());
			if(ProcessRegistration( hwnd ) == TRUE){
				EndDialog(hwnd, IDOK);
			}
			return TRUE;
		    break;
		case WM_COMMAND:
			switch(LOWORD(wParam)){
				case ID_EXIT:	//exit
					EndDialog(hwnd, IDOK);
					break;
				case ID_WANT_REG:
					ShowWindow(hwnd,SW_HIDE);

					DialogBox(	NULL,(LPSTR)MAKEINTRESOURCE(IDD_REGIST_PLEASE),hwnd,(DLGPROC/*WNDPROC*/)RegDlgProc);

					if(ProcessRegistration( hwnd )){
						EndDialog(hwnd, IDOK);
					}

					ShowWindow(hwnd, SW_SHOW);

					break;
				case IDC_BUYNOW:
					ShellExecute((HWND)GetDesktopWindow(), 
						"open", "http://www.ggchess.com/register.htm",
						NULL, NULL, SW_SHOWNORMAL);
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}

	return FALSE;
}

#endif