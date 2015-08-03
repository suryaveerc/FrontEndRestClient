/*
 * RepositoryAccessClient.h
 *
 *  Created on: Jul 21, 2015
 *      Author: suryaveer
 */


struct result_st {
    char *payload;
    size_t size;
};

int curl_post_to_url(const char* url, char *postdata);
int curl_get_from_url(const char* url, struct result_st **result);
static size_t write_callback(void *contents, size_t size, size_t nmemb, void **userp);
