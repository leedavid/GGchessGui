#include "stdafx.h"
#include <sys/timeb.h>
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

//VOID
//EditCommentPopUp(int index, char *title, char *str){
//  EitherCommentPopUp(index, title, str, TRUE);
//}
int
StopClockTimer(dispboard_t* pDis){
	if (pDis->clockTimerEvent == 0){
		return FALSE;
	}
	/*KillTimer(hwndMain, DIS.clockTimerEvent);*/
    KillTimer(pDis->hwndThis, pDis->clockTimerEvent);
	pDis->clockTimerEvent = 0;
	return TRUE;
}


DelayedEventCallback
GetDelayedEvent(dispboard_t* pDis){
  if (pDis->delayedTimerEvent) {
    return pDis->delayedTimerCallback;
  }
  else {
    return NULL;
  }
}

void
CancelDelayedEvent(dispboard_t* pDis){
  if (pDis->delayedTimerEvent) {
    KillTimer(pDis->hwndThis, pDis->delayedTimerEvent);
    pDis->delayedTimerEvent = 0;
  }
}
int
StopLoadGameTimer(dispboard_t* pDis){
	if (pDis->loadGameTimerEvent == 0) return FALSE;
	KillTimer(pDis->hwndThis, pDis->loadGameTimerEvent);
	pDis->loadGameTimerEvent = 0;
	return TRUE;
}
//这个很有用,用来延时调用一个程序
void
ScheduleDelayedEvent(dispboard_t* pDis, DelayedEventCallback cb, long millisec)
{
  if (pDis->delayedTimerEvent != 0) {
#ifdef DEBUG_MODE
      //if (appData.debugMode) {
      fprintf(appData.debugFP, "ScheduleDelayedEvent: event already scheduled\n");
      //}
#endif
    KillTimer(pDis->hwndThis, pDis->delayedTimerEvent);
    pDis->delayedTimerEvent = 0;
    pDis->delayedTimerCallback();
  }
  pDis->delayedTimerCallback = cb;
  pDis->delayedTimerEvent = (int)SetTimer(pDis->hwndThis, (UINT) DELAYED_TIMER_ID,
				(UINT) millisec, NULL);
}

void
StartAnalysisClock(dispboard_t* pDis){
  if (pDis->analysisTimerEvent) return;
  pDis->analysisTimerEvent = (int)SetTimer(pDis->hwndThis, (UINT) ANALYSIS_TIMER_ID,
		                        (UINT) 2000, NULL);
}
void
StartLoadGameTimer(dispboard_t* pDis, long millisec){
  pDis->loadGameTimerEvent = (int)SetTimer(pDis->hwndThis, (UINT) LOAD_GAME_TIMER_ID,
				(UINT) millisec, NULL);
}


void
DisplayAClock(HDC hdc, int timeRemaining, int highlight, RECT *rect, char *color) {
	char buf[100];
	//char *str;
	//COLORREF oldFg, oldBg;
	//HFONT oldFont;

	if (appData.clockMode) {
		//if (DIS.tinyLayout){
		//	sprintf(buf, "%c %s", color[0], TimeString(timeRemaining));
		//}
		//else{
		//	sprintf(buf, "%s: %s", color,   TimeString(timeRemaining));
		//}
		//StringCbPrintf(buf,sizeof(buf),"%s",TimeString(timeRemaining));
        TimeString(timeRemaining,buf);
		//str = buf;
	} 
    else {
		//str = color;
	}
	if(color[0] == 'W'){
		//DispStatRtime(str);
	}
	else{
		//DispStatBtime(str);
	}

	//if (highlight) {
	//	oldFg = SetTextColor(hdc, RGB(255, 255, 255)); /* white */
	//	oldBg = SetBkColor(hdc, RGB(0, 0, 0)); /* black */
	//} else {
	//	oldFg = SetTextColor(hdc, RGB(0, 0, 0)); /* black */
	//	oldBg = SetBkColor(hdc, RGB(255, 255, 255)); /* white */
	//}
	//oldFont = SelectObject(hdc, font[boardSize][CLOCK_FONT]->hf);

	//ExtTextOut(hdc, rect->left + MESSAGE_LINE_LEFTMARGIN,
	//	rect->top, ETO_CLIPPED|ETO_OPAQUE,
	//	rect, str, strlen(str), NULL);

	//(void) SetTextColor(hdc, oldFg);
	//(void) SetBkColor(hdc, oldBg);
	//(void) SelectObject(hdc, oldFont);
}

