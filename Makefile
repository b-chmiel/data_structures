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
PROFILE_FLAGS = -fprofile-arcs -ftest-coverage

all: coverage.html

data_structures.o: $(SRC_FILES) $(HDR_FILES)
	$(CC) $(CFLAGS) $(PROFILE_FLAGS) $(SRC_FILES) -o data_structures.o 
	mkdir -p $(OUT_DIR)
	mv data_structures.* $(OUT_DIR)/

test_src.o: $(TST_FILES)
	$(CC) $(CFLAGS) $(TST_FILES) -o test_src.o
	mkdir -p $(OUT_DIR)
	mv test_src.* $(OUT_DIR)/

test_src: data_structures.o test_src.o
	$(CC) $(OUT_DIR)/data_structures.o $(OUT_DIR)/test_src.o $(TST_LIBS) $(COV_LIBS) -o test_src
	mkdir -p $(OUT_DIR)
	mv test_src $(OUT_DIR)/

test: test_src
	./build/test_src
	mkdir -p $(COV_DIR)
	mv test.* test_src.* data_structures.* $(COV_DIR)/

coverage.html: test
	$(GCOV) $(GCOV_FLAGS) -o coverage.html
	mkdir -p $(COV_DIR)
	mv coverage.* $(COV_DIR)/

.PHONY: clean

clean:
	-rm -rf build/ coverage/