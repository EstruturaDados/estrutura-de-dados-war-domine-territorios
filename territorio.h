#ifndef TERRITORIO_H
#define TERRITORIO_H

typedef struct {
    char nome_territorio[100];
    char cor_exercito[50];
    int numero_tropas;
    char missao[100];
} Territorio;

extern Territorio *t;
extern int numero_territorio;

#endif
