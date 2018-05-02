#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

//WNDPROC consoleInputWindowProc;
//LRESULT CALLBACK
//ConsoleInputSubclass(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//  char buf[MSG_SIZ];
//  char *p;
//  static BOOL sendNextChar = FALSE;
//  static BOOL quoteNextChar = FALSE;
//  InputSource *is = DIS.consoleInputSource;
//  CHARFORMAT cf;
//  CHARRANGE sel;
//
//  switch (message) {
//  case WM_CHAR:
//    if (!appData.localLineEditing || sendNextChar) {
//      is->buf[0] = (CHAR) wParam;
//      is->count = 1;
//      SendMessage(hwndMain, WM_USER_Input, 0, (LPARAM) is);
//      sendNextChar = FALSE;
//      return 0;
//    }
//    if (quoteNextChar) {
//      buf[0] = (char) wParam;
//      buf[1] = NULLCHAR;
//      SendMessage(hwnd, EM_REPLACESEL, TRUE, (LPARAM) buf);
//      quoteNextChar = FALSE;
//      return 0;
//    }
//    switch (wParam) {
//    case '\r':   /* Enter key */
//      is->count = GetWindowText(hwnd, is->buf, INPUT_SOURCE_BUF_SIZE-1);     
//      if (DIS.consoleEcho) SaveInHistory(is->buf);
//      is->buf[is->count++] = '\n';
//      is->buf[is->count] = NULLCHAR;
//      SendMessage(hwndMain, WM_USER_Input, 0, (LPARAM) is);
//      if (DIS.consoleEcho) {
//	ConsoleOutput(is->buf, is->count, TRUE);
//      } else if (appData.localLineEditing) {
//	ConsoleOutput("\n", 1, TRUE);
//      }
//      /* fall thru */
//    case '\033': /* Escape key */
//      SetWindowText(hwnd, ""); 
//      cf.cbSize = sizeof(CHARFORMAT);
//      cf.dwMask = CFM_COLOR|CFM_BOLD|CFM_ITALIC|CFM_UNDERLINE|CFM_STRIKEOUT;
//      if (DIS.consoleEcho) {
//        cf.crTextColor = DIS.textAttribs[ColorNormal].color;
//      } else {
//	cf.crTextColor = COLOR_ECHOOFF;
//      }
//      cf.dwEffects = DIS.textAttribs[ColorNormal].effects;
//      SendMessage(hwnd, EM_SETCHARFORMAT, SCF_ALL, (LPARAM)&cf);
//      return 0;
//    case '\t':   /* Tab key */
//      if (GetKeyState(VK_SHIFT) < 0) {
//	/* shifted */
//	SetFocus(GetDlgItem(DIS.hwndConsole, OPT_ConsoleText));
//      } else {
//	/* unshifted */
//	if (IsIconic(hwndMain)) ShowWindow(hwndMain, SW_RESTORE);
//	if (DIS.buttonDesc[0].hwnd) {
//	  SetFocus(DIS.buttonDesc[0].hwnd);
//	} else {
//	  SetFocus(hwndMain);
//	}
//      }
//      return 0;
//    case '\023': /* Ctrl+S */
//      sendNextChar = TRUE;
//      return 0;
//    case '\021': /* Ctrl+Q */
//      quoteNextChar = TRUE;
//      return 0;
//    default:
//      break;
//    }
//    break;
//  case WM_KEYDOWN:
//    switch (wParam) {
//    case VK_UP:
//      GetWindowText(hwnd, buf, MSG_SIZ);
//      p = PrevInHistory(buf);
//      if (p != NULL) {
//	SetWindowText(hwnd, p);
//	sel.cpMin = 999999;
//	sel.cpMax = 999999;
//	SendMessage(hwnd, EM_EXSETSEL, 0, (LPARAM)&sel);
//        return 0;
//      }
//      break;
//    case VK_DOWN:
//      p = NextInHistory();
//      if (p != NULL) {
//	SetWindowText(hwnd, p);
//	sel.cpMin = 999999;
//	sel.cpMax = 999999;
//	SendMessage(hwnd, EM_EXSETSEL, 0, (LPARAM)&sel);
//        return 0;
//      }
//      break;
//    case VK_HOME:
//    case VK_END:
//      if (!(GetKeyState(VK_CONTROL) & ~1)) break;
//      /* fall thru */
//    case VK_PRIOR:
//    case VK_NEXT:
//      SendDlgItemMessage(DIS.hwndConsole, OPT_ConsoleText, message, wParam, lParam);
//      return 0;
//    }
//    break;
//  case WM_MBUTTONDOWN:
//    SendDlgItemMessage(DIS.hwndConsole, OPT_ConsoleText, 
//      WM_COMMAND, MAKEWPARAM(IDM_QuickPaste, 0), 0);
//    break;
//  case WM_RBUTTONUP:
//    if (GetKeyState(VK_SHIFT) & ~1) {
//      SendDlgItemMessage(DIS.hwndConsole, OPT_ConsoleText, 
//        WM_COMMAND, MAKEWPARAM(IDM_QuickPaste, 0), 0);
//    } else {
//      POINT pt;
//      HMENU hmenu;
//      hmenu = LoadMenu(hInst, "InputMenu");
//      SendMessage(hwnd, EM_EXGETSEL, 0, (LPARAM)&sel);
//      if (sel.cpMin == sel.cpMax) {
//        EnableMenuItem(hmenu, IDM_Copy, MF_BYCOMMAND|MF_GRAYED);
//        EnableMenuItem(hmenu, IDM_Cut, MF_BYCOMMAND|MF_GRAYED);
//      }
//      if (!IsClipboardFormatAvailable(CF_TEXT)) {
//        EnableMenuItem(hmenu, IDM_Paste, MF_BYCOMMAND|MF_GRAYED);
//      }
//      pt.x = LOWORD(lParam);
//      pt.y = HIWORD(lParam);
//      MenuPopup(hwnd, pt, hmenu, -1);
//    }
//    return 0;
//  case WM_COMMAND:
//    switch (LOWORD(wParam)) { 
//    case IDM_Undo:
//      SendMessage(hwnd, EM_UNDO, 0, 0);
//      return 0;
//    case IDM_SelectAll:
//      sel.cpMin = 0;
//      sel.cpMax = -1; /*999999?*/
//      SendMessage(hwnd, EM_EXSETSEL, 0, (LPARAM)&sel);
//      return 0;
//    case IDM_Cut:
//      SendMessage(hwnd, WM_CUT, 0, 0);
//      return 0;
//    case IDM_Paste:
//      SendMessage(hwnd, WM_PASTE, 0, 0);
//      return 0;
//    case IDM_Copy:
//      SendMessage(hwnd, WM_COPY, 0, 0);
//      return 0;
//    }
//    break;
//  }
//  return (*consoleInputWindowProc)(hwnd, message, wParam, lParam);
//}
//void
//ChangedConsoleFont()
//{
//  CHARFORMAT cfmt;
//  CHARRANGE tmpsel, sel;
//  MyFont *f = DIS.font[DIS.bsize][CONSOLE_FONT];
//
//
//  //HWND hText = GetDlgItem(DIS.hwndConsole, OPT_ConsoleText);
//  //HWND hInput = GetDlgItem(DIS.hwndConsole, OPT_ConsoleInput);
//
//
//  //HWND hText    = DLG.hText;
//  //HWND hInput   = DLG.hInput;
//
//  PARAFORMAT paraf;
//
//  cfmt.cbSize = sizeof(CHARFORMAT);
//  cfmt.dwMask = CFM_FACE|CFM_SIZE|CFM_CHARSET;  
//  StringCbCopy(cfmt.szFaceName,32,DIS.font[DIS.bsize][CONSOLE_FONT]->mfp.faceName);
//  /* yHeight is expressed in twips.  A twip is 1/20 of a font's point
//   * size.  This was undocumented in the version of MSVC++ that I had
//   * when I wrote the code, but is apparently documented now.
//   */
//  cfmt.yHeight = (int)(f->mfp.pointSize * 20.0 + 0.5);
//  cfmt.bCharSet = f->lf.lfCharSet;
//  cfmt.bPitchAndFamily = f->lf.lfPitchAndFamily;
//  SendMessage(DLG.hText, EM_SETCHARFORMAT, SCF_ALL, (LPARAM) &cfmt); 
//  SendMessage(DLG.hInput, EM_SETCHARFORMAT, SCF_ALL, (LPARAM) &cfmt); 
//  /* Why are the following seemingly needed too? */
//  SendMessage(DLG.hText, EM_SETCHARFORMAT, SCF_DEFAULT, (LPARAM) &cfmt); 
//  SendMessage(DLG.hInput, EM_SETCHARFORMAT, SCF_DEFAULT, (LPARAM) &cfmt); 
//  SendMessage(DLG.hText, EM_EXGETSEL, 0, (LPARAM)&sel);
//  tmpsel.cpMin = 0;
//  tmpsel.cpMax = -1; /*999999?*/
//  SendMessage(DLG.hText, EM_EXSETSEL, 0, (LPARAM)&tmpsel);
//  SendMessage(DLG.hText, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM) &cfmt); 
//  /* Trying putting this here too.  It still seems to tickle a RichEdit
//   *  bug: sometimes RichEdit indents the first line of a paragraph too.
//   */
//  paraf.cbSize = sizeof(paraf);
//  paraf.dwMask = PFM_OFFSET | PFM_STARTINDENT;
//  paraf.dxStartIndent = 0;
//  paraf.dxOffset = WRAP_INDENT;
//  SendMessage(DLG.hText, EM_SETPARAFORMAT, 0, (LPARAM) &paraf);
//  SendMessage(DLG.hText, EM_EXSETSEL, 0, (LPARAM)&sel);
//}
//
//WNDPROC consoleTextWindowProc;
//LRESULT CALLBACK		//控制对话框处理程序
//ConsoleWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//  static HWND hText, hInput, hFocus;
//  InputSource *is = DIS.consoleInputSource;
//  RECT rect;
//  static int sizeX, sizeY;
//  int newSizeX, newSizeY;
//  MINMAXINFO *mmi;
//
//  switch (message) {
//  case WM_INITDIALOG: /* message: initialize dialog box */
//    DIS.hwndConsole = hDlg;
//    hText = GetDlgItem(hDlg, OPT_ConsoleText);
//    hInput = GetDlgItem(hDlg, OPT_ConsoleInput);
//    SetFocus(hInput);
//    consoleTextWindowProc = (WNDPROC)(_int64)
//      SetWindowLong(hText, GWL_WNDPROC, (LONG) (_int64)ConsoleTextSubclass);
//    SendMessage(hText, EM_SETBKGNDCOLOR, FALSE, DIS.consoleBackgroundColor);
//    consoleInputWindowProc = (WNDPROC)(_int64)
//      SetWindowLong(hInput, GWL_WNDPROC, (LONG)(_int64) ConsoleInputSubclass);
//    SendMessage(hInput, EM_SETBKGNDCOLOR, FALSE, DIS.consoleBackgroundColor);
//    Colorize(ColorNormal, TRUE);
//    SendMessage(hInput, EM_SETCHARFORMAT, SCF_ALL, (LPARAM) &DIS.consoleCF);
//    ChangedConsoleFont();
//    GetClientRect(hDlg, &rect);
//    sizeX = rect.right;
//    sizeY = rect.bottom;
// //   if (DIS.consoleX != CW_USEDEFAULT && DIS.consoleY != CW_USEDEFAULT &&
//	//DIS.consoleW != CW_USEDEFAULT && DIS.consoleH != CW_USEDEFAULT) {
// //     WINDOWPLACEMENT wp;
// //     EnsureOnScreen(&DIS.consoleX, &DIS.consoleY);
// //     wp.length = sizeof(WINDOWPLACEMENT);
// //     wp.flags = 0;
// //     wp.showCmd = SW_SHOW;
// //     wp.ptMaxPosition.x = wp.ptMaxPosition.y = 0;
// //     wp.rcNormalPosition.left = DIS.consoleX;
// //     wp.rcNormalPosition.right = DIS.consoleX + DIS.consoleW;
// //     wp.rcNormalPosition.top = DIS.consoleY;
// //     wp.rcNormalPosition.bottom = DIS.consoleY + DIS.consoleH;
// //     SetWindowPlacement(hDlg, &wp);
// //   }
//    return FALSE;
//
//  case WM_SETFOCUS:
//    SetFocus(hInput);
//    return 0;
//
//  case WM_CLOSE:
//    ExitEvent(0);
//    /* not reached */
//    break;
//
//  case WM_SIZE:
//    if (IsIconic(hDlg)) break;
//    newSizeX = LOWORD(lParam);
//    newSizeY = HIWORD(lParam);
//    if (sizeX != newSizeX || sizeY != newSizeY) {
//      RECT rectText, rectInput;
//      POINT pt;
//      int newTextHeight, newTextWidth;
//      GetWindowRect(hText, &rectText);
//      newTextWidth = rectText.right - rectText.left + newSizeX - sizeX;
//      newTextHeight = rectText.bottom - rectText.top + newSizeY - sizeY;
//      if (newTextHeight < 0) {
//	newSizeY += -newTextHeight;
//        newTextHeight = 0;
//      }
//      SetWindowPos(hText, NULL, 0, 0,
//	newTextWidth, newTextHeight, SWP_NOZORDER|SWP_NOMOVE);
//      GetWindowRect(hInput, &rectInput); /* gives screen coords */
//      pt.x = rectInput.left;
//      pt.y = rectInput.top + newSizeY - sizeY;
//      ScreenToClient(hDlg, &pt);
//      SetWindowPos(hInput, NULL, 
//	pt.x, pt.y, /* needs client coords */	
//	rectInput.right - rectInput.left + newSizeX - sizeX,
//	rectInput.bottom - rectInput.top, SWP_NOZORDER);
//    }
//	sizeX = newSizeX;
//	sizeY = newSizeY;
//    break;
//
//  case WM_GETMINMAXINFO:
//    /* Prevent resizing window too small */
//    mmi = (MINMAXINFO *) lParam;
//    mmi->ptMinTrackSize.x = 100;
//    mmi->ptMinTrackSize.y = 100;
//    break;
//  }
//  //return DefWindowProc(hDlg, message, wParam, lParam);
//  return false;
//}
//

