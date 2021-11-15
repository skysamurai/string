#include <check.h>
#include <signal.h>
#include <string.h>

#include "../s21_string.h"
#include "tests.h"

START_TEST(normalTest) {
    char str[] = "This is a sample string";
    char ch = 's';
    char *origOutput;
    char *s21Output;

    origOutput = strchr(str, ch);
    s21Output = s21_strchr(str, ch);
    ck_assert(origOutput == s21Output);
}
END_TEST

START_TEST(arg1EmptyTest) {
    char ch = 's';
    char *origOutput;
    char *s21Output;

    origOutput = strchr("", ch);
    s21Output = s21_strchr("", ch);
    ck_assert(origOutput == s21Output);
}
END_TEST

/* START_TEST(arg1NULLTest) {  // must create SIGSEGV
    char ch = 's';
    char *origOutput;

    origOutput = s21_strchr(S21_NULL, ch);
}
END_TEST */

/* START_TEST(arg2NULLTest) {  // must create SIGSEGV
    char str[] = "This is a sample string";
    char *emptyChar = S21_NULL;
    char *origOutput;

    origOutput = s21_strchr(str, *emptyChar);
}
END_TEST */

/* START_TEST(argsNULLTest) {  // must create SIGSEGV
    char *emptyChar = S21_NULL;
    char *origOutput;

    origOutput = s21_strchr(S21_NULL, *emptyChar);
}
END_TEST */

TCase *CreateStrchrCase() {
    TCase *strchrCase = tcase_create("StrchrCase");

    tcase_add_test(strchrCase, normalTest);

    tcase_add_test(strchrCase, arg1EmptyTest);

/*     tcase_add_test_raise_signal(strchrCase, arg1NULLTest, SIGSEGV);
    tcase_add_test_raise_signal(strchrCase, arg2NULLTest, SIGSEGV);
    tcase_add_test_raise_signal(strchrCase, argsNULLTest, SIGSEGV); */

    return strchrCase;
}
