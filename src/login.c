#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/login.h"
#include "../include/motoristas.h"
#include "../include/agentes.h"
#include "../include/multas.h"
#include "../include/veiculos.h"
#include "../include/extras.h"

UsuarioLogado usuario_atual = {TIPO_ADMIN, -1};

static void flush_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int fazer_login(const char *cpf_matricula, const char *senha, TipoUsuario tipo) {
    if (tipo == TIPO_MOTORISTA) {
        Motorista *motorista = encontrar_motorista_por_cpf(cpf_matricula);
        if (motorista != NULL && strcmp(motorista->senha, senha) == 0) {
            usuario_atual.tipo = TIPO_MOTORISTA;
            usuario_atual.id_usuario = motorista->id;
            return 1;
        }
    } else if (tipo == TIPO_AGENTE) {
        Agente *agente = encontrar_agente_por_matricula(cpf_matricula);
        if (agente != NULL && strcmp(agente->senha, senha) == 0) {
            usuario_atual.tipo = TIPO_AGENTE;
            usuario_atual.id_usuario = agente->id;
            return 1;
        }
    }
    return 0;
}

void cadastrar_usuario_inicial() {
    if (total_motoristas == 0 && total_agentes == 0) {
        printf("=== CADASTRO INICIAL ===\n");
        printf("Nenhum usuario cadastrado. Vamos criar o primeiro agente.\n\n");
        cadastrar_agente();
        printf("Agora cadastre o primeiro motorista.\n\n");
        cadastrar_motorista();
    }
}

void menu_login() {
    int opcao;
    do {
        printf("========================================\n");
        printf("   APOTI  \n");
        printf("========================================\n\n");
        printf("1. Login como Motorista\n");
        printf("2. Login como Agente\n");
        printf("3. Cadastrar novo Motorista\n");
        printf("4. Cadastrar novo Agente\n");
        printf("0. Sair\n\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                flush_stdin();
                char cpf[STR], senha[STR];
                printf("CPF: ");
                fgets(cpf, STR, stdin);
                cpf[strcspn(cpf, "\n")] = 0;
                printf("Senha: ");
                fgets(senha, STR, stdin);
                senha[strcspn(senha, "\n")] = 0;

                if (fazer_login(cpf, senha, TIPO_MOTORISTA)) {
                    printf("Login realizado com sucesso!\n");
                    pausar();
                    menu_motorista();
                } else {
                    printf("CPF ou senha incorretos!\n");
                    pausar();
                }
                break;
            }
            case 2: {
                flush_stdin();
                char matricula[STR], senha[STR];
                printf("Matricula: ");
                fgets(matricula, STR, stdin);
                matricula[strcspn(matricula, "\n")] = 0;
                printf("Senha: ");
                fgets(senha, STR, stdin);
                senha[strcspn(senha, "\n")] = 0;

                if (fazer_login(matricula, senha, TIPO_AGENTE)) {
                    printf("Login realizado com sucesso!\n");
                    pausar();
                    menu_agente();
                } else {
                    printf("Matricula ou senha incorretos!\n");
                    pausar();
                }
                break;
            }
            case 3:
                cadastrar_motorista();
                break;
            case 4:
                cadastrar_agente();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                pausar();
        }
    } while (opcao != 0);
}

