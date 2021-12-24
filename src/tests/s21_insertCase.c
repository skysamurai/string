#include "tests.h"

START_TEST(normalTest) {
    char str[20] = "AAAAA";
    char check_str[] = "AABBBBBAAA";
    char* insert = s21_insert(str, "BBBBB", 2);
    char buffer[512];
    strcpy(buffer, insert);
    free(insert);
    ck_assert_msg(strcmp(buffer, check_str) == 0,
                  "fail on test 1\ns21 : %s\norig: %s\n", insert, check_str);
}
END_TEST

START_TEST(normalTest2) {
    char str[] = "AAAAA";
    char check_str[] = "AAAAA";
    char* insert = s21_insert(str, "", 2);
    char buffer[512];
    strcpy(buffer, insert);
    free(insert);
    ck_assert(strcmp(buffer, check_str) == 0);
}
END_TEST

START_TEST(normalTest3) {
    char str[] = "AAa1A";
    char check_str[] = "AAa1A";
    char* insert = s21_insert(str, "", 0);
        char buffer[512];
    strcpy(buffer, insert);
    free(insert);
    ck_assert(strcmp(buffer, check_str) == 0);
}
END_TEST

START_TEST(normalTest4) {
    char str[] = "12345";
    char* insert = s21_insert(str, "test", 10);
    ck_assert(insert == S21_NULL);
}
END_TEST

START_TEST(normalTest5) {
    char str[] = "12345";
    char* insert = s21_insert(str, "test", -1);
    ck_assert(insert == S21_NULL);
}
END_TEST

START_TEST(normalTest6) {
    char* str = S21_NULL;
    char* insert = s21_insert(str, "test", 1);
    ck_assert(insert == S21_NULL);
}
END_TEST

START_TEST(normalTest7) {
    char str[] = "12345";
    char* insert = s21_insert(str, S21_NULL, 1);
    ck_assert(insert == S21_NULL);
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
