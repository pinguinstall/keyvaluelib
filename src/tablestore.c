#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../include/libkvstore.h"
#include "helpers.h"


void KVT_init_table_store(kvtablestore_t **tblstore){
    *tblstore = calloc(1, sizeof(kvtablestore_t));
    (*tblstore)->len = 0;
    (*tblstore)->numcols = 0;
    (*tblstore)->cols = NULL;
}


void KVT_deallocate_table_store(kvtablestore_t **tblstore){
    long long unsigned int i;
    if((*tblstore)->numcols > 0 && (*tblstore)->cols != NULL){
        for(i=0; i < (*tblstore)->numcols; i++){
            if((*tblstore)->cols[i].data != NULL){
                free((*tblstore)->cols[i].data);
                (*tblstore)->cols[i].data = NULL;
            }
            if((*tblstore)->cols[i].name != NULL){
                free((*tblstore)->cols[i].name);
                (*tblstore)->cols[i].name = NULL;
            }
        }
        free((*tblstore)->cols);
        (*tblstore)->cols = NULL;
    }
    free(*tblstore);
    *tblstore = NULL;
}


long long int KV_get_colidx_in_table(kvtablestore_t **tblstore, const char* key){
    if((*tblstore)->numcols > 0 && (*tblstore)->cols != NULL){
        long long int unsigned i;
        for(i=0; i<(*tblstore)->numcols; i++){
            if(strcmp((*tblstore)->cols[i].name, key) == 0){
                return (long long int) i;
            }
        }
    }
    
    return -1;
}


int KV_is_col_in_table(kvtablestore_t **tblstore, const char* key){
    if(KV_get_colidx_in_table(tblstore, key) >= 0){
        return 1;
    } else {
        return 0;
    }
}


int KV_is_idx_in_table(kvtablestore_t **tblstore, long long unsigned int idx){
    if((*tblstore) != NULL && (*tblstore)->cols != NULL && (*tblstore)->len > idx){
        return 1;
    }
    
    return 0;
}


long long unsigned int KV_add_empty_row(kvtablestore_t **tblstore){
    if((*tblstore) != NULL && (*tblstore)->cols != NULL && (*tblstore)->numcols > 0 && (*tblstore)->len >= 0){
        long long unsigned int i;
        for(i=0; i<(*tblstore)->numcols; i++){
            
            (*tblstore)->cols[i].data = realloc((*tblstore)->cols[i].data, ((*tblstore)->len + 1) * KV_get_size_of_dtype((*tblstore)->cols[i].dtype));
            if((*tblstore)->cols[i].data == NULL){
                        perror("KV_add_empty_row: Could not allocate memory for more table rows!");
                        exit(EXIT_FAILURE);
            }
            
            KV_init_tblcell(&((*tblstore)->cols[i]), (*tblstore)->len);
        }
        
        (*tblstore)->len = (*tblstore)->len + 1;
    }
    
    
    
    return (*tblstore)->len;
}


long long unsigned int KV_add_empty_col(kvtablestore_t **tblstore, const char* name, int dtype){
    if((*tblstore) != NULL){
        (*tblstore)->cols = realloc((*tblstore)->cols, ((*tblstore)->numcols + 1) * sizeof(kvcolumn_t));
        if((*tblstore)->cols == NULL){
            perror("KV_add_empty_col: Could not allocate memory for more table cols!");
                        exit(EXIT_FAILURE);
        }
        
        (*tblstore)->cols[(*tblstore)->numcols].dtype = dtype;
        (*tblstore)->cols[(*tblstore)->numcols].name = strdup(name);
        (*tblstore)->cols[(*tblstore)->numcols].data = NULL;
        
        if(!((*tblstore)->len <= 0)){
            // allocate memory of the needed size
            (*tblstore)->cols[(*tblstore)->numcols].data = calloc((*tblstore)->len, KV_get_size_of_dtype(dtype));
                
            if((*tblstore)->cols[(*tblstore)->numcols].data == NULL){
                            perror("KV_add_empty_col: Could not allocate memory for more table cols!");
                            exit(EXIT_FAILURE);
            }
        }
        
        (*tblstore)->numcols = (*tblstore)->numcols + 1;
        
    }
    return 0;
}


