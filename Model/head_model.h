/********************************************************
	* File: head_model.h
	* Discription: #Include all the windows obj's and windows map's. 
	* Created: 28.03.2013
	* Copyright: (C) 2013 AK
	* Author: Alexander Kuznetsov
	* Email: prog.alex.k@gmail.com
	* Lg comment's : RU
********************************************************/

#ifndef HEAD_DATA_H
#define HEAD_DATA_H

//		!only array
#include "..\InfoAboutAccessObjs\BaseAccess.h"

//		!id's + array's
#include "..\InfoAboutAccessObjs\StandartAccess.h"
#include "..\InfoAboutAccessObjs\StandartAccess.h"

//begin RIGHT obj's:

//			!only array's

#include "..\InfoAboutAccessObjs\desktop.h"
#include "..\InfoAboutAccessObjs\directory.h"
#include "..\InfoAboutAccessObjs\event.h"
#include "..\InfoAboutAccessObjs\file.h"
#include "..\InfoAboutAccessObjs\job.h"
#include "..\InfoAboutAccessObjs\process.h"
#include "..\InfoAboutAccessObjs\thread.h"
#include "..\InfoAboutAccessObjs\timer.h"
#include "..\InfoAboutAccessObjs\semaphore.h"

//			!"SA 2x"

#include "..\InfoAboutAccessObjs\key.h"
#include "..\InfoAboutAccessObjs\key.h"
#include "..\InfoAboutAccessObjs\token.h"
#include "..\InfoAboutAccessObjs\token.h"
#include "..\InfoAboutAccessObjs\windowstation.h"
#include "..\InfoAboutAccessObjs\windowstation.h"

//end RIGHT obj's:

//		!Map's obj's:

#include "..\ObjsMap\WinNT.h"
#include "..\ObjsMap\Win2000.h"
#include "..\ObjsMap\WinXP.h"

#endif HEAD_DATA_H