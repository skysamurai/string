#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
    void *res = S21_NULL;
    s21_size_t i = 0;
    const unsigned char *cursor = str;

    if (cursor != S21_NULL) {
        while (i < n && cursor[i] != c) {
            i += 1;
        }

        if ((i < n) && (cursor[i] == c)) {
            res = (void *)(cursor + i);
        }
    }

    return res;
}
