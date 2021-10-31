#include "s21_string.h"
#include <malloc.h>
void *s21_memchr(const void *str, int c, s21_size_t n) {
    void* res = NULL;
    s21_size_t i = 0;
    while ((*((char*)str + i) != c) & (i < n)) {
        i++;
    }
    if (*((char*)str + i) == c)
        res = (char*)str + i;
    return res;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    int res = 0; s21_size_t i = 0;
    while ((res == 0) & (i < n)) {
        res = *((char*)str1 + i) - *((char*)str2 + i);
        i++;
    }
    return res;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
    for (s21_size_t i = 0; i < n; i++) {
        *((char*)dest + i) = *((char*)src + i);
    }
    return dest;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
    char* temp;
    temp = malloc(n*sizeof(char));
    for (s21_size_t i = 0; i < n; i++) {
        *(temp + i) = *((char*)src + i);
    }
    for (s21_size_t i = 0; i < n; i++) {
        *((char*)dest + i) = *(temp + i);
    }
    free(temp);
    return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
    for (s21_size_t i = 0; i < n; i++) {
        *((char*)str + i) = c;
    }
    return str;
}
