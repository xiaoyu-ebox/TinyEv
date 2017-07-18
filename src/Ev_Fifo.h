/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-3-12
 * Version     : v0.1
 * Description : Ev_Fifo header file
 *******************************************************************/
#ifndef __EV_FIFO_H__
#define __EV_FIFO_H__

/*----------------------------Head file----------------------------*/
#include "Ev_Base_Include.h"
#include "Ev_Time.h"

#include <pthread.h>
#include <semaphore.h>

/*----------------------------macro file---------------------------*/
#ifndef MIN
#define MIN(x, y)	((x) < (y) ? (x) : (y))
#endif
#ifndef MAX
#define MAX(x, y)	((x) < (y) ? (y) : (x))
#endif

/*----------------------------type define--------------------------*/
typedef enum {
	GENERAL_FIFO,		// 普通缓冲，读fifo时，buffer可以为NULL
	CIRCULAR_FIFO		// 圆形缓冲, 读fifo时，buffer不能为NULL
} fifo_type_t;


/*-----------------------------------------------------------------*/
class Ev_Fifo
{
public: // api
	Ev_Fifo(uint32 size, uint32 wait_msec = 0, fifo_type_t type = CIRCULAR_FIFO);
	virtual ~Ev_Fifo();

	uint32 fifo_push(const uint8 *buffer, uint32 push_size);
	uint32 fifo_pop(uint8 *buffer, uint32 pop_size);

	uint8 *fifo_try_read(uint8 *buffer, uint32 *read_size, bool enough = true);
	uint8 *fifo_try_read(uint8 *buffer, uint32 read_size);

	ev_error fifo_discard(uint32 size);

	uint32 fifo_get_capacity();
	uint32 fifo_get_occupy();
	bool fifo_is_empty();
	void fifo_clean();

public: // var

protected: // api

protected: // var

private: // api

private: // var
	fifo_type_t m_type;				// 缓冲类型
	uint8	*m_buffer;				// 缓冲区
	uint32	m_size;					// 缓冲size
	uint32	m_in;					// int计数
	uint32	m_out;					// out计数

	pthread_mutex_t 	m_mutex;	// 条件变量锁
	pthread_cond_t		m_cond;		// 条件变量

	bool 				m_iswait;
	struct timespec		m_wt;		// 等待时间
	pthread_spinlock_t	m_lock;		// 线程锁
};


#endif // __EV_FIFO_H__

