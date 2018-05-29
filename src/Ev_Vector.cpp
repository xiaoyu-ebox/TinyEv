/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-3-12
 * Version     : v0.1
 * Description : 
 *******************************************************************/
/*----------------------------Head file----------------------------*/
#include "Ev_Vector.h"
#include "Ev_Timer.h"
#include "Ev_SocketSvr.h"

/*----------------------------static func--------------------------*/
typedef void (*handle_ev_cb)(struct ev_loop *loop, ev_io *w, int revents);
typedef void (*timer_ev_cb)(struct ev_loop *loop, ev_timer *w, int revents);

void ev_vector_handle_cb(struct ev_loop *loop, void *io, int revents);
void ev_vector_connect_cb(struct ev_loop *loop, void *io, int revents);
void ev_vector_listen_cb(struct ev_loop *loop, void *io, int revents);
void ev_vector_signal_cb(struct ev_loop *loop, ev_signal *watcher, int revents);


/*----------------------------macro file---------------------------*/
#define __MODULE__						"[Vector]"

#define EV_TYPE_MASK					(EV_READ | EV_WRITE)

/*----------------------------type define--------------------------*/

/*----------------------------var define---------------------------*/
Ev_Vector *Ev_Vector::m_instance = NULL;
struct ev_loop *Ev_Vector::def_loop = NULL;

/*-----------------------------------------------------------------*/
Ev_Vector *Ev_Vector::instance()
{
	if(m_instance == NULL)
		m_instance = new Ev_Vector();

	return m_instance;
}

Ev_Vector::Ev_Vector()
{

}

Ev_Vector::~Ev_Vector()
{
	m_instance = NULL;
}

ev_error Ev_Vector::init()
{
	if((def_loop = ev_default_loop(0)) == NULL)
		return EV_INIT_ERR;

	return EV_SUCCESS;
}

void Ev_Vector::run_loop()
{
	ev_run(def_loop, 0);
}

void Ev_Vector::break_loop()
{
	ev_unloop(def_loop, EVBREAK_ALL);
}

struct ev_loop *Ev_Vector::default_loop()
{
	return def_loop;
}

ev_error Ev_Vector::register_handle_event(Ev_Handle *handle, ev_type_t events, handle_type_t type)
{
	ARGS_NULL_CHECK(handle);
	CONDITION_CHECK(handle->m_handle == INVALID_HANDLE);

	if(set_non_blocking(handle->m_handle) != EV_SUCCESS)
		return EV_CTRL_ERR;

	EV_PRINTF_INFO("%sregister handle:%d", handle->m_watcher ? "re-" : "", handle->m_handle);

	if(handle->m_watcher) {
		ev_io_stop(def_loop, handle->m_watcher);
	}
	else {
		handle->m_watcher = ev_new(ev_io, 1);
		handle->m_watcher->data = handle;
	}

	if(type == TYPE_SOCKET_SVR_LISTEN)
		ev_io_init(handle->m_watcher, (handle_ev_cb)ev_vector_listen_cb, handle->m_handle, events & EV_TYPE_MASK);
	else if(type == TYPE_TCP_SOCKET_CLI || type == TYPE_UNIX_SOCKET_CLI)
		ev_io_init(handle->m_watcher, (handle_ev_cb)ev_vector_connect_cb, handle->m_handle, events & EV_TYPE_MASK);
	else
		ev_io_init(handle->m_watcher, (handle_ev_cb)ev_vector_handle_cb, handle->m_handle, events & EV_TYPE_MASK);

	ev_io_start(def_loop, handle->m_watcher);

	return EV_SUCCESS;
}

/*****************************************************************************
 * 函数功能  : 注销handle事件
 * 输入参数  : *handle  handle指针
 * 输出参数  : 无
 * 返 回 值  : 无
*****************************************************************************/
void Ev_Vector::deregister_handle_event(Ev_Handle *handle)
{
	ARGS_NULL_CHECK_RV(handle);

	if(handle->m_watcher) {
		ev_io_stop(def_loop, handle->m_watcher);
		ev_free(handle->m_watcher);
		handle->m_watcher = NULL;
	}

	if(handle->m_handle != INVALID_HANDLE) {
		close(handle->m_handle);
		handle->m_handle = INVALID_HANDLE;
	}
}

ev_timer *Ev_Vector::register_timer_event(Ev_Timer *timer, ev_timer *watcher, double start, double repeat)
{
	ARGS_NULL_CHECK_RN(timer);

	if(watcher == NULL) {
		watcher = ev_new(ev_timer, 1);
		watcher->data = timer;
		ev_init(watcher, (timer_ev_cb)ev_vector_handle_cb);
	}
	else {
		ev_timer_stop(def_loop, watcher);
	}

	ev_timer_set(watcher, start, repeat);

	return watcher;
}

