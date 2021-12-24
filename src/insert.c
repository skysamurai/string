#include "s21_string.h"
#include "stdlib.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
    s21_size_t n_str = 0;
    s21_size_t n_src = 0;
    int n;
    void *temp = S21_NULL;
    if ((src != S21_NULL) && (str != S21_NULL)) {
        n_src = s21_strlen(src);
        if (start_index < n_src + 1) {
            n_str = s21_strlen(str);
            n = n_src + n_str;
            temp = malloc((n + 1) * sizeof(char));
            s21_memcpy(temp, (char *)src, start_index);
            s21_memcpy((char *)(temp + start_index), (char *)str, n_str);
            s21_memcpy(((char *)temp + start_index + n_str),
                        ((char *)src + start_index), n_src - start_index);
            ((char *)temp)[n] = '\0';
        }
    }
    return temp;
}
