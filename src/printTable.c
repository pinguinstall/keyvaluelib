#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include"../include/libkvstore.h"

void KVT_print_header(FILE *fp, kvtablestore_t **tblstore){
    if((*tblstore) != NULL && (*tblstore)->numcols > 0 && (*tblstore)->len > 0){
        long long unsigned int k;
        for(k=0; k<(*tblstore)->numcols; k++){
            if((*tblstore)->numcols > k + 1){
                fprintf(fp, "%s,", (*tblstore)->cols[k].name);
            } else {
                fprintf(fp, "%s\n", (*tblstore)->cols[k].name);
            }
        }
    }
}


void KVT_print_table(FILE *fp, kvtablestore_t **tblstore){
    if((*tblstore) != NULL && (*tblstore)->numcols > 0 && (*tblstore)->len > 0){
        long long unsigned int i, k;
        
        KVT_print_header(fp, tblstore);
        
        for(i=0; i<(*tblstore)->len; i++){
            for(k=0; k<(*tblstore)->numcols; k++){
                if((*tblstore)->numcols > k + 1){
                    switch((*tblstore)->cols[k].dtype) {
                        case KV_DOUBLE_T:
                            fprintf(fp, "%25.16e, ", ((double *) (*tblstore)->cols[k].data)[i]);
                            break;
                        case KV_FLOAT_T:
                            fprintf(fp, "%16.7e, ", ((float *) (*tblstore)->cols[k].data)[i]);
                            break;
                        case KV_INT_T:
                            fprintf(fp, "%i, ", ((int *) (*tblstore)->cols[k].data)[i]);
                            break;
                        case KV_UINT_T:
                            fprintf(fp, "%i, ", ((unsigned int *) (*tblstore)->cols[k].data)[i]);
                            break;
                        case KV_LONG_LONG_INT_T:
                            fprintf(fp, "%lld, ", ((long long int *) (*tblstore)->cols[k].data)[i]);
                            break;
                        case KV_LONG_LONG_UINT_T:
                            fprintf(fp, "%llu, ", ((unsigned long long int *) (*tblstore)->cols[k].data)[i]);
                            break;
                    }
                } else {
                    switch((*tblstore)->cols[k].dtype) {
                        case KV_DOUBLE_T:
                            fprintf(fp, "%25.16e\n", ((double *) (*tblstore)->cols[k].data)[i]);
                            break;
                        case KV_FLOAT_T:
                            fprintf(fp, "%16.7e\n", ((float *) (*tblstore)->cols[k].data)[i]);
                            break;
                        case KV_INT_T:
                            fprintf(fp, "%i\n", ((int *) (*tblstore)->cols[k].data)[i]);
                            break;
                        case KV_UINT_T:
                            fprintf(fp, "%i\n", ((unsigned int *) (*tblstore)->cols[k].data)[i]);
                            break;
                        case KV_LONG_LONG_INT_T:
                            fprintf(fp, "%lld\n", ((long long int *) (*tblstore)->cols[k].data)[i]);
                            break;
                        case KV_LONG_LONG_UINT_T:
                            fprintf(fp, "%llu\n", ((unsigned long long int *) (*tblstore)->cols[k].data)[i]);
                            break;
                    }
                }
            }
        }
    }
}
