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

// Inclusão das bibliotecas padrão necessárias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Constantes Globais ---
#define TAM_STRING 100
#define TAM_NOME 30
#define TAM_COR 10
#define NUM_MISSOES 5

// --- Estrutura de Dados ---
struct Territorio {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
};

// --- Protótipos das Funções ---
void LimparBufferEntrada();
void cadastrarTerritorios(struct Territorio* mapa, int numTerritorios);
void exibirMapa(const struct Territorio* mapa, int numTerritorios);
void atacar(struct Territorio* atacante, struct Territorio* defensor);
void liberarMemoria(struct Territorio* mapa, char* missao);
int validarAtaque(const struct Territorio* atacante, const struct Territorio* defensor);
void exibirResultadoAtaque(const struct Territorio* atacante, const struct Territorio* defensor, int atacanteVenceu);
void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
int verificarMissao(const char* missao, const struct Territorio* mapa, int tamanho);
void exibirMissao(const char* missao);
void inicializarMissoes(char* missoes[]);

// --- Função para limpar buffer de entrada ---
void LimparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- Função para inicializar o vetor de missões ---
void inicializarMissoes(char* missoes[]) {
    missoes[0] = "Conquistar 3 territórios consecutivos";
    missoes[1] = "Eliminar todas as tropas da cor vermelha";
    missoes[2] = "Conquistar 4 territórios no total";
    missoes[3] = "Ter pelo menos 10 tropas em um único território";
    missoes[4] = "Eliminar todas as tropas da cor azul";
}

// --- Função para sortear e atribuir missão ao jogador ---
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

// --- Função para exibir a missão do jogador ---
void exibirMissao(const char* missao) {
    printf("\n══════════════════════════════════════════════\n");
    printf("            🎯 SUA MISSÃO SECRETA 🎯\n");
    printf("══════════════════════════════════════════════\n");
    printf("  %s\n", missao);
    printf("══════════════════════════════════════════════\n");
}

// --- Função para verificar se a missão foi cumprida ---
int verificarMissao(const char* missao, const struct Territorio* mapa, int tamanho) {
    // Lógica simples para verificar cada tipo de missão
    if (strcmp(missao, "Conquistar 3 territórios consecutivos") == 0) {
        // Verifica se existe uma cor com 3 territórios consecutivos no vetor
        int sequencia = 1;
        for (int i = 1; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, mapa[i-1].cor) == 0) {
                sequencia++;
                if (sequencia >= 3) return 1;
            } else {
                sequencia = 1;
            }
        }
        return 0;
    }
    else if (strcmp(missao, "Eliminar todas as tropas da cor vermelha") == 0) {
        // Verifica se não existem tropas vermelhas
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0 && mapa[i].tropas > 0) {
                return 0;
            }
        }
        return 1;
    }
    else if (strcmp(missao, "Conquistar 4 territórios no total") == 0) {
        // Conta quantos territórios o jogador controla (assumindo que o jogador é a cor azul)
        int count = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0) {
                count++;
            }
        }
        return (count >= 4);
    }
    else if (strcmp(missao, "Ter pelo menos 10 tropas em um único território") == 0) {
        // Verifica se existe algum território com 10 ou mais tropas
        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].tropas >= 10) {
                return 1;
            }
        }
        return 0;
    }
    else if (strcmp(missao, "Eliminar todas as tropas da cor azul") == 0) {
        // Verifica se não existem tropas azuis
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0 && mapa[i].tropas > 0) {
                return 0;
            }
        }
        return 1;
    }
    
    return 0;
}

