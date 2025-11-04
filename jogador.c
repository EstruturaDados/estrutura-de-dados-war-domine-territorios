#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogador.h"
#include "territorio.h"

// Função para gerenciar missões dos jogadores
// Aloca memória para os jogadores e define missões iniciais.
Jogador* gerenciarMissoes(int numJogadores) {
    Jogador* jogadores = (Jogador*)malloc(numJogadores * sizeof(Jogador));
    if (jogadores == NULL) {
        printf("Erro ao alocar memória para os jogadores.\n");
        return NULL;
    }

    for (int i = 0; i < numJogadores; i++) {
        snprintf(jogadores[i].missao, sizeof(jogadores[i].missao), "Missão %d", i + 1);
        printf("Missão do jogador %d: %s\n", i + 1, jogadores[i].missao);
    }

    return jogadores;
}

// Função para verificar o progresso das missões
// Avalia se os jogadores cumpriram suas missões com base no estado atual do mapa.
void verificarMissoes(Jogador* jogadores, int numJogadores, const Territorio* mapa, int tamanho) {
    for (int i = 0; i < numJogadores; i++) {
        printf("Missão do jogador %s: %s\n", jogadores[i].nome, jogadores[i].missao);

        if (strstr(jogadores[i].missao, "10 tropas")) {
            for (int j = 0; j < tamanho; j++) {
                if (mapa[j].tropas >= 10 && strcmp(mapa[j].cor, jogadores[i].cor) == 0) {
                    printf("Jogador %s cumpriu sua missão: %s\n", jogadores[i].nome, jogadores[i].missao);
                    break;
                }
            }
        } else if (strstr(jogadores[i].missao, "Dominar 8 territórios")) {
            int count = 0;
            for (int j = 0; j < tamanho; j++) {
                if (strcmp(mapa[j].cor, jogadores[i].cor) == 0) {
                    count++;
                }
            }
            if (count >= 8) {
                printf("Jogador %s cumpriu sua missão: %s\n", jogadores[i].nome, jogadores[i].missao);
            }
        } else {
            printf("Missão do jogador %s ainda não implementada.\n", jogadores[i].nome);
        }
    }
}

// Função para inicializar os jogadores
// Aloca memória e define nomes, pontos e missões iniciais para cada jogador.
Jogador* inicializarJogadores(int numJogadores) {
    Jogador* jogadores = (Jogador*)malloc(numJogadores * sizeof(Jogador));
    if (jogadores == NULL) {
        printf("Erro ao alocar memória para os jogadores.\n");
        return NULL;
    }

    for (int i = 0; i < numJogadores; i++) {
        snprintf(jogadores[i].nome, sizeof(jogadores[i].nome), "Jogador %d", i + 1);
        jogadores[i].pontos = 0;
        snprintf(jogadores[i].missao, sizeof(jogadores[i].missao), "Missão %d", i + 1);
    }

    return jogadores;
}