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
#include "Ev_Logger_Syslog.h"

#include <syslog.h>

/*----------------------------macro file---------------------------*/

/*----------------------------type define--------------------------*/

/*----------------------------var define---------------------------*/

/*-----------------------------------------------------------------*/
Ev_Logger_Syslog::Ev_Logger_Syslog()
{

}

Ev_Logger_Syslog::~Ev_Logger_Syslog()
{
	closelog();
}

ev_error Ev_Logger_Syslog::init(const void *args)
{
	const char *identify = (char *)args;

	openlog(identify, LOG_CONS | LOG_PID, 0);
}

void Ev_Logger_Syslog::dbg(const char *format, va_list ap)
{
	vsyslog(LOG_DEBUG, format, ap);
}

void Ev_Logger_Syslog::info(const char *format, va_list ap)
{
	vsyslog(LOG_INFO, format, ap);
}

void Ev_Logger_Syslog::warning(const char *format, va_list ap)
{
	vsyslog(LOG_WARNING, format, ap);
}

void Ev_Logger_Syslog::error(const char *format, va_list ap)
{
	vsyslog(LOG_ERR, format, ap);
}

void Ev_Logger_Syslog::print(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	vsyslog(LOG_DEBUG, format, ap);
	va_end(ap);
}

