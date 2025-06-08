#include <stdbool.h>
#include <stdio.h>

#include "curl/curl.h"

FILE *fp;

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
	int written = fwrite(ptr, size, nmemb, fp);
	return written;
}

bool get(char *URL, char *FileName)
{
	CURL *curl;

	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();

	curl_easy_setopt(curl, CURLOPT_URL, URL);
	curl_easy_setopt(curl, CURLOPT_VERBOSE,
			 1L); // 在屏幕打印请求连接过程和返回http数据
	curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 1); // 查找次数,防止查找太深
	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3); // 连接超时
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3); // 接收数据时超时设置

	if ((fp = fopen(FileName, "w")) == NULL) {
		curl_easy_cleanup(curl);
		return false;
	}
	// CURLOPT_WRITEFUNCTION 将后继的动作交给write_data函数处理
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);

	curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	return true;
}

int demo_get_main(int argc, char *argv[])
{
	get("https://www.baidu.com", "c://baidu.html");

	return 0;
}
