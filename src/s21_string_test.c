#include <stdio.h>
#include <stdlib.h>
#include "s21_string.h"
#define n_char 25

// TEST C11 FILE

void s21_strcmp_test();
void s21_strcpy_test();

int main(void) {
    printf("==========NEW_RUN=============\n\n");
    s21_strcpy_test();
}

void s21_strcmp_test() {
    char string_test_1[3][30] = {{"Abcd12345#"},
                                      {"1234\0abс"},
                                      {"1234abc\0"}};
    char string_out_1[3][30] = {{"Abcd12345#"},
                                     {"1234\0abс"},
                                     {"1234abc\0"}};
    for (size_t i = 0; i < 3; ++i) {
            printf("%s ", string_test_1[i]);
            printf("%s ", string_out_1[i]);
            if (s21_strcmp(string_test_1[i], string_out_1[i]) != -1) {
                printf("SUCCESS\n");
            } else {
                printf("FAIL\n");
                }
    }
}

void s21_strcpy_test() {
    char string_test_1[3][30] = {{"\0"},
                                      {""},
                                      {"12"}};
    char string_out_1[3][30] = {{"Abcd12345#"},
                                     {"1234\0abс"},
                                     {"1234abc\0"}};
    for (size_t i = 0; i < 3; ++i) {
        printf("%s ", string_out_1[i]);
        s21_strcpy(string_out_1[i], string_test_1[i]);
        printf("%s ", string_out_1[i]);
        if (s21_strcmp(string_test_1[i], string_out_1[i]) != -1) {
                printf("SUCCESS\n");
            } else {
                printf("FAIL\n");
                }
    }
}
