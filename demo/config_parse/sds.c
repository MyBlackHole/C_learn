/* SDSLib, A C dynamic strings library
 *
 * Copyright (c) 2006-2012, Salvatore Sanfilippo <antirez at gmail dot com>
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

#include "sds.h"
#include "zmalloc.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 根据给定的初始化字符串 init 和字符串长度 initlen
 * 创建一个新的 sds
 *
 * 参数
 *  init ：初始化字符串指针
 *  initlen ：初始化字符串的长度
 *
 * 返回值
 *  sds ：创建成功返回 sdshdr 相对应的 sds
 *        创建失败返回 NULL
 *
 * 复杂度
 *  T = O(N)
 */
/* Create a new sds string with the content specified by the 'init' pointer
 * and 'initlen'.
 * If NULL is used for 'init' the string is initialized with zero bytes.
 *
 * The string is always null-termined (all the sds strings are, always) so
 * even if you create an sds string with:
 *
 * mystring = sdsnewlen("abc",3");
 *
 * You can print the string with printf() as there is an implicit \0 at the
 * end of the string. However the string is binary safe and can contain
 * \0 characters in the middle, as the length is stored in the sds header. */
sds sdsnewlen(const void *init, size_t initlen)
{
	struct sdshdr *sh;

	// 根据是否有初始化内容，选择适当的内存分配方式
	// T = O(N)
	if (init) {
		// zmalloc 不初始化所分配的内存
		sh = zmalloc(sizeof(struct sdshdr) + initlen + 1);
	} else {
		// zcalloc 将分配的内存全部初始化为 0
		sh = zcalloc(sizeof(struct sdshdr) + initlen + 1);
	}

	// 内存分配失败，返回
	if (sh == NULL) {
		return NULL;
	}

	// 设置初始化长度
	sh->len = initlen;
	// 新 sds 不预留任何空间
	sh->free = 0;
	// 如果有指定初始化内容，将它们复制到 sdshdr 的 buf 中
	// T = O(N)
	if (initlen && init) {
		memcpy(sh->buf, init, initlen);
	}
	// 以 \0 结尾
	sh->buf[initlen] = '\0';

	// 返回 buf 部分，而不是整个 sdshdr
	return (char *)sh->buf;
}

/*
 * 创建并返回一个只保存了空字符串 "" 的 sds
 *
 * 返回值
 *  sds ：创建成功返回 sdshdr 相对应的 sds
 *        创建失败返回 NULL
 *
 * 复杂度
 *  T = O(1)
 */
/* Create an empty (zero length) sds string. Even in this case the string
 * always has an implicit null term. */
sds sdsempty(void)
{
	return sdsnewlen("", 0);
}

/*
 * 根据给定字符串 init ，创建一个包含同样字符串的 sds
 *
 * 参数
 *  init ：如果输入为 NULL ，那么创建一个空白 sds
 *         否则，新创建的 sds 中包含和 init 内容相同字符串
 *
 * 返回值
 *  sds ：创建成功返回 sdshdr 相对应的 sds
 *        创建失败返回 NULL
 *
 * 复杂度
 *  T = O(N)
 */
/* Create a new sds string starting from a null termined C string. */
sds sdsnew(const char *init)
{
	size_t initlen = (init == NULL) ? 0 : strlen(init);
	return sdsnewlen(init, initlen);
}

/*
 * 复制给定 sds 的副本
 *
 * 返回值
 *  sds ：创建成功返回输入 sds 的副本
 *        创建失败返回 NULL
 *
 * 复杂度
 *  T = O(N)
 */
/* Duplicate an sds string. */
sds sdsdup(const sds s)
{
	return sdsnewlen(s, sdslen(s));
}

/*
 * 释放给定的 sds
 *
 * 复杂度
 *  T = O(N)
 */
/* Free an sds string. No operation is performed if 's' is NULL. */
void sdsfree(sds s)
{
	if (s == NULL) {
		return;
	}
	zfree(s - sizeof(struct sdshdr));
}

// 未使用函数，可能已废弃
/* Set the sds string length to the length as obtained with strlen(), so
 * considering as content only up to the first null term character.
 *
 * This function is useful when the sds string is hacked manually in some
 * way, like in the following example:
 *
 * s = sdsnew("foobar");
 * s[2] = '\0';
 * sdsupdatelen(s);
 * printf("%d\n", sdslen(s));
 *
 * The output will be "2", but if we comment out the call to sdsupdatelen()
 * the output will be "6" as the string was modified but the logical length
 * remains 6 bytes. */
void sdsupdatelen(sds s)
{
	struct sdshdr *sh = (void *)(s - (sizeof(struct sdshdr)));
	int reallen = strlen(s);
	sh->free += (sh->len - reallen);
	sh->len = reallen;
}

/*
 * 在不释放 SDS 的字符串空间的情况下，
 * 重置 SDS 所保存的字符串为空字符串。
 *
 * 复杂度
 *  T = O(1)
 */
/* Modify an sds string on-place to make it empty (zero length).
 * However all the existing buffer is not discarded but set as free space
 * so that next append operations will not require allocations up to the
 * number of bytes previously available. */
void sdsclear(sds s)
{
	// 取出 sdshdr
	struct sdshdr *sh = (void *)(s - (sizeof(struct sdshdr)));

	// 重新计算属性
	sh->free += sh->len;
	sh->len = 0;

	// 将结束符放到最前面（相当于惰性地删除 buf 中的内容）
	sh->buf[0] = '\0';
}

/* Enlarge the free space at the end of the sds string so that the caller
 * is sure that after calling this function can overwrite up to addlen
 * bytes after the end of the string, plus one more byte for nul term.
 *
 * Note: this does not change the *length* of the sds string as returned
 * by sdslen(), but only the free buffer space we have. */

