#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "territorio.h"

// Função para limpar o buffer de entrada
// Remove caracteres residuais no buffer após uma entrada do usuário.
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para liberar memória alocada
// Libera memória associada ao mapa e às missões dos jogadores.
void liberarMemoria(Territorio* mapa, char** missoes, int numJogadores) {
    free(mapa);
    if (missoes != NULL) {
        for (int i = 0; i < numJogadores; i++) {
            free(missoes[i]);
        }
        free(missoes);
    }
}

// Função para exibir territórios de um jogador
// Mostra os territórios controlados por um jogador específico e suas tropas.
void exibirTerritoriosJogador(const Territorio* mapa, int tamanho, const char* corJogador) {
    printf("\nTerritórios do jogador (%s):\n", corJogador);
    for (int i = 0; i < tamanho; i++) {
        if (strcmp(mapa[i].cor, corJogador) == 0) {
            printf("- %s: %d tropas\n", mapa[i].nome, mapa[i].tropas);
        }
    }
}