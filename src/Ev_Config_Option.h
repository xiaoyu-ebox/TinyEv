/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-3-11
 * Version     : v0.1
 * Description : Ev_Config_Option header file
 *******************************************************************/
#ifndef __EV_CONFIG_OPTION_H__
#define __EV_CONFIG_OPTION_H__

/*----------------------------Head file----------------------------*/

/*----------------------------macro file---------------------------*/
// 打印控制选项
#define DEBUG_NONE					(0)
#define DEBUG_DBG					(1 << 1)
#define DEBUG_INFO					(1 << 2)
#define DEBUG_WARN					(1 << 3)
#define DEBUG_ERR					(1 << 4)
#define DEBUG_HEX					(1 << 5)

// 开启/关闭选项
#define CONFIG_DISABLE				(0)
#define CONFIG_ENABLE				(1)

/*----------------------------type define--------------------------*/

/*-----------------------------------------------------------------*/

#endif // __EV_CONFIG_OPTION_H__

