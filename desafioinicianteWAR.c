#include <stdio.h>

// Definição da struct
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {

    // Vetor para armazenar 5 territórios
    struct Territorio territorios[5];

    int i;

    printf("Cadastro de Territorios\n\n");

    // Entrada de dados
    for(i = 0; i < 5; i++) {
        printf("Territorio %d\n", i + 1);

        printf("Nome: ");
        scanf("%s", territorios[i].nome);

        printf("Cor do exercito: ");
        scanf("%s", territorios[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n");
    }

    // Exibição dos dados
    printf("\nTerritorios cadastrados:\n\n");

    for(i = 0; i < 5; i++) {
        printf("Territorio %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
        printf("-------------------\n");
    }

    return 0;
}