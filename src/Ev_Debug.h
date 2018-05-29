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
#include "Mod_Logger.h"

/*----------------------------macro file---------------------------*/
#if (CONFIG_DEBUG & DEBUG_DBG)
#define EV_PRINTF_RAW(format, ...)			Mod_Logger::instance()->printf(format, ##__VA_ARGS__)
#define EV_PRINTF_DBG_NONLF(format, ...)	Mod_Logger::instance()->dbg(__DBG MOD_COLOR_S __MODULE__ MOD_COLOR_E format, ##__VA_ARGS__)
#define EV_PRINTF_DBG_FUNC()				Mod_Logger::instance()->dbg(__DBG MOD_COLOR_S __MODULE__ MOD_COLOR_E "[%d]%s\n", __LINE__, __FUNCTION__)
#define EV_PRINTF_DBG(format, ...)      	Mod_Logger::instance()->dbg(__DBG MOD_COLOR_S __MODULE__ MOD_COLOR_E format "\n", ##__VA_ARGS__)
#define EV_PRINTF_DBG_LINE()     			Mod_Logger::instance()->dbg(__DBG MOD_COLOR_S __MODULE__ MOD_COLOR_E "line:%d\n", __LINE__)
#define EV_PRINTF_DBG_TAB(format, ...)      Mod_Logger::instance()->dbg(__DBG MOD_COLOR_S __MODULE__ MOD_COLOR_E "\t" format "\n", ##__VA_ARGS__)
#define EV_PRINTF_DBG_TAB2(format, ...)     Mod_Logger::instance()->dbg(__DBG MOD_COLOR_S __MODULE__ MOD_COLOR_E "\t" "\t" format "\n", ##__VA_ARGS__)
#else
#define EV_PRINTF_RAW(format, ...)
#define EV_PRINTF_DBG_NONLF(format, ...)
#define EV_PRINTF_DBG_FUNC()
#define EV_PRINTF_DBG(format, ...)
#define EV_PRINTF_DBG_LINE()
#define EV_PRINTF_DBG_TAB(format, ...)
#define EV_PRINTF_DBG_TAB2(format, ...)
#endif

#if (CONFIG_DEBUG & DEBUG_INFO)
#define EV_PRINTF_INFO_INIT_SUCCESS()		Mod_Logger::instance()->info(__INFO MOD_COLOR_S __MODULE__ MOD_COLOR_E " init success.\n")
#define EV_PRINTF_INFO_NONLF(format, ...)	Mod_Logger::instance()->info(__INFO MOD_COLOR_S __MODULE__ MOD_COLOR_E format, ##__VA_ARGS__)
#define EV_PRINTF_INFO(format, ...)			Mod_Logger::instance()->info(__INFO MOD_COLOR_S __MODULE__ MOD_COLOR_E format "\n", ##__VA_ARGS__)
#define EV_PRINTF_INFO_TAB(format, ...)		Mod_Logger::instance()->info(__INFO MOD_COLOR_S __MODULE__ MOD_COLOR_E "\t" format "\n", ##__VA_ARGS__)
#define EV_PRINTF_INFO_TAB2(format, ...)	Mod_Logger::instance()->info(__INFO MOD_COLOR_S __MODULE__ MOD_COLOR_E "\t" "\t" format "\n", ##__VA_ARGS__)
#else
#define EV_PRINTF_INFO_NONLF(format, ...)
#define EV_PRINTF_INFO(format, ...)
#define EV_PRINTF_INFO_TAB(format, ...)
#define EV_PRINTF_INFO_TAB2(format, ...)
#endif

#if (CONFIG_DEBUG & DEBUG_WARN)
#define EV_PRINTF_WARN_NONLF(format, ...)	Mod_Logger::instance()->warning(__WARN MOD_COLOR_S __MODULE__ MOD_COLOR_E CTRL_F_YELLOW format CTRL_CLOSE_ALL, ##__VA_ARGS__)
#define EV_PRINTF_WARN(format, ...)			Mod_Logger::instance()->warning(__WARN MOD_COLOR_S __MODULE__ MOD_COLOR_E CTRL_F_YELLOW format CTRL_CLOSE_ALL "\n", ##__VA_ARGS__)
#else
#define EV_PRINTF_WARN_NONLF(format, ...)
#define EV_PRINTF_WARN(format, ...)
#endif

#if (CONFIG_DEBUG & DEBUG_ERR)
#define EV_PRINTF_ERR_NONLF(format, ...)	Mod_Logger::instance()->error(__ERR  MOD_COLOR_S __MODULE__ MOD_COLOR_E CTRL_F_RED format CTRL_CLOSE_ALL, ##__VA_ARGS__)
#define EV_PRINTF_ERR(format, ...)			Mod_Logger::instance()->error(__ERR  MOD_COLOR_S __MODULE__ MOD_COLOR_E CTRL_F_RED format CTRL_CLOSE_ALL "\n", ##__VA_ARGS__)
#else
#define EV_PRINTF_ERR_NONLF(format, ...)
#define EV_PRINTF_ERR(format, ...)
#endif

#if (CONFIG_DEBUG & DEBUG_HEX)
#define EV_PRINTF_DBG_HEX_NONLF(identify, array, size)	Mod_Logger::instance()->hexdump(MOD_COLOR_S __MODULE__ MOD_COLOR_E identify, array, size, true, false)
#define EV_PRINTF_DBG_HEX(identify, array, size)		Mod_Logger::instance()->hexdump(MOD_COLOR_S __MODULE__ MOD_COLOR_E identify, array, size)
#define EV_PRINTF_RAW_HEX_NONLF(identify, array, size)	Mod_Logger::instance()->hexdump(identify, array, size, false, false)
#define EV_PRINTF_RAW_HEX(identify, array, size)		Mod_Logger::instance()->hexdump(identify, array, size, false)

#define EV_PRINTF_DBG_HEX_REVERSE_NONLF(identify, array, size)	Mod_Logger::instance()->hexdump_reverse(MOD_COLOR_S __MODULE__ MOD_COLOR_E identify, array, size, true, false)
#define EV_PRINTF_DBG_HEX_REVERSE(identify, array, size)		Mod_Logger::instance()->hexdump_reverse(MOD_COLOR_S __MODULE__ MOD_COLOR_E identify, array, size)
#define EV_PRINTF_RAW_HEX_REVERSE_NONLF(identify, array, size)	Mod_Logger::instance()->hexdump_reverse(identify, array, size, false, false)
#define EV_PRINTF_RAW_HEX_REVERSE(identify, array, size)		Mod_Logger::instance()->hexdump_reverse(identify, array, size, false)
#else
#define EV_PRINTF_DBG_HEX_NONLF(identify, array, size)
#define EV_PRINTF_DBG_HEX(identify, array, size)
#define EV_PRINTF_RAW_HEX_NONLF(identify, array, size)
#define EV_PRINTF_RAW_HEX(identify, array, size)

#define EV_PRINTF_DBG_HEX_REVERSE_NONLF(identify, array, size)
#define EV_PRINTF_DBG_HEX_REVERSE(identify, array, size)
#define EV_PRINTF_RAW_HEX_REVERSE_NONLF(identify, array, size)
#define EV_PRINTF_RAW_HEX_REVERSE(identify, array, size)
#endif

/*----------------------------type define--------------------------*/

/*-----------------------------------------------------------------*/

#endif // __EV_DEBUG_H__

