#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produto.h"
#include "busca.h"
#include "editar.h"

Produto *inicio = NULL;

void inicializarEstoque(Estoque *e) {};

// Ferramentas:
Produto* criaProduto(int id, char nome[], int quantidade, float preco) { // cria um produto novo na memória.
    Produto *novo = (Produto*) malloc(sizeof(Produto));
    // a função "malloc" aloca o espaço na memória para salvar o novo produto.
    // "(sizeof(Produto))" faz o malloc alocar o espaço exato necessário para a adição. 
    // "novo" guarda o endereço de memória do novo produto.
    novo->id = id;
    strcpy(novo->nome, nome);
    novo->quantidade = quantidade;
    novo->preco = preco;
    novo->prox = NULL;

    return novo;
};

void adicionarProduto(Produto *novo) {
    novo->prox = inicio; // "prox" do novo produto será o endereço salvo em "inicio", que é o endereço do último produto adicionado.
    inicio = novo; // Agora, inicio aponta para o novo produto.
}

int inserirID() {
    int id;
    printf("Insira o ID do produto: ");
    scanf("%d", &id);
    printf("\n");
    return id;
}

int inserirQuantidade() {
    int quant;
    printf("Insira a quantidade de unidades do produto: ");
    scanf("%d", &quant);
    printf("\n");
    return quant;
}

char* inserirNome(char nome[]) {
    printf("Insira o nome do produto: ");
    scanf("%s", nome);
    printf("\n");
    return nome;
}

int inserirPreco() {
    int preco;
    printf("Insira o preço do produto: ");
    scanf("%d", &preco);
    printf("\n");
    return preco;
}

// Funções do Menu:
void cadastrarProduto() {
    int id = inserirID();

    char nome[50];
    inserirNome(nome);

    int quantidade = inserirQuantidade();

    float preco = inserirPreco();

    Produto *novo = criaProduto(id, nome, quantidade, preco);

    adicionarProduto(novo);
    printf("Produto adicionado com sucesso.\n");
}


void removerProduto(Estoque *e, int id) {
    Produto *atual = inicio;
    Produto *anterior = NULL;

    while (atual != NULL && atual->id != id) { // anda casas enquanto não encontrar o ID correto
        anterior = atual;
        atual = atual->prox;
    }

    // Caso percorra a lista até chegar no NULL:
    if (atual == NULL) {
        printf("Produto nao encontrado.\n");
        return;
    }

    // Caso o primeiro elemento seja o elemento a ser removido (o que inicio aponta):
    if (anterior == NULL) {
        inicio = atual->prox; // inicio -> NULL
    }
    else { // Caso seja do 2º elemento para frente:
        anterior->prox = atual->prox; // substitui o "prox" do elemento anterior ao que será removido.
    }

    free(atual); // libera o endereço de memória do item selecionado, removendo-o

    printf("Produto removido com sucesso.\n");
}

void listarProdutos(Estoque *e) {
    Produto *atual = inicio;

    if (atual == NULL) {
        printf("Não há produtos cadastrados.\n");
        return;
    }

    while(atual != NULL) {
        printf("ID: %d\n", atual->id);
        printf("Nome: %s\n", atual->nome);
        printf("Quantidade: %d\n", atual->quantidade);
        printf("Preco: %.2f\n\n", atual->preco);

        atual = atual->prox;
    }
}

void analisarEstoque(Estoque *e) {
    // Serão exibidas informações gerais do estoque (quantidade de produtos cadastrados, limite do estoque etc.)
}

int main () {
    Estoque var_estoque;
    inicializarEstoque(&var_estoque);

    int opcao;

    while (opcao != 0) {
        printf("| | |  | MENU |  | | |\n");
        printf("1. Adicionar produto\n");
        printf("2. Remover produto\n");
        printf("3. Listar produtos\n");
        printf("4. Buscar produto pelo nome\n");
        printf("5. Buscar produto por ID\n");
        printf("6. Editar produto\n");
        printf("7. Analisar estoque\n");
        printf("0. Encerrar programa\n");
        printf("Escolha uma opção: ");

        scanf("%d", &opcao);
        printf("\n");
        if (opcao == 1) {
            cadastrarProduto();
        } else if (opcao == 2) {
            removerProduto(&var_estoque, inserirID());
        } else if (opcao == 3) {
            listarProdutos(&var_estoque);
        } else if (opcao == 4) {
            buscarPorNome(&var_estoque);
        } else if (opcao == 5) {
            buscarPorID(&var_estoque, inserirID());
        } else if (opcao == 6) {
            editarProduto(&var_estoque, inserirID());

        }
    }

    return 0;
}