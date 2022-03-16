#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include "headers/desData.h"
#include "headers/key64to48.h"

KEY_DATA_INIT;

extern char KEY_PATH[];

int key56bit[56];
int key48bit[17][48];


void key56to48(int round, int pos, int text);
int key64to56(int pos, int text);
void key64to48(unsigned int key[]);

void create16Keys()
{
    FILE* pt = fopen(KEY_PATH, "rb");
    unsigned int key[64];
    int i;
    int ch;
 
    for (i = 0; i < 64; i++)
    {
        if (feof(pt))
        {
            break;
        }
        ch = getc(pt);
        key[i] = ch % 2;
    }
    // i now will be the key len
    // for example if key les than 64 -> ABC123 -> ABC123ABC123ABC123...
    for (int j = i; j < 64; j++)
    {
        key[j] = key[j % i];
    }
    
 
    key64to48(key);
    fclose(pt);
}

void key56to48(int round, int pos, int text)
{
    int i;
    for (i = 0; i < 56; i++)
    {
        if (PC2[i] == pos + 1) {
            break;
        }
    }
    key48bit[round][i] = text;
}
 
int key64to56(int pos, int text)
{
    int i;
    for (i = 0; i < 56; i++)
    {
        if (PC1[i] == pos + 1) {
            break;
        }
    }
    key56bit[i] = text;
}
 
void key64to48(unsigned int key[])
{
    int k, backup[17][2];
    int CD[17][56];
    int C[17][28], D[17][28];
 
    for (int i = 0; i < 64; i++) {
        key64to56(i, key[i]);
    }
 
    for (int i = 0; i < 56; i++)
    {
        if (i < 28) {
            C[0][i] = key56bit[i];
        }
        else {
            D[0][i - 28] = key56bit[i];
        }
    }
 
    for (int x = 1; x < 17; x++)
    {
        int shift = SHIFTS[x - 1];
 
        for (int i = 0; i < shift; i++) {
            backup[x - 1][i] = C[x - 1][i];
        }
 
        for (int i = 0; i < (28 - shift); i++) {
            C[x][i] = C[x - 1][i + shift];
        }
 
        k = 0;
        for (int i = 28 - shift; i < 28; i++) {
            C[x][i] = backup[x - 1][k++];
        }
 
        for (int i = 0; i < shift; i++) {
            backup[x - 1][i] = D[x - 1][i];
        }
 
        for (int i = 0; i < (28 - shift); i++) {
            D[x][i] = D[x - 1][i + shift];
        }
 
        k = 0;
        for (int i = 28 - shift; i < 28; i++) {
            D[x][i] = backup[x - 1][k++];
        }
    }
 
    for (int j = 0; j < 17; j++)
    {
        for (int i = 0; i < 28; i++) {
            CD[j][i] = C[j][i];
        }
 
        for (int i = 28; i < 56; i++) {
            CD[j][i] = D[j][i - 28];
        }
    }
 
    for (int j = 1; j < 17; j++)
    {
        for (int i = 0; i < 56; i++) {
            key56to48(j, i, CD[j][i]);
        }
    }
}
