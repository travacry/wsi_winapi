/********************************************************
	* File: CModel.h
	* Discription: Use model.dll: get DATA -> QStandardItemModel for View.
	* Created: 28.03.2013
	* Copyright: (C) 2013 AK
	* Author: Alexander Kuznetsov
	* Email: prog.alex.k@gmail.com
	* Lg comment's : RU
********************************************************/

#ifndef CMODEL_H
#define CMODEL_H

#include <windows.h>
#include <WTypes.h>

#include <list>

#include <QLibrary>
#include <QStandardItem>
#include <QStandardItemModel>

typedef struct stBase_
{

    std::string text;
    int val;

} STBASE;

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

enum VERWIN 
{	
	WinXP=51, 
	Win2000=50, 
	WinNT=40 
};

enum TYPEACCESS 
{ 
	SpecialAR,
	StandardAR,
	BasicAR 
};

using namespace std;	//in PACKEGE string

//prototypes:
typedef void(*getListCurrObjs)(list<PACKAGE>&);
typedef void(*getListMapObjsWin)(list<STBASE>&, VERWIN);
typedef void(*getListAccess)(list<STBASE>& data, TYPEACCESS type, string& objType);

/********************************************************/

	class CModel
	{

		list<PACKAGE>	m_pack_data;
		list<STBASE>	m_base_data;
		VERWIN			m_version;
		TYPEACCESS		m_type_acc;
		string			m_type_name_obj;
	
		getListCurrObjs 	SetListCurrObjs;
		getListMapObjsWin 	SetListMapObjsWin;
		getListAccess 		SetListMapAccess;
	
	public:

		QStandardItemModel*	m_pSim;

		CModel();
	
		QStandardItemModel* getStandartModel();

		void genCurrObjs();
		void genMapWin(VERWIN& ver);
		void genAccessTab(TYPEACCESS type, string& objType);

	};

/********************************************************/

#endif CMODEL_H