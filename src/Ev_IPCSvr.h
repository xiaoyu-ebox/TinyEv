/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-2-18
 * Version     : v0.1
 * Description : Ev_IPCSvr header file
 *******************************************************************/
#ifndef __EV_IPCSVR_H__
#define __EV_IPCSVR_H__

/*----------------------------Head file----------------------------*/
#include "Ev_SocketSvr.h"
#include "Ev_IPCSvrHandle.h"
#include "Ev_Module.h"
#include "Ev_Timer.h"
#include <list>
#include <map>

using namespace std;

/*----------------------------macro file---------------------------*/

/*----------------------------type define--------------------------*/

/*-----------------------------------------------------------------*/
class Ev_IPCSvr : public Ev_SocketSvr, public Ev_Timer
{
	static Ev_IPCSvr *m_instance;

public: // api
	Ev_IPCSvr();
	~Ev_IPCSvr();
	static Ev_IPCSvr *instance();
	ev_error init();

	void register_IPCCli(Ev_SocketCli	*socket_cli, event_id_t *event_ids, uint32 event_num);
	void deregister_IPCCli(Ev_SocketCli	*socket_cli);
	
	void forward_data_to_IPCCli(Ev_SocketCli	*socket_cli, ipc_msg_info_t *msg);
	const list<Ev_SocketCli *> *get_IPCCli_list_by_evid(event_id_t evid);

public: // var

protected: // api

protected: // var
	ev_error on_ev_accept_malloc_cli(Ev_SocketCli **socket);
	ev_error on_ev_accept_buttom(Ev_SocketCli *socket);
	
	ev_error on_ev_write() {return EV_SUCCESS;}
	ev_error on_ev_error();

	ev_error on_ev_timeout(ev_timer *timer);

private: // api

private: // var
	map<event_id_t, list<Ev_SocketCli *> *>evid_socket_list;	// 每个event id对应的Ev_SocketCli *集合

	ev_timer *m_restart_timer;
};


#endif // __EV_IPCSVR_H__

