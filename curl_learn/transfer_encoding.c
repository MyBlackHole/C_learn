#include <assert.h>
#include <curl/curl.h>

static char *postdata = "postdata";
static int postsize = 8;

static size_t read_callback(char *buffer, size_t size, size_t nitems,
			    void *userdata)
{
	assert(postsize <= size * nitems);

	int copied = 0;
	for (; postsize > 0; postsize--)
		*buffer++ = *(postdata + copied++);
	return copied;
}

int demo_transfer_encoding_main(void)
{
	// 居然会自动补充 Transfer-Encoding: chunked
	struct curl_slist *headers =
		curl_slist_append(NULL, "Content-Length: 8");
	CURL *curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
	curl_easy_setopt(curl, CURLOPT_URL, "http://localhost/");
	curl_easy_setopt(curl, CURLOPT_POST, 1L);
	curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_0);

	curl_easy_perform(curl);

	return 0;
}
