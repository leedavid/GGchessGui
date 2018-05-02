#include "resource.h"


#ifndef CHESS_DEFINE_H
#define CHESS_DEFINE_H

//#define 0 0

//#if __GNUC__ && !defined(_winmajor)
//#define oldDialog 0 /* cygwin doesn't define _winmajor; mingw does */
//#else
//#define oldDialog (_winmajor < 4)
//#endif

/* config.h.in.  Generated automatically from configure.in by autoheader.  */

/* Define if you have <sys/wait.h> that is POSIX.1 compatible.  */
/*#undef HAVE_SYS_WAIT_H*/

/* Define if you need to in order for stat and other things to work.  */
/*#undef _POSIX_SOURCE*/

/* Define as the return type of signal handlers (int or void).  */
/*#undef RETSIGTYPE*/

/* Define if you have the ANSI C header files.  */
#define STDC_HEADERS 1

/* Define if you can safely include both <sys/time.h> and <time.h>.  */
/*#undef TIME_WITH_SYS_TIME*/

/* Define if lex declares yytext as a char * by default, not a char[].  */
/*#undef YYTEXT_POINTER*/

/*#define FIRST_PTY_LETTER 'p'*/

//#define FEN_START_FLAG  "Z"

#define PGN_MAX_LINE 75
#define HAVE_FCNTL_H 1

#define HAVE_GETHOSTNAME 0

#define HAVE_GETTIMEOFDAY 0

/* Use our own random() defined in winboard.c. */
#define HAVE_RANDOM 1
//#define random myrandom
//#define srandom mysrandom

#define HAVE_SYS_SOCKET_H 0

/*#undef IBMRTAIX*/

#define LAST_PTY_LETTER 'q'

#define PATCHLEVEL "8"

#define PRODUCT "GGchess"

#define PTY_ITERATION

#define PTY_NAME_SPRINTF

#define PTY_TTY_NAME_SPRINTF

#define REMOTE_SHELL ""

/*#undef RTU*/

/*#undef UNIPLUS*/

#define USE_PTYS 0

#define VERSION "1.0"

/*#undef X_WCHAR*/

//#ifndef __BORLANDC__
//#define WIN32 1
//#else
//#define WIN32
//#endif
//
//#define ZIPPY 0

/* Define if you have the _getpty function.  */
/*#undef HAVE__GETPTY*/

/* Define if you have the ftime function.  */
#define HAVE_FTIME 1

/* Define if you have the grantpt function.  */
/*#undef HAVE_GRANTPT*/

/* Define if you have the rand48 function.  */
/*#undef HAVE_RAND48*/

/* Define if you have the sysinfo function.  */
/*#undef HAVE_SYSINFO*/

/* Define if you have the <lan/socket.h> header file.  */
/*#undef HAVE_LAN_SOCKET_H*/

/* Define if you have the <string.h> header file.  */
#define HAVE_STRING_H 1

/* Define if you have the <stropts.h> header file.  */
/*#undef HAVE_STROPTS_H*/

/* Define if you have the <sys/fcntl.h> header file.  */
#define HAVE_SYS_FCNTL_H 0

/* Define if you have the <sys/systeminfo.h> header file.  */
/*#undef HAVE_SYS_SYSTEMINFO_H*/

/* Define if you have the <sys/time.h> header file.  */
/*#undef HAVE_SYS_TIME_H*/

/* Define if you have the <unistd.h> header file.  */
/*#undef HAVE_UNISTD_H*/

/* Define if you have the i library (-li).  */
/*#undef HAVE_LIBI*/

/* Define if you have the seq library (-lseq).  */
/*#undef HAVE_LIBSEQ*/

/*
  Options
  -DEMULATE_RSH -DREMOTE_SHELL=\"\" is necessary on Windows 95, because it
    does not have its own rsh command.  It works better this way on NT too,
    because the NT rsh does not propagate signals to the remote process.
  -DATTENTION is included even though I haven't been able to send signals to
    child processes on Windows, because at least I can send them over rsh to
    Unix programs.  On Windows I send a newline instead, which wakes up the
    chess program if it's polling.  On my GNU Chess port the newline actually 
    works even for Move Now.
*/
#define EMULATE_RSH 1
//#define ATTENTION 1
//#undef ATTENTION 1

//#ifdef __BORLANDC__
//#define _strdup(x) strdup(x)
//#define STRICT
//#define _winmajor 3  /* windows 95 */
//#define SCF_DEFAULT 0x0000
//#define SCF_ALL 0x0004
//#endif


//#define	P(args)	args
typedef void *VOIDSTAR;
typedef char Boolean;
typedef char *String;
#define popen _popen
#define pclose _pclose
#ifndef TRUE
	#define TRUE  1
	#define FALSE 0
#endif
//#define PROTOVER                2       /* engine protocol version */

//#ifndef _amigados
//extern int StrCaseCmp (char *s1, char *s2);
//extern int ToLower (int c);
//extern int ToUpper (int c);
//#else
//#define StrCaseCmp Stricmp  /*  Use utility.library functions   */
//#include <proto/utility.h>
//#endif

#define StepNameTypeA    0		//正常的中国样式
#define StepNameTypeB    1
//#define D8add           33  
//#define D8ADD           0x21

//#define D8none          0x5a//33+90
//#define D8int           0x5a5a5a5a

#define D8none          0x7e//33+90
#define D8int           0x7e7e7e7e

