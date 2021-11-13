#include <check.h>
#include <signal.h>
#include <string.h>

#include "../s21_string.h"
#include "tests.h"

START_TEST(dFlagTest0) {
    char formatStr[100] = "|%d word|";
    char origStr[300] = "";
    char s21Str[300] = "";

    s21_sprintf(s21Str, formatStr, 300);
    sprintf(origStr, formatStr, 300);

    ck_assert(strcmp(s21Str, origStr) == 0);
}
END_TEST

START_TEST(dFlagTest1) {
    char formatStr[100] = "|%+010.5d word|";
    char origStr[300] = "";
    char s21Str[300] = "";

    s21_sprintf(s21Str, formatStr, 300);
    sprintf(origStr, formatStr, 300);

    ck_assert(strcmp(s21Str, origStr) == 0);
}
END_TEST

START_TEST(dFlagTest2) {
    char formatStr[100] = "|%#+- 0d word|";
    char origStr[300] = "";
    char s21Str[300] = "";

    s21_sprintf(s21Str, formatStr, 300);
    sprintf(origStr, formatStr, 300);

    ck_assert(strcmp(s21Str, origStr) == 0);
}
END_TEST

START_TEST(dFlagTest3) {
    char formatStr[100] = "|%+-+-+-+-+-+-d word|";
    char origStr[300] = "";
    char s21Str[300] = "";

    s21_sprintf(s21Str, formatStr, 300);
    sprintf(origStr, formatStr, 300);

    ck_assert(strcmp(s21Str, origStr) == 0);
}
END_TEST

START_TEST(dFlagTest4) {
    char formatStr[100] = "|%-+#  #   +     .30d word|";
    char origStr[300] = "";
    char s21Str[300] = "";

    s21_sprintf(s21Str, formatStr, 300);
    sprintf(origStr, formatStr, 300);

    ck_assert(strcmp(s21Str, origStr) == 0);
}
END_TEST

START_TEST(dFlagTest5) {
    char formatStr[100] = "|%*d word|";
    char origStr[300] = "";
    char s21Str[300] = "";

    s21_sprintf(s21Str, formatStr, 40, 300);
    sprintf(origStr, formatStr, 40, 300);

    ck_assert(strcmp(s21Str, origStr) == 0);
}
END_TEST

START_TEST(dFlagTest6) {
    char formatStr[100] = "|%*d wor\0d %*d %*d %*d|";
    char origStr[300] = "";
    char s21Str[300] = "";

    s21_sprintf(s21Str, formatStr, 40, 300, 3, 14, 15, 92, 6);
    sprintf(origStr, formatStr, 40, 300, 3, 14, 15, 92, 6);

    ck_assert(strcmp(s21Str, origStr) == 0);
}
END_TEST

START_TEST(dFlagTest7) {
    char formatStr[100] = "|% .*d word %*d %.*d % *d|";
    char origStr[300] = "";
    char s21Str[300] = "";

    s21_sprintf(s21Str, formatStr, 40, 300, 3, 14, 15, 92, 6);
    sprintf(origStr, formatStr, 40, 300, 3, 14, 15, 92, 6);

    ck_assert(strcmp(s21Str, origStr) == 0);
}
END_TEST

START_TEST(cSpecTest0) {
    char formatStr[100] = "|%c word|";
    char origStr[300] = "";
    char s21Str[300] = "";

    s21_sprintf(s21Str, formatStr, 'g');
    sprintf(origStr, formatStr, 'g');

    ck_assert(strcmp(s21Str, origStr) == 0);
}
END_TEST

START_TEST(cSpecTest1) {
    char formatStr[100] = "|%   +-#3.10c word|";
    char origStr[300] = "";
    char s21Str[300] = "";

    s21_sprintf(s21Str, formatStr, 'g');
    sprintf(origStr, formatStr, 'g');

    ck_assert(strcmp(s21Str, origStr) == 0);
}
END_TEST

START_TEST(iSpecTest0) {
    char formatStr[100] = "|%i word|";
    char origStr[300] = "";
    char s21Str[300] = "";

    s21_sprintf(s21Str, formatStr, 0364);
    sprintf(origStr, formatStr, 0364);

    ck_assert(strcmp(s21Str, origStr) == 0);
}
END_TEST

START_TEST(eSpecTest0) {
    char formatStr[100] = "%e word";
    int i;
    double d[] = {323.786e-303,
                  -123.456789,
                  42.0,
                  1234567.89012345,
                  1.00000000000000018,
                  555555.55555555555555555,
                  -888888888888888.8888888,
                  111111111111111111111111.2222222222,
                  0.085,
                  16.9};

    for (i = 0; i < 10; i++) {
        char s21Str[4000] = {0};
        s21_sprintf(s21Str, formatStr, d[i]);

        char origStr[4000] = {0};
        sprintf(origStr, formatStr, d[i]);

        ck_assert_msg(strcmp(s21Str, origStr) == 0, "test failed on i = %d", i);
    }
}
END_TEST

START_TEST(eSpecTest1) {
    char formatStr[100] = "%-+0.000e word";
    int i;
    double d[] = {323.786e-303,
                  -123.456789,
                  42.0,
                  1234567.89012345,
                  1.00000000000000018,
                  555555.55555555555555555,
                  -888888888888888.8888888,
                  111111111111111111111111.2222222222,
                  0.085,
                  16.9};

    for (i = 0; i < 10; i++) {
        char s21Str[4000] = {0};
        s21_sprintf(s21Str, formatStr, d[i]);

        char origStr[4000] = {0};
        sprintf(origStr, formatStr, d[i]);

        ck_assert_msg(strcmp(s21Str, origStr) == 0,
                      "test failed on i = %d, \ns21: |%s|, \norig: |%s|", i,
                      s21Str, origStr);
    }
}
END_TEST

TCase* CreateSprintfCase() {
    TCase* sprintfCase = tcase_create("sprintf case");

    tcase_add_test(sprintfCase, dFlagTest0);
    tcase_add_test(sprintfCase, dFlagTest1);
    tcase_add_test(sprintfCase, dFlagTest2);
    tcase_add_test(sprintfCase, dFlagTest3);
    tcase_add_test(sprintfCase, dFlagTest4);
    tcase_add_test(sprintfCase, dFlagTest5);
    tcase_add_test(sprintfCase, dFlagTest6);
    tcase_add_test(sprintfCase, dFlagTest7);

    tcase_add_test(sprintfCase, cSpecTest0);
    tcase_add_test(sprintfCase, cSpecTest1);

    tcase_add_test(sprintfCase, iSpecTest0);

    tcase_add_test(sprintfCase, eSpecTest0);
    tcase_add_test(sprintfCase, eSpecTest1);

    return sprintfCase;
}