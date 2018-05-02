#ifndef CHESS_ENUM_H
#define CHESS_ENUM_H

//枚举
enum mat_dummy_t {
   MAT_NONE,
   MAT_KK,
   MAT_KBK, MAT_KKB,
   MAT_KNK, MAT_KKN,
   MAT_KPK, MAT_KKP,
   MAT_KQKQ, MAT_KQKP, MAT_KPKQ,
   MAT_KRKR, MAT_KRKP, MAT_KPKR,
   MAT_KBKB, MAT_KBKP, MAT_KPKB, MAT_KBPK, MAT_KKBP,
   MAT_KNKN, MAT_KNKP, MAT_KPKN, MAT_KNPK, MAT_KKNP,
   MAT_KRPKR, MAT_KRKRP,
   MAT_KBPKB, MAT_KBKBP,
   MAT_NB
};

typedef enum { 
  SizeTiny, SizeTeeny, SizeDinky, SizePetite, SizeSlim, SizeSmall,
  SizeMediocre, SizeMiddling, SizeAverage, SizeModerate, SizeMedium,
  SizeBulky, SizeLarge, SizeBig, SizeHuge, SizeGiant, SizeColossal,
  SizeTitanic, NUM_SIZES, NoSize 
} BoardSize;

typedef enum {
	EmptySquare, 
    ClearBoard, WhitePlay, BlackPlay /*for use on EditPosition menus*/
}ChessSquare;

///* States for ics_getting_history */
//#define H_FALSE 0
//#define H_REQUESTED 1
//#define H_GOT_REQ_HEADER 2
//#define H_GOT_UNREQ_HEADER 3
//#define H_GETTING_MOVES 4
//#define H_GOT_UNWANTED_HEADER 5

//#define STARTED_NONE            0
//#define STARTED_MOVES           1
//#define STARTED_BOARD           2
//#define STARTED_OBSERVE         3
//#define STARTED_HOLDINGS        4
//#define STARTED_CHATTER         5
//#define STARTED_COMMENT         6
//#define STARTED_MOVES_NOHIDE    7
//#define STARTED_PLAYER_LIST     8
//#define STARTED_TABLE_LIST      9
//#define STARTED_ROOM_DIR       10

typedef enum {
	STARTED_NONE,            //0
	STARTED_MOVES,           //1
	STARTED_BOARD,           //2
	STARTED_OBSERVE,         //3
	STARTED_HOLDINGS,        //4
	STARTED_CHATTER,         //5
	STARTED_COMMENT,         //6
	STARTED_MOVES_NOHIDE,    //7
	STARTED_PLAYER_LIST,     //8

	STARTED_GAME_PLAYER,     //正在下棋或旁观的人员

	STARTED_TABLE_LIST,	     //9
	STARTED_ROOM_DIR,        //10

	STARTED_GAME_CAN_START,  //

}ICS_STARTED;


//引擎的状态
typedef enum {
	//还没加载，  正在加载     正在思考       已加载成功，   正在后台       正在思考      正在分析    
	Cps_NotLoad, Cps_UpLoading, Cps_InLoading, Cps_Waiting, Cps_Pondering, Cps_Thinking, Cps_Analyse, 
	//对手已准备好了
	Cps_ReadyOk,
}CPS_STAT;

typedef enum {
    //WhiteKingSideCastle = 1, WhiteQueenSideCastle,
    //WhiteKingSideCastleWild, WhiteQueenSideCastleWild,
    //WhiteHSideCastleFR, WhiteASideCastleFR, 
    //BlackKingSideCastle, BlackQueenSideCastle,
    //BlackKingSideCastleWild, BlackQueenSideCastleWild,
    //BlackHSideCastleFR, BlackASideCastleFR, 
    //WhitePromotionKnight, WhitePromotionBishop,
    //WhitePromotionRook, WhitePromotionQueen, WhitePromotionKing,
    //BlackPromotionKnight, BlackPromotionBishop,
    //BlackPromotionRook, BlackPromotionQueen, BlackPromotionKing,
    //WhiteCapturesEnPassant, BlackCapturesEnPassant,
    WhiteDrop = 1, BlackDrop, 
    NormalMove, AmbiguousMove, IllegalMove, ImpossibleMove,
    WhiteWins, BlackWins, GameIsDrawn, GameUnfinished,
    GNUChessGame, XBoardGame, MoveNumberOne, 
    Comment, PositionDiagram, ElapsedTime, PGNTag, NAG
  } ChessMove;

