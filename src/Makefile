flags = -Wall -Werror -Wextra
checkFlags = -I$(HOME)/homebrew/include -L$(HOME)/homebrew/Cellar/check/0.15.2/lib -lcheck


all: s21_string.a test

s21_string.a:
	gcc s21_string.c -c $(flags)
	ar -r s21_string.a s21_string.o
	rm s21_string.o

test: s21_string.a
	gcc s21_string.a s21_string-test.c ./tests/*.c $(flags) $(checkFlags)

clean: clear all

clear:
	$(RM) *.o *.a a.out

pol: s21_string.a
	gcc polygon.c s21_string.a $(checkFlags) $(flags)