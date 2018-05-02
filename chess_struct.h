#ifndef CHESS_STRUCT_H
#define CHESS_STRUCT_H

typedef VOIDSTAR ProcRef;
typedef VOIDSTAR InputSourceRef;





/* Type definition: Node of a double linked list.
*/
typedef struct _ListNode {
    struct _ListNode *succ;
    struct _ListNode *pred;
} ListNode;

typedef struct {
    struct _ListNode *head;     /*  The list structure consists of two  */
    struct _ListNode *tail;     /*  ListNode's: The pred entry of the   */
    struct _ListNode *tailPred; /*  head being the succ entry of the    */
} List;

typedef  unsigned __int8  sc_t;
typedef  unsigned __int16 num_t;
typedef struct {
    int				pid;          //棋局编号
    char			pevent[64];   //棋局位置
    char            date[32];     //比赛日期，格式统一为“yyyy.mm.dd”； 
    char            round[16];    //比赛轮次； 
    char            Red[24];      //红方名称
    char            Black[24];    //黑方名称
    char            result[32];   //比赛结果
    int             Relo;
    int             Belo;
    char            RtimeControl[32];
    char            BtimeControl[32];
    char            start_fen[128];
    char            fen_store[2400];
    char            note[128];      //备注
    
    int             isFenGame;   //是开局还是残局
    int             isChecked;     //是否计算过得分
    int             isLearned;     //是否学习过
    int             isFinish;      //是否完成了计划
    int             PlanID;        //计划ID
    int             score;         //最后得分
	int             rate;          //比重
	char            opera[32];     //操作员
	int             yqScore;       //引擎得分 90000没有分
} PGN;

//struct timezone {
//    int tz_minuteswest;
//    int tz_dsttime;
//};

/* A point in time */
//typedef struct {
//    long sec;  /* Assuming this is >= 32 bits */
//    int ms;    /* Assuming this is >= 16 bits */
//} TimeMark;

/* Search stats from chessprogram */
//typedef struct {
//    char movelist[2*MSG_SIZ]; /* Last PV we were sent */
//    int depth;                /* Current search depth */
//    int nr_moves;             /* Total nr of root moves */
//    int moves_left;           /* Moves remaining to be searched */
//    char move_name[MOVE_LEN]; /* Current move being searched, if provided */
//    unsigned long nodes;      /* # of nodes searched */
//    int time;                 /* Search time (centiseconds) */
//    int score;                /* Score (centipawns) */
//    int got_only_move;        /* If last msg was "(only move)" */
//    int got_fail;             /* 0 - nothing, 1 - got "--", 2 - got "++" */
//    int ok_to_send;           /* handshaking between send & recv */
//    int line_is_book;         /* 1 if movelist is book moves */
//    int seen_stat;            /* 1 if we've seen the stat01: line */
//} ChessProgramStats;

typedef int CPKind;

typedef struct {
    CPKind kind;
    HANDLE hProcess;
    DWORD pid;
    HANDLE hTo;
    HANDLE hFrom;
    SOCKET sock;
    SOCKET sock2;  /* stderr socket for OpenRcmd */
} ChildProc;

//以下为函数
//typedef void (*DelayedEventCallback) (disboard_t* pDis);
typedef void (*InputCallback) (InputSourceRef isr, VOIDSTAR closure, char *buf, int count, int error);

typedef struct {
    char *name;
    int squareSize;
    int lineGap;
    int clockFontPxlSize;
    int coordFontPxlSize;
    int fontPxlSize;
    int smallLayout;
    int tinyLayout;
    int minScreenSize;
} SizeDefaults;

/* Types */
typedef struct {
    char faceName[LF_FACESIZE];
    float pointSize;
    BYTE bold, italic, underline, strikeout;
} MyFontParams;

typedef struct {
    char *def;
    MyFontParams mfp;
    LOGFONT lf;
    HFONT hf;
} MyFont;

typedef struct {
    COLORREF color;
    int effects;
    char *name;
} MyColorizeAttribs;

