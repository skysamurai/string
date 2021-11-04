#include <check.h>
#include <signal.h>
#include <string.h>

#include "../s21_string/s21_string.h"
#include "tests.h"

START_TEST(normalTest) {
    char charsToTrim[] = {'*', ' ', '\''};
    char* banner = "*** Much Ado About Nothing ***";
    char* result = s21_trim(banner, charsToTrim);
    ck_assert(strcmp(result, "Much Ado About Nothing") == 0);
}
END_TEST

START_TEST(arg1EmptyTest) {
    char charsToTrim[] = {'*', ' ', '\''};
    char* banner = "";
    char* result = s21_trim(banner, charsToTrim);
    ck_assert(strcmp(result, "") == 0);
}
END_TEST

START_TEST(arg1NULLTest) {  // throws runtime exeption in C#
    char charsToTrim[] = {'*', ' ', '\''};
    char* banner = S21_NULL;
    s21_trim(banner, charsToTrim);
}
END_TEST

START_TEST(arg2EmptyTest) {
    char charsToTrim[] = {};
    char* banner = "*** Much Ado About Nothing ***";
    char* result = s21_trim(banner, charsToTrim);
    ck_assert(strcmp(result, "*** Much Ado About Nothing ***") == 0);
}
END_TEST

START_TEST(arg2NULLTest) {
    char* banner = "*** Much Ado About Nothing ***";
    char* result = s21_trim(banner, S21_NULL);
    ck_assert(strcmp(result, "*** Much Ado About Nothing ***") == 0);
}
END_TEST

START_TEST(argsNULLTest) {  // throws runtime exeption in C#
    ck_assert(s21_trim(S21_NULL, S21_NULL) == S21_NULL);
}
END_TEST

TCase* CreateTrimCase() {
    TCase* trimCase = tcase_create("trim case");
    tcase_add_test(trimCase, normalTest);
    tcase_add_test(trimCase, arg1EmptyTest);
    tcase_add_test_raise_signal(trimCase, arg1NULLTest, SIGSEGV);
    tcase_add_test(trimCase, arg2EmptyTest);
    tcase_add_test(trimCase, arg2NULLTest);
    tcase_add_test(trimCase, argsNULLTest);

    return trimCase;
}