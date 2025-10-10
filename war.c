// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_NOME 30
#define TAM_COR 10
#define TOTAL_MISSOES 5
#define MAX_JOGADORES 2

typedef struct {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
} Territorio;

// Funções
Territorio* alocarTerritorios(int quantidade);
void cadastrarTerritorios(Territorio* mapa, int quantidade);
void exibirTerritorios(Territorio* mapa, int quantidade);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa, char** missoes, int totalJogadores);
int selecionarTerritorio(Territorio* mapa, int quantidade, const char* msg);
int territoriosDaMesmaCor(Territorio* t1, Territorio* t2);
void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
int verificarMissao(char* missao, char* corJogador, Territorio* mapa, int tamanho);

int main() {
    srand(time(NULL)); // Garante aleatoriedade para rand()

    int totalTerritorios;
    printf("Digite a quantidade de territórios a cadastrar: ");
    scanf("%d", &totalTerritorios);
    getchar(); // Limpa o '\n' do buffer

    // Alocação dinâmica de memória
    Territorio* mapa = alocarTerritorios(totalTerritorios);

    // Cadastro dos territórios
    cadastrarTerritorios(mapa, totalTerritorios);

    // Define as cores dos dois jogadores (assume que foram usadas no cadastro)
    char* coresJogadores[MAX_JOGADORES] = { "vermelho", "azul" }; // Exemplo

    // Vetor de missões disponíveis
    char* missoesDisponiveis[TOTAL_MISSOES] = {
        "Conquistar 3 territórios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Conquistar ao menos 4 territórios",
        "Reduzir um território inimigo a 0 tropas",
        "Controlar pelo menos metade dos territórios"
    };

    // Missão de cada jogador (alocação dinâmica)
    char* missoesJogadores[MAX_JOGADORES];
    for (int i = 0; i < MAX_JOGADORES; i++) {
        missoesJogadores[i] = (char*)malloc(100 * sizeof(char));
        atribuirMissao(missoesJogadores[i], missoesDisponiveis, TOTAL_MISSOES);
        printf("\nJogador %d (%s), sua missão é: %s\n", i + 1, coresJogadores[i], missoesJogadores[i]);
    }

    // Loop de ataques
    char continuar;
    int jogadorAtual = 0;

    do {
        printf("\n=== Turno do Jogador %d (%s) ===\n", jogadorAtual + 1, coresJogadores[jogadorAtual]);

        int atacanteIdx, defensorIdx;
        do {
            atacanteIdx = selecionarTerritorio(mapa, totalTerritorios, "Escolha o território ATACANTE: ");
        } while (strcmp(mapa[atacanteIdx].cor, coresJogadores[jogadorAtual]) != 0);

        do {
            defensorIdx = selecionarTerritorio(mapa, totalTerritorios, "Escolha o território DEFENSOR: ");
            if (territoriosDaMesmaCor(&mapa[atacanteIdx], &mapa[defensorIdx])) {
                printf("Você não pode atacar um território da mesma cor!\n");
            }
        } while (territoriosDaMesmaCor(&mapa[atacanteIdx], &mapa[defensorIdx]));

        atacar(&mapa[atacanteIdx], &mapa[defensorIdx]);

        // Exibe mapa após o ataque
        exibirTerritorios(mapa, totalTerritorios);

        // Verifica se o jogador cumpriu sua missão
        if (verificarMissao(missoesJogadores[jogadorAtual], coresJogadores[jogadorAtual], mapa, totalTerritorios)) {
            printf("\n🏆 Jogador %d (%s) venceu ao completar sua missão: %s\n",
                   jogadorAtual + 1, coresJogadores[jogadorAtual], missoesJogadores[jogadorAtual]);
            break;
        }

        printf("\nDeseja continuar o jogo? (s/n): ");
        scanf(" %c", &continuar);
        getchar(); // limpa buffer

        jogadorAtual = (jogadorAtual + 1) % MAX_JOGADORES;

    } while (continuar == 's' || continuar == 'S');

    liberarMemoria(mapa, missoesJogadores, MAX_JOGADORES);
    return 0;
}

// === Funções ===

// Aloca dinamicamente os territórios
Territorio* alocarTerritorios(int quantidade) {
    Territorio* mapa = (Territorio*)calloc(quantidade, sizeof(Territorio));
    if (!mapa) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    return mapa;
}

// Cadastra os territórios
void cadastrarTerritorios(Territorio* mapa, int quantidade) {
    printf("\n=== Cadastro de Territórios ===\n");

    for (int i = 0; i < quantidade; i++) {
        printf("\nTerritório %d:\n", i + 1);

        printf("Nome: ");
        fgets(mapa[i].nome, TAM_NOME, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do exército: ");
        fgets(mapa[i].cor, TAM_COR, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // Limpa buffer
    }
}

// Exibe todos os territórios
void exibirTerritorios(Territorio* mapa, int quantidade) {
    printf("\n=== Estado Atual dos Territórios ===\n");
    for (int i = 0; i < quantidade; i++) {
        printf("[%d] Nome: %s | Cor: %s | Tropas: %d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Simula o ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    if (atacante->tropas <= 1) {
        printf("O atacante precisa de mais de 1 tropa para atacar.\n");
        return;
    }

    printf("\n-> %s (%s) ataca %s (%s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    int dadoA = (rand() % 6) + 1;
    int dadoD = (rand() % 6) + 1;

    printf("Dado atacante: %d | Dado defensor: %d\n", dadoA, dadoD);

    if (dadoA > dadoD) {
        printf("Resultado: Vitória do atacante!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas -= defensor->tropas;
    } else {
        printf("Resultado: Defesa bem-sucedida!\n");
        atacante->tropas -= 1;
    }
}

// Libera memória de territórios e missões
void liberarMemoria(Territorio* mapa, char** missoes, int totalJogadores) {
    free(mapa);
    for (int i = 0; i < totalJogadores; i++) {
        free(missoes[i]);
    }
    printf("\nMemória liberada com sucesso.\n");
}

// Seleciona um território válido
int selecionarTerritorio(Territorio* mapa, int quantidade, const char* msg) {
    int idx;
    do {
        exibirTerritorios(mapa, quantidade);
        printf("%s", msg);
        scanf("%d", &idx);
        getchar();
        if (idx < 0 || idx >= quantidade) {
            printf("Índice inválido!\n");
        }
    } while (idx < 0 || idx >= quantidade);
    return idx;
}

// Verifica se as cores dos territórios são iguais
int territoriosDaMesmaCor(Territorio* t1, Territorio* t2
