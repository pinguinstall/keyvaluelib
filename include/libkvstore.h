#ifndef ____LIBKVSTORE__H__
#define ____LIBKVSTORE__H__

#include <stdio.h>

#define KV_INT_T 0
#define KV_LONG_LONG_INT_T 1
#define KV_UINT_T 2
#define KV_LONG_LONG_UINT_T 3
#define KV_DOUBLE_T 4
#define KV_FLOAT_T 5
#define KV_CHARS_T 6

#define KV_INIT_VALUE 0

// KV store types
/////////////////////////////////////////////////////////////
/**
* @brief most elementary entry in a list
* 
*/
typedef struct kventry_t {
    int kvdtype;
    char *name;
    void *data;
    //TODO needed for array stores
    //const char* const name_postfixes[];
    //long long unsigned int len;
} kventry_t;


/**
* @brief the list of entries in the key value store
* 
*/
typedef struct kvstore_t {
    long long unsigned int len;
    kventry_t **entries;
} kvstore_t;


// col store types
/////////////////////////////////////////////////////////////
typedef struct kvcolumn_t {
    char *name;
    int dtype;
    void *data;
} kvcolumn_t;


typedef struct kvtablestore_t {
  long long unsigned int numcols;
  long long unsigned int len;
  
  kvcolumn_t *cols;
} kvtablestore_t;


// key and value sets
/////////////////////////////////////////////////////////////
typedef struct kvkeyset_t {
    long long unsigned int len;
    char **keys;
} kvkeyset_t;


typedef struct kvvalueset_double_t {
    long long unsigned int len;
    double *values;
} kvvalueset_double_t;


typedef struct kvvalueset_int_t {
    long long unsigned int len;
    int *values;
} kvvalueset_int_t;


typedef struct kvvalueset_uint_t {
    long long unsigned int len;
    unsigned int *values;
} kvvalueset_uint_t;


typedef struct kvvalueset_llint_t {
    long long unsigned int len;
    long long int *values;
} kvvalueset_llint_t;


typedef struct kvvalueset_lluint_t {
    long long unsigned int len;
    long long unsigned int *values;
} kvvalueset_lluint_t;


// top level functions
/////////////////////////////////////////////////////////////

// for table store

/**
* @brief initialize the table store
* 
* @param tblstore p_tblstore:pointer to a tablestore pointer
*/
void KVT_init_table_store(kvtablestore_t **tblstore);

/**
* @brief totally deallocate a tablestore
* 
* @param tblstore p_tblstore:pointer to a tablestore pointer
*/
void KVT_deallocate_table_store(kvtablestore_t **tblstore);

/**
* @brief Insert data into the table at row "idx" and column with key "key". You must provide an void*
* to the data and the data type. If dtype does not fit the dtype of the column 0 is returned and
* nothing is inserted. If insertion has occurred 1 is returned. table is expanded in both dimensions
* if necessary, data is always overwritten if it already exist.
* 
* @param tblstore p_tblstore: pointer to tablestore
* @param key p_key: column key
* @param idx p_idx: row index
* @param dtype p_dtype: dataytpe to insert
* @param value p_value: void* to data
* @return long long int
*/
int KVT_insert_into_store_via_idxKey(kvtablestore_t **tblstore, const char* key, long long int idx, int dtype, void* value);
void KVT_print_table(FILE *fp, kvtablestore_t **tblstore);

long long int KVT_insert_double_value_at_idx(kvtablestore_t **tblstore, long long int idx, const char* key, double value);
long long int KVT_insert_float_value_at_idx(kvtablestore_t **tblstore, long long int idx, const char* key, float value);
long long int KVT_insert_int_value_at_idx(kvtablestore_t **tblstore, long long int idx, const char* key, int value);
long long int KVT_insert_uint_value_at_idx(kvtablestore_t **tblstore, long long int idx, const char* key, unsigned int value);
long long int KVT_insert_llint_value_at_idx(kvtablestore_t **tblstore, long long int idx, const char* key, long long int value);
long long int KVT_insert_ullint_value_at_idx(kvtablestore_t **tblstore, long long int idx, const char* key, unsigned long long int value);

