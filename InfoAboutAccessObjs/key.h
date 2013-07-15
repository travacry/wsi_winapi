/********************************************************
	* File: key.h
	* Discription: The map special+full right's obj: Key
	* Created: 28.03.2013
	* Copyright: (C) 2013 AK
	* Author: Alexander Kuznetsov
	* Email: prog.alex.k@gmail.com
	* Lg comment's : RU
********************************************************/

//		!"SA 2x"

#include "StandartAccess.h"
#include "StandartAccess.h"

#include "../CreateMassArray/switch_enum_mass.h"
#include "../CreateMassArray/enum_helper_pre.h"

enumeration_begin(KeySARights)
declare_member(KEY_QUERY_VALUE) member_value(0x0001) delimiter
declare_member(KEY_SET_VALUE) member_value(0x0002) delimiter
declare_member(KEY_CREATE_SUB_KEY) member_value(0x0004) delimiter
declare_member(KEY_ENUMERATE_SUB_KEYS) member_value(0x0008) delimiter
declare_member(KEY_NOTIFY) member_value(0x0010) delimiter
declare_member(KEY_CREATE_LINK) member_value(0x0020) delimiter
declare_member(KEY_WOW64_32KEY) member_value(0x0200) delimiter
declare_member(KEY_WOW64_64KEY) member_value(0x0100) delimiter
declare_member(KEY_WOW64_RES) member_value(0x0300)
enumeration_end;

enumeration_begin(FullKeySARights)
declare_member(KEY_READ) member_value((STANDARD_RIGHTS_READ|KEY_QUERY_VALUE|KEY_ENUMERATE_SUB_KEYS|KEY_NOTIFY)&(~SYNCHRONIZE)) delimiter
declare_member(KEY_WRITE) member_value((STANDARD_RIGHTS_WRITE|KEY_SET_VALUE|KEY_CREATE_SUB_KEY)&(~SYNCHRONIZE)) delimiter
declare_member(KEY_EXECUTE) member_value((KEY_READ)&(~SYNCHRONIZE)) delimiter
declare_member(KEY_ALL_ACCESS) member_value((STANDARD_RIGHTS_ALL|KEY_QUERY_VALUE|KEY_SET_VALUE|KEY_CREATE_SUB_KEY|KEY_ENUMERATE_SUB_KEYS|KEY_NOTIFY|KEY_CREATE_LINK)&(~SYNCHRONIZE))
enumeration_end;

#include "../CreateMassArray/enum_helper_post.h"