typedef enum {
    ColorShout, ColorSShout, ColorChannel1, ColorChannel, ColorKibitz,
    ColorTell, ColorChallenge, ColorRequest, ColorSeek, ColorNormal,
    ColorNone, NColorClasses
} ColorClass;


//棋库得分
typedef enum {
	BOOK_VERY_BAD	= -2, 
	BOOK_LIT_BAD	= -1, 
	BOOK_BALANCE	=  0,
	BOOK_LIT_GOOD	=  1,
	BOOK_VERY_GOOD  =  2,
	BOOK_NOT_RESULT =  8
}Book_Sc;


typedef enum {
	//走棋    //吃子   //将军
    SoundMove,SoundEat,SoundCheck, SoundBell, SoundAlarm, SoundIcsWin, SoundIcsLoss,
    SoundIcsDraw, SoundIcsUnfinished, NSoundClasses
} SoundClass;

/* Names for chess variants, not necessarily supported */
//typedef enum {
//    VariantNormal,       /* Normal chess */
//    VariantLoadable,     /* "loadgame" command allowed (not really a variant)*/
//    VariantWildCastle,   /* Shuffle chess where king can castle from d file */
//    VariantNoCastle,     /* Shuffle chess with no castling at all */
//    VariantFischeRandom, /* FischeRandom */
//    VariantBughouse,     /* Bughouse, ICC/FICS rules */
//    VariantCrazyhouse,   /* Crazyhouse, ICC/FICS rules */
//    VariantLosers,       /* Try to lose all pieces or get mated (ICC wild 17)*/
//    VariantSuicide,      /* Try to lose all pieces incl. king (FICS) */
//    VariantGiveaway,     /* Try to have no legal moves left (ICC wild 26) */
//    VariantTwoKings,     /* Weird ICC wild 9 */
//    VariantKriegspiel,   /* Kriegspiel; pawns can capture invisible pieces */
//    VariantAtomic,       /* Capturing piece explodes (ICC wild 27) */
//    Variant3Check,       /* Win by giving check 3 times (ICC wild 25) */
//    VariantShatranj,     /* Unsupported (ICC wild 28) */
//    Variant29,           /* Temporary name for possible future ICC wild 29 */
//    Variant30,           /* Temporary name for possible future ICC wild 30 */
//    Variant31,           /* Temporary name for possible future ICC wild 31 */
//    Variant32,           /* Temporary name for possible future ICC wild 32 */
//    Variant33,           /* Temporary name for possible future ICC wild 33 */
//    Variant34,           /* Temporary name for possible future ICC wild 34 */
//    Variant35,           /* Temporary name for possible future ICC wild 35 */
//    Variant36,           /* Temporary name for possible future ICC wild 36 */
//    VariantUnknown       /* Catchall for other unknown variants */
//} VariantClass;

typedef enum {
	//没有
    GameNoneMode, BeginningOfGame, MachinePlaysWhite, MachinePlaysBlack,
    AnalyzeMode, /*TwoMachinesPlay,*/
    EditGame, PlayFromGameFile, EndOfGame, EditPosition, Training,
    IcsIdle, IcsPlayingWhite, IcsPlayingBlack, IcsObserving,
    IcsExamining, EditBook, //当前正在编辑棋库
  } GameMode;

//当前棋局的方式，

//typedef enum 

typedef enum {
  ArgString, ArgInt, ArgFloat, ArgBoolean, ArgTrue, ArgFalse, ArgNone, 
  ArgColor, ArgAttribs, ArgFilename, ArgBoardSize, ArgFont, ArgCommSettings,
  ArgSettingsFilename
} ArgType;

#endif