typedef struct {
    char* name;
    void* data;
} MySound;

typedef struct {
    COLORREF color;
    int effects;
    MySound sound;
} MyTextAttribs;

typedef char GetFunc(void *getClosure);

typedef struct {
    int   piece;  
    POINT pos;      /* window coordinates of current pos */
    POINT lastpos;  /* window coordinates of last pos - used for clipping */
    POINT from;     /* board coordinates of the piece's orig pos */
    POINT to;       /* board coordinates of the piece's new pos */
} AnimInfo;

typedef struct {
    POINT start;    /* window coordinates of start pos */
    POINT pos;      /* window coordinates of current pos */
    POINT lastpos;  /* window coordinates of last pos - used for clipping */
    POINT from;     /* board coordinates of the piece's orig pos */
} DragInfo;

typedef struct {
    POINT sq[2];	  /* board coordinates of from, to squares */
} HighlightInfo;

typedef struct {
    char *label;
    int id;
    HWND hwnd;
    WNDPROC wndproc;
} MyButtonDesc;

typedef struct _InputSource {
    CPKind kind;
    HANDLE hFile;
    SOCKET sock;
    int lineByLine;
    HANDLE hThread;
    DWORD id;
    char buf[INPUT_SOURCE_BUF_SIZE];
    char *next;
    DWORD count;
    int error;
    InputCallback func;
    struct _InputSource *second;  /* for stderr thread on CPRcmd */
    VOIDSTAR closure;
} InputSource;

typedef struct {
    HWND hDlg, hText;
    int sizeX, sizeY, newSizeX, newSizeY;
    HDWP hdwp;
} ResizeEditPlusButtonsClosure;

typedef struct {
    char *item;
    char *command;
    BOOLEAN getname;
    BOOLEAN immediate;
} IcsTextMenuEntry;

typedef struct {
    char *argName;
    ArgType argType;
    /***
    union {
    String *pString;       // ArgString
    int *pInt;             // ArgInt
    float *pFloat;         // ArgFloat
    Boolean *pBoolean;     // ArgBoolean
    COLORREF *pColor;      // ArgColor
    ColorClass cc;         // ArgAttribs
    String *pFilename;     // ArgFilename
    BoardSize *pBoardSize; // ArgBoardSize
    int whichFont;         // ArgFont
    DCB *pDCB;             // ArgCommSettings
    String *pFilename;     // ArgSettingsFilename
    } argLoc;
    ***/
    LPVOID argLoc;
    BOOL save;
} ArgDescriptor;

typedef struct {
    char piece;
    int command;
    char* name;
} DropEnable;


typedef struct {
    char *label;
    unsigned value;
} ComboData;

typedef struct {
    char *label;
    char *name;
} SoundComboData;

typedef struct {
    int item;
    int flags;
} Enables;


#define DSTEP        0
#define DLOG         1
#define DDATA	     2
#define DCON	     3
#define	DYQ 	     4
#define TIE_NUM      5

struct list_t {
    uint8 p, n;
};

#define MAX_GAME_LENGTH 1024

struct Record
{   
    uint8  nonCap;
    uint8  ischeck;
    //sint16 posVal;
    uint32 move;
    uint64 key;
};

struct move_stack_t {
    int move;
    int score;
};

struct book_face_info_t {
	sint8 result;       //2,1,0,-1,-2;
	uint8 step;         //棋步，最大２５５
	uint8 rate;         //比重，０～１００％
	uint8 isuse;        //是不是允许使用本棋步
};

struct book_face_t {
	uint8  f33[33];
	book_face_info_t info[1];
};


#ifdef USE_BerKeley_DB

typedef struct stock_dbs_t {
	
	DB_ENV *Env;

	DB *book;			//这是当前使用的的book;
	DB *back_db;           //这个是系统缺省的book;

	char *book_db_name;
	char *good_db_name;

	BOOL Book_Init_Ok;

} STOCK_DBS;

#endif

struct position_t {


