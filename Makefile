# Nome do compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -g

# Arquivos fonte e objetos
SRC = main.c territorio.c jogador.c utils.c
OBJ = main.o territorio.o jogador.o utils.o

# Nome do executável
EXEC = war

# Regra padrão
all: $(EXEC)

# Regra para criar o executável
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

# Regras para compilar os arquivos fonte
main.o: main.c territorio.h jogador.h utils.h
	$(CC) $(CFLAGS) -c main.c

territorio.o: territorio.c territorio.h
	$(CC) $(CFLAGS) -c territorio.c

jogador.o: jogador.c jogador.h territorio.h
	$(CC) $(CFLAGS) -c jogador.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

# Regra para limpar os arquivos gerados
clean:
	rm -f $(OBJ) $(EXEC)