#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct Territorio
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Definição da struct Missao
typedef struct {
    int tipo;           // 1: Destruir exército, 2: Conquistar territórios
    char alvo[10];      // Cor do exército a destruir
    int quantidade;     // Quantidade de territórios a conquistar
    int conquistados;   // Territórios já conquistados
} Missao;

// Definição da struct Jogo
typedef struct {
    Territorio *territorios;
    Missao missao_atual;
    int quantidade_territorios;
    int rodada;
} Jogo;

// Protótipos das funções
void inicializarJogo(Jogo *jogo, int quantidade);
void liberarJogo(Jogo *jogo);
void atribuirMissao(Jogo *jogo);
void exibirMenu();
void executarAtaque(Jogo *jogo);
void verificarMissao(const Jogo *jogo);
void exibirMapa(const Jogo *jogo);
void exibirStatus(const Jogo *jogo);
int validarEscolha(int escolha, int max);
int simularBatalha(Territorio *atacante, Territorio *defensor);
int verificarVitoria(const Jogo *jogo);
void inicializarTerritoriosAutomatico(Jogo *jogo);

int main() {
    srand(time(NULL));
    
    Jogo jogo;
    int quantidade;
    
    printf("=== SISTEMA ESTRATEGICO DE BATALHAS ===\n\n");
    
    printf("Digite a quantidade de territorios (4-8): ");
    scanf("%d", &quantidade);
    
    if (quantidade < 4 || quantidade > 8) {
        printf("Quantidade invalida! Usando valor padrao: 6\n");
        quantidade = 6;
    }
    
    // Inicializar jogo
    inicializarJogo(&jogo, quantidade);
    
    int opcao;
    do {
        exibirStatus(&jogo);
        exibirMenu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                executarAtaque(&jogo);
                break;
            case 2:
                verificarMissao(&jogo);
                break;
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
        
        // Verificar se missão foi cumprida
        if (verificarVitoria(&jogo)) {
            printf("\n🎉 PARABENS! MISSAO CUMPRIDA! 🎉\n");
            printf("Voce venceu o jogo na rodada %d!\n", jogo.rodada);
            break;
        }
        
        jogo.rodada++;
        
    } while (opcao != 0);
    
    liberarJogo(&jogo);
    printf("\nJogo finalizado. Obrigado por jogar!\n");
    
    return 0;
}

// Inicializar estrutura do jogo
void inicializarJogo(Jogo *jogo, int quantidade) {
    jogo->quantidade_territorios = quantidade;
    jogo->rodada = 1;
    
    // Alocação dinâmica dos territórios
    jogo->territorios = (Territorio*)calloc(quantidade, sizeof(Territorio));
    if (jogo->territorios == NULL) {
        printf("Erro na alocacao de memoria!\n");
        exit(1);
    }
    
    // Inicializar territórios automaticamente
    inicializarTerritoriosAutomatico(jogo);
    
    // Atribuir missão aleatória
    atribuirMissao(jogo);
}

// Liberar memória alocada
void liberarJogo(Jogo *jogo) {
    free(jogo->territorios);
}

// Inicializar territórios automaticamente
void inicializarTerritoriosAutomatico(Jogo *jogo) {
    const char *nomes[] = {"Brasil", "Argentina", "Chile", "Peru", "Colombia", "Venezuela", "Uruguai", "Paraguai"};
    const char *cores[] = {"Verde", "Vermelho", "Azul", "Amarelo", "Roxo", "Laranja"};
    
    for (int i = 0; i < jogo->quantidade_territorios; i++) {
        strcpy(jogo->territorios[i].nome, nomes[i]);
        strcpy(jogo->territorios[i].cor, cores[rand() % 6]);
        jogo->territorios[i].tropas = (rand() % 5) + 3; // 3-7 tropas
    }
}

