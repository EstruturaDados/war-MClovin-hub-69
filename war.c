#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ===================================================
// Estrutura que representa um território no jogo
// ===================================================
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ===================================================
// Função para limpar o buffer de entrada
// ===================================================
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ===================================================
// Função para cadastrar os territórios
// ===================================================
void cadastrarTerritorios(Territorio *mapa, int n) {
    printf("\n=== Cadastro de Territórios ===\n\n");

    for (int i = 0; i < n; i++) {
        printf("Território %d:\n", i + 1);

        printf("Nome: ");
        scanf(" %[^\n]", mapa[i].nome);
        limparBuffer();

        printf("Cor do exército: ");
        scanf(" %[^\n]", mapa[i].cor);
        limparBuffer();

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        limparBuffer();

        printf("------------------------------\n");
    }
    printf("\nCadastro concluído com sucesso!\n");
}

// ===================================================
// Função para exibir todos os territórios
// ===================================================
void exibirTerritorios(Territorio *mapa, int n) {
    if (mapa == NULL || n == 0) {
        printf("\nNenhum território cadastrado!\n");
        return;
    }

    printf("\n=== Territórios no mapa ===\n\n");
    for (int i = 0; i < n; i++) {
        printf("ID: %d\n", i);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do exército: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
        printf("------------------------------\n");
    }
}

// ===================================================
// Função que simula um ataque entre dois territórios
// ===================================================
void atacar(Territorio *atacante, Territorio *defensor) {
    printf("\n=== Iniciando ataque ===\n");
    printf("%s (%s) está atacando %s (%s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    // Rolagem de dados aleatória (1–6)
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    // Resultado do combate
    if (dadoAtacante > dadoDefensor) {
        printf("Resultado: O atacante venceu!\n");

        // O atacante conquista o território
        strcpy(defensor->cor, atacante->cor);

        // Metade das tropas do atacante se move
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas = atacante->tropas / 2;

        printf("O território %s agora pertence a %s.\n", defensor->nome, defensor->cor);
    } else {
        printf("Resultado: O defensor resistiu ao ataque!\n");
        atacante->tropas -= 1;
        if (atacante->tropas < 0) atacante->tropas = 0;
    }
}

// ===================================================
// Função para liberar a memória alocada
// ===================================================
void liberarMemoria(Territorio *mapa) {
    if (mapa != NULL) {
        free(mapa);
        printf("\nMemória liberada com sucesso!\n");
    }
}

// ===================================================
// Função principal com menu interativo
// ===================================================
int main() {
    srand(time(NULL)); // garante aleatoriedade nos dados

    Territorio *mapa = NULL;
    int n = 0;
    int opcao;

    do {
        printf("\n========== MENU PRINCIPAL ==========\n");
        printf("1 - Cadastrar territórios\n");
        printf("2 - Exibir territórios\n");
        printf("3 - Simular ataque\n");
        printf("4 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                // Se já existir memória alocada, libera antes
                liberarMemoria(mapa);

                printf("Quantos territórios deseja cadastrar? ");
                scanf("%d", &n);
                limparBuffer();

                mapa = (Territorio *)calloc(n, sizeof(Territorio));
                if (mapa == NULL) {
                    printf("Erro: falha ao alocar memória!\n");
                    return 1;
                }

                cadastrarTerritorios(mapa, n);
                break;

            case 2:
                exibirTerritorios(mapa, n);
                break;

            case 3:
                if (mapa == NULL || n < 2) {
                    printf("\nCadastre pelo menos 2 territórios primeiro!\n");
                    break;
                }

                exibirTerritorios(mapa, n);

                int idAtacante, idDefensor;
                printf("Escolha o ID do território atacante: ");
                scanf("%d", &idAtacante);
                limparBuffer();

                printf("Escolha o ID do território defensor: ");
                scanf("%d", &idDefensor);
                limparBuffer();

                if (idAtacante < 0 || idAtacante >= n || idDefensor < 0 || idDefensor >= n) {
                    printf("Erro: IDs inválidos!\n");
                } else if (strcmp(mapa[idAtacante].cor, mapa[idDefensor].cor) == 0) {
                    printf("Erro: um território não pode atacar outro da mesma cor!\n");
                } else {
                    atacar(&mapa[idAtacante], &mapa[idDefensor]);
                }

                break;

            case 4:
                printf("\nSaindo do sistema...\n");
                liberarMemoria(mapa);
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }

    } while (opcao != 4);

    return 0;
}