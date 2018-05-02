#pragma once


// dlgtest 对话框

class dlgtest : public CDialogEx
{
	DECLARE_DYNAMIC(dlgtest)

public:
	dlgtest(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~dlgtest();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
