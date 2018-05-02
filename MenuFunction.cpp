#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

//void
//HistorySet(char movelist[][2*MOVE_LEN], int first, int last, int current){
//  /* Currently not implemented in WinBoard */
//}


void 
FreezeUI(void){
	/*
	* Setting "frozen" should disable all user input other than deleting
	* the window.  We do this while engines are initializing themselves.
	* 当引擎初始化时,忽略所有的用户服务命令输入
	*/
	HMENU hmenu;
	int i;
	if (appData.Afrozen) return;
	appData.Afrozen = true;
	//hmenu = GetMenu(hwndMain);
    hmenu = GetMenu(OBS[0]->hwndThis);
	for (i=0; i<MENU_BAR_ITEMS; i++) {
		appData.oldMenuItemState[i] = EnableMenuItem(hmenu, i, MF_BYPOSITION|MF_GRAYED);
	}
	DrawMenuBar(OBS[0]->hwndThis);
}
void /* Undo a FreezeUI */
ThawUI(void){
  HMENU hmenu;
  int i;

  if (!appData.Afrozen) return;
  appData.Afrozen = false;
  hmenu = GetMenu(OBS[0]->hwndThis);
  for (i=0; i<MENU_BAR_ITEMS; i++) {
    EnableMenuItem(hmenu, i, MF_BYPOSITION|appData.oldMenuItemState[i]);
  }
  DrawMenuBar(OBS[0]->hwndThis);
}


void
ModeHighlight()
{
 // static UINT prevChecked = 0;
 // static int prevPausing = 0;
 // UINT nowChecked;

 // if (DIS.pausing != prevPausing) {
 //   prevPausing = DIS.pausing;
 //   (void) CheckMenuItem(GetMenu(hwndMain), IDM_Pause,
	//		 MF_BYCOMMAND|(DIS.pausing ? MF_CHECKED : MF_UNCHECKED));
 //   if (DIS.hwndPause) SetWindowText(DIS.hwndPause, DIS.pausing ? "C" : "P");
 // }

 // switch (DIS.gameMode) {
 // case BeginningOfGame:
 //   if (appData.icsActive)
 //     nowChecked = IDM_IcsClient;
 //   else if (appData.noChessProgram)
 //     nowChecked = IDM_EditGame;
	//else{
 //     nowChecked = IDM_MachineBlack;
	//}
 //   break;
 // case MachinePlaysBlack:
 //   nowChecked = IDM_MachineBlack;
 //   break;
 // case MachinePlaysWhite:
 //   nowChecked = IDM_MachineWhite;
 //   break;
 // case TwoMachinesPlay:
 //   nowChecked = IDM_TwoMachines;
 //   break;
 // case AnalyzeMode:
 //   nowChecked = IDM_AnalysisMode;
 //   break;
 // case AnalyzeFile:
 //   nowChecked = IDM_AnalyzeFile;
 //   break;
 // case EditGame:
 //   nowChecked = IDM_EditGame;
 //   break;
 // case PlayFromGameFile:
 //   nowChecked = IDM_LoadGame;
 //   break;
 // case EditPosition:
 //   nowChecked = IDM_EditPosition;
 //   break;
 // case Training:
 //   nowChecked = IDM_Training;
 //   break;
 // case IcsPlayingWhite:
 // case IcsPlayingBlack:
 // case IcsObserving:
 // case IcsIdle:
 //   nowChecked = IDM_IcsClient;
 //   break;
 // default:
 // case EndOfGame:
 //   nowChecked = 0;
 //   break;
 // }
 // if (prevChecked != 0)
 //   (void) CheckMenuItem(GetMenu(hwndMain),
	//		 prevChecked, MF_BYCOMMAND|MF_UNCHECKED);
 // if (nowChecked != 0)
 //   (void) CheckMenuItem(GetMenu(hwndMain),
	//		 nowChecked, MF_BYCOMMAND|MF_CHECKED);

 // if (nowChecked == IDM_LoadGame || nowChecked == IDM_Training) {
 //   (void) EnableMenuItem(GetMenu(hwndMain), IDM_Training, 
	//		  MF_BYCOMMAND|MF_ENABLED);
 // } else {
 //   (void) EnableMenuItem(GetMenu(hwndMain), 
	//		  IDM_Training, MF_BYCOMMAND|MF_GRAYED);
 // }

 // prevChecked = nowChecked;
}



void
SetMenuEnables(HMENU hmenu, Enables *enab)
{
  while (enab->item > 0) {
    (void) EnableMenuItem(hmenu, enab->item, enab->flags);
    enab++;
  }
}


