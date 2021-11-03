#include <check.h>
#include <signal.h>
#include <string.h>

#include "../s21_string/s21_string.h"
#include "tests.h"

// TODO
START_TEST(normalTest) {
    // char string[] = "This is the source string";
    // char* substring = "axle";

    ck_assert(1 == 1);
}
END_TEST

TCase* CreateStrcspnCase() {
    TCase* strcspnCase = tcase_create("strcspn case");
    tcase_add_test(strcspnCase, normalTest);

    return strcspnCase;
}