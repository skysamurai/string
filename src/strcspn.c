#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
    s21_size_t j, i = 0;
    int flag = 1;
    while ((str1[i] != 0) && (flag != 0)) {
        j = 0;
        while ((str2[j] != 0) && (flag != 0)) {
            if (str1[i] == str2[j]) flag = 0;
            ++j;
        }
        if (flag != 0) ++i;
    }
    return i;
}
