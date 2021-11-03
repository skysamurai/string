EFLAGS = -Wextra -Werror -Wpedantic -O2
COMPILLER = gcc
FILE = main.c

all: clean build run

build: clean
	${COMPILLER} *.c -o main.o

# cpplint:
# 	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
# 	python3 ../materials/linters/cpplint.py CPPLINT.cfg ${FILE}
# 	rm -rf CPPLINT.cfg
run:
	./main.o

# cppcheck:
# 	cppcheck --enable=all --suppress=missingIncludeSystem ${FILE}

clean:
	rm -rf *.o