    //uint8     board_[256];
    //uint8     *board;                 //棋子p256
    uint8     b256[256];
    list_t    piece_list[256];          //
    uint16    wBitRanks[16];
    uint16    wBitFiles[16];
    int       gply;
    int       curStep;                  //当前步子
    int       side;
    Record    His[MAX_GAME_LENGTH];


	move_stack_t* pMend;
    move_stack_t  all_move[128];

	book_face_t book_face[1];


};

typedef struct _CPS {
    //char *which;                //是第一个还是第二个

    //int msTotal;                  //局时
    //int msStep;                   //步时
    //int msFirst;                  //是不是第一时间段

    //HWND hwndHide;
    //HWND hwndParent;
    //dispboard_t* DIS;


	struct _CPS * loadWhich;        //加载那一个引擎，是first,还是second
	struct _CPS * loadPre;          //


	BOOL          isInLoading;      //引擎正在加载之中，
	BOOL          isUpLoading;      //引擎正在卸载之中
	HWND          loadWin;			//加载引擎的窗口

	position_t          pos[1];			//用来显示棋步用
	int                 pdmove;				//后台思考的棋步的名称
	

    int table;

    //char UCCI_which[128]; 
    //int  UCCI_which;             
    int  UCCI_initDone;        //引擎是不是准备好了
    //bool working;            //引擎正在工作
    int  playWhat;             //cps走红棋

    int  rep_eat_or_check;      //引擎连将或连捉

    //char *yqName;             //
    BOOL maybeThinking;
	BOOL maybePonering;
    ProcRef pr;
    InputSourceRef isr;
    //char *twoMachinesColor; /* "white\n" or "black\n" */ 
    //struct _CPS *other;
    //int sendTime;   /* 0=don't, 1=do, 2=test */
    int sendDrawOffers;
    int useSigint;
    int useSigterm;
    int offeredDraw; /* countdown */
    int reuse;
    int useSetboard; /* 0=use "edit"; 1=use "setboard" */
    int useSAN;      /* 0=use coordinate notation; 1=use SAN */
    int usePing;     /* 0=not OK to use ping; 1=OK */
    int lastPing;
    int lastPong;
    int usePlayother;/* 0=not OK to use playother; 1=OK */
    int useColors;   /* 0=avoid obsolete white/black commands; 1=use them */
    int useUsermove; /* 0=just send move; 1=send "usermove move" */
    int sendICS;     /* 0=don't use "ics" command; 1=do */
    int sendName;    /* 0=don't use "name" command; 1=do */
    int sdKludge;    /* 0=use "sd DEPTH" command; 1=use "depth\nDEPTH" */
    int stKludge;    /* 0=use "st TIME" command; 1=use "level 1 TIME" */
    char tidy[MSG_SIZ];
    int  matchWins;
    char variants[MSG_SIZ];
    int  analysisSupport;
    int  analyzing;

    int  ICS_id;
    //int  ICS_language;      //是用中文，就是１，反之是０
    int  ICS_net_id;
    char ICS_user[64];
    char ICS_pass[64];
    char ICS_info[256];

    char ICS_net_name[128];
    char ICS_net_host[256];
    int  ICS_net_port;
    char ICS_net_type[128];
    char ICS_net_info[256];


	//BOOL    clockMode;				//是不是计时方式

	BOOL 	IsBaoGan;	         //是否包干计时
	int     BaoGanTime;			//包干计时时间

    int		timePerStep;		//每步搜索时间
    int		timeSearchDepth;	//最大搜索深度    
    
	int     time_1_Step;		//第一阶段时间内要走多少步
	int     time_1_Time;

	int     time_2_Step;
	int     time_2_Time;

	int     timePerStepAdd;
	int     timeIsLost;         //超时判断负    

    //int     isPonderThink;      //是否后台思考
    int     useBook;			//是否使用棋库
    int     isEGB;              //有残局库
    int     isAutoLearn;        //是否自动学习

    char      szHost[256];

    int       yqID;             //引擎编号
    int		  ucci;				//程序的UCCI协议

    //int       Changed_ControlTime;
    //int       Already_Send_Initinfo;

	char      UCCI_ponderMove[32];	//后台思考的棋步
	BOOL      UCCI_havePonder;      //有后台思考棋步

    char      UCCI_name[64];
    char      UCCI_file[64];		//引擎文件名
    char      UCCI_path[MAX_PATH];	//这个是相对于主程序的引擎目录

    char      UCCI_copyright[128];
    char      UCCI_author[128];
    char      UCCI_user[64];
    char      UCCI_verson[16];
    int       UCCI_elo;

    bool      UCCI_batch;
    bool      UCCI_debug;
    bool      UCCI_usemillisec;

    /*BOOL      UCCI_ponder;*/
    //bool      UCCI_usebook;
    //bool      UCCI_useegtb;

	BOOL      UCCI_haveselfBook;		//有自己的开局库

    char      UCCI_iniString[256];
    char      UCCI_otherString[256];
    char      UCCI_addInfo[256];
    int       UCCI_smpNum;


    //char      UCCI_bookfiles[MAX_PATH];
    //char      UCCI_egtbpaths[MAX_PATH];

    int       UCCI_hashsize;
    int       UCCI_threads;
    int       UCCI_drawmoves;
    int       UCCI_repetition;
    char      UCCI_pruning[32];    //裁剪程度
    char      UCCI_knowledge[32];  //知识大小
    char      UCCI_selectivity[32];//选择性(随机性)系数
    int       UCCI_style;
    int       UCCI_loadbook;
    int       UCCI_clearhash;
    int       UCCI_dualtime;
    //-------------------------------引擎设置保存内容
} ChessProgramState;

