#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/libkvstore.h"
#include "helpers.h"

#define _POSIX_C_SOURCE 200809L

void KVS_init_store(kvstore_t **store){
    *store = calloc(1, sizeof(kvstore_t));
    if((*store) == NULL){
        perror("KV_init_store: Could not allocate memory for store object");
        exit(EXIT_FAILURE);
    }
    (*store)->len = 0;
}


void KVS_deallocate_kvstore(kvstore_t **store){
    if(*store != NULL && (*store)->len > 0){
        long long unsigned int i;
        for(i=0; i<(*store)->len; i++){
            if((*store)->entries[i]->data != NULL){
                free((*store)->entries[i]->data);
                (*store)->entries[i]->data = NULL;
            }
            if((*store)->entries[i]->name != NULL){
                free((*store)->entries[i]->name);
                (*store)->entries[i]->name = NULL;
            }
            if((*store)->entries[i] != NULL){
                free((*store)->entries[i]);
                (*store)->entries[i] = NULL;
            }
        }
        free((*store)->entries);
        (*store)->entries = NULL;
    }
    free((*store));
    (*store) = NULL;
}


long long int KV_get_pos_in_store(kvstore_t *kvst, const char* key){
    if(kvst != NULL && kvst->len > 0 && kvst->entries != NULL){
        long long unsigned int i;
        for(i=0; i<kvst->len; i++){
            if(strcmp(kvst->entries[i]->name, key) == 0){
                return i;
            }
        }
    }
    
    return -1;
}


int KVS_is_in_store(kvstore_t *kvst, const char* key){
    if(KV_get_pos_in_store(kvst, key) >= 0){
        return 1;
    } else {
        return 0;
    }
}


void KV_overwrite_store_entry(kvstore_t *store, long long unsigned int pos, kventry_t *entry){
    if(store != NULL && store->entries[pos] != NULL && store->entries[pos]->data != NULL && store->entries[pos]->name != NULL){
        free(store->entries[pos]->data);
        free(store->entries[pos]->name);
        free(store->entries[pos]);
        store->entries[pos] = entry;
    }
}


long long int KV_add_kventry_to_store(kvstore_t *store, kventry_t *entry, int overwrite){
    long long int pos = KV_get_pos_in_store(store, entry->name);
    
    // entry is in store and shall be overwritten
    if(pos >= 0 && overwrite){
        KV_overwrite_store_entry(store, pos, entry);
        return pos;
    }
    
    // entry is not in store
    if(pos < 0){
        store->len = store->len + 1;
        // allocate more memory for ptr to entry
        store->entries = realloc(store->entries, (store->len) * sizeof(kventry_t*));
        if(store->entries == NULL){
            perror("KV_add_kventry_to_store: Could not allocate memory for store!");
            exit(EXIT_FAILURE);
        }
        store->entries[store->len - 1] = entry;
        return store->len - 1;
    }
    
    return -1;
}


long long int KVS_add_kv_to_store(kvstore_t *store, const char* key, int dtype, void* value, int overwrite){
    kventry_t *newe = calloc(1, sizeof(kventry_t));
    if(newe == NULL){
        perror("KV_add_kv_to_store: Could not allocate memory for entry object");
        exit(EXIT_FAILURE);
    }

    // copy in new data
    newe->data = calloc(1, KV_get_size_of_dtype(dtype));
    memcpy(newe->data, value, KV_get_size_of_dtype(dtype));
    
    newe->kvdtype = dtype;
    newe->name = strdup(key);
    
    long long int pos = KV_add_kventry_to_store(store, newe, overwrite);
    
    if(pos < 0) {
        free(newe->data);
        newe->data = NULL;
        free(newe->name);
        newe->name = NULL;
        free(newe);
        newe = NULL;
    }
    
    return pos;
}


int KV_remove_entry_from_store_idx(kvstore_t *store, long long unsigned int idx){
    if(store != NULL && store->len > 0 && store->entries != NULL){
        kventry_t *last = store->entries[store->len - 1];
        if(store->entries[idx] != NULL){
            if(store->entries[idx]->data != NULL){
                free(store->entries[idx]->data);
            }
            if(store->entries[idx]->name != NULL){
                free(store->entries[idx]->name);
            }
            free(store->entries[idx]);
        }
        store->entries[idx] = last;
        store->entries[store->len - 1] = NULL;
        store->len = store->len - 1;
        return 1;
    }
    return 0;
}


int KVS_remove_entry_from_store_key(kvstore_t *store, const char* key){
    long long unsigned int pos = KV_get_pos_in_store(store, key);
    if(pos >= 0){
        return KV_remove_entry_from_store_idx(store, pos);
    }
    
    return 0;
}


int KVS_get_double_entry_from_store(kvstore_t *store, const char* key, double *retValue){
    if(store != NULL){
        long long unsigned int pos = KV_get_pos_in_store(store, key);
        if(pos >= 0 && store->entries[pos]->kvdtype == KV_DOUBLE_T){
            *retValue = *((double*) store->entries[pos]->data);
            return 1;
        }
    }
    return 0;
}

int KVS_get_float_entry_from_store(kvstore_t *store, const char* key, float *retValue){
    if(store != NULL){
        long long unsigned int pos = KV_get_pos_in_store(store, key);
        if(pos >= 0 && store->entries[pos]->kvdtype == KV_FLOAT_T){
            *retValue = *((float*) store->entries[pos]->data);
            return 1;
        }
    }
    return 0;
}


int KVS_get_int_entry_from_store(kvstore_t *store, const char* key, int *retValue){
    if(store != NULL){
        long long unsigned int pos = KV_get_pos_in_store(store, key);
        if(pos >= 0 && store->entries[pos]->kvdtype == KV_INT_T){
            *retValue = *((int*) store->entries[pos]->data);
            return 1;
        }
    }
    return 0;
}



int KVS_get_uint_entry_from_store(kvstore_t *store, const char* key, unsigned int *retValue){
    if(store != NULL){
        long long unsigned int pos = KV_get_pos_in_store(store, key);
        if(pos >= 0 && store->entries[pos]->kvdtype == KV_UINT_T){
            *retValue = *((unsigned int*) store->entries[pos]->data);
            return 1;
        }
    }
    return 0;
}

int KVS_get_llint_entry_from_store(kvstore_t *store, const char* key, long long int *retValue){
    if(store != NULL){
        long long unsigned int pos = KV_get_pos_in_store(store, key);
        if(pos >= 0 && store->entries[pos]->kvdtype == KV_LONG_LONG_INT_T){
            *retValue = *((long long int*) store->entries[pos]->data);
            return 1;
        }
    }
    return 0;
}

int KVS_get_ullint_entry_from_store(kvstore_t *store, const char* key, unsigned long long int *retValue){
    if(store != NULL){
        long long unsigned int pos = KV_get_pos_in_store(store, key);
        if(pos >= 0 && store->entries[pos]->kvdtype == KV_LONG_LONG_UINT_T){
            *retValue = *((long long unsigned int*) store->entries[pos]->data);
            return 1;
        }
    }
    return 0;
}
