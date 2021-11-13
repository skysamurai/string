#include <check.h>
#include <signal.h>
#include <string.h>

#include "../s21_string.h"
#include "tests.h"

START_TEST(normalEqualTest_1_106) {
    //  for(int i = -200; i < 141; ++i)   // print list str error
    //      printf("%s\n", sys_errlist[i]);
    for (int errnum = 1; errnum < 41; errnum++) {
        if ((errnum == 41) || (errnum = 58)) ++errnum;
        const char* origResult = strerror(errnum);
        const char* s21Result = s21_strerror(errnum);
        ck_assert_msg(strcmp(s21Result, origResult) == 0,
                      "fail for strerror№ %d. orig:%s,  s21:%s", errnum,
                      origResult, s21Result);
    }
}
END_TEST

START_TEST(normalEqualTest41_58) {  /// edit!!! SIGSERV
    int errnum = 41;                // or 58
    const char* origResult = strerror(errnum);
    const char* s21Result = s21_strerror(errnum);
    ck_assert_msg(s21_strcmp(s21Result, origResult) == 0,  // sega
                  "fail for strerror№ %d. orig:%s,  s21:%s", errnum, origResult,
                  s21Result);
    // printf(">>>errN%d orig = %s || s21 = %s \n", errnum, origResult,
    // s21Result);
}
END_TEST

START_TEST(ZeroTest) {
    int errnum = 0;
    const char* origResult = strerror(errnum);
    const char* s21Result = s21_strerror(errnum);
    ck_assert_msg(strcmp(s21Result, origResult) == 0,
                  "fail for strerror№ %d. orig:%s,  s21:%s", errnum, origResult,
                  s21Result);
}
END_TEST

START_TEST(normalMoreTest) {
    for (int errnum = 105; errnum < 200; errnum++) {
        const char* origResult = strerror(errnum);
        const char* s21Result = s21_strerror(errnum);
        ck_assert_msg(strcmp(s21Result, origResult) == 0,
                      "fail for strerror№ %d. orig:|%s|,  s21:|%s|", errnum,
                      origResult, s21Result);
    }
}
END_TEST

START_TEST(normalLessTest) {
    for (int errnum = -200; errnum < 0; errnum++) {
        const char* origResult = strerror(errnum);
        const char* s21Result = s21_strerror(errnum);
        ck_assert_msg(strcmp(s21Result, origResult) == 0,
                      "fail for strerror№ %d. orig:%s,  s21:%s", errnum,
                      origResult, s21Result);
    }
}
END_TEST

TCase* CreateStrerrorCase() {
    TCase* strerrorCase = tcase_create("strerrorCase");

    tcase_add_test(strerrorCase, normalEqualTest_1_106);
    tcase_add_test(strerrorCase, ZeroTest);
    tcase_add_test(strerrorCase, normalMoreTest);
    tcase_add_test(strerrorCase, normalLessTest);

    tcase_add_test(strerrorCase, normalEqualTest41_58);

    return strerrorCase;
}

// arg Null
