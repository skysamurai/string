#include <stdio.h>
#include <stdlib.h>
#include "s21_string.h"

char *s21_strcpy(char *string, const char *string1) {
    size_t i = 0;
    while (string1[i] != 0) {
        string[i] = string1[i];
        ++i;
    }
return string;
}

int s21_strcmp(const char *string, const char *string1) {
    int i = 0;
    int flag = 0;
    while ((flag != -1) && (string[i] != '\0') && ((string1[i] != '\0'))) {
      printf("%c %c ", string[i], string1[i]);
        if (string[i] != string1[i])
            flag = -1;
        else
            ++i;
    }
return flag;
}

size_t s21_strlen(const char *string) {
    size_t i = 0;
    while (string[i] != 0) ++i;
return i;
}