struct TimeDisp_t {
    int RemainTime;			//当前可用的时间
	int movetime;           //步时   
	int movestogo;          //要走多少步


	BOOL isBaoGan;
    //int  BaoGanTime;         //不是包干就是分段
    int inc;
    int c1time;
    int c1step;
    int c2time;
    int c2step;

    int SetStepTime;
    int SetDepth;

};

#define STARTED_NONE            0
#define STARTED_MOVES           1
#define STARTED_BOARD           2
//#define STARTED_OBSERVE         3
#define STARTED_HOLDINGS        4
#define STARTED_CHATTER         5
#define STARTED_COMMENT         6
#define STARTED_MOVES_NOHIDE    7
#define STARTED_PLAYER_LIST     8
#define STARTED_TABLE_LIST       9
#define STARTED_ROOM_DIR       10

//BUF_SIZE

#define ICS_BUF_SIZE   8192

struct ICS_t {

    //int  lastnotfinish;
    char buf[ICS_BUF_SIZE];
    int  buf_len;
    int  tkind;
    int  started;
    int  count; 
    //int  started;
    //int  i;
    //int  oldi;
    //int  tkind;
    //int  next_out;
    //int  leftover_len;
    //int  leftover_start;  
    char star_match[STAR_MATCH_N][MSG_SIZ];
    int  saveingComment;
    int  stage;      //当前的关位
    int  table;      //观战的棋局,或当前的桌面
    int  loggedOn;
    char ICS_183[8];  //183的开始加密串解密
    char ICS_name[32]; 

    char *p;
    ColorClass curColor;
    ColorClass prevColor;
};



