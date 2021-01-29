CC = gcc
GCOV = gcovr

TST_LIBS = -lcheck -lm -lpthread -lrt -lsubunit
COV_LIBS = -lgcov -coverage

SRC_DIR = src
HDR_DIR = include
TST_DIR = test
OUT_DIR = build
COV_DIR = coverage

SRC_FILES = $(addprefix $(SRC_DIR)/, *.c)
HDR_FILES = $(addprefix $(HDR_DIR)/, *.h)
TST_FILES = $(addprefix $(TST_DIR)/, *.c)

GCOV_FLAGS = -r . --html --html-details
CFLAGS = -c -Wall -Wextra -I$(HDR_DIR)
DEBUG_FLAGS = -g -c -Wall -Wextra -I$(HDR_DIR)
PROFILE_FLAGS = -fprofile-arcs -ftest-coverage

all: coverage.html

debug: data_structures_gdb.o

build: data_structures.o 

data_structures_gdb.o: $(SRC_FILES) $(HDR_FILES)
	mkdir -p $(OUT_DIR)
	$(CC) $(DEBUG_FLAGS) $(PROFILE_FLAGS) $(SRC_FILES) -o $(OUT_DIR)/data_structures_gdb.o 

data_structures.o: $(SRC_FILES) $(HDR_FILES)
	mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) $(PROFILE_FLAGS) $(SRC_FILES) -o $(OUT_DIR)/data_structures.o 

test_src.o: $(TST_FILES)
	mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) $(TST_FILES) -o $(OUT_DIR)/test_src.o $(DEBUG_FLAGS)

test_src: data_structures_gdb.o test_src.o
	mkdir -p $(OUT_DIR)
	$(CC) $(OUT_DIR)/data_structures_gdb.o $(OUT_DIR)/test_src.o $(TST_LIBS) $(COV_LIBS) -o $(OUT_DIR)/test_src

test: test_src
	./build/test_src

coverage.html: test
	$(GCOV) $(GCOV_FLAGS) -o coverage.html
	mkdir -p $(COV_DIR)
	mv coverage.* $(COV_DIR)/

valgrind: test_src
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes -s ./build/test_src 

valgrind-v: test_src
	valgrind --tool=memcheck -v --leak-check=full --show-reachable=yes ./build/test_src

massif: test_src
	valgrind --tool=massif --massif-out-file=/home/incvis/snap/massif-visualizer/massif.out ./build/test_src 


.PHONY: clean debug

clean:
	-rm -rf $(OUT_DIR) $(COV_DIR)