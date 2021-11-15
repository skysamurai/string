#include <check.h>
#include <signal.h>
#include <string.h>

#include "../s21_string.h"
#include "tests.h"

START_TEST(normalEqualTest) {
    char str1[100] = "aaa";
    char str2[100] = "aaa";
    char*  origResult = strncpy(str1, "aaa", 3);
    char*  s21Result = s21_strncpy(str2, "aaa", 3);

<<<<<<< HEAD
    ck_assert_msg(strcmp(s21Result,origResult) == 0,
=======
    ck_assert_msg(strcmp(s21Result, origResult) == 0,
>>>>>>> fb5d7c57d565b50553d2c04a4be6c5a7401c808b
                  "fail for strncpy(\"aaa\", \"aaa\", 3). orig:%s,  s21:%s",
                  origResult, s21Result);
}
END_TEST



START_TEST(normalLessTest) {
    char str1[100] = "aaa";
    char str2[100] = "aaa";
<<<<<<< HEAD
    char*  origResult = strncpy(str1, "123", 3);
    char*  s21Result = s21_strncpy(str2, "123",3);
    ck_assert_msg(strcmp(s21Result,origResult) == 0,
=======
    char*  origResult = strncpy(str1, "12", 98);
    char*  s21Result = s21_strncpy(str2, "12", 98);
    ck_assert_msg(strcmp(s21Result, origResult) == 0,
>>>>>>> fb5d7c57d565b50553d2c04a4be6c5a7401c808b
                  "fail for strncpy(\"aaa\", \"123\",3). orig:%s,  s21:%s",
                  origResult, s21Result);
}
END_TEST

START_TEST(normalMoreTest) {
    char str1[100] = "aaa";
    char str2[100] = "aaa";
    char*  origResult = strncpy(str1, "12345", 3);
    char*  s21Result = s21_strncpy(str2, "12345", 3);

<<<<<<< HEAD
    ck_assert_msg(strcmp(s21Result,origResult) == 0,
=======
    ck_assert_msg(strcmp(s21Result, origResult) == 0,
>>>>>>> fb5d7c57d565b50553d2c04a4be6c5a7401c808b
                  "fail for strncpy(\"aba\", \"12345\", 3). orig:%s,  s21:%s",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg1EmptyTest) { 
<<<<<<< HEAD
char str1[100] = "";
char str2[100] = "";
    char*  origResult = strncpy(str1, "aaa", 3);
    char*  s21Result = s21_strncpy(str2, "aaa", 3);
    ck_assert_msg(strcmp(s21Result,origResult) == 0,
=======
char str1[100] = "\0";
char str2[100] = "\0";
    char*  origResult = strncpy(str1, "aaa", 3);
    char*  s21Result = s21_strncpy(str2, "aaa", 3);
    ck_assert_msg(strcmp(s21Result, origResult) == 0,
>>>>>>> fb5d7c57d565b50553d2c04a4be6c5a7401c808b
                  "fail for strncpy(\"\", \"aaa\", 3). orig:%s,  s21:%s",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg1NULLTest) {  // must return SIGSEGV
    s21_strncpy(S21_NULL, "aaa", 3);
}
END_TEST

START_TEST(arg2EmptyTest) {
    char str1[100] = "aaa";
    char str2[100] = "aaa";
    char*  origResult = strncpy(str1, "", 3);
    char*  s21Result = s21_strncpy(str2, "", 3);
<<<<<<< HEAD
    ck_assert_msg(strcmp(s21Result,origResult) == 0,
=======
    ck_assert_msg(strcmp(s21Result, origResult) == 0,
>>>>>>> fb5d7c57d565b50553d2c04a4be6c5a7401c808b
                  "fail for strncpy(\"aaa\", \"\", 3). orig:%s,  s21:%s",
                  origResult, s21Result);
    
}
END_TEST

START_TEST(arg2NULLTest) {  // must return SIGSEGV
    char str1[100] = "aaa";
    s21_strncpy(str1, S21_NULL, 3);
}
END_TEST

START_TEST(arg3TooMuchTest) {
    char str1[1000] = "aaa";
    char str2[1000] = "aaa";
    char*  origResult = strncpy(str1, "123", 333);
    char*  s21Result = s21_strncpy(str2, "123", 333);

<<<<<<< HEAD
    ck_assert_msg(strcmp(s21Result,origResult) == 0,
=======
    ck_assert_msg(strcmp(s21Result, origResult) == 0,
>>>>>>> fb5d7c57d565b50553d2c04a4be6c5a7401c808b
                  "fail for strncpy(\"aaa\", \"123\", 333). orig:%s,  s21:%s",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg3ZeroTest) {
    char str1[100] = "aaa";
    char str2[100] = "aaa";
    char*  origResult = strncpy(str1, "123", 0);
    char*  s21Result = s21_strncpy(str2, "123", 0);

<<<<<<< HEAD
    ck_assert_msg(strcmp(s21Result,origResult) == 0,
=======
    ck_assert_msg(strcmp(s21Result, origResult) == 0,
>>>>>>> fb5d7c57d565b50553d2c04a4be6c5a7401c808b
                  "fail for strncpy(\"aaa\", \"123\", 0). orig:%s,  s21:%s",
                  origResult, s21Result);
}
END_TEST

START_TEST(arg3NULLTest) {  // must return SIGSEGV
    char str1[100] = "aaa";
    char* nullint = S21_NULL;

    s21_strncpy(str1, "baa", *nullint);
}
END_TEST

TCase* CreateStrncpyCase() {
    TCase* strncpyCase = tcase_create("strncpyCase");

    tcase_add_test(strncpyCase, normalEqualTest);
    tcase_add_test(strncpyCase, normalLessTest);
    tcase_add_test(strncpyCase, normalMoreTest);
    tcase_add_test(strncpyCase, arg3TooMuchTest);
    tcase_add_test(strncpyCase, arg3ZeroTest);
    tcase_add_test(strncpyCase, arg1EmptyTest);
    tcase_add_test(strncpyCase, arg2EmptyTest);

    tcase_add_test_raise_signal(strncpyCase, arg1NULLTest, SIGSEGV);
    tcase_add_test_raise_signal(strncpyCase, arg2NULLTest, SIGSEGV);
    tcase_add_test_raise_signal(strncpyCase, arg3NULLTest, SIGSEGV);

return strncpyCase;
}

// arg Null
