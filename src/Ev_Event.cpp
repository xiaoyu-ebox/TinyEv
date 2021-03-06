/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-3-28
 * Version     : v0.1
 * Description : 
 *******************************************************************/
/*----------------------------Head file----------------------------*/
#include "Ev_Event.h"
#include "Ev_Mod_Manager.h"

/*----------------------------static func--------------------------*/
static void *spawn(void *args, volatile bool *exit_flag);

/*----------------------------macro file---------------------------*/

/*----------------------------type define--------------------------*/

/*----------------------------var define---------------------------*/
Ev_Event *Ev_Event::m_instance = NULL;

/*-----------------------------------------------------------------*/
Ev_Event *Ev_Event::instance()
{
	if(m_instance == NULL)
		m_instance = new Ev_Event();

	return m_instance;
}

Ev_Event::Ev_Event() :
	ev_msg_fifo(NULL),
	m_msg_thread(NULL)
{
	ev_msg_fifo = new Ev_Fifo(MAX_EV_MSG_FIFO_SIZE * sizeof(void *), MIN_TO_MS(60));
}

Ev_Event::~Ev_Event()
{
	if(ev_msg_fifo) {
		delete ev_msg_fifo;
		ev_msg_fifo = NULL;
	}

	if(m_msg_thread) {
		Ev_Thread_Manager::instance()->destroy_thread(m_msg_thread);
		m_msg_thread = NULL;
	}
	
	m_instance = NULL;
}

ev_error Ev_Event::init()
{
	return EV_SUCCESS;
}

ev_error Ev_Event::run_ev_msg_manager()
{
	m_msg_thread = Ev_Thread_Manager::instance()->spawn("MSG_Manager", spawn, this);

	return EV_SUCCESS;
}

ev_error Ev_Event::ev_msg_handle(volatile bool *exit_flag)
{
	ipc_msg_info_t *ipc_msg_info;

	while(!(*exit_flag)) {
		if(ev_event_msg_pop(&ipc_msg_info) != EV_SUCCESS)
			continue;

		// 发送到服务器
		if(ipc_msg_info->type == MSG_TYPE_IPC_DISPENSE) {
			ev_msg_info_t *msg_info = (ev_msg_info_t *)ipc_msg_info->data;

			Ev_IPCCli::instance()->ipc_write_data((uint8 *)ipc_msg_info, sizeof(ipc_msg_info_t)+ipc_msg_info->length);
		}

		// 内部进程分发
		Ev_Mod_Manager::instance()->dispense_ev_event_msg((ev_msg_info_t *)ipc_msg_info->data);

		// 释放消息内存
		ev_free(ipc_msg_info);
	}

	return EV_SUCCESS;
}

ev_error Ev_Event::ev_put_event(msg_type_t type, event_id_t id, priority_t priority, uint8 *data, uint32 size)
{
	// 内存在ev_msg_handle里面释放
	uint8 *buffer = ev_new(uint8, sizeof(ipc_msg_info_t)+sizeof(ev_msg_info_t)+size);
	ipc_msg_info_t *ipc_msg_info = (ipc_msg_info_t *)buffer;
	ev_msg_info_t *ev_msg_info = (ev_msg_info_t *)ipc_msg_info->data;

	ipc_msg_info->type = type;
	ipc_msg_info->length = sizeof(ev_msg_info_t)+size;

	ev_msg_info->ev_id = id;
	ev_msg_info->priority = priority;
	ev_msg_info->length = size;
	if(data && size)
		memcpy(ev_msg_info->data, data, size);

	// push
	return ev_event_msg_push(&ipc_msg_info);
}

ev_error Ev_Event::ev_put_event(ipc_msg_info_t *ipc_msg)
{
	// 内存在ev_msg_handle里面释放
	uint8 *buffer = ev_new(uint8, sizeof(ipc_msg_info_t)+ipc_msg->length);

	memcpy(buffer, ipc_msg, sizeof(ipc_msg_info_t)+ipc_msg->length);

	// push
	return ev_event_msg_push((ipc_msg_info_t **)&buffer);
}

ev_error Ev_Event::ev_event_msg_push(ipc_msg_info_t **ipc_msg_info)
{
	return ev_msg_fifo->fifo_push((uint8 *)ipc_msg_info, sizeof(ipc_msg_info_t **)) ? EV_SUCCESS : EV_CONTAINER_FULL;
}

ev_error Ev_Event::ev_event_msg_pop(ipc_msg_info_t **ipc_msg_info)
{
	return ev_msg_fifo->fifo_pop((uint8 *)ipc_msg_info, sizeof(ipc_msg_info_t **)) ? EV_SUCCESS : EV_CONTAINER_FULL;
}

void *spawn(void *args, volatile bool *exit_flag)
{
	Ev_Event *obj = (Ev_Event *)args;

	obj->ev_msg_handle(exit_flag);

	return NULL;
}

