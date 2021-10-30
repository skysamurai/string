#include <stdio.h>
#include "s21_string.h"




// char *strcat(char *dest, const char *src)




// char *strncat(char *dest, const char *src, size_t n) 





// char *strchr(const char *str, int c) 






int s21_strcmp(const char *str1, const char *str2)

{
    for (; *str1 && *str1 == *str2 ; str2 ++ , str1 ++ ) ;
    return *str1 - *str2 ;
}





// int strncmp(const char *str1, const char *str2, size_t n)