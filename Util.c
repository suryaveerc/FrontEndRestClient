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
#include "../../dprint.h"
//int main(void){ return 1;}

void get_user_from_sip_uri(char *_u, char *_d,char * uri)
{
	char *uril = uri;
	char *_ul = _u;

	LM_DBG("PASSED URI %s\n",uril);
	uril=uril+4;
	LM_DBG("PASSED URI NOW %s\n",uril);
	while(*uril!='@')
	{
		 *_ul++=*uril++;
	}
	*_ul='\0';
	LM_DBG("PASSED URIL NOW %s\n",uril);
	LM_DBG("FETCHED USER %s\n",_u);
	++uril;
	_ul = _d;
	while(*uril!='\0')
		{
			 *_ul++=*uril++;
		}
		*_ul='\0';
		LM_DBG("PASSED URIL NOW %s\n",uril);
			LM_DBG("FETCHED DOMAIN %s\n",_d);
}

int db_print_single_json(char* _b,  const db_key_t* _k, const db_val_t* _v, const int _n)
{

	LM_DBG("ENTER INTO db_print_single_json");
	int i, ret, len , _l= 0;
	_l = JSON_BUF_LEN;
	ret = sprintf(_b,"%s","{");
	len=ret;
	

	LM_DBG("The current value of buffer is: %s\n",_b);
	if ((!_k) || (!_n) || (!_b) || (!_v)) {
		return -1;
	}
	for(i = 0; i < _n; i++)
	{
		LM_DBG("KEY: %s",_k[i]->s);
		if(_v[i].type==DB_INT)
		{
			LM_DBG("VALUE: %d\n",_v[i].val.int_val);
		}
		else
		{
			LM_DBG("VALUE: %s\n",_v[i].val.str_val.s);
		}
	}

	for(i = 0; i < _n; i++)
	{
		LM_DBG("Now processing Columns:\t\t %s\n",_k[i]->s);
		ret = snprintf(_b + len, _l - len, "\"%.*s\":", _k[i]->len, _k[i]->s);
			
		if (ret < 0 || ret >= (_l - len));
		len += ret;
		if(_v[i].type==DB_INT)
		{
			LM_DBG("Which has value:\t\t %d\n",_v[i].val.int_val);
			ret = snprintf(_b + len, _l - len, "%d,", _v[i].val.int_val);
			len += ret;
		}
		else
		{
			if(strcmp(_k[i]->s,"body")==0)
			{
				ret = escapeXML(_b+len,_v[i].val.str_val.s);
//						printf("Buffer: \t\t %s\n",_b);
				len += ret;
			}
			else
			{
				LM_DBG("Which has value:\t\t %s\n",_v[i].val.str_val.s);
				ret = snprintf(_b + len, _l - len, "\"%.*s\",", _v[i].val.str_val.len, _v[i].val.str_val.s);				
				len += ret;
			}
		}
		LM_DBG("Current buffer filled length:\t\t	 %d\n",len);
	}
	ret = snprintf(_b+len-1,_l-len-1,"%s","}");
	LM_DBG("The current value of buffer is: %s\n",_b);
	return len;
}

int escapeXML(char *_b, char *_source)
{
	char *_s = _source;
	char *escapeString = "&quot;";
	char *t1=escapeString;
	int len = 0;
	len = len + sprintf(_b++,"%s","\"");
//	printf("Buffer :\t %s\n",_b);
	while(*_s!='\0')	
	{	escapeString = t1;
		if(*_s == '\"')
		{
			while(*escapeString)
			{
				*_b++ = *escapeString++;
				++len;
			}
			++_s;
		}
		else if(*_s == '\n'|| *_s == '\r')
		{
			++_s;
		}
		else
		{
			++len;
			*_b++ = *_s++;
		}
	}
	*_b='\0';
	len = len + sprintf(_b,"%s","\",");
//	printf("%d\n",len);
	return len;
}
