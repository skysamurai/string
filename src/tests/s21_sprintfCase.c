#include "tests.h"

START_TEST(dFlagTest0) {
    char formatStr[100] = "|%d word|";
    char origStr[300] = "";
    char s21Str[300] = "";

    s21_sprintf(s21Str, formatStr, 300);
    sprintf(origStr, formatStr, 300);

    ck_assert(strcmp(s21Str, origStr) == 0);
}
END_TEST

START_TEST(dFlagTest1) {
    char formatStr[100] = "|%+.5d word|";
    char origStr[300] = "";
    char s21Str[300] = "";

    s21_sprintf(s21Str, formatStr, 300);
    sprintf(origStr, formatStr, 300);

    ck_assert(strcmp(s21Str, origStr) == 0);
}
END_TEST

START_TEST(dFlagTest2) {
    char formatStr[100] = "|%#d word|";
    char origStr[300] = "";
    char s21Str[300] = "";

    s21_sprintf(s21Str, formatStr, 300);
    sprintf(origStr, formatStr, 300);

    ck_assert(strcmp(s21Str, origStr) == 0);
}
END_TEST

START_TEST(dFlagTest3) {
    char formatStr[100] = "|%+d word|";
    char origStr[300] = "";
    char s21Str[300] = "";

    s21_sprintf(s21Str, formatStr, 300);
    sprintf(origStr, formatStr, 300);

    ck_assert(strcmp(s21Str, origStr) == 0);
}
END_TEST

START_TEST(dFlagTest4) {
    char formatStr[100] = "|%#.30d word|";
    char origStr[300] = "";
    char s21Str[300] = "";

    s21_sprintf(s21Str, formatStr, 300);
    sprintf(origStr, formatStr, 300);

    ck_assert(strcmp(s21Str, origStr) == 0);
}
END_TEST

START_TEST(dFlagTest5) {
    char formatStr[100] = "|%*d word|";
    char origStr[300] = "";
    char s21Str[300] = "";

    s21_sprintf(s21Str, formatStr, 40, 300);
    sprintf(origStr, formatStr, 40, 300);

    ck_assert(strcmp(s21Str, origStr) == 0);
}
END_TEST

START_TEST(dFlagTest6) {
    char formatStr[100] = "|%*d wor\0d %*d %*d %*d|";
    char origStr[300] = "";
    char s21Str[300] = "";

    s21_sprintf(s21Str, formatStr, 40, 300, 3, 14, 15, 92, 6, 5);
    sprintf(origStr, formatStr, 40, 300, 3, 14, 15, 92, 6, 5);

    ck_assert(strcmp(s21Str, origStr) == 0);
}
END_TEST

START_TEST(dFlagTest7) {
    char formatStr[100] = "|% .*d word %*d %.*d % *d|";
    char origStr[300] = "";
    char s21Str[300] = "";

    s21_sprintf(s21Str, formatStr, 40, 300, 3, 14, 15, 92, 6, 5);
    sprintf(origStr, formatStr, 40, 300, 3, 14, 15, 92, 6, 5);
    ck_assert(strcmp(s21Str, origStr) == 0);
}
END_TEST

START_TEST(dFlagTest8) {
    char formatStr[100] = "|%ld word|";
    char origStr[300] = "";
    char s21Str[300] = "";

    s21_sprintf(s21Str, formatStr, 300);
    sprintf(origStr, formatStr, 300);

    ck_assert(strcmp(s21Str, origStr) == 0);
}
END_TEST

START_TEST(dFlagTest9) {
    char formatStr[100] = "|%hd word|";
    char origStr[300] = "";
    char s21Str[300] = "";

    s21_sprintf(s21Str, formatStr, 300);
    sprintf(origStr, formatStr, 300);

    ck_assert(strcmp(s21Str, origStr) == 0);
}
END_TEST

