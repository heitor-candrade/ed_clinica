#ifndef LISTA_MEDICOS_H
#define LISTA_MEDICOS_H

typedef struct no {
    char nome[80];
    struct no *prox;
} No;

No* criar_lista_circular();
void destruir_lista(No **lista);
void imprimir_lista(No *lista);

void adicionar_inicio(No **lista, const char *nome);
void adicionar_final(No **lista, const char *nome);
void avancar_fila(No **lista);
void remover_atual(No **lista);
void listar_a_partir_do_atual(No *lista);

#endif
