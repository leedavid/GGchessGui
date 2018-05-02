#include "stdafx.h"
#include "chess.h"
#include "data.h"


//int NextRandChar[18];
//int ComRandSeed;
int   ComRandSeed;
int   IsSendRand  = 0;   //1, 刚发送, 2,已发送

ULONG_PTR m_nGdiplusToken;
AppData			appData;
dispboard_t	   *OBS[MAX_OBS_BOARD];
//DLG_STRUCT		DLG;
Tab_T           TAB;

HINSTANCE		hInst;									// 当前实例
HMODULE hMod;
HMODULE msft_mod;
HWND			hwndToolBar;
HWND			hStatusBar;

NOTIFYICONDATA	Note;									//托盘结构
HMENU			hPopupMenu;								//托盘菜单
TCHAR			szTitle[MAX_LOADSTRING];				// 标题栏文本
TCHAR			szWindowClass[MAX_LOADSTRING];			// 主窗口类名

TCHAR          *EvalInfo;

//  公共显示变量  End
ICS_t           ICS;
HANDLE			hDispThread;
HANDLE			hDispEvent;

TCHAR			installDir[MAX_PATH];			//软件运行目录
//TCHAR			szAppName[] = _T("GGchess");
//TCHAR			*variantNames[] = VARIANT_NAMES;

ArgDescriptor	argDescriptorIndirection =
				{ _T(""), ArgSettingsFilename, (LPVOID) NULL, FALSE };

char			P90ASC[92];
char            P256ASC[256];
int				LIST_ORDER_SJ = 0;        //棋库棋步是不是升降排序
//TCHAR           pUserName[256];
//DisStat_t            pDST[1];             //当前的线程状态

//uint32          Thread_Stat;          //当前的线程状态

//BOOL            ThCanLearn;             //可以学习了
//BOOL            ThOutLearn;             //已退出学习状态

ThStat_t       ThStat;

STOCK_DBS    MST[1];



