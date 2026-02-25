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
    char entrada[50];
    char *fim;
    long id;

    while (1) {
        printf("Insira o ID do produto: ");
        scanf(" %[^\n]", entrada);

        id = strtol(entrada, &fim, 10);

        // Verifica se é inteiro válido
        if (*fim != '\0') {
            printf("ID invalido. Digite apenas numeros inteiros.\n");
            continue;
        }

        // Verifica se é positivo
        if (id <= 0) {
            printf("O ID deve ser um numero inteiro positivo.\n");
            continue;
        }

        return (int)id;
    }
}

int inserirQuantidade() {
    char entrada[50];
    char *fim;
    long quant;

    while (1) {
        printf("Insira a quantidade de unidades do produto: ");
        scanf(" %[^\n]", entrada);

        quant = strtol(entrada, &fim, 10);

        // Verifica se é inteiro válido
        if (*fim != '\0') {
            printf("Quantidade invalida. Digite apenas numeros inteiros.\n");
            continue;
        }

        // Verifica se é positivo
        if (quant <= 0) {
            printf("A quantidade deve ser um numero inteiro positivo.\n");
            continue;
        }

        return (int)quant;
    }
}

char* inserirNome(char nome[]) {
    printf("Insira o nome do produto: ");
    scanf(" %[^\n]", nome);
    return nome;
}

float inserirPreco() {
    char entrada[50];
    char *fim;
    float preco;

    while (1) {
        printf("Insira o preco do produto: ");
        scanf(" %[^\n]", entrada);

        preco = strtof(entrada, &fim);

        // Verifica se é número válido
        if (*fim != '\0') {
            printf("Preco invalida. Digite apenas numeros.\n");
            continue;
        }

        // Verifica se é positivo
        if (preco <= 0) {
            printf("O preco deve ser um numero positivo.\n");
            continue;
        }

        return preco;
    }
}

int idJaExiste(int id) {
    Produto *atual = inicio;

    while (atual != NULL) {
        if (atual->id == id) {
            return 1; // ID já existe
        }
        atual = atual->prox;
    }

    return 0; // ID não existe
}

int nomeJaExiste(char nome[]) {
    Produto *atual = inicio;

    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            return 1; // Nome já existe
        }
        atual = atual->prox;
    }

    return 0; // Nome não existe
}

// Funções do Menu:
void cadastrarProduto() {
    int id = inserirID();

    if (idJaExiste(id)) {
        printf("Erro: Já existe um produto com esse ID.\n\n");
        return;
    }
    
    char nome[50];
    inserirNome(nome);

    if (nomeJaExiste(nome)) {
        printf("Erro: Já existe um produto com esse nome.\n\n");
        return;
    }

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
    Produto *atual = inicio;

    if (atual == NULL) {
        printf("Estoque vazio.\n");
        return;
    }

    int totalProdutos = 0;
    int totalUnidades = 0;
    float valorTotal = 0.0;

    Produto *maiorQuantidade = atual;
    Produto *maisCaro = atual;
    Produto *menorQuantidade = atual;

    while (atual != NULL) {
        totalProdutos++;
        totalUnidades += atual->quantidade;
        valorTotal += atual->quantidade * atual->preco;

        if (atual->quantidade > maiorQuantidade->quantidade) {
            maiorQuantidade = atual;
        }

        if (atual->preco > maisCaro->preco) {
            maisCaro = atual;
        }

        if (atual->quantidade < menorQuantidade->quantidade) {
            menorQuantidade = atual;
        }

        atual = atual->prox;
    }

    printf("===== ANALISE DO ESTOQUE =====\n");
    printf("Total de produtos cadastrados: %d\n", totalProdutos);
    printf("Total de unidades no estoque: %d\n", totalUnidades);
    printf("Valor total do estoque: R$ %.2f\n\n", valorTotal);

    printf("Produto com maior quantidade: %s (%d unidades)\n",
           maiorQuantidade->nome, maiorQuantidade->quantidade);

    printf("Produto mais caro: %s (R$ %.2f)\n",
           maisCaro->nome, maisCaro->preco);

    printf("Produto com menor quantidade: %s (%d unidades)\n",
           menorQuantidade->nome, menorQuantidade->quantidade);

    printf("\n");
}

int main () {
    Estoque var_estoque;
    inicializarEstoque(&var_estoque);

    int opcao = -1;

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
        } else if (opcao == 7) {
            analisarEstoque(&var_estoque);
        } else if (opcao == 0) {
            printf("Encerrando programa...\n");
        } else {
            printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}