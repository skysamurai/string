#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
    char *res = S21_NULL;
    int i = 0;
    while (((str + i)[0] != c) && (((str + i)[0]) != '\0')) {
        i++;
    }
    if ((str + i)[0] == c) {
        res = (char *)(str + i);
    }
    return res;
}
