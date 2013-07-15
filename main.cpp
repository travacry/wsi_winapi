#include "assert.h"
#include "Model\CManagerObjs.h"
using namespace std;

CManagerObjs mObj;
void getListCurrObjs(list<PACKAGE>& data)
{
	static CManagerObjs mObj_next;
	mObj_next.ParserObjs();

	cout << "This is function from dll: getListCurrObjs()" << endl;
	mObj_next.getPack(data);
	cout << "begin";
	PACKAGE pack = *data.begin();
	cout << "handle:" << pack.Handle << "id:" << pack.id << "obj_name:" << pack.ObjName;
	cout << "end";
}

#define	  stop __asm nop
int main(){
	int val = 0;
	const string ProcStr("PROCESS_TERMINATE");
	const string FileStr("FILE_READ_DATA");
	const string WinStaStr("WINSTA_CREATEDESKTOP");
	const string KeyStr("KEY_ENUMERATE_SUB_KEYS");

	const string WinNTStr("Controller");
	const string Win2000Str("Port");
	const string WinXpStr("Section");
	
	assert(ProcStr.compare(ProcessSARights_strs[0].text)==0);
	assert(FileStr.compare(FileSARights_strs[0].text)==0);
	assert(WinStaStr.compare(WinStaSARights_strs[3].text)==0);
	assert(KeyStr.compare(KeySARights_strs[3].text)==0);

	assert(WinNTStr.compare(WinNT_strs[18].text)==0);
	assert(Win2000Str.compare(Win2000_strs[18].text)==0);
	assert(WinXpStr.compare(WinXP_strs[18].text)==0);

	stop;

	string s1("test1"); 
	string s2("test2"); 
	string s3("test3"); 

	//прсит все обьекты
	mObj.ParserObjs();
	mObj.ParserAccess("Directory");
	mObj.ParserMap(Win2000);

	list<STBASE> data;
	mObj.getMapWin(data, WinXP);
	stop;

	string str("none");
	mObj.getMapAccess(data, StandardAR, str);
	stop;

	mObj.getMapAccess(data, BasicAR, str);
	stop;

	str = "Semaphore";
	mObj.getMapAccess(data, SpecialAR, str);
	stop;

	list<PACKAGE> data_pack;
	getListCurrObjs(data_pack);
	PACKAGE pak = *data_pack.begin();
	stop;

	//dll
	getListCurrObjs(data_pack);
	int sz = data_pack.size();
	list<PACKAGE>::iterator pIter = data_pack.begin();

	return 0;
}