/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-2-17
 * Version     : v0.1
 * Description : Ev_Time header file
 *******************************************************************/
#ifndef __EV_TIME_H__
#define __EV_TIME_H__

/*----------------------------Head file----------------------------*/
#include "Ev_Base_Include.h"

#include <time.h>

/*----------------------------macro file---------------------------*/
#define SEC_TO_MS(s)					(s * 1000)
#define MIN_TO_MS(m)					(SEC_TO_MS(m * 60))
#define HOUR_TO_MS(h)					(MIN_TO_MS(h * 60))
#define DAY_TO_MS(d)					(HOUR_TO_MS(d * 24))

#define SEC_TO_US(s)					(SEC_TO_MS(s) * 1000)
#define NSEC_TO_SEC						(1000000000)

#define MIN_TO_SEC						(60)
#define HOUR_TO_SEC						(60 * MIN_TO_SEC)
#define DAY_TO_SEC						(24 * HOUR_TO_SEC)
#define WEEK_TO_SEC						(7 * DAY_TO_SEC)
#define DAYS_TO_SEC(day)				((day) * DAY_TO_SEC)
#define TIME_TO_SEC(hour, min, sec)		((hour) * 3600 + (min) * 60 + (sec))

#define WEEK_TO_DAY						(7)


/*----------------------------type define--------------------------*/

/*-----------------------------------------------------------------*/
class Ev_Time
{
public: // api
	Ev_Time();
	~Ev_Time();


	// 精度:s
	static time_t current_time();
	// 精度:10ms
	static struct tm *current_time(struct tm *t);
	// 精度:us
	static struct timeval *current_time(struct timeval *t);
	// 精度:ns
	static struct timespec *current_time(struct timespec *t);

	static struct timespec *get_time(struct timespec *ts, struct timespec *add_ts);

	static uint32 get_sec_of_day(const tm *t);

	static uint32 get_surplus_sec_of_mon(const tm *t);

	// 打印当前时间
	static void printf_time();
	static void printf_time(uint32 sec);

	// 打印当前高精度时间
	static void printf_precise_time();
public: // var

protected: // api

protected: // var

private: // api

private: // var

};


#endif // __EV_TIME_H__

