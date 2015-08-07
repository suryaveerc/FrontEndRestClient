/*
 * Util.c
 *
 *  Created on: Jul 21, 2015
 *      Author: suryaveer
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Util.h"
#include "Common.h"
#include "cJSON.h"
//#include "../../dprint.h"

//This function fails when values are null. ex: {"username":null}
//Sending default values from the server.
int parse_json_to_result(char *json, db_res_t** result) {
	printf("received json: %s\n", json);
	cJSON *root, *record;
	int recordCount = 0;
	int colCount = 0;
	int i = 0;
	int j = 0;
	int int_val = 0;
	char *str_val = '\0';

	root = cJSON_Parse(json);
	recordCount = cJSON_GetArraySize(root);
	*result = calloc(1,sizeof(db_res_t));
	(*result)->n = recordCount;
	(*result)->rows = calloc(recordCount,sizeof(db_row_t) );

	//this is done to get the count of columns only once.
	record = cJSON_GetArrayItem(root, i);
	colCount = cJSON_GetArraySize(record);

	for (i = 0; i < recordCount; i++) {
		j = 0;
		record = cJSON_GetArrayItem(root, i);
		(*result)->rows[i].n = colCount;
		(*result)->rows[i].values = calloc(colCount,sizeof(db_val_t));
		cJSON *subitem = record->child;
		while (subitem) {
//			printf("%d---%s: ", j, subitem->string);
			if (subitem->type == cJSON_Number) {
				int_val =
						cJSON_GetObjectItem(record, subitem->string)->valueint;
				(*result)->rows[i].values[j].type = DB_INT;
				(*result)->rows[i].values[j].nul = 0;
				(*result)->rows[i].values[j++].val.int_val = int_val;
//				printf("%d\n", int_val);
			} else {
				str_val =
						cJSON_GetObjectItem(record, subitem->string)->valuestring;
//				printf("%s\n", str_val);
				(*result)->rows[i].values[j].type = DB_STRING;
				if (strcmp(str_val, "") == 0) {
					(*result)->rows[i].values[j].nul = 1;
					(*result)->rows[i].values[j++].free = 0;
				} else {
					(*result)->rows[i].values[j].nul = 0;
					(*result)->rows[i].values[j].free = 1;
					(*result)->rows[i].values[j++].val.string_val = strdup(str_val);
				}
			}
			subitem = subitem->next;
		}
	}
//	printf("Done\n");
	cJSON_Delete(root);
	return 1;
}

int create_url(const db_key_t* _k, const db_val_t* _v, const int _n, char* url,
		const char* _rt, const char* _r) {
//microsip@192.168.254.128?event=presence
	printf("ENTER IN create_url\n");
	memcpy(url, ROOT_URL, strlen(ROOT_URL) + 1);
	memcpy(url + strlen(ROOT_URL), _rt, strlen(_rt) + 1);

	int i, len = 0, ret = 0;
	int _l = MAX_URL_LEN;
	len = strlen(url);
	if (_r) {
		if (!_k || !_v || !_n) {
			printf("Required input parameters not supplied.");
			return -1;
		}
		memcpy(url + strlen(url), _r, strlen(_r) + 1);
		ret = snprintf(url + strlen(url), _l, "%s", "?");
		len += ret;
		for (i = 0; i < _n; i++) {

			if (strcmp(_k[i]->s, "domain") == 0
					|| strcmp(_k[i]->s, "username") == 0) {
				continue;
			}
			if (_v[i].type == DB_INT) {
				ret = snprintf(url + len, _l - len, "%s=", _k[i]->s);
				len += ret;
				ret = snprintf(url + len, _l - len, "%d&", _v[i].val.int_val);
				len += ret;
			} else {
				ret = snprintf(url + len, _l - len, "%s=", _k[i]->s);
				len += ret;
				ret = snprintf(url + len, _l - len, "%.*s&",
						_v[i].val.str_val.len, _v[i].val.str_val.s);
				len += ret;
			}
		}

		*(url + len - 1) = '\0'; // to remove the last comma.
	}
	printf("Generated URL: %s\n", url);
	return len <= _l ? 1 : -1;
}

void get_user_from_sip_uri(char *_u, char *_d, char * uri) {
	char *uril = uri;
	char *_ul = _u;

	printf("PASSED URI %s\n", uril);
	uril = uril + 4;
	printf("PASSED URI NOW %s\n", uril);
	while (*uril != '@') {
		*_ul++ = *uril++;
	}
	*_ul = '\0';
	printf("PASSED URIL NOW %s\n", uril);
	printf("FETCHED USER %s\n", _u);
	++uril;
	_ul = _d;
	while (*uril != '\0') {
		*_ul++ = *uril++;
	}
	*_ul = '\0';
	printf("PASSED URIL NOW %s\n", uril);
	printf("FETCHED DOMAIN %s\n", _d);
}

int db_print_single_json(char* _b, const db_key_t* _k, const db_val_t* _v,
		const int _n) {

	printf("In db_print_single_json\n");
	int i, ret, len, _l = 0;
	_l = JSON_BUF_LEN;
	ret = sprintf(_b, "%s", "{");
	len = ret;

//	printf("The current value of buffer is: %s\n",_b);
	if ((!_k) || (!_n) || (!_b) || (!_v)) {
		return -1;
	}
	/*
	 for(i = 0; i < _n; i++)
	 {
	 printf("KEY: %s",_k[i]->s);
	 if(_v[i].type==DB_INT)
	 {
	 printf("VALUE: %d\n",_v[i].val.int_val);
	 }
	 else
	 {
	 printf("VALUE: %s\n",_v[i].val.str_val.s);
	 }
	 }
	 */

	for (i = 0; i < _n; i++) {
//		printf("Now processing Columns:\t\t %s\n",_k[i]->s);
		ret = snprintf(_b + len, _l - len, "\"%.*s\":", _k[i]->len, _k[i]->s);

		if (ret < 0 || ret >= (_l - len))
			;
		len += ret;
		if (_v[i].type == DB_INT) {
//			printf("Which has value:\t\t %d\n",_v[i].val.int_val);
			ret = snprintf(_b + len, _l - len, "%d,", _v[i].val.int_val);
			len += ret;
		} else {
			if (strcmp(_k[i]->s, "body") == 0) {
				ret = escapeXML(_b + len, _v[i].val.str_val.s);
//						printf("Buffer: \t\t %s\n",_b);
				len += ret;
			} else {
//				printf("Which has value:\t\t %s\n",_v[i].val.str_val.s);
				ret = snprintf(_b + len, _l - len, "\"%.*s\",",
						_v[i].val.str_val.len, _v[i].val.str_val.s);
				len += ret;
			}
		}
//		printf("Current buffer filled length:\t\t	 %d\n",len);
	}
	ret = snprintf(_b + len - 1, _l - len - 1, "%s", "}");
