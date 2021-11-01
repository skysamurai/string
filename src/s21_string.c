#include <stdio.h>
#include "s21_string.h"




char *s21_strcat(char *dest, const char *src)
{
    char *a = dest ;
    for (; *dest != '\0' ; dest ++  );    
    for (; *src != '\0' ; src ++);
    *dest = *src ;
    return a;
}



 
 
//  char *strncat(char *dest, const char *src, size_t n)



char *s21_strchr(const char *str, int c) 

{
     for (; *str != '\0'; str++)
  if (*str == c)
    return (char *) str;

return NULL;
}




int s21_strcmp(const char *str1, const char *str2)

{
    for (; *str1 && *str1 == *str2 ; str2 ++ , str1 ++ ) ;
    return *str1 - *str2 ;
}





// int strncmp(const char *str1, const char *str2, size_t n)
