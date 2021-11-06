#include "./s21_string/s21_sprintf/s21_sprintf.h"
#include "string.h"
#include "./s21_string/s21_string.h"

int main(void) {
    char str[255] = {'\0'};
    char spec[] = "aaa%020.650+-10+.65e";
    double a = 3.15015e+3;

    s21_wrapper_sprintf(str, spec, a);
    printf("|%s|\n", str);

    sprintf(str, spec, a);
    printf("|%s|", str);

    return 0;
}
