/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2018-5-9
 * Version     : v0.1
 * Description : 
 *******************************************************************/
/*----------------------------Head file----------------------------*/
#include "Ev_Tools.h"

/*----------------------------macro file---------------------------*/

/*----------------------------type define--------------------------*/

/*----------------------------var define---------------------------*/

/*-----------------------------------------------------------------*/
Ev_Tools::Ev_Tools()
{

}

Ev_Tools::~Ev_Tools()
{

}

const char *Ev_Tools::program_name(const char *program_path)
{
	const char *p_flag = NULL, *p_last = program_path;

	if(program_path == NULL)
		return "";

	while((p_flag = strchr(p_last, '/')) != NULL) {
		p_last = p_flag+1;
	}

	return p_last;
}