#define LogBufSize      512

#define	DisW		    380
#define	DisH		    484
#define	DisOffX           5
#define	DisOffY          35
#define	ChessW		     38
#define	StackSize      4096
#define	ListSize        168
#define TIE_NUM           5

#define ABS(x) ((x)<0?-(x):(x))

#define BOARD_SIZE_X	9
#define BOARD_SIZE_Y    10

//#define Rto90(y)			((sq_t)(_RankTo90[(y)]))
//#define FRto90(x,y)         ((sq_t)(_RankTo90[(y)]+(x)))  //从F R 得到square90
//#define S90toF(sq)          _Square90ToFile[(sq)]
//#define S90toR(sq)          _Square90ToRank[(sq)]
//#define hwndTabID			33


#define	LoopBufSize                     512

#define DROP_RANK        -3
#define MAX_MOVES		1024
#define MSG_SIZ			512
#define DIALOG_SIZE		256
#define STAR_MATCH_N            16
#define MOVE_LEN		32
#define TIME_CONTROL		"5"	/* in minutes */
#define TIME_DELAY_QUOTE	"1.0"	/* seconds between moves */
#define TIME_DELAY              ((float) 1.0)
#define MOVES_PER_SESSION	40	/* moves per TIME_CONTROL */
#define TIME_INCREMENT          -1      /* if >= 0, MOVES_PER_SESSION unused */


#define ICS_HOST            "chessclub.com"
#define ICS_PORT	        "5000"
#define ICS_COMM_PORT           ""
#define FIRST_HOST			"localhost"
#define SECOND_HOST			"localhost"
#define TELNET_PROGRAM		"telnet"
#define MATCH_MODE			"False"
#define INIT_STRING			"new\nrandom\n"
#define WHITE_STRING		"white\ngo\n"
#define BLACK_STRING		"black\ngo\n"
#define COMPUTER_STRING         "computer\n"
#define REUSE_CHESS_PROGRAMS    1
#define WHITE_PIECE_COLOR	"#FFFFCC"
#define BLACK_PIECE_COLOR	"#202020"
#define LIGHT_SQUARE_COLOR	"#C8C365"
#define DARK_SQUARE_COLOR	"#77A26D"
#define JAIL_SQUARE_COLOR       "#808080"
#define HIGHLIGHT_SQUARE_COLOR	"#FFFF00"
#define PREMOVE_HIGHLIGHT_COLOR	"#FF0000"
#define BELLCHAR                '\007'
#define NULLCHAR                '\000'
#define FEATURE_TIMEOUT         1000 /*ms*/
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) > (b)) ? (a) : (b))



#define VARIANT_NAMES_NUM   24
#define VARIANT_NAMES { \
  "normal", \
  "normal", \
  "wildcastle", \
  "nocastle", \
  "fischerandom", \
  "bughouse", \
  "crazyhouse", \
  "losers", \
  "suicide", \
  "giveaway", \
  "twokings", \
  "kriegspiel", \
  "atomic", \
  "3check", \
  "shatranj", \
  "wild29", \
  "wild30", \
  "wild31", \
  "wild32", \
  "wild33", \
  "wild34", \
  "wild35", \
  "wild36", \
  "unknown" \
}

#define Max(x,y) (((x)>(y))?(x):(y))
#define Min(x,y) (((x)<(y))?(x):(y))

#define NoProc ((ProcRef) 0)

#define CPReal 1
#define CPComm 2
#define CPSock 3
#define CPRcmd 4

/* Static */
#define POSITION_FILT "Position files (*.fen,*.epd,*.pos)\0*.fen;*.epd;*.pos\0All files (*.*)\0*.*\0"
#define GAME_FILT     "Game files (*.pgn,*.gam)\0*.pgn;*.gam\0All files (*.*)\0*.*\0"
#define SOUND_FILT    "Wave files (*.wav)\0*.wav\0All files (*.*)\0*.*\0"
#define OUTER_MARGIN (pDis->tinyLayout ? 0 : 4)
#define INNER_MARGIN (pDis->tinyLayout ? 0 : 2)
#define MESSAGE_LINE_LEFTMARGIN 2
#define MESSAGE_TEXT_MAX 256
/*#define COLOR_ECHOOFF RGB(192,192,192)*/
#define COLOR_ECHOOFF DLG.consoleBackgroundColor
#define WRAP_INDENT 200

/* Settable */
#define FIRST_CHESS_PROGRAM		"ELEEYE.EXE"
#define FIRST_DIRECTORY			"plugins\\ElephantEye\\"
#define SECOND_CHESS_PROGRAM	"ELEEYE.EXE"
#define SECOND_DIRECTORY		"plugins\\ElephantEye\\"

#define CLOCK_FONT_TINY        "Arial:9.0 b"
#define CLOCK_FONT_TEENY       "Arial:9.0 b"
#define CLOCK_FONT_DINKY       "Arial:10.0 b"
#define CLOCK_FONT_PETITE      "Arial:10.0 b"
#define CLOCK_FONT_SLIM        "Arial:12.0 b"
#define CLOCK_FONT_SMALL       "Arial:14.0 b"
#define CLOCK_FONT_MEDIOCRE    "Arial:14.0 b"
#define CLOCK_FONT_MIDDLING    "Arial:14.0 b"
#define CLOCK_FONT_AVERAGE     "Arial:15.0 b"
#define CLOCK_FONT_MODERATE    "Arial:16.0 b"
#define CLOCK_FONT_MEDIUM      "Arial:16.0 b"
#define CLOCK_FONT_BULKY       "Arial:17.0 b"
#define CLOCK_FONT_LARGE       "Arial:19.0 b"
#define CLOCK_FONT_BIG         "Arial:20.0 b"
#define CLOCK_FONT_HUGE        "Arial:21.0 b"
#define CLOCK_FONT_GIANT       "Arial:22.0 b"
#define CLOCK_FONT_COLOSSAL    "Arial:23.0 b"
#define CLOCK_FONT_TITANIC     "Arial:24.0 b"

#define MESSAGE_FONT_TINY      "Small Fonts:6.0"
#define MESSAGE_FONT_TEENY     "Small Fonts:6.0"
#define MESSAGE_FONT_DINKY     "Small Fonts:7.0"
#define MESSAGE_FONT_PETITE    "Small Fonts:7.0"
#define MESSAGE_FONT_SLIM      "Arial:8.0 b"
#define MESSAGE_FONT_SMALL     "Arial:9.0 b"
#define MESSAGE_FONT_MEDIOCRE  "Arial:9.0 b"
#define MESSAGE_FONT_MIDDLING  "Arial:9.0 b"
#define MESSAGE_FONT_AVERAGE   "Arial:10.0 b"
#define MESSAGE_FONT_MODERATE  "Arial:10.0 b"
#define MESSAGE_FONT_MEDIUM    "Arial:10.0 b"
#define MESSAGE_FONT_BULKY     "Arial:10.0 b"
#define MESSAGE_FONT_LARGE     "Arial:10.0 b"
#define MESSAGE_FONT_BIG       "Arial:11.0 b"
#define MESSAGE_FONT_HUGE      "Arial:11.0 b"
#define MESSAGE_FONT_GIANT     "Arial:11.0 b"
#define MESSAGE_FONT_COLOSSAL  "Arial:12.0 b"
#define MESSAGE_FONT_TITANIC   "Arial:12.0 b"

#define COORD_FONT_TINY        "Small Fonts:4.0"
#define COORD_FONT_TEENY       "Small Fonts:4.0"
#define COORD_FONT_DINKY       "Small Fonts:5.0"
#define COORD_FONT_PETITE      "Small Fonts:5.0"
#define COORD_FONT_SLIM        "Small Fonts:6.0"
#define COORD_FONT_SMALL       "Small Fonts:7.0"
#define COORD_FONT_MEDIOCRE    "Small Fonts:7.0"
#define COORD_FONT_MIDDLING    "Small Fonts:7.0"
#define COORD_FONT_AVERAGE     "Arial:7.0 b"
#define COORD_FONT_MODERATE    "Arial:7.0 b"
#define COORD_FONT_MEDIUM      "Arial:7.0 b"
#define COORD_FONT_BULKY       "Arial:7.0 b"
#define COORD_FONT_LARGE       "Arial:7.0 b"
#define COORD_FONT_BIG         "Arial:8.0 b"
#define COORD_FONT_HUGE        "Arial:8.0 b"
#define COORD_FONT_GIANT       "Arial:8.0 b"
#define COORD_FONT_COLOSSAL    "Arial:9.0 b"
#define COORD_FONT_TITANIC     "Arial:9.0 b"

//#define CONSOLE_FONT_TINY      "Courier New:12.0"
//#define CONSOLE_FONT_TEENY     "Courier New:12.0"
//#define CONSOLE_FONT_DINKY     "Courier New:12.0"
//#define CONSOLE_FONT_PETITE    "Courier New:12.0"
//#define CONSOLE_FONT_SLIM      "Courier New:12.0"
//#define CONSOLE_FONT_SMALL     "Courier New:12.0"
//#define CONSOLE_FONT_MEDIOCRE  "Courier New:12.0"
//#define CONSOLE_FONT_MIDDLING  "Courier New:12.0"
//#define CONSOLE_FONT_AVERAGE   "Courier New:12.0"
//#define CONSOLE_FONT_MODERATE  "Courier New:12.0"
//#define CONSOLE_FONT_MEDIUM    "Courier New:12.0"
//#define CONSOLE_FONT_BULKY     "Courier New:12.0"
//#define CONSOLE_FONT_LARGE     "Courier New:12.0"
//#define CONSOLE_FONT_BIG       "Courier New:12.0"
//#define CONSOLE_FONT_HUGE      "Courier New:12.0"
//#define CONSOLE_FONT_GIANT     "Courier New:12.0"
//#define CONSOLE_FONT_COLOSSAL  "Courier New:12.0"
//#define CONSOLE_FONT_TITANIC   "Courier New:12.0"

