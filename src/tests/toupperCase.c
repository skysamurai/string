#include <check.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

#include "../s21_string.h"
#include "tests.h"

START_TEST(normalTest) {
    char str[] = "AAAAA";
    char check_str[] = "AAAAA";
    char* upper = s21_to_upper(str);
    ck_assert(strcmp(upper, check_str) == 0);
    free(upper);
}
END_TEST

START_TEST(normalTest2) {
    char str[] = "AAaAA";
    char check_str[] = "AAAAA";
    char* upper = s21_to_upper(str);
    ck_assert(strcmp(upper, check_str) == 0);
    free(upper);
}
END_TEST




START_TEST(normalTest3) {
    char str[] = "AAa1A";
    char check_str[] = "AAA1A";
    char* upper = s21_to_upper(str);
    ck_assert(strcmp(upper, check_str) == 0);
    free(upper);
}
END_TEST

START_TEST(normalTest4) {
    char str[] = "12345";
    char check_str[] = "12345";
    char* upper = s21_to_upper(str);
    ck_assert(strcmp(upper, check_str) == 0);
    free(upper);
}
END_TEST

START_TEST(normalTest5) {
    char str[] = "";
    char check_str[] = "";
    char* upper = s21_to_upper(str);
    ck_assert(strcmp(upper, check_str) == 0);
    free(upper);
}
END_TEST

START_TEST(normalTest6) {
    char* str = S21_NULL;
    char* upper = s21_to_upper(str);
    ck_assert(upper == S21_NULL);
    free(upper);
}
END_TEST

START_TEST(normalTest7) {
    char str[] = "!@#$%";
    char check_str[] = "!@#$%";
    char* upper = s21_to_upper(str);
    ck_assert(strcmp(upper, check_str) == 0);
    free(upper);
}
END_TEST

TCase* CreateToupperCase() {
    TCase* toupperCase = tcase_create("toupper case");
    tcase_add_test(toupperCase, normalTest);
    tcase_add_test(toupperCase, normalTest2);
    tcase_add_test(toupperCase, normalTest3);
    tcase_add_test(toupperCase, normalTest4);
    tcase_add_test(toupperCase, normalTest5);
    tcase_add_test(toupperCase, normalTest6);
    tcase_add_test(toupperCase, normalTest7);

    return toupperCase;
}