// --- Função para cadastrar territórios ---
void cadastrarTerritorios(struct Territorio* mapa, int numTerritorios) {
    printf("\n============================================\n");
    printf("        --- CADASTRO DE TERRITÓRIOS ---         \n");
    printf("============================================\n");
    
    for (int i = 0; i < numTerritorios; i++) {
        printf("\n--- Território %d de %d ---\n", i + 1, numTerritorios);

        printf("Nome do território: ");
        fgets(mapa[i].nome, TAM_NOME, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do exército (ex: azul, vermelho): ");
        fgets(mapa[i].cor, TAM_COR, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        LimparBufferEntrada();
    }
}

// --- Função para exibir o mapa (agora com const para garantir que não modifica) ---
void exibirMapa(const struct Territorio* mapa, int numTerritorios) {
    printf("\n                  --- MAPA DE TERRITÓRIOS ---                  \n");
    printf("----------------------------------------------------------------\n");
    
    for (int i = 0; i < numTerritorios; i++) {
        printf("Território %d", i + 1);
        printf("\tNome: %s\t", mapa[i].nome);
        printf("\tCor: %s\t", mapa[i].cor);
        printf("\tTropas: %d\n", mapa[i].tropas);
    }
    printf("----------------------------------------------------------------\n");
}

// --- Função para validar se o ataque é permitido (agora com const) ---
int validarAtaque(const struct Territorio* atacante, const struct Territorio* defensor) {
    // Verifica se não é o mesmo território
    if (atacante == defensor) {
        printf("Erro: Não é possível atacar o próprio território!\n");
        return 0;
    }
    
    // Verifica se são de cores diferentes
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Erro: Não é possível atacar um território da mesma cor!\n");
        return 0;
    }
    
    // Verifica se o atacante tem tropas suficientes (precisa ter pelo menos 2 para atacar)
    if (atacante->tropas < 2) {
        printf("Erro: Território atacante precisa ter pelo menos 2 tropas para atacar!\n");
        return 0;
    }
    
    return 1;
}

// --- Função para exibir resultado do ataque (agora com const) ---
void exibirResultadoataque(const struct Territorio* atacante, const struct Territorio* defensor, int atacanteVenceu, int conquistou) {
    printf("\n=== RESULTADO DO ATAQUE ===\n");
    printf("Atacante: %s (%s) - %d tropas\n", atacante->nome, atacante->cor, atacante->tropas);
    printf("Defensor: %s (%s) - %d tropas\n", defensor->nome, defensor->cor, defensor->tropas);
    
    if (atacanteVenceu) {
        if (conquistou) {
            printf("\n🏆 VITÓRIA DO ATACANTE! TERRITÓRIO CONQUISTADO! 🏆\n");
            printf("O território %s agora é controlado por %s\n", defensor->nome, atacante->cor);
        } else {
            printf("\n⚔️ VITÓRIA NA BATALHA! ⚔️\n");
            printf("O defensor perdeu 1 tropa\n");
        }
    } else {
        printf("\n💔 DERROTA DO ATACANTE! 💔\n");
        printf("O atacante perdeu 1 tropa\n");
    }
}

// --- Função principal de ataque (CORRIGIDA) ---
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    // Validar se o ataque é permitido
    if (!validarAtaque(atacante, defensor)) {
        printf("Ataque inválido!\n");
        return;
    }
    
    printf("\n⚔️  BATALHA INICIADA ⚔️\n");
    printf("%s (%s) - %d tropas vs %s (%s) - %d tropas\n", 
           atacante->nome, atacante->cor, atacante->tropas,
           defensor->nome, defensor->cor, defensor->tropas);
    
    // Simular dados de batalha
    int dadoAtacante = rand() % 6 + 1;  // 1-6
    int dadoDefensor = rand() % 6 + 1;  // 1-6
    
    printf("\n🎲 Dados da batalha:\n");
    printf("Atacante rolou: %d\n", dadoAtacante);
    printf("Defensor rolou: %d\n", dadoDefensor);
    
    // Determinar resultado
    if (dadoAtacante > dadoDefensor) {
        // Atacante venceu a batalha - defensor perde 1 tropa
        defensor->tropas--;
        
        // Verifica se o defensor foi eliminado (tropas chegou a zero)
        if (defensor->tropas <= 0) {
            // Território conquistado!
            // Transfere a cor do atacante para o defensor
            strcpy(defensor->cor, atacante->cor);
            
            // Move 1 tropa do atacante para o novo território
            defensor->tropas = 1;
            atacante->tropas--;
            
            exibirResultadoataque(atacante, defensor, 1, 1); // Conquistou
        } else {
            // Vitória na batalha mas não conquistou o território
            exibirResultadoataque(atacante, defensor, 1, 0); // Não conquistou
        }
        
    } else {
        // Atacante perdeu a batalha - atacante perde 1 tropa
        atacante->tropas--;
        
        exibirResultadoataque(atacante, defensor, 0, 0);
    }
}

// --- Função para liberar memória alocada ---
void liberarMemoria(struct Territorio* mapa, char* missao) {
    if (mapa != NULL) {
        free(mapa);
        printf("Memória do mapa liberada com sucesso!\n");
    }
    if (missao != NULL) {
        free(missao);
        printf("Memória da missão liberada com sucesso!\n");
    }
}

