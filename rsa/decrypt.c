#include <stdio.h>
#include <stdlib.h>
#include "headers/decrypt.h"
#include "headers/utils.h"

extern char PRIVATE_KEY_PATH[500]       ;
extern char PQ_PATH[500]                ;
extern char CIPHER_PATH[500]		;
extern char RESULT_PATH[500]		;


int inverse(int a, int mod)     /*find inverse of number a in % mod*/
{                               /*inverse of a = i*/
        int aprev, iprev, i = 1, atemp, itemp;

        aprev = mod, iprev = mod;
        while (a != 1)
        {
                atemp = a;
                itemp = i;
                a = aprev - aprev / atemp * a;
                i = iprev - aprev / atemp * i;
                aprev = atemp;
                iprev = itemp;
                while (i < 0)
                        i += mod;
        }

        return i;
}

int decrypt ()
{
        int d, n, p, q, h, m, qInv, m1m2;
        unsigned long long int c, dP, dQ, m1, m2;
        FILE *inp;

        inp = fopen(PRIVATE_KEY_PATH, "r");
        fscanf(inp, "%d %d", &n, &d);
        fclose(inp);

        inp = fopen(PQ_PATH, "r");
        fscanf(inp, "%d %d", &p, &q);
        fclose(inp);

	// printf("message: ");
	inp = fopen(CIPHER_PATH, "r");

        FILE *outp = fopen_mkdir(RESULT_PATH, "w");

	while (fscanf(inp, "%llu", &c) != EOF)
	{
        	dP = d % (p - 1);
        	dQ = d % (q - 1);
        	qInv = inverse(q,p);
        	m1 = modpow(c,dP,p);
        	m2 = modpow(c,dQ,q);
        	m1m2 = m1 - m2;
        	if (m1m2 < 0)
                	m1m2 += p;
       		h = (qInv * m1m2) % p;
        	m = m2 + h * q;
		// printf("%c", m);
                fprintf(outp, "%c", m);
	}
	fclose(inp);
	// printf("\n");
        return 0;
}