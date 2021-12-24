#include "tests.h"

START_TEST(normalTest) {
    char str[] = "AAAAA";
    char check_str[] = "aaaaa";
    char* lower = s21_to_lower(str);
    ck_assert(strcmp(lower, check_str) == 0);
    free(lower);
}
END_TEST

START_TEST(normalTest2) {
    char str[] = "AAaAA";
    char check_str[] = "aaaaa";
    char* lower = s21_to_lower(str);
    ck_assert(strcmp(lower, check_str) == 0);
    free(lower);
}
END_TEST

START_TEST(normalTest3) {
    char str[] = "AAa1A";
    char check_str[] = "aaa1a";
    char* lower = s21_to_lower(str);
    ck_assert(strcmp(lower, check_str) == 0);
    free(lower);
}
END_TEST

START_TEST(normalTest4) {
    char str[] = "12345";
    char check_str[] = "12345";
    char* lower = s21_to_lower(str);
    ck_assert(strcmp(lower, check_str) == 0);
    free(lower);
}
END_TEST

START_TEST(normalTest5) {
    char str[] = "";
    char check_str[] = "";
    char* lower = s21_to_lower(str);
    ck_assert(strcmp(lower, check_str) == 0);
    free(lower);
}
END_TEST

START_TEST(normalTest6) {
    char* str = S21_NULL;
    char* lower = s21_to_lower(str);
    ck_assert(lower == S21_NULL);
}
END_TEST

START_TEST(normalTest7) {
    char str[] = "!@#$%";
    char check_str[] = "!@#$%";
    char* lower = s21_to_lower(str);
    ck_assert(strcmp(lower, check_str) == 0);
    free(lower);
}
END_TEST

START_TEST(s21_to_lower_test) {
    char* str;
    char result[10][15] = {
        "hello world\0", "hello world\n\0", "0123456789\0", "a\n\0", " \n\0",
        "\t\t\n=t\n\0",  "\v\na\v\n",       " \0",          "\n\0",  "\0"};
    for (short i = 0; i < 10; i++) {
        str = s21_to_lower(result[i]);
        if (str) {
            ck_assert_str_eq(str, result[i]);
            free(str);
        }
    }
    str = s21_to_lower("HELLO WORLD");
    if (str) {
        ck_assert_str_eq(str, "hello world");
        free(str);
    }
    str = s21_to_lower("TeSt\nTeSt\ntEsT\v");
    if (str) {
        ck_assert_str_eq(str, "test\ntest\ntest\v");
        free(str);
    }
}
END_TEST

TCase* CreateTolowerCase() {
    TCase* tolowerCase = tcase_create("tolower case");
    tcase_add_test(tolowerCase, s21_to_lower_test);
    tcase_add_test(tolowerCase, normalTest);
    tcase_add_test(tolowerCase, normalTest2);
    tcase_add_test(tolowerCase, normalTest3);
    tcase_add_test(tolowerCase, normalTest4);
    tcase_add_test(tolowerCase, normalTest5);
    tcase_add_test(tolowerCase, normalTest6);
    tcase_add_test(tolowerCase, normalTest7);

    return tolowerCase;
}
