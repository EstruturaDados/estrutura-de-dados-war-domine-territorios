#include <stdio.h>
#include <stdlib.h> // Malloc, calloc e free
#include <string.h> // Strcpy e strcmp
#include <time.h>   // Aleatoriedade dos dados

// Constantes
#define MAX_NOME 30
#define MAX_COR 10

// --- Definição da Struct Territorio ---
// Struct para representar uma entidade complexa, como um Território,
// que tem nome, cor e quantidade de tropas.
typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

// --- Protótipos das Funções ---
// Declarar as funções antes para organizar o código
void cadastrarTerritorios(Territorio* mapa, int numTerritorios);
void exibirTerritorios(Territorio* mapa, int numTerritorios);
void atacar(Territorio* atacante, Territorio* defensor);
void atribuirMissao(char** destino, char* missoes[], int totalMissoes);
int verificarMissao(char* missao, Territorio* mapa, int numTerritorios, char* corJogador);
void liberarMemoria(Territorio* mapa, char* missao);

int main() {
    // Gerador de numeros aleatorios para as missoes e dados de batalha
    srand(time(NULL));

    int numTerritorios;
    Territorio* mapa = NULL; // Ponteiro para o início do array.
    char* missaoJogador = NULL; // Ponteiro para a missão do jogador, alocada dinamicamente.
    char corJogador[MAX_COR]; // A cor do jogador para verificar a missão
    
    int indiceAtacante, indiceDefensor;
    
    // Vetor de strings com as missões disponíveis
    char* missoes[] = {
        "Possuir 3 territorios.",
        "Possuir 20 ou mais tropas.",
        "Conquistar o territorio 'Gondor'.",
        "Conquistar um territorio com mais de 5 tropas.",
        "Ter a maior quantidade de tropas."
    };
    int totalMissoes = sizeof(missoes) / sizeof(missoes[0]);

    printf("--- Simulacao de Batalha (WAR) ---\n");
    printf("Quantos territorios voce deseja criar? ");
    scanf("%d", &numTerritorios);

    // --- Alocacao Dinamica de Memoria ---
    // Funcao calloc aloca um bloco de memoria para 'numTerritorios' structs
    // do tipo Territorio.
    mapa = (Territorio*)calloc(numTerritorios, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria para o mapa!\n");
        return 1; // Encerra o programa com erro
    }
    
    // Atribui uma missao ao jogador no inicio do jogo
    atribuirMissao(&missaoJogador, missoes, totalMissoes);

    // Função para preencher dados dos territórios
    cadastrarTerritorios(mapa, numTerritorios);
    
    // Assume que a cor do primeiro territorio cadastrado é a cor do jogador
    strcpy(corJogador, mapa[0].cor);

    // Exibe a missão do jogador
    printf("\n--- Sua Missao ---\n");
    printf("Missao: %s\n", missaoJogador);
    printf("Sua cor: %s\n", corJogador);
    
    // --- Loop principal do jogo ---
    // O jogo continuará em turnos até que o jogador cumpra sua missão ou decida sair.
    while(1) {
        printf("\n--- Inicio do Turno ---\n");
        exibirTerritorios(mapa, numTerritorios);

        // Permite que o usuário escolha os territórios para a batalha
        printf("\n--- Simulacao de Ataque ---\n");
        printf("Digite o indice do territorio atacante (0 a %d) ou -1 para sair: ", numTerritorios - 1);
        scanf("%d", &indiceAtacante);

        if (indiceAtacante == -1) {
            printf("Fim do jogo.\n");
            break; // Sai do loop
        }

        printf("Digite o indice do territorio defensor (0 a %d): ", numTerritorios - 1);
        scanf("%d", &indiceDefensor);
    
        // --- Validacao do Ataque ---
        // Garante que o jogador não ataque um território de sua própria cor
        if (strcmp(mapa[indiceAtacante].cor, mapa[indiceDefensor].cor) == 0) {
            printf("\nImpossivel atacar! O territorio defensor pertence a mesma cor do atacante.\n");
        } else if (indiceAtacante >= numTerritorios || indiceDefensor >= numTerritorios ||
                indiceAtacante < 0 || indiceDefensor < 0) {
            printf("\nIndices de territorios invalidos.\n");
        } else {
            // Chama a função de ataque, passando os ponteiros para os territórios
            atacar(&mapa[indiceAtacante], &mapa[indiceDefensor]);
        }
        
        // Verifica se a missão foi cumprida após o ataque
        if (verificarMissao(missaoJogador, mapa, numTerritorios, corJogador)) {
            printf("\n--- MISSAO CUMPRIDA! VITORIA! ---\n");
            printf("Parabens! Voce conquistou a vitoria cumprindo sua missao.\n");
            break; // Sai do loop principal
        } else {
            printf("\nMissao nao cumprida neste turno. O jogo continuaria...\n");
        }
    }

    // --- Gerenciamento de Memoria ---
    // Libera a memória alocada dinamicamente para o array de territórios e para a missão
    liberarMemoria(mapa, missaoJogador);

    return 0;
}

