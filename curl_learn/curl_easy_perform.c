#include <unistd.h>
#define CURL_STATICLIB
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "curl/curl.h"

int demo_curl_easy_performc_main(void)
{
	CURL *curl = curl_easy_init();
	printf("version %s\n", curl_version());
	CURLcode res;
	while (true) {
		if (curl) {
			curl_easy_setopt(curl, CURLOPT_URL,
					 "http://aio.backup.com:8000");
			res = curl_easy_perform(curl);
			printf("res: %d\n", res);
			sleep(2);
		}
	}
	curl_easy_cleanup(curl);

	return 0;
}
