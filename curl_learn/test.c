#define CURL_STATICLIB
#include <stdio.h>
#include <stdlib.h>

#include "curl/curl.h"

// #pragma comment(lib, "libcurl.lib")

int demo_test_main(void)
{
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "http://www.baidu.com");
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}

	printf("\n\n%p \n", curl);

	return 0;
}
