#ifndef FILA_PACIENTES_H
#define FILA_PACIENTES_H

typedef struct NoPaciente {
    int id_paciente;
    struct NoPaciente *prox;
} NoPaciente;

NoPaciente* criar_fila_pacientes();
void adicionar_paciente(NoPaciente **fila, int id);
void acessar_atual(NoPaciente *fila);
void remover_paciente(NoPaciente **fila);
void listar_pacientes(NoPaciente *fila);
void destruir_fila(NoPaciente **fila);

#endif