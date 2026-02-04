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

void limparBufferEntrada(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para rolar um dado de 6 lados
int rolarDado(){
    return (rand() % 6) + 1;
}

// Função para simular ataque entre territórios
void simularAtaque(Territorio *territory, int atacante, int defensor){
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
    int option;

        printf("======================\n");
        printf("    WAR GAME - Part II\n");
        printf("======================\n");

    do {     

        
        // Exibir tropas cadastradas
        if(totalTerritorio > 0) {
            printf("======================\n");
            printf("\nTROPAS CADASTRADAS:\n");
            printf("======================\n");
            for(int i = 0; i < totalTerritorio; i++) {
                printf("%s - %s - %d \n", 
                    territory[i].name, territory[i].color, territory[i].troop);
            }
            printf("\n");
        } else {
            printf("\nNenhuma tropa cadastrada ainda.\n\n");
        }
        
        printf("======================\n");
        printf("1 - Cadastrar Tropa \n");
        printf("2 - Simular Ataque\n");
        printf("0 - Para sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &option);
        limparBufferEntrada();

    switch (option){
        case 1:
            printf("\n=== Cadastrar Nova Tropa ===\n");

            if(totalTerritorio < MAX_TROOP) {
                printf("Digite o nome do território: ");
                fgets(territory[totalTerritorio].name, 30, stdin);
                territory[totalTerritorio].name[strcspn(territory[totalTerritorio].name, "\n")] = 0;

                printf("Digite a cor da tropa: ");
                fgets(territory[totalTerritorio].color, 10, stdin);
                territory[totalTerritorio].color[strcspn(territory[totalTerritorio].color, "\n")] = 0;

                printf("Digite o número de tropas: ");
                scanf("%d", &territory[totalTerritorio].troop);
                limparBufferEntrada();

                if(territory[totalTerritorio].troop <= 0) {
                    printf("\nErro: O número de tropas deve ser maior que zero.\n");
                } else {
                    totalTerritorio++;
                    printf("\n✓ Tropa cadastrada com sucesso!\n");
                }
            } else {
                printf("\nLimite máximo de territórios atingido.\n");
            }
            printf("\nPressione Enter para continuar...");
            getchar();
            break;

        case 2:
            printf("\n=== Simular Ataque ===\n");
            
            if(totalTerritorio < 2){
                printf("\n❌ É necessário ter pelo menos 2 territórios cadastrados!\n");
            } else {
                printf("\nTerritórios disponíveis:\n");
                for(int i = 0; i < totalTerritorio; i++){
                    printf("[%d] %s (%s) - %d tropas\n", 
                           i+1, territory[i].name, territory[i].color, territory[i].troop);
                }
                
                int atacante, defensor;
                printf("\nEscolha o território ATACANTE (1-%d): ", totalTerritorio);
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
                    simularAtaque(territory, atacante-1, defensor-1);
                }
            }
            
            printf("\nPressione Enter para continuar...");
            getchar();
            break;

        case 0:
            printf("Saindo do programa...\n");
            break;

        default:
            printf("\nOpção inválida. Tente novamente.\n");
            printf("Pressione Enter para continuar...");
            getchar();
            break;
    }

    } while (option != 0);

    // Liberar memória alocada
    free(territory);
    
    printf("\n👋 Obrigado por jogar WAR GAME!\n");
    
    return 0;
}
