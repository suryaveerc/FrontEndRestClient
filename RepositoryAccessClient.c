/*
 * RepositoryHandler.c
 *
 *  Created on: Jul 21, 2015
 *      Author: suryaveer
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "RepositoryAccessClient.h"
//#include "../../dprint.h"


struct curl_fetch_st {
    char *payload;
    size_t size;
};

int curl_post_to_url(const char* url, char *postdata)
{
	if(!url)
	{
		printf("URL not provided. Returning with error.\n");
		return -1;
	}
	
	printf("Preparing to POST to URL: %s\n",url);
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
		printf("ENTER INTO curl_post_to_url.....INIT\n");

		/* set URL */
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); 
//		curl_easy_setopt(curl, CURLOPT_POST, 1);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postdata);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcrp/0.1");

		res = curl_easy_perform(curl);
		if(res!=CURLE_OK)
		{
			printf("curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
		}
		curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
		printf("HTTP return CODE %d",http_code);
	}
	else
	{
		printf("Curl initialization failed.\n");
		curl_easy_cleanup(curl);
		curl_slist_free_all(headers);
		curl_global_cleanup();
		return -1;
	}
	curl_easy_cleanup(curl);
	curl_slist_free_all(headers);
	curl_global_cleanup();
	return http_code;
}

int curl_get_from_url(const char* url, struct* curl_payload)
{
	if(!url)
	{
		printf("URL not provided. Returning with error.\n");
		return -1;
	}
	printf("Preparing to GET from URL: %s\n",url);
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
		struct curl_fetch_st cf; 
	  	cf.payload = malloc(1);
	  	cf.size = 0;

		/* set URL */
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); 
		if(curl_payload!=NULL)
		{
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&cf);
		}
		res = curl_easy_perform(curl);
		if(res!=CURLE_OK)
		{
			printf("curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
		}
		else
		{
			if(curl_payload)
			{
				printf("cf.sizz: %d\n",cf.size);
				curl_payload = realloc(curl_payload,cf.size);
				if (curl_payload == NULL) {
					printf("Failed to expand buffer in curl.\n");
					curl_easy_cleanup(curl);
					curl_slist_free_all(headers);
					curl_global_cleanup();
					return -1;
				}
				memcpy(curl_payload, cf.payload,cf.size+1);
				 printf("In get payload : %s\n",curl_payload);
			}	
		}

		curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
		printf("HTTP return CODE %d\n",http_code);
	}
	else
	{
		printf("Curl initialization failed.\n");
	curl_easy_cleanup(curl);
	curl_slist_free_all(headers);
	curl_global_cleanup();
		return -1;
	}
	curl_easy_cleanup(curl);
	curl_slist_free_all(headers);
	curl_global_cleanup();
	return http_code;
}
static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct curl_fetch_st *cf = (struct curl_fetch_st *)userp;
 
  cf->payload = realloc(cf->payload, cf->size + realsize + 1);
  if(cf->payload == NULL) {
    /* out of memory! */ 
    printf("not enough memory (realloc returned NULL)\n");
    return -1;
  }
 
  memcpy(&(cf->payload[cf->size]), contents, realsize);
  cf->size += realsize;
  cf->payload[cf->size] = 0;
 printf("In callback: %s\n",cf->payload);
  return realsize;
}

