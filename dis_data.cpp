#include "stdafx.h"
#include "chess.h"
#include "data.h"

SizeInfo sizeInfo[] = {
  { L"tiny",     21, 1, 1, 1, 199, 251 },		//0
  { L"teeny",    25, 1, 1, 1, 235, 291 },
  { L"dinky",    29, 1, 1, 1, 271, 331 },
  { L"petite",   33, 1, 1, 1, 361, 428 },
  { L"slim",     37, 2, 1, 0, 388, 458 },
  { L"small",    40, 2, 1, 0, 433, 508 },
  { L"mediocre", 45, 2, 1, 0, 469, 548 },
  { L"middling", 49, 2, 0, 0, 514, 598 },
  { L"average",  54, 2, 0, 0, 560, 649 },
  { L"moderate", 58, 3, 0, 0, 614, 709 },
  { L"medium",   64, 3, 0, 0, 686, 789 },
  { L"bulky",    72, 3, 0, 0, 758, 869 },
  { L"large",    80, 3, 0, 0, 821, 939 },
  { L"big",      87, 3, 0, 0, 893, 1019 },
  { L"huge",     95, 3, 0, 0, 1010,1149 },
  { L"giant",    108, 3, 0, 0,1092,1240 },
  { L"colossal", 116, 4, 0, 0,1209,1370 },
  { L"titanic",  129, 4, 0, 0, 0, 0 },
  { NULL, 0, 0, 0, 0, 0, 0 }
};

MyFont fontRec[NUM_SIZES][NUM_FONTS] =
{
  { MF(CLOCK_FONT_TINY), MF(MESSAGE_FONT_TINY), 
    MF(COORD_FONT_TINY), MF(CONSOLE_FONT_TINY),
    MF(COMMENT_FONT_TINY), MF(EDITTAGS_FONT_TINY) },
  { MF(CLOCK_FONT_TEENY), MF(MESSAGE_FONT_TEENY), 
    MF(COORD_FONT_TEENY), MF(CONSOLE_FONT_TEENY),
    MF(COMMENT_FONT_TEENY), MF(EDITTAGS_FONT_TEENY) },
  { MF(CLOCK_FONT_DINKY), MF(MESSAGE_FONT_DINKY),
    MF(COORD_FONT_DINKY), MF(CONSOLE_FONT_DINKY),
    MF(COMMENT_FONT_DINKY), MF(EDITTAGS_FONT_DINKY) },
  { MF(CLOCK_FONT_PETITE), MF(MESSAGE_FONT_PETITE),
    MF(COORD_FONT_PETITE), MF(CONSOLE_FONT_PETITE),
    MF(COMMENT_FONT_PETITE), MF(EDITTAGS_FONT_PETITE) },
  { MF(CLOCK_FONT_SLIM), MF(MESSAGE_FONT_SLIM),
    MF(COORD_FONT_SLIM), MF(CONSOLE_FONT_SLIM),
    MF(COMMENT_FONT_SLIM), MF(EDITTAGS_FONT_SLIM) },
  { MF(CLOCK_FONT_SMALL), MF(MESSAGE_FONT_SMALL),
    MF(COORD_FONT_SMALL), MF(CONSOLE_FONT_SMALL),
    MF(COMMENT_FONT_SMALL), MF(EDITTAGS_FONT_SMALL) },
  { MF(CLOCK_FONT_MEDIOCRE), MF(MESSAGE_FONT_MEDIOCRE),
    MF(COORD_FONT_MEDIOCRE), MF(CONSOLE_FONT_MEDIOCRE),
    MF(COMMENT_FONT_MEDIOCRE), MF(EDITTAGS_FONT_MEDIOCRE) },
  { MF(CLOCK_FONT_MIDDLING), MF(MESSAGE_FONT_MIDDLING),
    MF(COORD_FONT_MIDDLING), MF(CONSOLE_FONT_MIDDLING),
    MF(COMMENT_FONT_MIDDLING), MF(EDITTAGS_FONT_MIDDLING) },
  { MF(CLOCK_FONT_AVERAGE), MF(MESSAGE_FONT_AVERAGE),
    MF(COORD_FONT_AVERAGE), MF(CONSOLE_FONT_AVERAGE),
    MF(COMMENT_FONT_AVERAGE), MF(EDITTAGS_FONT_AVERAGE) },
  { MF(CLOCK_FONT_MODERATE), MF(MESSAGE_FONT_MODERATE),
    MF(COORD_FONT_MODERATE), MF(CONSOLE_FONT_MODERATE),
    MF(COMMENT_FONT_MODERATE), MF(EDITTAGS_FONT_MODERATE) },
  { MF(CLOCK_FONT_MEDIUM), MF(MESSAGE_FONT_MEDIUM),
    MF(COORD_FONT_MEDIUM), MF(CONSOLE_FONT_MEDIUM),
    MF(COMMENT_FONT_MEDIUM), MF(EDITTAGS_FONT_MEDIUM) },
  { MF(CLOCK_FONT_BULKY), MF(MESSAGE_FONT_BULKY),
    MF(COORD_FONT_BULKY), MF(CONSOLE_FONT_BULKY),
    MF(COMMENT_FONT_BULKY), MF(EDITTAGS_FONT_BULKY) },
  { MF(CLOCK_FONT_LARGE), MF(MESSAGE_FONT_LARGE),
    MF(COORD_FONT_LARGE), MF(CONSOLE_FONT_LARGE),
    MF(COMMENT_FONT_LARGE), MF(EDITTAGS_FONT_LARGE) },
  { MF(CLOCK_FONT_BIG), MF(MESSAGE_FONT_BIG),
    MF(COORD_FONT_BIG), MF(CONSOLE_FONT_BIG),
    MF(COMMENT_FONT_BIG), MF(EDITTAGS_FONT_BIG) },
  { MF(CLOCK_FONT_HUGE), MF(MESSAGE_FONT_HUGE),
    MF(COORD_FONT_HUGE), MF(CONSOLE_FONT_HUGE),
    MF(COMMENT_FONT_HUGE), MF(EDITTAGS_FONT_HUGE) },
  { MF(CLOCK_FONT_GIANT), MF(MESSAGE_FONT_GIANT),
    MF(COORD_FONT_GIANT), MF(CONSOLE_FONT_GIANT),
    MF(COMMENT_FONT_GIANT), MF(EDITTAGS_FONT_GIANT) },
  { MF(CLOCK_FONT_COLOSSAL), MF(MESSAGE_FONT_COLOSSAL),
    MF(COORD_FONT_COLOSSAL), MF(CONSOLE_FONT_COLOSSAL),
    MF(COMMENT_FONT_COLOSSAL), MF(EDITTAGS_FONT_COLOSSAL) },
  { MF(CLOCK_FONT_TITANIC), MF(MESSAGE_FONT_TITANIC),
    MF(COORD_FONT_TITANIC), MF(CONSOLE_FONT_TITANIC),
    MF(COMMENT_FONT_TITANIC), MF(EDITTAGS_FONT_TITANIC) },
};

