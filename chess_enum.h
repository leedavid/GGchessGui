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

//const int BOOK_NOT_RESULT =    8;
//const int BOOK_VERY_GOOD  =    2;
//const int BOOK_LIT_GOOD   =    1;
//const int BOOK_BALANCE    =    0;
//const int BOOK_LIT_BAD    =   -1;
//const int BOOK_VERY_BAD   =   -2;

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
typedef enum {
    VariantNormal,       /* Normal chess */
    VariantLoadable,     /* "loadgame" command allowed (not really a variant)*/
    VariantWildCastle,   /* Shuffle chess where king can castle from d file */
    VariantNoCastle,     /* Shuffle chess with no castling at all */
    VariantFischeRandom, /* FischeRandom */
    VariantBughouse,     /* Bughouse, ICC/FICS rules */
    VariantCrazyhouse,   /* Crazyhouse, ICC/FICS rules */
    VariantLosers,       /* Try to lose all pieces or get mated (ICC wild 17)*/
    VariantSuicide,      /* Try to lose all pieces incl. king (FICS) */
    VariantGiveaway,     /* Try to have no legal moves left (ICC wild 26) */
    VariantTwoKings,     /* Weird ICC wild 9 */
    VariantKriegspiel,   /* Kriegspiel; pawns can capture invisible pieces */
    VariantAtomic,       /* Capturing piece explodes (ICC wild 27) */
    Variant3Check,       /* Win by giving check 3 times (ICC wild 25) */
    VariantShatranj,     /* Unsupported (ICC wild 28) */
    Variant29,           /* Temporary name for possible future ICC wild 29 */
    Variant30,           /* Temporary name for possible future ICC wild 30 */
    Variant31,           /* Temporary name for possible future ICC wild 31 */
    Variant32,           /* Temporary name for possible future ICC wild 32 */
    Variant33,           /* Temporary name for possible future ICC wild 33 */
    Variant34,           /* Temporary name for possible future ICC wild 34 */
    Variant35,           /* Temporary name for possible future ICC wild 35 */
    Variant36,           /* Temporary name for possible future ICC wild 36 */
    VariantUnknown       /* Catchall for other unknown variants */
} VariantClass;

typedef enum {
    BeginningOfGame, MachinePlaysWhite, MachinePlaysBlack,
    AnalyzeMode, AnalyzeFile, TwoMachinesPlay,
    EditGame, PlayFromGameFile, EndOfGame, EditPosition, Training,
    IcsIdle, IcsPlayingWhite, IcsPlayingBlack, IcsObserving,
    IcsExamining, EditBook, //当前正在编辑棋库
  } GameMode;

//typedef enum 

typedef enum {
  ArgString, ArgInt, ArgFloat, ArgBoolean, ArgTrue, ArgFalse, ArgNone, 
  ArgColor, ArgAttribs, ArgFilename, ArgBoardSize, ArgFont, ArgCommSettings,
  ArgSettingsFilename
} ArgType;

#endif