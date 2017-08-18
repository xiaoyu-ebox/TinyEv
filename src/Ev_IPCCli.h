/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-2-18
 * Version     : v0.1
 * Description : Ev_IPCCli header file
 *******************************************************************/
#ifndef __EV_IPCCLI_H__
#define __EV_IPCCLI_H__

/*----------------------------Head file----------------------------*/
#include "Ev_SocketCli.h"
#include "Ev_Mod_ID.h"
#include "Ev_Timer.h"

/*----------------------------macro file---------------------------*/
#define DEF_IPC_NODE			"/tmp/ev_ipc.socket"

/*----------------------------type define--------------------------*/
typedef enum {
	MSG_TYPE_INTERIOR_DISPENSE		= 0xFC,		// 内部分发的消息(一般服务器发送过来的消息会转换为此类型)
	MSG_TYPE_IPC_DISPENSE			= 0xFD,		// IPC之间分发的消息
	MSG_TYPE_REGISTER				= 0xFE		// 注册消息
} msg_type_t;

// ipc之间的数据传输结构
typedef struct {
	msg_type_t	type;
	uint32		length;		// data字段的长度
	uint8		data[0];
} ipc_msg_info_t;


typedef enum {
	EV_PRIORITY_LOW = 10,
	EV_PRIORITY_MID = 50,
	EV_PRIORITY_HIGH = 100
} priority_t;

// 进程内的数据传输结果(push到队列)
typedef struct {
	event_id_t	ev_id;		// 事件id
	priority_t	priority;	// 优先级
	uint32		length;		// data字段的长度
    uint8		data[0];	// 数据
} ev_msg_info_t;

/*-----------------------------------------------------------------*/
class Ev_IPCCli : public Ev_SocketCli, public Ev_Timer
{
	static Ev_IPCCli *m_instance;

public: // api
	Ev_IPCCli();
	~Ev_IPCCli();
	static Ev_IPCCli *instance();
	ev_error init();

	ev_error ipc_write_data(uint8 *data, uint32 size);

public: // var

protected: // api
	void on_ev_connect(ev_error ret);
	ev_error on_ev_stream_read(uint32 size);
	ev_error on_ev_error();
	ev_error on_ev_write() {return EV_SUCCESS;}

	ev_error on_ev_timeout(ev_timer *timer);
protected: // var
	
private: // api

private: // var
	ev_timer *m_connect_timer;
	uint8 *m_recv_buf;
};


#endif // __EV_IPCCLI_H__

