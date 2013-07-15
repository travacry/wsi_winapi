/********************************************************
	* File: BaseAccess.h
	* Discription: The map base right's
	* Created: 28.03.2013
	* Copyright: (C) 2013 AK
	* Author: Alexander Kuznetsov
	* Email: prog.alex.k@gmail.com
	* Lg comment's : RU
********************************************************/

//@это набор стандартных и специальных прав для обьекта.
//@в системе их 4 типа: - read
//@						- write
//@						- execute
//@						- all
//@для каждого обьекта смысл права разный! @Рихтер 339.

#ifndef BASEACCESS_H
#define BASEACCESS_H

#undef create_enum

//		!begin create array BaseARights;
#define create_mass
#include <iostream>
#include "../CreateMassArray/enum_helper_pre.h"
enumeration_begin(BaseARights)
	declare_member(GENERIC_READ) member_value(0x80000000L) delimiter
	declare_member(GENERIC_WRITE) member_value(0x40000000L) delimiter
	declare_member(GENERIC_EXECUTE) member_value(0x20000000L) delimiter
	declare_member(GENERIC_ALL) member_value(0x10000000L)
enumeration_end;
//		!end create array BaseARights;

//		!clear;
#include "../CreateMassArray/enum_helper_post.h"
#undef create_mass

#endif BASEACCESS_H