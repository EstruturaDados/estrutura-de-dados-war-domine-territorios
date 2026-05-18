#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atribuirMissao.h"

void atribuirMissaoTerritorio(char* nomeTerritorio, Territorio* t) {
    char* missoes[] = {
        "Conquistar territorio vizinho",
        "Defender territorio",
        "Conquistar 2 territorios vizinhos",
        "Destruir exercito inimigo"
    };

    int indice = rand() % 4; // Gera um indice aleatorio entre 0 e 3
    t->missao[0] = '\0';
    strncpy(t->missao, missoes[indice], sizeof(t->missao) - 1); // Atribui a missao correspondente ao territorio
}

void atribuirMissao() {
    extern Territorio *t;
    extern int numero_territorio;

    if (t == NULL || numero_territorio == 0) {
        printf("Nenhum territorio cadastrado!\n");
        return;
    }

    for (int i = 0; i < numero_territorio; i++) {
        atribuirMissaoTerritorio(t[i].nome_territorio, &t[i]);
    }
    printf("Missoes atribuidas com sucesso!\n");
}
