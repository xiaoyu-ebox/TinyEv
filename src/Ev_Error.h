/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-3-11
 * Version     : v0.1
 * Description : Ev_Error header file
 *******************************************************************/
#ifndef __EV_ERROR_H__
#define __EV_ERROR_H__

/*----------------------------Head file----------------------------*/
#include "Ev_BaseType.h"

/*----------------------------macro file---------------------------*/
#define ARGS_NULL_CHECK(var)			if(var == NULL) \
											return EV_ARGS_ERR
#define ARGS_NULL_CHECK_RN(var)			if(var == NULL) \
											return NULL
#define ARGS_NULL_CHECK_RV(var)			if(var == NULL) \
											return

#define CONDITION_CHECK(condition)		if(condition) \
											return EV_ARGS_ERR
#define CONDITION_CHECK_RN(condition)	if(condition) \
											return NULL
#define CONDITION_CHECK_RV(condition)	if(condition) \
											return


// 类型分段
#define ERROR_BASE					0
#define ERROR_DEV					50
#define ERROR_EV					100

/*----------------------------type define--------------------------*/
typedef uint32				ev_error;

enum {
	EV_SUCCESS = ERROR_BASE,			// 成功
	EV_UNKNOW_ERR,						// 未知错误
	EV_CONTINUE,						// 继续
	EV_UNHANDLE,						// 未处理事件
	EV_ARGS_ERR,						// 参数错误
	EV_ARGS_GET_ERR,					// 参数获取错误
	EV_ARGS_SET_ERR,             		// 参数设置错误
	EV_MEM_NO_ENOUGH,					// 内存不足
	EV_STAT_ERR,						// 状态错误
	EV_OBJ_CREATE_ERR,					// 对象创建错误
	EV_DATA_PARSE_ERR,					// 数据解析错误
	EV_CONTAINER_EMPTY,					// 容器已空
	EV_CONTAINER_FULL,					// 容器已满
	EV_REGISTER_ERR,					// 注册失败
	EV_CTRL_ERR,						// 控制错误
	EV_INIT_ERR,						// 初始化错误
	EV_NOT_INIT,						// 未初始化
	EV_ALREADY_INIT,					// 已经初始化了
	EV_NOT_FOUND,						// 没有找到
	EV_RW_ERR,							// 读写错误
	EV_RW_TIMEOUT,						// 读写超时
	EV_WATCH_EVENT_ERR,					// 监听事件错误
	EV_REMOVE_EVENT,					// 移除event监听(如定时器、可读事件)
	EV_REMOVE_HANDLE					// 移除handle(移除event监听并销毁handle(自身))
};

enum {
	EV_DEV_OPEN_ERR = ERROR_DEV,		// 设备打开错误
	EV_DEV_BUSY,						// 设备忙
	EV_DEV_CONNECTING,					// 连接进行中
	EV_DEV_CONNECT_ERR,					// 连接错误
	EV_DEV_BIND_ERR,					// 绑定错误
	EV_DEV_LISTEN_ERR,					// listen错误
	EV_DEV_ACCEPT_ERR,					// accpet错误
	EV_DEV_TYPE_UNSUPPORT,				// 设备类型不支持
};

/*-----------------------------------------------------------------*/

#endif // __EV_ERROR_H__

