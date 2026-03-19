#include "busca.h"

/*extern avisa que a variável 'inicio' já foi criada no main.c e será compartilhada aqui. */
extern Produto *inicio;

/* Função para buscar um produto pelo nome digitado pelo usuário */
void buscarPorNome(Estoque *e) {
    char nomeBusca[50];// Variável local para armazenar o que o usuário digitar.
    int encontrado = 0; // Flag para controlar se o produto foi localizado ou não.
    
    printf("Digite o nome do produto: ");
    scanf(" %[^\n]", nomeBusca);// Lê o nome permitindo espaços.
    printf("\n");
    
    /* crio um ponteiro auxiliar 'atual' 
     * que começa apontando para o inicio da lista
     */
    Produto *atual = inicio;
    
    // Enquanto o ponteiro não apontar para o vazio (fim da lista)...
    while (atual != NULL) {
        /* * Eu usei o strcmp para comparar o nome armazenado no endereço atual 
         * com a string que o usuário digitou
         */
        if (strcmp(atual->nome, nomeBusca) == 0) {//caso o produto seja encontrado,
            printf("=== Produto Encontrado ===\n")//exibe os dados do nó atual.
            printf("ID: %d\n", atual->id);
            printf("Nome: %s\n", atual->nome);
            printf("Quantidade: %d\n", atual->quantidade);
            printf("Preco: %.2f\n\n", atual->preco);
            encontrado = 1;
            break; // Interrompe o loop para economizar processamento.
        }
        // Faço o ponteiro pular para o endereço do próximo nó
        atual = atual->prox;
    }
    
    if (!encontrado) {
        printf("Produto nao encontrado.\n");// Mensagem caso a lista acabe sem achar nada.
    }
}

/* Função para buscar um produto pelo ID */
void buscarPorID(Estoque *e, int id) {
    Produto *atual = inicio; // Inicia a navegação pelo inicio da lista.
    int encontrado = 0;
    
    // Eu faço a mesma travessia na lista encadeada que usei na busca por nome
    while (atual != NULL) {
        // Acessando diretamente o campo ID através do ponteiro da struct.
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