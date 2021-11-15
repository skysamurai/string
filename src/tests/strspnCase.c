#include <check.h>
#include <signal.h>
#include <string.h>

#include "../s21_string.h"
#include "tests.h"

START_TEST(normalTest) {
    char str[] = "0123456789";
    char sym[] = "210";
    ck_assert(strspn(str, sym) == s21_strspn(str, sym));
}
END_TEST

START_TEST(arg1EmptyTest) {
    char str[] = "";
    char sym[] = "210";
    ck_assert(strspn(str, sym) == s21_strspn(str, sym));
}
END_TEST

START_TEST(arg1NULLTest) {
<<<<<<< HEAD
   char* str = S21_NULL;
   char sym []="210";
   s21_size_t res = s21_strspn(str,sym);
=======
    char* str = S21_NULL;
    char sym[] = "210";
    s21_size_t res = s21_strcspn(str, sym);
>>>>>>> f05c74554e462d4e7530071537c64324b033da99
}
END_TEST

START_TEST(arg2EmptyTest) {
    char str[] = "0123456789";
    char sym[] = "";
    ck_assert(strspn(str, sym) == s21_strspn(str, sym));
}
END_TEST

START_TEST(arg2NULLTest) {
<<<<<<< HEAD
   char str []="0123456789";
   char* sym = S21_NULL;
   s21_size_t res = s21_strspn(str,sym);
=======
    char str[] = "0123456789";
    char* sym = S21_NULL;
    s21_size_t res = s21_strcspn(str, sym);
>>>>>>> f05c74554e462d4e7530071537c64324b033da99
}
END_TEST

START_TEST(argsNULLTest) {
<<<<<<< HEAD
   char* str = S21_NULL;
   char* sym = S21_NULL;
   s21_size_t res = s21_strspn(str,sym);
=======
    char* str = S21_NULL;
    char* sym = S21_NULL;
    s21_size_t res = s21_strcspn(str, sym);
>>>>>>> f05c74554e462d4e7530071537c64324b033da99
}
END_TEST

TCase* CreateStrspnCase() {
    TCase* strspnCase = tcase_create("strspn case");
    tcase_add_test(strspnCase, normalTest);
    tcase_add_test(strspnCase, arg1EmptyTest);
    tcase_add_test_raise_signal(strspnCase, arg1NULLTest, SIGSEGV);
    tcase_add_test(strspnCase, arg2EmptyTest);
    tcase_add_test_raise_signal(strspnCase, arg2NULLTest, SIGSEGV);
    tcase_add_test_raise_signal(strspnCase, argsNULLTest, SIGSEGV);

    return strspnCase;
}