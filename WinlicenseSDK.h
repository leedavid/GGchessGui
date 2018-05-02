#ifndef __WINLICENSDK__
#define __WINLICENSDK__

// WinLicense constants definition

const int wlNoTrialExt             		= 0;
const int wlAppExtended            		= 1;
const int wlInvalidTrialExt        		= 2;
const int wlNoMoreExt              		= 3;
const int wlTrialOk                		= 0;
const int wlTrialDaysExpired       		= 1;
const int wlTrialExecExpired      		= 2;
const int wlTrialDateExpired       		= 3;
const int wlTrialRuntimExpired     		= 4;
const int wlTrialGlobalExpired     		= 5;
const int wlTrialInvalidCountry    		= 6;
const int wlTrialManipulated    		= 7;
const int wlMarkStolenKey          		= 0;
const int wlMarkInvalidKey        		= 1;
const int wlLicenseDaysExpired    		= 1;
const int wlLicenseExecExpired     		= 2;
const int wlLicenseDateExpired     		= 3;
const int wlLicenseGlobalExpired   		= 4;
const int wlLicenseRuntimeExpired  		= 5;
const int wlLicenseActivationExpired  	= 6;
const int wlIsTrial                		= 0;
const int wlIsRegistered           		= 1;
const int wlInvalidLicense         		= 2;
const int wlInvalidHardwareLicense 		= 3;
const int wlNoMoreHwdChanges       		= 4;
const int wlLicenseExpired         		= 5;
const int wlInvalidCountryLicense  		= 6;
const int wlLicenseStolen          		= 7;
const int wlWrongLicenseExp        		= 8;
const int wlWrongLicenseHardware   		= 9;
const int wlIsRegisteredNotActivared 	= 10;
const int wlIsRegisteredAndActivated 	= wlIsRegistered;

const int wlPermKey                		= -1;
const int wlNoKey                  		= -2;
const int wlNoTrialDate            		= -1;
const int wlInvalidCounter         		= -1;

