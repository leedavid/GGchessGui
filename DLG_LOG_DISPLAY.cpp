// DLG_LOG_DISPLAY.cpp : 实现文件
//

#include "stdafx.h"
#include "GGchess.h"
#include "DLG_LOG_DISPLAY.h"
#include "afxdialogex.h"


// DLG_LOG_DISPLAY 对话框

IMPLEMENT_DYNAMIC(DLG_LOG_DISPLAY, CDialogEx)

DLG_LOG_DISPLAY::DLG_LOG_DISPLAY(CWnd* pParent /*=NULL*/)
	: CDialogEx(DLG_LOG_DISPLAY::IDD, pParent)
{

}

DLG_LOG_DISPLAY::~DLG_LOG_DISPLAY()
{
}

void DLG_LOG_DISPLAY::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DLG_LOG_DISPLAY, CDialogEx)
END_MESSAGE_MAP()


// DLG_LOG_DISPLAY 消息处理程序
