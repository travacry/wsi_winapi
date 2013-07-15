/********************************************************
	* File: CMangerObjs.h
	* Discription: Manager for parsing objects created in windows and maps's init.
	* Created: 28.03.2013
	* Copyright: (C) 2013 AK
	* Author: Alexander Kuznetsov
	* Email: prog.alex.k@gmail.com
	* Lg comment's : RU
********************************************************/

//parser obj's

//******************************************************

#ifndef CMANOBJS_H
#define CMANOBJS_H

	#include "../Model/CWinInfo.h"
	#include "../Model/CWinObj.h"

	class CManagerObjs
	{

		CWinObj						m_WObj;
		_NtQuerySystemInformation	NtQuerySystemInformation;
		list<PACKAGE>				m_pack;
													
		list<STBASE>				m_mapWin;			
		list<STBASE>				m_mapAccess;		

		list<STBASE>				m_BaseAccess;		
		list<STBASE>				m_StandartAccess;	
		list<STBASE>				m_SpecAccess;		
	
	public:

		CManagerObjs();

		void ParserObjs();

		void ParserMap(VERWIN ver);

		void ParserAccess(string type);

		void getPack(list<PACKAGE>& data);					//*выходной пакет

															//@можно просматривать win карты
															//@и карты спецификаторов доступа:
		void getMapWin(list<STBASE>& data, VERWIN ver);		

		void getMapAccess(	list<STBASE>& data,				
							TYPEACCESS type, 
							string& objType); // { SpecialAR,StandardAR,BasicAR );
	
		void Clear();

		PVOID GetLibraryProcAddress(PSTR LibraryName, PSTR ProcName);

	private:

		void Generation(void* pArr, list<STBASE>& list, size_t size);
		void GenerationSpec(list<STBASE>& list,string& type);

	};

#endif

//******************************************************

//ПОДКЛЮЧЕНИЕ БИБЛИОТЕК:

CManagerObjs::CManagerObjs()
{
	//получение информации о системе
    NtQuerySystemInformation = (_NtQuerySystemInformation)
        GetLibraryProcAddress("ntdll.dll", "NtQuerySystemInformation");
	
}

PVOID CManagerObjs::GetLibraryProcAddress(PSTR LibraryName, PSTR ProcName)
{
	return GetProcAddress(GetModuleHandleA(LibraryName), ProcName);
}



void CManagerObjs::ParserObjs()
{
	CWinInfo m_wf;
	VERWIN ver = m_wf.getVersion();

	//проверка на первый
	PSYSTEM_HANDLE_INFORMATION pSysHandleInformation = new SYSTEM_HANDLE_INFORMATION;
    DWORD size = sizeof(SYSTEM_HANDLE_INFORMATION);
    DWORD needed = 0;

//@		!NtQuerySystemInformation IF ERROR => status != 0
    NTSTATUS status = NtQuerySystemInformation( SystemHandleInformation, 
												pSysHandleInformation, 
												size, 
												&needed );
	if( !NT_SUCCESS(status)){
		if( 0 == needed )
        {
            return;// some other error
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
            return;
        }
		for (int i=0; i<pSysHandleInformation->HandleCount; i++)
		{
			SYSTEM_HANDLE SysHI = pSysHandleInformation->Handles[i];
			m_WObj = &SysHI;    
			PACKAGE pack = m_WObj.GetPackageInfo(ver);
			m_pack.push_back(pack);
		}
	}
	delete pSysHandleInformation;
}

//очистить пакет
void CManagerObjs::Clear()
{
	m_pack.clear();
}

//заполнение win карт 
void CManagerObjs::ParserMap(VERWIN ver)
{
	switch(ver){
		case Win2000:	
			Generation(Win2000_strs, m_mapWin, sizeof(Win2000_strs) / sizeof(STBASE));
		break;
		case WinNT:	
			Generation(WinNT_strs, m_mapWin, sizeof(WinNT_strs) / sizeof(STBASE));
		break;
		case WinXP:	
			Generation(WinXP_strs, m_mapWin, sizeof(WinXP_strs) / sizeof(STBASE));
		break;
	}
}

//генерация списка обьектов
void  CManagerObjs::Generation(void* pArr, list<STBASE>& list, size_t size)
{
//		!к общему типу для всех обектов
	STBASE* pCur = static_cast<STBASE*>(pArr);

	for(int i=0; i<size; i++){	

		list.push_back(*pCur); 
		++pCur;	

	}
}

//генерирование специального спецификатора доступа
void  CManagerObjs::GenerationSpec(list<STBASE>& list, string& type)
{
	for (;;)
	{
		if(type=="Directory"){
			Generation(DirectorySARights_strs, list, m_WObj.countDirectorySARights);
			break;
		};
		if(type=="Token"){
			Generation(TokenSARights_strs, list, m_WObj.countTokenSARights);
			break;
		};
		if(type=="Process"){
			Generation(ProcessSARights_strs, list, m_WObj.countProcessSARights);
			break;
		};
		if(type=="Thread"){
			Generation(ThreadSARights_strs, list, m_WObj.countThreadSARights);
			break;
		};
		if(type=="Job"){
			Generation(JobSARights_strs, list, m_WObj.countJobSARights);
			break;
		};
		if(type=="Desktop"){
			Generation(DesktopSARights_strs, list, m_WObj.countDesktopSARights);
			break;
		};
		if(type=="Event"){
			Generation(EventSARights_strs, list, m_WObj.countEventSARights);
			break;
		};
		if(type=="File"){
			Generation(FileSARights_strs, list, m_WObj.countFileSARights);
			break;
		};
		if(type=="Key"){
			Generation(KeySARights_strs, list, m_WObj.countKeySARights);
			break;
		};
		if(type=="Semaphore"){
			Generation(SemaphoreSARights_strs, list, m_WObj.countSemaphoreSARights);
			break;
		};
		if(type=="Timer"){
			Generation(TimerSARights_strs, list, m_WObj.countTimerSARights);
			break;
		};
		if(type=="WindowStation"){
			Generation(WinStaSARights_strs, list, m_WObj.countWinStaSARights);
			break;
		};
	}	
}

//парсер спецификаторов доступа, заполняет: m_StandartAccess, m_BaseAccess, m_SpecAccess
void CManagerObjs::ParserAccess(string type)
{
	m_StandartAccess.clear();
	m_BaseAccess.clear();
	m_SpecAccess.clear();

	Generation(	StandartARights_strs,
				m_StandartAccess, 
				m_WObj.countStandartARights);

	Generation(	BaseARights_strs, 
				m_BaseAccess, 
				m_WObj.countBaseARights);

	GenerationSpec(	m_SpecAccess, type);
}


//получение выходного пакета обьектов
void CManagerObjs::getPack(list<PACKAGE>& data)
{

	data.clear();
	ParserObjs();
	data = m_pack;

}

//получение карт обьектов определенной версии Windows
void CManagerObjs::getMapWin(list<STBASE>& data, VERWIN ver)
{
	data.clear();
	m_mapWin.clear();
	ParserMap(ver);
	data = m_mapWin;
}

//получение карт спецификаторов доступа
void CManagerObjs::getMapAccess(list<STBASE>& data,TYPEACCESS type, string& objType) // { SpecialAR,StandardAR,BasicAR };
{

	data.clear();
	m_mapAccess.clear();

	switch (type){

		case SpecialAR:
			GenerationSpec(m_mapAccess,objType);
		break;

		case StandardAR:
			Generation(	StandartARights_strs, 
						m_mapAccess, 
						sizeof(StandartARights_strs) / sizeof(STBASE));
		break;

		case BasicAR:
			Generation(	BaseARights_strs, 
						m_mapAccess, 
						sizeof(BaseARights_strs) / sizeof(STBASE));
		break;

	}
	data = m_mapAccess;

}
