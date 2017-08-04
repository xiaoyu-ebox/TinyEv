/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-8-3
 * Version     : v0.1
 * Description : 
 *******************************************************************/
/*----------------------------Head file----------------------------*/
#include "Ev_Logger_Console.h"
#include "Ev_Time.h"

/*----------------------------macro file---------------------------*/

/*----------------------------type define--------------------------*/

/*----------------------------var define---------------------------*/

/*-----------------------------------------------------------------*/
void Ev_Logger_Console::dbg(const char *format, va_list ap)
{
	struct tm t;
	Ev_Time::current_time(&t);
	printf("[%02u-%02u %02u:%02u:%02u]", t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);

	vprintf(format, ap);
}

void Ev_Logger_Console::print(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	vprintf(format, ap);
	va_end(ap);
}

