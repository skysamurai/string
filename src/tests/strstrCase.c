#include <check.h>
#include <signal.h>
#include <string.h>

#include "../s21_string.h"
#include "tests.h"

START_TEST(normalTest) {
    char str1[] = "0123456789";
    char str2[] = "345";
    char *istr, *s21_istr;
    istr = strstr(str1, str2);
    s21_istr = s21_strstr(str1, str2);
    ck_assert(istr == s21_istr);
}
END_TEST

START_TEST(arg1EmptyTest) {
    char str1[] = "";
    char str2[] = "asdasd";
    char *istr, *s21_istr;
    istr = strstr(str1, str2);
    s21_istr = s21_strstr(str1, str2);
    ck_assert(istr == s21_istr);
}
END_TEST

/* START_TEST(arg1NULLTest) {
    char* str1 = S21_NULL;
    char str2[] = "asdasd";
    char *istr, *s21_istr;
    s21_istr = s21_strstr(str1, str2);
}
END_TEST */

START_TEST(arg2EmptyTest) {
    char str1[] = "asdasd";
    char str2[] = "";
    char *istr, *s21_istr;
    istr = strstr(str1, str2);
    s21_istr = s21_strstr(str1, str2);
    ck_assert(istr == s21_istr);
}
END_TEST

/* START_TEST(arg2NULLTest) {
    char str1[] = "dgdfgs";
    char* str2 = S21_NULL;
    char *istr, *s21_istr;
    s21_istr = s21_strstr(str1, str2);
}
END_TEST */

/* START_TEST(argsNULLTest) {
    char* str1 = S21_NULL;
    char* str2 = S21_NULL;
    char *istr, *s21_istr;
    s21_istr = s21_strstr(str1, str2);
}
END_TEST */

TCase* CreateStrstrCase() {
    TCase* strstrCase = tcase_create("strstr case");
    tcase_add_test(strstrCase, normalTest);
    tcase_add_test(strstrCase, arg1EmptyTest);
/*     tcase_add_test_raise_signal(strstrCase, arg1NULLTest, SIGSEGV); */
    tcase_add_test(strstrCase, arg2EmptyTest);
/*     tcase_add_test_raise_signal(strstrCase, arg2NULLTest, SIGSEGV);
    tcase_add_test_raise_signal(strstrCase, argsNULLTest, SIGSEGV); */

    return strstrCase;
}