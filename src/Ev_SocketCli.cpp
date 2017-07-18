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
#include "Ev_SocketCli.h"

/*----------------------------macro file---------------------------*/
#define __MODULE__						"[SocketCli]"

/*----------------------------type define--------------------------*/

/*----------------------------var define---------------------------*/

/*-----------------------------------------------------------------*/
Ev_SocketCli::Ev_SocketCli(socket_type_t s_type, uint32 stream_buf_size, fifo_type_t f_type) :
	Ev_Stream(stream_buf_size, f_type),
	m_type(s_type)
{

}

Ev_SocketCli::~Ev_SocketCli()
{

}

ev_error Ev_SocketCli::connect_to_host(const char *addr, uint32 args)
{
	ev_error ret = EV_SUCCESS;

	ARGS_NULL_CHECK(addr);

	// socket
	if(m_type == SOCKET_SYS_BUS_CLIENT) {
		// 1.初始化地址
		memset(&m_addr.un, 0, sizeof(m_addr.un));

		m_addr.un.sun_family = AF_UNIX;
		strcpy(m_addr.un.sun_path, addr);

		// 2.建立socket套接字
		if((m_handle = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
			m_handle = INVALID_HANDLE;
			return EV_OBJ_CREATE_ERR;
		}

		// 3.设置为非阻塞
		if(Ev_Vector::set_non_blocking(m_handle) != EV_SUCCESS)
			return EV_CTRL_ERR;

		// 4.建立连接(客户端和服务器端在同一台主机上，connect会马上结束，并返回0)
#if 0
		// 全部由on_ev_connect去通知连接成功还是失败
		if(connect(m_handle, (struct sockaddr *)&m_addr.un, sizeof(m_addr.un)) < 0)
			return EV_DEV_CONNECT_ERR;
#else
		connect(m_handle, (struct sockaddr *)&m_addr.un, sizeof(m_addr.un));
#endif

		// 5.加入事件watch
		return register_handle_event(EV_READ | EV_WRITE, TYPE_UNIX_SOCKET_CLI);
	}
	else if(m_type == SOCKET_TCP_CLIENT) {
		// 1.初始化地址
		memset(&m_addr.in, 0, sizeof(m_addr.in));
		m_addr.in.sin_family = AF_INET;
		m_addr.in.sin_port = htons(args);
		m_addr.in.sin_addr.s_addr = inet_addr(addr); // inet_addr转换为网络字节序

		// 2.建立socket套接字
		if((m_handle = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
			m_handle = INVALID_HANDLE;
			return EV_OBJ_CREATE_ERR;
		}
		
		// 3.设置为非阻塞
		if(Ev_Vector::set_non_blocking(m_handle) != EV_SUCCESS)
			return EV_CTRL_ERR;

		// 4.建立连接
		// 当客户端和服务器端在同一台主机上的时候，connect会马上结束，并返回0
		// 否则无论连接是否建立立即返回-1，并设置errno：
		//   a.如果errno为EINPROGRESS, 表示此时tcp三次握手仍旧进行。
		//	 b.如果errno不为EINPROGRESS，则说明连接错误。
#if 0
		int error = connect(m_handle, (struct sockaddr *)&m_addr.in, sizeof(m_addr.in));
		if(error < 0) {
			if(errno != EINPROGRESS) {
				// 连接错误
				EV_PRINTF_ERR("connect err!.");
				ret = EV_DEV_CONNECT_ERR;
			}
			else {
				// 连接正在进行中
				ret = EV_DEV_CONNECTING;
			}
		}
		else if(error == 0) {
			// 连接成功
			ret = EV_SUCCESS;
		}
#else
		connect(m_handle, (struct sockaddr *)&m_addr.in, sizeof(m_addr.in));
#endif
		// 5.
		return register_handle_event(EV_READ | EV_WRITE, TYPE_TCP_SOCKET_CLI);;
	}
	else if(m_type == SOCKET_NETLINK_CLIENT) {
		EV_PRINTF_WARN("Netlink is best not to inherit this class(don't use stream).");

		// 1.初始化地址
		memset(&m_addr.nl, 0, sizeof(m_addr.nl));
		m_addr.nl.nl_family = AF_NETLINK;
		m_addr.nl.nl_groups = NETLINK_KOBJECT_UEVENT;
		m_addr.nl.nl_pid = 0;	//getpid(); // both is ok

		// 2.建立socket套接字
		if((m_handle = socket(AF_NETLINK, SOCK_RAW, NETLINK_KOBJECT_UEVENT)) < 0) {
			m_handle = INVALID_HANDLE;
			return EV_OBJ_CREATE_ERR;
		}

		// 3.绑定socket
		if(bind(m_handle, (struct sockaddr *)&m_addr.nl, sizeof(m_addr.nl)) == -1)
			return EV_DEV_BIND_ERR;

		// 4.加入事件watch
		return register_handle_event(EV_READ, TYPE_NETLINK_SOCKET_CLI);
	}

	EV_PRINTF_ERR("Unsupport socket type.");
	return EV_DEV_TYPE_UNSUPPORT;
}

