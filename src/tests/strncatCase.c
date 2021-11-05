#include <check.h>
#include <signal.h>
#include <string.h>

#include "../s21_string.h"
#include "tests.h"

START_TEST(normalEqualTest) {
    ck_assert(s21_strncmp("aaa", "aaa", 3) == strncmp("aaa", "aaa", 3));
}
END_TEST

START_TEST(normalLessTest) {
    ck_assert(s21_strncmp("aaa", "aba", 3) == strncmp("aaa", "aba", 3));
}
END_TEST

START_TEST(normalMoreTest) {
    ck_assert(s21_strncmp("aba", "aaa", 3) == strncmp("aba", "aaa", 3));
}
END_TEST

START_TEST(arg3TooMuchTest) {
    ck_assert(s21_strncmp("aba", "aaa", 333) == strncmp("aba", "aaa", 333));
}
END_TEST

START_TEST(arg3ZeroTest) {
    ck_assert(s21_strncmp("baa", "aaa", 0) == strncmp("baa", "aaa", 0));
}
END_TEST

START_TEST(arg1EmptyTest) {
    ck_assert(s21_strncmp("", "aaa", 3) == strncmp("", "aaa", 3));
}
END_TEST

START_TEST(arg2EmptyTest) {
    ck_assert(s21_strncmp("aaa", "", 3) == strncmp("aaa", "", 3));
}
END_TEST

START_TEST(arg1NULLTest) {  // must return SIGSEGV
    s21_strncmp(S21_NULL, "aaa", 3);
}
END_TEST

START_TEST(arg2NULLTest) {  // must return SIGSEGV
    s21_strncmp("aaa", S21_NULL, 3);
}
END_TEST

TCase* CreatestrncmpCase() {
    TCase* strncmpCase = tcase_create("strncmpCase");

    tcase_add_test(strncmpCase, normalEqualTest);
    tcase_add_test(strncmpCase, normalLessTest);
    tcase_add_test(strncmpCase, normalMoreTest);
    tcase_add_test(strncmpCase, arg3TooMuchTest);
    tcase_add_test(strncmpCase, arg3ZeroTest);
    tcase_add_test(strncmpCase, arg1EmptyTest);
    tcase_add_test(strncmpCase, arg2EmptyTest);

    tcase_add_test_raise_signal(strncmpCase, arg1NULLTest, SIGSEGV);
    tcase_add_test_raise_signal(strncmpCase, arg2NULLTest, SIGSEGV);

    return strncmpCase;
}