//#define CONSOLE_FONT_TINY      "Fixedsys:8.0"
//#define CONSOLE_FONT_TEENY     "Fixedsys:8.0"
//#define CONSOLE_FONT_DINKY     "Fixedsys:8.0"
//#define CONSOLE_FONT_PETITE    "Fixedsys:8.0"
//#define CONSOLE_FONT_SLIM      "Fixedsys:8.0"
//#define CONSOLE_FONT_SMALL     "Fixedsys:8.0"
//#define CONSOLE_FONT_MEDIOCRE  "Fixedsys:8.0"
//#define CONSOLE_FONT_MIDDLING  "Fixedsys:8.0"
//#define CONSOLE_FONT_AVERAGE   "Fixedsys:8.0"
//#define CONSOLE_FONT_MODERATE  "Fixedsys:8.0"
//#define CONSOLE_FONT_MEDIUM    "Fixedsys:8.0"
//#define CONSOLE_FONT_BULKY     "Fixedsys:8.0"
//#define CONSOLE_FONT_LARGE     "Fixedsys:8.0"
//#define CONSOLE_FONT_BIG       "Fixedsys:8.0"
//#define CONSOLE_FONT_HUGE      "Fixedsys:8.0"
//#define CONSOLE_FONT_GIANT     "Fixedsys:8.0"
//#define CONSOLE_FONT_COLOSSAL  "Fixedsys:8.0"
//#define CONSOLE_FONT_TITANIC   "Fixedsys:8.0"

#define CONSOLE_FONT_TINY      "Fixedsys:7.0"
#define CONSOLE_FONT_TEENY     "Fixedsys:7.0"
#define CONSOLE_FONT_DINKY     "Fixedsys:7.0"
#define CONSOLE_FONT_PETITE    "Fixedsys:7.0"
#define CONSOLE_FONT_SLIM      "Fixedsys:7.0"
#define CONSOLE_FONT_SMALL     "Fixedsys:7.0"
#define CONSOLE_FONT_MEDIOCRE  "Fixedsys:7.0"
#define CONSOLE_FONT_MIDDLING  "Fixedsys:7.0"
#define CONSOLE_FONT_AVERAGE   "Fixedsys:7.0"
#define CONSOLE_FONT_MODERATE  "Fixedsys:7.0"
#define CONSOLE_FONT_MEDIUM    "Fixedsys:7.0"
#define CONSOLE_FONT_BULKY     "Fixedsys:7.0"
#define CONSOLE_FONT_LARGE     "Fixedsys:7.0"
#define CONSOLE_FONT_BIG       "Fixedsys:7.0"
#define CONSOLE_FONT_HUGE      "Fixedsys:7.0"
#define CONSOLE_FONT_GIANT     "Fixedsys:7.0"
#define CONSOLE_FONT_COLOSSAL  "Fixedsys:7.0"
#define CONSOLE_FONT_TITANIC   "Fixedsys:7.0"

//#define CONSOLE_FONT_TINY      "Fixedsys:6.0"
//#define CONSOLE_FONT_TEENY     "Fixedsys:6.0"
//#define CONSOLE_FONT_DINKY     "Fixedsys:6.0"
//#define CONSOLE_FONT_PETITE    "Fixedsys:6.0"
//#define CONSOLE_FONT_SLIM      "Fixedsys:6.0"
//#define CONSOLE_FONT_SMALL     "Fixedsys:6.0"
//#define CONSOLE_FONT_MEDIOCRE  "Fixedsys:6.0"
//#define CONSOLE_FONT_MIDDLING  "Fixedsys:6.0"
//#define CONSOLE_FONT_AVERAGE   "Fixedsys:6.0"
//#define CONSOLE_FONT_MODERATE  "Fixedsys:6.0"
//#define CONSOLE_FONT_MEDIUM    "Fixedsys:6.0"
//#define CONSOLE_FONT_BULKY     "Fixedsys:6.0"
//#define CONSOLE_FONT_LARGE     "Fixedsys:6.0"
//#define CONSOLE_FONT_BIG       "Fixedsys:6.0"
//#define CONSOLE_FONT_HUGE      "Fixedsys:6.0"
//#define CONSOLE_FONT_GIANT     "Fixedsys:7.0"
//#define CONSOLE_FONT_COLOSSAL  "Fixedsys:7.0"
//#define CONSOLE_FONT_TITANIC   "Fixedsys:7.0"

#define COMMENT_FONT_TINY      "Arial:9.0"
#define COMMENT_FONT_TEENY     "Arial:9.0"
#define COMMENT_FONT_DINKY     "Arial:9.0"
#define COMMENT_FONT_PETITE    "Arial:9.0"
#define COMMENT_FONT_SLIM      "Arial:9.0"
#define COMMENT_FONT_SMALL     "Arial:9.0"
#define COMMENT_FONT_MEDIOCRE  "Arial:9.0"
#define COMMENT_FONT_MIDDLING  "Arial:9.0"
#define COMMENT_FONT_AVERAGE   "Arial:9.0"
#define COMMENT_FONT_MODERATE  "Arial:9.0"
#define COMMENT_FONT_MEDIUM    "Arial:9.0"
#define COMMENT_FONT_BULKY     "Arial:9.0"
#define COMMENT_FONT_LARGE     "Arial:9.0"
#define COMMENT_FONT_BIG       "Arial:9.0"
#define COMMENT_FONT_HUGE      "Arial:9.0"
#define COMMENT_FONT_GIANT     "Arial:9.0"
#define COMMENT_FONT_COLOSSAL  "Arial:9.0"
#define COMMENT_FONT_TITANIC   "Arial:9.0"

