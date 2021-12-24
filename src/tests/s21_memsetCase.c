#include "tests.h"

START_TEST(normalEqualTest) {
    char str1[100] = "aaa";
    char str2[100] = "aaa";
    char* origResult = memset(str1, '1', 3);
    char* s21Result = s21_memset(str2, '1', 3);
    ck_assert_msg(strcmp(s21Result, origResult) == 0,
                  "fail for memset(\"aaa\", \"aaa\"). orig:%s,  s21:%s",
                  origResult, s21Result);
}
END_TEST

START_TEST(normalLessTest) {
    char str1[100] = "abcde";
    char str2[100] = "abcde";
    char* origResult = memset(str1, '1', 3);
    char* s21Result = s21_memset(str2, '1', 3);
    ck_assert_msg(strcmp(s21Result, origResult) == 0,
                  "fail for memset(\"abcde\", \"012\"). orig:%s,  s21:%s",
                  origResult, s21Result);
}
END_TEST

START_TEST(normalMoreTest) {
    char str1[100] = "abc";
    char str2[100] = "abc";
    char* origResult = memset(str1, '1', 5);
    char* s21Result = s21_memset(str2, '1', 5);
    ck_assert_msg(strcmp(s21Result, origResult) == 0,
                  "fail for memset(\"abc\", \"01234\"). orig:%s,  s21:%s",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg1EmptyTest) {
    char str1[100] = "\0";
    char str2[100] = "\0";
    char* origResult = memset(str1, '1', 5);
    char* s21Result = s21_memset(str2, '1', 5);
    ck_assert_msg(strcmp(s21Result, origResult) == 0,
                  "fail for memset(\"0\", \"01234\"). orig:%s,  s21:%s",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg2EmptyTest) {
    char str1[100] = "abc";
    char str2[100] = "abc";
    char* origResult = memset(str1, '\0', 1);
    char* s21Result = s21_memset(str2, '\0', 1);
    ck_assert_msg(strcmp(s21Result, origResult) == 0,
                  "fail for memset(\"abc\", \"\"). orig:%s,  s21:%s",
                  origResult, s21Result);
}
END_TEST

TCase* CreateMemsetCase() {
    TCase* memsetCase = tcase_create("memset case");

    tcase_add_test(memsetCase, normalEqualTest);
    tcase_add_test(memsetCase, normalLessTest);
    tcase_add_test(memsetCase, normalMoreTest);
    tcase_add_test(memsetCase, arg1EmptyTest);
    tcase_add_test(memsetCase, arg2EmptyTest);

    return memsetCase;
}
