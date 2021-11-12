#include <check.h>
#include <signal.h>
#include <string.h>

#include "s21_string.h"
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

START_TEST(arg3TooMuchTest) {
    char s21_dest[100] = "privet";
    char s21_src[100] = "aeiou";
    char dest[100] = "privet";
    char src[100] = "aeiou";

    strncat(dest, src, 200);
    s21_strncat(s21_dest, s21_src, 200);
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

// START_TEST(arg1EmptyTest) {
//     char s21_src[100] = "aeiou";
//     strncat("", s21_src, 6);
//     s21_strncat("", s21_src, 6);
// }
// END_TEST

START_TEST(arg2EmptyTest) {
    char s21_dest[100] = "privet";
    char dest[100] = "privet";
    strncat(dest, "", 5);
    s21_strncat(s21_dest, "", 5);
    ck_assert(strcmp(dest, s21_dest) == 0);
}
END_TEST

START_TEST(arg1NULLTest) {
    char s21_src[100] = "aeiou";
    s21_strncat(S21_NULL, s21_src, 5);
}
END_TEST

START_TEST(arg2NULLTest) {
    char s21_dest[100] = "privet";
    s21_strncat(s21_dest, S21_NULL, 5);
}
END_TEST

TCase* CreateStrncatCase() {
    TCase* strncatCase = tcase_create("strncat case");

    tcase_add_test(strncatCase, normalEqualTest);
    tcase_add_test(strncatCase, normalLessTest);
    tcase_add_test(strncatCase, normalMoreTest);
    tcase_add_test(strncatCase, arg3TooMuchTest);
    tcase_add_test(strncatCase, arg3ZeroTest);
    // tcase_add_test_raise_signal(strncatCase, arg1EmptyTest, SIGSEGV);
    tcase_add_test(strncatCase, arg2EmptyTest);

    tcase_add_test_raise_signal(strncatCase, arg1NULLTest, SIGSEGV);
    tcase_add_test_raise_signal(strncatCase, arg2NULLTest, SIGSEGV);

    return strncatCase;
}
