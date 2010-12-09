#include <stdio.h>
#include <gmp.h>
#include <stdarg.h>
#include "Hugefib.h"

int main(int argc, char *argv[])
{
    int i;
    if (argc > 1)
    {
        sscanf(argv[1],"%d",&i);
    } else {
        printf("Usage: %s i\n",argv[0]);
        i = 10;
    }
    mpz_t n;
    char *out;

    mpz_init(n);

    //for(i=0; i < 10000; i++)
    //{
    HugeFib(n,i);

    out = mpz_get_str(NULL,10,n);
    //}

    printf("%s\n",out);

    mpz_clear(n);

    return 1;
}

void HugeFib(mpz_t n, int l)
{
    mpz_t a;
    mpz_t b;
    mpz_t c;
    int i;
    int size = (i * 695 ) /1000;

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

    for ( i = 1; i < l; i++)
    {
        mpz_add(c,a,b);
        mpz_set(a,b);
        mpz_set(b,c);
    }

    mpz_set(n,c);

    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(c);
}
