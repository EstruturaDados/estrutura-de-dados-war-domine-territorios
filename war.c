#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da estrutura Territorio
struct Territorio {
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército que controla o território
    int tropas;      // Número de tropas no território
};

// ---------- Função de Cadastro ----------
// Cadastra os territórios informados pelo usuário
void cadastrarTerritorios(struct Territorio* mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);

        printf("Digite o nome do território: ");
        scanf(" %[^\n]", mapa[i].nome);

        printf("Digite a cor do exército: ");
        scanf(" %[^\n]", mapa[i].cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// ---------- Função de Exibição ----------
// Exibe os territórios cadastrados
void exibirTerritorios(struct Territorio* mapa, int n) {
    printf("\n=== Territórios Cadastrados ===\n");
    for (int i = 0; i < n; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do Exército: %s\n", mapa[i].cor);
        printf("Quantidade de Tropas: %d\n", mapa[i].tropas);
    }
}

// ---------- Função de Ataque ----------
// Simula um ataque entre dois territórios
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\n[ERRO] Não é possível atacar um território da mesma cor!\n");
        return;
    }

    if (atacante->tropas <= 1) {
        printf("\n[ERRO] O atacante precisa ter mais de 1 tropa para atacar!\n");
        return;
    }

    // Simulação de rolagem de dados (1 a 6)
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n>>> Ataque iniciado entre %s (Atacante) e %s (Defensor)\n",
           atacante->nome, defensor->nome);
    printf("Dado do Atacante: %d | Dado do Defensor: %d\n", dadoAtacante, dadoDefensor);

    // Resultado da batalha
    if (dadoAtacante > dadoDefensor) {
        printf("Resultado: O Atacante venceu!\n");

        // Defensor muda de dono (cor e tropas)
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;  // metade das tropas do atacante
        atacante->tropas -= defensor->tropas;     // as tropas são divididas
    } else {
        printf("Resultado: O Defensor resistiu!\n");
        atacante->tropas -= 1;  // atacante perde 1 tropa
    }
}

// ---------- Função de Liberação ----------
// Libera a memória alocada dinamicamente
void liberarMemoria(struct Territorio* mapa) {
    free(mapa);
}

int main() {
    srand(time(NULL)); // Garante aleatoriedade nos dados

    int n;
    printf("Digite o número de territórios a serem cadastrados: ");
    scanf("%d", &n);

    // Alocação dinâmica do vetor de territórios
    struct Territorio* mapa = (struct Territorio*) calloc(n, sizeof(struct Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    // Cadastro e exibição inicial
    cadastrarTerritorios(mapa, n);
    exibirTerritorios(mapa, n);

    // Menu de ataques
    int opcao;
    do {
        printf("\n--- Menu de Ações ---\n");
        printf("1 - Realizar ataque\n");
        printf("2 - Exibir territórios\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int idAtacante, idDefensor;

            // Seleção do atacante
            printf("\nEscolha o número do território atacante (1 a %d): ", n);
            scanf("%d", &idAtacante);

            // Seleção do defensor
            printf("Escolha o número do território defensor (1 a %d): ", n);
            scanf("%d", &idDefensor);

            if (idAtacante >= 1 && idAtacante <= n &&
                idDefensor >= 1 && idDefensor <= n &&
                idAtacante != idDefensor) {
                atacar(&mapa[idAtacante - 1], &mapa[idDefensor - 1]);
            } else {
                printf("\n[ERRO] Escolha inválida!\n");
            }
        } else if (opcao == 2) {
            exibirTerritorios(mapa, n);
        }
    } while (opcao != 0);

    liberarMemoria(mapa); // Liberação de memória antes de encerrar
    printf("\nPrograma finalizado!\n");

    return 0;
}