// Atribuir missão aleatória
void atribuirMissao(Jogo *jogo) {
    jogo->missao_atual.tipo = (rand() % 2) + 1; // 1 ou 2
    
    const char *cores[] = {"Verde", "Vermelho", "Azul", "Amarelo", "Roxo"};
    
    if (jogo->missao_atual.tipo == 1) {
        // Missão: Destruir exército específico
        strcpy(jogo->missao_atual.alvo, cores[rand() % 5]);
        jogo->missao_atual.quantidade = 0;
        jogo->missao_atual.conquistados = 0;
        
        printf("\n🎯 MISSAO ATRIBUIDA: Destruir o exercito %s!\n", jogo->missao_atual.alvo);
    } else {
        // Missão: Conquistar X territórios
        jogo->missao_atual.quantidade = (rand() % 3) + 2; // 2-4 territórios
        jogo->missao_atual.conquistados = 0;
        jogo->missao_atual.alvo[0] = '\0';
        
        printf("\n🎯 MISSAO ATRIBUIDA: Conquistar %d territorios!\n", jogo->missao_atual.quantidade);
    }
}

// Exibir menu principal
void exibirMenu() {
    printf("\n=== MENU PRINCIPAL ===\n");
    printf("1 - Atacar\n");
    printf("2 - Verificar Missao\n");
    printf("0 - Sair\n");
    printf("======================\n");
}

// Exibir status atual do jogo
void exibirStatus(const Jogo *jogo) {
    printf("\n=== RODADA %d ===\n", jogo->rodada);
    exibirMapa(jogo);
}

// Exibir mapa de territórios
void exibirMapa(const Jogo *jogo) {
    printf("\n🗺️  MAPA DE TERRITORIOS:\n");
    printf("------------------------\n");
    
    for (int i = 0; i < jogo->quantidade_territorios; i++) {
        printf("%d. %-12s %-10s %d tropas", 
               i + 1, 
               jogo->territorios[i].nome, 
               jogo->territorios[i].cor, 
               jogo->territorios[i].tropas);
        
        if (jogo->territorios[i].tropas <= 0) {
            printf(" [ELIMINADO]");
        }
        printf("\n");
    }
}

