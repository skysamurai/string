#include <check.h>
#include <signal.h>
#include <string.h>

#include "s21_string.h"
#include "tests.h"

START_TEST(normalTest) {
   char str[]="0123456789";
   char sym[]="210";
   ck_assert(strcspn(str,sym) == s21_strcspn(str,sym));
}
END_TEST

START_TEST(arg1EmptyTest) {
   char str[]="";
   char sym[]="210";
   ck_assert(strcspn(str,sym) == s21_strcspn(str,sym));
}
END_TEST

START_TEST(arg1NULLTest) {
   char* str = S21_NULL;
   char sym[]="210";
   s21_size_t res = s21_strcspn(str,sym);
}
END_TEST

START_TEST(arg2EmptyTest) {
   char str[] ="0123456789";
   char sym[] ="";
   ck_assert(strcspn(str,sym) == s21_strcspn(str,sym));
}
END_TEST

START_TEST(arg2NULLTest) {
   char str[] ="0123456789";
   char* sym = S21_NULL;
   s21_size_t res = s21_strcspn(str,sym);
}
END_TEST

START_TEST(argsNULLTest) {
   char* str = S21_NULL;
   char* sym = S21_NULL;
   s21_size_t res = s21_strcspn(str,sym);
}
END_TEST

TCase* CreateStrcspnCase() {
    TCase* strcspnCase = tcase_create("strcspn case");
    tcase_add_test(strcspnCase, normalTest);
    tcase_add_test(strcspnCase, arg1EmptyTest);
    tcase_add_test_raise_signal(strcspnCase, arg1NULLTest, SIGSEGV);
    tcase_add_test(strcspnCase, arg2EmptyTest);
    tcase_add_test_raise_signal(strcspnCase, arg2NULLTest, SIGSEGV);
    tcase_add_test_raise_signal(strcspnCase, argsNULLTest, SIGSEGV);

    return strcspnCase;
}