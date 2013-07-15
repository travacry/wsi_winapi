#include <iostream>
#include <windows.h>
#include <conio.h>
#include <list>
#include <windows.h>
#include <WTypes.h>

#define	  stop __asm nop

using namespace std;

#define SystemHandleInformation 16
typedef struct stBase_ 
{ 
	std::string text; 
	int val; 
} STBASE;

typedef NTSTATUS (NTAPI *_NtQuerySystemInformation)(
	ULONG SystemInformationClass,
	PVOID SystemInformation,
	ULONG SystemInformationLength,
	PULONG ReturnLength
);

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

//package for a data model
typedef struct stPACKAGE
{
	std::string	ObjName;
	std::string Special;
	std::string Sandart;
	std::string Base;	
	ULONG 		id;
	USHORT 		Handle;
} PACKAGE;

enum VERWIN { WinXP=51, Win2000=50, WinNT=40 };
enum TYPEACCESS { SpecialAR,StandardAR,BasicAR };

int main()
{
	HINSTANCE hLib = LoadLibrary(L"model.dll");
	if(hLib == NULL)
	{
		cout << "Unable to load library!" << endl;
		_getch();
		return 1;
	}
	//-------------------------------------------------
	list<PACKAGE>	pack_data;
	list<STBASE>	base_data;
	VERWIN			version;
	TYPEACCESS		type_acc;
	string			type_name_obj;
	//-------------------------------------------------

	//get all objs from current windows, with attr
	typedef void(*getListCurrObjs)(list<PACKAGE>& data); //prototype
	getListCurrObjs SetListCurrObjs;
	SetListCurrObjs = (getListCurrObjs)GetProcAddress((HMODULE)hLib, "getListCurrObjs"); // replacing previous string	

	//getListMapObjsWin(list<STBASE>& data, VERWIN ver)
	//get only map version (xp, 2000, nt)
	typedef void(*getListMapObjsWin)(list<STBASE>& data, VERWIN ver); //prototype
	getListMapObjsWin SetListMapObjsWin;

	version = WinXP;
	SetListMapObjsWin = (getListMapObjsWin)GetProcAddress((HMODULE)hLib, "getListMapObjsWin"); // replacing previous string

	//getListAccess(list<STBASE>& data, TYPEACCESS type, string& objType)
	//get only map access
	typedef void(*getListAccess)(list<STBASE>& data, TYPEACCESS type, string& objType); //prototype
	getListAccess SetListMapAccess;

	type_name_obj = "none";
	type_acc = StandardAR;
	SetListMapAccess = (getListAccess)GetProcAddress((HMODULE)hLib, "getListAccess"); // replacing previous string
	
	//-------------------------------------------------
	if(SetListCurrObjs == NULL){ cout << "Unable to load function getListCurrObjs." << endl; FreeLibrary((HMODULE)hLib); return 1; }
	if(SetListCurrObjs) { SetListCurrObjs(pack_data); };
	if(SetListMapObjsWin == NULL){ cout << "Unable to load function getListMapObjsWin." << endl; FreeLibrary((HMODULE)hLib); return 1; }
	if(SetListMapObjsWin) { SetListMapObjsWin(base_data, version); };
	if(SetListMapAccess == NULL){ cout << "Unable to load function getListAccess." << endl; FreeLibrary((HMODULE)hLib); return 1; }
	if(SetListMapAccess) { SetListMapAccess(base_data, type_acc, type_name_obj); };
	//-------------------------------------------------

	stop;
	//end
	FreeLibrary((HMODULE)hLib);
	_getch();
	
	return 0;
} 
