CC = gcc --coverage
ERROR_FLAGS = -Wall -Wextra -Werror
DEBUG_FLAGS = -g3


OS := $(shell uname)
ifeq ($(OS),Darwin)
	CHECK_FLAGS = -L$(HOME)/homebrew/Cellar/check/0.15.2/lib -lcheck
else ifeq ($(OS), Linux)
	CHECK_FLAGS = -lcheck_pic -pthread -lrt -lm -lsubunit
endif

LIB_SOURCES = parser.c s21_sprintf.c s21_string.c s21_sscanf.c
LIB_OBJECTS = $(patsubst %.c,%.o,$(LIB_SOURCES))
D_LIB_SOURCES = $(patsubst %.c,%.d,$(LIB_SOURCES))

TEST_SOURCES = $(shell find tests -type f -name "*.c" )
TEST_OBJECTS = $(patsubst %.c,%.o,$(TEST_SOURCES))
D_TEST_SOURCES = $(patsubst %.c,%.d,$(TEST_SOURCES))


#include extern makefile text
-include $(wildcard $(D_LIB_SOURCES))
-include $(wildcard $(D_TEST_SOURCES))


all: s21_string.a test


%.o: %.c %.h
	$(CC) $(DEBUG_FLAGS) -MD -c $< -o $@


tests/%.o: tests/%.c tests/tests.h
	$(CC) $(DEBUG_FLAGS) -MD -c $< -o $@


libs21_string.a: $(LIB_OBJECTS)
	ar rc libs21_string.a $^
	ranlib libs21_string.a


s21_string.a: libs21_string.a


test: s21_string.a $(TEST_OBJECTS)
	$(CC) $(DEBUG_FLAGS) tests/*.o -L. -ls21_string -o $@ $(CHECK_FLAGS)

gcov_report: clean test 
	./test
	lcov -t "gcov_report" -o gcov_report.info -c -d . 
	genhtml -o gcov_report gcov_report.info

clean:
	find . -type f -name "*.o" -delete
	find . -type f -name "*.d" -delete
	find . -type f -name "*.gcda" -delete
	find . -type f -name "*.gcno" -delete
	find . -type f -name "*.info" -delete
	rm -rf gcov_report
	rm -f libs21_string.a
	rm -f test
	rm -f main


re: clean all

.PHONY:
	all clean fclean re clear

# our target`s zone
main: s21_string.a
	$(CC) $(DEBUG_FLAGS) $(ERROR_FLAGS) $@.c -L. -ls21_string -o main

clear:
	clear

fprog: clear main
	./main

ftest: clear test
	./test


