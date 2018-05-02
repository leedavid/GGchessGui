#ifndef CHESS_CONST
#define CHESS_CONST




#undef FALSE
#define FALSE 0

#undef TRUE
#define TRUE 1

//#define BOOK_MOVE_USE_PLY    50                                  //最大使用的开局库步数
#define BOOK_MOVE_LEARN_PLY  64 //was                              //最大使用的学习步数
#define BOOK_BACK_MOVE      (BOOK_MOVE_LEARN_PLY - 2)              //备份棋库的步子

#define SCORE_WIDTH    95
//#define NO_BOOK_SCOER -1

////开局库的学习棋步数量
//static int BOOK_LEARN_NUM = 80;

//#define _MSC_VER   TRUE

#ifdef DEBUG
#  undef DEBUG
#  define DEBUG TRUE
#else
#  define DEBUG FALSE
#endif

#ifdef _MSC_VER
#  define S64_FORMAT "%I64d"
#  define U64_FORMAT "%016I64X"
#else
#  define S64_FORMAT "%lld"
#  define U64_FORMAT "%016llX"
#endif

// macros

#ifdef _MSC_VER
#  define S64(u) (u##i64)
#  define U64(u) (u##ui64)
#else
#  define S64(u) (u##LL)
#  define U64(u) (u##ULL)
#endif


#ifdef _MSC_VER
  typedef signed __int64   sint64;
  typedef unsigned __int64 uint64;
  //typedef unsigned __int16 sint16;
#else
  typedef signed long long int   sint64;
  typedef unsigned long long int uint64;
#endif

//    //你是不是初来乍到？
//const unsigned char CN183_IsFirstCome[32] = {
//        0xC4,0xE3,0xB2,0xBB,0xCA,0xC7,
//        0XB3,0xF5,0xC0,0xB4,0xD5,0xA7,
//        0xB5,0xBD,0xC2,0xF0,0x3F,0x3A,
//        0
//};

const TCHAR CN183_IsFirstCome[32] = {
	L"你不是初来乍到吗?:"
};

//-		ICS.tbuf	0x004fb258 L"\n你不是初来乍到吗?:\n"	wchar_t[0x00002000]


//const unsigned char CN183_UserName[32] = {
//	0xB5, 0xC7, 0xC2, 0xBD, 0xC3, 0xFB, 0x28,
//	0xD3, 0xA2, 0xCE, 0xC4, 0x29, 0x3A, 0
//};

const TCHAR CN183_UserName[32] = {
	L"登陆名(英文):"
};

//+		ICS.tbuf	0x004fb258 L"\n登陆名(英文):\n"	wchar_t[0x00002000]


//const unsigned char CN183_PassWord[16] = {
//    0xBF,0xDA,0xC1,0xEE,0x3A,0
//};

const TCHAR CN183_PassWord[16] = {
	L"口令:"
};
//+ICS.tbuf	0x004fb258 L"\n口令:\n"	wchar_t[0x00002000]





//常数

const sq_t _RankTo90[92] = {
	0, 9, 18,27,36,45,54,63,72,81,
	90,90,90,90,90,90,90,90,90,90,
	90,90,90,90,90,90,90,90,90,90,
	90,90,90,90,90,90,90,90,90,90,
	90,90,90,90,90,90,90,90,90,90,
	90,90,90,90,90,90,90,90,90,90,
	90,90,90,90,90,90,90,90,90,90,
	90,90,90,90,90,90,90,90,90,90,
	90,90,90,90,90,90,90,90,90,90,
	90,90
};
const sq_t _Square90ToFile[90] = {
	0,1,2,3,4,5,6,7,8,
	0,1,2,3,4,5,6,7,8,
	0,1,2,3,4,5,6,7,8,
	0,1,2,3,4,5,6,7,8,
	0,1,2,3,4,5,6,7,8,
	0,1,2,3,4,5,6,7,8,
	0,1,2,3,4,5,6,7,8,
	0,1,2,3,4,5,6,7,8,
	0,1,2,3,4,5,6,7,8,
	0,1,2,3,4,5,6,7,8,
};
const sq_t _Square90ToRank[90] = {
	0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,
	2,2,2,2,2,2,2,2,2,
	3,3,3,3,3,3,3,3,3,
	4,4,4,4,4,4,4,4,4,
	5,5,5,5,5,5,5,5,5,
	6,6,6,6,6,6,6,6,6,
	7,7,7,7,7,7,7,7,7,
	8,8,8,8,8,8,8,8,8,
	9,9,9,9,9,9,9,9,9,
};


