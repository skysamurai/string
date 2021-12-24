#include "s21_string.h"
#include <stdlib.h>

void *s21_to_upper(const char *str) {
    void *temp;
    if (str != S21_NULL) {
        int n = s21_strlen(str);
        temp = malloc((n + 1) * sizeof(char));
        for (int i = 0; i < n; i++) {
            if ((*((char *)str + i) > 96) & (*((char *)str + i) < 123)) {
                *((char *)temp + i) = *((char *)str + i) - 32;
            } else {
                *((char *)temp + i) = *((char *)str + i);
            }
        }
        ((char *)temp)[n] = '\0';
    } else {
        temp = S21_NULL;
    }
    return (char *)temp;
}
