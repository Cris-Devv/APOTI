#include <stdio.h>
#include "../include/extras.h"
#include "../include/multas.h"
#include "../include/motoristas.h"
#include "../include/veiculos.h"

/* ===== MENU PRINCIPAL ===== */
void menu_principal() {
    int opcao;
    do {
        printf("========================================\n");
        printf("   SISTEMA DE CADASTRO DE MULTAS v1.1  \n");
        printf("========================================\n\n");
        printf("  1. Cadastrar novo motorista\n");
        printf("  2. Cadastrar nova multa\n");
        printf("  3. Cadastrar novo veiculo para motorista\n");
        printf("  4. Listar motoristas\n");
        printf("  5. Listar veiculos\n");
        printf("  6. Listar todas as multas\n");
        printf("  7. Buscar por placa\n");
        printf("  8. Buscar por CPF\n");
        printf("  9. Excluir multa\n");
        printf(" 10. Alterar status de pagamento\n");
        printf("  0. Sair\n\n");
        printf("Opcao: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar_motorista();
                break;
            case 2:
                cadastrar_multa();
                break;
            case 3:
                cadastrar_veiculo_existente();
                break;
            case 4:
                listar_motoristas();
                break;
            case 5:
                listar_veiculos();
                break;
            case 6:
                listar_multas();
                break;
            case 7:
                buscar_por_placa();
                break;
            case 8:
                buscar_por_cpf();
                break;
            case 9:
                excluir_multa();
                break;
            case 10:
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