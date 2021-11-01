#include "s21_string.h"

#include <check.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

START_TEST(strpbrkBaseTest) {
    char str[] = "This is a sample string";
    char keys[] = "aeiou";
    char *origOutput;
    char *s21Output;

    origOutput = strpbrk(keys, str);
    s21Output = s21_strpbrk(keys, str);
    ck_assert_msg(origOutput == s21Output, "strpbrk normal input error");

    origOutput = strpbrk("df", str);
    s21Output = s21_strpbrk("df", str);
    ck_assert_msg(origOutput == s21Output, "strpbrk no such char error");

    origOutput = strpbrk("", str);
    s21Output = s21_strpbrk("", str);
    ck_assert_msg(origOutput == s21Output, "strpbrk empty string1 error");

    origOutput = strpbrk(keys, "");
    s21Output = s21_strpbrk(keys, "");
    ck_assert_msg(origOutput == s21Output, "strpbrk empty string2 error");

    origOutput = strpbrk("", "");
    s21Output = s21_strpbrk("", "");
    ck_assert_msg(origOutput == s21Output, "strpbrk empty strings error");
}
END_TEST

START_TEST(strpbrkSegF1) {
    char str[] = "This is a sample string";
    s21_strpbrk(NULL, str);
}
END_TEST

START_TEST(strpbrkSegF2) {
    char str[] = "This is a sample string";
    s21_strpbrk(str, NULL);
}
END_TEST

START_TEST(strrchrBaseTest) {
    char str[] = "This is a sample string";
    char ch = 's';
    char *origOutput;
    char *s21Output;

    origOutput = strrchr(str, ch);
    s21Output = s21_strrchr(str, ch);
    ck_assert_msg(origOutput == s21Output, "strrchr normal input error");

    origOutput = strrchr("", ch);
    s21Output = s21_strrchr("", ch);
    ck_assert_msg(origOutput == s21Output, "strrchr empty string error");

    origOutput = strrchr(str, NULL);
    s21Output = s21_strrchr(str, NULL);

    ck_assert_msg(origOutput == s21Output, "strrchr empty char error");
}

END_TEST
START_TEST(strpbrkSegF3) { s21_strpbrk(NULL, NULL); }
END_TEST

int main(void) {
    Suite *s1 = suite_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    TCase *strpbrkCase = tcase_create("strpbrkTest");
    suite_add_tcase(s1, strpbrkCase);
    tcase_add_test(strpbrkCase, strpbrkBaseTest);
    tcase_add_test_raise_signal(strpbrkCase, strpbrkSegF1, SIGSEGV);
    tcase_add_test_raise_signal(strpbrkCase, strpbrkSegF2, SIGSEGV);
    tcase_add_test_raise_signal(strpbrkCase, strpbrkSegF3, SIGSEGV);

    TCase *strrchrCase = tcase_create("strrchrTest");
    suite_add_tcase(s1, strrchrCase);
    tcase_add_test(strrchrCase, strrchrBaseTest);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
