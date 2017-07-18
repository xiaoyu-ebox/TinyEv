/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-2-18
 * Version     : v0.1
 * Description : Ev_Timer header file
 *******************************************************************/
#ifndef __EV_TIMER_H__
#define __EV_TIMER_H__

/*----------------------------Head file----------------------------*/
#include "Ev_Base_Include.h"

/*----------------------------macro file---------------------------*/

/*----------------------------type define--------------------------*/

/*-----------------------------------------------------------------*/
class Ev_Timer
{
public: // api
	virtual ~Ev_Timer();

	virtual ev_timer *register_timer_event(ev_timer *timer, double start, double repeat);
	virtual void start_timer_event(ev_timer *timer);
	virtual void stop_timer_event(ev_timer *timer);
	virtual void deregister_timer_event(ev_timer *timer);

public: // var

protected: // api
	/*****************************************************************************
	 * 函数功能  : 定时器超时事件函数
	 * 输入参数  : 无
	 * 输出参数  : 无
	 * 返 回 值: ev_error		EV_STOP_EVENT:停止定时器			其它：继续定时器
	*****************************************************************************/
	virtual ev_error on_ev_timeout(ev_timer *timer) = 0;

protected: // var

private: // api
	friend void ev_vector_handle_cb(struct ev_loop *loop, void *io, int revents);

private: // var

};


#endif // __EV_TIMER_H__