//MyButtonDesc buttonDesc[N_BUTTONS] =
//{
//	{"1",  IDM_ToStart, NULL, NULL},
//	{"2",  IDM_ToStart, NULL, NULL},
//	{"3",  IDM_ToStart, NULL, NULL},
//	{"4",  IDM_ToStart, NULL, NULL},
//	{"5",  IDM_ToStart, NULL, NULL},
//	{"<<", IDM_ToStart, NULL, NULL},
//	{"<<", IDM_ToStart, NULL, NULL},
//	{"<",  IDM_Backward, NULL, NULL},
//	{"P",  IDM_Pause, NULL, NULL},
//	{">",  IDM_Forward, NULL, NULL},
//	{">>", IDM_ToEnd, NULL, NULL},
//};

MyColorizeAttribs colorizeAttribs[] = {
  { (COLORREF)0, 0, _T("Shout Text") },
  { (COLORREF)0, 0, _T("SShout/CShout") },
  { (COLORREF)0, 0, _T("Channel 1 Text") },
  { (COLORREF)0, 0, _T("Channel Text") },
  { (COLORREF)0, 0, _T("Kibitz Text") },
  { (COLORREF)0, 0, _T("Tell Text") },
  { (COLORREF)0, 0, _T("Challenge Text") },
  { (COLORREF)0, 0, _T("Request Text") },
  { (COLORREF)0, 0, _T("Seek Text") },
  { (COLORREF)0, 0, _T("Normal Text") },
  { (COLORREF)0, 0, _T("None") }
};

//char *menuBarText[2][MENU_BAR_ITEMS+1] = {
//  { "&File", "&Mode", "&Action", "&Step", "&Options", "&Help", NULL },
//  { "&F", "&M", "&A", "&S", "&O", "&H", NULL },
//};
//
//DropEnable dropEnables[dropEnNum] = {
//  { 'P', 1, "Pawn" },
//  { 'N', 2, "Knight" },
//  { 'B', 3, "Bishop" },
//  { 'R', 4, "Rook" },
//  { 'Q', 5, "Queen" },
//};

TCHAR *defaultTextAttribs[] = 
{
  COLOR_SHOUT, COLOR_SSHOUT, COLOR_CHANNEL1, COLOR_CHANNEL, COLOR_KIBITZ,
  COLOR_TELL, COLOR_CHALLENGE, COLOR_REQUEST, COLOR_SEEK, COLOR_NORMAL,
  COLOR_NONE
};

