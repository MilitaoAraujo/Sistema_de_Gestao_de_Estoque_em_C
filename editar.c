#include "editar.h"

extern Produto *inicio;

/* Função para editar os dados de um produto */
/* Busca o produto pelo ID, exibe menu de opções e permite alterar nome, quantidade ou preço */
/* Valida os valores de quantidade e preço para não允许 valores negativos */
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
                scanf(" %[^\n]", atual->nome);
                printf("Nome atualizado com sucesso.\n");
            } else if (opcao == 2) {
                printf("Nova quantidade: ");
                scanf("%d", &atual->quantidade);
                while (atual->quantidade < 0) {
                    printf("Quantidade inválida. Insira a quantidade de unidades do produto novamente: ");
                    scanf("%d", &atual->quantidade);
                }
                printf("Quantidade atualizada com sucesso.\n");
            } else if (opcao == 3) {
                printf("Novo preco: ");
                scanf("%f", &atual->preco);
                while (atual->preco < 0) {
                    printf("Preço inválido. Insira o preço do produto novamente: ");
                    scanf("%f", &atual->preco);
                }
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