void
DisplayWhiteClock(long timeRemaining, int highlight){
	//HDC hdc;
	//hdc = GetDC(hwndMain);
	//if (!IsIconic(hwndMain)) {
	//	DisplayAClock(hdc, timeRemaining, highlight, NULL, "White");
	//}
	//if (highlight && DIS.iconCurrent == DIS.iconBlack) {
	//	DIS.iconCurrent = DIS.iconWhite;
	//	PostMessage(hwndMain, WM_SETICON, (WPARAM) TRUE, (LPARAM) DIS.iconCurrent);
	//	if (IsIconic(hwndMain)) {
	//		DrawIcon(hdc, 2, 2, DIS.iconCurrent);
	//	}
	//}
	//(void) ReleaseDC(hwndMain, hdc);
	//if (DIS.hwndConsole){					//改变一下图标哇
	//	PostMessage(DIS.hwndConsole, WM_SETICON, (WPARAM) TRUE, (LPARAM) DIS.iconCurrent);
	//}
}

void              //显示黑方的时钟
DisplayBlackClock(long timeRemaining, int highlight){
	//HDC hdc;
	//hdc = GetDC(hwndMain);
	//if (!IsIconic(hwndMain)) {
	//	DisplayAClock(hdc, timeRemaining, highlight, NULL, "Black");
	//}
	//if (highlight && DIS.iconCurrent == DIS.iconWhite) {
	//	DIS.iconCurrent = DIS.iconBlack;
	//	PostMessage(hwndMain, WM_SETICON, (WPARAM) TRUE, (LPARAM) DIS.iconCurrent);
	//	if (IsIconic(hwndMain)) {
	//		DrawIcon(hdc, 2, 2, DIS.iconCurrent);
	//	}
	//}
	//(void) ReleaseDC(hwndMain, hdc);
	//if (DIS.hwndConsole){
	//	PostMessage(DIS.hwndConsole, WM_SETICON, (WPARAM) TRUE, (LPARAM) DIS.iconCurrent);
	//}
}

void
StartClockTimer(dispboard_t* pDis, long millisec){  //开始计时
	pDis->clockTimerEvent 
        = (int)SetTimer(pDis->hwndThis, (UINT) CLOCK_TIMER_ID,(UINT) millisec, NULL);
}


void
TimeControlTagValue(char *buf){
    //char buf[MSG_SIZ];
    //if (!appData.clockMode) {
    //    StringCbCopy(buf,MSG_SIZ,"-");
    //} else if (DIS.movesPerSession > 0) {
    //    StringCbPrintf(buf,MSG_SIZ,"%d/%ld", DIS.movesPerSession, DIS.timeControl/1000);
    //} else if (DIS.timeIncrement == 0) {
    //    StringCbPrintf(buf,MSG_SIZ,"%ld", DIS.timeControl/1000);
    //} else {
    //    StringCbPrintf(buf,MSG_SIZ,"%ld+%ld", DIS.timeControl/1000, DIS.timeIncrement/1000);
    //}
    //return StrSave(buf);
}

/* Timekeeping seems to be a portability nightmare.  I think everyone
has ftime(), but I'm really not sure, so I'm including some ifdefs
to use other calls if you don't.  Clocks will be less accurate if
you have neither ftime nor gettimeofday.
*/

/* Get the current time as a TimeMark */
void
GetTimeMark(TimeMark *tm)

