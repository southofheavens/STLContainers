CC = clang
CFLAGS = -ansi

SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
LIB_DIR = lib
TESTS_DIR = tests

MAIN_SRC = main.c
MAIN_BIN = main
CONTAINERS_LIB = $(LIB_DIR)/libcontainers.so
TESTS_SRC = $(TESTS_DIR)/tests.c
TESTS_BIN = $(TESTS_DIR)/tests

OBJ_FILES = $(BUILD_DIR)/vector.o $(BUILD_DIR)/map.o $(BUILD_DIR)/list.o $(BUILD_DIR)/utility.o

all: $(MAIN_BIN) $(CONTAINERS_LIB) $(TESTS_BIN)

$(MAIN_BIN): $(MAIN_SRC) $(CONTAINERS_LIB)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -L./$(LIB_DIR) -lcontainers $< -o $@

$(CONTAINERS_LIB): $(OBJ_FILES)
	@mkdir -p $(LIB_DIR)
	$(CC) $(CFLAGS) -shared -fPIC $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

run_tests: $(TESTS_BIN)
	./$(TESTS_BIN)

$(TESTS_BIN): $(TESTS_SRC) $(CONTAINERS_LIB)
	$(CC) $(CFLAGS) -L./$(LIB_DIR) -lcontainers $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run_tests clean