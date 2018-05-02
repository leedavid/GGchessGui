#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

void
Colorize(ColorClass cc, int continuation)
{
  //DLG.currentColorClass      = cc;
  ICS.curColor               = cc;
  appData.AconsoleCF.dwMask       = CFM_COLOR|CFM_BOLD|CFM_ITALIC|CFM_UNDERLINE|CFM_STRIKEOUT;
  appData.AconsoleCF.crTextColor  = appData.AtextAttribs[cc].color;
  appData.AconsoleCF.dwEffects    = appData.AtextAttribs[cc].effects;
  //if (!continuation){
  //    MyPlaySound(&appData.AtextAttribs[cc].sound);   //第个字体都有声音
  //}
}



void
SetDefaultTextAttribs()
{
  int cc;     //ColorClass cc;
  for (cc = (ColorClass)0; cc < NColorClasses; cc++) {
    ParseAttribs(&appData.AtextAttribs[cc].color, 
		 &appData.AtextAttribs[cc].effects, 
	         defaultTextAttribs[cc]);
  }
}




BOOL  //returns TRUE if user selects a different color, FALSE otherwise 
ChangeColor(HWND hwnd, COLORREF *which)
{
  static BOOL firstTime = TRUE;
  static DWORD customColors[16];
  CHOOSECOLOR cc;
  COLORREF newcolor;
  int i;
  int ccl; //ColorClass ccl;

  if (firstTime) {
    /* Make initial colors in use available as custom colors */
    /* Should we put the compiled-in defaults here instead? */
    i = 0;
    customColors[i++] = appData.AlightSquareColor & 0xffffff;
    customColors[i++] = appData.AdarkSquareColor & 0xffffff;
    customColors[i++] = appData.AwhitePieceColor & 0xffffff;
    customColors[i++] = appData.AblackPieceColor & 0xffffff;
    customColors[i++] = appData.AhighlightSquareColor & 0xffffff;
    customColors[i++] = appData.ApremoveHighlightColor & 0xffffff;

    for (ccl = (ColorClass) 0; ccl < NColorClasses && i < 16; ccl++) {
      customColors[i++] = appData.AtextAttribs[ccl].color;
    }
    while (i < 16) customColors[i++] = RGB(255, 255, 255);
    firstTime = FALSE;
  }

  cc.lStructSize = sizeof(cc);
  cc.hwndOwner = hwnd;
  cc.hInstance = NULL;
  cc.rgbResult = (DWORD) (*which & 0xffffff);
  cc.lpCustColors = (LPDWORD) customColors;
  cc.Flags = CC_RGBINIT|CC_FULLOPEN;

  if (!ChooseColor(&cc)) return FALSE;

  newcolor = (COLORREF) (0x2000000 | cc.rgbResult);
  if (newcolor == *which) return FALSE;
  *which = newcolor;
  return TRUE;

  /*
  InitDrawingColors();
  InvalidateRect(hwnd, &boardRect, FALSE);
  */
}

VOID
ParseFontName(TCHAR *name, MyFontParams *mfp)
{
  TCHAR *p, *q;
  if (name == NULL) return;
  p = name;
  q = wcschr(p, ':');
  if (q) {
	  if (q - p >= sizeof(mfp->faceName)){
		  ExitArgError(_T("Font name too long:"), name);
	  }
    memcpy(mfp->faceName, p, sizeof(TCHAR)*(q - p));
    mfp->faceName[q - p] = NULLCHAR;
    p = q + 1;
  } else {
    q = mfp->faceName;
    while (*p && !isdigit(*p)) {
      *q++ = *p++;
      if (q - mfp->faceName >= sizeof(mfp->faceName))
	ExitArgError(_T("Font name too long:"), name);
    }
    while (q > mfp->faceName && q[-1] == ' ') q--;
    *q = NULLCHAR;
  }
  if (!*p) ExitArgError(_T("Font point size missing:"), name);
  mfp->pointSize = (float) _wtof(p);
  mfp->bold = (wcschr(p, 'b') != NULL);
  mfp->italic = (wcschr(p, 'i') != NULL);
  mfp->underline = (wcschr(p, 'u') != NULL);
  mfp->strikeout = (wcschr(p, 's') != NULL);
}

COLORREF
ParseColorName(TCHAR *name)
{
  int red, green, blue, count;
  TCHAR buf[MSG_SIZ];

  count = swscanf_s(name, _T("#%2x%2x%2x"), &red, &green, &blue);
  if (count != 3) {
    count = swscanf_s(name, _T("%3d%*[^0-9]%3d%*[^0-9]%3d"), 
      &red, &green, &blue);
  }
  if (count != 3) {
    //sprintf(buf, "Can't parse color name %s", name);
    StringCbPrintf(buf,MSG_SIZ,_T("Can't parse color name %s"), name);
	LogOut(buf);
    return RGB(0, 0, 0);
  }
  return PALETTERGB(red, green, blue);
}
VOID
LFfromMFP(LOGFONT* lf, MyFontParams *mfp)
{
  HDC hdc = CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
  lf->lfHeight = -(int)(mfp->pointSize * GetDeviceCaps(hdc, LOGPIXELSY) / 72.0 + 0.5);
  DeleteDC(hdc);
  lf->lfWidth = 0;
  lf->lfEscapement = 0;
  lf->lfOrientation = 0;
  lf->lfWeight = mfp->bold ? FW_BOLD : FW_NORMAL;
  lf->lfItalic = mfp->italic;
  lf->lfUnderline = mfp->underline;
  lf->lfStrikeOut = mfp->strikeout;
  lf->lfCharSet = DEFAULT_CHARSET;
  lf->lfOutPrecision = OUT_DEFAULT_PRECIS;
  lf->lfClipPrecision = CLIP_DEFAULT_PRECIS;
  lf->lfQuality = DEFAULT_QUALITY;
  lf->lfPitchAndFamily = DEFAULT_PITCH|FF_DONTCARE;
  //strcpy(lf->lfFaceName, mfp->faceName);
  StringCbCopy(lf->lfFaceName,32,mfp->faceName);
}

VOID
CreateFontInMF(MyFont *mf)
{
  LFfromMFP(&mf->lf, &mf->mfp);
  if (mf->hf) DeleteObject(mf->hf);
  mf->hf = CreateFontIndirect(&mf->lf);
}

