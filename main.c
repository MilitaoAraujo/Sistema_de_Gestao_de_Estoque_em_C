#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produto.h"
#include "busca.h"
#include "editar.h"

//A lista começa vazia, então o primeiro endereço de "inicio" é "NULL" (inicio -> NULL)
/* * inicio é o nosso ponteiro Cabeça da Lista Encadeada Simples
 * Como ele armazena apenas um endereço de memória, e não os dados do produto em si,
 * a partir dele conseguimos rastrear o primeiro elemento e, consequentemente,
 * acessar todos os outros elementos da estrutura seguindo os ponteiros sucessores
 */
Produto *inicio = NULL; 

void inicializarEstoque(Estoque *e) {};

// Ferramentas:

//cria um produto novo na memória.
Produto* criaProduto(int id, char nome[], int quantidade, float preco) { 
    //a função "malloc" aloca o espaço na memória para salvar o novo produto.
    //(sizeof(Produto)) faz o malloc alocar o espaço exato necessário para a adição. 
    //"novo" guarda o endereço de memória do novo produto.
    
    /* * Usamos o malloc para alocar a struct na memória Heap, que é persistente,
     * em vez da memória Stack (que destruiria a struct ao fim desta função)
     * O casting '(Produto*)' converte o ponteiro genérico retornado pelo malloc 
     * para o formato de ponteiro da nossa struct Produto
     */
    Produto *novo = (Produto*) malloc(sizeof(Produto));

    /*
     * Como 'novo' é um PONTEIRO para a struct, usamos o operador seta (->) 
     * para acessar e modificar seus membros internos diretamente no endereço de memória
     */
    novo->id = id;
    strcpy(novo->nome, nome);
    novo->quantidade = quantidade;
    novo->preco = preco;
    novo->prox = NULL; // Fundamental inicializar como NULL para não apontar para lixo de memória

    return novo;
};

void adicionarProduto(Produto *novo) {
    /*
     * Para percorrer a lista, usamos ponteiros auxiliares ('atual' e 'anterior')
     * O ponteiro 'anterior' é essencial em listas simples (unidirecionais) para 
     * conseguirmos "costurar" o novo nó no meio da lista sem perder a referência de trás
     */
    Produto *atual = inicio;
    Produto *anterior = NULL;

    // Busca o local correto para inserir, mantendo a lista ordenada pelo ID
    while (atual != NULL && atual->id < novo->id) {
        anterior = atual;
        atual = atual->prox;
    }

    if (anterior == NULL) {
        //prox do novo produto será o endereço salvo em inicio, que é o endereço do último produto adicionado
        novo->prox = inicio; 
        //Agora, inicio aponta para o novo produto
        inicio = novo; 
    } 
    else {
        /*
         * Costurando a lista: O produto 'anterior' deixa de apontar para o 'atual' 
         * e passa a apontar para o 'novo'. O 'novo' passa a apontar para o 'atual'
         */
        anterior->prox = novo;
        novo->prox = atual;
    }
}

int inserirID() {
    char entrada[50];
    char *fim;
    long id;

    // Loop infinito que só é quebrado quando o usuário insere um dado válido e a função dá "return"
    while (1) {
        printf("Insira o ID do produto: ");
        /*
         * O espaço antes do % no scanf limpa o buffer do teclado (ignora enters residuais)
         * [^\n] faz com que o scanf leia tudo até o usuário apertar Enter, permitindo capturar espaços
         */
        scanf(" %[^\n]", entrada);

        /*
         * strtol tenta converter a string 'entrada' em um número na base 10
         * Passamos o endereço de 'fim' (&fim). Se o usuário digitar letras no meio dos números,
         * o ponteiro 'fim' vai apontar para essa letra, nos indicando que a conversão falhou
         */
        id = strtol(entrada, &fim, 10);

        // Se o ponteiro 'fim' não estiver apontando para o fim da string ('\0'), a entrada é inválida
        if (*fim != '\0') {
            printf("ID invalido. Digite apenas numeros inteiros.\n");
            continue; // Interrompe a iteração atual e volta para o início do while
        }

        if (id <= 0) {
            printf("O ID deve ser um numero positivo.\n");
            continue;
        }

        return (int)id; // Converte o long para int de forma explícita e retorna
    }
}

