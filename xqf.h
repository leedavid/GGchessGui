#if !defined(XQDATA_H_INCLUDED)
#define XQDATA_H_INCLUDED

#pragma pack(push, 1)

const int CHESS_MAN_NUM = 32; // 双方总棋子数目

enum XM_TYPE
{
	XM_JU, // 车
	XM_MA, // 马
	XM_XIANG, // 相象
	XM_SHI, // 仕士
	XM_KING, // 帅将
	XM_PAO, // 炮
	XM_BING // 兵卒
};

const XM_TYPE g_xqMan[] = 
{
	XM_JU, XM_MA, XM_XIANG, XM_SHI, XM_KING, XM_SHI, XM_XIANG, XM_MA, XM_JU, XM_PAO, XM_PAO, XM_BING, XM_BING, XM_BING, XM_BING, XM_BING,
	XM_JU, XM_MA, XM_XIANG, XM_SHI, XM_KING, XM_SHI, XM_XIANG, XM_MA, XM_JU, XM_PAO, XM_PAO, XM_BING, XM_BING, XM_BING, XM_BING, XM_BING
};

// 走子顺序
enum XQ_ORDER
{
	XO_RED, // 红先
	XO_BLACK, // 黑先
	XO_NONE // 未知
};

// 结果
enum XQ_RESULT
{
	XR_UNKNOWN, // 未知
	XR_REDWIN, // 红胜
	XR_BLACKWIN, // 黑胜
	XR_PEACE // 和
};

// 数据类型
enum XQ_TYPE
{
	XT_ALL, // 全局
	XT_OPEN, // 开局
	XT_MIDDLE, // 中局
	XT_END // 残局
};

struct XQExplainData
{
	XQ_ORDER eOrder;
	XQExplainData()
	{
		eOrder = XO_NONE;
	}
};


struct XQFFileHeader
{
	WORD wMagic;
	BYTE ucVer;
	BYTE ucChk1;
	BYTE uc[0xC];
	BYTE ucBoard[CHESS_MAN_NUM];
	BYTE ucUn2[3];
	BYTE ucRes; // offset 0x33
	BYTE ucUn3[0xC];
	BYTE ucType; // 棋局类型(开中残全), offset: 0x40
	BYTE ucUn4[0xF];
	BYTE ucTitleLen; // 标题名称 offset 0x50
	char szTitle[0x90 - 0x51];
	BYTE ucUn5[0xD0 - 0x90];
	BYTE ucMatchName; // 比赛名称 offset 0xD0
	char szMatchName[0x110 - 0xD1]; // 比赛名称
	BYTE ucDateLen; // 比赛日期, offset 0x110
	char szDate[0x120 - 0x111];
	BYTE ucAddrLen; // 比赛地点，offset 0x120
	char szAddr[0x130 - 0x121];
	BYTE ucRedPlayerNameLen; // 红方棋手姓名, offset 0x130
	char szRedPlayerName[0x140 - 0x131];
	BYTE ucBlackPlayerNameLen; // 黑方棋手姓名， offset 0x140
	char szBlackPlayerName[0x150 - 0x141];
	BYTE ucTimeRuleLen; //　用时规则, offset 0x151
	char szTimeRule[0x190 - 0x151];
	BYTE ucRedTimeLen; // 红方用时长度, offset 0x190
	char szRedTime[0x1A0 - 0x191];
	BYTE ucBlackTime; // 黑方用时长度, offset 0x1a0
	char szBlackTime[0x1B0 - 0x1A1]; 
	BYTE ucUn6[0x1D0 - 0x1B0];
	BYTE ucCommenerNameLen; // 讲评人姓名长度, offset 0x1D0
	char szCommenerName[0x1E0 - 0x1D1];
	BYTE ucAuthorNameLen; // 文件作者姓名长度, offset 0x1E0
	char szAuthorName[0x1F0 - 0x1E1];
	BYTE ucUn7[0x400 - 0x1F0];
};
#pragma pack(pop)

struct XQNode
{
	BYTE ucStart;
	BYTE ucEnd;
	XQ_ORDER eOrder;     // 当前步是红走的还是黑走的
	char* szComment;
	XQNode* pParent;
	XQNode* pFirstChild; // 第一个选择
	XQNode* pCurChild;   // 当前选择
	XQNode* pLeft;       // 左结点
	XQNode* pRight;      // 右结点
	BYTE ucChessBoard[CHESS_MAN_NUM]; // 走完后之棋盘
	XQNode()
	{
		ucStart = ucEnd = 0;
		eOrder = XO_NONE;
		szComment = NULL;
		pParent = NULL;
		pFirstChild = NULL;
		pCurChild = NULL;
		pLeft = NULL;
		pRight = NULL;
	}

	~XQNode()
	{
		delete []szComment;
	}

};

//struct XQData
//{
////	XQExplainData dataExplain;
//	XQFFileHeader fileHeader;
//	XQNode* pRoot;
//
//	XQData()
//	{
//		pRoot = NULL;
//	}
//
//	~XQData()
//	{
//		DeleteXQNode(pRoot);
//	}
//};




#endif  // Sentry