ArgDescriptor argDescriptors[] = {
  /* positional arguments */

  { L"notUse", ArgNone, NULL },
  { L"whitePieceColor", ArgColor, (LPVOID)&appData.AwhitePieceColor, TRUE },
  { L"blackPieceColor", ArgColor, (LPVOID)&appData.AblackPieceColor, TRUE },
  { L"lightSquareColor", ArgColor, (LPVOID)&appData.AlightSquareColor, TRUE },
  { L"darkSquareColor", ArgColor, (LPVOID)&appData.AdarkSquareColor, TRUE },
  { L"highlightSquareColor", ArgColor, (LPVOID)&appData.AhighlightSquareColor, TRUE },
  { L"premoveHighlightColor", ArgColor, (LPVOID)&appData.ApremoveHighlightColor, TRUE },

  { L"timeDelay", ArgFloat, (LPVOID)&appData.timeDelay, TRUE },
  { L"internetChessServerMode", ArgBoolean, (LPVOID)&appData.icsActive, FALSE },	//象棋服务状态   
  { L"useTelnet", ArgBoolean, (LPVOID)&appData.useTelnet, FALSE },


  //{ "saveGameFile", ArgFilename, (LPVOID) &appData.saveGameFile, TRUE },

  { L"autoSaveGames", ArgBoolean, (LPVOID)&appData.autoSaveGames, TRUE },

  //{ "loadPositionFile", ArgFilename, (LPVOID) &appData.loadPositionFile, FALSE },


  //{ "loadPositionIndex", ArgInt, (LPVOID) &appData.loadPositionIndex, FALSE },

  //{ "savePositionFile", ArgFilename, (LPVOID) &appData.savePositionFile, FALSE },

  //{ "matchMode", ArgBoolean, (LPVOID) &appData.matchMode,		FALSE },

  //{ "matchGames", ArgInt,	 (LPVOID) &appData.matchGames,		FALSE },

  { L"showCoords", ArgBoolean, (LPVOID)&appData.showCoords, TRUE },

  { L"showThinking", ArgBoolean, (LPVOID)&appData.showThinking, TRUE },

  { L"ponderNextMove", ArgBoolean, (LPVOID)&appData.ponderNextMove, TRUE },		//后台思考
  { L"periodicUpdates", ArgBoolean, (LPVOID)&appData.periodicUpdates, TRUE },		//定期更新


  { L"popupExitMessage", ArgBoolean, (LPVOID)&appData.popupExitMessage, TRUE },

  { L"popUpErrors", ArgBoolean, (LPVOID)&appData.popupMoveErrors,
    FALSE }, /* only so that old WinBoard.ini files from betas can be read */
	{ L"clockFont", ArgFont, (LPVOID)CLOCK_FONT, TRUE },
	{ L"messageFont", ArgFont, (LPVOID)MESSAGE_FONT, TRUE },
	{ L"coordFont", ArgFont, (LPVOID)COORD_FONT, TRUE },
	{ L"tagsFont", ArgFont, (LPVOID)EDITTAGS_FONT, TRUE },
	{ L"commentFont", ArgFont, (LPVOID)COMMENT_FONT, TRUE },
	{ L"icsFont", ArgFont, (LPVOID)CONSOLE_FONT, TRUE },
	{ L"boardSize", ArgBoardSize, (LPVOID)&appData.bsize, TRUE }, /* must come after all fonts */
  //{ "size", ArgBoardSize, (LPVOID) &DIS.bsize, FALSE },
	{ L"ringBellAfterMoves", ArgBoolean, (LPVOID)&appData.ringBellAfterMoves, TRUE },
	/* historical; kept only so old winboard.ini files will parse */
	{ L"alwaysOnTop", ArgBoolean, (LPVOID)&appData.alwaysOnTop, TRUE },
  //{ "top", ArgTrue, (LPVOID) &DIS.alwaysOnTop, FALSE },
  //{ "xtop", ArgFalse, (LPVOID) &DIS.alwaysOnTop, FALSE },
  //{ "-top", ArgFalse, (LPVOID) &DIS.alwaysOnTop, FALSE },
	{ L"autoCallFlag", ArgBoolean, (LPVOID)&appData.autoCallFlag, TRUE },

	{ L"autoComment", ArgBoolean, (LPVOID)&appData.autoComment, TRUE },

	{ L"autoObserve", ArgBoolean, (LPVOID)&appData.autoObserve, TRUE },		//自动旁观

	{ L"flipView", ArgBoolean, (LPVOID)&appData.flipView, FALSE },

	{ L"autoFlipView", ArgBoolean, (LPVOID)&appData.autoFlipView, TRUE },

	{ L"autoRaiseBoard", ArgBoolean, (LPVOID)&appData.autoRaiseBoard, TRUE },

	{ L"quietPlay", ArgBoolean, (LPVOID)&appData.quietPlay, TRUE },

	{ L"getMoveList", ArgBoolean, (LPVOID)&appData.getMoveList, TRUE },
	{ L"moves", ArgTrue, (LPVOID)&appData.getMoveList, FALSE },
	{ L"xmoves", ArgFalse, (LPVOID)&appData.getMoveList, FALSE },
	{ L"-moves", ArgFalse, (LPVOID)&appData.getMoveList, FALSE },
  { L"testLegality", ArgBoolean, (LPVOID) &appData.testLegality, TRUE },
  { L"legal", ArgTrue, (LPVOID) &appData.testLegality, FALSE },
  { L"xlegal", ArgFalse, (LPVOID) &appData.testLegality, FALSE },
  { L"-legal", ArgFalse, (LPVOID) &appData.testLegality, FALSE },
  { L"premove", ArgBoolean, (LPVOID) &appData.premove, TRUE },
  { L"pre", ArgTrue, (LPVOID) &appData.premove, FALSE },
  { L"xpre", ArgFalse, (LPVOID) &appData.premove, FALSE },
  { L"-pre", ArgFalse, (LPVOID) &appData.premove, FALSE },
  { L"premoveWhite", ArgBoolean, (LPVOID) &appData.premoveWhite, TRUE },
  { L"prewhite", ArgTrue, (LPVOID) &appData.premoveWhite, FALSE },
  { L"xprewhite", ArgFalse, (LPVOID) &appData.premoveWhite, FALSE },
  { L"-prewhite", ArgFalse, (LPVOID) &appData.premoveWhite, FALSE },
  { L"premoveWhiteText", ArgString, (LPVOID) &appData.premoveWhiteText, TRUE },
  { L"premoveBlack", ArgBoolean, (LPVOID) &appData.premoveBlack, TRUE },
  { L"preblack", ArgTrue, (LPVOID) &appData.premoveBlack, FALSE },
  { L"xpreblack", ArgFalse, (LPVOID) &appData.premoveBlack, FALSE },
  { L"-preblack", ArgFalse, (LPVOID) &appData.premoveBlack, FALSE },
  { L"premoveBlackText", ArgString, (LPVOID) &appData.premoveBlackText, TRUE },
  { L"icsAlarm", ArgBoolean, (LPVOID) &appData.icsAlarm, TRUE},
  { L"alarm", ArgTrue, (LPVOID) &appData.icsAlarm, FALSE},

  { L"icsAlarmTime", ArgInt, (LPVOID) &appData.icsAlarmTime, TRUE},
  { L"localLineEditing", ArgBoolean, (LPVOID) &appData.localLineEditing, FALSE},
  { L"localLineEditing", ArgBoolean, (LPVOID) &appData.localLineEditing, FALSE},
  { L"edit", ArgTrue, (LPVOID) &appData.localLineEditing, FALSE },
  { L"xedit", ArgFalse, (LPVOID) &appData.localLineEditing, FALSE },
  { L"-edit", ArgFalse, (LPVOID) &appData.localLineEditing, FALSE },
  { L"animateMoving", ArgBoolean, (LPVOID) &appData.animate, TRUE },
  { L"animate", ArgTrue, (LPVOID) &appData.animate, FALSE },
  { L"xanimate", ArgFalse, (LPVOID) &appData.animate, FALSE },
  { L"-animate", ArgFalse, (LPVOID) &appData.animate, FALSE },
  { L"animateSpeed", ArgInt, (LPVOID) &appData.animSpeed, TRUE },
  { L"animateDragging", ArgBoolean, (LPVOID) &appData.animateDragging, TRUE },
  { L"drag", ArgTrue, (LPVOID) &appData.animateDragging, FALSE },
  { L"xdrag", ArgFalse, (LPVOID) &appData.animateDragging, FALSE },
  { L"-drag", ArgFalse, (LPVOID) &appData.animateDragging, FALSE },
  { L"blindfold", ArgBoolean, (LPVOID) &appData.blindfold, TRUE },
  { L"blind", ArgTrue, (LPVOID) &appData.blindfold, FALSE },
  { L"xblind", ArgFalse, (LPVOID) &appData.blindfold, FALSE },
  { L"-blind", ArgFalse, (LPVOID) &appData.blindfold, FALSE },
  { L"highlightLastMove", ArgBoolean,
    (LPVOID) &appData.highlightLastMove, TRUE },
  { L"highlight", ArgTrue, (LPVOID) &appData.highlightLastMove, FALSE },
  { L"xhighlight", ArgFalse, (LPVOID) &appData.highlightLastMove, FALSE },
  { L"-highlight", ArgFalse, (LPVOID) &appData.highlightLastMove, FALSE },
  { L"highlightDragging", ArgBoolean,
    (LPVOID) &appData.highlightDragging, TRUE },
  { L"highdrag", ArgTrue, (LPVOID) &appData.highlightDragging, FALSE },
  { L"xhighdrag", ArgFalse, (LPVOID) &appData.highlightDragging, FALSE },
  { L"-highdrag", ArgFalse, (LPVOID) &appData.highlightDragging, FALSE },
  { L"colorizeMessages", ArgBoolean, (LPVOID) &appData.colorize, TRUE },
  { L"colorize", ArgTrue, (LPVOID) &appData.colorize, FALSE },
  { L"xcolorize", ArgFalse, (LPVOID) &appData.colorize, FALSE },
  { L"-colorize", ArgFalse, (LPVOID) &appData.colorize, FALSE },
  { L"colorShout", ArgAttribs, (LPVOID) ColorShout, TRUE },
  { L"colorSShout", ArgAttribs, (LPVOID) ColorSShout, TRUE },
  { L"colorChannel1", ArgAttribs, (LPVOID) ColorChannel1, TRUE },
  { L"colorChannel", ArgAttribs, (LPVOID) ColorChannel, TRUE },
  { L"colorKibitz", ArgAttribs, (LPVOID) ColorKibitz, TRUE },
  { L"colorTell", ArgAttribs, (LPVOID) ColorTell, TRUE },
  { L"colorChallenge", ArgAttribs, (LPVOID) ColorChallenge, TRUE },
  { L"colorRequest", ArgAttribs, (LPVOID) ColorRequest, TRUE },
  { L"colorSeek", ArgAttribs, (LPVOID) ColorSeek, TRUE },
  { L"colorNormal", ArgAttribs, (LPVOID) ColorNormal, TRUE },
  { L"colorBackground", ArgColor, (LPVOID) &TAB.consoleBackgroundColor, TRUE },
  //{ "soundShout", ArgFilename,
  //  (LPVOID) &appData.AtextAttribs[ColorShout].sound.name, TRUE },
  //{ "soundSShout", ArgFilename,
  //  (LPVOID) &appData.AtextAttribs[ColorSShout].sound.name, TRUE },
  //{ "soundChannel1", ArgFilename,
  //  (LPVOID) &appData.AtextAttribs[ColorChannel1].sound.name, TRUE },
  //{ "soundChannel", ArgFilename,
  //  (LPVOID) &appData.AtextAttribs[ColorChannel].sound.name, TRUE },
  //{ "soundKibitz", ArgFilename,
  //  (LPVOID) &appData.AtextAttribs[ColorKibitz].sound.name, TRUE },
  //{ "soundTell", ArgFilename,
  //  (LPVOID) &appData.AtextAttribs[ColorTell].sound.name, TRUE },
  //{ "soundChallenge", ArgFilename,
  //  (LPVOID) &appData.AtextAttribs[ColorChallenge].sound.name, TRUE },
  //{ "soundRequest", ArgFilename,
  //  (LPVOID) &appData.AtextAttribs[ColorRequest].sound.name, TRUE },
  //{ "soundSeek", ArgFilename,
  //  (LPVOID) &appData.AtextAttribs[ColorSeek].sound.name, TRUE },
//  { "soundEat", ArgFilename, (LPVOID) &appData.Asounds[(int)SoundEat].name, TRUE },
//  { "soundCheck", ArgFilename, (LPVOID) &appData.Asounds[(int)SoundCheck].name, TRUE },
//  { "soundMove", ArgFilename, (LPVOID) &appData.Asounds[(int)SoundMove].name, TRUE },
//  { "soundBell", ArgFilename, (LPVOID) &appData.Asounds[(int)SoundBell].name, TRUE },
//  { "soundIcsWin", ArgFilename, (LPVOID) &appData.Asounds[(int)SoundIcsWin].name,TRUE },
//  { "soundIcsLoss", ArgFilename, 
  //  (LPVOID) &appData.Asounds[(int)SoundIcsLoss].name, TRUE },
  //{ "soundIcsDraw", ArgFilename, 
  //  (LPVOID) &appData.Asounds[(int)SoundIcsDraw].name, TRUE },
  //{ "soundIcsUnfinished", ArgFilename, 
  //  (LPVOID) &appData.Asounds[(int)SoundIcsUnfinished].name, TRUE},
  //{ "soundIcsAlarm", ArgFilename, 
  //  (LPVOID) &appData.Asounds[(int)SoundAlarm].name, TRUE },
  { L"reuseFirst", ArgBoolean, (LPVOID) &appData.reuseFirst, FALSE },

  { L"reuseChessPrograms", ArgBoolean,
    (LPVOID) &appData.reuseFirst, FALSE }, /* backward compat only */
	{ L"reuseSecond", ArgBoolean, (LPVOID)&appData.reuseSecond, FALSE },

  //{ "comPortSettings", ArgCommSettings, (LPVOID) &MAIN.dcb, false },
 
  //{ "icsX", ArgInt, (LPVOID) &DIS.consoleX, TRUE },
  //{ "icsY", ArgInt, (LPVOID) &DIS.consoleY, TRUE },
  //{ "icsW", ArgInt, (LPVOID) &DIS.consoleW, TRUE },
  //{ "icsH", ArgInt, (LPVOID) &DIS.consoleH, TRUE },
  //{ "analysisX", ArgInt, (LPVOID) &DIS.analysisX, TRUE },
  //{ "analysisY", ArgInt, (LPVOID) &DIS.analysisY, TRUE },
  //{ "analysisW", ArgInt, (LPVOID) &DIS.analysisW, TRUE },
  //{ "analysisH", ArgInt, (LPVOID) &DIS.analysisH, TRUE },
  //{ "commentX", ArgInt, (LPVOID) &DIS.commentX, TRUE },
  //{ "commentY", ArgInt, (LPVOID) &DIS.commentY, TRUE },
  //{ "commentW", ArgInt, (LPVOID) &DIS.commentW, TRUE },
  //{ "commentH", ArgInt, (LPVOID) &DIS.commentH, TRUE },
  //{ "tagsX", ArgInt, (LPVOID) &DIS.editTagsX, TRUE },
  //{ "tagsY", ArgInt, (LPVOID) &DIS.editTagsY, TRUE },
  //{ "tagsW", ArgInt, (LPVOID) &DIS.editTagsW, TRUE },
  //{ "tagsH", ArgInt, (LPVOID) &DIS.editTagsH, TRUE },
  //{ "gameListX", ArgInt, (LPVOID) &DIS.gameListX, TRUE },
  //{ "gameListY", ArgInt, (LPVOID) &DIS.gameListY, TRUE },
  //{ "gameListW", ArgInt, (LPVOID) &DIS.gameListW, TRUE },
  //{ "gameListH", ArgInt, (LPVOID) &DIS.gameListH, TRUE },
  //{ "settingsFile", ArgSettingsFilename, (LPVOID) &DIS.settingsFileName, false },
  //{ "ini", ArgSettingsFilename, (LPVOID) &DIS.settingsFileName, FALSE },
	{ L"saveSettingsOnExit", ArgBoolean, (LPVOID)&appData.AsaveSettingsOnExit, TRUE },
	{ L"chessProgram", ArgBoolean, (LPVOID)&appData.AchessProgram, FALSE },
  //{ "cp", ArgTrue, (LPVOID) &DIS.chessProgram, FALSE },
  //{ "xcp", ArgFalse, (LPVOID) &DIS.chessProgram, FALSE },
  //{ "-cp", ArgFalse, (LPVOID) &DIS.chessProgram, FALSE },
  //{ "icsMenu", ArgString, (LPVOID) &MAIN.icsTextMenuString, TRUE },
  //{ "icsNames", ArgString, (LPVOID) &appData.icsNames, false },
  //{"UCCI_NAME",ArgString, (LPVOID) &DIS.UCCI_NAME, TRUE },
  //{ "firstChessProgramNames", ArgString,  (LPVOID) &DIS.first.ChessProgramNames,TRUE },
  //{ "secondChessProgramNames", ArgString, (LPVOID) &DIS.second.ChessProgramNames,TRUE },
  //{ "initialMode", ArgString, (LPVOID) &appData.initialMode, FALSE },
  //{ "mode", ArgString, (LPVOID) &appData.initialMode, FALSE },
  //{ "variant", ArgString, (LPVOID) &appData.variant, FALSE },
  //{ "firstProtocolVersion", ArgInt, (LPVOID) &appData.firstProtocolVersion,  FALSE },
  //{ "secondProtocolVersion", ArgInt, (LPVOID) &appData.secondProtocolVersion,FALSE },
	{ L"showButtonBar", ArgBoolean, (LPVOID)&appData.showButtonBar, TRUE },

	{ L"pieceStyle", ArgInt, (LPVOID)&appData.pieceStyle, true },	//棋子风格
	{ L"winWidth", ArgInt, (LPVOID)&appData.winWidth, true },	//当前窗口的宽度
  //{ "sql_installed",  ArgBoolean,(LPVOID) &appData.sql_installed,	 true },
  //{ "sql_host",		  ArgString, (LPVOID) &appData.sql_host,		 true },	//mysql 主机名
  //{ "sql_user",		  ArgString, (LPVOID) &appData.sql_user,		 true },
  //{ "sql_pass",		  ArgString, (LPVOID) &appData.sql_pass,		 true },
  //{ "sql_port",		  ArgInt,	 (LPVOID) &appData.sql_port,		 true },
  //{ "sql_db_chess",   ArgString, (LPVOID) &appData.sql_db_chess,	 true },
  //{ "sql_db_face",    ArgString, (LPVOID) &appData.sql_db_face,		 true },
	{ L"moveType", ArgInt, (LPVOID)&appData.moveType, true },	//当前棋步的格式
	{ L"path_mxq", ArgString, (LPVOID)&appData.path_mxq, true },

	{ L"wxf_is_get", ArgBoolean, (LPVOID)&appData.wxf_is_get, true },
	{ L"wxf_url", ArgString, (LPVOID)&appData.wxf_url, true },
	{ L"wxf_alread_read", ArgInt, (LPVOID)&appData.wxf_alread_read, true },
	{ L"wxf_per_read", ArgInt, (LPVOID)&appData.wxf_per_read, true },

  //{ "first_yq_id",    ArgInt,    (LPVOID)  &DIS.first.yqID,   true},
  //{ "second_yq_id",   ArgInt,    (LPVOID)  &DIS.second.yqID,  true},
  //{ "boardX",         ArgInt,    (LPVOID)  &OBS[0]->boardX,       TRUE },
  //{ "boardY",         ArgInt,    (LPVOID)  &OBS[0]->boardY,       TRUE },
  //{ "first_yq_id",    ArgInt,    (LPVOID)  &OBS[0]->first.yqID,   true},
  //{ "second_yq_id",   ArgInt,    (LPVOID)  &OBS[0]->second.yqID,  true},

	{ L"boardX", ArgInt, (LPVOID)&appData.boardX, TRUE },
	{ L"boardY", ArgInt, (LPVOID)&appData.boardY, TRUE },

	{ L"first_yq_id", ArgInt, (LPVOID)&appData.first_yqID, true },
	{ L"second_yq_id", ArgInt, (LPVOID)&appData.second_yqID, true },
	{ L"ics_count_id", ArgInt, (LPVOID)&appData.ACPSics.ICS_id, true },

  { NULL, ArgNone, NULL, FALSE }				//最后一个数组,表示结束了
};