typedef void (*DelayedEventCallback) (void* pDis);
typedef struct {

    HWND hwndThis; 

	HWND hwndSaveDlg; 


	BOOL               IsFenGame;          //是不是输入的残局


    int					whiteFlag;
    int					blackFlag;
    int					userOfferedDraw;
    HICON				iconCurrent;
    TimeDisp_t          TimeDisp[2];  //红黑两方面
    PGN  			    pgn[1];  
    position_t          pos[1];
    int					flipView;                       //改变了上下显示
    int					leftView;                       //改变了左右显示
    int					premoveToX ;
    int					premoveToY ;
    int					premoveFromX ;
    int					premoveFromY ;
    int					premovePromoChar ;
    int					gotPremove;	
    int					fromX;
    int					fromY;
    int					toX;
    int					toY;
    uint8     B256dis[MAX_GAME_LENGTH][256];        //每个历史局面
    char      parseList[MAX_GAME_LENGTH][16];       //每步的UCCI步名,这个也不用了吗? 
    char      moveListName[MAX_GAME_LENGTH][16];
    AnimInfo			animInfo;
    DragInfo			dragInfo;
    HighlightInfo		highlightInfo;
    HighlightInfo		premoveHighlightInfo;
    GameMode			gameMode;					// = BeginningOfGame;	
    ChessProgramState	first;
    ChessProgramState	second;
    ChessProgramState	ics;

    ChessProgramState   set_cps;					//当前正在设定的CPS

    int					matchMode;
    int					screenHeight;
    int					screenWidth;
    int					doingSizing;
    int					lastSizing;
    RECT				boardRect;
    int					boardX;
    int					boardY;
    int					startedFromSetupPosition;  
    int					winWidth;
    int					winHeight;
    char				messageText[MESSAGE_TEXT_MAX];
    int					pausing;

	BOOL                mustPonder;		//必须后台思考

    //********************************************************
    uint8  lastReq[256];
    uint8  lastDrawn[256];

	

	HighlightInfo lastDrawnHighlight;
	HighlightInfo lastDrawnPremove;
	int lastDrawnFlipView;
	int lastReqValid;
	int lastDrawnValid;

    int					 clockTimerEvent;
    int					 loadGameTimerEvent;
    int					 analysisTimerEvent;
    DelayedEventCallback delayedTimerCallback;
    int					 delayedTimerEvent;

	int   			    programStartTime;     //程序开始启动的时间
	int                 tickStartTM;          //引擎开始的ticked
    long				intendedTickLength;
	BOOL                clockMode;				//是不是计时方式   
    int					firstMove;		// = TRUE;
    int					ics_user_moved;
    int					pauseExamForwardMostMove;

    Boolean				sameAgain;
    int					recursive;
	bool                useMS;          // 是不是使用MS
	int					searchTime;     //
	int					tinyLayout;
    int					smallLayout;
    int					squareSize;
    int					lineGap;
	BoardSize    		bsize;
	char				DspinCmd[MSG_SIZ];    //每个输给的命令
    char				DspCmdbuf[4096];	  //界面命令缓冲行
	char				*variant;

	int                 book_move[128];		  //棋库走步
	int                 book_val[128];        //棋步的价值
	int                 book_num;
	int                 book_max_num;         //最好的棋步


	HANDLE				pieceBitmap[16];    //棋盘的14个棋子,因最后一个是14,所以得15
    HANDLE				chessQbBitmap;      //棋盘位图
    HANDLE				chessMask;          //透明掩码位图
    HANDLE				chessInve;
    HANDLE				piecePutDownBitmap; //放下棋子
    HANDLE				piecePickFromBitmap;

	HBRUSH				lightSquareBrush;
    HBRUSH				darkSquareBrush;
    HBRUSH				whitePieceBrush;
    HBRUSH				blackPieceBrush;
    HBRUSH				iconBkgndBrush;
    HBRUSH				outlineBrush;

    HPEN				gridPen;
    HPEN				highlightPen;
    HPEN				premovePen;
    NPLOGPALETTE		pLogPal;
    BOOL				paletteChanged;

	HPALETTE			hPal;

	
	
	int                 matchGames;
	BOOL                noChessProgram;
	char               *initialMode;

}dispboard_t;




