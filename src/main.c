#include "s21_string.h"
#include "string.h"

int main(void) {
  char a[255] = "holla, how are u ?";
  s21_sprintf(a, "||%#20x|aaa% d |% 3.d||", 12345, -1, -34535);
  printf("%s\n", a);
      sprintf(a, "||%#20x|aaa% d |% 3.d||", 12345, -1, -34535);
  printf("%s\n", a);
  return 0;
}
