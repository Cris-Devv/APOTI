#ifndef MULTA_H

#define MULTA_H
#define STR 50
#define MAX_MULTAS 100


typedef struct
{
    int id;
    char  nome[STR];
    char  cpf[STR];
    char  cnh[STR];
    char  placa[STR];
    char  codigo[STR];
    char  descricao[200];
    char  data[STR]; /* formato: DD/MM/AAAA */
    char  local[STR];
    float valor;
    int   pontos;
    char  status[STR]; /* "Pendente", "Paga", "Recorrida" */
} Multa;

Multa multas[MAX_MULTAS];
int total = 0;
int proximo_id = 1;

// Protótipos das funções
void  cadastrar_multa();
void  listar_multas();
void  buscar_por_placa();
void  buscar_por_cpf();
void  excluir_multa();
void  alterar_status();
void  exibir_multa(Multa m);
void  salvar_arquivo();
void  carregar_arquivo();
int   validar_cpf(const char *cpf);
int   validar_placa(const char *placa);

#endif