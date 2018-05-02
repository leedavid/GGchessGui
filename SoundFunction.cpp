#include "stdafx.h"
#include "GGchess.h"
#include <sys/stat.h>
#include <commdlg.h>
#include <dlgs.h>
#include <commctrl.h>

#include "chess.h"
#include "data.h"
#include "pregen.h"

void
RingBell(){
  MyPlaySound(&appData.Asounds[(int)SoundMove]);
}
void 
PlayIcsWinSound(){
  MyPlaySound(&appData.Asounds[(int)SoundIcsWin]);
}

void 
PlayCheckSound(){	//将军的声音
	MyPlaySound(&appData.Asounds[(int)SoundCheck]);
}
void
PlayEatSound(){	//将军的声音
	MyPlaySound(&appData.Asounds[(int)SoundEat]);
}
void
PlayIcsLossSound(){
  MyPlaySound(&appData.Asounds[(int)SoundIcsLoss]);
}

void
PlayIcsDrawSound(){
  MyPlaySound(&appData.Asounds[(int)SoundIcsDraw]);
}

void
PlayIcsUnfinishedSound(){
  MyPlaySound(&appData.Asounds[(int)SoundIcsUnfinished]);
}
void
PlayAlarmSound(){
  MyPlaySound(&appData.Asounds[(int)SoundAlarm]);
}

BOOLEAN
MyLoadSound(MySound *ms){
  char buf[MSG_SIZ];
  BOOL ok = FALSE;
  struct stat st;
  FILE *f;

  if (ms->data){
	  free(ms->data);
  }
  ms->data = NULL;

  switch (ms->name[0]) {
		case NULLCHAR:
			/* Silence */
			ok = TRUE;
			break;
		case '$':
			/* System sound from Control Panel.  Don't preload here. */
			ok = TRUE;
			break;
		case '!':
			if (ms->name[1] == NULLCHAR) {
				/* "!" alone = silence */
				ok = TRUE;
			} 
			else {
				/* Builtin wave resource.  Error if not found. */
				HANDLE h = FindResource(hInst, ms->name + 1, "WAVE");
				if (h == NULL){
					break;
				}
				ms->data = (void *)LoadResource(hInst, (HRSRC)h);
				if (h == NULL){
					break;
				}
				ok = TRUE;
			}
			break;
		default:
			/* .wav file.  Error if not found. */
			//StringCbPrintf(buf,MSG_SIZ,"%schessboard\\%d\\qp.bmp",
			//installDir,appData.pieceStyle);
			StringCbPrintf(buf,MSG_SIZ,"%s\\snd\\%s",installDir,ms->name);
			//f = fopen(ms->name, "rb");
			//f = fopen(buf, "rb");
			fopen_s(&f,buf,"rb");
			if (f == NULL){
				break;
			}
			if (fstat(_fileno(f), &st) < 0){
				break;
			}
			ms->data = malloc(st.st_size);
			if (fread(ms->data, st.st_size, 1, f) < 1){
				break;
			}
			fclose(f);
			ok = TRUE;
			break;
  }
  if (!ok) {
    char buf[MSG_SIZ];
    //sprintf(buf, "Error loading sound %s", ms->name);
	StringCbPrintf(buf,MSG_SIZ,"Error loading sound %s", ms->name);
    DisplayError(buf, GetLastError());
  }
  return ok;
}



void			//设置缺省的声音 
SetDefaultSounds(){
  int cc;   //ColorClass cc;
  int sc;   //SoundClass sc;
  for (cc = (ColorClass)0; cc < NColorClasses; cc++) {
    appData.AtextAttribs[cc].sound.name = _strdup("");
    appData.AtextAttribs[cc].sound.data = NULL;
  }
  for (sc = (SoundClass)0; sc < NSoundClasses; sc++) {
    appData.Asounds[sc].name = _strdup("");
    appData.Asounds[sc].data = NULL;
  }
  appData.Asounds[(int)SoundBell].name = _strdup(SOUND_BELL);
}


BOOLEAN
MyPlaySound(MySound *ms){
	BOOLEAN ok = FALSE;
	switch (ms->name[0]) {
		case NULLCHAR:
			/* Silence */
			ok = TRUE;
			break;
		case '$':
			/* System sound from Control Panel (deprecated feature).
			"$" alone or an unset sound name gets default beep (still in use). */
			if (ms->name[1]) {
				ok = PlaySound(ms->name + 1, NULL, SND_ALIAS|SND_ASYNC);
			}
			if (!ok) ok = MessageBeep(MB_OK);
			break; 
		case '!':
			/* Builtin wave resource, or "!" alone for silence */
			if (ms->name[1]) {
				if (ms->data == NULL) return FALSE;
				ok = PlaySound((LPCSTR)ms->data, NULL, SND_MEMORY|SND_ASYNC);
			} else {
				ok = TRUE;
			}
			break;
		default:
			/* .wav file.  Error if not found. */
			if (ms->data == NULL) return FALSE;
			ok = PlaySound((LPCSTR)ms->data, NULL, SND_MEMORY|SND_ASYNC);
			break;
			}
			/* Don't print an error: this can happen innocently if the sound driver
			is busy; for instance, if another instance of WinBoard is playing
			a sound at about the same time. */
		#if 0
			if (!ok) {
				char buf[MSG_SIZ];
				//sprintf(buf, "Error playing sound %s", ms->name);
				StringCbPrintf(buf,MSG_SIZ,"Error playing sound %s", ms->name);
				DisplayError(buf, GetLastError());
			}
		#endif
	return ok;
}

void
LoadAllSounds(void)
{  
  int cc;    //ColorClass cc;
  int sc;    //SoundClass sc;
  for (cc = (ColorClass)0; cc < NColorClasses; cc++) {
    MyLoadSound(&appData.AtextAttribs[cc].sound);
  }
  for (sc = (SoundClass)0; sc < NSoundClasses; sc++) {
    MyLoadSound(&appData.Asounds[sc]);
  }
}