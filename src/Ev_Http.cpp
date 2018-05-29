/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-4-17
 * Version     : v0.1
 * Description : 
 *******************************************************************/
/*----------------------------Head file----------------------------*/
#include "Ev_Http.h"

/*----------------------------macro file---------------------------*/
#define __MODULE__				"[Http]"


#define HTTP_URL_HEAD				"http://"
#define HTTP_1_1_HEAD				"HTTP/1.1 "
/*----------------------------type define--------------------------*/

/*----------------------------var define---------------------------*/

/*-----------------------------------------------------------------*/
Ev_Http::Ev_Http() :
	Ev_SocketCli(SOCKET_TCP_CLIENT, 4096, GENERAL_FIFO)
{

}

Ev_Http::~Ev_Http()
{

}

ev_error Ev_Http::request_http(const char *url, const char *post_args)
{
	ev_error ret;
	uint16 port;
	char host[HTTP_HOST_MAX_SIZE], buffer[1024];
	const char *req_path;
	
	if((ret = parse_http_url(url, host, &port, &req_path)) != EV_SUCCESS)
		return ret;

	EV_PRINTF_DBG("host:%s, port:%u, path:[%s]", host, port, req_path);

	// 60.205.232.214			http://openapi.tuling123.com/openapi/api/v2
	ret = connect_to_host(host, port);
	EV_PRINTF_DBG("connect %s.", ret ? "failed" : "success");
	if(ret != EV_SUCCESS)
		return ret;

	uint32 size = packing_http_data(buffer, req_path, post_args);
	EV_PRINTF_DBG("packing:%d.", size);

	EV_PRINTF_DBG("send:[%s]", buffer);
	ret = write_data((uint8 *)buffer, size);
	EV_PRINTF_DBG("write %s.", ret ? "failed" : "success");

	return EV_SUCCESS;
}

void Ev_Http::on_ev_connect(ev_error ret)
{
	// TODO:异步连接后处理
	EV_PRINTF_INFO("Connect %s", ret ? "error" : "ok");

	if(ret) {
		deregister_handle_event();
	}
}

ev_error Ev_Http::parse_http_url(const char *url, char *host, uint16 *port, const char **req_path)
{
	uint8 i, host_len;
	const char *p, *p_path;
	char *p_port;
	// http://www.baidu.com/
	// http://192.168.12.23/
	// http://192.168.12.23:80/
	EV_PRINTF_DBG("parse:[%s]", url);
	
	p = HTTP_URL_HEAD;
	for(i = 0; i < sizeof(HTTP_URL_HEAD)-1; ++i) {
		if(url[i] != p[i]) {
			EV_PRINTF_DBG_LINE();
			return EV_ARGS_ERR;
		}
	}

	url += (sizeof(HTTP_URL_HEAD)-1);
	if((p_path = strchr(url, '/')) == NULL) {
		EV_PRINTF_DBG_LINE();
		return EV_ARGS_ERR;
	}

	// host
	host_len = p_path - url;
	memcpy(host, url, host_len);
	host[host_len] = '\0';

	// port
	EV_PRINTF_DBG("host:[%s]", host);
	if((p_port = strchr(host, ':')) != NULL) {
		*p_port++ = '\0';

		EV_PRINTF_DBG_LINE();

		if(host_len > (p_port - host))
			*port = atoi((char *)p_port);
		else
			*port = 80;
	}
	else {
		*port = 80;
		EV_PRINTF_DBG_LINE();
	}

	// req_path
	*req_path = p_path;

	return EV_SUCCESS;
}


ev_error Ev_Http::on_ev_stream_read(uint32 size)
{
	char *context;
	
	EV_PRINTF_DBG_FUNC();

	//EV_PRINTF_DBG("[%s]", stream_try_read(NULL, size));
	//EV_PRINTF_DBG_HEX(stream_try_read(NULL, size), size);

	if(unpacking_http_data((char *)stream_try_read(NULL, size), &context) == EV_SUCCESS) {
		EV_PRINTF_DBG("context:[%s]", context);
	}
	else {
		EV_PRINTF_ERR("parse err.");
	}

	return size; 
}

