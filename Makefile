CXX      := clang++
CXXFLAGS := -Wall -Wextra -std=c++20 -Iinclude -O3

SRC_DIR  := ./src
OBJ_DIR  := ./obj
BIN_DIR  := ./tests

TARGET   := $(BIN_DIR)/tests.exe

SRCS     := $(wildcard $(SRC_DIR)/*.cpp)
OBJS     := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(BIN_DIR)/tests.cpp

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

clean_obj:
	rm -rf $(OBJ_DIR)

clean_bin:
	rm -rf $(TARGET)

.PHONY: all clean