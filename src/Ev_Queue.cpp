/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2018-5-1
 * Version     : v0.1
 * Description : 
 *******************************************************************/
/*----------------------------Head file----------------------------*/
//#include "Ev_Queue.h"

using namespace std;

/*----------------------------macro file---------------------------*/

/*----------------------------type define--------------------------*/

/*----------------------------var define---------------------------*/

/*-----------------------------------------------------------------*/
template<typename T>
Ev_Queue<T>::Ev_Queue(uint32 wait_msec) :
	m_wait_msec(wait_msec)
{
	m_wt.tv_sec = wait_msec / 1000;
	m_wt.tv_nsec = (wait_msec % 1000) * 1000;

	pthread_cond_init(&m_cond, NULL);
	pthread_mutex_init(&m_mutex, NULL);
	pthread_spin_init(&m_lock, 0);
}

template<typename T>
Ev_Queue<T>::~Ev_Queue()
{
	// 释放
	pthread_cond_destroy(&m_cond);
	pthread_mutex_destroy(&m_mutex);
	pthread_spin_destroy(&m_lock);
}

template<typename T>
void Ev_Queue<T>::push(T &data)
{
	pthread_spin_lock(&m_lock);

	m_queue.push(data);

	// 为空时
	if(m_iswait) {
		m_iswait = false;
		pthread_mutex_lock(&m_mutex);
		pthread_cond_signal(&m_cond);
		pthread_mutex_unlock(&m_mutex);
	}

	pthread_spin_unlock(&m_lock);
}

template<typename T>
void Ev_Queue<T>::pop()
{
	pthread_spin_lock(&m_lock);
	
	m_queue.pop();

	pthread_spin_unlock(&m_lock);
}

template<typename T>
ev_error Ev_Queue<T>::get_front_data(T &data)
{
	int ret;

getm_lock_again:
	pthread_spin_lock(&m_lock);

	if(m_queue.size() <= 0) {
		struct timespec ts;

		// 如果等待时间为0，则直接返回
		if(m_wt.tv_sec == 0 && m_wt.tv_nsec == 0) {
			pthread_spin_unlock(&m_lock);
			return EV_CONTAINER_EMPTY;
		}

		m_iswait = true;
		pthread_mutex_lock(&m_mutex);
		Ev_Time::future_time(&ts, &m_wt);

		// 解锁
		pthread_spin_unlock(&m_lock);

		// 等待条件变量
		ret = pthread_cond_timedwait(&m_cond, &m_mutex, &ts);
		pthread_mutex_unlock(&m_mutex);
		if(ret != 0) {
			EV_PRINTF_RAW("Ev_Queue:put timeout:%d.", errno);
			return EV_RW_TIMEOUT;
		}
		goto getm_lock_again;
	}

	data = m_queue.front();

	pthread_spin_unlock(&m_lock);

	return EV_SUCCESS;
}

template<typename T>
ev_error Ev_Queue<T>::get_back_data(T &data)
{
	int ret;

getm_lock_again:
	pthread_spin_lock(&m_lock);

	if(m_queue.size() <= 0) {
		struct timespec ts;

		// 如果等待时间为0，则直接返回
		if(m_wt.tv_sec == 0 && m_wt.tv_nsec == 0) {
			pthread_spin_unlock(&m_lock);
			return EV_CONTAINER_EMPTY;
		}

		m_iswait = true;
		pthread_mutex_lock(&m_mutex);
		Ev_Time::future_time(&ts, &m_wt);

		// 解锁
		pthread_spin_unlock(&m_lock);

		// 等待条件变量
		ret = pthread_cond_timedwait(&m_cond, &m_mutex, &ts);
		pthread_mutex_unlock(&m_mutex);
		if(ret != 0) {
			EV_PRINTF_RAW("Ev_Queue:put timeout:%d.", errno);
			return EV_RW_TIMEOUT;
		}
		goto getm_lock_again;
	}

	data = m_queue.back();

	pthread_spin_unlock(&m_lock);

	return EV_SUCCESS;
}

template<typename T>
uint32 Ev_Queue<T>::get_size()
{
	pthread_spin_lock(&m_lock);
	
	return m_queue.size();

	pthread_spin_unlock(&m_lock);
}


