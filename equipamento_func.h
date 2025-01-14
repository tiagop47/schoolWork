/**
 * @file equipamento_func.h
 * @brief Ficheiro que contém todos os protótipos dasfunções relativas ao equipamento.
 * 
 */

#ifndef EQUIPAMENTO_H
#define EQUIPAMENTO_H

#include "estruturas.h"
#include "entrada.h"

/**
 * @brief Função principal para gerenciar o menu de equipamentos.
 * 
 * @param listaEquipamento Ponteiro para a lista de equipamentos.
 * @param listaReservas Ponteiro para a lista de reservas.
 * @param id_sequencial_equipamentos Ponteiro para o ID sequencial dos equipamentos.
 * @return int Código de saída do programa.
 */
int equipamento_main(ListaEquipamento *listaEquipamento, ListaReservas *listaReservas, int *id_sequencial_equipamentos);

/**
 * @brief Inicializa a lista de equipamentos.
 * 
 * @param lista Ponteiro para a lista de equipamentos.
 * @param capacidadeInicial Capacidade inicial da lista de equipamentos.
 */
void inicializarEquipamento(ListaEquipamento *lista, int capacidadeInicial);

/**
 * @brief Cria um novo equipamento.
 * 
 * @param lista Ponteiro para a lista de equipamentos.
 * @param id_sequencial Ponteiro para o ID sequencial dos equipamentos.
 */
void criarEquipamento(ListaEquipamento *lista, int *id_sequencial);

/**
 * @brief Elimina um equipamento existente.
 * 
 * @param lista Ponteiro para a lista de equipamentos.
 * @param id_eliminar ID do equipamento a ser eliminado.
 */
void eliminarEquipamento(ListaEquipamento *lista, int id_eliminar);

/**
 * @brief Edita um equipamento existente.
 * 
 * @param lista Ponteiro para a lista de equipamentos.
 * @param id_equipamento ID do equipamento a ser editado.
 */
void editarEquipamento(ListaEquipamento *lista, int id_equipamento);

/**
 * @brief Mostra todos os equipamentos.
 * 
 * @param lista Ponteiro para a lista de equipamentos.
 */
void mostrarEquipamentos(ListaEquipamento *lista);

/**
 * @brief Carrega os equipamentos a partir de um ficheiro.
 * 
 * @param lista Ponteiro para a lista de equipamentos.
 * @param nomeFicheiro Nome do ficheiro a partir do qual os equipamentos serão carregados.
 * @param id_sequencial_equipamentos Ponteiro para o ID sequencial dos equipamentos.
 */
void carregarEquipamentos(ListaEquipamento *lista, const char *nomeFicheiro, int *id_sequencial_equipamentos);

/**
 * @brief Guarda os equipamentos em um ficheiro.
 * 
 * @param lista Ponteiro para a lista de equipamentos.
 * @param nomeFicheiro Nome do ficheiro onde os equipamentos serão guardados.
 * @param id_sequencial_equipamentos ID sequencial dos equipamentos.
 */
void guardarEquipamentos(ListaEquipamento *lista, const char *nomeFicheiro, int id_sequencial_equipamentos);

/**
 * @brief Verifica se um equipamento existe na lista.
 * 
 * @param listaEquipamentos Ponteiro para a lista de equipamentos.
 * @param idEquipamento ID do equipamento a ser verificado.
 * @param tipoEquipamento Tipo do equipamento a ser verificado.
 * @return int 1 se o equipamento existe, 0 caso contrário.
 */
int equipamentoExiste(ListaEquipamento *listaEquipamentos, int idEquipamento, char *tipoEquipamento);

/**
 * @brief Coloca um equipamento em manutenção.
 * 
 * @param listaEquipamentos Ponteiro para a lista de equipamentos.
 * @param idEquipamento ID do equipamento a ser colocado em manutenção.
 */
void ColocarManutençao(ListaEquipamento *listaEquipamentos, int idEquipamento);

/**
 * @brief Retira um equipamento da manutenção.
 * 
 * @param listaEquipamentos Ponteiro para a lista de equipamentos.
 * @param idEquipamento ID do equipamento a ser retirado da manutenção.
 */
void RetirarManutençao(ListaEquipamento *listaEquipamentos, int idEquipamento);

/**
 * @brief Mostra todos os equipamentos indisponíveis.
 * 
 * @param listaEquipamento Ponteiro para a lista de equipamentos.
 */
void equipamentos_indisponivel(ListaEquipamento *listaEquipamento);

/**
 * @brief Mostra todos os equipamentos reservados.
 * 
 * @param listaEquipamentos Ponteiro para a lista de equipamentos.
 * @param idEquipamento ID do equipamento reservado.
 * @param tipoEquipamento Tipo do equipamento reservado.
 */
void reservados(ListaEquipamento *listaEquipamentos, int idEquipamento, char *tipoEquipamento);

#endif // EQUIPAMENTO_H