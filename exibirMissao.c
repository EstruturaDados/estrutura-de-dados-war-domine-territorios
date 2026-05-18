#include <stdio.h>
#include "exibirMissao.h"

void exibirMissao(Missao* m, int numero_missao) {
    printf("Informacoes das missoes cadastradas:\n");
    for (int i = 0; i < numero_missao; i++) {
        printf("Missao %d:\n", i + 1);
        printf("Descricao: %s\n", m[i].descricao);
        printf("Objetivo: %s\n", m[i].objetivo);
        printf("\n");
    }
}
