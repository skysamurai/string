#include <check.h>
#include <signal.h>
#include <string.h>

#include "../s21_string.h"
#include "tests.h"

START_TEST(normalTest) {
    char* origToken = S21_NULL;
    char origString[] = "a string, of, ,tokens\0,after null terminator";

    char* s21Token = S21_NULL;
    char s21String[] = "a string, of, ,tokens\0,after null terminator";

    origToken = strtok(origString, ",");
    s21Token = s21_strtok(s21String, ",");

    int i = 0;
    do {
        origToken = strtok(S21_NULL, ",");
        s21Token = s21_strtok(S21_NULL, ",");
        i++;
    } while (origToken != S21_NULL &&
             s21Token != S21_NULL);  // prevent strcmp segfault

    ck_assert_msg(origToken == S21_NULL && s21Token == S21_NULL,
                  "fail 3: orig Token:|%s|, s21 Token: |%s|",
                  origToken != S21_NULL ? origToken : "NULL",
                  s21Token != S21_NULL ? s21Token : "NULL");
}
END_TEST

START_TEST(noInitialStringTest) {  // must NOT create segfault
    char* origToken = S21_NULL;
    char origString[] = "a string, of, ,tokens\0,after null terminator";

    char* s21Token = S21_NULL;
    char s21String[] = "a string, of, ,tokens\0,after null terminator";

    origToken = strtok(origString, ",");
    s21Token = s21_strtok(s21String, ",");

    // ck_assert(s21Token == S21_NULL && origToken == S21_NULL);

    int i = 0;
    do {
        if (s21Token != S21_NULL && origToken != S21_NULL) {
            ck_assert_msg(strcmp(origToken, s21Token) == 0,
                          "fail 1: orig Token:|%s|, s21 Token: |%s|", origToken,
                          s21Token);
            ck_assert_msg(strcmp(origString, s21String) == 0,
                          "fail 2: orig Token:|%s|, s21 Token: |%s|",
                          origToken != S21_NULL ? origToken : "NULL",
                          s21Token != S21_NULL ? s21Token : "NULL");
        }

        origToken = strtok(S21_NULL, ",");
        s21Token = s21_strtok(S21_NULL, ",");
        i++;
    } while (origToken != S21_NULL &&
             s21Token != S21_NULL);  // prevent strcmp segfault

    ck_assert_msg(origToken == S21_NULL && s21Token == S21_NULL,
                  "fail 3: orig Token:|%s|, s21 Token: |%s|",
                  origToken != S21_NULL ? origToken : "NULL",
                  s21Token != S21_NULL ? s21Token : "NULL");
}
END_TEST

TCase* CreateStrtokCase() {
    TCase* strtokCase = tcase_create("strtok case");

    tcase_add_test(strtokCase, normalTest);
    tcase_add_test(strtokCase, noInitialStringTest);

    return strtokCase;
}
