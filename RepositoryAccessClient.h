/*
 * RepositoryAccessClient.h
 *
 *  Created on: Jul 21, 2015
 *      Author: suryaveer
 */


int curl_post_to_url(const char* url, char *postdata);
int curl_get_from_url(const char* url, struct payload p);
static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp);
