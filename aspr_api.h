// aspr_api.h : Defines API functions.
//

#ifndef ASPR_API_H
#define ASPR_API_H

// Mode status

typedef struct _MODE_STATUS {
    BYTE ModeId;
    bool IsRegistered,
    	 IsKeyPresent,
    	 IsWrongHardwareID,
    	 IsKeyExpired,
    	 IsModeExpired,
    	 IsBlackListedKey,
    	 IsModeActivated;
}MODE_STATUS, *PMODE_STATUS;

#ifdef __BORLANDC__

 extern "C"  char*   __declspec(dllimport) _stdcall GetRegistrationKeys();
 extern "C" _stdcall __declspec(dllimport) BOOL GetRegistrationInformation( BYTE ModeId, char** Key, char** Name);
 extern "C" _stdcall __declspec(dllimport) BOOL RemoveKey( BYTE ModeId );
 extern "C" _stdcall __declspec(dllimport) BOOL CheckKey( char* Key, char* Name, PMODE_STATUS mode_status );
 extern "C" _stdcall __declspec(dllimport) BOOL CheckKeyAndDecrypt( char* Key, char* Name, BOOL SaveKey );
 extern "C" _stdcall __declspec(dllimport) BOOL GetKeyDate( BYTE ModeId, WORD* Day, WORD* Month, WORD* Year );
 extern "C" _stdcall __declspec(dllimport) BOOL GetKeyExpirationDate( BYTE ModeId, WORD* Day, WORD* Month, WORD* Year );
 extern "C" _stdcall __declspec(dllimport) BOOL GetTrialDays( BYTE ModeId, DWORD* Total, DWORD* Left );
 extern "C" _stdcall __declspec(dllimport) BOOL GetTrialExecs( BYTE ModeId, DWORD* Total, DWORD* Left );
 extern "C" _stdcall __declspec(dllimport) BOOL GetExpirationDate( BYTE ModeId, WORD* Day, WORD* Month, WORD* Year );
 extern "C" _stdcall __declspec(dllimport) BOOL GetModeInformation( BYTE ModeID, char** ModeName, PMODE_STATUS mode_status);
 extern "C"  char*   __declspec(dllimport) _stdcall GetHardwareID();
 extern "C"  char*   __declspec(dllimport) _stdcall GetHardwareIDEx( BYTE ModeID );
 extern "C" _stdcall __declspec(dllimport) BOOL SetUserKey( char* Key, DWORD KeySize );

#else

 extern "C" char* __stdcall GetRegistrationKeys();
 extern "C" BOOL  __stdcall GetRegistrationInformation( BYTE ModeId, char** Key, char** Name);
 extern "C" BOOL  __stdcall RemoveKey( BYTE ModeId );
 extern "C" BOOL  __stdcall CheckKey( char* Key, char* Name, PMODE_STATUS mode_status );
 extern "C" BOOL  __stdcall CheckKeyAndDecrypt( char* Key, char* Name, BOOL SaveKey );
 extern "C" BOOL  __stdcall GetKeyDate( BYTE ModeId, WORD* Day, WORD* Month, WORD* Year );
 extern "C" BOOL  __stdcall GetKeyExpirationDate( BYTE ModeId, WORD* Day, WORD* Month, WORD* Year );
 extern "C" BOOL  __stdcall GetTrialDays( BYTE ModeId, DWORD* Total, DWORD* Left );
 extern "C" BOOL  __stdcall GetTrialExecs( BYTE ModeId, DWORD* Total, DWORD* Left );
 extern "C" BOOL  __stdcall GetExpirationDate( BYTE ModeId, WORD* Day, WORD* Month, WORD* Year );
 extern "C" BOOL  __stdcall GetModeInformation( BYTE ModeID, char** ModeName, PMODE_STATUS mode_status);
 extern "C" char* __stdcall GetHardwareID();
 extern "C" char* __stdcall GetHardwareIDEx( BYTE ModeID );
 extern "C" BOOL  __stdcall SetUserKey( char* Key, DWORD KeySize );

#endif

#endif