const int YT_LX_AN[10] = {
	IDC_lX_1,
	IDC_LX_2,	
	IDC_LX_4,
	IDC_LX_5,
	IDC_LX_3,
	IDC_LX_6,
	IDC_LX_7,
	IDC_LX_8,
	IDC_LX_9,
	IDC_LX_10
};

//const sq_t _SquareOpp[90] = {     //得到对方的棋格
//	81,82,83,84,85,86,87,88,89,
//	72,73,74,75,76,77,78,79,80,
//	63,64,65,66,67,68,69,70,71,
//	54,55,56,57,58,59,60,61,62,
//	45,46,47,48,49,50,51,52,53,
//	36,37,38,39,40,41,42,43,44,
//	27,28,29,30,31,32,33,34,35,
//	18,19,20,21,22,23,24,25,26,
//	 9,10,11,12,13,14,15,16,17,
//	 0, 1, 2, 3, 4, 5, 6, 7, 8,
//};
//
//const sint16 FileRankMask[10] = {
//	1,2,4,8,16,32,64,128,256,512
//};                 //



TCHAR * const StartFen 
	= L"rnbakabnr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RNBAKABNR w - - 0 0";
TCHAR * const CanJu_StartFen
		= L"3k5/9/9/9/9/9/9/9/9/4K4 w - - 0 0";


const unsigned char A90toA256[90] = {
//   1     2     3     4     5     6     7     8    9
  0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b,
  0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b,
  0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b,
  0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b,
  0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b,
  0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b,
  0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b,
  0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 
  0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbb, 
  0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb,
//90    91
};

const TCHAR MXQ_4C9BDC[] = 
L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789~@#$%^&*()_+-=[]{};'.,<>?:|";
const TCHAR MXQ_4C9B80[] =
L"hk8acb{dJKLMNOsq$27WXY=[]};ABCVZvuxwzPQRf35jyloFGH~@#%^*()_+-:|nip&DEISTU6'.,<>?0914grtem";
const TCHAR MXQ_4C9B24[] =
L"sq27vuz#$%^&*(35jyCDEFemHIJR_+-=[]{};lABSYZon914gr~@)':|xhdKGLMNOPQfwip6k.,<>?TUVWX8acb0t";
const TCHAR MXQ_4C9AC8[] =
L"s};'.,<>?q2#5jyl8artABCDEXYZ$%^&*ecb091~@()_JKLMNOPFGHISTUVWQR+-=[]{:|4hkfdo7z3nip6gvuxwm";
const TCHAR MXQ_4C9A6C[] =
L"c~@#:|z35hHIJKLMNYk8a*jylABCDEFGZrtem^&o927()_+-=[]vnb%dfsqwip{OPQRSTUVWX};'.,<>?6$0ux14g";
const TCHAR MXQ_4C9A10[] =
L"bdxwhk^&*()_8acABCDELMNOPQRSz35j-@#=[]{};'ylonip6FGHIJKfsq~$%+.,<>?:|2rte7vuTUVWXYZ0914gm";
const TCHAR MXQ_4C99B4[] =
L"a$%_+-=[]{}wABCDEFGHIJKYZz35j9;'cb~@#.,<>?:|dvhk8^&ux7p60tem14gr*()yLMNOPQRSTUVWXlonifsq2";
const TCHAR MXQ_4C9958[] =
L"bOPQRSTUBCKLVdf2~@#sq$%^&=AMNWXYZ[],<>?:|7vu5jylogrtemnDEFGHIJi*()_+-hk8a{};'.cp609xwz314";
const TCHAR MXQ_4C98FC[] =
L"7vuxwz-BCWX=[]|35jAYZrtem0h:~@#_+k8a{};'.,<>?cbdf^&sq29DEFGHIJ1$%*()yKLMNOPQRSTUVlonip64g";
const TCHAR MXQ_4C98A0[] =
L"2h_+-=[]{MNOPQRSTUVW}k~@#uxwzylABHIJKLXYZo914nteb$%^&:|87vdfsq*();'.,<>?m3iCDEFGpac60gr5j";





