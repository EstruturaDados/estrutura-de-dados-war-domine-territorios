#ifndef JOGADOR_H
#define JOGADOR_H

#include "territorio.h"

typedef struct {
    char nome[50];
    char cor[20]; // Adiciona o campo para a cor do jogador
    int pontos;
    char missao[100];
} Jogador;

Jogador* inicializarJogadores(int numJogadores);
void verificarMissoes(Jogador* jogadores, int numJogadores, const Territorio* mapa, int tamanho);

#endif