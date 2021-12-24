#include "tests.h"

START_TEST(normalEqualTest) {
    char str1[100] = "aaa";
    char str2[100] = "aaa";
    char* origResult = memcpy(str1, "aaa", 3);
    char* s21Result = s21_memcpy(str2, "aaa", 3);
    ck_assert_msg(strcmp(s21Result, origResult) == 0,
                  "fail for memcpy(\"aaa\", \"aaa\"). orig:%s,  s21:%s",
                  origResult, s21Result);
}
END_TEST

START_TEST(normalLessTest) {
    char str1[100] = "abcde";
    char str2[100] = "abcde";
    char* origResult = memcpy(str1, "012", 3);
    char* s21Result = s21_memcpy(str2, "012", 3);
    ck_assert_msg(strcmp(s21Result, origResult) == 0,
                  "fail for memcpy(\"abcde\", \"012\"). orig:%s,  s21:%s",
                  origResult, s21Result);
}
END_TEST

START_TEST(normalMoreTest) {
    char str1[100] = "abc";
    char str2[100] = "abc";
    char* origResult = memcpy(str1, "01234", 5);
    char* s21Result = s21_memcpy(str2, "01234", 5);
    ck_assert_msg(strcmp(s21Result, origResult) == 0,
                  "fail for memcpy(\"abc\", \"01234\"). orig:%s,  s21:%s",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg1EmptyTest) {
    char str1[100] = "\0";
    char str2[100] = "\0";
    char* origResult = memcpy(str1, "01234", 5);
    char* s21Result = s21_memcpy(str2, "01234", 5);
    ck_assert_msg(strcmp(s21Result, origResult) == 0,
                  "fail for memcpy(\"0\", \"01234\"). orig:%s,  s21:%s",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg2EmptyTest) {
    char str1[100] = "abc";
    char str2[100] = "abc";
    char* origResult = memcpy(str1, "", 1);
    char* s21Result = s21_memcpy(str2, "", 1);
    ck_assert_msg(strcmp(s21Result, origResult) == 0,
                  "fail for memcpy(\"abc\", \"\"). orig:%s,  s21:%s",
                  origResult, s21Result);
}
END_TEST

TCase* CreateMemcpyCase() {
    TCase* memcpyCase = tcase_create("memcpy case");

    tcase_add_test(memcpyCase, normalEqualTest);
    tcase_add_test(memcpyCase, normalLessTest);
    tcase_add_test(memcpyCase, normalMoreTest);
    tcase_add_test(memcpyCase, arg1EmptyTest);
    tcase_add_test(memcpyCase, arg2EmptyTest);

    return memcpyCase;
}
