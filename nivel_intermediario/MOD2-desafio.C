#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ==============================
// Estrutura do Território
// ==============================
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// ==============================
// Função para limpar buffer
// ==============================
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ==============================
// Função para cadastrar territórios
// ==============================
void cadastrarTerritorios(struct Territorio *mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\n-- Cadastro do território %d --\n", i + 1);

        printf("Nome do território: ");
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0;

        printf("Cor do território (exército): ");
        fgets(mapa[i].cor, 10, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = 0;

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        limparBufferEntrada();
    }
}

// ==============================
// Função para exibir territórios
// ==============================
void exibirTerritorios(struct Territorio *mapa, int n) {
    printf("\n--- Lista de Territórios ---\n");
    for (int i = 0; i < n; i++) {
        printf("%d - Nome: %s | Cor: %s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// ==============================
// Função de ataque
// ==============================
void atacar(struct Territorio *atacante, struct Territorio *defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Não é permitido atacar territórios da mesma cor!\n");
        return;
    }

    if (atacante->tropas <= 1) {
        printf("O território atacante precisa ter mais de 1 tropa para atacar!\n");
        return;
    }

    printf("\n%s (%s) está atacando %s (%s)\n",
           atacante->nome, atacante->cor,
           defensor->nome, defensor->cor);

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("O atacante venceu a batalha!\n");
        strcpy(defensor->cor, atacante->cor); // muda a cor
        defensor->tropas = atacante->tropas / 2; // metade das tropas do atacante
        atacante->tropas = atacante->tropas / 2; // atacante perde metade
    } else {
        printf("O defensor resistiu! O atacante perdeu 1 tropa.\n");
        atacante->tropas -= 1;
    }
}

// ==============================
// Função para liberar memória
// ==============================
void liberarMemoria(struct Territorio *mapa) {
    free(mapa);
}

// ==============================
// Função Principal
// ==============================
int main() {
    srand(time(NULL)); // garante aleatoriedade

    int n;
    printf("================================\n");
    printf("      WAR ESTRUTURADO\n");
    printf("================================\n");

    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &n);
    limparBufferEntrada();

    // Alocação dinâmica
    struct Territorio *mapa = (struct Territorio *) calloc(n, sizeof(struct Territorio));
    if (mapa == NULL) {
        printf("Erro na alocação de memória!\n");
        return 1;
    }

    // Cadastro
    cadastrarTerritorios(mapa, n);
    exibirTerritorios(mapa, n);

    // Simulação de ataque
    int opAtacante, opDefensor;
    char continuar = 's';
    while (continuar == 's') {
        printf("\nEscolha o território ATACANTE (1 a %d): ", n);
        scanf("%d", &opAtacante);
        printf("Escolha o território DEFENSOR (1 a %d): ", n);
        scanf("%d", &opDefensor);
        limparBufferEntrada();

        if (opAtacante >= 1 && opAtacante <= n && opDefensor >= 1 && opDefensor <= n) {
            atacar(&mapa[opAtacante - 1], &mapa[opDefensor - 1]);
        } else {
            printf("⚠️ Opção inválida!\n");
        }

        exibirTerritorios(mapa, n);

        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);
        limparBufferEntrada();
    }

    liberarMemoria(mapa);
    printf("\nMemória liberada. Encerrando o jogo...\n");
    return 0;
}