// --- Função Principal (main) ---
int main() {
    // Inicializar gerador de números aleatórios
    srand(time(NULL));
    
    struct Territorio* mapa = NULL;
    char* missaoJogador = NULL;
    char* missoes[NUM_MISSOES];
    int numTerritorios = 0;
    int opcao;
    int venceu = 0;
    
    printf("============================================\n");
    printf("        --- JOGO DE BATALHA - RISK ---         \n");
    printf("============================================\n");
    
    // Inicializar vetor de missões
    inicializarMissoes(missoes);
    
    // Solicitar número de territórios
    do {
        printf("\nDigite o número de territórios (mínimo 2): ");
        scanf("%d", &numTerritorios);
        LimparBufferEntrada();
        
        if (numTerritorios < 2) {
            printf("Erro: É necessário pelo menos 2 territórios para jogar!\n");
        }
    } while (numTerritorios < 2);
    
    // Alocação dinâmica de memória para os territórios
    mapa = (struct Territorio*) calloc(numTerritorios, sizeof(struct Territorio));
    
    if (mapa == NULL) {
        printf("Erro fatal: Falha na alocação de memória do mapa!\n");
        return 1;
    }
    
    // Alocação dinâmica de memória para a missão do jogador
    missaoJogador = (char*) malloc(TAM_STRING * sizeof(char));
    if (missaoJogador == NULL) {
        printf("Erro fatal: Falha na alocação de memória da missão!\n");
        free(mapa);
        return 1;
    }
    
    // Cadastrar territórios
    cadastrarTerritorios(mapa, numTerritorios);
    
    // Sortear e atribuir missão ao jogador
    atribuirMissao(missaoJogador, missoes, NUM_MISSOES);
    
    // Exibir missão ao jogador (apenas uma vez no início)
    exibirMissao(missaoJogador);
    
    // Loop principal do jogo
    do {
        printf("\n============================================\n");
        printf("--- MENU PRINCIPAL ---\n");
        printf("1 - Exibir mapa\n");
        printf("2 - Realizar ataque\n");
        printf("3 - Cadastrar novos territórios\n");
        printf("4 - Verificar missão\n");
        printf("0 - Sair do jogo\n");
        printf("Escolha uma opção: ");
        
        scanf("%d", &opcao);
        LimparBufferEntrada();
        
        switch(opcao) {
            case 1:
                exibirMapa(mapa, numTerritorios);
                printf("Pressione ENTER para continuar...\n");
                getchar();
                break;
                
            case 2: {
                int atacanteIdx, defensorIdx;
                
                printf("\n--- SELECIONAR ATAQUE ---\n");
                exibirMapa(mapa, numTerritorios);
                
                printf("\nEscolha o território ATACANTE (1-%d): ", numTerritorios);
                scanf("%d", &atacanteIdx);
                printf("Escolha o território DEFENSOR (1-%d): ", numTerritorios);
                scanf("%d", &defensorIdx);
                LimparBufferEntrada();
                
                // Converter para índices do vetor (0-based)
                atacanteIdx--;
                defensorIdx--;
                
                // Validar índices
                if (atacanteIdx >= 0 && atacanteIdx < numTerritorios && 
                    defensorIdx >= 0 && defensorIdx < numTerritorios) {
                    
                    atacar(&mapa[atacanteIdx], &mapa[defensorIdx]);
                    
                    // Verificar se a missão foi cumprida após o ataque
                    if (verificarMissao(missaoJogador, mapa, numTerritorios)) {
                        venceu = 1;
                    }
                    
                } else {
                    printf("Erro: Índices de território inválidos!\n");
                }
                
                printf("\nPressione ENTER para continuar...");
                getchar();
                break;
            }
            
            case 3: {
                int novoNum;
                printf("\nDigite o novo número de territórios: ");
                scanf("%d", &novoNum);
                LimparBufferEntrada();
                
                if (novoNum > 0) {
                    // Realocar memória
                    struct Territorio* novoMapa = (struct Territorio*) realloc(mapa, novoNum * sizeof(struct Territorio));
                    
                    if (novoMapa != NULL) {
                        mapa = novoMapa;
                        
                        if (novoNum > numTerritorios) {
                            // Cadastrar apenas os novos territórios
                            for (int i = numTerritorios; i < novoNum; i++) {
                                printf("\n--- Novo Território %d ---\n", i + 1);
                                printf("Nome: ");
                                fgets(mapa[i].nome, TAM_NOME, stdin);
                                mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';
                                
                                printf("Cor: ");
                                fgets(mapa[i].cor, TAM_COR, stdin);
                                mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';
                                
                                printf("Tropas: ");
                                scanf("%d", &mapa[i].tropas);
                                LimparBufferEntrada();
                            }
                        }
                        
                        numTerritorios = novoNum;
                        printf("Territórios atualizados com sucesso!\n");
                    } else {
                        printf("Erro na realocação de memória!\n");
                    }
                }
                break;
            }
            
            case 4:
                if (verificarMissao(missaoJogador, mapa, numTerritorios)) {
                    printf("\n🎉 PARABÉNS! SUA MISSÃO FOI CUMPRIDA! 🎉\n");
                    venceu = 1;
                } else {
                    printf("\n⏳ Sua missão ainda não foi cumprida...\n");
                }
                exibirMissao(missaoJogador);
                printf("Pressione ENTER para continuar...\n");
                getchar();
                break;
            
            case 0:
                printf("\nSaindo do jogo...\n");
                break;
                
            default:
                printf("Opção inválida!\n");
        }
        
        // Verificar vitória
        if (venceu) {
            printf("\n══════════════════════════════════════════════\n");
            printf("       🏆 VOCÊ VENCEU O JOGO! 🏆\n");
            printf("══════════════════════════════════════════════\n");
            printf("Sua missão foi cumprida com sucesso!\n");
            printf("Pressione ENTER para sair...\n");
            getchar();
            opcao = 0;  // Encerra o jogo
        }
        
    } while (opcao != 0);
    
    // Liberar memória alocada
    liberarMemoria(mapa, missaoJogador);
    
    return 0;
}