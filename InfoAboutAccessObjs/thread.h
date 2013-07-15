/********************************************************
	* File: thread.h
	* Discription: The map special right's obj: Thread
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

enumeration_begin(ThreadSARights)
declare_member(THREAD_TERMINATE) member_value(0x0001) delimiter
declare_member(THREAD_SUSPEND_RESUME) member_value(0x0002) delimiter
declare_member(THREAD_GET_CONTEXT) member_value(0x0008) delimiter
declare_member(THREAD_SET_CONTEXT) member_value(0x0010) delimiter
declare_member(THREAD_QUERY_INFORMATION) member_value(0x0040) delimiter
declare_member(THREAD_SET_INFORMATION) member_value(0x0020) delimiter
declare_member(THREAD_SET_THREAD_TOKEN) member_value(0x0080) delimiter
declare_member(THREAD_IMPERSONATE) member_value(0x0100) delimiter
declare_member(THREAD_DIRECT_IMPERSONATION) member_value(0x0200) delimiter
declare_member(THREAD_SET_LIMITED_INFORMATION) member_value(0x0400) delimiter	//winnt
declare_member(THREAD_QUERY_LIMITED_INFORMATION) member_value(0x0800) delimiter	//winnt
declare_member(THREAD_ALL_ACCESS) member_value(STANDARD_RIGHTS_REQUIRED|SYNCHRONIZE|0xFFFF)
enumeration_end;

#include "../CreateMassArray/enum_helper_post.h"
#undef create_mass
