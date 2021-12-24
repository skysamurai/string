#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
    char *res = S21_NULL;
    s21_size_t i = 0;
    const char *cursor = str;

    if (cursor != S21_NULL) {
        while (cursor[i] != '\0') {
            if (cursor[i] == c) {
                res = (char *)(cursor + i);
            }
            i += 1;
        }

        if (cursor[i] == c) {
            res = (char *)(cursor + i);
        }
    }

    return res;
}
