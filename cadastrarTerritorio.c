#include <stdio.h>
#include <stdlib.h>
#include "cadastrarTerritorio.h"

Territorio *t = NULL;
int numero_territorio = 0;

void cadastrarTerritorio() {
    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &numero_territorio);

    t = (Territorio*)malloc(sizeof(Territorio) * numero_territorio);
    if (t == NULL) {
        printf("Erro ao alocar memoria para o territorio.\n");
        return; // Encerra a funcao com erro
    }

    // Loop para inserir as informacoes dos territorios
    for (int i = 0; i < numero_territorio; i++) {
        printf("Digite o nome do territorio %d: ", i + 1);
        scanf("%s", t[i].nome_territorio);

        printf("Digite a cor do exercito %d: ", i + 1);
        scanf("%s", t[i].cor_exercito);

        printf("Digite o numero de tropas %d: ", i + 1);
        scanf("%d", &t[i].numero_tropas);

        t[i].missao[0] = '\0'; // missao vazia inicialmente
    }
}