// WinLicense functions prototype

 #ifdef __BORLANDC__

 extern "C" _stdcall __declspec(dllimport) int WLGenTrialExtensionFileKey(char* TrialHash, int Level,\
                                                int NumDays, int NumExec, SYSTEMTIME* NewDate, int NumMinutes,\
                                                int TimeRuntime, char* BufferOut);

 extern "C" _stdcall __declspec(dllimport) int WLGenTrialExtensionRegistryKey(char* TrialHash, int Level,\
                                                int NumDays, int NumExec, SYSTEMTIME* NewDate, int NumMinutes,\
                                                int TimeRuntime, char* pKeyName, char* pKeyValueName, char* BufferOut);

 extern "C" _stdcall __declspec(dllimport) int WLGenPassword(char* TrialHash, char* Name, char* BufferOut);

 extern "C" _stdcall __declspec(dllimport) int WLGenLicenseFileKey(char* LicenseHash, char* UserName, char* Organization,\
                                                char* CustomData, char* MachineID, int NumDays, int NumExec, SYSTEMTIME* NewDate, \
                                                int CountryId, int Runtime, int GlobalMinutes, char* BufferOut);

 extern "C" _stdcall __declspec(dllimport) int WLGenLicenseRegistryKey(char* LicenseHash, char* UserName, char* Organization,\
                                                char* CustomData, char* MachineID, int NumDays, int NumExec, SYSTEMTIME* NewDate, \
                                                int CountryId, int Runtime, int GlobalMinutes, char* KeyName, char* KeyValueName, char* BufferOut);

 extern "C" _stdcall __declspec(dllimport) int WLGenLicenseTextKey(char* LicenseHash, char* UserName, char* Organization,\
                                                char* CustomData, char* MachineID, int NumDays, int NumExec, SYSTEMTIME* NewDate, \
                                                int CountryId, int Runtime, int GlobalMinutes, char* BufferOut);

 extern "C" _stdcall __declspec(dllimport) int WLGenLicenseSmartKey(char* LicenseHash, char* UserName, char* Organization,\
                                                char* CustomData, char* MachineID, int NumDays, int NumExec, SYSTEMTIME* NewDate, \
                                                char* BufferOut);

 extern "C" _stdcall __declspec(dllimport) int WLRegGetStatus(int* pExtendedInfo);

 extern "C" _stdcall __declspec(dllimport) int WLTrialGetStatus(int* pExtendedInfo);

 extern "C" _stdcall __declspec(dllimport) int WLTrialExtGetStatus(void);
 
 extern "C" _stdcall __declspec(dllimport) bool WLRegGetLicenseInfo(char* pName, char* pCompanyName, char* pCustomData);

 extern "C" _stdcall __declspec(dllimport) int WLTrialTotalDays(void);
 
 extern "C" _stdcall __declspec(dllimport) int WLTrialTotalExecutions(void);

 extern "C" _stdcall __declspec(dllimport) int WLTrialDaysLeft(void);

 extern "C" _stdcall __declspec(dllimport) int WLTrialExecutionsLeft(void);

 extern "C" _stdcall __declspec(dllimport) int WLTrialExpirationDate(SYSTEMTIME* pExpDate);

 extern "C" _stdcall __declspec(dllimport) int WLTrialGlobalTimeLeft(void);

 extern "C" _stdcall __declspec(dllimport) int WLTrialRuntimeLeft(void);

 extern "C" _stdcall __declspec(dllimport) int WLTrialLockedCountry(void);

 extern "C" _stdcall __declspec(dllimport) int WLRegDaysLeft(void);

 extern "C" _stdcall __declspec(dllimport) int WLRegExecutionsLeft(void);

 extern "C" _stdcall __declspec(dllimport) int WLRegExpirationDate(SYSTEMTIME* pExpDate);

 extern "C" _stdcall __declspec(dllimport) int WLRegTotalExecutions(void);

 extern "C" _stdcall __declspec(dllimport) int WLRegTotalDays(void);

 extern "C" _stdcall __declspec(dllimport) bool WLHardwareGetID(char* pHardwareId);

 extern "C" _stdcall __declspec(dllimport) bool WLHardwareCheckID(char* pHardwareId);

 extern "C" _stdcall __declspec(dllimport) bool WLRegSmartKeyCheck(char* UserName, char* Organization, char* Custom, char* AsciiKey);

 extern "C" _stdcall __declspec(dllimport) bool WLRegNormalKeyCheck(char* AsciiKey);

 extern "C" _stdcall __declspec(dllimport) bool WLRegNormalKeyInstallToFile(char* AsciiKey);

 extern "C" _stdcall __declspec(dllimport) bool WLRegNormalKeyInstallToRegistry(char* AsciiKey);

 extern "C" _stdcall __declspec(dllimport) bool WLRegSmartKeyInstallToFile(char* UserName, char* Organization, char* Custom, char* AsciiKey);

 extern "C" _stdcall __declspec(dllimport) bool WLRegSmartKeyInstallToRegistry(char* UserName, char* Organization, char* Custom, char* AsciiKey);
 
 extern "C" _stdcall __declspec(dllimport) int WLTrialCustomCounterInc(int Value, int CounterId);

 extern "C" _stdcall __declspec(dllimport) int WLTrialCustomCounterDec(int Value, int CounterId);

 extern "C" _stdcall __declspec(dllimport) int WLTrialCustomCounter(int CounterId);

 extern "C" _stdcall __declspec(dllimport) int WLTrialCustomCounterSet(int Value, int CounterId);

 extern "C" _stdcall __declspec(dllimport) bool WLRestartApplication(void);

 extern "C" _stdcall __declspec(dllimport) int WLRegLockedCountry(void);

 extern "C" _stdcall __declspec(dllimport) int WLRegRuntimeLeft(void);

 extern "C" _stdcall __declspec(dllimport) int WLRegGlobalTimeLeft(void);

 extern "C" _stdcall __declspec(dllimport) bool WLRegDisableCurrentKey(int DisableFlags);

 extern "C" _stdcall __declspec(dllimport) bool WLRegRemoveCurrentKey(void);
 
 extern "C" _stdcall __declspec(dllimport) bool WLHardwareGetFormattedID(int BlockCharSize, int Uppercase, char* Buffer);
 
 extern "C" _stdcall __declspec(dllimport) bool WLPasswordCheck(char* UserName, char* Password);

 extern "C" _stdcall __declspec(dllimport) bool WLTrialExpireTrial(void);

 extern "C" _stdcall __declspec(dllimport) char* WLStringDecrypt(char* pString);

 extern "C" _stdcall __declspec(dllimport) void WLRegLicenseName(char* FileKeyName, char* RegKeyName, char* RegKeyValueName);

 extern "C" _stdcall __declspec(dllimport) bool WLRestartApplicationArgs(char* pArgs);

 extern "C" _stdcall __declspec(dllimport) bool WLActGetInfo(int* Custom1, int* Custom2, int* Custom3);

 extern "C" _stdcall __declspec(dllimport) bool WLActCheck(char* ActivationCode);

 extern "C" _stdcall __declspec(dllimport) bool WLActInstall(char* ActivationCode);

 extern "C" _stdcall __declspec(dllimport) bool WLActExpirationDate(SYSTEMTIME* pExpDate);

 extern "C" _stdcall __declspec(dllimport) int WLActDaysToActivate(void);

 extern "C" _stdcall __declspec(dllimport) bool WLActUninstall(void);

 extern "C" _stdcall __declspec(dllimport) int WLGetCurrentCountry(void);

 extern "C" _stdcall __declspec(dllimport) int WLTrialExtGetLevel(void);


 #else

 extern "C" int _stdcall GenerateTrialExtensionKey(char* TrialHash, int Level, int NumDays, int NumExec,\
                                                SYSTEMTIME* NewDate, int NumMinutes, int TimeRuntime,\
                                                char* BufferOut);

 extern "C" int _stdcall WLGenTrialExtensionFileKey(char* TrialHash, int Level,\
                                            int NumDays, int NumExec, SYSTEMTIME* NewDate, int NumMinutes,\
                                            int TimeRuntime, char* BufferOut);

 extern "C" int _stdcall WLGenTrialExtensionRegistryKey(char* TrialHash, int Level,\
                          int NumDays, int NumExec, SYSTEMTIME* NewDate, int NumMinutes,\
                          int TimeRuntime, char* pKeyName, char* pKeyValueName, char* BufferOut);

 extern "C" int _stdcall WLGenPassword(char* TrialHash, char* Name, char* BufferOut);

 extern "C" int _stdcall WLGenLicenseFileKey(char* LicenseHash, char* UserName, char* Organization,\
                          char* CustomData, char* MachineID, int NumDays, int NumExec, SYSTEMTIME* NewDate, \
                          int CountryId, int Runtime, int GlobalMinutes, char* BufferOut);

 extern "C" int _stdcall WLGenLicenseRegistryKey(char* LicenseHash, char* UserName, char* Organization,\
                          char* CustomData, char* MachineID, int NumDays, int NumExec, SYSTEMTIME* NewDate, \
                          int CountryId, int Runtime, int GlobalMinutes, char* KeyName, char* KeyValueName, char* BufferOut);

 extern "C" int _stdcall WLGenLicenseTextKey(char* LicenseHash, char* UserName, char* Organization,\
                          char* CustomData, char* MachineID, int NumDays, int NumExec, SYSTEMTIME* NewDate, \
                          int CountryId, int Runtime, int GlobalMinutes, char* BufferOut);

 extern "C" int _stdcall WLGenLicenseSmartKey(char* LicenseHash, char* UserName, char* Organization,\
                          char* CustomData, char* MachineID, int NumDays, int NumExec, SYSTEMTIME* NewDate, \
                          char* BufferOut);

 extern "C" int _stdcall WLRegGetStatus(int* pExtendedInfo);

 extern "C" int _stdcall WLTrialGetStatus(int* pExtendedInfo);

 extern "C" int _stdcall WLTrialExtGetStatus(void);
 
 extern "C" bool _stdcall WLRegGetLicenseInfo(char* pName, char* pCompanyName, char* pCustomData);

 extern "C" int _stdcall WLTrialTotalDays(void);
 
 extern "C" int _stdcall WLTrialTotalExecutions(void);

 extern "C" int _stdcall WLTrialDaysLeft(void);

 extern "C" int _stdcall WLTrialExecutionsLeft(void);

 extern "C" int _stdcall WLTrialExpirationDate(SYSTEMTIME* pExpDate);

 extern "C" int _stdcall WLTrialGlobalTimeLeft(void);

 extern "C" int _stdcall WLTrialRuntimeLeft(void);

 extern "C" int _stdcall WLTrialLockedCountry(void);

 extern "C" int _stdcall WLRegDaysLeft(void);

 extern "C" int _stdcall WLRegExecutionsLeft(void);

 extern "C" int _stdcall WLRegExpirationDate(SYSTEMTIME* pExpDate);

 extern "C" int _stdcall WLRegTotalExecutions(void);

 extern "C" int _stdcall WLRegTotalDays(void);

 extern "C" void _stdcall WLHardwareGetID(char* pHardwareId);

 extern "C" bool _stdcall WLHardwareCheckID(char* pHardwareId);

 extern "C" bool _stdcall WLRegSmartKeyCheck(char* UserName, char* Organization, char* Custom, char* AsciiKey);

 extern "C" bool _stdcall WLRegNormalKeyCheck(char* AsciiKey);

 extern "C" bool _stdcall WLRegNormalKeyInstallToFile(char* AsciiKey);

 extern "C" bool _stdcall WLRegNormalKeyInstallToRegistry(char* AsciiKey);

 extern "C" bool _stdcall WLRegSmartKeyInstallToFile(char* UserName, char* Organization, char* Custom, char* AsciiKey);

 extern "C" bool _stdcall WLRegSmartKeyInstallToRegistry(char* UserName, char* Organization, char* Custom, char* AsciiKey);
 
 extern "C" int _stdcall WLTrialCustomCounterInc(int Value, int CounterId);

 extern "C" int _stdcall WLTrialCustomCounterDec(int Value, int CounterId);

 extern "C" int _stdcall WLTrialCustomCounter(int CounterId);

 extern "C" int _stdcall WLTrialCustomCounterSet(int Value, int CounterId);

 extern "C" bool _stdcall WLRestartApplication(void);

 extern "C" int _stdcall WLRegLockedCountry(void);

 extern "C" int _stdcall WLRegRuntimeLeft(void);

 extern "C" int _stdcall WLRegGlobalTimeLeft(void);

 extern "C" bool _stdcall WLRegDisableCurrentKey(int DisableFlags);

 extern "C" bool _stdcall WLRegRemoveCurrentKey(void);
 
 extern "C" bool _stdcall WLHardwareGetFormattedID(int BlockCharSize, int Uppercase, char* Buffer);
 
 extern "C" bool _stdcall WLPasswordCheck(char* UserName, char* Password);

 extern "C" bool _stdcall WLTrialExpireTrial(void);

 extern "C" char* _stdcall WLStringDecrypt(char* pString);

 extern "C" void _stdcall WLRegLicenseName(char* FileKeyName, char* RegKeyName, char* RegKeyValueName);

 extern "C" bool _stdcall WLRestartApplicationArgs(char* pArgs);

 extern "C" bool _stdcall WLActGetInfo(int* Custom1, int* Custom2, int* Custom3);

 extern "C" bool _stdcall WLActCheck(char* ActivationCode);

 extern "C"  bool _stdcall WLActInstall(char* ActivationCode);

 extern "C"  bool _stdcall WLActExpirationDate(SYSTEMTIME* pExpDate);

 extern "C" int _stdcall WLActDaysToActivate(void);

 extern "C" bool _stdcall WLActUninstall(void);

 extern "C" int _stdcall WLGetCurrentCountry(void);

 extern "C" int _stdcall WLTrialExtGetLevel(void);

 #endif