int inserirQuantidade() {
    char entrada[50];
    char *fim;
    long quant;

    // Mesma lógica de validação do ID, garantindo que o programa não quebre com letras
    while (1) {
        printf("Insira a quantidade de unidades do produto: ");
        scanf(" %[^\n]", entrada);

        quant = strtol(entrada, &fim, 10);

        if (*fim != '\0') {
            printf("Quantidade invalida. Digite apenas numeros inteiros.\n");
            continue;
        }

        if (quant <= 0) {
            printf("A quantidade deve ser um numero inteiro positivo.\n");
            continue;
        }

        return (int)quant;
    }
}

char* inserirNome(char nome[]) {
    printf("Insira o nome do produto: ");
    // Lê a string inteira digitada, incluindo espaços, até quebrar a linha
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

        // strtof converte a entrada para número decimal
        preco = strtof(entrada, &fim);

        // Valida se o usuário digitou algum caractere não numérico
        if (*fim != '\0') {
            printf("Preco invalida. Digite apenas numeros.\n");
            continue;
        }

        if (preco <= 0) {
            printf("O preco deve ser um numero positivo.\n");
            continue;
        }

        return preco;
    }
}

int idJaExiste(int id) {
    Produto *atual = inicio;
    /*
     * O ponteiro 'atual' pula de endereço em endereço
     * percorrendo a lista linearmente até achar o ID ou chegar ao fim 
     */
    while (atual != NULL) {
        if (atual->id == id) {
            return 1; // Retorna 1 (Verdadeiro) sinalizando que encontrou a duplicata
        }
        atual = atual->prox; // Avança para o próximo nó
    }
    return 0;
}

int nomeJaExiste(char nome[]) {
    Produto *atual = inicio;
    while (atual != NULL) {
        /*
         * A função strcmp compara as duas strings
         * Se forem exatamente iguais, ela retorna 0
         */
        if (strcmp(atual->nome, nome) == 0) {
            return 1;
        }
        atual = atual->prox;
    }
    return 0;
}

// Funções do Menu:
void cadastrarProduto() {
    // Coleta as entradas e faz as verificações de duplicidade antes de instanciar o nó
    int id = inserirID();

    if (idJaExiste(id)) {
        printf("Erro: Já existe um produto com esse ID.\n\n");
        return; // Sai da função de cadastro prematuramente se houver erro
    }
    
    char nome[50];
    inserirNome(nome);

    if (nomeJaExiste(nome)) {
        printf("Erro: Já existe um produto com esse nome.\n\n");
        return;
    }

    int quantidade = inserirQuantidade();
    float preco = inserirPreco();

    // Se passou por todas as barreiras, o produto é criado e adicionado à lista
    Produto *novo = criaProduto(id, nome, quantidade, preco);

    adicionarProduto(novo);
    printf("Produto adicionado com sucesso.\n");
}

void removerProduto(Estoque *e, int id) {
    Produto *atual = inicio;
    Produto *anterior = NULL;

    //anda casas enquanto não encontrar o ID correto
    while (atual != NULL && atual->id != id) { 
        anterior = atual;
        atual = atual->prox;
    }

    //Caso percorra a lista até chegar no NULL
    if (atual == NULL) {
        printf("Produto nao encontrado.\n");
        return;
    }

    //Caso o primeiro elemento seja o elemento a ser removido
    if (anterior == NULL) {
        inicio = atual->prox; //inicio -> NULL
    }
    else { 
        // Caso seja do 2º elemento para frente:
        // substitui o "prox" do elemento anterior ao que será removido
        anterior->prox = atual->prox; 
    }

    // libera o endereço de memória do item selecionado, removendo-o
    /*
     * Apenas religa os ponteiros remove o item da lógica da lista, mas o bloco 
     * de memória continuaria ocupado indevidamente causando um Memory Leak então O free
     * devolve esse espaço de memória para o sistema operacional
     */
    free(atual); 

    printf("Produto removido com sucesso.\n");
}

