#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Desafio War

// declaraçao da struct territorio
typedef struct territorio
{
    int chave;
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// declaraçao da struct do nó para lista encadeada
typedef struct no
{
    Territorio territorio;
    struct no *prox;
} No;

Territorio cadastrarTerritorio(Territorio territorio);
void exibirTerritorio(Territorio territorio);
No *inserirNaLista(Territorio territorio, No *noCabeca);
void imprimirLista(No *noCabeca);
void realizarAtaque(Territorio *atacante, Territorio *defensor);

// solicita e armazena os dados do territorio
Territorio cadastrarTerritorio(Territorio territorio)
{
    printf("\nInforme o nome do território: ");
    scanf(" %[^\n]", territorio.nome);
    printf("Informe a cor do exército: ");
    scanf(" %[^\n]", territorio.cor);
    printf("Informe a quantidade de tropas: ");
    scanf(" %d", &territorio.tropas);

    return territorio;
}

// exibe os dados do territorio
void exibirTerritorio(Territorio territorio)
{
    // valida se territorio é vazio
    if (territorio.nome[0] == '\0')
    {
        printf("\nTerritório não cadastrado.\n");
        return;
    }

    printf("\n------------------------------------------------\n");
    printf("Nome: %s\n", territorio.nome);
    printf("Cor do exército: %s\n", territorio.cor);
    printf("Quantidade de tropas: %d\n", territorio.tropas);
    printf("------------------------------------------------\n");
}

// insere um novo territorio na lista encadeada
No *inserirNaLista(Territorio territorio, No *noCabeca)
{
    // valida se territorio é vazio
    if (territorio.nome[0] == '\0')
    {
        printf("\nTerritório não cadastrado.\n");
        return;
    }

    No *novo = (No *)malloc(sizeof(No));
    novo->territorio = territorio;
    novo->prox = noCabeca->prox;
    noCabeca->prox = novo;

    return noCabeca->prox;
}

// exibe todos os territorios cadastrados
void imprimirLista(No *noCabeca)
{
    No *temp = (No *)malloc(sizeof(No));

    printf("\nExibindo todos os territórios:\n");

    for (temp = noCabeca->prox; temp != NULL; temp = temp->prox)
    {
        exibirTerritorio(temp->territorio);
    }

    free(temp);
}

// realiza ataque entre dois territorios
void realizarAtaque(Territorio *atacante, Territorio *defensor){

}

int main(void)
{
    // inicializa variáveis
    char opc = '\0';
    char opcao = 'S';
    Territorio territorio = {0};
    No *noCabeca = (No *)malloc(sizeof(No));
    No *novoNo = (No *)malloc(sizeof(No));

    printf("\n***********************************************************");
    printf("\n                      Bem-vindo ao War!                   ");

    // laço para menu principal
    do
    {
        printf("\n***********************************************************\n");
        printf("\nSelecione uma opção: \n1. Cadastrar território\n2. Jogar\n3. Ver mapa\n4. Sair");
        printf("\nOpção: ");
        scanf(" %c", &opc);

        switch (opc)
        {
        case '1':
            printf("\n***********************************************************");
            printf("\n                  Cadastro dos territórios                  \n");

            do
            {
                // solicita dados para cadastro do territorio
                territorio = cadastrarTerritorio(territorio);
                // insere o nó na lista encadeada
                novoNo = inserirNaLista(territorio, noCabeca);
                // exibe o territorio cadastrado
                exibirTerritorio(novoNo->territorio);

                printf("\nCadastrar novo território? (Digite 'S' para Sim e 'N' para Não): ");
                scanf(" %c", &opcao);

            } while (opcao == 'S' || opcao == 's');
            
            printf("\nVoltando ao menu anterior...\n");

            break;

        case '2':
            printf("\n***********************************************************");
            printf("\n                   Vamos iniciar o jogo!                   \n");

            // realizarAtaque();

            break;

        case '3':
            printf("\n***********************************************************");
            printf("\n                     Ver mapa do jogo                      \n");
            imprimirLista(noCabeca);
            printf("\nVoltando ao menu anterior...\n");

            break;

        case '4':
            printf("\nEncerrando o jogo...\n\n");

            break;

        default:
            printf("\nOpção inválida.\n");

            break;
        }
    } while (opc != '4');

    // libera memória
    free(noCabeca);
    free(novoNo);

    return 0;
}
