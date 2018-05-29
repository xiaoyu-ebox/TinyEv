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
#define __DBG								""
#define __INFO								""
#define __WARN								""
#define __ERR								""

#define MOD_COLOR_S							CTRL_F_BLUE
#define MOD_COLOR_E							CTRL_CLOSE_ALL

/*----------------------------type define--------------------------*/

/*-----------------------------------------------------------------*/
class Mod_Logger
{
	static Mod_Logger *m_instance;

public: // api
	Mod_Logger();
	~Mod_Logger();
	static Mod_Logger *instance();

	/*****************************************************************************
	 * 函数功能  : logger初始化函数
	 * 输入参数  : type = LOG_PRINTF_TO_CONSOLE  log写入方式
	             level = LOG_LEVEL_INFO        log写入级别
	             *args = NULL             	   附属参数
	               		当type = LOG_PRINTF_TO_CONSOLE时：args无用
	               		当type = LOG_RECORD_BY_SYSLOG时：args为logger的标识
	               		当type = LOG_RECORD_TO_FILE：args为文件路径
	 * 输出参数  : 无
	 * 返 回 值  : ev_error
	*****************************************************************************/
	ev_error init(log_record_t type = LOG_PRINTF_TO_CONSOLE, log_level_t level = LOG_LEVEL_INFO, const char *args = NULL);

	void dbg(const char *format, ...);
	void info(const char *format, ...);
	void warning(const char *format, ...);
	void error(const char *format, ...);
	void printf(const char *format, ...);
	void hexdump(const char *identify, const uint8 *buf, uint32 size, bool timestamp = true, bool lf = true);
	void hexdump_reverse(const char *identify, const uint8 *buf, uint32 size, bool timestamp = true, bool lf = true);
	
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

