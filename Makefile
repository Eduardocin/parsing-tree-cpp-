# Makefile para Parsing Tree C++

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
SRCDIR = ParseTree
OUTDIR = $(SRCDIR)/output
TARGET = $(OUTDIR)/main.exe

# Arquivos fonte
SOURCES = $(SRCDIR)/main.cpp $(SRCDIR)/parse.cpp $(SRCDIR)/expressions.cpp
HEADERS = $(SRCDIR)/parser.h $(SRCDIR)/expressions.h

# Arquivo de entrada
INPUT = $(SRCDIR)/input

# Regra padrão
all: $(TARGET)

# Compilar o executável
$(TARGET): $(SOURCES) $(HEADERS) | $(OUTDIR)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Criar diretório de saída se não existir
$(OUTDIR):
	mkdir -p $(OUTDIR)

# Executar o programa
run: $(TARGET)
	$(TARGET) < $(INPUT)

# Limpar arquivos gerados
clean:
	rm -rf $(OUTDIR)

# Executar testes
test: $(TARGET)
	@echo "Executando testes..."
	$(TARGET) < $(INPUT)

# Compilar em modo debug
debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

# Mostrar ajuda
help:
	@echo "Comandos disponíveis:"
	@echo "  make        - Compilar o projeto"
	@echo "  make run    - Compilar e executar"
	@echo "  make test   - Executar testes"
	@echo "  make debug  - Compilar em modo debug"
	@echo "  make clean  - Limpar arquivos gerados"
	@echo "  make help   - Mostrar esta ajuda"

.PHONY: all run clean test debug help
