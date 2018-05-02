#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

void
InputEvent(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
	InputSource *is;

	is = (InputSource *) lParam;
	if (is->lineByLine) {
		/* Feed in lines one by one */
		char *p = is->buf;
		char *q = p;
		while (q < is->next) {
			if (*q++ == '\n') {
				(is->func)(is, is->closure, p, int(q - p), NO_ERROR);
				p = q;
			}
		}
		/* Move any partial line to the start of the buffer */
		q = is->buf;
		while (p < is->next) {
			*q++ = *p++;
		}
		is->next = q;
		if (is->error != NO_ERROR || is->count == 0) {
			/* Notify backend of the error.  Note: If there was a partial
			line at the end, it is not flushed through. */
			(is->func)(is, is->closure, is->buf, is->count, is->error);   
		}
	} 
	else {
		/* Feed in the whole chunk of input at once */
		(is->func)(is, is->closure, is->buf, is->count, is->error);
		is->next = is->buf;
	}
}

void
DestroyChildProcess(ProcRef pr, int/*boolean*/ signal){
	ChildProc *cp;

	cp = (ChildProc *) pr;
	if (cp == NULL) return;

	switch (cp->kind) {
  case CPReal:
	  /* TerminateProcess is considered harmful, so... */
	  CloseHandle(cp->hTo); /* Closing this will give the child an EOF and hopefully kill it */
	  if (cp->hFrom) CloseHandle(cp->hFrom);  /* if NULL, InputThread will close it */
	  /* The following doesn't work because the chess program
	  doesn't "have the same console" as WinBoard.  Maybe
	  we could arrange for this even though neither WinBoard
	  nor the chess program uses a console for stdio? */
	  /*!!if (signal) GenerateConsoleCtrlEvent(CTRL_BREAK_EVENT, cp->pid);*/
	  CloseHandle(cp->hProcess);
	  break;

  case CPComm:
	  if (cp->hFrom) CloseHandle(cp->hFrom);
	  break;

  case CPSock:
	  closesocket(cp->sock);
	  WSACleanup();
	  break;

  case CPRcmd:
	  if (signal) send(cp->sock2, "\017", 1, 0);  /* 017 = 15 = SIGTERM */
	  closesocket(cp->sock);
	  closesocket(cp->sock2);
	  WSACleanup();
	  break;
	}
	free(cp);
}


int
OpenCommPort(char *name, ProcRef *pr){
    return -1;
	//HANDLE h;
	//COMMTIMEOUTS ct;
	//ChildProc *cp;
	//char fullname[MSG_SIZ];

	//if (*name != '\\'){
	//	//sprintf(fullname, "\\\\.\\%s", name);
	//	StringCbPrintf(fullname,MSG_SIZ,"\\\\.\\%s", name);
	//}
	//else{
	//	//strcpy(fullname, name);
	//	StringCbCopy(fullname,MSG_SIZ,name);
	//}

	//h = CreateFile(name, GENERIC_READ | GENERIC_WRITE,
	//	0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
	//if (h == (HANDLE) -1) {
	//	return GetLastError();
	//}
	//pDis->hCommPort = (HWND)h;

	//if (!SetCommState(h, (LPDCB) &DIS.dcb)) return GetLastError();

	///* Accumulate characters until a 100ms pause, then parse */
	//ct.ReadIntervalTimeout = 100;
	//ct.ReadTotalTimeoutMultiplier = 0;
	//ct.ReadTotalTimeoutConstant = 0;
	//ct.WriteTotalTimeoutMultiplier = 0;
	//ct.WriteTotalTimeoutConstant = 0;
	//if (!SetCommTimeouts(h, (LPCOMMTIMEOUTS) &ct)) return GetLastError();

	///* Prepare return value */
	//cp = (ChildProc *) calloc(1, sizeof(ChildProc));
	//cp->kind = CPComm;
	//cp->hFrom = h;
	//cp->hTo = h;
	//*pr = (ProcRef *) cp;

	//return NO_ERROR;
}

