#include "editar.h"

extern Produto *inicio;

void editarProduto(Estoque *e, int id) {
    Produto *atual = inicio;
    int encontrado = 0;
    int opcao;
    
    while (atual != NULL) {
        if (atual->id == id) {
            printf("=== Produto Encontrado ===\n");
            printf("ID: %d\n", atual->id);
            printf("Nome: %s\n", atual->nome);
            printf("Quantidade: %d\n", atual->quantidade);
            printf("Preco: %.2f\n\n", atual->preco);
            encontrado = 1;
            
            printf("=== O que deseja editar? ===\n");
            printf("1. Nome\n");
            printf("2. Quantidade\n");
            printf("3. Preco\n");
            printf("0. Cancelar\n");
            printf("Escolha uma opção: ");
            scanf("%d", &opcao);
            printf("\n");
            
            if (opcao == 1) {
                printf("Novo nome: ");
                scanf("%s", atual->nome);
                printf("Nome atualizado com sucesso.\n");
            } else if (opcao == 2) {
                printf("Nova quantidade: ");
                scanf("%d", &atual->quantidade);
                printf("Quantidade atualizada com sucesso.\n");
            } else if (opcao == 3) {
                printf("Novo preco: ");
                scanf("%f", &atual->preco);
                printf("Preco atualizado com sucesso.\n");
            } else {
                printf("Edicao cancelada.\n");
            }
            break;
        }
        atual = atual->prox;
    }
    
    if (!encontrado) {
        printf("Produto nao encontrado.\n");
    }
}
