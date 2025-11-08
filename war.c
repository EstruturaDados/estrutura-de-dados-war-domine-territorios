#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5   // tamanho fixo da fila
#define TAM_PILHA 3  // capacidade máxima da pilha

// Estrutura da peça
typedef struct {
    char nome; // tipo ('I', 'O', 'T', 'L')
    int id;    // identificador único
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca pecas[TAM_FILA];
    int frente;
    int tras;
    int qtd;
} Fila;

// Estrutura da pilha
typedef struct {
    Peca pecas[TAM_PILHA];
    int topo;
} Pilha;

// Inicializa fila
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->qtd = 0;
}

// Inicializa pilha
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

// Gera nova peça
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = id;
    return nova;
}

// Insere peça na fila (enqueue)
void enqueue(Fila *f, Peca p) {
    if (f->qtd == TAM_FILA) return; // fila cheia
    f->tras = (f->tras + 1) % TAM_FILA;
    f->pecas[f->tras] = p;
    f->qtd++;
}

// Remove peça da fila (dequeue)
Peca dequeue(Fila *f) {
    Peca removida = {'-', -1};
    if (f->qtd == 0) return removida; // fila vazia
    removida = f->pecas[f->frente];
    f->frente = (f->frente + 1) % TAM_FILA;
    f->qtd--;
    return removida;
}

// Empilha peça (push)
void push(Pilha *p, Peca x) {
    if (p->topo == TAM_PILHA - 1) {
        printf("Pilha cheia! Nao e possivel reservar mais pecas.\n");
        return;
    }
    p->pecas[++p->topo] = x;
}

// Desempilha peça (pop)
Peca pop(Pilha *p) {
    Peca removida = {'-', -1};
    if (p->topo == -1) {
        printf("Pilha vazia! Nao ha peca reservada para usar.\n");
        return removida;
    }
    removida = p->pecas[p->topo--];
    return removida;
}

// Exibe o estado atual da fila e da pilha
void exibirEstado(Fila f, Pilha p) {
    printf("\n=== Estado Atual ===\n");

    // Exibe fila
    printf("Fila de pecas:\t");
    if (f.qtd == 0) printf("(vazia)");
    else {
        for (int i = 0; i < f.qtd; i++) {
            int idx = (f.frente + i) % TAM_FILA;
            printf("[%c %d] ", f.pecas[idx].nome, f.pecas[idx].id);
        }
    }

    // Exibe pilha
    printf("\nPilha de reserva (Topo -> base): ");
    if (p.topo == -1) printf("(vazia)");
    else {
        for (int i = p.topo; i >= 0; i--)
            printf("[%c %d] ", p.pecas[i].nome, p.pecas[i].id);
    }
    printf("\n");
}

// Troca peça da frente da fila com o topo da pilha
void trocarFrenteTopo(Fila *f, Pilha *p) {
    if (f->qtd == 0 || p->topo == -1) {
        printf("Nao ha pecas suficientes para troca.\n");
        return;
    }
    int idxFrente = f->frente;
    Peca temp = f->pecas[idxFrente];
    f->pecas[idxFrente] = p->pecas[p->topo];
    p->pecas[p->topo] = temp;
    printf("Troca realizada entre frente da fila e topo da pilha.\n");
}

// Troca múltipla: 3 primeiros da fila com 3 da pilha
void trocaMultipla(Fila *f, Pilha *p) {
    if (f->qtd < 3 || p->topo < 2) {
        printf("Nao ha pecas suficientes para troca multipla.\n");
        return;
    }
    for (int i = 0; i < 3; i++) {
        int idxFila = (f->frente + i) % TAM_FILA;
        int idxPilha = p->topo - i;
        Peca temp = f->pecas[idxFila];
        f->pecas[idxFila] = p->pecas[idxPilha];
        p->pecas[idxPilha] = temp;
    }
    printf("Troca multipla realizada entre as 3 primeiras pecas.\n");
}

int main() {
    Fila fila;
    Pilha pilha;
    int opcao, contador = 0;
    srand(time(NULL));

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    // Preenche fila inicial
    for (int i = 0; i < TAM_FILA; i++)
        enqueue(&fila, gerarPeca(contador++));

    do {
        exibirEstado(fila, pilha);

        // Menu
        printf("\nOpcoes:\n");
        printf("1 - Jogar peca da frente da fila\n");
        printf("2 - Enviar peca da fila para pilha de reserva\n");
        printf("3 - Usar peca da pilha de reserva\n");
        printf("4 - Trocar frente da fila com topo da pilha\n");
        printf("5 - Troca multipla (3 pecas)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: { // jogar peça
                Peca jogada = dequeue(&fila);
                if (jogada.id != -1)
                    printf("Jogando peca: [%c %d]\n", jogada.nome, jogada.id);
                enqueue(&fila, gerarPeca(contador++)); // mantém fila cheia
                break;
            }
            case 2: { // reservar peça
                if (fila.qtd == 0) {
                    printf("Fila vazia!\n");
                    break;
                }
                Peca reservada = dequeue(&fila);
                printf("Reservando peca: [%c %d]\n", reservada.nome, reservada.id);
                push(&pilha, reservada);
                enqueue(&fila, gerarPeca(contador++)); // mantém fila cheia
                break;
            }
            case 3: { // usar da reserva
                Peca usada = pop(&pilha);
                if (usada.id != -1)
                    printf("Usando peca reservada: [%c %d]\n", usada.nome, usada.id);
                break;
            }
            case 4: // troca simples
                trocarFrenteTopo(&fila, &pilha);
                break;
            case 5: // troca múltipla
                trocaMultipla(&fila, &pilha);
                break;
            case 0:
                printf("Encerrando o jogo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}
