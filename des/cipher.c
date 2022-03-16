#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include "headers/desData.h"

#define XOR(a, b) (a)^(b)

CHIPER_DATA_INIT;

extern int LEFT[17][32], RIGHT[17][32];
extern int EXPtext[48];
extern int XORtext[48];
extern int key48bit[17][48];
extern int X[8][6];
extern int X2[32];
extern int R[32];

void expansion_function(int pos, int text);
int SBox(int XORtext[]);
int PBox(int pos, int text);
int F1(int i);
int ToBits(int value);

void cipher(int Round, int mode)
{
    for (int i = 0; i < 32; i++) {
        expansion_function(i, RIGHT[Round - 1][i]);
    }
 
    for (int i = 0; i < 48; i++)
    {
        if (mode == 0) {
            XORtext[i] = XOR(EXPtext[i], key48bit[Round][i]);
        }
        else {
            XORtext[i] = XOR(EXPtext[i], key48bit[17 - Round][i]);
        }
    }
 
    SBox(XORtext);
 
    for (int i = 0; i < 32; i++) {
        PBox(i, X2[i]);
    }
 
    for (int i = 0; i < 32; i++) {
        RIGHT[Round][i] = XOR(LEFT[Round - 1][i], R[i]);
    }
}

void expansion_function(int pos, int text)
{
    for (int i = 0; i < 48; i++)
    {
        if (E[i] == pos + 1) {
            EXPtext[i] = text;
        }
    }
}

int SBox(int XORtext[])
{
    int k = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 6; j++) {
            X[i][j] = XORtext[k++];
        }
    }
 
    int value;
    for (int i = 0; i < 8; i++)
    {
        value = F1(i);
        ToBits(value);
    }
}
 
int PBox(int pos, int text)
{
    int i;
    for (i = 0; i < 32; i++)
    {
        if (P[i] == pos + 1) {
            break;
        }
    }
    R[i] = text;
}

int F1(int i)
{
    int r, c, b[6];
 
    for (int j = 0; j < 6; j++) {
        b[j] = X[i][j];
    }
 
    r = b[0] * 2 + b[5];
    c = 8 * b[1] + 4 * b[2] + 2 * b[3] + b[4];

    return S[i][r][c];
}

int ToBits(int value)
{
    int k, j, m;
    static int i;
 
    if (i % 32 == 0) {
        i = 0;
    }
 
    for (j = 3; j >= 0; j--)
    {
        m = 1 << j;
        k = value & m;
        if (k == 0) {
            X2[3 - j + i] = '0' - 48;
        }
        else {
            X2[3 - j + i] = '1' - 48;
        }
    }
 
    i = i + 4;
}
