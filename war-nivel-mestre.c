#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura do território
struct Territorio {
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército
    int tropas;      // Quantidade de tropas
};

typedef struct Territorio Territorio;

// Função para cadastrar os territórios
void cadastrarTerritorios(Territorio *mapa, int quantidade) {
    int i;

    printf("\n=== CADASTRO DE TERRITORIOS ===\n\n");

    for (i = 0; i < quantidade; i++) {
        printf("Territorio %d\n", i + 1);

        printf("Digite o nome do territorio: ");
        scanf("%29s", mapa[i].nome);

        printf("Digite a cor do exercito: ");
        scanf("%9s", mapa[i].cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);

        printf("\n");
    }
}

// Função para exibir os territórios
void exibirMapa(Territorio *mapa, int quantidade) {
    int i;

    printf("\n=== MAPA ATUAL ===\n\n");

    for (i = 0; i < quantidade; i++) {
        printf("Indice: %d\n", i);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do exercito: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
        printf("---------------------------\n");
    }
}

// Função para atribuir uma missão aleatória ao jogador
void atribuirMissao(char *destino, char *missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

// Função para exibir a missão do jogador
void exibirMissao(char *missao, int jogador) {
    printf("\n=== MISSAO DO JOGADOR %d ===\n", jogador);
    printf("%s\n", missao);
}

// Função que simula um ataque entre dois territórios
void atacar(Territorio *atacante, Territorio *defensor) {
    int dadoAtacante, dadoDefensor;
    int tropasTransferidas;

    // O atacante precisa ter pelo menos 2 tropas para atacar
    if (atacante->tropas <= 1) {
        printf("\nO territorio atacante nao possui tropas suficientes para atacar.\n");
        return;
    }

    printf("\n=== BATALHA ===\n");
    printf("Atacante: %s (%s) - Tropas: %d\n", atacante->nome, atacante->cor, atacante->tropas);
    printf("Defensor: %s (%s) - Tropas: %d\n", defensor->nome, defensor->cor, defensor->tropas);

    // Sorteio dos dados
    dadoAtacante = rand() % 6 + 1;
    dadoDefensor = rand() % 6 + 1;

    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    // Se o atacante vencer
    if (dadoAtacante > dadoDefensor) {
        printf("\nO atacante venceu a batalha!\n");

        tropasTransferidas = atacante->tropas / 2;

        if (tropasTransferidas < 1) {
            tropasTransferidas = 1;
        }

        // O defensor muda de cor
        strcpy(defensor->cor, atacante->cor);

        // Atualiza as tropas
        atacante->tropas = atacante->tropas - tropasTransferidas;
        defensor->tropas = tropasTransferidas;

        printf("O territorio %s foi conquistado!\n", defensor->nome);
    } else {
        printf("\nO defensor venceu a batalha!\n");

        atacante->tropas--;
        printf("O atacante perdeu 1 tropa.\n");
    }
}

// Função para verificar se a missão foi cumprida
int verificarMissao(char *missao, Territorio *mapa, int tamanho) {
    int i;
    int contadorAzul = 0;
    int contadorVermelho = 0;
    int contadorVerde = 0;
    int contadorAmarelo = 0;
    int totalTropas = 0;

    // Conta territórios por cor e soma tropas
    for (i = 0; i < tamanho; i++) {
        if (strcmp(mapa[i].cor, "azul") == 0) {
            contadorAzul++;
        }
        if (strcmp(mapa[i].cor, "vermelho") == 0) {
            contadorVermelho++;
        }
        if (strcmp(mapa[i].cor, "verde") == 0) {
            contadorVerde++;
        }
        if (strcmp(mapa[i].cor, "amarelo") == 0) {
            contadorAmarelo++;
        }

        totalTropas += mapa[i].tropas;
    }

    // Verificações simples das missões
    if (strcmp(missao, "Conquistar 3 territorios da cor azul") == 0 && contadorAzul >= 3) {
        return 1;
    }

    if (strcmp(missao, "Conquistar 3 territorios da cor vermelho") == 0 && contadorVermelho >= 3) {
        return 1;
    }

    if (strcmp(missao, "Conquistar 3 territorios da cor verde") == 0 && contadorVerde >= 3) {
        return 1;
    }

    if (strcmp(missao, "Conquistar 3 territorios da cor amarelo") == 0 && contadorAmarelo >= 3) {
        return 1;
    }

    if (strcmp(missao, "Alcancar 20 tropas no mapa") == 0 && totalTropas >= 20) {
        return 1;
    }

    return 0;
}

// Função para liberar memória
void liberarMemoria(Territorio *mapa, char *missao1, char *missao2) {
    free(mapa);
    free(missao1);
    free(missao2);
}

int main() {
    Territorio *mapa;
    int quantidade;
    int atacanteIndice, defensorIndice;
    char continuar;

    // Missões disponíveis
    char *missoes[] = {
        "Conquistar 3 territorios da cor azul",
        "Conquistar 3 territorios da cor vermelho",
        "Conquistar 3 territorios da cor verde",
        "Conquistar 3 territorios da cor amarelo",
        "Alcancar 20 tropas no mapa"
    };

    int totalMissoes = 5;

    // Missões dos jogadores
    char *missaoJogador1;
    char *missaoJogador2;

    srand(time(NULL));

    printf("Digite a quantidade de territorios que deseja cadastrar: ");
    scanf("%d", &quantidade);

    if (quantidade <= 0) {
        printf("Quantidade invalida.\n");
        return 1;
    }

    // Alocação dinâmica do mapa
    mapa = (Territorio *) calloc(quantidade, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memoria para o mapa.\n");
        return 1;
    }

    // Alocação dinâmica para as missões dos jogadores
    missaoJogador1 = (char *) malloc(100 * sizeof(char));
    missaoJogador2 = (char *) malloc(100 * sizeof(char));

    if (missaoJogador1 == NULL || missaoJogador2 == NULL) {
        printf("Erro ao alocar memoria para as missoes.\n");
        free(mapa);
        return 1;
    }

    // Cadastro dos territórios
    cadastrarTerritorios(mapa, quantidade);

    // Sorteio das missões
    atribuirMissao(missaoJogador1, missoes, totalMissoes);
    atribuirMissao(missaoJogador2, missoes, totalMissoes);

    // Exibe a missão apenas uma vez
    exibirMissao(missaoJogador1, 1);
    exibirMissao(missaoJogador2, 2);

    // Loop principal de ataques
    do {
        exibirMapa(mapa, quantidade);

        printf("\n=== ESCOLHA DOS TERRITORIOS PARA ATAQUE ===\n");

        printf("Digite o indice do territorio atacante: ");
        scanf("%d", &atacanteIndice);

        printf("Digite o indice do territorio defensor: ");
        scanf("%d", &defensorIndice);

        // Validação dos índices
        if (atacanteIndice < 0 || atacanteIndice >= quantidade ||
            defensorIndice < 0 || defensorIndice >= quantidade) {
            printf("\nIndice invalido.\n");
        }
        else if (atacanteIndice == defensorIndice) {
            printf("\nUm territorio nao pode atacar ele mesmo.\n");
        }
        else if (strcmp(mapa[atacanteIndice].cor, mapa[defensorIndice].cor) == 0) {
            printf("\nNao e permitido atacar territorio da mesma cor.\n");
        }
        else {
            atacar(&mapa[atacanteIndice], &mapa[defensorIndice]);

            // Verifica se algum jogador cumpriu a missão
            if (verificarMissao(missaoJogador1, mapa, quantidade)) {
                printf("\n*** O Jogador 1 cumpriu sua missao e venceu o jogo! ***\n");
                break;
            }

            if (verificarMissao(missaoJogador2, mapa, quantidade)) {
                printf("\n*** O Jogador 2 cumpriu sua missao e venceu o jogo! ***\n");
                break;
            }
        }

        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);

    } while (continuar == 's' || continuar == 'S');

    // Libera memória
    liberarMemoria(mapa, missaoJogador1, missaoJogador2);

    printf("\nMemoria liberada com sucesso.\n");
    printf("Programa encerrado.\n");

    return 0;
}
