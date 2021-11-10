CC = gcc
ERROR_FLAGS = -Wall -Wextra -Werror
DEBUG_FLAGS = -g3
OPTIM_FLAGS = -O0
h_path = -I./tests/* -I./s21_string -I./s21_string/s21_sprintf
#CHECK_FLAGS = -L$(HOME)/homebrew/Cellar/check/0.15.2/lib -lcheck#MAC
CHECK_FLAGS = -lcheck_pic -pthread -lrt -lm -lsubunit#LINUX


TARGET = main


LIB_SOURCES = parser.c s21_sprintf.c s21_string.c
LIB_OBJECTS = $(patsubst %.c,%.o,$(LIB_SOURCES))
D_LIB_SOURCES = $(patsubst %.c,%.d,$(LIB_SOURCES))

TEST_SOURCES = $(shell find tests/ -type f -name "*.c" )
TEST_OBJECTS = $(patsubst %.c,%.o,$(TEST_SOURCES))
D_TEST_SOURCES = $(patsubst %.c,%.d,$(TEST_SOURCES))

all: s21_string.a test

%.o: %.c
	$(CC) $(OPTIM_FLAGS) $(DEBUG_FLAGS) -c $< -o $@ -MD
include $(wildcart $(D_LIB_SOURCES))

tests/%.o: tests/%.c
	$(CC) $(OPTIM_FLAGS) $(DEBUG_FLAGS) -c $< -o $@ -MD -I$(CURDIR)
include $(wildcart $(D_TEST_SOURCES))

libs21_string.a: $(LIB_OBJECTS)
	ar rc libs21_string.a $^
	ranlib libs21_string.a

s21_string.a: libs21_string.a

test: s21_string.a $(TEST_OBJECTS)
	$(CC) $(OPTIM_FLAGS) $(DEBUG_FLAGS) tests/*.o -L. -ls21_string -o $@ $(CHECK_FLAGS) -MD

tst: test

clean:
	find . -type f -name "*.o" -delete
	find . -type f -name "*.d" -delete

fclean: clean
	rm -f test
	rm -f libs21_string.a
	rm -f $(TARGET)

re: fclean all

.PHONY:
	all clean fclean re

# our target`s zone
$(TARGET): s21_string.a
	$(CC) $(DEBUG_FLAGS) $(OPTIM_FLAGS) $@.c -L. -ls21_string -o $(TARGET)

f_prog: $(TARGET)
	./$(TARGET)

f_test: test
	./test