//void
//ConsoleCreate(){
//  //HWND hCons;
//  if (DIS.hwndConsole) return; //"WBCONSOLE"
//  //hCons = CreateDialog(hInst, szConsoleName, 0, NULL);
//
//         //  FARPROC lpProc = MakeProcInstance((FARPROC)DLG_BOOK_PROC,hInst);
//         //DLG.dlgBook = CreateDialog(hInst,MAKEINTRESOURCE(DLG_BOOK),hwndMain,(DLGPROC)lpProc);
//
//  //FARPROC lpProc = MakeProcInstance((FARPROC)ConsoleWndProc,hInst);
//
//  FARPROC lpProc = MakeProcInstance((FARPROC)ConsoleWndProc,hInst);
//
//  //hCons = CreateDialog(hInst,MAKEINTRESOURCE(DLG_InterPlay),hwndMain,(DLGPROC)lpProc);
//
//  FreeProcInstance(lpProc);
//
//  //HWND test = hCons;
//  //SendMessage(hCons, WM_INITDIALOG, 0, 0);
//}

//
//void
//ConsoleOutput(char* data, int length, int forceVisible){
//  HWND hText;
//  int trim, exlen;
//  char *p, *q;
//  char buf[CO_MAX+1];
//  POINT pEnd;
//  RECT rect;
//  static int delayLF = 0;
//  CHARRANGE savesel, sel;
//
//  if (DIS.hwndConsole == NULL || length > CO_MAX-100 || length == 0) return;
//  p = data;
//  q = buf;
//  if (delayLF) {
//    *q++ = '\r';
//    *q++ = '\n';
//    delayLF = 0;
//  }
//  while (length--) {
//    if (*p == '\n') {
//      if (*++p) {
//	*q++ = '\r';
//	*q++ = '\n';
//      } else {
//	delayLF = 1;
//      }
//    } else if (*p == '\007') {
//       MyPlaySound(&DIS.sounds[(int)SoundBell]);
//       p++;
//    } else {
//      *q++ = *p++;
//    }
//  }
//  *q = NULLCHAR;
//  hText = GetDlgItem(DIS.hwndConsole, OPT_ConsoleText);
//  SendMessage(hText, EM_HIDESELECTION, TRUE, FALSE);
//  /* Save current selection */
//  SendMessage(hText, EM_EXGETSEL, 0, (LPARAM)&savesel);
//  exlen = GetWindowTextLength(hText);
//  /* Find out whether current end of text is visible */
//  SendMessage(hText, EM_GETRECT, 0, (LPARAM) &rect);
//  SendMessage(hText, EM_POSFROMCHAR, (WPARAM) &pEnd, exlen);
//  /* Trim existing text if it's too long */
//  if (exlen + (q - buf) > CO_MAX) {
//    trim = (int)((CO_TRIM > (q - buf)) ? CO_TRIM : (q - buf));
//    sel.cpMin = 0;
//    sel.cpMax = trim;
//    SendMessage(hText, EM_EXSETSEL, 0, (LPARAM)&sel);
//    SendMessage(hText, EM_REPLACESEL, 0, (LPARAM)"");
//    exlen -= trim;
//    savesel.cpMin -= trim;
//    savesel.cpMax -= trim;
//    if (exlen < 0) exlen = 0;
//    if (savesel.cpMin < 0) savesel.cpMin = 0;
//    if (savesel.cpMax < savesel.cpMin) savesel.cpMax = savesel.cpMin;
//  }
//  /* Append the new text */
//  sel.cpMin = exlen;
//  sel.cpMax = exlen;
//  SendMessage(hText, EM_EXSETSEL, 0, (LPARAM)&sel);
//  SendMessage(hText, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&DIS.consoleCF);
//  SendMessage(hText, EM_REPLACESEL, 0, (LPARAM) buf);
//  if (forceVisible || exlen == 0 ||
//      (rect.left <= pEnd.x && pEnd.x < rect.right &&
//       rect.top <= pEnd.y && pEnd.y < rect.bottom)) {
//    /* Scroll to make new end of text visible if old end of text
//       was visible or new text is an echo of user typein */
//    sel.cpMin = 9999999;
//    sel.cpMax = 9999999;
//    SendMessage(hText, EM_EXSETSEL, 0, (LPARAM)&sel);
//    SendMessage(hText, EM_HIDESELECTION, FALSE, FALSE);
//    SendMessage(hText, EM_SCROLLCARET, 0, 0);
//    SendMessage(hText, EM_HIDESELECTION, TRUE, FALSE);
//  }
//  if (savesel.cpMax == exlen || forceVisible) {
//    /* Move insert point to new end of text if it was at the old
//       end of text or if the new text is an echo of user typein */
//    sel.cpMin = 9999999;
//    sel.cpMax = 9999999;
//    SendMessage(hText, EM_EXSETSEL, 0, (LPARAM)&sel);
//  } else {
//    /* Restore previous selection */
//    SendMessage(hText, EM_EXSETSEL, 0, (LPARAM)&savesel);
//  }
//  SendMessage(hText, EM_HIDESELECTION, FALSE, FALSE);
//}
//

