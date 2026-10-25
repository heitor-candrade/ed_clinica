#include <stdlib.h>
#include <stdio.h>
#include "fila_pacientes.h"

NoPaciente* criar_fila_pacientes() {
    return NULL;
}


void destruir_fila(NoPaciente **fila) {
    if (*fila == NULL) return; 

    NoPaciente *atual = (*fila)->prox;
    NoPaciente *aux;

    while (atual != *fila) {
        aux = atual;
        atual = atual->prox;
        free(aux);
    }

    free(*fila);
    *fila = NULL; 
}


void adicionar_paciente(NoPaciente **fila, int id) {
    NoPaciente *novo = (NoPaciente*) malloc(sizeof(NoPaciente));
    novo->id_paciente = id;

    if (*fila == NULL) {
        // Se está vazia, o paciente aponta para si mesmo e torna-se a referência (fim)
        novo->prox = novo;
        *fila = novo;
    } else {
        // O novo paciente aponta para o primeiro da fila
        novo->prox = (*fila)->prox;
        // O antigo último paciente aponta para o novo
        (*fila)->prox = novo;
        
        // Movemos o ponteiro da fila para o novo paciente, declarando-o como o novo final
        *fila = novo;
    }
}


void remover_paciente(NoPaciente **fila) {
    if (*fila == NULL) {
        printf("A fila de pacientes esta vazia.\n");
        return;
    }

    // O paciente a ser atendido (removido) é sempre o primeiro (o próximo depois do fim)
    NoPaciente *atendido = (*fila)->prox; 

    // Se só existe um paciente na fila
    if (*fila == atendido) {
        *fila = NULL; // A fila fica vazia
    } 
    // Se há mais de um paciente
    else {
        // O último da fila passa a apontar para o segundo paciente (pulando o primeiro)
        (*fila)->prox = atendido->prox;
    }

    free(atendido); // Liberta a memória do paciente que foi atendido
}


void acessar_atual(NoPaciente *fila) {
    if (fila == NULL) {
        printf("Nenhum paciente aguardando atendimento.\n");
        return;
    }
    
    // O próximo a ser atendido é sempre o primeiro da fila
    printf("Proximo a ser atendido: Paciente ID %d\n", fila->prox->id_paciente);
}


void listar_pacientes(NoPaciente *fila) {
    if (fila == NULL) {
        printf("Fila de espera vazia.\n");
        return;
    }

    NoPaciente *atual = fila->prox; // Começa pelo primeiro da fila
    int posicao = 1;

    printf("\n--- Fila de Espera (Pacientes) ---\n");
    do {
        printf("[%d] Paciente ID: %d\n", posicao, atual->id_paciente);
        atual = atual->prox;
        posicao++;
    } while (atual != fila->prox); // Pára quando der a volta completa
    
    printf("----------------------------------\n");
}