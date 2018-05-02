#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

#include "dlgs.h"

LRESULT CALLBACK
OldOpenFileHook(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
  BOOL ok;
  OPENFILENAME *ofn;
  static UINT *number; /* gross that this is static */

  switch (message) {
  case WM_INITDIALOG: /* message: initialize dialog box */
    /* Center the dialog over the application window */
    ofn = (OPENFILENAME *) lParam;
    if (ofn->Flags & OFN_ENABLETEMPLATE) {
      number = (UINT *) ofn->lCustData;
      SendMessage(GetDlgItem(hDlg, edt2), WM_SETTEXT, 0, (LPARAM) "");
    } else {
      number = NULL;
    }
    CenterWindow (hDlg, GetWindow (hDlg, GW_OWNER));
    return FALSE;  /* Allow for further processing */

  case WM_COMMAND:
    if ((LOWORD(wParam) == IDOK) && (number != NULL)) {
      *number = GetDlgItemInt(hDlg, OPT_IndexNumberOld, &ok, FALSE);
    }
    return FALSE;  /* Allow for further processing */
  }
  return FALSE;
}

int
DoReadFile(HANDLE hFile, char *buf, int count, DWORD *outCount, OVERLAPPED *ovl)
{
    int ok, err;

    ResetEvent(ovl->hEvent);
    ovl->Offset = ovl->OffsetHigh = 0;
    ok = ReadFile(hFile, buf, count, outCount, ovl);
    if (ok) {
        err = NO_ERROR;
    } 
    else {
        err = GetLastError();
        if (err == ERROR_IO_PENDING) {
            ok = GetOverlappedResult(hFile, ovl, outCount, TRUE);
            if (ok){
                err = NO_ERROR;
            }
            else{
                err = GetLastError();
            }
        }
    }
    return err;
}

int
DoWriteFile(HANDLE hFile, char *buf, int count, DWORD *outCount,OVERLAPPED *ovl){
    int ok, err;

    ResetEvent(ovl->hEvent);
    ovl->Offset = ovl->OffsetHigh = 0;
    ok = WriteFile(hFile, buf, count, outCount, ovl);
    if (ok) {
        err = NO_ERROR;
    } 
    else {
        err = GetLastError();
        if (err == ERROR_IO_PENDING) {
            ok = GetOverlappedResult(hFile, ovl, outCount, TRUE);
            if (ok){
                err = NO_ERROR;
            }
            else{
                err = GetLastError();
            }
        }
    }
    return err;
}


char
FileGet(void *getClosure){
  int c;
  FILE* f = (FILE*) getClosure;

  c = getc(f);
  if (c == EOF)
    return NULLCHAR;
  else
    return (char) c;
}

char *
QuoteForFilename(char *filename){
  int dquote, space;
  dquote = strchr(filename, '"') != NULL;
  space = strchr(filename, ' ') != NULL;
  if (dquote || space) {
    if (dquote) {
      return "'";
    } else {
      return "\"";
    }
  } else {
    return "";
  }
}
UINT APIENTRY
OpenFileHook(HWND hdlg, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
  static UINT *number;
  OPENFILENAME *ofname;
  OFNOTIFY *ofnot;
  switch (uiMsg) {
  case WM_INITDIALOG:
    ofname = (OPENFILENAME *)lParam;
    number = (UINT *)(ofname->lCustData);
    break;
  case WM_NOTIFY:
    ofnot = (OFNOTIFY *)lParam;
    if (ofnot->hdr.code == CDN_FILEOK) {
      *number = GetDlgItemInt(hdlg, OPT_IndexNumber, NULL, FALSE);
    }
    break;
  }
  return 0;
}


FILE *
OpenFileDialog(HWND hwnd, BOOL write, TCHAR *defName, TCHAR *defExt,
TCHAR *nameFilt, TCHAR *dlgTitle, UINT *number,
TCHAR fileTitle[MSG_SIZ], TCHAR fileName[MSG_SIZ])
{
  OPENFILENAME openFileName;
  TCHAR buf1[MSG_SIZ];
  FILE *f;

  if (fileName == NULL) fileName = buf1;
  if (defName == NULL) {
	  StringCbCopy(fileName,MSG_SIZ,_T("*."));
	  StringCbCat(fileName,MSG_SIZ,defExt);
  } 
  else {
	  StringCbCopy(fileName,MSG_SIZ,defName);
  }
  if (fileTitle){
	  StringCbCopy(fileTitle, MSG_SIZ, _T(""));
  }
  if (number) *number = 0;

  openFileName.lStructSize       = sizeof(OPENFILENAME);
  openFileName.hwndOwner         = hwnd;
  openFileName.hInstance         = hInst;
  openFileName.lpstrFilter = (LPCWSTR)nameFilt;
  openFileName.lpstrCustomFilter = (LPWSTR) NULL;
  openFileName.nMaxCustFilter    = 0L;
  openFileName.nFilterIndex      = 1L;
  openFileName.lpstrFile         = fileName;
  openFileName.nMaxFile          = MSG_SIZ;
  openFileName.lpstrFileTitle    = fileTitle;
  openFileName.nMaxFileTitle     = fileTitle ? MSG_SIZ : 0;
  openFileName.lpstrInitialDir   = NULL;
  openFileName.lpstrTitle = (LPCWSTR)dlgTitle;
  openFileName.Flags = OFN_PATHMUSTEXIST | OFN_HIDEREADONLY 
    | (write ? 0 : OFN_FILEMUSTEXIST) 
    | (number ? OFN_ENABLETEMPLATE | OFN_ENABLEHOOK: 0)
	| (OFN_EXPLORER);
    //| (oldDialog ? 0 : OFN_EXPLORER);
  openFileName.nFileOffset       = 0;
  openFileName.nFileExtension    = 0;
  openFileName.lpstrDefExt = (LPCWSTR)defExt;
  openFileName.lCustData         = (LPARAM) number;
  //openFileName.lpfnHook          = oldDialog ?  (LPOFNHOOKPROC) OldOpenFileHook : (LPOFNHOOKPROC) OpenFileHook;
  openFileName.lpfnHook          = (LPOFNHOOKPROC) OpenFileHook;
  //openFileName.lpTemplateName    = MAKEINTRESOURCE(oldDialog ? 1536 : DLG_IndexNumber);
  openFileName.lpTemplateName    = MAKEINTRESOURCE(DLG_IndexNumber);

  if (write ? GetSaveFileName(&openFileName) : GetOpenFileName(&openFileName)) {
	  /* open the file */
	  //f = fopen(openFileName.lpstrFile, write ? "a" : "rb");
	  _wfopen_s(&f,openFileName.lpstrFile, write ? _T("a") : _T("rb"));

	  if (f == NULL) {
		  MessageBox(hwnd, _T("File open failed"), NULL, MB_OK | MB_ICONEXCLAMATION);
		  return NULL;
	  }
  } 
  else {
	  int err = CommDlgExtendedError();
	  if (err != 0){
		  LogOut(L"Internal error in file dialog box");
	  }
	  return FALSE;
  }
  return f;
}






