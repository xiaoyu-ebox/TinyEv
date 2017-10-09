/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-8-18
 * Version     : v0.1
 * Description : Ev_Thread_Manager header file
 *******************************************************************/
#ifndef __EV_THREAD_MANAGER_H__
#define __EV_THREAD_MANAGER_H__

/*----------------------------Head file----------------------------*/
#include "Ev_Thread.h"

#include <iostream>
#include <vector>

using namespace std;
/*----------------------------macro file---------------------------*/

/*----------------------------type define--------------------------*/

/*-----------------------------------------------------------------*/
class Ev_Thread_Manager
{
	static Ev_Thread_Manager *m_instance;

public: // api
	Ev_Thread_Manager();
	~Ev_Thread_Manager();
	static Ev_Thread_Manager *instance();
	ev_error init();


	Ev_Thread *spawn(thread_function_t thread_func_cb, void *args = NULL);

	void destroy_thread(Ev_Thread *thread);
	void destroy_all_thread();

public: // var

protected: // api

protected: // var

private: // api

private: // var
	vector<Ev_Thread *> m_threads;
};


#endif // __EV_THREAD_MANAGER_H__

