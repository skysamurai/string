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

START_TEST(strpbrkSegF3) { s21_strpbrk(NULL, NULL); }
END_TEST

int main(void) {
    Suite *s1 = suite_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    TCase *strpbrkCase = tcase_create("sumBaseTest");
    suite_add_tcase(s1, strpbrkCase);
    tcase_add_test(strpbrkCase, strpbrkBaseTest);
    tcase_add_test_raise_signal(strpbrkCase, strpbrkSegF1, SIGSEGV);
    tcase_add_test_raise_signal(strpbrkCase, strpbrkSegF2, SIGSEGV);
    tcase_add_test_raise_signal(strpbrkCase, strpbrkSegF3, SIGSEGV);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