{
//#define HAVE_FTIME

#if HAVE_GETTIMEOFDAY

    struct timeval timeVal;
    struct timezone timeZone;

    gettimeofday(&timeVal, &timeZone);
    tm->sec = (long) timeVal.tv_sec; 
    tm->ms = (int) (timeVal.tv_usec / 1000L);

#else /*!HAVE_GETTIMEOFDAY*/
#if HAVE_FTIME

//#include <sys/timeb.h>

    struct _timeb timeB;

    _ftime_s(&timeB);
    tm->sec = (long) timeB.time;
    tm->ms = (int) timeB.millitm;

#else /*!HAVE_FTIME && !HAVE_GETTIMEOFDAY*/
    tm->sec = (long) time(NULL);
    tm->ms = 0;
#endif
#endif
}

/* Pause for `ms' milliseconds */
/* !! Ugh, this is a kludge. Fix it sometime. --tpm */
void
TimeDelay(long ms){
    TimeMark m1, m2;

    GetTimeMark(&m1);
    do {
        GetTimeMark(&m2);
    } while (SubtractTimeMarks(&m2, &m1) < ms);
}

void
CheckTimeControl(dispboard_t* pDis){
    //if (!appData.clockMode || appData.icsActive ||
    //    /*DIS.gameMode == PlayFromGameFile || DIS.forwardMostMove == 0) return;*/
    //    DIS.gameMode == PlayFromGameFile || DIS.pos.gply == 0) return;

    //if (DIS.timeIncrement >= 0) {
    //    //if (WhiteOnMove(DIS.forwardMostMove)) {
    //    if(DIS.forwardMostMove%2==0){
    //        DIS.blackTimeRemaining += DIS.timeIncrement;
    //    }
    //    else {
    //        DIS.whiteTimeRemaining += DIS.timeIncrement;
    //    }
    //}
    ///*
    //* add time to clocks when time control is achieved
    //*/
    //if (DIS.movesPerSession) {
    //    switch ((DIS.forwardMostMove + 1) % (DIS.movesPerSession * 2)) {
    //      case 0:
    //          /* White made time control */
    //          DIS.whiteTimeRemaining += DIS.timeControl;
    //          break;
    //      case 1:
    //          /* Black made time control */
    //          DIS.blackTimeRemaining += DIS.timeControl;
    //          break;
    //      default:
    //          break;
    //    }
    //}
}
int
CheckFlags(dispboard_t* pDis)
{

    //if (DIS.whiteTimeRemaining <= 0) {
    //    if (!DIS.whiteFlag) {
    //        DIS.whiteFlag = TRUE;
    //        if (appData.icsActive) {
    //            if (appData.autoCallFlag &&
    //                DIS.gameMode == IcsPlayingBlack && !DIS.blackFlag) {
    //                    SendToICS(DIS.ics_prefix);
    //                    SendToICS("flag\n");
    //            }
    //        } else {
    //            if (DIS.blackFlag) {
    //                DisplayTitle("Both flags fell");
    //            } else {
    //                DisplayTitle("White's flag fell");
    //                if (appData.autoCallFlag) {
    //                    GameEnds(BlackWins, "Black wins on time", GE_XBOARD);
    //                    return TRUE;
    //                }
    //            }
    //        }
    //    }
    //}
    //if (DIS.blackTimeRemaining <= 0) {
    //    if (!DIS.blackFlag) {
    //        DIS.blackFlag = TRUE;
    //        if (appData.icsActive) {
    //            if (appData.autoCallFlag &&
    //                DIS.gameMode == IcsPlayingWhite && !DIS.whiteFlag) {
    //                    SendToICS(DIS.ics_prefix);
    //                    SendToICS("flag\n");
    //            }
    //        } else {
    //            if (DIS.whiteFlag) {
    //                DisplayTitle("Both flags fell");
    //            } else {
    //                DisplayTitle("Black's flag fell");
    //                if (appData.autoCallFlag) {
    //                    GameEnds(WhiteWins, "White wins on time", GE_XBOARD);
    //                    return TRUE;
    //                }
    //            }
    //        }
    //    }
    //}
    return FALSE;
}

