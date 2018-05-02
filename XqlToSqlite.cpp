#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"
#include <sys/stat.h>
#include <io.h>
#include <fcntl.h>
#include <share.h>
#include "xqf.h"
//#include <windows.h>
//#include <stdio.h>
//#include <iostream>
//#include <fstream>
//#include <numeric>
//#include <algorithm>
//#include <crtdbg.h>
//#include <fstream>
//#include <iostream>

HANDLE hFile;
//最新版本号
enum {RECENT_VER = 0x12};

//解密用数据
BYTE m_ucKey[0x30];
// 文件版本
BYTE m_ucVer;
BYTE m_uc40E;
BYTE m_uc40F;
BYTE m_uc410;
WORD m_w412;

XQFFileHeader m_xqfHeader;

////////////////////////////////////
// 读取数据（先解密再返回
////////////////////////////////////
HRESULT ReadByCrack(BYTE* buf, int nBufLen){

	//
	if(NULL == buf || nBufLen <= 0){
		return E_INVALIDARG;
	}

	//You can also use the SetFilePointer function to query the current 
	//	file pointer position. 
	//	To do this, specify a move method of FILE_CURRENT 
	//	and a distance of 0 (zero).

	//
	int nPos = SetFilePointer(hFile,0,NULL,FILE_CURRENT);

	DWORD nBytesRead;

	// 读取数据
	BOOL bResult = ReadFile(hFile,
		(char*)buf,
		nBufLen,
		&nBytesRead,
		NULL);

	//Check For End of File
	if(bResult && nBytesRead == 0){
		return E_INVALIDARG;
	}

	for(int i = 0; i < nBufLen; i++){
		buf[i] -= m_ucKey[((nPos + i) & 0x1F) +  0xC];
	}

	return S_OK;
}

////////////////////////////////////
// 读取注释长度
////////////////////////////////////
HRESULT ReadCommentLen(int* pLen)
{
	if (NULL == pLen)
		return E_INVALIDARG;

	HRESULT hr = ReadByCrack((BYTE*)pLen, sizeof(int));
	if (FAILED(hr))
	{
		return hr;
	}

	*pLen -= m_w412;
	return S_OK;
}

////////////////////////////////////
// 从文件中读取数据
////////////////////////////////////
//XQData* LeadHead(){
//	XQDate* pDate = new XQData;
//
//	if(NULL == pData){
//		return NULL;
//	}
//
//	//if(!SUCCEEDED(ReadXQFHeader((BYTE*)&m_xqfHeader, sizeof(m_xqfHeader)))){
//	//	return NULL;
//	//}
//
//	//memcpy(&pData->fileHeader, &m_xqfHeader, sizeof(m_xqfHeader));
//	
//	pData->pRoot = ReadStep(NULL);
//	return pData;
//}

////////////////////////////////////
// 较验文件格式
////////////////////////////////////
bool CheckFormat(const BYTE* buf)
{

	// 检验文件头
	if (*(WORD*)buf != *(WORD*)"XQ")
		return false;
	
	// 文件比程序版本高，无法读取
	if (buf[2] > RECENT_VER)
	{
		return false;
	}
	
	// 较验
	//BYTE ucChk = std::accumulate(buf + 0xC, buf + 0x10, 0);
	//if (0 != ucChk)
	//{
	//	return false;
	//}

	return true;
}




//因为XQF有很多局,所以要分别存
BOOL		ReadXqfToPos   (dispboard_t* pDis, TCHAR* xqfFname){


	// 底层文件操作
	//std::ifstream m_file; 


	//初始化成员变量
	memset(m_ucKey, 0, sizeof(m_ucKey));
	m_ucVer = 0;
	m_uc40E = 0;
	m_uc40F = 0;
	m_uc410 = 0;
	m_uc40F = 0;

	//char* buf;
	//int pFile;

	//HANDLE hFile;

	hFile = CreateFile(xqfFname,
		           GENERIC_READ,          // open for reading
                   FILE_SHARE_READ,       // share for reading
                   NULL,                  // default security
                   OPEN_EXISTING,         // existing file only
                   FILE_ATTRIBUTE_NORMAL, // normal file
                   NULL);                 // no attr. template

	if (hFile == INVALID_HANDLE_VALUE) {
		LogOut(_T("\n不能打开文件\n"));
		LogOut(xqfFname);
		return FALSE;
	}


	//读文件头
	//if (!SUCCEEDED(ReadXQFHeader((BYTE*)&m_xqfHeader, sizeof(m_xqfHeader))))
    DWORD nBytesRead;

	// 读取数据
	BOOL bResult = ReadFile(hFile,
		(char*)&m_xqfHeader,
		sizeof(m_xqfHeader),
		&nBytesRead,
		NULL);
    

	CloseHandle(hFile);   //关闭文件


	return TRUE;
}

//将目录下的PGN文件都一个一个读入开局库
BOOL XqfFileCatToSql(dispboard_t* pDis, TCHAR* pgnRoot){

	BOOL havePgn = FALSE;

	TCHAR filename[MAX_PATH * 2];

	BOOL isFind = FALSE;
	TCHAR dir[MAX_PATH];
	TCHAR pre_name[MAX_PATH * 2];
	TCHAR new_name[MAX_PATH * 2];

	TCHAR ok_dir[MAX_PATH];
	//char bad_dir[MAX_PATH];w

	int ok_num = 0;	

	swprintf_s(ok_dir, sizeof(ok_dir) / sizeof(TCHAR), _T("%s%s"), pgnRoot, _T("_ok"));

	CreateDirectory(ok_dir,NULL);  //建立转换成功的目录 

	do{		//打开一个pgn文件
		OpenAllCatFileOnebyOne(&isFind,pgnRoot,_T("*.xqf"),_T("_ok"),dir,filename);

		if(isFind){
			swprintf_s(pre_name, sizeof(pre_name) / sizeof(TCHAR), _T("%s%s"), dir, filename);

			swprintf_s(pDis->pgn->note, sizeof(pDis->pgn->note) / sizeof(TCHAR), filename);  //将文件名称

			if(ReadXqfToPos(pDis,pre_name)){

				//读入成功了，就移动到_ok目录下
				swprintf_s(new_name, sizeof(new_name) / sizeof(TCHAR), _T("%s%s%s"), ok_dir, _T("\\"), filename);

				if(FALSE == MoveFileEx(pre_name,new_name,MOVEFILE_REPLACE_EXISTING)){
					LogOut(pre_name);
					LogOut(_T("\n不能移动或改名到_ok目录!!\n"));
					LogOut(new_name);
					break;
				}

				LogOut(_T("\n成功读入一局XQF文件!\n"));
				LogOut(pre_name);
				
				havePgn = TRUE;
			}

			else{
				//不能正确读入PGN文件
				LogOut(pre_name);
				LogOut(_T("读入XQF文件错误，请检查XQF格式!!\n"));

				//******************************************************************				
				swprintf_s(new_name, sizeof(new_name) / sizeof(TCHAR), _T("%s%s%s"), ok_dir, _T("\\"), filename);

				if(FALSE == MoveFileEx(pre_name,new_name,MOVEFILE_REPLACE_EXISTING)){
					LogOut(pre_name);
					LogOut(_T("\n不能移动或改名到_ok目录!!\n"));
					LogOut(new_name);
					break;
				}
				//******************************************************************
				havePgn = TRUE;
				break;
			}

			isFind = FALSE;

		}
		else{
			LogOut(pgnRoot);
			LogOut(_T("\n对不起，没有在以上目录下找到有效的XQF文件\n"));
		}

	}while(false);

	return havePgn;
	
}