// Executar ataque entre territórios
void executarAtaque(Jogo *jogo) {
    printf("\n⚔️  FASE DE ATAQUE\n");
    
    int atacante_idx, defensor_idx;
    
    // Escolher atacante
    printf("Escolha o territorio ATACANTE (1-%d): ", jogo->quantidade_territorios);
    scanf("%d", &atacante_idx);
    
    while (!validarEscolha(atacante_idx, jogo->quantidade_territorios) || 
           jogo->territorios[atacante_idx-1].tropas <= 1) {
        if (jogo->territorios[atacante_idx-1].tropas <= 1) {
            printf("Precisa de pelo menos 2 tropas! Escolha outro: ");
        } else {
            printf("Invalido! Escolha (1-%d): ", jogo->quantidade_territorios);
        }
        scanf("%d", &atacante_idx);
    }
    
    // Escolher defensor
    printf("Escolha o territorio DEFENSOR (1-%d): ", jogo->quantidade_territorios);
    scanf("%d", &defensor_idx);
    
    while (!validarEscolha(defensor_idx, jogo->quantidade_territorios) || 
           defensor_idx == atacante_idx || 
           jogo->territorios[defensor_idx-1].tropas <= 0) {
        if (defensor_idx == atacante_idx) {
            printf("Nao pode atacar a si mesmo! Escolha outro: ");
        } else if (jogo->territorios[defensor_idx-1].tropas <= 0) {
            printf("Territorio eliminado! Escolha outro: ");
        } else {
            printf("Invalido! Escolha (1-%d): ", jogo->quantidade_territorios);
        }
        scanf("%d", &defensor_idx);
    }
    
    atacante_idx--;
    defensor_idx--;
    
    Territorio *atacante = &jogo->territorios[atacante_idx];
    Territorio *defensor = &jogo->territorios[defensor_idx];
    
    printf("\n🎯 BATALHA: %s (%s) vs %s (%s)\n", 
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    
    int resultado = simularBatalha(atacante, defensor);
    
    // Atualizar missão se necessário
    if (resultado == 1 && defensor->tropas <= 0) {
        jogo->missao_atual.conquistados++;
        printf("✅ Territorio conquistado! Progresso: %d/%d\n", 
               jogo->missao_atual.conquistados, jogo->missao_atual.quantidade);
    }
}

// Simular batalha entre dois territórios
int simularBatalha(Territorio *atacante, Territorio *defensor) {
    int dado_ataque = (rand() % 6) + 1;
    int dado_defesa = (rand() % 6) + 1;
    
    printf("🎲 Dado de ataque: %d\n", dado_ataque);
    printf("🎲 Dado de defesa: %d\n", dado_defesa);
    
    int conquistado = 0;
    
    if (dado_ataque > dado_defesa) {
        defensor->tropas--;
        printf("✅ VITORIA DO ATACANTE!\n");
        printf("%s perde 1 tropa.\n", defensor->nome);
        
        if (defensor->tropas <= 0) {
            printf("🎯 %s CONQUISTADO!\n", defensor->nome);
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = 1;
            atacante->tropas--;
            conquistado = 1;
        }
    } else if (dado_ataque < dado_defesa) {
        atacante->tropas--;
        printf("❌ VITORIA DO DEFENSOR!\n");
        printf("%s perde 1 tropa.\n", atacante->nome);
    } else {
        defensor->tropas--;
        printf("⚔️ EMPATE! (favorece atacante)\n");
        printf("%s perde 1 tropa.\n", defensor->nome);
        
        if (defensor->tropas <= 0) {
            printf("🎯 %s CONQUISTADO!\n", defensor->nome);
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = 1;
            atacante->tropas--;
            conquistado = 1;
        }
    }
    
    printf("\n📊 POS-BATALHA:\n");
    printf("Atacante %s: %d tropas\n", atacante->nome, atacante->tropas);
    printf("Defensor %s: %d tropas\n", defensor->nome, defensor->tropas);
    
    return conquistado;
}

// Verificar status da missão
void verificarMissao(const Jogo *jogo) {
    printf("\n📋 VERIFICAR MISSAO\n");
    printf("===================\n");
    
    if (jogo->missao_atual.tipo == 1) {
        printf("MISSAO: Destruir o exercito %s\n", jogo->missao_atual.alvo);
        
        int territorios_restantes = 0;
        for (int i = 0; i < jogo->quantidade_territorios; i++) {
            if (strcmp(jogo->territorios[i].cor, jogo->missao_atual.alvo) == 0 && 
                jogo->territorios[i].tropas > 0) {
                territorios_restantes++;
            }
        }
        
        printf("Territorios restantes do exercito %s: %d\n", jogo->missao_atual.alvo, territorios_restantes);
        
        if (territorios_restantes == 0) {
            printf("✅ MISSAO CUMPRIDA!\n");
        } else {
            printf("⏳ Missao em andamento...\n");
        }
        
    } else {
        printf("MISSAO: Conquistar %d territorios\n", jogo->missao_atual.quantidade);
        printf("Progresso: %d/%d territorios conquistados\n", 
               jogo->missao_atual.conquistados, jogo->missao_atual.quantidade);
        
        if (jogo->missao_atual.conquistados >= jogo->missao_atual.quantidade) {
            printf("✅ MISSAO CUMPRIDA!\n");
        } else {
            printf("⏳ Faltam %d territorios\n", 
                   jogo->missao_atual.quantidade - jogo->missao_atual.conquistados);
        }
    }
}

// Verificar se missão foi cumprida
int verificarVitoria(const Jogo *jogo) {
    if (jogo->missao_atual.tipo == 1) {
        // Verificar se exército alvo foi destruído
        for (int i = 0; i < jogo->quantidade_territorios; i++) {
            if (strcmp(jogo->territorios[i].cor, jogo->missao_atual.alvo) == 0 && 
                jogo->territorios[i].tropas > 0) {
                return 0; // Ainda há territórios do exército alvo
            }
        }
        return 1; // Todos os territórios do exército alfo destruídos
    } else {
        // Verificar se conquistou territórios suficientes
        return (jogo->missao_atual.conquistados >= jogo->missao_atual.quantidade);
    }
}

// Validar escolha do usuário
int validarEscolha(int escolha, int max) {
    return (escolha >= 1 && escolha <= max);
}