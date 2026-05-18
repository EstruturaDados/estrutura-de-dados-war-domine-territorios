#include <stdio.h>
#include "exibirTerritorio.h"

void exibirTerritorio(Territorio* t, int numero_territorio) {
    printf("Informacoes dos territorios cadastrados:\n");
    for (int i = 0; i < numero_territorio; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("Nome: %s\n", t[i].nome_territorio);
        printf("Cor do exercito: %s\n", t[i].cor_exercito);
        printf("Numero de tropas: %d\n", t[i].numero_tropas);
        printf("\n");
    }
}

void exibirMapa() {
    extern Territorio *t;
    extern int numero_territorio;
    exibirTerritorio(t, numero_territorio);
}
