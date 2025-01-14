/**
 * @file espaço_func.c
 * @brief Ficheiro que contém todas as funções relativas ao espaço.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"

/**
 * @brief Inicializa a lista de espaços com uma capacidade inicial.
 * 
 * @param lista Ponteiro para a lista de espaços.
 * @param capacidadeInicial Capacidade inicial da lista.
 */
void inicializarEspaço(ListaEspaço *lista, int capacidadeInicial) {
    lista->espaços = (Espaço*)malloc(capacidadeInicial * sizeof(Espaço));
    if (lista->espaços == NULL) {
        printf("Falha na alocação de memória.\n");
        exit(1);
    }
    
    lista->espaços[0] = (Espaço){1,"Auditorio","Interior", 0,DISPONIVEL,0};
    lista->espaços[1] = (Espaço){2,"Sala de Reunião","Interior", 0,DISPONIVEL,0};
    lista->espaços[2] = (Espaço){3,"Espaço Externo","Exterior", 0,DISPONIVEL,0};
    lista->espaços[3] = (Espaço){4,"Bar", "Exterior", 0,DISPONIVEL,0};
    
    lista->totalEspaço = 4;
    lista->capacidade = capacidadeInicial;
}

/**
 * @brief Cria um novo espaço ou adiciona capacidade a um espaço existente.
 * 
 * @param lista Ponteiro para a lista de espaços.
 * @param id_sequencial Ponteiro para o ID sequencial dos espaços.
 */
