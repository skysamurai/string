#include "tests.h"

START_TEST(normalEqualTest) {
    char s21_dest[100] = "privet";
    char s21_src[100] = "aeiou";
    char dest[100] = "privet";
    char src[100] = "aeiou";

    strncat(dest, src, 5);
    s21_strncat(s21_dest, s21_src, 5);
    ck_assert(strcmp(dest, s21_dest) == 0);
}
END_TEST

START_TEST(normalLessTest) {
    char s21_dest[100] = "privet";
    char s21_src[100] = "aeiou";
    char dest[100] = "privet";
    char src[100] = "aeiou";

    strncat(dest, src, 4);
    s21_strncat(s21_dest, s21_src, 4);
    ck_assert(strcmp(dest, s21_dest) == 0);
}
END_TEST

START_TEST(normalMoreTest) {
    char s21_dest[100] = "privet";
    char s21_src[100] = "aeiou";
    char dest[100] = "privet";
    char src[100] = "aeiou";

    strncat(dest, src, 6);
    s21_strncat(s21_dest, s21_src, 6);
    ck_assert(strcmp(dest, s21_dest) == 0);
}
END_TEST

START_TEST(arg3ZeroTest) {
    char s21_dest[100] = "privet";
    char s21_src[100] = "aeiou";
    char dest[100] = "privet";
    char src[100] = "aeiou";

    strncat(dest, src, 0);
    s21_strncat(s21_dest, s21_src, 0);
    ck_assert(strcmp(dest, s21_dest) == 0);
}
END_TEST

START_TEST(arg2EmptyTest) {
    char s21_dest[100] = "privet";
    char dest[100] = "privet";
    strncat(dest, "", 5);
    s21_strncat(s21_dest, "", 5);
    ck_assert(strcmp(dest, s21_dest) == 0);
}
END_TEST

TCase* CreateStrncatCase() {
    TCase* strncatCase = tcase_create("strncat case");

    tcase_add_test(strncatCase, normalEqualTest);
    tcase_add_test(strncatCase, normalLessTest);
    tcase_add_test(strncatCase, normalMoreTest);
    tcase_add_test(strncatCase, arg3ZeroTest);
    tcase_add_test(strncatCase, arg2EmptyTest);

    return strncatCase;
}
