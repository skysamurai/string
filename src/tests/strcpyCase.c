#include <check.h>
#include <signal.h>
#include <string.h>

#include "../s21_string.h"
#include "tests.h"

START_TEST(normalEqualTest) {
    char str1[100] = "aaa";
    char str2[100] = "aaa";
    char* origResult = strcpy(str1, "aaa");
    char* s21Result = s21_strcpy(str2, "aaa");
    ck_assert_msg(strcmp(s21Result, origResult) == 0,
                  "fail for strcpy(\"aaa\", \"aaa\"). orig:%s,  s21:%s",
                  origResult, s21Result);
}
END_TEST

START_TEST(normalLessTest) {
    char str1[100] = "abcde";
    char str2[100] = "abcde";
    char* origResult = strcpy(str1, "012");
    char* s21Result = s21_strcpy(str2, "012");
    ck_assert_msg(strcmp(s21Result, origResult) == 0,
                  "fail for strcpy(\"abcde\", \"012\"). orig:%s,  s21:%s",
                  origResult, s21Result);
}
END_TEST

START_TEST(normalMoreTest) {
    char str1[100] = "abc";
    char str2[100] = "abc";
    char* origResult = strcpy(str1, "01234");
    char* s21Result = s21_strcpy(str2, "01234");
    ck_assert_msg(strcmp(s21Result, origResult) == 0,
                  "fail for strcpy(\"abc\", \"01234\"). orig:%s,  s21:%s",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg1EmptyTest) {
    char str1[100] = "\0";
    char str2[100] = "\0";
    char* origResult = strcpy(str1, "01234");
    char* s21Result = s21_strcpy(str2, "01234");
    ck_assert_msg(strcmp(s21Result, origResult) == 0,
                    "fail for strcpy(\"0\", \"01234\"). orig:%s,  s21:%s",
                    origResult, s21Result);
    }
END_TEST

START_TEST(arg2EmptyTest) {
    char str1[100] = "abc";
    char str2[100] = "abc";
    char* origResult = strcpy(str1, "");
    char* s21Result = s21_strcpy(str2, "");
    ck_assert_msg(strcmp(s21Result, origResult) == 0,
                  "fail for strcpy(\"abc\", \"\"). orig:%s,  s21:%s",
                  origResult, s21Result);
}
END_TEST

// START_TEST(arg1NULLTest) {  // must return SIGSEGV
//     s21_strcpy(S21_NULL, "aaa");
// }
// END_TEST

// START_TEST(arg2NULLTest) {  // must return SIGSEGV
//     s21_strcpy("aaa", S21_NULL);
// }
// END_TEST

TCase* CreateStrcpyCase() {
    TCase* strcpyCase = tcase_create("strcpyCase");

    tcase_add_test(strcpyCase, normalEqualTest);
    tcase_add_test(strcpyCase, normalLessTest);
    tcase_add_test(strcpyCase, normalMoreTest);
    tcase_add_test(strcpyCase, arg1EmptyTest);
    tcase_add_test(strcpyCase, arg2EmptyTest);

    // tcase_add_test_raise_signal(strcpyCase, arg1NULLTest, SIGSEGV);
    // tcase_add_test_raise_signal(strcpyCase, arg2NULLTest, SIGSEGV);

return strcpyCase;
}

// arg Null
