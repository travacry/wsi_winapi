/********************************************************
	* File: windowstation.h
	* Discription: The map special+full right's obj: WinSta
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

enumeration_begin(WinStaSARights)
declare_member(WINSTA_ENUMDESKTOPS) member_value(0x0001L) delimiter
declare_member(WINSTA_READATTRIBUTES) member_value(0x0002L) delimiter
declare_member(WINSTA_ACCESSCLIPBOARD) member_value(0x0004L) delimiter
declare_member(WINSTA_CREATEDESKTOP) member_value(0x0008L) delimiter
declare_member(WINSTA_WRITEATTRIBUTES) member_value(0x0010L) delimiter
declare_member(WINSTA_ACCESSGLOBALATOMS) member_value(0x0020L) delimiter
declare_member(WINSTA_EXITWINDOWS) member_value(0x0040L) delimiter
declare_member(WINSTA_ENUMERATE) member_value(0x0100L) delimiter
declare_member(WINSTA_READSCREEN) member_value(0x0200L)
enumeration_end;
//to enumeration predetermined indicators
enumeration_begin(FullWinStaSARights)
declare_member(WINSTA_ALL_ACCESS) member_value(WINSTA_ENUMDESKTOPS|WINSTA_READATTRIBUTES|
WINSTA_ACCESSCLIPBOARD|WINSTA_CREATEDESKTOP|
WINSTA_WRITEATTRIBUTES|WINSTA_ACCESSGLOBALATOMS|
WINSTA_EXITWINDOWS|WINSTA_ENUMERATE|WINSTA_READSCREEN)
enumeration_end;

#include "../CreateMassArray/enum_helper_post.h"