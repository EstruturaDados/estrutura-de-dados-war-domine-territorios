// war_mestre.c
// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO (Nível Mestre)
// ============================================================================
//
// Modularização completa, missões, passagem por referência/const correctness,
// alocação dinâmica (calloc) e lógica de combate simples.
//
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define NUM_TERRITORIOS 5
#define MAX_NOME 32
#define MAX_COR 16

#define MISSao_DESTRUIR_VERDE 0
#define MISSao_CONQUISTAR_3    1
#define NUM_MISSOES            2

typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;


Territorio *alocarMapa(size_t n);
void liberarMemoria(Territorio *mapa);

void inicializarTerritorios(Territorio *mapa, size_t n);

void exibirMenuPrincipal(void);
void exibirMapa(const Territorio *mapa, size_t n);
void exibirMissao(int idMissao);

void faseDeAtaque(Territorio *mapa, size_t n);
void simularAtaque(Territorio *atacante, Territorio *defensor);

int sortearMissao(void);
int verificarVitoria(const Territorio *mapa, size_t n, int idMissao, const char *corJogador);

void limparBufferEntrada(void);
void pausarTela(void);


Territorio *alocarMapa(size_t n) {
    Territorio *mapa = (Territorio *)calloc(n, sizeof(Territorio));
    return mapa; 
}

void liberarMemoria(Territorio *mapa) {
    free(mapa);
}

void inicializarTerritorios(Territorio *mapa, size_t n) {

    const char *nomes[NUM_TERRITORIOS] = { "Aldeia", "Porto", "Deserto", "Montanha", "Planicie" };
    const char *cores[NUM_TERRITORIOS] = { "Verde", "Vermelho", "Azul", "Amarelo", "Neutro" };
    const int tropasInit[NUM_TERRITORIOS] = { 5, 4, 3, 6, 2 };

    for (size_t i = 0; i < n && i < NUM_TERRITORIOS; ++i) {
        strncpy(mapa[i].nome, nomes[i], MAX_NOME - 1);
        mapa[i].nome[MAX_NOME - 1] = '\0';
        strncpy(mapa[i].cor, cores[i], MAX_COR - 1);
        mapa[i].cor[MAX_COR - 1] = '\0';
        mapa[i].tropas = tropasInit[i];
    }
}

void exibirMenuPrincipal(void) {
    puts("\n--- MENU ---");
    puts("1 - Atacar");
    puts("2 - Verificar missão");
    puts("0 - Sair");
    printf("Escolha: ");
}

