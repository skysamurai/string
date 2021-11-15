#include <check.h>
#include <signal.h>
#include <string.h>

#include "../s21_string.h"
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
    ck_assert(s21_memcmp("aba", "aaa", 333) > 0    ? 1
              : 0 == memcmp("aba", "aaa", 333) > 0 ? 1
                                                   : 0);
}
END_TEST

START_TEST(arg3ZeroTest) {
    ck_assert(s21_memcmp("baa", "aaa", 0) == memcmp("baa", "aaa", 0));
}
END_TEST

START_TEST(arg1EmptyTest) {
    ck_assert(s21_memcmp("", "aaa", 3) < 0    ? 1
              : 0 == memcmp("", "aaa", 3) < 0 ? 1
                                              : 0);
}
END_TEST

START_TEST(arg2EmptyTest) {
    ck_assert(s21_memcmp("aaa", "", 3) > 0    ? 1
              : 0 == memcmp("aaa", "", 3) > 0 ? 1
                                              : 0);
}
END_TEST

/* START_TEST(arg1NULLTest) {  // must return SIGSEGV
    s21_memcmp(S21_NULL, "aaa", 3);
}
END_TEST */

/* START_TEST(arg2NULLTest) {  // must return SIGSEGV
    s21_memcmp("aaa", S21_NULL, 3);
}
END_TEST */

TCase* CreateMemcmpCase() {
    TCase* memcmpCase = tcase_create("memcmp case");

    tcase_add_test(memcmpCase, normalEqualTest);
    tcase_add_test(memcmpCase, normalLessTest);
    tcase_add_test(memcmpCase, normalMoreTest);
    tcase_add_test(memcmpCase, arg3TooMuchTest);
    tcase_add_test(memcmpCase, arg3ZeroTest);
    tcase_add_test(memcmpCase, arg1EmptyTest);
    tcase_add_test(memcmpCase, arg2EmptyTest);

/*     tcase_add_test_raise_signal(memcmpCase, arg1NULLTest, SIGSEGV);
    tcase_add_test_raise_signal(memcmpCase, arg2NULLTest, SIGSEGV); */

    return memcmpCase;
}