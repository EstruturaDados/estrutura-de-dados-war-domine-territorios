#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TERRITORIOS 5
#define MAX_NOME 50
#define MAX_COR 30

typedef struct {
    char nome[MAX_NOME];
    char corExercito[MAX_COR];
    int tropas;
} Territorio;

typedef enum {
    DESTRUIR_VERDE,
    CONQUISTAR_TRES
} Missao;

void inicializarTerritorios(Territorio *mapa) {
    const char *nomes[MAX_TERRITORIOS] = {"Brasil", "Argentina", "Chile", "Peru", "Colombia"};
    const char *cores[MAX_TERRITORIOS] = {"Verde", "Azul", "Vermelho", "Amarelo", "Preto"};
    const int tropasIniciais[MAX_TERRITORIOS] = {5, 5, 5, 5, 5};

    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        strcpy(mapa[i].nome, nomes[i]);
        strcpy(mapa[i].corExercito, cores[i]);
        mapa[i].tropas = tropasIniciais[i];
    }
}

void exibirMapa(const Territorio *mapa) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("  Nome: %s\n", mapa[i].nome);
        printf("  Cor do Exercito: %s\n", mapa[i].corExercito);
        printf("  Tropas: %d\n", mapa[i].tropas);
        printf("-----------------------------\n");
    }
}

void batalha(Territorio *mapa, int atacante, int defensor) {
    if (atacante == defensor) {
        printf("Um territorio nao pode atacar a si mesmo!\n");
        return;
    }
    if (mapa[atacante].tropas <= 0) {
        printf("%s nao possui tropas para atacar!\n", mapa[atacante].nome);
        return;
    }
    if (mapa[defensor].tropas <= 0) {
        printf("%s ja foi conquistado!\n", mapa[defensor].nome);
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n=== Batalha ===\n");
    printf("%s (Atacante) rolou: %d\n", mapa[atacante].nome, dadoAtacante);
    printf("%s (Defensor) rolou: %d\n", mapa[defensor].nome, dadoDefensor);

    if (dadoAtacante >= dadoDefensor) {
        mapa[defensor].tropas--;
        printf("Resultado: O atacante venceu!\n");
        if (mapa[defensor].tropas <= 0) {
            printf("O territorio %s foi conquistado por %s!\n",
                   mapa[defensor].nome, mapa[atacante].corExercito);
            strcpy(mapa[defensor].corExercito, mapa[atacante].corExercito);
            mapa[defensor].tropas = 1;
        }
    } else {
        printf("Resultado: O defensor resistiu!\n");
    }
}

int verificarMissao(const Territorio *mapa, Missao missao, const char *corJogador) {
    if (missao == DESTRUIR_VERDE) {
        for (int i = 0; i < MAX_TERRITORIOS; i++) {
            if (strcmp(mapa[i].corExercito, "Verde") == 0 && mapa[i].tropas > 0) {
                return 0; // ainda existe exercito verde
            }
        }
        return 1;
    } else if (missao == CONQUISTAR_TRES) {
        int count = 0;
        for (int i = 0; i < MAX_TERRITORIOS; i++) {
            if (strcmp(mapa[i].corExercito, corJogador) == 0) {
                count++;
            }
        }
        return (count >= 3);
    }
    return 0;
}

void mostrarMissao(Missao missao) {
    printf("\n=== Sua Missao ===\n");
    if (missao == DESTRUIR_VERDE) {
        printf("-> Destruir o exercito Verde\n");
    } else if (missao == CONQUISTAR_TRES) {
        printf("-> Conquistar 3 territorios\n");
    }
}

int main() {
    srand(time(NULL));

    Territorio *mapa = (Territorio *) calloc(MAX_TERRITORIOS, sizeof(Territorio));
    if (!mapa) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    inicializarTerritorios(mapa);

    Missao missao = rand() % 2;
    const char *corJogador = "Azul";

    mostrarMissao(missao);
    exibirMapa(mapa);

    int opcao;
    do {
        printf("\n=== Menu Principal ===\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missao\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            int atacante, defensor;
            printf("Escolha o territorio atacante (1 a %d): ", MAX_TERRITORIOS);
            scanf("%d", &atacante);
            getchar();
            printf("Escolha o territorio defensor (1 a %d): ", MAX_TERRITORIOS);
            scanf("%d", &defensor);
            getchar();

            batalha(mapa, atacante - 1, defensor - 1);
            exibirMapa(mapa);
        } else if (opcao == 2) {
            if (verificarMissao(mapa, missao, corJogador)) {
                printf("\n🎉 Missao cumprida! Voce venceu!\n");
                break;
            } else {
                printf("\nMissao ainda nao cumprida.\n");
            }
        }
    } while (opcao != 0);

    free(mapa);
    return 0;
}