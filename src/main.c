#include "s21_string/s21_string.h"

int main(void) {
    char format[] = "%.50e";
    char string1[1024] = "aaaaa";
    s21_wrapper_sprintf(string1, format, 1111111111111111111111.222222222222);
    printf("|%s|\n", string1);

    char string2[1024] = "aaaaa";
                sprintf(string2, format, 1111111111111111111111.222222222222);
    printf("|%s|\n", string2);
}
