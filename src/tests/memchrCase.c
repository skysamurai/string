#include <check.h>
#include <signal.h>
#include <string.h>

#include "../s21_string/s21_string.h"
#include "tests.h"

START_TEST(normalTest) {
    char str[] = "This is a sample string";
    char ch = 's';
    char *origOutput;
    char *s21Output;

    origOutput = memchr(str, ch, strlen(str));
    s21Output = s21_memchr(str, ch, strlen(str));
    ck_assert(origOutput == s21Output);
}
END_TEST

START_TEST(arg1EmptyTest) {
    char ch = 's';
    char *origOutput;
    char *s21Output;

    origOutput = memchr("", ch, strlen(""));
    s21Output = s21_memchr("", ch, strlen(""));
    ck_assert(origOutput == s21Output);
}
END_TEST

START_TEST(arg1NULLTest) {  // must NOT create segfault
    char ch = 's';
    char *origOutput;
    char *s21Output;

    origOutput = memchr(S21_NULL, ch, 0);
    s21Output = s21_memchr(S21_NULL, ch, 0);

    ck_assert(origOutput == s21Output);
}

START_TEST(arg2NULLTest) {  // must create SIGSEGV
    char str[] = "This is a sample string";
    char *emptyChar = S21_NULL;
    char *origOutput;

    origOutput = s21_memchr(str, *emptyChar, strlen(str));
}
END_TEST

START_TEST(arg2NegativeTest) {
    char str[] = "This is a sample string";
    char *origOutput;
    char *s21Output;

    origOutput = memchr(str, -1, strlen(str));
    s21Output = s21_memchr(str, -1, strlen(str));
    ck_assert(origOutput == s21Output);
}
END_TEST

START_TEST(arg3NULLTest) {  // must create SIGSEGV
    char str[] = "This is a sample string";
    char ch = 's';
    int *nullint = NULL;
    char *origOutput;
    char *s21Output;

    origOutput = memchr(str, ch, *nullint);
    s21Output = s21_memchr(str, ch, *nullint);
    ck_assert(origOutput == s21Output);
}
END_TEST

START_TEST(arg3NegativeTest) {  // must NOT create segfault
    char str[] = "This is a sample string";
    char ch = 's';
    char *origOutput;
    char *s21Output;

    origOutput = memchr(str, ch, -1);
    s21Output = s21_memchr(str, ch, -1);
    ck_assert(origOutput == s21Output);
}
END_TEST

START_TEST(argsNULLTest) {  // must create SIGSEGV
    char *emptyChar = S21_NULL;
    int *nullint = NULL;
    char *origOutput;

    origOutput = s21_memchr(S21_NULL, *emptyChar, *nullint);
}
END_TEST

TCase *CreateMemchrCase() {
    TCase *memchrCase = tcase_create("memchr case");

    tcase_add_test(memchrCase, normalTest);
    tcase_add_test(memchrCase, arg1EmptyTest);
    tcase_add_test(memchrCase, arg1NULLTest);
    tcase_add_test(memchrCase, arg2NegativeTest);
    tcase_add_test(memchrCase, arg3NegativeTest);

    tcase_add_test_raise_signal(memchrCase, arg2NULLTest, SIGSEGV);
    tcase_add_test_raise_signal(memchrCase, arg3NULLTest, SIGSEGV);
    tcase_add_test_raise_signal(memchrCase, argsNULLTest, SIGSEGV);

    return memchrCase;
}