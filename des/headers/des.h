#pragma once

void initDes(char* state, char* inputPath, char* keyPath, char* outputPath);

void handleEncrypt();

void handleDecrypt();

void rek_mkdir(char *path);

FILE *fopen_mkdir(char *path, char *mode);

void convertToBinary(int n);
 
int convertCharToBit(long int n);
 
long int findFileSize(char* file_path);
 
int main(int argc, char *argv[]);