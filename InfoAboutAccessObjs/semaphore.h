/********************************************************
	* File: semaphore.h
	* Discription: The map special right's obj: Semaphore
	* Created: 28.03.2013
	* Copyright: (C) 2013 AK
	* Author: Alexander Kuznetsov
	* Email: prog.alex.k@gmail.com
	* Lg comment's : RU
********************************************************/

#undef create_enum
#define create_mass
#include "../CreateMassArray/enum_helper_pre.h"

enumeration_begin(SemaphoreSARights)
declare_member(SEMAPHORE_MUTANT_QUERY_STATE) member_value(0x0001) delimiter
declare_member(SEMAPHORE_MODIFY_STATE) member_value(0x0002)
enumeration_end;

#include "../CreateMassArray/enum_helper_post.h"
#undef create_mass#undef create_mass