// --- Funcao para Cadastrar Territorios ---
// Recebe um ponteiro para o array de structs e o numero total de territorios.
// Preenche os dados de cada um usando ponteiros.
void cadastrarTerritorios(Territorio* mapa, int numTerritorios) {
    for (int i = 0; i < numTerritorios; i++) {
        printf("\nCadastrando o Territorio %d de %d:\n", i + 1, numTerritorios);
        
        // Limpa o buffer de entrada do teclado para evitar problemas com a leitura de strings
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
        
        printf("Nome do Territorio: ");
        // fgets para ler o nome
        fgets(mapa[i].nome, MAX_NOME, stdin);
        // Remove o caractere de nova linha '\n'
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0;

        printf("Cor do exercito: ");
        scanf("%9s", mapa[i].cor);

        printf("Numero de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// --- Funcao para Exibir Territorios ---
// Percorre o array de structs e imprime as informações.
void exibirTerritorios(Territorio* mapa, int numTerritorios) {
    printf("%-20s %-10s %s\n", "Territorio", "Cor", "Tropas");
    printf("---------------------------------------------\n");
    for (int i = 0; i < numTerritorios; i++) {
        printf("%-20s %-10s %d\n", mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// --- Funcao de Ataque ---
// Recebe ponteiros para o território atacante e defensor para manipular seus dados
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\nBatalha iniciada: %s (%s) vs. %s (%s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    // Simula a rolagem de dados (número aleatório de 1 a 6)
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("Dados rolados: Atacante = %d | Defensor = %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("O atacante %s venceu a batalha!\n", atacante->nome);
        
        // O atacante conquista o território
        printf("O territorio %s agora pertence ao exercito %s.\n", defensor->nome, atacante->cor);
        strcpy(defensor->cor, atacante->cor); // Atualiza a cor (dono) do território
        
        // Metade das tropas do atacante são transferidas para o defensor
        int tropasTransferidas = atacante->tropas / 2;
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;

        printf("Tropas atualizadas: %d tropas transferidas. Atacante agora tem %d tropas. Defensor agora tem %d tropas.\n",
               tropasTransferidas, atacante->tropas, defensor->tropas);
        
    } else {
        printf("O defensor %s resistiu ao ataque!\n", defensor->nome);
        atacante->tropas--; // Atacante perde uma tropa
        printf("O atacante %s perdeu uma tropa. Total de tropas: %d.\n", atacante->nome, atacante->tropas);
    }
}

// --- Funcao de Atribuicao de Missao ---
// Recebe um ponteiro para ponteiro de char, o vetor de missoes e o tamanho
void atribuirMissao(char** destino, char* missoes[], int totalMissoes) {
    int indiceSorteado = rand() % totalMissoes;
    char* missaoSorteada = missoes[indiceSorteado];
    
    // Aloca memoria para a string da missao
    *destino = (char*)malloc(strlen(missaoSorteada) + 1);
    if (*destino == NULL) {
        printf("Erro ao alocar memoria para a missao!\n");
        return;
    }
    
    // Copia a string da missao sorteada para a memória alocada
    strcpy(*destino, missaoSorteada);
}

// --- Funcao de Verificacao de Missao ---
// Recebe a missao do jogador, o mapa, o tamanho e a cor do jogador
// e verifica se alguma das condições de vitória foi atendida.
int verificarMissao(char* missao, Territorio* mapa, int numTerritorios, char* corJogador) {
    // Missao 1: Possuir 3 territorios.
    if (strcmp(missao, "Possuir 3 territorios.") == 0) {
        int territoriosDoJogador = 0;
        for (int i = 0; i < numTerritorios; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                territoriosDoJogador++;
            }
        }
        return territoriosDoJogador >= 3;
    }
    
    // Missao 2: Possuir 20 ou mais tropas.
    if (strcmp(missao, "Possuir 20 ou mais tropas.") == 0) {
        for (int i = 0; i < numTerritorios; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0 && mapa[i].tropas >= 20) {
                return 1;
            }
        }
    }

    // Missao 3: Conquistar o territorio 'Gondor'.
    if (strcmp(missao, "Conquistar o territorio 'Gondor'.") == 0) {
        for (int i = 0; i < numTerritorios; i++) {
            if (strcmp(mapa[i].nome, "Gondor") == 0 && strcmp(mapa[i].cor, corJogador) == 0) {
                return 1;
            }
        }
    }
    
    // Missao 4: Conquistar um territorio com mais de 5 tropas.
    if (strcmp(missao, "Conquistar um territorio com mais de 5 tropas.") == 0) {
        for (int i = 0; i < numTerritorios; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0 && mapa[i].tropas > 5) {
                return 1;
            }
        }
    }
    
    // Missao 5: Ter a maior quantidade de tropas.
    if (strcmp(missao, "Ter a maior quantidade de tropas.") == 0) {
        int maxTropas = 0;
        int tropasJogador = 0;
        for(int i = 0; i < numTerritorios; i++) {
            if(mapa[i].tropas > maxTropas) {
                maxTropas = mapa[i].tropas;
            }
            if(strcmp(mapa[i].cor, corJogador) == 0) {
                tropasJogador += mapa[i].tropas;
            }
        }
        return tropasJogador > maxTropas;
    }

    return 0; // Missão não foi cumprida
}

// --- Funcao para Liberar Memoria ---
// Recebe os ponteiros para o array e a missão e libera a memória alocada.
void liberarMemoria(Territorio* mapa, char* missao) {
    if (mapa != NULL) {
        free(mapa);
        printf("\nMemoria do mapa liberada.\n");
    }
    if (missao != NULL) {
        free(missao);
        printf("Memoria da missao liberada.\n");
    }
}
