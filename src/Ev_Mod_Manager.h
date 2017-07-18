/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-3-19
 * Version     : v0.1
 * Description : Ev_Mod_Manager header file
 *******************************************************************/
#ifndef __EV_MOD_MANAGER_H__
#define __EV_MOD_MANAGER_H__

/*----------------------------Head file----------------------------*/
#include "Ev_IPCCli.h"
#include <list>
#include <map>

using namespace std;
class Ev_Module;

/*----------------------------macro file---------------------------*/

/*----------------------------type define--------------------------*/
typedef struct {
	Ev_Module *mod;
	event_id_t *ev_ids;
	uint32 ev_num;
} module_info_t;

/*-----------------------------------------------------------------*/
class Ev_Mod_Manager
{
	static Ev_Mod_Manager *m_instance;

public: // api
	Ev_Mod_Manager();
	~Ev_Mod_Manager();
	static Ev_Mod_Manager *instance();
	ev_error init();


	uint32 get_event_id_size();
	void get_event_id(event_id_t *ids);

	// 注册模块
	ev_error register_module(Ev_Module *module, event_id_t *event_ids, uint32 event_num);

	// 分发系统事件
	ev_error dispense_ev_event_msg(ev_msg_info_t *ev_msg_info);
public: // var

protected: // api

protected: // var

private: // api

private: // var
	// 每个event id对应一个list<Ev_Module *> *，
	// list<Ev_Module *> *里面存放含有该event id的所有Ev_Module *
	map<event_id_t, list<Ev_Module *> *>evid_mod_list;
};


#endif // __EV_MOD_MANAGER_H__

