/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All righm_ts reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-3-12
 * Version     : v0.1
 * Description : 
 *******************************************************************/
/*----------------------------Head file----------------------------*/
#include "Ev_Fifo.h"

/*----------------------------static func--------------------------*/
static inline bool is_power_of_2(uint32 n);
static uint32 roundup_power_of_two(uint32 val);

/*----------------------------macro file---------------------------*/
#define __MODULE__						"[Fifo]"

/*----------------------------type define--------------------------*/

/*----------------------------var define---------------------------*/

/*-----------------------------------------------------------------*/
Ev_Fifo::Ev_Fifo(uint32 size, uint32 wait_msec, fifo_type_t type) :
	m_type(type),
	m_buffer(NULL)
{
	if(!is_power_of_2(size))
		size = roundup_power_of_two(size);

	// 分配fifo buffer
	if((m_buffer = ev_new(uint8, size)) == NULL)
		return;

	m_wt.tv_sec = wait_msec / 1000;
	m_wt.tv_nsec = (wait_msec % 1000) * 1000;

	pthread_cond_init(&m_cond, NULL);
	pthread_mutex_init(&m_mutex, NULL);
	pthread_spin_init(&m_lock, 0);

	m_in = m_out = 0;
	m_size = size;

	//EV_PRINTF_DBG("%s fifo, wt:%u, size:%u", type == GENERAL_FIFO ? "general" : "circular", wait_msec, m_size);
}

Ev_Fifo::~Ev_Fifo()
{
	// 释放
	pthread_cond_destroy(&m_cond);
	pthread_mutex_destroy(&m_mutex);
	pthread_spin_destroy(&m_lock);

	if(m_buffer)
		ev_free(m_buffer);
	m_buffer = NULL;
}

uint32 Ev_Fifo::fifo_push(const uint8 *buffer, uint32 push_size)
{
	int ret;
	uint32 l;

	if(buffer == NULL || push_size == 0)
		return 0;

getm_lock_again:
	pthread_spin_lock(&m_lock);

	//EV_PRINTF_DBG("m_in:%d m_out:%d", m_in, m_out);
	l = (m_type == GENERAL_FIFO) ? (m_size - m_in) : (m_size - m_in + m_out);
	if(l < push_size) {
		struct timespec ts;

		// 如果等待时间为0，则直接返回
		if(m_wt.tv_sec == 0 && m_wt.tv_nsec == 0) {
			pthread_spin_unlock(&m_lock);
			return 0;
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
			EV_PRINTF_WARN("put timeout:%d.", errno);
			return 0;
		}
		goto getm_lock_again;
	}
	else {
	    /*
	    * Ensure that we sample the m_nOut index -before- we
	    * start putting bytes into the Unm_lockQueue.
	    */
		__sync_synchronize();

		if(m_type == GENERAL_FIFO) {
			memcpy(m_buffer + m_in, buffer, push_size);
		}
		else {
			/* first put the data starting from in to buffer end */
			l = MIN(push_size, m_size - (m_in & (m_size - 1)));
			memcpy(m_buffer + (m_in & (m_size - 1)), buffer, l);

			/* then put the rest (if any) at the beginning of the buffer */
			memcpy(m_buffer, buffer + l, push_size - l);
		}

		/*
		 * Ensure that we add the bytes to the kfifo -before-
		 * we update the in index.
		*/
		__sync_synchronize();

		m_in += push_size;

		// 为空时
		if(m_iswait) {
			m_iswait = false;
			pthread_mutex_lock(&m_mutex);
			pthread_cond_signal(&m_cond);
			pthread_mutex_unlock(&m_mutex);
		}

		pthread_spin_unlock(&m_lock);
	}

	return push_size;
}

uint32 Ev_Fifo::fifo_pop(uint8 *buffer, uint32 pop_size)
{
	int ret;
	uint32 l;

	if(buffer == NULL || pop_size == 0)
		return 0;

getm_lock_again:
	pthread_spin_lock(&m_lock);

	l = m_in - m_out;
	if(l < pop_size) {
		struct timespec ts;

		// 如果等待时间为0，则直接返回
		if(m_wt.tv_sec == 0 && m_wt.tv_nsec == 0) {
			pthread_spin_unlock(&m_lock);
			return 0;
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
			EV_PRINTF_WARN("put timeout:%d.", errno);
			return 0;
		}
		goto getm_lock_again;
	}

	/*
	 * Ensure that we sample the in index -before- we
	 * start removing bytes from the kfifo.
	 */
	__sync_synchronize();

	if(m_type == GENERAL_FIFO) {
		memcpy(buffer, m_buffer + m_out, pop_size);
	}
	else {
		/* first get the data from out until the end of the buffer */
		l = MIN(pop_size, m_size - (m_out & (m_size - 1)));
		memcpy(buffer, m_buffer + (m_out & (m_size - 1)), l);

		/* then get the rest (if any) from the beginning of the buffer */
		memcpy(buffer+l, m_buffer, pop_size - l);
	}

	/*
	 * Ensure that we remove the bytes from the kfifo -before-
	 * we update the out index.
	 */
	__sync_synchronize();

	m_out += pop_size;
	if(m_type == GENERAL_FIFO && m_out == m_in)
		m_out = m_in = 0;

	// 为满时
	if(m_iswait) {
		m_iswait = false;
		pthread_mutex_lock(&m_mutex);
		pthread_cond_signal(&m_cond);
		pthread_mutex_unlock(&m_mutex);
	}	
	pthread_spin_unlock(&m_lock);

	return pop_size;
}

