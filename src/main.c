#include <locale.h>

#include "../include/multas.h"
#include "../include/motoristas.h"
#include "../include/veiculos.h"
#include "../include/agentes.h"
#include "../include/login.h"

/* ===== FUNÇÃO PRINCIPAL ===== */
int main() {

    setlocale(LC_ALL, "Portuguese");

    carregar_arquivo();
    carregar_motoristas();
    carregar_veiculos();
    carregar_agentes();
    // cadastrar_usuario_inicial();
    menu_login();

    return 0;
}