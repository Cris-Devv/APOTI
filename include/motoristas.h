#ifndef MOTORISTAS_H
#define MOTORISTAS_H

#define STR 50
#define MAX_MOTORISTAS 100

typedef struct
{
    int id;
    char nome[STR];
    char cpf[STR];
    char cnh[STR];
    char email[STR];
    char senha[STR];
} Motorista;

extern Motorista motoristas[MAX_MOTORISTAS];
extern int total_motoristas;
extern int proximo_motorista_id;

void cadastrar_motorista();
void listar_motoristas();
Motorista *encontrar_motorista_por_cpf(const char *cpf);
Motorista *encontrar_motorista_por_id(int id);
void cadastrar_veiculo_existente();
void salvar_motoristas();
void carregar_motoristas();

#endif