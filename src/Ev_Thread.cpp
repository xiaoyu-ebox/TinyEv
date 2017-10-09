/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-8-18
 * Version     : v0.1
 * Description : 
 *******************************************************************/
/*----------------------------Head file----------------------------*/
#include "Ev_Thread.h"

/*----------------------------macro file---------------------------*/
#define __MODULE__						"[Thread]"

/*----------------------------type define--------------------------*/

/*----------------------------var define---------------------------*/

/*-----------------------------------------------------------------*/
Ev_Thread::Ev_Thread() :
	m_args(NULL),
	m_thread_function(NULL),
	m_pid(0)
{

}

Ev_Thread::~Ev_Thread()
{
	m_exit = true;
	pthread_join(m_pid, NULL);
}

void *thread_routine(void *args)
{
	Ev_Thread *obj = (Ev_Thread *)args;

	EV_PRINTF_DBG("pid:%p running.", obj);

	obj->m_exit = false;
	obj->m_exit_code = 0;

	if(obj->m_thread_function)
		obj->m_exit_code = (unsigned long)obj->m_thread_function(obj->m_args, &obj->m_exit);
	obj->m_exit = true;

	EV_PRINTF_DBG("pid:%p exit", obj);
}

pthread_t Ev_Thread::spawn(thread_function_t thread_func_cb, void *args)
{
	m_args = args;
	m_thread_function = thread_func_cb;
	pthread_create(&m_pid, NULL, thread_routine, this);

	return m_pid;
}

