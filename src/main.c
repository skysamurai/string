/*
   Double to ASCII Conversion without sprintf.
   Roughly equivalent to: sprintf(s, "%.14g", n);
*/

#include <math.h>
#include <string.h>
// For printf
#include <stdio.h>
//#include <stdlib.h>
#include "s21_string/s21_string.h"

static double PRECISION = 0.00000000000001;
static int MAX_NUMBER_STRING_SIZE = 3;
int main(int argc, char **argv) {
    int i;
    char s[MAX_NUMBER_STRING_SIZE];
    double d[] = {323.786e-303,
                  -123.456789,
                  42.0,
                  1234567.89012345,
                  1.00000000000000018,
                  555555.55555555555555555,
                  -888888888888888.8888888,
                  111111111111111111111111.2222222222,
                  0.085,
                  16.9};

    for (i = 0; i < 10; i++) {
        printf("\n\t\t%100.100lf:\nprintf:\t\t%.100e\n", d[i], d[i]);

        char s21str[400];
        s21_wrapper_sprintf(s21str, "s21   : %.100e", d[i]);
        printf("%s \n", s21str);
    }
}
