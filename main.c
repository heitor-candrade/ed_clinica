#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AZUL "\033[1;36m"
#define VERDE "\033[1;32m"
#define AMARELO "\033[1;33m"
#define VERMELHO "\033[1;31m"
#define ROXO "\033[1;35m"
#define RESET "\033[0m"

#include "lista_encadeada.h"
#include "lista_circular.h"
#include "fila_pacientes.h"
#include "pilha.h"


/* Mostra o titulo de cada menu. */
void mostrar_cabecalho(const char *titulo) {
    printf(AZUL "\n========================================\n" RESET);
    printf(ROXO "       CLINICA VIDASAUDÁVEL\n" RESET);
    printf(AZUL "----------------------------------------\n" RESET);
    printf(AMARELO "       %s\n" RESET, titulo);
    printf(AZUL "========================================\n" RESET);
}

/* Espera o usuario ler a mensagem. */
void esperar_enter(void) {
    int c;

    printf("\nPressione Enter para continuar...");
    while ((c = getchar()) != '\n' && c != EOF) {}
    getchar();
}

/* Le um numero inteiro. */
int ler_inteiro(int *numero) {
    if (scanf("%d", numero) != 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
        printf("Entrada invalida.\n");
        printf("Pressione Enter para continuar...");
        getchar();
        return 0;
    }
    return 1;
}

/* Verifica se o paciente ja esta na fila. */
int paciente_na_fila(NoPaciente *fila, int id) {
    if (fila == NULL)
        return 0;

    NoPaciente *atual = fila->prox;

    do {
        if (atual->id_paciente == id)
            return 1;

        atual = atual->prox;
    } while (atual != fila->prox);

    return 0;
}

/* Evita remover um paciente que ainda aparece no historico. */
int paciente_no_historico(Pilha *historico, int id) {
    if (historico == NULL)
        return 0;

    NoPilha *atual = historico->topo;

    while (atual != NULL) {
        if (atual->paciente.id == id)
            return 1;

        atual = atual->prox;
    }

    return 0;
}

/* Menu de pacientes. */
void menu_pacientes(Paciente **pacientes, NoPaciente *fila,
                    Pilha *historico) {
    int opcao = -1;

    while (opcao != 0) {
        system("clear");
        mostrar_cabecalho("GESTAO DE PACIENTES");
        printf(VERDE "1 - " RESET "Cadastrar paciente\n");
        printf(VERDE "2 - " RESET "Buscar paciente\n");
        printf(VERDE "3 - " RESET "Remover paciente\n");
        printf(VERDE "4 - " RESET "Listar pacientes\n");
        printf(AMARELO "0 - " RESET "Voltar ao menu principal\n");
        printf(AZUL "----------------------------------------\n" RESET);
        printf(AMARELO "Opcao: " RESET);

        if (!ler_inteiro(&opcao)) {
            opcao = -1;
            continue;
        }

        if (opcao == 1) {
            int id, idade;
            char nome[50];

            printf(AMARELO "ID: " RESET);
            if (!ler_inteiro(&id)) continue;

            printf(AMARELO "Nome: " RESET);
            if (scanf(" %49[^\n]", nome) != 1) {
                printf("Nome invalido.\n");
                continue;
            }

            printf(AMARELO "Idade: " RESET);
            if (!ler_inteiro(&idade)) continue;

            if (id <= 0 || idade < 0) {
                printf("ID ou idade invalida.\n");
            } else if (paciente_buscar_id(*pacientes, id) != NULL) {
                printf("Ja existe um paciente com esse ID.\n");
            } else if (paciente_adicionar_final(pacientes, id, nome, idade)) {
                printf("Paciente cadastrado.\n");
            } else {
                printf("Nao foi possivel cadastrar o paciente.\n");
            }

        } else if (opcao == 2) {
            int id;
            printf(AMARELO "ID do paciente: " RESET);
            if (!ler_inteiro(&id)) continue;

            Paciente *p = paciente_buscar_id(*pacientes, id);

            if (p == NULL)
                printf("Paciente nao encontrado.\n");
            else
                printf("ID: %d | Nome: %s | Idade: %d\n",
                       p->id, p->nome, p->idade);

        } else if (opcao == 3) {
            int id;
            printf(AMARELO "ID para remover: " RESET);
            if (!ler_inteiro(&id)) continue;

            if (paciente_na_fila(fila, id) ||
                paciente_no_historico(historico, id)) {
                printf("Nao remova um paciente que esta na fila ou no historico.\n");
            } else if (paciente_remover_id(pacientes, id)) {
                printf("Paciente removido.\n");
            } else {
                printf("Paciente nao encontrado.\n");
            }

        } else if (opcao == 4) {
            paciente_imprimir_lista(*pacientes);

        } else if (opcao != 0) {
            printf("Opcao invalida.\n");
        }

        if (opcao != 0)
            esperar_enter();
    }
}

