// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ============================
// Estrutura do Território
// ============================
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ============================
// Função para cadastrar territórios
// ============================
void cadastrarTerritorios(Territorio* mapa, int total) {
    for (int i = 0; i < total; i++) {

        printf("\nTerritorio %d\n", i);

        printf("Nome: ");
        scanf(" %[^\n]", mapa[i].nome);

        printf("Cor do exercito: ");
        scanf(" %s", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// ============================
// Função para exibir territórios
// ============================
void exibirTerritorios(Territorio* mapa, int total) {
    printf("\n===== MAPA ATUAL =====\n");

    for (int i = 0; i < total; i++) {
        printf("\n[%d] %s", i, mapa[i].nome);
        printf(" | Cor: %s", mapa[i].cor);
        printf(" | Tropas: %d", mapa[i].tropas);
    }
    printf("\n======================\n");
}

// ============================
// Função de ataque
// ============================
void atacar(Territorio* atacante, Territorio* defensor) {

    if (atacante->tropas <= 1) {
        printf("Atacante precisa de pelo menos 2 tropas para atacar!\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\nDado atacante: %d", dadoAtacante);
    printf("\nDado defensor: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {

        printf("Atacante venceu a batalha!\n");

        // transfere o controle
        strcpy(defensor->cor, atacante->cor);

        int tropasTransferidas = atacante->tropas / 2;

        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;

    } else {

        printf("Defensor venceu!\n");
        atacante->tropas--;

        if (atacante->tropas < 1)
            atacante->tropas = 1;
    }
}

// ============================
// Função para liberar memória
// ============================
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

// ============================
// MAIN
// ============================
int main() {

    srand(time(NULL)); // inicializa aleatoriedade

    int total;

    printf("Digite o numero total de territorios: ");
    scanf("%d", &total);

    // Alocação dinâmica
    Territorio* mapa = calloc(total, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, total);

    int opcao;

    do {
        printf("\n==== MENU WAR ====\n");
        printf("1 - Exibir territorios\n");
        printf("2 - Realizar ataque\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {

        case 1:
            exibirTerritorios(mapa, total);
            break;

        case 2: {
            int a, d;

            exibirTerritorios(mapa, total);

            printf("\nIndice do territorio atacante: ");
            scanf("%d", &a);

            printf("Indice do territorio defensor: ");
            scanf("%d", &d);

            if (a < 0 || a >= total || d < 0 || d >= total) {
                printf("Indice invalido!\n");
            }
            else if (strcmp(mapa[a].cor, mapa[d].cor) == 0) {
                printf("Nao pode atacar territorio da mesma cor!\n");
            }
            else {
                atacar(&mapa[a], &mapa[d]);
            }

            break;
        }

        case 0:
            printf("Encerrando jogo...\n");
            break;

        default:
            printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    liberarMemoria(mapa);

    printf("Memoria liberada com sucesso!\n");

    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
