#include <check.h>
#include <stdio.h>
#include <signal.h>
#include "s21_string.h"
#include <string.h>



START_TEST(s21_strcatTEST)
{ char dest[100] = "privet";
char src[10]  = "kak";
    snprintf(dest, sizeof(dest), "%s%s", dest, src);
    ck_assert_msg(dest == s21_strcat(dest, src), "failed on 12");
}
END_TEST

START_TEST(s21_strncatTEST)
{ char dest[100] = "privet";
char src[10]  = "kak";
s21_size_t n = 2 ; 
    snprintf(dest, sizeof(dest), "%s%s", dest, src);
    ck_assert_msg(dest == s21_strncat(dest, src, n), "failed on 12");
}
END_TEST


START_TEST(s21_strchrTEST)
{ char str[] = "privet";
char c  = 112;

    ck_assert_msg(strchr(str , c) == s21_strchr(str, c), "failed on 12");
}
END_TEST

START_TEST(s21_strcmpTEST)
{ char str1[] = "privet";
char str2[] = "privet";

    ck_assert_msg(strcmp(str1 , str2) == s21_strcmp(str1, str2), "failed on 12");
}
END_TEST

START_TEST(s21_strncmpTEST)
{ char str1[] = "privet";
char str2[] = "privet";
s21_size_t n = 10;
    ck_assert_msg(strncmp(str1 , str2, n) == s21_strncmp(str1, str2 , n), "failed on 12");
}
END_TEST


int main(void) {
    Suite *s1 = suite_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;


    TCase *strcatCase = tcase_create("JumBaseTest");
    suite_add_tcase(s1, strcatCase);
    tcase_add_test(strcatCase, s21_strcatTEST);

    TCase *strncatCase = tcase_create("JumBaseTest");
    suite_add_tcase(s1, strncatCase);
    tcase_add_test(strncatCase, s21_strncatTEST);


    TCase *strchrCase = tcase_create("GumBaseTest");
    suite_add_tcase(s1, strchrCase);
    tcase_add_test(strchrCase, s21_strchrTEST);

    TCase *strcmpCase = tcase_create("sumBaseTest");
    suite_add_tcase(s1, strcmpCase);
    tcase_add_test(strcmpCase, s21_strcmpTEST);

    TCase *strncmpCase = tcase_create("VumBaseTest");
    suite_add_tcase(s1, strncmpCase);
    tcase_add_test(strncmpCase, s21_strncmpTEST);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
