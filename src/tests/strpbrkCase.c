#include <check.h>
#include <signal.h>
#include <string.h>

#include "../s21_string.h"
#include "tests.h"

START_TEST(normalTest) {
    char str[] = "This is a sample string";
    char keys[] = "aeiou";
    char* origOutput;
    char* s21Output;

    origOutput = strpbrk(keys, str);
    s21Output = s21_strpbrk(keys, str);
    ck_assert(origOutput == s21Output);
}
END_TEST

START_TEST(noCharTest) {
    char str[] = "This is a sample string";
    char* origOutput;
    char* s21Output;

    origOutput = strpbrk("df", str);
    s21Output = s21_strpbrk("df", str);
    ck_assert(origOutput == s21Output);
}
END_TEST

START_TEST(arg1EmptyTest) {
    char str[] = "This is a sample string";
    char* origOutput;
    char* s21Output;

    origOutput = strpbrk("", str);
    s21Output = s21_strpbrk("", str);
    ck_assert(origOutput == s21Output);
}
END_TEST

START_TEST(arg1NULLTest) {  // must create SIGSEGV
    char str[] = "This is a sample string";
    s21_strpbrk(S21_NULL, str);
}
END_TEST

START_TEST(arg2EmptyTest) {
    char keys[] = "aeiou";
    char* origOutput;
    char* s21Output;
    origOutput = strpbrk(keys, "");
    s21Output = s21_strpbrk(keys, "");
    ck_assert(origOutput == s21Output);
}
END_TEST

START_TEST(arg2NULLTest) {  // must create SIGSEGV
    char str[] = "This is a sample string";
    s21_strpbrk(str, S21_NULL);
}
END_TEST

START_TEST(argsEmptyTest) {
    const char* a = "";
    char* origOutput;
    char* s21Output;
    origOutput = strpbrk("a", "a");
    s21Output = s21_strpbrk("a", "a");
    ck_assert(origOutput == s21Output);
}
END_TEST

START_TEST(argsNULLTest) {  // must create SIGSEGV
    s21_strpbrk(S21_NULL, S21_NULL);
}
END_TEST

TCase* CreateStrpbrkCase() {
    TCase* strpbrkCase = tcase_create("strpbrk case");
    tcase_add_test(strpbrkCase, normalTest);
    tcase_add_test(strpbrkCase, noCharTest);
    tcase_add_test(strpbrkCase, arg1EmptyTest);
    tcase_add_test(strpbrkCase, arg2EmptyTest);
    tcase_add_test(strpbrkCase, argsEmptyTest);
    tcase_add_test_raise_signal(strpbrkCase, arg1NULLTest, SIGSEGV);
    tcase_add_test_raise_signal(strpbrkCase, arg2NULLTest, SIGSEGV);
    tcase_add_test_raise_signal(strpbrkCase, argsNULLTest, SIGSEGV);

    return strpbrkCase;
}
