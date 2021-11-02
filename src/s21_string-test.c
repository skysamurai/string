#include "s21_string.h"
#include <check.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

#include "tests/tests.h"

int main(void) {
    Suite *s1 = suite_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    TCase *strpbrkCase = CreateStrpbrkCase();
    suite_add_tcase(s1, strpbrkCase);

    TCase *strrchrCase = CreateStrrchrCase();
    suite_add_tcase(s1, strrchrCase);

    TCase *memcmpCase = CreateMemcmpCase();
    suite_add_tcase(s1, memcmpCase);

    TCase *strcspnCase = CreateStrcspnCase();
    suite_add_tcase(s1, strcspnCase);

    TCase *memchrCase = CreateMemchrCase();
    suite_add_tcase(s1, memchrCase);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