/*
空间预分配?
空间预分配用于优化 SDS 的字符串增长操作： 当 SDS 的 API 对一个 SDS 进行修改，
并且需要对 SDS 进行空间扩展的时候， 程序不仅会为 SDS 分配修改所必须要的空间，
还会为 SDS 分配额外的未使用空间。

其中， 额外分配的未使用空间数量由以下公式决定：
如果对 SDS 进行修改之后， SDS 的长度（也即是 len 属性的值）将小于 1 MB ，
那么程序分配和 len 属性同样大小的未使用空间， 这时 SDS len 属性的值将和 free
属性 值相同。 举个例 ， 如果进行修改之后， SDS 的 len 将变成 13 字节，
那么程序也会分配 13 字节的 未使用空间， SDS 的 buf 数组的实际长度将变成 13 + 13
+ 1 = 27 字节（额外的一字节用于保存空字符）。

如果对 SDS 进行修改之后， SDS 的长度将大于等于 1 MB ， 那么程序会分配 1 MB
的未使用空间。 举个例子， 如果进行修改之后， SDS 的 len 将变成 30 MB ，
那么程序会 配 1 MB 的未使用空间， SDS 的 buf 数组的实际长度将为 30 MB + 1 MB +
1 byte 。

通过空间预分配策略， Redis 可以减少连续执行字符串增长操作所需的内存重分配次数。
通过这种预分配策略， SDS 将连续增长 N 次字符串所需的内存重分配次数从必定 N
次降低为最多 N 次。 见sdscat
*/

/*
 * 对 sds 中 buf 的长度进行扩展，确保在函数执行之后，
 * buf 至少会有 addlen + 1 长度的空余空间
 * （额外的 1 字节是为 \0 准备的）
 *
 * 返回值
 *  sds ：扩展成功返回扩展后的 sds
 *        扩展失败返回 NULL
 *
 * 复杂度
 *  T = O(N)
 */
sds sdsMakeRoomFor(sds s, size_t addlen)
{
	struct sdshdr *sh, *newsh;

	// 获取 s 目前的空余空间长度
	size_t free = sdsavail(s);

	size_t len, newlen;

	// s 目前的空余空间已经足够，无须再进行扩展，直接返回
	if (free >= addlen) {
		return s;
	}

	// 获取 s 目前已占用空间的长度
	len = sdslen(s);
	sh = (void *)(s - (sizeof(struct sdshdr)));

	// s 最少需要的长度
	newlen = (len + addlen);

	// 根据新长度，为 s 分配新空间所需的大小
	if (newlen < SDS_MAX_PREALLOC) {
		// 如果新长度小于 SDS_MAX_PREALLOC
		// 那么为它分配两倍于所需长度的空间
		newlen *= 2;
	} else {
		// 否则，分配长度为目前长度加上 SDS_MAX_PREALLOC
		newlen += SDS_MAX_PREALLOC;
	}
	// T = O(N)
	newsh = zrealloc(sh, sizeof(struct sdshdr) + newlen + 1);

	// 内存不足，分配失败，返回
	if (newsh == NULL) {
		return NULL;
	}

	// 更新 sds 的空余长度
	newsh->free = newlen - len;

	// 返回 sds
	return newsh->buf;
}

/*
 * 回收 sds 中的空闲空间，
 * 回收不会对 sds 中保存的字符串内容做任何修改。
 *
 * 返回值
 *  sds ：内存调整后的 sds
 *
 * 复杂度
 *  T = O(N)
 */
/* Reallocate the sds string so that it has no free space at the end. The
 * contained string remains not altered, but next concatenation operations
 * will require a reallocation.
 *
 * After the call, the passed sds string is no longer valid and all the
 * references must be substituted with the new pointer returned by the call. */
sds sdsRemoveFreeSpace(sds s)
{
	struct sdshdr *sh;

	sh = (void *)(s - (sizeof(struct sdshdr)));

	// 进行内存重分配，让 buf 的长度仅仅足够保存字符串内容
	// T = O(N) 例如之前的空间是sizeof(struct sdshdr)+sh->len
	// +10000，则现在zreal oc只是分配sizeof(struct
	// sdshdr)+sh->len，则多余的10000字节就被系统 收了
	sh = zrealloc(sh, sizeof(struct sdshdr) + sh->len + 1);

	// 空余空间为 0
	sh->free = 0;

	return sh->buf;
}

/*
 * 返回给定 sds 分配的内存字节数
 *
 * 复杂度
 *  T = O(1)
 */
/* Return the total size of the allocation of the specifed sds string,
 * including:
 * 1) The sds header before the pointer.
 * 2) The string.
 * 3) The free buffer at the end if any.
 * 4) The implicit null term.
 */
size_t sdsAllocSize(sds s)
{
	struct sdshdr *sh = (void *)(s - (sizeof(struct sdshdr)));

	return sizeof(*sh) + sh->len + sh->free + 1;
}

/* Increment the sds length and decrements the left free space at the
 * end of the string according to 'incr'. Also set the null term
 * in the new end of the string.
 *
 * 根据 incr 参数，增加 sds 的长度，缩减空余空间，
 * 并将 \0 放到新字符串的尾端
 *
 * This function is used in order to fix the string length after the
 * user calls sdsMakeRoomFor(), writes something after the end of
 * the current string, and finally needs to set the new length.
 *
 * 这个函数是在调用 sdsMakeRoomFor() 对字符串进行扩展，
 * 然后用户在字符串尾部写入了某些内容之后，
 * 用来正确更新 free 和 len 属性的。
 *
 * Note: it is possible to use a negative increment in order to
 * right-trim the string.
 *
 * 如果 incr 参数为负数，那么对字符串进行右截断操作。
 *
 * Usage example:
 *
 * Using sdsIncrLen() and sdsMakeRoomFor() it is possible to mount the
 * following schema, to cat bytes coming from the kernel to the end of an
 * sds string without copying into an intermediate buffer:
 *
 * 以下是 sdsIncrLen 的用例：
 *
 * oldlen = sdslen(s);
 * s = sdsMakeRoomFor(s, BUFFER_SIZE);
 * nread = read(fd, s+oldlen, BUFFER_SIZE);
 * ... check for nread <= 0 and handle it ...
 * sdsIncrLen(s, nread);
 *
 * 复杂度
 *  T = O(1)
 */
