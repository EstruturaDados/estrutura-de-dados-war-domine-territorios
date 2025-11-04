#include <stdio.h>
#include "mapa.h"
#include "ataque.h"
#include "missao.h"

int main() {
    printf("=== JOGO WAR - Implementação Modular ===\n");
    while (1) {
        printf("\nEscolha o desafio a executar:\n");
        printf("1) Nível Novato (cadastro estático de 5 territórios)\n");
        printf("2) Nível Aventureiro (mapa dinâmico + atacar)\n");
        printf("3) Nível Mestre (missões estratégicas)\n");
        printf("4) Sair\n");
        int op;
        printf("Opção: ");
        scanf("%d", &op);
        getchar(); // limpar buffer

        switch (op) {
            case 1: desafio_novato(); break;
            case 2: desafio_aventureiro(); break;
            case 3: desafio_mestre(); break;
            case 4: printf("Saindo...\n"); return 0;
            default: printf("Opção inválida.\n");
        }
    }
    return 0;
}
