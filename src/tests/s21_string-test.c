#include "../s21_string.h"

#include <check.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

#include "tests.h"

int main(void) {
    Suite *s1 = suite_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    TCase *strchrCase = CreateStrchrCase();
    suite_add_tcase(s1, strchrCase);

    TCase *strcmpCase = CreateStrcmpCase();
    suite_add_tcase(s1, strcmpCase);

    TCase *strncmpCate = CreateStrncmpCase();
    suite_add_tcase(s1, strncmpCate);

    TCase *strcatCate = CreateStrcatCase();
    suite_add_tcase(s1, strcatCate);

    TCase *strncatCate = CreateStrncatCase();
    suite_add_tcase(s1, strncatCate);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