START_TEST(cSpecTest0) {
    char formatStr[100] = "|%c word|";
    char origStr[300] = "";
    char s21Str[300] = "";

    s21_sprintf(s21Str, formatStr, 'g');
    sprintf(origStr, formatStr, 'g');

    ck_assert_msg(strcmp(s21Str, origStr) == 0,
                  "test failed \ns21 : |%s|, \norig: |%s|", s21Str, origStr);
}
END_TEST

START_TEST(cSpecTest1) {
    char formatStr[100] = "|%3.10c word|";
    char origStr[300] = "";
    char s21Str[300] = "";

    s21_sprintf(s21Str, formatStr, 'g');
    sprintf(origStr, formatStr, 'g');

    ck_assert_msg(strcmp(s21Str, origStr) == 0,
                  "test failed \ns21 : |%s|, \norig: |%s|", s21Str, origStr);
}
END_TEST

START_TEST(iSpecTest0) {
    char formatStr[100] = "|%i word|";
    char origStr[300] = "";
    char s21Str[300] = "";

    s21_sprintf(s21Str, formatStr, 0364);
    sprintf(origStr, formatStr, 0364);

    ck_assert(strcmp(s21Str, origStr) == 0);
}
END_TEST

START_TEST(eSpecTest5) {
    char formatStr[100] = "%.e word";
    int i;
    double d[] = {-42,
                  42.0,
                  1234567.89012345,
                  1.00000000000000018,
                  555555.55555555555555555,
                  -888888888888888.8888888,
                  16.9,
                  +0,
                  -0};

    for (i = 0; i < 8; i++) {
        char s21Str[4000] = {0};
        s21_sprintf(s21Str, formatStr, d[i]);

        char origStr[4000] = {0};
        sprintf(origStr, formatStr, d[i]);

        ck_assert_msg(strcmp(s21Str, origStr) == 0,
                      "test failed on i = %d, \ns21 : |%s|, \norig: |%s|", i,
                      s21Str, origStr);
    }
}
END_TEST

START_TEST(eSpecTest6) {
    char formatStr[100] = "%.E word";
    int i;
    double d[] = {-42,
                  42.0,
                  1234567.89012345,
                  1.00000000000000018,
                  555555.55555555555555555,
                  -888888888888888.8888888,
                  16.9,
                  +0,
                  -0};

    for (i = 0; i < 8; i++) {
        char s21Str[4000] = {0};
        s21_sprintf(s21Str, formatStr, d[i]);

        char origStr[4000] = {0};
        sprintf(origStr, formatStr, d[i]);

        ck_assert_msg(strcmp(s21Str, origStr) == 0,
                      "test failed on i = %d, \ns21 : |%s|, \norig: |%s|", i,
                      s21Str, origStr);
    }
}
END_TEST

START_TEST(fSpecTest0) {
    char formatStr[100] = "%f word";
    int i;
    float d[] = {-42,
                 -123.456789,
                 42.0,
                 1234567.89012345,
                 1.00000000000000018,
                 555555.55555555555555555,
                 -8,
                 0.085};

    for (i = 0; i < 7; i++) {
        char s21Str[4000] = {0};
        s21_sprintf(s21Str, formatStr, d[i]);

        char origStr[4000] = {0};
        sprintf(origStr, formatStr, d[i]);

        ck_assert_msg(strcmp(s21Str, origStr) == 0,
                      "test failed on i = %d, \ns21 : |%s|, \norig: |%s|", i,
                      s21Str, origStr);
    }
}
END_TEST

START_TEST(fSpecTest1) {
    char formatStr[100] = "%+f word";
    int i;
    float d[] = {-42,
                 -123.456789,
                 42.0,
                 1234567.89012345,
                 1.00000000000000018,
                 555555.55555555555555555,
                 -8,
                 0.085};

    for (i = 0; i < 7; i++) {
        char s21Str[4000] = {0};
        s21_sprintf(s21Str, formatStr, d[i]);

        char origStr[4000] = {0};
        sprintf(origStr, formatStr, d[i]);

        ck_assert_msg(strcmp(s21Str, origStr) == 0,
                      "test failed on i = %d, \ns21 : |%s|, \norig: |%s|", i,
                      s21Str, origStr);
    }
}
END_TEST

