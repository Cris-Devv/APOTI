#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "../include/extras.h"
#include "../include/multas.h"
#include "../include/motoristas.h"
#include "../include/veiculos.h"

#define ARQUIVO "data/multas.dat"

Multa multas[MAX_MULTAS];
int total = 0;
int proximo_id = 1;

static void flush_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Cadastro de multas
void cadastrar_multa() {

    printf("=== CADASTRAR NOVA MULTA ===\n\n");

    if (total >= MAX_MULTAS)
    {
        printf("ERRO: Limite maximo de %d multas atingido!\n", MAX_MULTAS);
        pausar();
        return;
    }

    Multa nova;
    nova.id = proximo_id;

    flush_stdin();
    do {
        printf("Insira a placa do seu veiculo: ");
        fgets(nova.placa, STR, stdin);
        nova.placa[strcspn(nova.placa, "\n")] = 0;

        for (int i = 0; nova.placa[i]; i++)
            nova.placa[i] = toupper(nova.placa[i]);

        if (!validar_placa(nova.placa)) {
            printf("Placa invalida! Use o formato ABC1234.\n");
        }
    } while (!validar_placa(nova.placa));

    Veiculo *veiculo = encontrar_veiculo_por_placa(nova.placa);
    if (veiculo != NULL)
    {
        Motorista *motorista = encontrar_motorista_por_id(veiculo->motorista_id);
        if (motorista != NULL)
        {
            strcpy(nova.nome, motorista->nome);
            strcpy(nova.cpf, motorista->cpf);
            strcpy(nova.cnh, motorista->cnh);
            printf("Dados do motorista carregados a partir da placa cadastrada.\n");
            printf("Nome: %s\nCPF: %s\nCNH: %s\n\n", nova.nome, nova.cpf, nova.cnh);
        }
    }
    else
    {
        printf("Nome do infrator : ");
        fgets(nova.nome, STR, stdin);
        nova.nome[strcspn(nova.nome, "\n")] = 0;

        do
        {
            printf("CPF (somente numeros ou com . e -) : ");
            fgets(nova.cpf, STR, stdin);
            nova.cpf[strcspn(nova.cpf, "\n")] = 0;

            if (!validar_cpf(nova.cpf))
                printf("CPF invalido! Tente novamente.\n");

        } while (!validar_cpf(nova.cpf));

        printf("Numero da CNH   : ");
        fgets(nova.cnh, STR, stdin);
        nova.cnh[strcspn(nova.cnh, "\n")] = 0;
    }

    printf("Tipo de infracao:\n");
    printf("1. Avancar semaforo vermelho\n");
    printf("2. Estacionar em local proibido\n");
    printf("3. Excesso de velocidade leve\n");
    printf("4. Excesso de velocidade grave\n");
    printf("5. Dirigir sem cinto\n");
    printf("6. Uso de celular dirigindo\n");
    printf("7. Transportar criancas sem cadeirinha\n");
    printf("8. Dirigir sem habilitacao\n");
    printf("9. Veiculo com defeito\n");
    printf("Opcao: ");
    int opcao_infracao;
    scanf("%d", &opcao_infracao);

    nova.tipo_infracao = (TipoInfracao)opcao_infracao;
    Infracao infracao = obter_infracao(nova.tipo_infracao);
    nova.valor = infracao.valor;
    nova.pontos = infracao.pontos;

    printf("Data (DD/MM/AAAA): ");
    fgets(nova.data, STR, stdin);
    nova.data[strcspn(nova.data, "\n")] = 0;

    printf("Local da infracao: ");
    fgets(nova.local, STR, stdin);
    nova.local[strcspn(nova.local, "\n")] = 0;

    strcpy(nova.status, "Pendente");

    multas[total] = nova;
    total++;
    proximo_id++;

    salvar_arquivo();
    printf("\nMulta cadastrada com sucesso! (ID: %d)\n", nova.id);
    printf("Infracao: %s\n", infracao.descricao);
    printf("Valor: R$ %.2f\n", nova.valor);
    printf("Pontos: %d\n", nova.pontos);
    pausar();
}

/* ===== CONSULTA ===== */

// Listagem de todas as multas de um carro
void listar_multas() {

    printf("=== LISTA DE MULTAS ===\n\n");

    if (total == 0)
    {
        printf("Nenhuma multa cadastrada.\n");
        pausar();
        return;
    }

    int i;
    for (i = 0; i < total; i++)
    {
        exibir_multa(multas[i]);
        printf("\n");
    }

    printf("Total: %d multa(s)\n", total);
    pausar();
}

