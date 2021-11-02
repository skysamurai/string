#include "s21_string.h"
#include "string.h"
#include "time.h"

int main(void) {
  char a[100] = "holla,?";
  int b = 0;

  clock_t begin = clock();
  //
  s21_wrapper_sprintf(a, "|%+.25e word|", 0.642);
  printf("\\%s~~%d/", a, b);
  //
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("%f\n", time_spent);

  char aa[100] = "holla,?";
  begin = clock();
  //
              sprintf(aa, "|%+.25e word|", 0.642);
  printf("\\%s~~%d/", aa, b);
  //
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("%f\n", time_spent);
  return 0;
}
