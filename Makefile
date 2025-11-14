# --- Variáveis ---

# Compilador
CC = gcc

# Diretórios
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Encontra todos os arquivos .c no diretório src e seus subdiretórios
SRCS = $(shell find $(SRC_DIR) -name '*.c')

# Mapeia os arquivos .c para arquivos .o no diretório build
# Ex: "src/ui/menu.c" se torna "build/ui/menu.o"
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# O executável final
TARGET = $(BUILD_DIR)/main

# Flags de Compilação
# -I<dir> informa ao gcc onde procurar pelos arquivos .h
# -Wall -Wextra são para mostrar todos os avisos (recomendado)
CFLAGS = -I$(INCLUDE_DIR) -Wall -Wextra

# Flags de Linkagem (ex: -lm para a biblioteca de matemática, se você precisar)
LDFLAGS = -lm

# --- Regras ---

# Regra padrão (o que acontece quando você digita "make")
all: $(TARGET)

# Regra de Linkagem: Como criar o executável final
# Depende de todos os arquivos de objeto (.o)
$(TARGET): $(OBJS)
	@echo "Linking..."
	# Cria o diretório build/ se ele não existir
	@mkdir -p $(@D)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Regra de Compilação: Como transformar um .c em um .o
# Esta regra de padrão lida com todos os seus arquivos .c
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling $<..."
	# Cria os subdiretórios necessários em build/ (ex: build/ui, build/rooms)
	@mkdir -p $(@D)
	# Compila o .c para um .o
	$(CC) $(CFLAGS) -c $< -o $@

# Regra "run": Compila e executa o programa
run: all
	@echo "Running application..."
	./$(TARGET)

# Regra "clean": Remove todos os arquivos compilados
clean:
	@echo "Cleaning build directory..."
	# -f (force) ignora erros se a pasta não existir
	rm -rf $(BUILD_DIR)

# Declara quais regras não são arquivos reais
.PHONY: all clean run