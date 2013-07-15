/********************************************************
	* File: CWinObj.h
	* Discription: Select the map windows and parses objects-type selected for this map.
	* Created: 28.03.2013
	* Copyright: (C) 2013 AK
	* Author: Alexander Kuznetsov
	* Email: prog.alex.k@gmail.com
	* Lg comment's : RU
********************************************************/

//parsing all win objects-type (from map's win)

//@здесь используется хеадеры без .cpp по той причине,
//@что используются макросы и для препроцессора подключение .cpp -
//@повторное включение хедера с переинициализацией emum || array

//******************************************************

#ifndef CWINOBJ_H
#define CWINOBJ_H

	#include "general_model.h"

	class CWinObj
	{

		PSYSTEM_HANDLE m_pSysHI;
		ULONG 		m_ProcessId;
		BYTE 		m_ObjectTypeNumber;		
		BYTE 		m_Flags;
		USHORT 		m_Handle;
		PVOID 		m_Object;
		ACCESS_MASK m_GrantedAccess;		//	все спецификаторы доступа выбранного обьекта

		PACKAGE		m_Package;				//	вся инфа

		size_t		m_Size_stAcc;			//	размер структуры (для всех структур одинаков)


											//	рамеры созданных массивов спецификаторов доступа(макросы):
		size_t		countStandartARights;	
		size_t		countBaseARights;		
		size_t		countDesktopSARights;
		size_t		countDirectorySARights;
		size_t		countEventSARights;
		size_t		countFileSARights;
		size_t		countJobSARights;
		size_t		countKeySARights;
		size_t		countProcessSARights;
		size_t		countSemaphoreSARights;
		size_t		countThreadSARights;
		size_t		countTimerSARights;
		size_t		countTokenSARights;
		size_t		countWinStaSARights;

	public:

		CWinObj();
		CWinObj(PSYSTEM_HANDLE pSysHI);
		CWinObj& operator=(const PSYSTEM_HANDLE right);
		PACKAGE& GetPackageInfo(VERWIN ver);

	private:
		
		void setInfoAccess(void* ArrayAcc, size_t size_el, int val, TYPEACCESS type);

		friend class CManagerObjs;

	};

#endif CWINOBJ_H

//******************************************************

//инициализация
CWinObj::CWinObj()
{
	m_ProcessId=m_ObjectTypeNumber=m_Flags=m_Handle=0;
	m_Object=nullptr;
	m_GrantedAccess=0;
	m_Package.Special=m_Package.Sandart=m_Package.Base="";
	m_Size_stAcc = sizeof(stBaseARights); //размер структуры

//		!определение размеров полученных массивов - спецификаторов доступа

	countStandartARights =		sizeof(StandartARights_strs) / sizeof(stBaseARights);
	countBaseARights =			sizeof(BaseARights_strs) / sizeof(stBaseARights);

	countDesktopSARights =		sizeof(DesktopSARights_strs) / sizeof(stBaseARights);
	countDirectorySARights =	sizeof(DirectorySARights_strs) / sizeof(stBaseARights);
	countEventSARights =		sizeof(EventSARights_strs) / sizeof(stBaseARights);
	countFileSARights =			sizeof(FileSARights_strs) / sizeof(stBaseARights);
	countJobSARights =			sizeof(JobSARights_strs) / sizeof(stBaseARights);
	countKeySARights =			sizeof(KeySARights_strs) / sizeof(stBaseARights);
	countProcessSARights =		sizeof(ProcessSARights_strs) / sizeof(stBaseARights);
	countSemaphoreSARights =	sizeof(SemaphoreSARights_strs) / sizeof(stBaseARights);
	countThreadSARights =		sizeof(ThreadSARights_strs) / sizeof(stBaseARights);
	countTimerSARights =		sizeof(TimerSARights_strs) / sizeof(stBaseARights);
	countTokenSARights =		sizeof(TokenSARights_strs) / sizeof(stBaseARights);
	countWinStaSARights =		sizeof(WinStaSARights_strs) / sizeof(stBaseARights);

}

//
CWinObj::CWinObj(PSYSTEM_HANDLE pSysHI)
{
	m_ProcessId = pSysHI->ProcessId;
	m_ObjectTypeNumber = pSysHI->ObjectTypeNumber;
	m_Flags = pSysHI->Flags;
	m_Handle = pSysHI->Handle;
	m_Object = pSysHI->Object;
	m_GrantedAccess = pSysHI->GrantedAccess;
}


CWinObj& CWinObj::operator=(const PSYSTEM_HANDLE right)
{
	m_ProcessId = right->ProcessId;
	m_ObjectTypeNumber = right->ObjectTypeNumber;
	m_Flags = right->Flags;
	m_Handle = right->Handle;
	m_Object = right->Object;
	m_GrantedAccess = right->GrantedAccess;
	return *this;
}

