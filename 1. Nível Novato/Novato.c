#include <stdio.h>
#include <string.h>

// Estrutura para armazenar dados de um território
typedef struct {
    char nome[30];
    char cor[15];
    int tropas;
} Territorio;

int main() {
    Territorio mapa[5];
    printf("Cadastro dos Territórios:\n");
    for (int i = 0; i < 5; i++) {
        printf("\nTerritório %d:\n", i+1);
        printf("Nome: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0'; // remove \n
        printf("Cor do Exército: ");
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Número de Tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // consome o \n deixado pelo scanf
    }

    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < 5; i++) {
        printf("%d. %s | Cor: %s | Tropas: %d\n", i+1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("===========================\n");
    return 0;
}