void sdsIncrLen(sds s, int incr)
{
	struct sdshdr *sh = (void *)(s - (sizeof(struct sdshdr)));

	// 确保 sds 空间足够
	assert(sh->free >= incr);

	// 更新属性
	sh->len += incr;
	sh->free -= incr;

	// 这个 assert 其实可以忽略
	// 因为前一个 assert 已经确保 sh->free - incr >= 0 了
	assert(sh->free >= 0);

	// 放置新的结尾符号
	s[sh->len] = '\0';
}

/* Grow the sds to have the specified length. Bytes that were not part of
 * the original length of the sds will be set to zero.
 *
 * if the specified length is smaller than the current length, no operation
 * is performed. */
/*
 * 将 sds 扩充至指定长度，未使用的空间以 0 字节填充。
 *
 * 返回值
 *  sds ：扩充成功返回新 sds ，失败返回 NULL
 *
 * 复杂度：
 *  T = O(N)
 */  // 用空字符将 SDS 扩展至给定长度。   O(N) ， N 为扩展新增的字节数。
sds sdsgrowzero(sds s, size_t len)
{
	struct sdshdr *sh = (void *)(s - (sizeof(struct sdshdr)));
	size_t totlen, curlen = sh->len;

	// 如果 len 比字符串的现有长度小，
	// 那么直接返回，不做动作
	if (len <= curlen) {
		return s;
	}

	// 扩展 sds
	// T = O(N)
	s = sdsMakeRoomFor(s, len - curlen);
	// 如果内存不足，直接返回
	if (s == NULL) {
		return NULL;
	}

	/* Make sure added region doesn't contain garbage */
	// 将新分配的空间用 0 填充，防止出现垃圾内容
	// T = O(N)
	sh = (void *)(s - (sizeof(struct sdshdr)));
	memset(s + curlen, 0,
	       (len - curlen + 1)); /* also set trailing \0 byte */

	// 更新属性
	totlen = sh->len + sh->free;
	sh->len = len;
	sh->free = totlen - sh->len;

	// 返回新的 sds
	return s;
}

/*
 * 将长度为 len 的字符串 t 追加到 sds 的字符串末尾
 *
 * 返回值
 *  sds ：追加成功返回新 sds ，失败返回 NULL
 *
 * 复杂度
 *  T = O(N)
 */
/* Append the specified binary-safe string pointed by 't' of 'len' bytes to the
 * end of the specified sds string 's'.
 *
 * After the call, the passed sds string is no longer valid and all the
 * references must be substituted with the new pointer returned by the call. */
sds sdscatlen(sds s, const void *t, size_t len)
{
	struct sdshdr *sh;

	// 原有字符串长度
	size_t curlen = sdslen(s);

	// 扩展 sds 空间
	// T = O(N)
	s = sdsMakeRoomFor(s, len);

	// 内存不足？直接返回
	if (s == NULL) {
		return NULL;
	}

	// 复制 t 中的内容到字符串后部
	// T = O(N)
	sh = (void *)(s - (sizeof(struct sdshdr)));
	memcpy(s + curlen, t, len);

	// 更新属性
	sh->len = curlen + len;
	sh->free = sh->free - len;

	// 添加新结尾符号
	s[curlen + len] = '\0';

	// 返回新 sds
	return s;
}

/*
 * 将给定字符串 t 追加到 sds 的末尾
 *
 * 返回值
 *  sds ：追加成功返回新 sds ，失败返回 NULL
 *
 * 复杂度
 *  T = O(N)
 */
/* Append the specified null termianted C string to the sds string 's'.
 *
 * After the call, the passed sds string is no longer valid and all the
 * references must be substituted with the new pointer returned by the call. */

/*
空间预分配?
空间预分配用于优化 SDS 的字符串增长操作： 当 SDS 的 API 对一个 SDS 进行修改，
并且需要对 SDS 进行空间扩展的时候， 程序不仅会为 SDS 分配修改所必须要的空间，
还会为 SDS 分配额外的未使用空间。

其中， 额外分配的未使用空间数量由以下公式决定：
如果对 SDS 进行修改之后， SDS 的长度（也即是 len 属性的值）将小于 1 MB ，
那么程序分配和 len 属性同样大小的未使用空间， 这时 SDS len 属性的值将和 free
属性 值相同。 举个例 ， 如果进行修改之后， SDS 的 len 将变成 13 字节，
那么程序也会分配 13 字节的 未使用空间， SDS 的 buf 数组的实际长度将变成 13 + 13
+ 1 = 27 字节（额外的一字节用于保存空字符）。

如果对 SDS 进行修改之后， SDS 的长度将大于等于 1 MB ， 那么程序会分配 1 MB
的未使用空间。 举个例子， 如果进行修改之后， SDS 的 len 将变成 30 MB ，
那么程序会 配 1 MB 的未使用空间， SDS 的 buf 数组的实际长度将为 30 MB + 1 MB +
1 byte 。

通过空间预分配策略， Redis 可以减少连续执行字符串增长操作所需的内存重分配次数。
通过这种预分配策略， SDS 将连续增长 N 次字符串所需的内存重分配次数从必定 N
次降低为最多 N 次。 见sdscat
*/

sds sdscat(sds s, const char *t)
{
	return sdscatlen(s, t, strlen(t));
}

