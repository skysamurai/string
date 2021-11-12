#include <math.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

static double PRECISION = 0.00000000000001;
static int MAX_NUMBER_STRING_SIZE = 3;
int main(int argc, char **argv) {
/*     int i;
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
        printf("printf:\t%.100e\n", d[i], d[i]);

        char s21str[4000] = {0};
        s21_sprintf(s21str, "s21:\t%.100e", d[i]);
        printf("%s \n\n", s21str); */

        /*printf("alt:\n");
        for (int i = 0; i < 4000; i++) {
            if (s21str[i] != '\0')
                printf("%c", s21str[i]);
            else
                printf("HERE");
        }
        printf("\nalt end\n");*/
    // }


// Массив со строкой для поиска
   char str [11]="0123456789";
   // Набор символов, которые должны входить в искомый сегмент
   char sym [10]="0001";
  
   // Определяем длину начального сегмента, содержащего символы “210”
   printf ("Длина сегмента: %ld\n", strspn(str,sym));

    return 0;
}
