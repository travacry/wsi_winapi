/********************************************************
	* File: token.h
	* Discription: The map special+full right's obj: Token
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

enumeration_begin(TokenSARights)
declare_member(TOKEN_ASSIGN_PRIMARY) member_value(0x0001) delimiter
declare_member(TOKEN_DUPLICATE) member_value(0x0002) delimiter
declare_member(TOKEN_IMPERSONATE) member_value(0x0004) delimiter
declare_member(TOKEN_QUERY) member_value(0x0008) delimiter
declare_member(TOKEN_QUERY_SOURCE) member_value(0x0010) delimiter
declare_member(TOKEN_ADJUST_PRIVILEGES) member_value(0x0020) delimiter
declare_member(TOKEN_ADJUST_GROUPS) member_value(0x0040) delimiter
declare_member(TOKEN_ADJUST_DEFAULT) member_value(0x0080) delimiter
declare_member(TOKEN_ADJUST_SESSIONID) member_value(0x0100) delimiter
enumeration_end;
enumeration_begin(FullTokenSARights)
declare_member(TOKEN_ALL_ACCESS_P) member_value(STANDARD_RIGHTS_REQUIRED|TOKEN_ASSIGN_PRIMARY|TOKEN_DUPLICATE|TOKEN_IMPERSONATE|TOKEN_QUERY|TOKEN_QUERY_SOURCE|TOKEN_ADJUST_PRIVILEGES|TOKEN_ADJUST_GROUPS|TOKEN_ADJUST_DEFAULT) delimiter
declare_member(TOKEN_READ) member_value(STANDARD_RIGHTS_READ|TOKEN_QUERY) delimiter
declare_member(TOKEN_WRITE) member_value(STANDARD_RIGHTS_WRITE|TOKEN_ADJUST_PRIVILEGES|TOKEN_ADJUST_GROUPS|TOKEN_ADJUST_DEFAULT) delimiter
declare_member(TOKEN_EXECUTE) member_value(STANDARD_RIGHTS_EXECUTE)
enumeration_end;
#include "../CreateMassArray/enum_helper_post.h"