/*******************************************************************
 *
 * Copyright (C), 2002-2017, www.lifesense.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-3-12
 * Version     : v0.1
 * Description : 
 *******************************************************************/
/*----------------------------Head file----------------------------*/
#include "Ev_Vector.h"
#include "Ev_Event.h"
#include "Ev_IPCSvr.h"

/*----------------------------macro file---------------------------*/
#define __MODULE__				"[Main]"

/*----------------------------type define--------------------------*/

/*----------------------------var define---------------------------*/

/*-----------------------------------------------------------------*/
int main(int argc, char **argv)
{
	// 初始化事件驱动容器
	Ev_Vector::instance()->init();

	// 初始化ipc server
	Ev_IPCSvr::instance()->init();

	// 初始化事件框架
	Ev_Event::instance()->init();

	// --------- module init start -------------

	// --------- module init end ---------------
	// 启动ipc消息处理
	Ev_Event::instance()->run_ev_msg_manager();

	// 启动io事件处理
	Ev_Vector::instance()->run_loop();

	EV_PRINTF_INFO("End APP.");

	return EV_SUCCESS;
}

