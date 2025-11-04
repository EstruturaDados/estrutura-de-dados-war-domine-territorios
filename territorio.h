#ifndef TERRITORIO_H
#define TERRITORIO_H

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

Territorio* alocarMapa(int tamanho);
void cadastrarTerritorios(Territorio* mapa, int tamanho);
void exibirMapa(const Territorio* mapa, int tamanho);
void atacar(Territorio* atacante, Territorio* defensor);
void realizarAtaque(Territorio* origem, Territorio* destino, const char* corJogador);
void inicializarTerritorios(Territorio* mapa, int tamanho);
void moverTropas(Territorio* origem, Territorio* destino, int quantidade, const char* corJogador);
void exibirTerritoriosJogador(const Territorio* mapa, int tamanho, const char* corJogador);

#endif