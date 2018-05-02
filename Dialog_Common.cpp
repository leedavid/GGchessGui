#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"



void DlgDefaultPosition(void){          //È±Ê¡Î»ÖÃ

	 dispboard_t* pDis = OBS[0];
    //if(DLG.dlgstep){
    //    FitStepListDlgPosition(DLG.dlgstep);
    //    CheckMenuItem(GetMenu(pDis->hwndThis),IDM_ShowStepListDlg,MF_CHECKED);
    //    //DLG.dlgstepUp = true;
    //}
    //if(DLG.dlgTimeDisplay){
    //    FitTimeDisplayDlgPosition(DLG.dlgTimeDisplay);
    //    //DLG.dlgTimeDisplayUp = true;
    //    CheckMenuItem(GetMenu(pDis->hwndThis),IDM_ShowTimeDisplay,MF_CHECKED);
    //}
    //if(HWND_CONSOLE){
    //    FitRichLogDlgPosition(HWND_CONSOLE);
    //    //DLG.IsConsoleShow = true;
    //    CheckMenuItem(GetMenu(pDis->hwndThis),IDM_RichLog,MF_CHECKED);
    //}
    //if(HWND_BOOK){
    //    FitBookDlgPositionDefault(HWND_BOOK);
    //    //HWND_BOOKUp = true;
    //    CheckMenuItem(GetMenu(pDis->hwndThis),IDM_BOOK_DLG,MF_CHECKED);
    //}  
    //SetFocus(pDis->hwndThis);
}

void
InitComboStrings(HWND hwndCombo, char **cd)
{
  SendMessage(hwndCombo, CB_RESETCONTENT, 0, 0);

  while (*cd != NULL) {
    SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM) *cd);
    cd++;
  }
}

//
//void
//InitComboStringsFromOption(HWND hwndCombo, TCHAR *str){
//  TCHAR buf1[ARG_MAX];
//  int len;
//
//  if (str[0] == '@') {
//   
//    //FILE* f = fopen(str + 1, "r");
//    FILE *f;
//	_wfopen_s(&f,str + 1, L"r");
//
//    if (f == NULL) {
//      DisplayFatalError(str + 1, errno, 2);
//      return;
//    }
//    len = (int)fread(buf1, 1, sizeof(buf1)-1, f);
//    fclose(f);
//    buf1[len] = NULLCHAR;
//    str = buf1;
//  }
//
//  SendMessage(hwndCombo, CB_RESETCONTENT, 0, 0);
//
//  for (;;) {
//    char buf[MSG_SIZ];
//    char *end = strchr(str, '\n');
//    if (end == NULL) return;
//    memcpy(buf, str, end - str);
//    buf[end - str] = NULLCHAR;
//    SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM) buf);
//    str = end + 1;
//  }
//}