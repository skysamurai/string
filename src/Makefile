compiler = gcc
flags = -std=c11 -ggdb3 -D __S21_WORDSIZE_8 -I ./
eflags = -Wextra -Werror -Wpedantic -O2
target = main.o

all: clean
	clear
	$(compiler) *.c -o $(target)
	./main.o
cpplint:
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py CPPLINT.cfg ${FILE}
	rm -rf CPPLINT.cfg

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./main.o

# cppcheck:
# 	cppcheck --enable=all --suppress=missingIncludeSystem ${FILE}

clean:
	rm -rf ./*.o
