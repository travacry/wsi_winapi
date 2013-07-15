/********************************************************
	* File: CWinInfo.h
	* Discription: Windows version ?
	* Created: 28.03.2013
	* Copyright: (C) 2013 AK
	* Author: Alexander Kuznetsov
	* Email: prog.alex.k@gmail.com
	* Lg comment's : RU
********************************************************/

//		!win version 

//@����� ������������ ������� ��� .cpp �� ��� �������,
//@��� ������������ ������� � ��� ������������� ����������� .cpp -
//@��������� ��������� ������ � ������������������ emum || array

//******************************************************

#ifndef CWININFO_H
#define CWININFO_H

	#include "general_model.h"
	using namespace std;

	class CWinInfo
	{

		DWORD m_dwVersion;			//	������ WINDOWS � ����� ������
		DWORD m_dwMajorVersion;		//	������� ������ WINDOWS
		DWORD m_dwMinorVersion;		//	������� ������ WINDOWS
		DWORD m_dwBuild;			//	����� �����		
		VERWIN m_Ver;				//	������ WINDOWS

	public:

		CWinInfo();					//	�������� ���������� �� ���� ����������*
		VERWIN getVersion() const;	//	id version Windows

	private:

		void CheckVersion();		//	������������������ ���������*

	};

#endif CWININFO_H

//******************************************************

CWinInfo::CWinInfo():m_dwVersion(0), m_dwMajorVersion(0),
	m_dwMinorVersion(0),m_dwBuild(0)
{

	CheckVersion();

};

void CWinInfo::CheckVersion()
{

    m_dwVersion = GetVersion();

    // Get the Windows version.
    m_dwMajorVersion = (DWORD)(LOBYTE(LOWORD(m_dwVersion)));
    m_dwMinorVersion = (DWORD)(HIBYTE(LOWORD(m_dwVersion)));

    // Get the build number.
    if (m_dwVersion < 0x80000000) m_dwBuild = (DWORD)(HIWORD(m_dwVersion));

    // Select version windows
	switch (m_dwMajorVersion*10 + m_dwMinorVersion)
	{
		case 51 : m_Ver = WinXP;	break;
		case 50 : m_Ver = Win2000;	break;
		case 40 : m_Ver = WinNT;	break;
	}

}

VERWIN CWinInfo::getVersion() const
{
	return m_Ver;
}