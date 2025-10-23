#include <stdio.h>
#include <string.h>

/*
    ================================================
    Programa: Cadastro de Territórios
    Autor: João Vitor Mendonça
    Data: 18/10/2025
    Descrição: 
      Este programa permite cadastrar 5 territórios,
      informando o nome, a cor do exército e a quantidade
      de tropas. Depois, mostra todos os dados cadastrados.
    ================================================
*/

// Estrutura que guarda as informações de cada território
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// Função para cadastrar os territórios
void cadastrarTerritorios(struct Territorio t[], int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\n--- Cadastro do território %d ---\n", i + 1);

        printf("Nome do território: ");
        scanf(" %[^\n]", t[i].nome); // lê até o enter

        printf("Cor do exército: ");
        scanf(" %[^\n]", t[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &t[i].tropas);
    }
}

// Função para exibir os dados cadastrados
void mostrarTerritorios(struct Territorio t[], int qtd) {
    printf("\n===== LISTA DE TERRITÓRIOS =====\n");
    for (int i = 0; i < qtd; i++) {
        printf("\nTerritório %d\n", i + 1);
        printf("Nome: %s\n", t[i].nome);
        printf("Cor: %s\n", t[i].cor);
        printf("Tropas: %d\n", t[i].tropas);
    }
    printf("\n===============================\n");
}

int main() {
    struct Territorio territorios[5]; // vetor para armazenar até 5 territórios

    printf("=== CADASTRO DE TERRITÓRIOS ===\n");
    cadastrarTerritorios(territorios, 5);

    printf("\nExibindo todos os territórios cadastrados...\n");
    mostrarTerritorios(territorios, 5);

    printf("\nCadastro finalizado com sucesso!\n");

    return 0;
}
