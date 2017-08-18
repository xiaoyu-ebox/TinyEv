/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-3-19
 * Version     : v0.1
 * Description : 
 *******************************************************************/
/*----------------------------Head file----------------------------*/
#include "Ev_IPCSvrHandle.h"
#include "Ev_IPCSvr.h"

/*----------------------------macro file---------------------------*/
#define __MODULE__						"[IPCSvrHandle]"

/*----------------------------type define--------------------------*/

/*----------------------------var define---------------------------*/

/*-----------------------------------------------------------------*/
Ev_IPCSvrHandle::Ev_IPCSvrHandle() :
	Ev_SocketCli(SOCKET_SYS_BUS_CLIENT),
	m_recv_buf(NULL)
{
	m_recv_buf = ev_new(uint8, IPC_BUFFER_DEF_SIZE);
}

Ev_IPCSvrHandle::~Ev_IPCSvrHandle()
{
	if(m_recv_buf) {
		ev_free(m_recv_buf);
		m_recv_buf = NULL;
	}
}

ev_error Ev_IPCSvrHandle::on_ev_stream_read(uint32 size)
{
	uint32 msg_size;
	ipc_msg_info_t *msg_info = (ipc_msg_info_t *)m_recv_buf;

	EV_PRINTF_DBG("on_ev_stream_read size:%u", size);

	while(1) {
		// 试读msg头部信息
		if(stream_try_read(m_recv_buf, sizeof(ipc_msg_info_t)) == NULL)
			return EV_SUCCESS;

		// 长度判断
		msg_size = sizeof(ipc_msg_info_t)+msg_info->length;
		if(size < msg_size)
			return EV_SUCCESS;

		// 读取msg
		stream_read(m_recv_buf, msg_size);
		size -= msg_size;

		//EV_PRINTF_DBG_HEX(buffer, size);
		switch(msg_info->type) {
			case MSG_TYPE_REGISTER: {
				Ev_IPCSvr::instance()->register_IPCCli(this, (event_id_t *)msg_info->data, msg_info->length/sizeof(event_id_t));
			} break;

			case MSG_TYPE_IPC_DISPENSE: {
				EV_PRINTF_DBG("new ipc msg:%u.", msg_info->length);

				// 分发到各个ipc
				Ev_IPCSvr::instance()->forward_data_to_IPCCli(this, msg_info);
			} break;

			default:
				break;
		}
	}

	return EV_SUCCESS;
}

ev_error Ev_IPCSvrHandle::on_ev_error()
{
	EV_PRINTF_ERR("IPCCli %u disconnect ...", m_handle);

	Ev_IPCSvr::instance()->deregister_IPCCli(this);

	// 移除监听并销毁自身
	return EV_REMOVE_HANDLE;
}

