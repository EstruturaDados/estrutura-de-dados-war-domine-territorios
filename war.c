
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pessoa{
    char nome[500];
    int idade;
    long int cpf;
};

/* typedef struct {...} estrutura_de_dados => usando typedef não precisamos declarar struct a cada vez que queremos acessar ou atribuir valor; usamos apenas o alias (estrutura_de_dados) */

// CADASTRO DE territorio

#define MAX_TAMANHO 5
#define NOME 30
#define COR 10

typedef struct{
    char nome[NOME];
    char cor[COR];
    int tropas;
} Territorio;

struct Emprestimo{
    char nomeUsuario[NOME];
    int identificador;
};


void limparBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // em C as vezes o terminal de saída acumula \n após a digitação do usuário (scanf), a limpeza garante nenhuma confusão com os dados inseridos pelo usuário
};

void exibirTerritorios(Territorio territorio[], int qtdTerritorios){
    for (int i = 0; i < qtdTerritorios; i++){
        printf("TERRITORIO %d:\n", i + 1);
        printf(" Nome: %s\n", territorio[i].nome);
        printf(" Cor: %s\n", territorio[i].cor);
        printf(" Tropas: %d\n\n", territorio[i].tropas);
    };
}

void combate(Territorio territorio[], int indiceAtaque, int indiceDefesa){
    Territorio *atacante = &territorio[indiceAtaque];
    Territorio *defensor = &territorio[indiceDefesa];

    printf("Atacante: %s | Cor %s - Tropas: %d\n", atacante->nome, atacante->cor, atacante->tropas);
    printf("Defensor : %s | Cor %s - Tropas: %d\n", defensor->nome, defensor->cor, defensor->tropas);

    if (atacante->tropas > defensor->tropas){
        printf("Atacante venceu!\n");
        atacante->tropas -= defensor->tropas;
        printf("Ainda lhe restam %d tropa(s).\n\n", (atacante->tropas));
    } else {
        printf("Defensor venceu!");
        defensor->tropas -= atacante->tropas;
        printf("Ainda lhe restam %d tropa(s).\n\n", (defensor->tropas));
    }

}

int main(){
    Territorio territorio[MAX_TAMANHO];
    
    int qtdTerritorios = 0;
    int opcao;

    do {
        printf("#########################################\n");
        printf("             WAR ESTRUTURADO             \n");
        printf("#########################################\n");
        printf("O que deseja fazer?\n");
        printf(" 1 - cadastrar território\n");
        printf(" 2 - listar territórios\n");
        printf(" 3 - atacar território\n");
        printf(" 0 - sair\n");

        scanf("%d", &opcao);

        limparBuffer();
        
        switch (opcao){
        case 1:
            printf("## Cadastro de território ##\n");
            if (qtdTerritorios < MAX_TAMANHO){
                printf("Qual o nome do território?\n");
                fgets(territorio[qtdTerritorios].nome, NOME, stdin);
                printf("Qual a cor do território?\n");
                fgets(territorio[qtdTerritorios].cor, COR, stdin);
                
                territorio[qtdTerritorios].nome[strcspn(territorio[qtdTerritorios].nome, "\n")] = '\0'; 
                territorio[qtdTerritorios].cor[strcspn(territorio[qtdTerritorios].cor, "\n")] = '\0';


                printf("Quantas tropas tem esse território?\n");
                scanf("%d", &territorio[qtdTerritorios].tropas);
                limparBuffer();

                qtdTerritorios++;

                exibirTerritorios(territorio, qtdTerritorios);

            }
            else{
                printf("Quantidade máxima de territórios atingida, não é possível cadastrar um novo.\n");
            }
            break;

        case 2:
            if (qtdTerritorios == 0){
                printf("Não há territórios cadastrados.\n");
                limparBuffer();
            } else {
                exibirTerritorios(territorio, qtdTerritorios);
            }
            break;

        case 3:
            int ataque, defesa;
            printf("Combate entre Territórios...\n");
            exibirTerritorios(territorio, qtdTerritorios);
            
            printf("Qual território vai ao ataque?...\n");
            scanf("%d", &ataque);
            
            printf("Qual território vai se defender?...\n");
            scanf("%d", &defesa);

            limparBuffer();

            printf("Combate acontecendo...\n");
            printf("...POW...\n");
            printf("...PEI...\n");
            printf("...TELI...\n");
            printf("...ZAGA...\n");

            int indiceAtaque = ataque - 1, indiceDefesa =  defesa - 1;

            combate(territorio, indiceAtaque,indiceDefesa);

            break;
        case 5:
            printf("Saindo...\n");
            break;
        case 0:
            printf("Saindo...\n");
            break;
        
        default:
            printf("\n\nVocê precisa escolher uma opção válida\n\n");
        };
    } while (opcao != 0 );           
}
