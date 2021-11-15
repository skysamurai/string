#include <check.h>
#include <signal.h>
#include <string.h>

#include "../s21_string.h"
#include "tests.h"

START_TEST(normalEqualTest) {
    char str1[100] = "aaa";
    char str2[100] = "aaa";
    char*  origResult = memmove(str1, "aaa", 3);
    char*  s21Result = s21_memmove(str2, "aaa", 3);

    ck_assert_msg(strcmp(s21Result, origResult) == 0,
                  "fail for memmove(\"aaa\", \"aaa\", 3). orig:%s,  s21:%s",
                  origResult, s21Result);
}
END_TEST



START_TEST(normalLessTest) {
    char str1[100] = "aaa";
    char str2[100] = "aaa";
    char*  origResult = memmove(str1, "12", 3);
    char*  s21Result = s21_memmove(str2, "12", 3);
    ck_assert_msg(strcmp(s21Result, origResult) == 0,
                  "fail for memmove(\"aaa\", \"123\",3). orig:%s,  s21:%s",
                  origResult, s21Result);
}
END_TEST

START_TEST(normalMoreTest) {
    char str1[100] = "aaa";
    char str2[100] = "aaa";
    char*  origResult = memmove(str1, "12345", 3);
    char*  s21Result = s21_memmove(str2, "12345", 3);

    ck_assert_msg(strcmp(s21Result, origResult) == 0,
                  "fail for memmove(\"aba\", \"12345\", 3). orig:%s,  s21:%s",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg1EmptyTest) { 
char str1[100] = "\0";
char str2[100] = "\0";
    char*  origResult = memmove(str1, "aaa", 3);
    char*  s21Result = s21_memmove(str2, "aaa", 3);
    ck_assert_msg(strcmp(s21Result, origResult) == 0,
                  "fail for memmove(\"\", \"aaa\", 3). orig:%s,  s21:%s",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg2EmptyTest) {
    char str1[100] = "aaa";
    char str2[100] = "aaa";
    char*  origResult = memmove(str1, "", 1);
    char*  s21Result = s21_memmove(str2, "", 1);
    ck_assert_msg(strcmp(s21Result, origResult) == 0,
                  "fail for memmove(\"aaa\", \"\", 3). orig:%s,  s21:%s",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg3TooMuchTest) {
    char str1[1000] = "aaa";
    char str2[1000] = "aaa";
    char*  origResult = memmove(str1, "123", 4);
    char*  s21Result = s21_memmove(str2, "123", 4);

    ck_assert_msg(strcmp(s21Result, origResult) == 0,
                  "fail for memmove(\"aaa\", \"123\", 333). orig:%s,  s21:%s",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg3ZeroTest) {
    char str1[100] = "aaa";
    char str2[100] = "aaa";
    char*  origResult = memmove(str1, "123", 0);
    char*  s21Result = s21_memmove(str2, "123", 0);

    ck_assert_msg(strcmp(s21Result, origResult) == 0,
                  "fail for memmove(\"aaa\", \"123\", 0). orig:%s,  s21:%s",
                  origResult, s21Result);
}
END_TEST

TCase* CreateMemmoveCase() {
    TCase* memmoveCase = tcase_create("memmoveCase");

    tcase_add_test(memmoveCase, normalEqualTest);
    tcase_add_test(memmoveCase, normalLessTest);
    tcase_add_test(memmoveCase, normalMoreTest);
    tcase_add_test(memmoveCase, arg3TooMuchTest);
    tcase_add_test(memmoveCase, arg3ZeroTest);
    tcase_add_test(memmoveCase, arg1EmptyTest);
    tcase_add_test(memmoveCase, arg2EmptyTest);

return memmoveCase;
}
