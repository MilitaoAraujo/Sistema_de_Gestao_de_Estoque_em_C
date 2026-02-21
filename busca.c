#include "busca.h"

extern Produto *inicio;

void buscarPorNome(Estoque *e) {
    char nomeBusca[50];
    int encontrado = 0;
    
    printf("Digite o nome do produto: ");
    scanf("%s", nomeBusca);
    printf("\n");
    
    Produto *atual = inicio;
    
    while (atual != NULL) {
        if (strcmp(atual->nome, nomeBusca) == 0) {
            printf("=== Produto Encontrado ===\n");
            printf("ID: %d\n", atual->id);
            printf("Nome: %s\n", atual->nome);
            printf("Quantidade: %d\n", atual->quantidade);
            printf("Preco: %.2f\n\n", atual->preco);
            encontrado = 1;
            break;
        }
        atual = atual->prox;
    }
    
    if (!encontrado) {
        printf("Produto nao encontrado.\n");
    }
}

void buscarPorID(Estoque *e, int id) {
    Produto *atual = inicio;
    int encontrado = 0;
    
    while (atual != NULL) {
        if (atual->id == id) {
            printf("=== Produto Encontrado ===\n");
            printf("ID: %d\n", atual->id);
            printf("Nome: %s\n", atual->nome);
            printf("Quantidade: %d\n", atual->quantidade);
            printf("Preco: %.2f\n\n", atual->preco);
            encontrado = 1;
            break;
        }
        atual = atual->prox;
    }
    
    if (!encontrado) {
        printf("Produto nao encontrado.\n");
    }
}