//	printf("The current value of buffer is: %s\n",_b);
	return len;
}

int escapeXML(char *_b, char *_source) {
	char *_s = _source;
	char *escapeString = "&quot;";
	char *t1 = escapeString;
	int len = 0;
	len = len + sprintf(_b++, "%s", "\"");
//	printf("Buffer :\t %s\n",_b);
	while (*_s != '\0') {
		escapeString = t1;
		if (*_s == '\"') {
			while (*escapeString) {
				*_b++ = *escapeString++;
				++len;
			}
			++_s;
		} else if (*_s == '\n' || *_s == '\r') {
			++_s;
		} else {
			++len;
			*_b++ = *_s++;
		}
	}
	*_b = '\0';
	len = len + sprintf(_b, "%s", "\",");
//	printf("%d\n",len);
	return len;
}

int free_result(db_res_t* _r)
{
	if (!_r)
	{
		return -1;
	}
	int i,row_count=0;
	int col_count=0;
	printf("freeing result set at %p\n", _r);
	row_count = _r->n;
	printf("RowCount %d .\n",row_count);
	for(i=0;i<row_count;i++)
	{
		printf("Freeing %d row.\n",i);
		col_count= _r->rows[i].n;
		printf("col_count %d .\n",col_count);
		int j=0;
		for(j=0;j<col_count;j++)
		{
			if(_r->rows[i].values[j].type == DB_STRING && _r->rows[i].values[j].nul==0)
			{
				printf("Freeing %d col.\n",j);
				free(_r->rows[i].values[j].val.string_val);
				_r->rows[i].values[j].val.string_val =NULL;
			}
			else if(_r->rows[i].values[j].type == DB_STR  && _r->rows[i].values[j].nul==0)
			{
				printf("Freeing %d col.",j);
				free(_r->rows[i].values[j].val.str_val.s);
				_r->rows[i].values[j].val.str_val.s =NULL;
			}
		}
		free(_r->rows[i].values);
		_r->rows[i].values = NULL;
	}
	free(_r->rows);
	_r->rows =NULL;
	free(_r);
	_r = NULL;
	printf("freed result set a %p\n", _r);
	return 0;
}
