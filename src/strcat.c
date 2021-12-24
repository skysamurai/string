#include "s21_string.h"

char *s21_strcat(char *dest, const char *src) {
    char *result = dest;
    while (*dest != '\0') dest++;
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return result;
}