START_TEST(fSpecTest2) {
    char formatStr[100] = "%#0.1f word";
    int i;
    float d[] = {-42,
                 -123.456789,
                 42.0,
                 1234567.89012345,
                 1.00000000000000018,
                 555555.55555555555555555,
                 -8,
                 0.085};

    for (i = 0; i < 7; i++) {
        char s21Str[4000] = {0};
        s21_sprintf(s21Str, formatStr, d[i]);

        char origStr[4000] = {0};
        sprintf(origStr, formatStr, d[i]);

        ck_assert_msg(strcmp(s21Str, origStr) == 0,
                      "test failed on i = %d, \ns21 : |%s|, \norig: |%s|", i,
                      s21Str, origStr);
    }
}
END_TEST

START_TEST(fSpecTest3) {
    char formatStr[100] = "%.*f word";
    int i;
    float d[] = {-42,
                 -123.456789,
                 42.0,
                 1234567.89012345,
                 1.00000000000000018,
                 555555.55555555555555555,
                 -8,
                 0.085};

    for (i = 0; i < 7; i++) {
        char s21Str[4000] = {0};
        s21_sprintf(s21Str, formatStr, -1, d[i]);

        char origStr[4000] = {0};
        sprintf(origStr, formatStr, -1, d[i]);

        ck_assert_msg(strcmp(s21Str, origStr) == 0,
                      "test failed on i = %d, \ns21 : |%s|, \norig: |%s|", i,
                      s21Str, origStr);
    }
}
END_TEST

START_TEST(fSpecTest4) {
    char formatStr[100] = "%0.5f word";
    int i;
    float d[] = {-42,
                 -123.456789,
                 42.0,
                 1234567.89012345,
                 1.00000000000000018,
                 555555.55555555555555555,
                 -8,
                 0.085};

    for (i = 0; i < 7; i++) {
        char s21Str[4000] = {0};
        s21_sprintf(s21Str, formatStr, -1, d[i]);

        char origStr[4000] = {0};
        sprintf(origStr, formatStr, -1, d[i]);

        ck_assert_msg(strcmp(s21Str, origStr) == 0,
                      "test failed on i = %d, \ns21 : |%s|, \norig: |%s|", i,
                      s21Str, origStr);
    }
}
END_TEST

START_TEST(fSpecTest5) {
    char formatStr[100] = "%.f word";
    int i;
    float d[] = {-42,
                 -123.456789,
                 42.0,
                 1234567.89012345,
                 1.00000000000000018,
                 555555.55555555555555555,
                 -8,
                 0.085};

    for (i = 0; i < 7; i++) {
        char s21Str[4000] = {0};
        s21_sprintf(s21Str, formatStr, d[i]);

        char origStr[4000] = {0};
        sprintf(origStr, formatStr, d[i]);

        ck_assert_msg(strcmp(s21Str, origStr) == 0,
                      "test failed on i = %d, \ns21 : |%s|, \norig: |%s|", i,
                      s21Str, origStr);
    }
}
END_TEST

START_TEST(fSpecTest6) {
    char formatStr[100] = "%.10f word";
    int i;
    float d[] = {-42,
                 -123.456789,
                 42.0,
                 1234567.89012345,
                 1.00000000000000018,
                 555555.55555555555555555,
                 -8,
                 0.085};

    for (i = 0; i < 7; i++) {
        char s21Str[4000] = {0};
        s21_sprintf(s21Str, formatStr, d[i]);

        char origStr[4000] = {0};
        sprintf(origStr, formatStr, d[i]);

        ck_assert_msg(strcmp(s21Str, origStr) == 0,
                      "test failed on i = %d, \ns21 : |%s|, \norig: |%s|", i,
                      s21Str, origStr);
    }
}
END_TEST

