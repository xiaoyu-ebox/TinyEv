/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-8-3
 * Version     : v0.1
 * Description : Ev_Logger_Console header file
 *******************************************************************/
#ifndef __EV_LOGGER_CONSOLE_H__
#define __EV_LOGGER_CONSOLE_H__

/*----------------------------Head file----------------------------*/
#include "Ev_Logger.h"

/*----------------------------macro file---------------------------*/

/*----------------------------type define--------------------------*/

/*-----------------------------------------------------------------*/
class Ev_Logger_Console : public Ev_Logger
{
public: // api
	Ev_Logger_Console() {}
	~Ev_Logger_Console() {}

	void dbg(const char *format, va_list ap);
	void vprint(const char *format, va_list ap);
	void print(const char *format, ...);

public: // var

protected: // api

protected: // var

private: // api

private: // var

};


#endif // __EV_LOGGER_CONSOLE_H__

