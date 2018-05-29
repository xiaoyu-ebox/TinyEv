/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-2-18
 * Version     : v0.1
 * Description : EV_PrivateData header file
 *******************************************************************/
#ifndef __EV_PRIVATEDATA_H__
#define __EV_PRIVATEDATA_H__

/*----------------------------Head file----------------------------*/
#include "Ev_Base_Include.h"

/*----------------------------macro file---------------------------*/

/*----------------------------type define--------------------------*/

/*-----------------------------------------------------------------*/
class Ev_Vector;
class EV_PrivateData
{
public: // api
	EV_PrivateData() : m_priv(0) {}
	virtual ~EV_PrivateData() {}

public: // var

protected: // api

protected: // var
	long int m_priv;
	
private: // api
	friend Ev_Vector;

private: // var

};


#endif // __EV_PRIVATEDATA_H__

