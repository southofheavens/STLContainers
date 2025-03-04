CC = clang
CFLAGS = -ansi

SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

OBJ_FILES = $(BUILD_DIR)/main.o $(BUILD_DIR)/vector.o $(BUILD_DIR)/map.o $(BUILD_DIR)/list.o

TARGET = main

all: $(BUILD_DIR) $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_FILES)

$(BUILD_DIR)/main.o: main.c $(INC_DIR)/vector.h $(INC_DIR)/map.h $(INC_DIR)/list.h
	$(CC) $(CFLAGS) -c main.c -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/vector.o: $(SRC_DIR)/vector.c $(INC_DIR)/vector.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/vector.c -o $(BUILD_DIR)/vector.o

$(BUILD_DIR)/map.o: $(SRC_DIR)/map.c $(INC_DIR)/map.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/map.c -o $(BUILD_DIR)/map.o

$(BUILD_DIR)/list.o: $(SRC_DIR)/list.c $(INC_DIR)/list.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/list.c -o $(BUILD_DIR)/list.o

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean