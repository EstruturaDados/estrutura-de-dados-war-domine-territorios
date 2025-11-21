#include <stdio.h>      // 1. Inclui a biblioteca de entrada e saída padrão (printf, scanf, fgets, getchar)
#include <stdlib.h>     // 2. Inclui funções de alocação de memória, números aleatórios e controle do programa
#include <string.h>     // 3. Inclui funções para manipulação de strings (texto)
#include <time.h>       // 4. Inclui acesso ao relógio do sistema para gerar números realmente aleatórios

typedef struct {    // 5. Inicia a definição de uma estrutura (um tipo de dado composto)
    char nome[30];  // 6. Campo que armazena o nome do território (máximo 29 caracteres + terminador nulo)
    char cor[10];   // 7. Campo que armazena a cor do exército controlador (ex: "Verde")
    int tropas;     // 8. Campo que armazena a quantidade de exércitos no território
} Territorio;       // 9. Finaliza a estrutura e dá o nome "Territorio" a esse tipo

Territorio *mapa = NULL;   // 10. Declara um ponteiro que apontará para o vetor de territórios (inicialmente nulo)
int total = 0;             // 11. Variável global que guardará o número total de territórios escolhidos
int missao;                // 12. Variável global que guardará o código da missão secreta (1 ou 2)

void iniciar() {           // 13. Declaração da função que configura o jogo inteiro
    printf("=== BEM-VINDO AO WAR - NÍVEL MESTRE ===\n");  // 14. Exibe mensagem de boas-vindas
    printf("Quantos territórios você quer no jogo? (5 a 20): ");  // 15. Pergunta ao usuário a quantidade de territórios
    scanf("%d", &total);   // 16. Lê o número digitado e armazena na variável total
    mapa = (Territorio*)calloc(total, sizeof(Territorio)); // 17. Aloca dinamicamente memória para 'total' territórios e zera tudo
    printf("\nDigite os dados dos %d territórios:\n\n", total);  // 18. Informa quantos territórios serão cadastrados

    for(int i = 0; i < total; i++) {               // 19. Inicia loop que executa 'total' vezes (uma para cada território)
        int c; while((c = getchar()) != '\n' && c != EOF); // 20. Limpa o buffer do teclado (remove o Enter que fica pendente)
        printf("Território %d:\n", i+1);           // 21. Mostra o número do território atual (1-based para o usuário)
        printf("  Nome: ");                        // 22. Solicita o nome do território
        fgets(mapa[i].nome, 30, stdin);            // 23. Lê uma linha completa do teclado e armazena no nome do território i
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0; // 24. Remove o caractere de nova linha que o fgets inclui
        printf("  Cor (ex: Verde): ");             // 25. Solicita a cor do exército
        scanf("%9s", mapa[i].cor);                 // 26. Lê a cor (máximo 9 caracteres + terminador)
        printf("  Tropas: ");                      // 27. Solicita a quantidade inicial de tropas
        scanf("%d", &mapa[i].tropas);              // 28. Lê o número e armazena no campo tropas do território i
        printf("  Cadastrado!\n\n");               // 29. Confirma que o território foi registrado com sucesso
    }                                              // 30. Fim do loop for – todos os territórios foram cadastrados

    srand(time(NULL));                             // 31. Inicializa o gerador de números aleatórios com o horário atual
    missao = 1 + rand() % 2;                       // 32. Gera aleatoriamente 1 ou 2 e armazena na variável missao
    printf("MISSÃO SECRETA GERADA!\n");            // 33. Informa que a missão foi sorteada
    printf("Sua missão é: ");                      // 34. Inicia a exibição da missão secreta
    if(missao == 1) printf("DESTRUIR O EXÉRCITO VERDE!\n\n");   // 35. Exibe missão 1 se missao for igual a 1
    else            printf("CONQUISTAR PELO MENOS 3 TERRITÓRIOS!\n\n"); // 36. Exibe missão 2 caso contrário
}                                                  // 37. Fim da função iniciar()