int KVT_get_double_value_at_idx(kvtablestore_t **tblstore, long long unsigned int idx, const char* key, double *retValue);
int KVT_get_float_value_at_idx(kvtablestore_t **tblstore, long long unsigned int idx, const char* key, float *retValue);
int KVT_get_int_value_at_idx(kvtablestore_t **tblstore, long long unsigned int idx, const char* key, int *retValue);
int KVT_get_uint_value_at_idx(kvtablestore_t **tblstore, long long unsigned int idx, const char* key, unsigned int *retValue);
int KVT_get_llint_value_at_idx(kvtablestore_t **tblstore, long long unsigned int idx, const char* key, long long int *retValue);
int KVT_get_ullint_value_at_idx(kvtablestore_t **tblstore, long long unsigned int idx, const char* key, unsigned long long int *retValue);

double KVT_get_double_value_at_idx_2(kvtablestore_t **tblstore, long long unsigned int idx, const char* key);
float KVT_get_float_value_at_idx_2(kvtablestore_t **tblstore, long long unsigned int idx, const char* key);
int KVT_get_int_value_at_idx_2(kvtablestore_t **tblstore, long long unsigned int idx, const char* key);
unsigned int KVT_get_uint_value_at_idx_2(kvtablestore_t **tblstore, long long unsigned int idx, const char* key);
long long int KVT_get_llint_value_at_idx_2(kvtablestore_t **tblstore, long long unsigned int idx, const char* key);
long long unsigned int KVT_get_ullint_value_at_idx_2(kvtablestore_t **tblstore, long long unsigned int idx, const char* key);

void KVT_add_doubles_with_prefix(kvtablestore_t **tblstore, long long int idx, const char* keyPrefix, double *data, int len, int countStart, int countEnd);
void KVT_add_llints_with_prefix(kvtablestore_t **tblstore, long long int idx, const char* keyPrefix, long long int *data, int len, int countStart, int countEnd);

//// for KV store
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //
/**
* @brief initialize basic stuff a store needs
* 
* @param store p_store:pointer to a store* variable
*/
void KVS_init_store(kvstore_t **store);

/**
* @brief Add an entry to the store using a void* to a variable. The entry is copied internally and
* cast to the right type.
* 
* @param store p_store: store to add the value to
* @param key p_key: key under which the value is stored
* @param dtype p_dtype: datatype of entry
* @param value p_value: void* to the value
* @param overwrite p_overwrite: overwrite if already in the store (1 = yes, 0 = no)
* @return long long int: position at which the new element has been added, -1 if not added
*/
long long int KVS_add_kv_to_store(kvstore_t *store, const char* key, int dtype, void* value, int overwrite);

/**
* @brief print store to file
* 
* @param fp p_fp:file pointer (can also be stderr and stdout)
* @param store p_store:pointer to store to print
*/
void KVS_print_kvstore(FILE *fp, kvstore_t *store);

/**
* @brief removes entry from store with key
* 
* @param store p_store:the store to remove the entry from
* @param key p_key:key of entry to remove
* @return int 1 if removal successful, 0 if not (e.g. entry not existent)
*/
int KVS_is_in_store(kvstore_t *store, const char* key);

/**
* @brief completely remove an entry from the store
* 
* @param store p_store: pointer to an allocated store
* @param key p_key: key of the entry to remove
* @return int: 1 if removal successful, 0 if not (e.g. entry not included)
*/
int KVS_remove_entry_from_store_key(kvstore_t *store, const char* key);

/**
* @brief totally de-allocate  
* 
* @param store p_store: pointer to kvstore_t pointer, the store to de-allocate
*/
void KVS_deallocate_kvstore(kvstore_t **store);


int KVS_get_double_entry_from_store(kvstore_t *store, const char* key, double *retValue);
int KVS_get_float_entry_from_store(kvstore_t *store, const char* key, float *retValue);
int KVS_get_int_entry_from_store(kvstore_t *store, const char* key, int *retValue);
int KVS_get_uint_entry_from_store(kvstore_t *store, const char* key, unsigned int *retValue);
int KVS_get_llint_entry_from_store(kvstore_t *store, const char* key, long long int *retValue);
int KVS_get_ullint_entry_from_store(kvstore_t *store, const char* key, unsigned long long int *retValue);

#endif
