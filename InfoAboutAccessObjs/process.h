/********************************************************
	* File: process.h
	* Discription: The map special right's obj: Process
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

enumeration_begin(ProcessSARights)
declare_member(PROCESS_TERMINATE) member_value(0x0001) delimiter
declare_member(PROCESS_CREATE_THREAD) member_value(0x0002) delimiter
declare_member(PROCESS_SET_SESSIONID) member_value(0x0004) delimiter
declare_member(PROCESS_VM_OPERATION) member_value(0x0008) delimiter
declare_member(PROCESS_VM_READ) member_value(0x0010) delimiter
declare_member(PROCESS_VM_WRITE) member_value(0x0020) delimiter
declare_member(PROCESS_DUP_HANDLE) member_value(0x0040) delimiter
declare_member(PROCESS_CREATE_PROCESS) member_value(0x0080) delimiter
declare_member(PROCESS_SET_QUOTA) member_value(0x0100) delimiter
declare_member(PROCESS_SET_INFORMATION) member_value(0x0200) delimiter
declare_member(PROCESS_QUERY_INFORMATION) member_value(0x0400) delimiter
declare_member(PROCESS_SUSPEND_RESUME) member_value(0x0800) delimiter
declare_member(PROCESS_QUERY_LIMITED_INFORMATION) member_value(0x1000) delimiter
declare_member(PROCESS_ALL_ACCESS) member_value(STANDARD_RIGHTS_REQUIRED|SYNCHRONIZE|0xFFFF)
enumeration_end;

#include "../CreateMassArray/enum_helper_post.h"
#undef create_mass