void mostrar() {                                   // 38. Declaração da função que exibe o mapa atual
    printf("\nMAPA ATUAL\n");                      // 39. Título da seção
    printf("══════════════════════════════════════════\n"); // 40. Linha decorativa
    for(int i = 0; i < total; i++) {               // 41. Loop que percorre todos os territórios
        printf("%d. [%s] %s → %d tropas\n", i+1, mapa[i].cor, mapa[i].nome, mapa[i].tropas); // 42. Exibe número, cor, nome e tropas de cada território
    }                                              // 43. Fim do loop for
    printf("══════════════════════════════════════════\n\n"); // 44. Linha decorativa final
}                                                  // 45. Fim da função mostrar()

void atacar(int a, int d) {                        // 46. Declaração da função de ataque – recebe dois números de territórios
    a--; d--;                                      // 47. Converte índices do usuário (1-based) para índices do vetor (0-based)
    if(strcmp(mapa[a].cor, mapa[d].cor) == 0) {    // 48. Verifica se ambos os territórios têm a mesma cor
        printf("Você não pode atacar seu próprio território!\n"); // 49. Mensagem de erro
        return;                                    // 50. Encerra a função imediatamente
    }                                              // 51. Fim do if
    if(mapa[a].tropas < 2) {                       // 52. Verifica se o atacante tem pelo menos 2 tropas (regra oficial do War)
        printf("Precisa de 2 ou mais tropas para atacar!\n"); // 53. Mensagem de erro
        return;                                    // 54. Encerra a função
    }                                              // 55. Fim do if

    int atk[3] = {1+rand()%6, 1+rand()%6, 1+rand()%6}; // 56. Gera 3 dados aleatórios de 1 a 6 para o atacante
    int def[2] = {1+rand()%6, 1+rand()%6};            // 57. Gera 2 dados aleatórios de 1 a 6 para o defensor

    for(int i = 0; i < 2; i++)                     // 58. Início do loop externo de ordenação
        for(int j = i+1; j < 3; j++)               // 59. Loop interno de ordenação
            if(atk[i] < atk[j]) {                  // 60. Se o dado atual for menor que o próximo
                int t = atk[i];                    // 61. Variável temporária recebe o valor atual
                atk[i] = atk[j];                   // 62. Troca os valores
                atk[j] = t;                        // 63. Completa a troca
            }                                      // 64. Fim do if de troca
                                                    // 65. Fim do loop interno
                                                    // 66. Fim do loop externo (dados do atacante agora estão ordenados decrescente)

    printf("Você rolou: %d %d %d\n", atk[0], atk[1], atk[2]);   // 67. Exibe os três dados do atacante
    printf("Inimigo rolou: %d %d\n", def[0], def[1]);          // 68. Exibe os dois dados do defensor

    int vitorias = 0;                                  // 69. Inicializa contador de vitórias do atacante
    if(atk[0] > def[0]) vitorias++;                    // 70. Compara o maior dado do atacante com o maior do defensor
    if(atk[1] > def[1]) vitorias++;                    // 71. Compara o segundo maior com o segundo maior

    if(vitorias >= 1) {                                // 72. Se o atacante ganhou pelo menos uma comparação
        mapa[d].tropas--;                              // 73. Defensor perde 1 tropa
        printf("Você venceu a batalha!\n");            // 74. Mensagem de vitória na batalha
        if(mapa[d].tropas <= 0) {                      // 75. Verifica se o defensor ficou sem tropas
            strcpy(mapa[d].cor, mapa[a].cor);          // 76. O território conquistado muda para a cor do atacante
            mapa[d].tropas = mapa[a].tropas / 2;       // 77. Metade das tropas do atacante são transferidas
            if(mapa[d].tropas < 1) mapa[d].tropas = 1; // 78. Garante que o território conquistado tenha pelo menos 1 tropa
            mapa[a].tropas -= mapa[d].tropas;          // 79. Subtrai do atacante as tropas que foram transferidas
            printf("VOCÊ CONQUISTOU O TERRITÓRIO!!!\n"); // 80. Mensagem de conquista total
        }                                              // 81. Fim do if de conquista
    } else {                                           // 82. Caso o defensor tenha ganhado as duas comparações
        mapa[a].tropas--;                              // 83. Atacante perde 1 tropa
        printf("Você perdeu 1 tropa...\n");            // 84. Mensagem de derrota
    }                                                  // 85. Fim do else
}                                                      // 86. Fim da função atacar()

