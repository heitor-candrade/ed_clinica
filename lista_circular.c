#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lista_circular.h"

No* criar_lista_circular() {
    return NULL;
}

void destruir_lista(No **lista) {
    if (lista == NULL || *lista == NULL)
        return;

    No *atual = (*lista)->prox;
    No *aux;

    while (atual != *lista) {
        aux = atual;
        atual = atual->prox;
        free(aux);
    }

    free(*lista);
    *lista = NULL;
}

/* Adiciona um medico no inicio da lista circular. */
void adicionar_inicio(No **lista, const char *nome) {
    No *novo = malloc(sizeof(No));
    if (novo == NULL) {
        printf("Nao foi possivel adicionar o medico.\n");
        return;
    }

    strncpy(novo->nome, nome, sizeof(novo->nome) - 1);
    novo->nome[sizeof(novo->nome) - 1] = '\0';

    if (*lista == NULL) {
        novo->prox = novo;
        *lista = novo;
    } else {
        novo->prox = (*lista)->prox;
        (*lista)->prox = novo;
    }
}

/* Adiciona um medico no final da lista circular. */
void adicionar_final(No **lista, const char *nome) {
    No *novo = malloc(sizeof(No));
    if (novo == NULL) {
        printf("Nao foi possivel adicionar o medico.\n");
        return;
    }

    strncpy(novo->nome, nome, sizeof(novo->nome) - 1);
    novo->nome[sizeof(novo->nome) - 1] = '\0';

    if (*lista == NULL) {
        novo->prox = novo;
        *lista = novo;
    } else {
        novo->prox = (*lista)->prox;
        (*lista)->prox = novo;
        *lista = novo;
    }
}

/* Avanca para o proximo medico do rodizio. */
void avancar_fila(No **lista) {
    if (lista == NULL || *lista == NULL || (*lista)->prox == *lista)
        return;

    *lista = (*lista)->prox;
}

/* Remove o medico que esta no inicio da escala. */
void remover_atual(No **lista) {
    if (lista == NULL || *lista == NULL) {
        printf("A escala esta vazia.\n");
        return;
    }

    No *atual = (*lista)->prox;

    if (*lista == atual) {
        free(atual);
        *lista = NULL;
    } else {
        (*lista)->prox = atual->prox;
        free(atual);
    }
}

/* Mostra a escala a partir do medico atual. */
void listar_a_partir_do_atual(No *lista) {
    if (lista == NULL) {
        printf("Nenhum medico na escala.\n");
        return;
    }

    No *atual = lista->prox;
    int posicao = 1;

    printf("--- Escala Circular de Medicos ---\n");
    do {
        if (posicao == 1)
            printf("[%d] %s <-- (PLANTAO ATUAL)\n", posicao, atual->nome);
        else
            printf("[%d] %s\n", posicao, atual->nome);

        atual = atual->prox;
        posicao++;
    } while (atual != lista->prox);

    printf("----------------------------------\n");
}

/* Imprime todos os nomes da lista circular. */
void imprimir_lista(No *lista) {
    if (lista == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    No *atual = lista->prox;

    printf("Lista Circular: [ ");
    do {
        printf("%s ", atual->nome);
        atual = atual->prox;
    } while (atual != lista->prox);

    printf("]\n");
}
