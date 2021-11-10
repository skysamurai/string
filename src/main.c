#include "s21_sprintf.h"
#include "s21_string.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(void) {
    char spec[] = "% #+-e$\nn string";
    double a = 0.2e-100;


    char stra[255] = {'\0'};
    s21_sprintf(stra, spec, a);
    printf("s21: |%s|\n", stra);


    char strb[255] = {'\0'};
        sprintf(strb, spec, a);
    printf("std: |%s|\n", strb);

    return 0;
}
