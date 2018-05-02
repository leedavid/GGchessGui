#pragma once


// DLG_LOG_DISPLAY 对话框

class DLG_LOG_DISPLAY : public CDialogEx
{
	DECLARE_DYNAMIC(DLG_LOG_DISPLAY)

public:
	DLG_LOG_DISPLAY(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DLG_LOG_DISPLAY();

// 对话框数据
	enum { IDD = DLG_RICH_LOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
