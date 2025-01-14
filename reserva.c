/**
 * @file reserva.c
 * @brief Função principal para gerir o menu das reservas.
 * 
 * Este arquivo contém todas as funções necessários para a gestão das reservas
 */
#include <stdio.h>
#include <stdlib.h>
#include "estruturas.h"
#include "reservas.h"
#include "entrada.h"
/**
 * @brief Função principal para gerenciar o menu de reservas.
 * 
 * @param listaReservas Ponteiro para a lista de reservas.
 * @param listaClientes Ponteiro para a lista de clientes.
 * @param EspaçoLista Ponteiro para a lista de espaços.
 * @param listaEquipamentos Ponteiro para a lista de equipamentos.
 * @param id_sequencial_reservas Ponteiro para o ID sequencial das reservas.
 */
void reserva_main(ListaReservas *listaReservas,ListaClientes *listaClientes,ListaEspaço *EspaçoLista,ListaEquipamento *listaEquipamentos,int *id_sequencial_reservas) {
    int opcao,id_editar,id_eliminar;

    do {
        printf("\nMenu de Reservas:\n");
        printf("[1] Criar Reserva\n");
        printf("[2] Editar Reserva\n");
        printf("[3] Eliminar Reserva\n");
        printf("[4] Mostrar Reservas\n");
        printf("[5] Alterar Estado da Reserva\n");
        printf("[6] Relatórios das Reservas\n");
        printf("[0] Sair\n");
        printf("Escolha uma opção: ");
        validarLOOP(&opcao);
        switch (opcao) {
            case 1:
                criarReserva(listaReservas,listaClientes,EspaçoLista,listaEquipamentos,id_sequencial_reservas);
           
                break;
            case 2: 
                printf("Digite o ID da reserva a editar: ");
                scanf("%d", &id_editar);
                editarReserva(listaReservas,listaClientes,EspaçoLista,listaEquipamentos,id_editar);
                break;
            
            case 3:                  
                printf("Digite o ID da reserva a eliminar: ");
                scanf("%d", &id_eliminar);
                eliminarReserva(listaReservas,listaEquipamentos,EspaçoLista,id_eliminar);
                break;
            case 4:
                mostrarReservas(listaReservas);
                break;
            case 5:
            mostrarReservas(listaReservas);
             alterarEstadoReserva(listaReservas,listaEquipamentos,EspaçoLista);
                break;      
                case 6:
                relatorio_reservas(listaReservas,listaClientes,EspaçoLista,listaEquipamentos);
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

   