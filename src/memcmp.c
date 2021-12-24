#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    int res = 0, n_str1 = s21_strlen(str1), n_str2 = s21_strlen(str2);
    s21_size_t i = 0;
    if (n_str1 > n_str2) res = 1;
    if (n_str1 < n_str2) res = -1;
    if (n_str1 == n_str2) {
        while ((res == 0) & (i < n)) {
            res = *((char *)str1 + i) - *((char *)str2 + i);
            i++;
        }
    }
    return res;
}
