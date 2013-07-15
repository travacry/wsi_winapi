#include <windows.h>
#include <stdio.h>
#include <Sddl.h>

#define	  stop __asm nop

#define NT_SUCCESS(inpNumber) ((inpNumber) >= 0)
//#define STATUS_INFO_LENGTH_MISMATCH 0xc0000004

#define SystemHandleInformation 16
#define ObjectBasicInformation 0
#define ObjectNameInformation 1
#define ObjectTypeInformation 2

typedef NTSTATUS (NTAPI *_NtQuerySystemInformation)(
	ULONG SystemInformationClass,
	PVOID SystemInformation,
	ULONG SystemInformationLength,
	PULONG ReturnLength
	);
typedef NTSTATUS (NTAPI *_NtDuplicateObject)(
	HANDLE SourceProcessHandle,
	HANDLE SourceHandle,
	HANDLE TargetProcessHandle,
	PHANDLE TargetHandle,
	ACCESS_MASK DesiredAccess,
	ULONG Attributes,
	ULONG Options
	);
typedef NTSTATUS (NTAPI *_NtQueryObject)(
	HANDLE ObjectHandle,
	ULONG ObjectInformationClass,
	PVOID ObjectInformation,
	ULONG ObjectInformationLength,
	PULONG ReturnLength
	);

typedef struct _UNICODE_STRING
{
	USHORT Length;
	USHORT MaximumLength;
	PWSTR Buffer;
} UNICODE_STRING, *PUNICODE_STRING;
typedef struct _SYSTEM_HANDLE
{
	ULONG ProcessId;
	BYTE ObjectTypeNumber;
	BYTE Flags;
	USHORT Handle;
	PVOID Object;
	ACCESS_MASK GrantedAccess;
} SYSTEM_HANDLE, *PSYSTEM_HANDLE;

typedef struct _SYSTEM_HANDLE_INFORMATION
{
	ULONG HandleCount;
	SYSTEM_HANDLE Handles[1];
} SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION;

typedef enum _POOL_TYPE
{
	NonPagedPool,
	PagedPool,
	NonPagedPoolMustSucceed,
	DontUseThisType,
	NonPagedPoolCacheAligned,
	PagedPoolCacheAligned,
	NonPagedPoolCacheAlignedMustS
} POOL_TYPE, *PPOOL_TYPE;
/*
typedef struct _OBJECT_TYPE_INFORMATION
{
	UNICODE_STRING Name;
	ULONG TotalNumberOfObjects;
	ULONG TotalNumberOfHandles;
	ULONG TotalPagedPoolUsage;
	ULONG TotalNonPagedPoolUsage;
	ULONG TotalNamePoolUsage;
	ULONG TotalHandleTableUsage;
	ULONG HighWaterNumberOfObjects;
	ULONG HighWaterNumberOfHandles;
	ULONG HighWaterPagedPoolUsage;
	ULONG HighWaterNonPagedPoolUsage;
	ULONG HighWaterNamePoolUsage;
	ULONG HighWaterHandleTableUsage;
	ULONG InvalidAttributes;
	GENERIC_MAPPING GenericMapping;
	ULONG ValidAccess;
	BOOLEAN SecurityRequired;
	BOOLEAN MaintainHandleCount;
	USHORT MaintainTypeList;
	POOL_TYPE PoolType;
	ULONG PagedPoolUsage;
	ULONG NonPagedPoolUsage;
} OBJECT_TYPE_INFORMATION, *POBJECT_TYPE_INFORMATION;
*/


typedef struct _FILE_STREAM_INFORMATION
{
  ULONG NextEntryOffset;
  ULONG StreamNameLength;
  LARGE_INTEGER StreamSize;
  LARGE_INTEGER StreamAllocationSize;
  WCHAR StreamName[1];
} FILE_STREAM_INFORMATION, *PFILE_STREAM_INFORMATION;