typedef struct {
    int whitePieceColor;
    int blackPieceColor;
    int lightSquareColor;
    int darkSquareColor;
    int jailSquareColor;
    int highlightSquareColor;
    int premoveHighlightColor;
    int movesPerSession;
    int timeIncrement;
    char *initString;
    char *secondInitString;

    //Boolean firstPlaysBlack;
    //Boolean noChessProgram;         //有没有象棋引擎加载程序
    //char *firstHost;
    //char *secondHost;
    //char *bitmapDirectory;
    //char *remoteShell;
    char *remoteUser;
    float timeDelay;
    //char *timeControl;
    Boolean icsActive;
    //char *icsCommPort;  /* if set, use serial port instead of tcp host/port */
    //char *icsLogon;     /* Hack to permit variable logon scripts. */
    //char *icsHelper;
    Boolean icsInputBox;
    Boolean useTelnet;
    char *telnetProgram;
    //char *gateway;
    //char *loadGameFile;
    //int loadGameIndex;      /* game # within file */
    //char *saveGameFile;
    Boolean autoSaveGames;		//自动保存游戏
    //char *loadPositionFile;
    //int loadPositionIndex;  /* position # within file */
    //char *savePositionFile;
    //Boolean matchMode;
    //int matchGames;
    //Boolean monoMode;
    //Boolean debugMode;
    //Boolean clockMode;
    char *boardSize;
    //Boolean Iconic;
    ////char *searchTime;
    //int searchDepth;
    Boolean showCoords;
    char *clockFont;
    char *messageFont; /* WinBoard only */
    char *coordFont;
    char *font; /* xboard only: all other fonts */
    char *tagsFont; /* WinBoard only */
    char *commentFont; /* WinBoard only */
    char *icsFont; /* WinBoard only */
    Boolean ringBellAfterMoves;
    Boolean autoCallFlag;
    Boolean flipView;
    Boolean autoFlipView;
    char *cmailGameName; /* xboard only */
    //Boolean alwaysPromoteToQueen;
    //Boolean oldSaveStyle; //老的保存样式
    Boolean quietPlay;
    Boolean showThinking;
    Boolean ponderNextMove;
    Boolean periodicUpdates;
    Boolean autoObserve;
    Boolean autoComment;
    Boolean getMoveList;
    Boolean testLegality;
    int borderXoffset; /* xboard only */
    int borderYoffset; /* xboard only */
    Boolean titleInWindow; /* xboard only */
    Boolean localLineEditing; /* WinBoard only */
    //Boolean zippyTalk;
    //Boolean zippyPlay;
    int flashCount; /* Number of times to flash (xboard only) */
    int flashRate; /* Flashes per second (xboard only)  */
    char *pixmapDirectory; /* Path to XPM/XIM files to use (xboard only) */
    int msLoginDelay;  /* Delay per character (in msec) while sending
                       ICS logon script (xboard only) */
    Boolean colorize;	/* If True, use the following colors to color text */
    /* Strings for colors, as "fg, bg, bold" (strings used in xboard only) */
    char *colorShout;
    char *colorSShout;
    char *colorChannel1;
    char *colorChannel;
    char *colorKibitz;
    char *colorTell;
    char *colorChallenge;
    char *colorRequest;
    char *colorSeek;
    char *colorNormal;
    char *soundProgram; /* sound-playing program */
    char *soundShout;
    char *soundSShout;
    char *soundChannel1;
    char *soundChannel;
    char *soundKibitz;
    char *soundTell;
    char *soundChallenge;
    char *soundRequest;
    char *soundSeek;
    char *soundMove;
    char *soundIcsWin;
    char *soundIcsLoss;
    char *soundIcsDraw;
    char *soundIcsUnfinished;
    char *soundIcsAlarm;
    //棋谱文件的缺省目录*************************************************
    int  winWidth;					//保存窗口的上次宽度；
    int  pieceStyle;				//棋子风格
    int  moveType;
    char *path_mxq;

	char *remoteShell;
	char *gateway;

    int  wxf_is_get;                    //是否读取WXF棋局
    char *wxf_url;                  //http://www.clubxiangqi.com/viewer/wxfmoves.html?ID
    int  wxf_alread_read;           //已经学习的  http://www.clubxiangqi.com/viewer/wxfmoves.html?ID=15520488
    int  wxf_per_read;				//每次读入的棋局数目
    Boolean reuseFirst;
    Boolean reuseSecond;
    Boolean animateDragging; /* If True, animate mouse dragging of pieces */
    Boolean animate;	/* If True, animate non-mouse moves */
    int animSpeed;	/* Delay in milliseconds between animation frames */
    Boolean popupMoveErrors;
    Boolean popupExitMessage;
    int showJail;
    Boolean highlightLastMove;
    Boolean highlightDragging;
    Boolean blindfold;          /* if true, no pieces are drawn */
    Boolean premove;		/* true if premove feature enabled */ 
    Boolean premoveWhite;	/* true if premoving White first move  */ 
    char *premoveWhiteText;	/* text of White premove 1 */ 
    Boolean premoveBlack;	/* true if premoving Black first move */ 
    char *premoveBlackText;	/* text of Black premove 1 */ 
    Boolean icsAlarm;		/* true if sounding alarm at a certain time */	
    int icsAlarmTime;		/* time to sound alarm, in milliseconds */
    Boolean autoRaiseBoard;
    int fontSizeTolerance; /* xboard only */
    /*char *initialMode;*/
    //char *variant;
    //int firstProtocolVersion;
    //int secondProtocolVersion;
    Boolean showButtonBar;
    //char		*icsNames;
    int boardX;
    int boardY;
    int first_yqID;
    int second_yqID;

	HICON				iconWhite;
    HICON				iconBlack;
	int					buttonCount;  //鼠标的按钮

	BoardSize           bsize;
	BOOL                alwaysOnTop;
	MyFont				*Afont[NUM_SIZES][NUM_FONTS];

	COLORREF			AlightSquareColor;
    COLORREF			AdarkSquareColor;
    COLORREF			AwhitePieceColor; 
    COLORREF			AblackPieceColor;
    COLORREF			AhighlightSquareColor;
    COLORREF			ApremoveHighlightColor;
   

	MyTextAttribs       AtextAttribs[(int)NColorClasses];
	MySound				Asounds[(int)NSoundClasses];
	int					AsaveSettingsOnExit;
	int					AchessProgram;

	ProcRef				AicsPR;
	ChessProgramState   ACPSics;     //第三个引擎,一般来说是网站连接
	FILE			    *debugFP;
	InputSourceRef		AtelnetISR;
	InputSourceRef		AfromUserISR;

	CHARFORMAT			AconsoleCF;
	int					prevStderrPort;
	NPLOGPALETTE		ApLogPal;


	int					Aexiting;  
	int					Afrozen;
	int					oldMenuItemState[MENU_BAR_ITEMS];
	Boolean				alarmSounded;

	char	Ahistory[HISTORY_SIZE][1024];
	int		AhistIn;
	int		AhistP;

} AppData, *AppDataPtr;
typedef struct {
    char *title, *question, *replyPrefix;
    ProcRef pr;
} QuestionParams;
struct DLG_STRUCT {