// WinLicense macros definition
 
 #ifdef __BORLANDC__
 
 #define REMOVE_BLOCK_START      __emit__ (0xEB, 0x10, 0x57, 0x4C, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x57, 0x4C, 0x20, 0x20);
 #define REMOVE_BLOCK_END        __emit__ (0xEB, 0x10, 0x57, 0x4C, 0x20, 0x20, 0x01, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x57, 0x4C, 0x20, 0x20);

 #define CODEREPLACE_START      __emit__ (0xEB, 0x10, 0x57, 0x4C, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x57, 0x4C, 0x20, 0x20);
 #define CODEREPLACE_END        __emit__ (0xEB, 0x10, 0x57, 0x4C, 0x20, 0x20, 0x01, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x57, 0x4C, 0x20, 0x20);
 
 #define REGISTERED_START __emit__ (0xEB, 0x10, 0x57, 0x4C, 0x20, 0x20, 0x02, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x57, 0x4C, 0x20, 0x20);
 #define REGISTERED_END   __emit__ (0xEB, 0x10, 0x57, 0x4C, 0x20, 0x20, 0x03, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x57, 0x4C, 0x20, 0x20);
 
 #define ENCODE_START     __emit__ (0xEB, 0x10, 0x57, 0x4C, 0x20, 0x20, 0x04, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x57, 0x4C, 0x20, 0x20);
 #define ENCODE_END       __emit__ (0xEB, 0x10, 0x57, 0x4C, 0x20, 0x20, 0x05, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x57, 0x4C, 0x20, 0x20);

 #define CLEAR_START      __emit__ (0xEB, 0x10, 0x57, 0x4C, 0x20, 0x20, 0x06, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x57, 0x4C, 0x20, 0x20);
 #define CLEAR_END        __emit__ (0xEB, 0x15, 0x57, 0x4C, 0x20, 0x20, 0x07, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x57, 0x4C, 0x20, 0x20, 0x00, 0x00, \
                                    0x00, 0x00, 0x00);

  #define UNREGISTERED_START __emit__ (0xEB, 0x10, 0x57, 0x4C, 0x20, 0x20, 0x08, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x57, 0x4C, 0x20, 0x20);
 #define UNREGISTERED_END   __emit__ (0xEB, 0x10, 0x57, 0x4C, 0x20, 0x20, 0x09, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x57, 0x4C, 0x20, 0x20);

 #define VM_START     __emit__ (0xEB, 0x10, 0x57, 0x4C, 0x20, 0x20, 0x0C, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x57, 0x4C, 0x20, 0x20);
 #define VM_END       __emit__ (0xEB, 0x10, 0x57, 0x4C, 0x20, 0x20, 0x0D, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x57, 0x4C, 0x20, 0x20);

 #define VM_START_WITHLEVEL(x)     __emit__ (0xEB, 0x10, 0x57, 0x4C, 0x20, 0x20, 0x0C, 0x00, 0x00, 0x00, \
                                    0x00, x, 0x00, 0x00, 0x57, 0x4C, 0x20, 0x20);

 #define UNPROTECTED_START     __emit__ (0xEB, 0x10, 0x57, 0x4C, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x57, 0x4C, 0x20, 0x20);
 #define UNPROTECTED_END       __emit__ (0xEB, 0x10, 0x57, 0x4C, 0x20, 0x20, 0x21, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x57, 0x4C, 0x20, 0x20);

 #define __WL_MACROS__
 #endif
 
