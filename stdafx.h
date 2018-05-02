// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once




//#define   DEBUG_MODE			  //调试方式	
//#define   DEBUG_USE_DEBUG_FILE  //使用调试文件
//#define   USE_SLOW_BOARD  

#define   USE_ASSERT
#define   USE_RAND_BOOK_MOVE

//使用WINLICENSE加密码保护***************************************
#define USE_IDM_EVAL_OUT          //输出评估信息
//使用WINLICENSE加密码保护***************************************

//#define USE_EAT_DIFF_CHESS                 //常捉不同的子，不算常捉
//#define USE_OLD_SEE_DRAW

const int  const_MIN_TIME = 500;		//最少时间  //最少的时间	




//#ifdef   USE_ASSERT
//#define ASSERT(a) { if(!(a)) 	{char LogBuf[256]; StringCbPrintf(LogBuf,LogBufSize,\
//	"file \"%s\", line %d, assertion \"" #a "\" failed",__FILE__,__LINE__);LogOut(LogBuf);}}
//
////#define ASSERT(a)
//#else
//#define ASSERT(a)
//#endif

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

//#define _AFX_NO_OLE_SUPPORT

#include <SDKDDKVer.h>

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#ifdef IDC_STATIC
#undef IDC_STATIC
#endif
#include <afxext.h>         // MFC extensions

// TODO: reference additional headers your program requires here
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Wininet.lib")


// Windows Header Files:
#include <windows.h>
//#include <stdlib.h>
//#include <malloc.h>
//#include <memory.h>
//#include <tchar.h>
//#include <new.h>
//#include <emmintrin.h>
#include <strsafe.h>
//#include <commctrl.h>
//#include <winsock.h>
#include <richedit.h>
//#include <mmsystem.h>
//#include <ShellAPI.H>
//#include <prsht.h>
//#include <math.h>
//#include <time.h>
//#include <wininet.h>
//#include <commdlg.h>
#include <stdlib.h>
#include <tchar.h>
#include <cmath>
#include <vector>
#include <deque>
#include <map>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <tuple>
#include <random>
//#include <gdiplus.h>



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC support for ribbons and control bars



#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif






#pragma comment(lib, "sqlite3.lib")
#include "sqlite3.h"


#ifdef    DB_UNKNOWN
#undef DB_UNKNOWN
#endif
////#define DBTYPE MS_DBTYPE
//#undef DBTYPE


#pragma comment(lib, "libdb62.lib")
#include "db.h"    





//------------------------------------------------------
// stdafx.h : 标准系统包含文件的包含文件，
// 或是常用但不常更改的项目特定的包含文件
//