void menu_motorista() {
    int opcao;
    do {
        printf("========================================\n");
        printf("         MENU MOTORISTA                 \n");
        printf("========================================\n\n");
        printf("1. Ver minhas multas\n");
        printf("2. Pagar multa\n");
        printf("0. Logout\n\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                printf("=== MINHAS MULTAS ===\n\n");
                int encontrou = 0;
                for (int i = 0; i < total; i++) {
                    // Verificar se a multa pertence ao motorista logado
                    int motorista_id = -1;
                    for (int j = 0; j < total_veiculos; j++) {
                        if (strcmp(multas[i].placa, veiculos[j].placa) == 0) {
                            motorista_id = veiculos[j].motorista_id;
                            break;
                        }
                    }
                    if (motorista_id == usuario_atual.id_usuario) {
                        exibir_multa(multas[i]);
                        printf("\n");
                        encontrou = 1;
                    }
                }
                if (!encontrou) {
                    printf("Nenhuma multa encontrada.\n");
                }
                pausar();
                break;
            }
            case 2: {
                printf("=== PAGAR MULTA ===\n\n");
                printf("Digite o ID da multa: ");
                int id;
                scanf("%d", &id);

                int pos = -1;
                for (int i = 0; i < total; i++) {
                    if (multas[i].id == id) {
                        // Verificar se a multa pertence ao motorista logado
                        int motorista_id = -1;
                        for (int j = 0; j < total_veiculos; j++) {
                            if (strcmp(multas[i].placa, veiculos[j].placa) == 0) {
                                motorista_id = veiculos[j].motorista_id;
                                break;
                            }
                        }
                        if (motorista_id == usuario_atual.id_usuario) {
                            pos = i;
                            break;
                        }
                    }
                }

                if (pos == -1) {
                    printf("Multa nao encontrada ou nao pertence a voce.\n");
                } else if (strcmp(multas[pos].status, "Paga") == 0) {
                    printf("Esta multa ja foi paga.\n");
                } else {
                    strcpy(multas[pos].status, "Paga");
                    salvar_arquivo();
                    printf("Multa paga com sucesso!\n");
                }
                pausar();
                break;
            }
            case 0:
                usuario_atual.tipo = TIPO_ADMIN;
                usuario_atual.id_usuario = -1;
                printf("Logout realizado.\n");
                pausar();
                break;
            default:
                printf("Opcao invalida!\n");
                pausar();
        }
    } while (opcao != 0 && usuario_atual.tipo == TIPO_MOTORISTA);
}

void menu_agente() {
    int opcao;
    do {
        printf("========================================\n");
        printf("          MENU AGENTE                   \n");
        printf("========================================\n\n");
        printf("1. Cadastrar multa\n");
        printf("2. Buscar multas por placa\n");
        printf("3. Buscar multas por CPF\n");
        printf("4. Atualizar multa\n");
        printf("5. Excluir multa\n");
        printf("0. Logout\n\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar_multa();
                break;
            case 2:
                buscar_por_placa();
                break;
            case 3:
                buscar_por_cpf();
                break;
            case 4: {
                printf("=== ATUALIZAR MULTA ===\n\n");
                printf("Digite o ID da multa: ");
                int id;
                scanf("%d", &id);

                int pos = -1;
                for (int i = 0; i < total; i++) {
                    if (multas[i].id == id) {
                        pos = i;
                        break;
                    }
                }

                if (pos == -1) {
                    printf("Multa nao encontrada.\n");
                } else {
                    exibir_multa(multas[pos]);
                    printf("\nDigite os novos dados:\n");

                    flush_stdin();
                    printf("Data (DD/MM/AAAA): ");
                    fgets(multas[pos].data, STR, stdin);
                    multas[pos].data[strcspn(multas[pos].data, "\n")] = 0;

                    printf("Local: ");
                    fgets(multas[pos].local, STR, stdin);
                    multas[pos].local[strcspn(multas[pos].local, "\n")] = 0;

                    printf("Tipo de infracao:\n");
                    printf("1. Avancar semaforo vermelho\n");
                    printf("2. Estacionar em local proibido\n");
                    printf("3. Excesso de velocidade leve\n");
                    printf("4. Excesso de velocidade grave\n");
                    printf("5. Dirigir sem cinto\n");
                    printf("6. Uso de celular dirigindo\n");
                    printf("7. Transportar criancas sem cadeirinha\n");
                    printf("8. Dirigir sem habilitacao\n");
                    printf("9. Veiculo com defeito\n");
                    printf("Opcao: ");
                    int opcao_infracao;
                    scanf("%d", &opcao_infracao);

                    multas[pos].tipo_infracao = (TipoInfracao)opcao_infracao;
                    Infracao infracao = obter_infracao(multas[pos].tipo_infracao);
                    multas[pos].valor = infracao.valor;
                    multas[pos].pontos = infracao.pontos;

                    salvar_arquivo();
                    printf("Multa atualizada com sucesso!\n");
                }
                pausar();
                break;
            }
            case 5:
                excluir_multa();
                break;
            case 0:
                usuario_atual.tipo = TIPO_ADMIN;
                usuario_atual.id_usuario = -1;
                printf("Logout realizado.\n");
                pausar();
                break;
            default:
                printf("Opcao invalida!\n");
                pausar();
        }
    } while (opcao != 0 && usuario_atual.tipo == TIPO_AGENTE);
}
