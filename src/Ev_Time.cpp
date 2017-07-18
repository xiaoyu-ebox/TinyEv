/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-2-17
 * Version     : v0.1
 * Description : 
 *******************************************************************/
/*----------------------------Head file----------------------------*/
#include "Ev_Time.h"

/*----------------------------macro file---------------------------*/
#define __MODULE__						"[Time]"

/*----------------------------type define--------------------------*/

/*----------------------------var define---------------------------*/

/*-----------------------------------------------------------------*/
Ev_Time::Ev_Time()
{

}

Ev_Time::~Ev_Time()
{

}

// precise:s
time_t Ev_Time::current_time()
{
	return time(NULL);
}


// precise:10ms
struct tm *Ev_Time::current_time(struct tm *t)
{
	time_t now;

	time(&now);
	localtime_r(&now, t);

	return t;
}

// precise:us
struct timeval *Ev_Time::current_time(struct timeval *t)
{
	gettimeofday(t, NULL);

	return t;
}

// precise:ns
struct timespec *Ev_Time::current_time(struct timespec *t)
{
	clock_gettime(CLOCK_REALTIME, t);

	return t;
}

struct timespec *Ev_Time::get_time(struct timespec *ts, struct timespec *add_ts)
{
	current_time(ts);

	if(add_ts) {
		ts->tv_sec  += add_ts->tv_sec;
		ts->tv_nsec += add_ts->tv_nsec;
		if(ts->tv_nsec >= NSEC_TO_SEC) {
			ts->tv_nsec %= NSEC_TO_SEC;
			++ts->tv_sec;
		}
	}

	return ts;
}

// 获取当天到现在经过的秒数
uint32 Ev_Time::get_sec_of_day(const tm *t)
{
	return t->tm_hour * 3600 + t->tm_min * 60 + t->tm_sec;
}

// 获取本月剩余的秒数
uint32 Ev_Time::get_surplus_sec_of_mon(const tm *t)
{
	uint32 surplus_sec_of_mon;
	uint8 surplus_day_of_mon;

	uint8 days_of_mon[] = {
		31, 28, 31, 30, 31, 30,
		31, 31, 30, 31, 30, 31
	};

	// 当天剩余的sec
	surplus_sec_of_mon = DAY_TO_SEC - get_sec_of_day(t);

	if(t->tm_mon == 1) {
		uint32 year = t->tm_year + 1900;
		surplus_day_of_mon = 28;

		// 判断闰年
		if((year%4==0 && year%100!=0) || (year%400==0))
			surplus_day_of_mon += 1;
		surplus_day_of_mon -= t->tm_mday;
	}
	else {
		// 剩余天数
		surplus_day_of_mon = days_of_mon[t->tm_mon]-t->tm_mday;
	}

	// 剩余天剩余的sec
	surplus_sec_of_mon += (surplus_day_of_mon * DAY_TO_SEC);

	return surplus_sec_of_mon;
}


void Ev_Time::printf_time()
{
	tm t;
	current_time(&t);

	EV_PRINTF_DBG("%u-%02u-%02u [%u] %02u:%02u:%02u", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_wday,
											t.tm_hour, t.tm_min, t.tm_sec);
}

void Ev_Time::printf_time(uint32 sec)
{
	uint8 day = 0, hour = 0, min = 0;

	if(sec >= DAY_TO_SEC) {
		day = sec / DAY_TO_SEC;
		sec %= DAY_TO_SEC;
	}

	if(sec >= HOUR_TO_SEC) {
		hour = sec / HOUR_TO_SEC;
		sec %= HOUR_TO_SEC;
	}

	if(sec >= MIN_TO_SEC) {
		min = sec / MIN_TO_SEC;
		sec %= MIN_TO_SEC;
	}

	EV_PRINTF_DBG("[%u] %02u:%02u:%02u", day, hour, min, sec);
}

void Ev_Time::printf_precise_time()
{
	struct timespec t;

	current_time(&t);

	EV_PRINTF_DBG("%lu.%09lu", t.tv_sec, t.tv_nsec);
}

