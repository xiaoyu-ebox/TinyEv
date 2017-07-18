/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-3-12
 * Version     : v0.1
 * Description : Ev_Stream header file
 *******************************************************************/
#ifndef __EV_STREAM_H__
#define __EV_STREAM_H__

/*----------------------------Head file----------------------------*/
#include "Ev_Handle.h"
#include "Ev_Fifo.h"

/*----------------------------macro file---------------------------*/

/*----------------------------type define--------------------------*/

/*-----------------------------------------------------------------*/
class Ev_Stream : public Ev_Handle, private Ev_Fifo
{
public: // api
	Ev_Stream(uint32 fifo_size = 1024, fifo_type_t type = CIRCULAR_FIFO);
	virtual ~Ev_Stream();


	// stream读取函数
	uint32 stream_read(uint8 *buffer, uint32 size);

	// stream试读函数(size不会减少)
	uint8 *stream_try_read(uint8 *buffer, uint32 *read_size, bool enough = true);
	uint8 *stream_try_read(uint8 *buffer, uint32 read_size);

	// stream容量
	uint32 stream_capacity();

	// stream已使用size
	uint32 stream_occupy();

	// 清空stream
	void stream_clean();
	
public: // var

protected: // api
	/*****************************************************************************
	 * 函数功能  : stream可读事件
	 * 输入参数  : size  可读的size
	 * 输出参数  : 无
	 * 返 回 值:  >0：读掉的缓冲size
	 			 <=0：错误码，即ev_error的值前面加负号。
	*****************************************************************************/
	virtual ev_error on_ev_stream_read(uint32 size) = 0;
	
	virtual ev_error on_ev_write() = 0;

	virtual ev_error on_ev_error() = 0;

protected: // var

private: // api
	ev_error on_ev_read();

private: // var

};


#endif // __EV_STREAM_H__