long long int KV_fill_with_rows_until_len(kvtablestore_t **tblstore, long long unsigned int endLen){
    long long unsigned int i = 0;
    if((*tblstore) != NULL){
        while((*tblstore)->len < endLen){
            KV_add_empty_row(tblstore);
            i++;
        }
    }
    return (long long int) i;
}



int KVT_insert_into_store_via_idxKey(kvtablestore_t **tblstore, const char* key, long long int idx, int dtype, void* value){
    if((*tblstore) != NULL){
            if(!KV_is_col_in_table(tblstore, key)){
                KV_add_empty_col(tblstore, key, dtype);
            }
            if(!KV_is_idx_in_table(tblstore, idx)){
                KV_fill_with_rows_until_len(tblstore, idx + 1);
            }
            
            if((*tblstore)->cols[KV_get_colidx_in_table(tblstore, key)].dtype == dtype){
                size_t needed = KV_get_size_of_dtype(dtype);
                memcpy((char*) (*tblstore)->cols[KV_get_colidx_in_table(tblstore, key)].data + needed * idx, value, needed);
                return 1;
            } else {
                return 0;
            }

    }
    return 0;
}


long long int KVT_insert_double_value_at_idx(kvtablestore_t **tblstore, long long int idx, const char* key, double value){
    double *v = calloc(1, sizeof(double));
    *v = value;
    long long int ret = KVT_insert_into_store_via_idxKey(tblstore, key, idx, KV_DOUBLE_T, v);
    free(v);
    v = NULL;
    return ret;
}


long long int KVT_insert_float_value_at_idx(kvtablestore_t **tblstore, long long int idx, const char* key, float value){
    float *v = calloc(1, sizeof(float));
    *v = value;
    long long int ret = KVT_insert_into_store_via_idxKey(tblstore, key, idx, KV_FLOAT_T, v);
    free(v);
    v = NULL;
    return ret;
}


long long int KVT_insert_int_value_at_idx(kvtablestore_t **tblstore, long long int idx, const char* key, int value){
    int *v = calloc(1, sizeof(int));
    *v = value;
    long long int ret = KVT_insert_into_store_via_idxKey(tblstore, key, idx, KV_INT_T, v);
    free(v);
    v = NULL;
    return ret;
}


long long int KVT_insert_uint_value_at_idx(kvtablestore_t **tblstore, long long int idx, const char* key, unsigned int value){
    unsigned int *v = calloc(1, sizeof(unsigned int));
    *v = value;
    long long int ret = KVT_insert_into_store_via_idxKey(tblstore, key, idx, KV_UINT_T, v);
    free(v);
    v = NULL;
    return ret;
}


long long int KVT_insert_llint_value_at_idx(kvtablestore_t **tblstore, long long int idx, const char* key, long long int value){
    long long int *v = calloc(1, sizeof(long long int));
    *v = value;
    long long int ret = KVT_insert_into_store_via_idxKey(tblstore, key, idx, KV_LONG_LONG_INT_T, v);
    free(v);
    v = NULL;
    return ret;
}


long long int KVT_insert_ullint_value_at_idx(kvtablestore_t **tblstore, long long int idx, const char* key, unsigned long long int value){
    unsigned long long int *v = calloc(1, sizeof(unsigned long long int));
    *v = value;
    long long int ret = KVT_insert_into_store_via_idxKey(tblstore, key, idx, KV_LONG_LONG_UINT_T, v);
    free(v);
    v = NULL;
    return ret;
}


int KVT_get_double_value_at_idx(kvtablestore_t **tblstore, long long unsigned int idx, const char* key, double *retValue){
    if((*tblstore) != NULL){
        long long int colidx = KV_get_colidx_in_table(tblstore, key);
        if((*tblstore)->len > idx && colidx >= 0 && (*tblstore)->cols[colidx].dtype == KV_DOUBLE_T){
            *retValue = ((double *) (*tblstore)->cols[colidx].data)[idx];
            return 1;
        }
    }
    return 0;
}


int KVT_get_float_value_at_idx(kvtablestore_t **tblstore, long long unsigned int idx, const char* key, float *retValue){
    if((*tblstore) != NULL){
        long long int colidx = KV_get_colidx_in_table(tblstore, key);
        if((*tblstore)->len > idx && colidx >= 0 && (*tblstore)->cols[colidx].dtype == KV_FLOAT_T){
            *retValue = ((float *) (*tblstore)->cols[colidx].data)[idx];
            return 1;
        }
    }
    
    return 0;
}


