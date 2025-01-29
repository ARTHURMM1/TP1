# Compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -Wall -std=c++11 -Iinclude

# Nome do executável principal
TARGET = main

# Nome do executável de testes
TEST_TARGET = testes

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TESTS_DIR = tests

# Lista de arquivos fonte do programa principal
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Lista de arquivos objeto do programa principal
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Arquivo de teste
TEST_SRC = $(TESTS_DIR)/testes.cpp
TEST_OBJ = $(OBJ_DIR)/testes.o

# Regra padrão
all: $(BIN_DIR)/$(TARGET)

# Regra para criar o executável principal
$(BIN_DIR)/$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regra para compilar os arquivos fonte em objetos
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para compilar o arquivo de testes
$(TEST_OBJ): $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para criar o executável de testes
$(BIN_DIR)/$(TEST_TARGET): $(filter-out $(OBJ_DIR)/main.o, $(OBJS)) $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regra para limpar os arquivos gerados
clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/$(TARGET) $(BIN_DIR)/$(TEST_TARGET)

# Garante que os diretórios existam
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Dependências para garantir que os diretórios sejam criados antes da compilação
$(OBJS): | $(OBJ_DIR)
$(BIN_DIR)/$(TARGET): | $(BIN_DIR)
$(BIN_DIR)/$(TEST_TARGET): | $(BIN_DIR)