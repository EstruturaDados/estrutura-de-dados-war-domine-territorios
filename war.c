#include <stdio.h>
#include <string.h>

// Definição da struct Territorio
// Armazena nome do território, cor do exército e quantidade de tropas
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
    // Declaração de vetor para armazenar 5 territórios
    struct Territorio territorios[5];

    // Entrada de dados dos territórios
    printf("Cadastro de Territórios\n");
    printf("=======================\n");

    for (int i = 0; i < 5; i++) {
        printf("\nTerritório %d:\n", i + 1);

        // Leitura do nome do território
        printf("Digite o nome do território: ");
        scanf("%s", territorios[i].nome);

        // Leitura da cor do exército
        printf("Digite a cor do exército: ");
        scanf("%s", territorios[i].cor);

        // Leitura da quantidade de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    // Exibição dos dados cadastrados
    printf("\nResumo dos Territórios Cadastrados\n");
    printf("==================================\n");

    for (int i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].cor);
        printf("Quantidade de Tropas: %d\n", territorios[i].tropas);
        printf("----------------------------------\n");
    }

    return 0;
}
