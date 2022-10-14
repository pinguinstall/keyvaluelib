# keyvaluelib
simple library to store, query and dump table data in C

The library works by giving a (row) index number, and a key, it will automatically create rows and columns and stores the data in the corresponding cell.
Make sure you index is something sensible (small numbers), because data is completely allocated up to the highest index.

## usage
```c
#include <libkvstore.h>
kvtablestore_t *mystore;
KVT_init_table_store(&mystore);

long index = 0;

KVT_insert_double_value_at_idx(&mystore, index, "MYVALUE1", 1.234);
KVT_insert_double_value_at_idx(&mystore, index, "MYVALUE2", 2.987);

// ...

index++;
KVT_insert_double_value_at_idx(&mystore, index, "MYVALUE1", 10.234);
KVT_insert_double_value_at_idx(&mystore, index, "MYVALUE2", 20.987);

// ...
FILE *fp;
// fopen() ...
KVT_print_table(fp, &mystore);

// to close
KVT_deallocate_table_store(&mystore);

// long long int KVT_insert_float_value_at_idx(kvtablestore_t **tblstore, long long int idx, const char* key, float value);
// long long int KVT_insert_int_value_at_idx(kvtablestore_t **tblstore, long long int idx, const char* key, int value);
// long long int KVT_insert_uint_value_at_idx(kvtablestore_t **tblstore, long long int idx, const char* key, unsigned int value);
// long long int KVT_insert_llint_value_at_idx(kvtablestore_t **tblstore, long long int idx, const char* key, long long int value);
// long long int KVT_insert_ullint_value_at_idx(kvtablestore_t **tblstore, long long int idx, const char* key, unsigned long long int value);

// if you have an array and want to generate "MYVALUE_<runningNumber>" entries
// void KVT_add_doubles_with_prefix(kvtablestore_t **tblstore, long long int idx, const char* keyPrefix, double *data, int len, int countStart, int countEnd);
//void KVT_add_llints_with_prefix(kvtablestore_t **tblstore, long long int idx, const char* keyPrefix, long long int *data, int len, int countStart, int countEnd);

// you can also get the values from the store
// int KVT_get_double_value_at_idx(kvtablestore_t **tblstore, long long unsigned int idx, const char* key, double *retValue);
// int KVT_get_float_value_at_idx(kvtablestore_t **tblstore, long long unsigned int idx, const char* key, float *retValue);
// int KVT_get_int_value_at_idx(kvtablestore_t **tblstore, long long unsigned int idx, const char* key, int *retValue);
// int KVT_get_uint_value_at_idx(kvtablestore_t **tblstore, long long unsigned int idx, const char* key, unsigned int *retValue);
// int KVT_get_llint_value_at_idx(kvtablestore_t **tblstore, long long unsigned int idx, const char* key, long long int *retValue);
// int KVT_get_ullint_value_at_idx(kvtablestore_t **tblstore, long long unsigned int idx, const char* key, unsigned long long int *retValue);

// double KVT_get_double_value_at_idx_2(kvtablestore_t **tblstore, long long unsigned int idx, const char* key);
// float KVT_get_float_value_at_idx_2(kvtablestore_t **tblstore, long long unsigned int idx, const char* key);
// int KVT_get_int_value_at_idx_2(kvtablestore_t **tblstore, long long unsigned int idx, const char* key);
// unsigned int KVT_get_uint_value_at_idx_2(kvtablestore_t **tblstore, long long unsigned int idx, const char* key);
// long long int KVT_get_llint_value_at_idx_2(kvtablestore_t **tblstore, long long unsigned int idx, const char* key);
// long long unsigned int KVT_get_ullint_value_at_idx_2(kvtablestore_t **tblstore, long long unsigned int idx, const char* key);
```

There are also some other, incomplete functions ... just look in the code.
