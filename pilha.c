#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

/* Cria uma pilha vazia. */
Pilha* pilha_criar(void) {
    Pilha *P = malloc(sizeof(Pilha));
    if (P == NULL)
        return NULL;
    P->tam = 0;
    P->topo = NULL;
    return P;
}

/* Libera a pilha e seus elementos. */
void pilha_destruir(Pilha **P) {
    if (P == NULL || *P == NULL)
        return;
    while ((*P)->topo != NULL)
        pilha_remover(P);
    free(*P);
    *P = NULL;
}

/* Adiciona um atendimento no topo. */
int pilha_adicionar(Pilha **P, const Paciente *p) {
    if (P == NULL || *P == NULL || p == NULL)
        return 0;
    NoPilha *q = malloc(sizeof(NoPilha));
    if (q == NULL)
        return 0;
    q->paciente = *p;
    q->paciente.prox = NULL;
    q->prox = (*P)->topo;
    (*P)->topo = q;
    (*P)->tam++;
    return 1;
}

/* Consulta o topo sem remover. */
int pilha_topo(Pilha *P, Paciente *p) {
    if (P == NULL || p == NULL || P->topo == NULL)
        return 0;
    *p = P->topo->paciente;
    p->prox = NULL;
    return 1;
}

/* Remove o atendimento do topo. */
void pilha_remover(Pilha **P) {
    if (P == NULL || *P == NULL || (*P)->topo == NULL)
        return;
    NoPilha *q = (*P)->topo;
    (*P)->topo = q->prox;
    free(q);
    (*P)->tam--;
}
/* Retorna a quantidade de atendimentos. */
int pilha_tamanho(Pilha *P) {
    if (P == NULL)
        return 0;
    return P->tam;
}

/* Exibe o historico do mais recente ao mais antigo. */
void pilha_imprimir(Pilha *P) {
    if (P == NULL || P->topo == NULL) {
        printf("Historico vazio.\n");
        return;
    }
    NoPilha *q = P->topo;
    printf("\n--- HISTORICO DE ATENDIMENTOS ---\n");
    while (q != NULL) {
        printf("ID: %d | Nome: %s\n",
               q->paciente.id, q->paciente.nome);
        q = q->prox;
    }
}
