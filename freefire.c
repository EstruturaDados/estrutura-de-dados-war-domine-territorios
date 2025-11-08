#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMP 20

// ===== STRUCT =====
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// ===== PROTÓTIPOS =====
void cadastrarComponentes(Componente comp[], int *total);
void mostrarComponentes(Componente comp[], int total);
void bubbleSortNome(Componente comp[], int total, int *comparacoes);
void insertionSortTipo(Componente comp[], int total, int *comparacoes);
void selectionSortPrioridade(Componente comp[], int total, int *comparacoes);
int buscaBinariaPorNome(Componente comp[], int total, char nome[], int *comparacoes);

// ===== FUNÇÃO PRINCIPAL =====
int main() {
    Componente componentes[MAX_COMP];
    int total = 0;
    int opcao, comp = 0;
    clock_t inicio, fim;
    double tempo;
    char nomeBusca[30];

    do {
        printf("\n=== SISTEMA DE MONTAGEM DA TORRE DE FUGA ===\n");
        printf("1. Cadastrar componentes\n");
        printf("2. Ordenar por NOME (Bubble Sort)\n");
        printf("3. Ordenar por TIPO (Insertion Sort)\n");
        printf("4. Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("5. Busca binaria por nome (após ordenar por nome)\n");
        printf("6. Mostrar todos os componentes\n");
        printf("0. Sair\nEscolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                cadastrarComponentes(componentes, &total);
                break;

            case 2:
                inicio = clock();
                comp = 0;
                bubbleSortNome(componentes, total, &comp);
                fim = clock();
                tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                printf("Ordenacao concluida por NOME (%d comparacoes, %.6f s)\n", comp, tempo);
                mostrarComponentes(componentes, total);
                break;

            case 3:
                inicio = clock();
                comp = 0;
                insertionSortTipo(componentes, total, &comp);
                fim = clock();
                tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                printf("Ordenacao concluida por TIPO (%d comparacoes, %.6f s)\n", comp, tempo);
                mostrarComponentes(componentes, total);
                break;

            case 4:
                inicio = clock();
                comp = 0;
                selectionSortPrioridade(componentes, total, &comp);
                fim = clock();
                tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                printf("Ordenacao concluida por PRIORIDADE (%d comparacoes, %.6f s)\n", comp, tempo);
                mostrarComponentes(componentes, total);
                break;

            case 5:
                if (total == 0) {
                    printf("Cadastre e ordene os componentes primeiro!\n");
                    break;
                }
                printf("Nome do componente-chave: ");
                fgets(nomeBusca, 30, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                comp = 0;
                inicio = clock();
                int pos = buscaBinariaPorNome(componentes, total, nomeBusca, &comp);
                fim = clock();
                tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

                if (pos != -1)
                    printf("Componente '%s' encontrado (comparacoes: %d, tempo: %.6f s)\n",
                           componentes[pos].nome, comp, tempo);
                else
                    printf("Componente nao encontrado (%d comparacoes, %.6f s)\n", comp, tempo);
                break;

            case 6:
                mostrarComponentes(componentes, total);
                break;

            case 0:
                printf("Encerrando o sistema...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}

// ===== FUNÇÕES =====

// Cadastro dos componentes
void cadastrarComponentes(Componente comp[], int *total) {
    if (*total >= MAX_COMP) {
        printf("Limite maximo atingido!\n");
        return;
    }

    int n;
    printf("Quantos componentes deseja cadastrar (max %d)? ", MAX_COMP - *total);
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n && *total < MAX_COMP; i++) {
        printf("\nNome: ");
        fgets(comp[*total].nome, 30, stdin);
        comp[*total].nome[strcspn(comp[*total].nome, "\n")] = '\0';
        printf("Tipo: ");
        fgets(comp[*total].tipo, 20, stdin);
        comp[*total].tipo[strcspn(comp[*total].tipo, "\n")] = '\0';
        printf("Prioridade (1 a 10): ");
        scanf("%d", &comp[*total].prioridade);
        getchar();
        (*total)++;
    }

    printf("Componentes cadastrados com sucesso!\n");
}

// Exibe todos os componentes
void mostrarComponentes(Componente comp[], int total) {
    if (total == 0) {
        printf("Nenhum componente cadastrado.\n");
        return;
    }

    printf("\n--- LISTA DE COMPONENTES ---\n");
    for (int i = 0; i < total; i++) {
        printf("%d) Nome: %-20s | Tipo: %-15s | Prioridade: %d\n",
               i + 1, comp[i].nome, comp[i].tipo, comp[i].prioridade);
    }
}

// ===== ORDENACOES =====

// Bubble Sort (por nome)
void bubbleSortNome(Componente comp[], int total, int *comparacoes) {
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            (*comparacoes)++;
            if (strcmp(comp[j].nome, comp[j + 1].nome) > 0) {
                Componente tmp = comp[j];
                comp[j] = comp[j + 1];
                comp[j + 1] = tmp;
            }
        }
    }
}

// Insertion Sort (por tipo)
void insertionSortTipo(Componente comp[], int total, int *comparacoes) {
    for (int i = 1; i < total; i++) {
        Componente chave = comp[i];
        int j = i - 1;
        while (j >= 0 && strcmp(comp[j].tipo, chave.tipo) > 0) {
            (*comparacoes)++;
            comp[j + 1] = comp[j];
            j--;
        }
        comp[j + 1] = chave;
    }
}

// Selection Sort (por prioridade)
void selectionSortPrioridade(Componente comp[], int total, int *comparacoes) {
    for (int i = 0; i < total - 1; i++) {
        int min = i;
        for (int j = i + 1; j < total; j++) {
            (*comparacoes)++;
            if (comp[j].prioridade < comp[min].prioridade)
                min = j;
        }
        if (min != i) {
            Componente tmp = comp[i];
            comp[i] = comp[min];
            comp[min] = tmp;
        }
    }
}

// ===== BUSCA BINÁRIA =====
int buscaBinariaPorNome(Componente comp[], int total, char nome[], int *comparacoes) {
    int ini = 0, fim = total - 1;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(comp[meio].nome, nome);
        if (cmp == 0) return meio;
        else if (cmp < 0) ini = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}