/*
 * 将另一个 sds 追加到一个 sds 的末尾
 *
 * 返回值
 *  sds ：追加成功返回新 sds ，失败返回 NULL
 *
 * 复杂度
 *  T = O(N)
 */
/* Append the specified sds 't' to the existing sds 's'.
 *
 * After the call, the modified sds string is no longer valid and all the
 * references must be substituted with the new pointer returned by the call. */
sds sdscatsds(sds s, const sds t)
{
	return sdscatlen(s, t, sdslen(t));
}

/*
 * 将字符串 t 的前 len 个字符复制到 sds s 当中，
 * 并在字符串的最后添加终结符。
 *
 * 如果 sds 的长度少于 len 个字符，那么扩展 sds
 *
 * 复杂度
 *  T = O(N)
 *
 * 返回值
 *  sds ：复制成功返回新的 sds ，否则返回 NULL
 */
/* Destructively modify the sds string 's' to hold the specified binary
 * safe string pointed by 't' of length 'len' bytes. */
// 将给定的 C 字符串复制到 SDS 里面， 覆盖 SDS 原有的字符串。              O(N)
// ， N 为被复制 C 字符串的长度。
sds sdscpylen(sds s, const char *t, size_t len)
{
	struct sdshdr *sh = (void *)(s - (sizeof(struct sdshdr)));

	// sds 现有 buf 的长度
	size_t totlen = sh->free + sh->len;

	// 如果 s 的 buf 长度不满足 len ，那么扩展它
	if (totlen < len) {
		// T = O(N)
		s = sdsMakeRoomFor(s, len - sh->len);
		if (s == NULL) {
			return NULL;
		}
		sh = (void *)(s - (sizeof(struct sdshdr)));
		totlen = sh->free + sh->len;
	}

	// 复制内容
	// T = O(N)
	memcpy(s, t, len);

	// 添加终结符号
	s[len] = '\0';

	// 更新属性
	sh->len = len;
	sh->free = totlen - len;

	// 返回新的 sds
	return s;
}

/*
 * 将字符串复制到 sds 当中，
 * 覆盖原有的字符。
 *
 * 如果 sds 的长度少于字符串的长度，那么扩展 sds 。
 *
 * 复杂度
 *  T = O(N)
 *
 * 返回值
 *  sds ：复制成功返回新的 sds ，否则返回 NULL
 */
/* Like sdscpylen() but 't' must be a null-termined string so that the length
 * of the string is obtained with strlen(). */
// 将给定的 C 字符串复制到 SDS 里面， 覆盖 SDS 原有的字符串。              O(N)
// ， N 为被复制 C 字符串的长度。
sds sdscpy(sds s, const char *t)
{
	return sdscpylen(s, t, strlen(t));
}

/* Helper for sdscatlonglong() doing the actual number -> string
 * conversion. 's' must point to a string with room for at least
 * SDS_LLSTR_SIZE bytes.
 *
 * The function returns the lenght of the null-terminated string
 * representation stored at 's'. */
#define SDS_LLSTR_SIZE 21
int sdsll2str(char *s, long long value)
{
	char *p, aux;
	unsigned long long v;
	size_t l;

	/* Generate the string representation, this method produces
     * an reversed string. */
	v = (value < 0) ? -value : value;
	p = s;
	do {
		*p++ = '0' + (v % 10);
		v /= 10;
	} while (v);
	if (value < 0) {
		*p++ = '-';
	}

	/* Compute length and add null term. */
	l = p - s;
	*p = '\0';

	/* Reverse the string. */
	p--;
	while (s < p) {
		aux = *s;
		*s = *p;
		*p = aux;
		s++;
		p--;
	}
	return l;
}

/* Identical sdsll2str(), but for unsigned long long type. */
int sdsull2str(char *s, unsigned long long v)
{
	char *p, aux;
	size_t l;

	/* Generate the string representation, this method produces
     * an reversed string. */
	p = s;
	do {
		*p++ = '0' + (v % 10);
		v /= 10;
	} while (v);

	/* Compute length and add null term. */
	l = p - s;
	*p = '\0';

	/* Reverse the string. */
	p--;
	while (s < p) {
		aux = *s;
		*s = *p;
		*p = aux;
		s++;
		p--;
	}
	return l;
}

/* Create an sds string from a long long value. It is much faster than:
 *
 * sdscatprintf(sdsempty(),"%lld\n", value);
 */
// 根据输入的 long long 值 value ，创建一个 SDS
sds sdsfromlonglong(long long value)
{
	char buf[SDS_LLSTR_SIZE];
	int len = sdsll2str(buf, value);

	return sdsnewlen(buf, len);
}

/*
 * 打印函数，被 sdscatprintf 所调用
 *
 * T = O(N^2)
 */
/* Like sdscatpritf() but gets va_list instead of being variadic. */
sds sdscatvprintf(sds s, const char *fmt, va_list ap)
{
	va_list cpy;
	char staticbuf[1024], *buf = staticbuf, *t;
	size_t buflen = strlen(fmt) * 2;

	/* We try to start using a static buffer for speed.
     * If not possible we revert to heap allocation. */
	if (buflen > sizeof(staticbuf)) {
		buf = zmalloc(buflen);
		if (buf == NULL) {
			return NULL;
		}
	} else {
		buflen = sizeof(staticbuf);
	}

	/* Try with buffers two times bigger every time we fail to
     * fit the string in the current buffer size. */
	while (1) {
		buf[buflen - 2] = '\0';
		va_copy(cpy, ap);
		// T = O(N)
		vsnprintf(buf, buflen, fmt, cpy);
		if (buf[buflen - 2] != '\0') {
			if (buf != staticbuf) {
				zfree(buf);
			}
			buflen *= 2;
			buf = zmalloc(buflen);
			if (buf == NULL) {
				return NULL;
			}
			continue;
		}
		break;
	}

	/* Finally concat the obtained string to the SDS string and return it. */
	t = sdscat(s, buf);
	if (buf != staticbuf) {
		zfree(buf);
	}
	return t;
}

