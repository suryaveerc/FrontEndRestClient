/*
 * RepositoryHandler.h
 *
 *  Created on: Jul 21, 2015
 *      Author: suryaveer
 */
/* This function will insert the resource in the repository.
Input Parameters:
 db_key_t* _k: List of Columns.
 db_val_t* _v: List of Values
 int _n total: number of values
 char _rt: Type of resource (Presentity/Subscriber/ etc)
 char _r: Id of resource in case of PUT request. Optional.
*/

int upsertResource(const db_key_t* _k, const db_val_t* _v, const int _n, const char *_rt, const char *_r);

/* This function will insert/update the resource in the repository.
Input Parameters:
 db_key_t* _k: List of Columns.
 db_val_t* _v: List of Values
 int _n total: number of values
 db_res_t** _r: Pointer to structure where results will be stored.
 char _rt: Type of resource (Presentity/Subscriber/ etc)
 char _p: Id of resource. ex username@domain.com
*/

int getResource(const db_key_t* _k, const db_val_t* _v, const int _n, db_res_t** _r, const char *_rt, char* _p, int _f);
int checkResource(const db_key_t* _k, const db_val_t* _v, const int _n, const char *_rt, char* _p);