ev_error Ev_Http::send_http_data(Ev_SocketCli *socket, char *send_buffer, const char *req_path, const char *post_args)
{
	ev_error ret;

	uint32 size = packing_http_data(send_buffer, req_path, post_args);
	ret = socket->write_data((uint8 *)send_buffer, size);
	if(ret)
		EV_PRINTF_DBG("write failed:%d", ret);

	return ret;
}

/*****************************************************************************
 * 函数功能  : 
 * 输入参数  : const uint8_t *req_path   请求的路径
               const uint8_t *post_args  post的参数
 * 输出参数  : uint8_t *dest_buf         存放的缓冲区
 * 返 回 值  : uint32_t					   组包数据的有效长度
*****************************************************************************/
uint32 Ev_Http::packing_http_data(char *buffer, const char *req_path, const char *post_args)
{
	uint32 len, total_len = 0;
	
	if(post_args) {
		// post头报文
		memcpy(buffer, HTTP_POST_FLAG, sizeof(HTTP_POST_FLAG));
		total_len = sizeof(HTTP_POST_FLAG)-1;
	}
	else {
		// get 头报文
		memcpy(buffer, HTTP_GET_FLAG, sizeof(HTTP_GET_FLAG));
		total_len = sizeof(HTTP_GET_FLAG)-1;
	}

	// url路径
	len = strlen(req_path);
	memcpy(&buffer[total_len], req_path, len);
	total_len += len;

	if(post_args == NULL) {
		// GET方式
		memcpy(&buffer[total_len], HTTP_GET_BODY, sizeof(HTTP_GET_BODY));
		total_len += sizeof(HTTP_GET_BODY);
	}
	else {
		// 长度占的字节数
		uint8 len_size = 0;
		char len_buf[15] = {0};

		// http
		memcpy(&buffer[total_len], HTTP_POST_BODY, sizeof(HTTP_POST_BODY));
		total_len += (sizeof(HTTP_POST_BODY)-1);

		// 长度
		len = strlen(post_args);
		sprintf(len_buf, "%u\r\n\r\n", len);
		len_size = ((len > 9999) ? 5 : (len > 999) ? 4 : (len > 99) ? 3 : (len > 9) ? 2 : 1) + (sizeof("\r\n\r\n")-1);
		memcpy(&buffer[total_len], len_buf, len_size);
		total_len += len_size;

		// post参数
		memcpy(&buffer[total_len], post_args, len);
		total_len += len;

		buffer[total_len] = '\n';
		total_len += 1;

		buffer[total_len] = '\0';
	}

	return total_len;
}


ev_error Ev_Http::unpacking_http_data(char *http_data, char **context)
{
	uint16 i, body_len;
	uint32 http_code;
	const char *p;
	char *pc;

	ARGS_NULL_CHECK(http_data);

	p = HTTP_1_1_HEAD;
	for(i = 0; i < sizeof(HTTP_1_1_HEAD)-1; ++i) {
		if(http_data[i] != p[i]) {
			EV_PRINTF_DBG_LINE();
			return EV_ARGS_ERR;
		}
	}

	http_data += sizeof(HTTP_1_1_HEAD)-1;
	http_code = atoi(http_data);
	if(http_code != 200)
		return EV_ARGS_GET_ERR;

	pc = http_data;
	while((pc = strchr(pc, '\n')) != NULL) {
		if(pc[1] == '\n') {
			pc += 2;
			break;
		}
		else if(pc[2] == '\n') {
			pc += 3;
			break;
		}

		++pc;
	}

	// len
	body_len = strtol(pc, NULL, 16);
	if(body_len == 0 || (pc = strchr(pc, '\n')) == NULL) {
		*context = NULL;
		return EV_SUCCESS;
	}

	// body
	*context = ++pc;
	if((pc = strchr(pc, '\n')) == NULL)
		return EV_ARGS_GET_ERR;

	if(*(pc-1) == '\r')
		--pc;
	if(pc - *context < body_len)
		return EV_ARGS_GET_ERR;
	*pc = '\0';

	return EV_SUCCESS;
}

