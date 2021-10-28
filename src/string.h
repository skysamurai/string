#ifndef SRC_STRING_H_
#define SRC_STRING_H_

// The pointer has the size of the system's bit depth.
// For example in 32 bit system sizeof(void*) will 4 bytes.
// Therefore, we will convert the null pointer to the void* type.
// Theoretically, any other type can be used instead of void*
// because the pointer size is fixed by system`s bit depth.
#define NULL (void*)0

int s21_sprintf(char *str, char *format, ...);

#endif  // SRC_STRING_H_