#define EDITTAGS_FONT_TINY     "Courier New:8.0"
#define EDITTAGS_FONT_TEENY    "Courier New:8.0"
#define EDITTAGS_FONT_DINKY    "Courier New:8.0"
#define EDITTAGS_FONT_PETITE   "Courier New:8.0"
#define EDITTAGS_FONT_SLIM     "Courier New:8.0"
#define EDITTAGS_FONT_SMALL    "Courier New:8.0"
#define EDITTAGS_FONT_MEDIUM   "Courier New:8.0"
#define EDITTAGS_FONT_MEDIOCRE "Courier New:8.0"
#define EDITTAGS_FONT_MIDDLING "Courier New:8.0"
#define EDITTAGS_FONT_AVERAGE  "Courier New:8.0"
#define EDITTAGS_FONT_MODERATE "Courier New:8.0"
#define EDITTAGS_FONT_BULKY    "Courier New:8.0"
#define EDITTAGS_FONT_LARGE    "Courier New:8.0"
#define EDITTAGS_FONT_BIG      "Courier New:8.0"
#define EDITTAGS_FONT_HUGE     "Courier New:8.0"
#define EDITTAGS_FONT_GIANT    "Courier New:8.0"
#define EDITTAGS_FONT_COLOSSAL "Courier New:8.0"
#define EDITTAGS_FONT_TITANIC  "Courier New:8.0"

#define COLOR_SHOUT            "#209000"
#define COLOR_SSHOUT         "b #289808"
#define COLOR_CHANNEL1         "#2020E0"
#define COLOR_CHANNEL        "b #4040FF"
#define COLOR_KIBITZ         "b #FF00FF"
#define COLOR_TELL             "#FF0000"  //"b  #FF0000"
#define COLOR_CHALLENGE     "bi #FF0000"
#define COLOR_REQUEST       "bi #FF0000"
#define COLOR_SEEK             "#980808"
#define COLOR_NORMAL           "#000000"
#define COLOR_NONE             "#000000"
#define COLOR_BKGD             "#FFFFFF"

#define SOUND_BELL "$"

#define BUILT_IN_SOUND_NAMES {\
	"Beepbeep", "Ching", "Click", "Cymbal", "Ding", "Drip", \
	"Gong", "Laser", "Move", "Penalty", "Phone", "Pop", "Pop2", \
	"Slap", "Squeak", "Swish", "Thud", "Whipcrack", \
	"Alarm", "Challenge", "Channel", "Channel1", "Draw", "Kibitz", \
	"Lose", "Request", "Seek", "Shout", "SShout", "Tell", "Unfinished", \
	"Win", NULL \
}

//#define SETTINGS_FILE         "GGchess.ini"
//
//#define ICS_LOGON             "ics.ini"

//#define ICS_NAMES "\
//chessclub.com /icsport=5000 /icshelper=timestamp\n\
//freechess.org /icsport=5000 /icshelper=timeseal\n\
//global.chessparlor.com /icsport=6000 /icshelper=timeseal\n\
//chessanytime.com /icsport=5000\n\
//chess.net /icsport=5000\n\
//zics.org /icsport=5000\n\
//jogo.cex.org.br /icsport=5000\n\
//ajedrez.cec.uchile.cl /icsport=5000\n\
//fly.cc.fer.hr /icsport=7890\n\
//freechess.nl /icsport=5000 /icshelper=timeseal\n\
//jeu.echecs.com /icsport=5000\n\
//chess.unix-ag.uni-kl.de /icsport=5000 /icshelper=timeseal\n\
//chess.mds.mdh.se /icsport=5000\n\
//"


//#define  UCCI_UCCI	0
//#define  UCCI_QH	1
//#define  UCCI_GG	2
//#define  UCCI_OHTER 3

//#define UCCI_NAMES "\
//ELEEYE.EXE /ElephantEye /UCCI_UCCI\n\
//QHPlugin.exe /Qianhong /UCCI_QH\n\
//keplugin.exe /ki11egg /UCCI_QH\n\
//"

#define ICS_TEXT_MENU_DEFAULT "\
-\n\
&Who,who,0,1\n\
Playe&rs,players,0,1\n\
&Games,games,0,1\n\
&Sought,sought,0,1\n\
|&Tell (name),tell,1,0\n\
M&essage (name),message,1,0\n\
-\n\
&Finger (name),finger,1,1\n\
&Vars (name),vars,1,1\n\
&Observe (name),observe,1,1\n\
&Match (name),match,1,1\n\
Pl&ay (name),play,1,1\n\
"

#define FCP_NAMES "\
GNUChess\n\
\"GNUChes5 xboard\"\n\
"

#define SCP_NAMES "\
GNUChess\n\
\"GNUChes5 xboard\"\n\
"
/* Values for flags arguments */
#define F_WHITE_ON_MOVE 1
//#define F_CHECK_CHECK   2         //要检查是不是将军了
//#define F_WHITE_KCASTLE_OK 2
//#define F_WHITE_QCASTLE_OK 4
//#define F_BLACK_KCASTLE_OK 8
//#define F_BLACK_QCASTLE_OK 16
//#define F_ALL_CASTLE_OK (F_WHITE_KCASTLE_OK | F_WHITE_QCASTLE_OK | \
//			 F_BLACK_KCASTLE_OK | F_BLACK_QCASTLE_OK)
//#define F_IGNORE_CHECK 32
//#define F_KRIEGSPIEL_CAPTURE 64 /* pawns can try to capture invisible pieces */
//#define F_ATOMIC_CAPTURE 128    /* capturing piece explodes, destroying itself
//				   and all non-pawns on adjacent squares; 
//				   destroying your own king is illegal */

