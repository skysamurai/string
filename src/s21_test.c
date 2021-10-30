#include <check.h>
#include <stdio.h>
#include <signal.h>
#include "s21_string.h"
#include <string.h> 


START_TEST(s21_strcmpTEST) //Конечно, на практике мы не пишем тесты, обреченные на провал
{ char str1 [] = "privet";
char str2 [] = "privet";

    ck_assert_msg(strcmp( str1 ,str2) == s21_strcmp(str1,str2), "failed on 12");
    
}
END_TEST



int main(void)
{
    Suite *s1 = suite_create("Core"); //Объявляем сьюит
    SRunner *sr = srunner_create(s1); //Лаунчер сьюита
    int nf; // Статус тестов сьюита

    TCase *strcmpCase = tcase_create("sumBaseTest"); //Новый кейс getCase для функции get
    suite_add_tcase(s1, strcmpCase); //Добавляем кейс getCase для запуска
    //В кейс getCase добавляем тесты, описанные выше
    tcase_add_test(strcmpCase, s21_strcmpTEST);
  


   

    //Запустить всё это дело
    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}