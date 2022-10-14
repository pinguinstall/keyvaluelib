#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/libkvstore.h"

double KV_get_entry_value_as_double(kventry_t *entry){
    switch(entry->kvdtype){
        case KV_DOUBLE_T:
            return (double) *((double *) entry->data);
            break;
        case KV_FLOAT_T:
            return (double) *((float *) entry->data);
            break;
        case KV_INT_T:
            return (double) *((int *) entry->data);
            break;
        case KV_UINT_T:
            return (double) *((unsigned int *) entry->data);
            break;
        case KV_LONG_LONG_INT_T:
            return (double) *((long long int *) entry->data);
            break;
        case KV_LONG_LONG_UINT_T:
            return (double) *((long long unsigned int *) entry->data);
            break;
    }
    return 0.0;
}


float KV_get_entry_value_as_float(kventry_t *entry){
    switch(entry->kvdtype){
        case KV_DOUBLE_T:
            return (float) *((double *) entry->data);
            break;
        case KV_FLOAT_T:
            return *((float *) entry->data);
            break;
        case KV_INT_T:
            return (float) *((int *) entry->data);
            break;
        case KV_UINT_T:
            return (float) *((unsigned int *) entry->data);
            break;
        case KV_LONG_LONG_INT_T:
            return (float) *((long long int *) entry->data);
            break;
        case KV_LONG_LONG_UINT_T:
            return (float) *((long long unsigned int *) entry->data);
            break;
    }
    return 0.0;
}


int KV_get_entry_value_as_int(kventry_t *entry){
    switch(entry->kvdtype){
        case KV_DOUBLE_T:
            return (int) *((double *) entry->data);
            break;
        case KV_FLOAT_T:
            return (int) *((float *) entry->data);
            break;
        case KV_INT_T:
            return *((int *) entry->data);
            break;
        case KV_UINT_T:
            return (int) *((unsigned int *) entry->data);
            break;
        case KV_LONG_LONG_INT_T:
            return (int) *((long long int *) entry->data);
            break;
        case KV_LONG_LONG_UINT_T:
            return (int) *((long long unsigned int *) entry->data);
            break;
    }
    return 0;
}


long long int KV_get_entry_value_as_llint(kventry_t *entry){
    switch(entry->kvdtype){
        case KV_DOUBLE_T:
            return (long long int) *((double *) entry->data);
            break;
        case KV_FLOAT_T:
            return (long long int) *((float *) entry->data);
            break;
        case KV_INT_T:
            return (long long int) *((int *) entry->data);
            break;
        case KV_UINT_T:
            return (long long int) *((unsigned int *) entry->data);
            break;
        case KV_LONG_LONG_INT_T:
            return *((long long int *) entry->data);
            break;
        case KV_LONG_LONG_UINT_T:
            return (long long int) *((long long unsigned int *) entry->data);
            break;
    }
    return 0;
}


long long unsigned int KV_get_entry_value_as_ullint(kventry_t *entry){
    switch(entry->kvdtype){
        case KV_DOUBLE_T:
            return (long long unsigned int) *((double *) entry->data);
            break;
        case KV_FLOAT_T:
            return (long long unsigned int) *((float *) entry->data);
            break;
        case KV_INT_T:
            return (long long unsigned int) *((int *) entry->data);
            break;
        case KV_UINT_T:
            return (long long unsigned int) *((unsigned int *) entry->data);
            break;
        case KV_LONG_LONG_INT_T:
            return (long long unsigned int) *((long long int *) entry->data);
            break;
        case KV_LONG_LONG_UINT_T:
            return *((long long unsigned int *) entry->data);
            break;
    }
    return 0;
}


