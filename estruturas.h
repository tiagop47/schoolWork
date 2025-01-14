/**
 * @file estruturas.h
 * @brief Ficheiro que contém todas as estruturas.
 * 
 */

#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#define NIF 10
#define TAMANHO_NOME 10
#define CLIENTES_LIM 20
#define TELEMOVEL_NUM 10
#define TAMANHO_MAIL 45
#define MAQUINAS 100
#define MAX_ESPAÇO 100
#define MAX_EQUIPAMENTOS 100
#define NOME_TIPO 30
#define MAX_RESERVAS 30
#define NOME_ESPAÇO 30
#define MAX_UTILIZAÇAO 100
/**
* @brief DATA
 */

typedef enum { 
    Janeiro = 1, Fevereiro, Março, Abril, Maio, Junho, 
    Julho, Agosto, Setembro, Outubro, Novembro, Dezembro
} Mes;

typedef struct {
    int dia;
    Mes mes;
    int ano;
} Data;
/**
 * @brief Estado das Reservas
 */

typedef enum {
    PENDENTE=0,
    CONFIRMADA,
    FINALIZADA,
    CANCELADA
} EstadoReserva;


typedef enum {
    MANUTENÇAO,
    DISPONIVEL,
    RESERVADO
} Estado;


/**
 * @brief Estrutura para representar clientes
 */

typedef struct {
    char nome[TAMANHO_NOME];
    char apelido[TAMANHO_NOME];
    char nif[NIF];
    int id_pessoal;
    char telemovel[TELEMOVEL_NUM];
    char email[TAMANHO_MAIL];
} Cliente;
/**
 * @brief Lista de clientes
 */

typedef struct {
    Cliente *clientes;
    int capacidade;
    int totalClientes;
} ListaClientes;

/**
 * @brief Representar um espaço
 */

typedef struct {
    int id;
    char nome[NOME_ESPAÇO];
    char tipo[NOME_TIPO]; 
    int quantidade; 
    Estado estado;
    int quantidadeReserva;
} Espaço;
/**
 * @brief Lista de espaços
 */

typedef struct{
    Espaço *espaços;
    int capacidade;
    int totalEspaço;
} ListaEspaço;

/**
 * @brief Representação de um equipamento
 */

typedef struct {
    int id;
    char nome[NOME_TIPO];
    char tipo[NOME_TIPO];
    Estado estado;
    int quantidade;
    int quantidadeManutençao;
    int quantidadeReserva;
} Equipamento;

/**
 * @brief Listagem de equipamentos
 */

typedef struct {
    Equipamento *equipamentos;
    int capacidade;
    int totalEquipamento;
} ListaEquipamento;
/**
 * @brief Representação de uma reserva
 */
typedef struct {
    int id;
    int idCliente;
    int idEspaço;
    int idEquipamento;
    Data dataReserva;  
    int duraçao; 
    EstadoReserva estado;
    int numParticipantes;
    char tipoEquipamentos[NOME_TIPO];
    int quantidadeEquipamentos;
    int quantidadeEspaço;
    char nomeEspaço[NOME_ESPAÇO];
    int removida;
} Reserva;

/**
 * @brief Listagem de reservas.
 */

typedef struct {
    Reserva *reservas;
    int capacidade;
    int totalReservas;
} ListaReservas;

#endif