void    //显示双方的时间
DisplayBothClocks(dispboard_t* pDis){
 /*   int wom = (DIS.gameMode == EditPosition) ? !DIS.blackPlaysFirst : WhiteOnMove(DIS.currentMove);*/
    
    //int wom = (DIS.gameMode == EditPosition) ? !0 : DIS.currentMove%2==0;

    //DisplayWhiteClock(DIS.whiteTimeRemaining,  wom);
    //DisplayBlackClock(DIS.blackTimeRemaining, !wom);

    //TimeString

    //if(DIS.first.UCCI_which == 1){      //引擎走红
    //    SendMessage(DLG.TimeRedTotal,WM_SETTEXT,0,(LPARAM)TimeString(DIS.first.msTotal));
    //    SendMessage(DLG.TimeRedStep, WM_SETTEXT,0,(LPARAM)TimeString(DIS.first.msStep));

    //    SendMessage(DLG.TimeBlueTotal,WM_SETTEXT,0,(LPARAM)TimeString(DIS.second.msTotal));
    //    SendMessage(DLG.TimeBlueStep, WM_SETTEXT,0,(LPARAM)TimeString(DIS.second.msStep));
    //}
    //else{
    //    SendMessage(DLG.TimeRedTotal,WM_SETTEXT,0,(LPARAM)TimeString(DIS.second.msTotal));
    //    SendMessage(DLG.TimeRedStep, WM_SETTEXT,0,(LPARAM)TimeString(DIS.second.msStep));

    //    SendMessage(DLG.TimeBlueTotal,WM_SETTEXT,0,(LPARAM)TimeString(DIS.first.msTotal));
    //    SendMessage(DLG.TimeBlueStep, WM_SETTEXT,0,(LPARAM)TimeString(DIS.first.msStep));
    //}
    //char buf[64];
    //TimeString(pDis->TimeDisp[WHITE].msTotal,buf);
    //SendMessage(pDis->TimeRedTotal,  WM_SETTEXT,0,(LPARAM)buf);
    //TimeString(pDis->TimeDisp[WHITE].msStep,buf);
    //SendMessage(pDis->TimeRedStep,   WM_SETTEXT,0,(LPARAM)buf);

    //TimeString(pDis->TimeDisp[BLACK].msTotal,buf);
    //SendMessage(pDis->TimeBlueTotal, WM_SETTEXT,0,(LPARAM)buf);
    //TimeString(pDis->TimeDisp[BLACK].msStep,buf);
    //SendMessage(pDis->TimeBlueStep,  WM_SETTEXT,0,(LPARAM)buf);

    //SendMessage(pDis->TimeBlueTotal, WM_SETTEXT,0,(LPARAM)TimeString(pDis->TimeDisp[BLACK].msTotal));
    //SendMessage(pDis->TimeBlueStep,  WM_SETTEXT,0,(LPARAM)TimeString(pDis->TimeDisp[BLACK].msStep));
}

/* Return the difference in milliseconds between two
time marks.  We assume the difference will fit in a long!
*/
long
SubtractTimeMarks(TimeMark *tm2,TimeMark *tm1)
{
    return 1000L*(tm2->sec - tm1->sec) +
        (long) (tm2->ms - tm1->ms);
}

/*
* Code to manage the game clocks.
*
* In tournament play, black starts the clock and then white makes a move.
* We give the human user a slight advantage if he is playing white---the
* clocks don't run until he makes his first move, so it takes zero time.
* Also, we don't account for network lag, so we could get out of sync
* with GNU Chess's clock -- but then, referees are always right.  
*/

//static TimeMark tickStartTM;
//static long intendedTickLength;

long        //得到下一步定时时间
NextTickLength(long timeRemaining)
{
    long nominalTickLength, nextTickLength;

    if (timeRemaining > 0L && timeRemaining <= 10000L)      //小于1000MS了
        nominalTickLength = 100L;
    else
        nominalTickLength = 1000L;
    nextTickLength = timeRemaining % nominalTickLength;
    if (nextTickLength <= 0) {
        nextTickLength += nominalTickLength;
    }

    return nextTickLength;
}


