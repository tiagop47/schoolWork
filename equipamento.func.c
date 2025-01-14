/**
 * @file equipamento_func.c
 * @brief Ficheiro que contém todas as funções relativas ao menu principal equipamentos.
 * 
 */
#include "equipamento_func.h"
#include "entrada.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Inicializa a lista de equipamentos com uma capacidade inicial.
 * 
 * @param lista Ponteiro para a lista de equipamentos.
 * @param capacidadeInicial Capacidade inicial da lista.
 */

void inicializarEquipamentos(ListaEquipamento *lista, int capacidadeInicial) {
    lista->equipamentos = (Equipamento*)malloc(capacidadeInicial * sizeof(Equipamento));
    if (lista->equipamentos == NULL) {
        printf("Falha na alocação de memória.\n");
        exit(1);
    }

    lista->capacidade = capacidadeInicial;
    lista->totalEquipamento = 3;  // Inicializa com 4 equipamentos

    lista->equipamentos[0] = (Equipamento){1,"Câmera","AudioVisual", DISPONIVEL, 0, 0, 0};
    lista->equipamentos[1] = (Equipamento){2,"Mesa","Mobiliario", DISPONIVEL, 0, 0, 0};
    lista->equipamentos[2] = (Equipamento){3,"Focos","Iluminaçao", DISPONIVEL, 0 , 0, 0};
   
}
/**
 * @brief Cria um novo equipamento ou adiciona unidades a um equipamento existente.
 * 
 * @param lista Ponteiro para a lista de equipamentos.
 * @param id_sequencial Ponteiro para o ID sequencial dos equipamentos.
 */

