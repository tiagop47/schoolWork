/**
 * @file equipamento.c
 * @brief Função principal para gerir o menu dos equipamentos.
 * 
 * Este arquivo contém todas as funções necessários para a gestão dos equipamentos
 */
#include <stdio.h>
#include <stdlib.h>
#include "equipamento_func.h"
#include "estruturas.h"
/**
 * @brief Função principal para gerir o menu de equipamentos.
 * 
 * @param listaEquipamento Ponteiro para a lista dos equipamentos.
 * @param id_sequencial_equipamentos Ponteiro para o ID sequencial dos equipamentos.
 */
int equipamento_main(ListaEquipamento *listaEquipamento,ListaReservas *listaReservas, int *id_sequencial_equipamentos) {
    int opcao,quantidade,id_remover;
    int opção_manutençao;
    int idEquipamentoDisponivel,idEquipamentoManutencao;

    do {
        printf("\nMenu de Equipamentos:\n");
        printf("1. |Criar Equipamento|\n");
        printf("2. |Editar Equipamento|\n");
        printf("3. |Eliminar Equipamento|\n");
        printf("4. |Mostrar Equipamentos|\n");
        printf("5. |ALTERAR ESTADO EQUIPAMENTO|\n");
        printf("6. |Relatório do EQUIPAMENTO|\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        validarLOOP(&opcao);

        switch (opcao) {
            case 1:
                criarEquipamento(listaEquipamento, id_sequencial_equipamentos);
                break;
            case 2: {
            
                printf("Digite o ID do equipamento a editar: ");
                scanf("%d", &id_sequencial_equipamentos);
                editarEquipamento(listaEquipamento, id_sequencial_equipamentos);
                break;
            }
            case 3: {
                
                printf("Digite o ID do equipamento a eliminar: ");
                scanf("%d", &id_remover);
                eliminarEquipamento(listaEquipamento, id_remover);
                break;
            }
            case 4:
                mostrarEquipamentos(listaEquipamento);
                printf("Equipamentos indisponíveis:\n");
                equipamentos_indisponivel(listaEquipamento);
                break;
            case 5:
            do {
                printf("[0] MENU ANTERIOR.\n");
                printf("[1] COLOCAR MANUTENÇÃO.\n");
                printf("[2] COLOCAR DISPONIVEL.\n");
                validarLOOP(&opção_manutençao);
                switch (opção_manutençao) {
                    case 0:
                        printf("SAIR DO MODO MANUTENÇÃO.\n");
                        break;
                    case 1:
                        printf("Alterar Estado [ID]: ");
                        scanf("%d", &idEquipamentoManutencao);
                        ColocarManutençao(listaEquipamento, idEquipamentoManutencao);
                        break;
                    case 2:
                        printf("Alterar Estado [ID]: ");
                        scanf("%d", &idEquipamentoDisponivel);
                        RetirarManutençao(listaEquipamento, idEquipamentoDisponivel);
                        break;
                    default:
                        printf("Opção inválida. Tente novamente.\n");
                        break;
                }
            } while (opção_manutençao != 0);
            break;
            case 6:
                relatorio_equipamentos(listaEquipamento, listaReservas);
                break;
                
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while (opcao != 0);
return 0;
    }