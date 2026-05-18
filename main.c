#include <stdio.h>
#include "cadastrarTerritorio.h"
#include "exibirTerritorio.h"
#include "atribuirMissao.h"
#include "atacarTerritorio.h"
#include "verificarMissao.h"
#include "liberarMemoria.h"

int main() {
    int opcao;

    do {
        printf("\n=== MENU ===\n");
        printf("1 - Cadastrar Territorio\n");
        printf("2 - Exibir Territorio\n");
        printf("3 - Atacar Territorio\n");
        printf("4 - Atribuir Missao\n");
        printf("5 - Verificar Missoes\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                cadastrarTerritorio();
                break;

            case 2:
                exibirMapa();
                break;

            case 3:
                atacarTerritorio();
                break;

            case 4:
                atribuirMissao();
                break;

            case 5:
                verificarMissao();
                break;

            case 0:
                liberarMemoria();
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 0);

    return 0;
}
