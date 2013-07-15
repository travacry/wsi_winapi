/********************************************************
	* File: StandartAccess.h
	* Discription: The map standart right's (enum eq #define_identifier_val + array)
	* Created: 28.03.2013
	* Copyright: (C) 2013 AK
	* Author: Alexander Kuznetsov
	* Email: prog.alex.k@gmail.com
	* Lg comment's : RU
********************************************************/

//@����������� �� ���� ����� �������� �������
//@����:	- �������� �������
//@			- ������ ���������� � ������

//		!���������� ������ 2 ���� 
//		!����� �� ���� "��������" =>

#if STANDART_ACC == 2
	#undef STANDART_ACC
	#define STANDART_ACC 3
#endif
#if STANDART_ACC == 1
	#undef STANDART_ACC
	#define STANDART_ACC 2
#endif

//		!�� 1 �������� ������������ iostream

#ifndef STANDART_ACC
	#define STANDART_ACC 1
	#include <iostream>
#endif

//		!enum + array

//		!� ��������� ������������� !!! - 1 ��������
//		!ARG = VAL
//		!����: #define DELETE = 0x00010000L; - in header's Windows
//		!����: EQ = > enum TEST { DELETE = 0x00010000L, }; 
//		!������� ������ ����� ������������ ��������� "SA 2x"

#if STANDART_ACC<3

	#include "../CreateMassArray/switch_enum_mass.h"
	#include "../CreateMassArray/enum_helper_pre.h"

	enumeration_begin(StandartARights)
	declare_member(DELETE) member_value(0x00010000L) delimiter
	declare_member(READ_CONTROL) member_value(0x00020000L) delimiter
	declare_member(WRITE_DAC) member_value(0x00040000L) delimiter
	declare_member(WRITE_OWNER) member_value(0x00080000L) delimiter
	declare_member(SYNCHRONIZE) member_value(0x00100000L) delimiter
	//->token
	declare_member(STANDARD_RIGHTS_REQUIRED) member_value(0x000F0000L) delimiter
	declare_member(STANDARD_RIGHTS_READ) member_value(0x00020000L) delimiter
	declare_member(STANDARD_RIGHTS_WRITE) member_value(0x00020000L) delimiter
	//<-token
	declare_member(STANDARD_RIGHTS_EXECUTE) member_value(0x00020000L) delimiter
	declare_member(STANDARD_RIGHTS_ALL) member_value(0x001F0000L) delimiter
	declare_member(SPECIFIC_RIGHTS_ALL) member_value(0x0000FFFFL)
	enumeration_end;

	#include "../CreateMassArray/enum_helper_post.h"

#endif
