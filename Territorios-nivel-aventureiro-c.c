#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct Territorio
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// Protótipos das funções
void cadastrarTerritorios(struct Territorio *territorios, int quantidade);
void exibirTerritorios(struct Territorio *territorios, int quantidade);
void simularAtaque(struct Territorio *atacante, struct Territorio *defensor);
int validarEscolha(int escolha, int quantidade);

int main() {
    // Inicializar gerador de números aleatórios
    srand(time(NULL));
    
    int quantidade;
    printf("=== SISTEMA DE BATALHAS ESTRATEGICAS ===\n\n");
    
    // Solicitar quantidade de territórios
    printf("Digite a quantidade de territorios: ");
    scanf("%d", &quantidade);
    
    // Alocação dinâmica com calloc
    struct Territorio *territorios = (struct Territorio*)calloc(quantidade, sizeof(struct Territorio));
    
    if (territorios == NULL) {
        printf("Erro na alocacao de memoria!\n");
        return 1;
    }
    
    // Cadastro dos territórios
    cadastrarTerritorios(territorios, quantidade);
    
    // Exibir territórios cadastrados
    exibirTerritorios(territorios, quantidade);
    
    // Fase de batalhas
    printf("=== FASE DE BATALHAS ===\n\n");
    
    int continuar = 1;
    while (continuar) {
        int atacante_idx, defensor_idx;
        
        // Escolha do território atacante
        printf("Escolha o territorio ATACANTE (1 a %d): ", quantidade);
        scanf("%d", &atacante_idx);
        
        while (!validarEscolha(atacante_idx, quantidade) || territorios[atacante_idx-1].tropas <= 1) {
            if (territorios[atacante_idx-1].tropas <= 1) {
                printf("Territorio precisa de pelo menos 2 tropas para atacar! Escolha outro: ");
            } else {
                printf("Escolha invalida! Digite um numero entre 1 e %d: ", quantidade);
            }
            scanf("%d", &atacante_idx);
        }
        
        // Escolha do território defensor
        printf("Escolha o territorio DEFENSOR (1 a %d, diferente do atacante): ", quantidade);
        scanf("%d", &defensor_idx);
        
        while (!validarEscolha(defensor_idx, quantidade) || defensor_idx == atacante_idx) {
            if (defensor_idx == atacante_idx) {
                printf("Nao pode atacar a si mesmo! Escolha outro: ");
            } else {
                printf("Escolha invalida! Digite um numero entre 1 e %d: ", quantidade);
            }
            scanf("%d", &defensor_idx);
        }
        
        // Ajustar índices para base 0
        atacante_idx--;
        defensor_idx--;
        
        printf("\n=== BATALHA ===\n");
        printf("ATACANTE: %s (%s) - %d tropas\n", 
               territorios[atacante_idx].nome, 
               territorios[atacante_idx].cor, 
               territorios[atacante_idx].tropas);
        printf("DEFENSOR: %s (%s) - %d tropas\n\n", 
               territorios[defensor_idx].nome, 
               territorios[defensor_idx].cor, 
               territorios[defensor_idx].tropas);
        
        // Simular batalha
        simularAtaque(&territorios[atacante_idx], &territorios[defensor_idx]);
        
        // Exibir situação após a batalha
        printf("\n=== SITUACAO POS-BATALHA ===\n");
        exibirTerritorios(territorios, quantidade);
        
        // Verificar se há territórios para continuar batalhas
        int territorios_ativos = 0;
        for (int i = 0; i < quantidade; i++) {
            if (territorios[i].tropas > 0) {
                territorios_ativos++;
            }
        }
        
        if (territorios_ativos <= 1) {
            printf("\n=== FIM DO JOGO ===\n");
            printf("Apenas um territorio restante!\n");
            continuar = 0;
        } else {
            printf("\nDeseja continuar as batalhas? (1 - Sim, 0 - Nao): ");
            scanf("%d", &continuar);
        }
    }
    
    // Liberar memória alocada
    free(territorios);
    printf("\nMemoria liberada. Fim do programa.\n");
    
    return 0;
}

// Função para cadastrar territórios
void cadastrarTerritorios(struct Territorio *territorios, int quantidade) {
    printf("\n=== CADASTRO DE %d TERRITORIOS ===\n\n", quantidade);
    
    for (int i = 0; i < quantidade; i++) {
        printf("--- Territorio %d ---\n", i + 1);
        
        printf("Nome: ");
        scanf("%29s", territorios[i].nome);
        
        printf("Cor do exercito: ");
        scanf("%9s", territorios[i].cor);
        
        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        
        printf("\n");
    }
}

// Função para exibir territórios
void exibirTerritorios(struct Territorio *territorios, int quantidade) {
    printf("=== MAPA DE TERRITORIOS ===\n\n");
    
    for (int i = 0; i < quantidade; i++) {
        printf("%d. %s (%s) - %d tropas", 
               i + 1, 
               territorios[i].nome, 
               territorios[i].cor, 
               territorios[i].tropas);
        
        if (territorios[i].tropas <= 0) {
            printf(" [ELIMINADO]");
        }
        printf("\n");
    }
    printf("\n");
}

// Função para simular ataque
void simularAtaque(struct Territorio *atacante, struct Territorio *defensor) {
    // Sortear dados de ataque (1-6) e defesa (1-6)
    int dado_ataque = (rand() % 6) + 1;
    int dado_defesa = (rand() % 6) + 1;
    
    printf("Dado de ataque: %d\n", dado_ataque);
    printf("Dado de defesa: %d\n", dado_defesa);
    
    // Lógica da batalha
    if (dado_ataque > dado_defesa) {
        // Atacante vence
        defensor->tropas--;
        printf("\n✅ VITORIA DO ATACANTE!\n");
        printf("%s perde 1 tropa.\n", defensor->nome);
        
        if (defensor->tropas <= 0) {
            printf("🎯 %s foi CONQUISTADO por %s!\n", defensor->nome, atacante->nome);
            // Transferir propriedade (opcional)
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = 1; // Território conquistado recebe 1 tropa
            atacante->tropas--; // Atacante perde 1 tropa para ocupar
        }
    } else if (dado_ataque < dado_defesa) {
        // Defensor vence
        atacante->tropas--;
        printf("\n❌ VITORIA DO DEFENSOR!\n");
        printf("%s perde 1 tropa.\n", atacante->nome);
    } else {
        // Empate - favorece o atacante
        defensor->tropas--;
        printf("\n⚔️ EMPATE! (favorece o atacante)\n");
        printf("%s perde 1 tropa.\n", defensor->nome);
        
        if (defensor->tropas <= 0) {
            printf("🎯 %s foi CONQUISTADO por %s!\n", defensor->nome, atacante->nome);
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = 1;
            atacante->tropas--;
        }
    }
}

// Função para validar escolha do usuário
int validarEscolha(int escolha, int quantidade) {
    return (escolha >= 1 && escolha <= quantidade);
}