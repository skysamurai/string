#include <check.h>
#include <signal.h>
#include <string.h>

#include "../s21_string.h"
#include "tests.h"

START_TEST(normalTest) {
    char* origToken;
    char origString[] = "a string, of, ,tokens\0,after null terminator";

    char* s21Token;
    char s21String[] = "a string, of, ,tokens\0,after null terminator";

    origToken = strtok(origString, ",");
    s21Token = s21_strtok(s21String, ",");

    ck_assert(strcmp(origToken, s21Token) == 0);
    ck_assert(strcmp(origString, s21String) == 0);
    do {
        origToken = strtok(NULL, ",");
        s21Token = s21_strtok(NULL, ",");

        ck_assert(strcmp(origToken, s21Token) == 0);
        ck_assert(strcmp(origString, s21String) == 0);

    } while (origToken && s21Token);
    ck_assert(strcmp(origToken, s21Token) == 0);
    ck_assert(strcmp(origString, s21String) == 0);
}
END_TEST

TCase* CreateStrtokCase() {
    TCase* strtokCase = tcase_create("strtok case");

    tcase_add_test(strtokCase, normalTest);

    return strtokCase;
}