ErrorMap errmap[] = 
{ {WSAEINTR, L"Interrupted system call"},
{ WSAEBADF, L"Bad file number" },
{ WSAEACCES, L"Permission denied" },
{ WSAEFAULT, L"Bad address" },
{ WSAEINVAL, L"Invalid argument" },
{ WSAEMFILE, L"Too many open files" },
{ WSAEWOULDBLOCK, L"Operation would block" },
{ WSAEINPROGRESS, L"Operation now in progress" },
{ WSAEALREADY, L"Operation already in progress" },
{ WSAENOTSOCK, L"Socket operation on non-socket" },
{ WSAEMSGSIZE, L"Message too long" },
{ WSAEPROTOTYPE, L"Protocol wrong type for socket" },
{ WSAENOPROTOOPT, L"Protocol not available" },
{ WSAEPROTONOSUPPORT, L"Protocol not supported" },
{ WSAESOCKTNOSUPPORT, L"Socket type not supported" },
{ WSAEOPNOTSUPP, L"Operation not supported on socket" },
{ WSAEPFNOSUPPORT, L"Protocol family not supported" },
{ WSAEAFNOSUPPORT, L"Address family not supported by protocol family" },
{ WSAEADDRINUSE, L"Address already in use" },
{ WSAEADDRNOTAVAIL, L"Can't assign requested address" },
{ WSAENETDOWN, L"Network is down" },
{ WSAENETUNREACH, L"Network is unreachable" },
{ WSAENETRESET, L"Network dropped connection on reset" },
{ WSAECONNABORTED, L"Software caused connection abort" },
{ WSAECONNRESET, L"Connection reset by peer" },
{ WSAENOBUFS, L"No buffer space available" },
{ WSAEISCONN, L"Socket is already connected" },
{ WSAENOTCONN, L"Socket is not connected" },
{ WSAESHUTDOWN, L"Can't send after socket shutdown" },
{ WSAETOOMANYREFS, L"Too many references: can't splice" },
{ WSAETIMEDOUT, L"Connection timed out" },
{ WSAECONNREFUSED, L"Connection refused" },
{ WSAELOOP, L"Too many levels of symbolic links" },
{ WSAENAMETOOLONG, L"File name too long" },
{ WSAEHOSTDOWN, L"Host is down" },
{ WSAEHOSTUNREACH, L"No route to host" },
{ WSAENOTEMPTY, L"Directory not empty" },
{ WSAEPROCLIM, L"Too many processes" },
{ WSAEUSERS, L"Too many users" },
{ WSAEDQUOT, L"Disc quota exceeded" },
{ WSAESTALE, L"Stale NFS file handle" },
{ WSAEREMOTE, L"Too many levels of remote in path" },
{ WSAEDISCON, L"Undocumented Winsock error code WSAEDISCON" },
{ WSASYSNOTREADY, L"Winsock subsystem unusable" },
{ WSAVERNOTSUPPORTED, L"Required Winsock version is not supported" },
{ WSANOTINITIALISED, L"Winsock not initialized" },
{ WSAHOST_NOT_FOUND, L"Host name not found by name server (authoritative)" },
{ WSATRY_AGAIN, L"Host name not found by name server (nonauthoritative), or name server failure" },
{ WSANO_RECOVERY, L"Nonrecoverable name server error" },
{ WSANO_DATA, L"Host name has no address data of required type" },
  {0, NULL}
};

