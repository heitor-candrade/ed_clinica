#include "lista_encadeada.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Cria uma lista de pacientes vazia. */
Paciente* paciente_criar_lista(void) {
    return NULL;
}
/* Libera todos os pacientes da lista. */
void paciente_destruir_lista(Paciente **L) {
    if (L == NULL)
        return;
    while (*L != NULL) {
        Paciente *aux = *L;
        *L = (*L)->prox;
        free(aux);
    }
}

/* Adiciona um paciente no final da lista. */
int paciente_adicionar_final(Paciente **L, int id,
                             const char *nome, int idade) {
    if (L == NULL || nome == NULL)
        return 0;
    Paciente *q = malloc(sizeof(Paciente));
    if (q == NULL)
        return 0;
    q->id = id;
    q->idade = idade;
    strncpy(q->nome, nome, sizeof(q->nome) - 1);
    q->nome[sizeof(q->nome) - 1] = '\0';
    q->prox = NULL;
    if (*L == NULL) {
        *L = q;
        return 1;
    }
    Paciente *aux = *L;
    while (aux->prox != NULL)
        aux = aux->prox;
    aux->prox = q;
    return 1;
}
/* Busca um paciente pelo ID. */
Paciente* paciente_buscar_id(Paciente *L, int id) {
    while (L != NULL) {
        if (L->id == id)
            return L;

        L = L->prox;
    }
    return NULL;
}

/* Remove um paciente pelo ID. */
int paciente_remover_id(Paciente **L, int id) {
    if (L == NULL || *L == NULL)
        return 0;
    Paciente *q = *L;
    Paciente *ant = NULL;
    while (q != NULL && q->id != id) {
        ant = q;
        q = q->prox;
    }
    if (q == NULL)
        return 0;
    if (ant == NULL)
        *L = q->prox;
    else
        ant->prox = q->prox;

    free(q);
    return 1;
}

/* Mostra os pacientes cadastrados. */
void paciente_imprimir_lista(Paciente *L) {
    if (L == NULL) {
        printf("Nenhum paciente cadastrado.\n");
        return;
    }
    while (L != NULL) {
        printf("ID: %d | Nome: %s | Idade: %d\n",
               L->id, L->nome, L->idade);
        L = L->prox;
    }
}
