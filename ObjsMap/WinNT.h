/********************************************************
	* File: WinNT.h
	* Discription: Map object's WinNT.
	* Created: 28.03.2013
	* Copyright: (C) 2013 AK
	* Author: Alexander Kuznetsov
	* Email: prog.alex.k@gmail.com
	* Lg comment's : RU
********************************************************/

#ifndef WINNT_H
#define WINNT_H

#undef create_enum
#define create_mass
#include "../CreateMassArray/enum_helper_pre.h"

enumeration_begin(WinNT)
declare_member(Type) 					member_value(1) delimiter
declare_member(Directory) 				member_value(2) delimiter
declare_member(SymbolicLink) 			member_value(3) delimiter
declare_member(Token) 					member_value(4) delimiter
declare_member(Process) 				member_value(5) delimiter
declare_member(Thread) 					member_value(6) delimiter
declare_member(Event) 					member_value(7) delimiter
declare_member(EventPair) 				member_value(8) delimiter //Represents an event pair, an object consisting of two events, high and low.
declare_member(Mutant) 					member_value(9) delimiter //Mutants control access to code to make sure that only one thread is executing a line of code at a time. Mutants are generally used in user-mode but can also be used in kernel mode.
declare_member(Semaphore) 				member_value(10) delimiter
declare_member(Timer) 					member_value(11) delimiter
declare_member(Profile) 				member_value(12) delimiter
declare_member(WindowStation) 			member_value(13) delimiter
declare_member(Desktop) 				member_value(14) delimiter
declare_member(Section) 				member_value(15) delimiter //Sections represent areas of memory that can be viewed as a contiguous sequence of addresses.
declare_member(Key) 					member_value(16) delimiter
declare_member(Port) 					member_value(17) delimiter
declare_member(Adapter) 				member_value(18) delimiter
declare_member(Controller) 				member_value(19) delimiter
declare_member(Device) 					member_value(20) delimiter
declare_member(Driver) 					member_value(21) delimiter
declare_member(IoCompletion) 			member_value(22) delimiter
declare_member(File) 					member_value(23)
enumeration_end;

#undef create_mass
#endif