void criarEquipamento(ListaEquipamento *lista, int *id_sequencial) {
    int i, opçao_equipamento, quantidade, id, encontrado;
    char nomeNovo[NOME_TIPO];
    char tipoNovo[NOME_TIPO];
    *id_sequencial = lista->totalEquipamento;
    do {
        printf("\nEquipamentos disponíveis:\n");
        for (i = 0; i < lista->totalEquipamento; i++) {
            printf("%d. %s (%s)\n", lista->equipamentos[i].id, lista->equipamentos[i].nome, lista->equipamentos[i].tipo);
        }
        printf("[0] MENU ANTERIOR\n");
        printf("[1] Adicionar Produtos Existentes\n");
        printf("[2] Criar Novo Equipamento\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opçao_equipamento);

        switch (opçao_equipamento) {
            case 0:
                return;
            case 1:
                printf("Digite o ID do equipamento ao qual deseja adicionar unidades: ");
                scanf("%d", &id);
                encontrado = 0;
                for (i = 0; i < lista->totalEquipamento; i++) {
                    if (lista->equipamentos[i].id == id) {
                        printf("Quantos %s pretende adicionar? ", lista->equipamentos[i].nome);
                        scanf("%d", &quantidade);
                        lista->equipamentos[i].quantidade += quantidade;
                        printf("Adicionou %d unidades de %s. Total: %d.\n", quantidade, lista->equipamentos[i].nome, lista->equipamentos[i].quantidade);
                        encontrado = 1;
                        break;
                    }
                }
                if (!encontrado) {
                    printf("Equipamento não encontrado.\n");
                }
                break;
            case 2:
                printf("Nome do novo equipamento: ");
                scanf("%s", nomeNovo);
                printf("Tipo do novo equipamento: ");
                scanf("%s", tipoNovo);

                if (lista->totalEquipamento == lista->capacidade) {
                    lista->capacidade *= 2;
                    Equipamento *temp = realloc(lista->equipamentos, lista->capacidade * sizeof(Equipamento));
                    if (temp == NULL) {
                        printf("Erro ao realocar memória.\n");
                        return;
                    }
                    lista->equipamentos = temp;
                }

                lista->equipamentos[lista->totalEquipamento] = (Equipamento){
                    .id = ++(*id_sequencial),
                    .nome = "",
                    .tipo = "",
                    .estado = DISPONIVEL,
                    .quantidade = 0
                };
                strcpy(lista->equipamentos[lista->totalEquipamento].nome, nomeNovo);
                strcpy(lista->equipamentos[lista->totalEquipamento].tipo, tipoNovo);
                printf("Quantos %s pretende adicionar? ", nomeNovo);
                scanf("%d", &quantidade);
                lista->equipamentos[lista->totalEquipamento].quantidade = quantidade;
                lista->totalEquipamento++;
                printf("Novo equipamento %s (%s) criado com ID %d e %d unidades.\n", nomeNovo, tipoNovo, *id_sequencial, quantidade);
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while (opçao_equipamento != 0);
}

/**
 * @brief Elimina um equipamento da lista de equipamentos.
 * 
 * @param listaEquipamentos Ponteiro para a lista de equipamentos.
 * @param id_eliminar ID do equipamento a ser eliminado.
 */
void eliminarEquipamento(ListaEquipamento *listaEquipamentos, int id_eliminar) {
    int i;
    int indice = -1;

    // Encontrar o índice do equipamento pelo ID
    for (i = 0; i < listaEquipamentos->totalEquipamento; i++) {
        if (listaEquipamentos->equipamentos[i].id == id_eliminar) {
            indice = i;
            break;
        }
    }

    if (indice != -1) {
        // Deslocar os elementos para a esquerda
        for (i = indice; i < listaEquipamentos->totalEquipamento - 1; i++) {
            listaEquipamentos->equipamentos[i] = listaEquipamentos->equipamentos[i + 1];
        }

        listaEquipamentos->totalEquipamento--;

        // Opcional: Realoque a memória para liberar espaço não utilizado
        Equipamento *temp = realloc(listaEquipamentos->equipamentos, listaEquipamentos->totalEquipamento * sizeof(Equipamento));
        if (temp != NULL || listaEquipamentos->totalEquipamento == 0) {
            listaEquipamentos->equipamentos = temp;
        } else {
            printf("Erro ao realocar memória.\n");
            exit(1);
        }

        printf("O equipamento de ID: [%d] foi apagado do sistema.\n", id_eliminar);
    } else {
        printf("ID introduzido não é válido. Tente novamente.\n");
    }
}
/**
 * @brief Edita as informações de um equipamento existente.
 * 
 * @param lista Ponteiro para a lista de equipamentos.
 * @param id_equipamento ID do equipamento a ser editado.
 */
void editarEquipamento(ListaEquipamento *lista, int id_equipamento) {
    int encontrado = 0;
    char novo_nome[NOME_TIPO];
    char novo_tipo[NOME_TIPO];
    int nova_quantidade;

    for (int i = 0; i < lista->totalEquipamento; i++) {
        if (lista->equipamentos[i].id == id_equipamento) {
            encontrado = 1;

            printf("Novo nome para o equipamento '%s' (ID: %d): ", lista->equipamentos[i].nome, id_equipamento);
            scanf("%s", novo_nome);
            printf("Novo tipo para o equipamento '%s' (ID: %d): ", lista->equipamentos[i].nome, id_equipamento);
            scanf("%s", novo_tipo);
            printf("Nova quantidade para o equipamento '%s' (ID: %d): ", lista->equipamentos[i].nome, id_equipamento);
            scanf("%d", &nova_quantidade);

            strcpy(lista->equipamentos[i].nome, novo_nome);
            strcpy(lista->equipamentos[i].tipo, novo_tipo);
            lista->equipamentos[i].quantidade = nova_quantidade;

            printf("Equipamento atualizado com sucesso!\n");
            printf("ID: %d\tNome: %s\tTipo: %s\tQuantidade: %d\n", lista->equipamentos[i].id, lista->equipamentos[i].nome, lista->equipamentos[i].tipo, lista->equipamentos[i].quantidade);
            break;
        }
    }

    if (!encontrado) {
        printf("Equipamento com ID %d não encontrado.\n", id_equipamento);
    }
}
/**
 * @brief Mostra todos os equipamentos na lista de equipamentos.
 * 
 * @param lista Ponteiro para a lista de equipamentos.
 */
void mostrarEquipamentos(ListaEquipamento *lista) {
    int i;
    for (i = 0; i < lista->totalEquipamento; i++) {
        printf("ID: %d\tNome: %s\tTipo: %s\tQuantidade disponivel: %d\n", 
               lista->equipamentos[i].id, 
               lista->equipamentos[i].nome,
               lista->equipamentos[i].tipo,    
               lista->equipamentos[i].quantidade
                                                               );
    }
}
/**
 * @brief Mostra todos os equipamentos indisponíveis na lista de equipamentos.
 * 
 * @param listaEquipamento Ponteiro para a lista de equipamentos.
 */
void equipamentos_indisponivel(ListaEquipamento *listaEquipamento) {
    int i;
    for (i = 0; i < listaEquipamento->totalEquipamento; i++) {
        if (listaEquipamento->equipamentos[i].quantidadeManutençao > 0 || listaEquipamento->equipamentos[i].quantidadeReserva > 0) {
            printf("ID: %d\tNome: %s\tQuantidade em Manutenção: %d\nReservados: %d\n", 
                   listaEquipamento->equipamentos[i].id, 
                   listaEquipamento->equipamentos[i].nome, 
                   listaEquipamento->equipamentos[i].quantidadeManutençao,
                   listaEquipamento->equipamentos[i].quantidadeReserva);
           
        }
    }
}
 /**
 * @brief Carrega os dados dos equipamentos a partir de um ficheiro.
 * 
 * @param lista Ponteiro para a lista de equipamentos.
 * @param nomeFicheiro Nome do ficheiro a partir do qual os dados serão carregados.
 * @param id_sequencial_equipamentos Ponteiro para o ID sequencial dos equipamentos.
 */
void carregarEquipamentos(ListaEquipamento *lista, const char *nomeFicheiro,int *id_sequencial_equipamentos) {
    FILE *file = fopen(nomeFicheiro, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o ficheiro %s para leitura.\n", nomeFicheiro);
        return;
    }

    fread(&(lista->totalEquipamento), sizeof(int), 1, file);

    lista->capacidade = lista->totalEquipamento;
    lista->equipamentos = malloc(lista->capacidade * sizeof(Equipamento));
    if (lista->equipamentos == NULL) {
        printf("Erro ao alocar memória para os equipamentos.\n");
        fclose(file);
        return;
    }

    fread(lista->equipamentos, sizeof(Equipamento), lista->totalEquipamento, file);

    fclose(file);
    printf("Dados carregados com sucesso de %s.\n", nomeFicheiro);
}
/**
 * @brief Guarda os dados dos equipamentos em um ficheiro.
 * 
 * @param lista Ponteiro para a lista de equipamentos.
 * @param nomeFicheiro Nome do ficheiro onde os dados serão guardados.
 * @param id_sequencial_equipamentos ID sequencial dos equipamentos.
 */
void guardarEquipamentos(ListaEquipamento *lista, const char *nomeFicheiro,int id_sequencial_equipamentos) {
    FILE *file = fopen(nomeFicheiro, "wb");
    if (file == NULL) {
        printf("Erro ao abrir o ficheiro %s para escrita.\n", nomeFicheiro);
        return;
    }

    // Escrever o número total de equipamentos
    fwrite(&(lista->totalEquipamento), sizeof(int), 1, file);

    // Escrever os dados dos equipamentos
    fwrite(lista->equipamentos, sizeof(Equipamento), lista->totalEquipamento, file);

    fclose(file);
    printf("Dados guardados com sucesso em %s.\n", nomeFicheiro);
}
/**
 * @brief Verifica se um equipamento existe na lista de equipamentos.
 * 
 * @param listaEquipamentos Ponteiro para a lista de equipamentos.
 * @param idEquipamento ID do equipamento a ser verificado.
 * @param tipoEquipamento Tipo do equipamento a ser verificado.
 * @return int Retorna 1 se o equipamento existir, caso contrário, retorna 0.
 */
int equipamentoExiste(ListaEquipamento *listaEquipamentos, int idEquipamento,char *tipoEquipamento) {
    for (int i = 0; i < listaEquipamentos->totalEquipamento; i++) {
        if (listaEquipamentos->equipamentos[i].id == idEquipamento &&
            strcmp(listaEquipamentos->equipamentos[i].tipo, tipoEquipamento) == 0) {
            return 1;
        }
    }
    return 0;
}
/**
 * @brief Coloca um equipamento em manutenção.
 * 
 * @param listaEquipamentos Ponteiro para a lista de equipamentos.
 * @param idEquipamento ID do equipamento a ser colocado em manutenção.
 */
void ColocarManutençao(ListaEquipamento *listaEquipamentos, int idEquipamento) {
    Equipamento *equipamento = NULL;
    int quantidade, i;

    for (i = 0; i < listaEquipamentos->totalEquipamento; i++) {
        if (listaEquipamentos->equipamentos[i].id == idEquipamento) {
            equipamento = &listaEquipamentos->equipamentos[i];
            break;
        }
    }

    if (equipamento == NULL) {
        printf("Equipamento não encontrado.\n");
        return;
    }

    printf("Quantos equipamentos deseja colocar em MANUTENÇÃO? ");
    scanf("%d", &quantidade);
    if (quantidade > equipamento->quantidade) {
        printf("Quantidade inválida. Não há equipamentos suficientes disponíveis.\n");
        return;
    }

    equipamento->quantidade -= quantidade;
    equipamento->quantidadeManutençao += quantidade;
    printf("%d equipamentos alterados para MANUTENÇÃO com sucesso.\n", quantidade);

    // Atualizar o estado do equipamento para manutenção
    equipamento->estado = MANUTENÇAO;
}
/**
 * @brief Retira um equipamento da manutenção.
 * 
 * @param listaEquipamentos Ponteiro para a lista de equipamentos.
 * @param idEquipamento ID do equipamento a ser retirado da manutenção.
 */
void RetirarManutençao(ListaEquipamento *listaEquipamentos, int idEquipamento) {
    Equipamento *equipamento = NULL; 
    int i,quantidade;
  
    
    for (i = 0; i < listaEquipamentos->totalEquipamento; i++) {
        if (listaEquipamentos->equipamentos[i].id == idEquipamento) {
            equipamento = &listaEquipamentos->equipamentos[i];
            break;
        }
    }

    if (equipamento == NULL) {
        printf("Equipamento não encontrado.\n");
        return;
    }

    // Perguntar a quantidade de equipamentos a retirar da manutenção
    printf("Quantos equipamentos deseja retirar da MANUTENÇÃO? ");
    scanf("%d", &quantidade);

    if (quantidade > equipamento->quantidadeManutençao) {
        printf("Quantidade inválida. Não há itens suficientes em manutenção.\n");
        return;
    }

    equipamento->quantidadeManutençao -= quantidade;
    equipamento->quantidade += quantidade;
    printf("%d equipamentos retirados da manutenção com sucesso. Total agora disponível: %d\n", quantidade, equipamento->quantidade);

    if (equipamento->quantidadeManutençao == 0) {
        equipamento->estado = DISPONIVEL;
    }
}
/**
 * @brief Coloca um equipamento em reserva.
 * 
 * @param listaEquipamentos Ponteiro para a lista de equipamentos.
 * @param idEquipamento ID do equipamento a ser reservado.
 * @param tipoEquipamento Tipo do equipamento a ser reservado.
 */
void reservados(ListaEquipamento *listaEquipamentos, int idEquipamento,char *tipoEquipamento) {
    Equipamento *equipamento = NULL; // Manter o ponteiro NULL para se não for encontrado no LOOP nao crie erros.
    int quantidade, i;
    int quantidadeValida=0;
    // Encontrar o equipamento pelo ID e tipo
    for (i = 0; i < listaEquipamentos->totalEquipamento; i++) {
        if (listaEquipamentos->equipamentos[i].id == idEquipamento &&
            strcmp(listaEquipamentos->equipamentos[i].tipo, tipoEquipamento) == 0) {
            equipamento = &listaEquipamentos->equipamentos[i];
            break;
        }
    }

    if (equipamento == NULL) {
        printf("Equipamento não encontrado.\n");
        return;
    }

    // Perguntar a quantidade de equipamentos a colocar em reserva
    while(!quantidadeValida){
    printf("Quantos equipamentos deseja reservar?: ");
    scanf("%d", &quantidade);
    if (quantidade > equipamento->quantidade) {
        printf("Quantidade inválida. Não há equipamentos suficientes disponíveis.\n");
    }else{
        quantidadeValida=1;
    }
}
    equipamento->quantidade -= quantidade;
    equipamento->quantidadeReserva += quantidade;

    if (equipamento->quantidade == 0) {
        equipamento->estado = RESERVADO;
    }
}
/**
 * @brief Gera um relatório detalhado de todos os equipamentos e suas utilizações.
 * 
 * @param listaEquipamentos Ponteiro para a lista de equipamentos.
 * @param listaReservas Ponteiro para a lista de reservas.
 */

void relatorio_equipamentos(ListaEquipamento *listaEquipamentos, ListaReservas *listaReservas) {
    int i, j;
    int totalReservas = 0;
    int maxUtilizacao = 0;
    int minUtilizaçao = MAX_UTILIZAÇAO; // Inicializa com o valor máximo possível
    int totalEquipamentoindisp = 0;
    int totalEquipamentos = 0;
    Equipamento equipamentoMaisUtilizado;
    Equipamento equipamentoMenosUtilizado;

    for (i = 0; i < listaEquipamentos->totalEquipamento; i++) {
        totalEquipamentos += listaEquipamentos->equipamentos[i].quantidade;
        totalEquipamentos += listaEquipamentos->equipamentos[i].quantidadeManutençao;
        totalEquipamentos += listaEquipamentos->equipamentos[i].quantidadeReserva;
    }
    printf("=========================================\n");
    printf("           RELATÓRIO DE EQUIPAMENTOS    \n");
    printf("=========================================\n");
    printf("Total de Equipamentos Registados: %d\n", totalEquipamentos);
    printf("-----------------------------------------\n");

    for (i = 0; i < listaEquipamentos->totalEquipamento; i++) {
        Equipamento equipamento = listaEquipamentos->equipamentos[i];
        int utilizaçaoEquipamento = 0;
        int quantidadeUtilizada = equipamento.quantidadeReserva + equipamento.quantidadeManutençao;

        printf("Equipamento ID: %d\n", equipamento.id);
        printf("Nome: %s\n", equipamento.nome);
        printf("Tipo: %s\n", equipamento.tipo);

        // Utilização do equipamento nas reservas
        for (j = 0; j < listaReservas->totalReservas; j++) {
            if (listaReservas->reservas[j].idEquipamento == equipamento.id) {
                utilizaçaoEquipamento++;
                totalReservas++;
                printf("  - Reserva ID: %d, Cliente ID: %d, Espaço ID: %d, Data: %d/%d/%d, Duração: %d horas\n",
                       listaReservas->reservas[j].id,
                       listaReservas->reservas[j].idCliente,
                       listaReservas->reservas[j].idEspaço,
                       listaReservas->reservas[j].dataReserva.dia,
                       listaReservas->reservas[j].dataReserva.mes,
                       listaReservas->reservas[j].dataReserva.ano,
                       listaReservas->reservas[j].duraçao);
            }
        }

        printf("Total de Reservas: %d\n", utilizaçaoEquipamento);
        printf("Quantidade Utilizada: %d\n", quantidadeUtilizada);
        printf("-----------------------------------------\n");

        // Qual é o mais utilizado
        if (quantidadeUtilizada > maxUtilizacao) {
            maxUtilizacao = quantidadeUtilizada;
            equipamentoMaisUtilizado = equipamento;
        }

        // Qual é o menos utilizado
        if (quantidadeUtilizada < minUtilizaçao) {
            minUtilizaçao = quantidadeUtilizada;
            equipamentoMenosUtilizado = equipamento;
        }

        // Contabiliza a quantidade de equipamentos indisponíveis (reservados ou em manutenção)
        totalEquipamentoindisp += quantidadeUtilizada;
    }
  
    // Equipamento mais utilizado
    if (maxUtilizacao > 0) {
        printf("=========================================\n");
        printf("Equipamento mais utilizado:\n");
        printf("Equipamento ID: %d\n", equipamentoMaisUtilizado.id);
        printf("Nome: %s\n", equipamentoMaisUtilizado.nome);
        printf("Total de Utilizações: %d\n", maxUtilizacao);
    } else {
        printf("Nenhum equipamento foi utilizado.\n");
    }

    // Equipamento menos utilizado
    if (minUtilizaçao >= 0) {
        printf("=========================================\n");
        printf("Equipamento menos utilizado:\n");
        printf("Equipamento ID: %d\n", equipamentoMenosUtilizado.id);
        printf("Nome: %s\n", equipamentoMenosUtilizado.nome);
        printf("Total de Utilizações: %d\n", minUtilizaçao);
    }

    // Calcula e exibe a taxa de utilização
    if (totalEquipamentos > 0) {
        float taxaUtilizaçao = (float)totalEquipamentoindisp / totalEquipamentos * 100;
        printf("=========================================\n");
        printf("Taxa de Utilização dos Equipamentos: %.2f%%\n", taxaUtilizaçao);
    } else {
        printf("Nenhuma reserva foi realizada.\n");
    }

    printf("=========================================\n");
}