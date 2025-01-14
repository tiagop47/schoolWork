/**
 * @file main.c
 * @brief Função principal do programa.
 * 
 * Painel Principal.
 */

#include <stdio.h>
#include <stdlib.h>
#include "entrada.h"
#include "equipamento_func.h"
#include "estruturas.h"
#include "espaço_func.h"
#include "reservas.h"

/**
 * @brief Função principal do programa.
 * 
 * @param argc Número de argumentos de linha de comando.
 * @param argv Array de strings contendo os argumentos de linha de comando.
 * @return int Código de saída do programa.
 */

int main(int argc, char** argv) {
    int opçao;
   
    int id_sequencial=1;
    int id_sequencial_espaço=1;
    int id_sequencial_equipamentos=1;
    int id_sequencial_reservas=1;
    
    int capacidadeInicial = CLIENTES_LIM;  
    int capacidadeInicial_espaço = MAX_ESPAÇO;  
    int capacidadeInicialEquipamentos = MAX_EQUIPAMENTOS;
    int capacidadeInicial_Reservas=MAX_RESERVAS;
    
    
    ListaClientes listaClientes;
    inicializarClientes(&listaClientes, capacidadeInicial);
    carregarClientes(&listaClientes, "clientes.bin", &id_sequencial);
     
    ListaEspaço EspaçoLista;
    inicializarEspaço(&EspaçoLista,capacidadeInicial_espaço);
    carregarEspaços(&EspaçoLista,"Espaço.bin",&id_sequencial_espaço);
    
    ListaEquipamento listaEquipamentos;
    inicializarEquipamentos(&listaEquipamentos, capacidadeInicialEquipamentos);
    carregarEquipamentos(&listaEquipamentos, "equipamentos.bin",&id_sequencial_equipamentos);

    
    ListaReservas listaReservas;
    inicializarReservas(&listaReservas,capacidadeInicial_Reservas);
    carregarReservas(&listaReservas,"reservas.bin",&id_sequencial_reservas);
    
    
    do{
    formataçao();
    linha();
    printf("\t\t\t\t\tPAINEL CONTROLO");
    linha();
    printf("Escolha uma das seguintes opções: \n");
    printf("\t\t|Secção CLIENTE     |Opção[1]|\n");
    printf("\t\t|Secção EQUIPAMENTO |Opção[2]|\n");
    printf("\t\t|Secção ESPAÇO      |Opção[3]|\n");
    printf("\t\t|Secção RESERVAS    |Opção[4]|\n");
    printf("\t\t|FECHAR PROGRAMA [0].\n");
    printf("Secção: ");
 validarLOOP(&opçao);

            switch (opçao){
                case 0:
                    guardarClientes(&listaClientes, "clientes.bin", id_sequencial);
                    free(listaClientes.clientes);
                    guardarEspaços(&EspaçoLista,"Espaço.bin",id_sequencial_espaço);
                    free(EspaçoLista.espaços);
                    guardarEquipamentos(&listaEquipamentos, "equipamentos.bin",id_sequencial_equipamentos);
                    free(listaEquipamentos.equipamentos);
                    guardarReservas(&listaReservas,"Reservas.bin",id_sequencial_reservas);
                    free(listaReservas.reservas);
                    printf("Até breve!\n");
                    return 0;
            
                case 1: 
                    clientes_main(&listaClientes,&id_sequencial,&listaReservas);
                    break;
                case 2:
                    equipamento_main(&listaEquipamentos,&listaReservas,&id_sequencial_equipamentos);
                    break;
                case 3:
                   espaço_main(&EspaçoLista,&id_sequencial_espaço);
                   break;
                case 4:
                    reserva_main(&listaReservas,&listaClientes,&EspaçoLista,&listaEquipamentos ,&id_sequencial_reservas);
                    break;
            default:
                printf("Opção inválida.");
                break;
            }
    }while(opçao !=0);
    return(EXIT_SUCCESS);
} 
