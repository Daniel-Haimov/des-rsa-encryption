#pragma once

unsigned long long int modpow(unsigned long long int base, int power, int mod);

void rek_mkdir(char *path);

FILE *fopen_mkdir(char *path, char *mode);