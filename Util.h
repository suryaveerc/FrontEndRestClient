/*
 * Util.h
 *
 *  Created on: Jul 21, 2015
 *      Author: suryaveer
 */
#include "../../db/db_key.h"
#include "../../db/db_val.h"

int db_print_single_json(char* _b, const db_key_t* _k, const db_val_t* _v, const int _n);
int escapeXML(char *_b, char *_source);
void get_user_from_sip_uri(char *_u,char *_d, char *uri);