void criarEspaço(ListaEspaço *lista, int *id_sequencial) {
    int i, id, opçao_p, quantidade, encontrado;
    char espaçoNovo[TAMANHO_NOME];
    *id_sequencial = lista->totalEspaço;
    int opçao_tipo;

    do {
        printf(" [0] MENU ANTERIOR\n");
        printf(" [1] Adicionar Capacidade ao Espaço\n");
        printf(" [2] Criar Novo Espaço\n");
        scanf("%d", &opçao_p);
     
        switch (opçao_p) {
            case 0:
                return;
            case 1:
                printf("Digite o ID do espaço ao qual deseja adicionar capacidade: ");
                scanf("%d", &id);
                encontrado = 0;
     
                for (i = 0; i < lista->totalEspaço; i++) {   
                    if (lista->espaços[i].id == id) {
                        printf("Capacidade a adicionar? ");
                        scanf("%d", &quantidade);   
                        lista->espaços[i].quantidade += quantidade;
                        printf("Adicionou %d à capacidade de %s |capacidade total: %d|\n", quantidade, lista->espaços[i].nome, lista->espaços[i].quantidade);  
                        encontrado = 1;
                        break;
                    }
                }
                if (!encontrado) {
                    printf("Espaço não encontrado.\n");
                }
                break;

            case 2:
                printf("Nome do novo espaço: ");
                scanf("%s", espaçoNovo);   
      
                do {
                    printf("[1]Tipo de espaço INTERIOR\n");
                    printf("[2]Tipo de espaço EXTERIOR\n");
                    printf("Tipo de espaço (interior/exterior): ");
                    validarLOOP(&opçao_tipo);
                    switch (opçao_tipo) {
                        case 1:
                            strcpy(lista->espaços[i].tipo, "Interior");
                            break;
                        case 2:
                            strcpy(lista->espaços[i].tipo, "Exterior");
                            break;
                        default:
                            printf("Opção inválida! Tente novamente.\n");
                            break;
                    }
                } while (opçao_tipo != 1 && opçao_tipo != 2);
 
                if (lista->totalEspaço == lista->capacidade) {
                    lista->capacidade *= 2;
                    Espaço *temp = realloc(lista->espaços, lista->capacidade * sizeof(Espaço));
                    if (temp == NULL) {
                        printf("Erro ao realocar memória.\n");
                        return;
                    }
                    lista->espaços = temp;
                }

                lista->espaços[lista->totalEspaço] = (Espaço){
                    .id = ++(*id_sequencial),
                    .nome = "",
                    .tipo = "",
                    .quantidade = 0,
                    .estado = DISPONIVEL,
                    .quantidadeReserva = 0
                };
                strcpy(lista->espaços[lista->totalEspaço].nome, espaçoNovo);
                printf("Capacidade a atribuir a %s: ", espaçoNovo);
                scanf("%d", &quantidade);
                lista->espaços[lista->totalEspaço].quantidade = quantidade;
                lista->totalEspaço++;
                printf("Novo espaço %s\tID %d\tCapacidade %d\n", espaçoNovo, *id_sequencial, quantidade);
                break;
           
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while (opçao_p != 0);
}

/**
 * @brief Elimina um espaço da lista de espaços.
 * 
 * @param lista Ponteiro para a lista de espaços.
 * @param id_espaco ID do espaço a ser eliminado.
 */
void eliminarEspaço(ListaEspaço *lista, int id_espaco) {
    int encontrado = 0;

    // Procurar o espaço pelo ID
    for (int i = 0; i < lista->totalEspaço; i++) {
        if (lista->espaços[i].id == id_espaco) {
            encontrado = 1;

            // Deslocar todos os espaços subsequentes uma posição para trás
            for (int j = i; j < lista->totalEspaço - 1; j++) {
                lista->espaços[j] = lista->espaços[j + 1];
            }

            // Diminuir o total de espaços
            lista->totalEspaço--;

            printf("Espaço com ID %d eliminado com sucesso.\n", id_espaco);
            break;
        }
    }

    if (!encontrado) {
        printf("Espaço com ID %d não encontrado.\n", id_espaco);
    }
}

/**
 * @brief Edita um espaço existente na lista de espaços.
 * 
 * @param lista Ponteiro para a lista de espaços.
 * @param id_espaco ID do espaço a ser editado.
 */
void editarEspaço(ListaEspaço *lista, int id_espaco) {
    int encontrado = 0;
    char novo_nome[30];
    int nova_quantidade;
    int opção_tipo;

    // Procurar o espaço pelo ID
    for (int i = 0; i < lista->totalEspaço; i++) {
        if (lista->espaços[i].id == id_espaco) {
            encontrado = 1;

            // Solicitar novo nome e nova quantidade
            printf("Novo nome para o espaço '%s' (ID: %d): ", lista->espaços[i].nome, id_espaco);
            scanf("%s", novo_nome);
      
            do {
                printf("[1]Tipo de espaço INTERIOR\n");
                printf("[2]Tipo de espaço EXTERIOR\n");
                printf("Tipo de espaço (interior/exterior): ");
                validarLOOP(&opção_tipo);
                switch (opção_tipo) {
                    case 1:
                        strcpy(lista->espaços[i].tipo, "Interior");
                        break;
                    case 2:
                        strcpy(lista->espaços[i].tipo, "Exterior");
                        break;
                    default:
                        printf("Opção inválida! Tente novamente.\n");
                        break;
                }
            } while (opção_tipo != 1 && opção_tipo != 2);

            printf("Nova quantidade para o espaço '%s' (ID: %d): ", lista->espaços[i].nome, id_espaco);
            scanf("%d", &nova_quantidade);

            // Atualizar o espaço
            strcpy(lista->espaços[i].nome, novo_nome);
            lista->espaços[i].quantidade = nova_quantidade;

            printf("Espaço atualizado com sucesso!\n");
            printf("ID: %d\tNome: %s\tQuantidade: %d\n", lista->espaços[i].id, lista->espaços[i].nome, lista->espaços[i].quantidade);
            break;
        }
    }

    if (!encontrado) {
        printf("Espaço com ID %d não encontrado.\n", id_espaco);
    }
}

/**
 * @brief Verifica se um espaço existe na lista de espaços.
 * 
 * @param listaEspacos Ponteiro para a lista de espaços.
 * @param idEspaço ID do espaço a ser verificado.
 * @return int Retorna 1 se o espaço existir, 0 caso contrário.
 */
int espaçoExiste(ListaEspaço *listaEspacos, int idEspaço) {
    int i;
    for (i = 0; i < listaEspacos->totalEspaço; i++) {
        if (listaEspacos->espaços[i].id == idEspaço) {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Mostra todos os espaços na lista de espaços.
 * 
 * @param lista Ponteiro para a lista de espaços.
 */
void mostrar_espaço(ListaEspaço *lista) {
    int i;
    if (lista == NULL || lista->totalEspaço == 0) {
        printf("Nenhum espaço disponível.\n");
        return;
    }
    for (i = 0; i < lista->totalEspaço; i++) {
        printf("ID: %d\tNome: %s\tTipo: %s\tCapacidade: %d\n", 
            lista->espaços[i].id, 
            lista->espaços[i].nome,
            lista->espaços[i].tipo,
            lista->espaços[i].quantidade);
    }
}

/**
 * @brief Marca um espaço como reservado.
 * 
 * @param lista Ponteiro para a lista de espaços.
 * @param id_espaço ID do espaço a ser reservado.
 * @param quantidade Quantidade a ser reservada.
 */
void espaçoReservado(ListaEspaço *lista, int id_espaço, int quantidade) {
    for (int i = 0; i < lista->totalEspaço; i++) {
        if (lista->espaços[i].id == id_espaço) {
            lista->espaços[i].quantidadeReserva += quantidade;
            lista->espaços[i].quantidade -= quantidade;
            break;
        }
    }
}

/**
 * @brief Mostra todos os espaços reservados na lista de espaços.
 * 
 * @param lista Ponteiro para a lista de espaços.
 */
void espaços_reservados(ListaEspaço *lista) {
    for (int i = 0; i < lista->totalEspaço; i++) {
        if (lista->espaços[i].quantidadeReserva > 0) {
            printf("ID: %d, Nome: %s, Quantidade: %d\n", lista->espaços[i].id, lista->espaços[i].nome, lista->espaços[i].quantidadeReserva);
        }
    }
}

/**
 * @brief Carrega os dados dos espaços a partir de um ficheiro.
 * 
 * @param lista Ponteiro para a lista de espaços.
 * @param nomeFicheiro Nome do ficheiro a partir do qual os dados serão carregados.
 * @param id_sequencial_espaço Ponteiro para o ID sequencial dos espaços.
 */
void carregarEspaços(ListaEspaço *lista, const char *nomeFicheiro, int *id_sequencial_espaço) {
    FILE *file = fopen(nomeFicheiro, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o ficheiro %s para leitura.\n", nomeFicheiro);
        return;
    }

    // Ler o número total de espaços
    fread(&(lista->totalEspaço), sizeof(int), 1, file);

    lista->capacidade = lista->totalEspaço;
    lista->espaços = malloc(lista->capacidade * sizeof(Espaço));
    if (lista->espaços == NULL) {
        printf("Erro ao alocar memória para os espaços.\n");
        fclose(file);
        return;
    }
    fread(lista->espaços, sizeof(Espaço), lista->totalEspaço, file);

    fclose(file);
    printf("Dados carregados com sucesso de %s.\n", nomeFicheiro);
}

/**
 * @brief Guarda os dados dos espaços em um ficheiro.
 * 
 * @param lista Ponteiro para a lista de espaços.
 * @param nomeFicheiro Nome do ficheiro onde os dados serão guardados.
 * @param id_sequencial_espaço ID sequencial dos espaços.
 */
void guardarEspaços(ListaEspaço *lista, const char *nomeFicheiro, int id_sequencial_espaço) {
    FILE *file = fopen(nomeFicheiro, "wb");
    if (file == NULL) {
        printf("Erro ao abrir o ficheiro %s para escrita.\n", nomeFicheiro);
        return;
    }

    // Escrever o número total de espaços
    fwrite(&(lista->totalEspaço), sizeof(int), 1, file);
    // Escrever os dados dos espaços a quantidade de vezes totalEspaço
    fwrite(lista->espaços, sizeof(Espaço), lista->totalEspaço, file);

    fclose(file);
    printf("Dados guardados com sucesso em %s.\n", nomeFicheiro);
}

/**
 * @brief Gera um relatório dos espaços na lista de espaços.
 * 
 * @param listaEspacos Ponteiro para a lista de espaços.
 */
void relatorio_espaço(ListaEspaço *listaEspacos) {
    int i;
    int totalEspacosDisponiveis = 0;
    int totalInteriores = 0;
    int totalExteriores = 0;
    int maxReservas = 0;
    int minReservas = 0;
    Espaço espacoComMaisReservas;
    Espaço espacoComMenosReservas;

    printf("=========================================\n");
    printf("           RELATÓRIO DE ESPAÇOS         \n");
    printf("=========================================\n");

    //  Espaços disponíveis
    for (i = 0; i < listaEspacos->totalEspaço; i++) {
        if (listaEspacos->espaços[i].quantidade > 0) {
            totalEspacosDisponiveis++;

            if (strcmp(listaEspacos->espaços[i].tipo, "Interior") == 0) {
                totalInteriores++;
            } else if (strcmp(listaEspacos->espaços[i].tipo, "Exterior") == 0) {
                totalExteriores++;
            }
        }

        // Espaço mais e menos reservado
        if (i == 0 || listaEspacos->espaços[i].quantidadeReserva > espacoComMaisReservas.quantidadeReserva) {
            espacoComMaisReservas = listaEspacos->espaços[i];
        }

        if (i == 0 || listaEspacos->espaços[i].quantidadeReserva < espacoComMenosReservas.quantidadeReserva) {
            espacoComMenosReservas = listaEspacos->espaços[i];
        }
    }

    // Total de espaços
    printf("Total de Espaços Disponíveis: %d\n", totalEspacosDisponiveis);
    printf("Total de Espaços Interiores: %d\n", totalInteriores);
    printf("Total de Espaços Exteriores: %d\n", totalExteriores);
    printf("-----------------------------------------\n");

    // Espaço com mais reservas
    if (totalEspacosDisponiveis > 0) {
        printf("Espaço com Mais Reservas:\n");
        printf("ID: %d\tNome: %s\tTipo: %s\tReservas: %d\n",
               espacoComMaisReservas.id,
               espacoComMaisReservas.nome,
               espacoComMaisReservas.tipo,
               espacoComMaisReservas.quantidadeReserva);
    } else {
        printf("Nenhum espaço disponível.\n");
    }

    // Espaço com menos reservas
    if (totalEspacosDisponiveis > 0) {
        printf("Espaço com Menos Reservas:\n");
        printf("ID: %d\tNome: %s\tTipo: %s\tReservas: %d\n",
               espacoComMenosReservas.id,
               espacoComMenosReservas.nome,
               espacoComMenosReservas.tipo,
               espacoComMenosReservas.quantidadeReserva);
    } else {
        printf("Nenhum espaço disponível.\n");
    }

    printf("=========================================\n");
}