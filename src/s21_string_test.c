#include <stdio.h>
#include <stdlib.h>
#include "s21_string.h"
#define n_char 25

// TEST C11 FILE

void s21_strcmp_test();
void s21_strcpy_test();
void s21_strlen_test();

int main(void) {
    printf("==========NEW_RUN=============\n\n");
    s21_strcpy_test();
    s21_strlen_test();
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

void s21_strlen_test() {
    char string_test[4][30] = {{"\0abcdef1"}, {"ab\0c"}, {"abc\0"}, {"abcd123"}};
    size_t string_out[4] = {0, 2, 3, 7};
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            printf("%c", string_test[i][j]);
            if (!string_test[i][j])
                printf(" ");
        }
            printf(" %zu ", string_out[i]);

            if (s21_strlen(string_test[i]) == string_out[i]) {
                printf("SUCCESS\n");
            } else {
                printf("FAIL\n");
                }
    }
}