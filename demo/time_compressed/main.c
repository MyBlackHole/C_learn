#include <stdio.h>
#include <time.h>

// 将时间压缩为16位十六进制值
unsigned short compress_time(struct tm *timeinfo)
{
	// 月份占4位 (1-12 → 0-11)
	unsigned int month = timeinfo->tm_mon; // 0-11

	// 日期占5位 (1-31 → 0-30)
	unsigned int day = timeinfo->tm_mday - 1; // 0-30

	// 小时占5位 (0-23)
	unsigned int hour = timeinfo->tm_hour;

	// 组合为14位值 (4+5+5=14)
	return (month << 10) | (day << 5) | hour;
}

// 从压缩值解析时间
void decompress_time(unsigned short compressed, struct tm *timeinfo)
{
	// 提取小时 (低5位)
	timeinfo->tm_hour = compressed & 0x1F;

	// 提取日期 (中间5位)
	timeinfo->tm_mday = ((compressed >> 5) & 0x1F) + 1;

	// 提取月份 (高4位)
	timeinfo->tm_mon = (compressed >> 10) & 0x0F;
}

int main()
{
	time_t rawtime;
	struct tm *timeinfo;

	// 获取当前时间
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	printf("当前时间: %04d-%02d-%02d %02d:%02d:%02d\n",
	       timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,
	       timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min,
	       timeinfo->tm_sec);

	// 压缩时间（去除年份，最小单位小时）
	unsigned short compressed = compress_time(timeinfo);
	printf("压缩值 (十六进制): 0x%04X\n", compressed);
	printf("压缩值 (十进制): %d\n", compressed);

	// 解析压缩时间
	struct tm decompressed = { 0 };
	decompress_time(compressed, &decompressed);

	printf("解析时间: %02d月%02d日 %02d时\n", decompressed.tm_mon + 1,
	       decompressed.tm_mday, decompressed.tm_hour);

	// 验证压缩/解压过程
	if (timeinfo->tm_mon == decompressed.tm_mon &&
	    timeinfo->tm_mday == decompressed.tm_mday &&
	    timeinfo->tm_hour == decompressed.tm_hour) {
		printf("✓ 压缩/解压验证成功\n");
	} else {
		printf("✗ 压缩/解压验证失败\n");
	}

	return 0;
}

// 输出示例：
// ❯ xmake run demo_time_compressed
// 当前时间: 2025-06-23 11:07:39
// 压缩值 (十六进制): 0x16CB
// 压缩值 (十进制): 5835
// 解析时间: 06月23日 11时
// ✓ 压缩/解压验证成功
