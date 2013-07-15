#ifndef DLL_H
	#define DLL_H

	#include "../Model/CManagerObjs.h"

	static CManagerObjs mObj;
	using namespace std;

	extern "C" __declspec(dllexport) void Func();

	extern "C" __declspec(dllexport) void getListCurrObjs(list<PACKAGE>& data);

	extern "C" __declspec(dllexport) void getListMapObjsWin(list<STBASE>& data, VERWIN ver);

	extern "C" __declspec(dllexport) void getListAccess(list<STBASE>& data, 
														TYPEACCESS type, 
														string& objType);
#endif