const char ASCP90[128]  = {
//   0   1   2   3   4   5   6   7   8   9
	91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
	91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
	91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
	91, 91,  0,  1, 91,  3,  4,  5,  6, 91, 
//          32   !   "   #   $   %   &   '
	 8,  9, 10, 11, 12, 13, 14, 15, 16, 17,
//  (    )   *   +   ,   -   .   /   0   1  
    18, 19, 20, 21, 22, 23, 24, 25, 26, 27,
//   2   3   4   5   6   7   8   9   :   ;
    28, 29, 30, 31,  2, 32, 33, 34, 35, 36, 
//   <   =   >   ?   @   A   B   C   D   E
    37, 38, 39, 40, 41, 42, 43, 44, 45, 46,
//   F   G   H   I   J   K   L   M   N   O
    47, 48, 49, 50, 51, 52, 53, 54, 55, 56,
//   P   Q   R   S   T   U   V   W   X   Y
    57, 58, 91, 59,  7, 60, 91, 61, 62, 63,
//    Z  [   \   ]   ^   _   '   a   b   c
    64, 65, 66, 67, 68, 69, 70, 71, 72, 73,
//	 d   e   f   g   h   i   j   k   l   m
    74, 75, 76, 77, 78, 79, 80, 81, 82, 83,
//   n   o   p   q   r   s   t   u   v   w
	84, 85, 86, 87, 88, 89, 90, 91,
//   x   y   z   {   |    }  ~  DEl
};


typedef struct {
  TCHAR *name;
  int squareSize;
  int lineGap;
  int smallLayout;
  int tinyLayout;
  int cliWidth, cliHeight;
} SizeInfo;

typedef struct {
    int err;
    TCHAR* msg;
} ErrorMap;

const UINT WM_TASKBARCREATED = RegisterWindowMessage(TEXT("TaskbarCreated"));


#define STSIZE    64
//const char  ST_SCORE_STRING[][STSIZE] = {
//	"请选择棋局评价...",
//	"红方胜",
//	"红方大优",
//	"红方略优",
//	"双方均势",
//	"黑方略优",
//	"黑方大优",
//	"黑方胜"
//};
const sq_t ST_SCORE[8] = {
	SCORE_NO,
	SCORE_R_WIN,
	SCORE_R_GOOD,
	SCORE_R_LITTLE,
	SCORE_BALANCE ,
	SCORE_B_LITTLE,
	SCORE_B_GOOD,
	SCORE_B_WIN,

//#define   SCORE_NO			101
//#define   SCORE_B_WIN		0
//#define   SCORE_B_GOOD		35
//#define   SCORE_B_LITTLE	20
//#define	SCORE_BALANCE     50
//#define   SCORE_R_LITTLE	68
//#define   SCORE_R_GOOD		80
//#define   SCORE_R_WIN		100
};
const char ST_SAVEAS[][STSIZE]  = {
	"保存到MySql数据库(缺省)",
	"保存为PGN文件...",
	"保存为DHTML文件...",
	"保存为其它格式文件..."
};

enum {
    UCCI_NONE		= 0,
    UCCI_UCCI_ms	= 1,		//使用ms
    UCCI_QianHong	= 2,
    UCCI_QiBing		= 3,
    UCCI_GGchess    = 4,
    UCCI_OTHER		= 5,
    UCCI_CYC105		= 6,
    UCCI_UCCI_OLD	= 7,	    //使用s
    UCCI_CYC106		= 8,
	UCCI_DaShen		= 9,
};

//#define LOOK_AT  '\016'



//const char ST_UCCI[][STSIZE]   =  {
//	"请选择引擎协议...",
//	"象堡协议-UCCI",
//	"浅红协议-QHCI",
//	"佳佳协议-GGCI",
//	"其它协议-OTCI"
//};

