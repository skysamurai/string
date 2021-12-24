#include "tests.h"

START_TEST(normalEqualTest_1_106) {
    const char* origResult;
    const char* s21Result;
    for (int errnum = 1; errnum < 100; errnum++) {
        char* nullStr = "null";
        origResult = strerror(errnum);
        s21Result = s21_strerror(errnum);
        if (origResult == S21_NULL) origResult = nullStr;
        if (s21Result == S21_NULL) s21Result = nullStr;

        ck_assert_msg(strcmp(s21Result, origResult) == 0,
                      "fail for strerror№ %d. orig:%s,  s21:%s", errnum,
                      origResult, s21Result);
    }
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

    return strerrorCase;
}
