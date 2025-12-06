# Compiler and flags
CC = gcc
CFLAGS = -g -Wall -Wextra -std=c17 -Iinclude

# Output directories
BIN_DIR = bin
OBJ_DIR = build

# Source files
SRC_DIR = src test
SRC = src/*.c

# Object files
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# Output binary
BIN = $(BIN_DIR)/ooc

# Default target
all: $(BIN)

# Link object files into final binary
$(BIN): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJ) -o $(BIN)

# Compile each C file into an object file
$(OBJ_DIR)/%.o: src/%.c test/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts via CLI parameter
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