void listarProdutos(Estoque *e) {
    Produto *atual = inicio;

    // Tratamento básico para evitar listar uma lista vazia
    if (atual == NULL) {
        printf("Não há produtos cadastrados.\n");
        return;
    }

    printf("\n--- LISTA DE PRODUTOS ---\n");
    // Percorre todos os nós e imprime seus membros
    while(atual != NULL) {
        printf("ID: %d\n", atual->id);
        printf("Nome: %s\n", atual->nome);
        printf("Quantidade: %d\n", atual->quantidade);
        printf("Preco: %.2f\n\n", atual->preco); // .2f formata o float para 2 casas decimais

        atual = atual->prox; 
    }
    printf("------------------------------------------\n");
}

void analisarEstoque(Estoque *e) {
    Produto *atual = inicio;

    if (atual == NULL) {
        printf("Estoque vazio.\n");
        return;
    }

    // Variáveis acumuladoras para totais do estoque
    int totalProdutos = 0;
    int totalUnidades = 0;
    float valorTotal = 0.0;

    /*
     * Usamos ponteiros para guardar a referência do nó inteiro que detém os recordes 
     * maiormenor quantidade e preço, em vez de criar variáveis soltas para copiar 
     * os dados da struct
     */
    Produto *maiorQuantidade = atual;
    Produto *maisCaro = atual;
    Produto *maisBarato = atual;
    Produto *menorQuantidade = atual;

    // Iteração única que levanta todas as estatísticas simultaneamente
    while (atual != NULL) {
        totalProdutos++; // Incrementa a quantidade de nós únicos
        totalUnidades += atual->quantidade; // Acumula o volume total de itens
        valorTotal += atual->quantidade * atual->preco; // Acumula o valor monetário

        // Estruturas de decisão para atualizar os ponteiros recordistas, se necessário
        if (atual->quantidade > maiorQuantidade->quantidade) {
            maiorQuantidade = atual;
        }
        if (atual->preco > maisCaro->preco) {
            maisCaro = atual;
        }
        if (atual->preco < maisBarato->preco) {
            maisBarato = atual;
        }
        if (atual->quantidade < menorQuantidade->quantidade) {
            menorQuantidade = atual;
        }

        atual = atual->prox; // Pula para o próximo nó
    }

    // Impressão do relatório final acessando os dados através dos ponteiros salvos
    printf("===== ANALISE DO ESTOQUE =====\n");
    printf("Total de produtos cadastrados: %d\n", totalProdutos);
    printf("Total de unidades no estoque: %d\n", totalUnidades);
    printf("Valor total do estoque: R$ %.2f\n\n", valorTotal);
    printf("Produto com maior quantidade: %s (%d unidades)\n", maiorQuantidade->nome, maiorQuantidade->quantidade);
    printf("Produto mais caro: %s (R$ %.2f)\n", maisCaro->nome, maisCaro->preco);
    printf("Produto mais barato: %s (R$ %.2f)\n", maisBarato->nome, maisBarato->preco);
    printf("Produto com menor quantidade: %s (%d unidades)\n", menorQuantidade->nome, menorQuantidade->quantidade);
    printf("\n");
}

/*
 * Ponto de partida do codigo
 * É aqui que a execução se inicia e onde controlamos o fluxo principal com o menu
 */
int main () {
    // Instancia a estrutura controladora do estoque na memória Stack
    Estoque var_estoque;
    inicializarEstoque(&var_estoque);

    int opcao = -1; // Inicializada com -1 para garantir a entrada no loop

    // Loop principal da aplicação. Mantém o sistema rodando até o usuário pedir para sair
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

        // Estrutura de roteamento que chama as funções de acordo com a escolha do usuário
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
            printf("Opção inválida. Tente novamente.\n"); // Tratamento caso digitem número inexistente no menu
        }
    }

    return 0; // Sinaliza ao sistema operacional que o programa executou e encerrou sem erros
}