// Listagem por placa do carro
void buscar_por_placa() {

    printf("=== BUSCAR POR PLACA ===\n\n");

    char placa[8];
    printf("Digite a placa: ");
    scanf(" %s", placa);

    /* converte para maiusculo */
    int k;
    for (k = 0; placa[k]; k++)
        if (placa[k] >= 'a' && placa[k] <= 'z')
            placa[k] -= 32;

    int encontrado = 0, i;
    for (i = 0; i < total; i++)
    {
        if (strcmp(multas[i].placa, placa) == 0)
        {
            exibir_multa(multas[i]);
            printf("\n");
            encontrado = 1;
        }
    }

    if (!encontrado)
        printf("Nenhuma multa encontrada para a placa '%s'.\n", placa);

    pausar();
}

// Listagem por CPF do infrator
void buscar_por_cpf() {

    printf("=== BUSCAR POR CPF ===\n\n");

    char cpf[15];
    printf("Digite o CPF: ");
    scanf(" %s", cpf);

    int encontrado = 0, i;
    for (i = 0; i < total; i++)
    {
        if (strcmp(multas[i].cpf, cpf) == 0)
        {
            exibir_multa(multas[i]);
            printf("\n");
            encontrado = 1;
        }
    }

    if (!encontrado)
        printf("Nenhuma multa encontrada para o CPF '%s'.\n", cpf);

    pausar();
}

/* ===== ATUALIZAR STATUS ===== */

// Pagamento de multas
void alterar_status() {

    printf("=== ALTERAR STATUS ===\n\n");

    int id;
    printf("Digite o ID da multa: ");
    scanf(" %d", &id);

    int i, pos = -1;
    for (i = 0; i < total; i++)
    {
        if (multas[i].id == id)
        {
            pos = i;
            break;
        }
    }

    if (pos == -1)
    {
        printf("Multa com ID %d nao encontrada.\n", id);
        pausar();
        return;
    }

    exibir_multa(multas[pos]);
    printf("\nNovo status:\n");
    printf("  1 - Pendente\n");
    printf("  2 - Paga\n");
    printf("  3 - Recorrida\n");
    printf("Opcao: ");
    int op;
    scanf(" %d", &op);

    switch (op)
    {
    case 1:
        strcpy(multas[pos].status, "Pendente");
        break;
    case 2:
        strcpy(multas[pos].status, "Paga");
        break;
    case 3:
        strcpy(multas[pos].status, "Recorrida");
        break;
    default:
        printf("Opcao invalida.\n");
        pausar();
        return;
    }

    salvar_arquivo();
    printf("Status atualizado para '%s'.\n", multas[pos].status);
    pausar();
}

/* ===== EXCLUSAO ===== */

// Exclusão de multa
void excluir_multa() {

    printf("=== EXCLUIR MULTA ===\n\n");

    if (total == 0)
    {
        printf("Nenhuma multa cadastrada.\n");
        pausar();
        return;
    }

    int id;
    printf("Digite o ID da multa a excluir: ");
    scanf(" %d", &id);

    int i, pos = -1;
    for (i = 0; i < total; i++)
    {
        if (multas[i].id == id)
        {
            pos = i;
            break;
        }
    }

    if (pos == -1)
    {
        printf("Multa com ID %d nao encontrada.\n", id);
        pausar();
        return;
    }

    exibir_multa(multas[pos]);
    printf("Confirma exclusao? (s/n): ");
    char resp;
    scanf(" %c", &resp);

    if (resp == 's' || resp == 'S')
    {
        /* desloca os registros para preencher o buraco */
        for (i = pos; i < total - 1; i++)
            multas[i] = multas[i + 1];
        total--;
        salvar_arquivo();
        printf("Multa excluida com sucesso!\n");
    }
    else
    {
        printf("Exclusao cancelada.\n");
    }

    pausar();
}

/* ===== ARQUIVO ===== */

// Salva dados em arquivo
void salvar_arquivo() {
    FILE *fp = fopen(ARQUIVO, "wb");
    if (!fp)
    {
        printf("ERRO: Nao foi possivel salvar o arquivo!\n");
        return;
    }
    fwrite(&total, sizeof(int), 1, fp);
    fwrite(&proximo_id, sizeof(int), 1, fp);
    fwrite(multas, sizeof(Multa), total, fp);
    fclose(fp);
    printf("Dados salvos com sucesso!\n");
}

