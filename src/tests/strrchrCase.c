#include <check.h>
#include <signal.h>
#include <string.h>

#include "s21_string.h"
#include "tests.h"

START_TEST(normalTest) {
    char str[] = "This is a sample string";
    char ch = 's';
    char *origOutput;
    char *s21Output;

    origOutput = strrchr(str, ch);
    s21Output = s21_strrchr(str, ch);
    ck_assert(origOutput == s21Output);
}
END_TEST

START_TEST(noCharTest) {
    char str[] = "This is a sample string";
    char ch = 'k';
    char *origOutput;
    char *s21Output;

    origOutput = strrchr(str, ch);
    s21Output = s21_strrchr(str, ch);
    ck_assert(origOutput == s21Output);
}
END_TEST

START_TEST(arg1EmptyTest) {
    char ch = 's';
    char *origOutput;
    char *s21Output;

    origOutput = strrchr("", ch);
    s21Output = s21_strrchr("", ch);
    ck_assert(origOutput == s21Output);
}
END_TEST

START_TEST(arg1NULLTest) {  // must create SIGSEGV
    char ch = 's';
    char *origOutput;

    origOutput = s21_strrchr(S21_NULL, ch);
}
END_TEST

START_TEST(arg2NULLTest) {  // must create SIGSEGV
    char str[] = "This is a sample string";
    char *emptyChar = S21_NULL;
    char *origOutput;

    origOutput = s21_strrchr(str, *emptyChar);
}
END_TEST

START_TEST(arg2NegativeTest) {
    char str[] = "This is a sample string";

    ck_assert(s21_strrchr(str, -1) == strchr(str, -1));
}
END_TEST

START_TEST(argsNULLTest) {  // must create SIGSEGV
    char *emptyChar = S21_NULL;
    char *origOutput;

    origOutput = s21_strrchr(S21_NULL, *emptyChar);
}
END_TEST

TCase *CreateStrrchrCase() {
    TCase *strrchrCase = tcase_create("strrchr case");

    tcase_add_test(strrchrCase, normalTest);
    tcase_add_test(strrchrCase, noCharTest);

    tcase_add_test(strrchrCase, arg1EmptyTest);
    tcase_add_test(strrchrCase, arg2NegativeTest);

    tcase_add_test_raise_signal(strrchrCase, arg1NULLTest, SIGSEGV);
    tcase_add_test_raise_signal(strrchrCase, arg2NULLTest, SIGSEGV);
    tcase_add_test_raise_signal(strrchrCase, argsNULLTest, SIGSEGV);

    return strrchrCase;
}
