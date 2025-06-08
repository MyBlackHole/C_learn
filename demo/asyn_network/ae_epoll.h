/* Linux epoll(2) based ae.c module
 *
 * Copyright (c) 2009-2012, Salvatore Sanfilippo <antirez at gmail dot com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Redis nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/epoll.h>
#include <unistd.h>

#include "ae.h"
#include "zmalloc.h"

/*
 * 事件状态
 */
typedef struct aeApiState {
	// epoll_event 实例描述符
	int epfd;

	// 事件槽
	struct epoll_event *events;

} aeApiState;

/*
 * 创建一个新的 epoll 实例，并将它赋值给 eventLoop
 */
int aeApiCreate(aeEventLoop *eventLoop);

/*
 * 调整事件槽大小
 */
int aeApiResize(aeEventLoop *eventLoop, int setsize);

/*
 * 释放 epoll 实例和事件槽
 */
void aeApiFree(aeEventLoop *eventLoop);

/*
 * 关联给定事件到 fd
 */
int aeApiAddEvent(aeEventLoop *eventLoop, int fd, int mask);

/*
 * 从 fd 中删除给定事件
 */
void aeApiDelEvent(aeEventLoop *eventLoop, int fd, int delmask);

/*
 * 获取可执行事件
 */ 
// 文件事件 aeCreateFileEvent 时间事件 aeCreateTimeEvent aeProcessEvents 中执行文件和时间事件
int aeApiPoll(aeEventLoop *eventLoop, struct timeval *tvp);

/*
 * 返回当前正在使用的 poll 库的名字
 */
char *aeApiName(void);
