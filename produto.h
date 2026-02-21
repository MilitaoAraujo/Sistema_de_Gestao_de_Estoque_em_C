#ifndef PRODUTO_H
#define PRODUTO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Produto {
    int id;
    char nome[50];
    int quantidade;
    float preco;
    struct Produto *prox;
} Produto;

typedef struct {
    Produto *inicio;
} Estoque;

#endif
