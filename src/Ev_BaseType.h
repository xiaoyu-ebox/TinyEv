/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-3-11
 * Version     : v0.1
 * Description : Ev_BaseType header file
 *******************************************************************/
#ifndef __EV_BASETYPE_H__
#define __EV_BASETYPE_H__

/*----------------------------Head file----------------------------*/

/*----------------------------macro file---------------------------*/
#define ARRAY_SIZE(array)	(sizeof(array)/sizeof(array[0]))

#define MAC_SIZE			6

/*----------------------------type define--------------------------*/
// linux gcc(bit): char->8; short->16; int->32; long long->64; long(long int)->32||64
typedef signed char         sint8;
typedef signed short        sint16;
typedef signed int          sint32;
typedef signed long long    sint64;

typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned int        uint32;
typedef unsigned long long  uint64;



// 布尔类型
#ifndef __cplusplus
typedef enum {
	false,
	true
} bool;
#endif

// 数组类型
typedef struct {
	uint32 size;
	uint8 *data;	
} ev_array;

/*-----------------------------------------------------------------*/

#endif // __EV_BASETYPE_H__