void
show_bytes(FILE* fp, char *buf, int count) {
    while (count--) {
/*        if (*buf < 040 || *(unsigned char *) buf > 0177) {
            fprintf(fp, "\\%03o", *buf & 0xff);
        }*/ 
        if ((unsigned char)(*buf) < 040 ) {
            fprintf(fp, "\\%03o", *buf & 0xff);
        }
        else {
            putc(*buf, fp);
        }
        buf++;
    }
    fflush(fp);
}



//int
//looking_at(buf, index, pattern)
//char *buf;
//int *index;
//char *pattern;
//{
//    char *bufp = &buf[*index], *patternp = pattern;
//    int star_count = 0;
//    char *matchp = star_match[0];
//
//    for (;;) {
//        if (*patternp == NULLCHAR) {
//            *index = leftover_start = bufp - buf;
//            *matchp = NULLCHAR;
//            return TRUE;
//        }
//        if (*bufp == NULLCHAR) return FALSE;
//        if (*patternp == '*') {
//            if (*bufp == *(patternp + 1)) {
//                *matchp = NULLCHAR;
//                matchp = star_match[++star_count];
//                patternp += 2;
//                bufp++;
//                continue;
//            } else if (*bufp == '\n' || *bufp == '\r') {
//                patternp++;
//                if (*patternp == NULLCHAR)
//                    continue;
//                else
//                    return FALSE;
//            } else {
//                *matchp++ = *bufp++;
//                continue;
//            }
//        }
//        if (*patternp != *bufp) return FALSE;
//        patternp++;
//        bufp++;
//    }
//}
//int
//looking_at(char *buf,int *index, char *pattern) {
//int
//looking_at(TCHAR *buf, TCHAR *pattern) {
//	/* Test whether pattern is present at &buf[*index]; if so, return TRUE,
//	advance *index beyond it, and set leftover_start to the new value of
//	*index; else return FALSE.  If pattern contains the character '*', it
//	matches any sequence of characters not containing '\r', '\n', or the
//	character following the '*' (if any), and the matched sequence(s) are
//	copied into star_match.
//	*/
//	int ip = 0;
//	int *index = &ip;
//	TCHAR *bufp = &buf[*index], *patternp = pattern;
//	int star_count = 0;
//	TCHAR *matchp = ICS.star_match[0];
//
//	for (;;) {
//		if (*patternp == NULLCHAR) {
//			/**index  = ICS.leftover_start = (int)(bufp - buf);*/
//			*index = (int)(bufp - buf);
//			*matchp = NULLCHAR;
//			return TRUE;
//		}
//		if (*bufp == NULLCHAR){
//			return FALSE;
//		}
//		/*if (*patternp == '*') {*/
//		if (*patternp == '@') {
//			if (*bufp == *(patternp + 1)) {
//				*matchp = NULLCHAR;
//				matchp = ICS.star_match[++star_count];
//				patternp += 2;
//				bufp++;
//				continue;
//			}
//			else if (*bufp == '\n' || *bufp == '\r') {
//				patternp++;
//				if (*patternp == NULLCHAR){
//					continue;
//				}
//				else{
//					return FALSE;
//				}
//			}
//			else {
//				*matchp++ = *bufp++;
//				continue;
//			}
//		}
//		if (*patternp != *bufp){
//			return FALSE;
//		}
//		patternp++;
//		bufp++;
//	}
//
//	//return FALSE;
//}