/* Special epfile values */
#define EP_NONE -1
#define EP_UNKNOWN -2

#define MT_NONE 0
#define MT_CHECK 1
#define MT_CHECKMATE 2
#define MT_STALEMATE 3

#define SIZE_DEFAULTS \
{ { "Titanic",  129, 4, 34, 14, 14, 0, 0, 1200 }, \
  { "Colossal", 116, 4, 34, 14, 14, 0, 0, 1200 }, \
  { "Giant",    108, 3, 34, 14, 14, 0, 0, 1024 }, \
  { "Huge",     95, 3, 34, 14, 14, 0, 0, 1024 }, \
  { "Big",      87, 3, 34, 14, 14, 0, 0, 864 }, \
  { "Large",    80, 3, 34, 14, 14, 0, 0, 864 }, \
  { "Bulky",    72, 3, 34, 12, 14, 0, 0, 864 }, \
  { "Medium",   64, 3, 34, 12, 14, 0, 0, 768 }, \
  { "Moderate", 58, 3, 34, 12, 14, 0, 0, 768 }, \
  { "Average",  54, 2, 30, 11, 12, 0, 0, 600 }, \
  { "Middling", 49, 2, 24, 10, 12, 0, 0, 600 }, \
  { "Mediocre", 45, 2, 20, 10, 12, 1, 0, 600 }, \
  { "Small",    40, 2, 20, 10, 12, 1, 0, 480 }, \
  { "Slim",     37, 2, 20, 10, 12, 1, 0, 480 }, \
  { "Petite",   33, 1, 15, 9,  11, 1, 0, 480 }, \
  { "Dinky",    29, 1, 15, 9,  11, 1, 0, 480 }, \
  { "Teeny",    25, 1, 12, 8,  11, 1, 1, 480 }, \
  { "Tiny",     21, 1, 12, 8,  11, 1, 1, 0 }, \
  { NULL, 0, 0, 0, 0, 0, 0 } }

#define BORDER_X_OFFSET 3
#define BORDER_Y_OFFSET 27
//#define FIRST_CHESS_PROGRAM	"gnuchessx"
//#define SECOND_CHESS_PROGRAM	"gnuchessx"

/* Default to no flashing (the "usual" XBoard behavior) */
#define FLASH_COUNT	0		/* Number of times to flash */
#define FLASH_RATE	5		/* Flashes per second */

/* Default delay per character (in msec) while sending login script */
#define MS_LOGIN_DELAY  0

typedef int (*FileProc) (FILE *f, int n, char *title);
//void CatchDeleteWindow(Widget w, String procname);

#define TOPLEVEL 1 /* preference item; 1 = make popup windows toplevel */

//#define INFOFILE     "xboard.info"
//#define MANPAGE      "xboard.6"
//#define CLOCK_FONT   "-*-helvetica-bold-r-normal--*-*-*-*-*-*-*-*"
//#define COORD_FONT   "-*-helvetica-bold-r-normal--*-*-*-*-*-*-*-*"
//#define DEFAULT_FONT "-*-helvetica-medium-r-normal--*-*-*-*-*-*-*-*"

#define CLOCK_FONT 0
#define MESSAGE_FONT 1
#define COORD_FONT 2
#define CONSOLE_FONT 3
#define COMMENT_FONT 4
#define EDITTAGS_FONT 5
#define NUM_FONTS 6
/* Functions */





/* Constants */

//#define CLOCK_FONT 0
#define MESSAGE_FONT 1
//#define COORD_FONT 2
#define CONSOLE_FONT 3
#define COMMENT_FONT 4
#define EDITTAGS_FONT 5
#define NUM_FONTS 6

/* Positions of some menu items.  Origin is zero and separator lines count. */
/* It's gross that these are needed. */
#define ACTION_POS 2	 /* Posn of "Action" on menu bar */
#define OPTIONS_POS 4	 /* Posn of "Options" on menu bar */
#define ICS_POS 4 	 /* Posn of "ICS " on Options menu */
#define SOUNDS_POS 6     /* Posn of "Sounds" on Options menu */
/* end grossness */

#define WM_USER_ICS_INFO              (WM_USER + 4246)    //网站传送到每个棋盘的信息
#define WM_USER_MainBoard_Sized       (WM_USER + 4245)    //主窗口的大小改变了
#define WM_USER_Input                 (WM_USER + 4242)
#define WM_USER_Mouseleave            (WM_USER + 4243)
#define WM_USER_GetConsoleBackground  (WM_USER + 4244)

#define WM_USER_YqLoad_OK             (WM_USER + 4300)   //引擎加载成功了
#define WM_USER_YqUpload_OK           (WM_USER + 4301)   //引擎卸载成功了

#define WM_USER_BOOK_MOVE             (WM_USER + 43002)  //有棋库走步了

#define CLOCK_TIMER_ID        51
#define LOAD_GAME_TIMER_ID    52
#define ANALYSIS_TIMER_ID     53
#define MOUSE_TIMER_ID        54
#define DELAYED_TIMER_ID      55

#define SOLID_PIECE           0
#define OUTLINE_PIECE         1
#define WHITE_PIECE           2

#define COPY_TMP "wbcopy.tmp"
#define PASTE_TMP "wbpaste.tmp"

