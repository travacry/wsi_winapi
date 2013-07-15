/********************************************************
	* File: enum_helper_pre.h
	* Discription: This macro's create the data type : enum and array
	* Created: 28.03.2013
	* Copyright: (C) 2013 AK
	* Author: Alexander Kuznetsov
	* Email: prog.alex.k@gmail.com
	* Lg comment's : RU
********************************************************/

//@Note , такой макрос на текущий момент minGW например не поддержвивает
//@Note , а препроцессор в mvs2010 справляется на ура.


//		!_TEXT("text") => L"text"

#define _TEXT(arg) L##arg

//		!,
#ifndef delimiter
	#define delimiter ,
#endif

//		!@Enum TEST	
#ifdef create_enum 
//		!enum TEST {
	#ifndef enumeration_begin
		#define enumeration_begin(arg) enum arg {
	#endif
//		!enum TEST { ARG
	#ifndef declare_member
		#define declare_member(arg) arg
	#endif
//		!enum TEST { ARG = VAL
	#ifndef member_value
		#define member_value(arg) = arg
	#endif
//		!enum TEST { ARG = VAL };
	#ifndef enumeration_end
		#define enumeration_end };
	#endif
#endif

//		!@Array TEST
#ifdef create_mass
	#ifndef enumeration_begin
//		!struct stTEST {	std::string text; 
//							int val;	};
//		!stTEST TEST_strs[] = {
		#define enumeration_begin(arg) struct	st##arg { std::string text; int val; }; \
												st##arg arg##_strs[] = {
	#endif
//		!stTEST TEST_strs[] = { { "text",
	#ifndef declare_member
		#define declare_member(arg) { std::string(#arg), 
	#endif
//		!stTEST TEST_strs[] = { { "text", val }
	#ifndef member_value
		#define member_value(arg) arg }
	#endif
//		!stTEST TEST_strs[] = { { "text", val } };
	#ifndef enumeration_end
		#define enumeration_end };
	#endif
#endif

