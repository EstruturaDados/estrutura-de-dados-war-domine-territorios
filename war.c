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

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Struct que representa um território do jogo War
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Cadastra os territórios com dados fornecidos pelo usuário
void cadastrar(Territorio* mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\n--- Território %d ---\n", i + 1);
        printf("Nome: ");
        scanf("%29s", mapa[i].nome);
        printf("Cor do exército: ");
        scanf("%9s", mapa[i].cor);
        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Exibe os dados de todos os territórios
void exibir(Territorio* mapa, int n) {
    printf("\n========== TERRITÓRIOS ==========\n");
    for (int i = 0; i < n; i++) {
        printf("[%d] %s | Cor: %s | Tropas: %d\n",
            i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Simula o ataque entre dois territórios usando dados (1 a 6)
void atacar(Territorio* atacante, Territorio* defensor) {
    int dado_ataque  = (rand() % 6) + 1;
    int dado_defesa  = (rand() % 6) + 1;

    printf("\n⚔  %s ataca %s!\n", atacante->nome, defensor->nome);
    printf("   Dado do atacante: %d | Dado do defensor: %d\n",
           dado_ataque, dado_defesa);

    if (dado_ataque > dado_defesa) {
        // Atacante vence: conquista o território
        printf("   Resultado: %s CONQUISTOU %s!\n",
               atacante->nome, defensor->nome);
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
    } else {
        // Defensor resiste: atacante perde uma tropa
        printf("   Resultado: %s resistiu! %s perde 1 tropa.\n",
               defensor->nome, atacante->nome);
        atacante->tropas--;
        if (atacante->tropas < 0) atacante->tropas = 0;
    }
}

// Libera a memória alocada dinamicamente
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

    srand(time(NULL));

    int n;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &n);

    // Alocação dinâmica do vetor de territórios
    Territorio* mapa = calloc(n, sizeof(Territorio));
    if (!mapa) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    cadastrar(mapa, n);
    exibir(mapa, n);

    // Loop de ataques
    char continuar = 's';
    while (continuar == 's' || continuar == 'S') {
        int atk, def;

        printf("\nÍndice do território ATACANTE: ");
        scanf("%d", &atk);
        printf("Índice do território DEFENSOR: ");
        scanf("%d", &def);

        // Validações básicas
        if (atk < 0 || atk >= n || def < 0 || def >= n) {
            printf("Índices inválidos.\n");
            continue;
        }
        if (atk == def) {
            printf("Um território não pode atacar a si mesmo.\n");
            continue;
        }
        if (strcmp(mapa[atk].cor, mapa[def].cor) == 0) {
            printf("Você não pode atacar um território da sua própria cor!\n");
            continue;
        }
        if (mapa[atk].tropas <= 0) {
            printf("O território atacante não tem tropas suficientes.\n");
            continue;
        }

        atacar(&mapa[atk], &mapa[def]);
        exibir(mapa, n);

        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);
    }

    liberarMemoria(mapa);
    printf("\nMemória liberada. Fim do jogo!\n");
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
