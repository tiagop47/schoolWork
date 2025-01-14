/**
 * @file entrada.c
 * @brief Ficheiro que contém todas as funções relativas ao cliente e formataçao.
 * 
 */
#include "entrada.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> //apenas por causa do isdigit.

/**
 * @brief Verifica se um cliente com determinado ID existe na lista.
 * 
 * @param clientes Ponteiro para a lista de clientes.
 * @param idCliente ID do cliente a ser verificado.
 * @return int 1 se o cliente existe, 0 caso contrário.
 */
int clienteExiste(ListaClientes *clientes, int idCliente) {
    int i;
    for (i = 0; i < clientes->totalClientes; i++) {
        if (clientes->clientes[i].id_pessoal == idCliente) {
            return 1; // Cliente existe
        }
    }
    return 0; // Cliente não existe
}
/**
 * @brief Obtém uma data válida do usuário.
 * 
 * @param data Ponteiro para a estrutura de data.
 */
void obterData(Data *data) {
    int valido = 0;
    while (!valido) {
        printf("Digite o dia (1-31): ");
        scanf("%d", &data->dia);
        if (data->dia < 1 || data->dia > 31) {
            printf("Dia inválido. Tente novamente.\n");
            continue;
        }

        printf("Digite o mês (1-12): ");
        scanf("%d",&data->mes);
        if (data->mes < Janeiro || data->mes > Dezembro) {
            printf("Mês inválido. Tente novamente.\n");
            continue;
        }

        printf("Digite o ano: ");
        scanf("%d", &data->ano);
        if(data->ano < 2024 || data->ano > 2025){
            printf("Datas de reserva[2024-2025]. Tente novamente.\n");
            continue;
        }
        valido = 1; // Se todas as validações passarem, define a data como válida
    }
}
/**
 * @brief Valida a entrada de uma opção de menu.
 * 
 * @param opcao Ponteiro para a variável que armazenará a opção válida.
 */
void validarLOOP(int *opcao) {
    char entrada[2];
    int valido = 0;

    while (!valido) {
        printf("Opção: ");
        scanf("%s", entrada);

        if (!apenasNumeros(entrada)) {
            printf("Apenas serão aceites DIGITOS.\n");
        } else {
            *opcao = entrada[0] - '0';  // Converte o caractere para inteiro
            if (*opcao >= 0 && *opcao <= 6) {
                valido = 1;
            }else{
                printf("Tente novamente.\n");
            }
        }
    }
}
/**
 * @brief Valida um endereço de email.
 * 
 * @param email String contendo o email a ser validado.
 * @return int 1 se o email é válido, 0 caso contrário.
 */
int validarEmail(char email[TAMANHO_MAIL]) {
    int tamanho = strlen(email);
    char *arroba = strchr(email, '@');
    char *ponto = strrchr(email, '.');

    // Critério 1: Deve ter pelo menos 6 caracteres
    if (tamanho < 6) {
        printf("Email inválido.\n");
        return 0;
    }

    // Critério 2: Deve conter um '@' com pelo menos um caractere antes
    if (!arroba || arroba == email) {
        printf("Email inválido.\n");
        return 0;
    }
    // Critério 3: Deve haver pelo menos um caractere entre '@' e '.'
    if (!ponto || ponto <= arroba + 1) {
        printf("Email inválido.\n");
        return 0;
    }
    // Critério 4: Deve haver pelo menos 2 caracteres após '.'
    if (strlen(ponto + 1) < 2) {
        printf("Email inválido.\n");
        return 0;
    }

    return 1; // Email é válido
}
/**
 * @brief Solicita um endereço de email válido do usuário.
 * 
 * @param email String onde o email válido será armazenado.
 */
void solicitarEmail(char email[TAMANHO_MAIL]) {
    while (1) {
        printf("Digite o seu Email: ");
        scanf("%s", email);
        if (validarEmail(email)) {
            printf("Email atribuído.\n");
            break;
        }
    }
}
/**
 * @brief Valida um número de telemóvel.
 * 
 * @param telemovel String contendo o número de telemóvel a ser validado.
 */
