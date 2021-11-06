#include "./s21_string/s21_sprintf/s21_sprintf.h"
#include "string.h"
#include "./s21_string/s21_string.h"

int main(void) {
    char str[255];
    char spec[] = "privet, anton, kak tvoi %5d";
    long a = 3;

    sprintf(str, spec, a);
    printf("|%s|\n", str);

    s21_wrapper_sprintf(str, spec, a);
    printf("|%s|", str);

    return 0;
}
