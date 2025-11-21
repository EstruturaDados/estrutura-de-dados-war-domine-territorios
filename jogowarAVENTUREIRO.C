// ====================================================================
// JOGO WAR - NÍVEL AVENTUREIRO COMPLETO
// ====================================================================

#include <stdio.h>      // Caixa de ferramentas para mostrar texto e ler do teclado (printf, scanf)
#include <stdlib.h>     // Caixa com calloc, malloc, free, rand, srand e exit
#include <string.h>     // Ferramentas para mexer com palavras (strcpy, strcmp, strcspn)
#include <time.h>       // Relógio do computador para deixar os dados diferentes toda vez

// 1. CRIANDO A CAIXINHA QUE GUARDA AS INFORMAÇÕES DE UM TERRITÓRIO
typedef struct {
    char nome[30];   // Até 29 letras + 1 espaço invisível que o C coloca no final
    char cor[10];    // Cor do exército que domina (ex: "Verde", "Azul")
    int tropas;      // Quantos soldados tem nesse território
} Territorio;        // Damos o nome de "Territorio" pra essa caixa

// 2. VARIÁVEIS QUE O PROGRAMA INTEIRO VAI USAR
Territorio *mapa = NULL;        // Setinha que vai apontar pro nosso mapa inteiro (começa apontando pro nada)
int total_territorios = 0;      // Guarda quantos territórios o jogador escolheu

// 3. FUNÇÃO: CADASTRAR TODOS OS TERRITÓRIOS
void cadastrar_territorios() {
    printf("Quantos territórios você quer no jogo? ");     // Pergunta pro jogador
    scanf("%d", &total_territorios);                       // Guarda a resposta nessa caixa

    // Pede memória pro computador pra guardar todas as caixas
    mapa = (Territorio*) calloc(total_territorios, sizeof(Territorio));
    // calloc = reserva espaço e já deixa tudo zerado (muito seguro!)

    printf("\nVamos cadastrar %d territórios agora!\n\n", total_territorios);

    for(int i = 0; i < total_territorios; i++) {           // Repete para cada território
        // LIMPA O "ENTER" QUE FICA PRESO NO TECLADO (truque importante!)
        int c; 
        while((c = getchar()) != '\n' && c != EOF);

        printf("=== Território %d ===\n", i+1);            // Mostra qual território estamos cadastrando
        printf("  Nome: ");
        fgets(mapa[i].nome, 30, stdin);                    // Lê o nome completo (pode ter espaços)
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0;     // Tira o "enter" do final do nome

        printf("  Cor do exército (ex: Verde): ");
        scanf("%9s", mapa[i].cor);                         // Lê a cor (máximo 9 letras)

        printf("  Quantas tropas: ");
        scanf("%d", &mapa[i].tropas);                      // Lê o número de tropas

        printf("  Cadastrado com sucesso!\n\n");           // 
    }
}