void validarTelemovel(char telemovel[TELEMOVEL_NUM]) {
    while (1) {
        printf("Introduza o número de telemóvel: ");
        scanf("%s", telemovel);
        if (strlen(telemovel) == 9 && (telemovel[0] == '9' || telemovel[0] == '2') && apenasNumeros(telemovel)) {
            break;
        } else {
            printf("Verifique novamente.\n");
        }
    }
}
/**
 * @brief Verifica se uma string contém apenas números.
 * 
 * @param numero String a ser verificada.
 * @return int 1 se a string contém apenas números, 0 caso contrário.
 */
int apenasNumeros(char *numero){
    while (*numero != '\0') {
        if (*numero < '0' || *numero > '9') {
            return 0;
        }
        numero++;
    }
    return 1;
}
/**
 * @brief Utilizado para facilitar leitura.
 */
void formataçao() {
    int i, j;
    for (i = 0; i < 1; i++) {
        for (j = 0; j < 1; j++) {
            putchar('\t');
        }
        putchar('\n');
    }
}
/**
 * @brief linha de separação.
 */
void linha() {
    printf("\n\n\t\t*************************************************************\n");
}
/**
 * @brief Converte a primeira letra de uma string para maiúscula.
 * 
 * @param str String a ser convertida.
 */
void maiscula(char *str) {
    if (str[0] >= 'a' && str[0] <= 'z') {
        str[0] = str[0] - 'a' + 'A';
    }
}
/**
 * @brief Valida um NIF (Número de Identificação Fiscal).
 * 
 * @param nif String contendo o NIF a ser validado.
 */
void validarNIF(char nif[NIF]) {
    printf("\t\tNIF de caráter obrigatório!\n");
    while (1) {
        printf("\t\tInsira o NIF: ");
        scanf("%s", nif); 
        if (strlen(nif) == 9 && apenasNumeros(nif)) {
            break;
        } else {
            printf("NIF inválido(tente novamente).\n");
        }
    }
}
/**
 * @brief Inicializa a lista de clientes.
 * 
 * @param listarclientes Ponteiro para a lista de clientes.
 * @param capacidadeInicial Capacidade inicial da lista de clientes.
 */
void inicializarClientes(ListaClientes *listarclientes,int capacidadeInicial) {
    listarclientes->clientes = (Cliente *)malloc(capacidadeInicial * sizeof(Cliente));
    if (listarclientes->clientes == NULL) {
        printf("Falha na alocação de memória.\n");
        exit(1);
    }
    listarclientes->capacidade = capacidadeInicial;
    listarclientes->totalClientes = 0;
}
/**
 * @brief Solicita as informações iniciais de um cliente.
 * 
 * @param cliente Ponteiro para a estrutura de cliente.
 */
void primeiro_contacto(Cliente *cliente) {
    printf("\t\tIntroduza o nome de cliente (PRIMEIRO): ");
    scanf("%s", cliente->nome); 
    printf("\t\tApelido: ");
    scanf("%s", cliente->apelido);
    solicitarEmail(cliente->email);
    validarTelemovel(cliente->telemovel);
    validarNIF(cliente->nif);
    maiscula(cliente->nome);
    maiscula(cliente->apelido);
}
/**
 * @brief Exibe as informações de um cliente.
 * 
 * @param cliente Ponteiro para a estrutura de cliente.
 */
void entrou(Cliente *cliente) {
    linha();
    printf("\t\t(ID)entificação:| %d |\n", cliente->id_pessoal);
    printf("\t\tCliente %s  %s  NIF: %s\n", cliente->nome, cliente->apelido, cliente->nif);
    printf("\t\t\t\t\tCLIENTE ATRIBUIDO!");
    linha();
}
/**
 * @brief Adiciona um novo cliente à lista de clientes.
 * 
 * @param listarclientes Ponteiro para a lista de clientes.
 * @param id_sequencial Ponteiro para o ID sequencial dos clientes.
 */
void adicionarCliente(ListaClientes *listarclientes, int *id_sequencial) {
    if (listarclientes->totalClientes >= listarclientes->capacidade) {
        listarclientes->capacidade *= 2;
        listarclientes->clientes = realloc(listarclientes->clientes, listarclientes->capacidade * sizeof(Cliente));
        if (listarclientes->clientes == NULL) {
            printf("Falha ao realocar memória.\n");
            exit(1);
        }
    }
    Cliente *cliente = &listarclientes->clientes[listarclientes->totalClientes];
    cliente->id_pessoal = (*id_sequencial)++;
    primeiro_contacto(cliente);
    entrou(cliente);
    listarclientes->totalClientes++;
}
/**
 * @brief Mostra todos os clientes na lista de clientes.
 * 
 * @param listaClientes Ponteiro para a lista de clientes.
 */
