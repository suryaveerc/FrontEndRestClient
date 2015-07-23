/*
 * RepositoryRequestHandler.c
 *
 *  Created on: Jul 21, 2015
 *      Author: suryaveer
 */


#include <stdio.h>
#include <curl/curl.h>

int main(void)
{
	CURL *curl;
	CURLcode res;
	curl_global_init(CURL_GLOBAL_ALL);
	
	struct curl_slist *headers =NULL;
	curl_slist_append(headers, "Accept: application/json");  
   	curl_slist_append( headers, "Content-Type: application/json");
    	curl_slist_append( headers, "charsets: utf-8"); 
	

	curl = curl_easy_init();
	if(curl)
	{
		curl_easy_setopt(curl,CURLOPT_URL,"http://192.168.254.1:8080/PresenceRepository/rest/V1/presentity/microsip@192.168.254.128?event=presence");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	        curl_easy_setopt(curl, CURLOPT_HTTPGET,1); 
        	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); 

		res = curl_easy_perform(curl);

		if(res!=CURLE_OK)
		{
			 fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
		}
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	return 0;
}
