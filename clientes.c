/**
 * @file clientes.c
 * @brief Função principal para gerir o menu de clientes.
 * 
 * Este arquivo contém a função principal para gerenciar o menu de clientes, permitindo adicionar, editar, eliminar e mostrar clientes.
 */
#include <stdlib.h>
#include <stdio.h>
#include "estruturas.h"
#include "entrada.h"
/**
 * @brief Função principal para gerir o menu de clientes.
 * 
 * @param listaClientes Ponteiro para a lista dos clientes.
 * @param id_sequencial Ponteiro para o ID sequencial dos clientes.
 * @param listaReservas Ponteiro para a lista de reservas.
 */
void clientes_main(ListaClientes *listaClientes, int *id_sequencial,ListaReservas *listaReservas) {
    int opcao;
    int id_editar;  
    int id_remover; 

    do {
        printf("Menu de Opções:\n");
        printf("[1] Adicionar Cliente\n");
        printf("[2] Editar Cliente\n");
        printf("[3] Eliminar Cliente\n");
        printf("[4] Mostrar Todos os Clientes\n");
        printf("[5] Relatório de Clientes\n");
        printf("[0] PAINEL CONTROLO\n");
        printf("Escolha uma das seguintes opções: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 0:
               
               
                return;
            case 1:
                adicionarCliente(listaClientes, id_sequencial);
                break;
            case 2:
                printf("ID do cliente a editar: ");
                scanf("%d", &id_editar);
                editarCliente(listaClientes, id_editar);
                break;
            case 3:
                printf("Digite o ID do cliente a eliminar: ");
                scanf("%d", &id_remover);
                eliminarCliente(listaClientes, id_remover);
                break;
            case 4:
                mostrarClientes(listaClientes);
                break;
            case 5:
                relatorio_cliente(listaClientes,listaReservas);
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);
}
