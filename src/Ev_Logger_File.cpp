/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-8-4
 * Version     : v0.1
 * Description : 
 *******************************************************************/
/*----------------------------Head file----------------------------*/
#include "Ev_Logger_File.h"
#include "Ev_Time.h"

/*----------------------------macro file---------------------------*/

/*----------------------------type define--------------------------*/

/*----------------------------var define---------------------------*/

/*-----------------------------------------------------------------*/
Ev_Logger_File::Ev_Logger_File() :
	m_logfile(NULL),
	m_w_buffer(NULL)
{

}

Ev_Logger_File::~Ev_Logger_File()
{
	if(m_w_buffer) {
		ev_free(m_w_buffer);
		m_w_buffer = NULL;
	}
}

ev_error Ev_Logger_File::init(const void *args)
{
	const char *filename = (const char *)args;

	if(args == NULL)
		return EV_ARGS_ERR;

	m_w_buffer = ev_new(char, 2048);
	if(m_w_buffer == NULL)
		return EV_NOMEM;

	m_logfile = fopen(filename, "a");
	if(m_logfile == NULL) {
		ev_free(m_w_buffer);
		m_w_buffer = NULL;
		return EV_DEV_OPEN_ERR;
	}

	return EV_SUCCESS;
}

void Ev_Logger_File::dbg(const char *format, va_list ap)
{
	struct tm t;
	Ev_Time::current_time(&t);

	fprintf(m_logfile, "[%02u-%02u %02u:%02u:%02u]", t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
	vsprintf(m_w_buffer, format, ap);
	fprintf(m_logfile, "%s", m_w_buffer);
	fflush(m_logfile);
}

void Ev_Logger_File::print(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	vsprintf(m_w_buffer, format, ap);
	fprintf(m_logfile, "%s", m_w_buffer);
	va_end(ap);
}

