#include "./s21_string/s21_sprintf/s21_sprintf.h"
#include "string.h"
#include "error.h"
#include "errno.h"
#include "./s21_string/s21_string.h"

int main(void) {
    char str[255] = {'\0'};
    char spec[] = "aaa%--+#0#5.10d";
    int a = 4;

    s21_sprintf(str, spec, a);
    printf("|%s|\n", str);

    sprintf(str, spec, a);
    printf("|%s|", str);

    if (errno) {
        printf("%s", strerror(errno));
    }

    return 0;
}
