#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/motoristas.h"
#include "../include/veiculos.h"
#include "../include/multas.h"

Motorista motoristas[MAX_MOTORISTAS];
int total_motoristas = 0;
int proximo_motorista_id = 1;

static void flush_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

Motorista *encontrar_motorista_por_cpf(const char *cpf) {
    for (int i = 0; i < total_motoristas; i++) {
        if (strcmp(motoristas[i].cpf, cpf) == 0)
            return &motoristas[i];
    }
    return NULL;
}

Motorista *encontrar_motorista_por_id(int id) {
    for (int i = 0; i < total_motoristas; i++) {
        if (motoristas[i].id == id)
            return &motoristas[i];
    }
    return NULL;
}

void salvar_motoristas() {
    FILE *fp = fopen("data/motoristas.dat", "wb");
    if (!fp) {
        printf("ERRO: Nao foi possivel salvar o arquivo de motoristas!\n");
        return;
    }
    fwrite(&total_motoristas, sizeof(int), 1, fp);
    fwrite(&proximo_motorista_id, sizeof(int), 1, fp);
    fwrite(motoristas, sizeof(Motorista), total_motoristas, fp);
    fclose(fp);
}

void carregar_motoristas() {
    FILE *fp = fopen("data/motoristas.dat", "rb");
    if (!fp) {
        printf("Nenhum arquivo de motoristas encontrado. Iniciando com banco vazio.\n");
        return;
    }
    fread(&total_motoristas, sizeof(int), 1, fp);
    fread(&proximo_motorista_id, sizeof(int), 1, fp);
    fread(motoristas, sizeof(Motorista), total_motoristas, fp);
    fclose(fp);
    printf("Dados de motoristas carregados: %d encontrado(s).\n", total_motoristas);
}

void cadastrar_motorista() {
    printf("=== CADASTRAR NOVO MOTORISTA ===\n\n");

    if (total_motoristas >= MAX_MOTORISTAS) {
        printf("ERRO: Limite maximo de %d motoristas atingido!\n", MAX_MOTORISTAS);
        pausar();
        return;
    }

    Motorista novo;
    novo.id = proximo_motorista_id;

    flush_stdin();
    printf("Nome: ");
    fgets(novo.nome, STR, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = 0;

    do {
        printf("CPF (somente numeros ou com . e -): ");
        fgets(novo.cpf, STR, stdin);
        novo.cpf[strcspn(novo.cpf, "\n")] = 0;

        if (!validar_cpf(novo.cpf))
            printf("CPF invalido! Tente novamente.\n");
    } while (!validar_cpf(novo.cpf));

    printf("Numero da CNH: ");
    fgets(novo.cnh, STR, stdin);
    novo.cnh[strcspn(novo.cnh, "\n")] = 0;

    printf("Email: ");
    fgets(novo.email, STR, stdin);
    novo.email[strcspn(novo.email, "\n")] = 0;

    char confirma[STR];
    do {
        printf("Senha: ");
        fgets(novo.senha, STR, stdin);
        novo.senha[strcspn(novo.senha, "\n")] = 0;

        printf("Confirme sua senha: ");
        fgets(confirma, STR, stdin);
        confirma[strcspn(confirma, "\n")] = 0;

        if (strcmp(novo.senha, confirma) != 0)
            printf("Senhas nao conferem! Tente novamente.\n");
    } while (strcmp(novo.senha, confirma) != 0);

    motoristas[total_motoristas] = novo;
    total_motoristas++;
    proximo_motorista_id++;
    salvar_motoristas();

    printf("\nMotorista cadastrado com sucesso! (ID: %d)\n", novo.id);

    char resposta[STR];
    do {
        printf("Deseja cadastrar um veiculo para este motorista agora? (s/n): ");
        fgets(resposta, STR, stdin);
        resposta[strcspn(resposta, "\n")] = 0;

        if (resposta[0] == 's' || resposta[0] == 'S') {
            cadastrar_veiculo_para_motorista(novo.id);
        }
    } while (resposta[0] == 's' || resposta[0] == 'S');

    pausar();
}

void cadastrar_veiculo_existente() {
    if (total_motoristas == 0) {
        printf("Nenhum motorista cadastrado.\n");
        pausar();
        return;
    }

    char cpf[STR];
    printf("Digite o CPF do motorista: ");
    scanf(" %49s", cpf);

    Motorista *motorista = encontrar_motorista_por_cpf(cpf);
    if (motorista == NULL) {
        printf("Motorista nao encontrado.\n");
        pausar();
        return;
    }

    cadastrar_veiculo_para_motorista(motorista->id);
}

void listar_motoristas() {
    printf("=== LISTAR MOTORISTAS ===\n\n");

    if (total_motoristas == 0) {
        printf("Nenhum motorista cadastrado.\n");
        pausar();
        return;
    }

    for (int i = 0; i < total_motoristas; i++) {
        Motorista m = motoristas[i];
        printf("ID: %d\n", m.id);
        printf("Nome : %s\n", m.nome);
        printf("CPF  : %s\n", m.cpf);
        printf("CNH  : %s\n", m.cnh);
        printf("Email: %s\n", m.email);
        printf("-----------------------------\n");
    }

    printf("Total: %d motorista(s)\n", total_motoristas);
    pausar();
}
