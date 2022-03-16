#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include "headers/desData.h"

PERMUTATION_DATA_INIT;

extern int IPtext[64];
extern int ENCRYPTED[64];

int initialPermutation(int pos, int text)
{
    int i;
    for (i = 0; i < 64; i++)
    {
        if (IP[i] == pos + 1) {
            break;
        }
    }
    IPtext[i] = text;
}

void finalPermutation(int pos, int text)
{
    int i;
    for (i = 0; i < 64; i++)
    {
        if (FP[i] == pos + 1) {
            break;
        }
    }
    ENCRYPTED[i] = text;
}