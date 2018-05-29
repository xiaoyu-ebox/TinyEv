/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-3-19
 * Version     : v0.1
 * Description : Ev_Module header file
 *******************************************************************/
#ifndef __EV_MODULE_H__
#define __EV_MODULE_H__

/*----------------------------Head file----------------------------*/
#include "Ev_Mod_Manager.h"
#include "Ev_IPCCli.h"

/*----------------------------macro file---------------------------*/

/*----------------------------type define--------------------------*/

/*-----------------------------------------------------------------*/
class Ev_Module
{
public: // api
	Ev_Module(event_id_t *event_ids, uint32 event_num);
	virtual ~Ev_Module();

	// 发送系统事件函数
	static ev_error ev_put_event(event_id_t id, priority_t priority, uint8 *data, uint32 size);
	static ev_error ev_put_event_internal(event_id_t id, priority_t priority, uint8 *data, uint32 size);
public: // var

protected: // api
	// 有系统事件调用函数
	virtual ev_error on_ev_event(event_id_t id, uint8 *data, uint32 size) = 0;

protected: // var

private: // api
	friend ev_error Ev_Mod_Manager::dispense_ev_event_msg(ev_msg_info_t *ev_msg_info);

private: // var
	event_id_t *m_event_ids;
	uint32 m_event_num;
};


#endif // __EV_MODULE_H__

