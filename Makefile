CC = clang
CFLAGS = -ansi 

SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
LIB_DIR = lib
TESTS_DIR = tests

CONTAINERS_LIB = $(LIB_DIR)/libcontainers.so

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))

TESTS_SRC_FILES = $(wildcard $(TESTS_DIR)/*.c)
TESTS_BIN_FILES = $(patsubst $(TESTS_DIR)/%.c, $(TESTS_DIR)/%, $(TESTS_SRC_FILES))

all: $(CONTAINERS_LIB) $(TESTS_BIN_FILES)

$(CONTAINERS_LIB): $(OBJ_FILES)
	@mkdir -p $(LIB_DIR)
	$(CC) $(CFLAGS) -shared -fPIC $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

containers: $(CONTAINERS_LIB)

run_tests: $(TESTS_BIN_FILES)
	@for test in $^; do ./$$test; done

$(TESTS_DIR)/%: $(TESTS_DIR)/%.c $(CONTAINERS_LIB)
	$(CC) $(CFLAGS) -L./$(LIB_DIR) -lcontainers $< -o $@

clean:
	@rm -rf $(BUILD_DIR)

clean_all: clean
	@rm -rf $(LIB_DIR)
	@rm $(TESTS_BIN_FILES)

.PHONY: all containers run_tests clean clean_all