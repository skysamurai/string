#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
    char *res = S21_NULL;
    s21_size_t len = s21_strlen(needle);
    if (len) {
        for (; *haystack && !res; haystack++) {
            if (!s21_strncmp(haystack, needle, len)) {
                res = (char *)haystack;
            }
        }
    } else {
        res = (char *)haystack;
    }
    return res;
}