#endif
 
 /* intel cpp compiler */
 
#ifndef __WL_MACROS__
 
 #ifdef __ICL
 
 #define REMOVE_BLOCK_START \
  __asm __emit 0xEB \
  __asm __emit 0x10 \
  __asm __emit 0x57 \
  __asm __emit 0x4C \
  __asm __emit 0x20 \
  __asm __emit 0x20 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x57 \
  __asm __emit 0x4C \
  __asm __emit 0x20 \
  __asm __emit 0x20 \
 
 #define REMOVE_BLOCK_END \
  __asm __emit 0xEB \
  __asm __emit 0x10 \
  __asm __emit 0x57 \
  __asm __emit 0x4C \
  __asm __emit 0x20 \
  __asm __emit 0x20 \
  __asm __emit 0x01 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x57 \
  __asm __emit 0x4C \
  __asm __emit 0x20 \
  __asm __emit 0x20 \

  #define CODEREPLACE_START \
  __asm __emit 0xEB \
  __asm __emit 0x10 \
  __asm __emit 0x57 \
  __asm __emit 0x4C \
  __asm __emit 0x20 \
  __asm __emit 0x20 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x57 \
  __asm __emit 0x4C \
  __asm __emit 0x20 \
  __asm __emit 0x20 \
 
 #define CODEREPLACE_END \
  __asm __emit 0xEB \
  __asm __emit 0x10 \
  __asm __emit 0x57 \
  __asm __emit 0x4C \
  __asm __emit 0x20 \
  __asm __emit 0x20 \
  __asm __emit 0x01 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x57 \
  __asm __emit 0x4C \
  __asm __emit 0x20 \
  __asm __emit 0x20 \

 #define REGISTERED_START \
  __asm __emit 0xEB \
  __asm __emit 0x10 \
  __asm __emit 0x57 \
  __asm __emit 0x4C \
  __asm __emit 0x20 \
  __asm __emit 0x20 \
  __asm __emit 0x02 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x57 \
  __asm __emit 0x4C \
  __asm __emit 0x20 \
  __asm __emit 0x20 \
 
 #define REGISTERED_END \
  __asm __emit 0xEB \
  __asm __emit 0x10 \
  __asm __emit 0x57 \
  __asm __emit 0x4C \
  __asm __emit 0x20 \
  __asm __emit 0x20 \
  __asm __emit 0x03 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x57 \
  __asm __emit 0x4C \
  __asm __emit 0x20 \
  __asm __emit 0x20 \
 
 
 #define ENCODE_START \
  __asm __emit 0xEB \
  __asm __emit 0x10 \
  __asm __emit 0x57 \
  __asm __emit 0x4C \
  __asm __emit 0x20 \
  __asm __emit 0x20 \
  __asm __emit 0x04 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x57 \
  __asm __emit 0x4C \
  __asm __emit 0x20 \
  __asm __emit 0x20 \
 
 
 #define ENCODE_END \
  __asm __emit 0xEB \
  __asm __emit 0x10 \
  __asm __emit 0x57 \
  __asm __emit 0x4C \
  __asm __emit 0x20 \
  __asm __emit 0x20 \
  __asm __emit 0x05 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x57 \
  __asm __emit 0x4C \
  __asm __emit 0x20 \
  __asm __emit 0x20 \
 
 
 #define CLEAR_START \
  __asm __emit 0xEB \
  __asm __emit 0x10 \
  __asm __emit 0x57 \
  __asm __emit 0x4C \
  __asm __emit 0x20 \
  __asm __emit 0x20 \
  __asm __emit 0x06 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x57 \
  __asm __emit 0x4C \
  __asm __emit 0x20 \
  __asm __emit 0x20 \

 
 #define CLEAR_END \
  __asm __emit 0xEB \
  __asm __emit 0x15 \
  __asm __emit 0x57 \
  __asm __emit 0x4C \
  __asm __emit 0x20 \
  __asm __emit 0x20 \
  __asm __emit 0x07 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x57 \
  __asm __emit 0x4C \
  __asm __emit 0x20 \
  __asm __emit 0x20 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 
 
  #define UNREGISTERED_START \
  __asm __emit 0xEB \
  __asm __emit 0x10 \
  __asm __emit 0x57 \
  __asm __emit 0x4C \
  __asm __emit 0x20 \
  __asm __emit 0x20 \
  __asm __emit 0x08 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x57 \
  __asm __emit 0x4C \
  __asm __emit 0x20 \
  __asm __emit 0x20 \
 
 #define UNREGISTERED_END \
  __asm __emit 0xEB \
  __asm __emit 0x10 \
  __asm __emit 0x57 \
  __asm __emit 0x4C \
  __asm __emit 0x20 \
  __asm __emit 0x20 \
  __asm __emit 0x09 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x57 \
  __asm __emit 0x4C \
  __asm __emit 0x20 \
  __asm __emit 0x20 \

  #define VM_START_WITHLEVEL(x) \
  __asm __emit 0xEB \
  __asm __emit 0x10 \
  __asm __emit 0x57 \
  __asm __emit 0x4C \
  __asm __emit 0x20 \
  __asm __emit 0x20 \
  __asm __emit 0x0C \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit x \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x57 \
  __asm __emit 0x4C \
  __asm __emit 0x20 \
  __asm __emit 0x20 \


  #define VM_START \
  __asm __emit 0xEB \
  __asm __emit 0x10 \
  __asm __emit 0x57 \
  __asm __emit 0x4C \
  __asm __emit 0x20 \
  __asm __emit 0x20 \
  __asm __emit 0x0C \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x57 \
  __asm __emit 0x4C \
  __asm __emit 0x20 \
  __asm __emit 0x20 \
  
 #define VM_END \
  __asm __emit 0xEB \
  __asm __emit 0x10 \
  __asm __emit 0x57 \
  __asm __emit 0x4C \
  __asm __emit 0x20 \
  __asm __emit 0x20 \
  __asm __emit 0x0D \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x57 \
  __asm __emit 0x4C \
  __asm __emit 0x20 \
  __asm __emit 0x20 \


  #define UNPROTECTED_START \
  __asm __emit 0xEB \
  __asm __emit 0x10 \
  __asm __emit 0x57 \
  __asm __emit 0x4C \
  __asm __emit 0x20 \
  __asm __emit 0x20 \
  __asm __emit 0x20 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x57 \
  __asm __emit 0x4C \
  __asm __emit 0x20 \
  __asm __emit 0x20 \
  
 #define UNPROTECTED_END \
  __asm __emit 0xEB \
  __asm __emit 0x10 \
  __asm __emit 0x57 \
  __asm __emit 0x4C \
  __asm __emit 0x20 \
  __asm __emit 0x20 \
  __asm __emit 0x21 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x57 \
  __asm __emit 0x4C \
  __asm __emit 0x20 \
  __asm __emit 0x20 \


 #define __WL_MACROS__
 
 #endif
