# Compiler and flags
CXX = clang++
CXXFLAGS = -Wall -std=c++17 -Werror -Wpedantic -pedantic -O2

# Directories
SRC_DIR = src
TARGET_DIR = target

# Source and target files
SRC = $(SRC_DIR)/main.cpp
TARGET = $(TARGET_DIR)/main

# Default target
.PHONY: all
all: $(TARGET_DIR) $(TARGET)

# Rule to build the target (executable)
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to create the build directory if it doesn't exist
$(TARGET_DIR):
	mkdir -p $(TARGET_DIR)

# Clean up build artifacts
.PHONY: clean
clean:
	rm -rf $(TARGET_DIR)

.PHONY: run
run: all
	./$(TARGET)