START_TEST(oSpecTest0) {
    char formatStr[100] = "%o word";
    char origStr[300] = "";
    char s21Str[300] = "";

    s21_sprintf(s21Str, formatStr, 127);
    sprintf(origStr, formatStr, 127);

    ck_assert(strcmp(s21Str, origStr) == 0);
}
END_TEST

START_TEST(oSpecTest1) {
    char formatStr[100] = "%#o word";
    char origStr[300] = "";
    char s21Str[300] = "";

    s21_sprintf(s21Str, formatStr, 127);
    sprintf(origStr, formatStr, 127);

    ck_assert(strcmp(s21Str, origStr) == 0);
}
END_TEST

START_TEST(oSpecTest2) {
    char formatStr[100] = "%0o word";
    char origStr[300] = "";
    char s21Str[300] = "";

    s21_sprintf(s21Str, formatStr, 127);
    sprintf(origStr, formatStr, 127);

    ck_assert(strcmp(s21Str, origStr) == 0);
}
END_TEST

START_TEST(sSpecTest0) {
    char formatStr[100] = "%s word";
    char origStr[300] = "";
    char s21Str[300] = "";

    s21_sprintf(s21Str, formatStr, "string");
    sprintf(origStr, formatStr, "string");

    ck_assert(strcmp(s21Str, origStr) == 0);
}
END_TEST

START_TEST(sSpecTest1) {
    char formatStr[100] = "%100s word";
    char origStr[300] = "";
    char s21Str[300] = "";

    s21_sprintf(s21Str, formatStr, "string");
    sprintf(origStr, formatStr, "string");

    ck_assert(strcmp(s21Str, origStr) == 0);
}
END_TEST

START_TEST(xSpecTest0) {
    char formatStr[100] = "%x word";
    char origStr[300] = "";
    char s21Str[300] = "";

    s21_sprintf(s21Str, formatStr, 127);
    sprintf(origStr, formatStr, 127);

    ck_assert(strcmp(s21Str, origStr) == 0);
}
END_TEST

START_TEST(pSpecTest0) {
    char formatStr[100] = "%p word";
    char origStr[300] = "";
    char s21Str[300] = "";

    char* ptr = "stringWithPtr";

    s21_sprintf(s21Str, formatStr, ptr);
    sprintf(origStr, formatStr, ptr);

    ck_assert(strcmp(s21Str, origStr) == 0);
}
END_TEST

START_TEST(nSpecTest0) {
    char origStr[300] = "";
    char s21Str[300] = "";

    int origCount;
    int s21Count;

    s21_sprintf(s21Str, "word%n", &s21Count);
    sprintf(origStr, "word%n", &origCount);

    ck_assert(strcmp(s21Str, origStr) == 0);

    ck_assert(origCount == s21Count);
}
END_TEST

START_TEST(precentSpecTest0) {
    char formatStr[100] = "%% word%%d%d";
    char origStr[300] = "";
    char s21Str[300] = "";

    s21_sprintf(s21Str, formatStr, 5);
    sprintf(origStr, formatStr, 5);

    ck_assert(strcmp(s21Str, origStr) == 0);
}
END_TEST

START_TEST(stringSpecTest0) {
    char formatStr[100] = "%.*s";
    char origStr[300] = "";
    char s21Str[300] = "";
    char string[300] = "HOLLA amigos";

    s21_sprintf(s21Str, formatStr, 10, string);
    sprintf(origStr, formatStr, 10, string);

    ck_assert(strcmp(s21Str, origStr) == 0);
}
END_TEST

START_TEST(uSpecTest0) {
    char formatStr[100] = "%u word";
    char origStr[300] = "";
    char s21Str[300] = "";

    s21_sprintf(s21Str, formatStr, 1);
    sprintf(origStr, formatStr, 1);

    ck_assert_msg(strcmp(s21Str, origStr) == 0,
                  "test failed \ns21 : |%s|, \norig: |%s|", s21Str, origStr);
}
END_TEST