char * KV_get_entry_value_as_chars(kventry_t *entry){
    if(entry->kvdtype == KV_CHARS_T){
        return (char *) entry->data;
    }
    
    char *ret = NULL;
    size_t needed;
    
    switch(entry->kvdtype){
        case KV_DOUBLE_T:
            needed = snprintf(NULL, 0, "%25.16e", *((double *) entry->data));
            ret = calloc(needed+1, sizeof(char));
            sprintf(ret, "%25.16e", *((double *) entry->data));
            break;
        case KV_FLOAT_T:
            needed = snprintf(NULL, 0, "%16.7e", *((float *) entry->data));
            ret = calloc(needed+1, sizeof(char));
            sprintf(ret, "%16.7e", *((float *) entry->data));
            break;
        case KV_INT_T:
            needed = snprintf(NULL, 0, "%i", *((int *) entry->data));
            ret = calloc(needed+1, sizeof(char));
            sprintf(ret, "%i", *((int *) entry->data));
            break;
        case KV_UINT_T:
            needed = snprintf(NULL, 0, "%i", *((unsigned int *) entry->data));
            ret = calloc(needed+1, sizeof(char));
            sprintf(ret, "%i", *((unsigned int *) entry->data));
            break;
        case KV_LONG_LONG_INT_T:
            needed = snprintf(NULL, 0, "%lld", *((long long int *) entry->data));
            ret = calloc(needed+1, sizeof(char));
            sprintf(ret, "%lld", *((long long int *) entry->data));
            break;
        case KV_LONG_LONG_UINT_T:
            needed = snprintf(NULL, 0, "%llu", *((long long unsigned int *) entry->data));
            ret = calloc(needed+1, sizeof(char));
            sprintf(ret, "%llu", *((long long unsigned int *) entry->data));
            break;
    }
    
    return ret;
}


int KV_get_store_value_list_asdouble(kvstore_t *store, kvvalueset_double_t **valuesetdbl){
    if(store != NULL && store->len > 0){
        *valuesetdbl = calloc(1, sizeof(kvvalueset_double_t));
        (*valuesetdbl)->len = store->len;
        (*valuesetdbl)->values = calloc(store->len, sizeof(double));
        
        long long unsigned int i;
        for(i=0; i<store->len; i++){
            if(store->entries[i]->data != NULL){
                (*valuesetdbl)->values[i] = KV_get_entry_value_as_double(store->entries[i]);
            }
        }
        
        return 1;
    }
    
    return 0;
}


int KV_get_store_value_list_asllint(kvstore_t *store, kvvalueset_llint_t **valuesetlli){
    if(store != NULL && store->len > 0){
        *valuesetlli = calloc(1, sizeof(kvvalueset_llint_t));
        (*valuesetlli)->len = store->len;
        (*valuesetlli)->values = calloc(store->len, sizeof(long long int));
        
        long long unsigned int i;
        for(i=0; i<store->len; i++){
            if(store->entries[i]->data != NULL){
                (*valuesetlli)->values[i] = KV_get_entry_value_as_llint(store->entries[i]);
            }
        }
        
        return 1;
    }
    
    return 0;
}


void KV_get_key_list(kvstore_t *store, kvkeyset_t **keyset){
    if(store != NULL){
        *keyset = calloc(1, sizeof(kvkeyset_t));
        (*keyset)->len = store->len;
        (*keyset)->keys = calloc(store->len, sizeof(const char*));
        long long unsigned int i;
        for(i=0; i<store->len; i++){
            size_t needed = snprintf(NULL, 0, "%s", store->entries[i]->name);
            (*keyset)->keys[i] = calloc(needed+1, sizeof(char));
            sprintf((*keyset)->keys[i], "%s", store->entries[i]->name);
        }
    }
}


void KV_deallocate_key_list(kvkeyset_t **keyset){
    if(keyset != NULL && (*keyset) != NULL && (*keyset)->len > 0){
        long long unsigned int i;
        for(i=0; i<(*keyset)->len; i++){
            if((*keyset)->keys[i] != NULL){
                free((*keyset)->keys[i]);
            }
        }
        free(*keyset);
    }
}
