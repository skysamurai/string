#include "tests.h"

START_TEST(normalTest) {
    char str[] = "This is a sample string";
    char ch = 's';
    char *origOutput;
    char *s21Output;

    origOutput = strrchr(str, ch);
    s21Output = s21_strrchr(str, ch);
    ck_assert(origOutput == s21Output);
}
END_TEST

START_TEST(noCharTest) {
    char str[] = "This is a sample string";
    char ch = 'k';
    char *origOutput;
    char *s21Output;

    origOutput = strrchr(str, ch);
    s21Output = s21_strrchr(str, ch);
    ck_assert(origOutput == s21Output);
}
END_TEST

START_TEST(arg1EmptyTest) {
    char ch = 's';
    char *origOutput;
    char *s21Output;

    origOutput = strrchr("", ch);
    s21Output = s21_strrchr("", ch);
    ck_assert(origOutput == s21Output);
}
END_TEST

TCase *CreateStrrchrCase() {
    TCase *strrchrCase = tcase_create("strrchr case");

    tcase_add_test(strrchrCase, normalTest);
    tcase_add_test(strrchrCase, noCharTest);
    tcase_add_test(strrchrCase, arg1EmptyTest);

    return strrchrCase;
}
