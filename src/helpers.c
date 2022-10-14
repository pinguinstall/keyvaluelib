#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/libkvstore.h"

size_t KV_get_size_of_dtype(int dtype){
    switch(dtype){
        case KV_DOUBLE_T:
            return sizeof(double);
            break;
        case KV_FLOAT_T:
            return sizeof(float);
            break;
        case KV_INT_T:
            return sizeof(int);
            break;
        case KV_UINT_T:
            return sizeof(unsigned int);
            break;
        case KV_LONG_LONG_INT_T:
            return sizeof(long long int);
            break;
        case KV_LONG_LONG_UINT_T:
            return sizeof(long long unsigned int);
            break;
    }
    
    return -1;
}


void KV_init_tblcell(kvcolumn_t *col, long long unsigned idx){
    switch(col->dtype){
        case KV_DOUBLE_T:
            ((double *) col->data)[idx] = (double) KV_INIT_VALUE;
            break;
        case KV_FLOAT_T:
            ((float *) col->data)[idx] = (float) KV_INIT_VALUE;
            break;
        case KV_INT_T:
            ((int *) col->data)[idx] = (int) KV_INIT_VALUE;
            break;
        case KV_UINT_T:
            ((unsigned int *) col->data)[idx] = (unsigned int) KV_INIT_VALUE;
            break;
        case KV_LONG_LONG_INT_T:
            ((long long int *) col->data)[idx] = (long long int) KV_INIT_VALUE;
            break;
        case KV_LONG_LONG_UINT_T:
            ((long long unsigned int *) col->data)[idx] = (long long unsigned int) KV_INIT_VALUE;
            break;
    }
}


void KVT_add_doubles_with_prefix(kvtablestore_t **tblstore, long long int idx, const char* keyPrefix, double *data, int len, int countStart, int countEnd){
    if((*tblstore) != NULL && len == (countEnd - countStart + 1)){
        int i = 0;
        int k = countStart;
        for(i=0; i<len; i++){
            size_t needed = snprintf(NULL, 0, "%s%i", keyPrefix, k);
            char *key = calloc(needed+1, sizeof(char));
            sprintf(key, "%s%i", keyPrefix, k);
            
            KVT_insert_double_value_at_idx(tblstore, idx, key, data[i]);
            
            if(key != NULL) free(key);
            
            k++;
        }
    }
}


void KVT_add_llints_with_prefix(kvtablestore_t **tblstore, long long int idx, const char* keyPrefix, long long int *data, int len, int countStart, int countEnd){
    if((*tblstore) != NULL && len == (countEnd - countStart + 1)){
        int i = 0;
        int k = countStart;
        for(i=0; i<len; i++){
            size_t needed = snprintf(NULL, 0, "%s%i", keyPrefix, k);
            char *key = calloc(needed+1, sizeof(char));
            sprintf(key, "%s%i", keyPrefix, k);
            
            KVT_insert_llint_value_at_idx(tblstore, idx, key, data[i]);
            if(key != NULL) free(key);
            k++;
        }
    }
}
