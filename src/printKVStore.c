#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include"../include/libkvstore.h"

void KVS_print_kvstore(FILE *fp, kvstore_t *store){
    if(store != NULL && store->len > 0){
        long long unsigned int i;
        for(i=0; i<store->len; i++){
            switch(store->entries[i]->kvdtype){
                case KV_DOUBLE_T:
                    fprintf(fp, "%s: %25.16e\n", store->entries[i]->name, *((double*) store->entries[i]->data));
                    break;
                case KV_FLOAT_T:
                    fprintf(fp, "%s: %16.7e\n", store->entries[i]->name, *((float*) store->entries[i]->data));
                    break;
                case KV_INT_T:
                    fprintf(fp, "%s: %i\n", store->entries[i]->name, *((int*) store->entries[i]->data));
                    break;
                case KV_UINT_T:
                    fprintf(fp, "%s: %i\n", store->entries[i]->name, *((unsigned int*) store->entries[i]->data));
                    break;
                case KV_LONG_LONG_INT_T:
                    fprintf(fp, "%s: %lld\n", store->entries[i]->name, *((long long int*) store->entries[i]->data));
                    break;
                case KV_LONG_LONG_UINT_T:
                    fprintf(fp, "%s: %llu\n", store->entries[i]->name, *((long long unsigned int*) store->entries[i]->data));
                    break;
                case KV_CHARS_T:
                    fprintf(fp, "%s: %s\n", store->entries[i]->name, (char *) store->entries[i]->data);
                    break;
            }
        }
    }
}
