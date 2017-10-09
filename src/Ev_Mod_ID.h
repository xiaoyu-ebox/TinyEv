/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-3-19
 * Version     : v0.1
 * Description : Ev_Mod_ID header file
 *******************************************************************/
#ifndef __EV_MOD_ID_H__
#define __EV_MOD_ID_H__

/*----------------------------Head file----------------------------*/
#include "Ev_Base_Include.h"

/*----------------------------macro file---------------------------*/
// mod id分类
#define MOD_ID_SYSTEM_BASE			0x0001		// 输入事件
#define MOD_ID_CUSTOMER_BASE 		0x0100


// system
#define SYSTEM_EVENT_REBOOT			(MOD_ID_SYSTEM_BASE)		// 系统重启
#define SYSTEM_EVENT_POWEROFF		(MOD_ID_SYSTEM_BASE+1)		// 系统关机
#define SYSTEM_EVENT_SUSPEND		(MOD_ID_SYSTEM_BASE+2)		// 系统挂起
#define SYSTEM_EVENT_RESUME			(MOD_ID_SYSTEM_BASE+3)		// 系统唤醒
#define SYSTEM_EVENT_INPUT			(MOD_ID_SYSTEM_BASE+4)		// 系统按键

/*----------------------------type define--------------------------*/
typedef uint16 event_id_t;

/*-----------------------------------------------------------------*/


/*----------------------宏定义----------------------*/



#endif // __EV_MOD_ID_H__

