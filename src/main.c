/*!
 * C-Hash-Matcher <https://github.com/ryansmith98/C-Hash-Matcher>
 *
 * Copyright (c) 2017, Ryan Smith.
 * Licensed under the MIT License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <unistd.h>

#include "sha256.h"

int main(int argc, char *argv[])
{
    clock_t start = clock();
    setlocale(LC_NUMERIC, "");

    // char targetHash[65] = "e401f2bd399f3456e5348217a7908ca545ea6d179f60f297a1b0133e87d2ff85"; //5,000
    // char targetHash[65] = "8990d5f8063b0f92bf863fa819cee92e93dd1630cb368e4f6959536a7165f2a9"; //94,010,302
    char targetHash[65] = "c2eb7898bb6771503ffee5d0c722e5b561fe480edbc30141880a1cdf1e5b1cf6"; //REAL TARGET

    // MAX:                                         18,446,744,073,709,551,615
    unsigned long long startingInt = 0;
    unsigned long long tartgetInt = 1000000;

    unsigned long long counterInt = startingInt;
    unsigned char hexOfInt[32];
    unsigned char hash[32];

    int printCounter = 0;
    int clearCounter = 0;

    FILE *f = fopen("hashes.txt", "w");

    printf("\nStarting at:  %'llu\n", startingInt);
    printf("Finishing at: %'llu\n", tartgetInt);
    printf("------------------------------------------------------------------------------\n");
    printf("Target hash:  %s\n\n", targetHash);
    printf("Hashing...\n");

    while (counterInt < tartgetInt) {

        // Converts counterInt to hex & hashes
        sprintf(hexOfInt, "%x", counterInt);
        SHA256_CTX ctx;
        sha256_init(&ctx);
        sha256_update(&ctx,hexOfInt,strlen(hexOfInt));
        sha256_final(&ctx,hash);

        char string[32];
        char* hashValue[32];
        int i;
        for (i=0; i < 32; i++) {
            sprintf(string, "%02x", hash[i]);
            strcat(hashValue, string);
        }

        // Checks if the resulting hash is equal to the target hash
        if (strcmp(hashValue, targetHash) == 0) {
            system("clear");
            printf("----------------------------------------------------------------------------\n");
            printf("A match for your target hash hash been found!\n\n");
            printf("Raw value:  %s\n", hexOfInt);
            printf("Int value:  %'llu\n", counterInt);
            printf("Hash value: %s\n", hashValue);
            printf("----------------------------------------------------------------------------\n");
            break;
        } else {
            if (argc > 1) {
                if (strcmp(argv[1], "log-all") == 0){
                    printf("\n%'llu\n", counterInt);
                    printf("%s\n", hexOfInt);
                    printf("%s\n", hashValue);
                } else if (strcmp(argv[1], "log-count") == 0) {
                    // printf("%'llu\n", counterInt);
                    if (printCounter > 1000000){
                        if (clearCounter > 1000000){
                            system("clear");
                            // clearCounter = 0;
                        }
                        printf("%'llu\n", counterInt);
                        printCounter = 0;
                    }
                } else if (strcmp(argv[1], "log-hex") == 0) {
                    printf("%s\n", hexOfInt);
                } else if (strcmp(argv[1], "log-hash") == 0) {
                    printf("%s\n", hashValue);
                } else if (strcmp(argv[1], "log-hex-part") == 0) {
                    if (printCounter > 1000000){
                        if (clearCounter > 1000000){
                            system("clear");
                            // clearCounter = 0;
                        }
                        printf("%s\n", hexOfInt);
                        printCounter = 0;
                    }
                }
            }
        }

        // ----------------------------------
        // Writes hashing results to txt file
        // ----------------------------------
        fprintf(f, "%s\n", hexOfInt);
        // fprintf(f, "%'llu\n", counterInt);
        fprintf(f, "%s\n", hashValue);

        // ---------------
        // Clear hashValue
        // ---------------
        strncpy(hashValue, "", sizeof(hashValue));
        counterInt++;
        printCounter++;
        clearCounter++;
    }

    clock_t finish = clock();
    printf("\n%'llu hashes checked in %'f seconds.\n\n", (tartgetInt - startingInt), (double)(finish - start) / CLOCKS_PER_SEC);

    return 0;
}
