/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2018-5-3
 * Version     : v0.1
 * Description : Ev_KeepLive header file
 *******************************************************************/
#ifndef __EV_KEEPLIVE_H__
#define __EV_KEEPLIVE_H__

/*----------------------------Head file----------------------------*/
#include "Ev_Base_Include.h"

/*----------------------------macro file---------------------------*/

/*----------------------------type define--------------------------*/

/*-----------------------------------------------------------------*/
class Ev_KeepLive
{
public: // api
	Ev_KeepLive();
	virtual ~Ev_KeepLive();

	virtual bool check_keeplive();
	virtual void set_keeplive();
	virtual bool get_keeplive();

public: // var

protected: // api

protected: // var

private: // api

private: // var
	bool keeplive;
};


#endif // __EV_KEEPLIVE_H__

