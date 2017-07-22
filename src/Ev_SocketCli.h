/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-2-18
 * Version     : v0.1
 * Description : Ev_SocketCli header file
 *******************************************************************/
#ifndef __EV_SOCKETCLI_H__
#define __EV_SOCKETCLI_H__

/*----------------------------Head file----------------------------*/
#include "Ev_Stream.h"

#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <linux/netlink.h>
#include <arpa/inet.h>

/*----------------------------macro file---------------------------*/

/*----------------------------type define--------------------------*/
typedef enum {
	SOCKET_SYS_BUS_CLIENT,
	SOCKET_SYS_BUS_SERVER,
	SOCKET_TCP_CLIENT,
	SOCKET_TCP_SERVER,
	SOCKET_NETLINK_CLIENT
} socket_type_t;

typedef union {
	struct sockaddr_un un;
	struct sockaddr_in in;
	struct sockaddr_nl nl;
} socket_addr_t;

/*-----------------------------------------------------------------*/
class Ev_SocketCli : public Ev_Stream
{
public: // api
	Ev_SocketCli(socket_type_t s_type = SOCKET_TCP_CLIENT,
							uint32 stream_buf_size = 8192,
							fifo_type_t f_type = CIRCULAR_FIFO);
	virtual ~Ev_SocketCli();

	virtual ev_error connect_to_host(const char *addr = NULL, uint32 args = 0);

public: // var

protected: // api
	friend void ev_vector_connect_cb(struct ev_loop *loop, void *io, int events);
	virtual void on_ev_connect(ev_error ret) = 0;
	virtual ev_error on_ev_stream_read(uint32 size) = 0;

protected: // var

private: // api

private: // var
	socket_type_t m_type;
	socket_addr_t m_addr;
};


#endif // __EV_SOCKETCLI_H__

