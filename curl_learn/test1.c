#define CURL_STATICLIB
#include <stdio.h>
#include <stdlib.h>

#include "curl/curl.h"

int demo_test1_main(void)
{
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
		curl_easy_setopt(
			curl, CURLOPT_URL,
			"https://api.metaengine.yzbtkj.cn/v2/add_new_questions");
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
		struct curl_slist *headers = NULL;
		headers =
			curl_slist_append(headers, "accept: application/json");
		headers = curl_slist_append(headers,
					    "Content-Type: application/json");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		const char *data =
			"{\r\n    \"key\": \"d8c7084c-3be4-5636-8168-d3b438c920d1\",\r\n   "
			" "
			"\"secret\": "
			"\"49810c57bb55d056c629e48caf8a98998e96a9da51907d25ea5888ccf88ba624"
			"\","
			"\r\n    \"app_id\": \"a3a58df6571011ecad83e0d55eeff354\",\r\n    "
			"\"case_text\" :\"顾客试穿了一件大衣与裤子\",\r\n    \"sales_id\": "
			"1\r\n}\r\n";
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
		res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));
		}
	}
	curl_easy_cleanup(curl);
	return 0;
}
