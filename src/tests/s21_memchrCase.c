#include "tests.h"

START_TEST(normalTest) {
    char str[] = "This is a sample string";
    char ch = 's';
    char *origOutput;
    char *s21Output;

    origOutput = memchr(str, ch, strlen(str));
    s21Output = s21_memchr(str, ch, strlen(str));

    ck_assert(origOutput == s21Output);
}
END_TEST

START_TEST(normalNoSuchCharTest) {
    char str[] = "This is a sample string";
    char ch = 'k';
    char *origOutput;
    char *s21Output;

    origOutput = memchr(str, ch, strlen(str));
    s21Output = s21_memchr(str, ch, strlen(str));

    ck_assert(origOutput == s21Output);
}
END_TEST

START_TEST(arg1EmptyTest) {
    char ch = 's';
    char *origOutput;
    char *s21Output;

    origOutput = memchr("", ch, strlen(""));
    s21Output = s21_memchr("", ch, strlen(""));

    ck_assert(origOutput == s21Output);
}
END_TEST

TCase *CreateMemchrCase() {
    TCase *memchrCase = tcase_create("memchr case");

    tcase_add_test(memchrCase, normalTest);
    tcase_add_test(memchrCase, normalNoSuchCharTest);
    tcase_add_test(memchrCase, arg1EmptyTest);

    return memchrCase;
}
