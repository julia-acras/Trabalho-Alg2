# Compilador e flags
CC     = gcc
CFLAGS = -Wall -Wextra -std=c11

# Nome do executável
BIN    = menu-heap-or-quick

# Arquivos-fonte
SRC    = menu.c heap.c
OBJ    = $(SRC:.c=.o)

# Regra principal: compilar tudo e gerar o executável
$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN)

# Regras genéricas para compilar cada .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Alvos auxiliares
.PHONY: run valgrind clean

run: $(BIN)
	./$(BIN)

valgrind: $(BIN)
	valgrind --leak-check=full --track-origins=yes ./$(BIN)

clean:
	rm -f $(OBJ) $(BIN)
