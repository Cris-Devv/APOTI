#ifndef AGENTES_H
#define AGENTES_H

#define STR 50
#define MAX_AGENTES 50

typedef struct
{
    int id;
    char nome[STR];
    char cpf[STR];
    char matricula[STR];
    char email[STR];
    char senha[STR];
} Agente;

extern Agente agentes[MAX_AGENTES];
extern int total_agentes;
extern int proximo_agente_id;

void cadastrar_agente();
void listar_agentes();
Agente *encontrar_agente_por_cpf(const char *cpf);
Agente *encontrar_agente_por_matricula(const char *matricula);
void salvar_agentes();
void carregar_agentes();

#endif