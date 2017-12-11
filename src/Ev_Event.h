/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-3-28
 * Version     : v0.1
 * Description : Ev_Event header file
 *******************************************************************/
#ifndef __EV_EVENT_H__
#define __EV_EVENT_H__

/*----------------------------Head file----------------------------*/
#include "Ev_Fifo.h"
#include "Ev_IPCCli.h"
#include "Ev_Thread_Manager.h"

/*----------------------------macro file---------------------------*/

/*----------------------------type define--------------------------*/

/*-----------------------------------------------------------------*/
class Ev_Event
{
	static Ev_Event *m_instance;

public: // api
	Ev_Event();
	~Ev_Event();
	static Ev_Event *instance();
	ev_error init();

	// 系统消息处理
	ev_error run_ev_msg_manager();
	ev_error ev_msg_handle(volatile bool *exit_flag);
	ev_error ev_put_event(msg_type_t type, event_id_t id, priority_t priority, uint8 *data, uint32 size);
	ev_error ev_put_event(ipc_msg_info_t *ipc_msg);

	// push系统消息
	ev_error ev_event_msg_push(ipc_msg_info_t **ipc_msg_info);
	ev_error ev_event_msg_pop(ipc_msg_info_t **ipc_msg_info);
	

public: // var

protected: // api

protected: // var

private: // api

private: // var
	Ev_Fifo *ev_msg_fifo;
	Ev_Thread *m_msg_thread;
};


#endif // __EV_EVENT_H__

