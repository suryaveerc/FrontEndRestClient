/*
 * Util.c
 *
 *  Created on: Jul 21, 2015
 *      Author: suryaveer
 */


#include <stdio.h>
#include "Util.h"


int main(void)
{
	char *jsonBuffer;
	db_key_t query_cols[13];
	db_val_t query_vals[13];
	int n_query_cols = 0;
	str A = str_init("A");
	str B = str_init("B");
	str C = str_init("C");
	str D = str_init("D");
	str Av = str_init("AAA");
	str Bv = str_init("BBB");
	str Dv = str_init("DDDD");

	query_vals[n_query_cols].val.str_val=Av;
	query_vals[n_query_cols].type=DB_STR;
	query_cols[n_query_cols++]=&A;
	query_vals[n_query_cols].val.str_val=Bv;
	query_vals[n_query_cols].type=DB_STR;
	query_cols[n_query_cols++]=&B;
	query_vals[n_query_cols].val.int_val=12;
	query_vals[n_query_cols].type=DB_INT;
	query_cols[n_query_cols++]=&C;
	query_vals[n_query_cols].val.str_val=Dv;
	query_vals[n_query_cols].type=DB_STR;
	query_cols[n_query_cols]=&D;
	
	int status = db_print_single_json(&jsonBuffer,SQL_BUF_LEN,query_cols,query_vals,n_query_cols);

	printf("Return status : %d\n", status);
}	
/* [{"domain":"192.168.254.128","username":"microsip"}] */
int db_print_single_json(char* _b, const int _l, const db_key_t* _k, const db_val_t* _v, const int _n)
{
	int i, ret, len = 0;
	ret = sprintf(_b,"%s","[{");
	len=ret;
	printf("The current value of buffer is: %s\n",_b);
	if ((!_k) || (!_n) || (!_b) || (!_l) || (!_v)) {
		return -1;
	}

	for(i = 0; i <= _n; i++)
	{
	
		ret = snprintf(_b + len, _l - len, "\"%.*s\":", _k[i]->len, _k[i]->s);
			printf("The current value of buffer is: %s\n",_b);
		if (ret < 0 || ret >= (_l - len));
		len += ret;
		if(_v[i].type==DB_INT)
		{
			ret = snprintf(_b + len, _l - len, "%d,", _v[i].val.int_val);
			printf("The current value of buffer is: %s\n",_b);
			len += ret;
		}
		else
		{
			ret = snprintf(_b + len, _l - len, "\"%.*s\",", _v[i].val.str_val.len, _v[i].val.str_val.s);				
			printf("The current value of buffer is: %s\n",_b);
			len += ret;
		}
	}
	ret = snprintf(_b+len-1,_l-len-1,"%s","}]");
	printf("The current value of buffer is: %s\n",_b);
	return len;
}
