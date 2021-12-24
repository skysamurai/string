#include "tests.h"

START_TEST(normalTest) {
    char str[] = "AAAAA";
    char check_str[] = "AAAAA";
    char* upper = s21_to_upper(str);
    char buffer[512];
    strcpy(buffer, upper);
    free(upper);
    ck_assert(strcmp(buffer, check_str) == 0);
}
END_TEST

START_TEST(normalTest2) {
    char str[] = "AAaAA";
    char check_str[] = "AAAAA";
    char* upper = s21_to_upper(str);
    char buffer[512];
    strcpy(buffer, upper);
    free(upper);
    ck_assert(strcmp(buffer, check_str) == 0);
}
END_TEST

START_TEST(normalTest3) {
    char str[] = "AAa1A";
    char check_str[] = "AAA1A";
    char* upper = s21_to_upper(str);
    char buffer[512];
    strcpy(buffer, upper);
    free(upper);
    ck_assert(strcmp(buffer, check_str) == 0);
}
END_TEST

START_TEST(normalTest4) {
    char str[] = "12345";
    char check_str[] = "12345";
    char* upper = s21_to_upper(str);
    char buffer[512];
    strcpy(buffer, upper);
    free(upper);
    ck_assert(strcmp(buffer, check_str) == 0);
}
END_TEST

START_TEST(normalTest5) {
    char str[] = "";
    char check_str[] = "";
    char* upper = s21_to_upper(str);
    char buffer[512];
    strcpy(buffer, upper);
    free(upper);
    ck_assert(strcmp(buffer, check_str) == 0);
}
END_TEST

START_TEST(normalTest6) {
    char* str = S21_NULL;
    char* upper = s21_to_upper(str);
    ck_assert(upper == S21_NULL);
}
END_TEST

START_TEST(normalTest7) {
    char str[] = "!@#$%";
    char check_str[] = "!@#$%";
    char* upper = s21_to_upper(str);
    char buffer[512];
    strcpy(buffer, upper);
    free(upper);
    ck_assert(strcmp(buffer, check_str) == 0);
}
END_TEST

START_TEST(s21_to_upper_test) {
    char* str;
    char result[10][15] = {
        "HELLO WORLD\0", "HELLO WORLD\n\0", "0123456789\0", "A\n\0", " \n\0",
        "\t\t\n=T\n\0",  "\v\nA\v\n",       " \0",          "\n\0",  "\0"};
    for (short i = 0; i < 10; i++) {
        str = s21_to_upper(result[i]);
        if (str) {
            ck_assert_str_eq(str, result[i]);
            free(str);
        }
    }
}
END_TEST

TCase* CreateToupperCase() {
    TCase* toupperCase = tcase_create("toupper case");
    tcase_add_test(toupperCase, s21_to_upper_test);
    tcase_add_test(toupperCase, normalTest);
    tcase_add_test(toupperCase, normalTest2);
    tcase_add_test(toupperCase, normalTest3);
    tcase_add_test(toupperCase, normalTest4);
    tcase_add_test(toupperCase, normalTest5);
    tcase_add_test(toupperCase, normalTest6);
    tcase_add_test(toupperCase, normalTest7);

    return toupperCase;
}
