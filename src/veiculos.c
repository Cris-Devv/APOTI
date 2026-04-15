#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/extras.h"
#include "../include/veiculos.h"
#include "../include/motoristas.h"
#include "../include/multas.h"

#define ARQUIVO_VEICULOS "data/veiculos.dat"

Veiculo veiculos[MAX_VEICULOS];
int total_veiculos = 0;
int proximo_veiculo_id = 1;

static void flush_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

Veiculo *encontrar_veiculo_por_placa(const char *placa) {
    for (int i = 0; i < total_veiculos; i++) {
        if (strcmp(veiculos[i].placa, placa) == 0)
            return &veiculos[i];
    }
    return NULL;
}

void salvar_veiculos() {
    FILE *fp = fopen(ARQUIVO_VEICULOS, "wb");
    if (!fp) {
        printf("ERRO: Nao foi possivel salvar o arquivo de veiculos!\n");
        return;
    }
    fwrite(&total_veiculos, sizeof(int), 1, fp);
    fwrite(&proximo_veiculo_id, sizeof(int), 1, fp);
    fwrite(veiculos, sizeof(Veiculo), total_veiculos, fp);
    fclose(fp);
}

void carregar_veiculos() {
    FILE *fp = fopen(ARQUIVO_VEICULOS, "rb");
    if (!fp) {
        printf("Nenhum arquivo de veiculos encontrado. Iniciando com banco vazio.\n");
        return;
    }
    fread(&total_veiculos, sizeof(int), 1, fp);
    fread(&proximo_veiculo_id, sizeof(int), 1, fp);
    fread(veiculos, sizeof(Veiculo), total_veiculos, fp);
    fclose(fp);
    printf("Dados de veiculos carregados: %d encontrado(s).\n", total_veiculos);
}

void listar_veiculos_do_motorista(int motorista_id) {
    printf("=== VEICULOS DO MOTORISTA (ID %d) ===\n\n", motorista_id);
    int encontrados = 0;
    for (int i = 0; i < total_veiculos; i++) {
        if (veiculos[i].motorista_id == motorista_id) {
            printf("ID: %d\n", veiculos[i].id);
            printf("Placa : %s\n", veiculos[i].placa);
            printf("Modelo: %s\n", veiculos[i].modelo);
            printf("Cor   : %s\n", veiculos[i].cor);
            printf("-----------------------------\n");
            encontrados++;
        }
    }
    if (encontrados == 0)
        printf("Nenhum veiculo cadastrado para este motorista.\n");
}

void listar_veiculos() {
    printf("=== LISTAR VEICULOS ===\n\n");

    if (total_veiculos == 0) {
        printf("Nenhum veiculo cadastrado.\n");
        pausar();
        return;
    }

    for (int i = 0; i < total_veiculos; i++) {
        Veiculo v = veiculos[i];
        Motorista *motorista = encontrar_motorista_por_id(v.motorista_id);
        printf("ID: %d\n", v.id);
        printf("Placa : %s\n", v.placa);
        printf("Modelo: %s\n", v.modelo);
        printf("Cor   : %s\n", v.cor);
        if (motorista != NULL)
            printf("Motorista: %s (CPF: %s)\n", motorista->nome, motorista->cpf);
        printf("-----------------------------\n");
    }

    printf("Total: %d veiculo(s)\n", total_veiculos);
    pausar();
}

void cadastrar_veiculo_para_motorista(int motorista_id) {
    if (total_veiculos >= MAX_VEICULOS) {
        printf("ERRO: Limite maximo de %d veiculos atingido!\n", MAX_VEICULOS);
        pausar();
        return;
    }

    Motorista *motorista = encontrar_motorista_por_id(motorista_id);
    if (motorista == NULL) {
        printf("Motorista nao encontrado.\n");
        pausar();
        return;
    }

    Veiculo novo;
    novo.id = proximo_veiculo_id;
    novo.motorista_id = motorista_id;

    flush_stdin();
    do {
        printf("Placa do veiculo: ");
        fgets(novo.placa, STR, stdin);
        novo.placa[strcspn(novo.placa, "\n")] = 0;

        for (int i = 0; novo.placa[i]; i++)
            novo.placa[i] = toupper(novo.placa[i]);

        if (!validar_placa(novo.placa)) {
            printf("Placa invalida! Use o formato ABC1234.\n");
            continue;
        }

        if (encontrar_veiculo_por_placa(novo.placa) != NULL) {
            printf("Esta placa ja esta cadastrada.\n");
        }
    } while (!validar_placa(novo.placa) || encontrar_veiculo_por_placa(novo.placa) != NULL);

    printf("Modelo do veiculo: ");
    fgets(novo.modelo, STR, stdin);
    novo.modelo[strcspn(novo.modelo, "\n")] = 0;

    printf("Cor do veiculo: ");
    fgets(novo.cor, STR, stdin);
    novo.cor[strcspn(novo.cor, "\n")] = 0;

    veiculos[total_veiculos] = novo;
    total_veiculos++;
    proximo_veiculo_id++;
    salvar_veiculos();

    printf("\nVeiculo cadastrado com sucesso! (ID: %d)\n", novo.id);
    pausar();
}
