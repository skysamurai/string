#include <check.h>
#include <signal.h>
#include <string.h>

#include "../s21_string.h"
#include "tests.h"

START_TEST(dFlagTest0) {
    char formatStr[100] = "|%d word|";
    char origStr[100] = "";
    char s21Str[100] = "";

    s21_sprintf(s21Str, formatStr, 300);
    sprintf(origStr, formatStr, 300);

    ck_assert(strcmp(s21Str, origStr) == 0);
}
END_TEST

START_TEST(dFlagTest1) {
    char formatStr[100] = "|%+010.5d word|";
    char origStr[100] = "";
    char s21Str[100] = "";

    s21_sprintf(s21Str, formatStr, 300);
    sprintf(origStr, formatStr, 300);

    ck_assert(strcmp(s21Str, origStr) == 0);
}
END_TEST

TCase* CreateSprintfCase() {
    TCase* sprintfCase = tcase_create("sprintf case");

    tcase_add_test(sprintfCase, dFlagTest0);
    tcase_add_test(sprintfCase, dFlagTest1);

    return sprintfCase;
}