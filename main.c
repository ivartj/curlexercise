#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <curl/curl.h>

const char *progname = "curlexercise";

void vwarning(const char *fmt, va_list ap)
{
	fprintf(stderr, "%s: ", progname);
	vfprintf(stderr, fmt, ap);
	fputs("\n", stderr);
}

void warning(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vwarning(fmt, ap);
}

void fatal(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vwarning(fmt, ap);
	exit(1);
}

// Returns a cURL error code.
int fetch(void)
{
	CURL *handle;
	int err;

	handle = curl_easy_init();
	curl_easy_setopt(handle, CURLOPT_URL, "http://stud.ux.uis.no/~ivartj/");
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, fwrite);
	curl_easy_setopt(handle, CURLOPT_WRITEDATA, stdout);
	err = curl_easy_perform(handle);
	return err;
}

int main(int argc, char *argv[])
{
	int err;
	
	if(argc)
		progname = argv[0];
	err = curl_global_init(CURL_GLOBAL_WIN32);
	if(err != CURLE_OK)
		fatal(curl_easy_strerror(err));
	atexit(curl_global_cleanup);
	err = fetch();
	if(err != CURLE_OK)
		fatal(curl_easy_strerror(err));
	exit(0);
}
