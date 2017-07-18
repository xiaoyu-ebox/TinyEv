/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-4-17
 * Version     : v0.1
 * Description : Ev_Http header file
 *******************************************************************/
#ifndef __EV_HTTP_H__
#define __EV_HTTP_H__

/*----------------------------Head file----------------------------*/
#include "Ev_Http_Define.h"
#include "Ev_SocketCli.h"

/*----------------------------macro file---------------------------*/
#define HTTP_HOST_MAX_SIZE		52

/*----------------------------type define--------------------------*/

/*-----------------------------------------------------------------*/
class Ev_Http : public Ev_SocketCli
{
public: // api
	Ev_Http();
	~Ev_Http();

	ev_error request_http(const char *url, const char *post_args);

	static ev_error parse_http_url(const char *url, char *host, uint16 *port, const char **req_path);
	static ev_error send_http_data(Ev_SocketCli *socket, char *send_buffer, const char *req_path, const char *post_args);
	static uint32 packing_http_data(char *buffer, const char *req_path, const char *post_args);
	static ev_error unpacking_http_data(char *http_data, char **context);
public: // var

protected: // api

protected: // var
	void on_ev_connect(ev_error ret);
	ev_error on_ev_stream_read(uint32 size);
	ev_error on_ev_error() {return EV_REMOVE_EVENT;}
	ev_error on_ev_write() {return EV_SUCCESS;}

private: // api

private: // var

};


#endif // __EV_HTTP_H__

