#include "tests.h"

START_TEST(normalEqualTest) {
    char str1[100] = "aaa";
    char str2[100] = "aaa";
    char* origResult = strncpy(str1, "aaa", 4);
    char* s21Result = s21_strncpy(str2, "aaa", 4);

    ck_assert_msg(strcmp(s21Result, origResult) == 0,
                  "fail for strncpy(\"aaa\", \"aaa\", 4). orig:%s,  s21:%s",
                  origResult, s21Result);
}
END_TEST

START_TEST(normalLessTest) {
    char str1[100] = "aaa";
    char str2[100] = "aaa";
    char* origResult = strncpy(str1, "123", 4);
    char* s21Result = s21_strncpy(str2, "123", 4);
    ck_assert_msg(strcmp(s21Result, origResult) == 0,
                  "fail for strncpy(\"aaa\", \"123\",4). orig:%s,  s21:%s",
                  origResult, s21Result);
}
END_TEST

START_TEST(normalMoreTest) {
    char str1[100] = "aaa";
    char str2[100] = "aaa";
    char* origResult = strncpy(str1, "12345", 6);
    char* s21Result = s21_strncpy(str2, "12345", 6);

    ck_assert_msg(strcmp(s21Result, origResult) == 0,
                  "fail for strncpy(\"aba\", \"12345\", 6). orig:%s,  s21:%s",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg1EmptyTest) {
    char str1[100] = "\0";
    char str2[100] = "\0";
    char* origResult = strncpy(str1, "aaa", 4);
    char* s21Result = s21_strncpy(str2, "aaa", 4);
    ck_assert_msg(strcmp(s21Result, origResult) == 0,
                  "fail for strncpy(\"\", \"aaa\", 3). orig:%s,  s21:%s",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg2EmptyTest) {
    char str1[100] = "aaa";
    char str2[100] = "aaa";
    char* origResult = strncpy(str1, "", 4);
    char* s21Result = s21_strncpy(str2, "", 4);
    ck_assert_msg(strcmp(s21Result, origResult) == 0,
                  "fail for strncpy(\"aaa\", \"\", 4). orig:%s,  s21:%s",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg3TooMuchTest) {
    char str1[1000] = "aaa";
    char str2[1000] = "aaa";
    char* origResult = strncpy(str1, "123", 333);
    char* s21Result = s21_strncpy(str2, "123", 333);

    ck_assert_msg(strcmp(s21Result, origResult) == 0,
                  "fail for strncpy(\"aaa\", \"123\", 333). orig:%s,  s21:%s",
                  origResult, s21Result);
}
END_TEST

TCase* CreateStrncpyCase() {
    TCase* strncpyCase = tcase_create("strncpyCase");

    tcase_add_test(strncpyCase, normalEqualTest);
    tcase_add_test(strncpyCase, normalLessTest);
    tcase_add_test(strncpyCase, normalMoreTest);
    tcase_add_test(strncpyCase, arg3TooMuchTest);
    tcase_add_test(strncpyCase, arg1EmptyTest);
    tcase_add_test(strncpyCase, arg2EmptyTest);

    return strncpyCase;
}
