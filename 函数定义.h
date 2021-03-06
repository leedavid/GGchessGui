#ifndef CHESS_FUNCTION_H
#define CHESS_FUNCTION_H

//#include "chess_function_common.h"

//extern BOOL    see_draw_old(position_t *pos,int mfrom,int mto, int to);
//extern BOOL    see_draw_new(position_t *pos,int mfrom,int mto, int from, int to, int which);

//extern BOOL    see_draw_20071018(position_t *pos,int mfrom,int mto, int from, int to, int which);
//extern BOOL    see_draw_20080818(position_t *pos,int mfrom,int mto, int from, int to, int which);

extern BOOL    see_draw_20081016(position_t *pos,int mfrom,int mto, int from, int to, int which);

//extern BOOL    isTrueCap_ByDirect(position_t *pos,int mto, int to, int from, int which);
//extern BOOL    testall_TrueCap_noPawnKing(position_t *pos,int to, int from, int which);

extern BOOL    isFourTypeChess(position_t *pos,int mfrom,int mto, int cap, int becap, int which);

//是不是构成的新捉...
//extern BOOL    testall_TrueCap_noPawnKing_W_NewCap(position_t *pos,int mfrom,int mto, int from, int to, int which);

//判断一下是不是真的捉
extern void    test_Is_True_Cap         (position_t *pos,int from, int to, int ot_from,int ot_to, int which);
extern BOOL    Is_Can_Move_To_Eat       (position_t *pos,int from, int to);
extern BOOL    isPretectedd             (position_t *pos, int side, int sqDst, int sqExcept);
extern BOOL     isCanProtect_Last_Move  (position_t *pos, int side, int protect, int becap);
extern void    ExportAllUbb         (void);

extern int PgnTotalGameNumFromSql(sqlite3 *db);
extern int PgnTotalGameUncheckNumFromSql(sqlite3 *db);

extern void    Export_Sqlite_Qj();
extern void    SendDebugEvalCmd();

extern void			//主窗口绘图程序
PaintChartProc(dispboard_t* pDis, HWND hwnd);

extern void		//发送走步到引擎,注意只是发送用户走了一步,并不要叫诉引擎要走棋!!!
SendCurPosToProgram(dispboard_t* pDis, ChessProgramState *cps);

extern void SendOnlyFenToProgram(dispboard_t* pDis, ChessProgramState *cps);

//extern void    get_Xor_Char(char* orgChar, int seed, char* nowChar);

extern void CopyUBBToClipboard(dispboard_t* pDis);

// 此代码模块中包含的函数的前向声明:
extern BOOL     PopObsBoardDialog(int table);
extern void     SetMenuEnables(HMENU hmenu, Enables *enab);
extern HWND	    CreateStatus(HWND hMain);

extern ATOM				MyRegisterClass(HINSTANCE hInstance);
extern BOOL				InitInstance(HINSTANCE, int,LPTSTR);
extern LRESULT  CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
extern LRESULT  CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

extern void		AnalyzeModeEvent (dispboard_t* pDis);
extern void		AnalyzeFileEvent (dispboard_t* pDis);

extern void     initIcs(void);
extern void     ParseIcsBuf_CN(char* buf);
extern void     ParseIcsBuf_EN(char* buf);
extern void     strCopybyNum(char* dst, size_t num, char* src);
//extern void     strCopybyNumTC(TCHAR* dst,size_t num, char* src);

extern void     OpenAllCatFileOnebyOne(BOOL* isFindOne, TCHAR *root, TCHAR *ftype, 
	TCHAR* NotOpen, TCHAR* dir, TCHAR* filename);
extern BOOL		ReadPgnToPos(dispboard_t* pDis, TCHAR* pgnFname);
//extern BOOL     PgnFileCatToBook (char* pgnRoot);

extern BOOL     PgnFileCatToSql(dispboard_t* pDis, TCHAR* pgnRoot);
extern BOOL     MxqFileCatToSql(dispboard_t* pDis, TCHAR* pgnRoot);
//extern BOOL     XqfFileCatToSql(dispboard_t* pDis, TCHAR* pgnRoot);

extern void		FitConsoleItemPosition(HWND hDlg,int newSizeX,int newSizeY);




extern LRESULT  CALLBACK DLG_BOOK_PROC(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam);

