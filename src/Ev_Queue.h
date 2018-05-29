/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2018-5-1
 * Version     : v0.1
 * Description : Ev_Queue header file
 *******************************************************************/
#ifndef __EV_QUEUE_H__
#define __EV_QUEUE_H__

/*----------------------------Head file----------------------------*/
#include "Ev_Base_Include.h"
#include "Ev_Time.h"

#include <pthread.h>
#include <semaphore.h>

#include <queue>

using namespace std;

/*----------------------------macro file---------------------------*/

/*----------------------------type define--------------------------*/

/*-----------------------------------------------------------------*/
template<typename T>
class Ev_Queue
{
public: // api
	Ev_Queue(uint32 wait_msec = 3600000);
	~Ev_Queue();

	void push(T &data);
	void pop();
	ev_error get_front_data(T &data);
	ev_error get_back_data(T &data);

	uint32 get_size();

public: // var

protected: // api

protected: // var

private: // api

private: // var
	queue<T> m_queue;
	uint32 m_wait_msec;

	pthread_mutex_t 	m_mutex;	// 条件变量锁
	pthread_cond_t		m_cond;		// 条件变量

	bool 				m_iswait;
	struct timespec		m_wt;		// 等待时间
	pthread_spinlock_t	m_lock;		// 线程锁
};

#include "Ev_Queue.cpp"

#endif // __EV_QUEUE_H__

