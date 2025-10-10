// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Constantes Globais ---
#define QTD_TERRITORIOS 5
#define TAM_NOME 30
#define TAM_COR 10

// --- Estrutura de Dados ---
// struct para Território
typedef struct {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
} Territorio;

// struct para Jogador
typedef struct {
    char cor[TAM_COR]; 
    char* missao; 
} Jogador;

// --- Vetor de missões estratégicas ---
const char* missoes[] = {
    "Conquistar 3 territórios seguidos.",
    "Eliminar todas as tropas da cor vermelha.",
    "Conquistar 5 territórios em uma única rodada.",
    "Ter 10 tropas em um unico territorio.",
    "Conquistar todos os territórios do mapa."
};
const int TOTAL_MISSOES = 5;

// --- Protótipos das Funções ---
void cadastrarTerritorios(Territorio* mapa, int n);
void exibirTerritorios(const Territorio* mapa, int n);
void atacar(Territorio* atacante, Territorio* defensor);
void atribuirMissao(char* destino, const char* missoes[], int totalMissoes);
int verificarMissao(const char* missao, Territorio* mapa, int tamanho, const char* corJogador);
void liberarMemoria(Territorio* mapa, Jogador* jogador);
void exibirMenuPrincipal(void);
void exibirMissao(const Jogador* jogador);

// --- Função Principal (main) ---
int main() {
    srand(time(NULL));

    // 1. Configuração Inicial (Setup):
    int n;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &n);

    // Alocação dinâmica do mapa de territórios
    Territorio* mapa = (Territorio*) calloc(n, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro de alocação de memória para o mapa!\n");
        return 1;
    }

    // Alocação dinâmica da struct do jogador
    Jogador* jogador = (Jogador*) malloc(sizeof(Jogador));
    if (jogador == NULL) {
        printf("Erro de alocação de memória para o jogador!\n");
        free(mapa);
        return 1;
    }
    
    // Alocação dinâmica da string da missão
    jogador->missao = (char*) malloc(100 * sizeof(char));
    if (jogador->missao == NULL) {
        printf("Erro de alocação de memória para a missão!\n");
        free(mapa);
        free(jogador);
        return 1;
    }

    // Cadastro inicial dos territórios
    cadastrarTerritorios(mapa, n);
    
    // Define a cor do jogador para a verificação da missão
    printf("\nQual a cor do seu exército? ");
    scanf(" %9s", jogador->cor);

    // Atribuir a missão e xibir missão
    atribuirMissao(jogador->missao, missoes, TOTAL_MISSOES);
    exibirMissao(jogador);
    
    // 2. Laço Principal do Jogo (Game Loop):
    int opcao;
    int jogoEmAndamento = 1;
    while (jogoEmAndamento) {
        exibirMenuPrincipal();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                exibirTerritorios(mapa, n);
                int a, d;
                printf("\nEscolha o território atacante (índice): ");
                scanf("%d", &a);
                printf("Escolha o território defensor (índice): ");
                scanf("%d", &d);

                if (a >= 0 && a < n && d >= 0 && d < n) {
                    atacar(&mapa[a], &mapa[d]);
                } else {
                    printf("\n[ERRO] Índices inválidos!\n");
                }
                break;
            }

            case 2:
                if (verificarMissao(jogador->missao, mapa, n, jogador->cor)) {
                    printf("\n========== VITÓRIA ==========\n");
                    printf("Parabéns! Você cumpriu sua missão!\n");
                    printf("=============================\n");
                    jogoEmAndamento = 0;
                } else {
                    printf("\nMissão ainda não cumprida. Continue jogando!\n");
                }
                break;

            case 0:
                jogoEmAndamento = 0;
                break;

            default:
                printf("\nOpção inválida!\n");
        }
    }
    
    // 3. Limpeza:
    liberarMemoria(mapa, jogador);
    
    return 0;
}

// --- Implementação das Funções ---

// --- Cadastro dos territórios ---
void cadastrarTerritorios(Territorio* mapa, int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i);
        printf("Nome: ");
        scanf(" %29[^\n]", mapa[i].nome);
        printf("Cor do exército: ");
        scanf(" %9s", mapa[i].cor);
        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// --- Exibir todos os territórios ---
void exibirTerritorios(const Territorio* mapa, int n) {
    int i;
    printf("\n===== MAPA DE TERRITÓRIOS =====\n");
    printf("%-3s | %-20s | %-10s | %-7s\n", "ID", "Nome", "Cor", "Tropas");
    printf("-------------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("%-3d | %-20s | %-10s | %-7d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("-------------------------------------------\n");
}

// --- Função de ataque ---
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\n[ERRO] Não pode atacar um território da mesma cor!\n");
        return;
    }

    if (atacante->tropas < 2) {
        printf("\n[ERRO] O território atacante precisa ter pelo menos 2 tropas!\n");
        return;
    }

    int dadoA = (rand() % 6) + 1;
    int dadoD = (rand() % 6) + 1;

    printf("\nAtaque de %s (%s) contra %s (%s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    printf("Dado atacante: %d | Dado defensor: %d\n", dadoA, dadoD);

    if (dadoA > dadoD) {
        printf(">> Vitória do atacante!\n");
        defensor->tropas = atacante->tropas / 2;
        strcpy(defensor->cor, atacante->cor);
        printf("%s agora pertence ao exército %s!\n", defensor->nome, defensor->cor);
    } else {
        printf(">> Defesa bem-sucedida!\n");
        atacante->tropas -= 1;
    }
}

// --- Atribuir missão aleatória ---
void atribuirMissao(char* destino, const char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

// --- Verificação de missão ---
int verificarMissao(const char* missao, Territorio* mapa, int tamanho, const char* corJogador) {
    int i;
    if (strstr(missao, "Conquistar 3 territórios seguidos")) {
        int contador = 0;
        for (i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) contador++;
        }
        if (contador >= 3) return 1;
    }
    else if (strstr(missao, "Eliminar todas as tropas da cor vermelha")) {
        for (i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0) return 0;
        }
        return 1;
    }
    else if (strstr(missao, "Ter 10 tropas")) {
        for (i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0 && mapa[i].tropas >= 10)
                return 1;
        }
    }
    else if (strstr(missao, "Conquistar todos os territórios")) {
        for (i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) != 0) return 0;
        }
        return 1;
    }
    return 0;
}

// --- Liberação de memória ---
void liberarMemoria(Territorio* mapa, Jogador* jogador) {
    free(mapa);
    free(jogador->missao);
    free(jogador);
}

// --- Menu principal ---
void exibirMenuPrincipal(void) {
    printf("\n===== MENU PRINCIPAL =====\n");
    printf("1 - Atacar um território\n");
    printf("2 - Verificar missão\n");
    printf("0 - Sair do jogo\n");
    printf("Escolha uma opção: ");
}

// --- Mostrar missão atual ---
void exibirMissao(const Jogador* jogador) {
    printf("\n===== SUA MISSÃO =====\n");
    printf("%s\n", jogador->missao);
    printf("======================\n");
}

// --- Limpar buffer de entrada ---
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
