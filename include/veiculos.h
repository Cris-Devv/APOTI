#ifndef VEICULOS_H
#define VEICULOS_H

#define STR 50
#define MAX_VEICULOS 200

typedef struct
{
    int id;
    int motorista_id;
    char placa[STR];
    char modelo[STR];
    char cor[STR];
} Veiculo;

extern Veiculo veiculos[MAX_VEICULOS];
extern int total_veiculos;
extern int proximo_veiculo_id;

void cadastrar_veiculo_para_motorista(int motorista_id);
void listar_veiculos();
void listar_veiculos_do_motorista(int motorista_id);
Veiculo *encontrar_veiculo_por_placa(const char *placa);
void salvar_veiculos();
void carregar_veiculos();

#endif