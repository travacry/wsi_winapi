/********************************************************
	* File: file.h
	* Discription: The map special right's obj: Job
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

enumeration_begin(JobSARights)
declare_member(JOB_OBJECT_ASSIGN_PROCESS) member_value(0x0001) delimiter
declare_member(JOB_OBJECT_SET_ATTRIBUTES) member_value(0x0002) delimiter
declare_member(JOB_OBJECT_QUERY) member_value(0x0004) delimiter
declare_member(JOB_OBJECT_TERMINATE) member_value(0x0008) delimiter
declare_member(JOB_OBJECT_SET_SECURITY_ATTRIBUTES) member_value(0x0010) delimiter
declare_member(JOB_OBJECT_ALL_ACCESS) member_value(STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0x1F)
enumeration_end;
#include "../CreateMassArray/enum_helper_post.h"
#undef create_mass