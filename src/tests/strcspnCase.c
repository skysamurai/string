#include <check.h>
#include <signal.h>
#include <string.h>

#include "../s21_string/s21_string.h"
#include "tests.h"

// TODO
START_TEST(normalEqualTest) {
    int origResult = strcspn ("1234567890","1234567890");
    int s21Result = s21_strcspn ("1234567890","1234567890");
    ck_assert_msg(s21Result == origResult, "fail for strcspn(\"1234567890\", \"1234567890\"). orig:%d,  s21:%d",
                  origResult, s21Result);
}
END_TEST

START_TEST(normalLessTest) {
    int origResult = strcspn ("1234567890","fcba73");
    int s21Result = s21_strcspn ("1234567890","fcba73");
    ck_assert_msg(s21Result == origResult, "fail for strcspn(\"1234567890\", \"fcba73\"). orig:%d,  s21:%d",
                  origResult, s21Result);
}
END_TEST

START_TEST(normalMoreTest) {
    int origResult = strcspn ("fcba73","1234567890");
    int s21Result = s21_strcspn ("fcba73","1234567890");
    ck_assert_msg(s21Result == origResult, "fail for strcspn(\"fcba73\", \"1234567890\"). orig:%d,  s21:%d",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg1EmptyTest) {
    int origResult = strcspn ("","1234567890");
    int s21Result = s21_strcspn ("","1234567890");
    ck_assert_msg(s21Result == origResult, "fail for strcspn(\"\", \"1234567890\"). orig:%d,  s21:%d",
                  origResult, s21Result);
END_TEST
}

START_TEST(arg2EmptyTest) {
    int origResult = strcspn ("1234567890","");
    int s21Result = s21_strcspn ("1234567890","");
    ck_assert_msg(s21Result == origResult, "fail for strcspn(\"1234567890\", \"\"). orig:%d,  s21:%d",
                  origResult, s21Result);
   // printf(">>>>>>strspn arg1MOreTest original/s21 %d = %d \n ", origResult, s21Result);
}
END_TEST

START_TEST(arg1NULLTest) {  // must return SIGSEGV
    s21_strcspn (S21_NULL,"1234567890");
}
END_TEST

START_TEST(arg2NULLTest) {  // must return SIGSEGV
    s21_strcmp(S21_NULL, "aaa");
    s21_strcspn ("1234567890",S21_NULL);
}
END_TEST

TCase* CreateStrcspnCase() {
    TCase* strcspnCase = tcase_create("strcspn case");
    tcase_add_test(strcspnCase, normalEqualTest);
    tcase_add_test(strcspnCase, normalLessTest);
    tcase_add_test(strcspnCase, normalMoreTest);
    tcase_add_test(strcspnCase, arg1EmptyTest);
    tcase_add_test(strcspnCase, arg2EmptyTest);
    tcase_add_test_raise_signal(strcspnCase, arg1NULLTest, SIGSEGV);
    tcase_add_test_raise_signal(strcspnCase, arg2NULLTest, SIGSEGV);
    return strcspnCase;
}