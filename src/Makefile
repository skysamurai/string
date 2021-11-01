GCC = gcc -Wall -Wextra -Werror -std=c11

clean:
	rm -f *.o *.out *.a

cfg:
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg

cpplint:
	python3 ../materials/linters/cpplint.py --extensions=c *.c

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

check:
	clear
	$(MAKE) cppcheck
	$(MAKE) cpplint
	$(MAKE) cpplint

s21_string.o:
	$(GCC) -c s21_string.c

s21_string.a: s21_string.o
	ar rcs libs21_string.a s21_string.o
	
test: s21_string.a
	$(GCC) test.c -L. -ls21_string
	
all: s21_string.a
	$(MAKE) clean
	$(MAKE) s21_string.a
	$(MAKE) test 
	