/*****************************************************************************
 * 函数功能  : 试读取缓冲(fifo size不减小)
 * 输入参数  : *buffer     存放读取的数据(fifo类型为普通时，不拷贝数据到buffer)
               *read_size  读取的个数
               enough	   为true时，可读size不够*read_size时，返回为NULL，
               			   为false时，可读size不够*read_size时，*read_size为赋值为可读size
 * 输出参数  : read_size   实际读取的个数
 * 返 回 值  : 当可读大小不够read_size或者*read_size为0时，返回NULL
*****************************************************************************/
uint8 *Ev_Fifo::fifo_try_read(uint8 *buffer, uint32 *read_size, bool enough)
{
	uint8 *p;
	uint32 l;

	ARGS_NULL_CHECK_RN(read_size);
	CONDITION_CHECK_RN(*read_size == 0);
	// 圆形fifo时，buffer不能为NULL
	if(m_type == CIRCULAR_FIFO)
		ARGS_NULL_CHECK_RN(buffer);

	pthread_spin_lock(&m_lock);

	if(m_in - m_out < *read_size) {
		if(enough) {
			pthread_spin_unlock(&m_lock);
			return NULL;
		}

		*read_size = m_in - m_out;
	}

	if(m_type == GENERAL_FIFO) {
		p = m_buffer + m_out;
	}
	else {
		/*
		 * Ensure that we sample the in index -before- we
		 * start removing bytes from the kfifo.
		 */
		__sync_synchronize();

		/* first get the data from out until the end of the buffer */
		l = MIN(*read_size, m_size - (m_out & (m_size - 1)));
		memcpy(buffer, m_buffer + (m_out & (m_size - 1)), l);

		/* then get the rest (if any) from the beginning of the buffer */
		memcpy(buffer+l, m_buffer, *read_size - l);

		/*
		 * Ensure that we remove the bytes from the kfifo -before-
		 * we update the out index.
		 */
		__sync_synchronize();

		p = buffer;
	}

	pthread_spin_unlock(&m_lock);

	return p;
}

/*****************************************************************************
 * 函数功能  : 试读取缓冲(fifo size不减小)
 * 输入参数  : *buffer     	  存放读取的数据(fifo类型为普通时，不拷贝数据到buffer)
               read_size  读取的个数
 * 输出参数  : 无
 * 返 回 值  : 当可读大小不够read_size或者*read_size为0时，返回NULL
*****************************************************************************/
uint8 *Ev_Fifo::fifo_try_read(uint8 *buffer, uint32 read_size)
{
	return fifo_try_read(buffer, &read_size);
}

ev_error Ev_Fifo::fifo_discard(uint32 size)
{
	pthread_spin_lock(&m_lock);

	if(m_in - m_out < size) {
		pthread_spin_unlock(&m_lock);
		return EV_RW_ERR;
	}

	m_out += size;
	if(m_type == GENERAL_FIFO && m_out == m_in)
		m_out = m_in = 0;

	pthread_spin_unlock(&m_lock);

	return EV_SUCCESS;
}

uint32 Ev_Fifo::fifo_get_capacity()
{
	return m_size;
}

uint32 Ev_Fifo::fifo_get_occupy()
{
	pthread_spin_lock(&m_lock);
	uint32 capacity = m_in - m_out;
	pthread_spin_unlock(&m_lock);

	return capacity;
}

bool Ev_Fifo::fifo_is_empty()
{
	return fifo_get_occupy() ? false : true;
}

void Ev_Fifo::fifo_clean()
{
	pthread_spin_lock(&m_lock);

	m_in = m_out = 0;

	pthread_spin_unlock(&m_lock);
}

static inline bool is_power_of_2(uint32 n)
{
	return ((n != 0) && ((n & (n - 1)) == 0));
}

static uint32 roundup_power_of_two(uint32 val)
{
	if((val & (val-1)) == 0)
		return val;

	uint32 maxuint = (uint32)((uint32)~0);
	uint32 andv = ~(maxuint & (maxuint >> 1));
	while((andv & val) == 0)
		andv >>= 1;

	return andv << 1;
}

