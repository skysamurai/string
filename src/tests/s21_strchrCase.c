#include "tests.h"

START_TEST(normalTest) {
    char str[] = "This is a sample string";
    char ch = 's';
    char *origOutput;
    char *s21Output;

    origOutput = strchr(str, ch);
    s21Output = s21_strchr(str, ch);
    ck_assert(origOutput == s21Output);
}
END_TEST

START_TEST(arg1EmptyTest) {
    char ch = 's';
    char *origOutput;
    char *s21Output;

    origOutput = strchr("", ch);
    s21Output = s21_strchr("", ch);
    ck_assert(origOutput == s21Output);
}
END_TEST

TCase *CreateStrchrCase() {
    TCase *strchrCase = tcase_create("StrchrCase");

    tcase_add_test(strchrCase, normalTest);

    tcase_add_test(strchrCase, arg1EmptyTest);

    return strchrCase;
}