void exibirMapa(const Territorio *mapa, size_t n) {
    puts("\n=== MAPA ATUAL ===");
    printf("%-3s %-16s %-10s %s\n", "ID", "TERRITORIO", "COR", "TROPAS");
    puts("-----------------------------------------");
    for (size_t i = 0; i < n; ++i) {
        printf("%-3zu %-16s %-10s %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

void exibirMissao(int idMissao) {
    puts("\n=== MISSÃO ===");
    switch (idMissao) {
        case MISSao_DESTRUIR_VERDE:
            puts("Destruir o exército Verde (eliminar todas as tropas de territórios com cor 'Verde').");
            break;
        case MISSao_CONQUISTAR_3:
            puts("Conquistar 3 territórios (ter 3 ou mais territórios com a sua cor).");
            break;
        default:
            puts("Missão desconhecida.");
            break;
    }
}

void faseDeAtaque(Territorio *mapa, size_t n) {
    int idxAtacador = -1, idxDefensor = -1;
    exibirMapa((const Territorio *)mapa, n);
    printf("\nDigite o ID do território ATACANTE (1-%zu, 0 para cancelar): ", n);
    if (scanf("%d", &idxAtacador) != 1) { limparBufferEntrada(); puts("Entrada invalida."); return; }
    if (idxAtacador == 0) { limparBufferEntrada(); puts("Ataque cancelado."); return; }
    printf("Digite o ID do território DEFENSOR (1-%zu): ", n);
    if (scanf("%d", &idxDefensor) != 1) { limparBufferEntrada(); puts("Entrada invalida."); return; }
    limparBufferEntrada();

    if (idxAtacador < 1 || idxAtacador > (int)n || idxDefensor < 1 || idxDefensor > (int)n) {
        puts("IDs invalidos. Operacao abortada.");
        return;
    }
    if (idxAtacador == idxDefensor) {
        puts("Um territorio nao pode atacar a si mesmo.");
        return;
    }

    Territorio *at = &mapa[idxAtacador - 1];
    Territorio *df = &mapa[idxDefensor - 1];
    simularAtaque(at, df);
}

void simularAtaque(Territorio *atacante, Territorio *defensor) {
    if (atacante->tropas <= 1) {
        printf("%s nao tem tropas suficientes para atacar (minimo 2 tropas necessarias).\n", atacante->nome);
        return;
    }

    int dadoAtaque = rand() % 6 + 1; 
    int dadoDefesa  = rand() % 6 + 1;

    printf("\n%s (Cor %s, Tropas %d) ataca %s (Cor %s, Tropas %d)\n",
           atacante->nome, atacante->cor, atacante->tropas,
           defensor->nome, defensor->cor, defensor->tropas);

    printf("Dado do atacante: %d | Dado do defensor: %d\n", dadoAtaque, dadoDefesa);

    if (dadoAtaque >= dadoDefesa) {
        defensor->tropas -= 1;
        printf("%s perde 1 tropa (restam %d).\n", defensor->nome, defensor->tropas);
        if (defensor->tropas <= 0) {
            defensor->tropas = 1;
            atacante->tropas -= 1;
            strncpy(defensor->cor, atacante->cor, MAX_COR - 1);
            defensor->cor[MAX_COR - 1] = '\0';
            printf("%s foi conquistado pelo exército %s! (Atacante agora tem %d tropas)\n",
                   defensor->nome, defensor->cor, atacante->tropas);
        }
    } else {
        atacante->tropas -= 1;
        printf("Ataque falhou: atacante perde 1 tropa (restam %d).\n", atacante->tropas);
    }
}

int sortearMissao(void) {
    return rand() % NUM_MISSOES; 
}

int verificarVitoria(const Territorio *mapa, size_t n, int idMissao, const char *corJogador) {
    if (idMissao == MISSao_DESTRUIR_VERDE) {
        for (size_t i = 0; i < n; ++i) {
            if (strcmp(mapa[i].cor, "Verde") == 0 && mapa[i].tropas > 0) return 0;
        }
        return 1; 
    } else if (idMissao == MISSao_CONQUISTAR_3) {
        int contador = 0;
        for (size_t i = 0; i < n; ++i) {
            if (strcmp(mapa[i].cor, corJogador) == 0) contador++;
        }
        return contador >= 3 ? 1 : 0;
    }
    return 0;
}

void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void pausarTela(void) {
    printf("\nPressione ENTER para continuar...");
    fflush(stdout);
    int c = getchar();
    if (c != '\n') {
        limparBufferEntrada();
    }
}

int main(void) {
    setlocale(LC_ALL, "");
    srand((unsigned int)time(NULL));

    size_t n = NUM_TERRITORIOS;
    Territorio *mapa = alocarMapa(n);
    if (mapa == NULL) {
        fprintf(stderr, "Erro: falha ao alocar memoria para o mapa.\n");
        return EXIT_FAILURE;
    }

    inicializarTerritorios(mapa, n);

    char corJogador[MAX_COR];
    printf("Bem-vindo ao WAR - Nivel Mestre!\n");
    printf("Escolha a cor do seu exercito (ex: Verde, Vermelho, Azul, Amarelo, Neutro): ");
    if (fgets(corJogador, sizeof(corJogador), stdin) == NULL) {
        strncpy(corJogador, "Jogador", MAX_COR - 1);
        corJogador[MAX_COR - 1] = '\0';
    } else {
        corJogador[strcspn(corJogador, "\n")] = '\0';
        if (strlen(corJogador) == 0) {
            strncpy(corJogador, "Jogador", MAX_COR - 1);
            corJogador[MAX_COR - 1] = '\0';
        }
    }

    int idMissao = sortearMissao();
    printf("\nSua missao secreta atribuida:\n");
    exibirMissao(idMissao);

    int opcao = -1;
    do {
        exibirMapa((const Territorio *)mapa, n);
        puts("");
        exibirMenuPrincipal();
        if (scanf("%d", &opcao) != 1) {
            limparBufferEntrada();
            puts("Entrada invalida. Tente novamente.");
            opcao = -1;
            continue;
        }
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                faseDeAtaque(mapa, n);
                pausarTela();
                break;
            case 2:
                exibirMissao(idMissao);
                if (verificarVitoria((const Territorio *)mapa, n, idMissao, corJogador)) {
                    puts("\n*** PARABENS! Missao cumprida! ***");
                    opcao = 0;
                } else {
                    puts("\nMissao ainda nao cumprida. Continue jogando!");
                }
                pausarTela();
                break;
            case 0:
                puts("\nSaindo do jogo. Obrigado por jogar!");
                break;
            default:
                puts("Opcao invalida. Tente novamente.");
                pausarTela();
                break;
        }

    } while (opcao != 0);

    liberarMemoria(mapa);
    return EXIT_SUCCESS;
}