//const  sq_t  initialPosition[90] = {
//	BlackChe,	BlackMa, BlackXiang,BlackShi,BlackKing,BlackShi,BlackXiang,BlackMa, BlackChe,
//	NOCHESS,	NOCHESS,   NOCHESS,     NOCHESS,   NOCHESS,    NOCHESS,   NOCHESS,     NOCHESS,   NOCHESS,
//	NOCHESS,    BlackPao,NOCHESS,     NOCHESS,   NOCHESS,    NOCHESS,   NOCHESS,     BlackPao,NOCHESS,
//	BlackPawn,NOCHESS,   BlackPawn, NOCHESS,   BlackPawn,NOCHESS,   BlackPawn, NOCHESS,   BlackPawn,
//	NOCHESS,	NOCHESS,   NOCHESS,     NOCHESS,   NOCHESS,    NOCHESS,   NOCHESS,     NOCHESS,   NOCHESS,
//	
//	NOCHESS,	NOCHESS,   NOCHESS,     NOCHESS,   NOCHESS,    NOCHESS,   NOCHESS,     NOCHESS,   NOCHESS,
//	WhitePawn,NOCHESS,   WhitePawn, NOCHESS,   WhitePawn,NOCHESS,   WhitePawn, NOCHESS,   WhitePawn,
//	NOCHESS,    WhitePao,NOCHESS,     NOCHESS,   NOCHESS,    NOCHESS,   NOCHESS,     WhitePao,NOCHESS,
//	NOCHESS,	NOCHESS,   NOCHESS,     NOCHESS,   NOCHESS,    NOCHESS,   NOCHESS,     NOCHESS,   NOCHESS,
//	WhiteChe,	WhiteMa, WhiteXiang,WhiteShi,WhiteKing,WhiteShi,WhiteXiang,WhiteMa, WhiteChe,
//};
//const sq_t twoKingsPosition[90]= {  //只有二个王的棋局
//	NOCHESS,	NOCHESS,   NOCHESS,    BlackKing, NOCHESS,     NOCHESS,   NOCHESS,     NOCHESS,   NOCHESS,
//	NOCHESS,	NOCHESS,   NOCHESS,    NOCHESS,     NOCHESS,     NOCHESS,   NOCHESS,     NOCHESS,   NOCHESS,
//	NOCHESS,	NOCHESS,   NOCHESS,    NOCHESS,     NOCHESS,     NOCHESS,   NOCHESS,     NOCHESS,   NOCHESS,
//	NOCHESS,	NOCHESS,   NOCHESS,    NOCHESS,     NOCHESS,     NOCHESS,   NOCHESS,     NOCHESS,   NOCHESS,
//	NOCHESS,	NOCHESS,   NOCHESS,    NOCHESS,     NOCHESS,     NOCHESS,   NOCHESS,     NOCHESS,   NOCHESS,
//	
//	NOCHESS,	NOCHESS,   NOCHESS,    NOCHESS,     NOCHESS,     NOCHESS,   NOCHESS,     NOCHESS,   NOCHESS,
//	NOCHESS,	NOCHESS,   NOCHESS,    NOCHESS,     NOCHESS,     NOCHESS,   NOCHESS,     NOCHESS,   NOCHESS,
//	NOCHESS,	NOCHESS,   NOCHESS,    NOCHESS,     NOCHESS,     NOCHESS,   NOCHESS,     NOCHESS,   NOCHESS,
//	NOCHESS,	NOCHESS,   NOCHESS,    NOCHESS,     NOCHESS,     NOCHESS,   NOCHESS,     NOCHESS,   NOCHESS,
//	NOCHESS,	NOCHESS,   NOCHESS,    NOCHESS,     WhiteKing, NOCHESS,   NOCHESS,     NOCHESS,   NOCHESS,
//};
const int SAMPLE_SQ_SIZE = 54;

const sint8 _nHorseLegTab[512] = {
                               0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,-16,  0,-16,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0, -1,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0, -1,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0, 16,  0, 16,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0
};

const uint16 _xBitMask[256] = 
{
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   1,   2,   4,   8,  16,  32,  64, 128, 256,   0,   0,   0,   0,
	0,   0,   0,   1,   2,   4,   8,  16,  32,  64, 128, 256,   0,   0,   0,   0,
	0,   0,   0,   1,   2,   4,   8,  16,  32,  64, 128, 256,   0,   0,   0,   0,
	0,   0,   0,   1,   2,   4,   8,  16,  32,  64, 128, 256,   0,   0,   0,   0,
	0,   0,   0,   1,   2,   4,   8,  16,  32,  64, 128, 256,   0,   0,   0,   0,
	0,   0,   0,   1,   2,   4,   8,  16,  32,  64, 128, 256,   0,   0,   0,   0,
	0,   0,   0,   1,   2,   4,   8,  16,  32,  64, 128, 256,   0,   0,   0,   0,
	0,   0,   0,   1,   2,   4,   8,  16,  32,  64, 128, 256,   0,   0,   0,   0,
	0,   0,   0,   1,   2,   4,   8,  16,  32,  64, 128, 256,   0,   0,   0,   0,
	0,   0,   0,   1,   2,   4,   8,  16,  32,  64, 128, 256,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0
};

