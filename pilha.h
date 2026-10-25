#ifndef PILHA_H
#define PILHA_H
#include "lista_encadeada.h"

typedef struct no_pilha {
    Paciente paciente;
    struct no_pilha *prox;
} NoPilha;

typedef struct {
    int tam;
    NoPilha *topo;
} Pilha;

Pilha* pilha_criar(void);
void pilha_destruir(Pilha **P);
void pilha_remover(Pilha **P);
void pilha_imprimir(Pilha *P);
int pilha_tamanho(Pilha *P);
int pilha_adicionar(Pilha **P, const Paciente *p);
int pilha_topo(Pilha *P, Paciente *p);
#endif
