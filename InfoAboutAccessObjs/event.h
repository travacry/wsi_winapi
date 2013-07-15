/********************************************************
	* File: event.h
	* Discription: The map special right's obj: Event
	* Created: 28.03.2013
	* Copyright: (C) 2013 AK
	* Author: Alexander Kuznetsov
	* Email: prog.alex.k@gmail.com
	* Lg comment's : RU
********************************************************/

//		!"SA 2x"

#include "StandartAccess.h"
#include "StandartAccess.h"

#undef create_enum
#define create_mass
#include "../CreateMassArray/enum_helper_pre.h"

enumeration_begin(EventSARights)
declare_member(EVENT_MUTANT_QUERY_STATE) member_value(0x0001) delimiter
declare_member(EVENT_MODIFY_STATE) member_value(0x0002) delimiter
declare_member(EVENT_ALL_ACCESS) member_value(STANDARD_RIGHTS_REQUIRED|SYNCHRONIZE|0x3)
enumeration_end;

#include "../CreateMassArray/enum_helper_post.h"
#undef create_mass