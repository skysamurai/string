#include "s21_string.h"
#include <stdlib.h>

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
    void *temp;
    temp = malloc(n * sizeof(char));
    s21_memcpy(temp, src, n);
    s21_memcpy(dest, temp, n);
    free(temp);
    return dest;
}
