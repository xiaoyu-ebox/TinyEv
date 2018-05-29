/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2018-5-3
 * Version     : v0.1
 * Description : 
 *******************************************************************/
/*----------------------------Head file----------------------------*/
#include "Ev_KeepLive.h"

/*----------------------------macro file---------------------------*/

/*----------------------------type define--------------------------*/

/*----------------------------var define---------------------------*/

/*-----------------------------------------------------------------*/
Ev_KeepLive::Ev_KeepLive() :
	keeplive(true)
{

}

Ev_KeepLive::~Ev_KeepLive()
{

}

bool Ev_KeepLive::check_keeplive()
{
	bool tmp_st = keeplive;
	keeplive = false;

	return tmp_st;
}

void Ev_KeepLive::set_keeplive()
{
	keeplive = true;
}

bool Ev_KeepLive::get_keeplive()
{
	return keeplive;
}

