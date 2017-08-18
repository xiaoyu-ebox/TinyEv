/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-3-11
 * Version     : v0.1
 * Description : Ev_Config header file
 *******************************************************************/
#ifndef __EV_CONFIG_H__
#define __EV_CONFIG_H__

/*----------------------------Head file----------------------------*/
#include "Ev_Config_Option.h"

/*----------------------------macro file---------------------------*/
// debug选项,关闭：DEBUG_NONE
#define CONFIG_DEBUG					(DEBUG_ERR | DEBUG_WARN | DEBUG_HEX | DEBUG_INFO | DEBUG_DBG)	// DEBUG_DBG

#define ENABLE_ASSEST_CHECK				CONFIG_ENABLE

#define MAX_EV_MSG_FIFO_SIZE			128

// IPC通讯消息最大size
#define IPC_BODY_DEF_SIZE				(4096)
#define IPC_BUFFER_DEF_SIZE				(sizeof(ipc_msg_info_t)+IPC_BODY_DEF_SIZE)

// stream buffer min size >= (IPC_BUFFER_DEF_SIZE*2)
#define STREAM_BUFFER_DEF_SIZE			(IPC_BODY_DEF_SIZE<<1)

/*----------------------------type define--------------------------*/

/*-----------------------------------------------------------------*/

#endif // __EV_CONFIG_H__