void mostrarClientes(ListaClientes *listaClientes) {
    int i;
    for (i = 0; i < listaClientes->totalClientes; i++) {
        linha();
        formataçao();
        printf("\t\tCliente [%d]\n\t\tNome: %s %s\n\t\tNIF: %s\n", listaClientes->clientes[i].id_pessoal, listaClientes->clientes[i].nome, listaClientes->clientes[i].apelido, listaClientes->clientes[i].nif);
        printf("\t\tNúmero telemóvel: %s\n\t\tEmail: %s\n", listaClientes->clientes[i].telemovel, listaClientes->clientes[i].email);
    }
}
/**
 * @brief Edita as informações de um cliente existente.
 * 
 * @param listarclientes Ponteiro para a lista de clientes.
 * @param id_editar ID do cliente a ser editado.
 */
void editarCliente(ListaClientes *listarclientes, int id_editar) {
    int indice = procurar_id(listarclientes->clientes, listarclientes->totalClientes, id_editar);
    if (indice != -1) {
        Cliente *cliente = &listarclientes->clientes[indice];
        int opcao;
        
        printf("Editar informações do cliente\n");
        printf("[1] Novo nome\n");
        printf("[2] Novo apelido\n");
        printf("[3] Editar NIF\n");
        printf("[4] Alterar Número telemóvel\n");
        printf("[5] Alterar Email\n");
        printf("[6] Voltar ao menu anterior\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Novo nome: ");
                scanf("%s", cliente->nome); 
                maiscula(cliente->nome);
                break;
            case 2:
                printf("Novo apelido: ");
                scanf("%s", cliente->apelido); 
                maiscula(cliente->apelido);
                break;
            case 3:
                validarNIF(cliente->nif);
                printf("O NIF foi alterado com sucesso\n");
                break;
            case 4:
                printf("Novo número: ");
                validarTelemovel(cliente->telemovel);
                printf("O número foi alterado com sucesso\n");
                break;
            case 5:
                solicitarEmail(cliente->email);
                printf("Email alterado com sucesso.\n");
                break;
            case 6:
                printf("Voltar ao menu anterior\n");
                return;
            default:
                printf("Opção inválida!\n");
        }
    } else {
        printf("ID inválido!\n");
    }
}
/**
 * @brief Elimina um cliente da lista de clientes.
 * 
 * @param listarclientes Ponteiro para a lista de clientes.
 * @param id_eliminar ID do cliente a ser eliminado.
 */
void eliminarCliente(ListaClientes *listarclientes, int id_eliminar) {
    int i;
    int indice = procurar_id(listarclientes->clientes, listarclientes->totalClientes, id_eliminar);
    if (indice != -1) {
        for (i = indice; i < listarclientes->totalClientes - 1; i++) {
            listarclientes->clientes[i] = listarclientes->clientes[i + 1];
        }
        listarclientes->totalClientes--;
        listarclientes->clientes = realloc(listarclientes->clientes, listarclientes->capacidade * sizeof(Cliente));
        if (listarclientes->clientes == NULL && listarclientes->totalClientes > 0) {
            printf("Erro ao realocar memória.\n");
            exit(1);
        }
        printf("O cliente de ID: [%d] foi apagado do sistema.\n", id_eliminar);
    } else {
        printf("ID introduzido não é válido. Tente novamente.\n");
    }
}
/**
 * @brief Procura um cliente pelo ID.
 * 
 * @param clientes Array de clientes.
 * @param num_clientes Número total de clientes.
 * @param id ID do cliente a ser procurado.
 * @return int Índice do cliente na lista, ou -1 se não encontrado.
 */
int procurar_id(Cliente *clientes, int num_clientes, int id) {
    for (int i = 0; i < num_clientes; i++) {
        if (clientes[i].id_pessoal == id) {
            return i;
        }
    }
    return -1;
}
/**
 * @brief Carrega os clientes a partir de um ficheiro.
 * 
 * @param listarclientes Ponteiro para a lista de clientes.
 * @param filename Nome do ficheiro a partir do qual os clientes serão carregados.
 * @param id_sequencial Ponteiro para o ID sequencial dos clientes.
 */
