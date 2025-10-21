#include <stdio.h> 
#include <string.h>

#define MAX_TERRITORIOS 5

struct Territorio{
    char nome[30];
    char cor[10];
    int tropas;
};

void limparBufferEntrada(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
};

int main(){
    struct Territorio cadastros[MAX_TERRITORIOS];
    int totalTerritorios = 0;
    int opcao;

do {

    
    printf("============================\n");
    printf("     Territórios do War\n");
    printf("============================\n");
    printf("1 - Cadastrar novo território\n");
    printf("2 - Listar todos os territórios\n");
    printf("0 - Sair\n");
    printf("-----------------------------\n");
    printf("Escolha uma opção :");

    
    scanf("%d", &opcao);
    limparBufferEntrada();

    switch (opcao){
    case 1 : 
        printf("--- Cadastro de novo território ---\n\n");

        if(totalTerritorios < MAX_TERRITORIOS){
            printf("Digite o nome do território: ");
            fgets(cadastros[totalTerritorios].nome, sizeof(cadastros[totalTerritorios].nome), stdin);

            printf("Digite a cor do território: ");
            fgets(cadastros[totalTerritorios].cor, sizeof(cadastros[totalTerritorios].cor), stdin);

            cadastros[totalTerritorios].nome[strcspn(cadastros[totalTerritorios].nome, "\n")] = '\0';
            cadastros[totalTerritorios].cor[strcspn(cadastros[totalTerritorios].cor, "\n")] = '\0';
            
            
            printf("Digite a qunatidade de tropas: ");
            scanf("%d", &cadastros[totalTerritorios].tropas);
            limparBufferEntrada();
            

            totalTerritorios++;

            printf("\nTerritório cadastrado com sucesso!!\n");
        } else{
            printf("Total de territórios cadastrados!!\n");
        }

        printf("\nPressione Enter para continuar...");
        getchar();// Pausa para o usuário ler a mensagem antes de voltar ao menu
        break;
    
    case 2: 
        printf("--- Lista de territórios cadastrados --- \n\n");

        if(totalTerritorios == 0) {
            printf("Nenhum território cadastrado ainda.\n");
        } else{
            for(int i = 0; i < totalTerritorios; i++){
                printf("---------------------------------\n");
                printf("Território %d\n", i + 1);
                printf("Nome: %s\n", cadastros[i].nome);
                printf("Dominado por: %s\n", cadastros[i].cor);
                printf("Tropas: %d\n", cadastros[i].tropas);
                
            }
             printf("-------------------------------------\n");
        }
        
        
        printf("\nPressine enter para continuar...");
        getchar();
        break;

    case 0: 
        printf("\nSaindo do sistema...\n");
        break;

    default: 
        printf("\nOpção invalida!Tente novamente.\n");
        printf("\nPressione enter para continuar...");
        getchar();
        break;
    
    }

}while(opcao != 0);
return 0;

};
