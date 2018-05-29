/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-6-5
 * Version     : v0.1
 * Description : Ev_Uart header file
 *******************************************************************/
#ifndef __EV_UART_H__
#define __EV_UART_H__

/*----------------------------Head file----------------------------*/
#include "Ev_Handle.h"

/*----------------------------macro file---------------------------*/

/*----------------------------type define--------------------------*/
typedef enum {
	BR9600,
	BR19200,
	BR38400,
	BR115200,
	BR1000000,
	BR_MAX		// INVALID
} uart_br_t;

typedef enum {
	DATABIT7,
	DATABIT8
} uart_db_t;

typedef enum {
	STOPBIT1,
	STOPBIT2
} uart_sb_t;

typedef enum {
	PARITY_NONE,
	PARITY_ODD,
	PARITY_EVEN
} uart_parity_t;

typedef enum {
	FCNONE,
	FCSOFT,
	FCHARD
} uart_fc_t;

/*-----------------------------------------------------------------*/
class Ev_Uart : public Ev_Handle
{
public: // api
	explicit Ev_Uart(const char *name);
	virtual ~Ev_Uart();

	virtual ev_error config(uart_br_t baud_rate, uart_db_t databits, uart_sb_t stopbits,
														uart_parity_t parity, uart_fc_t flow_ctrl);
public: // var

protected: // api
	virtual ev_error set_baud_rate(uart_br_t baud_rate);
	virtual ev_error set_uart_attr(uart_db_t databits, uart_sb_t stopbits, uart_parity_t parity, uart_fc_t flow_ctrl);
	virtual ev_error set_uart_vtime_vmin(uint8 time_100ms, uint8 min_char);

protected: // var

private: // api

private: // var
	char m_name[64];
};


#endif // __EV_UART_H__