#endif
 
 
 /* LCC by Jacob Navia */
 
#ifndef __WL_MACROS__
 
 #ifdef __LCC__
 
 #define REMOVE_BLOCK_START     __asm__ (" .byte\t0xEB, 0x10, 0x57, 0x4C, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x57, 0x4C, 0x20, 0x20");
 #define REMOVE_BLOCK_END       __asm__ (" .byte\t0xEB, 0x10, 0x57, 0x4C, 0x20, 0x20, 0x01, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x57, 0x4C, 0x20, 0x20");

 #define CODEREPLACE_START     __asm__ (" .byte\t0xEB, 0x10, 0x57, 0x4C, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x57, 0x4C, 0x20, 0x20");
 #define CODEREPLACE_END       __asm__ (" .byte\t0xEB, 0x10, 0x57, 0x4C, 0x20, 0x20, 0x01, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x57, 0x4C, 0x20, 0x20");
 
 #define REGISTERED_START __asm__(" .byte\t0xEB, 0x10, 0x57, 0x4C, 0x20, 0x20, 0x02, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x57, 0x4C, 0x20, 0x20");
 #define REGISTERED_END   __asm__(" .byte\t0xEB, 0x10, 0x57, 0x4C, 0x20, 0x20, 0x03, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x57, 0x4C, 0x20, 0x20");
 
 #define ENCODE_START     __asm__(" .byte\t0xEB, 0x10, 0x57, 0x4C, 0x20, 0x20, 0x04, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x57, 0x4C, 0x20, 0x20");
 #define ENCODE_END       __asm__(" .byte\t0xEB, 0x10, 0x57, 0x4C, 0x20, 0x20, 0x05, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x57, 0x4C, 0x20, 0x20");
 
 #define CLEAR_START      __asm__(" .byte\t0xEB, 0x10, 0x57, 0x4C, 0x20, 0x20, 0x06, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x57, 0x4C, 0x20, 0x20");
 
 #define CLEAR_END        __asm__(" .byte\t0xEB, 0x15, 0x57, 0x4C, 0x20, 0x20, 0x07, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x57, 0x4C, 0x20, 0x20, 0x00, 0x00, \
                                    0x00, 0x00, 0x00");

 #define UNREGISTERED_START __asm__(" .byte\t0xEB, 0x10, 0x57, 0x4C, 0x20, 0x20, 0x08, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x57, 0x4C, 0x20, 0x20");
 #define UNREGISTERED_END   __asm__(" .byte\t0xEB, 0x10, 0x57, 0x4C, 0x20, 0x20, 0x09, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x57, 0x4C, 0x20, 0x20");

 #define VM_START_WITHLEVEL(x) __asm__(" .byte\t0xEB, 0x10, 0x57, 0x4C, 0x20, 0x20, 0x0C, 0x00, 0x00, 0x00, \
                                    0x00, x, 0x00, 0x00, 0x57, 0x4C, 0x20, 0x20");

 #define VM_START         __asm__(" .byte\t0xEB, 0x10, 0x57, 0x4C, 0x20, 0x20, 0x0C, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x57, 0x4C, 0x20, 0x20");

 #define VM_END           __asm__(" .byte\t0xEB, 0x10, 0x57, 0x4C, 0x20, 0x20, 0x0D, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x57, 0x4C, 0x20, 0x20");

 #define UNPROTECTED_START         __asm__(" .byte\t0xEB, 0x10, 0x57, 0x4C, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x57, 0x4C, 0x20, 0x20");

 #define UNPROTECTED_END           __asm__(" .byte\t0xEB, 0x10, 0x57, 0x4C, 0x20, 0x20, 0x21, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x57, 0x4C, 0x20, 0x20");

 #define __WL_MACROS__
 #endif
 
