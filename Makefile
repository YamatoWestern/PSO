# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -g -I./include
LDFLAGS :=

# Directories
SRC_DIR := src
TEST_DIR := test
BUILD_DIR := build
BIN_DIR := bin

# Source files and object files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
TEST_SRCS := $(TEST_DIR)/test_main.cpp
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
TEST_OBJS := $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(TEST_SRCS))

# Executables
EXEC := $(BIN_DIR)/main
TEST_EXEC := $(BIN_DIR)/unittest

# Default target
all: $(EXEC)

# Main executable
$(EXEC): $(OBJS) $(BUILD_DIR)/main.o
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Test executable
$(TEST_EXEC): $(OBJS) $(TEST_OBJS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Rule to build object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Test target
test: $(TEST_EXEC)
	./$(TEST_EXEC)

# Memory leak check target
memcheck: $(TEST_EXEC)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TEST_EXEC)

# Clean target
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Phony targets
.PHONY: all test memcheck clean
