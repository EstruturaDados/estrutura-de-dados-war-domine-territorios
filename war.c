#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura de Representação
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Protótipos
void atribuirMissao(char** destino, char* missoes[], int totalMissoes);
void exibirMissao(char* missao);
void exibirMapa(Territorio* mapa, int tamanho);
void atacar(Territorio* atacante, Territorio* defensor);
int verificarMissao(char* missao, Territorio* mapa, int tamanho);
void liberarMemoria(Territorio* mapa, char* missao);

int main() {
    srand(time(NULL)); 

    char* bancoDeMissoes[] = {
        "Conquistar 3 territorios",
        "Eliminar tropas da cor Vermelha",
        "Dominar o mapa com a cor Azul",
        "Ter mais de 10 tropas em um setor",
        "Conquistar o territorio China"
    };
    int totalMissoes = 5;
    int numTerritorios = 4;

    Territorio* mapa = (Territorio*)malloc(numTerritorios * sizeof(Territorio));
    char* missaoJogador = NULL;

    // Inicialização do Mapa
    strcpy(mapa[0].nome, "China");   strcpy(mapa[0].cor, "Azul");     mapa[0].tropas = 8;
    strcpy(mapa[1].nome, "America"); strcpy(mapa[1].cor, "Vermelha");  mapa[1].tropas = 8;
    strcpy(mapa[2].nome, "Brasil");  strcpy(mapa[2].cor, "Verde");     mapa[2].tropas = 8;
    strcpy(mapa[3].nome, "Africa");  strcpy(mapa[3].cor, "Amarela");   mapa[3].tropas = 8;

    atribuirMissao(&missaoJogador, bancoDeMissoes, totalMissoes);

    printf("--- BEM-VINDO AO TESTE WAR NIVEL MESTRE! ---\n");
    exibirMissao(missaoJogador);
    printf("---------------------------------------------\n\n");

    int jogoAtivo = 1;
    while (jogoAtivo) {
        exibirMapa(mapa, numTerritorios);

        int orig, dest;
        printf("\n--- MENU DE ATAQUE ---\n");
        printf("Escolha o indice do ATACANTE (0 a 3) ou -1 para sair: ");
        scanf("%d", &orig);

        if (orig == -1) break;

        printf("Escolha o indice do DEFENSOR (0 a 3): ");
        scanf("%d", &dest);

        if (orig >= 0 && orig < numTerritorios && dest >= 0 && dest < numTerritorios) {
            atacar(&mapa[orig], &mapa[dest]);
        } else {
            printf("Indices invalidos!\n");
            continue;
        }

        // ==========================================
        // ABA DE VERIFICAÇÃO DE MISSÃO (NOVO)
        // ==========================================
        printf("\n[SISTEMA] Verificando objetivos...\n");
        if (verificarMissao(missaoJogador, mapa, numTerritorios)) {
            printf("\n**********************************************\n");
            printf(" ----VITORIA DETECTADA!----\n");
            printf(" MISSÃO CONCLUIDA: %s\n", missaoJogador);
            printf("**********************************************\n");
            
            exibirMapa(mapa, numTerritorios); // Mostra o mapa final da vitória
            jogoAtivo = 0; // Finaliza o loop e o código conclui
        } else {
            printf("[SISTEMA] Missao ainda pendente. Proximo turno...\n");
        }
        // ==========================================
    }

    liberarMemoria(mapa, missaoJogador);
    return 0;
}

void atribuirMissao(char** destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    *destino = (char*)malloc((strlen(missoes[indice]) + 1) * sizeof(char));
    if (*destino != NULL) {
        strcpy(*destino, missoes[indice]);
    }
}

void exibirMissao(char* missao) {
    if (missao) printf("SUA MISSAO SECRETA: %s\n", missao);
}

void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Aviso: Voce nao pode atacar a si mesmo!\n");
        return;
    }
    if (atacante->tropas <= 0) {
        printf("Aviso: Tropas insuficientes para atacar!\n");
        return;
    }

    int dadoAtk = (rand() % 6) + 1;
    int dadoDef = (rand() % 6) + 1;

    printf("Combate: %s(%d) vs %s(%d)\n", atacante->nome, dadoAtk, defensor->nome, dadoDef);

    if (dadoAtk > dadoDef) {
        printf("Sucesso! %s conquistado por %s.\n", defensor->nome, atacante->nome);
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas -= defensor->tropas;
    } else {
        printf("Falha! O atacante %s perdeu 1 tropa.\n", atacante);
        atacante->tropas--;
    }
}

// Lógica aprimorada para verificar todas as missões do vetor
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    int contAzul = 0;
    int temVermelha = 0;

    for (int i = 0; i < tamanho; i++) {
        // Conta territórios Azuis (cor do jogador principal)
        if (strcmp(mapa[i].cor, "Azul") == 0) contAzul++;
        // Verifica se ainda existe alguém Vermelho no mapa
        if (strcmp(mapa[i].cor, "Vermelha") == 0) temVermelha = 1;

        // Missão: Ter mais de 10 tropas em um setor
        if (strstr(missao, "10 tropas") && mapa[i].tropas >= 10) return 1;
    }

    // Missão: Conquistar 3 territorios
    if (strstr(missao, "3 territorios") && contAzul >= 3) return 1;

    // Missão: Eliminar cor Vermelha
    if (strstr(missao, "Eliminar") && temVermelha == 0) return 1;

    // Missão: Dominar o mapa todo (4 territórios)
    if (strstr(missao, "Dominar o mapa") && contAzul == tamanho) return 1;

    // Missão: Conquistar China (território no índice 0)
    if (strstr(missao, "China") && strcmp(mapa[0].cor, "Azul") == 0) return 1;

    return 0; 
}

void exibirMapa(Territorio* mapa, int tamanho) {
    printf("\n--- MAPA ATUAL ---\n");
    for (int i = 0; i < tamanho; i++) {
        printf("[%d] %s | Cor: %-10s | Tropas: %d\n", i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

void liberarMemoria(Territorio* mapa, char* missao) {
    free(mapa);
    free(missao);
    printf("\nMemoria limpa. Jogo encerrado.\n");
}