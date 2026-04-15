#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../include/agentes.h"
#include "../include/multas.h"

Agente agentes[MAX_AGENTES];
int total_agentes = 0;
int proximo_agente_id = 1;

// static void flush_stdin(void)
// {
//     int c;
//     while ((c = getchar()) != '\n' && c != EOF)
//         ;
// }

Agente *encontrar_agente_por_cpf(const char *cpf)
{
    for (int i = 0; i < total_agentes; i++)
    {
        if (strcmp(agentes[i].cpf, cpf) == 0)
            return &agentes[i];
    }
    return NULL;
}

Agente *encontrar_agente_por_matricula(const char *matricula)
{
    for (int i = 0; i < total_agentes; i++)
    {
        if (strcmp(agentes[i].matricula, matricula) == 0)
            return &agentes[i];
    }
    return NULL;
}

void salvar_agentes()
{
    FILE *fp = fopen("data/agentes.dat", "wb");
    if (!fp)
    {
        printf("ERRO: Nao foi possivel salvar o arquivo de agentes!\n");
        return;
    }
    fwrite(&total_agentes, sizeof(int), 1, fp);
    fwrite(&proximo_agente_id, sizeof(int), 1, fp);
    fwrite(agentes, sizeof(Agente), total_agentes, fp);
    fclose(fp);
}

void carregar_agentes()
{
    FILE *fp = fopen("data/agentes.dat", "rb");
    if (!fp)
    {
        printf("Nenhum arquivo de agentes encontrado. Iniciando com banco vazio.\n");
        return;
    }
    fread(&total_agentes, sizeof(int), 1, fp);
    fread(&proximo_agente_id, sizeof(int), 1, fp);
    fread(agentes, sizeof(Agente), total_agentes, fp);
    fclose(fp);
    printf("Dados de agentes carregados: %d encontrado(s).\n", total_agentes);
}

void cadastrar_agente()
{
    printf("=== CADASTRAR NOVO AGENTE ===\n\n");

    if (total_agentes >= MAX_AGENTES)
    {
        printf("ERRO: Limite maximo de %d agentes atingido!\n", MAX_AGENTES);
        printf("\nPressione ENTER para continuar...");
        getchar();
        return;
    }

    Agente novo;
    novo.id = proximo_agente_id;

    // flush_stdin();
    printf("Nome: ");
    fgets(novo.nome, STR, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = 0;

    do
    {
        printf("CPF (somente numeros ou com . e -): ");
        fgets(novo.cpf, STR, stdin);
        novo.cpf[strcspn(novo.cpf, "\n")] = 0;

        if (!validar_cpf(novo.cpf))
            printf("CPF invalido! Tente novamente.\n");
    } while (!validar_cpf(novo.cpf));

    printf("Matricula: ");
    fgets(novo.matricula, STR, stdin);
    novo.matricula[strcspn(novo.matricula, "\n")] = 0;

    printf("Email: ");
    fgets(novo.email, STR, stdin);
    novo.email[strcspn(novo.email, "\n")] = 0;

    char confirma[STR];
    do
    {
        printf("Senha: ");
        fgets(novo.senha, STR, stdin);
        novo.senha[strcspn(novo.senha, "\n")] = 0;

        printf("Confirme sua senha: ");
        fgets(confirma, STR, stdin);
        confirma[strcspn(confirma, "\n")] = 0;

        if (strcmp(novo.senha, confirma) != 0)
            printf("Senhas nao conferem! Tente novamente.\n");
    } while (strcmp(novo.senha, confirma) != 0);

    agentes[total_agentes] = novo;
    total_agentes++;
    proximo_agente_id++;
    salvar_agentes();

    printf("\nAgente cadastrado com sucesso! (ID: %d)\n", novo.id);
    printf("\nPressione ENTER para continuar...");
    getchar();
}

void listar_agentes()
{
    printf("=== LISTAR AGENTES ===\n\n");

    if (total_agentes == 0)
    {
        printf("Nenhum agente cadastrado.\n");
        printf("\nPressione ENTER para continuar...");
        getchar();
        return;
    }

    for (int i = 0; i < total_agentes; i++)
    {
        Agente a = agentes[i];
        printf("ID: %d\n", a.id);
        printf("Nome : %s\n", a.nome);
        printf("CPF  : %s\n", a.cpf);
        printf("Matricula: %s\n", a.matricula);
        printf("Email: %s\n", a.email);
        printf("-----------------------------\n");
    }

    printf("Total: %d agente(s)\n", total_agentes);
    printf("\nPressione ENTER para continuar...");
    getchar();
}