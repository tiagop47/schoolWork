/**
 * @file espaço_func.h
 * @brief Ficheiro que contém todos os protótipos de funções relativas ao espaço.
 * 
 */
#ifndef ESPAÇO_FUNC_H
#define ESPAÇO_FUNC_H

#include "estruturas.h"
#include "entrada.h"

/**
 * @brief Função principal para gerenciar o menu de espaços.
 * 
 * @param EspaçoLista Ponteiro para a lista de espaços.
 * @param id_sequencial_espaço Ponteiro para o ID sequencial dos espaços.
 */
void espaço_main(ListaEspaço *EspaçoLista, int *id_sequencial_espaço);

/**
 * @brief Inicializa a lista de espaços.
 * 
 * @param lista Ponteiro para a lista de espaços.
 * @param capacidadeInicial Capacidade inicial da lista de espaços.
 */
void inicializarEspaço(ListaEspaço *lista, int capacidadeInicial);

/**
 * @brief Cria um novo espaço.
 * 
 * @param lista Ponteiro para a lista de espaços.
 * @param id_sequencial Ponteiro para o ID sequencial dos espaços.
 */
void criarEspaço(ListaEspaço *lista, int *id_sequencial);

/**
 * @brief Elimina um espaço existente.
 * 
 * @param lista Ponteiro para a lista de espaços.
 * @param id_espaco ID do espaço a ser eliminado.
 */
void eliminarEspaço(ListaEspaço *lista, int id_espaco);

/**
 * @brief Edita um espaço existente.
 * 
 * @param lista Ponteiro para a lista de espaços.
 * @param id_espaco ID do espaço a ser editado.
 */
void editarEspaço(ListaEspaço *lista, int id_espaco);

/**
 * @brief Mostra todos os espaços.
 * 
 * @param lista Ponteiro para a lista de espaços.
 */
void mostrar_espaço(ListaEspaço *lista);

/**
 * @brief Carrega os espaços a partir de um ficheiro.
 * 
 * @param lista Ponteiro para a lista de espaços.
 * @param nomeFicheiro Nome do ficheiro a partir do qual os espaços serão carregados.
 * @param id_sequencial_espaço Ponteiro para o ID sequencial dos espaços.
 */
void carregarEspaços(ListaEspaço *lista, const char *nomeFicheiro, int *id_sequencial_espaço);

/**
 * @brief Guarda os espaços em um ficheiro.
 * 
 * @param lista Ponteiro para a lista de espaços.
 * @param nomeFicheiro Nome do ficheiro onde os espaços serão guardados.
 * @param id_sequencial_espaço ID sequencial dos espaços.
 */
void guardarEspaços(ListaEspaço *lista, const char *nomeFicheiro, int id_sequencial_espaço);

/**
 * @brief Verifica se um espaço existe na lista.
 * 
 * @param listaEspaço Ponteiro para a lista de espaços.
 * @param idEspaço ID do espaço a ser verificado.
 * @return int 1 se o espaço existe, 0 caso contrário.
 */
int espaçoExiste(ListaEspaço *listaEspaço, int idEspaço);

/**
 * @brief Marca um espaço como reservado.
 * 
 * @param lista Ponteiro para a lista de espaços.
 * @param id_espaço ID do espaço a ser reservado.
 * @param quantidade Quantidade de espaço a ser reservada.
 */
void espaçoReservado(ListaEspaço *lista, int id_espaço, int quantidade);

/**
 * @brief Mostra todos os espaços reservados.
 * 
 * @param lista Ponteiro para a lista de espaços.
 */
void espaços_reservados(ListaEspaço *lista);

/**
 * @brief Gera um relatório detalhado de todos os espaços.
 * 
 * @param listaEspacos Ponteiro para a lista de espaços.
 */
void relatorio_espaço(ListaEspaço *listaEspacos);

#endif // ESPAÇO_FUNC_H