const uint16 _yBitMask[256] = 
{
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0,   0,   0,   0,
	0,   0,   0,   2,   2,   2,   2,   2,   2,   2,   2,   2,   0,   0,   0,   0,
	0,   0,   0,   4,   4,   4,   4,   4,   4,   4,   4,   4,   0,   0,   0,   0,
	0,   0,   0,   8,   8,   8,   8,   8,   8,   8,   8,   8,   0,   0,   0,   0,
	0,   0,   0,  16,  16,  16,  16,  16,  16,  16,  16,  16,   0,   0,   0,   0,
	0,   0,   0,  32,  32,  32,  32,  32,  32,  32,  32,  32,   0,   0,   0,   0,
	0,   0,   0,  64,  64,  64,  64,  64,  64,  64,  64,  64,   0,   0,   0,   0,
	0,   0,   0, 128, 128, 128, 128, 128, 128, 128, 128, 128,   0,   0,   0,   0,
	0,   0,   0, 256, 256, 256, 256, 256, 256, 256, 256, 256,   0,   0,   0,   0,
	0,   0,   0, 512, 512, 512, 512, 512, 512, 512, 512, 512,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0
};

// 该数组很方便地实现了坐标的镜像(左右对称)
const uint8 _cucMirrorSquare[256] = {
  0, 0, 0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 0, 0, 0, 0,
  0, 0, 0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 0, 0, 0, 0,
  0, 0, 0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 0, 0, 0, 0,

  0, 0, 0, 0x3b, 0x3a, 0x39, 0x38, 0x37, 0x36, 0x35, 0x34, 0x33, 0, 0, 0, 0,
  0, 0, 0, 0x4b, 0x4a, 0x49, 0x48, 0x47, 0x46, 0x45, 0x44, 0x43, 0, 0, 0, 0,
  0, 0, 0, 0x5b, 0x5a, 0x59, 0x58, 0x57, 0x56, 0x55, 0x54, 0x53, 0, 0, 0, 0,
  0, 0, 0, 0x6b, 0x6a, 0x69, 0x68, 0x67, 0x66, 0x65, 0x64, 0x63, 0, 0, 0, 0,
  0, 0, 0, 0x7b, 0x7a, 0x79, 0x78, 0x77, 0x76, 0x75, 0x74, 0x73, 0, 0, 0, 0,
  0, 0, 0, 0x8b, 0x8a, 0x89, 0x88, 0x87, 0x86, 0x85, 0x84, 0x83, 0, 0, 0, 0,
  0, 0, 0, 0x9b, 0x9a, 0x99, 0x98, 0x97, 0x96, 0x95, 0x94, 0x93, 0, 0, 0, 0,
  0, 0, 0, 0xab, 0xaa, 0xa9, 0xa8, 0xa7, 0xa6, 0xa5, 0xa4, 0xa3, 0, 0, 0, 0,
  0, 0, 0, 0xbb, 0xba, 0xb9, 0xb8, 0xb7, 0xb6, 0xb5, 0xb4, 0xb3, 0, 0, 0, 0,
  0, 0, 0, 0xcb, 0xca, 0xc9, 0xc8, 0xc7, 0xc6, 0xc5, 0xc4, 0xc3, 0, 0, 0, 0,

  0, 0, 0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 0, 0, 0, 0,
  0, 0, 0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 0, 0, 0, 0,
  0, 0, 0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 0, 0, 0, 0,
};

