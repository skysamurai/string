#include <stdio.h>
#include <stdlib.h>
#include "s21_string.h"

int s21_strcmp(const char *str1, const char *str2) {
    int i = 0;
    int flag = 0;
    while ((flag != -1) && (str1[i] != '\0') && ((str2[i] != '\0'))) {
        if (str1[i] != str2[i])
            flag = -1;
        else
            ++i;
    }
return flag;
}

int s21_strncmp(const char *str1, const char *str2, size_t n) {
    int i = 0;
    int flag = 0;
    while ((flag != -1) && (i != n) && ((str2[i] != '\0'))) {
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

char *s21_strncpy(char *dest, const char *src, size_t n) {
    size_t i = 0;
    while ((src[i] != 0) && (i <= n)) {
        dest[i] = src[i];
        ++i;
    }
return dest;
}

size_t s21_strcspn(const char *str1, const char *str2) {
    size_t j, i = 0;
    int flag = 1;
    while ((str1[i] != 0) && (flag != 0 )) {
        j = 0;
        while ((str2[j] != 0) && (flag != 0)) {
            if (str1[i] == str2[j])
                flag = 0;
        ++j;
        }
        if (flag != 0)
            ++i;
    }
return i;
}

char *s21_strerror(int errnum) {
    errnum = 123;
    printf("%i, ", errnum);
}

size_t s21_strlen(const char *str) {
    size_t i = 0;
    while (str[i] != 0) ++i;
return i;
}
