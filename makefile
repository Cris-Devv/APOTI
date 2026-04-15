# ========================================
# MAKEFILE - Sistema de Multas em C
# ========================================

# Compilador e flags de compilação
CC = gcc
CFLAGS = -Wall -Wextra -I./include

# Diretórios do projeto
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include
DATA_DIR = data

# Arquivo executável final
TARGET = $(BUILD_DIR)/multas

# Arquivos FONTE a compilar
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/extras.c \
       $(SRC_DIR)/multas.c \
       $(SRC_DIR)/motoristas.c \
       $(SRC_DIR)/veiculos.c \
       $(SRC_DIR)/agentes.c \
       $(SRC_DIR)/login.c

# Converte cada .c em seu arquivo .o correspondente
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# HEADERS que as compilações dependem
HEADERS = $(INCLUDE_DIR)/multas.h $(INCLUDE_DIR)/extras.h $(INCLUDE_DIR)/motoristas.h $(INCLUDE_DIR)/veiculos.h $(INCLUDE_DIR)/agentes.h $(INCLUDE_DIR)/login.h

# ========================================
# REGRAS
# ========================================

# Regra padrão (executada com 'make' ou 'mingw32-make')
all: $(BUILD_DIR) $(DATA_DIR) $(TARGET)
	@echo Compilacao concluida com sucesso!

# Cria o diretório build se não existir
$(BUILD_DIR):
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)

# Cria o diretório data se não existir
$(DATA_DIR):
	@if not exist $(DATA_DIR) mkdir $(DATA_DIR)

# Linka os .o e gera o executável final
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	@echo Executavel gerado: $@

# Regra genérica para compilar cada .c em .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo Compilado: $<

# Remove os arquivos gerados (clean)
clean:
	@if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)
	@if exist $(DATA_DIR) rmdir /s /q $(DATA_DIR)
	@echo Build removido!

# Executa o programa
run: all
	$(TARGET)

# Mostra informações do projeto
info:
	@echo === INFORMACOES DO PROJETO ===
	@echo Compilador: $(CC)
	@echo Flags: $(CFLAGS)
	@echo Arquivos fonte: $(SRCS)
	@echo Arquivos objeto: $(OBJS)
	@echo Executavel: $(TARGET)

# Declara que essas não são arquivos reais
.PHONY: all clean run info