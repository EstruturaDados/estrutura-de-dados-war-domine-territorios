#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "atacarTerritorio.h"

void atacar(Territorio* atacante, Territorio* defensor) {
    int dado_atacante = rand() % 6 + 1; // Gera um numero aleatorio entre 1 e 6 para o atacante
    int dado_defensor = rand() % 6 + 1;
    printf("Dado do atacante: %d\n", dado_atacante);
    printf("Dado do defensor: %d\n", dado_defensor);

    if (dado_atacante > dado_defensor) {
        printf("O atacante (%s) venceu!\n", atacante->nome_territorio);
        defensor->numero_tropas -= 1;
    } else {
        printf("O defensor (%s) venceu!\n", defensor->nome_territorio);
        atacante->numero_tropas -= 1;
    }
}

void atacarTerritorio() {
    extern Territorio *t;
    extern int numero_territorio;

    srand(time(NULL));

    int i_atacante = -1, i_defensor = -1;

    printf("\nEscolha o indice do atacante: ");
    scanf("%d", &i_atacante);

    printf("Escolha o indice do defensor: ");
    scanf("%d", &i_defensor);

    if (i_atacante >= numero_territorio || i_defensor >= numero_territorio ||
        i_atacante < 0 || i_defensor < 0) {
        printf("Indice invalido.\n");
        return;
    }

    atacar(&t[i_atacante], &t[i_defensor]);

    printf("\n--- Resultado ---\n");
    for (int i = 0; i < numero_territorio; i++) {
        printf("%s: %d tropas\n", t[i].nome_territorio, t[i].numero_tropas);
    }
}
