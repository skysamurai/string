#include <check.h>
#include <signal.h>
#include <string.h>

#include "s21_string.h"
#include "tests.h"

START_TEST(normalTest) {
    char str[] = "This is a sample string";
    char keys[] = "aeiou";
    char* origOutput;
    char* s21Output;

    origOutput = strcat(keys, str);
    s21Output = s21_strcat(keys, str);
    ck_assert(origOutput == s21Output);
}
END_TEST

START_TEST(noCharTest) {
    char str[] = "This is a sample string";
    char* origOutput;
    char* s21Output;

    origOutput = strcat("df", str);
    s21Output = s21_strcat("df", str);
    ck_assert(origOutput == s21Output);
}
END_TEST

START_TEST(arg1EmptyTest) {
    char str[] = "This is a sample string";
    char* origOutput;
    char* s21Output;

    origOutput = strcat("", str);
    s21Output = s21_strcat("", str);
    ck_assert(origOutput == s21Output);
}
END_TEST

START_TEST(arg2EmptyTest) {
    char keys[] = "aeiou";
    char* origOutput;
    char* s21Output;
    origOutput = strcat(keys, "");
    s21Output = s21_strcat(keys, "");
    ck_assert(origOutput == s21Output);
}
END_TEST

START_TEST(argsEmptyTest) {
    char* origOutput;
    char* s21Output;
    origOutput = strcat("", "");
    s21Output = s21_strcat("", "");
    ck_assert(origOutput == s21Output);
}
END_TEST

START_TEST(arg1NULLTest) {  // must create SIGSEGV
    char str[] = "This is a sample string";
    s21_strcat(S21_NULL, str);
}
END_TEST

START_TEST(arg2NULLTest) {  // must create SIGSEGV
    char str[] = "This is a sample string";
    s21_strcat(str, S21_NULL);
}
END_TEST

START_TEST(argsNULLTest) {  // must create SIGSEGV
    s21_strcat(S21_NULL, S21_NULL);
}
END_TEST

TCase* CreateStrcatCase() {
    TCase* strcatCase = tcase_create("strcatCase");
    tcase_add_test(strcatCase, normalTest);
    tcase_add_test(strcatCase, noCharTest);
    tcase_add_test(strcatCase, arg1EmptyTest);
    tcase_add_test(strcatCase, arg2EmptyTest);
    tcase_add_test(strcatCase, argsEmptyTest);
    tcase_add_test_raise_signal(strcatCase, arg1NULLTest, SIGSEGV);
    tcase_add_test_raise_signal(strcatCase, arg2NULLTest, SIGSEGV);
    tcase_add_test_raise_signal(strcatCase, argsNULLTest, SIGSEGV);

    return strcatCase;
}