typedef struct _IO_STATUS_BLOCK {
  union {
    NTSTATUS Status;
    PVOID    Pointer;
  };
  ULONG_PTR Information;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;
/*
typedef enum _FILE_INFORMATION_CLASS { 
  FileDirectoryInformation                 = 1,
  FileFullDirectoryInformation,
  FileBothDirectoryInformation,
  FileBasicInformation,
  FileStandardInformation,
  FileInternalInformation,
  FileEaInformation,
  FileAccessInformation,
  FileNameInformation,
  FileRenameInformation,
  FileLinkInformation,
  FileNamesInformation,
  FileDispositionInformation,
  FilePositionInformation,
  FileFullEaInformation,
  FileModeInformation,
  FileAlignmentInformation,
  FileAllInformation,
  FileAllocationInformation,
  FileEndOfFileInformation,
  FileAlternateNameInformation,
  FileStreamInformation,
  FilePipeInformation,
  FilePipeLocalInformation,
  FilePipeRemoteInformation,
  FileMailslotQueryInformation,
  FileMailslotSetInformation,
  FileCompressionInformation,
  FileObjectIdInformation,
  FileCompletionInformation,
  FileMoveClusterInformation,
  FileQuotaInformation,
  FileReparsePointInformation,
  FileNetworkOpenInformation,
  FileAttributeTagInformation,
  FileTrackingInformation,
  FileIdBothDirectoryInformation,
  FileIdFullDirectoryInformation,
  FileValidDataLengthInformation,
  FileShortNameInformation,
  FileIoCompletionNotificationInformation,
  FileIoStatusBlockRangeInformation,
  FileIoPriorityHintInformation,
  FileSfioReserveInformation,
  FileSfioVolumeInformation,
  FileHardLinkInformation,
  FileProcessIdsUsingFileInformation,
  FileNormalizedNameInformation,
  FileNetworkPhysicalNameInformation,
  FileIdGlobalTxDirectoryInformation,
  FileIsRemoteDeviceInformation,
  FileAttributeCacheInformation,
  FileNumaNodeInformation,
  FileStandardLinkInformation,
  FileRemoteProtocolInformation,
  FileMaximumInformation
} FILE_INFORMATION_CLASS, *PFILE_INFORMATION_CLASS;

NTSTATUS ZwQueryInformationFile(
  _In_   HANDLE FileHandle,
  _Out_  PIO_STATUS_BLOCK IoStatusBlock,
  _Out_  PVOID FileInformation,
  _In_   ULONG Length,
  _In_   FILE_INFORMATION_CLASS FileInformationClass
);
*/

PVOID GetLibraryProcAddress(PSTR LibraryName, PSTR ProcName)
{
	return GetProcAddress(GetModuleHandleA(LibraryName), ProcName);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//определение версии Win
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum VERWIN { WinXP, Win2000, WinNT };
//для XP : 51 , для Win2000 : 50 , для NT : 40
VERWIN GetWinVersion(){
	DWORD dwVersion = 0; 
    DWORD dwMajorVersion = 0;
    DWORD dwMinorVersion = 0; 
    DWORD dwBuild = 0;

    dwVersion = GetVersion();
 
    // Get the Windows version.
    dwMajorVersion = static_cast<DWORD>(LOBYTE(LOWORD(dwVersion)));
    dwMinorVersion = static_cast<DWORD>(HIBYTE(LOWORD(dwVersion)));

    // Get the build number.
    if (dwVersion < 0x80000000) dwBuild = static_cast<DWORD>(HIWORD(dwVersion));

    //printf("Version is %d.%d (%d)\n", dwMajorVersion, dwMinorVersion, dwBuild);
	switch (dwMajorVersion*10 + dwMinorVersion){
		case 51 : return WinXP;
		case 50 : return Win2000;
		case 40 : return WinNT;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//добавление информации о правах доступа к той инфе что уже есть
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Resize(char*& sBase, char* str){
	char* tmp = sBase;
	if (sBase == nullptr){
		sBase = new char[strlen(str)+1];
		strcpy(sBase, str);
	} else {
		sBase = new char [strlen(sBase) + strlen(str)+1];
		strcpy(sBase, tmp);
		delete[] tmp;
		strcat(sBase, str);
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//получение строки с правами доступа
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DirectorySARights(DWORD SpecialAccessRights, char* sTypeAccess){
	switch (SpecialAccessRights){
		case FILE_LIST_DIRECTORY:	
			Resize(sTypeAccess, " FILE_LIST_DIRECTORY");	break;
		case FILE_ADD_FILE:			
			Resize(sTypeAccess, " FILE_ADD_FILE");			break;
		case FILE_ADD_SUBDIRECTORY:			
			Resize(sTypeAccess, " FILE_ADD_SUBDIRECTORY");			break;
		case FILE_READ_EA:			
			Resize(sTypeAccess, " FILE_READ_EA");			break;
		case FILE_WRITE_EA:			
			Resize(sTypeAccess, " FILE_WRITE_EA");			break;
		case FILE_TRAVERSE:			
			Resize(sTypeAccess, " FILE_TRAVERSE");			break;
		case FILE_DELETE_CHILD:			
			Resize(sTypeAccess, " FILE_DELETE_CHILD");			break;
		case FILE_READ_ATTRIBUTES:			
			Resize(sTypeAccess, " FILE_READ_ATTRIBUTES");			break;
		case FILE_WRITE_ATTRIBUTES:			
			Resize(sTypeAccess, " FILE_WRITE_ATTRIBUTES");			break;
	}
}

void FileSARights(DWORD SpecialAccessRights, char* sTypeAccess)
{
	switch (SpecialAccessRights){
		case FILE_READ_DATA:
			Resize(sTypeAccess, " FILE_READ_DATA");	break;
		case FILE_WRITE_DATA:
			Resize(sTypeAccess, " FILE_WRITE_DATA");	break;
		case FILE_APPEND_DATA:
			Resize(sTypeAccess, " FILE_APPEND_DATA");	break;
		case FILE_READ_EA:
			Resize(sTypeAccess, " FILE_READ_EA");	break;
		case FILE_WRITE_EA:
			Resize(sTypeAccess, " FILE_WRITE_EA");	break;
		case FILE_EXECUTE:
			Resize(sTypeAccess, " FILE_EXECUTE");	break;
		case FILE_READ_ATTRIBUTES:
			Resize(sTypeAccess, " FILE_READ_ATTRIBUTES");	break;
		case FILE_WRITE_ATTRIBUTES:
			Resize(sTypeAccess, " FILE_WRITE_ATTRIBUTES");	break;
	}
}

void TokenSARights(DWORD SpecialAccessRights, char* sTypeAccess)
{
	switch (SpecialAccessRights){
		case TOKEN_ASSIGN_PRIMARY:
			Resize(sTypeAccess, " TOKEN_ASSIGN_PRIMARY");	break;
		case TOKEN_DUPLICATE:
			Resize(sTypeAccess, " TOKEN_DUPLICATE");	break;
		case TOKEN_IMPERSONATE:
			Resize(sTypeAccess, " TOKEN_IMPERSONATE");	break;
		case TOKEN_QUERY:
			Resize(sTypeAccess, " TOKEN_QUERY");	break;
		case TOKEN_QUERY_SOURCE:
			Resize(sTypeAccess, " TOKEN_QUERY_SOURCE");	break;
		case TOKEN_ADJUST_PRIVILEGES:
			Resize(sTypeAccess, " TOKEN_ADJUST_PRIVILEGES");	break;
		case TOKEN_ADJUST_GROUPS:
			Resize(sTypeAccess, " TOKEN_ADJUST_GROUPS");	break;
		case TOKEN_ADJUST_DEFAULT:
			Resize(sTypeAccess, " TOKEN_ADJUST_DEFAULT");	break;
		case TOKEN_ADJUST_SESSIONID:
			Resize(sTypeAccess, " TOKEN_ADJUST_SESSIONID");	break;
		case TOKEN_ALL_ACCESS_P:
			Resize(sTypeAccess, " TOKEN_ALL_ACCESS_P");	break;
	}
}
void ProcessSARights(DWORD SpecialAccessRights, char* sTypeAccess)
{
	switch (SpecialAccessRights){
		case PROCESS_TERMINATE:
			Resize(sTypeAccess, " PROCESS_TERMINATE");	break;		
		case PROCESS_CREATE_THREAD:
			Resize(sTypeAccess, " PROCESS_CREATE_THREAD");	break;		
		case PROCESS_SET_SESSIONID:
			Resize(sTypeAccess, " PROCESS_SET_SESSIONID");	break;		
		case PROCESS_VM_OPERATION:
			Resize(sTypeAccess, " PROCESS_VM_OPERATION");	break;		
		case PROCESS_VM_READ:
			Resize(sTypeAccess, " PROCESS_VM_READ");	break;		
		case PROCESS_VM_WRITE:
			Resize(sTypeAccess, " PROCESS_VM_WRITE");	break;		
		case PROCESS_DUP_HANDLE:
			Resize(sTypeAccess, " PROCESS_DUP_HANDLE");	break;		
		case PROCESS_CREATE_PROCESS:
			Resize(sTypeAccess, " PROCESS_CREATE_PROCESS");	break;		
		case PROCESS_SET_QUOTA:
			Resize(sTypeAccess, " PROCESS_SET_QUOTA");	break;		
		case PROCESS_SET_INFORMATION:
			Resize(sTypeAccess, " PROCESS_SET_INFORMATION");	break;		
		case PROCESS_QUERY_INFORMATION:
			Resize(sTypeAccess, " PROCESS_QUERY_INFORMATION");	break;		
		case PROCESS_SUSPEND_RESUME:
			Resize(sTypeAccess, " PROCESS_SUSPEND_RESUME");	break;		
		case PROCESS_QUERY_LIMITED_INFORMATION:
			Resize(sTypeAccess, " PROCESS_QUERY_LIMITED_INFORMATION");	break;		
		case PROCESS_ALL_ACCESS:
		case 0x0FFF:
			Resize(sTypeAccess, " PROCESS_ALL_ACCESS");	break;
	}
}
void ThreadSARights(DWORD SpecialAccessRights, char* sTypeAccess)
{
	switch (SpecialAccessRights){
		case THREAD_TERMINATE:
			Resize(sTypeAccess, " THREAD_TERMINATE");	break;
		case THREAD_SUSPEND_RESUME:
			Resize(sTypeAccess, " THREAD_SUSPEND_RESUME");	break;
		case THREAD_GET_CONTEXT:
			Resize(sTypeAccess, " THREAD_GET_CONTEXT");	break;
		case THREAD_SET_CONTEXT:
			Resize(sTypeAccess, " THREAD_SET_CONTEXT");	break;
		case THREAD_QUERY_INFORMATION:
			Resize(sTypeAccess, " THREAD_QUERY_INFORMATION");	break;
		case THREAD_SET_INFORMATION:
			Resize(sTypeAccess, " THREAD_SET_INFORMATION");	break;
		case THREAD_SET_THREAD_TOKEN:
			Resize(sTypeAccess, " THREAD_SET_THREAD_TOKEN");	break;
		case THREAD_IMPERSONATE:
			Resize(sTypeAccess, " THREAD_IMPERSONATE");	break;
		case THREAD_DIRECT_IMPERSONATION:
			Resize(sTypeAccess, " THREAD_DIRECT_IMPERSONATION");	break;
		case THREAD_ALL_ACCESS:
			Resize(sTypeAccess, " THREAD_ALL_ACCESS");	break;
	}
}
void JobSARights(DWORD SpecialAccessRights, char* sTypeAccess)
{
	switch (SpecialAccessRights){
		case JOB_OBJECT_ASSIGN_PROCESS:
			Resize(sTypeAccess, " JOB_OBJECT_ASSIGN_PROCESS");	break;
		case JOB_OBJECT_SET_ATTRIBUTES:
			Resize(sTypeAccess, " JOB_OBJECT_SET_ATTRIBUTES");	break;
		case JOB_OBJECT_QUERY:
			Resize(sTypeAccess, " JOB_OBJECT_QUERY");	break;
		case JOB_OBJECT_TERMINATE:
			Resize(sTypeAccess, " JOB_OBJECT_TERMINATE");	break;
		case JOB_OBJECT_SET_SECURITY_ATTRIBUTES:
			Resize(sTypeAccess, " JOB_OBJECT_SET_SECURITY_ATTRIBUTES");	break;
		case JOB_OBJECT_ALL_ACCESS:
			Resize(sTypeAccess, " JOB_OBJECT_ALL_ACCESS");	break;
	}
}
void EventSARights(DWORD SpecialAccessRights, char* sTypeAccess)
{
	switch (SpecialAccessRights){
		case MUTANT_QUERY_STATE: Resize(sTypeAccess, " JOB_OBJECT_ALL_ACCESS");	break;
		case EVENT_MODIFY_STATE: Resize(sTypeAccess, " JOB_OBJECT_ALL_ACCESS");	break;
		case EVENT_ALL_ACCESS: Resize(sTypeAccess, " JOB_OBJECT_ALL_ACCESS");	break;
	}
}
void SemaphoreSARights(DWORD SpecialAccessRights, char* sTypeAccess)
{
	switch (SpecialAccessRights){
		case MUTANT_QUERY_STATE: Resize(sTypeAccess, " MUTANT_QUERY_STATE");	break;
		case SEMAPHORE_MODIFY_STATE: Resize(sTypeAccess, " SEMAPHORE_MODIFY_STATE");	break;
		case SEMAPHORE_ALL_ACCESS: Resize(sTypeAccess, " SEMAPHORE_ALL_ACCESS");	break;
	}
}
void TimerSARights(DWORD SpecialAccessRights, char* sTypeAccess)
{
	switch (SpecialAccessRights){
		case TIMER_QUERY_STATE: Resize(sTypeAccess, " TIMER_QUERY_STATE");	break;
		case TIMER_MODIFY_STATE: Resize(sTypeAccess, " TIMER_MODIFY_STATE");	break;
		case TIMER_ALL_ACCESS: Resize(sTypeAccess, " TIMER_ALL_ACCESS");	break;
	}
}
void WindowStationSARights(DWORD SpecialAccessRights, char* sTypeAccess)
{
	switch (SpecialAccessRights){
		case WINSTA_ENUMDESKTOPS: Resize(sTypeAccess, " WINSTA_ENUMDESKTOPS");	break;
		case WINSTA_READATTRIBUTES: Resize(sTypeAccess, " WINSTA_READATTRIBUTES");	break;
		case WINSTA_ACCESSCLIPBOARD: Resize(sTypeAccess, " WINSTA_ACCESSCLIPBOARD");	break;
		case WINSTA_CREATEDESKTOP: Resize(sTypeAccess, " WINSTA_CREATEDESKTOP");	break;
		case WINSTA_WRITEATTRIBUTES: Resize(sTypeAccess, " WINSTA_WRITEATTRIBUTES");	break;
		case WINSTA_ACCESSGLOBALATOMS: Resize(sTypeAccess, " WINSTA_ACCESSGLOBALATOMS");	break;
		case WINSTA_EXITWINDOWS: Resize(sTypeAccess, " WINSTA_EXITWINDOWS");	break;
		case WINSTA_ENUMERATE: Resize(sTypeAccess, " WINSTA_ENUMERATE");	break;
		case WINSTA_READSCREEN: Resize(sTypeAccess, " WINSTA_READSCREEN");	break;
		case WINSTA_ALL_ACCESS: Resize(sTypeAccess, " WINSTA_ALL_ACCESS");	break;
	}
}
void DesktopSARights(DWORD SpecialAccessRights, char* sTypeAccess)
{
	switch (SpecialAccessRights){
		case DESKTOP_READOBJECTS: Resize(sTypeAccess, " DESKTOP_READOBJECTS");	break;
		case DESKTOP_CREATEWINDOW: Resize(sTypeAccess, " DESKTOP_CREATEWINDOW");	break;
		case DESKTOP_CREATEMENU: Resize(sTypeAccess, " DESKTOP_CREATEMENU");	break;
		case DESKTOP_HOOKCONTROL: Resize(sTypeAccess, " DESKTOP_HOOKCONTROL");	break;
		case DESKTOP_JOURNALRECORD: Resize(sTypeAccess, " DESKTOP_JOURNALRECORD");	break;
		case DESKTOP_JOURNALPLAYBACK: Resize(sTypeAccess, " DESKTOP_JOURNALPLAYBACK");	break;
		case DESKTOP_ENUMERATE: Resize(sTypeAccess, " DESKTOP_ENUMERATE");	break;
		case DESKTOP_WRITEOBJECTS: Resize(sTypeAccess, " DESKTOP_WRITEOBJECTS");	break;
		case DESKTOP_SWITCHDESKTOP: Resize(sTypeAccess, " DESKTOP_SWITCHDESKTOP");	break;
	}
}
void KeySARights(DWORD SpecialAccessRights, char* sTypeAccess)
{
	switch (SpecialAccessRights){
		case KEY_QUERY_VALUE: Resize(sTypeAccess, " KEY_QUERY_VALUE");	break;
		case KEY_SET_VALUE: Resize(sTypeAccess, " KEY_SET_VALUE");	break;
		case KEY_CREATE_SUB_KEY: Resize(sTypeAccess, " KEY_CREATE_SUB_KEY");	break;
		case KEY_ENUMERATE_SUB_KEYS: Resize(sTypeAccess, " KEY_ENUMERATE_SUB_KEYS");	break;
		case KEY_NOTIFY: Resize(sTypeAccess, " KEY_NOTIFY");	break;
		case KEY_CREATE_LINK: Resize(sTypeAccess, " KEY_CREATE_LINK");	break;
		case KEY_WOW64_32KEY: Resize(sTypeAccess, " KEY_WOW64_32KEY");	break;
		case KEY_WOW64_64KEY: Resize(sTypeAccess, " KEY_WOW64_64KEY");	break;
		case KEY_WOW64_RES: Resize(sTypeAccess, " KEY_WOW64_RES");	break;
		case KEY_READ: Resize(sTypeAccess, " KEY_READ");	break;
		case KEY_WRITE: Resize(sTypeAccess, " KEY_WRITE");	break;
		case KEY_ALL_ACCESS: Resize(sTypeAccess, " KEY_ALL_ACCESS");	break;
	}
}
void WmiGuidSARights(DWORD SpecialAccessRights, char* sTypeAccess)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//получение строк для отображения по GrantedAccess прав доступ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ChangeAccess(char*& sTypeAccess,const ACCESS_MASK GrantedAccess, 
	const BYTE ObjectTypeNumber,const VERWIN ver){
// 1111 (28-31) . 111 (25-27) . 1 (24) . 1 (23) . 111 1111 (22-16) . 1111 1111 1111 1111 (0-15)

	DWORD SpecialAccessRights =		GrantedAccess&0x0000ffff;	//0-15
	DWORD StandardAccessRights =	GrantedAccess&0x007f0000;	//22-16
	DWORD Audit =					GrantedAccess&0x00800000;	//23 доступ к системному списку контроля доступа
	DWORD MaximumAllowable =		GrantedAccess&0x01000000;	//24
	DWORD Reserve =					GrantedAccess&0x0e000000;	//25-27
	DWORD BasicAccessRights =		GrantedAccess&0xf0000000;	//28-31
	//Стандартные права не меняются от обьекта к обьекту
	sTypeAccess = nullptr;

	switch (StandardAccessRights){
		case DELETE						: Resize(sTypeAccess, "DELETE");					break;
		case READ_CONTROL				: Resize(sTypeAccess, "READ_CONTROL");				break;
		case WRITE_DAC					: Resize(sTypeAccess, "WRITE_DAC");					break;
		case WRITE_OWNER				: Resize(sTypeAccess, "WRITE_OWNER");				break;
		case SYNCHRONIZE				: Resize(sTypeAccess, "SYNCHRONIZE");				break;
		case STANDARD_RIGHTS_REQUIRED	: Resize(sTypeAccess, "STANDARD_RIGHTS_REQUIRED");	break;
		case STANDARD_RIGHTS_ALL		: Resize(sTypeAccess, "STANDARD_RIGHTS_ALL");		break;
	}
	//Специальные права - определение полного списка специальных прав,
	//соответствующих обьекту
	if (ver == WinNT){
	switch (ObjectTypeNumber) {
		case 2 : /*"Directory"*/	
			DirectorySARights(SpecialAccessRights, sTypeAccess);
		break;
		case 4 : /*"Token"*/							
			TokenSARights(SpecialAccessRights, sTypeAccess);
		break;
		case 5 : /*"Process"*/							
			ProcessSARights(SpecialAccessRights, sTypeAccess);
		break;
		case 6 : /*"Thread"*/							
			ThreadSARights(SpecialAccessRights, sTypeAccess);
		break;
		case 7 :  /*"Event"*/;			
			EventSARights(SpecialAccessRights, sTypeAccess);
		break;
		case 10 : /*"Semaphore"*/
			SemaphoreSARights(SpecialAccessRights, sTypeAccess);
		break;
		case 11 : /*"Timer"*/			
			TimerSARights(SpecialAccessRights, sTypeAccess);	
		break;
		case 13 : /*"WindowStation"*/	
			WindowStationSARights(SpecialAccessRights, sTypeAccess);	
		break;
		case 14 : /*"Desktop"*/
			DesktopSARights(SpecialAccessRights, sTypeAccess);	
		break;
		case 16 : /*"Key"*/			
			KeySARights(SpecialAccessRights, sTypeAccess);
		break;   
		case 23 : /*"File"*/		
			FileSARights(SpecialAccessRights, sTypeAccess);
		break;
		default : /*"UnKnown"*/		
		break;
		}
	}
	if (ver == WinXP){
	switch (ObjectTypeNumber) {
		case 2 : 
			DirectorySARights(SpecialAccessRights, sTypeAccess);
		break;
		case 4 :
			TokenSARights(SpecialAccessRights, sTypeAccess);
		break;
		case 5 :
			ProcessSARights(SpecialAccessRights, sTypeAccess);
		break;
		case 6 :
			ThreadSARights(SpecialAccessRights, sTypeAccess);
		break;
		case 7 :
			JobSARights(SpecialAccessRights, sTypeAccess);
		break;  		
		case 9 :
			EventSARights(SpecialAccessRights, sTypeAccess);
		break;
		case 13 :
			SemaphoreSARights(SpecialAccessRights, sTypeAccess);
		break;
		case 14 :
			TimerSARights(SpecialAccessRights, sTypeAccess);
		break;
		case 17 :
			WindowStationSARights(SpecialAccessRights, sTypeAccess);
		break;
		case 18 :
			DesktopSARights(SpecialAccessRights, sTypeAccess);
		break;
		case 20 :
			KeySARights(SpecialAccessRights, sTypeAccess);
		break;   
		case 28 :
			FileSARights(SpecialAccessRights, sTypeAccess);
		break;
		case 29 :
			WmiGuidSARights(SpecialAccessRights, sTypeAccess);
		break;
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//определение обьекта по его типу ObjectTypeNumber и версии Win - ver
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ChangeTab(char* sObjectType,BYTE ObjectTypeNumber, VERWIN ver){
/*
		' Windows NT 4          Window 2000            Window XP, probably 2003 and Vista
 ' -----------------     -------------------    -------------------
 '  1 - Type              1 - Type               1 - (Type)
 '  2 - Directory         2 - Directory          2 - Directory
 '  3 - SymbolicLink      3 - SymbolicLink       3 - SymbolicLink
 '  4 - Token             4 - Token              4 - Token
 '  5 - Process           5 - Process            5 - Process
 '  6 - Thread            6 - Thread             6 - Thread
 '  7 - Event             7 - Job                7 - Job
 '  8 - EventPair         8 - Event              8 - ((DebugObject))
 '  9 - Mutant            9 - EventPair          9 - Event
 ' 10 - Semaphore        10 - Mutant            10 - (EventPair)
 ' 11 - Timer            11 - Callback          11 - Mutant
 ' 12 - Profile          12 - Semaphore         12 - (Callback)
 ' 13 - WindowStation    13 - Timer             13 - Semaphore
 ' 14 - Desktop          14 - Profile           14 - Timer
 ' 15 - Section          15 - WindowsStation    15 - (Profile)
 ' 16 - Key              16 - Desktop           16 - KeyedEvent
 ' 17 - Port             17 - Section           17 - WindowStation
 ' 18 - Adapter          18 - Key               18 - Desktop
 ' 19 - Controller       19 - Port              19 - Section
 ' 20 - Device           20 - WaitablePort      20 - Key
 ' 21 - Driver           21 - Adapter           21 - Port
 ' 22 - IoCompletion     22 - Controller        22 - WaitablePort
 ' 23 - File             23 - Device            23 - (Adapter)
 '                       24 - Driver            24 - (Controller)
 '                       25 - IoCompletion      25 - (Device)
 '                       26 - File              26 - (Driver)
 '                       27 - WmiGuid           27 - IoCompletion
 '                                              28 - File
 '                                              29 - WmiGuid
 */
	if (ver == WinNT)
	switch (ObjectTypeNumber) {
		case 1:  strcpy(sObjectType,"Type");			break;
		case 2 : strcpy(sObjectType,"Directory");		break;
		case 3 : strcpy(sObjectType,"SymbolicLink");	break;
		case 4 : strcpy(sObjectType,"Token");			break;
		case 5 : strcpy(sObjectType,"Process");			break;
		case 6 : strcpy(sObjectType,"Thread");			break;
		case 7 : strcpy(sObjectType,"Event");			break;
		case 8 : strcpy(sObjectType,"(EventPair)");		break;
		case 9 : strcpy(sObjectType,"Mutant");			break;
		case 10 : strcpy(sObjectType,"Semaphore");		break;
		case 11 : strcpy(sObjectType,"Timer");			break;
		case 12 : strcpy(sObjectType,"(Profile)");		break;
		case 13 : strcpy(sObjectType,"WindowStation");	break;
		case 14 : strcpy(sObjectType,"Desktop");		break;
		case 15 : strcpy(sObjectType,"Section");		break;
		case 16 : strcpy(sObjectType,"Key");			break;   
		case 17 : strcpy(sObjectType,"Port");			break;
		case 18 : strcpy(sObjectType,"(Adapter)");		break;
		case 19 : strcpy(sObjectType,"(Controller)");	break;
		case 20 : strcpy(sObjectType,"(Device)");		break;
		case 21 : strcpy(sObjectType,"(Driver)");		break;
		case 22 : strcpy(sObjectType,"IoCompletion");	break;
		case 23 : strcpy(sObjectType,"File");			break;
		default : strcpy(sObjectType,"UnKnown");		break;
	};
	//enum {}
	if (ver == Win2000)
	switch (ObjectTypeNumber) {
		case 1:  strcpy(sObjectType,"Type");			break;
		case 2 : strcpy(sObjectType,"Directory");		break;
		case 3 : strcpy(sObjectType,"SymbolicLink");	break;
		case 4 : strcpy(sObjectType,"Token");			break;
		case 5 : strcpy(sObjectType,"Process");			break;
		case 6 : strcpy(sObjectType,"Thread");			break;
		case 7 : strcpy(sObjectType,"Job");				break;  
		case 8 : strcpy(sObjectType,"Event");			break;
		case 9 : strcpy(sObjectType,"(EventPair)");		break;
		case 10 : strcpy(sObjectType,"Mutant");			break;
		case 11 : strcpy(sObjectType,"(Callback)");		break;
		case 12 : strcpy(sObjectType,"Semaphore");		break;
		case 13 : strcpy(sObjectType,"Timer");			break;
		case 14 : strcpy(sObjectType,"(Profile)");		break;
		case 15 : strcpy(sObjectType,"WindowStation");	break;
		case 16 : strcpy(sObjectType,"Desktop");		break;
		case 17 : strcpy(sObjectType,"Section");		break;
		case 18 : strcpy(sObjectType,"Key");			break;   
		case 19 : strcpy(sObjectType,"Port");			break;
		case 20 : strcpy(sObjectType,"WaitablePort");	break;
		case 21 : strcpy(sObjectType,"(Adapter)");		break;
		case 22 : strcpy(sObjectType,"(Controller)");	break;
		case 23 : strcpy(sObjectType,"(Device)");		break;
		case 24 : strcpy(sObjectType,"(Driver)");		break;
		case 25 : strcpy(sObjectType,"IoCompletion");	break;
		case 26 : strcpy(sObjectType,"File");			break;
		case 27 : strcpy(sObjectType,"WmiGuid");		break;
		default : strcpy(sObjectType,"UnKnown");		break;
	};
	if (ver == WinXP)
	switch (ObjectTypeNumber) {
		case 1:  strcpy(sObjectType,"Type");			break;
		case 2 : strcpy(sObjectType,"Directory");		break;
		case 3 : strcpy(sObjectType,"SymbolicLink");	break;
		case 4 : strcpy(sObjectType,"Token");			break;
		case 5 : strcpy(sObjectType,"Process");			break;
		case 6 : strcpy(sObjectType,"Thread");			break;
		case 7 : strcpy(sObjectType,"Job");				break;  
		case 8 : strcpy(sObjectType,"((DebugObject))"); break;
		case 9 : strcpy(sObjectType,"Event");			break;
		case 10 : strcpy(sObjectType,"(EventPair)");	break;
		case 11 : strcpy(sObjectType,"Mutant");			break;
		case 12 : strcpy(sObjectType,"(Callback)");		break;
		case 13 : strcpy(sObjectType,"Semaphore");		break;
		case 14 : strcpy(sObjectType,"Timer");			break;
		case 15 : strcpy(sObjectType,"(Profile)");		break;
		case 16 : strcpy(sObjectType,"KeyedEvent");		break;
		case 17 : strcpy(sObjectType,"WindowStation");	break;
		case 18 : strcpy(sObjectType,"Desktop");		break;
		case 19 : strcpy(sObjectType,"Section");		break;
		case 20 : strcpy(sObjectType,"Key");			break;   
		case 21 : strcpy(sObjectType,"Port");			break;
		case 22 : strcpy(sObjectType,"WaitablePort");	break;
		case 23 : strcpy(sObjectType,"(Adapter)");		break;
		case 24 : strcpy(sObjectType,"(Controller)");	break;
		case 25 : strcpy(sObjectType,"(Device)");		break;
		case 26 : strcpy(sObjectType,"(Driver)");		break;
		case 27 : strcpy(sObjectType,"IoCompletion");	break;
		case 28 : strcpy(sObjectType,"File");			break;
		case 29 : strcpy(sObjectType,"WmiGuid");		break;
		default : strcpy(sObjectType,"UnKnown");		break;
	};
}