/* States for ics_getting_history */
#define H_FALSE 0
#define H_REQUESTED 1
#define H_GOT_REQ_HEADER 2
#define H_GOT_UNREQ_HEADER 3
#define H_GETTING_MOVES 4
#define H_GOT_UNWANTED_HEADER 5

/* whosays values for GameEnds */
#define GE_ICS 0
#define GE_ENGINE 1
#define GE_PLAYER 2
#define GE_FILE 3
#define GE_XBOARD 4

/* Maximum number of games in a cmail message */
#define CMAIL_MAX_GAMES 20

/* Different types of move when calling RegisterMove */
#define CMAIL_MOVE   0
#define CMAIL_RESIGN 1
#define CMAIL_DRAW   2
#define CMAIL_ACCEPT 3

/* Different types of result to remember for each game */
#define CMAIL_NOT_RESULT 0
#define CMAIL_OLD_RESULT 1
#define CMAIL_NEW_RESULT 2

/* Telnet protocol constants */
#define TN_WILL 0373
#define TN_WONT 0374
#define TN_DO   0375
#define TN_DONT 0376
#define TN_IAC  0377
#define TN_ECHO 0001
#define TN_SGA  0003
#define TN_PORT 23

#define HIGHLIGHT_PEN 0
#define PREMOVE_PEN   1
#define MF(x) {x, {0, }, {0, }, 0}

#define ARG_MAX 20000

#define PALETTESIZE 256

#define BUTTON_WIDTH (tinyLayout ? 16 : 32)
#define N_BUTTONS 11
#define MENU_BAR_ITEMS 6
#define INPUT_SOURCE_BUF_SIZE (4096*2)

#define ICS_TEXT_MENU_SIZE (IDM_CommandXLast - IDM_CommandX + 1)

#define dropEnNum       5

#define CO_MAX  100000
#define CO_TRIM   1000

#define MAX_CLIPS 200   /* more than enough */

#define ICS_GENERIC 0
#define ICS_ICC 1
#define ICS_FICS 2
#define ICS_CHESSNET 3 /* not really supported */




/* Board style 12 looks like this:
   
   <12> r-b---k- pp----pp ---bP--- ---p---- q------- ------P- P--Q--BP -----R-K W -1 0 0 0 0 0 0 paf MaxII 0 2 12 21 25 234 174 24 Q/d7-a4 (0:06) Qxa4 0 0
   
 * The "<12> " is stripped before it gets to this routine.  The two
 * trailing 0's (flip state and clock ticking) are later addition, and
 * some chess servers may not have them, or may have only the first.
 * Additional trailing fields may be added in the future.  
 */

#define PATTERN "%72c%c%d%d%d%d%d%d%d%s%s%d%d%d%d%d%d%d%d%s%s%s%d%d"

#define RELATION_OBSERVING_PLAYED    0
#define RELATION_OBSERVING_STATIC   -2   /* examined, oldmoves, or smoves */
#define RELATION_PLAYING_MYMOVE      1
#define RELATION_PLAYING_NOTMYMOVE  -1
#define RELATION_EXAMINING           2
#define RELATION_ISOLATED_BOARD     -3
#define RELATION_STARTING_POSITION  -4   /* FICS only */

#define XXOK		"_c"
//#define NOSCORE	    101
#define   SCORE_NO			101
#define   SCORE_B_WIN		0
#define   SCORE_B_GOOD		20
#define   SCORE_B_LITTLE	35
#define	  SCORE_BALANCE     50
#define   SCORE_R_LITTLE	68
#define   SCORE_R_GOOD		80
#define   SCORE_R_WIN		100


#define MYSQLCHAESET    "gbk" //"utf8"//"gbk"        //gb2312

//类型定义
typedef __int8  		sint8;
typedef __int8          sq_t; 
typedef unsigned char	uint8;
typedef signed short	sint16;
typedef unsigned short	uint16;
typedef signed int		sint32;
typedef unsigned int	uint32;
typedef int				inc_t;
//typedef int				sq_t;
//typedef uint16			mv_t;
//typedef sq_t            Board90[90];

//attack
#define PawnCheck       0x08				//兵将
#define PaoCheck        0x04				//炮将
#define CheCheck        0x01				//车将
#define MaCheck         0x02				//马将
//SendMessage(hStatusBar,SB_SETTEXT,StaBarCom,(LPARAM)buf);
#define StaBarCom       2 

#define MAX_LOADSTRING 100
#define IDI_TRAY			IDR_MENU_NOTE
#define WM_SHELLNOTIFY		WM_USER+5

#define HISTORY_SIZE 64
#define kFactor 4

#define DIS_LOG          0
#define DIS_YQA		     1
#define DIS_YQB          2

//#define inBoard(s256)                _nBoardIndex[s256]
#define StoX(s256)                  ((s256)&0xf)
#define StoY(s256)                  ((s256)>>4)
#define XYtoS(x,y)	                (((y)<<4) + (x))

#define IN_RSHI        (1<<0)
#define IN_BSHI        (1<<1)

#define IN_RXIANG      (1<<2)
#define IN_BXIANG      (1<<3)

#define IN_RKING       (1<<4)
#define IN_BKING       (1<<5)

#define IN_BSIDE       (1<<6)
#define IN_RSIDE       (1<<7)

#define xBitMask(s256)              _xBitMask[s256]
#define yBitMask(s256)              _yBitMask[s256]

enum  { KING=1, SHI=2, XIANG=3, MA=4, CHE=5, PAO=6, PAWN=7};

