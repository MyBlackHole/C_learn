#include <stdbool.h>

#include "curl/curl.h"

bool Post(char *Url, char *Cookie, char *PostVal)
{
	CURL *curl;
	CURLcode res = { 0 };

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, Url); // 指定url
		curl_easy_setopt(curl, CURLOPT_COOKIEFILE,
				 Cookie); // 指定cookie文件
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS,
				 PostVal); // 指定post内容
		// curl_easy_setopt(curl, CURLOPT_PROXY, "10.99.60.201:8080");  //
		// 是否代理
		res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));
			return false;
		}
		curl_easy_cleanup(curl);
	}
	return true;
}

int demo_post_main(int argc, char *argv[])
{
	Post("https://www.baidu.com/post.php", "exfffffx",
	     "&logintype=uid&u=xieyan&psw=xxx86");
	return 0;
}
