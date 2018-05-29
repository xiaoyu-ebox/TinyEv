/*******************************************************************
 *
 * Copyright (C), 20xx-2017, www.xxxxxx.com, All rights reserved.
 *
 * Author      : xiaoyu | xiaoyu_ebox@163.com
 * Create Time : 2017-12-15
 * Version     : v0.1
 * Description : Console_Ctrl header file
 *******************************************************************/
#ifndef __CONSOLE_CTRL_H__
#define __CONSOLE_CTRL_H__

/*----------------------------Head file----------------------------*/

/*----------------------------macro file---------------------------*/
#define CTRL_PREFIX							"\033["
#define CTRL_SUFFIX							"m"

#define F_BLACK								"30"
#define F_RED								"31"
#define F_GREEN								"32"
#define F_YELLOW							"33"
#define F_BLUE								"34"
#define F_PURPLE							"35"
#define F_DARK_GREEN						"36"
#define F_WHILE								"37"

#define B_BLACK								"40"
#define B_RED								"41"
#define B_GREEN								"42"
#define B_YELLOW							"43"
#define B_BLUE								"44"
#define B_PURPLE							"45"
#define B_DARK_GREEN						"46"
#define B_WHILE								"47"


#define CTRL_CLOSE_ALL						CTRL_PREFIX "0" CTRL_SUFFIX
#define CTRL_HIGH_WORD						CTRL_PREFIX "1" CTRL_SUFFIX
#define CTRL_UNDERLINE						CTRL_PREFIX "4" CTRL_SUFFIX
#define CTRL_BLINK							CTRL_PREFIX "5" CTRL_SUFFIX
#define CTRL_INVERT							CTRL_PREFIX "7" CTRL_SUFFIX
#define CTRL_HIDE							CTRL_PREFIX "8" CTRL_SUFFIX

// F&B   // "\033[40;31m.....\033[0m"
#define CTRL_B_F(b_color, f_color)			CTRL_PREFIX b_color ";" f_color CTRL_SUFFIX

#define CTRL_F_BLACK						CTRL_PREFIX F_BLACK CTRL_SUFFIX
#define CTRL_F_RED							CTRL_PREFIX F_RED CTRL_SUFFIX
#define CTRL_F_GREEN						CTRL_PREFIX F_GREEN CTRL_SUFFIX
#define CTRL_F_YELLOW						CTRL_PREFIX F_YELLOW CTRL_SUFFIX
#define CTRL_F_BLUE							CTRL_PREFIX F_BLUE CTRL_SUFFIX
#define CTRL_F_PURPLE						CTRL_PREFIX F_PURPLE CTRL_SUFFIX
#define CTRL_F_DARK_GREEN					CTRL_PREFIX F_DARK_GREEN CTRL_SUFFIX
#define CTRL_F_WHILE						CTRL_PREFIX F_WHILE CTRL_SUFFIX

#define CTRL_B_BLACK						CTRL_PREFIX B_BLACK CTRL_SUFFIX
#define CTRL_B_RED							CTRL_PREFIX B_RED CTRL_SUFFIX
#define CTRL_B_GREEN						CTRL_PREFIX B_GREEN CTRL_SUFFIX
#define CTRL_B_YELLOW						CTRL_PREFIX B_YELLOW CTRL_SUFFIX
#define CTRL_B_BLUE							CTRL_PREFIX B_BLUE CTRL_SUFFIX
#define CTRL_B_PURPLE						CTRL_PREFIX B_PURPLE CTRL_SUFFIX
#define CTRL_B_DARK_GREEN					CTRL_PREFIX B_DARK_GREEN CTRL_SUFFIX
#define CTRL_B_WHILE						CTRL_PREFIX B_WHILE CTRL_SUFFIX

/*----------------------------type define--------------------------*/

/*-----------------------------------------------------------------*/



#endif // __CONSOLE_CTRL_H__

