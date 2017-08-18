/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-3-12
 * Version     : v0.1
 * Description : Ev_Vector header file
 *******************************************************************/
#ifndef __EV_VECTOR_H__
#define __EV_VECTOR_H__

/*----------------------------Head file----------------------------*/
#include "Ev_Base_Include.h"
#include "Ev_Timer.h"

/*----------------------------macro file---------------------------*/

/*----------------------------type define--------------------------*/
typedef enum {
	TYPE_HANDLE,
	TYPE_TCP_SOCKET_CLI,
	TYPE_UNIX_SOCKET_CLI,
	TYPE_NETLINK_SOCKET_CLI,
	TYPE_SOCKET_SVR,
	TYPE_SOCKET_SVR_LISTEN
} handle_type_t;

enum {
	EVENT_READ = EV_READ,
	EVENT_WRITE = EV_WRITE
};
typedef uint32				ev_type_t;

typedef void (*ev_signal_cb_t)(struct ev_loop *loop, int signal);

/*-----------------------------------------------------------------*/
class Ev_Handle;
class Ev_Vector
{
	static Ev_Vector *m_instance;

public: // api
	Ev_Vector();
	~Ev_Vector();
	static Ev_Vector *instance();
	static ev_error init();


	static void run_loop();
	static void break_loop();
	static struct ev_loop *default_loop();


	// 注册/注销handle事件
	static ev_error register_handle_event(Ev_Handle *handle, ev_type_t events = EV_READ, handle_type_t type = TYPE_HANDLE);
	static void deregister_handle_event(Ev_Handle *handle);


	// 注册/注销timer事件
	static ev_timer *register_timer_event(Ev_Timer *timer, ev_timer *watcher, double start, double repeat);
	static void start_timer_event(ev_timer *watcher);
	static void stop_timer_event(ev_timer *watcher);
	static void deregister_timer_event(ev_timer *watcher);


	// 注册/注销signal事件
	static ev_error register_signal_event(int signal, ev_signal_cb_t cb);


	// 设置非阻塞
	static ev_error set_non_blocking(int fd);

public: // var

protected: // api

protected: // var

private: // api

private: // var
	static struct ev_loop *def_loop;
};


#endif // __EV_VECTOR_H__