#endif
 
 
#ifndef __WL_MACROS__
 
 #define REMOVE_BLOCK_START \
  __asm _emit 0xEB \
  __asm _emit 0x10 \
  __asm _emit 0x57 \
  __asm _emit 0x4C \
  __asm _emit 0x20 \
  __asm _emit 0x20 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x57 \
  __asm _emit 0x4C \
  __asm _emit 0x20 \
  __asm _emit 0x20 \
 
 #define REMOVE_BLOCK_END \
  __asm _emit 0xEB \
  __asm _emit 0x10 \
  __asm _emit 0x57 \
  __asm _emit 0x4C \
  __asm _emit 0x20 \
  __asm _emit 0x20 \
  __asm _emit 0x01 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x57 \
  __asm _emit 0x4C \
  __asm _emit 0x20 \
  __asm _emit 0x20 \

 #define CODEREPLACE_START \
  __asm _emit 0xEB \
  __asm _emit 0x10 \
  __asm _emit 0x57 \
  __asm _emit 0x4C \
  __asm _emit 0x20 \
  __asm _emit 0x20 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x57 \
  __asm _emit 0x4C \
  __asm _emit 0x20 \
  __asm _emit 0x20 \
 
 #define CODEREPLACE_END \
  __asm _emit 0xEB \
  __asm _emit 0x10 \
  __asm _emit 0x57 \
  __asm _emit 0x4C \
  __asm _emit 0x20 \
  __asm _emit 0x20 \
  __asm _emit 0x01 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x57 \
  __asm _emit 0x4C \
  __asm _emit 0x20 \
  __asm _emit 0x20 \

 #define REGISTERED_START \
  __asm _emit 0xEB \
  __asm _emit 0x10 \
  __asm _emit 0x57 \
  __asm _emit 0x4C \
  __asm _emit 0x20 \
  __asm _emit 0x20 \
  __asm _emit 0x02 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x57 \
  __asm _emit 0x4C \
  __asm _emit 0x20 \
  __asm _emit 0x20 \
 
