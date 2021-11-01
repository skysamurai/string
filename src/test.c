#include <stdio.h>
#include <string.h>
#include "s21_string.h"
#include <stdlib.h>

int main(void) {

   // Исходный массив
   char src[22]="     Hello World-----\0";
   char new_src[5]="* \'-\0";
 
/*    // Заполняем массив символом ‘1’
   memset (src, 'a', 10);

   // Вывод массива src на консоль
   printf ("src: %s-\n",src);

   printf ("s21_strlen: %d\n",s21_strlen(src));

   printf ("s21_strchr: %s\n",s21_strchr(src, 108));

   printf ("src: %s\n", src);

   char* upper = (char*)s21_to_upper(src);

   printf ("s21_to_upper: %s\n",upper);

   free(upper);

   printf ("src: %s\n", src);

   char* lower = (char*)s21_to_lower(src);

   printf ("s21_to_lower: %s\n", lower);

   free(lower);

   printf ("src: %s\n", src); */

/*    printf ("src: %s\n", src);

   printf ("src2: %s\n", new_src);

   char* ins = (char*)s21_insert(src, new_src, 3);

   printf ("ins: %s\n",ins);

   printf ("src: %s\n", src);

   printf ("src2: %s\n", new_src);

   free(ins); */

   printf ("src: %s\n", src);

   printf ("src2: %s\n", new_src);

   char* trim = (char*)s21_trim(src, new_src);

   printf ("trim: -%s-\n",trim);

   printf ("src: %s\n", src);

   printf ("src2: %s\n", new_src);

   printf ("src: %s\n", src);

   free(trim);

}
