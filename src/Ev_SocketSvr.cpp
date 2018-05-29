/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-2-18
 * Version     : v0.1
 * Description : 
 *******************************************************************/
/*----------------------------Head file----------------------------*/
#include "Ev_SocketSvr.h"

#include <stddef.h>

/*----------------------------macro file---------------------------*/
#define __MODULE__						"[SocketSvr]"


/*----------------------------type define--------------------------*/

/*----------------------------var define---------------------------*/

/*-----------------------------------------------------------------*/
Ev_SocketSvr::Ev_SocketSvr(socket_type_t type) :
	m_type(type)
{

}

Ev_SocketSvr::~Ev_SocketSvr()
{

}

ev_error Ev_SocketSvr::create_host_service(const char *addr, uint32 args)
{
	if(m_type == SOCKET_SYS_BUS_SERVER) {
		ARGS_NULL_CHECK(addr);

		memset(&m_addr.un, 0, sizeof(m_addr.un));

		m_addr.un.sun_family = AF_UNIX;
		strcpy(m_addr.un.sun_path, addr);

		if((m_handle = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
			m_handle = INVALID_HANDLE;
			return EV_OBJ_CREATE_ERR;
		}

		// 解除链接
		unlink(addr);

		// 绑定
		int size = offsetof(struct sockaddr_un, sun_path) + strlen(m_addr.un.sun_path);
		if(bind(m_handle, (struct sockaddr *)&m_addr.un, size) < 0)
			return EV_DEV_BIND_ERR;

		// 都可读写
		chmod(addr, 0777);

		return listen_client_connect();
	}
	else if(m_type == SOCKET_TCP_SERVER) {
		// 1.初始化地址
		memset(&m_addr.in, 0, sizeof(m_addr.in));
		m_addr.in.sin_family = AF_INET;
		m_addr.in.sin_port = htons(args);
		if(addr)
			m_addr.in.sin_addr.s_addr = inet_addr(addr); // inet_addr转换为网络字节序
		else
			m_addr.in.sin_addr.s_addr = htonl(INADDR_ANY); // inet_addr转换为网络字节序

		// 2.建立socket套接字
		if((m_handle = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
			m_handle = INVALID_HANDLE;
			return EV_OBJ_CREATE_ERR;
		}

		int opt = 1;  
		setsockopt(m_handle, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

		// 3.绑定
		if(bind(m_handle, (struct sockaddr *)&m_addr.in, sizeof(struct sockaddr_in)) < 0)
			return EV_DEV_BIND_ERR;

		return listen_client_connect();
	}
	
	EV_PRINTF_ERR("Unsupport socket type.");
	return EV_DEV_TYPE_UNSUPPORT;
}

ev_error Ev_SocketSvr::listen_client_connect()
{
	if(listen(m_handle, 8) < 0)
		return EV_DEV_LISTEN_ERR;

	return register_handle_event(EV_READ, TYPE_SOCKET_SVR_LISTEN);
}

ev_error Ev_SocketSvr::on_ev_accept()
{
	ev_error ret;
	sint32 s_fd;
	socklen_t sin_size;
	socket_addr_t s_addr;
	Ev_SocketCli *socket_cli = NULL;

	// 等待客户端连接请求到达
	sin_size = sizeof(socket_addr_t);
	if((s_fd = accept(m_handle, (struct sockaddr *)&s_addr, &sin_size)) < 0) {
		EV_PRINTF_ERR("accept err:%d, %d", m_handle, errno);
		return EV_DEV_ACCEPT_ERR;
	}

	if((ret = on_ev_accept_malloc_cli(&socket_cli)) != EV_SUCCESS)
		return ret;

	socket_cli->m_handle = s_fd;
	if((ret = Ev_Vector::register_handle_event(socket_cli, EV_READ, TYPE_SOCKET_SVR)) != EV_SUCCESS) {
		delete socket_cli;

		return EV_REGISTER_ERR;
	}

	return on_ev_accept_buttom(socket_cli);
}


