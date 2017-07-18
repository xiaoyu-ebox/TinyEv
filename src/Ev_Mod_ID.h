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
// 内部事件flag
#define INTERNAL_EVENT				0x8000		// event_id_t为16位整形


// mod id分类
#define MOD_ID_SYSTEM_BASE			0x0001		// 输入事件
#define MOD_ID_CUSTOMER_BASE 		0x0100


// system
#define SYSTEM_EVENT_REBOOT			(MOD_ID_SYSTEM_BASE)		// 系统重启
#define SYSTEM_EVENT_POWEROFF		(MOD_ID_SYSTEM_BASE+1)		// 系统关机
#define SYSTEM_EVENT_SUSPEND		(MOD_ID_SYSTEM_BASE+2)		// 系统挂起
#define SYSTEM_EVENT_RESUME			(MOD_ID_SYSTEM_BASE+3)		// 系统唤醒
#define SYSTEM_EVENT_INPUT			(MOD_ID_SYSTEM_BASE+4)		// 系统按键



// CUSTOMER（放到其它文件）
#define WIFI_BASE					(MOD_ID_CUSTOMER_BASE+0x20)
#define SCALE_BASE					(MOD_ID_CUSTOMER_BASE+0x30)
#define RFID_BASE					(MOD_ID_CUSTOMER_BASE+0x40)
#define ALARM_BASE					(MOD_ID_CUSTOMER_BASE+0x50)


// wifi
#define WIFI_UPDATE_STATE			(WIFI_BASE)
#define WIFI_CONNECT_TO				(WIFI_BASE+1)
#define WIFI_DISCONNECT				(WIFI_BASE+2)

// scale
#define SCALE_POWER_CTL				(SCALE_BASE)

// rfid
#define RFID_POWER_CTL				(RFID_BASE)
#define RFID_SWIPE_CARD				(RFID_BASE+1)


// alarm
#define ALARM_MORNING				(ALARM_BASE)
#define ALARM_NOON					(ALARM_BASE+1)
#define ALARM_OTHER					(ALARM_BASE+2)

/*----------------------------type define--------------------------*/
typedef uint16 event_id_t;

/*-----------------------------------------------------------------*/


/*----------------------宏定义----------------------*/



#endif // __EV_MOD_ID_H__