//void
//EchoOn()
//{
//  HWND hInput;
//  DIS.consoleEcho = TRUE;
//  hInput = GetDlgItem(DIS.hwndConsole, OPT_ConsoleInput);
//  SendMessage(hInput, EM_SETCHARFORMAT, SCF_ALL, (LPARAM)&DIS.consoleCF);
//  SendMessage(hInput, EM_SETBKGNDCOLOR, FALSE, DIS.consoleBackgroundColor);
//}
//
//
//void
//EchoOff()
//{
//  CHARFORMAT cf;
//  HWND hInput;
//  DIS.consoleEcho = FALSE;
//  hInput = GetDlgItem(DIS.hwndConsole, OPT_ConsoleInput);
//  /* This works OK: set text and background both to the same color */
//  cf = DIS.consoleCF;
//  cf.crTextColor = COLOR_ECHOOFF;
//  SendMessage(hInput, EM_SETCHARFORMAT, SCF_ALL, (LPARAM)&cf);
//  SendMessage(hInput, EM_SETBKGNDCOLOR, FALSE, cf.crTextColor);
//}
//LRESULT CALLBACK 
//ConsoleTextSubclass(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
//  HWND hInput;
//  CHARRANGE sel;
//
//  switch (message) {
//  case WM_KEYDOWN:
//    if (!(GetKeyState(VK_CONTROL) & ~1)) break;
//    switch (wParam) {
//    case VK_PRIOR:
//      SendMessage(hwnd, EM_LINESCROLL, 0, -999999);
//      return 0;
//    case VK_NEXT:
//      sel.cpMin = 999999;
//      sel.cpMax = 999999;
//      SendMessage(hwnd, EM_EXSETSEL, 0, (LPARAM)&sel);
//      SendMessage(hwnd, EM_SCROLLCARET, 0, 0);
//      return 0;
//    }
//    break;
//  case WM_CHAR:
//    if (wParam == '\t') {
//      if (GetKeyState(VK_SHIFT) < 0) {
//	/* shifted */
//	if (IsIconic(hwndMain)) ShowWindow(hwndMain, SW_RESTORE);
//	if (DIS.buttonDesc[0].hwnd) {
//	  SetFocus(DIS.buttonDesc[0].hwnd);
//	} else {
//	  SetFocus(hwndMain);
//	}
//      } else {
//	/* unshifted */
//	SetFocus(GetDlgItem(DIS.hwndConsole, OPT_ConsoleInput));
//      }
//    } else {
//      hInput = GetDlgItem(DIS.hwndConsole, OPT_ConsoleInput);
//      SetFocus(hInput);
//      SendMessage(hInput, message, wParam, lParam);
//    }
//    return 0;
//  case WM_PASTE:
//    hInput = GetDlgItem(DIS.hwndConsole, OPT_ConsoleInput);
//    SetFocus(hInput);
//    return SendMessage(hInput, message, wParam, lParam);
//  case WM_MBUTTONDOWN:
//    return SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(IDM_QuickPaste, 0), 0);
//  case WM_RBUTTONDOWN:
//    if (!(GetKeyState(VK_SHIFT) & ~1)) {
//      /* Move selection here if it was empty */
//      POINT pt;
//      pt.x = LOWORD(lParam);
//      pt.y = HIWORD(lParam);
//      SendMessage(hwnd, EM_EXGETSEL, 0, (LPARAM)&sel);
//      if (sel.cpMin == sel.cpMax) {
//        sel.cpMin = (LONG)SendMessage(hwnd, EM_CHARFROMPOS, 0, (LPARAM)&pt); /*doc is wrong*/
//	sel.cpMax = sel.cpMin;
//	SendMessage(hwnd, EM_EXSETSEL, 0, (LPARAM)&sel);
//      }
//      SendMessage(hwnd, EM_HIDESELECTION, FALSE, FALSE);
//    }
//    return 0;
//  case WM_RBUTTONUP:
//    if (GetKeyState(VK_SHIFT) & ~1) {
//      SendDlgItemMessage(DIS.hwndConsole, OPT_ConsoleText, 
//        WM_COMMAND, MAKEWPARAM(IDM_QuickPaste, 0), 0);
//    } else {
//      POINT pt;
//      HMENU hmenu = LoadIcsTextMenu(DIS.icsTextMenuEntry);
//      SendMessage(hwnd, EM_EXGETSEL, 0, (LPARAM)&sel);
//      if (sel.cpMin == sel.cpMax) {
//        EnableMenuItem(hmenu, IDM_Copy, MF_BYCOMMAND|MF_GRAYED);
//        EnableMenuItem(hmenu, IDM_QuickPaste, MF_BYCOMMAND|MF_GRAYED);
//      }
//      if (!IsClipboardFormatAvailable(CF_TEXT)) {
//        EnableMenuItem(hmenu, IDM_Paste, MF_BYCOMMAND|MF_GRAYED);
//      }
//      pt.x = LOWORD(lParam);
//      pt.y = HIWORD(lParam);
//      MenuPopup(hwnd, pt, hmenu, -1);
//    }
//    return 0;
//  case WM_COMMAND:
//    switch (LOWORD(wParam)) {
//    case IDM_QuickPaste:
//      {
//        SendMessage(hwnd, EM_EXGETSEL, 0, (LPARAM)&sel);
//	if (sel.cpMin == sel.cpMax) {
//	  MessageBeep(MB_ICONEXCLAMATION);
//          return 0;
//	}
//	SendMessage(hwnd, WM_COPY, 0, 0);
//	hInput = GetDlgItem(DIS.hwndConsole, OPT_ConsoleInput);
//        SendMessage(hInput, WM_PASTE, 0, 0);
//        SetFocus(hInput);
//        return 0;
//      }
//    case IDM_Cut:
//      SendMessage(hwnd, WM_CUT, 0, 0);
//      return 0;
//    case IDM_Paste:
//      SendMessage(hwnd, WM_PASTE, 0, 0);
//      return 0;
//    case IDM_Copy:
//      SendMessage(hwnd, WM_COPY, 0, 0);
//      return 0;
//    default:
//      {
//	int i = LOWORD(wParam) - IDM_CommandX;
//	if (i >= 0 && i < ICS_TEXT_MENU_SIZE &&
//	    DIS.icsTextMenuEntry[i].command != NULL) {
//	 CommandX(hwnd, DIS.icsTextMenuEntry[i].command,
//		   DIS.icsTextMenuEntry[i].getname,
//		   DIS.icsTextMenuEntry[i].immediate);
//	  return 0;
//	}
//      }
//      break;
//    }
//    break;
//  }
//  return (*consoleTextWindowProc)(hwnd, message, wParam, lParam);
//}