//int
//looking_at(char *buf,int *index, char *pattern) {
int
looking_at(TCHAR *buf, TCHAR *pattern) {
    /* Test whether pattern is present at &buf[*index]; if so, return TRUE,
    advance *index beyond it, and set leftover_start to the new value of
    *index; else return FALSE.  If pattern contains the character '*', it
    matches any sequence of characters not containing '\r', '\n', or the
    character following the '*' (if any), and the matched sequence(s) are
    copied into star_match.
    */
    int ip = 0;
    int *index = &ip;
	TCHAR *bufp = &buf[*index], *patternp = pattern;
    int star_count = 0;
	TCHAR *matchp = ICS.star_match[0];

    for (;;) {
        if (*patternp == NULLCHAR) {
            /**index  = ICS.leftover_start = (int)(bufp - buf);*/
            *index  = (int)(bufp - buf);
            *matchp = NULLCHAR;
            return TRUE;
        }
        if (*bufp == NULLCHAR){
            return FALSE;
        }
        /*if (*patternp == '*') {*/
        if (*patternp == '@') {
            if (*bufp == *(patternp + 1)) {
                *matchp = NULLCHAR;
                matchp = ICS.star_match[++star_count];
                patternp += 2;
                bufp++;
                continue;
            } 
            else if (*bufp == '\n' || *bufp == '\r') {
                patternp++;
                if (*patternp == NULLCHAR){
                    continue;
                }
                else{
                    return FALSE;
                }
            } 
            else {
                *matchp++ = *bufp++;
                continue;
            }
        }
        if (*patternp != *bufp){
            return FALSE;
        }
        patternp++;
        bufp++;
    }

    //return FALSE;
}
void
SendToPlayer(TCHAR *data,int length){
    int error=0, outCount;
    //outCount = OutputToProcess(NoProc, data, length, &error);
	outCount = length;
	ConsoleOutput(data, length, FALSE);
    if (outCount < length) {
		DisplayFatalError(L"Error writing to display", error, 1);
    }

	//if (pr == NoProc) {
	//	ConsoleOutput(message, count, FALSE);
	//	return count;
	//}
}

//错误	6	error LNK2001 : 无法解析的外部符号 "void __cdecl cstruct dispboard_t *,char *)" (? DisplayMoveError@@YAXPAUdispboard_t@@PAD@Z)	E : \PROG\GGchessGUi\moves.obj	GGchess


void
InterruptChildProcess(ProcRef pr)
{
  ChildProc *cp;

  cp = (ChildProc *) pr;
  if (cp == NULL) return;
  switch (cp->kind) {
  case CPReal:
    /* The following doesn't work because the chess program
       doesn't "have the same console" as WinBoard.  Maybe
       we could arrange for this even though neither WinBoard
       nor the chess program uses a console for stdio */
    /*!!GenerateConsoleCtrlEvent(CTRL_C_EVENT, cp->pid);*/
    break;

  case CPComm:
  case CPSock:
    /* Can't interrupt */
    break;

  case CPRcmd:
    send(cp->sock2, "\002", 1, 0);  /* 2 = SIGINT */
    break;
  }
}


int
OpenTelnet(TCHAR *host, TCHAR *port, ProcRef *pr){
	TCHAR cmdLine[MSG_SIZ];

	if (port[0] == NULLCHAR) {
		//sprintf(cmdLine, "%s %s", appData.telnetProgram, host);
		swprintf_s(cmdLine,MSG_SIZ,
			_T("%s %s"), appData.telnetProgram, host);
	} else {
		//sprintf(cmdLine, "%s %s %s", appData.telnetProgram, host, port);
		swprintf_s(cmdLine, MSG_SIZ,
			_T("%s %s %s"), appData.telnetProgram, host, port);
	}
    //telnet xiangqi.movesky.net 3791

	return StartChildProcess(cmdLine, _T(""), pr);
}