void ResetCpsTime(ChessProgramState *cps){
    //TimeString
    if(cps->isBaoGan){
        cps->msFirst = cps->BaoGanTime * 60 * 1000;
        cps->msStep  = cps->timePerStep * 1000;
    }
    else{
       cps->msFirst = cps->firstClassTime * 60 * 1000;
       if(cps->firstClassTimeStep != 0){
           cps->msStep  = cps->msFirst / cps->firstClassTimeStep;
       }

       if(cps->timePerStep * 1000 < cps->msStep){
           cps->msStep = cps->timePerStep * 1000;
       }
    }
}

void  /* Stop clocks and reset to a fresh time control */ 
ResetClocks(dispboard_t* pDis) {
    StopClockTimer(pDis);
    //if (appData.icsActive) {
    //    DIS.whiteTimeRemaining = DIS.blackTimeRemaining = 0;
    //} 
    //else {
    //    DIS.whiteTimeRemaining = DIS.blackTimeRemaining = DIS.timeControl;
    //}
    //if (DIS.whiteFlag || DIS.blackFlag) {
    //    DisplayTitle("");
    //    DIS.whiteFlag = DIS.blackFlag = FALSE;
    //}

    //得到当前的时间设定
    //if(DIS.first.isBaoGan){
    //}
    ResetCpsTime(&pDis->first);
    ResetCpsTime(&pDis->second);

    DisplayBothClocks(pDis);
}


#define FUDGE 25 /* 25ms = 1/40 sec; should be plenty even for 50 Hz clocks */

/* Decrement running clock by amount of time that has passed */
void
DecrementClocks(dispboard_t* pDis){
    long timeRemaining;
    long lastTickLength, fudge;
    TimeMark now;

    if (!appData.clockMode){
        return;
    }
    if (pDis->gameMode==AnalyzeMode || pDis->gameMode == AnalyzeFile){
        return;
    }

    GetTimeMark(&now);

    lastTickLength = SubtractTimeMarks(&now, &pDis->tickStartTM);

    /* Fudge if we woke up a little too soon */
    fudge = pDis->intendedTickLength - lastTickLength;
    if (fudge < 0 || fudge > FUDGE){
        fudge = 0;
    }

    //if (WhiteOnMove(DIS.forwardMostMove)) {
    if(pDis->pos->side == WHITE){
        //timeRemaining = DIS.whiteTimeRemaining -= lastTickLength;
        //DisplayWhiteClock(DIS.whiteTimeRemaining - fudge,
        //    WhiteOnMove(DIS.currentMove));

        timeRemaining = pDis->whiteTimeRemaining -= lastTickLength;
        DisplayWhiteClock(pDis->whiteTimeRemaining - fudge,
            pDis->pos->side == WHITE);
    } 
    else {
        //timeRemaining = DIS.blackTimeRemaining -= lastTickLength;
        //DisplayBlackClock(DIS.blackTimeRemaining - fudge,
        //    !WhiteOnMove(DIS.currentMove));

        timeRemaining = pDis->blackTimeRemaining -= lastTickLength;
        DisplayBlackClock(pDis->blackTimeRemaining - fudge,
            !(pDis->pos->side == WHITE));
    }

    if (CheckFlags(pDis)) return;

    pDis->tickStartTM = now;
    pDis->intendedTickLength = NextTickLength(timeRemaining - fudge) + fudge;
    StartClockTimer(pDis,pDis->intendedTickLength);

    /* if the time remaining has fallen below the alarm threshold, sound the
    * alarm. if the alarm has sounded and (due to a takeback or time control
    * with increment) the time remaining has increased to a level above the
    * threshold, reset the alarm so it can sound again. 
    */

    if (appData.icsActive && appData.icsAlarm) {

        /* make sure we are dealing with the user's clock */
        //if (!( ((DIS.gameMode == IcsPlayingWhite) && WhiteOnMove(DIS.currentMove)) ||
        //    ((DIS.gameMode == IcsPlayingBlack) && !WhiteOnMove(DIS.currentMove))
        //    )){
        if(!(((pDis->gameMode == IcsPlayingWhite) && (pDis->pos->side == WHITE)) ||
            ((pDis->gameMode == IcsPlayingBlack) && !(pDis->pos->side == WHITE))
            )){
                return;
        }

        if (appData.alarmSounded && (timeRemaining > appData.icsAlarmTime)) {
            appData.alarmSounded = FALSE;
        } 
        else if (!appData.alarmSounded && (timeRemaining <= appData.icsAlarmTime)) { 
            PlayAlarmSound();
            appData.alarmSounded = TRUE;
        }
    }
}

