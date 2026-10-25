#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H

typedef struct paciente {
    int id;
    char nome[50];
    int idade;
    struct paciente *prox;
} Paciente;

Paciente* paciente_criar_lista(void);
void paciente_destruir_lista(Paciente **L);
int paciente_adicionar_final(Paciente **L, int id,
                             const char *nome, int idade);
Paciente* paciente_buscar_id(Paciente *L, int id);
int paciente_remover_id(Paciente **L, int id);
void paciente_imprimir_lista(Paciente *L);

#endif
