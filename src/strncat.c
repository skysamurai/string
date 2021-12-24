#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
    char *a = dest;
    s21_size_t i = 0;
    s21_size_t n_dest = s21_strlen(dest);
    s21_size_t n_src = s21_strlen(src);
    for (; *dest != '\0'; dest++) {
    }
    for (i = 0; i < n && i < (n_src + n_dest); i++) {
        *(dest + i) = *(src + i);
    }
    return a;
}
