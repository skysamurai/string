#include "tests.h"

START_TEST(normalEqualTest) {
    int origResult = strncmp("aaa", "aaa", 3);
    int s21Result = s21_strncmp("aaa", "aaa", 3);

    ck_assert_msg(s21Result == origResult,
                  "fail for strncmp(\"aaa\", \"aaa\", 3). orig:%d,  s21:%d",
                  origResult, s21Result);
}
END_TEST

START_TEST(normalLessTest) {
    int origResult = strncmp("aaa", "aba", 3);
    int s21Result = s21_strncmp("aaa", "aba", 3);

    ck_assert_msg(s21Result < 0 && origResult < 0,
                  "fail for strncmp(\"aaa\", \"aba\", 3). orig:%d,  s21:%d",
                  origResult, s21Result);
}
END_TEST

START_TEST(normalMoreTest) {
    int origResult = strncmp("aba", "aaa", 3);
    int s21Result = s21_strncmp("aba", "aaa", 3);

    ck_assert_msg(s21Result > 0 && origResult > 0,
                  "fail for strncmp(\"aba\", \"aaa\", 3). orig:%d,  s21:%d",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg1EmptyTest) {
    int origResult = strncmp("", "aaa", 3);
    int s21Result = s21_strncmp("", "aaa", 3);

    ck_assert_msg(s21Result < 0 && origResult < 0,
                  "fail for strncmp(\"\", \"aaa\", 3). orig:%d,  s21:%d",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg2EmptyTest) {
    int origResult = strncmp("aaa", "", 3);
    int s21Result = s21_strncmp("aaa", "", 3);

    ck_assert_msg(s21Result > 0 && origResult > 0,
                  "fail for strncmp(\"\", \"aaa\", 3). orig:%d,  s21:%d",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg3TooMuchTest) {
    int origResult = strncmp("aba", "aaa", 333);
    int s21Result = s21_strncmp("aba", "aaa", 333);

    ck_assert_msg(s21Result > 0 && origResult > 0,
                  "fail for strncmp(\"aba\", \"aaa\", 333). orig:%d,  s21:%d",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg3ZeroTest) {
    int origResult = strncmp("baa", "aaa", 0);
    int s21Result = s21_strncmp("baa", "aaa", 0);

    ck_assert_msg(s21Result == origResult,
                  "fail for strncmp(\"baa\", \"aaa\", 0). orig:%d,  s21:%d",
                  origResult, s21Result);
}
END_TEST

// NEW TESTS

START_TEST(test1) {
    char str1[] = {'1', '0', '3', '5', '\0'};
    char str2[] = {'1', '2', '3', '5', '6', '\0'};
    int res;
    int s21_res;
    res = strncmp(str1, str2, 3);
    s21_res = s21_strncmp(str1, str2, 3);
    ck_assert_msg(res < 0 && s21_res < 0, "failed. orig:%d   s21:%d", res,
                  s21_res);
}
END_TEST

START_TEST(test2) {
    char str1[] = {'1', '2', '3', '5'};
    char str2[] = {'1', '2', '1', '5', '4'};
    int res;
    int s21_res;
    res = strncmp(str1, str2, 4);
    s21_res = s21_strncmp(str1, str2, 4);
    ck_assert_msg(res > 0 && s21_res > 0, "failed. orig:%d   s21:%d", res,
                  s21_res);
}
END_TEST

TCase* CreateStrncmpCase() {
    TCase* strncmpCase = tcase_create("strncmpCase");

    tcase_add_test(strncmpCase, normalEqualTest);
    tcase_add_test(strncmpCase, normalLessTest);
    tcase_add_test(strncmpCase, normalMoreTest);
    tcase_add_test(strncmpCase, arg3TooMuchTest);
    tcase_add_test(strncmpCase, arg3ZeroTest);
    tcase_add_test(strncmpCase, arg1EmptyTest);
    tcase_add_test(strncmpCase, arg2EmptyTest);

    // NEW TESTS

    tcase_add_test(strncmpCase, test1);
    tcase_add_test(strncmpCase, test2);

    return strncmpCase;
}
