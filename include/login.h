#ifndef LOGIN_H
#define LOGIN_H

typedef enum {
    TIPO_MOTORISTA,
    TIPO_AGENTE,
    TIPO_ADMIN
} TipoUsuario;

typedef struct {
    TipoUsuario tipo;
    int id_usuario;
} UsuarioLogado;

extern UsuarioLogado usuario_atual;

void menu_login();
void menu_motorista();
void menu_agente();
int fazer_login(const char *cpf_matricula, const char *senha, TipoUsuario tipo);
void cadastrar_usuario_inicial();

#endif