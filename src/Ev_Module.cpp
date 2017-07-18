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
#include "Ev_Module.h"
#include "Ev_Mod_Manager.h"
#include "Ev_Event.h"

/*----------------------------macro file---------------------------*/
#define __MODULE__						"[Module]"

/*----------------------------type define--------------------------*/

/*----------------------------var define---------------------------*/

/*-----------------------------------------------------------------*/
Ev_Module::Ev_Module(event_id_t *event_ids, uint32 event_num)
{
	Ev_Mod_Manager::instance()->register_module(this, event_ids, event_num);
}

Ev_Module::~Ev_Module()
{

}

/*****************************************************************************
 * 函数功能  : 发出系统事件
 * 输入参数  : id        事件id
               priority  事件优先级
               *data     事件参数(临时变量即可，内部会做拷贝)
               size      参数size
 * 输出参数  : 无
 * 返 回 值  : 无
*****************************************************************************/
ev_error Ev_Module::ev_put_event(event_id_t id, priority_t priority, uint8 *data, uint32 size)
{
	return Ev_Event::instance()->ev_put_event(MSG_TYPE_IPC_DISPENSE, id, priority, data, size);
}

ev_error Ev_Module::ev_put_event_internal(event_id_t id, priority_t priority, uint8 *data, uint32 size)
{
	return Ev_Event::instance()->ev_put_event(MSG_TYPE_INTERIOR_DISPENSE, id, priority, data, size);
}


