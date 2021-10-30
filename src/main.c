#include "s21_string.h"
#include "string.h"

int main(void) {
  char a[255] = "holla, how are u ?";
  int b;

  s21_sprintf(a, "|%p%n + word|", &a, &b);
  printf("%s~~%d\n", a, b);

      sprintf(a, "|%p%n + word|", &a, &b);
  printf("%s~~%d",   a, b);

  return 0;
}
