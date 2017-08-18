/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-3-11
 * Version     : v0.1
 * Description : Ev_Debug header file
 *******************************************************************/
#ifndef __EV_DEBUG_H__
#define __EV_DEBUG_H__

/*----------------------------Head file----------------------------*/
#include "Ev_Config.h"

/*----------------------------macro file---------------------------*/
#define __DBG								""
#define __INFO								""
#define __WARN								"W"
#define __ERR								"E"

#if (CONFIG_DEBUG & DEBUG_DBG)
#define EV_PRINTF_DBG_FUNC()				Mod_Logger::instance()->dbg(__DBG __MODULE__ "%s\n", __FUNCTION__)
#define EV_PRINTF_DBG(format, ...)      	Mod_Logger::instance()->dbg(__DBG __MODULE__ format "\n", ##__VA_ARGS__)
#define EV_PRINTF_DBG_LINE()     			Mod_Logger::instance()->dbg(__DBG __MODULE__ "line:%d\n", __LINE__)
#define EV_PRINTF_DBG_TAB(format, ...)      Mod_Logger::instance()->dbg(__DBG __MODULE__ "\t" format "\n", ##__VA_ARGS__)
#define EV_PRINTF_DBG_TAB2(format, ...)     Mod_Logger::instance()->dbg(__DBG __MODULE__ "\t" "\t" format "\n", ##__VA_ARGS__)
#else
#define EV_PRINTF_DBG(format, ...)
#endif

#if (CONFIG_DEBUG & DEBUG_INFO)
#define EV_PRINTF_INFO(format, ...)     	Mod_Logger::instance()->info(__INFO __MODULE__ format "\n", ##__VA_ARGS__)
#define EV_PRINTF_INFO_TAB(format, ...)     Mod_Logger::instance()->info(__INFO __MODULE__ "\t" format "\n", ##__VA_ARGS__)
#define EV_PRINTF_INFO_TAB2(format, ...)    Mod_Logger::instance()->info(__INFO __MODULE__ "\t" "\t" format "\n", ##__VA_ARGS__)
#else
#define EV_PRINTF_INFO(format, ...)
#endif

#if (CONFIG_DEBUG & DEBUG_WARN)
#define EV_PRINTF_WARN(format, ...)			Mod_Logger::instance()->warning("\033[47;33m" __WARN __MODULE__ format "\033[0m\n", ##__VA_ARGS__)
#else
#define EV_PRINTF_WARN(format, ...)
#endif

#if (CONFIG_DEBUG & DEBUG_ERR)
#define EV_PRINTF_ERR(format, ...)			Mod_Logger::instance()->error("\033[47;31m" __ERR __MODULE__ format "\033[0m\n", ##__VA_ARGS__)
#else
#define EV_PRINTF_ERR(format, ...)
#endif

#if (CONFIG_DEBUG & DEBUG_HEX)
#define EV_PRINTF_DBG_HEX(identify, array, size)		Mod_Logger::instance()->hexdump(__MODULE__ identify, array, size)
#else
#define EV_PRINTF_DBG_HEX(identify, array, size)
#endif

/*----------------------------type define--------------------------*/

/*-----------------------------------------------------------------*/

#endif // __EV_DEBUG_H__

