/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-8-18
 * Version     : v0.1
 * Description : Ev_Thread header file
 *******************************************************************/
#ifndef __EV_THREAD_H__
#define __EV_THREAD_H__

/*----------------------------Head file----------------------------*/
#include "Ev_Base_Include.h"

#include <pthread.h>

/*----------------------------macro file---------------------------*/

/*----------------------------type define--------------------------*/
typedef void *(*thread_function_t)(void *args, volatile bool *exit_flag);

/*-----------------------------------------------------------------*/
class Ev_Thread_Manager;
class Ev_Thread
{
public: // api
	void quit() {m_exit = true;}
	void force_quit();

	bool is_running() {return !m_exit;}
	uint32 get_pid() {return m_pid;}
	uint32 get_exit_code() {return m_exit_code;}

public: // var
	volatile bool m_exit;

protected: // api

protected: // var

private: // api
	Ev_Thread();
	~Ev_Thread();

	friend Ev_Thread_Manager;
	friend void *thread_routine(void *args);
	pthread_t spawn(thread_function_t thread_func_cb, void *args = NULL);

private: // var
	void *m_args;
	thread_function_t m_thread_function;
	unsigned long m_exit_code;
	pthread_t m_pid;
};


#endif // __EV_THREAD_H__

