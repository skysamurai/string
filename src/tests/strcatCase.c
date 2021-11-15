#include <check.h>
#include <signal.h>
#include <string.h>

#include "../s21_string.h"
#include "tests.h"

START_TEST(normalTest0) {
    char str1[100] = "";
    char str2[100] = "";
    char* origOutput;
    char* s21Output;

    origOutput = strcat(str1, "aaaaaaa");
    s21Output = s21_strcat(str2, "aaaaaaa");
    ck_assert(strcmp(origOutput, s21Output) == 0);
}
END_TEST

START_TEST(normalTest) {
    char str[100] = "This is a sample string";
    char keys[100] = "aeiou";
    char* origOutput;
    char* s21Output;

    origOutput = strcat(keys, str);
    s21Output = s21_strcat(keys, str);
    ck_assert(strcmp(origOutput, s21Output) == 0);
}
END_TEST

// START_TEST(noCharTest) {
//     char str[] = "This is a sample string";
//     char* s21Output;

//     s21Output = s21_strcat("df", str);
// }
// END_TEST

// START_TEST(arg1EmptyTest) {
//     char str[] = "This is a sample string";
//     char* s21Output;
//     s21Output = s21_strcat("", str);
// }
// END_TEST

START_TEST(arg2EmptyTest) {
    char keys[] = "aeiou";
    char keys2[] = "aeiou";
    char* origOutput;
    char* s21Output;
    origOutput = strcat(keys, "");
    s21Output = s21_strcat(keys2, "");
    ck_assert(strcmp(origOutput, s21Output) == 0);
}
END_TEST

// START_TEST(argsEmptyTest) {
//     char* s21Output;
//     s21Output = s21_strcat("", "");
// }
// END_TEST

// START_TEST(arg1NULLTest) {  // must create SIGSEGV
//     char str[] = "This is a sample string";
//     s21_strcat(S21_NULL, str);
// }
// END_TEST

// START_TEST(arg2NULLTest) {  // must create SIGSEGV
//     char str[] = "This is a sample string";
//     s21_strcat(str, S21_NULL);
// }
// END_TEST

// START_TEST(argsNULLTest) {  // must create SIGSEGV
//     s21_strcat(S21_NULL, S21_NULL);
// }
// END_TEST

TCase* CreateStrcatCase() {
    TCase* strcatCase = tcase_create("strcatCase");
    tcase_add_test(strcatCase, normalTest0);
    tcase_add_test(strcatCase, normalTest);
    // tcase_add_test_raise_signal(strcatCase, noCharTest, SIGBUS);
    // tcase_add_test_raise_signal(strcatCase, arg1EmptyTest, SIGBUS);
    tcase_add_test(strcatCase, arg2EmptyTest);
    // tcase_add_test_raise_signal(strcatCase, argsEmptyTest, SIGBUS);
    // tcase_add_test_raise_signal(strcatCase, arg1NULLTest, SIGSEGV);
    // tcase_add_test_raise_signal(strcatCase, arg2NULLTest, SIGSEGV);
    // tcase_add_test_raise_signal(strcatCase, argsNULLTest, SIGSEGV);

    return strcatCase;
}
