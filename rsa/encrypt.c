#include <stdio.h>
#include <stdlib.h>
#include "headers/encrypt.h"
#include "headers/utils.h"

extern char PUBLIC_KEY_PATH[500]	;
extern char INPUT_PATH[500]			;
extern char CIPHER_PATH[500]		;

int encrypt ()
{
    int m, n, e;
    unsigned long long int c;

    FILE *key = fopen(PUBLIC_KEY_PATH, "r");
    fscanf(key, "%d %d", &n, &e);
    fclose(key);

	// printf("ciphertext c = ");

	FILE *inp = fopen(INPUT_PATH, "r");
	FILE *outp = fopen_mkdir(CIPHER_PATH, "w");

	char msg;
	while (fscanf(inp, "%c", &msg) != EOF){
		c = modpow(msg, e, n);
		fprintf(outp, "%llu\n", c);
	}
	
	// int i;
	// for (i = 0; argv[1][i]!= '\0'; i++)
	// {
    //     	c = modpow(argv[1][i],e,n);
	// 	// printf("%llu ", c);
	// 	fprintf(outp, "%llu\n", c);
	// }

    // printf("\n");
    fclose(outp);
    return 0;
}