/* These modify either ncpEnables or gnuEnables */
Enables cmailEnables[] = {
  { IDM_MailMove, MF_BYCOMMAND|MF_ENABLED },
  { IDM_ReloadCMailMsg, MF_BYCOMMAND|MF_ENABLED },
  { ACTION_POS, MF_BYPOSITION|MF_ENABLED },
  { IDM_CallFlag, MF_BYCOMMAND|MF_GRAYED },
  { IDM_Draw, MF_BYCOMMAND|MF_ENABLED },
  { IDM_Adjourn, MF_BYCOMMAND|MF_GRAYED },
  { IDM_Abort, MF_BYCOMMAND|MF_GRAYED },

  { IDM_DlgDefaultPosition, MF_BYCOMMAND|MF_ENABLED },

  { -1, -1 }
};

Enables icsEnables[] = {
  { IDM_MailMove, MF_BYCOMMAND|MF_GRAYED },
  { IDM_ReloadCMailMsg, MF_BYCOMMAND|MF_GRAYED },
  { IDM_MachineWhite, MF_BYCOMMAND|MF_GRAYED },
  { IDM_MachineBlack, MF_BYCOMMAND|MF_GRAYED },
  { IDM_TwoMachines, MF_BYCOMMAND|MF_GRAYED },
  { IDM_AnalysisMode, MF_BYCOMMAND|MF_GRAYED },
  { IDM_AnalyzeFile, MF_BYCOMMAND|MF_GRAYED },
  { IDM_TimeControl, MF_BYCOMMAND|MF_GRAYED },
  { IDM_MoveNow, MF_BYCOMMAND|MF_GRAYED },
  { IDM_Hint, MF_BYCOMMAND|MF_GRAYED },
  { IDM_Book, MF_BYCOMMAND|MF_GRAYED },
  { IDM_IcsOptions, MF_BYCOMMAND|MF_ENABLED },


  { IDM_DlgDefaultPosition, MF_BYCOMMAND|MF_ENABLED },

  { -1, -1 }
};