enum  {
       EMPTY=0,
       RKING=1,  RSHI=2,RXIANG=3, RMA=4, RCHE=5, RPAO=6, RPAWN=7,
       BKING=8,  BSHI=9,BXIANG=10,BMA=11,BCHE=12,BPAO=13,BPAWN=14,
       EMPTY16=16, OUTSIDE=32};

enum {  ICS_MXQ_CN      = 1,  
        ICS_QQ          = 2, 
        ICS_CHINAGAME   = 3, 
        ICS_OURGAME     = 4, 
        ICS_GAMEABC     = 5,
        ICS_MXQ_EN      = 6,
        ICS_MXQ_EN183   = 7,
        ICS_MXQ_CN183   = 8
       };

const int BanValue     = 29512;
const int BanTest      = 29216;

#define MATE_VALUE       30000
//#define DRAW_VALUE 0
#define KNOWN_WIN (2*Che_VAL)

#define UpMask(s256)                _UpMask[s256]
#define LoMask(s256)                _LoMask[s256]
#define RightMask(s256)             _RightMask[s256]
#define LeftMask(s256)              _LeftMask[s256]

#define RankMove(x,r16)            (&_smvRankMoveTab[x-3][r16])
#define FileMove(y,f16)            (&_smvFileMoveTab[y-3][f16])

#define RankMask(x,r16)            (&_smsRankMaskTab[x-3][r16])
#define FileMask(y,f16)            (&_smsFileMaskTab[y-3][f16])

#define Mirror(p256)               _cucMirrorSquare[p256]

#define DUpLeft                      1          //向上向左
#define DLoRight                     0          //向下向右


#define PieceList(pos,sq) ((pos)->piece_list[sq])
#define PieceListStart(pos,piece)   ((pos)->piece_list[(piece)].n)
#define NextPiece(pos,square) ((pos)->piece_list[square].n)
#define PrevPiece(pos,square) ((pos)->piece_list[square].p)

#define RemovePiece(pos,square) do {                                \
    NextPiece(pos,PrevPiece(pos,square)) = NextPiece(pos,square);   \
    PrevPiece(pos,NextPiece(pos,square)) = PrevPiece(pos,square);   \
  } while(0)

#define InsertPiece(pos,piece,square) do {               \
    NextPiece(pos,square) = PieceListStart(pos,piece);   \
    PrevPiece(pos,NextPiece(pos,square)) = square;       \
    PrevPiece(pos,square)    = piece;                    \
    PieceListStart(pos,piece) = square;                  \
  } while(0)

#define MovePiece(pos,from,to) do {                     \
    PieceList(pos,to) = PieceList(pos,from);            \
    PrevPiece(pos,NextPiece(pos,to)) = to;              \
    NextPiece(pos,PrevPiece(pos,to)) = to;              \
  } while(0)

#define LAST_DIS_SIDE(pdis)     (((pdis)->pos->gply%2==0)?WHITE:BLACK)

#define ICS_LINE_ADD()   { ICS.sstart_line ++; if(ICS.sstart_line > ICS_BUF_NUM){ICS.sstart_line = 0;} }

 /*       ICS.start_line ++;
        if(ICS.start_line > ICS_BUF_NUM){
            ICS.start_line = 0;
        }*/

//#define PieceListEnd (BK + 128 + 1)

#define PieceListEnd (BPAWN+8)          //棋子结尾

#define NULLMOVE                        0
#define NOMOVE                          1
#define FROM(x)                         (((x)>>8)&0xff)
#define TO(x)                           ((x)&0xff)
#define PIECE(x)                        (((x)>>16)&0xff)
#define CAPTURE(x)                      (((x)>>24)&0xff)

#define MOVE_FromTo(from,to)            (((from)<<8)|(to))

#define MOVE_FromFC(from,fc)            (((from)<<8)|((fc)<<16))    //frompiece

#define MOVE_FromFc_to_tc(fromfc,to,tc) ((fromfc)|(to)|((tc)<<24))
#define MOVE_FromFc_to(fromfc,to)       ((fromfc)|(to))
#define MOVE_FROM(from,fc,to,tc)        (((from)<<8)|(to)|((fc)<<16)|((tc)<<24))

enum {WHITE, BLACK, NEUTRAL};        //红方.黑方

#define   REPEAT_NO        0       //没有重复
#define   REPEAT_TRUE      1       //是真和棋
//#define   REPEAT_BAN_ME    3       //走子方走了禁着
#define   REPEAT_BAN_OTHER 4       //走子方走了禁着

const uint8 _PieceColor[16] = {
   //0, 
   NEUTRAL, 
   WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,      
   BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
   NEUTRAL,
};

#define COLOR(p14)     _PieceColor[p14]

#define IsWhite(p14)   (_PieceColor[p14] == WHITE)      //是不是红棋
#define IsBlack(p14)   (_PieceColor[p14] == BLACK)      //是不是黑棋

#define NotWhite(p14)   (_PieceColor[p14] != WHITE)      //是不是红棋
#define NotBlack(p14)   (_PieceColor[p14] != BLACK)      //是不是黑棋

#define ZOBRIST(p14,p256)  Zobrist[p14][p256]

//#define WhiteOnMove(move)	(((move) % 2) == 0)

#define FEN_SIZE                3200
#define MXQ_LOG_DELAY_MS        200

#endif




