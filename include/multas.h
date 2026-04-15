#ifndef MULTA_H
#define MULTA_H

#define STR 50
#define MAX_MULTAS 100

typedef enum {
    INF_AVANCAR_SEMAFORO_VERMELHO = 1,
    INF_ESTACIONAR_LOCAL_PROIBIDO,
    INF_EXCESSO_VELOCIDADE_LEVE,
    INF_EXCESSO_VELOCIDADE_GRAVE,
    INF_DIRIGIR_SEM_CINTO,
    INF_USO_CELULAR_DIRIGINDO,
    INF_TRANSPORTAR_CRIAANCAS_SEM_CADEIRINHA,
    INF_DIRIGIR_SEM_HABILITACAO,
    INF_VEICULO_COM_DEFEITO
} TipoInfracao;

typedef struct {
    TipoInfracao tipo;
    char descricao[200];
    float valor;
    int pontos;
} Infracao;

typedef struct
{
    int id;
    char  nome[STR];
    char  cpf[STR];
    char  cnh[STR];
    char  placa[STR];
    TipoInfracao tipo_infracao;
    char  data[STR]; /* formato: DD/MM/AAAA */
    char  local[STR];
    float valor;
    int   pontos;
    char  status[STR]; /* "Pendente", "Paga", "Recorrida" */
} Multa;

extern Multa multas[MAX_MULTAS];
extern int total;
extern int proximo_id;

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
Infracao obter_infracao(TipoInfracao tipo);

#endif