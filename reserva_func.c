/**
 * @file reserva_func.c
 * @brief Ficheiro que contém todas as funções relativas às reservas.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"
#include "reservas.h"
/**
 * @brief Inicializa a lista de reservas.
 * 
 * @param lista Ponteiro para a lista de reservas.
 * @param capacidadeInicial Capacidade inicial da lista de reservas.
 */
void inicializarReservas(ListaReservas *lista, int capacidadeInicial) {
    lista->reservas = (Reserva*)malloc(capacidadeInicial * sizeof(Reserva));
    if (lista->reservas == NULL) {
        printf("Falha na alocação de memória.\n");
        exit(1);
    }
    lista->capacidade = capacidadeInicial;
    lista->totalReservas = 0;
}
/**
 * @brief Cria uma nova reserva.
 * 
 * @param listaReservas Ponteiro para a lista de reservas.
 * @param listaClientes Ponteiro para a lista de clientes.
 * @param listaEspaços Ponteiro para a lista de espaços.
 * @param listaEquipamentos Ponteiro para a lista de equipamentos.
 * @param id_sequencial_reservas Ponteiro para o ID sequencial das reservas.
 */
void criarReserva(ListaReservas *listaReservas, ListaClientes *listaClientes, ListaEspaço *listaEspaços, ListaEquipamento *listaEquipamentos, int *id_sequencial_reservas) {
    Reserva novaReserva;
    int i,adicionarMaisEquipamentos;
    int idClienteValido = 0;
    int idEspaçoValido = 0;
    int idEquipamentoValido=0;
    novaReserva.removida=0;
   *id_sequencial_reservas= listaReservas->totalReservas;
    if (listaReservas->totalReservas == listaReservas->capacidade) {
        listaReservas->capacidade *= 2;
        Reserva *temp = realloc(listaReservas->reservas, listaReservas->capacidade * sizeof(Reserva));
        if (temp == NULL) {
            printf("Erro ao realocar memória.\n");
            return;
        }
        listaReservas->reservas = temp;
    }
    novaReserva.id = ++(*id_sequencial_reservas);
   

    while (!idClienteValido) {
        if (listaClientes == NULL || listaClientes->totalClientes == 0) {
            printf("Nenhum cliente disponível.\n");
            return;
        }
        mostrarClientes(listaClientes); // Supondo que existe uma função para listar os clientes
        printf("ID do Cliente: ");
        scanf("%d", &novaReserva.idCliente);
        if (clienteExiste(listaClientes, novaReserva.idCliente)) {
            idClienteValido = 1;
        }else{
            printf("ID de Cliente inválido. Tente novamente.\n");
        }
    }

    idEspaçoValido = 0;
  while (!idEspaçoValido) {
    mostrar_espaço(listaEspaços);
    printf("ID do Espaço: ");
    scanf("%d", &novaReserva.idEspaço);
    printf("Capacidade de Espaço que necessita: ");
    scanf("%d", &novaReserva.quantidadeEspaço);

    for (i = 0; i < listaEspaços->totalEspaço; i++) {
        if (listaEspaços->espaços[i].id == novaReserva.idEspaço) {
            if (listaEspaços->espaços[i].quantidade >= novaReserva.quantidadeEspaço) {
                listaEspaços->espaços[i].quantidadeReserva += novaReserva.quantidadeEspaço;
                listaEspaços->espaços[i].quantidade -= novaReserva.quantidadeEspaço;
                idEspaçoValido = 1;
                strncpy(novaReserva.nomeEspaço, listaEspaços->espaços[i].nome, NOME_ESPAÇO-1);
                novaReserva.nomeEspaço[NOME_ESPAÇO-1] = '\0';
                break;
            } else {
            }
        }
    }
    if (!idEspaçoValido) {
        printf("Capacidade insuficiente do espaço disponível ou ID inválido, tente novamente.\n");        
    }
}
    obterData(&novaReserva.dataReserva);

    do{
    printf("Duração da Reserva (em horas): ");
    scanf("%d", &novaReserva.duraçao);
    if(novaReserva.duraçao < 1 || novaReserva.duraçao > 48){
        printf("A reserva tem uma duração min |1H| -- máx|48H| .\n");
    }
    
    }while(novaReserva.duraçao < 1 || novaReserva.duraçao > 48);


do{
    printf("Número de Participantes: ");
    scanf("%d", &novaReserva.numParticipantes);
   if(novaReserva.numParticipantes > novaReserva.quantidadeEspaço){
       printf("Número de Participantes excede a capacidade do espaço. Tente novamente.\n");
   }
}while(novaReserva.numParticipantes > novaReserva.quantidadeEspaço);


    idEquipamentoValido = 0;
while (!idEquipamentoValido) {
    mostrarEquipamentos(listaEquipamentos);
    printf("Qual o ID do equipamento a associar à reserva? ");
    scanf("%d", &novaReserva.idEquipamento);

    for (i = 0; i < listaEquipamentos->totalEquipamento; i++) {
        if (listaEquipamentos->equipamentos[i].id == novaReserva.idEquipamento) {
            idEquipamentoValido = 1;
            strcpy(novaReserva.tipoEquipamentos, listaEquipamentos->equipamentos[i].tipo);
            break;
        }
    }

    if (!idEquipamentoValido) {
        printf("ID do equipamento inválido. Tente novamente.\n");
    }
}
    reservados(listaEquipamentos, novaReserva.idEquipamento, novaReserva.tipoEquipamentos);
    novaReserva.quantidadeEquipamentos = listaEquipamentos->equipamentos[i].quantidadeReserva;
  
    
    novaReserva.estado = PENDENTE;

    listaReservas->reservas[listaReservas->totalReservas++] = novaReserva;
 
    printf("Reserva criada com sucesso! ID da Reserva: %d\n", novaReserva.id);
}
/**
 * @brief Edita uma reserva existente.
 * 
 * @param listaReservas Ponteiro para a lista de reservas.
 * @param listaClientes Ponteiro para a lista de clientes.
 * @param listaEspaços Ponteiro para a lista de espaços.
 * @param listaEquipamentos Ponteiro para a lista de equipamentos.
 * @param id_reserva ID da reserva a ser editada.
 */
