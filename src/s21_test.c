#include <check.h>
#include <stdio.h>
#include <signal.h>
#include "s21_string.h"
#include <string.h> 



// START_TEST(s21_strchrTEST) //Конечно, на практике мы не пишем тесты, обреченные на провал
// { char str [] = "privet";
// int c [] = 112;

//     ck_assert_msg(strchr( str ,c) == s21_strchr(str,c), "failed on 12");
    
// }
// END_TEST

START_TEST(s21_strcmpTEST) //Конечно, на практике мы не пишем тесты, обреченные на провал
{ char str1 [] = "privet";
char str2 [] = "privet";

    ck_assert_msg(strcmp( str1 ,str2) == s21_strcmp(str1,str2), "failed on 12");
    
}
END_TEST



int main(void)
{
    Suite *s1 = suite_create("Core"); //Объявляем сьюит
    Suite *s2 = suite_create("Core"); //Объявляем сьюит
    // SRunner *sr = srunner_create(s1); //Лаунчер сьюита
    SRunner *sr = srunner_create(s2); //Лаунчер сьюита
    int nf; // Статус тестов сьюита


//   TCase *strchrCase = tcase_create("GumBaseTest"); //Новый кейс getCase для функции get
//     suite_add_tcase(s1, strchrCase); //Добавляем кейс getCase для запуска
//     //В кейс getCase добавляем тесты, описанные выше
//     tcase_add_test(strchrCase, s21_strchrTEST);

    TCase *strcmpCase = tcase_create("sumBaseTest"); //Новый кейс getCase для функции get
    suite_add_tcase(s2, strcmpCase); //Добавляем кейс getCase для запуска
    //В кейс getCase добавляем тесты, описанные выше
    tcase_add_test(strcmpCase, s21_strcmpTEST);
  


   

    //Запустить всё это дело
    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}