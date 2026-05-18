#ifndef EXIBIR_MISSAO_H
#define EXIBIR_MISSAO_H

typedef struct {
    char descricao[100];
    char objetivo[100];
} Missao;

void exibirMissao(Missao* m, int numero_missao);

#endif
