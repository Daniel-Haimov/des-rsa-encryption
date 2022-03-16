#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "headers/des.h"
#include "headers/encrypt.h"
#include "headers/decrypt.h"
#include "headers/cipher.h"
#include "headers/permutation.h"
#include "headers/key64to48.h"


FILE* out;
char INPUT_PATH[500]     ;//   = "inputs/input.txt";
char KEY_PATH[500]       ;//   = "inputs/key.txt";
char RESULT_PATH[500]    ;//   = "outputs/result.txt";
char CIPHER_PATH[500]    ;//   = "outputs/cipher.txt";
char DECRYPTED_PATH[500] ;//   = "outputs/decrypted.txt";
char BITS_TMP_PATH[500]  ;//   = "outputs/bits.txt";

char OUTPUTS_PATH[500]   ;//   = "outputs";


int LEFT[17][32], RIGHT[17][32];
int IPtext[64];
int EXPtext[48];
int XORtext[48];
int X[8][6];
int X2[32];
int R[32];
int key48bit[17][48];
int CIPHER[64];
int ENCRYPTED[64];

void initDes(char* state, char* inputPath, char* keyPath, char* outputPath)
{

    strcpy(KEY_PATH, keyPath);

    char uuid[100];
    sprintf(uuid, "%ld%d", time(NULL), rand());

    if (!strcmp(state, "e")){ //input -> cipher
        strcat(INPUT_PATH, inputPath);
        strcat(CIPHER_PATH, outputPath);

        // create tmp files

        strcat(BITS_TMP_PATH, uuid);
    }
    else if (!strcmp(state, "d")){ //cipher -> result
        strcat(CIPHER_PATH, inputPath);
        strcpy(RESULT_PATH, outputPath);

        // create tmp files

        strcat(DECRYPTED_PATH, uuid);
    }

    create16Keys();
}

void handleEncrypt()
{
    // remove old cipher file if any
    remove(CIPHER_PATH);
    long int n = findFileSize(INPUT_PATH) / 8;
    convertCharToBit(n);
    encrypt(n);
    
    remove(BITS_TMP_PATH);
}

void handleDecrypt()
{
    // remove old result file if any
    remove(RESULT_PATH);
    long int nCipher = findFileSize(CIPHER_PATH) / 64;
    decrypt(nCipher);
    
    remove(DECRYPTED_PATH);

}

void rek_mkdir(char *path) {
    char *sep = strrchr(path, '/');
    if(sep != NULL) {
        *sep = 0;
        rek_mkdir(path);
        *sep = '/';
    }
    mkdir(path, 0777);
    // if(mkdir(path, 0777))
    //     printf("error while trying to create '%s'\n%m\n", path); 
}

FILE *fopen_mkdir(char *path, char *mode) {
    char *sep = strrchr(path, '/');
    if(sep) { 
        char *path0 = strdup(path);
        path0[ sep - path ] = 0;
        rek_mkdir(path0);
        free(path0);
    }
    return fopen(path,mode);
}

void convertToBinary(int n)
{
    int k, m;
    for (int i = 7; i >= 0; i--)
    {
        m = 1 << i;
        k = n & m;
 
        if (k == 0) {
            fprintf(out, "0");
        }
        else {
            fprintf(out, "1");
        }
    }
}
 
int convertCharToBit(long int n)
{
    FILE* inp = fopen(INPUT_PATH, "rb");
    out = fopen_mkdir(BITS_TMP_PATH, "wb+");
    char ch;
    int i = n * 8;
 
    while (i)
    {
        ch = fgetc(inp);
        if (ch == -1) {
            break;
        }
        i--;
        convertToBinary(ch);
    }
    fclose(out);
    fclose(inp);
}
 
long int findFileSize(char* file_path)
{
    FILE* inp = fopen(file_path, "rb");
    long int size;
 
    if (fseek(inp, 0L, SEEK_END)) {
        perror("fseek() failed");
    }
    // size will contain number of chars in the input file.
    else {
        size = ftell(inp);
    }
    fclose(inp);
 
    return size;
}
 
int main(int argc, char *argv[])
{ 

// initDes("inputs/input.txt", "inputs/key.txt", "outputs", "result");

// "inputs/input.txt" "inputs/key.txt" "outputs" "result"
    if(argc == 5){
        printf("%s, %s, %s, %s, %s\n", argv[0], argv[1], argv[2], argv[3], argv[4]);
        initDes(argv[1], argv[2], argv[3], argv[4]);
        if (!strcmp(argv[1], "e") || !strcmp(argv[1], "encrypt")){
            handleEncrypt();
        }
        else if (!strcmp(argv[1], "d") || !strcmp(argv[1], "decrypt")){
            handleDecrypt();
        }
    }else{
        printf("DES FAILED\n");
    }

    return 0;
}
