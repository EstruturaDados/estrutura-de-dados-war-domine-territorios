// ===== NÍVEL NOVATO – COM EXPLICAÇÃO LINHA POR LINHA =====
#include <stdio.h>      // Essa linha traz as ferramentas para mostrar texto (printf) e ler do teclado (scanf, fgets)
#include <string.h>     // Essa traz ferramentas para trabalhar com palavras (como tirar o "enter" do final)

typedef struct {        // Aqui começamos a criar uma "caixa" que guarda várias coisas juntas
    char nome[30];      // → guarda até 29 letras + 1 espaço que o C coloca sozinho no final (\0)
    char cor[15];       // → guarda a cor do exército (ex: "Verde", "Azul")
    int tropas;         // → guarda um número inteiro (quantos soldadinhos tem)
} Territorio;           // Damos o nome "Territorio" para essa caixa toda

Territorio mapa[5];     // Criamos uma prateleira com 5 caixas iguais chamadas mapa[0] até mapa[4]

int main() {            // Toda aventura em C começa aqui dentro do main()
    
    printf("BEM-VINDO AO JOGO WAR! Vamos montar o mapa!\n\n");
    // printf mostra texto na tela. O \n pula linha

    for(int i = 0; i < 5; i++) {  
        // for = repete 5 vezes. i começa em 0 e vai até 4
        // i é o número da caixa que estamos enchendo agora

        printf("=== Território %d ===\n", i+1);
        // Mostra "Território 1", "Território 2"...

        printf("Digite o nome do território: ");

        // Limpa o '\n' deixado por scanf das iterações anteriores (não faz nada na primeira)
        int c;
        while((c = getchar()) != '\n' && c != EOF);
        // Essa linha mágica LIMPA o "enter" que fica preso no teclado depois de um scanf anterior
        // Sem ela, o fgets pula direto (é um truque importante!)

        fgets(mapa[i].nome, 30, stdin);
        // fgets lê uma linha inteira do teclado e coloca dentro de mapa[i].nome
        printf("Digite a cor do exército: ");
        scanf("%14s", mapa[i].cor);
        // %s lê uma palavra (sem espaços) e guarda na cor (limite para evitar overflow)

        printf("Digite quantas tropas tem: ");
        scanf("%d", &mapa[i].tropas);
        // %d lê um número inteiro
        // O & antes de mapa[i].tropas significa "o endereço da caixa de tropas"
        // %s lê uma palavra (sem espaços) e guarda na cor

        printf("Digite quantas tropas tem: ");
        scanf("%d", &mapa[i].tropas);
        // %d lê um número inteiro
        // O & antes de mapa[i].tropas significa "o endereço da caixa de tropas"

        printf("Cadastrado com sucesso!\n\n");
    }

    // MOSTRA TODO O CONTEÚDO CADASTRADO
    printf("\n=== MAPA COMPLETO DO WAR ===\n");
    printf("═══════════════════════════════\n");

    for(int i = 0; i < 5; i++) {
        // Percorre as 5 caixas de novo para mostrar

        printf("%d. %s\n", i+1, mapa[i].nome);
        // Mostra o número e o nome

        printf("   Cor: %s | Tropas: %d\n\n", mapa[i].cor, mapa[i].tropas);
        // Mostra cor e tropas com uma formatação bonita
    }

    printf("FIM DO PROGRAMA! Você realizou o cadastro com sucesso!\n");
    return 0;           // Diz para o computador: "tudo deu certo!"
}