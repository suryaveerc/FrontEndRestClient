/*
 * Util.h
 *
 *  Created on: Jul 21, 2015
 *      Author: suryaveer
 */
#define str_h

struct _str{
	char* s; /**< string as char array */
	int len; /**< string length, not including null-termination */
};

#define SQL_BUF_LEN 65536
#define str_init(_string)  {_string, sizeof(_string) - 1}

typedef enum {
	DB_INT,        /**< represents an 32 bit integer number      */
	DB_BIGINT,     /**< represents an 64 bit integer number      */
	DB_DOUBLE,     /**< represents a floating point number       */
	DB_STRING,     /**< represents a zero terminated const char* */
	DB_STR,        /**< represents a string of 'str' type        */
	DB_DATETIME,   /**< represents date and time                 */
	DB_BLOB,       /**< represents a large binary object         */
	DB_BITMAP      /**< an one-dimensional array of 32 flags     */
} db_type_t;
typedef struct _str str;
typedef str* db_key_t;
typedef struct {
	db_type_t type; /**< Type of the value                              */
	int nul;		/**< Means that the column in database has no value */
	int free;		/**< Means that the value should be freed */
	/** Column value structure that holds the actual data in a union.  */
	union {
		int           int_val;    /**< integer value              */
		long long     bigint_val; /**< big integer value          */
		double        double_val; /**< double value               */
		const char*   string_val; /**< zero terminated string     */
		str           str_val;    /**< str type string value      */
		str           blob_val;   /**< binary object data         */
		unsigned int  bitmap_val; /**< Bitmap data type           */
	} val;
} db_val_t;

typedef struct db_row {
	db_val_t* values;  /**< Columns in the row */
	int n;             /**< Number of columns in the row */
} db_row_t;
typedef struct db_res {
	struct {
		db_key_t* names;   /**< Column names                    */
		db_type_t* types;  /**< Column types                    */
		int n;             /**< Number of columns               */
	} col;
	struct db_row* rows;   /**< Rows                            */
	int n;                 /**< Number of rows in current fetch */
	int res_rows;          /**< Number of total rows in query   */
	int last_row;          /**< Last row                        */
} db_res_t;
int db_print_single_json(char* _b, const db_key_t* _k, const db_val_t* _v, const int _n);
int escapeXML(char *_b, char *_source);
void get_user_from_sip_uri(char *_u,char *_d, char *uri);
int parse_json_to_result(char *json, db_res_t** result);
int create_url(const db_key_t* _k, const db_val_t* _v, const int _n, char *url);
