#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura para armazenar dados de um território
typedef struct {
    char nome[30];
    char cor[15];
    int tropas;
} Territorio;

// Função para exibir o estado atual do mapa
void exibirMapa(Territorio* mapa, int tamanho) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d. %s | Cor: %s | Tropas: %d\n", i+1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("===========================\n");
}

// Função para simular ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoAtq = (rand() % 6) + 1;
    int dadoDef = (rand() % 6) + 1;
    printf("\n%s ataca %s!\n", atacante->nome, defensor->nome);
    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAtq, dadoDef);
    if (dadoAtq >= dadoDef) {
        // Atacante vence ou empata
        defensor->tropas--;
        printf("O defensor perde 1 tropa!\n");
        if (defensor->tropas <= 0) {
            defensor->tropas = 1;
            strcpy(defensor->cor, atacante->cor);
            printf("Território conquistado pelo atacante!\n");
        }
    } else {
        printf("O ataque falhou. Nenhuma tropa perdida pelo defensor.\n");
    }
}

int main() {
    srand((unsigned int)time(NULL));
    int tamanho = 5;
    Territorio* mapa = (Territorio*)calloc(tamanho, sizeof(Territorio));
    if (!mapa) {
        printf("Erro ao alocar memória para o mapa.\n");
        return 1;
    }
    printf("Cadastro dos Territórios:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("\nTerritório %d:\n", i+1);
        printf("Nome: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';
        printf("Cor do Exército: ");
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';
        printf("Número de Tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar();
    }
    exibirMapa(mapa, tamanho);
    char continuar = 's';
    while (continuar == 's' || continuar == 'S') {
        int atq, def;
        printf("\nEscolha o território atacante (1 a 5): ");
        scanf("%d", &atq);
        printf("Escolha o território defensor (1 a 5): ");
        scanf("%d", &def);
        getchar();
        if (atq < 1 || atq > tamanho || def < 1 || def > tamanho || atq == def) {
            printf("Escolha inválida.\n");
        } else {
            atacar(&mapa[atq-1], &mapa[def-1]);
            exibirMapa(mapa, tamanho);
        }
        printf("Deseja realizar outro ataque? (s/n): ");
        scanf("%c", &continuar);
        getchar();
    }
    free(mapa);
    return 0;
}
