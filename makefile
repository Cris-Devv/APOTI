# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -I./include

# Pastas
SRC_DIR = src
BUILD_DIR = build

# Arquivos: pega todos os .c em src/ e mapeia para .o em build/
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Nome do executável final
TARGET = $(BUILD_DIR)/multas

# Regra padrão
all: $(BUILD_DIR) $(TARGET)

# Cria a pasta build se não existir
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Linka os .o e gera o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compila cada .c em seu respectivo .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Remove os arquivos gerados
clean:
	rm -rf $(BUILD_DIR)

# Evita conflito se existir um arquivo chamado "all" ou "clean"
.PHONY: all clean