START_TEST(uSpecTest1) {
    char formatStr[100] = "%lu word";
    char origStr[300] = "";
    char s21Str[300] = "";

    s21_sprintf(s21Str, formatStr, 1);
    sprintf(origStr, formatStr, 1);

    ck_assert_msg(strcmp(s21Str, origStr) == 0,
                  "test failed \ns21 : |%s|, \norig: |%s|", s21Str, origStr);
}
END_TEST

START_TEST(uSpecTest2) {
    char formatStr[100] = "%hu word";
    char origStr[300] = "";
    char s21Str[300] = "";

    s21_sprintf(s21Str, formatStr, 1);
    sprintf(origStr, formatStr, 1);

    ck_assert_msg(strcmp(s21Str, origStr) == 0,
                  "test failed \ns21 : |%s|, \norig: |%s|", s21Str, origStr);
}
END_TEST

START_TEST(gSpecTest0) {
    char formatStr[100] = "%g word";
    int i;

    char s21Str[4000] = {0};
    s21_sprintf(s21Str, formatStr, 0.1);

    char origStr[4000] = {0};
    sprintf(origStr, formatStr, 0.1);

    ck_assert_msg(strcmp(s21Str, origStr) == 0,
                  "test failed on i = %d, \ns21 : |%s|, \norig: |%s|", i,
                  s21Str, origStr);
}
END_TEST

TCase* CreateSprintfCase() {
    TCase* sprintfCase = tcase_create("sprintf case");

    tcase_add_test(sprintfCase, dFlagTest0);
    tcase_add_test(sprintfCase, dFlagTest1);
    tcase_add_test(sprintfCase, dFlagTest2);
    tcase_add_test(sprintfCase, dFlagTest3);
    tcase_add_test(sprintfCase, dFlagTest4);
    tcase_add_test(sprintfCase, dFlagTest5);
    tcase_add_test(sprintfCase, dFlagTest6);
    tcase_add_test(sprintfCase, dFlagTest7);
    tcase_add_test(sprintfCase, dFlagTest8);
    tcase_add_test(sprintfCase, dFlagTest9);

    tcase_add_test(sprintfCase, cSpecTest0);
    tcase_add_test(sprintfCase, cSpecTest1);

    tcase_add_test(sprintfCase, iSpecTest0);

    tcase_add_test(sprintfCase, eSpecTest5);
    tcase_add_test(sprintfCase, eSpecTest6);

    tcase_add_test(sprintfCase, fSpecTest0);
    tcase_add_test(sprintfCase, fSpecTest1);
    tcase_add_test(sprintfCase, fSpecTest2);
    tcase_add_test(sprintfCase, fSpecTest3);
    tcase_add_test(sprintfCase, fSpecTest4);
    tcase_add_test(sprintfCase, fSpecTest5);
    tcase_add_test(sprintfCase, fSpecTest6);

    tcase_add_test(sprintfCase, oSpecTest0);
    tcase_add_test(sprintfCase, oSpecTest1);
    tcase_add_test(sprintfCase, oSpecTest2);

    tcase_add_test(sprintfCase, sSpecTest0);
    tcase_add_test(sprintfCase, sSpecTest1);

    tcase_add_test(sprintfCase, xSpecTest0);

    tcase_add_test(sprintfCase, pSpecTest0);

    tcase_add_test(sprintfCase, nSpecTest0);

    tcase_add_test(sprintfCase, uSpecTest0);
    tcase_add_test(sprintfCase, uSpecTest1);
    tcase_add_test(sprintfCase, uSpecTest2);

    tcase_add_test(sprintfCase, gSpecTest0);

    tcase_add_test(sprintfCase, precentSpecTest0);
    tcase_add_test(sprintfCase, stringSpecTest0);

    return sprintfCase;
}
