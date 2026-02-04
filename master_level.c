#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TROOP 5

typedef struct{
    char name[30];
    char color[10];
    int troop;
} Territorio;

typedef enum {
    DESTRUIR_COR,      // Destruir exército de uma cor específica
    CONQUISTAR_N       // Conquistar N territórios
} TipoMissao;

typedef struct {
    TipoMissao tipo;
    char corAlvo[10];  // Para missão DESTRUIR_COR
    int numTerritorios; // Para missão CONQUISTAR_N
    int territoriosConquistados;
} Missao;

void limparBufferEntrada(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ============= FUNÇÕES DE INICIALIZAÇÃO =============

void inicializarTerritorios(Territorio *territory, int *totalTerritorio){
    strcpy(territory[0].name, "Brasil");
    strcpy(territory[0].color, "Verde");
    territory[0].troop = 5;
    
    strcpy(territory[1].name, "Argentina");
    strcpy(territory[1].color, "Azul");
    territory[1].troop = 4;
    
    strcpy(territory[2].name, "Chile");
    strcpy(territory[2].color, "Vermelho");
    territory[2].troop = 3;
    
    strcpy(territory[3].name, "Peru");
    strcpy(territory[3].color, "Amarelo");
    territory[3].troop = 4;
    
    strcpy(territory[4].name, "Colombia");
    strcpy(territory[4].color, "Verde");
    territory[4].troop = 3;
    
    *totalTerritorio = MAX_TROOP;
}

void atribuirMissao(Missao *missao){
    int tipoAleatorio = rand() % 2;
    
    if(tipoAleatorio == 0){
        missao->tipo = DESTRUIR_COR;
        strcpy(missao->corAlvo, "Verde");
        printf("\n🎯 MISSÃO ATRIBUÍDA: Destruir todos os exércitos VERDES!\n");
    } else {
        missao->tipo = CONQUISTAR_N;
        missao->numTerritorios = 3;
        missao->territoriosConquistados = 0;
        printf("\n🎯 MISSÃO ATRIBUÍDA: Conquistar 3 territórios!\n");
    }
}

// ============= FUNÇÕES DE EXIBIÇÃO =============

void exibirTerritorios(const Territorio *territory, int totalTerritorio){
    printf("\n╔════════════════════════════════════╗\n");
    printf("║     TERRITÓRIOS CADASTRADOS        ║\n");
    printf("╚════════════════════════════════════╝\n");
    for(int i = 0; i < totalTerritorio; i++){
        printf("[%d] %-15s | %-10s | %2d tropas\n", 
               i+1, territory[i].name, territory[i].color, territory[i].troop);
    }
    printf("\n");
}

void exibirMissao(const Missao *missao){
    printf("\n┌────────────────────────────────────┐\n");
    printf("│         SUA MISSÃO ATUAL           │\n");
    printf("└────────────────────────────────────┘\n");
    
    if(missao->tipo == DESTRUIR_COR){
        printf("🎯 Destruir todos os exércitos %s\n", missao->corAlvo);
    } else {
        printf("🎯 Conquistar %d territórios\n", missao->numTerritorios);
        printf("   Progresso: %d/%d\n", missao->territoriosConquistados, missao->numTerritorios);
    }
    printf("\n");
}

// ============= FUNÇÕES DE VERIFICAÇÃO =============

int verificarCorEliminada(const Territorio *territory, int totalTerritorio, const char *cor){
    for(int i = 0; i < totalTerritorio; i++){
        if(strcmp(territory[i].color, cor) == 0 && territory[i].troop > 0){
            return 0; // Cor ainda existe
        }
    }
    return 1; // Cor eliminada
}

int verificarMissao(const Territorio *territory, int totalTerritorio, const Missao *missao){
    if(missao->tipo == DESTRUIR_COR){
        if(verificarCorEliminada(territory, totalTerritorio, missao->corAlvo)){
            printf("\n🎊 PARABÉNS! Você eliminou todos os exércitos %s!\n", missao->corAlvo);
            printf("🏆 MISSÃO CUMPRIDA! Você venceu o jogo!\n\n");
            return 1;
        } else {
            printf("\n⏳ A cor %s ainda possui territórios.\n", missao->corAlvo);
            printf("   Continue atacando!\n\n");
            return 0;
        }
    } else { // CONQUISTAR_N
        if(missao->territoriosConquistados >= missao->numTerritorios){
            printf("\n🎊 PARABÉNS! Você conquistou %d territórios!\n", missao->numTerritorios);
            printf("🏆 MISSÃO CUMPRIDA! Você venceu o jogo!\n\n");
            return 1;
        } else {
            printf("\n⏳ Progresso: %d/%d territórios conquistados.\n", 
                   missao->territoriosConquistados, missao->numTerritorios);
            printf("   Continue conquistando!\n\n");
            return 0;
        }
    }
}

// ============= FUNÇÕES DE COMBATE =============

// Função para rolar um dado de 6 lados
int rolarDado(){
    return (rand() % 6) + 1;
}

// Função para simular ataque entre territórios
void simularAtaque(Territorio *territory, int atacante, int defensor, Missao *missao){
    if(territory[atacante].troop <= 1){
        printf("\n❌ Erro: O território atacante precisa ter pelo menos 2 tropas!\n");
        return;
    }
    
    if(territory[defensor].troop <= 0){
        printf("\n❌ Erro: O território defensor não possui tropas!\n");
        return;
    }
    
    printf("\n⚔️  BATALHA! ⚔️\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("Atacante: %s (%s) - %d tropas\n", 
           territory[atacante].name, territory[atacante].color, territory[atacante].troop);
    printf("Defensor: %s (%s) - %d tropas\n", 
           territory[defensor].name, territory[defensor].color, territory[defensor].troop);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    // Rolar dados
    int dadoAtaque = rolarDado();
    int dadoDefesa = rolarDado();
    
    printf("\n🎲 Dados rolados:\n");
    printf("   Ataque: %d\n", dadoAtaque);
    printf("   Defesa: %d\n", dadoDefesa);
    printf("\n");
    
    // Resolver batalha (empate favorece atacante)
    if(dadoAtaque >= dadoDefesa){
        territory[defensor].troop--;
        printf("✅ ATACANTE VENCEU!\n");
        printf("   %s perde 1 tropa!\n", territory[defensor].name);
        
        // Verificar se território foi conquistado
        if(territory[defensor].troop == 0){
            printf("\n🏆 TERRITÓRIO CONQUISTADO!\n");
            printf("   %s conquistou %s!\n", territory[atacante].name, territory[defensor].name);
            
            // Transferir 1 tropa para o território conquistado
            territory[atacante].troop--;
            territory[defensor].troop = 1;
            strcpy(territory[defensor].color, territory[atacante].color);
            printf("   1 tropa foi movida para o território conquistado.\n");
            
            // Atualizar progresso da missão
            if(missao->tipo == CONQUISTAR_N){
                missao->territoriosConquistados++;
                printf("   📈 Progresso da missão: %d/%d territórios conquistados\n", 
                       missao->territoriosConquistados, missao->numTerritorios);
            }
        }
    } else {
        territory[atacante].troop--;
        printf("🛡️  DEFENSOR VENCEU!\n");
        printf("   %s perde 1 tropa!\n", territory[atacante].name);
    }
    
    printf("\n📊 Resultado:\n");
    printf("   %s: %d tropas\n", territory[atacante].name, territory[atacante].troop);
    printf("   %s: %d tropas\n", territory[defensor].name, territory[defensor].troop);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
}

void executarAtaque(Territorio *territory, int totalTerritorio, Missao *missao){
    exibirTerritorios(territory, totalTerritorio);
    
    int atacante, defensor;
    printf("Escolha o território ATACANTE (1-%d): ", totalTerritorio);
    scanf("%d", &atacante);
    limparBufferEntrada();
    
    printf("Escolha o território DEFENSOR (1-%d): ", totalTerritorio);
    scanf("%d", &defensor);
    limparBufferEntrada();
    
    // Validar entrada
    if(atacante < 1 || atacante > totalTerritorio || 
       defensor < 1 || defensor > totalTerritorio){
        printf("\n❌ Territórios inválidos!\n");
    } else if(atacante == defensor){
        printf("\n❌ Um território não pode atacar a si mesmo!\n");
    } else {
        // Converter para índice do array (0-based)
        simularAtaque(territory, atacante-1, defensor-1, missao);
    }
}

// ============= MENU E CONTROLE =============

void exibirMenu(){
    printf("╔════════════════════════════════════╗\n");
    printf("║         MENU PRINCIPAL             ║\n");
    printf("╠════════════════════════════════════╣\n");
    printf("║  1 - Atacar                        ║\n");
    printf("║  2 - Verificar Missão              ║\n");
    printf("║  0 - Sair                          ║\n");
    printf("╚════════════════════════════════════╝\n");
    printf("Escolha uma opção: ");
}

int main(){
    // Alocar memória dinamicamente com calloc
    Territorio *territory = (Territorio*) calloc(MAX_TROOP, sizeof(Territorio));
    
    if(territory == NULL){
        printf("Erro ao alocar memória!\n");
        return 1;
    }
    
    // Inicializar gerador de números aleatórios
    srand(time(NULL));
    
    int totalTerritorio = 0;
    Missao missao;
    int option;
    int jogoAtivo = 1;

    // Cabeçalho do jogo
    printf("\n");
    printf("╔════════════════════════════════════════════╗\n");
    printf("║                                            ║\n");
    printf("║        🎮 WAR GAME - Part III 🎮          ║\n");
    printf("║           Missão de Conquista             ║\n");
    printf("║                                            ║\n");
    printf("╚════════════════════════════════════════════╝\n");
    printf("\n");
    
    // Inicializar territórios automaticamente
    printf("🌍 Inicializando mapa do jogo...\n");
    inicializarTerritorios(territory, &totalTerritorio);
    printf("✅ %d territórios inicializados!\n", totalTerritorio);
    
    // Atribuir missão aleatória
    atribuirMissao(&missao);
    
    printf("\nPressione Enter para começar...");
    getchar();

    // Loop principal do jogo
    do {     
        printf("\n");
        exibirTerritorios(territory, totalTerritorio);
        exibirMissao(&missao);
        exibirMenu();
        
        scanf("%d", &option);
        limparBufferEntrada();

        switch (option){
            case 1: // Atacar
                printf("\n=== FASE DE ATAQUE ===\n");
                executarAtaque(territory, totalTerritorio, &missao);
                printf("\nPressione Enter para continuar...");
                getchar();
                break;

            case 2: // Verificar Missão
                printf("\n=== VERIFICAÇÃO DE MISSÃO ===\n");
                if(verificarMissao(territory, totalTerritorio, &missao)){
                    jogoAtivo = 0; // Jogador venceu
                }
                printf("Pressione Enter para continuar...");
                getchar();
                break;

            case 0: // Sair
                printf("\n👋 Saindo do jogo...\n");
                jogoAtivo = 0;
                break;

            default:
                printf("\n❌ Opção inválida. Tente novamente.\n");
                printf("Pressione Enter para continuar...");
                getchar();
                break;
        }

    } while (jogoAtivo);

    // Liberar memória alocada
    free(territory);
    
    printf("\n╔════════════════════════════════════════════╗\n");
    printf("║   Obrigado por jogar WAR GAME Part III!   ║\n");
    printf("╚════════════════════════════════════════════╝\n\n");
    
    return 0;
}
