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
void exibirTerritorios(Territorio *mapa, int quantidade) {
    int i;

    printf("\n=== TERRITORIOS CADASTRADOS ===\n\n");

    for (i = 0; i < quantidade; i++) {
        printf("Indice: %d\n", i);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do exercito: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
        printf("---------------------------\n");
    }
}

// Função que simula um ataque entre dois territórios
void atacar(Territorio *atacante, Territorio *defensor) {
    int dadoAtacante, dadoDefensor;
    int tropasTransferidas;

    // Validação simples: atacante precisa ter mais de 1 tropa para atacar
    if (atacante->tropas <= 1) {
        printf("\nO territorio atacante nao possui tropas suficientes para atacar.\n");
        return;
    }

    printf("\n=== BATALHA ===\n");
    printf("Atacante: %s (%s) - Tropas: %d\n", atacante->nome, atacante->cor, atacante->tropas);
    printf("Defensor: %s (%s) - Tropas: %d\n", defensor->nome, defensor->cor, defensor->tropas);

    // Simulação dos dados
    dadoAtacante = rand() % 6 + 1;
    dadoDefensor = rand() % 6 + 1;

    printf("\nDado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    // Regra simples de vitória
    if (dadoAtacante > dadoDefensor) {
        printf("\nO atacante venceu a batalha!\n");

        // O atacante perde metade das tropas para ocupar o território
        tropasTransferidas = atacante->tropas / 2;

        // Garantir que ao menos 1 tropa seja transferida
        if (tropasTransferidas < 1) {
            tropasTransferidas = 1;
        }

        // Atualiza o defensor com a nova cor
        strcpy(defensor->cor, atacante->cor);

        // Atualiza as tropas dos dois territórios
        atacante->tropas = atacante->tropas - tropasTransferidas;
        defensor->tropas = tropasTransferidas;

        printf("O territorio %s foi conquistado!\n", defensor->nome);
    } else {
        printf("\nO defensor venceu a batalha!\n");

        // Se perder, atacante perde 1 tropa
        atacante->tropas--;

        printf("O atacante perdeu 1 tropa.\n");
    }
}

// Função para liberar a memória alocada dinamicamente
void liberarMemoria(Territorio *mapa) {
    free(mapa);
}

int main() {
    Territorio *mapa;
    int quantidade;
    int atacanteIndice, defensorIndice;
    char continuar;

    // Inicializa a semente dos números aleatórios
    srand(time(NULL));

    printf("Digite a quantidade de territorios que deseja cadastrar: ");
    scanf("%d", &quantidade);

    // Validação simples
    if (quantidade <= 0) {
        printf("Quantidade invalida.\n");
        return 1;
    }

    // Alocação dinâmica de memória
    mapa = (Territorio *) calloc(quantidade, sizeof(Territorio));

    // Verifica se a memória foi alocada corretamente
    if (mapa == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    // Cadastro inicial
    cadastrarTerritorios(mapa, quantidade);

    // Exibe os territórios cadastrados
    exibirTerritorios(mapa, quantidade);

    // Loop de ataques
    do {
        printf("\n=== ESCOLHA DOS TERRITORIOS PARA ATAQUE ===\n");
        exibirTerritorios(mapa, quantidade);

        printf("Digite o indice do territorio atacante: ");
        scanf("%d", &atacanteIndice);

        printf("Digite o indice do territorio defensor: ");
        scanf("%d", &defensorIndice);

        // Validação dos índices
        if (atacanteIndice < 0 || atacanteIndice >= quantidade ||
            defensorIndice < 0 || defensorIndice >= quantidade) {
            printf("\nIndice invalido.\n");
        }
        // Não pode atacar a si mesmo
        else if (atacanteIndice == defensorIndice) {
            printf("\nUm territorio nao pode atacar ele mesmo.\n");
        }
        // Não pode atacar território da mesma cor
        else if (strcmp(mapa[atacanteIndice].cor, mapa[defensorIndice].cor) == 0) {
            printf("\nNao e permitido atacar um territorio da mesma cor.\n");
        }
        else {
            atacar(&mapa[atacanteIndice], &mapa[defensorIndice]);

            printf("\n=== MAPA APOS O ATAQUE ===\n");
            exibirTerritorios(mapa, quantidade);
        }

        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);

    } while (continuar == 's' || continuar == 'S');

    // Libera a memória ao final do programa
    liberarMemoria(mapa);

    printf("\nMemoria liberada com sucesso.\n");
    printf("Programa encerrado.\n");

    return 0;
}
