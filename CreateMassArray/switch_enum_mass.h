/********************************************************
	* File: switch_enum_mass.h
	* Discription: This macro's is "switch - enum/array", 
	* The switch between the creation of such an element as : enum or array, enum -> array
	* Created: 28.03.2013
	* Copyright: (C) 2013 AK
	* Author: Alexander Kuznetsov
	* Email: prog.alex.k@gmail.com
	* Lg comment's : RU
********************************************************/

//		!@2 �������� -> create Array 

#ifdef create_enum
	#define create_mass
#endif

//		!@1 �������� -> create Enum

#ifndef create_enum
	#undef create_mass
	#define create_enum
#endif

//		!@end

#ifdef create_mass
	#undef create_enum
#endif


//		!@��������: ���� ���������� create_enum ��� create_mass ��� ������� - � ������ ������������ ���� ������ �
//		!@�� ������� �� - ����� "��������".