//将256的棋格压缩成一个字节,只有将,相,仕可压缩
//const char B256ToByte[256] = {
//    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
//    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
//    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
//    0,   0,   0,  0xe,0xe,   2,   7,   8,   9,   7, 0xe, 0xe,   0,   0,   0,   0,
//    0,   0,   0,  0xe,0xe, 0xe,   4,   5,   6, 0xe, 0xe, 0xe,   0,   0,   0,   0,
//    0,   0,   0,    3,0xe, 0xe,   2,   1,   3, 0xe, 0xe,   6,   0,   0,   0,   0,
//    0,   0,   0,  0xe,0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe,   0,   0,   0,   0,
//    0,   0,   0,  0xe,0xe,   4, 0xe, 0xe, 0xe,   5, 0xe, 0xe,   0,   0,   0,   0,
//    0,   0,   0,  0xe,0xe,   4, 0xe, 0xe, 0xe,   5, 0xe, 0xe,   0,   0,   0,   0,
//    0,   0,   0,  0xe,0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe,   0,   0,   0,   0,
//    0,   0,   0,    3,0xe, 0xe,   2,   1,   3, 0xe, 0xe,   6,   0,   0,   0,   0,
//    0,   0,   0,  0xe,0xe, 0xe,   4,   5,   6, 0xe, 0xe, 0xe,   0,   0,   0,   0,
//    0,   0,   0,  0xe,0xe,   2,   7,   8,   9,   7, 0xe, 0xe,   0,   0,   0,   0,
//    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
//    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
//    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0
//};


const char B256ToByte[256] = {
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,  0xe,0xe,   2,   4,   8,   5,   7, 0xe, 0xe,   0,   0,   0,   0,
    0,   0,   0,  0xe,0xe, 0xe,   9,   1,   7, 0xe, 0xe, 0xe,   0,   0,   0,   0,
    0,   0,   0,    3,0xe, 0xe,   2,   6,   3, 0xe, 0xe,   1,   0,   0,   0,   0,
    0,   0,   0,  0xe,0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe,   0,   0,   0,   0,
    0,   0,   0,  0xe,0xe,   4, 0xe, 0xe, 0xe,   5, 0xe, 0xe,   0,   0,   0,   0,
    0,   0,   0,  0xe,0xe,   4, 0xe, 0xe, 0xe,   5, 0xe, 0xe,   0,   0,   0,   0,
    0,   0,   0,  0xe,0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe,   0,   0,   0,   0,
    0,   0,   0,    3,0xe, 0xe,   2,   6,   3, 0xe, 0xe,   1,   0,   0,   0,   0,
    0,   0,   0,  0xe,0xe, 0xe,   9,   1,   7, 0xe, 0xe, 0xe,   0,   0,   0,   0,
    0,   0,   0,  0xe,0xe,   2,   4,   8,   5,   7, 0xe, 0xe,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0
};

const int MXQ_ICS_BUT[12] = {
    IDC_ICS_CONNECT,        //连线或断线按钮
    IDC_ICS_SET,            //设置连线帐号     
    IDC_GO_PLACE,
    IDC_BUT_ICS_BOARD, 
	IDC_MORE_BUTTON,
    IDC_BUTTON7,
    IDC_BUTTON8, 
    IDC_BUTTON2,
};
const int OBS_BUT[2][10] = {
    {
     IDC_BUTTON1,
     IDC_BUTTON2,
     IDC_BUTTON3,
     IDC_BUTTON4,
     IDC_BUTTON5,
     IDC_BUTTON6,
     IDC_BUTTON7,
     IDC_BUTTON8,
     IDC_BUTTON9,
     IDC_BUTTON10
    },
    {
     IDC_BUTTON11,
     IDC_BUTTON12,
     IDC_BUTTON13,
     IDC_BUTTON14,
     IDC_BUTTON15,
     IDC_BUTTON16,
     IDC_BUTTON17,
     IDC_BUTTON18,
     IDC_BUTTON19,
     IDC_BUTTON20},
};

const int MXQ_ICS_PLACE[9] = {
    IDC_DIR_1,
    IDC_DIR_2,
    IDC_DIR_3,
    IDC_DIR_4,
    IDC_DIR_5,
    IDC_DIR_6,
    IDC_DIR_7,
    IDC_DIR_8,
    //IDC_DIR_9
};

#define DirNone                       0
#define DirUp                         (1<<0)
#define DirRight                      (1<<1)
#define DirLow                        (1<<2)
#define DirLeft                       (1<<3)
#define DirChe                        (DirUp+DirRight+DirLow+DirLeft)
#define DirMa                         (1<<4)
#define DirShi                        (1<<5)
#define DirXiang                      (1<<6)
#define DirKing                       (1<<7)
//#define GetDir(from,to)              _GetDir[from-to+256]

#define GetDir(from,to)               _GetDir[from][to] 

#define StoX(s256)   ((s256)&0xf)
#define StoY(s256)   ((s256)>>4)
#define XYtoS(x,y)	 (((y)<<4) + (x))