//char *
//TimeString(long ms) {  //将时间转换成字符串
void 
TimeString (long ms, char* buf){
    int second, minute;
    //int hour;
    int day;
    int rms;
    char *sign = "";
    //static char buf[32];

    //if (ms > 0 && ms <= 9900) {
    //    /* convert milliseconds to tenths, rounding up */
    //    double tenths = floor( ((double)(ms + 99L)) / 100.00 );
    //    //sprintf(buf, " %03.1f ", tenths/10.0);
    //    StringCbPrintf(buf,32," %03.1f ", tenths/10.0);
    //    return buf;
    //}

    ///* convert milliseconds to seconds, rounding up */
    ///* use floating point to avoid strangeness of integer division
    //with negative dividends on many machines */
    //second = (long) floor(((double) (ms + 999L)) / 1000.0);

    //if (second < 0) {
    //    sign = "-";
    //    second = -second;
    //}

    //day = second / (60 * 60 * 24);
    //second = second % (60 * 60 * 24);
    //hour = second / (60 * 60);
    //second = second % (60 * 60);
    //minute = second / 60;
    //second = second % 60;

    //if (day > 0){
    //    //sprintf(buf, " %s%ld:%02ld:%02ld:%02ld ",
    //    // sign, day, hour, minute, second);
    //    StringCbPrintf(buf,32," %s%ld:%02ld:%02ld:%02ld ",
    //        sign, day, hour, minute, second);
    //}
    //else if (hour > 0){
    //    //sprintf(buf, " %s%ld:%02ld:%02ld ", sign, hour, minute, second);
    //    StringCbPrintf(buf,32," %s%ld:%02ld:%02ld ", sign, hour, minute, second);
    //}
    //else{
    //    //sprintf(buf, " %s%2ld:%02ld ", sign, minute, second);
    //    StringCbPrintf(buf,32," %s%02ld:%02ld ", sign, minute, second);
    //}

    if(ms < 0){
        sign = "-";
    }
    day    = ms /  (60 * 60 * 24 * 1000);
    rms    = ms %  (60 * 60 * 24 * 1000);
    //hour   = rms / (60 * 60 * 1000);
    //rms    = rms % (60 * 60 * 1000);

    minute = rms / (60 * 1000);
    rms    = rms % (60 * 1000);
    
    second = rms / 1000;
    rms    = rms % 1000;

    StringCbPrintf(buf,32,"%1s%.03d:%.02d:%.03d",sign,minute,second,rms);
   

    //return buf;
}

