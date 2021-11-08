#include <errno.h>
#include <error.h>
#include <stdio.h>
#include <string.h>

#include "./s21_string/s21_sprintf/s21_sprintf.h"
#include "./s21_string/s21_string.h"

int main(void) {
    char spec[] = "a%-5d%ln";

    char stra[255] = {'\0'};
    int a = 4;

    s21_sprintf(stra, spec, a, &a);
    printf("s21: |%d|%s|\n", a, stra);

    char strb[255] = {'\0'};
    int b = 4;

    sprintf(strb, spec, b, &b);
    printf("std: |%d|%s|", b, strb);

    if (errno) {
        printf("%s", strerror(errno));
    }

    return 0;
}