#define REGISTERED_END \
  __asm _emit 0xEB \
  __asm _emit 0x10 \
  __asm _emit 0x57 \
  __asm _emit 0x4C \
  __asm _emit 0x20 \
  __asm _emit 0x20 \
  __asm _emit 0x03 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x57 \
  __asm _emit 0x4C \
  __asm _emit 0x20 \
  __asm _emit 0x20 \
 
 #define ENCODE_START \
  __asm _emit 0xEB \
  __asm _emit 0x10 \
  __asm _emit 0x57 \
  __asm _emit 0x4C \
  __asm _emit 0x20 \
  __asm _emit 0x20 \
  __asm _emit 0x04 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x57 \
  __asm _emit 0x4C \
  __asm _emit 0x20 \
  __asm _emit 0x20 \
 
 #define ENCODE_END \
  __asm _emit 0xEB \
  __asm _emit 0x10 \
  __asm _emit 0x57 \
  __asm _emit 0x4C \
  __asm _emit 0x20 \
  __asm _emit 0x20 \
  __asm _emit 0x05 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x57 \
  __asm _emit 0x4C \
  __asm _emit 0x20 \
  __asm _emit 0x20 \
 
 #define CLEAR_START \
  __asm _emit 0xEB \
  __asm _emit 0x10 \
  __asm _emit 0x57 \
  __asm _emit 0x4C \
  __asm _emit 0x20 \
  __asm _emit 0x20 \
  __asm _emit 0x06 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x57 \
  __asm _emit 0x4C \
  __asm _emit 0x20 \
  __asm _emit 0x20 \
 
 #define CLEAR_END \
  __asm _emit 0xEB \
  __asm _emit 0x15 \
  __asm _emit 0x57 \
  __asm _emit 0x4C \
  __asm _emit 0x20 \
  __asm _emit 0x20 \
  __asm _emit 0x07 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x57 \
  __asm _emit 0x4C \
  __asm _emit 0x20 \
  __asm _emit 0x20 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 

 #define UNREGISTERED_START \
  __asm _emit 0xEB \
  __asm _emit 0x10 \
  __asm _emit 0x57 \
  __asm _emit 0x4C \
  __asm _emit 0x20 \
  __asm _emit 0x20 \
  __asm _emit 0x08 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x57 \
  __asm _emit 0x4C \
  __asm _emit 0x20 \
  __asm _emit 0x20 \
 
