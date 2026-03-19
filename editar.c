#include "editar.h"

// Eu uso o 'extern' de novo para ter acesso à lista encadeada original
extern Produto *inicio;

/* Função para editar os dados de um produto */
/* Busca o produto pelo ID, exibe menu de opções e permite alterar nome, quantidade ou preço */
void editarProduto(Estoque *e, int id) {
    Produto *atual = inicio;
    int encontrado = 0;
    int opcao;
    
    // bloco iterativo para achar o nó exato que o usuário quer alterar
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
            
            /*
             * como 'atual' aponta para o endereço real do produto na 
             * memória Heap, qualquer scanf que eu fizer no
             * ->campo vai modificar o dado real e permanente
             */
            if (opcao == 1) {
                printf("Novo nome: ");
                scanf(" %[^\n]", atual->nome);
                printf("Nome atualizado com sucesso.\n");
            } else if (opcao == 2) {
                printf("Nova quantidade: ");
                scanf("%d", &atual->quantidade);
                
                // loop de validação para impedir entrada de valores negativos
                while (atual->quantidade < 0) {
                    printf("Quantidade inválida. Insira a quantidade de unidades do produto novamente: ");
                    scanf("%d", &atual->quantidade);
                }
                printf("Quantidade atualizada com sucesso.\n");
            } else if (opcao == 3) {
                printf("Novo preco: ");
                scanf("%f", &atual->preco);
                
                // mesma lógica de validação aqui para proteger a integridade do preço
                while (atual->preco < 0) {
                    printf("Preço inválido. Insira o preço do produto novamente: ");
                    scanf("%f", &atual->preco);
                }
                printf("Preco atualizado com sucesso.\n");
            } else {
                printf("Edicao cancelada.\n");
            }
            break; //encerra a busca para poupar a CPU
        }
        atual = atual->prox; // Continua a travessia se ainda não encontrou
    }
    
    if (!encontrado) {
        printf("Produto nao encontrado.\n");
    }
}