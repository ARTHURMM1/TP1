# Variáveis
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iinclude
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_SRC = $(SRC_DIR)/teste.cpp
TEST_BIN = $(BIN_DIR)/teste
EXEC = $(BIN_DIR)/main

# Arquivos fonte e objetos
SRCS = $(filter-out $(TEST_SRC), $(wildcard $(SRC_DIR)/*.cpp))
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Regras
all: $(EXEC)

# Regra para compilar o programa principal
$(EXEC): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Regra para compilar os arquivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para compilar o teste
teste: $(TEST_SRC)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $< -o $(TEST_BIN)

# Limpeza
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Remoção completa
distclean: clean
	rm -rf html latex

.PHONY: all clean distclean teste
