/********************************************************
	* File: desktop.h
	* Discription: The map special right's obj: desktop
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

enumeration_begin(DesktopSARights)
declare_member(DESKTOP_READOBJECTS) member_value(0x0001L) delimiter
declare_member(DESKTOP_CREATEWINDOW) member_value(0x0002L) delimiter
declare_member(DESKTOP_CREATEMENU) member_value(0x0004L) delimiter
declare_member(DESKTOP_HOOKCONTROL) member_value(0x0008L) delimiter
declare_member(DESKTOP_JOURNALRECORD) member_value(0x0010L) delimiter
declare_member(DESKTOP_JOURNALPLAYBACK) member_value(0x0020L) delimiter
declare_member(DESKTOP_ENUMERATE) member_value(0x0040L) delimiter
declare_member(DESKTOP_WRITEOBJECTS) member_value(0x0080L) delimiter
declare_member(DESKTOP_SWITCHDESKTOP) member_value(0x0100L)
enumeration_end;

#include "../CreateMassArray/enum_helper_post.h"
#undef create_mass