	//HWND        hwndSaveGame;			//		保存棋局窗口句柄

    WNDPROC     consoleTextWindowProc;
    WNDPROC     consoleInputWindowProc;
    BOOLEAN     consoleEcho;
    
    InputSource *consoleInputSource;
    COLORREF	consoleBackgroundColor;

    HWND		hwndConsole;
    //bool        IsConsoleShow;
    HWND hText;
    HWND hInput;
    HWND dlgBook;          //棋库窗口
    HWND  hwndGoPlace;
    //
    HWND hwndICS_Board_List;    //棋局列表窗口
    //WN

};

//struct pgn_file_t {
//
//    int  isStart;
//    char Fen[128]; 
//    
//    //*****************data
//    int  pgn_score;            //计算得分
//    int  islearned;            //是不是学习过了
//    char pgn_event[64];
//    char pgn_date[32];
//    char pgn_round[32];
//    char pgn_site[32];
//    char pgn_white[32];
//    int  pgn_white_elo;
//    char pgn_black[32];
//    int  pgn_black_elo;
//    char pgn_result[16];
//    char pgn_format[8];
//    int  use_time1;
//    int  use_time2;
//    int  use_time3;
//    int  white_time;
//    int  black_time;
//    char result_other[16];      //红方断线什么的    
//    //*****************data
//};




#endif