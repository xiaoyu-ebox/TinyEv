/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-3-11
 * Version     : v0.1
 * Description : 
 *******************************************************************/
/*----------------------------Head file----------------------------*/
#include "Ev_Handle.h"
#include "Ev_Vector.h"

/*----------------------------macro file---------------------------*/
#define __MODULE__						"[Handle]"

/*----------------------------type define--------------------------*/

/*----------------------------var define---------------------------*/

/*-----------------------------------------------------------------*/
Ev_Handle::Ev_Handle() :
	m_handle(INVALID_HANDLE),
	m_watcher(NULL)
{

}

Ev_Handle::~Ev_Handle()
{
	if(m_handle != INVALID_HANDLE) {
		close(m_handle);
		m_handle = INVALID_HANDLE;

		// 注销监听事件
	}
}

ev_error Ev_Handle::register_handle_event(ev_type_t events, handle_type_t type)
{
	return Ev_Vector::register_handle_event(this, events, type);
}

void Ev_Handle::deregister_handle_event()
{
	return Ev_Vector::deregister_handle_event(this);
}

ev_error Ev_Handle::write_data(uint8 *pdata, uint32 size)
{
	sint32 wsize = write(m_handle, pdata, size);

	return wsize == size ? EV_SUCCESS : EV_RW_ERR;
}


