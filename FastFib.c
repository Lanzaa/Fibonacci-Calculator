#include <stdio.h>
#include <string.h>
#include <gmp.h>

void print_help(char* name);
void print_usage(char* name);
void FastFib(mpz_t n, int l);
void sqFib(mpz_t c, mpz_t b, mpz_t a);
void nextFib(mpz_t c, mpz_t b, mpz_t a);

// Set the max usable value
int MAX_I = 0x7FFFFFFF; // 2,147,483,647

int main(int argc, char *argv[]) {

    int quiet = 0;
    unsigned int i = -1;
    int k = 0;
    for (int j = 1; j < argc; j++) {
        if (0 == strcmp(argv[j],"-q")) {
                quiet = 1;
        } else if (0 == strcmp(argv[j], "-h")) {
                print_help(argv[0]);
                return 0;
        } else {
            // Try to parse this as the input
            // yes... if all input is valid, the last one is used
            k = sscanf(argv[j],"%d",&i);
            if (k == 0) {
                printf("Invalid argument: %s\n",argv[j]);
                print_usage(argv[0]);
                return 1;
            }
        }
    }
    if (i < 0 || i > MAX_I) { // invalid input
        printf("Input value must be 0 <= i <= %d\n", MAX_I);
        return 1;
    }
    mpz_t n;
    char *out;

    mpz_init(n);

    printf("Calculating Fib(%d)...\n", i);
    FastFib(n,i);

    //mpz_fib_ui(n, i);
    if (!quiet) {
        // Print n to stdout
        printf("Fib(%d) is...\n", i);
        mpz_out_str(NULL, 10, n);
        printf("\n");
    } else {
        printf("Finished calculation.\n");
    }

    mpz_clear(n);

    return 0;
}

void print_help(char* name) {
    // TODO add more helpful instructions
    int width = 5;
    print_usage(name);
    printf("This program calulates arbitrary fibonacci numbers.\n");
    printf("%5s\t%s", "-h", "Prints this message.\n");
    printf("%5s\t%s", "-q", "Prevents the conversion from binary to decimal of Fib(i).\n");
    printf("%5s\t%s %d\n", "i", "i must be an integer, 0 <= i <=", MAX_I);
    printf("\n");
}

void print_usage(char* name) {
    printf("Usage: %s [-h] [-q] i\n", name);
}

void FastFib(mpz_t n, int l) {
    mpz_t a;
    mpz_t b;
    mpz_t c;
    int i = 31; // TODO change this for larger l values

    if ( l <= 0 ) {
        mpz_set_ui(n,0);
        return;
    }
    else if ( l == 1 ) {
        mpz_set_ui(n,1);
        return;
    }

    mpz_init(a);
    mpz_init(b);
    mpz_init(c);

    mpz_set_ui(a,0);
    mpz_set_ui(b,1);

    while ( !(l & (1 << i)) && i >= 1) {
        i--;
    }
    i--;
    for ( ; i >= 0; i--) {
        if ( l & (1 << i) ) {
            sqFib(c,b,a);
            nextFib(c,b,a);
        } else {
            sqFib(c,b,a);
        }
    }

    mpz_set(n,b);
    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(c);
    return;
}

void sqFib(mpz_t c, mpz_t b, mpz_t a) {
    mpz_mul(c,b,a);
    mpz_mul_2exp(c,c,1);
    mpz_mul(a,a,a);
    mpz_mul(b,b,b);
    mpz_add(c,b,c);
    mpz_add(a,a,b);
    mpz_set(b,c);
}

void nextFib(mpz_t c, mpz_t b, mpz_t a) {
    mpz_add(c,b,a);
    mpz_set(a,b);
    mpz_set(b,c);
}