int	/* Code to open TCP sockets */
OpenTCP(char *host, char *port, ProcRef *pr){
	ChildProc *cp;
	int err;
	SOCKET s;
	struct sockaddr_in sa, mysa;
	struct hostent FAR *hp;
	unsigned short uport;
	WORD wVersionRequested;
	WSADATA wsaData;

	/* Initialize socket DLL */
	wVersionRequested = MAKEWORD(1, 1);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) return err;

	/* Make socket */
	if ((s = socket(PF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		err = WSAGetLastError();
		WSACleanup();
		return err;
	}

	/* Bind local address using (mostly) don't-care values.
	*/
	memset((char *) &mysa, 0, sizeof(struct sockaddr_in));
	mysa.sin_family = AF_INET;
	mysa.sin_addr.s_addr = INADDR_ANY;
	uport = (unsigned short) 0;
	mysa.sin_port = htons(uport);
	if (bind(s, (struct sockaddr *) &mysa, sizeof(struct sockaddr_in))
		== SOCKET_ERROR) {
			err = WSAGetLastError();
			WSACleanup();
			return err;
		}
#define _WINSOCK_DEPRECATED_NO_WARNINGS
		/* Resolve remote host name */
		memset((char *) &sa, 0, sizeof(struct sockaddr_in));
		if (!(hp = gethostbyname(host))) {
			unsigned int b0, b1, b2, b3;

			err = WSAGetLastError();

			if (sscanf_s(host, "%u.%u.%u.%u", &b0, &b1, &b2, &b3) == 4) {
				hp = (struct hostent *) calloc(1, sizeof(struct hostent));
				hp->h_addrtype = AF_INET;
				hp->h_length = 4;
				hp->h_addr_list = (char **) calloc(2, sizeof(char *));
				hp->h_addr_list[0] = (char *) malloc(4);
				hp->h_addr_list[0][0] = (char) b0;
				hp->h_addr_list[0][1] = (char) b1;
				hp->h_addr_list[0][2] = (char) b2;
				hp->h_addr_list[0][3] = (char) b3;
			} else {
				WSACleanup();
				return err;
			}
		}
		sa.sin_family = hp->h_addrtype;
		uport = (unsigned short) atoi(port);
		sa.sin_port = htons(uport);
		memcpy((char *) &sa.sin_addr, hp->h_addr, hp->h_length);

		/* Make connection */
		if (connect(s, (struct sockaddr *) &sa,
			sizeof(struct sockaddr_in)) == SOCKET_ERROR) {
				err = WSAGetLastError();
				WSACleanup();
				return err;
			}

			/* Prepare return value */
			cp = (ChildProc *) calloc(1, sizeof(ChildProc));
			cp->kind = CPSock;
			cp->sock = s;
			*pr = (ProcRef *) cp;

			return NO_ERROR;
}



int
OpenLoopback(ProcRef *pr){
  DisplayFatalError(L"Not implemented", 0, 1);
  return NO_ERROR;
}

#define _WINSOCK_DEPRECATED_NO_WARNINGS
int
OpenRcmd(char* host, char* user, char* cmd, ProcRef* pr){
	ChildProc *cp;
	int err;
	SOCKET s, s2, s3;
	struct sockaddr_in sa, mysa;
	struct hostent FAR *hp;
	unsigned short uport;
	WORD wVersionRequested;
	WSADATA wsaData;
	int fromPort;
	char stderrPortStr[MSG_SIZ];

	/* Initialize socket DLL */
	wVersionRequested = MAKEWORD(1, 1);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) return err;

	/* Resolve remote host name */
	memset((char *) &sa, 0, sizeof(struct sockaddr_in));
	if (!(hp = gethostbyname(host))) {
		unsigned int b0, b1, b2, b3;

		err = WSAGetLastError();

		if (sscanf_s(host, "%u.%u.%u.%u", &b0, &b1, &b2, &b3) == 4) {
			hp = (struct hostent *) calloc(1, sizeof(struct hostent));
			hp->h_addrtype = AF_INET;
			hp->h_length = 4;
			hp->h_addr_list = (char **) calloc(2, sizeof(char *));
			hp->h_addr_list[0] = (char *) malloc(4);
			hp->h_addr_list[0][0] = (char) b0;
			hp->h_addr_list[0][1] = (char) b1;
			hp->h_addr_list[0][2] = (char) b2;
			hp->h_addr_list[0][3] = (char) b3;
		} else {
			WSACleanup();
			return err;
		}
	}
	sa.sin_family = hp->h_addrtype;
	uport = (unsigned short) 514;
	sa.sin_port = htons(uport);
	memcpy((char *) &sa.sin_addr, hp->h_addr, hp->h_length);

	/* Bind local socket to unused "privileged" port address
	*/
	s = INVALID_SOCKET;
	memset((char *) &mysa, 0, sizeof(struct sockaddr_in));
	mysa.sin_family = AF_INET;
	mysa.sin_addr.s_addr = INADDR_ANY;
	for (fromPort = 1023;; fromPort--) {
		if (fromPort < 0) {
			WSACleanup();
			return WSAEADDRINUSE;
		}
		if (s == INVALID_SOCKET) {
			if ((s = socket(PF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
				err = WSAGetLastError();
				WSACleanup();
				return err;
			}
		}
		uport = (unsigned short) fromPort;
		mysa.sin_port = htons(uport);
		if (bind(s, (struct sockaddr *) &mysa, sizeof(struct sockaddr_in))
			== SOCKET_ERROR) {
				err = WSAGetLastError();
				if (err == WSAEADDRINUSE) continue;
				WSACleanup();
				return err;
			}
			if (connect(s, (struct sockaddr *) &sa,
				sizeof(struct sockaddr_in)) == SOCKET_ERROR) {
					err = WSAGetLastError();
					if (err == WSAEADDRINUSE) {
						closesocket(s);
						s = -1;
						continue;
					}
					WSACleanup();
					return err;
				}
				break;
	}

	/* Bind stderr local socket to unused "privileged" port address
	*/
	s2 = INVALID_SOCKET;
	memset((char *) &mysa, 0, sizeof(struct sockaddr_in));
	mysa.sin_family = AF_INET;
	mysa.sin_addr.s_addr = INADDR_ANY;
	for (fromPort = 1023;; fromPort--) {
		if (fromPort == appData.prevStderrPort) continue; // don't reuse port
		if (fromPort < 0) {
			(void) closesocket(s);
			WSACleanup();
			return WSAEADDRINUSE;
		}
		if (s2 == INVALID_SOCKET) {
			if ((s2 = socket(PF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
				err = WSAGetLastError();
				closesocket(s);
				WSACleanup();
				return err;
			}
		}
		uport = (unsigned short) fromPort;
		mysa.sin_port = htons(uport);
		if (bind(s2, (struct sockaddr *) &mysa, sizeof(struct sockaddr_in))
			== SOCKET_ERROR) {
				err = WSAGetLastError();
				if (err == WSAEADDRINUSE) continue;
				(void) closesocket(s);
				WSACleanup();
				return err;
			}
			if (listen(s2, 1) == SOCKET_ERROR) {
				err = WSAGetLastError();
				if (err == WSAEADDRINUSE) {
					closesocket(s2);
					s2 = INVALID_SOCKET;
					continue;
				}
				(void) closesocket(s);
				(void) closesocket(s2);
				WSACleanup();
				return err;
			}
			break;
	}
	appData.prevStderrPort = fromPort; // remember port used
	//sprintf(stderrPortStr, "%d", fromPort);
	sprintf_s(stderrPortStr,MSG_SIZ,"%d", fromPort);

	if (send(s, stderrPortStr, (int)strlen(stderrPortStr) + 1, 0) == SOCKET_ERROR) {
		err = WSAGetLastError();
		(void) closesocket(s);
		(void) closesocket(s2);
		WSACleanup();
		return err;
	}

	//if (send(s, UserName(), (int)strlen(UserName()) + 1, 0) == SOCKET_ERROR) {
	//	err = WSAGetLastError();
	//	(void) closesocket(s);
	//	(void) closesocket(s2);
	//	WSACleanup();
	//	return err;
	//}
    if (*user == NULLCHAR){
        //user = UserName();
        user = "test";
    }
	if (send(s, user, (int)strlen(user) + 1, 0) == SOCKET_ERROR) {
		err = WSAGetLastError();
		(void) closesocket(s);
		(void) closesocket(s2);
		WSACleanup();
		return err;
	}
	if (send(s, cmd, (int)strlen(cmd) + 1, 0) == SOCKET_ERROR) {
		err = WSAGetLastError();
		(void) closesocket(s);
		(void) closesocket(s2);
		WSACleanup();
		return err;
	}

	if ((s3 = accept(s2, NULL, NULL)) == INVALID_SOCKET) {
		err = WSAGetLastError();
		(void) closesocket(s);
		(void) closesocket(s2);
		WSACleanup();
		return err;
	}
	(void) closesocket(s2);  /* Stop listening */

	/* Prepare return value */
	cp = (ChildProc *) calloc(1, sizeof(ChildProc));
	cp->kind = CPRcmd;
	cp->sock = s;
	cp->sock2 = s3;
	*pr = (ProcRef *) cp;

	return NO_ERROR;
}







int//开始象棋引擎
StartChildProcess(TCHAR *cmdLine, TCHAR *dir, ProcRef *pr){

	/* Start a child process running the given program.
	The process's standard output can be read from "from", and its
	standard input can be written to "to".
	Exit with fatal error if anything goes wrong.
	Returns an opaque pointer that can be used to destroy the process
	later.
	*/
#define BUFSIZE 4096*2

	HANDLE hChildStdinRd;
	HANDLE hChildStdinWr;
	HANDLE hChildStdoutRd;
	HANDLE hChildStdoutWr;
	HANDLE hChildStdinWrDup;
	HANDLE hChildStdoutRdDup;
	SECURITY_ATTRIBUTES saAttr;
	BOOL fSuccess;
	PROCESS_INFORMATION piProcInfo;
	STARTUPINFO siStartInfo;
	ChildProc *cp;
	TCHAR buf[MSG_SIZ];
	DWORD err;

#ifdef DEBUG_USE_DEBUG_FILE
	//if (appData.debugMode) {
		fprintf(appData.debugFP, "StartChildProcess (dir=\"%s\") %s\n", dir, cmdLine);
	//}
#endif

	*pr = NoProc;

	/* Set the bInheritHandle flag so pipe handles are inherited. */
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;        //一定要为TRUE，不然句柄不能被继承。
	saAttr.lpSecurityDescriptor = NULL;  //使用系统默认的安全描述符

	/*
	* The steps for redirecting child's STDOUT:
	*     1. Create anonymous pipe to be STDOUT for child.
	*     2. Create a noninheritable duplicate of read handle,
	*         and close the inheritable read handle.
	*/

	/* Create a pipe for the child's STDOUT. */
	if (! CreatePipe(&hChildStdoutRd, &hChildStdoutWr, &saAttr, 0)) {
		return GetLastError();
	}

	/* Duplicate the read handle to the pipe, so it is not inherited. */
	fSuccess = DuplicateHandle(GetCurrentProcess(), hChildStdoutRd,
		GetCurrentProcess(), &hChildStdoutRdDup, 0,
		FALSE,	/* not inherited */
		DUPLICATE_SAME_ACCESS);
	if (! fSuccess) {
		return GetLastError();
	}
	CloseHandle(hChildStdoutRd);

	/*
	* The steps for redirecting child's STDIN:
	*     1. Create anonymous pipe to be STDIN for child.
	*     2. Create a noninheritable duplicate of write handle,
	*         and close the inheritable write handle.
	*/

	/* Create a pipe for the child's STDIN. */
	if (! CreatePipe(&hChildStdinRd, &hChildStdinWr, &saAttr, 0)) {
		return GetLastError();
	}

	/* Duplicate the write handle to the pipe, so it is not inherited. */
	fSuccess = DuplicateHandle(GetCurrentProcess(), hChildStdinWr,
		GetCurrentProcess(), &hChildStdinWrDup, 0,
		FALSE,	/* not inherited */
		DUPLICATE_SAME_ACCESS);
	if (! fSuccess) {
		return GetLastError();
	}
	CloseHandle(hChildStdinWr);

	/* Arrange to (1) look in dir for the child .exe file, and
	* (2) have dir be the child's working directory.  Interpret
	* dir relative to the directory WinBoard loaded from. */
	GetCurrentDirectory(MSG_SIZ, buf);
	SetCurrentDirectory(installDir);
	SetCurrentDirectory(dir);

    //if(DIS.first.ucci == UCCI_CYC105){
    //    cmdLine = "cyclone.exe";
    //}
    //else{
    //    //SetCurrentDirectory(dir);
    //}

    //cmdLine = "F:\\Test105\\debug\\cyclone.exe";

    

	/* Now create the child process. */

	siStartInfo.cb = sizeof(STARTUPINFO);
	siStartInfo.lpReserved          = NULL;
	siStartInfo.lpDesktop           = NULL;
	siStartInfo.lpTitle             = NULL;
	siStartInfo.dwFlags             = STARTF_USESTDHANDLES;
	siStartInfo.cbReserved2         = 0;
	siStartInfo.lpReserved2         = NULL;
	siStartInfo.hStdInput           = hChildStdinRd;
	siStartInfo.hStdOutput          = hChildStdoutWr;
	siStartInfo.hStdError           = hChildStdoutWr;

    //char plug[MSG_SIZ];
	//StringCbPrintf(plug,MSG_SIZ,"%s -info", cmdLine);

    

	//fSuccess = CreateProcess(NULL,
	//	cmdLine,	   /* command line */
	//	//plug,
	//	NULL,	   /* process security attributes */
	//	NULL,	   /* primary thread security attrs */
	//	TRUE,	   /* handles are inherited */
	//	DETACHED_PROCESS|CREATE_NEW_PROCESS_GROUP,
	//	NULL,	   /* use parent's environment */
	//	NULL,
	//	&siStartInfo, /* STARTUPINFO pointer */
	//	&piProcInfo); /* receives PROCESS_INFORMATION */

	fSuccess = CreateProcess(
		NULL,			//指定了要执行的模块						//1
		cmdLine,	   /* command line */							//2
														//plug,
		NULL,	   /* process security attributes */				//3
		NULL,	   /* primary thread security attrs */				//4
		TRUE,	   /* handles are inherited */                      //5
		DETACHED_PROCESS|CREATE_NEW_PROCESS_GROUP, 	                //6
		NULL,	   /* use parent's environment */					//7
		NULL,	      //lpCurrentDirectory				//8
		&siStartInfo, /* STARTUPINFO pointer */						//9
		&piProcInfo); /* receives PROCESS_INFORMATION */			//10

	//fSucess = CreateProcess(
	//	NULL,
	//	cmdLine,


	err = GetLastError();
	SetCurrentDirectory(buf); /* return to prev directory */
	if (! fSuccess) {
		return err;
	}

	/* Close the handles we don't need in the parent */
	CloseHandle(piProcInfo.hThread);
	CloseHandle(hChildStdinRd);
	CloseHandle(hChildStdoutWr);

	/* Prepare return value */
	cp = (ChildProc *) calloc(1, sizeof(ChildProc));
	cp->kind = CPReal;
	cp->hProcess = piProcInfo.hProcess;
	cp->pid = piProcInfo.dwProcessId;
	cp->hFrom = hChildStdoutRdDup;
	cp->hTo = hChildStdinWrDup;

	*pr = (void *) cp;

	/* Klaus Friedel says that this Sleep solves a problem under Windows
	2000 where engines sometimes don't see the initial command(s)
	from WinBoard and hang.  I don't understand how that can happen,
	but the Sleep is harmless, so I've put it in.  Others have also
	reported what may be the same problem, so hopefully this will fix
	it for them too.  */
	//Sleep(500);

	return NO_ERROR;
}




int
OutputToProcess(ProcRef pr, TCHAR *message, int count, int *outError){

	DWORD dOutCount;
	int outCount = SOCKET_ERROR;
	ChildProc *cp = (ChildProc *) pr;
	static OVERLAPPED ovl;

	//char buf[2048];

	if (pr == NoProc) {
		ConsoleOutput(message, count, FALSE);
		return count;
	} 

	if (ovl.hEvent == NULL) {
		ovl.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	}
	ovl.Internal = ovl.InternalHigh = ovl.Offset = ovl.OffsetHigh = 0;

	switch (cp->kind) {
		case CPSock:
		case CPRcmd:
			//sprintf_s(buf, sizeof(buf), "%S", message);
			outCount = send(cp->sock, CW2A(message), count, 0);
			if (outCount == SOCKET_ERROR) {
				*outError = WSAGetLastError();
			} 
			else {
				*outError = NO_ERROR;
			}
			break;

		case CPReal:
			if (WriteFile(((ChildProc *)pr)->hTo, CW2A(message), count,&dOutCount, NULL)) {
				*outError = NO_ERROR;
				outCount = (int) dOutCount;
			} 
			else {
				*outError = GetLastError();
			}
			break;

		case CPComm:
			//sprintf_s(buf, sizeof(buf), "%S", message);
			*outError = DoWriteFile(((ChildProc *)pr)->hTo, CW2A(message), count, &dOutCount, &ovl);
			if (*outError == NO_ERROR) {
				outCount = (int) dOutCount;
			}
			break;
	}
	return outCount;
}



int
OutputToProcessDelayed(ProcRef pr, TCHAR *message, int count, int *outError,long msdelay){
  /* Ignore delay, not implemented for WinBoard */
  return OutputToProcess(pr, message, count, outError);
}



InputSourceRef
AddInputSource(ProcRef pr, int lineByLine, InputCallback func, VOIDSTAR closure) {

  InputSource *is, *is2;
  ChildProc *cp = (ChildProc *) pr;

  is = (InputSource *) calloc(1, sizeof(InputSource));
  is->lineByLine = lineByLine;
  is->func = func;
  is->closure = closure;
  is->second = NULL;
  is->next = is->buf;
  if (pr == NoProc) {
    is->kind = CPReal;
    TAB.consoleInputSource = is;        //日志窗口
  } 
  else {
    is->kind = cp->kind;
    switch (cp->kind) {
    case CPReal:
      is->hFile = cp->hFrom;
      cp->hFrom = NULL; /* now owned by InputThread */
      is->hThread =
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) NonOvlInputThread,
		     (LPVOID) is, 0, &is->id);
      break;

    case CPComm:
      is->hFile = cp->hFrom;
      cp->hFrom = NULL; /* now owned by InputThread */
      is->hThread =
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) InputThread,
		     (LPVOID) is, 0, &is->id);
      break;

    case CPSock:
      is->sock = cp->sock;
      is->hThread =
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) SocketInputThread,
		     (LPVOID) is, 0, &is->id);
      break;

    case CPRcmd:
      is2 = (InputSource *) calloc(1, sizeof(InputSource));
      *is2 = *is;
      is->sock = cp->sock;
      is->second = is2;
      is2->sock = cp->sock2;
      is2->second = is2;
      is->hThread =
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) SocketInputThread,
		     (LPVOID) is, 0, &is->id);
      is2->hThread =
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) SocketInputThread,
		     (LPVOID) is2, 0, &is2->id);
      break;
    }
  }
  return (InputSourceRef) is;
}

void
RemoveInputSource(InputSourceRef isr)
{
  InputSource *is;

  is = (InputSource *) isr;
  is->hThread = NULL;  /* tell thread to stop */
  CloseHandle(is->hThread);
  if (is->second != NULL) {
    is->second->hThread = NULL;
    CloseHandle(is->second->hThread);
  }
}
