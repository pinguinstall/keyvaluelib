CFLAGS=-O3 -march=native -g -pipe -Warray-bounds -Wall -pedantic -Wextra
FPIC=-fpic
SHARED=-shared

all:
	$(CC) $(CFLAGS) $(FPIC) -c src/tablestore.c
	$(CC) $(CFLAGS) $(FPIC) -c src/kvstore.c
	$(CC) $(CFLAGS) $(FPIC) -c src/storetolist.c
	$(CC) $(CFLAGS) $(FPIC) -c src/printKVStore.c
	$(CC) $(CFLAGS) $(FPIC) -c src/printTable.c
	$(CC) $(CFLAGS) $(FPIC) -c src/helpers.c
	$(CC) $(CFLAGS) $(FPIC) $(SHARED) -o libkvstore.so *.o $(LDFLAGS)
	
clean:
	rm -rf *.o *.exe *.log core