/*
 * 打印任意数量个字符串，并将这些字符串追加到给定 sds 的末尾
 *
 * T = O(N^2)
 */
/* Append to the sds string 's' a string obtained using printf-alike format
 * specifier.
 *
 * After the call, the modified sds string is no longer valid and all the
 * references must be substituted with the new pointer returned by the call.
 *
 * Example:
 *
 * s = sdsempty("Sum is: ");
 * s = sdscatprintf(s,"%d+%d = %d",a,b,a+b).
 *
 * Often you need to create a string from scratch with the printf-alike
 * format. When this is the need, just use sdsempty() as the target string:
 *
 * s = sdscatprintf(sdsempty(), "... your format ...", args);
 */
sds sdscatprintf(sds s, const char *fmt, ...)
{
	va_list ap;
	char *t;
	va_start(ap, fmt);
	// T = O(N^2)
	t = sdscatvprintf(s, fmt, ap);
	va_end(ap);
	return t;
}

/* This function is similar to sdscatprintf, but much faster as it does
 * not rely on sprintf() family functions implemented by the libc that
 * are often very slow. Moreover directly handling the sds string as
 * new data is concatenated provides a performance improvement.
 *
 * However this function only handles an incompatible subset of printf-alike
 * format specifiers:
 *
 * %s - C String
 * %S - SDS string
 * %i - signed int
 * %I - 64 bit signed integer (long long, int64_t)
 * %u - unsigned int
 * %U - 64 bit unsigned integer (unsigned long long, uint64_t)
 * %% - Verbatim "%" character.
 */
sds sdscatfmt(sds s, char const *fmt, ...)
{
	struct sdshdr *sh = (void *)(s - (sizeof(struct sdshdr)));
	size_t initlen = sdslen(s);
	const char *f = fmt;
	int i;
	va_list ap;

	va_start(ap, fmt);
	f = fmt; /* Next format specifier byte to process. */
	i = initlen; /* Position of the next byte to write to dest str. */
	while (*f) {
		char next, *str;
		size_t l;
		long long num;
		unsigned long long unum;

		/* Make sure there is always space for at least 1 char. */
		if (sh->free == 0) {
			s = sdsMakeRoomFor(s, 1);
			sh = (void *)(s - (sizeof(struct sdshdr)));
		}

		switch (*f) {
		case '%':
			next = *(f + 1);
			f++;
			switch (next) {
			case 's':
			case 'S':
				str = va_arg(ap, char *);
				l = (next == 's') ? strlen(str) : sdslen(str);
				if (sh->free < l) {
					s = sdsMakeRoomFor(s, l);
					sh = (void *)(s -
						      (sizeof(struct sdshdr)));
				}
				memcpy(s + i, str, l);
				sh->len += l;
				sh->free -= l;
				i += l;
				break;
			case 'i':
			case 'I':
				if (next == 'i') {
					num = va_arg(ap, int);
				} else {
					num = va_arg(ap, long long);
				}
				{
					char buf[SDS_LLSTR_SIZE];
					l = sdsll2str(buf, num);
					if (sh->free < l) {
						s = sdsMakeRoomFor(s, l);
						sh = (void *)(s -
							      (sizeof(struct sdshdr)));
					}
					memcpy(s + i, buf, l);
					sh->len += l;
					sh->free -= l;
					i += l;
				}
				break;
			case 'u':
			case 'U':
				if (next == 'u') {
					unum = va_arg(ap, unsigned int);
				} else {
					unum = va_arg(ap, unsigned long long);
				}
				{
					char buf[SDS_LLSTR_SIZE];
					l = sdsull2str(buf, unum);
					if (sh->free < l) {
						s = sdsMakeRoomFor(s, l);
						sh = (void *)(s -
							      (sizeof(struct sdshdr)));
					}
					memcpy(s + i, buf, l);
					sh->len += l;
					sh->free -= l;
					i += l;
				}
				break;
			default: /* Handle %% and generally %<unknown>. */
				s[i++] = next;
				sh->len += 1;
				sh->free -= 1;
				break;
			}
			break;
		default:
			s[i++] = *f;
			sh->len += 1;
			sh->free -= 1;
			break;
		}
		f++;
	}
	va_end(ap);

	/* Add null-term */
	s[i] = '\0';
	return s;
}

/*
 * 对 sds 左右两端进行修剪，清除其中 cset 指定的所有字符
 *
 * 比如 sdsstrim(xxyyabcyyxy, "xy") 将返回 "abc"
 *
 * 复杂性：
 *  T = O(M*N)，M 为 SDS 长度， N 为 cset 长度。
 */
/* Remove the part of the string from left and from right composed just of
 * contiguous characters found in 'cset', that is a null terminted C string.
 *
 * After the call, the modified sds string is no longer valid and all the
 * references must be substituted with the new pointer returned by the call.
 *
 * Example:
 *
 * s = sdsnew("AA...AA.a.aa.aHelloWorld     :::");
 * s = sdstrim(s,"A. :");
 * printf("%s\n", s);
 *
 * Output will be just "Hello World".
 */

/*
惰性空间释放

惰性空间释放用于优化 SDS 的字符串缩短操作： 当 SDS 的 API 需要缩短 SDS
保存的字符串时， 程序并不立即使用内存重分配来回收缩 短后多出来的字节， 而是使用
free 属性 这些字节的数量记录起来， 并等待将 使用。

举个例子， sdstrim 函数接受一个 SDS 和一个 C 字符串作为参数， 从 SDS
左右两端分别移除所有在 C 字符串中出现过的字符。
*/
// 把释放的字符串字节数添加到free中，凭借free和len就可以有效管理空间

