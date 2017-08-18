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
#include "Ev_Stream.h"

/*----------------------------macro file---------------------------*/
#define __MODULE__						"[Stream]"

/*----------------------------type define--------------------------*/

/*----------------------------var define---------------------------*/

/*-----------------------------------------------------------------*/
Ev_Stream::Ev_Stream(uint32 fifo_size, fifo_type_t type) :
	Ev_Fifo(fifo_size, 0, type),
	m_recv_buf(NULL)
{
	m_recv_buf = ev_new(uint8, STREAM_BUFFER_DEF_SIZE);
}

Ev_Stream::~Ev_Stream()
{
	if(m_recv_buf) {
		ev_free(m_recv_buf);
		m_recv_buf = NULL;
	}
}

ev_error Ev_Stream::on_ev_read()
{
	int ret;
	bool has_data = false;
	ssize_t size;

	while(1) {
		size = read(m_handle, m_recv_buf, STREAM_BUFFER_DEF_SIZE);
		if(size > 0) {
			// 表示接受数据完毕，返回值即是接受到的字节数
			fifo_push(m_recv_buf, size);
			has_data = true;
		}
		else if(size == 0) {
			// 表示连接已经正常断开
			EV_PRINTF_ERR("recv err1.");
			
			if(has_data) {
				ret = on_ev_stream_read(stream_occupy());
				if(ret > 0) {
					// 读掉ret个字节缓冲数据
					fifo_discard(ret);
				}
			}

			// 通知服务端
			return on_ev_error();
		}
		else {
			if(errno == EAGAIN) {
				// 表示 recv 操作还没执行完成
				break;
			}
			else {
				// 表示 recv 操作遇到系统错误 errno
				// 测试无法连接socket时，会执行到这里。
				EV_PRINTF_ERR("recv err2.");

				// 通知服务端
				return on_ev_error();
			}
		}
	}

	ret = on_ev_stream_read(stream_occupy());
	if(ret > 0) {
		// 读掉ret个字节缓冲数据
		fifo_discard(ret);

		return EV_SUCCESS;
	}
	
	return -ret;
}

uint32 Ev_Stream::stream_read(uint8 *buffer, uint32 size)
{
	return fifo_pop(buffer, size);
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
uint8 *Ev_Stream::stream_try_read(uint8 *buffer, uint32 *read_size, bool enough)
{
	return fifo_try_read(buffer, read_size, enough);
}

/*****************************************************************************
 * 函数功能  : 试读取缓冲(fifo size不减小)
 * 输入参数  : *buffer     	  存放读取的数据(fifo类型为普通时，不拷贝数据到buffer)
               read_size  读取的个数
 * 输出参数  : 无
 * 返 回 值  : 当可读大小不够read_size或者*read_size为0时，返回NULL
*****************************************************************************/
uint8 *Ev_Stream::stream_try_read(uint8 *buffer, uint32 read_size)
{
	return stream_try_read(buffer, &read_size);
}

uint32 Ev_Stream::stream_capacity()
{
	return fifo_get_capacity();
}

uint32 Ev_Stream::stream_occupy()
{
	return fifo_get_occupy();
}

void Ev_Stream::stream_clean()
{
	fifo_clean();
}

