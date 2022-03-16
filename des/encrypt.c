#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#include "headers/des.h"
#include "headers/permutation.h"
#include "headers/cipher.h"


FILE* out;

extern char BITS_TMP_PATH[];
extern char CIPHER_PATH[];

extern int LEFT[17][32], RIGHT[17][32];
extern int IPtext[64];
extern int CIPHER[64];
extern int ENCRYPTED[64];

void Encryption(long int plain[]);

void encrypt(long int n)
{
    FILE* in = fopen(BITS_TMP_PATH, "rb");
 
    long int plain[n * 64];
    int i = -1;
    char ch;
 
    while (!feof(in))
    {
        ch = getc(in);
        plain[++i] = ch - 48;
    }
 
    for (int i = 0; i < n; i++) {
        Encryption(plain + 64 * i);
    }
 
    fclose(in);
}

void Encryption(long int plain[])
{
    out = fopen_mkdir(CIPHER_PATH, "ab+");
    for (int i = 0; i < 64; i++) {
        initialPermutation(i, plain[i]);
    }
 
    for (int i = 0; i < 32; i++) {
        LEFT[0][i] = IPtext[i];
    }
 
    for (int i = 32; i < 64; i++) {
        RIGHT[0][i - 32] = IPtext[i];
    }
 
    for (int k = 1; k < 17; k++)
    {
        cipher(k, 0);
 
        for (int i = 0; i < 32; i++)
            LEFT[k][i] = RIGHT[k - 1][i];
    }
 
    for (int i = 0; i < 64; i++)
    {
        if (i < 32) {
            CIPHER[i] = RIGHT[16][i];
        }
        else {
            CIPHER[i] = LEFT[16][i - 32];
        }
        finalPermutation(i, CIPHER[i]);
    }
 
    for (int i = 0; i < 64; i++) {
        fprintf(out, "%d", ENCRYPTED[i]);
    }
    fclose(out);
}
