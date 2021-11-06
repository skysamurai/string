CC = gcc
e_flags = -Wall -Wextra -Werror -g3
# h_path = -I${HOME}/homebrew/include -I./tests/* -I./s21_string -I./s21_string/s21_sprintf
# check_flags = -L$(HOME)/homebrew/Cellar/check/0.15.2/lib -lcheck
h_path = -I./tests/* -I./s21_string -I./s21_string/s21_sprintf
# check_flags = -L$(HOME)/homebrew/Cellar/check/0.15.2/lib -lcheck
target = a.o

all: programm tests

s21_string.o:
	$(CC) -c ./s21_string/*.c ./s21_string/s21_sprintf/*.c $(h_path)

s21_string.a: s21_string.o
	ar rcs libs21_string.a *.o

programm:
	$(CC) main.c -L. -ls21_string -o $(target)

test:
	$(CC) ./tests/*.c -L. -ls21_string $(check_flags) -o $(target) -I${HOME}/homebrew/include

clean:
	rm -rf *.o* *.a

cls:
	clear

run_programm:
	./$(target)

f_prog: cls clean s21_string.a programm run_programm

f_test: cls clean s21_string.a test run_programm