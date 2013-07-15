/********************************************************
	* File: timer.h
	* Discription: The map special right's obj: Timer
	* Created: 28.03.2013
	* Copyright: (C) 2013 AK
	* Author: Alexander Kuznetsov
	* Email: prog.alex.k@gmail.com
	* Lg comment's : RU
********************************************************/

#undef create_enum
#define create_mass
#include "../CreateMassArray/enum_helper_pre.h"

enumeration_begin(TimerSARights)
declare_member(TIMER_QUERY_STATE) member_value(0x0001) delimiter
declare_member(TIMER_MODIFY_STATE) member_value(0x0002)
enumeration_end;

#include "../CreateMassArray/enum_helper_post.h"
#undef create_mass