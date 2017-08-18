/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-3-19
 * Version     : v0.1
 * Description : Ev_IPCSvrHandle header file
 *******************************************************************/
#ifndef __EV_IPCSVRHANDLE_H__
#define __EV_IPCSVRHANDLE_H__

/*----------------------------Head file----------------------------*/
#include "Ev_IPCCli.h"

/*----------------------------macro file---------------------------*/

/*----------------------------type define--------------------------*/

/*-----------------------------------------------------------------*/
class Ev_IPCSvrHandle : public Ev_SocketCli
{
public: // api
	Ev_IPCSvrHandle();
	~Ev_IPCSvrHandle();


public: // var

protected: // api
	void on_ev_connect(ev_error ret) {}
	ev_error on_ev_stream_read(uint32 size);
	ev_error on_ev_error();
	ev_error on_ev_write() {return EV_SUCCESS;}

protected: // var

private: // api

private: // var
	uint8 *m_recv_buf;
};


#endif // __EV_IPCSVRHANDLE_H__

