#ifndef PRODUTO_H
#define PRODUTO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Estrutura que representa um produto no estoque */
typedef struct Produto {
    int id;
    char nome[50];
    int quantidade;
    float preco;
    struct Produto *prox;
} Produto;

/* Estrutura que representa o estoque (lista encadeada de produtos) */
typedef struct {
    Produto *inicio;
} Estoque;

#endif
