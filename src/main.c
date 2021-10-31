#include "s21_string.h"
#include "string.h"

int main(void) {
  char a[255] = "holla, | wow ||| how are u ?";
  int b = 0;

  s21_wrapper_sprintf(a, "|%10.100e\\|/ _  word|", 300.0000000000000000016);
  printf("%s~~%d\n", a, b);

              sprintf(a, "|%10.100e\\|/ _  word|", 300.0000000000000000016);
  printf("%s~~%d\n",   a, b);


  char c[255] = "Holla, how are u ?";
  char *tok;
  char delim[] = ", ?";
  tok = s21_strtok(c, delim);
  while(tok != NULL) {
    printf("%s|", tok);
    tok = s21_strtok(NULL, delim);
  }

  tok = strtok(c, delim);
  while(tok != NULL) {
    printf("%s|", tok);
    tok = strtok(NULL, delim);
  }

  return 0;
}
