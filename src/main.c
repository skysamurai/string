#include "s21_sprintf.h"
#include <string.h>
#include <stdio.h>
#include "s21_string.h"
#include <stdlib.h>

int main(void) {
    /* char spec[] = "%e"; */
/*     char spec[] = "%-+10.5lo";
    unsigned long int a = 0;
    a -= 1;


    char stra[255] = {'\0'};

    s21_sprintf(stra, spec, a);
    printf("s21: |%s|\n", stra);


    char strb[255] = {'\0'};
    long int b = -50;

        sprintf(strb, spec, a);
    printf("std: |%s|", strb); */

    /* int len;

    len = s21_strspn("это строка из примера", "акортэ с");
    printf("%d", len); */

    char str1[] = "dgdfgs";
    char* str2 = S21_NULL;
    char *istr, *s21_istr;
    istr = strstr(str1,str2);
    //s21_istr = s21_strstr(str1,str2);
    
    printf("%s\n%s\n", istr, s21_istr);

    return 0;
}
