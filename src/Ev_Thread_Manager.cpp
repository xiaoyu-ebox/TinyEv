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
#include "Ev_Thread_Manager.h"

/*----------------------------macro file---------------------------*/
#define __MODULE__						"[Thread_Manager]"

/*----------------------------type define--------------------------*/

/*----------------------------var define---------------------------*/
Ev_Thread_Manager *Ev_Thread_Manager::m_instance = NULL;

/*-----------------------------------------------------------------*/
Ev_Thread_Manager *Ev_Thread_Manager::instance()
{
	if(m_instance == NULL)
		m_instance = new Ev_Thread_Manager();

	return m_instance;
}

Ev_Thread_Manager::Ev_Thread_Manager()
{

}

Ev_Thread_Manager::~Ev_Thread_Manager()
{
	destroy_all_thread();

	m_instance = NULL;
}

ev_error Ev_Thread_Manager::init()
{
	return EV_SUCCESS;
}

Ev_Thread *Ev_Thread_Manager::spawn(thread_function_t thread_func_cb, void *args)
{
	Ev_Thread *thread = new Ev_Thread;

	thread->spawn(thread_func_cb, args);
	m_threads.push_back(thread);

	return thread;
}

void Ev_Thread_Manager::destroy_thread(Ev_Thread *thread)
{
	ARGS_NULL_CHECK_RV(thread);

	vector<Ev_Thread *>::iterator it  = m_threads.begin();

	while(it != m_threads.end()) {
		if(*it == thread) {
			delete thread;
			it = m_threads.erase(it);
	
			break;
		}

		++it;
	}
}

void Ev_Thread_Manager::destroy_all_thread()
{
	vector<Ev_Thread *>::iterator it  = m_threads.begin();

	while(it != m_threads.end()) {
		delete (*it);

		it = m_threads.erase(it);
	}
}