/* Verifica se o nome ja esta na escala. */
int medico_na_lista(No *medicos, const char *nome) {
    if (medicos == NULL)
        return 0;

    No *atual = medicos->prox;

    do {
        if (strcmp(atual->nome, nome) == 0)
            return 1;

        atual = atual->prox;
    } while (atual != medicos->prox);

    return 0;
}

/* Menu da lista circular de medicos. */
void menu_medicos(No **medicos) {
    int opcao = -1;

    while (opcao != 0) {
        system("clear");
        mostrar_cabecalho("ESCALA CIRCULAR DE MEDICOS");
        printf(VERDE "1 - " RESET "Ver escala\n");
        printf(VERDE "2 - " RESET "Avancar plantao\n");
        printf(VERDE "3 - " RESET "Adicionar medico no inicio\n");
        printf(VERDE "4 - " RESET "Adicionar medico no final\n");
        printf(VERMELHO "5 - " RESET "Remover medico atual\n");
        printf(AMARELO "0 - " RESET "Voltar ao menu principal\n");
        printf(AZUL "----------------------------------------\n" RESET);
        printf(AMARELO "Opcao: " RESET);

        if (!ler_inteiro(&opcao)) {
            opcao = -1;
            esperar_enter();
            continue;
        }

        if (opcao == 1) {
            listar_a_partir_do_atual(*medicos);

        } else if (opcao == 2) {
            if (*medicos == NULL) {
                printf(VERMELHO "Nao ha medicos na escala.\n" RESET);
            } else {
                avancar_fila(medicos);
                printf(VERDE "Plantao avancado. Medico atual: %s\n" RESET,
                       (*medicos)->prox->nome);
            }

        } else if (opcao == 3 || opcao == 4) {
            char nome[80];

            printf(AMARELO "Nome do medico: " RESET);
            if (scanf(" %79[^\n]", nome) != 1) {
                printf(VERMELHO "Nome invalido.\n" RESET);
                esperar_enter();
                continue;
            }

            if (medico_na_lista(*medicos, nome)) {
                printf(AMARELO "Esse medico ja esta na escala.\n" RESET);
            } else if (opcao == 3) {
                adicionar_inicio(medicos, nome);
                printf(VERDE "Medico %s adicionado no inicio da escala.\n" RESET, nome);
            } else {
                adicionar_final(medicos, nome);
                printf(VERDE "Medico %s adicionado no final da escala.\n" RESET, nome);
            }

        } else if (opcao == 5) {
            if (*medicos == NULL) {
                printf(VERMELHO "Nao ha medicos para remover.\n" RESET);
            } else {
                char nome[80];
                snprintf(nome, sizeof(nome), "%s", (*medicos)->prox->nome);
                remover_atual(medicos);
                printf(VERDE "Medico %s removido da escala.\n" RESET, nome);

                if (*medicos != NULL) {
                    printf("Proximo medico no plantao: %s\n",
                           (*medicos)->prox->nome);
                } else {
                    printf(AMARELO "A escala ficou vazia.\n" RESET);
                }
            }

        } else if (opcao != 0) {
            printf(VERMELHO "Opcao invalida.\n" RESET);
        }

        if (opcao != 0)
            esperar_enter();
    }
}


