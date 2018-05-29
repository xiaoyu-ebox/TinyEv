/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-8-3
 * Version     : v0.1
 * Description : Ev_Logger header file
 *******************************************************************/
#ifndef __EV_LOGGER_H__
#define __EV_LOGGER_H__

/*----------------------------Head file----------------------------*/
#include "Ev_Config.h"
#include "Ev_Error.h"
#include "Console_Ctrl.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

/*----------------------------macro file---------------------------*/
#define LOG_FILENAME_MAX_LENGTH			256

/*----------------------------type define--------------------------*/
typedef enum {
	LOG_PRINTF_TO_CONSOLE,
	LOG_RECORD_BY_SYSLOG,
	LOG_RECORD_TO_FILE
} log_record_t;

typedef enum {
	LOG_LEVEL_DBG,
	LOG_LEVEL_INFO,
	LOG_LEVEL_WARNING,
	LOG_LEVEL_ERROR
} log_level_t;


/*-----------------------------------------------------------------*/
class Ev_Logger
{
public: // api
	Ev_Logger() {}
	virtual ~Ev_Logger() {}


	virtual ev_error init(const void *args = NULL) {return EV_SUCCESS;}

	virtual void dbg(const char *format, va_list ap) {}
	virtual void info(const char *format, va_list ap) {}
	virtual void warning(const char *format, va_list ap) {}
	virtual void error(const char *format, va_list ap) {}
	virtual void vprint(const char *format, va_list ap) {}
	virtual void print(const char *format, ...) {}


public: // var

protected: // api

protected: // var

private: // api

private: // var

};


#endif // __EV_LOGGER_H__

