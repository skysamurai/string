CC = gcc
e_flags = -Wall -Wextra -Werror
# c_flags = -g3
h_path = -I./tests/* -I./s21_string -I./s21_string/s21_sprintf
#check_flags = -L$(HOME)/homebrew/Cellar/check/0.15.2/lib -lcheck 										#MAC
check_flags = -lcheck_pic -pthread -lrt -lm -lsubunit		#LINUX
target = a.o
# -L$(HOME)/homebrew/Cellar/check/0.15.2/lib
# -I${HOME}/homebrew/include

all: clean programm tests


s21_string.o:
	$(CC) $(c_flags) -c ./s21_string/*.c ./s21_string/s21_sprintf/*.c $(h_path)


s21_string.a: s21_string.o
	ar rcs libs21_string.a *.o


programm: s21_string.a
	$(CC) $(c_flags) main.c -L. -ls21_string -o $(target)


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
