#include "s21_string/s21_string.h"

int main(void) {
    char string[1024];
    s21_wrapper_sprintf(string, "%d", 5);
    printf("%s", string);
}