// 接受一个 SDS 和一个 C 字符串作为参数， 从 SDS 左右两端分别移除所有在 C
// 字符串中出现过的字符。

sds sdstrim(sds s, const char *cset)
{
	struct sdshdr *sh = (void *)(s - (sizeof(struct sdshdr)));
	char *start, *end, *sp, *ep;
	size_t len;

	// 设置和记录指针
	sp = start = s;
	ep = end = s + sdslen(s) - 1;

	// 修剪, T = O(N^2)
	while (sp <= end && strchr(cset, *sp)) {
		sp++;
	}
	while (ep > start && strchr(cset, *ep)) {
		ep--;
	}

	// 计算 trim 完毕之后剩余的字符串长度
	len = (sp > ep) ? 0 : ((ep - sp) + 1);

	// 如果有需要，前移字符串内容
	// T = O(N)
	if (sh->buf != sp) {
		memmove(sh->buf, sp, len);
	}

	// 添加终结符
	sh->buf[len] = '\0';

	// 更新属性
	sh->free = sh->free + (sh->len - len);
	sh->len = len;

	// 返回修剪后的 sds
	return s;
}

/*
 * 按索引对截取 sds 字符串的其中一段
 * start 和 end 都是闭区间（包含在内）
 *
 * 索引从 0 开始，最大为 sdslen(s) - 1
 * 索引可以是负数， sdslen(s) - 1 == -1
 *
 * 复杂度
 *  T = O(N)
 */
/* Turn the string into a smaller (or equal) string containing only the
 * substring specified by the 'start' and 'end' indexes.
 *
 * start and end can be negative, where -1 means the last character of the
 * string, -2 the penultimate character, and so forth.
 *
 * The interval is inclusive, so the start and end characters will be part
 * of the resulting string.
 *
 * The string is modified in-place.
 *
 * Example:
 *
 * s = sdsnew("Hello World");
 * sdsrange(s,1,-1); => "ello World"
 */ // 保留 SDS 给定区间内的数据， 不在区间内的数据会被覆盖或清除。            O(N) ， N 为被保留数据的字节数。
void sdsrange(sds s, int start, int end)
{ // 把buf中未解析的数据拷贝到内存头部，等下次继续接收到数据后和新数据一起解析看是否是完整的key或者value字符串
	struct sdshdr *sh = (void *)(s - (sizeof(struct sdshdr)));
	size_t newlen, len = sdslen(s);

	if (len == 0) {
		return;
	}

	if (start < 0) { // 例如如果start=-1，则从end往前start字节开始
		start = len + start;
		if (start < 0) {
			start = 0;
		}
	}

	if (end < 0) { // end=-1表示结尾处为到时第二字节处
		end = len + end;
		if (end < 0) {
			end = 0;
		}
	}
	newlen = (start > end) ? 0 : (end - start) + 1;
	if (newlen != 0) {
		if (start >= (signed)len) {
			newlen = 0;
		} else if (end >=
			   (signed)len) { // 如果end处比len还大，则end只能为len末尾处
			end = len - 1;
			newlen = (start > end) ? 0 : (end - start) + 1;
		}
	} else {
		start = 0;
	}

	// 如果有需要，对字符串进行移动
	// T = O(N)
	if (start && newlen) {
		memmove(sh->buf, sh->buf + start, newlen);
	}

	// 添加终结符
	sh->buf[newlen] = 0;

	// 更新属性
	sh->free = sh->free + (sh->len - newlen);
	sh->len = newlen;
}

/*
 * 将 sds 字符串中的所有字符转换为小写
 *
 * T = O(N)
 */
/* Apply tolower() to every character of the sds string 's'. */
void sdstolower(sds s)
{
	int len = sdslen(s), j;

	for (j = 0; j < len; j++) {
		s[j] = tolower(s[j]);
	}
}

/*
 * 将 sds 字符串中的所有字符转换为大写
 *
 * T = O(N)
 */
/* Apply toupper() to every character of the sds string 's'. */
void sdstoupper(sds s)
{
	int len = sdslen(s), j;

	for (j = 0; j < len; j++) {
		s[j] = toupper(s[j]);
	}
}

/*
 * 对比两个 sds ， strcmp 的 sds 版本
 *
 * 返回值
 *  int ：相等返回 0 ，s1 较大返回正数， s2 较大返回负数
 *
 * T = O(N)
 */
/* Compare two sds strings s1 and s2 with memcmp().
 *
 * Return value:
 *
 *     1 if s1 > s2.
 *    -1 if s1 < s2.
 *     0 if s1 and s2 are exactly the same binary string.
 *
 * If two strings share exactly the same prefix, but one of the two has
 * additional characters, the longer string is considered to be greater than
 * the smaller one. */  //对比两个 SDS 字符串是否相同。
int sdscmp(const sds s1, const sds s2)
{
	size_t l1, l2, minlen;
	int cmp;

	l1 = sdslen(s1);
	l2 = sdslen(s2);
	minlen = (l1 < l2) ? l1 : l2;
	cmp = memcmp(s1, s2, minlen);

	if (cmp == 0) {
		return l1 - l2;
	}

	return cmp;
}

/* Split 's' with separator in 'sep'. An array
 * of sds strings is returned. *count will be set
 * by reference to the number of tokens returned.
 *
 * 使用分隔符 sep 对 s 进行分割，返回一个 sds 字符串的数组。
 * *count 会被设置为返回数组元素的数量。
 *
 * On out of memory, zero length string, zero length
 * separator, NULL is returned.
 *
 * 如果出现内存不足、字符串长度为 0 或分隔符长度为 0
 * 的情况，返回 NULL
 *
 * Note that 'sep' is able to split a string using
 * a multi-character separator. For example
 * sdssplit("foo_-_bar","_-_"); will return two
 * elements "foo" and "bar".
 *
 * 注意分隔符可以的是包含多个字符的字符串
 *
 * This version of the function is binary-safe but
 * requires length arguments. sdssplit() is just the
 * same function but for zero-terminated strings.
 *
 * 这个函数接受 len 参数，因此它是二进制安全的。
 * （文档中提到的 sdssplit() 已废弃）
 *
 * T = O(N^2)
 */
