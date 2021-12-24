#include "tests.h"

START_TEST(normalEqualTest) {
    ck_assert(s21_memcmp("aaa", "aaa", 3) == memcmp("aaa", "aaa", 3));
}
END_TEST

START_TEST(normalLessTest) {
    ck_assert(s21_memcmp("aaa", "aba", 3) == memcmp("aaa", "aba", 3));
}
END_TEST

START_TEST(normalMoreTest) {
    ck_assert(s21_memcmp("aba", "aaa", 3) == memcmp("aba", "aaa", 3));
}
END_TEST

START_TEST(arg3TooMuchTest) {
    ck_assert(s21_memcmp("aba", "aaa", 333) > 0 ? 1
              : memcmp("aba", "aaa", 333) > 0   ? 1
                                                : 0);
}
END_TEST

START_TEST(arg3ZeroTest) {
    ck_assert(s21_memcmp("baa", "aaa", 0) == memcmp("baa", "aaa", 0));
}
END_TEST

START_TEST(arg1EmptyTest) {
    ck_assert(s21_memcmp("", "aaa", 3) < 0 ? 1
              : memcmp("", "aaa", 3) < 0   ? 1
                                           : 0);
}
END_TEST

START_TEST(arg2EmptyTest) {
    ck_assert(s21_memcmp("aaa", "", 3) > 0 ? 1
              : memcmp("aaa", "", 3) > 0   ? 1
                                           : 0);
}
END_TEST

TCase* CreateMemcmpCase() {
    TCase* memcmpCase = tcase_create("memcmp case");

    tcase_add_test(memcmpCase, normalEqualTest);
    tcase_add_test(memcmpCase, normalLessTest);
    tcase_add_test(memcmpCase, normalMoreTest);
    tcase_add_test(memcmpCase, arg3TooMuchTest);
    tcase_add_test(memcmpCase, arg3ZeroTest);
    tcase_add_test(memcmpCase, arg1EmptyTest);
    tcase_add_test(memcmpCase, arg2EmptyTest);

    return memcmpCase;
}