extern LRESULT  CALLBACK SaveGameDlgCallBack(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

			    //从CPS那儿得到时间控制的信息
extern void		GetTimeInfoFromCps(dispboard_t* pDis, TimeDisp_t* pTimeDisp, ChessProgramState * cps);

extern int		BoardWidth_X(int boardSize);
extern int		BoardWidth_Y(int boardSize);
extern void		B90ToD8(sq_t *b90, int* D8,bool isWhiteGo);

extern char		*CmailMsg (void);
extern void		Change_BlueRed(void);
extern void		Change_Right_Left(void);
//extern HWND		CreateListLog(HWND hMain,int x,int y,int w,int h);	//建立日志信息窗口										  
extern LRESULT  CALLBACK ConsoleTextSubclass(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
extern void		CommandX(HWND hwnd, char *command, BOOLEAN getname, BOOLEAN immediate);

extern VOID		DrawCoordsOnDC(dispboard_t* pDis, HDC hdc);							//画上棋格坐标
extern VOID		DrawGridOnDC(dispboard_t* pDis,HDC hdc,HDC tmphdc, HDC hdcmask);		//画上棋盘的线，与边框线
extern int		DoWriteFile(HANDLE hFile, char *buf, int count, DWORD *outCount,OVERLAPPED *ovl);
extern int		DoReadFile(HANDLE hFile, char *buf, int count, DWORD *outCount,	OVERLAPPED *ovl);
				//显示当前棋局的所有棋库信息
//extern void     DispGGFaceQKinfo(list_t * list,Board90 b90,bool isWhiteGo,MYSQL *my);

////extern void		DispStatS(const char *string);

extern void		DispAllCanMove(void);
extern bool		D8ToB90(int *D8, sq_t *b90);

extern char		FileGet(void *getClosure);

extern void    GetMoveName(position_t *pos, TCHAR* szStepName, int move, int ntype);
extern void    GetMoveNameSimple(position_t *pos, TCHAR* szStepName, int move, int ntype);

extern int      str2move(position_t *pos, TCHAR *str);

extern         move_stack_t *generate_moves(position_t *pos, move_stack_t *ms);
//extern         move_stack_t *generate_check_evasions(position_t *pos, move_stack_t *ms);

extern         void gen_legal_moves(position_t *pos);

extern         BOOL  move_is_legal(position_t *pos, int move);

//extern void     GetMirrorOnlyB90(position_t *pos, uint8 b32[28]);


extern void     GetMirrorOnlyB33(position_t *pos, uint8 b33[33]);

extern void     HDCDrawPosition(dispboard_t* pDis, HDC hdc, BOOLEAN repaint, uint8* B256);     //显示

void            //显示
HDCDrawChart(HWND hwnd, dispboard_t* pDis, HDC hdc, BOOLEAN repaint);

extern void		InitComboStrings(void *, char **cd);
//extern void		initPrepareStep(void);
extern void     p90ToAsc(void);
extern void		initWin(void);					//主程序初始化
				//判断走步是不是有效哇
//extern ChessMove IsMoveValid(Board90 board, bool isWhiteGo,int fx, int fy, int tx, int ty);

//extern ChessMove IsMoveValid_FT(position_t *pos,int fx, int fy, int tx, int ty); 
//extern bool      IsMoveValid  (position_t *pos,int move);

extern ChessMove		//判断走步是不是有效哇
IsMoveValid_FT(position_t *pos,int ffx, int ffy, int ttx, int tty);

extern void MakePosMoveOnly(position_t *pos, int m);
extern void UnMakePosMoveOnly(position_t *pos);

//extern int		IsInCheck(Board90 board, bool isWhiteGo);

extern  int     IsInCheck(position_t *pos, bool who);

//extern void		InitComboStringsFromOption(HWND hwndCombo, char *str);


extern HANDLE	LoadChessBitmapBySize(HINSTANCE hinst, TCHAR *fileName,int squareSize);
//extern int		looking_at (char *,int *i, char *);

extern int		looking_at (TCHAR *,TCHAR *);


				 //得到棋库中一个局面的局面分数哇
//extern bool     MysqlGetOneFaceScore(Board90 b90, bool isWhiteGo,qkface_t *pf, MYSQL *my);

extern TCHAR *	NextInHistory();

extern void     PopIcsBoardDialog(void);

extern BoardSize ParseBoardSize(TCHAR *name);
extern TCHAR *	PrevInHistory(TCHAR *cmd);
extern void		PaintProc(dispboard_t* pDis);
//extern void		PlayCheckSound();
//extern void		PlayEatSound();
//extern BOOLEAN	ParseSettingsFile(char *name, char fullname[MSG_SIZ]);		//解析name文件

extern void		ParaseDisMoveToUCCImove(int move, char *UCCImove, int ucci);

extern bool		parse_disp_cmd(void);

extern char *	QuoteForFilename(char *filename);

extern void		RedoDispChess(void);
extern void		RenewBoard(void);
extern void	    ResizeBoard(dispboard_t* pDis, int newSizeX, int newSizeY, int flags); //重新更新棋盘大小

//extern void		SetDefaultSounds(void);
extern void		SetDefaultTextAttribs(void);
extern void		SaveInHistory(TCHAR *cmd);
extern void		SquareToPos(dispboard_t* pDis, int file, int rank, int * x, int * y);  //从file 与 rank 得到当前的坐标
extern void		SendToICS (TCHAR *s);
//extern void		SendToProgram (dispboard_t* pDis, char *message, ChessProgramState *cps);
extern void		SendBoard (ChessProgramState *cps, int moveNum);
extern void		SendTimeRemaining (ChessProgramState *cps, int/*boolean*/ machineWhite);
extern char     StringGet(void *getClosure);
extern int		StrCaseCmp(char *s1,char *s2);
extern void		SendControlParameterToCps(ChessProgramState *cps);

extern int		ToUpper(int c);
extern int		ToLower(int c);

extern void		UndoDispChess(void);
extern int      move_is_check(position_t *pos,int move);

extern void EditPositionPasteFEN (TCHAR *fen, dispboard_t *pDis);
extern void TimeDelay (long ms);
//extern void SendMultiLineToICS ( char *text );

extern void AnalysisPeriodicEvent (int force);
extern void SetWhiteToPlayEvent (void);
extern void SetBlackToPlayEvent (void);
extern BOOL string_start_with(const char s1[], const char s2[]);
extern void InitBackEnd1 (dispboard_t* pDis);
extern void InitBackEnd2 (dispboard_t* pDis);
//extern int IsPromotion (int fromX, int fromY, int toX, int toY);
extern int PieceForSquare (int x, int y);
extern int OKToStartUserMove (dispboard_t* pDis,int x, int y);
extern void GameReset(dispboard_t* pDis,int redraw, BOOL isResetYq, BOOL isResetGameMode);
void ResetGameEvent (dispboard_t* pDis);
extern int LoadGame (FILE *f, int n, char *title, int useList);
extern int LoadGameFromFile (char *filename, int n, char *title, int useList);
//extern int CmailLoadGame (FILE *f, int n, char *title, int useList);
extern int ReloadGame (int offset);
extern int SaveGame (FILE *f, int dummy, char *dummy2);
//extern int SaveGameToFile (char *filename, int append);
extern int LoadPosition (FILE *f, int n, char *title);
extern int ReloadPosition (int offset);
extern int SavePosition (FILE *f, int dummy, char *dummy2);
extern void EditPositionEvent (void);
extern void FlipViewEvent (dispboard_t* pDis);
extern void MachineWhiteEvent (void);
extern void MachineBlackEvent (void);
extern void TwoMachinesEvent (void);
extern void EditGameEvent (dispboard_t* pDis);
extern void TrainingEvent (void);
extern void IcsClientEvent (void);
extern void ForwardEvent (dispboard_t* pDis);
extern void BackwardEvent (dispboard_t* pDis);
extern void ToEndEvent (dispboard_t* pDis);
extern void ToStartEvent (dispboard_t* pDis);
extern void ToNrEvent(dispboard_t* pDis, int to);
extern void RevertEvent (void);
extern void RetractMoveEvent (void);
extern void MoveNowEvent (void);
extern void TruncateGameEvent (void);
extern void PauseEvent (void);
extern void CallFlagEvent (void);
extern void AcceptEvent (void);
extern void DeclineEvent (void);
extern void RematchEvent (void);
extern void DrawEvent (void);
extern void AbortEvent (void);
extern void AdjournEvent (void);
extern void ResignEvent (void);
extern void StopObservingEvent (void);
extern void StopExaminingEvent (void);
extern void PonderNextMoveEvent (dispboard_t* pDis, int newState);
extern void ShowThinkingEvent (dispboard_t* pDis,int newState);
extern void PeriodicUpdatesEvent (dispboard_t* pDis,int newState);
extern void HintEvent (void);
extern void BookEvent (void);
extern void AboutGameEvent (void);
extern void ExitEvent (int status);
extern char *DefaultFileName (char *);
extern void UserMoveEvent (dispboard_t* pDis, int fromX, int fromY, int toX, int toY, int ucci);
extern void DecrementClocks (dispboard_t* pDis);
//extern char *TimeString (long millisec);
extern void TimeString (long millisec, TCHAR* buf);
extern void AutoPlayGameLoop (dispboard_t* pDis);
extern void DisplayBothClocks (dispboard_t* pDis);
extern void EditPositionMenuEvent (int selection, int x, int y);
extern void DropMenuEvent (int selection, int x, int y);
extern int ParseTimeControl (char *tc, int ti, int mps);
extern void ProcessICSInitScript (FILE * f);
extern void EditCommentEvent (void);
extern void ReplaceComment (int index, char *text);
extern int ReplaceTags (char *tags, PGN *gi);/* returns nonzero on error */
extern void AppendComment (int index, char *text);

//extern void CMX_183CN_Get_Pass_By_Client(char *pre, char *passed);
//extern void CMX_183EN_Get_Pass_By_Client(char *pre, char *passed);
extern void CMX_183_Get_Client_Code(void);
extern void CMX_183_SEND_CODDING(TCHAR* pretext);
extern void CMX_183_SEND_CODDING_DelayMs(TCHAR* pretext, int ms);

//extern HRESULT __fastcall AnsiToUnicode(char* pszA, TCHAR* ppszW);
//extern HRESULT __fastcall UnicodeToAnsi(TCHAR* pszW, char* ppszA);
//extern void CMX_183CN_Get_Pass_By_Client(char *pre, char *passed);
//extern void ReloadCmailMsgEvent (int unregister);
extern void MailMoveEvent (void);
extern void EditTagsEvent (void);
extern void GetMoveListEvent (void);
extern void ExitAnalyzeMode (void);

extern void DoEcho (void);
extern void DontEcho (void);
//extern void TidyProgramName (char *prog, char *host, char *buf);
extern void AskQuestionEvent(TCHAR *title, TCHAR *question,
	TCHAR *replyPrefix, TCHAR *which);

//extern TCHAR *VariantName (VariantClass v);
//extern VariantClass StringToVariant (char *e);

char *StrStr (char *string, char *match);
char *StrCaseStr (char *string, char *match);
//char *StrSave (char *s);
//char *StrSavePtr (char *s, char **savePtr);

extern void ModeHighlight (void);
extern void SetICSMode (void);
extern void SetGNUMode (void);
extern void SetNCPMode (void);
extern void SetCmailMode (void);
extern void SetTrainingModeOn (void);
extern void SetTrainingModeOff (void);
extern void SetUserThinkingEnables (void);
extern void SetMachineThinkingEnables (dispboard_t* pDis);
extern void DisplayTitle (dispboard_t* pDis);
extern void DisplayMessage(dispboard_t* pDis, TCHAR* message, TCHAR* extMessage);
//extern void DisplayError (String message, int error);
extern void DisplayMoveError (dispboard_t* pDis, TCHAR* message);
//extern void DisplayTwoMachinesTitle(dispboard_t* pDis);

/* If status == 0, we are exiting with a benign message, not an error */
extern void DisplayFatalError (TCHAR *message, int error, int status);

//extern void DisplayInformation (String message);
//extern void DisplayNote (String message);
extern void AskQuestion(TCHAR *title, TCHAR *question, TCHAR *replyPrefix,
		    ProcRef pr);
//extern void DisplayIcsInteractionTitle (String title);
//extern void DrawPosition (int fullRedraw, board_t *board);
extern void ResetFrontEnd (dispboard_t* pDis);
//extern void CommentPopUp (String title, String comment);
//extern void CommentPopDown (void);
//extern void EditCommentPopUp (int index, String title, String text);

//extern void RingBell (void);
//extern void PlayIcsWinSound (void);
//extern void PlayIcsLossSound (void);
//extern void PlayIcsDrawSound (void);
//extern void PlayIcsUnfinishedSound (void);
//extern void PlayAlarmSound (void);
extern void EchoOn (void);
extern void EchoOff (void);
extern void Raw (void);
extern void Colorize (ColorClass cc, int continuation);

//extern char *UserName (void);
//extern char *HostName (void);

extern int ClockTimerRunning (void);
extern int StopClockTimer (dispboard_t* pDis);
extern void StartClockTimer (dispboard_t* pDis,long millisec);

extern void DisplayWhiteClock (dispboard_t* pDis,int fudge,  int highlight);
extern void DisplayBlackClock (dispboard_t* pDis,int fudge,  int highlight);

extern int LoadGameTimerRunning (void);
extern int StopLoadGameTimer (dispboard_t* pDis);
extern void StartLoadGameTimer (dispboard_t* pDis,long millisec);
extern BOOL AutoSaveGame (dispboard_t* pDis);

extern void ScheduleDelayedEvent (dispboard_t* pDis,DelayedEventCallback cb, long millisec);
extern DelayedEventCallback GetDelayedEvent (void);
extern void CancelDelayedEvent (void);

extern int StartChildProcess(TCHAR *cmdLine, TCHAR *dir, ProcRef *pr);
extern void DestroyChildProcess (ProcRef pr, int/*boolean*/ signal);
extern void InterruptChildProcess (ProcRef pr);
extern int OpenRcmd(char *host, char *user, char *cmd, ProcRef *pr);
extern int OpenTelnet(TCHAR *host, TCHAR *port, ProcRef *pr);
extern int OpenTCP(char *host, char *port, ProcRef *pr);
extern int OpenCommPort(char *name, ProcRef *pr);
extern int OpenLoopback (ProcRef *pr);



/* pr == NoProc means the local keyboard */
extern InputSourceRef AddInputSource (ProcRef pr, int lineByLine,
				 InputCallback func, VOIDSTAR closure);
extern void RemoveInputSource (InputSourceRef isr);

/* pr == NoProc means the local display */
extern int OutputToProcess (ProcRef pr, TCHAR *message, int count, int *outError);
extern int OutputToProcessDelayed (ProcRef pr, TCHAR *message, int count,
			      int *outError, long msdelay);
extern void SetIcsLogOk(TCHAR* buf); //已登录成功了网站
extern void AlreadDisConnectIcs(void);


//extern void ICSInitScript (void);
extern void StartAnalysisClock (dispboard_t* pDis);
extern void AnalysisPopUp (char *title, char *label);
extern void AnalysisPopDown (void);

extern void SetHighlights (dispboard_t* pDis, int fromX, int fromY, int toX, int toY);
extern void ClearHighlights (dispboard_t* pDis);
extern void SetPremoveHighlights (dispboard_t* pDis,int fromX, int fromY, int toX, int toY);
extern void ClearPremoveHighlights (dispboard_t* pDis);

extern void ShutDownFrontEnd (void);
extern void BoardToTop (dispboard_t* pDis);

extern void AnimateMove (dispboard_t* pDis, uint8* B256, int fromX, int fromY, int toX, int toY);
//extern void HistorySet (char movelist[][2*MOVE_LEN],
//		   int first, int last, int current); not use know
extern void FreezeUI (void);
extern void ThawUI (void);


extern void ClearGameInfo (PGN *pgg);


extern char* StripHighlight (char *);  /* returns static data */
extern char* StripHighlightAndTitle (char *);  /* returns static data */

extern void SetUpChildIO (int to_prog[2], int from_prog[2]);

extern int ListEmpty (List *);
extern void ListNew (List *);
extern void ListRemove (ListNode *);
extern void ListNodeFree (ListNode *);
extern ListNode *ListNodeCreate (size_t);
extern void ListInsert (ListNode *, ListNode *);
extern void ListAddHead (List *, ListNode *);
extern void ListAddTail (List *, ListNode *);
extern ListNode *ListElem (List *, int);

extern sq_t CharToPiece (int c,int ucci);

extern void CopyBoard (uint8* to, uint8* from);

extern int CompareBoards (uint8* board1, uint8* board2);

extern int IsMateDead(position_t* pos); //是否被将死了哇


extern void board_red2black(dispboard_t* pDis);
extern void CopyGameToClipboardUBB (dispboard_t* pDis, BOOL startStep);
//extern void CopyGameToClipboardJava(dispboard_t* pDis, BOOL startStep);

extern void PasteGameFromClipboard(dispboard_t* pDis);

extern int CopyTextToClipboard(TCHAR *text);

extern void CopyFENToClipboard(dispboard_t* pDis);
extern void PasteFENFromClipboard(dispboard_t* pDis);


extern int PasteTextFromClipboard(TCHAR **text, dispboard_t* pDis);

extern VOID DeleteClipboardTempFiles();

extern VOID EditTagsProc(void);



extern VOID ShowGameListProc(void);

extern TCHAR *move2str(int move, TCHAR *str);

extern VOID GeneralOptionsPopup(HWND hwnd);
extern VOID BoardOptionsPopup(HWND hwnd);
extern VOID IcsOptionsPopup(HWND hwnd);
extern VOID FontsOptionsPopup(HWND hwnd);
//extern VOID SoundOptionsPopup(HWND hwnd);
extern VOID CommPortOptionsPopup(HWND hwnd);
extern VOID LoadOptionsPopup(HWND hwnd);
extern VOID SaveOptionsPopup(HWND hwnd);
extern VOID TimeControlOptionsPopup(HWND hwnd);

extern void YqSetOptionsPopup(int table);

extern BOOL InitApplication(HINSTANCE);
extern BOOL InitInstance(HINSTANCE, int, LPWSTR);
extern LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
extern LRESULT CALLBACK About(HWND, UINT, WPARAM, LPARAM);
extern LRESULT CALLBACK BoardSizeDlg(HWND, UINT, WPARAM, LPARAM);
//extern LRESULT CALLBACK ButtonProc(HWND, UINT, WPARAM, LPARAM);
extern VOID InitAppData(LPWSTR);
extern VOID InitDrawingColors(dispboard_t* pDis);
extern VOID InitDrawingSizes(dispboard_t* pDis, int boardSize, int flags);
extern VOID InitMenuChecks(VOID);
extern VOID ICSInitScript(VOID);
extern BOOL CenterWindow(HWND hwndChild, HWND hwndParent);
extern VOID ResizeEditPlusButtons(HWND hDlg, HWND hText, int sizeX, int sizeY, int newSizeX, int newSizeY);
extern VOID PromotionPopup(HWND hwnd);
extern HWND	CreateAToolBar(HWND hwndParent);
extern FILE *OpenFileDialog(HWND hWnd, BOOL write, TCHAR *defName, TCHAR *defExt,
	TCHAR *nameFilt, TCHAR *dlgTitle, UINT *number,
	TCHAR fileTitle[MSG_SIZ], TCHAR fileName[MSG_SIZ]);
extern VOID InputEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
extern DWORD InputThread(LPVOID arg);
extern DWORD NonOvlInputThread(LPVOID arg);
extern DWORD SocketInputThread(LPVOID arg);
extern BOOL ChangeColor(HWND hwnd, COLORREF *which);
extern VOID ChangeBoardSize(dispboard_t* pDis, int newSize);
extern BOOL APIENTRY MyCreateFont(HWND hwnd, MyFont *font);
//extern VOID ErrorPopDown(VOID);
extern VOID EnsureOnScreen(dispboard_t* pDis, int *x, int *y);




//HBITMAP 
//DoLoadBitmap(HINSTANCE hinst, char *piece, int squareSize, char *suffix);
extern COLORREF ParseColorName(TCHAR *name);
extern void ParseAttribs(COLORREF *color, int *effects, TCHAR* argValue);
extern VOID CreateFontInMF(MyFont *mf);
extern VOID ChangedConsoleFont();
extern VOID ParseFontName(TCHAR *name, MyFontParams *mfp);
extern void InitComboStrings(HANDLE hwndCombo, char **cd);
//extern BOOLEAN MyLoadSound(MySound *ms);
//extern BOOLEAN MyPlaySound(MySound *ms);
extern VOID ExitArgError(TCHAR *msg, TCHAR *badArg);
extern int establish (void);
extern void read_from_player (InputSourceRef isr, VOIDSTAR closure,
			 char *buf, int count, int error);
extern void read_from_ics (InputSourceRef isr, VOIDSTAR closure,
		      char *buf, int count, int error);

extern void read_from_ics_mxq_cn(InputSourceRef isr, VOIDSTAR closure,
                              char *data, int count, int error);
extern void read_from_ics_mxq_en(InputSourceRef isr, VOIDSTAR closure,
                              char *data, int count, int error);
extern void read_from_ics_not_ready_know(InputSourceRef isr, 
                                  VOIDSTAR closure,	char *data, int count, int error);

//extern void SendToPlayerByColor(char *str, ColorClass cc,int len, int notShout);
extern void SendToPlayerByColor(TCHAR *str, ColorClass cc, int notShout);
extern void SendToICS (TCHAR *s);
extern void SendToICSDelayed (TCHAR *s, long msdelay);
extern void SendMoveToICS (dispboard_t* pDis, ChessMove moveType, int fromX, int fromY,
		      int toX, int toY);
extern void InitPosition (dispboard_t* pDis,int redraw);
extern void HandleMachineMove (TCHAR *message, ChessProgramState *cps);
extern int AutoPlayOneMove (dispboard_t* pDis);
extern int LoadGameOneMove (ChessMove readAhead);
//extern int LoadGameFromFile (char *filename, int n, char *title, int useList);
//extern int LoadPositionFromFile (char *filename, int n, char *title);
//extern int SavePositionToFile (char *filename);
extern void ApplyMove(dispboard_t* pDis,position_t* pos,int fromX, int fromY, int toX, int toY);
extern void MakeMove   (dispboard_t* pDis,int fromX, int fromY, int toX, int toY,bool isMateTest);
extern void ShowMove   (dispboard_t* pDis,int fromX, int fromY, int toX, int toY);
extern void FinishMove (dispboard_t* pDis, ChessMove moveType, int fromX, int fromY, int toX, int toY);
		   
extern void BackwardInner (dispboard_t* pDis,int target);
extern void ForwardInner (dispboard_t* pDis, int target);
extern void GameEnds (dispboard_t* pDis, ChessMove result, TCHAR *resultDetails, int whosays);
extern void EditPositionDone (void);
extern void PrintOpponents (FILE *fp);
extern void PrintPosition (FILE *fp, int move);
extern void StartChessProgram (ChessProgramState *cps);
extern void SendToProgram (TCHAR *message, ChessProgramState *cps);
//extern void SendMoveToProgram (dispboard_t* pDis, ChessProgramState *cps, char* ponderMove);

extern void SendMoveToProgram (dispboard_t* pDis, ChessProgramState *cps, TCHAR* ponderMove);

extern void SendProgramGo(ChessProgramState *cps, CPS_STAT go_type, TCHAR* premove);
extern void ReceiveFromProgram (InputSourceRef isr, VOIDSTAR closure,
			   char *buf, int count, int error);
extern void SendTimeControl (ChessProgramState *cps,
			int mps, long tc, int inc, int sd, int st);
//extern char *TimeControlTagValue (void);
extern void TimeControlTagValue(char *buf);
extern void Attention (ChessProgramState *cps);
extern void FeedMovesToProgram (ChessProgramState *cps, int upto);
extern void ResurrectChessProgram (void);
//extern void DisplayComment (int moveNumber, char *text);
//extern void DisplayMove (int moveNumber);
extern void DisplayAnalysis (void);

extern void ParseGameHistory (char *game);
extern void ParseBoard12 (char *string);
extern void StartClocks  (dispboard_t* pDis);
extern void SwitchClocks (dispboard_t* pDis);
extern void StopClocks   (dispboard_t* pDis);
extern void ResetClocks  (dispboard_t* pDis);
//extern char *PGNDate (void);
//extern void PGNDate(char* ret);
extern void SetGameInfo (void);
//extern Boolean ParseFEN (board_t board, int *blackPlaysFirst, char *fen);
extern int RegisterMove (void);
extern void MakeRegisteredMove (void);
extern void TruncateGame (dispboard_t* pDis);
//extern int looking_at (char *, int *, char *);
extern void CopyPlayerNameIntoFileName (char **, char *);
//extern char *SavePart (char *);
extern int SaveGameOldStyle (FILE *);
extern int SaveGamePGN (FILE *);
//extern void GetTimeMark (TimeMark *);
//extern long SubtractTimeMarks (TimeMark *, TimeMark *);
extern int CheckFlags (dispboard_t* pDis);		//查看一下一方是不是超时了
extern long NextTickLength (dispboard_t* pDis,int);
extern void CheckTimeControl (dispboard_t* pDis);
extern void show_bytes (FILE *, char *, int);
extern int string_to_rating (char *str);
extern void ParseFeatures (char* args, ChessProgramState *cps);
extern void InitBackEnd3 (dispboard_t* pDis);
extern void FeatureDone (ChessProgramState* cps, int val);
extern void InitChessProgram (ChessProgramState *cps);

extern LRESULT CALLBACK GeneralOptions(HWND, UINT, WPARAM, LPARAM);
extern LRESULT CALLBACK BoardOptions(HWND, UINT, WPARAM, LPARAM);
extern LRESULT CALLBACK IcsOptions(HWND, UINT, WPARAM, LPARAM);
extern LRESULT CALLBACK FontOptions(HWND, UINT, WPARAM, LPARAM);
extern LRESULT CALLBACK CommPortOptions(HWND, UINT, WPARAM, LPARAM);
extern LRESULT CALLBACK LoadOptions(HWND, UINT, WPARAM, LPARAM);
extern LRESULT CALLBACK SaveOptions(HWND, UINT, WPARAM, LPARAM);
extern LRESULT CALLBACK TimeControl(HWND, UINT, WPARAM, LPARAM);
//extern VOID ChangeBoardSize(BoardSize newSize);
extern VOID PaintSampleSquare(
    HWND     hwnd, 
    int      ctrlid, 
    COLORREF squareColor, 
    COLORREF pieceColor,
    COLORREF squareOutlineColor,
    COLORREF pieceDetailColor,
    BOOL     isWhitePiece,
    BOOL     isMono,
    HBITMAP  pieces[3] 
    );
extern VOID PaintColorBlock(HWND hwnd, int ctrlid, COLORREF color);
extern VOID SetBoardOptionEnables(HWND hDlg);
extern BoardSize BoardOptionsWhichRadio(HWND hDlg);
extern BOOL APIENTRY MyCreateFont(HWND hwnd, MyFont *font);
extern VOID UpdateSampleText(HWND hDlg, int id, MyColorizeAttribs *mca);
extern LRESULT CALLBACK ColorizeTextDialog(HWND , UINT, WPARAM, LPARAM);
extern VOID ColorizeTextPopup(HWND hwnd, ColorClass cc);
extern VOID SetIcsOptionEnables(HWND hDlg);
extern VOID SetSampleFontText(HWND hwnd, int id, const MyFont *mf);
extern VOID CopyFont(MyFont *dest, const MyFont *src);
//extern void InitSoundComboData(SoundComboData *scd);
//extern void ResetSoundComboData(SoundComboData *scd);
//extern void InitSoundCombo(HWND hwndCombo, SoundComboData *scd);
//extern int SoundDialogWhichRadio(HWND hDlg);
//extern VOID SoundDialogSetEnables(HWND hDlg, int radio);
//extern char * SoundDialogGetName(HWND hDlg, int radio);
//extern void DisplaySelectedSound(HWND hDlg, HWND hCombo, const char *name);
extern VOID ParseCommSettings(char *arg, DCB *dcb);
extern VOID PrintCommSettings(FILE *f, char *name, DCB *dcb);
extern void InitCombo(HANDLE hwndCombo, ComboData *cd);
extern void SelectComboValue(HANDLE hwndCombo, ComboData *cd, unsigned value);
extern VOID SetLoadOptionEnables(HWND hDlg);
extern VOID SetSaveOptionEnables(HWND hDlg);
extern VOID SetTimeControlEnables(HWND hDlg,ChessProgramState *cps);

//extern VOID ConsoleOutput(char* data, int length, int forceVisible);
//extern VOID ConsoleCreate();
extern void IcsCountSetPopup(void);
extern LRESULT CALLBACK
  ConsoleWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
extern VOID ColorizeTextPopup(HWND hwnd, ColorClass cc);
extern VOID PrintCommSettings(FILE *f, char *name, DCB *dcb);
extern VOID ParseCommSettings(char *arg, DCB *dcb);
//extern LRESULT CALLBACK
//  StartupDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
extern VOID APIENTRY MenuPopup(HWND hwnd, POINT pt, HMENU hmenu, UINT def);
extern void ParseIcsTextMenu(char *icsTextMenuString);
extern VOID PopUpMoveDialog(char firstchar);
extern VOID UpdateSampleText(HWND hDlg, int id, MyColorizeAttribs *mca);

extern void DrawPosition(dispboard_t* pDis, bool full,uint8* B256);

extern void WinErrorDisp(LPTSTR lpszFunction);

extern bool IsGGqjNormal(PGN *pgg);
//extern ChessMove PromoCharToMoveType(int whiteOnMove, int promoChar);
//SQL
//extern bool MysqlInit(MYSQL* my);
//extern MYSQL* MysqlCreateConnect(MYSQL* my,char *host, 
//			char *user, char *pass,char *dbname, unsigned int port);


extern void ShutDownFrontEnd(void);

extern void IDT_CANJU_Event(void);


//extern void Sql2000_To_Mysql_Event(void);
//extern VOID Board90toFRinfo(Board90 board, FRinfo_t *FR);

extern void ClearProgramStats(void);  //初始化程序状态
//extern void CoordsToAlgebraicCallback (Board90 board, int flags,
//					 ChessMove kind, int fx, int fy, int tx, int ty, VOIDSTAR closure);
//extern void CheckTestCallback (Board90 board, int flags, ChessMove kind,
//				 int fx, int fy, int tx, int ty, VOIDSTAR closure);

extern void	DrawBoardOnDC(dispboard_t* pDis,HDC hdc, uint8* B256, HDC tmphdc, HDC hdcmask);	//在DC上画上棋子
extern void DrawHighlightsOnDC(dispboard_t* pDis,HDC hdc);										//画上高亮的棋格	
extern void	DrawPieceOnDC(dispboard_t* pDis, HDC hdc, sint8 piece, int color, int sqcolor,
						  int x, int y, HDC tmphdc, HDC hdcmask);				//画上相应的一个棋子哇

//extern void DispStatRtime(const char* string);
//extern void DispStatBtime(const char* string);

extern int	EventToSquare_X(int x, dispboard_t* pDis);
extern int  EventToSquare_Y(int y, dispboard_t* pDis);

//extern void FitTabDialogToTabControl();  //重新调整一下TAB中的子控件大小

//extern void GenLegalCallback (Board90 board, int flags, ChessMove kind,
//				int fx, int fy, int tx, int ty,	VOIDSTAR closure);



//extern void LegalityTestCallback (Board90 board,int flags, ChessMove kind,
//				    int fx, int fy, int tx, int ty,VOIDSTAR closure);
extern void LoadGameDialog(HWND hwnd, char* title);



/* Is a move from (rf, ff) to (rt, ft) legal for the player whom the
   flags say is on move?  Other arguments as in GenPseudoLegal.
   Returns the type of move made, taking promoChar into account. */
//extern ChessMove LegalityTest (Board90 board, int flags, int fx, int fy, int tx, int ty);


extern void	MouseEvent(dispboard_t* pDis,HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);	//鼠标动作程序
//extern void MateTestCallback (Board90 board, int flags, ChessMove kind,
//				int fx, int fy, int tx, int ty,	VOIDSTAR closure);
extern void PackHolding(char packed[],char *holding);
//extern int  PosFlags(int index);
extern Boolean ParseOneMove (TCHAR *move, int moveNum,ChessMove *moveType, 
							 int *fromX, int *fromY,int *toX, int *toY,int ucci);

extern void NextMatchGame (void);
extern char PieceToCharUCCI(sq_t p,   int ucci);

extern void PositionToFEN (dispboard_t* pDis, TCHAR *fen, int move,int ucci);






//extern void SendGGqjToDlg(PGN *pgg);  //发送佳佳棋局中的信息到对话框中
extern void SendToPlayer(TCHAR *data,int length);
extern void SetupDropMenu(HMENU hmenu);

extern void MachinePlayEvent(ChessProgramState* now);
extern void ToolBarMachineThink(dispboard_t* pDis, BOOL isRed);
//extern void IsComputerCanGo(ChessProgramState* now); //计算机能不能走一步
//extern void GetTimeSetInfoFromCps(ChessProgramState *cps);

extern void SetCpsPlayWhat(ChessProgramState* now); //设定CPS走那方


//extern void SendStartInfoToCps(ChessProgramState* cps);

extern void TelnetRequest(TCHAR ddww, TCHAR option) ;
extern void TwoMachinesEventIfReady (dispboard_t* pDis);

//extern void TestIsSame(void);
//
//extern void TestFaceEvent(void);

extern int piece_from_char(int c);

extern uint64 genrand_int64(void);

extern uint64 compute_hash_key(const position_t *pos);

//走子方是不是被将军
extern int isTurnInCheck(position_t * pos, int side);
extern void init_mersenne(void);
extern void init_zobrist(void);
extern BOOL set_position(dispboard_t* pDis, position_t *pos, TCHAR *fen);

extern void	DispHistoryStepName(dispboard_t* pDis,int moveNum);
extern void ScreenSquare(dispboard_t* pDis,int x, int y,POINT * pt);
extern void Tween(POINT *start,POINT * mid, POINT *finish,int factor,POINT frames[],int *nFrames);
extern void	DrawHighlightOnDC(dispboard_t* pDis, HDC hdc, BOOLEAN on, int x, int y, int pen);
extern int  piece_to_char(int piece);
extern void position_to_fen_by_b256(uint8 B256[256],int side, TCHAR* fen);

extern void ErrorPopUp(TCHAR *title, TCHAR *content);
extern void UnMakeMove(void);

//extern move_stack_t *generate_check_evasions(position_t *pos, move_stack_t *ms);
//extern move_stack_t *generate_moves_by_testlegal(position_t *pos, move_stack_t *ms);

extern int strncasecmp(const char *s1, const char *s2, size_t length);

extern void DlgDefaultPosition(void);

//extern void ShowStepListEvent(void);
//extern void FitStepListDlgPosition(HWND hDlg);

//extern void TimeDisplayListEvent(void);
//extern void FitTimeDisplayDlgPosition(HWND hDlg);

extern void DLG_Rich_Log_Event(void);
extern void FitRichLogDlgPosition(HWND hDlg);

extern void DLG_BOOK_Event(void);
extern void FitBookDlgPositionDefault(HWND hDlg);
extern void ConsoleOutput(TCHAR* data, int length, int forceVisible);

//extern void LogOut(ColorClass cc, char* data, bool NotShout);

extern void LogOut(TCHAR* data);
extern void LogOuts(char* data);

extern void BoardDisplay(uint8 B256[256], char* reason);


//*********************************MYSQL************************************
#ifdef USE_MYSQL_DATABASE
extern int	LoadGameOneGameFromMysql(GameQJ *pgg,bool isToEnd);			//读入一局佳佳棋局到内存中
extern void	initializeMySql(void);
extern void Import_QJ_To_Mysql_Event(void);
				//得到一局已校对的棋局来学习一下
extern bool     MysqlGetOneCheckedAndLearn(GameQJ *pgg, MYSQL *my);
extern bool SaveQiJuFrompDisBoardEvent(GameQJ *pgg,MYSQL *my);
extern bool MysqlSaveGGqj(GameQJ *pgg, MYSQL* mycon,bool isUpdate);
extern bool MysqlGetOneUncheckGGqj(GameQJ *pgg, MYSQL* mycon);
extern void Web_To_Mysql_Event(void);
extern void LearnChecked_QJ_To_Mysql_Event(void);
#endif



extern int SqlLiteCallback(void *NotUsed, int argc, char **argv, char **azColName);

extern int SqliteOpenDataBase(sqlite3 **db, char* dbname);

extern int SqlLiteExec(sqlite3 *db, char* sql);

extern int SaveSettingDataToSqlite(void);       //保存设定数据到数据库中

extern int GetSetingInfoFromSqlite(void);

extern int GetCountInfoByUserId(ChessProgramState *cps,int id);
extern int GetNetInfoByNetId(ChessProgramState *cps,int id);








extern int  BD_initEnv(STOCK_DBS* mst);     //初始化环境

extern int BD_initEnv2();     //初始化环境

extern void BerKeley_DB_EXIT(STOCK_DBS *mst);

extern BOOL FillBookbyPos(dispboard_t* pDis, DB *db);


extern void UpdateBookResult(dispboard_t *pDis, DB *db);

extern int  Book_Back_Up(DB* dst, DB* src);



extern void read_from_ics_mxq_en183(InputSourceRef isr, VOIDSTAR closure,	char *data, int count, int error);
extern void read_from_ics_mxq_cn183(InputSourceRef isr, VOIDSTAR closure,	char *data, int count, int error);

extern void read_from_ics_xqclub(InputSourceRef isr, VOIDSTAR closure, char *data, int count, int error);

extern void SetIcsTitleName(TCHAR* title);

extern   int ban_repeat(position_t * pos);
//extern int Draw_Repeat_Ban(position_t *pos);

extern void  YqInfoToSetDialog(ChessProgramState *cps, HWND hDlg); //将引擎的信息显示到对话框

extern int   GetYqinfoFromSqliteByID(ChessProgramState *cps,int id);

//加载一个引擎，并指出加载到那一个
//extern void  LoadChessProgramState(ChessProgramState *cps, HWND win, int toWhich);
extern void LoadChessProgramState(ChessProgramState *precps, ChessProgramState *loadcps, HWND hWin);

extern void  InternetPlayEvent(void);  

extern bool position_is_ok(position_t *pos);
 //给每一个旁观的棋局发送同样的信息
//extern void SendEveryObsBoard(UINT message,WPARAM wParam,LPARAM lParam);

extern int  HaveBookMoveInDB(dispboard_t* pDis);
extern int  BD_openGoodDb(STOCK_DBS* mst);

extern BOOL APIENTRY firstDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
extern BOOL isHaveKeyfile(char char16[16]);


extern void EnCode(char *Command);

//extern void LetCpsPonder(ChessProgramState *cps);
extern void DLG_SAVE_GAME_Event(int table);
//extern void PgnInitialize(dispboard_t *pDis);

extern void AutoLearnEvent(void);
extern void UpDataOneFaceEvent(dispboard_t* pDis,DB *db);

extern BOOL PgnGetGameInfoFromSqliteById(dispboard_t* pDis, int id, sqlite3 *db);
extern BOOL PgnFenToPos(dispboard_t* pDis, BOOL isStop);
extern BOOL PgnUpdateGameToSqlite(dispboard_t *pDis, sqlite3 *db);
extern int  GetPosBookScoreByAllNextPos(position_t *pos, DB *db);
extern int  bk_GetBookInfo(book_face_t* bft, DB *db);
extern int  bk_SaveBookInfo(book_face_t* bft, DB *db);
extern void PgnFenFromCurPosition(dispboard_t *pDis);
extern BOOL PgnInsertGameToSqlite(dispboard_t *pDis, int* saveId, sqlite3 *db);
//局面状态改变
extern BOOL ChangeGameMode(dispboard_t *pDis, GameMode gm);
extern BOOL HandleTableIcsMessage(dispboard_t *pDis, TCHAR* buf);
extern int 	ConnectToIcs(void);
extern void TrimIcsName(TCHAR* Name);

//extern void ChangeDisBoardTable(dispboard_t *pDis, int table);

extern void IcsGameStart(dispboard_t* pDis);

extern void SendAllEvalToClipBoard(dispboard_t* pDis);
extern void SendAllEvalToClipBoardFlip(dispboard_t* pDispDis);

extern BOOL AnalizeEvent(dispboard_t* pDis);             //让引擎思考
extern BOOL LetYqAnalizeCurPos(dispboard_t* pDis);       //让引擎分析当前的局面

extern void Back_Up_Book(void);
extern void FitMainTabPosition(dispboard_t *pDis);

extern void UpdateSteplParam(void);
extern BOOL PgnGetOneFinishedGameFromSql(dispboard_t *pDis, sqlite3 *db);
extern TCHAR *MoveToUBBove(TCHAR *pm);
#endif