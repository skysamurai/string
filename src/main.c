#include "s21_string/s21_string.h"

int main(void) {
    char format[] = "%e";
    char string1[1024] = "aaaaa";
    s21_wrapper_sprintf(string1, format, 10.);
    printf("|%s|\n", string1);

    char string2[1024] = "aaaaa";
                sprintf(string2, format, 10.);
    printf("|%s|\n", string2);
}