int KVT_get_int_value_at_idx(kvtablestore_t **tblstore, long long unsigned int idx, const char* key, int *retValue){
    if((*tblstore) != NULL){
        long long int colidx = KV_get_colidx_in_table(tblstore, key);
        if((*tblstore)->len > idx && colidx >= 0 && (*tblstore)->cols[colidx].dtype == KV_INT_T){
            *retValue = ((int *) (*tblstore)->cols[colidx].data)[idx];
            return 1;
        }
    }
    
    return 0;
}

int KVT_get_uint_value_at_idx(kvtablestore_t **tblstore, long long unsigned int idx, const char* key, unsigned int *retValue){
    if((*tblstore) != NULL){
        long long int colidx = KV_get_colidx_in_table(tblstore, key);
        if((*tblstore)->len > idx && colidx >= 0 && (*tblstore)->cols[colidx].dtype == KV_UINT_T){
            *retValue = ((unsigned int *) (*tblstore)->cols[colidx].data)[idx];
            return 1;
        }
    }
    
    return 0;
}


int KVT_get_llint_value_at_idx(kvtablestore_t **tblstore, long long unsigned int idx, const char* key, long long int *retValue){
    if((*tblstore) != NULL){
        long long int colidx = KV_get_colidx_in_table(tblstore, key);
        if((*tblstore)->len > idx && colidx >= 0 && (*tblstore)->cols[colidx].dtype == KV_LONG_LONG_INT_T){
            *retValue = ((long long int *) (*tblstore)->cols[colidx].data)[idx];
            return 1;
        }
    }
    
    return 0;
}


int KVT_get_ullint_value_at_idx(kvtablestore_t **tblstore, long long unsigned int idx, const char* key, unsigned long long int *retValue){
    if((*tblstore) != NULL){
        long long int colidx = KV_get_colidx_in_table(tblstore, key);
        if((*tblstore)->len > idx && colidx >= 0 && (*tblstore)->cols[colidx].dtype == KV_LONG_LONG_UINT_T){
            *retValue = ((unsigned long long int *) (*tblstore)->cols[colidx].data)[idx];
            return 1;
        }
    }
    
    return 0;
}


double KVT_get_double_value_at_idx_2(kvtablestore_t **tblstore, long long unsigned int idx, const char* key){
    double ret = 0;
    int success = KVT_get_double_value_at_idx(tblstore, idx, key, &ret);
    if(!success){
        fprintf(stderr, "could not get key \"%s\" as double\n", key);
    }
    return ret;
}


float KVT_get_float_value_at_idx_2(kvtablestore_t **tblstore, long long unsigned int idx, const char* key){
    float ret = 0;
    int success = KVT_get_float_value_at_idx(tblstore, idx, key, &ret);
    if(!success){
        fprintf(stderr, "could not get key \"%s\" as float\n", key);
    }
    return ret;
}


int KVT_get_int_value_at_idx_2(kvtablestore_t **tblstore, long long unsigned int idx, const char* key){
    int ret = 0;
    int success = KVT_get_int_value_at_idx(tblstore, idx, key, &ret);
    if(!success){
        fprintf(stderr, "could not get key \"%s\" as int\n", key);
    }
    return ret;
}


unsigned int KVT_get_uint_value_at_idx_2(kvtablestore_t **tblstore, long long unsigned int idx, const char* key){
    unsigned int ret = 0;
    int success = KVT_get_uint_value_at_idx(tblstore, idx, key, &ret);
    if(!success){
        fprintf(stderr, "could not get key \"%s\" as unsigned int\n", key);
    }
    return ret;
}


long long int KVT_get_llint_value_at_idx_2(kvtablestore_t **tblstore, long long unsigned int idx, const char* key){
    long long int ret = 0;
    int success = KVT_get_llint_value_at_idx(tblstore, idx, key, &ret);
    if(!success){
        fprintf(stderr, "could not get key \"%s\" as long long int\n", key);
    }
    return ret;
}


long long unsigned int KVT_get_ullint_value_at_idx_2(kvtablestore_t **tblstore, long long unsigned int idx, const char* key){
    long long unsigned int ret = 0;
    int success = KVT_get_ullint_value_at_idx(tblstore, idx, key, &ret);
    if(!success){
        fprintf(stderr, "could not get key \"%s\" as long long unsigned int\n", key);
    }
    return ret;
}
