# Makefile: https://www.gnu.org/software/make/manual/make.html

# Define the C compiler to use
CC = gcc
# Define compiler flags
# Compiler flags for warnings, errors and GNU extensions
CFLAGS = -Wvla -Wextra -Werror -D_GNU_SOURCE
INCLUDE = -I./include -I../lib

# Directories
BIN_DIR = bin
BUILD_DIR = build
SRC_DIR = src
TEST_DIR = test
LIB_DIR = ../lib

# Colors for better output
COLOR_RESET = \033[0m
COLOR_BLUE = \033[0;34m
COLOR_GREEN = \033[0;32m
COLOR_RED = \033[0;31m
COLOR_YELLOW = \033[1;33m

# Source files
SRC_FILES = $(SRC_DIR)/edit_distance.c $(SRC_DIR)/main_ex2.c
TEST_FILES = $(TEST_DIR)/test_ex2.c
LIB_FILES = $(LIB_DIR)/unity.c

# Object files
OBJ_FILES = $(BUILD_DIR)/edit_distance.o $(BUILD_DIR)/main_ex2.o $(BUILD_DIR)/test_ex2.o $(BUILD_DIR)/unity.o

# Executables
EXEC_MAIN = $(BIN_DIR)/main_ex2
EXEC_TEST = $(BIN_DIR)/test_ex2

# Default target to build everything
all: $(EXEC_MAIN) $(EXEC_TEST)

# Create build and bin directories if they don't exist
.PHONY: directories
directories:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)

# Rules to build object files
$(BUILD_DIR)/edit_distance.o: $(SRC_DIR)/edit_distance.c | directories
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(BUILD_DIR)/main_ex2.o: $(SRC_DIR)/main_ex2.c | directories
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(BUILD_DIR)/test_ex2.o: $(TEST_DIR)/test_ex2.c | directories
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(BUILD_DIR)/unity.o: $(LIB_DIR)/unity.c | directories
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# Rules to link the executables
$(EXEC_MAIN): $(BUILD_DIR)/edit_distance.o $(BUILD_DIR)/main_ex2.o $(BUILD_DIR)/unity.o | directories
	$(CC) $(CFLAGS) -I./include $^ -o $@

$(EXEC_TEST): $(BUILD_DIR)/unity.o $(BUILD_DIR)/test_ex2.o | directories
	$(CC) $(CFLAGS) $(INCLUDE) $^ -o $@

# Rule to run the tests
test: $(EXEC_TEST)
	@echo "Running tests..."
	./$(EXEC_TEST)

# Rule to clean the project
clean:
	@echo "Cleaning build and bin directories..."
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Help rule with colored output
help:
	@echo "Makefile commands:"
	@echo "  all   - Build the entire project"
	@echo "  test  - Run the test executable"
	@echo "  clean - Clean object files and executables"