//поучение пакета данных
PACKAGE& CWinObj::GetPackageInfo(VERWIN ver)
{
	//получить обьект
	switch(ver)
	{

//		!выбор по картам обьектов Windows
		case Win2000:
			m_Package.ObjName = Win2000_strs[m_ObjectTypeNumber-1].text;
		break;
		case WinNT:
			m_Package.ObjName = WinNT_strs[m_ObjectTypeNumber-1].text;
		break;
		case WinXP:
			m_Package.ObjName = WinXP_strs[m_ObjectTypeNumber-1].text;
		break;

	}
//		!получение по маске доспупа спец. дост.
//		!1111 (28-31) . 111 (25-27) . 1 (24) . 1 (23) 
//		!. 111 1111 (22-16) . 1111 1111 1111 1111 (0-15)

	DWORD StandardAccessRights =	STANDART_GM(m_GrantedAccess);
	DWORD SpecialAccessRights =		SPECIAL_GM(m_GrantedAccess);
	DWORD BasicAccessRights =		BASE_GM(m_GrantedAccess);

//		!прозапас+)
	DWORD Audit =					AUDIT_GM(m_GrantedAccess);
	DWORD MaximumAllowable =		MAXALLOWABLE_GM(m_GrantedAccess);
	DWORD Reserve =					RESERVE_GM(m_GrantedAccess);
	
//		!1.получение стандартных прав:

	setInfoAccess(	StandartARights_strs, 
					countStandartARights, 
					StandardAccessRights, 
					StandardAR);

//		!2.дополнительные специальные права (полные и тд):

//		!получение специальных прав
	for (;;)
	{

		if(m_Package.ObjName=="Directory"){
			setInfoAccess(DirectorySARights_strs, countDirectorySARights, 
							SpecialAccessRights, SpecialAR);
			break;
		};
		if(m_Package.ObjName=="Token"){
			setInfoAccess(TokenSARights_strs, countTokenSARights, 
				SpecialAccessRights, SpecialAR);
			break;
		};
		if(m_Package.ObjName=="Process"){
			setInfoAccess(ProcessSARights_strs, countProcessSARights, 
				SpecialAccessRights, SpecialAR);
			break;
		};
		if(m_Package.ObjName=="Thread"){
			setInfoAccess(ThreadSARights_strs, countThreadSARights, 
				SpecialAccessRights, SpecialAR);
			break;
		};
		if(m_Package.ObjName=="Job"){
			setInfoAccess(JobSARights_strs, countJobSARights, 
				SpecialAccessRights, SpecialAR);
			break;
		};
		if(m_Package.ObjName=="Desktop"){
			setInfoAccess(DesktopSARights_strs, countDesktopSARights, 
				SpecialAccessRights, SpecialAR);
			break;
		};
		if(m_Package.ObjName=="Event"){
			setInfoAccess(EventSARights_strs, countEventSARights, 
				SpecialAccessRights, SpecialAR);
			break;
		};
		if(m_Package.ObjName=="File"){
			setInfoAccess(FileSARights_strs, countFileSARights, 
				SpecialAccessRights, SpecialAR);
			break;
		};
		if(m_Package.ObjName=="Key"){
			setInfoAccess(KeySARights_strs, countKeySARights, 
				SpecialAccessRights, SpecialAR);
			break;
		};
		if(m_Package.ObjName=="Semaphore"){
			setInfoAccess(SemaphoreSARights_strs, countSemaphoreSARights, 
				SpecialAccessRights, SpecialAR);
			break;
		};
		if(m_Package.ObjName=="Timer"){
			setInfoAccess(TimerSARights_strs, countTimerSARights, 
				SpecialAccessRights, SpecialAR);
			break;
		};
		//WinStaSARights
		if(m_Package.ObjName=="WindowStation"){
			setInfoAccess(WinStaSARights_strs, countWinStaSARights, 
				SpecialAccessRights, SpecialAR);
			break;
		};
		m_Package.ObjName="undefined"; break;

	}

//		!3.получение базовых прав (BaseARights):

	setInfoAccess(BaseARights_strs, countBaseARights, 
		StandardAccessRights, BasicAR);

	m_Package.id = m_ProcessId;
	m_Package.Handle = m_Handle;

	return m_Package;
}

//		!Выборка информации и сохранение
//		!ArrayAcc - массив элементов
//		!size_el - счетчик элементов
//		!val - искомое значение
//		!type - тип доспупа

void CWinObj::setInfoAccess(void* ArrayAcc, size_t size_el, int val, TYPEACCESS type){

	stBaseARights* pSt = static_cast<stBaseARights*>(ArrayAcc);

	for(int i=0; i<size_el; i++)
	{
		if (pSt[i].val	== val){ 
			switch(type){
//		!получение имени из массива st_*******. (прим: собственно это все зачем так мудрил)
				case SpecialAR:
					m_Package.Special = pSt[i].text;
				break;
				case StandardAR:
					m_Package.Sandart = pSt[i].text;
				break;
				case BasicAR:
					m_Package.Base = pSt[i].text;
				break;
			}
		}
	}	
}