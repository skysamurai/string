#include <check.h>
#include <signal.h>
#include <string.h>

#include "s21_string.h"
#include "tests.h"

START_TEST(normalEqualTest) {
    int origResult = strcmp("aaa", "aaa");
    int s21Result = s21_strcmp("aaa", "aaa");

    ck_assert_msg(s21Result == origResult,
                  "fail for strcmp(\"aaa\", \"aaa\"). orig:%d,  s21:%d",
                  origResult, s21Result);
}
END_TEST

START_TEST(normalLessTest) {
    int origResult = strcmp("aaa", "aba");
    int s21Result = s21_strcmp("aaa", "aba");

    ck_assert_msg(s21Result == origResult,
                  "fail for strcmp(\"aaa\", \"aba\"). orig:%d,  s21:%d",
                  origResult, s21Result);
}
END_TEST

START_TEST(normalMoreTest) {
    int origResult = strcmp("aba", "aaa");
    int s21Result = s21_strcmp("aba", "aaa");

    ck_assert_msg(s21Result == origResult,
                  "fail for strcmp(\"aba\", \"aaa\"). orig:%d,  s21:%d",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg1EmptyTest) {
    int origResult = strcmp("", "aaa");
    int s21Result = s21_strcmp("", "aaa");

    ck_assert_msg(s21Result == origResult,
                  "fail for strcmp(\"\", \"aaa\"). orig:%d,  s21:%d",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg1NULLTest) {  // must return SIGSEGV
    s21_strcmp(S21_NULL, "aaa");
}
END_TEST

START_TEST(arg2EmptyTest) {
    int origResult = strcmp("aaa", "");
    int s21Result = s21_strcmp("aaa", "");

    ck_assert_msg(s21Result == origResult,
                  "fail for strcmp(\"aaa\", \"\"). orig:%d,  s21:%d",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg2NULLTest) {  // must return SIGSEGV
    s21_strcmp("aaa", S21_NULL);
}
END_TEST

START_TEST(arg3TooMuchTest) {
    int origResult = strcmp("aba", "aaa");
    int s21Result = s21_strcmp("aba", "aaa");

    ck_assert_msg(s21Result == origResult,
                  "fail for strcmp(\"aba\", \"aaa\"). orig:%d,  s21:%d",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg3ZeroTest) {
    int origResult = strcmp("baa", "aaa");
    int s21Result = s21_strcmp("baa", "aaa");

    ck_assert_msg(s21Result == origResult,
                  "fail for strcmp(\"baa\", \"aaa\", 0). orig:%d,  s21:%d",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg3NULLTest) {
    s21_strcmp("aaa", "baa");
}
END_TEST

TCase* CreateStrcmpCase() {
    TCase* strcmpCase = tcase_create("strcmpCase");

    tcase_add_test(strcmpCase, normalEqualTest);
    tcase_add_test(strcmpCase, normalLessTest);
    tcase_add_test(strcmpCase, normalMoreTest);
    tcase_add_test(strcmpCase, arg3TooMuchTest);
    tcase_add_test(strcmpCase, arg3ZeroTest);
    tcase_add_test(strcmpCase, arg1EmptyTest);
    tcase_add_test(strcmpCase, arg2EmptyTest);

    tcase_add_test_raise_signal(strcmpCase, arg1NULLTest, SIGSEGV);
    tcase_add_test_raise_signal(strcmpCase, arg2NULLTest, SIGSEGV);
    tcase_add_test(strcmpCase, arg3NULLTest);

    return strcmpCase;
}

// arg Null

