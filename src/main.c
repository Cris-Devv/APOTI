#include <locale.h>
#include "../include/extras.h"
#include "../include/multas.h"
#include "../include/motoristas.h"
#include "../include/veiculos.h"

/* ===== FUNÇÃO PRINCIPAL ===== */
int main() {

    setlocale(LC_ALL, "Portuguese");

    carregar_arquivo();
    carregar_motoristas();
    carregar_veiculos();
    pausar();
    menu_principal();

    return 0;
}