void
SwitchClocks(dispboard_t* pDis){
    /* A player has just moved, so stop the previously running
    clock and (if in clock mode) start the other one.
    We redisplay both clocks in case we're in ICS mode, because
    ICS gives us an update to both clocks after every move.
    Note that this routine is called *after* forwardMostMove
    is updated, so the last fractional tick must be subtracted
    from the color that is *not* on move now.
    */

    long lastTickLength;
    TimeMark now;
    int flagged = FALSE;

    GetTimeMark(&now);

    if (StopClockTimer(pDis) && appData.clockMode) {
        lastTickLength = SubtractTimeMarks(&now, &pDis->tickStartTM);
        //if (WhiteOnMove(DIS.forwardMostMove)) {
        if(pDis->pos->side == WHITE){
            pDis->blackTimeRemaining -= lastTickLength;
        } 
        else {
            pDis->whiteTimeRemaining -= lastTickLength;
        }
        flagged = CheckFlags(pDis);
    }
    CheckTimeControl(pDis);

    if (flagged || !appData.clockMode){
        return;
    }

    switch (pDis->gameMode) {
      case MachinePlaysBlack:
      case MachinePlaysWhite:
      case BeginningOfGame:
          if (pDis->pausing){
              return;
          }
          break;

      case EditGame:
      case PlayFromGameFile:
      case IcsExamining:
          return;

      default:
          break;
    }

    pDis->tickStartTM = now;
    //intendedTickLength = NextTickLength(WhiteOnMove(DIS.forwardMostMove) ?
    //    DIS.whiteTimeRemaining : DIS.blackTimeRemaining);
    pDis->intendedTickLength = NextTickLength(pDis->pos->side == WHITE ?
        pDis->whiteTimeRemaining : pDis->blackTimeRemaining);
    StartClockTimer(pDis,pDis->intendedTickLength);
}

void  /* Stop both clocks */
StopClocks(dispboard_t* pDis){	
    long lastTickLength;
    TimeMark now;

    if (!StopClockTimer(pDis)){
        return;
    }
    if (!appData.clockMode){
        return;
    }

    GetTimeMark(&now);

    lastTickLength = SubtractTimeMarks(&now, &pDis->tickStartTM);
    //if (WhiteOnMove(DIS.forwardMostMove)) {
    if(pDis->pos->side == WHITE){
        pDis->whiteTimeRemaining -= lastTickLength;
        /*DisplayWhiteClock(DIS.whiteTimeRemaining, WhiteOnMove(DIS.currentMove));*/
        DisplayWhiteClock(pDis->whiteTimeRemaining, pDis->pos->side == WHITE);
    } 
    else {
        pDis->blackTimeRemaining -= lastTickLength;
        /*DisplayBlackClock(DIS.blackTimeRemaining, !WhiteOnMove(DIS.currentMove));*/
        DisplayBlackClock(pDis->blackTimeRemaining, !pDis->pos->side == WHITE);
    }
    CheckFlags(pDis);
}

/* Start clock of player on move.  Time may have been reset, so
if clock is already running, stop and restart it. */
void
StartClocks(dispboard_t* pDis){
    (void) StopClockTimer(pDis); /* in case it was running already */
    DisplayBothClocks(pDis);
    if (CheckFlags(pDis)){
        return;
    }
    if (!appData.clockMode){
        return;
    }
    if (pDis->gameMode == AnalyzeMode || pDis->gameMode == AnalyzeFile){
        return;
    }

    GetTimeMark(&pDis->tickStartTM);
    //intendedTickLength = NextTickLength(WhiteOnMove(DIS.forwardMostMove) ?
    pDis->intendedTickLength = NextTickLength(pDis->pos->side == WHITE ?
        pDis->whiteTimeRemaining : pDis->blackTimeRemaining);
    StartClockTimer(pDis,pDis->intendedTickLength);
}

int						//解析时间控制
ParseTimeControl(char *tc, int ti, int mps)  {
    //int matched, min, sec, ms;
    //matched = sscanf_s(tc, "%d:%d:%d", &min, &sec, &ms);
    //if (matched == 1) {
    //    DIS.timeControl = min * 60 * 1000;
    //} 
    //else if (matched == 2) {
    //    DIS.timeControl = (min * 60 + sec) * 1000;
    //}
    //else if (matched == 3){
    //    DIS.timeControl = (min * 60 + sec) * 1000 + ms;
    //}
    //else {
    //    return FALSE;
    //}

    //if (ti >= 0) {
    //    DIS.timeIncrement = ti * 1000;  /* convert to ms */
    //    DIS.movesPerSession = 0;
    //} 
    //else {
    //    DIS.timeIncrement = 0;
    //    DIS.movesPerSession = mps;
    //}
    return TRUE;
}


