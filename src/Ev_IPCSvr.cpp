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
#include "Ev_IPCSvr.h"
#include <algorithm>

/*----------------------------macro file---------------------------*/
#define __MODULE__						"[IPCSvr]"

/*----------------------------type define--------------------------*/

/*----------------------------var define---------------------------*/
Ev_IPCSvr *Ev_IPCSvr::m_instance = NULL;

/*-----------------------------------------------------------------*/
Ev_IPCSvr *Ev_IPCSvr::instance()
{
	if(m_instance == NULL)
		m_instance = new Ev_IPCSvr();

	return m_instance;
}

Ev_IPCSvr::Ev_IPCSvr() :
	Ev_SocketSvr(SOCKET_SYS_BUS_SERVER),
	m_restart_timer(NULL)
{

}

Ev_IPCSvr::~Ev_IPCSvr()
{
	if(m_restart_timer) {
		deregister_timer_event(m_restart_timer);
		m_restart_timer = NULL;
	}

	m_instance = NULL;
}

ev_error Ev_IPCSvr::init()
{
	m_restart_timer = register_timer_event(m_restart_timer, 2., 2.);
	
	return create_host_service(DEF_IPC_NODE);
}

ev_error Ev_IPCSvr::on_ev_accept_malloc_cli(Ev_SocketCli **socket)
{
	*socket = new Ev_IPCSvrHandle;
	return EV_SUCCESS;
}

ev_error Ev_IPCSvr::on_ev_accept_buttom(Ev_SocketCli *socket)
{
	EV_PRINTF_INFO("New IPC Client:[%d]", socket->m_handle);
	return EV_SUCCESS;
}

/*****************************************************************************
 * 函数功能  : 客户端注册处理函数
 * 输入参数  : socket_cli      客户端指针
               *event_ids  ev_ids列表
               event_num   ev ids个数
 * 输出参数  : 无
 * 返 回 值  : 无
*****************************************************************************/
void Ev_IPCSvr::register_IPCCli(Ev_SocketCli	*socket_cli, event_id_t *event_ids, uint32 event_num)
{
	uint16 i;
	list<Ev_SocketCli *> *socket_list = NULL;

	ARGS_NULL_CHECK_RV(socket_cli);
	ARGS_NULL_CHECK_RV(event_ids);
	CONDITION_CHECK_RV(event_num == 0);

	for(i = 0; i < event_num; ++i) {
		map<event_id_t, list<Ev_SocketCli *> *>::iterator it = evid_socket_list.find(event_ids[i]);
		if(it == evid_socket_list.end()) {
			// 没找到
			socket_list = new list<Ev_SocketCli *>;
			socket_list->push_back(socket_cli);

			evid_socket_list.insert(pair<event_id_t, list<Ev_SocketCli *> *>(event_ids[i], socket_list));
		}
		else {
			// 找到
			socket_list = it->second;
			socket_list->push_back(socket_cli);
		}
	}

	EV_PRINTF_DBG("Event Add: %d, All: %ld", event_num, evid_socket_list.size());
}

/*****************************************************************************
 * 函数功能  : 注销客户端(从ev_ids列表删除客户端)
 * 输入参数  : *socket_cli  客户端指针
 * 输出参数  : 无
 * 返 回 值  : 无
*****************************************************************************/
void Ev_IPCSvr::deregister_IPCCli(Ev_SocketCli	*socket_cli)
{
	list<Ev_SocketCli *> *socket_list = NULL;
	map<event_id_t, list<Ev_SocketCli *> *>::iterator it = evid_socket_list.begin();

	for(; it != evid_socket_list.end(); ++it) {
		socket_list = it->second;

		list<Ev_SocketCli *>::iterator client = find(socket_list->begin(), socket_list->end(), socket_cli);
		if(client != socket_list->end())
			socket_list->erase(client);
	}
}

void Ev_IPCSvr::forward_data_to_IPCCli(Ev_SocketCli	*socket_cli, ipc_msg_info_t *ipc_msg)
{
	ev_msg_info_t *ev_msg_info = (ev_msg_info_t *)ipc_msg->data;
	const list<Ev_SocketCli *> *socket_list = get_IPCCli_list_by_evid(ev_msg_info->ev_id);
	if(socket_list == NULL)
		return;

	list<Ev_SocketCli *>::const_iterator it = socket_list->begin();
	for(; it != socket_list->end(); ++it) {
		if(*it != socket_cli) {
			(*it)->write_data((uint8*)ipc_msg, sizeof(*ipc_msg) + ipc_msg->length);
		}
		else {
			EV_PRINTF_DBG("skip self.");
		}
	}
}

const list<Ev_SocketCli *> *Ev_IPCSvr::get_IPCCli_list_by_evid(event_id_t evid)
{
	map<event_id_t, list<Ev_SocketCli *> *>::iterator it = evid_socket_list.find(evid);
	if(it != evid_socket_list.end()) {
		// 找到
		return it->second;
	}

	// 没找到
	return NULL;
}

ev_error Ev_IPCSvr::on_ev_error()
{
	EV_PRINTF_DBG_FUNC();

	// TODO:clear所有的evid_socket_list(暂时无法测试是否ok)
	list<Ev_SocketCli *> *socket_list = NULL;
	map<event_id_t, list<Ev_SocketCli *> *>::iterator it = evid_socket_list.begin();
	for(; it != evid_socket_list.end(); ++it) {
		socket_list = it->second;

		list<Ev_SocketCli *>::const_iterator client = socket_list->begin();
		for(; client != socket_list->end(); ++client)
			delete (*client);

		delete socket_list;
	}

	// TODO:定时重起服务(什么条件会跑到此处呢？)
	start_timer_event(m_restart_timer);

	// 移除事件监听
	return EV_REMOVE_EVENT;
}

ev_error Ev_IPCSvr::on_ev_timeout(ev_timer *timer)
{
	if(init() == EV_SUCCESS)
		return EV_REMOVE_EVENT;

	return EV_SUCCESS;
}

