#include <string.h>
#include <locale.h>
#ifdef _WIN32
#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "territorio.h"
#include "jogador.h"
#include "utils.h"

// Função principal do jogo
// Responsável por inicializar o jogo, configurar jogadores e territórios, e gerenciar o loop principal do jogo.
int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8"); // Configura o locale para UTF-8
#ifdef _WIN32
    SetConsoleOutputCP(65001); // Define o código de página para UTF-8 no Windows
    SetConsoleCP(65001);
#endif

    printf("Teste de UTF-8: ç, ã, á, é, í, ó, ú, ü, ñ\n");

    srand(time(NULL)); // Inicializa a semente para números aleatórios

    int numTerritorios = 20; // Número total de territórios disponíveis
    int numJogadores;

    // Game setup menu
    printf("==================== CONFIGURAÇÃO DO JOGO ====================\n");
    do {
        printf("Digite o número de jogadores (2 a 4): ");
        scanf("%d", &numJogadores);
        limparBufferEntrada();
        if (numJogadores < 2 || numJogadores > 4) {
            printf("Número inválido. Deve ser entre 2 e 4.\n");
        }
    } while (numJogadores < 2 || numJogadores > 4);

    // Inicializa os territórios e jogadores
    Territorio* mapa = alocarMapa(numTerritorios);
    if (mapa == NULL) {
        printf("Erro ao alocar memória para os territórios.\n");
        return 1;
    }
    inicializarTerritorios(mapa, numTerritorios);

    Jogador* jogadores = inicializarJogadores(numJogadores);
    if (jogadores == NULL) {
        printf("Erro ao alocar memória para os jogadores.\n");
        free(mapa);
        return 1;
    }

    // Atribuir territórios e cores aos jogadores
    for (int i = 0; i < numJogadores; i++) {
        printf("\nJogador %d, escolha sua cor: ", i + 1);
        fgets(jogadores[i].cor, sizeof(jogadores[i].cor), stdin);
        jogadores[i].cor[strcspn(jogadores[i].cor, "\n")] = '\0';

        printf("Escolha 5 territórios para o jogador %d:\n", i + 1);
        for (int j = 0; j < 5; j++) {
            int escolha;
            do {
                printf("Digite o número do território (1 a %d): ", numTerritorios);
                scanf("%d", &escolha);
                limparBufferEntrada();
                if (escolha < 1 || escolha > numTerritorios || strcmp(mapa[escolha - 1].cor, "Livre") != 0) {
                    printf("Território inválido ou já ocupado. Tente novamente.\n");
                }
            } while (escolha < 1 || escolha > numTerritorios || strcmp(mapa[escolha - 1].cor, "Livre") != 0);

            snprintf(mapa[escolha - 1].cor, sizeof(mapa[escolha - 1].cor), "%s", jogadores[i].cor);
            printf("Território %d atribuído ao jogador %d.\n", escolha, i + 1);
        }
    }

    // Atribuir missões
    printf("\nMissões:\n");
    for (int i = 0; i < numJogadores; i++) {
        if (i == 0) {
            snprintf(jogadores[i].missao, sizeof(jogadores[i].missao), "Dominar 8 territórios.");
        } else {
            snprintf(jogadores[i].missao, sizeof(jogadores[i].missao), "Eliminar todas as tropas do jogador %s.", jogadores[0].nome);
        }
        printf("Jogador %s: %s\n", jogadores[i].nome, jogadores[i].missao);
    }

    // Gameplay menu
    int rodada = 1;
    while (rodada <= 15) {
        printf("\n==================== RODADA %d ====================\n", rodada);
        for (int i = 0; i < numJogadores; i++) {
            int acoesRestantes = 2;
            while (acoesRestantes > 0) {
                printf("\n==================== MENU ====================\n");
                printf("Jogador atual: %s\n", jogadores[i].nome);
                printf("Ações restantes: %d\n", acoesRestantes);
                printf("1 - Atacar\n");
                printf("2 - Mover Tropas\n");
                printf("3 - Visualizar Tropas/Territórios\n");
                printf("0 - Finalizar Turno\n");
                printf("Escolha uma opção: ");
                int opcao;
                scanf("%d", &opcao);
                limparBufferEntrada();

                switch (opcao) {
                    case 1: {
                        int origem, destino;
                        printf("Escolha o território de origem para atacar: ");
                        scanf("%d", &origem);
                        printf("Escolha o território de destino para atacar: ");
                        scanf("%d", &destino);
                        realizarAtaque(&mapa[origem - 1], &mapa[destino - 1], jogadores[i].cor);
                        acoesRestantes--;
                        break;
                    }
                    case 2: {
                        int origemMov, destinoMov, qtdTropas;
                        printf("Escolha o território de origem para mover tropas: ");
                        scanf("%d", &origemMov);
                        printf("Escolha o território de destino para mover tropas: ");
                        scanf("%d", &destinoMov);
                        printf("Quantas tropas deseja mover: ");
                        scanf("%d", &qtdTropas);
                        moverTropas(&mapa[origemMov - 1], &mapa[destinoMov - 1], qtdTropas, jogadores[i].cor);
                        acoesRestantes--;
                        break;
                    }
                    case 3:
                        exibirTerritoriosJogador(mapa, numTerritorios, jogadores[i].cor);
                        break;
                    case 0:
                        printf("Turno finalizado para o jogador %s.\n", jogadores[i].nome);
                        acoesRestantes = 0;
                        break;
                    default:
                        printf("Opção inválida. Tente novamente.\n");
                }
            }
        }
        rodada++;

        // Display troop balance at the end of the round
        printf("\nSaldo de tropas ao final da rodada:\n");
        for (int i = 0; i < numJogadores; i++) {
            int totalTropas = 0;
            for (int j = 0; j < numTerritorios; j++) {
                if (strcmp(mapa[j].cor, jogadores[i].cor) == 0) {
                    totalTropas += mapa[j].tropas;
                }
            }
            printf("Jogador %s: %d tropas\n", jogadores[i].nome, totalTropas);
        }
    }

    free(mapa);
    free(jogadores);
    return 0;
}