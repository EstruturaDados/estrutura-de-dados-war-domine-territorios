#include<stdio.h>
#include<stdlib.h>     // necessario para malloc e free
#include<string.h>
#include<time.h>
// definindo uma Struct do tipo Territorio é um novo TIPO (tipo int, ou float) um dado que possui varios dados dentro
typedef struct{
    char nome [30];
    char cor [10];
    int tropas;
} Territorio;

void cadastrar(Territorio *mapa, int quantidade){     // modularização criando a função cadastrar
    int i;
    for (i = 0; i < quantidade; i++){   // laço for para fazer a iteração dos dados pedidos ao usuário

        printf("\nNome do territorio: ");
        while(getchar() != '\n');                      // para limpar o enter
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';
 
        printf("Cor do exercito: ");
        fgets(mapa[i].cor, 10, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';
        
        printf("Numero de tropas: ");
        scanf("%d", &mapa[i].tropas);   // Para ler o número de tropas, usamos & para passar o endereço da variável
    }
}
void atribuirMissao (char *destino, char *missoes[], int totalMissoes){
	int sorteio = rand() % totalMissoes;
	strcpy(destino, missoes[sorteio]);
}
void exibirMissao(const char *missao){
    printf("\n===== SUA MISSAO =====\n");
    printf("%s\n", missao);
    printf("======================\n");
}

void atacar(Territorio *atacante, Territorio *defensor){
	if (atacante->tropas <= 1){
		printf("Nao ha tropas suficientes para o ataque!\n");
		return;
	}
	int dadoAtacante = rand()%6 + 1;
	int dadoDefensor = rand()%6 + 1;
	printf("O atacante %s rolou o dado e tirou: %d\n", atacante->nome, dadoAtacante);
	printf("O defensor %s rolou o dado e tirou: %d\n", defensor->nome, dadoDefensor);
	if(dadoAtacante >= dadoDefensor){             // Com essa condição o empate favorece o atacante
		printf("O atacante %s venceu essa batalha\n", atacante->nome);
		defensor->tropas -= 1;
	}
	else{
		printf("O defensor %s ganhou essa batalha\n", defensor->nome);
		if (atacante->tropas > 1)
    atacante->tropas--;
	}
	if (defensor -> tropas <=0){
		printf("Territorio conquistado pelo exercito %s \n", atacante->cor);
		strcpy(defensor->cor, atacante->cor);
		int tropasTransferidas = atacante->tropas /2;
		if (tropasTransferidas < 1){      //garante que será transferido pelo menos 1 tropa (lembrando que C nao possui "meia" tropa)
			tropasTransferidas = 1;      //em C o meio seria arredondado para baixo ou seja 0 por isso garantimos 1 tropa
		}
		defensor->tropas = tropasTransferidas;
    	atacante->tropas -= tropasTransferidas;		
		}
	
	}
	void exibirMapa(Territorio *mapa, int quantidade){
		printf("\n========== MAPA DO MUNDO ==========\n");
	int i;
    for (i=0; i < quantidade ; i++){     // criando um laço de repetição for para exibição de todos os territorios cadastrados
    	printf("%d. %s (Exercito: %s, Tropas: %d)\n",
			i+1,
    		mapa[i].nome,
    		mapa[i].cor,
    		mapa[i].tropas);
	}
	printf("==================================\n");
	}
	
	int verificarMissao(char *missao, Territorio *mapa, int tamanho){
		int i, count = 0;
		if (strcmp(missao, "Conquistar 3 territorios") == 0 ){
			for (i = 0; i < tamanho; i++){
				if (strcmp(mapa[i].cor, mapa[0].cor) == 0){
				count++;
				}
			}
			if (count >=3){
				return 1;
			}
		}
		if (strcmp(missao, "Eliminar exercito vermelho") == 0){
			for (i = 0; i < tamanho; i++){
				if (strcmp(mapa[i].cor, "vermelho") == 0){
					return 0;    // se ainda existe cor vermelho
				}
			}
			return 1;   // não existe vermelho
		}
		if (strcmp(missao, "Dominar todos os territorios") == 0){
			for (i = 0; i < tamanho; i++){
				if (strcmp(mapa[i].cor, mapa[0].cor) != 0){
					return 0;  // achou uma cor diferente da cor do territorio (posição 0)
				}
			}
			return 1;  // no caso de todas as cores ja serem iguais ao do territorio posiçao 0
		}
		if (strcmp(missao, "Conquistar a Asia") == 0){
			for (i = 0; i < tamanho; i++){
				if (strcmp(mapa[i].nome, "Asia") == 0){
					if (strcmp(mapa[i].cor, mapa[0].cor) != 0){
						return 0;
					}
				}
			}
			return 1;
		}
			if (strcmp(missao, "Eliminar exercito azul") == 0){
			for (i = 0; i < tamanho; i++){
				if (strcmp(mapa[i].cor, "azul") == 0){
					return 0;    // se ainda existe cor azul
				}
			}
			return 1;
	}
		return 0;
	}
	void liberarMemoria(Territorio *mapa, char *missao){
    free(mapa);
    free(missao);
	}
	
	
int main(){
	char *missoes[] = {
    "Conquistar 3 territorios",
    "Eliminar exercito vermelho",
    "Dominar todos os territorios",
    "Conquistar a Asia",
    "Eliminar exercito azul"
};
int totalMissoes = 5;

char *missaoJogador = malloc(100 * sizeof(char));
if(missaoJogador == NULL){
	printf("Erro ao alocar memoria para missao!\n");
	return 1;
}
	
	srand(time(NULL)); // para gerar numeros aleatorio que serão usados nos dados do ataque
	int quantidade;
	printf("Quantos territorios deseja cadastar? ");
	scanf("%d", &quantidade);
	
    Territorio *nomeDosTerritorios;  // criando um ponteiro para a STRUCT nomeDosTerritorios
    
    nomeDosTerritorios = calloc (quantidade, sizeof(Territorio));  // alocando memoria dinamicamente com ponteiro
    
    if (nomeDosTerritorios == NULL){    // verificando se a alocação na memoria deu certo
    	printf("Erro na alocacao de memoria!\n");
    	return 1;
	}
 	cadastrar(nomeDosTerritorios, quantidade);
 	printf("\nTerritorios cadastrados com sucesso!\n");
 	
 	atribuirMissao(missaoJogador, missoes, totalMissoes);
 	exibirMissao(missaoJogador);
 	
 	exibirMapa(nomeDosTerritorios, quantidade);
	
	int atac, defensor;
	
	int opcao;

do {
    printf("\n====== MENU ======\n");
    printf("1 - Atacar\n");
    printf("2 - Ver Missao\n");
    printf("0 - Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    switch(opcao){

        case 1:
            printf("\n======= FASE DE ATAQUE =======\n");
            printf("Escolha o territorio atacante (1 a %d): ", quantidade);
            scanf("%d", &atac);

            printf("Digite o numero do defensor: ");
            scanf("%d", &defensor);

            if (atac < 1 || atac > quantidade || defensor < 1 || defensor > quantidade || atac == defensor){
                printf("Escolha invalida!\n");
                break;
            }

            if (strcmp(nomeDosTerritorios[atac-1].cor,
                       nomeDosTerritorios[defensor-1].cor) == 0){
                printf("Nao pode atacar territorio da mesma cor!\n");
                break;
            }

            atacar(&nomeDosTerritorios[atac-1],
                   &nomeDosTerritorios[defensor-1]);

            if (verificarMissao(missaoJogador, nomeDosTerritorios, quantidade)){
                exibirMapa(nomeDosTerritorios, quantidade);
                printf("\nPARABENS! Missao concluida!\n");
                opcao = 0;
            }

            exibirMapa(nomeDosTerritorios, quantidade);
            break;

        case 2:
            exibirMissao(missaoJogador);
            break;

        case 0:
            printf("Encerrando o jogo...\n");
            break;

        default:
            printf("Opcao invalida!\n");
    }

} while(opcao != 0);
	
	
	
    liberarMemoria(nomeDosTerritorios, missaoJogador);       // Libera a memória dos territorios e da missão jogador

    return 0;
};