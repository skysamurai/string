#include "tests.h"

START_TEST(normalTest) {
    char str1[] = "0123456789";
    char str2[] = "345";
    char *istr, *s21_istr;
    istr = strstr(str1, str2);
    s21_istr = s21_strstr(str1, str2);
    ck_assert(istr == s21_istr);
}
END_TEST

START_TEST(normalNoSuchTest) {
    char str1[] = "0123456789";
    char str2[] = "nostring";
    char *istr, *s21_istr;
    istr = strstr(str1, str2);
    s21_istr = s21_strstr(str1, str2);
    ck_assert(istr == s21_istr);
}
END_TEST

START_TEST(smalVSbig) {
    char str1[] = "nostrg";
    char str2[] = "0123456789";
    char *istr, *s21_istr;
    istr = strstr(str1, str2);
    s21_istr = s21_strstr(str1, str2);
    ck_assert(istr == s21_istr);
}
END_TEST

START_TEST(arg1EmptyTest) {
    char str1[] = "";
    char str2[] = "asdasd";
    char *istr, *s21_istr;
    istr = strstr(str1, str2);
    s21_istr = s21_strstr(str1, str2);
    ck_assert(istr == s21_istr);
}
END_TEST

START_TEST(arg2EmptyTest) {
    char str1[] = "asdasd";
    char str2[] = "";
    char *istr, *s21_istr;
    istr = strstr(str1, str2);
    s21_istr = s21_strstr(str1, str2);
    ck_assert(istr == s21_istr);
}
END_TEST

TCase *CreateStrstrCase() {
    TCase *strstrCase = tcase_create("strstr case");
    tcase_add_test(strstrCase, normalTest);
    tcase_add_test(strstrCase, normalNoSuchTest);
    tcase_add_test(strstrCase, smalVSbig);
    tcase_add_test(strstrCase, arg1EmptyTest);
    tcase_add_test(strstrCase, arg2EmptyTest);

    return strstrCase;
}
