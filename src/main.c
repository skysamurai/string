#include "s21_string.h"
#include "string.h"
#include "time.h"

int main(void) {
  char a[] = "privet, kak dela ?";
  char* tok;
  tok = s21_strtok(S21_NULL, " .,");
  printf("|%s|", tok);
  while((tok = s21_strtok(S21_NULL, ",.")) != S21_NULL) {
    printf("|%s|", tok);
  }

  // char buf[1024] = {'\0'};

  // double number = 1.13494;

  // unsigned int s;
  // unsigned int e;
  // unsigned long long m;

  // getSEM(&s, &e, &m, number);
  // //m |= 1ull << 52ull;

  // int i = 0;
  // long long j = 1;
  // for(i = 0; m != 0; ++i) {
  //   e =  m % 2;
  //   buf[i] = '0' + e;
  //   m /= 2;
  // }
  // --i;

  // m = 0;
  // for(i; i != 0; --i, j <<= 1) {
  //   m += (buf[i] - '0') * j;
  // }

  // sprintf(buf, "%e", number);
  return 0;
}
