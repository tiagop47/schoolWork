/**
 * @file espaço.c
 * @brief Função principal para gerir o menu dos espaços.
 * 
 * Este arquivo contém todas as funções necessários para a gestão dos espaços
 */
#include <stdio.h>
#include <stdlib.h>
#include "espaço_func.h"

/**
 * @brief Função principal para gerenciar o menu de espaços.
 * 
 * @param EspaçoLista Ponteiro para a lista de espaços.
 * @param id_sequencial_espaço Ponteiro para o ID sequencial dos espaços.
 */

void espaço_main(ListaEspaço *EspaçoLista, int *id_sequencial_espaço) {
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Criar Espaço\n");
        printf("2. Editar Espaço\n");
        printf("3. Eliminar Espaço\n");
        printf("4. Mostrar Espaços\n");
        printf("5. Relatório dos Espaços\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        validarLOOP(&opcao);

        switch (opcao) {
            case 1:
                mostrar_espaço(EspaçoLista);
                criarEspaço(EspaçoLista, id_sequencial_espaço);
                break;
            case 2: {
                int id;
                printf("Digite o ID do espaço a editar: ");
                scanf("%d", &id);
                editarEspaço(EspaçoLista, id);
                break;
            }
            case 3: {
                int id;
                printf("Digite o ID do espaço a eliminar: ");
                scanf("%d", &id);
                eliminarEspaço(EspaçoLista, id);
                break;
            }
            case 4:
                mostrar_espaço(EspaçoLista);
                printf("Espaços RESERVADOS:\n");
                espaços_reservados(EspaçoLista);       
                break;
            case 5:
                 relatorio_espaço(EspaçoLista);   
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while (opcao != 0);
}