Enables ncpEnables[] = {
  { IDM_MailMove, MF_BYCOMMAND|MF_GRAYED },
  { IDM_ReloadCMailMsg, MF_BYCOMMAND|MF_GRAYED },
  { IDM_MachineWhite, MF_BYCOMMAND|MF_GRAYED },
  { IDM_MachineBlack, MF_BYCOMMAND|MF_GRAYED },
  { IDM_TwoMachines, MF_BYCOMMAND|MF_GRAYED },
  { IDM_AnalysisMode, MF_BYCOMMAND|MF_GRAYED },
  { IDM_AnalyzeFile, MF_BYCOMMAND|MF_GRAYED },
  { IDM_IcsClient, MF_BYCOMMAND|MF_GRAYED },
  //{ ACTION_POS, MF_BYPOSITION|MF_GRAYED },        //主菜单的最顶菜单是0为开头的!!!
  { IDM_Revert, MF_BYCOMMAND|MF_GRAYED },
  { IDM_MoveNow, MF_BYCOMMAND|MF_GRAYED },
  { IDM_RetractMove, MF_BYCOMMAND|MF_GRAYED },
  //{ IDM_TimeControl, MF_BYCOMMAND|MF_GRAYED },
  { IDM_Hint, MF_BYCOMMAND|MF_GRAYED },
  { IDM_Book, MF_BYCOMMAND|MF_GRAYED },

  { IDM_DlgDefaultPosition, MF_BYCOMMAND|MF_ENABLED },

  { -1, -1 }
};

