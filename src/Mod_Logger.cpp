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
#include "Ev_Logger_File.h"
#include "Ev_Time.h"

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
	m_type(LOG_PRINTF_TO_CONSOLE),
	m_level(LOG_LEVEL_DBG),
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

ev_error Mod_Logger::init(log_record_t type, log_level_t level, const char *args)
{
	m_type = type;

	if(m_type == LOG_PRINTF_TO_CONSOLE)
		m_obj_logger = new Ev_Logger_Console();
	else if(m_type == LOG_RECORD_BY_SYSLOG)
		m_obj_logger = new Ev_Logger_Syslog();
	else if(m_type == LOG_RECORD_TO_FILE)
		m_obj_logger = new Ev_Logger_File();

	return m_obj_logger->init(args);
}

void Mod_Logger::dbg(const char *format, ...)
{
	if(m_level > LOG_LEVEL_DBG)
		return;

	va_list ap;
	va_start(ap, format);
	m_obj_logger->dbg(format, ap);
	va_end(ap);
}

void Mod_Logger::info(const char *format, ...)
{
	if(m_level > LOG_LEVEL_INFO)
		return;

	va_list ap;
	va_start(ap, format);
	if(m_type == LOG_RECORD_BY_SYSLOG)
		m_obj_logger->info(format, ap);
	else
		m_obj_logger->dbg(format, ap);
	va_end(ap);
}

void Mod_Logger::warning(const char *format, ...)
{
	if(m_level > LOG_LEVEL_WARNING)
		return;

	va_list ap;
	va_start(ap, format);
	if(m_type == LOG_RECORD_BY_SYSLOG)
		m_obj_logger->warning(format, ap);
	else
		m_obj_logger->dbg(format, ap);
	va_end(ap);
}

void Mod_Logger::error(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	if(m_type == LOG_RECORD_BY_SYSLOG)
		m_obj_logger->error(format, ap);
	else
		m_obj_logger->dbg(format, ap);
	va_end(ap);
}

void Mod_Logger::printf(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	m_obj_logger->vprint(format, ap);
	va_end(ap);
}

void Mod_Logger::hexdump(const char *identify, const uint8 *buf, uint32 size, bool timestamp, bool lf)
{
	char temp_buf[256 * 3 + 1];
	char *p_temp_buf;
	uint16 temp_size;

	if(m_type == LOG_RECORD_BY_SYSLOG) {
		m_obj_logger->print(identify);
	}
	else {
		if(timestamp) {
			struct tm t;
			Ev_Time::current_time(&t);
			m_obj_logger->print(CTRL_F_GREEN "[%02u-%02u %02u:%02u:%02u]" CTRL_CLOSE_ALL "%s ", t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec, identify);
		}
		else {
			m_obj_logger->print("%s ", identify);
		}
	}

	while(size) {
		p_temp_buf = temp_buf;
		temp_size = size > 256 ? 256 : size;
		size -= temp_size;

		while(temp_size--) {
			sprintf(p_temp_buf, "%02x ", *buf++);
			p_temp_buf += 3;
		}
		*p_temp_buf = '\0';
		m_obj_logger->print(temp_buf);
	}

	if(lf)
		m_obj_logger->print("\n");
}

void Mod_Logger::hexdump_reverse(const char *identify, const uint8 *buf, uint32 size, bool timestamp, bool lf)
{
	char temp_buf[256 * 3 + 1];
	char *p_temp_buf;
	uint8 temp_size;

	if(m_type == LOG_RECORD_BY_SYSLOG) {
		m_obj_logger->print(identify);
	}
	else {
		if(timestamp) {
			struct tm t;
			Ev_Time::current_time(&t);
			m_obj_logger->print(CTRL_F_GREEN "[%02u-%02u %02u:%02u:%02u]" CTRL_CLOSE_ALL "%s ", t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec, identify);
		}
		else {
			m_obj_logger->print("%s ", identify);
		}
	}

	buf += (size-1);
	while(size) {
		p_temp_buf = temp_buf;
		temp_size = size > 256 ? 256 : size;
		size -= temp_size;

		while(temp_size--) {
			sprintf(p_temp_buf, "%02x ", *buf--);
			p_temp_buf += 3;
		}
		*p_temp_buf = '\0';
		m_obj_logger->print(temp_buf);
	}

	if(lf)
		m_obj_logger->print("\n");
}


