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
    char targetHash[65] = "5db201172615cb5b532e6e502d5683b30b1879e9b1e2b7f18534dff22d5be876"; //REAL TARGET

    unsigned long long startingInt = 5000000000; // 5,000,000,000
    unsigned long long startingHex = 0x7649f43c17e43e08446ce5b3119f905acc4e380233e8e96f0468f12aa2b249fa; // 5,000,000,000

    unsigned long long tartgetInt = 5000000000; // 5,000,000,000
    unsigned long long targetHex = 0x7649f43c17e43e08446ce5b3119f905acc4e380233e8e96f0468f12aa2b249fd; // 5,000,000,000

    unsigned long long counterHex = startingHex;
    unsigned char hexOfInt[32];
    unsigned char hash[32];

    int printCounter = 0;
    int clearCounter = 0;


    FILE *f = fopen("hashes.txt", "w");

    printf("\nStarting at:  %'llu\n", startingHex);
    printf("Finishing at: %'llu\n", tartgetInt);
    printf("------------------------------------------------------------------------------\n");
    printf("Target hash:  %s\n\n", targetHash);
    printf("Hashing...\n");

    while (counterHex < targetHex) {

        printf("%x\n", counterHex);
        // Converts counterInt to hex & hashes
        // sprintf(hexOfInt, "%x", counterInt);
        SHA256_CTX ctx;
        sha256_init(&ctx);
        sha256_update(&ctx,hexOfInt,strlen(counterHex));
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
            printf("Raw value:  %s\n", counterHex);
            // printf("Int value:  %'llu\n", counterInt);
            printf("Hash value: %s\n", hashValue);
            printf("----------------------------------------------------------------------------\n");
            break;
        } else {
            // if (argc > 1) {
            //     if (strcmp(argv[1], "log-all") == 0){
            //         printf("\n%'llu\n", counterInt);
            //         printf("%s\n", hexOfInt);
            //         printf("%s\n", hashValue);
            //     } else if (strcmp(argv[1], "log-count") == 0) {
            //         printf("%'llu\n", counterInt);
            //     } else if (strcmp(argv[1], "log-hex") == 0) {
            //         printf("%s\n", hexOfInt);
            //     } else if (strcmp(argv[1], "log-hash") == 0) {
            //         printf("%s\n", hashValue);
            //     } else if (strcmp(argv[1], "log-hex-part") == 0) {
            //         if (printCounter > 1000000){
            //             if (clearCounter > 1000000){
            //                 system("clear");
            //                 // clearCounter = 0;
            //             }
            //             printf("%s\n", hexOfInt);
            //             printCounter = 0;
            //         }
            //     }
            // }
        }

        // ----------------------------------
        // Writes hashing results to txt file
        // ----------------------------------
        fprintf(f, "%s\n", counterHex);
        // fprintf(f, "%'llu\n", counterInt);
        fprintf(f, "%s\n", hashValue);

        // ---------------
        // Clear hashValue
        // ---------------
        strncpy(hashValue, "", sizeof(hashValue));
        counterHex++;
        printCounter++;
        clearCounter++;
    }

    clock_t finish = clock();
    printf("\n%'llu hashes checked in %'f seconds.\n\n", (targetHex - startingHex), (double)(finish - start) / CLOCKS_PER_SEC);

    return 0;
}
