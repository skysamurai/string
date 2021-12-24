#include "tests.h"

START_TEST(normalTest0) {
    char str1[100] = "";
    char str2[100] = "";
    char* origOutput;
    char* s21Output;

    origOutput = strcat(str1, "aaaaaaa");
    s21Output = s21_strcat(str2, "aaaaaaa");
    ck_assert(strcmp(origOutput, s21Output) == 0);
}
END_TEST

START_TEST(normalTest) {
    char str[100] = "This is a sample string";
    char keys[100] = "aeiou";
    char* origOutput;
    char* s21Output;

    origOutput = strcat(keys, str);
    s21Output = s21_strcat(keys, str);
    ck_assert(strcmp(origOutput, s21Output) == 0);
}
END_TEST

START_TEST(arg2EmptyTest) {
    char keys[] = "aeiou";
    char keys2[] = "aeiou";
    char* origOutput;
    char* s21Output;
    origOutput = strcat(keys, "");
    s21Output = s21_strcat(keys2, "");
    ck_assert(strcmp(origOutput, s21Output) == 0);
}
END_TEST

TCase* CreateStrcatCase() {
    TCase* strcatCase = tcase_create("strcatCase");
    tcase_add_test(strcatCase, normalTest0);
    tcase_add_test(strcatCase, normalTest);

    tcase_add_test(strcatCase, arg2EmptyTest);

    return strcatCase;
}
