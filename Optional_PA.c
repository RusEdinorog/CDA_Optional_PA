/*
Lev Vinokur
Optional Programming Assignment
April 24th 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DIR "traces.txt"
#define NUMHEXLINES 12000
#define MAX_LEN 100
#define BLOCK_SIZE 16 // Size of each cache block in bytes
#define CACHE_SIZE 64 // Size of the cache in bytes
#define NUM_BLOCKS 4  // Number of blocks in the cache

// Structs:
typedef struct
{
    int tag;               // Tag for a block
    char data[BLOCK_SIZE]; // Data for a block
} CacheBlock;

// Prototypes:
void directMappedCache(CacheBlock cache[NUM_BLOCKS], char lines[NUMHEXLINES][MAX_LEN]);

int main()
{
    char lines[NUMHEXLINES][MAX_LEN];
    char fname[20];
    FILE *fptr = NULL;
    int i = 0;
    int totalLines = 0;

    // Get all inputs from file
    fptr = fopen(DIR, "r");
    while (fgets(lines[i], MAX_LEN, fptr))
    {
        lines[i][strlen(lines[i]) - 1] = '\0';
        i++;
    }

    // Assign the value of i to the number of total lines find in the file
    totalLines = i;

    // DEBUG:
    // printf("\n The contents of the file are : \n");

    // Convert all hex values to binary numbers and store the result in an array:
    for (i = 0; i < totalLines; ++i)
    {
        // DEBUG: Prints all the hex values
        // printf(" %s\n", lines[i]);

        int len = strlen(lines[i]);

        char newStr[MAX_LEN] = "";

        for (int j = 2; j < len; j++) // Start looping at the second element because we want to skip the 0x and start at the actual hex number
        {
            // TODO: I think all of the below can be switched to having only one strcat call per each statement
            //  Construct New String Value
            switch (lines[i][j])
            {
            case '0':
                // printf("0000");

                // Add the 4 binary values to the end of the array
                strcat(newStr, "0000");

                break;
            case '1':
                // printf("0001");

                // Add the 4 binary values to the end of the array
                strcat(newStr, "0001");

                break;
            case '2':
                // printf("0010");

                // Add the 4 binary values to the end of the array
                strcat(newStr, "0010");

                break;
            case '3':
                // printf("0011");

                // Add the 4 binary values to the end of the array
                strcat(newStr, "0011");

                break;
            case '4':
                // printf("0100");

                // Add the 4 binary values to the end of the array
                strcat(newStr, "0100");

                break;
            case '5':
                // printf("0101");

                // Add the 4 binary values to the end of the array
                strcat(newStr, "0101");

                break;
            case '6':
                // printf("0110");

                // Add the 4 binary values to the end of the array
                strcat(newStr, "0110");

                break;
            case '7':
                // printf("0111");

                // Add the 4 binary values to the end of the array
                strcat(newStr, "0111");

                break;
            case '8':
                // printf("1000");

                // Add the 4 binary values to the end of the array
                strcat(newStr, "1000");

                break;
            case '9':
                // printf("1001\n");

                // Add the 4 binary values to the end of the array
                strcat(newStr, "1001");

                // printf("Printed: \n");
                // printf("%c", newStr[curLen]);
                // printf("%c", newStr[curLen + 1]);
                // printf("%c", newStr[curLen + 2]);
                // printf("%c", newStr[curLen + 3]);
                // printf("\n\n\n");

                break;
            case 'A':
            case 'a':
                // printf("1010");

                // Add the 4 binary values to the end of the array
                strcat(newStr, "1010");

                break;
            case 'B':
            case 'b':
                // printf("1011");

                // Add the 4 binary values to the end of the array
                strcat(newStr, "1011");
                break;
            case 'C':
            case 'c':
                // printf("1100");

                // Add the 4 binary values to the end of the array
                strcat(newStr, "1100");

                break;
            case 'D':
            case 'd':
                // printf("1101");

                // Add the 4 binary values to the end of the array
                strcat(newStr, "1101");

                break;
            case 'E':
            case 'e':
                // printf("1110");

                // Add the 4 binary values to the end of the array
                strcat(newStr, "1110");

                break;
            case 'F':
            case 'f':
                // printf("1111");

                // Add the 4 binary values to the end of the array
                strcat(newStr, "1111");

                break;
            default:
                // printf("\nInvalid hexadecimal digit %c", lines[i][j]);
            } // end switch

        } // end inner for

        // Debug
        // printf("\nFinal string: \n");
        // printf("%s", newStr);

        // Strcpy the new string to overwrite the old string
        strcpy(lines[i], newStr);

        // Debug
        //  len = strlen(lines[i]);
        //  printf("\nFinal string again: \n");
        //  for (int j = 0; j < len; j++)
        //  {
        //      printf("%c", lines[i][j]);
        //  }

    } // end outer for

    printf("\n");

    // Init cache
    CacheBlock cache[NUM_BLOCKS];
    for (int i = 0; i < NUM_BLOCKS; i++)
    {
        cache[i].tag = -1; // Initializing all values in the cache to -1 so that we know they are not taken by any value yet
    }

    // Implement all caching functions and output the results as they come:
    directMappedCache(cache, lines);

    // Output the resulting runtimes of all the caching functions:

    return 0;

} // end main

void directMappedCache(CacheBlock cache[NUM_BLOCKS], char lines[NUMHEXLINES][MAX_LEN])
{
    int numHits = 0;
    int numMisses = 0;
    int finalIntAddress = 0;

    for (int i = 0; i < NUMHEXLINES; i++)
    {

        // Convert our binary number (which at the moment is a char array) into an int that we can use to calculate the current block address
        int curLen = strlen(lines[i]);
        for (int j = 0; j < curLen; j++)
        {
            if (lines[i][j] == '1')
            {
                finalIntAddress += pow(2, curLen - j - 1);
            }
        }

        // Calculate the block index and tag for the given address
        int block_index = finalIntAddress / BLOCK_SIZE % NUM_BLOCKS;
        int tag = finalIntAddress / BLOCK_SIZE / NUM_BLOCKS;

        // Check if the block is in the cache
        if (cache[block_index].tag == tag)
        {
            // Cache hit, return the byte at the given address
            //printf("%d\n", cache[block_index].data[finalIntAddress % BLOCK_SIZE]);
            numHits++;
        }
        else
        {
            // Cache miss, load the block from memory and update the cache
            // (In this example, we just fill the block with random data)
            for (int i = 0; i < BLOCK_SIZE; i++)
            {
                cache[block_index].data[i] = rand() % 256;
            }
            cache[block_index].tag = tag;
            //printf("%d\n", cache[block_index].data[finalIntAddress % BLOCK_SIZE]);
            numMisses++;
        }
    }

    printf("The number of hits in the direct cache: %d\n", numHits);
    printf("The number of misses in the direct cache: %d\n", numMisses);

} // end
