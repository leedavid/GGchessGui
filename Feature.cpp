#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"





void 
ParseAttribs(COLORREF *color, int *effects, TCHAR* argValue){
  TCHAR *e = argValue;
  int eff = 0;

  while (*e) {
    if (*e == 'b')      eff |= CFE_BOLD;
    else if (*e == 'i') eff |= CFE_ITALIC;
    else if (*e == 'u') eff |= CFE_UNDERLINE;
    else if (*e == 's') eff |= CFE_STRIKEOUT;
    else if (*e == '#' || isdigit(*e)) break;
    e++;
  }
  *effects = eff;
  *color   = ParseColorName(e);
}




int
BoolFeature(char **p,char *name,int *loc,ChessProgramState *cps){
    TCHAR buf[MSG_SIZ];
    int len = (int)strlen(name);
    int val;
    if (strncmp((*p), name, len) == 0 && (*p)[len] == '=') {
      (*p) += len + 1;
      sscanf_s(*p, "%d", &val);
      *loc = (val != 0);
      while (**p && **p != ' ') (*p)++;
      swprintf_s(buf,MSG_SIZ, L"accepted %hs\n", name);
      SendToProgram(buf, cps);
      return TRUE;
    }
    return FALSE;
}

int
IntFeature(char **p,char *name,int *loc,ChessProgramState *cps){
    TCHAR buf[MSG_SIZ];
    int len = (int)strlen(name);
    if (strncmp((*p), name, len) == 0 && (*p)[len] == '=') {
      (*p) += len + 1;
      sscanf_s(*p, "%d", loc);
      while (**p && **p != ' ') (*p)++;
      swprintf_s(buf,MSG_SIZ, L"accepted %hs\n", name);
      SendToProgram(buf, cps);
      return TRUE;
    }
    return FALSE;
}



void
FeatureDone(ChessProgramState *cps,int val){
    //DelayedEventCallback cb = GetDelayedEvent();
    //if ((cb == InitBackEnd3 && cps == &DIS.first) ||
    //    (cb == TwoMachinesEventIfReady && cps == &DIS.second)) {
    //        CancelDelayedEvent();
    //        ScheduleDelayedEvent(cb, val ? 1 : 3600000);
    //}
    //cps->UCCI_initDone = val;
}




VOID			//有参数错误时,显示并退出
ExitArgError(TCHAR *msg, TCHAR *badArg){
  TCHAR buf[MSG_SIZ];
  StringCbPrintf(buf,MSG_SIZ,_T("%s %s"), msg, badArg);
  LogOut(buf);
  exit(2);
}
