#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

void
SaveInHistory(TCHAR *cmd){
  //if (DIS.history[DIS.histIn] != NULL) {
  //  free(DIS.history[DIS.histIn]);
  //  DIS.history[DIS.histIn] = NULL;
  //}
  if (*cmd == NULLCHAR) return;

  //DIS.history[DIS.histIn] = StrSave(cmd);
  StringCbPrintf(appData.Ahistory[appData.AhistIn],1024,cmd);

  appData.AhistIn = (appData.AhistIn + 1) % HISTORY_SIZE;
  //if (DIS.history[DIS.histIn] != NULL) {
  //  free(DIS.history[DIS.histIn]);
  //  DIS.history[DIS.histIn] = NULL;
  //}
  appData.AhistP = appData.AhistIn;
}

TCHAR *
PrevInHistory(TCHAR *cmd){
	int newhp;
	if (appData.AhistP == appData.AhistIn) {
		//if (DIS.history[DIS.histIn] != NULL){
		//	free(DIS.history[DIS.histIn]);
		//}
		//DIS.history[DIS.histIn] = StrSave(cmd);
		StringCbPrintf(appData.Ahistory[appData.AhistIn],1024,cmd);
	}
	newhp = (appData.AhistP - 1 + HISTORY_SIZE) % HISTORY_SIZE;
	if (newhp == appData.AhistIn || appData.Ahistory[newhp] == NULL){
		return NULL;
	}
	appData.AhistP = newhp;
	return appData.Ahistory[appData.AhistP];
}

TCHAR *
NextInHistory(){
	if (appData.AhistP == appData.AhistIn){
		return NULL;
	}
	appData.AhistP = (appData.AhistP + 1) % HISTORY_SIZE;
	return appData.Ahistory[appData.AhistP];
}




char
StringGet(void *getClosure)
{
  char **p = (char **) getClosure;
  return *((*p)++);
}

//void 
//Board90toFRinfo(Board90 board, FRinfo_t *FR){
//	memset(FR,0,sizeof(FRinfo_t));
//	for(int i=0;i<90;i++){
//		if(board[i] != NOCHESS){
//			sq_t x = S90toF(i);  
//			sq_t y = S90toR(i);
//			FR->BitFiles[x] |= FileRankMask[y];
//			FR->BitRanks[y] |= FileRankMask[x];
//		}
//	}
//}
int       //将字符串转成等级分
string_to_rating(char *str){
    /* Convert str to a rating. Checks for special cases of "----",
    "++++", etc. Also strips ()'s */
    while(*str && !isdigit(*str)){
        ++str;
    }
    if (!*str)
        return 0;	/* One of the special "no rating" cases */
    else
        return atoi(str);
}

//***********************************************************************

//char *
//StrSavePtr(char *s,char **savePtr){
//    if (*savePtr) {
//        free(*savePtr);
//    }
//    if ((*savePtr = (char *) malloc(strlen(s) + 1))) {
//        //strcpy(*savePtr, s);
//        StringCbCopy(*savePtr,strlen(s),s);
//    }
//    return(*savePtr);
//}
//
/*
* This is necessary because some C libraries aren't ANSI C compliant yet.
*/
char *
StrStr(char *string,char *match){
    int i, length;

    length = (int)strlen(match);

    for (i = (int)strlen(string) - length; i >= 0; i--, string++){
        if (!strncmp(match, string, length)){
            return string;
        }
    }

    return NULL;
}

char *
StrCaseStr(char *string,char *match){
    int i, j, length;

    length = (int)strlen(match);

    for (i = (int)strlen(string) - length; i >= 0; i--, string++) {
        for (j = 0; j < length; j++) {
            if (ToLower(match[j]) != ToLower(string[j]))
                break;
        }
        if (j == length){
            return string;
        }
    }

    return NULL;
}


int
StrCaseCmp(char *s1,char *s2){
    char c1, c2;

    for (;;) {
        c1 = ToLower(*s1++);
        c2 = ToLower(*s2++);
        if (c1 > c2) return 1;
        if (c1 < c2) return -1;
        if (c1 == NULLCHAR) {
            return 0;
        }
    }
}


int
ToLower(int c){
    return isupper(c) ? tolower(c) : c;
}


int
ToUpper(int c){
    return islower(c) ? toupper(c) : c;
}

//**********************************************************


/*
 * This array is designed for mapping upper and lower case letter
 * together for a case independent comparison.  The mappings are
 * based upon ASCII character sequences.
 */


static unsigned char cm[] =
{
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
    0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
    0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
    0x40, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
    0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
    0x78, 0x79, 0x7a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
    0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
    0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
    0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f,
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
    0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f,
    0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
    0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f,
    0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7,
    0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf,
    0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7,
    0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf,
    0xc0, 0xe1, 0xe2, 0xe3, 0xe4, 0xc5, 0xe6, 0xe7,
    0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef,
    0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7,
    0xf8, 0xf9, 0xfa, 0xdb, 0xdc, 0xdd, 0xde, 0xdf,
    0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7,
    0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef,
    0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7,
    0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff,
};

/*
 *----------------------------------------------------------------------
 *
 * strcasecmp --
 *
 *      Compares two strings, ignoring case differences.
 *
 * Results:
 *      Compares two null-terminated strings s1 and s2, returning -1, 0,
 *      or 1 if s1 is lexicographically less than, equal to, or greater
 *      than s2.
 *
 * Side effects:
 *      None.
 *
 *----------------------------------------------------------------------
 */

int             strcasecmp(const char *s1, const char *s2)
{
    unsigned char   u1,
                    u2;

    for (;; s1++, s2++) {
        u1 = (unsigned char) *s1;
        u2 = (unsigned char) *s2;
        if ((u1 == '\0') || (cm[u1] != cm[u2])) {
            break;
        }
    }
    return cm[u1] - cm[u2];
}

/*
 *----------------------------------------------------------------------
 *
 * strncasecmp --
 *
 *      Compares two strings, ignoring case differences.
 *
 * Results:
 *      Compares up to length chars of s1 and s2, returning -1, 0, or 1
 *      if s1 is lexicographically less than, equal to, or greater
 *      than s2 over those characters.
 *
 * Side effects:
 *      None.
 *
 *----------------------------------------------------------------------
 */



int             strncasecmp(const char *s1, const char *s2, size_t length)
{
    unsigned char   u1,
                    u2;

    for (; length != 0; length--, s1++, s2++) {
        u1 = (unsigned char) *s1;
        u2 = (unsigned char) *s2;
        if (cm[u1] != cm[u2]) {
            return cm[u1] - cm[u2];
        }
        if (u1 == '\0') {
            return 0;
        }
    }
    return 0;
}