int venceu() {                                         // 87. Função que verifica se a missão secreta foi cumprida
    if(missao == 1) {                                  // 88. Se a missão for eliminar o exército Verde
        for(int i = 0; i < total; i++)                 // 89. Percorre todos os territórios
            if(strcmp(mapa[i].cor, "Verde") == 0 && mapa[i].tropas > 0) // 90. Verifica se existe território Verde com tropas
                return 0;                              // 91. Ainda existe Verde vivo → missão não cumprida
        return 1;                                      // 92. Não existe mais Verde → missão cumprida
    } else {                                           // 93. Caso a missão seja conquistar 3 territórios
        int conta = 0;                                 // 94. Inicializa contador
        for(int i = 0; i < total; i++)                 // 95. Percorre todos os territórios
            if(strcmp(mapa[i].cor, mapa[0].cor) == 0) conta++; // 96. Conta quantos têm a mesma cor do primeiro território (sua cor)
        return conta >= 3;                             // 97. Retorna 1 se tiver 3 ou mais, 0 caso contrário
    }                                                  // 98. Fim do else
}                                                      // 99. Fim da função venceu()

void limpar() {                                        // 100. Função que libera a memória alocada
    free(mapa);                                        // 101. Devolve ao sistema operacional o bloco de memória alocado
    mapa = NULL;                                       // 102. Define o ponteiro como nulo (evita acesso indevido)
}                                                      // 103. Fim da função limpar()

int main() {                                           // 104. Função principal – ponto de entrada de todo programa C
    iniciar();                                         // 105. Executa toda a configuração inicial do jogo
    int op;                                            // 106. Variável que armazena a opção do menu
    do {                                               // 107. Inicia loop principal do jogo
        mostrar();                                     // 108. Exibe o mapa atual
        printf("1. Atacar\n2. Verificar missão\n0. Sair\n→ "); // 109. Exibe o menu de opções
        scanf("%d", &op);                              // 110. Lê a escolha do jogador

        if(op == 1) {                                  // 111. Se o jogador escolheu atacar
            int a, d;                                  // 112. Variáveis para território atacante e defensor
            printf("De qual território (1-%d): ", total); // 113. Pergunta o território de origem
            scanf("%d", &a);                           // 114. Lê o número
            printf("Para qual território (1-%d): ", total); // 115. Pergunta o território alvo
            scanf("%d", &d);                           // 116. Lê o número
            if(a >= 1 && a <= total && d >= 1 && d <= total && a != d) // 117. Valida os números digitados
                atacar(a, d);                          // 118. Executa o ataque
            else                                       // 119. Caso os números sejam inválidos
                printf("Números inválidos!\n");        // 120. Exibe mensagem de erro
        }                                              // 121. Fim do if(op == 1)

        if(op == 2) {                                  // 122. Se o jogador escolheu verificar a missão
            if(venceu()) {                             // 123. Chama a função que verifica vitória
                printf("PARABÉNS!!! VOCÊ CUMPRIU A MISSÃO SECRETA!\n"); // 124. Mensagem de vitória
                printf("VOCÊ É O GRÃO-MESTRE DO WAR!!!\n"); // 125. Mensagem final
                break;                                 // 126. Sai do loop (vitória)
            } else {                                   // 127. Caso ainda não tenha vencido
                printf("Ainda não cumpriu a missão... continue lutando!\n"); // 128. Mensagem de incentivo
            }                                          // 129. Fim do else
        }                                              // 130. Fim do if(op == 2)
    } while(op != 0);                                  // 131. Condição do loop: continua enquanto não escolher sair (0)

    limpar();                                          // 132. Libera toda a memória alocada
    printf("\nObrigado por jogar! Você é incrível!\n"); // 133. Mensagem de despedida
    return 0;                                          // 134. Retorna 0 ao sistema operacional (execução bem-sucedida)
}                                                      // 135. Fim do programa