void carregarClientes(ListaClientes *listarclientes, const char *filename, int *id_sequencial) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }

    fscanf(file, "%d", id_sequencial);  
    Cliente cliente;
    while (fscanf(file, "%s %s %s %d %s %s",
                  cliente.nome, cliente.apelido, cliente.nif, &cliente.id_pessoal, cliente.email, cliente.telemovel) != EOF) {
        if (listarclientes->totalClientes >= listarclientes->capacidade) {
            listarclientes->capacidade *= 2;
            listarclientes->clientes = realloc(listarclientes->clientes, listarclientes->capacidade * sizeof(Cliente));
            if (listarclientes->clientes == NULL) {
                printf("Erro ao realocar memória.\n");
                fclose(file);
                return;
            }
        }
        listarclientes->clientes[listarclientes->totalClientes] = cliente;
        listarclientes->totalClientes++;
    }
    fclose(file);
}
/**
 * @brief Guarda os clientes em um ficheiro.
 * 
 * @param listarclientes Ponteiro para a lista de clientes.
 * @param filename Nome do ficheiro onde os clientes serão guardados.
 * @param id_sequencial ID sequencial dos clientes.
 */
void guardarClientes(ListaClientes *listarclientes, const char *filename, int id_sequencial) {
    int i;
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }
    fprintf(file, "%d\n", id_sequencial);
    for (i = 0; i < listarclientes->totalClientes; i++) {
        fprintf(file, "%s %s %s %d %s %s\n",
                listarclientes->clientes[i].nome,
                listarclientes->clientes[i].apelido,
                listarclientes->clientes[i].nif,
                listarclientes->clientes[i].id_pessoal,
                listarclientes->clientes[i].email,
                listarclientes->clientes[i].telemovel);
    }
    fclose(file);
    printf("Dados guardados com sucesso. Ficheiro: %s\n", filename);
}
/**
 * @brief Gera um relatório detalhado de todos os clientes e suas reservas.
 * 
 * @param listaClientes Ponteiro para a lista de clientes.
 * @param listaReservas Ponteiro para a lista de reservas.
 */
void relatorio_cliente(ListaClientes *listaClientes, ListaReservas *listaReservas) {
    int i, j;
    int totalReservas = 0;
    int maxReservas = 0;
    Cliente clienteComMaisReservas;

    printf("=========================================\n");
    printf("           RELATÓRIO DE CLIENTES         \n");
    printf("=========================================\n");

    printf("Total de Clientes Registados: %d\n", listaClientes->totalClientes);
    printf("-----------------------------------------\n");

    for (i = 0; i < listaClientes->totalClientes; i++) {
    Cliente cliente = listaClientes->clientes[i];
        int reservasCliente = 0;

        printf("Cliente ID: %d\n", cliente.id_pessoal);
        printf("Nome: %s %s\n", cliente.nome, cliente.apelido);

        printf("Reservas Realizadas:\n");

        for (j = 0; j < listaReservas->totalReservas; j++) {
            if (listaReservas->reservas[j].idCliente == cliente.id_pessoal) {
                reservasCliente++;
                printf("  - Reserva ID: %d, Espaço ID: %d, Data: %d/%d/%d, Duração: %d horas\n",
                       listaReservas->reservas[j].id,
                       listaReservas->reservas[j].idEspaço,
                       listaReservas->reservas[j].dataReserva.dia,
                       listaReservas->reservas[j].dataReserva.mes,
                       listaReservas->reservas[j].dataReserva.ano,
                       listaReservas->reservas[j].duraçao);
            }
        }

        printf("Total de Reservas: %d\n", reservasCliente);
        printf("-----------------------------------------\n");

        if (reservasCliente > maxReservas) {
            maxReservas = reservasCliente;
            clienteComMaisReservas = cliente;
        }
    }

    if (maxReservas > 0) {
        printf("=========================================\n");
        printf("Cliente com mais reservas:\n");
        printf("Cliente ID: %d\n", clienteComMaisReservas.id_pessoal);
        printf("Nome: %s %s\n", clienteComMaisReservas.nome, clienteComMaisReservas.apelido);
        printf("Total de Reservas: %d\n", maxReservas);
    }else{
        printf("Nenhum cliente tem reservas.\n");
    }

    printf("=========================================\n");
}