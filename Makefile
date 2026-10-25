CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pedantic
FONTES = main.c lista_encadeada.c lista_circular.c fila_pacientes.c pilha.c
CABECALHOS = lista_encadeada.h lista_circular.h fila_pacientes.h pilha.h

all: clinica

clinica: $(FONTES) $(CABECALHOS)
	$(CC) $(CFLAGS) $(FONTES) -o clinica

clean:
	rm -f clinica

.PHONY: all clean