//Enables ncpEnables[] = {
//  { IDM_MailMove, MF_BYCOMMAND|MF_ENABLED },
//  { IDM_ReloadCMailMsg, MF_BYCOMMAND|MF_ENABLED },
//  { IDM_MachineWhite, MF_BYCOMMAND|MF_ENABLED },
//  { IDM_MachineBlack, MF_BYCOMMAND|MF_ENABLED },
//  { IDM_TwoMachines, MF_BYCOMMAND|MF_ENABLED },
//  { IDM_AnalysisMode, MF_BYCOMMAND|MF_ENABLED },
//  { IDM_AnalyzeFile, MF_BYCOMMAND|MF_ENABLED},
//  { IDM_IcsClient, MF_BYCOMMAND|MF_ENABLED },
//  { ACTION_POS, MF_BYPOSITION|MF_ENABLED },
//  { IDM_Revert, MF_BYCOMMAND|MF_ENABLED },
//  { IDM_MoveNow, MF_BYCOMMAND|MF_ENABLED },
//  { IDM_RetractMove, MF_BYCOMMAND|MF_ENABLED },
//  //{ IDM_TimeControl, MF_BYCOMMAND|MF_GRAYED },
//  { IDM_Hint, MF_BYCOMMAND|MF_ENABLED },
//  { IDM_Book, MF_BYCOMMAND|MF_ENABLED },
//
//  { IDM_DlgDefaultPosition, MF_BYCOMMAND|MF_ENABLED },
//
//  { -1, -1 }
//};
Enables gnuEnables[] = {
  { IDM_MailMove, MF_BYCOMMAND|MF_GRAYED },
  { IDM_ReloadCMailMsg, MF_BYCOMMAND|MF_GRAYED },
  { IDM_IcsClient, MF_BYCOMMAND|MF_GRAYED },
  { IDM_Accept, MF_BYCOMMAND|MF_GRAYED },
  { IDM_Decline, MF_BYCOMMAND|MF_GRAYED },
  { IDM_Rematch, MF_BYCOMMAND|MF_GRAYED },
  { IDM_Adjourn, MF_BYCOMMAND|MF_GRAYED },
  { IDM_StopExamining, MF_BYCOMMAND|MF_GRAYED },
  { IDM_StopObserving, MF_BYCOMMAND|MF_GRAYED },
  { IDM_Revert, MF_BYCOMMAND|MF_GRAYED },

  { IDM_DlgDefaultPosition, MF_BYCOMMAND|MF_ENABLED },

  { -1, -1 }
};