/* Menu da fila e dos atendimentos. */
void menu_atendimento(Paciente *pacientes, NoPaciente **fila,
                      No **medicos, Pilha **historico) {
    int opcao = -1;

    while (opcao != 0) {
        system("clear");
        mostrar_cabecalho("ATENDIMENTO E FILA DE ESPERA");
        printf(VERDE "1 - " RESET "Colocar paciente na fila\n");
        printf(VERDE "2 - " RESET "Ver fila de espera\n");
        printf(VERDE "3 - " RESET "Ver proximo paciente\n");
        printf(VERDE "4 - " RESET "Atender proximo paciente\n");
        printf(AMARELO "0 - " RESET "Voltar ao menu principal\n");
        printf(AZUL "----------------------------------------\n" RESET);
        printf(AMARELO "Opcao: " RESET);

        if (!ler_inteiro(&opcao)) {
            opcao = -1;
            continue;
        }

        if (opcao == 1) {
            int id;
            printf(AMARELO "ID do paciente: " RESET);
            if (!ler_inteiro(&id)) continue;

            if (paciente_buscar_id(pacientes, id) == NULL) {
                printf("Cadastre o paciente primeiro.\n");
            } else if (paciente_na_fila(*fila, id)) {
                printf("Paciente ja esta na fila.\n");
            } else {
                adicionar_paciente(fila, id);
                printf("Paciente adicionado a fila.\n");
            }

        } else if (opcao == 2) {
            listar_pacientes(*fila);

        } else if (opcao == 3) {
            acessar_atual(*fila);

        } else if (opcao == 4) {
            if (*fila == NULL) {
                printf("Nao ha pacientes na fila.\n");
            } else if (*medicos == NULL) {
                printf("Nao ha medicos na escala.\n");
            } else {
                int id = (*fila)->prox->id_paciente;
                Paciente *p = paciente_buscar_id(pacientes, id);

                if (p == NULL) {
                    printf("Paciente nao encontrado no cadastro.\n");
                } else if (!pilha_adicionar(historico, p)) {
                    printf("Nao foi possivel guardar o atendimento.\n");
                } else {
                    remover_paciente(fila);
                    printf("Paciente %s atendido pelo medico %s.\n",
                           p->nome, (*medicos)->prox->nome);

                    /* O proximo atendimento sera do proximo medico. */
                    avancar_fila(medicos);
                }
            }

        } else if (opcao != 0) {
            printf("Opcao invalida.\n");
        }

        if (opcao != 0)
            esperar_enter();
    }
}

/* Menu do historico. */
void menu_historico(Pilha **historico, NoPaciente **fila) {
    int opcao = -1;

    while (opcao != 0) {
        system("clear");
        mostrar_cabecalho("HISTORICO DE ATENDIMENTOS");
        printf(VERDE "1 - " RESET "Ver historico\n");
        printf(VERDE "2 - " RESET "Desfazer ultimo atendimento\n");
        printf(AMARELO "0 - " RESET "Voltar ao menu principal\n");
        printf(AZUL "----------------------------------------\n" RESET);
        printf(AMARELO "Opcao: " RESET);

        if (!ler_inteiro(&opcao)) {
            opcao = -1;
            continue;
        }

        if (opcao == 1) {
            pilha_imprimir(*historico);

        } else if (opcao == 2) {
            Paciente p;

            if (!pilha_topo(*historico, &p)) {
                printf("Historico vazio.\n");
            } else if (paciente_na_fila(*fila, p.id)) {
                printf("Paciente ja esta na fila.\n");
            } else {
                adicionar_paciente(fila, p.id);
                pilha_remover(historico);
                printf("Atendimento desfeito. Paciente voltou ao fim da fila.\n");
            }

        } else if (opcao != 0) {
            printf("Opcao invalida.\n");
        }

        if (opcao != 0)
            esperar_enter();
    }
}

int main(void) {
    Paciente *pacientes = paciente_criar_lista();
    No *medicos = criar_lista_circular();
    NoPaciente *fila = criar_fila_pacientes();
    Pilha *historico = pilha_criar();
    int opcao = -1;

    if (historico == NULL) {
        printf("Erro ao criar o historico.\n");
        return 1;
    }

    while (opcao != 0) {
        system("clear");
        mostrar_cabecalho("MENU PRINCIPAL");
        printf(VERDE "1 - " RESET "Gestao de pacientes\n");
        printf(VERDE "2 - " RESET "Escala de medicos\n");
        printf(VERDE "3 - " RESET "Atendimento e fila\n");
        printf(VERDE "4 - " RESET "Historico de atendimentos\n");
        printf(VERMELHO "0 - " RESET "Sair do sistema\n");
        printf(AZUL "----------------------------------------\n" RESET);
        printf(AMARELO "Opcao: " RESET);

        if (!ler_inteiro(&opcao)) {
            opcao = -1;
            continue;
        }

        if (opcao == 1) {
            menu_pacientes(&pacientes, fila, historico);
        } else if (opcao == 2) {
            menu_medicos(&medicos);
        } else if (opcao == 3) {
            menu_atendimento(pacientes, &fila, &medicos, &historico);
        } else if (opcao == 4) {
            menu_historico(&historico, &fila);
        } else if (opcao != 0) {
            printf("Opcao invalida.\n");
            esperar_enter();
        }
    }

    destruir_fila(&fila);
    pilha_destruir(&historico);
    paciente_destruir_lista(&pacientes);
    destruir_lista(&medicos);

    printf("Sistema encerrado.\n");
    return 0;
}
