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

START_TEST(arg2EmptyTest) {
    char str[] = "0123456789";
    char sym[] = "";
    ck_assert(strspn(str, sym) == s21_strspn(str, sym));
}
END_TEST

TCase* CreateStrspnCase() {
    TCase* strspnCase = tcase_create("strspn case");
    tcase_add_test(strspnCase, normalTest);
    tcase_add_test(strspnCase, arg1EmptyTest);
    tcase_add_test(strspnCase, arg2EmptyTest);

    return strspnCase;
}
