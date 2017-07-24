/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-3-12
 * Version     : v0.1
 * Description : Ev_Malloc header file
 *******************************************************************/
#ifndef __EV_MALLOC_H__
#define __EV_MALLOC_H__

/*----------------------------Head file----------------------------*/

/*----------------------------macro file---------------------------*/
#define ev_new(_type_, _count_)	(_type_ *)calloc(sizeof(_type_), (_count_))
#define ev_free(_variable_)		free(_variable_)

/*----------------------------type define--------------------------*/

/*-----------------------------------------------------------------*/

#endif // __EV_MALLOC_H__

