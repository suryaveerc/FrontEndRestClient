#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Util.h"
#include "RepositoryAccessClient.h"
#include "Common.h"

void test_curl_get(char* url);
void test_util_get();
int testUTIL_createURL(char* url);
static const char *R_PRESENTITY = "presentity";
//static const char *ROOT_URL ="http://192.168.254.1:8080/PresenceRepository/rest/V1/";

int main(void) {

	/*	char *url = (char*)malloc(MAX_URL_LEN);
	 memcpy ( url, ROOT_URL, strlen(ROOT_URL)+1 );
	 printf("%s\n",url);
	 memcpy ( url+strlen(ROOT_URL), R_PRESENTITY, strlen(R_PRESENTITY)+1 );
	 printf("%s\n",url);
	 memcpy ( url+strlen(url), "/microsip@192.168.254.128", strlen("/microsip@192.168.254.128")+1 );
	 printf("%s\n",url);
	 testUTIL_createURL(url);*/
//	testPost();
	test_util_get();
	return 1;
}

void test_util_get() {
	db_res_t *result = NULL;
	/*char* url =
			"http://192.168.254.1:8080/PresenceRepository/rest/V1/presentity";
	getResource(NULL, NULL, 0, &result, PRESENTITY, NULL);*/
	char* json = "[{\"id\":11,\"username\":\"microsip\",\"domain\":\"192.168.254.128\",\"event\":\"presence\",\"etag\":\"a.1437194656.2922.1.0\",\"expires\":1437200355,\"received_time\":-1,\"body\":\"\",\"extra_hdrs\":\"\",\"sender\":\"\"},{\"id\":12,\"username\":\"microsip\",\"domain\":\"92.168.254.128\",\"event\":\"presence\",\"etag\":\"a.1437194656.2922.1.0\",\"expires\":1437200355,\"received_time\":-1,\"body\":\"\",\"extra_hdrs\":\"\",\"sender\":\"\"}]";
	parse_json_to_result(json,&result);
	free_result(result);
}

int testPost() {

	char* url =
			"http://192.168.254.1:8080/PresenceRepository/rest/V1/presentity";
	char* data =
			" {\"username\":\"korea\",\"domain\":\"192.168.254.131\",\"event\":\"presence\",\"etag\":\"a.1438804374.29490.1.0\",\"expires\":1438808052,\"sender\":\"\",\"body\":\"<?xml version=&quot;1.0&quot; encoding=&quot;UTF-8&quot;?><presence entity=&quot;sip:nkorea@192.168.254.131&quot; xmlns=&quot;urn:ietf:params:xml:ns:pidf&quot;> <tuple id=&quot;pjd9ba66dde5b94997b640c149575512fa&quot;>  <status>   <basic>open</basic>  </status>  <timestamp>2015-08-05T15:54:12.427Z</timestamp> </tuple></presence>\",\"received_time\":1438804452}";
	curl_post(url, data);
}

int test_updateResource() {
	db_res_t* result = NULL;
	db_key_t query_cols[4];
	db_val_t query_vals[4];
	db_key_t update_cols[5];
	db_val_t update_vals[5];
	int n_query_cols = 0;
	int n_update_cols = 0;
	//query keys
	str domain = str_init("domain");
	str username = str_init("username");
	str event = str_init("event");
	str etag = str_init("etag");
	// update keys
	str expires = str_init("expires");
	str sender = str_init("sender");
	str body = str_init("body");
	str receivedTime = str_init("received_time");

	str domainValue = str_init("192.168.254.128");
	str usernameValue = str_init("microsip");
	str eventValue = str_init("presence");
	str etagValue = str_init("a.1437194656.2922.1.0");
	str etagValue_q = str_init("a.1437194656.2922.1.2");
	int expiresValue = 1437200355;
	str senderValue = str_init("");
	str bodyValue =
					str_init(
							"<?xml version=\"1.0\" encoding=\"UTF-8\"?><presence entity=\"sip:microsip@192.168.254.128\" xmlns=\"urn:ietf:params:xml:ns:pidf\" xmlns:dm=\"urn:ietf:params:xml:ns:pidf:data-model\" xmlns:rpid=\"urn:ietf:params:xml:ns:pidf:rpid\"> <tuple id=\"pj3812dd2fb6f24ca5956323c7895bc2c6\">  <status>   <basic>open</basic>  </status>  <timestamp>2015-07-18T01:19:15.172Z</timestamp>  <note>Idle</note> </tuple> <dm:person id=\"pj155edc6d5cb64829a79b25e2ff4a9b5e\">  <rpid:activities>   <rpid:unknown />  </rpid:activities>  <dm:note>Idle</dm:note> </dm:person></presence>");
	int receivedTimeValue = 1437196755;

	query_vals[n_query_cols].val.str_val = domainValue;
	query_vals[n_query_cols].type = DB_STR;
	query_cols[n_query_cols++] = &domain;

	query_vals[n_query_cols].val.str_val = usernameValue;
	query_vals[n_query_cols].type = DB_STR;
	query_cols[n_query_cols++] = &username;

	query_vals[n_query_cols].val.str_val = eventValue;
	query_vals[n_query_cols].type = DB_STR;
	query_cols[n_query_cols++] = &event;

	query_vals[n_query_cols].val.str_val = etagValue_q;
	query_vals[n_query_cols].type = DB_STR;
	query_cols[n_query_cols++] = &etag;

	//update keys
	update_cols[n_update_cols] = &etag;
	update_vals[n_update_cols].type = DB_STR;
	update_vals[n_update_cols++].val.str_val = etagValue;

	update_cols[n_update_cols] = &expires;
	update_vals[n_update_cols].type = DB_INT;
	update_vals[n_update_cols].val.int_val = expiresValue;

	update_cols[n_update_cols] = &sender;
	update_vals[n_update_cols].type = DB_STR;
	update_vals[n_update_cols++].val.str_val = senderValue;

	update_cols[n_update_cols] = &body;
	update_vals[n_update_cols].type = DB_STR;
	update_vals[n_update_cols++].val.str_val = bodyValue;

	update_cols[n_update_cols] = &receivedTime;
	update_vals[n_update_cols].type = DB_INT;
	update_vals[n_update_cols++].val.int_val = receivedTimeValue;

	int status = 0;

	status = updateResource(query_cols, query_vals, update_cols, update_vals,
			n_query_cols, n_update_cols, PRESENTITY,
			"microsip@192.168.254.128");

	printf("Return status : %d\n", status);

	return 1;
}

/*
 int testUTIL_create_json_struct() {
 char *json =
 "[{\"domain\":\"192.168.254.128\",\"username\":\"microsip\",\"event\":\"presence\",\"etag\":\"a.1437194656.2922.1.0\",\"expires\":1437200355,\"sender\":\"\",\"body\": \"\",\"received_time\":\"1437196755\"},{\"domain\":\"192.168.254.128\",\"username\":\"microsip\",\"event\":\"presence\",\"etag\":\"a.2922.1.0\",\"expires\":456,\"sender\":\"\",\"body\": \"\",\"received_time\":\"1437196755\"}]";

 db_res_t *result = NULL;
 int i = 0;

 i = parse_json_to_result(json, &result);

 printf("result0: %d\n", result->rows[1].values->val.int_val);
 printf("result1: %d\n", result->rows[0].values->val.int_val);
 return 1;
 }
 */

