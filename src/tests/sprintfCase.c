#include <check.h>
#include <signal.h>
#include <string.h>

#include "../s21_string/s21_string.h"
#include "tests.h"

START_TEST(bgreydonTest) {
    char origStr[100] = "";
    char s21Str[100] = "";

    s21_sprintf(s21Str, "|%d word|", 300);
    sprintf(origStr, "|%d word|", 300);

    ck_assert(strcmp(s21Str, origStr) == 0);
}
END_TEST

TCase* CreateSprintfCase() {
    TCase* sprintfCase = tcase_create("sprintf case");

    tcase_add_test(sprintfCase, bgreydonTest);

    return sprintfCase;
}