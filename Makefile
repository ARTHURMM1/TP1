CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iinclude
LDFLAGS = 
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include
TARGET = $(BIN_DIR)/main

# arquivos fonte
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

# regra default
all: $(TARGET)

# compilar .exe
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJ_FILES) -o $@ $(LDFLAGS)

# compilar .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# rodar
run: all
	$(TARGET)
# debug
debug: CXXFLAGS += -g
debug: clean all

# phony targets
.PHONY: all clean run debug
