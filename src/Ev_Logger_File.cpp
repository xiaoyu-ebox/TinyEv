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
#include <dirent.h>

/*----------------------------macro file---------------------------*/

/*----------------------------type define--------------------------*/

/*----------------------------var define---------------------------*/

/*-----------------------------------------------------------------*/
Ev_Logger_File::Ev_Logger_File() :
	m_logfile(NULL),
	m_file_name(NULL),
	m_w_buffer(NULL)
{
	m_w_buffer = ev_new(char, 2048);
	m_file_name = ev_new(char, 256);
}

Ev_Logger_File::~Ev_Logger_File()
{
	if(m_logfile) {
		fclose(m_logfile);
		m_logfile = NULL;
	}

	if(m_w_buffer) {
		ev_free(m_w_buffer);
		m_w_buffer = NULL;
	}

	if(m_file_name) {
		ev_free(m_file_name);
		m_file_name = NULL;
	}
}

ev_error Ev_Logger_File::init(const void *program_name)
{
	ev_error ret;
	uint32 max_index;

	ARGS_NULL_CHECK(m_w_buffer);
	ARGS_NULL_CHECK(m_file_name);

	ret = log_dir_init((const char *)program_name);
	if(ret != EV_SUCCESS)
		return ret;

	if(get_max_index(m_file_name, max_index) != EV_SUCCESS)
		return EV_ARGS_GET_ERR;

	struct tm t;
	Ev_Time::current_time(&t);
	sprintf(&m_file_name[strlen(m_file_name)], "/%u-log-%u%02u%02u_%02u%02u%02u.log", max_index+1, t.tm_year + 1900,
																t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);

	m_logfile = fopen(m_file_name, "a");
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

void Ev_Logger_File::vprint(const char *format, va_list ap)
{
	vsprintf(m_w_buffer, format, ap);
	fprintf(m_logfile, "%s", m_w_buffer);
}

void Ev_Logger_File::print(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	vsprintf(m_w_buffer, format, ap);
	fprintf(m_logfile, "%s", m_w_buffer);
	va_end(ap);
}

ev_error Ev_Logger_File::log_dir_init(const char *program_name)
{
	if(program_name == NULL || program_name[0] == '\0')
		return EV_ARGS_ERR;	

	strcpy(m_file_name, "/var/log/mango/");
	strncat(m_file_name, program_name, 200);

	struct stat dir_st;
	if(lstat(m_file_name, &dir_st) != 0) {
		if(mkdir(m_file_name, 0755) != 0) {
			printf("error[%d]:%s\n", __LINE__, strerror(errno));
			return EV_OBJ_CREATE_ERR;
		}

		if(lstat(m_file_name, &dir_st) != 0) {
			printf("error[%d]:%s\n", __LINE__, strerror(errno));
			return EV_ARGS_GET_ERR;
		}
	}

	if(S_ISLNK(dir_st.st_mode)) {
		// TODO:进一步判断链接是否为目录类型
		printf("warn:logger dir is link\n");
		return EV_STAT_ERR;
	}
	else if(S_ISDIR(dir_st.st_mode)) {
		if(access(m_file_name, W_OK) != 0) {
			return EV_PERMISSION_ERR;
		}
	}
	else {
		return EV_STAT_ERR;
	}

	return EV_SUCCESS;
}


uint32 Ev_Logger_File::get_max_index(const char *dir_path, uint32 &max_index)
{
	DIR *dir;
	struct dirent *ptr;

	if ((dir = opendir(dir_path)) == NULL) {
		printf("Open dir error...\n");
		return EV_DEV_OPEN_ERR;
	}

	uint32 tmp_index;
	max_index = 0;
	while ((ptr = readdir(dir)) != NULL) {
		if((strcmp(ptr->d_name, ".") == 0) || (strcmp(ptr->d_name, "..") == 0))
			continue;
		else if(ptr->d_type == 8) {
			sscanf(ptr->d_name, "%u-", &tmp_index);
			if(tmp_index > max_index)
				max_index = tmp_index;
		}
	}

	return EV_SUCCESS;
}


