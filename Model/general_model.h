/********************************************************
	* File: general_model.h
	* Discription: Initialization of the structure and macros for the basic classes.
	* Created: 28.03.2013
	* Copyright: (C) 2013 AK
	* Author: Alexander Kuznetsov
	* Email: prog.alex.k@gmail.com
	* Lg comment's : RU
********************************************************/

#ifndef GEN_MODEL_H
#define GEN_MODEL_H

//		!id's + array's + map's win(xp,2000,nt)
#include "head_model.h"

#include <string>
#include <list>
#include <iostream>

//		!получить список открытых процессов
#define SystemHandleInformation 16

//		!базовая структура для всех спецификаторов доступа
#ifndef STBASE

	typedef struct stBase_ 
	{ 

		std::string text; 
		int val; 

	} STBASE;

#endif

#include <windows.h>
#include <WTypes.h>
//#include <winnt.h>
//#include <WinDef.h>

typedef NTSTATUS (NTAPI *_NtQuerySystemInformation)
(
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

//		!пакет данных

#ifndef PACKAGE

	typedef struct stPACKAGE
	{

		std::string	ObjName;
		std::string Special;
		std::string Sandart;
		std::string Base;	
		ULONG 		id;
		USHORT 		Handle;

	} PACKAGE;

#endif

//		!идентификатор версии windows

#ifndef VERWIN

	enum VERWIN { WinXP=51, Win2000=50, WinNT=40 };

#endif

//		!идентификаторы правил доступа

#ifndef TYPEACCESS

	enum TYPEACCESS 
	{	

		SpecialAR,
		StandardAR,
		BasicAR 

	};

#endif

//		!макросы для разбора маски доступа
//		!1111 (28-31) . 111 (25-27) . 1 (24) . 1 (23) 
//		!. 111 1111 (22-16) . 1111 1111 1111 1111 (0-15)

//		!23 доступ к системному списку контроля доступа.
//		!GrantedAccess

#define SPECIAL_GM(AM)		((DWORD)((AM) & 0x0000ffff)) //0-15
#define STANDART_GM(AM)		((DWORD)((AM) & 0x007f0000)) //22-16
#define AUDIT_GM(AM)		((DWORD)((AM) & 0x00800000)) //23
#define MAXALLOWABLE_GM(AM)	((DWORD)((AM) & 0x01000000)) //24
#define RESERVE_GM(AM)		((DWORD)((AM) & 0x0e000000)) //25-27
#define BASE_GM(AM)			((DWORD)((AM) & 0xf0000000)) //28-31

//		!определение ошибки 0,< = false; > = true;

#define NT_SUCCESS(inpNumber) ((inpNumber) >= 0)

#endif GEN_MODEL_H
