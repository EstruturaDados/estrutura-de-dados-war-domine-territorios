#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TERRITORIO 5

// Criar a estrutura Território

struct Territorio{
char nome[30];
char cor[20]; 
int tropas;
};

// Limpa o buffer de entrada para evitar problemas com fgets após scanf
void LimparBufferEntrada(){
    int c;
    while (( c = getchar()) != '\n' && c != EOF);
}

// Função principal
int main(){

    printf("================================\n");
    printf("WAR ESTRUTURADO-CADASTRO INICIAL\n");
    printf("================================\n");
    
    // Array estático para armazenar os territorios
    struct Territorio mapa[TERRITORIO];
    int total_territorios = 0;

    // Cadastro dos territorios
      
    printf("Cadastro de 5 territorios\n");
    printf("================================");
    do
    {
        printf("\n--Cadastro do território %d--\n", total_territorios + 1);
        printf("\nNome do territorio: ");
        fgets(mapa[total_territorios].nome, 30, stdin);
        mapa[total_territorios].nome[strcspn(mapa[total_territorios].nome, "\n")] = 0;

    
        printf("Cor do território: ");
        fgets(mapa[total_territorios].cor, 20, stdin);
        mapa[total_territorios].cor[strcspn(mapa[total_territorios].cor, "\n")] = 0;

        printf("Número de tropas: ");
        scanf("%d", &mapa[total_territorios].tropas);
        getchar(); // Limpa o buffer do teclado
        printf("================================");

        total_territorios++; // Incrementa o contador de territórios cadastrados
    } while (total_territorios < TERRITORIO);

    // Exibe a lista de territórios cadastrados
    printf("\n--- MAPA DO MUNDO - ESTADO ATUAL---\n");
    for(int i = 0; i < total_territorios; i++){
        printf("TERRITORIO: %d\n"
            " -Nome: %s\n"
            " -Dominado por: %s\n"
            " -Tropas: %d\n \n", 
            i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas );
        
    }
     return 0;
    }