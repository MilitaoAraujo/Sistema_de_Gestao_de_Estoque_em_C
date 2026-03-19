#include "busca.h"

/* * Eu usei a palavra-chave extern para avisar ao compilador que 
 * o ponteiro global inicio já foi criado no main.c. Assim, eu consigo 
 * acessar a mesma lista encadeada da memória principal por aqui
 */
extern Produto *inicio;

/* Função para buscar um produto pelo nome digitado pelo usuário */
void buscarPorNome(Estoque *e) {
    char nomeBusca[50];
    int encontrado = 0; // Eu uso essa flag para saber se devo imprimir a mensagem de erro no final
    
    printf("Digite o nome do produto: ");
    scanf(" %[^\n]", nomeBusca);
    printf("\n");
    
    /* crio um ponteiro auxiliar 'atual' 
     * que começa apontando para o topo da lista
     */
    Produto *atual = inicio;
    
    // Eu percorro a lista encadeada até o ponteiro cair no NULL
    while (atual != NULL) {
        /* * Eu usei o strcmp para comparar o nome armazenado no endereço atual 
         * com a string que o usuário digitou
         */
        if (strcmp(atual->nome, nomeBusca) == 0) {
            printf("=== Produto Encontrado ===\n");
            printf("ID: %d\n", atual->id);
            printf("Nome: %s\n", atual->nome);
            printf("Quantidade: %d\n", atual->quantidade);
            printf("Preco: %.2f\n\n", atual->preco);
            encontrado = 1;
            break; // Eu uso o break para parar de procurar assim que acho o item, poupando processamento
        }
        // Faço o ponteiro pular para o endereço do próximo nó
        atual = atual->prox;
    }
    
    if (!encontrado) {
        printf("Produto nao encontrado.\n");
    }
}

/* Função para buscar um produto pelo ID */
void buscarPorID(Estoque *e, int id) {
    Produto *atual = inicio;
    int encontrado = 0;
    
    // Eu faço a mesma travessia na lista encadeada que usei na busca por nome
    while (atual != NULL) {
        // Acessando diretamente o campo ID através do ponteiro da struct
        if (atual->id == id) {
            printf("=== Produto Encontrado ===\n");
            printf("ID: %d\n", atual->id);
            printf("Nome: %s\n", atual->nome);
            printf("Quantidade: %d\n", atual->quantidade);
            printf("Preco: %.2f\n\n", atual->preco);
            encontrado = 1;
            break;
        }
        atual = atual->prox; // Pulo pro próximo endereço
    }
    
    if (!encontrado) {
        printf("Produto nao encontrado.\n");
    }
}