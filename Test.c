#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Util.h"
#include "RepositoryAccessClient.h"
#include "Common.h"

void test_curl_get(char* url);
int testUTIL_createURL(char* url);
static const char *R_PRESENTITY ="presentity";
static const char *ROOT_URL ="http://192.168.254.1:8080/PresenceRepository/rest/V1/";

int main(void)
{
	
/*	char *url = (char*)malloc(MAX_URL_LEN);
	memcpy ( url, ROOT_URL, strlen(ROOT_URL)+1 );
	printf("%s\n",url);
	memcpy ( url+strlen(ROOT_URL), R_PRESENTITY, strlen(R_PRESENTITY)+1 );
	printf("%s\n",url);
	memcpy ( url+strlen(url), "/microsip@192.168.254.128", strlen("/microsip@192.168.254.128")+1 );
	printf("%s\n",url);
	testUTIL_createURL(url);*/
	test_getResource();
//	test_curl_get(url);
	return 1;
}
void test_curl_get(char* url)
{
	char* curl_payload = (char*)malloc(1);
	curl_get_from_url(url, NULL);
}

int test_getResource(char* url)
{
	db_res_t* result=NULL;
	db_key_t query_cols[4];
	db_val_t query_vals[4];
	int n_query_cols = 0;
	str domain	= str_init("domain");
	str username	= str_init("username");
	str event	= str_init("event");
	str etag	= str_init("etag");

	str domainValue	= str_init("192.168.254.129");
	str usernameValue	= str_init("microsip");
	str eventValue	= str_init("presence");
	str etagValue	= str_init("a.1437194656.2922.1.0");


	query_vals[n_query_cols].val.str_val=domainValue;
	query_vals[n_query_cols].type=DB_STR;
	query_cols[n_query_cols++]=&domain;

	query_vals[n_query_cols].val.str_val=usernameValue;
	query_vals[n_query_cols].type=DB_STR;
	query_cols[n_query_cols++]=&username;

	query_vals[n_query_cols].val.str_val=eventValue;
	query_vals[n_query_cols].type=DB_STR;
	query_cols[n_query_cols++]=&event;

	query_vals[n_query_cols].val.str_val=etagValue;
	query_vals[n_query_cols].type=DB_STR;
	query_cols[n_query_cols++]=&etag;
	
	int status = 0; 

	status =  getResource(query_cols, query_vals, n_query_cols, &result, "presentity/","microsip@192.168.254.128", 1);

	printf("Return status : %d\n", status);

	return 1;
}

int testUTIL_create_json_struct()
{
	char *json = "[{\"domain\":\"192.168.254.128\",\"username\":\"microsip\",\"event\":\"presence\",\"etag\":\"a.1437194656.2922.1.0\",\"expires\":1437200355,\"sender\":\"\",\"body\": \"\",\"received_time\":\"1437196755\"},{\"domain\":\"192.168.254.128\",\"username\":\"microsip\",\"event\":\"presence\",\"etag\":\"a.2922.1.0\",\"expires\":456,\"sender\":\"\",\"body\": \"\",\"received_time\":\"1437196755\"}]";

	db_res_t *result = NULL;
	int i=0;

	i = parse_json_to_result(json, &result);

	printf("result0: %d\n",result->rows[1].values->val.int_val);
	printf("result1: %d\n",result->rows[0].values->val.int_val);
	 return 1;
}

