# Sistema de Gestão de Estoque

Sistema de gerenciamento de inventário desenvolvido em **C** para a disciplina de **Linguagem de Programação I**.

---

### Funcionalidades

- Adicionar produto
- Remover produto
- Listar produtos
- Buscar produto pelo nome
- Buscar produto por ID
- Editar produto (nome, quantidade, preço)
- Analisar estoque


### Arquivos do Projeto

| Arquivo | Descrição |
|---------|------------|
| main.c | Funções principais (cadastrar, remover, listar) |
| produto.h | Definição das structs Produto e Estoque |
| busca.c / busca.h | Funções buscarPorNome e buscarPorID |
| editar.c / editar.h | Função editarProduto |

---

### Como Executar

#### Via Terminal

```powershell
gcc main.c busca.c editar.c -o programa ; .\programa
```

#### Via Extensão C/C++

1. Instale a extensão **C/C++ (Microsoft)**
2. No canto superior direito, clique no ícone de **Play**
3. Selecione o compilador **gcc** para iniciar

> **Nota**: Ao executar via extensão, configure o tasks.json para compilar todos os arquivos juntos (`main.c busca.c editar.c`).
 **Nota**: Devido a problemas em rodar o codigo em C no vscode é altamente recomendavel rodar o programa no OnlineGDB.

---

### Equipe

* **Militão Araujo Duarte do Rêgo**
* **Aryendrew Arnold da Silva Oliveira**
* **Karlos Eduardo Saraiva da Silva**

<p align="center">UEPB - Campina Grande/PB</p>
