/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-6-5
 * Version     : v0.1
 * Description : 
 *******************************************************************/
/*----------------------------Head file----------------------------*/
#include "Ev_Uart.h"
#include <termios.h>

/*----------------------------macro file---------------------------*/

/*----------------------------type define--------------------------*/

/*----------------------------var define---------------------------*/
static const int br_list[] = {B9600, B19200, B38400, B115200, B1000000};

/*-----------------------------------------------------------------*/
Ev_Uart::Ev_Uart(const char *name)
{
	strncpy(m_name, name, sizeof(m_name));
	m_name[sizeof(m_name)-1] = '\0';
}

Ev_Uart::~Ev_Uart()
{

}

ev_error Ev_Uart::config(uart_br_t baud_rate, uart_db_t databits, uart_sb_t stopbits,
											uart_parity_t parity, uart_fc_t flow_ctrl)
{
	ev_error ret;
	
	// open uart
	m_handle = ::open(m_name, O_RDWR);
    if(m_handle < 0)
		return EV_DEV_OPEN_ERR;

	if((ret = set_baud_rate(baud_rate)) != EV_SUCCESS)
		return ret;

	if((ret = set_uart_attr(databits, stopbits, parity, flow_ctrl)) != EV_SUCCESS)
		return ret;

	if((ret = set_uart_vtime_vmin(15, 1)) != EV_SUCCESS)
		return ret;

	return EV_SUCCESS;
}

ev_error Ev_Uart::set_baud_rate(uart_br_t baud_rate)
{
	struct termios options;

	if(baud_rate > BR_MAX)
		return EV_ARGS_ERR;

	if(tcgetattr(m_handle, &options) != 0)
		return EV_ARGS_GET_ERR;

	cfsetispeed(&options, br_list[baud_rate]);
	cfsetospeed(&options, br_list[baud_rate]);

	if(tcsetattr(m_handle, TCSANOW, &options) != 0)
		return EV_ARGS_SET_ERR;

	return EV_SUCCESS;
}

ev_error Ev_Uart::set_uart_attr(uart_db_t databits, uart_sb_t stopbits, uart_parity_t parity, uart_fc_t flow_ctrl)
{
	struct termios options;

	if(tcgetattr(m_handle, &options) != 0)
		return EV_ARGS_GET_ERR;

	options.c_cflag &= ~CSIZE;
	switch(databits) {
		case DATABIT7:
			options.c_cflag |= CS7;
			break;
		case DATABIT8:
			options.c_cflag |= CS8;
			break;
		default:
			return EV_ARGS_ERR;
	}

	switch(stopbits) {
		case STOPBIT1:
			options.c_cflag &= ~CSTOPB;
			break;
		case STOPBIT2:
			options.c_cflag |= CSTOPB;
			break;
		default:
			return EV_ARGS_ERR;
	}

	switch(parity) {
		case PARITY_NONE:
			options.c_cflag &= ~PARENB;
			options.c_iflag &= ~INPCK;
			break;
		case PARITY_ODD:
			options.c_cflag |= (PARODD | PARENB);
			options.c_iflag |= INPCK;
			break;
		case PARITY_EVEN:
			options.c_cflag |= PARENB;
			options.c_cflag &= ~PARODD;
			options.c_iflag |= INPCK;
			break;
		default:
			return EV_ARGS_ERR;
	}

	switch(flow_ctrl) {
		case FCNONE:
			options.c_cflag &= ~CRTSCTS;
			break;
		case FCSOFT:
			options.c_cflag |= CRTSCTS;
			break;
		case FCHARD:
			options.c_cflag |= IXON | IXOFF | IXANY;
			break;
		default:
			return EV_ARGS_ERR;
	}

	if (parity != PARITY_NONE)
		options.c_iflag |= INPCK;

	options.c_cflag |= CLOCAL | CREAD;
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	options.c_oflag &= ~OPOST;
	options.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);

	if (tcsetattr(m_handle, TCSANOW, &options) != 0)
		return EV_ARGS_SET_ERR;

	tcflush(m_handle, TCIOFLUSH);

	return EV_SUCCESS;
}

// 阻塞读的情况下才会有效
ev_error Ev_Uart::set_uart_vtime_vmin(uint8 time_100ms, uint8 min_char)
{
	struct termios options;

	if(tcgetattr(m_handle, &options) != 0)
		return EV_ARGS_GET_ERR;

	options.c_cc[VTIME] = time_100ms;	
	options.c_cc[VMIN] = min_char;

	if (tcsetattr(m_handle, TCSANOW, &options) != 0)
		return EV_ARGS_SET_ERR;

	return EV_SUCCESS;
}


