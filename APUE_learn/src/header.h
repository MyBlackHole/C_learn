/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   header 头文件。
 *
 * 主要是定义了一些全局的宏和头文件
 *
 */
#ifndef HEADER
#define HEADER
#include "tools.h"
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef DBG
#define M_TRACE printf
#else
#define M_TRACE (void)
#endif

#endif // HEADER
