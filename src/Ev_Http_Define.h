/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-4-17
 * Version     : v0.1
 * Description : Ev_Http_Define header file
 *******************************************************************/
#ifndef __EV_HTTP_DEFINE_H__
#define __EV_HTTP_DEFINE_H__

/*----------------------------Head file----------------------------*/

/*----------------------------macro file---------------------------*/
// http请求参数:
#define HTTP_GET_FLAG                   "GET "
#define HTTP_POST_FLAG                  "POST "
#define HTTP_POST_LEN_OCCUPANCY         "   "
#define STRING_OCCUPANCY				"%s"

#define HTTP_LINE_FEED                  "\r\n\r\n"
#define HTTP_GET_BODY                   " HTTP/1.1\r\nConnection: Keep-alive\r\nHost: 60.205.232.214\r\n\r\n"
#define HTTP_POST_BODY                  " HTTP/1.1\r\nConnection: Keep-alive\r\nHost: 60.205.232.214\r\nContent-Length: "
#define HTTP_POST_BODY_TAIL             HTTP_POST_LEN_OCCUPANCY HTTP_LINE_FEED

#define HTTP_LEN_OCCUPANCY_SIZE			(sizeof(HTTP_POST_LEN_OCCUPANCY) + sizeof(HTTP_LINE_FEED) - 2)
#define HTTP_LF_SIZE					(sizeof(HTTP_LINE_FEED)-1)

/*----------------------------type define--------------------------*/

/*-----------------------------------------------------------------*/


#endif // __EV_HTTP_DEFINE_H__

