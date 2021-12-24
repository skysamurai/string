#include "s21_string.h"

s21_size_t s21_strlen(const char *str) {
    return (s21_strchr(str, 0) - str);
}
