#include "string.h"

#define s21


int main(void) {
  char a[255] = "привет, как у вас дела ?";
  #ifndef s21
    sprintf(a, "%daaa%daa%da%d%d", 1, 2, 3, 4, 5);
  #else
    s21_sprintf(a, "%d   %d  %d %d%d", 1, 2, 3, 4, 5);
  #endif
  int* b = NULL;
  return 0;
}