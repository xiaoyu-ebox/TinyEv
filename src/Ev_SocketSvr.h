/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-2-18
 * Version     : v0.1
 * Description : Ev_SocketSvr header file
 *******************************************************************/
#ifndef __EV_SOCKETSVR_H__
#define __EV_SOCKETSVR_H__

/*----------------------------Head file----------------------------*/
#include "Ev_SocketCli.h"

/*----------------------------macro file---------------------------*/

/*----------------------------type define--------------------------*/

/*-----------------------------------------------------------------*/
class Ev_SocketSvr : public Ev_Handle
{
public: // api
	explicit Ev_SocketSvr(socket_type_t type = SOCKET_TCP_SERVER);
	virtual ~Ev_SocketSvr();

	ev_error create_host_service(const char *addr, uint32 args = 0);

public: // var

protected: // api
	virtual ev_error on_ev_accept_malloc_cli(Ev_SocketCli **socket) = 0;
	virtual ev_error on_ev_accept_buttom(Ev_SocketCli *socket) = 0;

protected: // var

private: // api
	ev_error listen_client_connect();
	ev_error on_ev_accept();

	friend void ev_vector_listen_cb(struct ev_loop *loop, void *io, int revents);
private: // var
	socket_type_t m_type;
	socket_addr_t m_addr;
};


#endif // __EV_SOCKETSVR_H__

