/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-8-4
 * Version     : v0.1
 * Description : Ev_Logger_File header file
 *******************************************************************/
#ifndef __EV_LOGGER_FILE_H__
#define __EV_LOGGER_FILE_H__

/*----------------------------Head file----------------------------*/
#include "Ev_Logger.h"

/*----------------------------macro file---------------------------*/

/*----------------------------type define--------------------------*/

/*-----------------------------------------------------------------*/
class Ev_Logger_File : public Ev_Logger
{
public: // api
	Ev_Logger_File();
	~Ev_Logger_File();


	ev_error init(const void *args = NULL);

	void dbg(const char *format, va_list ap);
	void print(const char *format, ...);

public: // var

protected: // api

protected: // var

private: // api

private: // var
	FILE *m_logfile;
	char *m_w_buffer;
};


#endif // __EV_LOGGER_FILE_H__

