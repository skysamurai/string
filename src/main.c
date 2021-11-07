#include "./s21_string/s21_sprintf/s21_sprintf.h"
#include <string.h>
#include <error.h>
#include <errno.h>
#include <stdio.h>
#include "./s21_string/s21_string.h"

int main(void) {
    char spec[] = "%08.5d%5d%ln";

    char stra[255] = {'\0'};
    int a = 4;

    s21_sprintf(stra, spec, a, a, &a);
    printf("s21: |%d|%s|\n", a, stra);


    char strb[255] = {'\0'};
    int b = 4;

        sprintf(strb, spec, b, b, &b);
    printf("std: |%d|%s|", b, strb);

    if (errno) {
        printf("%s", strerror(errno));
    }

    return 0;
}
