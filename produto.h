#ifndef PRODUTO_H
#define PRODUTO_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Estrutura que representa um produto no estoque */
typedef struct Produto {
    int id;// Espaço para o código numérico do produto.
    char nome[50];// Vetor de caracteres para armazenar o nome.
    int quantidade;// Espaço para a quantidade em estoque.
    float preco;// Espaço para o valor monetário.
    
    /* * Aqui eu criei o ponteiro prox, Ele guarda o endereço do próximo 
     * produto na memória, gerando a nossa lista encadeada
     * Com isso, eu consigo acessar um produto através de outro
     */
    struct Produto *prox; 
} Produto;

/* Estrutura que representa o estoque, uma lista encadeada de produtos */
typedef struct {
    /* * Eu criei essa struct para encapsular o controle do estoque
     * inicio vai apontar para o primeiro Produto da lista, 
     * servindo como o ponto de partida para eu iterar pelos dados
     */
    Produto *inicio;
} Estoque;

#endif