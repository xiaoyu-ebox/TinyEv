/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-2-18
 * Version     : v0.1
 * Description : 
 *******************************************************************/
/*----------------------------Head file----------------------------*/
#include "Ev_Timer.h"
#include "Ev_Vector.h"

/*----------------------------macro file---------------------------*/
#define __MODULE__						"[Timer]"

/*----------------------------type define--------------------------*/

/*----------------------------var define---------------------------*/

/*-----------------------------------------------------------------*/
Ev_Timer::~Ev_Timer()
{

}

Obj_Timer *Ev_Timer::register_timer_event(Obj_Timer *timer, double start, double repeat)
{
	return Ev_Vector::instance()->register_timer_event(this, timer, start, repeat);
}

void Ev_Timer::start_timer_event(Obj_Timer *timer)
{
	Ev_Vector::instance()->start_timer_event(timer);
}

void Ev_Timer::stop_timer_event(Obj_Timer *timer)
{
	Ev_Vector::instance()->stop_timer_event(timer);
}

void Ev_Timer::deregister_timer_event(Obj_Timer *timer)
{
	Ev_Vector::instance()->deregister_timer_event(timer);
}


