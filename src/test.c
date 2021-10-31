#include <stdio.h>
#include <string.h>
#include "s21_string.h"

int  ch = 'r';
char str[] =    "lazy";
char string[] = "The quick brown dog jumps over the lazy fox";
char fmt1[] =   "         1         2         3         4         5";
char fmt2[] =   "12345678901234567890123456789012345678901234567890";

int main(void) {
    char *pdest;
    int result;
    printf("String to be searched:\n             %s\n", string);
    printf("             %s\n             %s\n\n", fmt1, fmt2);

    printf("Search char: %c\n", ch);
    pdest = s21_memchr(string, ch, sizeof(string));
    result = (int)(pdest - string + 1);
    if (pdest != NULL) {
        printf("Result:      %c found at position %d\n", ch, result);
    } else {
        printf("Result:      %c not found\n", ch);
    }
    
   char first[]  = "51111";
   char second[] = "41111";
   int int_arr1[] = {1,1,3,4};
   int int_arr2[] = {1,2,3,4};

   printf( "Compare '%.20s' to '%.20s':\n", first, second );
   result = s21_memcmp( first, second, 5 );
   printf("%d\n", result);
   if( result < 0 )
      printf( "First is less than second.\n" );
   else if( result == 0 )
      printf( "First is equal to second.\n" );
   else
      printf( "First is greater than second.\n" );

   printf( "Compare '%d,%d' to '%d,%d':\n", int_arr1[0], int_arr1[1], int_arr2[0], int_arr2[1]);
   result = s21_memcmp( int_arr1, int_arr2, sizeof(int) * 2 );
   if( result < 0 )
      printf( "int_arr1 is less than int_arr2.\n" );
   else if( result == 0 )
      printf( "int_arr1 is equal to int_arr2.\n" );
   else
      printf( "int_arr1 is greater than int_arr2.\n" );
  
  char str1[] = "Пример строки";
  char str2[40];
  char str3[60];
 
  s21_memcpy (str2, str1, strlen(str1)+1);               // копируем строку str1  и сохраняем в str2
  s21_memcpy (str3, "Копирование успешно выполнено",60); // копируем 60 байт строки и сохраняем в str3
  
  printf("%s\n", str1);
  printf("%s\n", str2);
  printf("%s\n", str3);

  // Исходный массив данных
   unsigned char src2[10]="1234567890";

   // Вывод массива src на консоль
   printf ("src2 old: %s\n",src2);

   // Копируем 3 байт
   s21_memmove (&src2[4], &src2[3], 3);

   // Вывод массива src на консоль
   printf ("src2 new: %s\n",src2);
  
  // Исходный массив данных
   unsigned char src[10]="1234567890";

   // Вывод массива src на консоль
   printf ("src old: %s\n",src);

   // Копируем 3 байт
   memmove (&src[4], &src[3], 3);

   // Вывод массива src на консоль
   printf ("src new: %s\n",src);

   // Исходный массив
   unsigned char src21[15]="1234567890";
 
   // Заполняем массив символом ‘1’
   memset (src21, '1', 10);

   // Вывод массива src на консоль
   printf ("src21: %s\n",src21);

   // Исходный массив
   unsigned char src22[15]="1234567890";
 
   // Заполняем массив символом ‘1’
   s21_memset (src22, '1', 10);

   // Вывод массива src на консоль
   printf ("src22: %s\n",src22);
}