void editarReserva(ListaReservas *listaReservas, ListaClientes *listaClientes, ListaEspaço *listaEspaços, ListaEquipamento *listaEquipamentos, int id_reserva) {
    int i, encontrado = 0;

    for (i = 0; i < listaReservas->totalReservas; i++) {
        if (listaReservas->reservas[i].id == id_reserva) {
            encontrado = 1;

            // Devolver itens antigos ao inventário
            for (int j = 0; j < listaEquipamentos->totalEquipamento; j++) {
                if (listaEquipamentos->equipamentos[j].id == listaReservas->reservas[i].idEquipamento) {
                    listaEquipamentos->equipamentos[j].quantidade += listaReservas->reservas[i].quantidadeEquipamentos;
                    listaEquipamentos->equipamentos[j].quantidadeReserva -= listaReservas->reservas[i].quantidadeEquipamentos;
                    break;
                }
            }

            for (int j = 0; j < listaEspaços->totalEspaço; j++) {
                if (listaEspaços->espaços[j].id == listaReservas->reservas[i].idEspaço) {
                    listaEspaços->espaços[j].quantidade += listaReservas->reservas[i].quantidadeEspaço;
                    listaEspaços->espaços[j].quantidadeReserva -= listaReservas->reservas[i].quantidadeEspaço;
                    break;
                }
            }

            // Atualizar cliente
            int idClienteValido = 0;
            while (!idClienteValido) {
                if (listaClientes == NULL || listaClientes->totalClientes == 0) {
                    printf("Nenhum cliente disponível.\n");
                    return;
                }
                mostrarClientes(listaClientes); // Supondo que existe uma função para listar os clientes
                printf("ID do Cliente: ");
                scanf("%d", &listaReservas->reservas[i].idCliente);
                if (clienteExiste(listaClientes, listaReservas->reservas[i].idCliente)) {
                    idClienteValido = 1;
                } else {
                    printf("ID de Cliente inválido. Tente novamente.\n");
                }
            }

            // Atualizar espaço
            int idEspacoValido = 0;
            while (!idEspacoValido) {
                mostrar_espaço(listaEspaços); // Supondo que existe uma função para listar os espaços
                printf("ID do Espaço: ");
                scanf("%d", &listaReservas->reservas[i].idEspaço);
                printf("Capacidade de Espaço que necessita: ");
                scanf("%d", &listaReservas->reservas[i].quantidadeEspaço);

                for (int j = 0; j < listaEspaços->totalEspaço; j++) {
                    if (listaEspaços->espaços[j].id == listaReservas->reservas[i].idEspaço) {
                        if (listaEspaços->espaços[j].quantidade >= listaReservas->reservas[i].quantidadeEspaço) {
                            idEspacoValido = 1;
                            listaEspaços->espaços[j].quantidade -= listaReservas->reservas[i].quantidadeEspaço;
                            listaEspaços->espaços[j].quantidadeReserva += listaReservas->reservas[i].quantidadeEspaço;
                            break;
                        } else {
                            printf("Capacidade insuficiente do espaço disponível. Tente novamente.\n");
                        }
                    }
                }

                if (!idEspacoValido) {
                    printf("ID de Espaço inválido ou quantidade insuficiente. Tente novamente.\n");
                }
            }

            // Atualizar data da reserva
            obterData(&listaReservas->reservas[i].dataReserva);

            // Atualizar duração
            printf("Duração (em horas): ");
            scanf("%d", &listaReservas->reservas[i].duraçao);

            // Atualizar estado
            printf("Estado (0 - Pendente, 1 - Confirmada, 2 - Finalizada, 3 - Cancelada): ");
            int estado;
            scanf("%d", &estado);
            listaReservas->reservas[i].estado = estado;

            // Atualizar número de participantes
            do {
                printf("Número de Participantes: ");
                scanf("%d", &listaReservas->reservas[i].numParticipantes);
                if (listaReservas->reservas[i].numParticipantes > listaReservas->reservas[i].quantidadeEspaço) {
                    printf("Número de Participantes excede a capacidade do espaço. Tente novamente.\n");
                }
            } while (listaReservas->reservas[i].numParticipantes > listaReservas->reservas[i].quantidadeEspaço);

            // Atualizar tipo e quantidade de equipamentos
            int idEquipamentoValido = 0;
            while (!idEquipamentoValido) {
                mostrarEquipamentos(listaEquipamentos); // Supondo que existe uma função para listar os equipamentos
                printf("ID do Equipamento: ");
                scanf("%d", &listaReservas->reservas[i].idEquipamento);
                printf("Tipo de Equipamentos: ");
                scanf("%s", listaReservas->reservas[i].tipoEquipamentos);

                for (int j = 0; j < listaEquipamentos->totalEquipamento; j++) {
                    if (listaEquipamentos->equipamentos[j].id == listaReservas->reservas[i].idEquipamento &&
                        strcmp(listaEquipamentos->equipamentos[j].tipo, listaReservas->reservas[i].tipoEquipamentos) == 0) {
                        idEquipamentoValido = 1;
                        int quantidadeValida = 0;
                        while (!quantidadeValida) {
                            printf("Quantidade de Equipamentos: ");
                            scanf("%d", &listaReservas->reservas[i].quantidadeEquipamentos);
                            if (listaReservas->reservas[i].quantidadeEquipamentos <= listaEquipamentos->equipamentos[j].quantidade) {
                                quantidadeValida = 1;
                            } else {
                                printf("Quantidade de Equipamentos indisponível. Tente novamente.\n");
                            }
                        }
                        // Atualizar inventário de equipamentos
                        listaEquipamentos->equipamentos[j].quantidade -= listaReservas->reservas[i].quantidadeEquipamentos;
                        listaEquipamentos->equipamentos[j].quantidadeReserva += listaReservas->reservas[i].quantidadeEquipamentos;
                        break;
                    }
                }

                if (!idEquipamentoValido) {
                    printf("ID ou Tipo de Equipamento inválido. Tente novamente.\n");
                }
            }

            printf("Reserva atualizada com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Reserva com ID %d não encontrada.\n", id_reserva);
    }
}
/**
 * @brief Elimina uma reserva existente.
 * 
 * @param listaReservas Ponteiro para a lista de reservas.
 * @param listaEquipamentos Ponteiro para a lista de equipamentos.
 * @param listaEspaços Ponteiro para a lista de espaços.
 * @param id_eliminar ID da reserva a ser eliminada.
 */
void eliminarReserva(ListaReservas *listaReservas, ListaEquipamento *listaEquipamentos, ListaEspaço *listaEspaços, int id_eliminar) {
    int i,j;
    int indice = -1;

    // Encontrar o índice da reserva pelo ID
    for ( i = 0; i < listaReservas->totalReservas; i++) {
        if (listaReservas->reservas[i].id == id_eliminar) {
            indice = i;
            break;
        }
    }

    if (indice != -1) {
        // Atualizar inventário para libertar os itens reservados
        for (j = 0; j < listaEquipamentos->totalEquipamento; j++) {
            if (listaEquipamentos->equipamentos[j].id == listaReservas->reservas[indice].idEquipamento) {
                listaEquipamentos->equipamentos[j].quantidade += listaReservas->reservas[indice].quantidadeEquipamentos;
                listaEquipamentos->equipamentos[j].quantidadeReserva -= listaReservas->reservas[indice].quantidadeEquipamentos;
                break;
            }
        }

        for (j = 0; j < listaEspaços->totalEspaço; j++) {
            if (listaEspaços->espaços[j].id == listaReservas->reservas[indice].idEspaço) {
                listaEspaços->espaços[j].quantidade += listaReservas->reservas[indice].quantidadeEspaço;
                listaEspaços->espaços[j].quantidadeReserva -= listaReservas->reservas[indice].quantidadeEspaço;
                break;
            }
        }

        // Marcar a reserva como removida
        listaReservas->reservas[indice].removida = 1;

        printf("Reserva com ID %d eliminada com sucesso.\n", id_eliminar);
    } else {
        printf("ID introduzido não é válido. Tente novamente.\n");
    }
}
/**
 * @brief Mostra todas as reservas.
 * 
 * @param lista Ponteiro para a lista de reservas.
 */
void mostrarReservas(ListaReservas *lista) {
    int i;
            formataçao();
    for (i = 0; i < lista->totalReservas; i++) {
        if (!lista->reservas[i].removida) {
            printf("ID Reserva: %d\tCliente ID: %d\nEspaço: %s\nData: %d/%d/%d\tDuração: %d(h)\tEstado: %s\tParticipantes: %d\tEquipamento (tipo): %s\tQuantidade: %d\n", 
                   lista->reservas[i].id, 
                   lista->reservas[i].idCliente, 
                   lista->reservas[i].nomeEspaço,
                   lista->reservas[i].dataReserva.dia,
                   lista->reservas[i].dataReserva.mes,
                   lista->reservas[i].dataReserva.ano,
                   lista->reservas[i].duraçao,
                   estadoReservaParaString(lista->reservas[i].estado), 
                   lista->reservas[i].numParticipantes,
                   lista->reservas[i].tipoEquipamentos,
                   lista->reservas[i].quantidadeEquipamentos);
        }
    putchar('\n');
    }
}
/**
 * @brief Converte o estado da reserva para uma string.
 * 
 * @param estado Estado da reserva.
 * @return char* String representando o estado da reserva.
 */
char *estadoReservaParaString(EstadoReserva estado) {
    switch (estado) {
        case PENDENTE:
            return "Pendente";
        case CONFIRMADA:
            return "Confirmada";
        case FINALIZADA:
            return "Finalizada";
        case CANCELADA:
            return "Cancelada";
        default:
            return "Desconhecido";
    }
}
/**
 * @brief Carrega as reservas a partir de um ficheiro.
 * 
 * @param lista Ponteiro para a lista de reservas.
 * @param nomeFicheiro Nome do ficheiro a partir do qual as reservas serão carregadas.
 * @param id_sequencial_reservas Ponteiro para o ID sequencial das reservas.
 */
void carregarReservas(ListaReservas *lista, const char *nomeFicheiro, int *id_sequencial_reservas) {
    FILE *file = fopen(nomeFicheiro, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o ficheiro %s para leitura.\n", nomeFicheiro);
        return;
    }

    // Ler o total de reservas
    fread(&(lista->totalReservas), sizeof(int), 1, file);

    // Ler o id sequencial das reservas
    fread(id_sequencial_reservas, sizeof(int), 1, file);

    // Ajustar a capacidade da lista de reservas
    lista->capacidade = lista->totalReservas;
    lista->reservas = malloc(lista->capacidade * sizeof(Reserva));
    if (lista->reservas == NULL) {
        printf("Erro ao alocar memória para as reservas.\n");
        fclose(file);
        return;
    }

    // Ler as reservas do arquivo
    fread(lista->reservas, sizeof(Reserva), lista->totalReservas, file);

    fclose(file);
    printf("Dados carregados com sucesso de %s.\n", nomeFicheiro);
}
/**
 * @brief Guarda os dados das reservas em um ficheiro.
 * 
 * @param lista Ponteiro para a lista de equipamentos.
 * @param nomeFicheiro Nome do ficheiro onde os dados serão guardados.
 * @param id_sequencial_equipamentos ID sequencial das reservas.
 */
void guardarReservas(ListaReservas *lista, const char *nomeFicheiro, int id_sequencial_reservas) {
    FILE *file = fopen(nomeFicheiro, "wb");
    if (file == NULL) {
        printf("Erro ao abrir o ficheiro %s para escrita.\n", nomeFicheiro);
        return;
    }

    // Escrever o total de reservas
    fwrite(&(lista->totalReservas), sizeof(int), 1, file);

    // Escrever o id sequencial das reservas
    fwrite(&id_sequencial_reservas, sizeof(int), 1, file);

    // Escrever as reservas no arquivo
    fwrite(lista->reservas, sizeof(Reserva), lista->totalReservas, file);

    fclose(file);
    printf("Dados guardados com sucesso em %s.\n", nomeFicheiro);
}
/**
 * @brief Altera o estado de uma reserva.
 * 
 * @param listaReservas Ponteiro para a lista de reservas.
 * @param listaEquipamentos Ponteiro para a lista de equipamentos.
 * @param listaEspaços Ponteiro para a lista de espaços.
 */
void alterarEstadoReserva(ListaReservas *listaReservas, ListaEquipamento *listaEquipamentos, ListaEspaço *listaEspaços) {
    int id_reserva, novo_estado;
    int encontrado = 0;

    printf("Digite o ID da reserva que deseja alterar o estado: ");
    scanf("%d", &id_reserva);

    for (int i = 0; i < listaReservas->totalReservas; i++) {
        if (listaReservas->reservas[i].id == id_reserva) {
            encontrado = 1;

            printf("Estado atual: %s\n", estadoReservaParaString(listaReservas->reservas[i].estado));
            printf("Selecione o novo estado:\n");
            printf("0 - Pendente\n");
            printf("1 - Confirmada\n");
            printf("2 - Finalizada\n");
            printf("3 - Cancelada\n");
            printf("Digite o número correspondente ao novo estado: ");
            scanf("%d", &novo_estado);

            if (novo_estado >= 0 && novo_estado <= 3) {
                // Atualizar inventário se a reserva for finalizada ou cancelada
                if (novo_estado == FINALIZADA || novo_estado == CANCELADA) {
                    // Atualizar quantidade de equipamentos
                    for (int j = 0; j < listaEquipamentos->totalEquipamento; j++) {
                        if (listaEquipamentos->equipamentos[j].id == listaReservas->reservas[i].idEquipamento) {
                            listaEquipamentos->equipamentos[j].quantidade += listaReservas->reservas[i].quantidadeEquipamentos;
                            listaEquipamentos->equipamentos[j].quantidadeReserva -= listaReservas->reservas[i].quantidadeEquipamentos;
                        }
                    }

                    // Atualizar quantidade de espaços
                    for (int j = 0; j < listaEspaços->totalEspaço; j++) {
                        if (listaEspaços->espaços[j].id == listaReservas->reservas[i].idEspaço) {
                            listaEspaços->espaços[j].quantidade += listaReservas->reservas[i].quantidadeEspaço;
                            listaEspaços->espaços[j].quantidadeReserva -= listaReservas->reservas[i].quantidadeEspaço;
                        }
                    }
                    printf("Inventário foi reposto.\n");
                }

                listaReservas->reservas[i].estado = novo_estado;
                printf("Estado da reserva com ID %d alterado com sucesso para %s.\n", id_reserva, estadoReservaParaString(novo_estado));
            } else {
                printf("Estado inválido. Tente novamente.\n");
            }
            break;
        }
    }

    if (!encontrado) {
        printf("Reserva com ID %d não encontrada.\n", id_reserva);
    }
}
/**
 * @brief Gera um relatório detalhado de todas as reservas.
 * 
 * @param listaReservas Ponteiro para a lista de reservas.
 * @param listaClientes Ponteiro para a lista de clientes.
 * @param EspaçoLista Ponteiro para a lista de espaços.
 * @param listaEquipamentos Ponteiro para a lista de equipamentos.
 */
void relatorio_reservas(ListaReservas *listaReservas, ListaClientes *listaClientes, ListaEspaço *EspaçoLista, ListaEquipamento *listaEquipamentos) {
    int i, j;

    printf("=========================================\n");
    printf("           RELATÓRIO DE RESERVAS         \n");
    printf("=========================================\n");

    if (listaReservas->totalReservas == 0) {
        printf("Nenhuma reserva disponível.\n");
        printf("=========================================\n");
        return;
    }

    for (i = 0; i < listaReservas->totalReservas; i++) {
        Reserva reserva = listaReservas->reservas[i];
        Cliente cliente;
        Espaço espaço;
        Equipamento equipamento;

        // Encontrar o cliente
        for (j = 0; j < listaClientes->totalClientes; j++) {
            if (listaClientes->clientes[j].id_pessoal == reserva.idCliente) {
                cliente = listaClientes->clientes[j];
                break;
            }
        }

        // Encontrar o espaço
        for (j = 0; j < EspaçoLista->totalEspaço; j++) {
            if (EspaçoLista->espaços[j].id == reserva.idEspaço) {
                espaço = EspaçoLista->espaços[j];
                break;
            }
        }

        // Encontrar o equipamento
        for (j = 0; j < listaEquipamentos->totalEquipamento; j++) {
            if (listaEquipamentos->equipamentos[j].id == reserva.idEquipamento) {
                equipamento = listaEquipamentos->equipamentos[j];
                break;
            }
        }

        // Calcular a taxa de ocupação do espaço
       float taxaOcupaçao = (float)reserva.numParticipantes / reserva.quantidadeEspaço * 100;

        // Mostrar os detalhes da reserva
        printf("Reserva ID: %d\n", reserva.id);
        printf("Cliente: %s %s\n", cliente.nome, cliente.apelido);
        printf("Data da Reserva: %d/%d/%d\n", reserva.dataReserva.dia, reserva.dataReserva.mes, reserva.dataReserva.ano);
        printf("Duração: %d horas\n", reserva.duraçao);
        printf("Número de Participantes: %d\n", reserva.numParticipantes);
        printf("Estado: %s\n", (reserva.estado == 0) ? "Pendente" : (reserva.estado == 1) ? "Confirmada" : (reserva.estado == 2) ? "Finalizada" : "Cancelada");
        printf("Espaço: %s\t||Taxa de Ocupação do Espaço: %.2f%%\n", espaço.nome, taxaOcupaçao);
        printf("Equipamento: %s\tTipo Equipamento: %s\n", equipamento.nome, equipamento.tipo);
        printf("Quantidade de Equipamentos Reservados: %d\n", reserva.quantidadeEquipamentos);
        printf("-----------------------------------------\n");
    }
}