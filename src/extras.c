#include "../include/extras.h"
#include "multas.c"

/* ===== MENU PRINCIPAL ===== */
void menu_principal() {
    int opcao;
    do {
        printf("========================================\n");
        printf("   SISTEMA DE CADASTRO DE MULTAS v1.0  \n");
        printf("========================================\n\n");
        printf("  1. Cadastrar nova multa\n");
        printf("  2. Listar todas as multas\n");
        printf("  3. Buscar por placa\n");
        printf("  4. Buscar por CPF\n");
        printf("  5. Excluir multa\n");
        printf("  6. Alterar status de pagamento\n");
        printf("  0. Sair\n\n");
        printf("Opcao: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar_multa();
                break;
            case 2:
                listar_multas();
                break;
            case 3:
                buscar_por_placa();
                break;
            case 4:
                buscar_por_cpf();
                break;
            case 5:
                excluir_multa();
                break;
            case 6:
                alterar_status();
                break;
            case 0:
                printf("\nSaindo... Ate logo!\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
                pausar();
        }
    } while (opcao != 0);
}

void pausar() {
    printf("\nPressione ENTER para continuar...");
    getchar();
}