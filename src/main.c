#include "s21_sprintf.h"
#include "s21_string.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(void) {
    char spec[] = "%-+10.5lo";
    unsigned long int a = 0;
    a = -1;


    char stra[255] = {'\0'};

    s21_sprintf(stra, spec, 50, 3, a);
    printf("s21: |%s|\n", stra);


    char strb[255] = {'\0'};
    long int b = -50;

        sprintf(strb, spec, 50, 3, a);
    printf("std: |%s|", strb);

    return 0;
}