sds *sdssplitlen(const char *s, int len, const char *sep, int seplen,
		 int *count)
{
	int elements = 0, slots = 5, start = 0, j;
	sds *tokens;

	if (seplen < 1 || len < 0) {
		return NULL;
	}

	tokens = zmalloc(sizeof(sds) * slots);
	if (tokens == NULL) {
		return NULL;
	}

	if (len == 0) {
		*count = 0;
		return tokens;
	}

	// T = O(N^2)
	for (j = 0; j < (len - (seplen - 1)); j++) {
		/* make sure there is room for the next element and the final one */
		if (slots < elements + 2) {
			sds *newtokens;

			slots *= 2;
			newtokens = zrealloc(tokens, sizeof(sds) * slots);
			if (newtokens == NULL) {
				goto cleanup;
			}
			tokens = newtokens;
		}
		/* search the separator */
		// T = O(N)
		if ((seplen == 1 && *(s + j) == sep[0]) ||
		    (memcmp(s + j, sep, seplen) == 0)) {
			tokens[elements] = sdsnewlen(s + start, j - start);
			if (tokens[elements] == NULL) {
				goto cleanup;
			}
			elements++;
			start = j + seplen;
			j = j + seplen - 1; /* skip the separator */
		}
	}
	/* Add the final element. We are sure there is room in the tokens array. */
	tokens[elements] = sdsnewlen(s + start, len - start);
	if (tokens[elements] == NULL) {
		goto cleanup;
	}
	elements++;
	*count = elements;
	return tokens;

cleanup: {
	int i;
	for (i = 0; i < elements; i++) {
		sdsfree(tokens[i]);
	}
	zfree(tokens);
	*count = 0;
	return NULL;
}
}

/*
 * 释放 tokens 数组中 count 个 sds
 *
 * T = O(N^2)
 */
/* Free the result returned by sdssplitlen(), or do nothing if 'tokens' is NULL.
 */
void sdsfreesplitres(sds *tokens, int count)
{
	if (!tokens) {
		return;
	}
	while (count--) {
		sdsfree(tokens[count]);
	}
	zfree(tokens);
}

/*
 * 将长度为 len 的字符串 p 以带引号（quoted）的格式
 * 追加到给定 sds 的末尾
 *
 * T = O(N)
 */
/* Append to the sds string "s" an escaped string representation where
 * all the non-printable characters (tested with isprint()) are turned into
 * escapes in the form "\n\r\a...." or "\x<hex-number>".
 *
 * After the call, the modified sds string is no longer valid and all the
 * references must be substituted with the new pointer returned by the call. */
sds sdscatrepr(sds s, const char *p, size_t len)
{
	s = sdscatlen(s, "\"", 1);

	while (len--) {
		switch (*p) {
		case '\\':
		case '"':
			s = sdscatprintf(s, "\\%c", *p);
			break;
		case '\n':
			s = sdscatlen(s, "\\n", 2);
			break;
		case '\r':
			s = sdscatlen(s, "\\r", 2);
			break;
		case '\t':
			s = sdscatlen(s, "\\t", 2);
			break;
		case '\a':
			s = sdscatlen(s, "\\a", 2);
			break;
		case '\b':
			s = sdscatlen(s, "\\b", 2);
			break;
		default:
			if (isprint(*p)) {
				s = sdscatprintf(s, "%c", *p);
			} else {
				s = sdscatprintf(s, "\\x%02x",
						 (unsigned char)*p);
			}
			break;
		}
		p++;
	}

	return sdscatlen(s, "\"", 1);
}

/* Helper function for sdssplitargs() that returns non zero if 'c'
 * is a valid hex digit. */
/*
 * 如果 c 为十六进制符号的其中一个，返回正数
 *
 * T = O(1)
 */
int is_hex_digit(char c)
{
	return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') ||
	       (c >= 'A' && c <= 'F');
}

/* Helper function for sdssplitargs() that converts a hex digit into an
 * integer from 0 to 15 */
/*
 * 将十六进制符号转换为 10 进制
 *
 * T = O(1)
 */
int hex_digit_to_int(char c)
{
	switch (c) {
	case '0':
		return 0;
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	case 'a':
	case 'A':
		return 10;
	case 'b':
	case 'B':
		return 11;
	case 'c':
	case 'C':
		return 12;
	case 'd':
	case 'D':
		return 13;
	case 'e':
	case 'E':
		return 14;
	case 'f':
	case 'F':
		return 15;
	default:
		return 0;
	}
}

