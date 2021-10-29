COMPILLER = gcc
FLAG = -Werror -Wall -Wextra
FILE = main.c

all: clean cpplint cppcheck build

biuld: clean
	${COMPILLER} ${FLAG} ${FILE} -o main.o

cpplint:
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py CPPLINT.cfg ${FILE}
	rm -rf CPPLINT.cfg

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem ${FILE}

clean:
	rm -rf *.o