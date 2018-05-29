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
#include "Ev_IPCCli.h"
#include "Ev_Mod_Manager.h"
#include "Ev_Event.h"

/*----------------------------macro file---------------------------*/
#define __MODULE__						"[IPCCli]"


#define TIMER_RECOONECT_SEC		(2.)


/*----------------------------type define--------------------------*/

/*----------------------------var define---------------------------*/
Ev_IPCCli *Ev_IPCCli::m_instance = NULL;

/*-----------------------------------------------------------------*/
Ev_IPCCli *Ev_IPCCli::instance()
{
	if(m_instance == NULL)
		m_instance = new Ev_IPCCli();

	return m_instance;
}

Ev_IPCCli::Ev_IPCCli() :
	Ev_SocketCli(SOCKET_SYS_BUS_CLIENT),
	m_connect_timer(NULL),
	m_recv_buf(NULL)
{

}

Ev_IPCCli::~Ev_IPCCli()
{
	if(m_connect_timer) {
		deregister_timer_event(m_connect_timer);
		m_connect_timer = NULL;
	}

	if(m_recv_buf) {
		ev_free(m_recv_buf);
		m_recv_buf = NULL;
	}
	
	m_instance = NULL;
}

ev_error Ev_IPCCli::init()
{
	ev_error ret;
	m_recv_buf = ev_new(uint8, IPC_BUFFER_DEF_SIZE);
	if(m_recv_buf == NULL)
		return EV_NOMEM;

	m_connect_timer = register_timer_event(m_connect_timer, TIMER_RECOONECT_SEC, 0);

	ret = connect_to_host(DEF_IPC_NODE);

	EV_PRINTF_INFO("init ok %d, ret %d", m_handle, ret);
	return EV_SUCCESS;
}

void Ev_IPCCli::on_ev_connect(ev_error ret)
{
	if(ret)
		EV_PRINTF_ERR("Connect error.");
	else
		EV_PRINTF_INFO("Connect ok.");

	if(ret == EV_SUCCESS) {
		// 发送所有的方法id到服务器
		uint8 *msg_buffer;
		ipc_msg_info_t *msg_info;
		uint32 length = Ev_Mod_Manager::instance()->get_event_id_size() * sizeof(event_id_t);

		msg_buffer = ev_new(uint8, sizeof(ipc_msg_info_t)+length);
		msg_info = (ipc_msg_info_t *)msg_buffer;

		msg_info->type = MSG_TYPE_REGISTER;
		msg_info->length = length;
		Ev_Mod_Manager::instance()->get_event_id((event_id_t *)msg_info->data);
		ipc_write_data(msg_buffer, sizeof(ipc_msg_info_t)+length);

		// 释放内存
		ev_free(msg_buffer);
	}
	else {
		deregister_handle_event();

		/* 添加重连机制(因为重复定时的时间为0，如果单纯使用
		   start_timer_event这句再次启动定时器将会死循环) */
		register_timer_event(m_connect_timer, TIMER_RECOONECT_SEC, 0);
		start_timer_event(m_connect_timer);
	}
}

ev_error Ev_IPCCli::ipc_write_data(uint8 *data, uint32 size)
{
	ev_error ret;
	//EV_PRINTF_DBG_HEX(data, size);
	//EV_PRINTF_DBG("<-- %d", size);

	return write_data(data, size);
}

ev_error Ev_IPCCli::on_ev_stream_read(uint32 size)
{
	uint32 msg_size;
	ipc_msg_info_t *ipc_msg = (ipc_msg_info_t *)m_recv_buf;

	//EV_PRINTF_DBG("--> %d", size);

	while(1) {
		// 试读msg头部信息
		if(stream_try_read(m_recv_buf, sizeof(ipc_msg_info_t)) == NULL)
			return EV_SUCCESS;

		// 长度判断
		msg_size = sizeof(ipc_msg_info_t)+ipc_msg->length;
		if(size < msg_size) {
			EV_PRINTF_ERR("size err:%u-%u.", msg_size, size);
			return EV_SUCCESS;
		}

		// 读取msg
		stream_read(m_recv_buf, msg_size);
		size -= msg_size;

		switch(ipc_msg->type) {
			case MSG_TYPE_IPC_DISPENSE: {
				// 修改为内部消息
				ipc_msg->type = MSG_TYPE_INTERIOR_DISPENSE;

				Ev_Event::instance()->ev_put_event(ipc_msg);
			} break;

			default:
				break;
		}
	}

	return EV_SUCCESS;
}

ev_error Ev_IPCCli::on_ev_error()
{
	EV_PRINTF_DBG_FUNC();

	// 添加定时重连机制
	start_timer_event(m_connect_timer);

	// 移除事件监听
	return EV_REMOVE_EVENT;
}

ev_error Ev_IPCCli::on_ev_timeout(ev_timer *timer)
{
	connect_to_host(DEF_IPC_NODE);

	return EV_SUCCESS;
}

