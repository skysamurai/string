#include <check.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

#include "../s21_string.h"
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
    free(lower);
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

TCase* CreateTolowerCase() {
    TCase* tolowerCase = tcase_create("tolower case");
    tcase_add_test(tolowerCase, normalTest);
    tcase_add_test(tolowerCase, normalTest2);
    tcase_add_test(tolowerCase, normalTest3);
    tcase_add_test(tolowerCase, normalTest4);
    tcase_add_test(tolowerCase, normalTest5);
    tcase_add_test(tolowerCase, normalTest6);
    tcase_add_test(tolowerCase, normalTest7);

    return tolowerCase;
}
