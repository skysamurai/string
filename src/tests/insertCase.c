#include <check.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

#include "../s21_string.h"
#include "tests.h"

START_TEST(normalTest) {
    char str[20] = "AAAAA";
    char check_str[] = "AABBBBBAAA";
    char* insert = s21_insert(str, "BBBBB", 2);
    ck_assert(strcmp(insert, check_str) == 0);
    free(insert);
}
END_TEST

START_TEST(normalTest2) {
    char str[] = "AAAAA";
    char check_str[] = "AAAAA";
    char* insert = s21_insert(str, "", 2);
    ck_assert(strcmp(insert, check_str) == 0);
    free(insert);
}
END_TEST




START_TEST(normalTest3) {
    char str[] = "AAa1A";
    char check_str[] = "AAa1A";
    char* insert = s21_insert(str, "", 0);
    ck_assert(strcmp(insert, check_str) == 0);
    free(insert);
}
END_TEST

START_TEST(normalTest4) {
    char str[] = "12345";
    char* insert = s21_insert(str, "test", 10);
    ck_assert(insert == S21_NULL);
    free(insert);
}
END_TEST

START_TEST(normalTest5) {
    char str[] = "12345";
    char* insert = s21_insert(str, "test", -1);
    ck_assert(insert == S21_NULL);
    free(insert);
}
END_TEST

START_TEST(normalTest6) {
    char* str = S21_NULL;
    char* insert = s21_insert(str, "test", 1);
    ck_assert(insert == S21_NULL);
    free(insert);
}
END_TEST

START_TEST(normalTest7) {
    char str[] = "12345";
    char* insert = s21_insert(str, S21_NULL, 1);
    ck_assert(insert == S21_NULL);
    free(insert);
}
END_TEST

TCase* CreateInsertCase() {
    TCase* insertCase = tcase_create("insert case");
    tcase_add_test(insertCase, normalTest);
    tcase_add_test(insertCase, normalTest2);
    tcase_add_test(insertCase, normalTest3);
    tcase_add_test(insertCase, normalTest4);
    tcase_add_test(insertCase, normalTest5);
    tcase_add_test(insertCase, normalTest6);
    tcase_add_test(insertCase, normalTest7);

    return insertCase;
}
