#include "s21_string.h"
#include "string.h"
#include "time.h"

int main(void) {
  char a[100] = "holla,?";
  int b = 0;

  clock_t begin = clock();
  //
  s21_wrapper_sprintf(a, "|%d word|", 300);
  printf("\\%s~~%d/", a, b);
  //
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("%f\n", time_spent);

  begin = clock();
  //
              sprintf(a, "|%d word|", 300);
  printf("\\%s~~%d/", a, b);
  //
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("%f\n", time_spent);
  return 0;
}
