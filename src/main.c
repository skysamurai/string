#include <stdio.h>
#include <stdlib.h>
#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, size_t n) {
    int i = 0;
    int flag = 0;
    while ((flag != -1) && (i != n) && ((str2[i] != '\0'))) {
      printf("%c %c ", str1[i], str2[i]);
        if (str1[i] != str2[i])
            flag = -1;
        else
            ++i;
    }
return flag;
}
char *s21_strcpy(char *dest, const char *src) {
    size_t i = 0;
    while (src[i] != 0) {
        dest[i] = src[i];
        ++i;
    }
return dest;
}

int s21_strcmp(const char *str1, const char *str2) {
    int i = 0;
    int flag = 0;
    while ((flag != -1) && (str1[i] != '\0') && ((str2[i] != '\0'))) {
      printf("%c %c ", str1[i], str2[i]);
        if (str1[i] != str2[i])
            flag = -1;
        else
            ++i;
    }
return flag;
}

size_t s21_strlen(const char *str) {
    size_t i = 0;
    while (str[i] != 0) ++i;
return i;
}
