#include "s21_string.h"

int s21_strcmp(const char *str1, const char *str2) {
    int res = 0;
    int n_str1 = s21_strlen(str1), n_str2 = s21_strlen(str2), i = 0;
    if (n_str1 > n_str2) res = 1;
    if (n_str1 < n_str2) res = -1;
    if (n_str1 == n_str2) {
        while ((str1[i] == str2[i]) && (n_str1)) {
            ++i;
            --n_str1;
        }
        if (n_str1 != 0) res = str1[i] - str2[i];
    }
    return res;
}