#define UNREGISTERED_END \
  __asm _emit 0xEB \
  __asm _emit 0x10 \
  __asm _emit 0x57 \
  __asm _emit 0x4C \
  __asm _emit 0x20 \
  __asm _emit 0x20 \
  __asm _emit 0x09 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x57 \
  __asm _emit 0x4C \
  __asm _emit 0x20 \
  __asm _emit 0x20 \

 #define VM_START \
  __asm _emit 0xEB \
  __asm _emit 0x10 \
  __asm _emit 0x57 \
  __asm _emit 0x4C \
  __asm _emit 0x20 \
  __asm _emit 0x20 \
  __asm _emit 0x0C \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x57 \
  __asm _emit 0x4C \
  __asm _emit 0x20 \
  __asm _emit 0x20 \

 #define VM_START_WITHLEVEL(x) \
  __asm _emit 0xEB \
  __asm _emit 0x10 \
  __asm _emit 0x57 \
  __asm _emit 0x4C \
  __asm _emit 0x20 \
  __asm _emit 0x20 \
  __asm _emit 0x0C \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit x \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x57 \
  __asm _emit 0x4C \
  __asm _emit 0x20 \
  __asm _emit 0x20 \
 
 #define VM_END \
  __asm _emit 0xEB \
  __asm _emit 0x10 \
  __asm _emit 0x57 \
  __asm _emit 0x4C \
  __asm _emit 0x20 \
  __asm _emit 0x20 \
  __asm _emit 0x0D \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x57 \
  __asm _emit 0x4C \
  __asm _emit 0x20 \
  __asm _emit 0x20 \

 #define UNPROTECTED_START \
  __asm _emit 0xEB \
  __asm _emit 0x10 \
  __asm _emit 0x57 \
  __asm _emit 0x4C \
  __asm _emit 0x20 \
  __asm _emit 0x20 \
  __asm _emit 0x20 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x57 \
  __asm _emit 0x4C \
  __asm _emit 0x20 \
  __asm _emit 0x20 \

 #define UNPROTECTED_END \
  __asm _emit 0xEB \
  __asm _emit 0x10 \
  __asm _emit 0x57 \
  __asm _emit 0x4C \
  __asm _emit 0x20 \
  __asm _emit 0x20 \
  __asm _emit 0x21 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x57 \
  __asm _emit 0x4C \
  __asm _emit 0x20 \
  __asm _emit 0x20 \
 

#endif
