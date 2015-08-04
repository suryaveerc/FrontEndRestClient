/*
 * RepositoryHandler.c
 *
 *  Created on: Jul 21, 2015
 *      Author: suryaveer
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Common.h"
#include "Util.h"
#include "RepositoryAccessClient.h"
#include "RepositoryHandler.h"
//#include "../../dprint.h"


int updateResource(const db_key_t* _qk, const db_val_t* _qv,
		const db_key_t* _uk, const db_val_t* _uv, const int _qn, const int _un,
		const char *_rt, const char *_r) {

	if ((!_qk) || (!_qv) || (!_qn) || (!_uk) || (!_uv) || (!_un) || (!_rt) || (!_r))
	{
		printf("Required parameters not received.\n");
		return -1;
	}
	char *jsonBuffer = malloc(JSON_BUF_LEN);
	int status = 0;
	status = db_print_single_json(jsonBuffer, _uk, _uv, _un);

	if (!status) {
		printf("Unable to process the requested input");
		free(jsonBuffer);
		return -1;
	}

	char *url = malloc(MAX_URL_LEN);
	if (create_url(_qk, _qv, _qn, url, _rt, _r) < 0) {
		printf("Unable to create complete URL\n");
		return -1;
	}
	printf("The URL is %s: \n", url);

	status = curl_put(url, jsonBuffer);
	if (status)
		printf("PUT to %s successful with status %d. \n", url, status);
	else
		printf("PUT to %s failed. \n", url);

	free(url);
	free(jsonBuffer);
	return (status != 200 ? 0 : 1);
}

int insertResource(const db_key_t* _k, const db_val_t* _v, const int _n,
		const char *_rt, const char *_r) {

	if ((!_k) || (!_v) || (!_n) || (!_rt))
		return -1;
	char *jsonBuffer = malloc(JSON_BUF_LEN);
	int status = 0;
	status = db_print_single_json(jsonBuffer, _k, _v, _n);

	if (!status) {
		printf("Unable to process the requested input");
		free(jsonBuffer);
		return -1;
	}

	char *url = malloc(MAX_URL_LEN);
	memcpy(url, ROOT_URL, strlen(ROOT_URL) + 1);
	memcpy(url + strlen(ROOT_URL), _rt, strlen(_rt) + 1);
	printf("The URL is %s: \n", url);
	if (!_r)/* Presence of _r represent the request for PUT request*/
	{
		status = curl_post(url, jsonBuffer);
		if (status)
			printf("POST to %s successful with status %d. \n", url, status);
		else
			printf("POST to %s failed. \n", url);
	} else {
		status = curl_post(url, jsonBuffer);
		if (status)
			printf("POST to %s successful with status %d. \n", url, status);
		else
			printf("POST to %s failed. \n", url);
	}
	free(url);
	free(jsonBuffer);
	return (status != 200 ? 0 : 1);
}

int getResource(const db_key_t* _k, const db_val_t* _v, const int _n,
		db_res_t** _r, const char *_rt, char* _p) {
	if (!_k || !_v || !_n || !_p || !_rt) {
		printf("Required values not provided.\n");
		return -1;
	}
	char* url = (char*) malloc(MAX_URL_LEN);
	if (create_url(_k, _v, _n, url, _rt, _p) < 0) {
		printf(
				"Failed to process request. URL creation failed. Resource is: %s\n",
				_p);
		return -1;
	}
	int status = 0;
	struct result_st *result;
	result->payload = (char*) malloc(1);
	result->size = 0;
	status = curl_get(url, &result);
	printf("GETRESOURCE: result after GET: %s\n", result->payload);
	if (status)
		printf("GEt from %s successful with status %d. \n", url, status);
	else
		printf("GET from %s failed with status %d. \n", url, status);
	free(url);
	parse_json_to_result(result->payload, _r);
	return (status != 200 ? 0 : 1);
}

int checkResource(const db_key_t* _k, const db_val_t* _v, const int _n, const char *_rt, char* _p)
{
	if (!_k || !_v || !_n || !_p || !_rt) {
		printf("Required values not provided.\n");
		return -1;
	}
	char* url = (char*) malloc(MAX_URL_LEN);
	if (create_url(_k, _v, _n, url, _rt, _p) < 0) {
		printf("Failed to process request. URL creation failed. Resource is: %s\n",_p);
		return -1;
	}
	int status = 0;
	status = curl_head(url);
	if (status)
		printf("HEAD for %s successful with status %d. \n", url, status);
	else
		printf("HEAD for %s failed with status %d. \n", url, status);
	free(url);
	return (status != 200 ? 0 : 1);
}

int deleteResource(const db_key_t* _k, const db_val_t* _v, const int _n, const char *_rt, char* _p)
{
	if (!_k || !_v || !_n || !_p || !_rt) {
		printf("Required values not provided.\n");
		return -1;
	}
	char* url = (char*) malloc(MAX_URL_LEN);
	if (create_url(_k, _v, _n, url, _rt, _p) < 0) {
		printf("Failed to process request. URL creation failed. Resource is: %s\n",_p);
		return -1;
	}
	int status = 0;
	status = curl_delete(url);
	if (status)
		printf("DELETE for %s successful with status %d. \n", url, status);
	else
		printf("DELETE for %s failed with status %d. \n", url, status);
	free(url);
	return (status != 200 ? 0 : 1);
}
/*
int curl_perform(char* url, char operation)
{
	switch(operation)
	{
		case DELETE :
		break;
		case GET :
		break;
		case HEAD :
		break;
		default :
		printf("Invalid Operation\n" );
	}
}*/
