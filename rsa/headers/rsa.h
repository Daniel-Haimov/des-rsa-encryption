#pragma once

uint32_t findD(uint16_t e, uint32_t phi);
int ifprime(uint16_t n);
uint16_t gcd(uint16_t num1, uint32_t num2);
uint16_t getprime();
void setprimes(uint16_t e, uint16_t *p, uint16_t *q, uint32_t *n, uint32_t *phi);
void generateRsa();
void initPaths(char* privateKeyPath, char* publicKeyPath, char* pqKeyPath, char* inputPath, char* resultPath, char* cipherPath);
int main (int argc, char *argv[]);