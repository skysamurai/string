#include <check.h>
#include <signal.h>
#include <string.h>

#include "../s21_string/s21_string.h"
#include "tests.h"

START_TEST(normalEqualTest) {
    int origResult = strlen("aaa");
    int s21Result = s21_strlen("aaa");

    ck_assert_msg(s21Result == origResult,
                  "fail for strlen(\"aaa\", \"aaa\"). orig:%d,  s21:%d",
                  origResult, s21Result);
}
END_TEST

START_TEST(normalLessTest) {
    int origResult = strlen("a\0a");
    int s21Result = s21_strlen("a\0a");

    ck_assert_msg(s21Result == origResult,
                  "fail for strlen(\"a\0a\", \"a\0a\"). orig:%d,  s21:%d",
                  origResult, s21Result);
}
END_TEST

START_TEST(normalMoreTest) {
    int origResult = strlen("01234567890123456789012345678901234567890123456789");
    int s21Result = s21_strlen("01234567890123456789012345678901234567890123456789");

    ck_assert_msg(s21Result == origResult,
                  "fail for strlen(\"len50\", \"len50\"). orig:%d,  s21:%d",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg1EmptyTest) {
    int origResult = strlen("");
    int s21Result = s21_strlen("");

    ck_assert_msg(s21Result == origResult,
                  "fail for strlen(\"\", \"\"). orig:%d,  s21:%d",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg1NULLTest) {  // must return SIGSEGV
    s21_strlen(S21_NULL);
}
END_TEST

TCase* CreateStrlenCase() {
    TCase* strlenCase = tcase_create("strlenCase");

    tcase_add_test(strlenCase, normalEqualTest);
    tcase_add_test(strlenCase, normalLessTest);
    tcase_add_test(strlenCase, normalMoreTest);
    tcase_add_test(strlenCase, arg1EmptyTest);

    tcase_add_test_raise_signal(strlenCase, arg1NULLTest, SIGSEGV);
    return strlenCase;
}

// arg Null
