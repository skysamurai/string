#include "s21_string.h"

char *s21_strcpy(char *dest, const char *src) {
    s21_size_t n = s21_strlen(src);
    s21_memcpy(dest, src, n + 1);
    return dest;
}
