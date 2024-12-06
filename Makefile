CC = gcc
CFLAGS = -pedantic -std=c17 -g -O0
WARNINGS = -Wall -Wextra -Wconversion -Wredundant-decls -Wstrict-prototypes
EXTRA = -fsanitize=address -fsanitize=undefined -fsanitize=leak \
		-fstack-protector-strong
BASE_TESTS := $(shell find ./base/ -type f -name '*.c')

# building and testing the base folder only
build_base:
	@$(CC) $(CFLAGS) $(WARNINGS) $(BASE_TESTS) -lcriterion -o test.out
base: build_base
	@./test.out

# TODO: suppress output when DAY is empty
SRC := $(shell find ./base/ ./2024/day-$(DAY)/ -type f -name '*.c' \
	   ! -name 'test.c')
# TODO: avoid running the tests in the base folder here
SRC_AND_TEST := $(shell find ./base/ ./2024/day-$(DAY)/ -type f -name '*.c' \
	   ! -name 'main.c')

build:
	@$(CC) $(CFLAGS) $(WARNINGS) $(EXTRA) $(SRC) -o main.out
test:
	@$(CC) $(CFLAGS) $(WARNINGS) $(SRC_AND_TEST) -lcriterion -o test.out
	@./test.out
run: build
	LSAN_OPTIONS=detect_leaks=1 LSAN_OPTIONS=report_objects=1 ./main.out
clean:
	@rm -f *.o *.out
