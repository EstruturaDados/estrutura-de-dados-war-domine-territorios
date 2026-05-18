#include <stdio.h>
#include "verificarMissao.h"

void verificarMissaoTerritorio(Territorio* t, int numero_territorio) {
    printf("Verificando missoes dos territorios:\n");
    for (int i = 0; i < numero_territorio; i++) {
        printf("Territorio %d: %s\n", i + 1, t[i].nome_territorio);
        printf("Missao: %s\n", t[i].missao);
        printf("\n");
    }
}

void verificarMissao() {
    extern Territorio *t;
    extern int numero_territorio;

    if (t == NULL || numero_territorio == 0) {
        printf("Nenhum territorio cadastrado!\n");
        return;
    }

    verificarMissaoTerritorio(t, numero_territorio);
}
