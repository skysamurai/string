#include "tests.h"

#include <check.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

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
    
    TCase *strcmpCase = CreateStrcmpCase();
    suite_add_tcase(s1, strcmpCase);

    TCase *memchrCase = CreateMemchrCase();
    suite_add_tcase(s1, memchrCase);

    TCase *trimCase = CreateTrimCase();
    suite_add_tcase(s1, trimCase);

    TCase *strtokCase = CreateStrtokCase();
    suite_add_tcase(s1, strtokCase);

    TCase *sprintfCase = CreateSprintfCase();
    suite_add_tcase(s1, sprintfCase);

    TCase *strncmpCase = CreateStrncmpCase();
    suite_add_tcase(s1, strncmpCase);

    /* TODO: Seldon rewrite
        TCase *strcatCase = CreateStrcatCase();
        suite_add_tcase(s1, strcatCase);
    */

    /* TODO: Seldon rewrite
       TCase *strncatCase = CreateStrncatCase();
       suite_add_tcase(s1, strncatCase);
    */

    TCase *strchrCase = CreateStrchrCase();
    suite_add_tcase(s1, strchrCase);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
