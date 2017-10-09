/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
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
static void sigint_cb(struct ev_loop *loop, int signal);
static void exit_cb();

/*----------------------------var define---------------------------*/

/*-----------------------------------------------------------------*/
int main(int argc, char **argv)
{
	// 初始化log
	Mod_Logger::instance()->init(LOG_PRINTF_TO_CONSOLE, LOG_LEVEL_DBG);

	// 初始化事件驱动容器
	Ev_Vector::instance()->init();

	// 注册信号事件
	Ev_Vector::register_signal_event(SIGINT, sigint_cb);
	Ev_Vector::register_signal_event(SIGTERM, sigint_cb);
	Ev_Vector::register_signal_event(SIGQUIT, sigint_cb);

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

	exit_cb();

	printf("End APP.\n");

	return EV_SUCCESS;
}

static void sigint_cb(struct ev_loop *loop, int signal)
{
	EV_PRINTF_WARN("Recv signal:%d.", signal);

	Ev_Vector::instance()->break_loop();
}

void exit_cb()
{
	EV_PRINTF_INFO("Exit APP.");

	delete Mod_Logger::instance();
}



