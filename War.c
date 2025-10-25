#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char cor[15];
    int tropas;
} Territorio;

typedef struct {
    char descricao[100];
    int objetivoTropas; 
} Missao;

// Função p/ cadastrar territórios
void cadastrarTerritorios(Territorio *territorios, int n) {
    for (int i = 0; i < n; i++) {
        printf("\n=== Cadastro do Território %d ===\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", territorios[i].nome);
        printf("Cor: ");
        scanf(" %[^\n]", territorios[i].cor);
        printf("Número de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }
}

// Função p/  exibir territórios
void listarTerritorios(Territorio *territorios, int n) {
    printf("\n=== Territórios Cadastrados ===\n");
    for (int i = 0; i < n; i++) {
        printf("%d - %s (%s) | Tropas: %d\n", i + 1,
               territorios[i].nome, territorios[i].cor, territorios[i].tropas);
    }
}

// Função para simular ataque entre territórios
void atacar(Territorio *atacante, Territorio *defensor) {
    printf("\n%s está atacando %s!\n", atacante->nome, defensor->nome);

    if (atacante->tropas < 2) {
        printf("Ataque impossível! Tropas insuficientes.\n");
        return;
    }

    // Simulação com números aleatórios
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        defensor->tropas--;
        printf("Vitória do atacante! Tropas do defensor: %d\n", defensor->tropas);
    } else {
        atacante->tropas--;
        printf("Defensor resistiu! Tropas do atacante: %d\n", atacante->tropas);
    }
}

// Função p/ ver se a missão foi concluída
int verificarMissao(Territorio *territorios, int n, Missao *missao) {
    int total = 0;
    for (int i = 0; i < n; i++)
        total += territorios[i].tropas;

    if (total >= missao->objetivoTropas) {
        printf("\n🎉 Missão cumprida: %s\n", missao->descricao);
        return 1;
    }
    return 0;
}

int main() {
    srand(time(NULL));

    int n;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &n);

    Territorio *territorios = (Territorio *)malloc(n * sizeof(Territorio));
    if (!territorios) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    cadastrarTerritorios(territorios, n);
    listarTerritorios(territorios, n);

    // Criar missão
    Missao *missao = (Missao *)malloc(sizeof(Missao));
    strcpy(missao->descricao, "Conquistar 20 tropas no total!");
    missao->objetivoTropas = 20;

    int opcao, a, d;
    do {
        printf("\n=== MENU ===\n");
        printf("1 - Listar territórios\n");
        printf("2 - Atacar\n");
        printf("3 - Verificar missão\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                listarTerritorios(territorios, n);
                break;
            case 2:
                listarTerritorios(territorios, n);
                printf("Escolha atacante (1 a %d): ", n);
                scanf("%d", &a);
                printf("Escolha defensor (1 a %d): ", n);
                scanf("%d", &d);
                if (a != d && a > 0 && d > 0 && a <= n && d <= n)
                    atacar(&territorios[a - 1], &territorios[d - 1]);
                else
                    printf("Opção inválida.\n");
                break;
            case 3:
                if (verificarMissao(territorios, n, missao))
                    opcao = 0; // encerra o jogo se vencer
                break;
            case 0:
                printf("Encerrando jogo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    free(territorios);
    free(missao);
    return 0;
}
