#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "territorio.h"

// Função para alocar memória para o mapa de territórios
// Retorna um ponteiro para um array de territórios inicializado com calloc.
Territorio* alocarMapa(int tamanho) {
    return (Territorio*)calloc(tamanho, sizeof(Territorio));
}

// Função para cadastrar territórios manualmente
// Permite ao usuário inserir informações sobre cada território.
void cadastrarTerritorios(Territorio* mapa, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);

        printf("Nome do território: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do exército: ");
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // Limpa o buffer
    }
}

// Função para exibir o estado atual do mapa
// Mostra informações detalhadas de cada território.
void exibirMapa(const Territorio* mapa, int tamanho) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < tamanho; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do Exército: %s\n", mapa[i].cor);
        printf("Número de Tropas: %d\n", mapa[i].tropas);
    }
}

// Função para simular um ataque entre dois territórios
// Realiza a lógica de combate com base em dados aleatórios.
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\nSimulando ataque entre %s (atacante) e %s (defensor)...\n",
           atacante->nome, defensor->nome);

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("%s venceu o ataque!\n", atacante->nome);
        defensor->tropas--;
        if (defensor->tropas <= 0) {
            printf("%s conquistou o território %s!\n", atacante->nome, defensor->nome);
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = atacante->tropas / 2;
        }
    } else {
        printf("%s defendeu com sucesso!\n", defensor->nome);
        atacante->tropas--;
    }
}

// Função para realizar um ataque validando as condições
// Verifica se o jogador pode atacar e executa a lógica de combate.
void realizarAtaque(Territorio* origem, Territorio* destino, const char* corJogador) {
    if (strcmp(origem->cor, corJogador) != 0) {
        printf("Você só pode atacar com territórios que pertencem a você!\n");
        return;
    }
    if (strcmp(destino->cor, corJogador) == 0) {
        printf("Você não pode atacar seus próprios territórios!\n");
        return;
    }

    printf("\n%s está atacando %s!\n", origem->nome, destino->nome);

    int dadoAtaque = rand() % 6 + 1; // Rolagem do dado para ataque
    int dadoDefesa = rand() % 6 + 1; // Rolagem do dado para defesa

    printf("Dado de ataque: %d\n", dadoAtaque);
    printf("Dado de defesa: %d\n", dadoDefesa);

    if (dadoAtaque > dadoDefesa) {
        printf("%s conquistou o território %s!\n", origem->nome, destino->nome);
        strcpy(destino->cor, origem->cor);
        destino->tropas = 1; // Move uma tropa para o território conquistado
        // O atacante mantém sua contagem de tropas
    } else {
        printf("%s defendeu com sucesso!\n", destino->nome);
        origem->tropas -= 1; // Deduz uma tropa da origem
    }
}

// Função para inicializar os territórios
// Define nomes, cores e tropas iniciais para cada território.
void inicializarTerritorios(Territorio* mapa, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        snprintf(mapa[i].nome, sizeof(mapa[i].nome), "Território %d", i + 1);
        strcpy(mapa[i].cor, "Livre");
        mapa[i].tropas = rand() % 3 + 1; // Atribui um número aleatório de tropas entre 1 e 3
    }
}

// Função para mover tropas entre territórios
// Valida as condições e atualiza as tropas nos territórios envolvidos.
void moverTropas(Territorio* origem, Territorio* destino, int quantidade, const char* corJogador) {
    if (strcmp(origem->cor, corJogador) != 0 || strcmp(destino->cor, corJogador) != 0) {
        printf("Você só pode mover tropas entre territórios que pertencem a você!\n");
        return;
    }
    if (quantidade <= 0) {
        printf("Movimentação inválida: a quantidade de tropas deve ser maior que 0.\n");
        return;
    }
    if (origem->tropas <= quantidade) {
        printf("Movimentação inválida: tropas insuficientes no território %s.\n", origem->nome);
        return;
    }

    origem->tropas -= quantidade;
    destino->tropas += quantidade;

    printf("%d tropas movidas de %s para %s.\n", quantidade, origem->nome, destino->nome);
}