#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ========================================================
//              STRUCT DO TERRITÓRIO
// ========================================================
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ========================================================
//              FUNÇÃO DE CADASTRO
// ========================================================
void cadastrarTerritorios(Territorio* mapa, int qtd) {
    printf("\n===== Cadastro de Territórios =====\n\n");

    for (int i = 0; i < qtd; i++) {
        printf("--- Território %d ---\n", i + 1);

        printf("Nome do território: ");
        scanf(" %[^\n]", mapa[i].nome);

        printf("Cor do exército: ");
        scanf(" %[^\n]", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        printf("\n");
    }
}

// ========================================================
//              FUNÇÃO DE EXIBIÇÃO
// ========================================================
void exibirTerritorios(Territorio* mapa, int qtd) {
    printf("\n===== Dados dos Territórios =====\n\n");
    for (int i = 0; i < qtd; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
        printf("-----------------------------\n");
    }
}

// ========================================================
//              FUNÇÃO DE ATAQUE
// ========================================================
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\n❌ Você não pode atacar um território da mesma cor!\n");
        return;
    }

    if (atacante->tropas <= 1) {
        printf("\n⚠️  O atacante precisa ter mais de 1 tropa para atacar!\n");
        return;
    }

    printf("\n🎲 Batalha: %s (atacante) vs %s (defensor)\n", atacante->nome, defensor->nome);

    int dadoAtk = rand() % 6 + 1;
    int dadoDef = rand() % 6 + 1;

    printf("Dado do atacante: %d\n", dadoAtk);
    printf("Dado do defensor: %d\n", dadoDef);

    if (dadoAtk > dadoDef) {
        printf("🔥 O atacante venceu a batalha!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas /= 2;
    } else {
        printf("💀 O defensor resistiu ao ataque!\n");
        atacante->tropas -= 1;
    }
}

// ========================================================
//              FUNÇÃO DE ATRIBUIÇÃO DE MISSÃO
// ========================================================
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

// ========================================================
//              FUNÇÃO DE EXIBIÇÃO DA MISSÃO
// ========================================================
void exibirMissao(char* missao) {
    printf("\n🎯 Sua missão é: %s\n", missao);
}

// ========================================================
//              FUNÇÃO DE VERIFICAÇÃO DA MISSÃO
// ========================================================
// Aqui simplificamos as condições — em um jogo real,
// cada missão teria sua lógica específica.
int verificarMissao(char* missao, Territorio* mapa, int qtd, char* corJogador) {
    // Exemplo de 3 tipos simples de missões:
    if (strcmp(missao, "Conquistar 3 territórios seguidos") == 0) {
        int cont = 0;
        for (int i = 0; i < qtd; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) cont++;
        }
        return cont >= 3;
    }
    else if (strcmp(missao, "Dominar todos os territórios") == 0) {
        for (int i = 0; i < qtd; i++) {
            if (strcmp(mapa[i].cor, corJogador) != 0) return 0;
        }
        return 1;
    }
    else if (strcmp(missao, "Eliminar todas as tropas da cor vermelha") == 0) {
        for (int i = 0; i < qtd; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0) return 0;
        }
        return 1;
    }

    // Outras missões podem ser adicionadas
    return 0;
}

// ========================================================
//              FUNÇÃO DE LIBERAÇÃO DE MEMÓRIA
// ========================================================
void liberarMemoria(Territorio* mapa, char* missao1, char* missao2) {
    free(mapa);
    free(missao1);
    free(missao2);
    printf("\n✅ Memória liberada com sucesso.\n");
}

// ========================================================
//              FUNÇÃO PRINCIPAL
// ========================================================
int main() {
    srand(time(NULL));

    int qtd;
    printf("Digite o número de territórios: ");
    scanf("%d", &qtd);

    // Alocação dinâmica do mapa
    Territorio* mapa = (Territorio*) calloc(qtd, sizeof(Territorio));
    if (!mapa) {
        printf("Erro ao alocar memória para territórios!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, qtd);
    exibirTerritorios(mapa, qtd);

    // ======== MISSÕES ========
    char* missoes[] = {
        "Conquistar 3 territórios seguidos",
        "Dominar todos os territórios",
        "Eliminar todas as tropas da cor vermelha",
        "Manter pelo menos 5 territórios ativos",
        "Ter mais de 20 tropas no total"
    };
    int totalMissoes = 5;

    // ======== ALOCAÇÃO DINÂMICA DAS MISSÕES ========
    char* missaoJogador1 = (char*) malloc(100 * sizeof(char));
    char* missaoJogador2 = (char*) malloc(100 * sizeof(char));

    atribuirMissao(missaoJogador1, missoes, totalMissoes);
    atribuirMissao(missaoJogador2, missoes, totalMissoes);

    printf("\n===== JOGADOR 1 =====");
    exibirMissao(missaoJogador1);

    printf("\n===== JOGADOR 2 =====");
    exibirMissao(missaoJogador2);

    // ======== LOOP DE TURNOS ========
    int turno = 1;
    while (1) {
        printf("\n===== TURNO %d =====\n", turno);
        exibirTerritorios(mapa, qtd);

        int atk, def;
        printf("\nEscolha o território atacante (1-%d): ", qtd);
        scanf("%d", &atk);
        printf("Escolha o território defensor (1-%d): ", qtd);
        scanf("%d", &def);

        if (atk < 1 || atk > qtd || def < 1 || def > qtd) {
            printf("❌ Índices inválidos!\n");
            continue;
        }

        atacar(&mapa[atk - 1], &mapa[def - 1]);

        // ======== VERIFICA MISSÕES ========
        if (verificarMissao(missaoJogador1, mapa, qtd, mapa[atk - 1].cor)) {
            printf("\n🏆 Jogador 1 cumpriu sua missão e venceu!\n");
            break;
        }

        if (verificarMissao(missaoJogador2, mapa, qtd, mapa[def - 1].cor)) {
            printf("\n🏆 Jogador 2 cumpriu sua missão e venceu!\n");
            break;
        }

        turno++;
    }

    liberarMemoria(mapa, missaoJogador1, missaoJogador2);
    return 0;
}
