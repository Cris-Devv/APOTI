#include "extras.c"

/* ===== FUNÇÃO PRINCIPAL ===== */
int main() {

    setlocale(LC_ALL, "Portuguese");

    carregar_arquivo();
    pausar();
    menu_principal();

    return 0;
}