LIB_NAME = data_structures

CC = gcc
GCOV = gcovr

TST_LIBS = -lcheck -lm -lpthread -lrt -lsubunit
COV_LIBS = -lgcov -coverage

SRC_DIR = src
HDR_DIR = include
TST_DIR = test
OUT_DIR = build
COV_DIR = coverage

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)
TST_SRCS = $(wildcard $(TST_DIR)/*.c)
TST_OBJS = $(TST_SRCS:$(TST_DIR)/%.c=$(OUT_DIR/%.o))

GCOV_FLAGS = -r . --html --html-details
CFLAGS = -c -Wall -Wextra -I$(HDR_DIR)
DEBUG_FLAGS = -g -Wall -Wextra -I$(HDR_DIR)
PROFILE_FLAGS = -fprofile-arcs -ftest-coverage


.PHONY: clean valgrind valgrind-v test coverage

	
$(LIB_NAME):
	mkdir -p $(OUT_DIR)
	$(CC) $(DEBUG_FLAGS) -c $(SRC_DIR)/*.c 
	ar -rc build/data_structures.a *.o 
	rm -f *.o

test_src: $(LIB_NAME)
	$(CC) $(DEBUG_FLAGS) test/*.c $(TST_LIBS) -Lbuild -l:data_structures.a -o build/test_src

test: test_src
	./build/test_src

coverage.html: test
	$(GCOV) $(GCOV_FLAGS) -o coverage.html
	mkdir -p $(COV_DIR)
	mv coverage.* $(COV_DIR)/

coverage: coverage.html

valgrind: test_src
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes -s ./build/test_src 

valgrind-v: test_src
	valgrind --tool=memcheck -v --leak-check=full --show-reachable=yes ./build/test_src

clean:
	-rm -rf $(OUT_DIR) $(COV_DIR)