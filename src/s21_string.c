#include "s21_string.h"

#include <stdio.h>
#include <stdlib.h>

char *s21_strpbrk(const char *str1, const char *str2) {
    char *returnVal = NULL;
    int i = 0;
    while (str1[i] != '\0' && returnVal == NULL) {
        for (int j = 0; str2[j] != '\0'; j++) {
            if (str1[i] == str2[j]) {
                returnVal = ((char *)str1) + i;
                break;
            }
            printf("\n");
        }
        i++;
    }
    return returnVal;
}