void
InitMenuChecks(){
  HMENU hmenu = GetMenu(OBS[0]->hwndThis);

   //通讯菜单
   //EnableMenuItem(hmenu,
   //   IDM_CommPort,
   //   MF_BYCOMMAND|((appData.icsActive &&*appData.icsCommPort != NULLCHAR) ? MF_ENABLED : MF_GRAYED));

   //退出时是不是保存菜单
   CheckMenuItem(hmenu, IDM_SaveSettingsOnExit,
	   MF_BYCOMMAND|(appData.AsaveSettingsOnExit ? MF_CHECKED : MF_UNCHECKED));
}
void
SetupDropMenu(HMENU hmenu){
 // int i, count, enable;
 // char *p;
 // //extern char white_holding[], black_holding[];
 // char item[MSG_SIZ];

 // for (i=0; i<dropEnNum; i++) {
 //   p = strchr(DIS.gameMode == IcsPlayingWhite ? DIS.white_holding : DIS.black_holding,
	//       DIS.dropEnables[i].piece);
 //   count = 0;
	//while (p && *p++ == DIS.dropEnables[i].piece){
	//	count++;
	//}
 //   //sprintf(item, "%s  %d", dropEnables[i].name, count);
	//StringCbPrintf(item,MSG_SIZ,"%s  %d", DIS.dropEnables[i].name, count);
 //   enable = count > 0 || !appData.testLegality
 //     /*!!temp:*/ || (DIS.pgn.variant == VariantCrazyhouse
	//	      && !appData.icsActive);
 //   ModifyMenu(hmenu, DIS.dropEnables[i].command,
	//       MF_BYCOMMAND | (enable ? MF_ENABLED : MF_GRAYED) | MF_STRING,
	//       DIS.dropEnables[i].command, item);
 // }
}



void APIENTRY
MenuPopup(HWND hwnd, POINT pt, HMENU hmenu, UINT def)
{
  HMENU hmenuTrackPopup;	/* floating pop-up menu  */

  /*
   * Get the first pop-up menu in the menu template. This is the
   * menu that TrackPopupMenu displays.
   */
  hmenuTrackPopup = GetSubMenu(hmenu, 0);

  SetMenuDefaultItem(hmenuTrackPopup, def, FALSE);

  /*
   * TrackPopup uses screen coordinates, so convert the
   * coordinates of the mouse click to screen coordinates.
   */
  ClientToScreen(hwnd, (LPPOINT) &pt);

  /* Draw and track the floating pop-up menu. */
  TrackPopupMenu(hmenuTrackPopup, TPM_CENTERALIGN | TPM_RIGHTBUTTON,
		 pt.x, pt.y, 0, hwnd, NULL);

  /* Destroy the menu.*/
  DestroyMenu(hmenu);
}




void
ParseIcsTextMenu(char *icsTextMenuString)
{
 // int flags = 0;
 // IcsTextMenuEntry *e = DIS.icsTextMenuEntry;
 // char *p = icsTextMenuString;
 // while (e->item != NULL && e < DIS.icsTextMenuEntry + ICS_TEXT_MENU_SIZE) {
 //   free(e->item);
 //   e->item = NULL;
 //   if (e->command != NULL) {
 //     free(e->command);
 //     e->command = NULL;
 //   }
 //   e++;
 // }
 // e = DIS.icsTextMenuEntry;
 // while (*p && e < DIS.icsTextMenuEntry + ICS_TEXT_MENU_SIZE) {
 //   if (*p == ';' || *p == '\n') {
 //     e->item = _strdup("-");
 //     e->command = NULL;
 //     p++;
 //   } else if (*p == '-') {
 //     e->item = _strdup("-");
 //     e->command = NULL;
 //     p++;
 //     if (*p) p++;
 //   } else {
 //     char *q, *r, *s, *t;
 //     char c;
 //     q = strchr(p, ',');
 //     if (q == NULL) break;
 //     *q = NULLCHAR;
 //     r = strchr(q + 1, ',');
 //     if (r == NULL) break;
 //     *r = NULLCHAR;
 //     s = strchr(r + 1, ',');
 //     if (s == NULL) break;
 //     *s = NULLCHAR;
 //     c = ';';
 //     t = strchr(s + 1, c);
 //     if (t == NULL) {
	//c = '\n';
	//t = strchr(s + 1, c);
 //     }
 //     if (t != NULL) *t = NULLCHAR;
 //     e->item = _strdup(p);
 //     e->command = _strdup(q + 1);
 //     e->getname = *(r + 1) != '0';
 //     e->immediate = *(s + 1) != '0';
 //     *q = ',';
 //     *r = ',';
 //     *s = ',';
 //     if (t == NULL) break;
 //     *t = c;
 //     p = t + 1;
 //   }
 //   e++;
 // } 
}

HMENU
LoadIcsTextMenu(IcsTextMenuEntry *e){
    HMENU hmenu, h;
    int i = 0;
    hmenu = LoadMenu(hInst, "TextMenu");
    h = GetSubMenu(hmenu, 0);
    while (e->item) {
        if (strcmp(e->item, "-") == 0) {
            AppendMenu(h, MF_SEPARATOR, 0, 0);
        } 
        else {
            if (e->item[0] == '|') {
                AppendMenu(h, MF_STRING|MF_MENUBARBREAK,
                    IDM_CommandX + i, &e->item[1]);
            } 
            else {
                AppendMenu(h, MF_STRING, IDM_CommandX + i, e->item);
            }
        }
        e++;
        i++;
    } 
    return hmenu;
}