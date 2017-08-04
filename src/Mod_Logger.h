/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-8-3
 * Version     : v0.1
 * Description : Mod_Logger header file
 *******************************************************************/
#ifndef __MOD_LOGGER_H__
#define __MOD_LOGGER_H__

/*----------------------------Head file----------------------------*/
#include "Ev_Logger.h"

/*----------------------------macro file---------------------------*/

/*----------------------------type define--------------------------*/

/*-----------------------------------------------------------------*/
class Mod_Logger
{
	static Mod_Logger *m_instance;

public: // api
	Mod_Logger();
	~Mod_Logger();
	static Mod_Logger *instance();
	ev_error init(log_record_t type = LOG_PRINTF_TO_CONSOLE, log_level_t level = LOG_LEVEL_INFO, const char *filename = NULL);

	void dbg(const char *format, ...);
	void info(const char *format, ...);
	void warning(const char *format, ...);
	void error(const char *format, ...);
	void hexdump(const uint8 *buf, uint32 size);

	void set_level(log_level_t level) {m_level = level;}

public: // var

protected: // api

protected: // var

private: // api

private: // var
	log_record_t m_type;
	log_level_t m_level;
	Ev_Logger *m_obj_logger;
};


#endif // __MOD_LOGGER_H__

