#include <check.h>
#include <signal.h>
#include <string.h>

#include "../s21_string/s21_string.h"
#include "tests.h"

START_TEST(normalEqualTest) {
    int origResult = strncmp("aaa", "aaa", 3);
    int s21Result = s21_strncmp("aaa", "aaa", 3);

    ck_assert_msg(s21Result == origResult,
                  "fail for strncmp(\"aaa\", \"aaa\", 3). orig:%d,  s21:%d",
                  origResult, s21Result);
}
END_TEST

START_TEST(normalLessTest) {
    int origResult = strncmp("aaa", "aba", 3);
    int s21Result = s21_strncmp("aaa", "aba", 3);

    ck_assert_msg(s21Result == origResult,
                  "fail for strncmp(\"aaa\", \"aba\", 3). orig:%d,  s21:%d",
                  origResult, s21Result);
}
END_TEST

START_TEST(normalMoreTest) {
    int origResult = strncmp("aba", "aaa", 3);
    int s21Result = s21_strncmp("aba", "aaa", 3);

    ck_assert_msg(s21Result == origResult,
                  "fail for strncmp(\"aba\", \"aaa\", 3). orig:%d,  s21:%d",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg1EmptyTest) {
    int origResult = strncmp("", "aaa", 3);
    int s21Result = s21_strncmp("", "aaa", 3);

    ck_assert_msg(s21Result == origResult,
                  "fail for strncmp(\"\", \"aaa\", 3). orig:%d,  s21:%d",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg1NULLTest) {  // must return SIGSEGV
    s21_strncmp(S21_NULL, "aaa", 3);
}
END_TEST

START_TEST(arg2EmptyTest) {
    int origResult = strncmp("aaa", "", 3);
    int s21Result = s21_strncmp("aaa", "", 3);

    ck_assert_msg(s21Result == origResult,
                  "fail for strncmp(\"aaa\", \"\", 3). orig:%d,  s21:%d",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg2NULLTest) {  // must return SIGSEGV
    s21_strncmp("aaa", S21_NULL, 3);
}
END_TEST

START_TEST(arg3TooMuchTest) {
    int origResult = strncmp("aba", "aaa", 333);
    int s21Result = s21_strncmp("aba", "aaa", 333);

    ck_assert_msg(s21Result == origResult,
                  "fail for strncmp(\"aba\", \"aaa\", 333). orig:%d,  s21:%d",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg3ZeroTest) {
    int origResult = strncmp("baa", "aaa", 0);
    int s21Result = s21_strncmp("baa", "aaa", 0);

    ck_assert_msg(s21Result == origResult,
                  "fail for strncmp(\"baa\", \"aaa\", 0). orig:%d,  s21:%d",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg3NULLTest) {  // must return SIGSEGV
    int* nullint = S21_NULL;

    s21_strncmp("aaa", "baa", *nullint);
}
END_TEST

TCase* CreateStrncmpCase() {
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
    tcase_add_test_raise_signal(strncmpCase, arg3NULLTest, SIGSEGV);

    return strncmpCase;
}

// arg Null
