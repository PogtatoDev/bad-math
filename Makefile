CXX      := g++
CXXFLAGS := -Wall -Wextra -std=c++20 -Iinclude -O3

SRC_DIR  := src
OBJ_DIR  := obj
BIN_DIR  := tests

TARGET   := $(BIN_DIR)/tests.out

SRCS     := $(wildcard $(SRC_DIR)/*.cpp)
OBJS     := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(BIN_DIR)/tests.cpp

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

clean_bin:
	rm -rf $(TARGET)

.PHONY: all clean