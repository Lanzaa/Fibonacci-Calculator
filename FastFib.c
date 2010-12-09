#include <stdio.h>
#include <gmp.h>
#include "FastFib.h"

int main(int argc, char *argv[])
{
    int i;
    if (argc > 1)
    {
        sscanf(argv[1],"%d",&i);
    } else {
        printf("Usage: %s i\n",argv[0]);
        i = 100;
    }
    mpz_t n;
    char *out;

    mpz_init(n);

    FastFib(n,i);

    //out = mpz_get_str(NULL,10,n);
	//printf("%s\n",out);

    mpz_clear(n);

    return 1;
}

void FastFib(mpz_t n, int l)
{
    mpz_t a;
    mpz_t b;
    mpz_t c;
    int i = 31; // TODO change this for larger l values

    if ( l <= 0 )
    {
        mpz_set_ui(n,0);
        return;
    }
    else if ( l == 1 )
    {
        mpz_set_ui(n,1);
        return;
    }

    mpz_init(a);
    mpz_init(b);
    mpz_init(c);

    mpz_set_ui(a,0);
    mpz_set_ui(b,1);

    while ( !(l & (1 << i)) && i >= 1)
    {
        i--;
    }
    i--;
    for ( ; i >= 0; i--)
    {
        if ( l & (1 << i) )
        {
            sqFib(c,b,a);
            nextFib(c,b,a);
        }
        else
        {
            sqFib(c,b,a);
        }
    }

    mpz_set(n,b);
    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(c);
    return;
}

void sqFib(mpz_t c, mpz_t b, mpz_t a)
{
    mpz_mul(c,b,a);
    mpz_mul_2exp(c,c,1);
    mpz_mul(a,a,a);
    mpz_mul(b,b,b);
    mpz_add(c,b,c);
    mpz_add(a,a,b);
    mpz_set(b,c);
}

void nextFib(mpz_t c, mpz_t b, mpz_t a)
{
    mpz_add(c,b,a);
    mpz_set(a,b);
    mpz_set(b,c);
}
