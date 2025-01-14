/**
 * @file reservas.h
 * @brief Ficheiro que contém todos os protótipos de funções relativas às reservas.
 * 
 */
#ifndef RESERVA_FUNC_H
#define RESERVA_FUNC_H

#include "espaço_func.h"
#include "equipamento_func.h"
#include "entrada.h"
#include "estruturas.h"

/**
 * @brief Função principal para gerenciar o menu de reservas.
 * 
 * @param listaReservas Ponteiro para a lista de reservas.
 * @param listaClientes Ponteiro para a lista de clientes.
 * @param EspaçoLista Ponteiro para a lista de espaços.
 * @param listaEquipamentos Ponteiro para a lista de equipamentos.
 * @param id_sequencial_reservas Ponteiro para o ID sequencial das reservas.
 */
void reserva_main(ListaReservas *listaReservas, ListaClientes *ListaClientes, ListaEspaço *EspaçoLista, ListaEquipamento *listaEquipamentos, int *id_sequencial_reservas);

/**
 * @brief Inicializa a lista de reservas.
 * 
 * @param lista Ponteiro para a lista de reservas.
 * @param capacidadeInicial Capacidade inicial da lista de reservas.
 */
void inicializarReservas(ListaReservas *lista, int capacidadeInicial);

/**
 * @brief Edita uma reserva existente.
 * 
 * @param listaReservas Ponteiro para a lista de reservas.
 * @param listaClientes Ponteiro para a lista de clientes.
 * @param listaEspaços Ponteiro para a lista de espaços.
 * @param listaEquipamentos Ponteiro para a lista de equipamentos.
 * @param id_reserva ID da reserva a ser editada.
 */
void editarReserva(ListaReservas *listaReservas, ListaClientes *listaClientes, ListaEspaço *listaEspaços, ListaEquipamento *listaEquipamentos, int id_reserva);

/**
 * @brief Elimina uma reserva existente.
 * 
 * @param listaReservas Ponteiro para a lista de reservas.
 * @param listaEquipamentos Ponteiro para a lista de equipamentos.
 * @param listaEspaços Ponteiro para a lista de espaços.
 * @param id_eliminar ID da reserva a ser eliminada.
 */
void eliminarReserva(ListaReservas *listaReservas, ListaEquipamento *listaEquipamentos, ListaEspaço *listaEspaços, int id_eliminar);

/**
 * @brief Mostra todas as reservas.
 * 
 * @param lista Ponteiro para a lista de reservas.
 */
void mostrarReservas(ListaReservas *lista);

/**
 * @brief Carrega as reservas a partir de um ficheiro.
 * 
 * @param listaReservas Ponteiro para a lista de reservas.
 * @param nomeFicheiro Nome do ficheiro a partir do qual as reservas serão carregadas.
 * @param id_sequencial_reservas Ponteiro para o ID sequencial das reservas.
 */
void carregarReservas(ListaReservas *listaReservas, const char *nomeFicheiro, int *id_sequencial_reservas);

/**
 * @brief Guarda as reservas em um ficheiro.
 * 
 * @param listaReservas Ponteiro para a lista de reservas.
 * @param nomeFicheiro Nome do ficheiro onde as reservas serão guardadas.
 * @param id_sequencial_reservas ID sequencial das reservas.
 */
void guardarReservas(ListaReservas *listaReservas, const char *nomeFicheiro, int id_sequencial_reservas);

/**
 * @brief Cria uma nova reserva.
 * 
 * @param lista Ponteiro para a lista de reservas.
 * @param listaClientes Ponteiro para a lista de clientes.
 * @param EspaçoLista Ponteiro para a lista de espaços.
 * @param listaEquipamentos Ponteiro para a lista de equipamentos.
 * @param id_sequencial_reservas Ponteiro para o ID sequencial das reservas.
 */
void criarReserva(ListaReservas *lista, ListaClientes *listaClientes, ListaEspaço *EspaçoLista, ListaEquipamento *listaEquipamentos, int *id_sequencial_reservas);

/**
 * @brief Converte o estado da reserva para uma string.
 * 
 * @param estado Estado da reserva.
 * @return char* String representando o estado da reserva.
 */
char *estadoReservaParaString(EstadoReserva estado);

/**
 * @brief Altera o estado de uma reserva.
 * 
 * @param listaReservas Ponteiro para a lista de reservas.
 * @param listaEquipamentos Ponteiro para a lista de equipamentos.
 * @param listaEspaços Ponteiro para a lista de espaços.
 */
void alterarEstadoReserva(ListaReservas *listaReservas, ListaEquipamento *listaEquipamentos, ListaEspaço *listaEspaços);

#endif // RESERVA_FUNC_H