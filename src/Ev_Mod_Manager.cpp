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
#include "Ev_Mod_Manager.h"
#include "Ev_Module.h"

/*----------------------------macro file---------------------------*/
#define __MODULE__						"[Mod_Manager]"

/*----------------------------type define--------------------------*/

/*----------------------------var define---------------------------*/
Ev_Mod_Manager *Ev_Mod_Manager::m_instance = NULL;

/*-----------------------------------------------------------------*/
Ev_Mod_Manager *Ev_Mod_Manager::instance()
{
	if(m_instance == NULL)
		m_instance = new Ev_Mod_Manager();

	return m_instance;
}

Ev_Mod_Manager::Ev_Mod_Manager()
{

}

Ev_Mod_Manager::~Ev_Mod_Manager()
{
	list<Ev_Module *> *mod_list = NULL;
	map<event_id_t, list<Ev_Module *> *>::iterator it = evid_mod_list.begin();
	for(; it != evid_mod_list.end();) {
		mod_list = it->second;

		list<Ev_Module *>::const_iterator mod = mod_list->begin();
		for(; mod != mod_list->end();) {
			EV_PRINTF_WARN("mod:%p not delete.", *mod);

			mod_list->erase(mod++);
		}

		delete mod_list;
		evid_mod_list.erase(it++);
	}

	m_instance = NULL;
}

ev_error Ev_Mod_Manager::init()
{
	return EV_SUCCESS;
}

uint32 Ev_Mod_Manager::get_event_id_size()
{
	return evid_mod_list.size();
}

// 获取当前进程的所有模块的事件id
void Ev_Mod_Manager::get_event_id(event_id_t *ids)
{
	map<event_id_t, list<Ev_Module *> *>::iterator it = evid_mod_list.begin();

	for(; it != evid_mod_list.end(); ++it)
		*ids++ = it->first;
}

// 注册模块
ev_error Ev_Mod_Manager::register_module(Ev_Module *module, event_id_t *event_ids, uint32 event_num)
{
	uint16 i;
	list<Ev_Module *> *mod_list = NULL;

	ARGS_NULL_CHECK(module);
	ARGS_NULL_CHECK(event_ids);
	CONDITION_CHECK(event_num == 0);

	for(i = 0; i < event_num; ++i) {
		map<event_id_t, list<Ev_Module *> *>::iterator it = evid_mod_list.find(event_ids[i]);
		if(it == evid_mod_list.end()) {
			// 没找到
			mod_list = new list<Ev_Module *>;
			mod_list->push_back(module);
			evid_mod_list.insert(pair<event_id_t, list<Ev_Module *> *>(event_ids[i], mod_list));
		}
		else {
			// 找到
			mod_list = it->second;
			mod_list->push_back(module);
		}
	}

	EV_PRINTF_DBG("evid_mod_list size:%lu", evid_mod_list.size());

	return EV_SUCCESS;
}

ev_error Ev_Mod_Manager::unregister_module_event(Ev_Module *module, event_id_t *event_ids, uint32 event_num)
{
	list<Ev_Module *> *mod_list = NULL;

	ARGS_NULL_CHECK(module);
	ARGS_NULL_CHECK(event_ids);
	CONDITION_CHECK(event_num == 0);

	for(uint16 i = 0; i < event_num; ++i) {
		map<event_id_t, list<Ev_Module *> *>::iterator it = evid_mod_list.find(event_ids[i]);

		if(it != evid_mod_list.end()) {
			// 找到
			mod_list = it->second;

			list<Ev_Module *>::iterator mit;
			for(mit = mod_list->begin(); mit != mod_list->end(); ++mit) {
				EV_PRINTF_DBG("module it:%p, %p", *mit, module);

				if(*mit == module) {
					mod_list->erase(mit);
					break;
				}
			}
		}
	}
}

// 分发系统消息到各个模块
ev_error Ev_Mod_Manager::dispense_ev_event_msg(ev_msg_info_t *ev_msg_info)
{
	list<Ev_Module *> *mod_list = NULL;
	// 找出额ev_id的模块链表
	map<event_id_t, list<Ev_Module *> *>::iterator it = evid_mod_list.find(ev_msg_info->ev_id);

	if(it != evid_mod_list.end()) {
		// 找到
		mod_list = it->second;

		list<Ev_Module *>::const_iterator mod = mod_list->begin();
		for(; mod != mod_list->end(); ++mod) {
			(*mod)->on_ev_event(ev_msg_info->ev_id, ev_msg_info->data, ev_msg_info->length);
		}
	}
}

