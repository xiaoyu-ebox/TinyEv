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
#include <stdio.h>

/*----------------------------macro file---------------------------*/
#define __DBG								""
#define __INFO								""
#define __WARN								"W"
#define __ERR								"E"

#if (CONFIG_DEBUG & DEBUG_DBG)
#define EV_PRINTF_DBG_FUNC()				printf(__DBG __MODULE__ "%s\n", __FUNCTION__)
#define EV_PRINTF_DBG(format, ...)      	printf(__DBG __MODULE__ format "\n", ##__VA_ARGS__)
#define EV_PRINTF_DBG_LINE()     			printf(__DBG __MODULE__ "line:%d\n", __LINE__)
#define EV_PRINTF_DBG_TAB(format, ...)      printf(__DBG __MODULE__ "\t" format "\n", ##__VA_ARGS__)
#define EV_PRINTF_DBG_TAB2(format, ...)     printf(__DBG __MODULE__ "\t" "\t" format "\n", ##__VA_ARGS__)
#else
#define EV_PRINTF_DBG(format, ...)
#endif

#if (CONFIG_DEBUG & DEBUG_INFO)
#define EV_PRINTF_INFO(format, ...)     	printf(__INFO __MODULE__ format "\n", ##__VA_ARGS__)
#define EV_PRINTF_INFO_TAB(format, ...)     printf(__INFO __MODULE__ "\t" format "\n", ##__VA_ARGS__)
#define EV_PRINTF_INFO_TAB2(format, ...)    printf(__INFO __MODULE__ "\t" "\t" format "\n", ##__VA_ARGS__)
#else
#define EV_PRINTF_INFO(format, ...)
#endif

#if (CONFIG_DEBUG & DEBUG_WARN)
#define EV_PRINTF_WARN(format, ...)			printf("\033[47;33m" __WARN __MODULE__ format "\033[0m\n", ##__VA_ARGS__)
#else
#define EV_PRINTF_WARN(format, ...)
#endif

#if (CONFIG_DEBUG & DEBUG_ERR)
#define EV_PRINTF_ERR(format, ...)			printf("\033[47;31m" __ERR __MODULE__ format "\033[0m\n", ##__VA_ARGS__)
#else
#define EV_PRINTF_ERR(format, ...)
#endif

#if (CONFIG_DEBUG & DEBUG_HEX)
#define EV_PRINTF_DBG_HEX(array, size)		do { \
												const uint8 *p = (const uint8 *)(array); \
												uint16 len = (size); \
												printf(__MODULE__); \
												while(len--) \
													printf("%02x ", *p++); \
												printf("\n"); \
											} while(0)
#else
#define EV_PRINTF_DBG_HEX(array, size)
#endif

/*----------------------------type define--------------------------*/

/*-----------------------------------------------------------------*/

#endif // __EV_DEBUG_H__