// Carrega dados de um arquivo
void carregar_arquivo() {
    FILE *fp = fopen(ARQUIVO, "rb");
    if (!fp)
    {
        printf("Nenhum arquivo encontrado. Iniciando com banco vazio.\n");
        return;
    }
    fread(&total, sizeof(int), 1, fp);
    fread(&proximo_id, sizeof(int), 1, fp);
    fread(multas, sizeof(Multa), total, fp);
    fclose(fp);
    printf("Dados carregados: %d multa(s) encontrada(s).\n", total);
}

// Função para exibir os detalhes de uma multa de forma formatada
void exibir_multa(Multa m) {
    Infracao inf = obter_infracao(m.tipo_infracao);
    printf("+-------------------------------------------------+\n");
    printf("| ID: %-5d                                       |\n", m.id);
    printf("+-------------------------------------------------+\n");
    printf("  Nome   : %s\n", m.nome);
    printf("  CPF    : %s\n", m.cpf);
    printf("  CNH    : %s\n", m.cnh);
    printf("  Placa  : %s\n", m.placa);
    printf("  Infracao: %s\n", inf.descricao);
    printf("  Data   : %s\n", m.data);
    printf("  Local  : %s\n", m.local);
    printf("  Valor  : R$ %.2f\n", m.valor);
    printf("  Pontos : %d\n", m.pontos);
    printf("  Status : %s\n", m.status);
    printf("+-------------------------------------------------+\n");
}

// Validação simples de CPF (apenas formato)
int validar_cpf(const char *cpf) {
    int i, digitos = 0;
    for (i = 0; cpf[i] != '\0'; i++)
    {
        if (cpf[i] >= '0' && cpf[i] <= '9')
            digitos++;
        else if (cpf[i] != '.' && cpf[i] != '-')
            return 0;
    }
    return (digitos == 11);
}

// Validação simples de placa (formato antigo: ABC1234 ou Mercosul: ABC1D23)
int validar_placa(const char *placa) {
    if (strlen(placa) != 7)
        return 0;
    int i;
    for (i = 0; i < 3; i++)
        if (placa[i] < 'A' || placa[i] > 'Z')
            return 0;
    if (placa[3] < '0' || placa[3] > '9')
        return 0;
    /* aceita digito ou letra na 5a posicao (Mercosul) */
    if (placa[5] < '0' || placa[5] > '9')
        return 0;
    if (placa[6] < '0' || placa[6] > '9')
        return 0;
    return 1;
}

Infracao obter_infracao(TipoInfracao tipo) {
    Infracao inf;
    inf.tipo = tipo;
    switch (tipo) {
        case INF_AVANCAR_SEMAFORO_VERMELHO:
            strcpy(inf.descricao, "Avancar semaforo vermelho");
            inf.valor = 293.47;
            inf.pontos = 7;
            break;
        case INF_ESTACIONAR_LOCAL_PROIBIDO:
            strcpy(inf.descricao, "Estacionar em local proibido");
            inf.valor = 195.23;
            inf.pontos = 4;
            break;
        case INF_EXCESSO_VELOCIDADE_LEVE:
            strcpy(inf.descricao, "Excesso de velocidade leve");
            inf.valor = 130.16;
            inf.pontos = 4;
            break;
        case INF_EXCESSO_VELOCIDADE_GRAVE:
            strcpy(inf.descricao, "Excesso de velocidade grave");
            inf.valor = 195.23;
            inf.pontos = 5;
            break;
        case INF_DIRIGIR_SEM_CINTO:
            strcpy(inf.descricao, "Dirigir sem cinto de seguranca");
            inf.valor = 130.16;
            inf.pontos = 5;
            break;
        case INF_USO_CELULAR_DIRIGINDO:
            strcpy(inf.descricao, "Uso de celular dirigindo");
            inf.valor = 293.47;
            inf.pontos = 7;
            break;
        case INF_TRANSPORTAR_CRIAANCAS_SEM_CADEIRINHA:
            strcpy(inf.descricao, "Transportar criancas sem cadeirinha");
            inf.valor = 293.47;
            inf.pontos = 7;
            break;
        case INF_DIRIGIR_SEM_HABILITACAO:
            strcpy(inf.descricao, "Dirigir sem habilitacao");
            inf.valor = 880.41;
            inf.pontos = 7;
            break;
        case INF_VEICULO_COM_DEFEITO:
            strcpy(inf.descricao, "Veiculo com defeito");
            inf.valor = 130.16;
            inf.pontos = 4;
            break;
        default:
            strcpy(inf.descricao, "Infracao desconhecida");
            inf.valor = 0.0;
            inf.pontos = 0;
    }
    return inf;
}