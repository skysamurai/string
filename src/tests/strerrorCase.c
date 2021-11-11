#include <check.h>
#include <signal.h>
#include <string.h>

#include "../s21_string/s21_string.h"
#include "tests.h"

START_TEST(normalEqualTest_1_40) {
    for(int errnum = 1; errnum < 41; errnum++) {
        const char* origResult = strerror(errnum);
        const char* s21Result = s21_strerror(errnum);
        ck_assert_msg(s21Result == origResult,
                    "fail for strerror№ %d. orig:%s,  s21:%s", errnum,
                    origResult, s21Result);
    }

}
END_TEST

START_TEST(ZeroTest) {
    int errnum = 0;
    const char* origResult = strerror(errnum);
    const char* s21Result = s21_strerror(errnum);
    printf(">>>sreerror %d>>>>%s\n", errnum, origResult);
    printf(">>>s21error %d>>>>%s\n", errnum, s21Result);
    ck_assert_msg(s21Result == origResult,
                "fail for strerror№ %d. orig:%s,  s21:%s", errnum,
                origResult, s21Result);
}
END_TEST

// START_TEST(normalMoreTest) {
//     int errnum = 100;
//     const char* origResult = strerror(errnum);
//     const char* s21Result = s21_strerror(errnum);

//     ck_assert_msg(s21Result == origResult,
//                   "fail for strerror(\"len50\", \"len50\"). orig:%s,  s21:%s",
//                   origResult, s21Result);
// }
// END_TEST

// START_TEST(arg1NULLTest) {  // must return SIGSEGV
//     int* errnum = s21_NULL;
//     s21_strerror(errnum);
// }
// END_TEST

TCase* CreateStrerrorCase() {
    TCase* strerrorCase = tcase_create("strerrorCase");

    tcase_add_test(strerrorCase, normalEqualTest_1_40);
    tcase_add_test(strerrorCase, ZeroTest);
    // tcase_add_test(strerrorCase, normalMoreTest);
    // tcase_add_test(strerrorCase, arg1EmptyTest);

    // tcase_add_test_raise_signal(strerrorCase, arg1NULLTest, SIGSEGV);
return strerrorCase;
}

// arg Null
