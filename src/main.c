#include "s21_string.h"
#include "string.h"

int main(void) {
  char a[255] = "holla, how are u ?";
  s21_sprintf(a, "|%c|", 'f');
  printf("%s\n", a);
      sprintf(a, "|%c|", 'f');
  printf("%s\n", a);
  return 0;
}