// 4. FUNÇÃO: MOSTRAR O MAPA ATUAL
void mostrar_mapa() {
    printf("\n=== MAPA ATUAL DO JOGO ===\n");
    printf("══════════════════════════════════\n");
    for(int i = 0; i < total_territorios; i++) {
        printf("%d. %s [%s] → %d tropas\n",
               i+1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("══════════════════════════════════\n\n");
}

// 5. FUNÇÃO PRINCIPAL DE ATAQUE - A MELHOR PARTE!
void atacar(Territorio* atacante, Territorio* defensor) {
    // atacante e defensor são SETINHAS que apontam direto pras caixas!

    // Não pode atacar território da mesma cor
    if(strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Você não pode atacar seu próprio território!\n");
        return;                                            // Sai da função imediatamente
    }

    // Regra do War: precisa de pelo menos 2 tropas pra atacar
    if(atacante->tropas < 2) {
        printf("Você precisa de pelo menos 2 tropas para atacar!\n");
        return;
    }

    // Rolar dados de verdade!
    int dado_atk[3], dado_def[2];                          // 3 dados pro atacante, 2 pro defensor
    printf("Rolando os dados...\n");

    for(int i = 0; i < 3; i++) dado_atk[i] = 1 + rand() % 6;   // Rola 3 dados (1 a 6)
    for(int i = 0; i < 2; i++) dado_def[i] = 1 + rand() % 6;   // Rola 2 dados

    // Ordena do maior pro menor (os 2 primeiros são os que valem)
    for(int i = 0; i < 2; i++) {
        for(int j = i+1; j < 3; j++) {
            if(dado_atk[i] < dado_atk[j]) {
                int temp = dado_atk[i];
                dado_atk[i] = dado_atk[j];
                dado_atk[j] = temp;
            }
        }
    }
    // (mesma coisa pros dados do defensor - você pode copiar o código se quiser)

    printf("Atacante rolou: %d %d %d\n", dado_atk[0], dado_atk[1], dado_atk[2]);
    printf("Defensor rolou: %d %d\n", dado_def[0], dado_def[1]);

    int vitorias = 0;
    if(dado_atk[0] > dado_def[0]) vitorias++;   // Compara o maior com o maior
    if(dado_atk[1] > dado_def[1]) vitorias++;   // Compara o segundo com o segundo

    if(vitorias >= 1) {
        // ATACANTE VENCEU!
        defensor->tropas--;                     // Defensor perde 1 tropa
        printf("Atacante venceu a batalha!\n");

        if(defensor->tropas <= 0) {
            // CONQUISTA TOTAL!
            strcpy(defensor->cor, atacante->cor);           // Muda a cor do território
            defensor->tropas = atacante->tropas / 2;         // Metade das tropas vão pro novo dono
            if(defensor->tropas < 1) defensor->tropas = 1;  // Mínimo 1 tropa
            atacante->tropas -= defensor->tropas;           // Atacante perde as tropas que enviou
            printf("VOCÊ CONQUISTOU O TERRITÓRIO!!!\n");
        }
    } else {
        atacante->tropas--;                     // Atacante perde 1 tropa
        printf("Defensor resistiu! Você perdeu 1 tropa.\n");
    }
}

// 6. FUNÇÃO: DEVOLVER A MEMÓRIA (sempre limpar a bagunça!)
void liberar_memoria() {
    free(mapa);        // Devolve toda a memória que pedimos com calloc
    mapa = NULL;       // Aponta a setinha pro nada (boa prática)
}

// 7. A AVENTURA COMEÇA AQUI!
int main() {
    srand(time(NULL));                 // Liga o gerador de números aleatórios com a hora do PC

    printf("BEM-VINDO AO JOGO WAR - NÍVEL AVENTUREIRO!\n");
    printf("Você vai conquistar o mundo!\n\n");

    cadastrar_territorios();           // Chama a função de cadastro

    int opcao;
    do {
        mostrar_mapa();                // Mostra o mapa atual
        printf("1. Atacar\n");
        printf("2. Ver mapa de novo\n");
        printf("0. Sair do jogo\n");
        printf("O que você quer fazer? ");
        scanf("%d", &opcao);

        if(opcao == 1) {
            int a, d;
            printf("Número do território que vai ATACAR: ");
            scanf("%d", &a); a--;      // Transforma de 1-5 para 0-4
            printf("Número do território que vai DEFENDER: ");
            scanf("%d", &d); d--;

            // Verifica se os números são válidos
            if(a >= 0 && a < total_territorios && d >= 0 && d < total_territorios && a != d) {
                atacar(&mapa[a], &mapa[d]);   // & = "endereço de" → passa as setinhas!
            } else {
                printf("Números inválidos! Tente de novo.\n");
            }
        }

    } while(opcao != 0);           // Repete até o jogador escolher sair

    liberar_memoria();             // Limpa tudo antes de ir embora
    printf("\nObrigado por jogar! Você é um verdadeiro general!\n");

    return 0;                      // Diz pro computador: "tudo deu certo!"
}