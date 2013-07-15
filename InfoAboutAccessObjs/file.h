/********************************************************
	* File: file.h
	* Discription: The map special right's obj: File
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

enumeration_begin(FileSARights)
declare_member(FILE_READ_DATA) member_value(0x0001) delimiter
declare_member(FILE_ADD_FILE) member_value(0x0002) delimiter
declare_member(FILE_APPEND_DATA) member_value(0x0004) delimiter
declare_member(FILE_READ_EA) member_value(0x0008) delimiter
declare_member(FILE_WRITE_EA) member_value(0x0010) delimiter
declare_member(FILE_EXECUTE) member_value(0x0020) delimiter
declare_member(FILE_DELETE_CHILD) member_value(0x0040) delimiter
declare_member(FILE_READ_ATTRIBUTES) member_value(0x0080) delimiter
declare_member(FILE_WRITE_ATTRIBUTES) member_value(0x0100) delimiter
declare_member(FILE_ALL_ACCESS) member_value(STANDARD_RIGHTS_REQUIRED|SYNCHRONIZE|0x1FF)
enumeration_end;

#include "../CreateMassArray/enum_helper_post.h"
#undef create_mass