void Ev_Vector::start_timer_event(ev_timer *watcher)
{
	ev_timer_start(def_loop, watcher);
}

void Ev_Vector::stop_timer_event(ev_timer *watcher)
{
	ev_timer_stop(def_loop, watcher);
}

void Ev_Vector::deregister_timer_event(ev_timer *watcher)
{
	ARGS_NULL_CHECK_RV(watcher);

	ev_timer_stop(def_loop, watcher);

	ev_free(watcher);
}

ev_error Ev_Vector::register_signal_event(int signal, ev_signal_cb_t cb)
{
	ev_signal *watcher = ev_new(ev_signal, 1);

	watcher->data = (void *)cb;
	ev_signal_init(watcher, ev_vector_signal_cb, signal);
	ev_signal_start(def_loop, watcher);

	return EV_SUCCESS;
}

ev_error Ev_Vector::set_non_blocking(int fd)
{
	int flags;

	CONDITION_CHECK(fd < 0);

	// 得到文件状态标志
	flags = fcntl(fd, F_GETFL, 0);
	if(flags < 0)
		return EV_ARGS_GET_ERR;

	// 设置文件状态标志
	flags |= O_NONBLOCK;

	// 设置文件状态标志
	if(fcntl(fd, F_SETFL, flags) < 0)
		return EV_ARGS_SET_ERR;

	return EV_SUCCESS;
}

void ev_vector_handle_cb(struct ev_loop *loop, void *io, int revents)
{
	ev_error ret;

	ARGS_NULL_CHECK_RV(io);

	switch(revents) {
		case EV_READ: {
			Ev_Handle *handle = (Ev_Handle *)((ev_io *)io)->data;

			ret = handle->on_ev_read();
			if(ret == EV_REMOVE_EVENT || ret == EV_REMOVE_HANDLE)
				Ev_Vector::deregister_handle_event(handle);
			if(ret == EV_REMOVE_HANDLE)
				delete handle;
		} break;

		case EV_WRITE: {
			Ev_Handle *handle = (Ev_Handle *)((ev_io *)io)->data;
			if(ret == EV_REMOVE_EVENT || ret == EV_REMOVE_HANDLE)
				Ev_Vector::deregister_handle_event(handle);
			if(ret == EV_REMOVE_HANDLE)
				delete handle;
		} break;

		case EV_TIMER: {
			Ev_Timer *timer = (Ev_Timer *)((ev_timer *)io)->data;
			if(timer->on_ev_timeout((ev_timer *)io) == EV_REMOVE_EVENT)
				Ev_Vector::deregister_timer_event((ev_timer *)io);
		} break;

		default:
			break;
	}
}

void ev_vector_listen_cb(struct ev_loop *loop, void *io, int revents)
{
	ARGS_NULL_CHECK_RV(io);

	switch(revents) {
		case EV_READ: {
			Ev_SocketSvr *handle = (Ev_SocketSvr *)((ev_io *)io)->data;
			handle->on_ev_accept();
			// 不管on_ev_accept返回值是否异常
		} break;

		default:
			break;
	}
}

void ev_vector_connect_cb(struct ev_loop *loop, void *io, int events)
{
	int error = 0;
	ev_error ret = EV_SUCCESS;
	socklen_t len = sizeof(error);
	Ev_SocketCli *socket_client;
	
	ARGS_NULL_CHECK_RV(io);

	socket_client = (Ev_SocketCli *)((ev_io *)io)->data;

	if(events == EV_WRITE)
		getsockopt(((ev_io *)io)->fd, SOL_SOCKET, SO_ERROR, &error, &len);

	// 可读并可写:连接出错 可写:连接成功(使用getsockopt再次判断)
	if(events == (EV_READ | EV_WRITE) || error != 0)
		ret = EV_DEV_CONNECT_ERR;

	// 回调on_ev_connect函数
	socket_client->on_ev_connect(ret);

	// 如果成功，重新注册回调函数
	if(ret == EV_SUCCESS)
		Ev_Vector::register_handle_event(socket_client, EV_READ, TYPE_HANDLE);
}

void ev_vector_signal_cb(struct ev_loop *loop, ev_signal *watcher, int revents)
{
	ev_signal_cb_t cb = (ev_signal_cb_t)watcher->data;
	
	if(cb)
		cb(loop, watcher->signum);
}

