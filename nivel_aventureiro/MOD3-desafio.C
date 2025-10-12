#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define JOGADORES 2

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
// Função para cadastrar os territórios
// ==============================
void cadastrar_territorio(struct Territorio *mapa, int n) {  
    for(int i = 0; i < n; i++){
        printf("\n-- Cadastro do território %d --\n", i + 1);

        printf("Nome do território: ");
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0;

        printf("Cor do território: ");
        fgets(mapa[i].cor, 10, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = 0;

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        limparBufferEntrada();
    }
}

// ==============================
// Exibir territórios
// ==============================
void exibir_territorios(struct Territorio *mapa, int n) {
    printf("\n===============================\n");
    printf(" MAPA DO MUNDO - ESTADO ATUAL \n");
    printf("===============================\n");
    for (int i = 0; i < n; i++) {
        printf("Território %d: Nome: %s | Cor: %s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// ==============================
// Função de ataque
// ==============================
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Não é permitido atacar territórios da mesma cor!\n");
        return;
    }

    if(atacante->tropas < 1) {
        printf("O território atacante precisa ter pelo menos 1 tropa para atacar!\n");
        return;
    }
    printf("\n%s (%s) está atacando %s (%s)\n", 
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("O atacante venceu!\n");
        strcpy(defensor->cor, atacante->cor);      // muda a cor
        defensor->tropas = atacante->tropas / 2;   // metade das tropas
        atacante->tropas = atacante->tropas / 2;
    } else {
        printf("O defensor resistiu! O atacante perdeu 1 tropa.\n");
        atacante->tropas -= 1;
    }
}

// ==============================
// Função para atribuir missão
// ==============================
void atribuirMissao(char *destino, const char *missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

// ==============================
// Função para verificar missão (exemplo simples)
// ==============================
int verificarMissao(char *missao, struct Territorio *mapa, int tamanho) {
    // Exemplo simples: "Conquistar território com cor X"
    // Aqui vamos apenas verificar se existe algum território com cor "azul"
    if (strstr(missao, "azul") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0) return 1; // missão cumprida
        }
    }
    // Outras missões podem ser implementadas
    return 0; // missão não cumprida
}

// ==============================
// Função para liberar memória
// ==============================
void liberar_memoria(struct Territorio *mapa, char **missoesJogadores) {
    free(mapa);
    for (int i = 0; i < JOGADORES; i++) {
        free(missoesJogadores[i]);
    }
    free(missoesJogadores);
}

// ==============================
// Função para exibir o menu
// ==============================
int menu() {
    int opcao;
    printf("\n===============================\n");
    printf("      MENU DE AÇÕES       \n");
    printf("===============================\n");
    printf("1 - Atacar\n");
    printf("2 - Verificar missão\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    return opcao;
}


// ==============================
// Função principal ajustada
// ==============================
int main() {
    srand(time(NULL));
    printf("\n===================================\n");
    printf("          JOGO WAR        \n");
    printf("===================================\n");
    int numTerritorios;
    printf("Quantos territórios quer cadastrar? ");
    scanf("%d", &numTerritorios);
    limparBufferEntrada();

    // Alocação dinâmica de territórios
    struct Territorio *mapa = (struct Territorio *) calloc(numTerritorios, sizeof(struct Territorio));
    if (!mapa) {
        printf("Erro na alocação de memória!\n");
        return 1;
    }

    // Cadastro
    cadastrar_territorio(mapa, numTerritorios);
    exibir_territorios(mapa, numTerritorios);

    // -------------------------
    // Sistema de missões
    // -------------------------
    const char *missoesDisponiveis[5] = {
        "Conquistar 3 territórios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Ter mais tropas que o adversário",
        "Conquistar território com cor azul",
        "Controlar todos os territórios pares",
    };

    char **missoesJogadores = (char **)malloc(JOGADORES * sizeof(char*));
    for (int i = 0; i < JOGADORES; i++) {
        missoesJogadores[i] = (char *)malloc(100 * sizeof(char)); // espaço para missão
        atribuirMissao(missoesJogadores[i], missoesDisponiveis, 5);
        printf("\nJogador %d recebeu sua missão: %s\n", i + 1, missoesJogadores[i]);
    }

    // -------------------------
    // Loop do jogo com menu
    // -------------------------
    int opcao, atacante, defensor;
    char continuar = 's';

    while (1) {
        opcao = menu(); // Exibe o menu
        
        switch (opcao) {
            case 1: // Atacar
                printf("\nEscolha o território ATACANTE (1 a %d): ", numTerritorios);
                scanf("%d", &atacante);

                printf("Escolha o território DEFENSOR (1 a %d): ", numTerritorios);
                scanf("%d", &defensor);
                limparBufferEntrada();

                if (atacante >= 1 && atacante <= numTerritorios && defensor >= 1 && defensor <= numTerritorios) {
                    atacar(&mapa[atacante - 1], &mapa[defensor - 1]);
                } else {
                    printf(" Opção inválida!\n");
                }

                exibir_territorios(mapa, numTerritorios);
                break;

            case 2: // Verificar missão
                for (int i = 0; i < JOGADORES; i++) {
                    if (verificarMissao(missoesJogadores[i], mapa, numTerritorios)) {
                        printf("\nJogador %d cumpriu sua missão: %s\n", i + 1, missoesJogadores[i]);
                        continuar = 'n';
                    } else {
                        printf("\nJogador %d ainda não cumpriu sua missão: %s\n", i + 1, missoesJogadores[i]);
                    }
                }
                break;

            case 0: // Sair
                printf("\nEncerrando o jogo...\n");
                liberar_memoria(mapa, missoesJogadores);
                return 0;

            default:
                printf("Opção inválida! Tente novamente.\n");
        }

        if (continuar == 'n') break;
    }

    // Liberação de memória
    liberar_memoria(mapa, missoesJogadores);

    printf("\nMemória liberada. Encerrando o jogo...\n");
    return 0;
}
