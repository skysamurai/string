compiler = gcc
flags = -std=c11 -ggdb3 -D __S21_WORDSIZE_8 -I ./
eflags = -Wextra -Werror -Wpedantic -O2 -g
target = main.o

all: clean
	clear
	$(compiler) *.c -o $(target)
	./main.o

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./main.o

clean:
	rm -rf ./*.o
