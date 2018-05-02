#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

void 
LoadGameDialog(HWND hwnd, char* title){
	//UINT number = 0;
	//FILE *f;
	//char fileTitle[MSG_SIZ];
	//f = OpenFileDialog(hwnd, FALSE, "",
	//	appData.oldSaveStyle ? "gam" : "pgn",
	//	GAME_FILT,title, &number, fileTitle, NULL);
	//if (f != NULL) {
	//	DIS.cmailMsgLoaded = FALSE;
	//	if (number == 0) {
	//		int error = GameListBuild(f);
	//		if (error) {
	//			DisplayError("Cannot build game list", error);
	//		}
	//		else if (!ListEmpty(&DIS.gameList) &&
	//			((ListGame *) DIS.gameList.tailPred)->number > 1) {
	//				GameListPopUp(f, fileTitle);
	//				return;
	//		}
	//		GameListDestroy();
	//		number = 1;
	//	}
	//	LoadGame(f, number, fileTitle, FALSE);
	//}
}