/* Split a line into arguments, where every argument can be in the
 * following programming-language REPL-alike form:
 *
 * 将一行文本分割成多个参数，每个参数可以有以下的类编程语言 REPL 格式：
 *
 * foo bar "newline are supported\n" and "\xff\x00otherstuff"
 *
 * The number of arguments is stored into *argc, and an array
 * of sds is returned.
 *
 * 参数的个数会保存在 *argc 中，函数返回一个 sds 数组。
 *
 * The caller should free the resulting array of sds strings with
 * sdsfreesplitres().
 *
 * 调用者应该使用 sdsfreesplitres() 来释放函数返回的 sds 数组。
 *
 * Note that sdscatrepr() is able to convert back a string into
 * a quoted string in the same format sdssplitargs() is able to parse.
 *
 * sdscatrepr() 可以将一个字符串转换为一个带引号（quoted）的字符串，
 * 这个带引号的字符串可以被 sdssplitargs() 分析。
 *
 * The function returns the allocated tokens on success, even when the
 * input string is empty, or NULL if the input contains unbalanced
 * quotes or closed quotes followed by non space characters
 * as in: "foo"bar or "foo'
 *
 * 即使输入出现空字符串， NULL ，或者输入带有未对应的括号，
 * 函数都会将已成功处理的字符串先返回。
 *
 * 这个函数主要用于 config.c 中对配置文件进行分析。
 * 例子：
 *  sds *arr = sdssplitargs("timeout 10086\r\nport 123321\r\n");
 * 会得出
 *  arr[0] = "timeout"
 *  arr[1] = "10086"
 *  arr[2] = "port"
 *  arr[3] = "123321"
 *
 * T = O(N^2)
 */
sds *sdssplitargs(const char *line, int *argc)
{
	const char *p = line;
	char *current = NULL;
	char **vector = NULL;

	*argc = 0;
	while (1) {
		/* skip blanks */
		// 跳过空白
		// T = O(N)
		while (*p && isspace(*p)) {
			p++;
		}

		if (*p) {
			/* get a token */
			int inq = 0; /* set to 1 if we are in "quotes" */
			int insq =
				0; /* set to 1 if we are in 'single quotes' */
			int done = 0;

			if (current == NULL) {
				current = sdsempty();
			}

			// T = O(N)
			while (!done) {
				if (inq) {
					if (*p == '\\' && *(p + 1) == 'x' &&
					    is_hex_digit(*(p + 2)) &&
					    is_hex_digit(*(p + 3))) {
						unsigned char byte;

						byte = (hex_digit_to_int(
								*(p + 2)) *
							16) +
						       hex_digit_to_int(
							       *(p + 3));
						current = sdscatlen(
							current, (char *)&byte,
							1);
						p += 3;
					} else if (*p == '\\' && *(p + 1)) {
						char c;

						p++;
						switch (*p) {
						case 'n':
							c = '\n';
							break;
						case 'r':
							c = '\r';
							break;
						case 't':
							c = '\t';
							break;
						case 'b':
							c = '\b';
							break;
						case 'a':
							c = '\a';
							break;
						default:
							c = *p;
							break;
						}
						current = sdscatlen(current, &c,
								    1);
					} else if (*p == '"') {
						/* closing quote must be followed by a space or
                         * nothing at all. */
						if (*(p + 1) &&
						    !isspace(*(p + 1))) {
							goto err;
						}
						done = 1;
					} else if (!*p) {
						/* unterminated quotes */
						goto err;
					} else {
						current = sdscatlen(current, p,
								    1);
					}
				} else if (insq) {
					if (*p == '\\' && *(p + 1) == '\'') {
						p++;
						current = sdscatlen(current,
								    "'", 1);
					} else if (*p == '\'') {
						/* closing quote must be followed by a space or
                         * nothing at all. */
						if (*(p + 1) &&
						    !isspace(*(p + 1))) {
							goto err;
						}
						done = 1;
					} else if (!*p) {
						/* unterminated quotes */
						goto err;
					} else {
						current = sdscatlen(current, p,
								    1);
					}
				} else {
					switch (*p) {
					case ' ':
					case '\n':
					case '\r':
					case '\t':
					case '\0':
						done = 1;
						break;
					case '"':
						inq = 1;
						break;
					case '\'':
						insq = 1;
						break;
					default:
						current = sdscatlen(current, p,
								    1);
						break;
					}
				}
				if (*p) {
					p++;
				}
			}
			/* add the token to the vector */
			// T = O(N)
			vector = zrealloc(vector,
					  ((*argc) + 1) * sizeof(char *));
			vector[*argc] = current;
			(*argc)++;
			current = NULL;
		} else {
			/* Even on empty input string return something not NULL. */
			if (vector == NULL) {
				vector = zmalloc(sizeof(void *));
			}
			return vector;
		}
	}

err:
	while ((*argc)--) {
		sdsfree(vector[*argc]);
	}
	zfree(vector);
	if (current) {
		sdsfree(current);
	}
	*argc = 0;
	return NULL;
}

/* Modify the string substituting all the occurrences of the set of
 * characters specified in the 'from' string to the corresponding character
 * in the 'to' array.
 *
 * 将字符串 s 中，
 * 所有在 from 中出现的字符，替换成 to 中的字符
 *
 * For instance: sdsmapchars(mystring, "ho", "01", 2)
 * will have the effect of turning the string "hello" into "0ell1".
 *
 * 比如调用 sdsmapchars(mystring, "ho", "01", 2)
 * 就会将 "hello" 转换为 "0ell1"
 *
 * The function returns the sds string pointer, that is always the same
 * as the input pointer since no resize is needed.
 * 因为无须对 sds 进行大小调整，
 * 所以返回的 sds 输入的 sds 一样
 *
 * T = O(N^2)
 */
sds sdsmapchars(sds s, const char *from, const char *to, size_t setlen)
{
	size_t j, i, l = sdslen(s);

	// 遍历输入字符串
	for (j = 0; j < l; j++) {
		// 遍历映射
		for (i = 0; i < setlen; i++) {
			// 替换字符串
			if (s[j] == from[i]) {
				s[j] = to[i];
				break;
			}
		}
	}
	return s;
}

/* Join an array of C strings using the specified separator (also a C string).
 * Returns the result as an sds string. */
sds sdsjoin(char **argv, int argc, char *sep)
{
	sds join = sdsempty();
	int j;

	for (j = 0; j < argc; j++) {
		join = sdscat(join, argv[j]);
		if (j != argc - 1) {
			join = sdscat(join, sep);
		}
	}
	return join;
}
