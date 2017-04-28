#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sha256.h"

void print_hash(unsigned char hash[])
{
    int idx;

    for (idx=0; idx < 32; idx++)
        printf("%02x",hash[idx]);

    printf("\n");
}



int main()
{
    clock_t begin = clock();

    int startingInt = 0;
    int tartgetInt = 100000;

    unsigned char targetHash[32] = "1a6562590ef19d1045d06c4055742d38288e9e6dcd71ccde5cee80f1d5a774eb";
    unsigned char stringToHash[32];
    unsigned char hash[32];

    while (startingInt < tartgetInt) {
        sprintf(stringToHash, "%d", startingInt);
        printf("%s\n", stringToHash);
        SHA256_CTX ctx;
        sha256_init(&ctx);
        sha256_update(&ctx,stringToHash,strlen(stringToHash));
        sha256_final(&ctx,hash);

        if (hash == targetHash) {
            printf("A match for your target hash hash been found!\n");
            printf("Raw value: %s\n", stringToHash);
            printf("Hashed value: %s\n", hash);
        } else {
            print_hash(hash);
        }

        startingInt++;
    }

    // for (startingInt; tartgetInt; startingInt++)

    // getchar();
    clock_t end = clock();
    double time_spent = (double)(end - begin);
    printf("Hashing time: %d\n", time_spent);

    return 0;
}
