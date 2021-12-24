#include "tests.h"

START_TEST(normalTest) {
    char str[] = "This is a sample string";
    char keys[] = "aeiou";
    char* origOutput;
    char* s21Output;

    origOutput = strpbrk(keys, str);
    s21Output = s21_strpbrk(keys, str);
    ck_assert(origOutput == s21Output);
}
END_TEST

START_TEST(noCharTest) {
    char str[] = "This is a sample string";
    char* origOutput;
    char* s21Output;

    origOutput = strpbrk("df", str);
    s21Output = s21_strpbrk("df", str);
    ck_assert(origOutput == s21Output);
}
END_TEST

START_TEST(arg1EmptyTest) {
    char str[] = "This is a sample string";
    char* origOutput;
    char* s21Output;

    origOutput = strpbrk("", str);
    s21Output = s21_strpbrk("", str);
    ck_assert(origOutput == s21Output);
}
END_TEST

START_TEST(arg2EmptyTest) {
    char keys[] = "aeiou";
    char* origOutput;
    char* s21Output;
    origOutput = strpbrk(keys, "");
    s21Output = s21_strpbrk(keys, "");
    ck_assert(origOutput == s21Output);
}
END_TEST

START_TEST(argsEmptyTest) {
    char* origOutput;
    char* s21Output;
    origOutput = strpbrk("a", "a");
    s21Output = s21_strpbrk("a", "a");
    ck_assert(origOutput == s21Output);
}
END_TEST

TCase* CreateStrpbrkCase() {
    TCase* strpbrkCase = tcase_create("strpbrk case");
    tcase_add_test(strpbrkCase, normalTest);
    tcase_add_test(strpbrkCase, noCharTest);
    tcase_add_test(strpbrkCase, arg1EmptyTest);
    tcase_add_test(strpbrkCase, arg2EmptyTest);
    tcase_add_test(strpbrkCase, argsEmptyTest);

    return strpbrkCase;
}
