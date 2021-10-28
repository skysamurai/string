compiler = gcc
flags = -std=c11 -ggdb3
tflags = -Wformat-overflow=0 -Wdiscarded-qualifiers
eflags = -Wall -Wextra -Werror
target = main.o

all:
	rm -rf ./main.o
	clear
	$(compiler) $(flags) $(tflags) *.c -o $(target)
	./main.o

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./main.o
