/*
 * Copyright (c) 2014  Wu, Xingbo <wuxb45@gmail.com>
 *
 * All rights reserved. No warranty, explicit or implicit, provided.
 */

#define _GNU_SOURCE
#define _LARGEFILE64_SOURCE

#include "coding.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// 对 uint64_t 每8位进行与 0x80 或 0x7f
uint8_t *encode_uint64(uint8_t *const dst, const uint64_t v)
{
	static const uint64_t B = 0x80;
	static const uint64_t M = 0x7f;
	uint8_t *ptr = dst;
	uint64_t t = v;
	while (t >= B) {
		// 赋值单位
		*ptr = (uint8_t)((t & M) | B);
		++ptr;
		// 循环单位
		t >>= 7;
	}
	*ptr = (uint8_t)t;
	++ptr;
	// 返回是 v 的 8 整数倍位后的下一个8位首地址
	return ptr;
}

// encode_uint64 逆过程
const uint8_t *decode_uint64(const uint8_t *const src, uint64_t *const value)
{
	uint64_t result = 0;
	static const uint64_t B = 0x80;
	static const uint64_t M = 0x7f;
	const uint8_t *p = src;

	for (uint32_t shift = 0; shift <= 63; shift += 7) {
		const uint64_t byte = (uint64_t)(*p);
		++p;
		if (byte & B) {
			// More bytes are present
			result |= ((byte & M) << shift);
		} else {
			result |= (byte << shift);
			*value = result;
			return p;
		}
	}
	*value = 0;
	return src;
}

uint8_t *encode_uint16(uint8_t *const dst, const uint16_t v);

uint8_t *encode_uint32(uint8_t *const dst, const uint32_t v);

const uint8_t *decode_uint16(const uint8_t *const src, uint16_t *const value);

const uint8_t *decode_uint32(const uint8_t *const src, uint32_t *const value);
