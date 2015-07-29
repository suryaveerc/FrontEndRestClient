/*
 * RepositoryHandler.c
 *
 *  Created on: Jul 21, 2015
 *      Author: suryaveer
 */


#include <stdio.h>
#include <curl/curl.h>
#include "RepositoryAccessClient.h"
#include "../../dprint.h"

int curl_post_to_url(const char* url, char *postdata)
{
	LM_DBG("ENTER INTO curl_post_to_url");
	CURL *curl;
	CURLcode res;
	curl_global_init(CURL_GLOBAL_ALL);
	int http_code = 0;	
	struct curl_slist *headers =NULL;
	headers=curl_slist_append(headers, "Accept: application/json");  
   	headers=curl_slist_append( headers, "Content-Type: application/json");
    	headers=curl_slist_append( headers, "charsets: utf-8"); 
	

	curl = curl_easy_init();
	if(curl)
	{
		LM_DBG("ENTER INTO curl_post_to_url.....INIT");

		/* set URL */
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); 
//		curl_easy_setopt(curl, CURLOPT_POST, 1);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postdata);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcrp/0.1");

		res = curl_easy_perform(curl);
		if(res!=CURLE_OK)
		{
			LM_DBG("curl error OCCURED");
			 LM_DBG("curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
		}

		curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
		LM_DBG("HTTP ERROR CODE %d",http_code);
		curl_easy_cleanup(curl);
	}
	curl_slist_free_all(headers);
	curl_global_cleanup();
	
	return http_code;
}
