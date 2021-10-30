#include "s21_string.h"

int main(void) {
  char a[255] = "holla, how are u ?";
  int b = 0;

  s21_wrapper_sprintf(a, "|%#10.10e\\|/ _  word|", 133.3);
  printf("%s~~%d\n", a, b);

  sprintf(a, "|%10.10e\\|/ _  word|", 133.3);
  printf("%s~~%d",   a, b);

  return 0;
}
