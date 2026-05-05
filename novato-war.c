#include <stdio.h>
#include <string.h>

//Exercício de cadastramento dos territórios para o jogo WAR

struct Territorio {
    char nome[30]; //nome do território
    char cor[10]; //cor do exército
    int tropas; //quantidade de tropas;
};

int main(){
    struct Territorio territorios[5]; //Criamos espaço para o armazenamento de 5 territórios
    int i;

    printf("\n=== CADASTRO DE TERRITÓRIOS ===\n\n");

    //Entrada de dados, o laço será executado 5 vezes, 1 para cada território

    for( i = 0; i < 5; i++){
        printf("Território %d\n", i + 1);

        printf("Digite o nome do território: \n");
        scanf("%s", territorios[i].nome);

        printf("Digite a cor do exército: \n");
        scanf("%s", territorios[i].cor);

        printf("Digite a quantidade de tropas: \n");
        scanf("%d", &territorios[i].tropas); //aqui usamos um & pois a variável é uma int (Mesmo serve sempre para quando for float, double ou uma struct.campo numérico)

        printf("\n");
    }

    //Agora iremos exibir os dados

    printf("\n=== TERRITÓRIOS CADASTRADOS ===\n\n");

    for(i = 0; i < 5; i++){
        printf("Território %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exercito: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
        printf("-------------------------\n");
    }

    return 0;

}
