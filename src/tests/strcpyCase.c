#include <check.h>
#include <signal.h>
#include <string.h>

#include "../s21_string/s21_string.h"
#include "tests.h"

START_TEST(normalEqualTest) {
    char* origResult;
    char* s21Result;
    const char* str2[4];
    str2[4] = "hello";
    origResult = strcpy("aaa", str2);
    s21Result  = s21_strcpy("aaa", str2);

    // ck_assert_msg(s21Result == origResult,
    //               "fail for strcpy(\"aaa\", \"aaa\"). orig:%p,  s21:%p",
    //               origResult, s21Result);
    printf(">>>>>>strcpy>>>>%p", origResult);
    printf(">>>>>>strcpy>>>>%p", s21Result);
    ck_assert(s21Result == origResult);
}
END_TEST

START_TEST(normalLessTest) {
    char* origResult = strcpy("aaa", "aba");
    char* s21Result = s21_strcpy("aaa", "aba");

    ck_assert_msg(s21Result == origResult,
                  "fail for strcpy(\"aaa\", \"aba\"). orig:%d,  s21:%d",
                  origResult, s21Result);
}
END_TEST

START_TEST(normalMoreTest) {
    char* origResult = strcpy("aba", "aaa");
    char* s21Result = s21_strcpy("aba", "aaa");

    ck_assert_msg(s21Result == origResult,
                  "fail for strcpy(\"aba\", \"aaa\"). orig:%d,  s21:%d",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg1EmptyTest) {
    char* origResult = strcpy("1234", "aaa"); ///  !!!!!!!!!!!
    char* s21Result = s21_strcpy("1234", "aaa");

    ck_assert_msg(*s21Result == *origResult,
                  "fail for strcpy(\"\", \"aaa\"). orig:%d,  s21:%d",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg1NULLTest) {  // must return SIGSEGV
    s21_strcpy(S21_NULL, "aaa");
}
END_TEST

START_TEST(arg2EmptyTest) {
    char* origResult = strcpy("aaa", "");
    char* s21Result = s21_strcpy("aaa", "");

    ck_assert_msg(s21Result == origResult,
                  "fail for strcpy(\"aaa\", \"\"). orig:%d,  s21:%d",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg2NULLTest) {  // must return SIGSEGV
    s21_strcpy("aaa", S21_NULL);
}
END_TEST

TCase* CreateStrcpyCase() {
    TCase* strcpyCase = tcase_create("strcpyCase");

    tcase_add_test(strcpyCase, normalEqualTest);
    tcase_add_test(strcpyCase, normalLessTest);
    tcase_add_test(strcpyCase, normalMoreTest);
    tcase_add_test(strcpyCase, arg1EmptyTest);
    tcase_add_test(strcpyCase, arg2EmptyTest);

    tcase_add_test_raise_signal(strcpyCase, arg1NULLTest, SIGSEGV);
    tcase_add_test_raise_signal(strcpyCase, arg2NULLTest, SIGSEGV);

    return strcpyCase;
}

// arg Null

