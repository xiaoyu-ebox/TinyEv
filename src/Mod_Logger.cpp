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
#include "Mod_Logger.h"
#include "Ev_Logger_Console.h"
#include "Ev_Logger_Syslog.h"


/*----------------------------macro file---------------------------*/

/*----------------------------type define--------------------------*/

/*----------------------------var define---------------------------*/
Mod_Logger *Mod_Logger::m_instance = NULL;

/*-----------------------------------------------------------------*/
Mod_Logger *Mod_Logger::instance()
{
	if(m_instance == NULL)
		m_instance = new Mod_Logger();

	return m_instance;
}

Mod_Logger::Mod_Logger() :
	m_obj_logger(NULL)
{

}

Mod_Logger::~Mod_Logger()
{
	if(m_obj_logger) {
		delete m_obj_logger;
		m_obj_logger = NULL;
	}
	
	m_instance = NULL;
}

ev_error Mod_Logger::init(log_record_t type, log_level_t level, const char *filename)
{
	if(type == LOG_PRINTF_TO_CONSOLE)
		m_obj_logger = new Ev_Logger_Console();
	else if(type == LOG_RECORD_BY_SYSLOG)
		m_obj_logger = new Ev_Logger_Syslog();

#if 0
	if(m_type == LOG_RECORD_TO_FILE) {
		m_filename = ev_new(char, LOG_FILENAME_MAX_LENGTH);

		memset(m_filename, 0, LOG_FILENAME_MAX_LENGTH);
		strncpy(m_filename, filename, LOG_FILENAME_MAX_LENGTH-1);
		m_filename[LOG_FILENAME_MAX_LENGTH-1] = '\0';
	}
#endif
}

void Mod_Logger::dbg(const char *format, ...)
{
	if(m_level > LOG_LEVEL_DBG)
		return;

	va_list ap;
	int cnt;

	va_start(ap, format);
	m_obj_logger->dbg(format, ap);
	va_end(ap);
}

void Mod_Logger::info(const char *format, ...)
{
	if(m_level > LOG_LEVEL_INFO)
		return;

	va_list ap;
	int cnt;

	va_start(ap, format);
	m_obj_logger->info(format, ap);
	va_end(ap);
}

void Mod_Logger::warning(const char *format, ...)
{
	if(m_level > LOG_LEVEL_WARNING)
		return;

	va_list ap;
	int cnt;

	va_start(ap, format);
	m_obj_logger->warning(format, ap);
	va_end(ap);
}

void Mod_Logger::error(const char *format, ...)
{
	va_list ap;
	int cnt;

	va_start(ap, format);
	m_obj_logger->error(format, ap);
	va_end(ap);
}

void Mod_Logger::hexdump(const uint8 *buf, uint32 size)
{
	m_obj_logger->hexdump(buf, size);
}