#define inBoard(s256)                _nBoardIndex[s256]
#define PawnCheck       0x08				//兵将
#define PaoCheck        0x04				//炮将
#define CheCheck        0x01				//车将
#define MaCheck         0x02				//马将

#define horseLegTab(s512)           _nHorseLegTab[s512]

const int King_VAL           =    10000;
const int Shi_VAL            =    170;          //170
const int Xiang_VAL          =    160;          //160
const int Che_VAL            =    1000;         //1000
const int Ma_VAL             =    400;          //400
const int Pao_VAL            =    400;          //400
const int Pawn_VAL           =    100;          //100
                                 //原先是256

const int _IsWhiteLargePiece[16] = {
	 //EMPTY=0,
             0,
    //RKING=1,  RSHI=2,RXIANG=3, RMA=4, RCHE=5, RPAO=6, RPAWN=7,
	         0,      0,       0,     1,      1,      0,       1,
    //BKING=8,  BSHI=9,BXIANG=10,BMA=11,BCHE=12,BPAO=13,BPAWN=14,
	         0,      0,       0,     0,      0,      0,       0,
			 0,
};

const int _IsBlackLargePiece[16] = {
	 //EMPTY=0,
             0,
    //RKING=1,  RSHI=2,RXIANG=3, RMA=4, RCHE=5, RPAO=6, RPAWN=7,
	         0,      0,       0,     0,      0,      0,       0,
    //BKING=8,  BSHI=9,BXIANG=10,BMA=11,BCHE=12,BPAO=13,BPAWN=14,	         
			 0,      0,       0,     1,      1,      0,       1,
			 0,
};


//#define IsWhiteLargePiece(piece)      _IsWhiteLargePiece[piece]
//#define IsBlackLargePiece(piece)      _IsBlackLargePiece[piece]

//是红的棋子,且不是过河兵
//#define IsWhiteLargePieceNoRiverPawn(piece)      (IsWhite(piece) ) 
//#define IsBlackLargePieceNoRiverPawn(piece)      (IsBlack(piece) )


//这个一起要考虑一下. 任何时候,常捉不过河的兵不算捉. 
//#define IsWhitePaoNoRiverPawn(sq)      ((pos->b256[sq] == RPAWN && StoY(sq) <= 0x7) || (pos->b256[sq] != RPAWN && IsWhite(pos->b256[sq])))
//#define IsBlackPaoNoRiverPawn(sq)      ((pos->b256[sq] == BPAWN && StoY(sq) >= 0x8) || (pos->b256[sq] != BPAWN && IsBlack(pos->b256[sq])))

#define EVAL_INFO_SIZE   (64*1024-1)

//当前的显示状态

const int TH_Importing       =    (1<<0);      //当前正在导入 
const int TH_Learning        =    (1<<1);      //当前正在学习
const int TH_OutLearningOK   =    (1<<2);      //已成功退出了学习状态

const sint16 PieceValues[16] = {

   //0, 
   0, 
   King_VAL, Shi_VAL, Xiang_VAL, Ma_VAL, Che_VAL, Pao_VAL, Pawn_VAL,
   King_VAL, Shi_VAL, Xiang_VAL, Ma_VAL, Che_VAL, Pao_VAL, Pawn_VAL,
};

const char _PIECE_ID[16] = {
            0,
            KING,SHI,XIANG,MA,CHE,PAO,PAWN,
            KING,SHI,XIANG,MA,CHE,PAO,PAWN,
            0,
       };
#define PIECE_ID(p14) _PIECE_ID[p14]


enum {
    NO_DRAW_NOW         =0, //现在还不知道是不是和棋
    REP_REP_NOCAP       =1,
    REP_REP_DRAW        =2, //双方走重复步子了
    REP_TRUE_DRAW       =3, //双方和棋了,不可能赢了

    WHITE_CHECK_BAN     =4, //红方连将,判负
    BLACK_CHECK_BAN     =5, //黑方连将,判负
    WHITE_CAP_BAN       =6, //红方连捉
    BLACK_CAP_BAN       =7, //黑方连捉
};

#define MAX_OBS_BOARD  201       //最大200桌,已用指针来实现了


	#define L3_DB_INI   "data\\ini.s3db"
    #define L3_DB_PGN   "data\\pgn.s3db"




#endif