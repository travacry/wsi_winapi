#include "model.h"
extern "C" __declspec(dllexport) void Func()
{
	cout << "This is function from dll: Func()" << endl;
} 

extern "C" __declspec(dllexport) void getListCurrObjs(list<PACKAGE>& data)
{
	mObj.getPack(data);
}
extern "C" __declspec(dllexport) void getListMapObjsWin(list<STBASE>& data, VERWIN ver)
{
	mObj.getMapWin(data, ver);
}
extern "C" __declspec(dllexport) void getListAccess(list<STBASE>& data, TYPEACCESS type, string& objType)
{
	mObj.getMapAccess(data, type, objType);
}

