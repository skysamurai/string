CC = clang
e_flags = -Wall -Wextra -Werror -g3
h_path = -I${HOME}/.brew/include -I./tests/* -I./s21_string -I./s21_string/s21_sprintf
check_flags = -L$(HOME)/.brew/Cellar/check/0.15.2/lib -lcheck
target = a.o

all: programm tests

programm:
	$(CC) main.c ./s21_string/*.c ./s21_string/s21_sprintf/*.c $(h_path) -o $(target)

test:
	$(CC) ./tests/*.c ./s21_string/*.c ./s21_string/s21_sprintf/*.c $(h_path) $(check_flags) -o $(target)

clean:
	rm -rf *.o*

cls:
	clear

run_programm:
	./$(target)

f_prog: cls clean programm run_programm

f_test: cls clean test run_programm
