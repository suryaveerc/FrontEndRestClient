/*
 * RepositoryAccess.c
 *
 *  Created on: Jul 21, 2015
 *      Author: suryaveer
 */


/* This function will insert/update the resource in the repository.
Input Parameters:
 db_key_t* _k: List of Columns.
 db_val_t* _v: List of Values
 int _n total: number of values
 char _t: Type of resource (Presentity/Subscriber/ etc)
 char _r: Id of resource in case of PUT request. Optional.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Common.h"
#include "Util.h"

int upsertResource(const db_key_t* _k, const db_val_t* _v, const int _n, const char *_rt, const char *_r)
{
	char *jsonBuffer = malloc(JSON_BUF_LEN);
	int status=0;
	if( (!_k) || (!_v) || (!_n) || (!_rt) )
		return -1;
	

	status = db_print_single_json(jsonBuffer, _k,_v,_n);

	if(!status)
	{
		printf("Unable to process the requested input");
		return -1;
	}

	char *url = malloc(MAX_URL_LEN);
	strcat(url,ROOT_URL);
	strcat(url,R_PRESENTITY);
	printf("The URL is %s: \n",url);
	printf("The current value of buffer is: %s\n",jsonBuffer);
	if(!_r)
	{
		/* Presence of _r represent the request for PUT request*/
		curl_post_to_url(url,jsonBuffer);
	}
	free(url);
	free(jsonBuffer);
	return 0;
}
int main(void)
{
	db_key_t query_cols[13];
	db_val_t query_vals[13];
	int n_query_cols = 0;
	str domain	= str_init("domain");
	str username	= str_init("username");
	str event	= str_init("event");
	str etag	= str_init("etag");
	str expires	= str_init("expires");
	str sender	= str_init("sender");
	str body	= str_init("body");
	str receivedTime	= str_init("receivedTime");

	str domainValue	= str_init("192.168.254.129");
	str usernameValue	= str_init("suryaveer");
	str eventValue	= str_init("presence");
	str etagValue	= str_init("a.1437194656.2922.1.0");
	int expiresValue	= 1437200355;
	str senderValue	= str_init("");
	str bodyValue	= str_init("<?xml version=\"1.0\" encoding=\"UTF-8\"?><presence entity=\"sip:microsip@192.168.254.128\" xmlns=\"urn:ietf:params:xml:ns:pidf\" xmlns:dm=\"urn:ietf:params:xml:ns:pidf:data-model\" xmlns:rpid=\"urn:ietf:params:xml:ns:pidf:rpid\"> <tuple id=\"pj3812dd2fb6f24ca5956323c7895bc2c6\">  <status>   <basic>open</basic>  </status>  <timestamp>2015-07-18T01:19:15.172Z</timestamp>  <note>Idle</note> </tuple> <dm:person id=\"pj155edc6d5cb64829a79b25e2ff4a9b5e\">  <rpid:activities>   <rpid:unknown />  </rpid:activities>  <dm:note>Idle</dm:note> </dm:person></presence>");
	int receivedTimeValue	= 1437196755;


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

	query_vals[n_query_cols].val.int_val=expiresValue;
	query_vals[n_query_cols].type=DB_INT;
	query_cols[n_query_cols++]=&expires;

	query_vals[n_query_cols].val.str_val=senderValue;
	query_vals[n_query_cols].type=DB_STR;
	query_cols[n_query_cols++]=&sender;

	query_vals[n_query_cols].val.str_val=bodyValue;
	query_vals[n_query_cols].type=DB_STR;
	query_cols[n_query_cols++]=&body;
	
	query_vals[n_query_cols].val.int_val=receivedTimeValue;
	query_vals[n_query_cols].type=DB_INT;
	query_cols[n_query_cols]=&receivedTime;

	int status = 0; 
	status = upsertResource(query_cols,  query_vals,  n_query_cols,  "Presentity",  NULL);

	printf("Return status : %d\n", status);
}	

