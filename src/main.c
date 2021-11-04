#include "s21_string/s21_string.h"

int main(void) {
char* origToken = S21_NULL;
    char origString[] = "a string, of, ,tokens\0,after null terminator";

    char* s21Token = S21_NULL;
    char s21String[] = "a string, of, ,tokens\0,after null terminator";

    // origToken = strtok(origString, ",");
    // s21Token = s21_strtok(s21String, ",");

    int i = 0;
    do {
        origToken = strtok(S21_NULL, ",");
        s21Token = s21_strtok(S21_NULL, ",");
        i++;
    } while (origToken != S21_NULL &&
             s21Token != S21_NULL);  // prevent strcmp segfault
}
