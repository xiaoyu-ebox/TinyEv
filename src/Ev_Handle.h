/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-3-11
 * Version     : v0.1
 * Description : Ev_Handle header file
 *******************************************************************/
#ifndef __EV_HANDLE_H__
#define __EV_HANDLE_H__

/*----------------------------Head file----------------------------*/
#include "EV_PrivateData.h"
#include "Ev_Vector.h"

/*----------------------------macro file---------------------------*/
#define INVALID_HANDLE				-1

/*----------------------------type define--------------------------*/

/*-----------------------------------------------------------------*/
class Ev_Handle : public EV_PrivateData
{
public: // api
	Ev_Handle();
	virtual ~Ev_Handle();


	// 写数据函数
	virtual ev_error write_data(uint8 *pdata, uint32 size);

public: // var
	sint32	m_handle;

protected: // api
	/*****************************************************************************
	 * 函数功能  : handle可读事件函数
	 * 输入参数  : 无
	 * 输出参数  : 无
	 * 返 回 值: 无
	*****************************************************************************/
	virtual ev_error on_ev_read() = 0;

	/*****************************************************************************
	 * 函数功能  : handle可写事件函数
	 * 输入参数  : 无
	 * 输出参数  : 无
	 * 返 回 值: 无
	*****************************************************************************/
	virtual ev_error on_ev_write() = 0;

	/*****************************************************************************
	 * 函数功能  : handle错误事件函数
	 * 输入参数  : 无
	 * 输出参数  : 无
	 * 返 回 值: 无
	*****************************************************************************/
	virtual ev_error on_ev_error() = 0;


	// 注册handle事件
	virtual ev_error register_handle_event(ev_type_t events, handle_type_t type);
	virtual void deregister_handle_event();

protected: // var

private: // api
	friend Ev_Vector;
	friend void ev_vector_handle_cb(struct ev_loop *loop, void *io, int revents);

private: // var
	ev_io	*m_watcher;
};


#endif // __EV_HANDLE_H__