Enables machineThinkingEnables[] = {
  { IDM_LoadGame, MF_BYCOMMAND|MF_GRAYED },
  { IDM_LoadNextGame, MF_BYCOMMAND|MF_GRAYED },
  { IDM_LoadPrevGame, MF_BYCOMMAND|MF_GRAYED },
  { IDM_ReloadGame, MF_BYCOMMAND|MF_GRAYED },
  { IDM_PasteGame, MF_BYCOMMAND|MF_GRAYED },
  { IDM_LoadPosition, MF_BYCOMMAND|MF_GRAYED },
  { IDM_LoadNextPosition, MF_BYCOMMAND|MF_GRAYED },
  { IDM_LoadPrevPosition, MF_BYCOMMAND|MF_GRAYED },
  { IDM_ReloadPosition, MF_BYCOMMAND|MF_GRAYED },
  { IDM_PastePosition, MF_BYCOMMAND|MF_GRAYED },
  { IDM_MachineWhite, MF_BYCOMMAND|MF_GRAYED },
  { IDM_MachineBlack, MF_BYCOMMAND|MF_GRAYED },
  { IDM_TwoMachines, MF_BYCOMMAND|MF_GRAYED },
  { IDM_TypeInMove, MF_BYCOMMAND|MF_GRAYED },
  { IDM_RetractMove, MF_BYCOMMAND|MF_GRAYED },

  { IDM_DlgDefaultPosition, MF_BYCOMMAND|MF_ENABLED },

  { -1, -1 }
};

Enables trainingOffEnables[] = {
  { IDM_EditComment, MF_BYCOMMAND|MF_ENABLED },
  { IDM_Pause, MF_BYCOMMAND|MF_ENABLED },
  { IDM_Forward, MF_BYCOMMAND|MF_ENABLED },
  { IDM_Backward, MF_BYCOMMAND|MF_ENABLED },
  { IDM_ToEnd, MF_BYCOMMAND|MF_ENABLED },
  { IDM_ToStart, MF_BYCOMMAND|MF_ENABLED },
  { IDM_MoveNow, MF_BYCOMMAND|MF_ENABLED },
  { IDM_TruncateGame, MF_BYCOMMAND|MF_ENABLED },

  { IDM_DlgDefaultPosition, MF_BYCOMMAND|MF_ENABLED },

  { -1, -1 }
};

Enables trainingOnEnables[] = {
  { IDM_EditComment, MF_BYCOMMAND|MF_GRAYED },
  { IDM_Pause, MF_BYCOMMAND|MF_GRAYED },
  { IDM_Forward, MF_BYCOMMAND|MF_GRAYED },
  { IDM_Backward, MF_BYCOMMAND|MF_GRAYED },
  { IDM_ToEnd, MF_BYCOMMAND|MF_GRAYED },
  { IDM_ToStart, MF_BYCOMMAND|MF_GRAYED },
  { IDM_MoveNow, MF_BYCOMMAND|MF_GRAYED },
  { IDM_TruncateGame, MF_BYCOMMAND|MF_GRAYED },

  { IDM_DlgDefaultPosition, MF_BYCOMMAND|MF_ENABLED },

  { -1, -1 }
};

Enables userThinkingEnables[] = {
  { IDM_LoadGame, MF_BYCOMMAND|MF_ENABLED },
  { IDM_LoadNextGame, MF_BYCOMMAND|MF_ENABLED },
  { IDM_LoadPrevGame, MF_BYCOMMAND|MF_ENABLED },
  { IDM_ReloadGame, MF_BYCOMMAND|MF_ENABLED },
  { IDM_PasteGame, MF_BYCOMMAND|MF_ENABLED },
  { IDM_LoadPosition, MF_BYCOMMAND|MF_ENABLED },
  { IDM_LoadNextPosition, MF_BYCOMMAND|MF_ENABLED },
  { IDM_LoadPrevPosition, MF_BYCOMMAND|MF_ENABLED },
  { IDM_ReloadPosition, MF_BYCOMMAND|MF_ENABLED },
  { IDM_PastePosition, MF_BYCOMMAND|MF_ENABLED },
  { IDM_MachineWhite, MF_BYCOMMAND|MF_ENABLED },
  { IDM_MachineBlack, MF_BYCOMMAND|MF_ENABLED },
  { IDM_TwoMachines, MF_BYCOMMAND|MF_ENABLED },
  { IDM_TypeInMove, MF_BYCOMMAND|MF_ENABLED },
  { IDM_RetractMove, MF_BYCOMMAND|MF_ENABLED },

  { IDM_DlgDefaultPosition, MF_BYCOMMAND|MF_ENABLED },

  { -1, -1 }
};




