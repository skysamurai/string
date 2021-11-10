#include <check.h>
#include <signal.h>
#include <string.h>

#include "s21_string.h"
#include "tests.h"

// TODO
START_TEST(normalTest) {
    char str[] = "fcba73";
    char keys[] = "1234567890";
    int i;
    i = strcspn(str,keys);
    int s21_i;
    s21_i = s21_strcspn (str,keys);
    ck_assert(i == s21_i);
}
END_TEST

TCase* CreateStrcspnCase() {
    TCase* strcspnCase = tcase_create("strcspn case");
    tcase_add_test(strcspnCase, normalTest);

    return strcspnCase;
}