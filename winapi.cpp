#include "winapi.h"
//Источники : http://www.powerbasic.com/support/pbforums/showthread.php?p=262465
#define	  stop __asm nop

int wmain(int argc, WCHAR *argv[])
{
	//импорт из библиотек Native-API функции:

	//получение информации о системе
    _NtQuerySystemInformation NtQuerySystemInformation = (_NtQuerySystemInformation)
        GetLibraryProcAddress("ntdll.dll", "NtQuerySystemInformation");
	//для копирования хендла в текущий процесс
    _NtDuplicateObject NtDuplicateObject = (_NtDuplicateObject)
        GetLibraryProcAddress("ntdll.dll", "NtDuplicateObject");
	//получает некоторую информацию об одном или нескольких объектах. 
	//открытых вызывающим процесом
    _NtQueryObject NtQueryObject = (_NtQueryObject)
        GetLibraryProcAddress("ntdll.dll", "NtQueryObject");

	PSYSTEM_HANDLE_INFORMATION pSysHandleInformation = new SYSTEM_HANDLE_INFORMATION;
    DWORD size = sizeof(SYSTEM_HANDLE_INFORMATION);
    DWORD needed = 0;
    NTSTATUS status = NtQuerySystemInformation( SystemHandleInformation, 
                      pSysHandleInformation, size, &needed );
    if( !NT_SUCCESS(status))
    {
        if( 0 == needed )
        {
            return 0;// some other error
        }
        // The previously supplied buffer wasn't enough.
        delete pSysHandleInformation;
        size = needed + 1024;
        pSysHandleInformation = (PSYSTEM_HANDLE_INFORMATION)new BYTE[size];
        status = NtQuerySystemInformation( SystemHandleInformation, 
                                           pSysHandleInformation, size, &needed );
        if( !NT_SUCCESS(status))
        {
            // some other error so quit.
            delete pSysHandleInformation;
            return 0;
        }
		stop;
		VERWIN curr_ver = GetWinVersion();
		for (int i=0; i<pSysHandleInformation->HandleCount; i++)
		{
			SYSTEM_HANDLE& SysHI = pSysHandleInformation->Handles[i];
			char sObjectType[15] = { "\0" };
			char* sTypeAccess;
			
			try {
				ChangeTab(sObjectType, SysHI.ObjectTypeNumber, curr_ver);
			} catch (...) {
				printf("error, UnKnown");
				continue;
			}
			
			ChangeAccess(sTypeAccess, SysHI.GrantedAccess,SysHI.ObjectTypeNumber, curr_ver);
		//	static const char* names[] = {""
			printf("Type: %15s , ProcessId: %8d, Handle: %8d \n", sObjectType, SysHI.ProcessId, SysHI.Handle);
			printf("Access: %10s \n", sTypeAccess);
			delete[] sTypeAccess; 
		}
	}

	stop;
    return 0;
}