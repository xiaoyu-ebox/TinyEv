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


	ev_error init(const void *program_name = NULL);

	void dbg(const char *format, va_list ap);
	void vprint(const char *format, va_list ap);
	void print(const char *format, ...);

public: // var

protected: // api

protected: // var

private: // api
	ev_error log_dir_init(const char *program_name);
	ev_error get_max_index(const char *dir_path, uint32 &max_index);

private: // var
	FILE *m_logfile;
	char *m_file_name;
	char *m_w_buffer;
};


#endif // __EV_LOGGER_FILE_H__

