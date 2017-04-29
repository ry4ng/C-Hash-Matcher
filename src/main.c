#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <unistd.h>

#include "sha256.h"

// void print_hash(unsigned char hash[])
// {
//     int i;
//     for (i=0; i < 32; i++)
//         printf("%02x",hash[i]);
//     printf("\n");
// }

int main()
{
    clock_t start = clock();
    setlocale(LC_NUMERIC, "");

    // char targetHash[65] = "e401f2bd399f3456e5348217a7908ca545ea6d179f60f297a1b0133e87d2ff85"; //5,000
    // char targetHash[65] = "8990d5f8063b0f92bf863fa819cee92e93dd1630cb368e4f6959536a7165f2a9"; //94,010,302
    char targetHash[65] = "8cd178e5738e3042f4ff9cf1f9c86d38980b50074066b4873ef126c6a2c6815a"; //REAL TARGET

    unsigned long long startingInt = 1240798589; // 1,240,798,589
    unsigned long long tartgetInt = 10000000000; // 10,000,000,000

    unsigned char hexOfInt[32];
    unsigned char hash[32];

    unsigned int counter;

    FILE *f = fopen("../hashes.txt", "w");

    printf("\nStarting at: %'llu\n", startingInt);
    printf("Finishing at: %'llu\n", tartgetInt);
    printf("------------------------------------------------------------------------------\n");
    printf("Target hash:  %s\n\n", targetHash);

    while (startingInt < tartgetInt) {

        sprintf(hexOfInt, "%x", startingInt);

        // Prints Raw Value
        // printf("%s \n", hexOfInt);

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

        if (strcmp(hashValue, targetHash) == 0) {
            system("clear");
            printf("----------------------------------------------------------------------------\n");
            printf("A match for your target hash hash been found!\n\n");
            printf("Raw value:  %s\n", hexOfInt);
            printf("Int value:  %'llu\n", startingInt);
            printf("Hash value: %s\n", hashValue);
            printf("----------------------------------------------------------------------------\n");
            break;
        } else {
            // Prints hashed value
            // printf("%s \n", hashValue);
        }

        // Writes hashing results to file
        fprintf(f, "\n%s\n", hexOfInt);
        fprintf(f, "%'llu\n", startingInt);
        fprintf(f, "%s\n", hashValue);

        counter++;
        if (counter >= 1000) {
            system("clear");
            printf("Currently on: ");
            printf("%'llu\n", startingInt);
            counter = 0;
        }

        // Clear hashValue
        strncpy(hashValue, "", sizeof(hashValue));
        startingInt++;
    }

    clock_t finish = clock();
    printf("\n%'llu hashes checked in %'f seconds.\n\n", tartgetInt - startingInt, (double)(finish - start) / CLOCKS_PER_SEC);

    return 0;
}
