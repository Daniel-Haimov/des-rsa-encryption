#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <inttypes.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "headers/rsa.h"
#include "headers/encrypt.h"
#include "headers/decrypt.h"
#include "headers/utils.h"

#define MAX_VALUE 65535

#define E_VALUE 3 /*65535*/

char PRIVATE_KEY_PATH[500]	;
char PUBLIC_KEY_PATH[500]	;
char PQ_PATH[500]    		;
char INPUT_PATH[500]		;
char RESULT_PATH[500]		;
char CIPHER_PATH[500]		;

uint32_t findD(uint16_t e, uint32_t phi)
{
	uint32_t eprev, dprev, d = 1, etemp, dtemp;

	eprev = phi, dprev = phi;
	while (e != 1)
	{
		etemp = e;
		dtemp = d;
		e = eprev - eprev / etemp * e;
		d = dprev - eprev / etemp * d;
		eprev = etemp;
		dprev = dtemp;
		while (d < 0)
			d += phi;
	}

	return d;
}

int ifprime(uint16_t n)
{
	uint16_t i;
	for (i = 2; i <= n / 2; i++)
	{
		if (n % i == 0)
			return 0;
	}
	return 1;
}

uint16_t gcd(uint16_t num1, uint32_t num2)
{
	uint16_t i, temp;
	if (num1 > num2)
	{
		temp = num1;
		num1 = num2;
		num2 = temp;
	}
	for (i = num1; i > 0; i--)
	{
		if (num1 % i == 0 && num2 % i == 0)
			return i;
	}
}

uint16_t getprime()
{
	uint16_t n;
	do
	{
		srand(time(NULL));
		n = rand() % MAX_VALUE + 5;
	}while  (!ifprime(n));
	return n;
}

void setprimes(uint16_t e, uint16_t *p, uint16_t *q, uint32_t *n, uint32_t *phi)
{
	do
	{
		*p = getprime();
		do
			*q = getprime();
		while(*p == *q);

		*n = *p * *q;
		*phi = *n - *p - *q + 1;
	}while (gcd(e,*phi) != 1);
}

void generateRsa(){
	uint16_t e = E_VALUE, p, q;
	uint32_t n, phi, d;

	setprimes(e, &p, &q, &n, &phi);

	d = findD(e,phi);
	FILE *outp = fopen_mkdir(PUBLIC_KEY_PATH, "w");
	fprintf(outp, "%"PRIu32" %"PRIu16, n, e);
	fclose(outp);

	outp = fopen_mkdir(PRIVATE_KEY_PATH, "w");
	fprintf(outp, "%"PRIu32" %"PRIu32, n, d);
	fclose(outp);

	outp = fopen_mkdir(PQ_PATH, "w");
    fprintf(outp, "%"PRIu16" %"PRIu16, p, q);
    fclose(outp);
}

void initPaths(char* privateKeyPath, char* publicKeyPath, char* pqKeyPath, char* inputPath, char* resultPath, char* cipherPath){
	strcat(PRIVATE_KEY_PATH, privateKeyPath);
	strcat(PUBLIC_KEY_PATH, publicKeyPath);
	strcat(PQ_PATH, pqKeyPath);
	strcat(INPUT_PATH, inputPath);
	strcat(RESULT_PATH, resultPath);
	strcat(CIPHER_PATH, cipherPath);
}

int main (int argc, char *argv[])
{

	if (argc == 5 && (!strcmp(argv[1], "i") || !strcmp(argv[1], "init"))){
		printf("start generate...\n");
		initPaths(argv[2], argv[3], argv[4], "", "", "");
		generateRsa();
	}
	else if (argc == 5 && (!strcmp(argv[1], "e") || !strcmp(argv[1], "encrypt"))){
		initPaths("", argv[3], "", argv[2], "", argv[4]);
		encrypt();
	}
	else if (argc == 6 && (!strcmp(argv[1], "d") || !strcmp(argv[1], "decrypt"))){
		initPaths(argv[3], "", argv[4], "", argv[5], argv[2]);
		decrypt();
	}
	else{
		printf("RSA FAILED\n");
	}
	
	return 0;
}